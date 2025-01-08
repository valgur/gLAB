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
 * File: output.c
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
 * Change Log: First public version
 * -------------
 *          gLAB v1.3.2
 * Release: 2010/02/02
 * Change Log: Imported SATDIFF, SATSTAT and SATSTATTOT printing from gLAB.c
 *             Added satellite SATPVT message
 *             Change in SATDIFF and CS messages to show the GNSS system that 
 *                  the satellite belongs to
 *             It is now possible to print in the MODEL and SATPVT messages 
 *                  the inertial velocity of the satellite
 *             PREFIT message now includes the weight that will be applied to 
 *                  the filter
 *             ZTD and estimated residual tropospheric delay is now printed 
 *                  in the FILTER message
 *             Forward/Backward processing included
 *             SATSTAT message will now provide the GNSS system it refers to
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: Included prealignCP option to set/unset carrier-phase prealignment
 *             C1/P1 flexibility option is added to allow flexible handling of C1 and P1
 *             Receiver apriori position INFO message now provides the origin of the
 *                  position
 *             Changed printInput and printMeas function to show all the measurements 
 *                  independently that they have been set as available or unavailable
 *             Corrected a bug when computing the position in trajectories
 *             Cycle-slip detector changed to specify when it does not have enough measurements
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/08/19
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
 * Change Log: Included new DCB management.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: Tropospheric correction option is extended to select independently the nominal and mapping used.
 *             Dilution Of Precision extension: (GDOP, PDOP, TDOP, VDOP, HDOP) new variables.
 *             Some minor floating length adjustments. 
 *             Filter 'inf' value for clock and coordinates noise process and initial covariance substituted
 *                  to real floating quantities.
 * -----------
 * Release: 2012/12/31
 * Change Log: gLAB version released together with the Educational Book:
 *             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
 *             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
 *             ISBN: 978-92-9221-885-0 (two volumes)
 *             ISSN: 1013-7076
 *             December 2012.
 *
 *             SATSEL debugging message included in the output messages.
 * -----------
 *          gLAB v2.2.0
 * Release: 2014/09/22
 * Change Log: Added cycle slip L1C1 initial value in  message "INFO PREPROCESSING CycleSlip L1C1".
 *	       Added the following INFO message "INFO MODELLING Satellite mass centre to Antenna Phase Centre (APC) correction: ON/OFF"
 *	       Added text messages when using BeiDou, NeQuick, F-PPP for ionospheric models, or ESA's tropospheric model or
 *			IONEX, F-PPP DCB values.
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
 *             Added printUserError function for printing user-defined error.
 *             Modifications regarding PRINT INFO (PREPROCESSING) and PRINT CS.
 *             Modified printSatSel function (now prints epoch and constellation)
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: SATSEL messages may have an '*' if the model will be recalculated before computing the 
 *                     navigation solution (only in SBAS mode).
 *             Modified "Receiver apriori position" INFO message for parameters 'calculateRINEX' and 'calculateUSER'.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: Added Number of samples to L1C1 and BW cycle-slip info messages.
 *             Fixed a '*' that was in incorrect position in MODEL messages in SBAS mode.
 *             The '[NPA only]' tag from SBASUNSEL message number 36 has been erased.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added functions to convert RTCM binary files.
 *             Added printDGNSS message.
 *             Added functions for SBAS plots mode.
 *             Added function to print KML file.
 *             Added function to print SP3 file.
 *             Added INFO messages for transmission time of message check in navigation files and for the Step detector.
 *             Modified printCS to distinguish between Rover and Reference Station when DGNSS is activated.
 *             SBAS messages are now printed sorted by message type (SBASIONO, SBASCORR,...) instead of PRN.
 *             Added flag at the end of the OUTPUT message to indicate the type of processing used in each epoch.
 *             Fixed MODEL/SBASCORR/SBASVAR messages not being printed with an '*' when gLAB changed from PA to NPA mode
 *                 due to discarded satellites from non SBAS criteria (such as low elevation).
 *             Added spaces in EPOCHSAT and OUTPUT messages after the label to align columns with other gLAB messages.
 *             Added header and format to Stanford-ESA output file.
 *             Added INFO messages for Stanford-ESA output file and its parameters.
 *             Added INFO message for use of sigma of the ionosphere when IONEX, F-PPP or SBAS iono model are used.
 *             Added function to print SBAS summary.
 *             Added INFO message for the GDOP threshold when there is a threshold set.
 *             Added INFO message for satellite and receiver phase center variation corrections.
 *             Added SBASUNSEL messages number 46 and 47.
 *             Taken out degree sign from output messages to avoid text encoding problems.
 *             INPUT and MEAS messages will now print GPS P1 and P2 corrected with P1-C1 DCB if P1-C1 DCB treatment is
 *               set to strict and GPS receiver is known.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Added INFO line for prefit outlier detectors.
 *             Added INFO line for N-consecutive check.
 *             Added fields to last line of SBAS summary for Stanford-ESA values (this fields will appear even if
 *               Stanford-ESA has not been enabled).
 *             Fields 'MIs', 'Hor_MIs' and 'Ver_MIs' in SBAS summary now will always show the MIs for all in view
 *               satellites combination, as there are now new fields for Stanford-ESA MIs values.
 *             Changed measurement name in converted RINEX files from RTCM v3 from 'C1W', 'L1W', 'S1W', 'C2W', 'L2W', 'S2W'
 *               to 'C1P', 'L1P', 'S1P', 'C2P', 'L2P', 'S2P' respectively.
 *             Added line "Total epochs processed with NPA solution" in SBAS summary. It will only appear if mode switching
 *               has been enabled.
 *             If user forced NPA processing mode in parameters, all values in SBAS summary will be referred to NPA.
 *             Fixed incorrect year formatting in writing a EMS file when SBAS messages were read from a RINEX-B file.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   Added field "Vertical positioning error" in SBASOUT message. This field is the absolute value
 *                 of the north error. With this field it is easier to do VPE/VPL plots.
 *               If current GEO is under alarm and there are other GEO also under alarm, the remaining alarm
 *                 in the SBASUNSEL will be of the selected GEO, instead of the last GEO under alarm processed.
 *               When an incorrect message is read, now it will be written to RINEX-B or EMS file (before it was
 *                 not written), due to the effect of reading an incorrect message or not reading any message is
 *                 not equivalent.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Added INFO print for L1C1 consistency check.
 *               Added SNR field at the end of the MODEL message. gLAB will search first for the "S" measurement in the
 *                 observation file. If it is not present, it will search for the SNR flag in the current measurement.
 *                 If no SNR is available, 999 will be printed in this field.
 *               Added troposhere wet mapping and arc number at the end of the PREFIT message.
 *               Added number of satellites used in the solution computation in the penultimate field of the OUTPUT message.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added INFO messages with the KML ranges selected.
 *               Added 'printDates' and 'printCoordinates' functions for printing the results
 *                 of date or coordinates conversion (for conversion mode only).
 *               Added 'writeReffile' function for writing a reference position file.
 *               Data Gap INFO message will now appear as OFF when all cycle-slip detectors
 *                 are disabled instead of showing the data gap size (this correspons to the
 *                 internal logical of gLAB).
 *               Changed N-consecutive INFO message from "INFO PREPROCESSING Cycle-slip N-Con:"
 *                 to "INFO PREPROCESSING N-consecutive:", as the N-consecutive function is
 *                 a blind measurement filter, not a cycle-slip detector.
 *               In DGNSS mode, epochs in SPP will be shown in red in the output KML instead
 *                 of being empty.
 *               In SBAS mode, epochs in NPA will be shown in red in the output KML instead
 *                 of being empty.
 *               Fixed problem with carriage returns when writing SBAS converted files and
 *                 SBAS conversion log when sbas source file has a different line ending
 *                 than the current operative system.
 *               Fixed bug that applied a wrong DCB when printing P1 and P2 GPS measurements 
 *                 in MEAS message when receiver was set to type 1 or type 2. 
 *               SBASUNSEL message will now print the number of missing or wrong 
 *                 consecutive messages instead of always writing "4 or more consecutive...".
 *               Fixed bug in MEAS message that made to apply wrong DCBs to GPS P1 measurements
 *                 when DCB P1-C1 was set to strict.
 *               Fixed bug with wrong decimation in KML timestamps due to an integer overflow.
 *                 This bug was introduced in version 4.2.0 when decimal decimation was added.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   Added function 'writeObsRinexEpochUserAddedError' for writing RINEX observation file
 *                 with user added error.
 *               Fixed KML timestamps not being written to file when observation file timestamps where 
 *                 inconsistent (for example 1.000304, 2.000304, ...).
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log:   Added a INFO message with number of threads used during the processing (gLAB needs to be
 *                 rebuild with '-fopenmp' in order to enable multithreading).
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log:   Added a INFO message with the list of SBAS GEO satellites excluded (for SPP, PPP, SBAS and DGNSS modes).
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log:   Added a INFO message with the URA threshold for discarding satellites.
 *               Added a INFO message with the UDREI threshold for discarding satellites.
 *               Modified the INFO message with the measurements selected and their weights. Now gLAB will group the
 *                satellites with the same weight mode and print one line for each group and measurement.
 *               Added discard reason "Satellite has an UDREI value of <value> (user threshold is <threshold>)" in
 *                 SBASUNSEL message.
 *               Added SPP, PPP and DGNSS summary.
 *               Added start and end epoch to summary.
 *               Changed print order of SBAS summary line "Total epochs skipped due to GDOP exceeding ...". Now it will
 *                 be printed just below the other lines containing "Total epochs skipped due to ...".
 *               Changed all lines in the SBAS summary containing "Total samples" to "Total geometries".
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log:   Added INFO message for HDOP, PDOP and HDOPorPDOP thresholds options.
 *               Added INFO message for KML files EGM96 geoid model option.
 *               Added in SPP/PPP/SBAS/DGNSS summaries the number of epochs with data gap. The data gap count
 *                 is breakdown in different messages. If no epochs were decimated, it will show the number of
 *                 data gaps in during the summary period all data gaps in the whole file. If data was decimated,
 *                 it will show the number of data gaps not decimated in the summary period 
 *                 (i.e. the data gap had en epoch in the summary period which would have been processed), the 
 *                 number of data gaps in the summary period which only had epochs that would have been decimated
 *                 and the total number of data gaps in the whole file.
 *               Added in SPP/PPP/SBAS/DGNSS summaries the percentile and maximum values of of HDOP, VDOP, PDOP, 
 *                 GDOP and TDOP. This values have also been added to the last line of the summary.
 *               Added in SBAS summary the continuity risk for maritime. It has also been added in the last line
 *                 of the summary.
 *               Added computation of EGM96 geoid height when writing to the KML file.
 *               Changed in SBAS summary the line "Continuity Risk" to "Continuity Risk Airborne".  
 *               Fixed bug when checking for discontinuity at the end of the hour in hourly SBAS continuity 
 *                 risk maps. This bug made that a false discontinuity was always added at all hourly maps 
 *                 except at hour 0.
 *               Fixed bug in SBAS summary that made the percentage of line "Total epochs skipped (any reason)"
 *                 not being 0 when no epoch had been included in the summary.
 *               Fixed bug in SPP/PPP/SBAS/DGNSS summaries that made to always compute the 95 percentile instead
 *                 of the user defined percentile.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log:   Added function 'printBuffersBestGEO' for printing data buffered when option select best GEO
 *                 is enabled. If option 'printSBASUNUSED' is enabled, it will print first all the messages
 *                 from the discarded GEOs.
 *               Added INFO message for GEO acquisition time.
 *               Added INFO message for GEO switching cooltime.
 *               Several 'static' variables in different functions now have below the OpenMP directive
 *                 '#pragma omp threadprivate()' to avoid race conditions in multithreading.
 *               Fixed last epoch of discontinuities ocurring at the end of each hour (except at hour 23)
 *                 being computed with an extra epoch at the end (the first epoch of the next hour). That
 *                 is, these discontinuities were an epoch longer due to the last epoch was considered as
 *                 the first epoch of the next hour, instead of the last epoch of the current hour. This 
 *                 did not affect the continuity risk computation.
 *               Fixed incorrect number given in "Total epochs missing in observation file (during summary
 *                 period and decimated" and in "Total epochs missing in observation file (during summary 
 *                 period)" reported in the summary (in all modes) when decimation was greater than the
 *                 observation file data interval.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log:   Fixed incorrect data interval written in the header of the output SP3 file created by
 *                 gLAB. This ocurred when the decimation set by the user was smaller than the
 *                 RINEX observation data rate.
 *               Fixed wrong GEO PRN print in SBASOUT message when option to select best GEO was
 *                 enabled. Function 'printBuffersBestGEO' now sets the variable with the GEO PRN
 *                 used for printing the GEO PRN in the SBASOUT message.
 * -----------
 *          gLAB v5.4.2
 * Release: 2019/03/08
 * Change Log:   Added INFO messages in SBAS processing mode for Kh and Kv values.
 *               Added INFO messages in SBAS processing mode for SBAS receiver type used.
 *               If any of the HDOP, PDOP or GDOP filters is disabled, it will print an
 *                 INFO message stating that it is OFF, instead of not printing anything.
 *               Changed INFO messages in SBAS processing mode for SBAS messages timeouts.
 *                 If any of these messages are disabled (such as MT10), instead of
 *                 appearing its timeout, it will print "Message disabled".
 * -----------
 *          gLAB v5.4.3
 * Release: 2019/03/20
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.4
 * Release: 2019/05/10
 * Change Log:   Fixed incorrect print of SNR value in MODEL message when using
 *                 RINEX 2 files and the SNR was read as a measurement.
 * -----------
 *          gLAB v5.5.0
 * Release: 2020/11/13
 * Change Log:   When user selects an end epoch which is after the last epoch in the RINEX observation file,
 *                the last epoch of summary shown in the summary will be the last epoch processed, not the
 *                last epoch set by the user.
 *               Fixed incorrect number of epochs missing in summary when the user selects an end epoch
 *                which is after the last epoch available in the RINEX observation file.
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
 *               Added SFCSDATA, MWCSDATA, LICSDATA, and IGFCSDATA containing internal computations for each
 *                 cycle-slip detector.
 *               Added SBASDFMCCORR, SBASDFMCVAR and SBASDFMCUNSEL messages for SBAS DFMC.
 *               All output messages changed to add additional information. Some of the common changes are
 *                 that the epoch is also printed in format "HH:MM:SS.zz" as well as per satellite messages
 *                 also include the satellite block, SVN (if ANTEX is provided), arc number and arc length.
 *               INFO messages at the start of the output file containing gLAB internal configuration will
 *                 print the configuration with ranges of satellites in order to minimize the number of lines.
 *               Printing functions have been optimized by either returning the pointer to a constant array
 *                 (instead of copying the string to another variable) or by computing only once per epoch
 *                 fields which are common to all messages (e.g. epoch).
 *               Last line of summary now has the column number between brackets in the fields with names.
 *               INPUT message has been deprecated, only left for compatibility reason. Use MEAS messsage
 *                 instead.
 *               Fixed wrong number of epochs missing in summary when decimation was higher than the
 *                 observation file data rate and the last epoch of the observation file was not 
 *                 processed due to the decimation.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "input.h"
#include "output.h"
#include "dataHandling.h"
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#if defined __WIN32__
 	//Windows.h used for GetProcessTimes function, which retrieves time spent by process
 	//The windows include has to be added at the end otherwise compilation fails
	#include <windows.h>
#else
 	//Library "sys/resource.h" does not exist in Windows
	#include <sys/resource.h>
#endif


/**************************************
 * Declarations of internal operations
 **************************************/

/*****************************************************************************
 * Name        : printDisabledGLONASS
 * Description : Print disabled GLONASS satellites due to missing k
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printDisabledGLONASS(TOptions *options) {


	int						i, j, l;
	int						SelectedAMeas;
	int						initPRN;
	char					auxstrGLO[3][MAX_INPUT_LINE];
	TRangeList 				List;
	


	//Print disabled GLONASS FDMA frequencies
	for(i=1;i<=2;i++) {
		SelectedAMeas=0;
		for (j=1;j<=listMaxSatGNSS[GLONASS];j++) {
			if (options->includeSatellite[GLONASS][j]==0) continue;
			if (options->GLOsatFDMAdisabled[GLONASS][j][i]==1) {
				InitRangeList(GLONASS,j,&List);
				initPRN=j;
				l=0;
				SelectedAMeas=1;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==0) {
			//No satellites unselected
			sprintf(auxstrGLO[i],"-");
		} else {
			for (j=initPRN;j<=listMaxSatGNSS[GLONASS];j++) {
				if (options->includeSatellite[GLONASS][j]==0) {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if (j<=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
							List.listSatGNSS[l][List.numJumpslist[l]-1][1]=GLONASS;
							List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
						} else {
							List.listSatGNSS[l][List.numJumpslist[l]-1][1]=GLONASS;
							List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
						}
					}
				} else {
					if (options->GLOsatFDMAdisabled[GLONASS][j][i]==0) {
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							List.listSatGNSS[l][List.numJumpslist[l]-1][1]=GLONASS;
							List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
						}
					} else if (j!=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
						//The current satellite has the frequency unselected
						//Check if previous satellite had the frequency unselected. If not, add a new range
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
							ExtendRangeList(GLONASS,j,l,&List);
						} 
					}
				}
			}
			if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
				List.listSatGNSS[l][List.numJumpslist[l]-1][1]=GLONASS;
				List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[GLONASS];
			}
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstrGLO[i]);
			freeRangeList(&List);
		}
	}

	//Check if both unselected satellites per frequencies are equal
	if (strcmp(auxstrGLO[1],auxstrGLO[2])==0) {
		if (auxstrGLO[1][0]!='-') {
			fprintf(options->outFileStream,"INFO%s GLONASS FDMA frequencies disabled (no frequency number): 1|2 %s\n",options->workMode<=wmSHOWINPUT?" PREPROCESSING":"",auxstrGLO[1]);
		}
	} else {
		for(i=1;i<=2;i++) {
			if (auxstrGLO[i][0]=='-') continue;
			fprintf(options->outFileStream,"INFO%s GLONASS FDMA frequency disabled (no frequency number): %d %s\n",options->workMode<=wmSHOWINPUT?" PREPROCESSING":"",i,auxstrGLO[i]);
		}
	}

 }

/*****************************************************************************
 * Name        : printConstFreqDisabled
 * Description : Print constellations disabled due to unexistent frequncies
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
 void printConstFreqDisabled(TOptions *options) {

	int		i, j;
	int		aux,aux2,len;
	char	auxstr[MAX_INPUT_LINE];

	auxstr[0]='\0';
	len=0;
	aux2=0;
	for(i=0;i<MAX_GNSS;i++) {
		aux=0;
		for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
			if (options->unselUnavailGNSSFreqFilter[i][j]==1) {
				if (aux==0) {
					len+=sprintf(&auxstr[len]," %s [%d",gnsstype2gnssname(i),j);
				} else {
					len+=sprintf(&auxstr[len],",%d",j);
				}
				aux++;
				aux2++;
			}
		}
		if (aux>0) {
			len+=sprintf(&auxstr[len],"]");
		}
	}
	if (aux2>0) {
		fprintf(options->outFileStream,"INFO%s Excluded unexistent frequenc%s from filter:%s\n",options->workMode<=wmSHOWINPUT?" PREPROCESSING":"",aux2==1?"y":"ies",auxstr);
	}
}

/*****************************************************************************
 * Name        : printFilterMeas
 * Description : Print filter measurements
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              I  N/A  TOptions structure
 * int NavMode                     I  N/A  Navigation mode (SPP/PPP)
 *****************************************************************************/
 void printFilterMeas(TOptions *options, int NavMode) {

	int						i, j, k, l, m, len;	
	int						aux,lenMeas,lenSmooth,lenWeight,lenListGrouped;
	int						AnySatelliteUnselected,AnyFrequencyUnselected;
	int						PositionChecked[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int						SelectedAMeas,MeasEqual;
	int						numOcurrences;
	int						numPrinted,refMeasPos,*strPrinted;
	double					**prevValuesWeight;
	char					auxstr[MAX_INPUT_LINE],auxstr2[MAX_INPUT_LINE];
	char					auxstrWeight[MAX_INPUT_LINE];
	char					**strListGrouped,**strMeas,**strSmooth,**strWeight;
	TRangeList 				List;

	//Ad-hoc loop to detect if any frequency has been manually unselected by the user,
	//so the print can suggest to enable back some frequencies if no measurements are available
	AnyFrequencyUnselected=0;
	for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
		for (i=0;i<MAX_GNSS;i++) {
			if (availGNSSFreq[i][k]==0) continue;
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue;
				if ((i==GLONASS && (k==1 || k==2) && options->usableFreq[i][j][k]==0 && options->GLOsatFDMAdisabled[i][j][k]==0 ) ||
					  (i==GLONASS && k!=1 && k!=2 && options->usableFreq[i][j][k]==0) ||
					  (i!=GLONASS && options->usableFreq[i][j][k]==0)) {
					AnyFrequencyUnselected=1;
				}
				if (AnyFrequencyUnselected==1) break;
			}
			if (AnyFrequencyUnselected==1) break;
		}
		if (AnyFrequencyUnselected==1) {
			break;
		}
	}

	//Ad-hoc loop to detect if any satellite has been manually unselected by the user,
	//so the print can suggest to enable back some satellits if no satellites are available
	AnySatelliteUnselected=0;
	for (i=0;i<MAX_GNSS;i++) {
		for (j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==0) {
				AnySatelliteUnselected=1;
			}
			if (AnySatelliteUnselected==1) break;
		}
		if (AnySatelliteUnselected==1) break;
	}

	//Initialize checked measurements
	for(i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			for (k=0;k<MAX_CS_LIST;k++) {
				PositionChecked[i][j][k]=0;
			}
		}
	}

	//Initialize with first measurement available
	SelectedAMeas=0;
	prevValuesWeight=NULL;		
	for(i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
			for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
				prevValuesWeight=malloc(sizeof(double*));
				prevValuesWeight[0]=NULL;
				prevValuesWeight[0]=malloc(sizeof(double)*7);
				l=0;
				InitRangeList((enum GNSSystem)i,j,&List);
				prevValuesWeight[l][0]=(double)options->weightMode[i][j][k];
				prevValuesWeight[l][1]=options->WeightConstantsValues[i][j][k][0];
				prevValuesWeight[l][2]=options->WeightConstantsValues[i][j][k][1];
				prevValuesWeight[l][3]=options->WeightConstantsValues[i][j][k][2];
				prevValuesWeight[l][4]=(double)i;
				prevValuesWeight[l][5]=(double)j;
				prevValuesWeight[l][6]=(double)k;
				SelectedAMeas=1;
				PositionChecked[i][j][k]=1;
				break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==1) break;
	}

	while(SelectedAMeas==1) {
		numOcurrences=0;
		for(i=(int)prevValuesWeight[l][4];i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) {
					//Satellite unselected. The current range ends
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==(int)prevValuesWeight[l][4]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==(int)prevValuesWeight[l][4] && j<=(int)prevValuesWeight[l][5]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
					continue;
				}
				for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
					MeasEqual=AreFilterMeasurementsEqual(1,ROVERPOS,(enum GNSSystem)i,j,k,ROVERPOS,(enum GNSSystem)prevValuesWeight[l][4],(int)prevValuesWeight[l][5],(int)prevValuesWeight[l][6],options);
					if (MeasEqual==1) {
						//Check if any value is different than the last values read
						if ((double)(options->weightMode[i][j][k])!=prevValuesWeight[l][0] || options->WeightConstantsValues[i][j][k][0]!=prevValuesWeight[l][1] ||
								options->WeightConstantsValues[i][j][k][1]!=prevValuesWeight[l][2] || options->WeightConstantsValues[i][j][k][2]!=prevValuesWeight[l][3]) {
							continue;
						} else {
							//Each satellite will only have once a given measurement
							PositionChecked[i][j][k]=1;//Mark measurement as checked
							break;
						}
						
					}
				} //End for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++)
				if (k==options->numfilterMeasList[ROVERPOS][i][j]||options->numfilterMeasList[ROVERPOS][i][j]==0) {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if (i==(int)prevValuesWeight[l][4] && j<=(int)prevValuesWeight[l][5]) {
							//This is a satellite prior to the first satellite with the current measurement
							//Do nothing
						} else {
							//The current satellite did not have the checked measurement
							if(j==1) {
								//PRN 1 of new constellation
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
				} else {
					numOcurrences++;
					if (i!=(int)(prevValuesWeight[l][4]) || j!=(int)(prevValuesWeight[l][5])) {
						//The current satellite had the checked measurement
						//Check if previous satellite had it. If not, add a new range
						if (j==1) {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						} else {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						}
					}
				}
			} //End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
		} //End for(i=0;i<MAX_GNSS;i++) 
		//Initialize with next measurement
		if (numOcurrences==1) {
			List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
			List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
		}

		SelectedAMeas=0;
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
				for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
					if (PositionChecked[i][j][k]==1) continue;
					AddRangeList((enum GNSSystem)i,j,&List);
					l=List.size-1;
					prevValuesWeight=realloc(prevValuesWeight,sizeof(double*)*List.size);
					prevValuesWeight[l]=NULL;
					prevValuesWeight[l]=malloc(sizeof(double)*7);
					prevValuesWeight[l][0]=(double)options->weightMode[i][j][k];
					prevValuesWeight[l][1]=options->WeightConstantsValues[i][j][k][0];
					prevValuesWeight[l][2]=options->WeightConstantsValues[i][j][k][1];
					prevValuesWeight[l][3]=options->WeightConstantsValues[i][j][k][2];
					prevValuesWeight[l][4]=(double)i;
					prevValuesWeight[l][5]=(double)j;
					prevValuesWeight[l][6]=(double)k;
					SelectedAMeas=1;
					PositionChecked[i][j][k]=1;
					break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==0) break;
	} 

	//Save all the different blocks found
	strListGrouped=NULL;
	strMeas=NULL;
	strSmooth=NULL;
	strWeight=NULL;
	strPrinted=NULL;
	strListGrouped=malloc(sizeof(char*)*List.size);
	strMeas=malloc(sizeof(char*)*List.size);
	strSmooth=malloc(sizeof(char*)*List.size);
	strWeight=malloc(sizeof(char*)*List.size);
	strPrinted=malloc(sizeof(int)*List.size);
	lenMeas=lenSmooth=lenWeight=lenListGrouped=0;	
	for(l=0;l<List.size;l++) {
		//Alloc memory for text saving
		strListGrouped[l]=NULL;
		strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
		strMeas[l]=NULL;
		strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
		strSmooth[l]=NULL;
		strSmooth[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
		strWeight[l]=NULL;
		strWeight[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
		strPrinted[l]=0;
		//Create the list of satellites per block
		SatRangeList2String(l,&List,auxstr);
		//Save data for later grouping by filter measurement
		i=(int)prevValuesWeight[l][4];
		j=(int)prevValuesWeight[l][5];
		k=(int)prevValuesWeight[l][6];
		WeightType2String(i,j,k,auxstrWeight,options);
		len=sprintf(auxstr2,"%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]));
		if (strcmp(auxstr2,"NAN")==0) {
			sprintf(auxstr2,"%s (frequency %d)",options->filterMeasKind[ROVERPOS][i][j][k]==Pseudorange?"Pseudorange  ":"Carrier phase",options->filterMeasfreq[ROVERPOS][i][j][k][0]);
		} else {
			if (options->filterListWithMeas[ROVERPOS][i][j][k]==1) {
				if (options->numCombfilterMeas[ROVERPOS][i][j][k]>1) {
					for(m=1;m<=options->numCombfilterMeas[ROVERPOS][i][j][k];m++) {
						len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][m]));
					}
				}
			} else {
				if (options->filterMeasList[ROVERPOS][i][j][k][0]>=IF12) {
					sprintf(auxstr2,"%s-Auto-%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]),options->filterMeasKind[ROVERPOS][i][j][k]==Pseudorange?"Pseudorange":"Carrier phase");		
				} else {
					sprintf(auxstr2,"%s-Auto",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]));		
				}
			}
		}

		strcpy(strMeas[l],auxstr2);

		if (options->filterMeasSmoothed[ROVERPOS][i][j][k]==1) {
			 len=sprintf(auxstr2,"%s",meastype2measstr(options->filterSmoothMeasList[ROVERPOS][i][j][k][0]));
			 if (strcmp(auxstr2,"NAN")==0) {
				 sprintf(auxstr2,"Carrier phase (frequency %d)",options->filterSmoothMeasfreq[ROVERPOS][i][j][k][0]);
			 } else {
				 if (options->filterSmoothListWithMeas[ROVERPOS][i][j][k]==1) {
					 if (options->numCombfilterSmoothMeas[ROVERPOS][i][j][k]>1) {
						 for(m=1;m<=options->numCombfilterSmoothMeas[ROVERPOS][i][j][k];m++) {
							 len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->filterSmoothMeasList[ROVERPOS][i][j][k][m]));
						 }
					 }
				 } else {
					 sprintf(auxstr2,"%s-Auto",meastype2measstr(options->filterSmoothMeasList[ROVERPOS][i][j][k][0]));
				 }
			 }
			 sprintf(strSmooth[l],"Smooth: %s [n=%d]",auxstr2,options->smoothEpochs);
		} else {
			strSmooth[l][0]='\0';
		}
		strcpy(strWeight[l],auxstrWeight);
		strcpy(strListGrouped[l],auxstr);
		aux=(int)strlen(strMeas[l]);
		if (aux>lenMeas) lenMeas=aux;
		aux=(int)strlen(strSmooth[l]);
		if (aux>lenSmooth) lenSmooth=aux;
		aux=(int)strlen(strWeight[l]);
		if (aux>lenWeight) lenWeight=aux;
		aux=(int)strlen(strListGrouped[l]);
		if (aux>lenListGrouped) lenListGrouped=aux;
	}
	numPrinted=0;
	if (List.size==0) {
		if (options->workMode==wmDOPROCESSING) {
			if (NavMode==1) {
				sprintf(messagestr,"No measurement selected for the filter or cannot auto select any dual frequency combination for PPP. Add more measurements%s%s",AnySatelliteUnselected==0?"":" or unexclude excluded satellites",AnyFrequencyUnselected==0?"":" or unexclude excluded frequencies");
			} else {
				sprintf(messagestr,"No measurement selected for the filter. Add more measurements%s%s",AnySatelliteUnselected==0?"":" or unexclude excluded satellites",AnyFrequencyUnselected==0?"":" or unexclude excluded frequencies");
			}
			printError(messagestr,options);
		}
	} else {
		while(numPrinted<List.size) {
			for(l=0;l<List.size;l++) {
				if (strPrinted[l]==0) {
					refMeasPos=l;
					break;
				}
			}
			for(l=0;l<List.size;l++) {
				if (strPrinted[l]==1) continue;
				if (strcmp(strMeas[l],strMeas[refMeasPos])==0) {
					strPrinted[l]=1;
					numPrinted++;
					if (lenSmooth==0) {
						fprintf(options->outFileStream,"INFO FILTER Meas:%-*s %-*s %s\n",lenListGrouped,strListGrouped[l],lenMeas,strMeas[l],strWeight[l]);
					} else {
						fprintf(options->outFileStream,"INFO FILTER Meas:%-*s %-*s %-*s %s\n",lenListGrouped,strListGrouped[l],lenMeas,strMeas[l],lenSmooth,strSmooth[l],strWeight[l]);
					}
				}
			}
		}
	}
	
	for(l=0;l<List.size;l++) {
		free(strMeas[l]);
		free(strSmooth[l]);
		free(strWeight[l]);
		free(strListGrouped[l]);
		free(prevValuesWeight[l]);
	}
	free(strPrinted);
	free(strMeas);
	free(strSmooth);
	free(strWeight);
	free(strListGrouped);
	free(prevValuesWeight);
	freeRangeList(&List);
}

/*****************************************************************************
 * Name        : printParameters
 * Description : Print Input parameters
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              I  N/A  TOptions structure
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTGDdata  *tgdData              I  N/A  Support products to use for TGD correction, when applicable
 * int NavMode                     I  N/A  Navigation mode (SPP/PPP)
 * char *stdesaFile                I  N/A  Filename for output Stanford-ESA plot
 * char *stdesaFileLOI             I  N/A  Filename for output Stanford-ESA values
 * char *kmlFile                   I  N/A  Filename for output KML file
 * char *kml0File                  I  N/A  Filename for output KML0 file
 * char *sp3File                   I  N/A  Filename for output SP3 file
 * char *RefFile                   I  N/A  Filename for output Reference file
 * int navFilesVersion             I  N/A  List of version of RINEX navigation file used per used type
 * int numNavFilesVersion          I  N/A  Number of RINEX navigation file used per used type
 *****************************************************************************/
void printParameters (TOptions *options, TEpoch *epoch, TGNSSproducts *products, TTGDdata *tgdData, int NavMode, char *stdesaFile, char *stdesaFileLOI, char *kmlFile, char *kml0File, char *sp3File, char *RefFile, int navFilesVersion[MAXNAVSOURCESWITHIONO][MAX_GNSS], int numNavFilesVersion[MAXNAVSOURCESWITHIONO]) {
	int						i, j, k, l, m, n, p, r, s, t, u, staType, type,len;	
	int						aux,aux2,aux3,lenMeas,lenMeasType[MEASTYPELISTS],lenSmooth,lenListGrouped,lenListMeasGrouped;
	int						startPos,EndPos;
	int						measAvail,SNRCombinationsAvail,NoMeasAvail,initGNSS,initPRN,AnySatelliteUnselected,AnyFrequencyUnselected;
	int						numLines,numLinesGrouped,numOcurrences,lenFreq,numAuto,freq,numJoined;
	int						PositionChecked[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int						**LastPositionList,**prevValuesCS,*numFreqJoined,**freqJoined,**prevValuesRefSta,*freqList;
	int						SelectedAMeas,MeasEqual,DiffList,numElements[MAX_FREQUENCIES_PER_GNSS];
	int						numPrinted,refMeasPos,*strPrinted,*strPrintedAuto,numLinesFreq[MAX_FREQUENCIES_PER_GNSS],maxLinesFreq;
	int						numTotCombInterSystemClockBias, numEstimateCombInterSystemClockBias[MAX_GNSS+1],numRINEXCombInterSystemClockBias[MAX_GNSS+1],numUserCombInterSystemClockBias[MAX_GNSS+1];
	int						constellationUsed[MAX_GNSS];
	int						numNavUnique[MAXNAVSOURCES];
	enum MeasurementType	*measList,***MeasOrderList,meas,codeMeas,DopplerMeas,prevMeas;
	enum GNSSystem			GNSS;
	double					**prevValuesSNR,**prevValuesSNRComb,*ThresholdList, *ThresholdListGrouped,**antennaValues;
	double					auxd,auxd2;
	char					auxstr[MAX_INPUT_LINE],auxstr2[MAX_INPUT_LINE],auxstr3[MAX_INPUT_LINE],auxstr4[MAX_INPUT_LINE],auxstr5[MAX_INPUT_LINE];
	char					**strList,**strListGrouped,**strListMeasGrouped,**strMeas,**strSmooth,**strListJoined,**freqJoinedText;
	char					***strMeasType[MAX_FREQUENCIES_PER_GNSS],**strListGroupedType[MAX_FREQUENCIES_PER_GNSS],**FreqTextList;
	TRangeList 				List;
	

	if (!options->printInfo) return;
	
	if (strcmp(epoch->receiver.name,DEFAULTMARKERNAME)==0) {
		strcpy(auxstr,"Unknown");
	} else {
		strcpy(auxstr,epoch->receiver.name);
	}
	#if defined _OPENMP
		fprintf(options->outFileStream,"INFO Number of threads used: %d\n",options->numthreads);
	#endif

	if ( options->SBAScorrections==SBAS1Fused ) {
		fprintf(options->outFileStream,"INFO SBAS single frequency processing mode activated\n");
	} else if ( options->SBAScorrections==SBASDFMCused ) {
		fprintf(options->outFileStream,"INFO SBAS DFMC processing mode activated\n");
	}

	//Get the list of unique RINEX navigation file versions used. To get it, sort the list and extract the unique RINEX versions
	for(i=0;i<MAXNAVSOURCESWITHIONO;i++) {
		if (numNavFilesVersion[i]==0) continue;
		qsort(navFilesVersion[i],numNavFilesVersion[i],sizeof(int),qsort_compare_int);
		numNavUnique[i]=1;
		//Start loop at position 1 as the first item (at position 0) will be always the first unique value
		for(j=1;j<numNavFilesVersion[i];j++) {
			for(k=0;k<numNavUnique[i];k++) {
				if (navFilesVersion[i][k]==navFilesVersion[i][j]) break;
			}
			if(k==numNavUnique[i]) {
				navFilesVersion[i][k]=navFilesVersion[i][j];
				numNavUnique[i]++;
			}
		}
		fprintf(options->outFileStream,"INFO INPUT RINEX navigation file version%s for %s:",numNavUnique[i]==1?"":"s",i==ORBNAVPOS?"orbit and clock data":(i==TGDNAVPOS?"TGD":(i==HEALTHNAVPOS?"health for PPP":"iono parameters")));
		for(j=0;j<numNavUnique[i];j++) {
			fprintf(options->outFileStream," %.2f",(double)(navFilesVersion[i][j])/100.);
		}
		fprintf(options->outFileStream,"\n");
	}

	fprintf(options->outFileStream,"INFO INPUT RINEX observation file version: %.2f\n",epoch->RINEXobsVersion);
	if (epoch->receiver.interval>0.) {
		auxd=epoch->receiver.interval;
	} else {
		auxd=epoch->receiver.intervalEstimate;
	}
	fprintf(options->outFileStream,"INFO INPUT RINEX observation file interval: %.5g (seconds)\n",auxd);
	fprintf(options->outFileStream,"INFO INPUT Station marker: %s\n",auxstr);
	if (epoch->receiver.antenna.type[0] == '\0') {
		strcpy(auxstr,"Unknown");
	} else {
		strcpy(auxstr,epoch->receiver.antenna.type);
	}
	fprintf(options->outFileStream,"INFO INPUT Antenna type:   %s\n",auxstr);
	if (epoch->receiver.type[0] == '\0') {
		fprintf(options->outFileStream,"INFO INPUT GPS Receiver type:  0-Unknown\n");
	} else {
		fprintf(options->outFileStream,"INFO INPUT GPS Receiver type:  %s [%s]\n",epoch->receiver.type,GPSrecType2str(epoch->receiver.recType));
	}
	fprintf(options->outFileStream,"INFO PREPROCESSING Prealign carrier phase measurements: %3s\n",options->prealignCP?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PREPROCESSING Check for uncorrected pseudorange jumps in carrier phase measurements: %3s\n",options->checkPhaseCodeJumps?"ON":"OFF");
	if (options->decimate==0.) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Decimation: disabled\n");
	} else if (options->decimate>=1.) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Decimation: %d (seconds)\n",(int)options->decimate);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Decimation: %.7g (seconds)\n",options->decimate);
	}
	fprintf(options->outFileStream,"INFO PREPROCESSING Automatic smoothing selected: %3s\n",options->smoothAuto?"ON":"OFF");

	//Print excluded satellites
	SelectedAMeas=0;
	AnySatelliteUnselected=0;
	for (i=0;i<MAX_GNSS;i++) {
		for (j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==0) {
				InitRangeList((enum GNSSystem)i,j,&List);
				initGNSS=i;
				l=0;
				SelectedAMeas=1;
				AnySatelliteUnselected=1;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==1) break;
	}
	if (SelectedAMeas==0) {
		//No satellites unselected
		fprintf(options->outFileStream,"INFO PREPROCESSING Excluded satellites: None\n");
	} else {
		for (i=initGNSS;i<MAX_GNSS;i++) {
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==1) {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==List.listSatGNSS[l][List.numJumpslist[l]-1][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==List.listSatGNSS[l][List.numJumpslist[l]-1][0] && j<=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
				} else {
					if (i!=List.listSatGNSS[l][List.numJumpslist[l]-1][0] || j!=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
						//The current satellite was unselected
						//Check if previous satellite was selected. If not, add a new range
						if (j==1) {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						} else {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						}
					}
				}
			}
		}
		//Create the list of satellites per block
		SatRangeList2String(l,&List,auxstr);
		fprintf(options->outFileStream,"INFO PREPROCESSING Excluded satellites: %s\n",auxstr);
		freeRangeList(&List);
	}
	

	//Print Excluded GEO PRN
	if (options->SBAScorrections>NoSBASdata) {
		aux=1;
		for(i=MINGEOPRN;i<=MAXGEOPRN;i++) {
			if (options->GEOPRNunsel[i]==1) {
				if(aux==1) {
					fprintf(options->outFileStream,"INFO PREPROCESSING GEO-PRN excluded:");
					aux=0;
				}
				fprintf(options->outFileStream," %3d",i);
			}
		}
		if(aux==0) {
			fprintf(options->outFileStream,"\n");
		}
	}

	//Print Usable frequencies (not unselected by user and available in file)
	for(i=0;i<MAX_GNSS;i++) {
		aux=0;
		aux2=0;
		sprintf(auxstr,"[%s]:",gnsstype2gnssname(i));
		fprintf(options->outFileStream,"INFO PREPROCESSING Usable frequencies %-*s",maxLenghtConstName+3,auxstr);
		for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
			if (availGNSSFreq[i][j]==1) {
				for(k=1;k<=listMaxSatGNSS[i];k++) {
					if (options->usableFreq[i][k][j]==1) {
						break;
					}
				}
				if (k<=listMaxSatGNSS[i] && epoch->measOrder[i].availFreq[j]==1) {
					sprintf(auxstr,"(%s)",Freqname[i][j]);
					fprintf(options->outFileStream," F%1d %-*s",j,maxLengthFreqName+2,auxstr);
					aux++;
				} else if (epoch->measOrder[i].availFreq[j]==1) {
					aux2++;
				}
			}
		}
		
		if (aux==0) {
			fprintf(options->outFileStream," No frequencies available in RINEX observation file%s\n",aux2==0?"":" and not unselected");
		} else {
			fprintf(options->outFileStream,"\n");
		}
	}

	//Print order of preference for filling frequencies
	freqList=NULL;
	freqJoinedText=NULL;
	strListGrouped=NULL;
	numLines=lenListGrouped=lenFreq=0;
	SelectedAMeas=0;
	for(i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==0) continue;
			auxstr[0]='\0';
			len=0;
			for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
				freq=options->defaultFreq[i][j][k];
				if (freq==-1) break;
				if (options->usableFreq[i][j][freq]==0) continue;
				if (epoch->measOrder[i].availFreq[freq]==0) continue;
				if (options->availFreq[i][j][freq]==0) continue;
				len+=sprintf(&auxstr[len],"%01d",freq);
			}
			if (auxstr[0]=='\0') continue;
			l=0;
			InitRangeList((enum GNSSystem)i,j,&List);
			LastPositionList=NULL;
			LastPositionList=malloc(sizeof(int*));
			LastPositionList[l]=NULL;
			LastPositionList[l]=malloc(sizeof(int)*3);
			LastPositionList[l][0]=i;
			LastPositionList[l][1]=j;
			LastPositionList[l][2]=atoi(auxstr);
			FreqTextList=NULL;
			FreqTextList=malloc(sizeof(char*));
			FreqTextList[l]=NULL;
			FreqTextList[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strcpy(FreqTextList[l],auxstr);
			SelectedAMeas=1;
			break;
		}
		if (SelectedAMeas==1) break;
	}
	if (SelectedAMeas==1) {
		//Look for different measurement orders
		for(i=LastPositionList[0][0];i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				auxstr[0]='\0';
				len=0;
				for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
					freq=options->defaultFreq[i][j][k];
					if (freq==-1) break;
					if (options->usableFreq[i][j][freq]==0) continue;
					if (epoch->measOrder[i].availFreq[freq]==0) continue;
					if (options->availFreq[i][j][freq]==0) continue;
					len+=sprintf(&auxstr[len],"%01d",freq);
				}
				if (options->includeSatellite[i][j]==0||auxstr[0]=='\0') {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999 && ((i>LastPositionList[0][0]) || (i==LastPositionList[0][0] && j>LastPositionList[0][1]))) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==LastPositionList[l][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==LastPositionList[l][0] && j<=LastPositionList[l][1]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
					continue;
				}
				freq=atoi(auxstr);
				if (freq!=LastPositionList[l][2]) {
					//Frequency order is different. Look if this order was already saved before
					for(m=0;m<List.size;m++) {
						if(freq==LastPositionList[m][2]) {
							break;
						}
					}
					if (m==List.size) {
						//Block not found. New measurement 
						AddRangeList((enum GNSSystem)i,j,&List);
						LastPositionList=realloc(LastPositionList,sizeof(int*)*List.size);
						LastPositionList[m]=NULL;
						LastPositionList[m]=malloc(sizeof(int)*3);
						LastPositionList[m][0]=i;
						LastPositionList[m][1]=j;
						LastPositionList[m][2]=freq;
						FreqTextList=realloc(FreqTextList,sizeof(char*)*List.size);
						FreqTextList[m]=NULL;
						FreqTextList[m]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strcpy(FreqTextList[m],auxstr);
					} else {
						//Block found (measurement was already read before). Extend the list with the new start of range
						ExtendRangeList((enum GNSSystem)i,j,m,&List);
					}
					//Save the end of the range
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==LastPositionList[l][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==LastPositionList[l][0] && j<=LastPositionList[l][1]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
					//Save the index of the last type of block we are using to compare
					l=m;
				} else {
					if (i!=LastPositionList[l][0] || j!=LastPositionList[l][1]) {
						//The current satellite had the checked measurement
						//Check if previous satellite had it. If not, add a new range
						if (j==1) {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						} else {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						}
					}
				}
			}
		} //End for(i=LastPositionList[0][0];i<MAX_GNSS;i++)

		for(l=0;l<List.size;l++) {
			//Create the list of satellites per block
			freqList=realloc(freqList,sizeof(int)*(l+1));
			freqList[l]=LastPositionList[l][2];
			freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(l+1));
			freqJoinedText[l]=NULL;
			freqJoinedText[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			freqJoinedText[l][0]='\0';
			strListGrouped=realloc(strListGrouped,sizeof(char*)*(l+1));
			strListGrouped[l]=NULL;
			strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			SatRangeList2String(l,&List,auxstr);
			strcpy(strListGrouped[l],auxstr);
			aux=(int)strlen(strListGrouped[l]);
			if (aux>lenListGrouped) {
				lenListGrouped=aux;
			}
			aux=(int)strlen(FreqTextList[l]);
			for(k=0;k<aux;k++) {
				sprintf(auxstr,"%s%s%c",freqJoinedText[l],k==0?"":"|",FreqTextList[l][k]);
				sprintf(freqJoinedText[l],"%s",auxstr);
			}
			aux=(int)strlen(freqJoinedText[l]);
			if (aux>lenFreq) {
				lenFreq=aux;
			}
		}

		for(l=0;l<List.size;l++) {
			fprintf(options->outFileStream,"INFO PREPROCESSING Measurement frequency filling order %-*s%s\n",lenFreq,freqJoinedText[l],strListGrouped[l]);
		}
		for(l=0;l<List.size;l++) {
			free(FreqTextList[l]);
			free(freqJoinedText[l]);
			free(strListGrouped[l]);
			free(LastPositionList[l]);
		}
		free(LastPositionList);
		free(freqJoinedText);
		free(FreqTextList);
		free(strListGrouped);
		free(freqList);
		freeRangeList(&List);
	}

	//Print disbled GLONASS satellites due to missing k's
	printDisabledGLONASS(options);

	//Print excluded frequencies by user
	AnyFrequencyUnselected=0;
	freqList=NULL;
	strListGrouped=NULL;
	strPrinted=NULL;
	numLines=lenListGrouped=0;
	for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
		SelectedAMeas=0;
		numOcurrences=0;
		for (i=0;i<MAX_GNSS;i++) {
			if (availGNSSFreq[i][k]==0) continue;
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue;
				if ((i==GLONASS && (k==1 || k==2) && options->usableFreq[i][j][k]==0 && options->GLOsatFDMAdisabled[i][j][k]==0 ) ||
					  (i==GLONASS && k!=1 && k!=2 && options->usableFreq[i][j][k]==0) ||
					  (i!=GLONASS && options->usableFreq[i][j][k]==0)) {
					InitRangeList((enum GNSSystem)i,j,&List);
					initGNSS=i;
					l=0;
					SelectedAMeas=1;
					AnyFrequencyUnselected=1;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==0) {
			continue;
		}
		for (i=initGNSS;i<MAX_GNSS;i++) {
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0|| options->usableFreq[i][j][k]==1||availGNSSFreq[i][k]==0
						|| (i==GLONASS && (k==1 || k==2) && options->usableFreq[i][j][k]==0 && options->GLOsatFDMAdisabled[i][j][k]==1)) {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==List.listSatGNSS[l][List.numJumpslist[l]-1][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==List.listSatGNSS[l][List.numJumpslist[l]-1][0] && j<=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
					continue;
				} else {
					numOcurrences++;
					//The current satellite does not have the frequency
					if (i!=List.listSatGNSS[l][List.numJumpslist[l]-1][0] || j!=List.listSatPRN[l][List.numJumpslist[l]-1][0]) {
						//Check if previous satellite was selected. If not, add a new range
						if (j==1) {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						} else {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						}
					}
				}
			}
		}
		if (numOcurrences==1) {
			List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
			List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
		}
		//Create the list of satellites per block
		freqList=realloc(freqList,sizeof(int)*(numLines+1));
		freqList[numLines]=k;
		strPrinted=realloc(strPrinted,sizeof(int)*(numLines+1));
		strPrinted[numLines]=0;
		strListGrouped=realloc(strListGrouped,sizeof(char*)*(numLines+1));
		strListGrouped[numLines]=NULL;
		strListGrouped[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
		SatRangeList2String(l,&List,auxstr);
		strcpy(strListGrouped[numLines],auxstr);
		aux=(int)strlen(strListGrouped[numLines]);
		if (aux>lenListGrouped) {
			lenListGrouped=aux;
		}
		numLines++;
		freeRangeList(&List);
	}
	if (AnyFrequencyUnselected==0) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Excluded frequencies by user: None\n");
	} else {
		numPrinted=0;
		numLinesGrouped=0;
		lenFreq=0;
		lenMeas=1;
		strListJoined=NULL;
		freqJoinedText=NULL;
		while(numPrinted<numLines) {
			auxstr[0]='\0';
			len=0;
			aux2=0;
			for(l=0;l<numLines;l++) {
				if (strPrinted[l]==1) continue;
				if (auxstr[0]=='\0') {
					//Start of group
					m=l;
					len=sprintf(auxstr,"%d",freqList[l]);
					strPrinted[l]=1;
					numPrinted++;
					numLinesGrouped++;
					aux2++;
				} else if (strcmp(strListGrouped[m],strListGrouped[l])==0) {
					len+=sprintf(&auxstr[len],"|%d",freqList[l]);
					strPrinted[l]=1;
					numPrinted++;
					aux2++;
				}
			}
			aux=(int)strlen(auxstr);
			if(aux>lenFreq) {
				lenFreq=aux;
			}
			if (aux2>1) {
				lenMeas=3;
			}

			strListJoined=realloc(strListJoined,sizeof(char*)*numLinesGrouped);
			strListJoined[numLinesGrouped-1]=NULL;
			strListJoined[numLinesGrouped-1]=malloc(sizeof(char)*MAX_INPUT_LINE);
			freqJoinedText=realloc(freqJoinedText,sizeof(char*)*numLinesGrouped);
			freqJoinedText[numLinesGrouped-1]=NULL;
			freqJoinedText[numLinesGrouped-1]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strcpy(freqJoinedText[numLinesGrouped-1],auxstr);
			strcpy(strListJoined[numLinesGrouped-1],strListGrouped[m]);
		}
		for(l=0;l<numLinesGrouped;l++) {
			aux=(int)strlen(freqJoinedText[l]);
			fprintf(options->outFileStream,"INFO PREPROCESSING Excluded frequenc%-*s by user: %-*s %s\n",lenMeas,aux==1?"y":"ies",lenFreq,freqJoinedText[l],strListJoined[l]);
		}
		for(l=0;l<numLinesGrouped;l++) {
			free(freqJoinedText[l]);
			free(strListJoined[l]);
		}
		for(l=0;l<numLines;l++) {
			free(strListGrouped[l]);
		}
		free(freqJoinedText);
		free(strListJoined);
		free(strListGrouped);
		free(freqList);
		free(strPrinted);
	}

	//Print excluded frequencies in CS due to they do not exist
	auxstr[0]='\0';
	len=0;
	aux2=0;
	for(i=0;i<MAX_GNSS;i++) {
		aux=0;
		for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
			if (options->unselUnavailGNSSFreqCS[i][j]==1) {
				if (aux==0) {
					len+=sprintf(&auxstr[len]," %s [%d",gnsstype2gnssname(i),j);
				} else {
					len+=sprintf(&auxstr[len],",%d",j);
				}
				aux++;
				aux2++;
			}
		}
		if (aux>0) {
			len+=sprintf(&auxstr[len],"]");
		}
	}
	if (aux2>0) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Excluded unexistent frequenc%s from cycle-slip detectors:%s\n",aux2==1?"y":"ies",auxstr);
	}
	
	//Print excluded constellations in filter due to frequencies that do not exist
	printConstFreqDisabled(options);
	
	fprintf(options->outFileStream,"INFO PREPROCESSING Elevation mask: %.2f (degrees)\n",options->elevationMask/d2r);
	fprintf(options->outFileStream,"INFO PREPROCESSING Discard satellites under eclipse conditions: %3s\n",options->discardEclipsedSatellites?"ON":"OFF");
	if ( options->receiverPositionSource == rpSETREF) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position: [Position from reference file, used for modelling and for dXYZ and dNEU");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position (metres): %14.4f %14.4f %14.4f  [",epoch->receiver.aproxPosition[0],epoch->receiver.aproxPosition[1],epoch->receiver.aproxPosition[2]);
	}
	if (options->receiverPositionSource == rpRINEX) fprintf(options->outFileStream,"RINEX");
	else if (options->receiverPositionSource == rpSINEX) fprintf(options->outFileStream,"SINEX");
	else if (options->receiverPositionSource == rpCALCULATE || options->receiverPositionSource == rpCALCULATEREF) {
		fprintf(options->outFileStream,"TO_BE_CALCULATED");
	}
	else if (options->receiverPositionSource == rpCALCULATERINEX || options->receiverPositionSource == rpCALCULATERINEXREF) {
		fprintf(options->outFileStream,"TO_BE_CALCULATED, RINEX as initial position");
	}
	else if (options->receiverPositionSource == rpCALCULATEUSER || options->receiverPositionSource == rpCALCULATEUSERREF) {
		fprintf(options->outFileStream,"TO_BE_CALCULATED, User input as initial position");
	}
	else if (options->receiverPositionSource == rpSET) fprintf(options->outFileStream,"SET");
	else if (options->receiverPositionSource == rpRTCMbaseline || options->receiverPositionSource == rpRTCMUserbaseline) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ and dNEU compared with reference station");
	else if (options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ and dNEU compared with RINEX Rover position");
	else if (options->receiverPositionSource == rpRTCMRoverUSER || options->receiverPositionSource == rpRTCMRefRoverUSER ) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ and dNEU compared with user defined position");
	else if (options->receiverPositionSource == rpRTCMRoverUSERREF || options->receiverPositionSource == rpRTCMRefUSERRoverREF ) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ and dNEU compared with position from reference file");
	fprintf(options->outFileStream,"]\n");
	if ( options->receiverPositionSource == rpRTCMRoverUSER || options->receiverPositionSource == rpRTCMRefRoverUSER ) {
		if (options->aprioriReceiverPositionGeod[2]!=-999999) {
			//User has given geodetic coordinates
			fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position (Geodetic Lon[º],Lat[º],Height[m]): %14.10f %15.10f %14.4f\n",options->aprioriReceiverPositionGeod[1]*r2d,options->aprioriReceiverPositionGeod[0]*r2d,options->aprioriReceiverPositionGeod[2]);
		}
		fprintf(options->outFileStream,"INFO PREPROCESSING User defined position for computing dXYZ and dNEU (metres): %14.4f %14.4f %14.4f\n",options->aprioriReceiverPosition[0],options->aprioriReceiverPosition[1],options->aprioriReceiverPosition[2]);
	} else if ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) {
		fprintf(options->outFileStream,"INFO PREPROCESSING RINEX position for computing dXYZ and dNEU (metres): %14.4f %14.4f %14.4f\n",epoch->receiver.aproxPositionRover[0],epoch->receiver.aproxPositionRover[1],epoch->receiver.aproxPositionRover[2]);
	}
	if ( options->receiverPositionSource >= rpRTCMUserbaseline) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Reference station user defined position (metres): %14.4f %14.4f %14.4f\n",options->ReferenceStationPosition[0],options->ReferenceStationPosition[1],options->ReferenceStationPosition[2]);
		if (options->ReferenceStationPositionGeod[2]!=-999999) {
			//User has given geodetic coordinates
			fprintf(options->outFileStream,"INFO PREPROCESSING Reference station user defined position (Geodetic Lon[º],Lat[º],Height[m]): %14.10f %15.10f %14.4f\n",options->ReferenceStationPositionGeod[1]*r2d,options->ReferenceStationPositionGeod[0]*r2d,options->ReferenceStationPositionGeod[2]);
		}
	}
	fprintf(options->outFileStream,"INFO PREPROCESSING Discard measurements not available in satellite blocks: %3s\n",options->SatBlockMeasDiscard==1?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PREPROCESSING Discard unpaired measurements in rover RINEX observation file: %3s%s\n",options->DiscardUnpairedMeas[ROVERPOS]==1?"ON":"OFF",options->ForcedDiscardUnpairedMeas[ROVERPOS]==0?"":" (forced disconnection due to observation RINEX is version 2)");
	if (options->DGNSS==1) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Discard unpaired measurements in reference station RINEX observation file: %3s%s\n",options->DiscardUnpairedMeas[REFSTAPOS]==1?"ON":"OFF",options->ForcedDiscardUnpairedMeas[REFSTAPOS]==0?"":" (forced disconnection due to observation RINEX is version 2)");
	}

	//Print measurement priority list
	for (staType=0;staType<NUM_OBSRINEX;staType++) {
		if (staType==REFSTAPOS && options->DGNSS==0) continue;
		//Initialize number of elements
		for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
			numElements[k]=-1;
			numLinesFreq[k]=0;
		}

		for(n=0;n<MEASTYPELISTS;n++) {
			lenMeasType[n]=0;
		}
		lenListGrouped=0;
		maxLinesFreq=0;
		for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
			numElements[k]=0;
			strMeasType[k]=NULL;
			strListGroupedType[k]=NULL;
			for(n=0;n<MEASTYPELISTS;n++) {
				SelectedAMeas=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (availGNSSFreq[i][k]==0) continue;
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						if (options->usableFreq[i][j][k]==0) continue;
						l=0;
						InitRangeList((enum GNSSystem)i,j,&List);
						LastPositionList=NULL;
						LastPositionList=malloc(sizeof(int*));
						LastPositionList[l]=NULL;
						LastPositionList[l]=malloc(sizeof(int)*5);
						MeasOrderList=NULL;
						MeasOrderList=malloc(sizeof(enum MeasurementType*));
						MeasOrderList[l]=NULL;
						MeasOrderList[l]=malloc(sizeof(enum MeasurementType*)*3);
						LastPositionList[l][0]=i;
						LastPositionList[l][1]=j;
						for(p=0;p<MEASTYPELISTS;p++) {
							LastPositionList[l][p+2]=options->numMeasAvailOrder[staType][i][j][k][p];
							MeasOrderList[l][p]=&options->MeasAvailOrder[staType][i][j][k][p][0];
						}
						SelectedAMeas=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==0) continue;
			//Look for different measurement orders
			for(i=LastPositionList[l][0];i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0||options->usableFreq[i][j][k]==0) {
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if(j==1) {
								//PRN 1 of new constellation
								if (i==LastPositionList[l][0]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								}
							} else {
								if (i==LastPositionList[l][0] && j<=LastPositionList[l][1]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
						continue;
					}
					DiffList=0;
					for(n=0;n<MEASTYPELISTS;n++) {
						if (options->numMeasAvailOrder[staType][LastPositionList[l][0]][LastPositionList[l][1]][k][n]!=options->numMeasAvailOrder[staType][i][j][k][n]) {
							DiffList=1;
							break;
						}
					}
					if (DiffList==0) {
						for(n=0;n<MEASTYPELISTS;n++) {
							for(m=0;m<options->numMeasAvailOrder[staType][i][j][k][n];m++) {
								if (options->MeasAvailOrder[staType][LastPositionList[l][0]][LastPositionList[l][1]][k][n][m]!=options->MeasAvailOrder[staType][i][j][k][n][m]) {
									DiffList=1;
									break;
								}
							}
							if (DiffList==1) break;
						}
					}
					if (DiffList==1) {
						//Values are different. Look if these values were already saved before
						for(m=0;m<List.size;m++) {
							DiffList=0;
							for(n=0;n<MEASTYPELISTS;n++) {
								if (LastPositionList[m][n+2]!=options->numMeasAvailOrder[staType][i][j][k][n]) {
									DiffList=1;
									break;
								}
							}
							if (DiffList==0) {
								for(n=0;n<MEASTYPELISTS;n++) {
									for(p=0;p<LastPositionList[m][n+2];p++) {
										if (MeasOrderList[m][n][p]!=options->MeasAvailOrder[staType][i][j][k][n][p]) {
											DiffList=1;
											break;
										}
									}
									if (DiffList==1) break;
								}
							}
							if (DiffList==0) break;
						}
						if (m==List.size) {
							//Block not found. New measurement 
							AddRangeList((enum GNSSystem)i,j,&List);
							LastPositionList=realloc(LastPositionList,sizeof(int*)*List.size);
							LastPositionList[m]=NULL;
							LastPositionList[m]=malloc(sizeof(int)*5);
							LastPositionList[m][0]=i;
							LastPositionList[m][1]=j;
							MeasOrderList=realloc(MeasOrderList,sizeof(enum MeasurementType*)*List.size);
							MeasOrderList[m]=NULL;
							MeasOrderList[m]=malloc(sizeof(enum MeasurementType*)*3);
							for(n=0;n<MEASTYPELISTS;n++) {
								LastPositionList[m][n+2]=options->numMeasAvailOrder[staType][i][j][k][n];
								MeasOrderList[m][n]=&options->MeasAvailOrder[staType][i][j][k][n][0];
							}
						} else {
							//Block found (measurement was already read before). Extend the list with the new start of range
							ExtendRangeList((enum GNSSystem)i,j,m,&List);
						}
						//Save the end of the range
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if(j==1) {
								//PRN 1 of new constellation
								if (i==LastPositionList[l][0]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								}
							} else {
								if (i==LastPositionList[l][0] && j<=LastPositionList[l][1]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
						//Save the index of the last type of block we are using to compare
						l=m;
					} else {
						if (i!=LastPositionList[l][0] || j!=LastPositionList[l][1]) {
							//The current satellite had the checked measurement
							//Check if previous satellite had it. If not, add a new range
							if (j==1) {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							} else {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							}
						}
					}
				}
			} //End for(i=LastPositionList[l][0];i<MAX_GNSS;i++)
			for(l=0;l<List.size;l++) {
				if (LastPositionList[l][2]==0 && LastPositionList[l][3]==0 && LastPositionList[l][4]==0) {
					//Empty table. Skip it
					continue;
				}
				strMeasType[k]=realloc(strMeasType[k],sizeof(char*)*(numElements[k]+1));
				strMeasType[k][numElements[k]]=NULL;
				strMeasType[k][numElements[k]]=malloc(sizeof(char*)*MEASTYPELISTS);
				for(n=0;n<MEASTYPELISTS;n++) {
					strMeasType[k][numElements[k]][n]=NULL;
					strMeasType[k][numElements[k]][n]=malloc(sizeof(char)*(MAX_INPUT_LINE));
					strMeasType[k][numElements[k]][n][0]='\0';
				}
				strListGroupedType[k]=realloc(strListGroupedType[k],sizeof(char*)*(numElements[k]+1));
				strListGroupedType[k][numElements[k]]=NULL;
				strListGroupedType[k][numElements[k]]=malloc(sizeof(char)*(MAX_INPUT_LINE));
				//Create the list of satellites per block
				SatRangeList2String(l,&List,auxstr);
				strcpy(strListGroupedType[k][numElements[k]],auxstr);
				//Save list of measurements
				for(n=0;n<MEASTYPELISTS;n++) {
					for(m=0;m<LastPositionList[l][n+2];m++) {
						sprintf(auxstr2,"%s %s",strMeasType[k][numElements[k]][n],meastype2measstr(MeasOrderList[l][n][m]));
						sprintf(strMeasType[k][numElements[k]][n],"%s",auxstr2);
					}
					aux=(int)strlen(strMeasType[k][numElements[k]][n]);
					if (aux>lenMeasType[n]) lenMeasType[n]=aux;
				}
				aux=(int)strlen(strListGroupedType[k][numElements[k]]);
				if (aux>lenListGrouped) lenListGrouped=aux;
				numElements[k]++;
			}
			numLinesFreq[k]+=numElements[k];
			for(l=0;l<List.size;l++) {
				free(LastPositionList[l]);
				free(MeasOrderList[l]);
			}
			free(MeasOrderList);
			free(LastPositionList);
			freeRangeList(&List);	
			if (numLinesFreq[k]>maxLinesFreq) {
				maxLinesFreq=numLinesFreq[k];
			}
		} //End for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++)

		for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
			for(l=0;l<numElements[k];l++) {
				fprintf(options->outFileStream,"INFO PREPROCESSING %s priority list for frequency %d: %-*s %-*s |%-*s %s%s\n",staType==ROVERPOS?"Rover":"Reference Station",k,lenListGrouped,strListGroupedType[k][l],lenMeasType[CODEMEAS],strMeasType[k][l][CODEMEAS],lenMeasType[PHASEMEAS],strMeasType[k][l][PHASEMEAS],strlen(strMeasType[k][l][DOPPLERMEAS])>0?"|":"",strMeasType[k][l][DOPPLERMEAS]);
			}
		}
		for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
			if (strMeasType[k]==NULL) continue;
			for(l=0;l<numElements[k];l++) {
				for(n=0;n<MEASTYPELISTS;n++) {
					free(strMeasType[k][l][n]);
				}
				free(strMeasType[k][l]);
				free(strListGroupedType[k][l]);
			}
			free(strMeasType[k]);
			free(strListGroupedType[k]);
		}
	}

	if (options->csNcon ) {
		fprintf(options->outFileStream,"INFO PREPROCESSING N-consecutive: ON  [Min: %d sample%s]\n",-1*options->csNconMin+1,(-1*options->csNconMin+1)==1?"":"s");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING N-consecutive: OFF\n");
	}
	if (options->csLLI==0 && options->csSF==0 && options->csMW==0 && options->csLI==0 && options->csIGF==0) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip Data Gap: OFF (all cycle-slip detectors disabled)\n");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip Data Gap: %.7g (seconds)%s\n",options->csDataGap,options->csDataGapSizeMode==csDataGapSizeAuto?" [Automatically adjusted to RINEX observation file data rate]":"");
	}	
	if (options->csLLI) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LLI:      ON\n");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LLI:      OFF\n");
	}
	if (options->csSF) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip SF:       ON  [Init:%.3lf  Window:%d  K-factor:%.3lf  Samples:%d]\n",options->csSFinit,options->csSFwindow,options->csSFkfactor,options->csSFsamples);
		if (options->csUnconsistencyCheck) {
			fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip SF Unconsistency check threshold: %.2f\n",options->csUnconsistencyCheckThreshold);
		} else {
			fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip SF Unconsistency check: OFF\n");
		}
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip SF:       OFF\n");
	}
	if (options->csMW) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip %s:       ON  [SigMin:%.3lf  Window:%.d  K-factor:%.3lf  Samples:%d]\n",options->printV5format==0?"MW":"BW",options->csMWmin,options->csMWwindow,options->csMWkfactor,options->csMWsamples);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip %s:       OFF\n",options->printV5format==0?"MW":"BW");
	}
	if (options->csLI) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LI:       ON  [MaxJump:%.3lf  Max:%.3lf  To:%.3lf  Samples:%d]\n",options->csLImaxjump,options->csLImax,options->csLIt,options->csLIsamples);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LI:       OFF\n");
	}
	if (options->csIGF) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip IGF:      ON  [MaxJump:%.3lf  Max:%.3lf  To:%.3lf  Samples:%d]\n",options->csIGFmaxjump,options->csIGFmax,options->csIGFt,options->csIGFsamples);
		fprintf(options->outFileStream,"INFO PREPROCESSING Method for computing IGF combination: %s\n",options->csIGFminNoise==1?"Minimum noise combination":"Substracting two iono-free combinations");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip IGF:      OFF\n");
	}
	if (epoch->receiver.recType == rtNOP1) {
		fprintf(options->outFileStream,"INFO PREPROCESSING GPS Receiver type does not provide P1. Using C1 as P1 measurement\n"); 
	}

	//Print measurements for SF cycle-slip detector for Rover
	for (staType=0;staType<NUM_OBSRINEX;staType++) {
		if (staType==REFSTAPOS && options->DGNSS==0) continue;
		//SF cycle slip print
		if (options->csSF) {
			//Initialize checked measurements
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					for (k=0;k<options->numcsSFMeasList[staType][i][j];k++) {
						PositionChecked[i][j][k]=0;
					}
				}
			}
			l=0;
			prevValuesCS=NULL;
			prevValuesCS=malloc(sizeof(int*));
			SelectedAMeas=0;
			NoMeasAvail=1;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue;
					for (k=0;k<options->numcsSFMeasList[staType][i][j];k++) {
						InitRangeList((enum GNSSystem)i,j,&List);
						prevValuesCS[l]=NULL;
						prevValuesCS[l]=malloc(sizeof(int)*5);
						prevValuesCS[l][0]=i;
						prevValuesCS[l][1]=j;
						prevValuesCS[l][2]=options->csSFMeasFreq[staType][i][j][k][0];
						prevValuesCS[l][3]=(int)options->csSFMeasList[staType][i][j][k][0];
						prevValuesCS[l][4]=(int)options->csSFMeasList[staType][i][j][k][1];
						SelectedAMeas=1;
						NoMeasAvail=0;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			while(SelectedAMeas==1) {
				numOcurrences=0;
				for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==prevValuesCS[l][0]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						for(k=0;k<options->numcsSFMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							DiffList=0;
							//Check if any value is different than the last values read
							for(m=0;m<1;m++) {
								if (options->csSFMeasFreq[staType][i][j][k][m]!=prevValuesCS[l][2+m]) {
									DiffList=1;
								}
							}
							if (DiffList==0) {
								for(m=0;m<2;m++) {
									if (options->csSFMeasList[staType][i][j][k][m]!=(enum MeasurementType)prevValuesCS[l][3+m]) {
										DiffList=1;
									}
								}
							}
							if (DiffList==0) {
								PositionChecked[i][j][k]=1;
								break;
							} else {
								continue;
							}
						}
						if (k==options->numcsSFMeasList[staType][i][j]||options->numcsSFMeasList[staType][i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
									//This is a satellite prior to the first satellite with the current measurement
									//Do nothing
								} else {
									//The current satellite did not have the checked measurement
									if(j==1) {
										//PRN 1 of new constellation
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
						} else {
							numOcurrences++;
							if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}//End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
				}//End for(i=0;i<MAX_GNSS;i++)			
				//Initialize with next measurement
				if (numOcurrences==1) {
					List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
					List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
				}
				SelectedAMeas=0;
				for(i=0;i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						for (k=0;k<options->numcsSFMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							AddRangeList((enum GNSSystem)i,j,&List);
							l=List.size-1;
							prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
							prevValuesCS[l]=NULL;
							prevValuesCS[l]=malloc(sizeof(int)*5);
							prevValuesCS[l][0]=i;
							prevValuesCS[l][1]=j;
							prevValuesCS[l][2]=options->csSFMeasFreq[staType][i][j][k][0];
							prevValuesCS[l][3]=options->csSFMeasList[staType][i][j][k][0];
							prevValuesCS[l][4]=options->csSFMeasList[staType][i][j][k][1];
							SelectedAMeas=1;
							PositionChecked[i][j][k]=1;
							break;
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==0) break;
			}
			if (NoMeasAvail==0) {
				//Save all the different blocks found
				strListGrouped=NULL;
				strMeas=NULL;
				strPrinted=NULL;
				strListGrouped=malloc(sizeof(char*)*List.size);
				strMeas=malloc(sizeof(char*)*List.size);
				strPrinted=malloc(sizeof(int)*List.size);
				lenMeas=lenListGrouped=0;
				for(l=0;l<List.size;l++) {
					//Alloc memory for text saving
					strListGrouped[l]=NULL;
					strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					strMeas[l]=NULL;
					strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					//Create the list of satellites per block
					SatRangeList2String(l,&List,auxstr);
					//Save data for later grouping by measurements
					i=prevValuesCS[l][0];
					j=prevValuesCS[l][1];
					if (prevValuesCS[l][3]==NA) {
						sprintf(strMeas[l],"Auto");
					} else {
						sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][3]));
						sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][4]));
					}
					strcpy(strListGrouped[l],auxstr);
					aux=(int)strlen(strMeas[l]);
					if (aux>lenMeas) lenMeas=aux;
					aux=(int)strlen(strListGrouped[l]);
					if (aux>lenListGrouped) lenListGrouped=aux;
				}
				//Join all lines with "Auto"
				auxstr[0]='\0';
				strListJoined=NULL;
				freqJoined=NULL;
				freqJoinedText=NULL;
				numFreqJoined=NULL;
				numAuto=0;
				lenFreq=0;
				for(l=0;l<List.size;l++) {
					if (strcmp(strMeas[l],"Auto")==0) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
							freqJoinedText[numAuto]=NULL;
							freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText[numAuto][0]='\0';
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
								freqJoinedText[numAuto]=NULL;
								freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText[numAuto][0]='\0';
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
						strPrinted[l]=1;
					} else {
						strPrinted[l]=0;
					}
				}
				strPrintedAuto=NULL;
				strPrintedAuto=malloc(sizeof(int)*numAuto);
				for(l=0;l<numAuto;l++) {
					if (numFreqJoined[l]>lenFreq) {
						lenFreq=numFreqJoined[l];
					}
				}
				lenFreq=2*lenFreq-1; //To account for the "|" separator
				for(l=0;l<numAuto;l++) {
					auxstr[0]='\0';
					qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
					for(m=0;m<numFreqJoined[l];m++) {
						sprintf(auxstr,"%s%s%d",freqJoinedText[l],m==0?"":"|",freqJoined[l][m]);
						sprintf(freqJoinedText[l],"%s",auxstr);
					}
					strPrintedAuto[l]=0;
				}
				if (List.size>numAuto) aux=List.size;
				else aux=numAuto;
				for(k=1;k<=MAX_FREQUENCIES_PER_GNSS;k++) {
					if (k==MAX_FREQUENCIES_PER_GNSS) m=0;
					else m=k;
					for(l=0;l<aux;l++) {
						if (l<numAuto) {
							if (strPrintedAuto[l]==0 && freqJoinedText[l][0]==('0'+ m)) {
								fprintf(options->outFileStream,"INFO PREPROCESSING %s SF Detector Frequenc%s %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",numFreqJoined[l]==1?"y  ":"ies",lenFreq,freqJoinedText[l],lenListGrouped,strListJoined[l],"Auto");
								strPrintedAuto[l]=1;
							}
						}
						if (l<List.size) {
							if (strPrinted[l]==0 && prevValuesCS[l][2]==m) {
								fprintf(options->outFileStream,"INFO PREPROCESSING %s SF Detector Frequency   %-*d %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",lenFreq,prevValuesCS[l][2],lenListGrouped,strListGrouped[l],strMeas[l]);
								strPrinted[l]=1;
							}
						}
					}
				}

				for(l=0;l<numAuto;l++) {
					free(freqJoined[l]);
					free(freqJoinedText[l]);
					free(strListJoined[l]);
				}
				for(l=0;l<List.size;l++) {
					free(strMeas[l]);
					free(strListGrouped[l]);
					free(prevValuesCS[l]);
				}
				free(freqJoined);
				free(freqJoinedText);
				free(strListJoined);
				free(numFreqJoined);
				free(strMeas);
				free(strListGrouped);
				free(strPrinted);
				free(strPrintedAuto);
				free(prevValuesCS);
				freeRangeList(&List);
			} else {
				free(prevValuesCS);
			}
			//Print frequencies not checked or autofilled
			prevValuesCS=NULL;
			prevValuesCS=malloc(sizeof(int*));
			SelectedAMeas=0;
			for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
				for(i=0;i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						if (options->csSFfreqAutoChecked[staType][i][j][k][options->autoFillcsSF]==1) {
							InitRangeList((enum GNSSystem)i,j,&List);
							l=0;
							prevValuesCS[l]=NULL;
							prevValuesCS[l]=malloc(sizeof(int)*3);
							prevValuesCS[l][0]=i;
							prevValuesCS[l][1]=j;
							prevValuesCS[l][2]=k;
							SelectedAMeas=1;
							break;
						}
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) {
				for(k=prevValuesCS[0][2];k<MAX_FREQUENCIES_PER_GNSS;k++) {
					for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
						for(j=1;j<=listMaxSatGNSS[i];j++) {
							if (options->csSFfreqAutoChecked[staType][i][j][k][options->autoFillcsSF]==0||options->includeSatellite[i][j]==0) {
								//Frequency checked or satellite unchecked. End current range
								if (k!=prevValuesCS[l][2]) {
									//New frequency, add new range list
									if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
									}
								} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
									if(j==1) {
										//PRN 1 of new constellation
										if (i==prevValuesCS[l][0]) {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
										} else {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
										}
									} else {
										if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
										} else {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
										}
									}
								}
							} else {
								if (k!=prevValuesCS[l][2]) {
									//New frequency, add new range list
									if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
										//Last range has no end. Set it at the last satellite of the last constellation
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
									}
									AddRangeList((enum GNSSystem)i,j,&List);
									l=List.size-1;
									prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
									prevValuesCS[l]=NULL;
									prevValuesCS[l]=malloc(sizeof(int)*3);
									prevValuesCS[l][0]=i;
									prevValuesCS[l][1]=j;
									prevValuesCS[l][2]=k;
								} else {
									//Same frequency
									numOcurrences++;
									if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
										//The current satellite had the checked measurement
										//Check if previous satellite had it. If not, add a new range
										if (j==1) {
											if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
												ExtendRangeList((enum GNSSystem)i,j,l,&List);
											} 
										} else {
											if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
												ExtendRangeList((enum GNSSystem)i,j,l,&List);
											} 
										}
									}
								}
							}
						}
					}
				}
				//Save all the different blocks found
				strListGrouped=NULL;
				strMeas=NULL;
				strListGrouped=malloc(sizeof(char*)*List.size);
				strMeas=malloc(sizeof(char*)*List.size);
				lenMeas=lenListGrouped=0;
				for(l=0;l<List.size;l++) {
					//Alloc memory for text saving
					strListGrouped[l]=NULL;
					strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					strMeas[l]=NULL;
					strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					//Create the list of satellites per block
					SatRangeList2String(l,&List,auxstr);
					strcpy(strListGrouped[l],auxstr);
					sprintf(strMeas[l],"%d",prevValuesCS[l][2]);
					aux=(int)strlen(strMeas[l]);
					if (aux>lenMeas) lenMeas=aux;
					aux=(int)strlen(strListGrouped[l]);
					if (aux>lenListGrouped) lenListGrouped=aux;
				}
				//Join all lines with same satellite ranges
				auxstr[0]='\0';
				strListJoined=NULL;
				freqJoined=NULL;
				numFreqJoined=NULL;
				numAuto=0;
				lenFreq=0;
				for(l=0;l<List.size;l++) {
					if (numAuto==0) {
						strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
						strListJoined[numAuto]=NULL;
						strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
						freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
						freqJoined[numAuto]=NULL;
						freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
						numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
						strcpy(strListJoined[numAuto],strListGrouped[l]);
						freqJoined[numAuto][0]=prevValuesCS[l][2];
						numFreqJoined[numAuto]=1;
						numAuto++;
					} else {
						for(m=0;m<numAuto;m++) {
							if (m==l) continue;
							if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
						}
						if (m==numAuto) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][2];
							numFreqJoined[m]++;
						}
					}
				}
				for(l=0;l<numAuto;l++) {
					if (numFreqJoined[l]>lenFreq) {
						lenFreq=numFreqJoined[l];
					}
				}
				lenFreq=2*lenFreq-1; //To account for the "|" separator
				for(l=0;l<numAuto;l++) {
					auxstr[0]='\0';
					len=0;
					qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
					for(m=0;m<numFreqJoined[l];m++) {
						len+=sprintf(&auxstr[len],"%s%d",m==0?"":"|",freqJoined[l][m]);
					}
					fprintf(options->outFileStream,"INFO PREPROCESSING %s SF Detector %s Frequenc%s %-*s %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->autoFillcsSF==0?"Warning Unchecked":"Autofilled",numFreqJoined[l]==1?"y  ":"ies",lenFreq,auxstr,strListJoined[l]);
				}
				for(l=0;l<numAuto;l++) {
					free(strListJoined[l]);
					free(freqJoined[l]);
				}
				for(l=0;l<List.size;l++) {
					free(strListGrouped[l]);
					free(strMeas[l]);
					free(prevValuesCS[l]);
				}
				free(numFreqJoined);
				free(strListJoined);
				free(freqJoined);
				free(strListGrouped);
				free(strMeas);
				free(prevValuesCS);
				freeRangeList(&List);
			} else {
				fprintf(options->outFileStream,"INFO PREPROCESSING %s SF Detector: No frequencies %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->autoFillcsSF==0?"left unchecked":"autofilled");
				free(prevValuesCS);
			}
		}

		//Melboure Wubbena cycle slip print
		if (options->csMW) {
			//Initialize checked measurements
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					for (k=0;k<options->numcsMWMeasList[staType][i][j];k++) {
						PositionChecked[i][j][k]=0;
					}
				}
			}
			l=0;
			prevValuesCS=NULL;
			prevValuesCS=malloc(sizeof(int*));
			SelectedAMeas=0;
			NoMeasAvail=1;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue;
					for (k=0;k<options->numcsMWMeasList[staType][i][j];k++) {
						InitRangeList((enum GNSSystem)i,j,&List);
						prevValuesCS[l]=NULL;
						prevValuesCS[l]=malloc(sizeof(int)*8);
						prevValuesCS[l][0]=i;
						prevValuesCS[l][1]=j;
						prevValuesCS[l][2]=options->csMWMeasFreq[staType][i][j][k][0];
						prevValuesCS[l][3]=options->csMWMeasFreq[staType][i][j][k][1];
						prevValuesCS[l][4]=(int)options->csMWMeasList[staType][i][j][k][2];
						prevValuesCS[l][5]=(int)options->csMWMeasList[staType][i][j][k][3];
						prevValuesCS[l][6]=(int)options->csMWMeasList[staType][i][j][k][5];
						prevValuesCS[l][7]=(int)options->csMWMeasList[staType][i][j][k][6];
						SelectedAMeas=1;
						NoMeasAvail=0;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			while(SelectedAMeas==1) {
				numOcurrences=0;
				for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==prevValuesCS[l][0]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						for(k=0;k<options->numcsMWMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							DiffList=0;
							//Check if any value is different than the last values read
							for(m=0;m<2;m++) {
								if (options->csMWMeasFreq[staType][i][j][k][m]!=prevValuesCS[l][2+m]) {
									DiffList=1;
								}
							}
							if (DiffList==0) {
								for(m=2;m<NUMMEASCSMW+2;m++) {
									if(m==4) continue;
									if(m<4) {
										if (options->csMWMeasList[staType][i][j][k][m]!=(enum MeasurementType)prevValuesCS[l][m+2]) {
											DiffList=1;
										}
									} else {
										if (options->csMWMeasList[staType][i][j][k][m]!=(enum MeasurementType)prevValuesCS[l][m+1]) {
											DiffList=1;
										}
									}
								}
							}
							if (DiffList==0) {
								PositionChecked[i][j][k]=1;
								break;
							} else {
								continue;
							}
						}
						if (k==options->numcsMWMeasList[staType][i][j]||options->numcsMWMeasList[staType][i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
									//This is a satellite prior to the first satellite with the current measurement
									//Do nothing
								} else {
									//The current satellite did not have the checked measurement
									if(j==1) {
										//PRN 1 of new constellation
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
						} else {
							numOcurrences++;
							if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}//End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
				}//End for(i=0;i<MAX_GNSS;i++)			
				//Initialize with next measurement
				if (numOcurrences==1) {
					List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
					List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
				}
				SelectedAMeas=0;
				for(i=0;i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						for (k=0;k<options->numcsMWMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							AddRangeList((enum GNSSystem)i,j,&List);
							l=List.size-1;
							prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
							prevValuesCS[l]=NULL;
							prevValuesCS[l]=malloc(sizeof(int)*8);
							prevValuesCS[l][0]=i;
							prevValuesCS[l][1]=j;
							prevValuesCS[l][2]=options->csMWMeasFreq[staType][i][j][k][0];
							prevValuesCS[l][3]=options->csMWMeasFreq[staType][i][j][k][1];
							prevValuesCS[l][4]=options->csMWMeasList[staType][i][j][k][2];
							prevValuesCS[l][5]=options->csMWMeasList[staType][i][j][k][3];
							prevValuesCS[l][6]=options->csMWMeasList[staType][i][j][k][5];
							prevValuesCS[l][7]=options->csMWMeasList[staType][i][j][k][6];
							SelectedAMeas=1;
							PositionChecked[i][j][k]=1;
							break;
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==0) break;
			}
			if (NoMeasAvail==0) {
				//Save all the different blocks found
				strListGrouped=NULL;
				strMeas=NULL;
				strPrinted=NULL;
				strListGrouped=malloc(sizeof(char*)*List.size);
				strMeas=malloc(sizeof(char*)*List.size);
				strPrinted=malloc(sizeof(int)*List.size);
				lenMeas=lenListGrouped=0;
				for(l=0;l<List.size;l++) {
					//Alloc memory for text saving
					strListGrouped[l]=NULL;
					strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					strMeas[l]=NULL;
					strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					//Create the list of satellites per block
					SatRangeList2String(l,&List,auxstr);
					//Save data for later grouping by measurements
					i=prevValuesCS[l][0];
					j=prevValuesCS[l][1];
					if (prevValuesCS[l][4]==NA) {
						sprintf(strMeas[l],"Auto");
					} else {
						sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][4]));
						sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][5]));
						sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][6]));
						sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
					}
					strcpy(strListGrouped[l],auxstr);
					aux=(int)strlen(strMeas[l]);
					if (aux>lenMeas) lenMeas=aux;
					aux=(int)strlen(strListGrouped[l]);
					if (aux>lenListGrouped) lenListGrouped=aux;
				}
				//Join all lines with "Auto"
				auxstr[0]='\0';
				strListJoined=NULL;
				freqJoined=NULL;
				freqJoinedText=NULL;
				numFreqJoined=NULL;
				numAuto=0;
				lenFreq=0;
				for(l=0;l<List.size;l++) {
					if (strcmp(strMeas[l],"Auto")==0) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
							freqJoinedText[numAuto]=NULL;
							freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText[numAuto][0]='\0';
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
								freqJoinedText[numAuto]=NULL;
								freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText[numAuto][0]='\0';
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
						strPrinted[l]=1;
					} else {
						strPrinted[l]=0;
					}
				}
				strPrintedAuto=NULL;
				strPrintedAuto=malloc(sizeof(int)*numAuto);
				for(l=0;l<numAuto;l++) {
					if ((numFreqJoined[l])>lenFreq) {
						lenFreq=numFreqJoined[l];
					}
				}
				lenFreq=3*lenFreq-1; //To account for the "|" separator
				for(l=0;l<numAuto;l++) {
					auxstr[0]='\0';
					qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
					for(m=0;m<numFreqJoined[l];m++) {
						sprintf(auxstr,"%s%s%02d",freqJoinedText[l],m==0?"":"|",freqJoined[l][m]);
						sprintf(freqJoinedText[l],"%s",auxstr);
					}
					strPrintedAuto[l]=0;
				}
				if (List.size>numAuto) aux=List.size;
				else aux=numAuto;
				//Print values sorted by first pair of frequencies
				for(k=1;k<=MAX_FREQUENCIES_PER_GNSS;k++) {
					if (k==MAX_FREQUENCIES_PER_GNSS) m=0;
					else m=k;
					for(n=1;n<=MAX_FREQUENCIES_PER_GNSS;n++) {
						if (n==MAX_FREQUENCIES_PER_GNSS) p=0;
						else p=n;
						for(l=0;l<aux;l++) {
							//Lines for auto added frequencies
							if (l<numAuto) {
								if (strPrintedAuto[l]==0 && freqJoined[l][0]==(10*m+p)) {
									fprintf(options->outFileStream,"INFO PREPROCESSING %s %s Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->printV5format==0?"MW":"BW",lenFreq,freqJoinedText[l],lenListGrouped,strListJoined[l],"Auto");
									strPrintedAuto[l]=1;
								}
							}
							//Lines for user defined frequencies
							if (l<List.size) {
								if (strPrinted[l]==0 && (prevValuesCS[l][3]+10*prevValuesCS[l][2])==(10*m+p) ) {
									sprintf(auxstr,"%02d",prevValuesCS[l][3]+10*prevValuesCS[l][2]);
									fprintf(options->outFileStream,"INFO PREPROCESSING %s %s Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->printV5format==0?"MW":"BW",lenFreq,auxstr,lenListGrouped,strListGrouped[l],strMeas[l]);
									strPrinted[l]=1;
								}
							}
						}
					}
				}

				for(l=0;l<numAuto;l++) {
					free(freqJoined[l]);
					free(freqJoinedText[l]);
					free(strListJoined[l]);
				}
				for(l=0;l<List.size;l++) {
					free(strMeas[l]);
					free(strListGrouped[l]);
					free(prevValuesCS[l]);
				}
				free(freqJoined);
				free(freqJoinedText);
				free(strListJoined);
				free(numFreqJoined);
				free(strMeas);
				free(strListGrouped);
				free(strPrinted);
				free(strPrintedAuto);
				free(prevValuesCS);
				freeRangeList(&List);
			} else {
				free(prevValuesCS);
			}

			//Print frequencies not checked or autofilled
			for(p=0;p<2;p++) {
				if (p==0) type=options->autoFillcsMW;
				else if(p==1) {
					if (options->autoFillcsMW==UNCHECKFREQ) break;
					else type=UNCHECKFREQ;
				}
				prevValuesCS=NULL;
				prevValuesCS=malloc(sizeof(int*));
				SelectedAMeas=0;
				for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
					for(i=0;i<MAX_GNSS;i++) {
						for(j=1;j<=listMaxSatGNSS[i];j++) {
							if (options->includeSatellite[i][j]==0) continue;
							if (options->csMWfreqAutoChecked[staType][i][j][k][type]==1) {
								InitRangeList((enum GNSSystem)i,j,&List);
								l=0;
								prevValuesCS[l]=NULL;
								prevValuesCS[l]=malloc(sizeof(int)*3);
								prevValuesCS[l][0]=i;
								prevValuesCS[l][1]=j;
								prevValuesCS[l][2]=k;
								SelectedAMeas=1;
								break;
							}
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) {
					for(k=prevValuesCS[0][2];k<MAX_FREQUENCIES_PER_GNSS;k++) {
						for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
							for(j=1;j<=listMaxSatGNSS[i];j++) {
								if (options->csMWfreqAutoChecked[staType][i][j][k][type]==0||options->includeSatellite[i][j]==0) {
									//Frequency checked or satellite unselected. End current range
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
									} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
										if(j==1) {
											//PRN 1 of new constellation
											if (i==prevValuesCS[l][0]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
											}
										} else {
											if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
											}
										}
									}
								} else {
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											//Last range has no end. Set it at the last satellite of the last constellation
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
										AddRangeList((enum GNSSystem)i,j,&List);
										l=List.size-1;
										prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
										prevValuesCS[l]=NULL;
										prevValuesCS[l]=malloc(sizeof(int)*3);
										prevValuesCS[l][0]=i;
										prevValuesCS[l][1]=j;
										prevValuesCS[l][2]=k;
									} else {
										//Same frequency
										numOcurrences++;
										if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
											//The current satellite had the checked measurement
											//Check if previous satellite had it. If not, add a new range
											if (j==1) {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											} else {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											}
										}
									}
								}
							}
						}
					}
					//Save all the different blocks found
					strListGrouped=NULL;
					strMeas=NULL;
					strListGrouped=malloc(sizeof(char*)*List.size);
					strMeas=malloc(sizeof(char*)*List.size);
					lenMeas=lenListGrouped=0;
					for(l=0;l<List.size;l++) {
						//Alloc memory for text saving
						strListGrouped[l]=NULL;
						strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strMeas[l]=NULL;
						strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						//Create the list of satellites per block
						SatRangeList2String(l,&List,auxstr);
						strcpy(strListGrouped[l],auxstr);
						sprintf(strMeas[l],"%d",prevValuesCS[l][2]);
						aux=(int)strlen(strMeas[l]);
						if (aux>lenMeas) lenMeas=aux;
						aux=(int)strlen(strListGrouped[l]);
						if (aux>lenListGrouped) lenListGrouped=aux;
					}
					//Join all lines with same satellite ranges
					auxstr[0]='\0';
					strListJoined=NULL;
					freqJoined=NULL;
					numFreqJoined=NULL;
					numAuto=0;
					lenFreq=0;
					for(l=0;l<List.size;l++) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
					}
					for(l=0;l<numAuto;l++) {
						if (numFreqJoined[l]>lenFreq) {
							lenFreq=numFreqJoined[l];
						}
					}
					lenFreq=2*lenFreq-1; //To account for the "|" separator
					for(l=0;l<numAuto;l++) {
						auxstr[0]='\0';
						len=0;
						qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
						for(m=0;m<numFreqJoined[l];m++) {
							len+=sprintf(&auxstr[len],"%s%d",m==0?"":"|",freqJoined[l][m]);
						}
						fprintf(options->outFileStream,"INFO PREPROCESSING %s %s Detector: %s Frequenc%s %-*s %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->printV5format==0?"MW":"BW",type==0?(p==0?"Warning Unchecked":"Warning Could not autofill"):"Autofilled",numFreqJoined[l]==1?"y  ":"ies",lenFreq,auxstr,strListJoined[l]);
					}
					for(l=0;l<numAuto;l++) {
						free(strListJoined[l]);
						free(freqJoined[l]);
					}
					for(l=0;l<List.size;l++) {
						free(strListGrouped[l]);
						free(strMeas[l]);
						free(prevValuesCS[l]);
					}
					free(numFreqJoined);
					free(strListJoined);
					free(freqJoined);
					free(strListGrouped);
					free(strMeas);
					free(prevValuesCS);
					freeRangeList(&List);
				} else {
					if(p==0) {
						fprintf(options->outFileStream,"INFO PREPROCESSING %s %s Detector: No frequencies %s\n",staType==ROVERPOS?"Rover":"Reference Station",options->printV5format==0?"MW":"BW",type==0?"left unchecked":"autofilled");
					}
					free(prevValuesCS);
				}
			}
		}
		//LI cycle-slip print
		if (options->csLI) {
			//Initialize checked measurements
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					for (k=0;k<options->numcsLIMeasList[staType][i][j];k++) {
						PositionChecked[i][j][k]=0;
					}
				}
			}
			l=0;
			prevValuesCS=NULL;
			prevValuesCS=malloc(sizeof(int*));
			SelectedAMeas=0;
			NoMeasAvail=1;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue;
					for (k=0;k<options->numcsLIMeasList[staType][i][j];k++) {
						InitRangeList((enum GNSSystem)i,j,&List);
						prevValuesCS[l]=NULL;
						prevValuesCS[l]=malloc(sizeof(int)*6);
						prevValuesCS[l][0]=i;
						prevValuesCS[l][1]=j;
						prevValuesCS[l][2]=options->csLIMeasFreq[staType][i][j][k][0];
						prevValuesCS[l][3]=options->csLIMeasFreq[staType][i][j][k][1];
						prevValuesCS[l][4]=(int)options->csLIMeasList[staType][i][j][k][1];
						prevValuesCS[l][5]=(int)options->csLIMeasList[staType][i][j][k][2];
						SelectedAMeas=1;
						NoMeasAvail=0;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			while(SelectedAMeas==1) {
				numOcurrences=0;
				for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==prevValuesCS[l][0]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						for(k=0;k<options->numcsLIMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							DiffList=0;
							//Check if any value is different than the last values read
							for(m=0;m<2;m++) {
								if (options->csLIMeasFreq[staType][i][j][k][m]!=prevValuesCS[l][2+m]) {
									DiffList=1;
								}
							}
							if (DiffList==0) {
								for(m=0;m<2;m++) {
									if (options->csLIMeasList[staType][i][j][k][m+1]!=(enum MeasurementType)prevValuesCS[l][4+m]) {
										DiffList=1;
									}
								}
							}
							if (DiffList==0) {
								PositionChecked[i][j][k]=1;
								break;
							} else {
								continue;
							}
						}
						if (k==options->numcsLIMeasList[staType][i][j]||options->numcsLIMeasList[staType][i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
									//This is a satellite prior to the first satellite with the current measurement
									//Do nothing
								} else {
									//The current satellite did not have the checked measurement
									if(j==1) {
										//PRN 1 of new constellation
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
						} else {
							numOcurrences++;
							if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}//End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
				}//End for(i=0;i<MAX_GNSS;i++)			
				//Initialize with next measurement
				if (numOcurrences==1) {
					List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
					List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
				}
				SelectedAMeas=0;
				for(i=0;i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						for (k=0;k<options->numcsLIMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							AddRangeList((enum GNSSystem)i,j,&List);
							l=List.size-1;
							prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
							prevValuesCS[l]=NULL;
							prevValuesCS[l]=malloc(sizeof(int)*6);
							prevValuesCS[l][0]=i;
							prevValuesCS[l][1]=j;
							prevValuesCS[l][2]=options->csLIMeasFreq[staType][i][j][k][0];
							prevValuesCS[l][3]=options->csLIMeasFreq[staType][i][j][k][1];
							prevValuesCS[l][4]=options->csLIMeasList[staType][i][j][k][1];
							prevValuesCS[l][5]=options->csLIMeasList[staType][i][j][k][2];
							SelectedAMeas=1;
							PositionChecked[i][j][k]=1;
							break;
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==0) break;
			}
			if (NoMeasAvail==0) {
				//Save all the different blocks found
				strListGrouped=NULL;
				strMeas=NULL;
				strPrinted=NULL;
				strListGrouped=malloc(sizeof(char*)*List.size);
				strMeas=malloc(sizeof(char*)*List.size);
				strPrinted=malloc(sizeof(int)*List.size);
				lenMeas=lenListGrouped=0;
				for(l=0;l<List.size;l++) {
					//Alloc memory for text saving
					strListGrouped[l]=NULL;
					strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					strMeas[l]=NULL;
					strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					//Create the list of satellites per block
					SatRangeList2String(l,&List,auxstr);
					//Save data for later grouping by measurements
					i=prevValuesCS[l][0];
					j=prevValuesCS[l][1];
					if (prevValuesCS[l][4]==NA) {
						sprintf(strMeas[l],"Auto");
					} else {
						sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][4]));
						sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][5]));
					}
					strcpy(strListGrouped[l],auxstr);
					aux=(int)strlen(strMeas[l]);
					if (aux>lenMeas) lenMeas=aux;
					aux=(int)strlen(strListGrouped[l]);
					if (aux>lenListGrouped) lenListGrouped=aux;
				}
				//Join all lines with "Auto"
				auxstr[0]='\0';
				strListJoined=NULL;
				freqJoined=NULL;
				freqJoinedText=NULL;
				numFreqJoined=NULL;
				numAuto=0;
				lenFreq=0;
				for(l=0;l<List.size;l++) {
					if (strcmp(strMeas[l],"Auto")==0) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
							freqJoinedText[numAuto]=NULL;
							freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText[numAuto][0]='\0';
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
								freqJoinedText[numAuto]=NULL;
								freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText[numAuto][0]='\0';
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][3]+10*prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
						strPrinted[l]=1;
					} else {
						strPrinted[l]=0;
					}
				}
				strPrintedAuto=NULL;
				strPrintedAuto=malloc(sizeof(int)*numAuto);
				for(l=0;l<numAuto;l++) {
					if ((numFreqJoined[l])>lenFreq) {
						lenFreq=numFreqJoined[l];
					}
				}
				lenFreq=3*lenFreq-1; //To account for the "|" separator
				for(l=0;l<numAuto;l++) {
					auxstr[0]='\0';
					qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
					for(m=0;m<numFreqJoined[l];m++) {
						sprintf(auxstr,"%s%s%02d",freqJoinedText[l],m==0?"":"|",freqJoined[l][m]);
						sprintf(freqJoinedText[l],"%s",auxstr);
					}
					strPrintedAuto[l]=0;
				}
				if (List.size>numAuto) aux=List.size;
				else aux=numAuto;
				//Print values sorted by first pair of frequencies
				for(k=1;k<=MAX_FREQUENCIES_PER_GNSS;k++) {
					if (k==MAX_FREQUENCIES_PER_GNSS) m=0;
					else m=k;
					for(n=1;n<=MAX_FREQUENCIES_PER_GNSS;n++) {
						if (n==MAX_FREQUENCIES_PER_GNSS) p=0;
						else p=n;
						for(l=0;l<aux;l++) {
							//Lines for auto added frequencies
							if (l<numAuto) {
								if (strPrintedAuto[l]==0 && freqJoined[l][0]==(10*m+p)) {
									fprintf(options->outFileStream,"INFO PREPROCESSING %s LI Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",lenFreq,freqJoinedText[l],lenListGrouped,strListJoined[l],"Auto");
									strPrintedAuto[l]=1;
								}
							}
							//Lines for user defined frequencies
							if (l<List.size) {
								if (strPrinted[l]==0 && (prevValuesCS[l][3]+10*prevValuesCS[l][2])==(10*m+p) ) {
									sprintf(auxstr,"%02d",prevValuesCS[l][3]+10*prevValuesCS[l][2]);
									fprintf(options->outFileStream,"INFO PREPROCESSING %s LI Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",lenFreq,auxstr,lenListGrouped,strListGrouped[l],strMeas[l]);
									strPrinted[l]=1;
								}
							}
						}
					}
				}

				for(l=0;l<numAuto;l++) {
					free(freqJoined[l]);
					free(freqJoinedText[l]);
					free(strListJoined[l]);
				}
				for(l=0;l<List.size;l++) {
					free(strMeas[l]);
					free(strListGrouped[l]);
					free(prevValuesCS[l]);
				}
				free(freqJoined);
				free(freqJoinedText);
				free(strListJoined);
				free(numFreqJoined);
				free(strMeas);
				free(strListGrouped);
				free(strPrinted);
				free(strPrintedAuto);
				free(prevValuesCS);
				freeRangeList(&List);
			} else {
				free(prevValuesCS);
			}
			//Print frequencies not checked or autofilled
			for(p=0;p<2;p++) {
				if (p==0) type=options->autoFillcsLI;
				else if(p==1) {
					if (options->autoFillcsLI==UNCHECKFREQ) break;
					else type=UNCHECKFREQ;
				}
				prevValuesCS=NULL;
				prevValuesCS=malloc(sizeof(int*));
				SelectedAMeas=0;
				for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
					for(i=0;i<MAX_GNSS;i++) {
						for(j=1;j<=listMaxSatGNSS[i];j++) {
							if (options->includeSatellite[i][j]==0) continue;
							if (options->csLIfreqAutoChecked[staType][i][j][k][type]==1) {
								InitRangeList((enum GNSSystem)i,j,&List);
								l=0;
								prevValuesCS[l]=NULL;
								prevValuesCS[l]=malloc(sizeof(int)*3);
								prevValuesCS[l][0]=i;
								prevValuesCS[l][1]=j;
								prevValuesCS[l][2]=k;
								SelectedAMeas=1;
								break;
							}
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) {
					for(k=prevValuesCS[0][2];k<MAX_FREQUENCIES_PER_GNSS;k++) {
						for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
							for(j=1;j<=listMaxSatGNSS[i];j++) {
								if (options->csLIfreqAutoChecked[staType][i][j][k][type]==0||options->includeSatellite[i][j]==0) {
									//Frequency checked or satellite unselected. End current range
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
									} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
										if(j==1) {
											//PRN 1 of new constellation
											if (i==prevValuesCS[l][0]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
											}
										} else {
											if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
											}
										}
									}
								} else {
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											//Last range has no end. Set it at the last satellite of the last constellation
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
										AddRangeList((enum GNSSystem)i,j,&List);
										l=List.size-1;
										prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
										prevValuesCS[l]=NULL;
										prevValuesCS[l]=malloc(sizeof(int)*3);
										prevValuesCS[l][0]=i;
										prevValuesCS[l][1]=j;
										prevValuesCS[l][2]=k;
									} else {
										//Same frequency
										numOcurrences++;
										if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
											//The current satellite had the checked measurement
											//Check if previous satellite had it. If not, add a new range
											if (j==1) {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											} else {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											}
										}
									}
								}
							}
						}
					}
					//Save all the different blocks found
					strListGrouped=NULL;
					strMeas=NULL;
					strListGrouped=malloc(sizeof(char*)*List.size);
					strMeas=malloc(sizeof(char*)*List.size);
					lenMeas=lenListGrouped=0;
					for(l=0;l<List.size;l++) {
						//Alloc memory for text saving
						strListGrouped[l]=NULL;
						strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strMeas[l]=NULL;
						strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						//Create the list of satellites per block
						SatRangeList2String(l,&List,auxstr);
						strcpy(strListGrouped[l],auxstr);
						sprintf(strMeas[l],"%d",prevValuesCS[l][2]);
						aux=(int)strlen(strMeas[l]);
						if (aux>lenMeas) lenMeas=aux;
						aux=(int)strlen(strListGrouped[l]);
						if (aux>lenListGrouped) lenListGrouped=aux;
					}
					//Join all lines with same satellite ranges
					auxstr[0]='\0';
					strListJoined=NULL;
					freqJoined=NULL;
					numFreqJoined=NULL;
					numAuto=0;
					lenFreq=0;
					for(l=0;l<List.size;l++) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
					}
					for(l=0;l<numAuto;l++) {
						if (numFreqJoined[l]>lenFreq) {
							lenFreq=numFreqJoined[l];
						}
					}
					lenFreq=2*lenFreq-1; //To account for the "|" separator
					for(l=0;l<numAuto;l++) {
						auxstr[0]='\0';
						len=0;
						qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
						for(m=0;m<numFreqJoined[l];m++) {
							len+=sprintf(&auxstr[len],"%s%d",m==0?"":"|",freqJoined[l][m]);
						}
						fprintf(options->outFileStream,"INFO PREPROCESSING %s LI Detector: %s Frequenc%s %-*s %s\n",staType==ROVERPOS?"Rover":"Reference Station",type==0?(p==0?"Warning Unchecked":"Warning Could not autofill"):"Autofilled",numFreqJoined[l]==1?"y  ":"ies",lenFreq,auxstr,strListJoined[l]);
					}
					for(l=0;l<numAuto;l++) {
						free(strListJoined[l]);
						free(freqJoined[l]);
					}
					for(l=0;l<List.size;l++) {
						free(strListGrouped[l]);
						free(strMeas[l]);
						free(prevValuesCS[l]);
					}
					free(numFreqJoined);
					free(strListJoined);
					free(freqJoined);
					free(strListGrouped);
					free(strMeas);
					free(prevValuesCS);
					freeRangeList(&List);
				} else {
					if(p==0) {
						fprintf(options->outFileStream,"INFO PREPROCESSING %s LI Detector: No frequencies %s\n",staType==ROVERPOS?"Rover":"Reference Station",type==0?"left unchecked":"autofilled");
					}
					free(prevValuesCS);
				}
			}
		}
		//IGF cycle slip print
		if (options->csIGF) {
			//Initialize checked measurements
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					for (k=0;k<options->numcsIGFMeasList[staType][i][j];k++) {
						PositionChecked[i][j][k]=0;
					}
				}
			}
			l=0;
			prevValuesCS=NULL;
			prevValuesCS=malloc(sizeof(int*));
			SelectedAMeas=0;
			NoMeasAvail=1;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue;
					for (k=0;k<options->numcsIGFMeasList[staType][i][j];k++) {
						InitRangeList((enum GNSSystem)i,j,&List);
						prevValuesCS[l]=NULL;
						prevValuesCS[l]=malloc(sizeof(int)*10);
						prevValuesCS[l][0]=i;
						prevValuesCS[l][1]=j;
						prevValuesCS[l][2]=options->csIGFMeasFreq[staType][i][j][k][0];
						prevValuesCS[l][3]=options->csIGFMeasFreq[staType][i][j][k][1];
						prevValuesCS[l][4]=options->csIGFMeasFreq[staType][i][j][k][2];
						prevValuesCS[l][5]=options->csIGFMeasFreq[staType][i][j][k][3];
						prevValuesCS[l][6]=(int)options->csIGFMeasList[staType][i][j][k][2];
						prevValuesCS[l][7]=(int)options->csIGFMeasList[staType][i][j][k][3];
						prevValuesCS[l][8]=(int)options->csIGFMeasList[staType][i][j][k][5];
						prevValuesCS[l][9]=(int)options->csIGFMeasList[staType][i][j][k][6];
						SelectedAMeas=1;
						NoMeasAvail=0;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			while(SelectedAMeas==1) {
				numOcurrences=0;
				for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==prevValuesCS[l][0]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						for(k=0;k<options->numcsIGFMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							DiffList=0;
							//Check if any value is different than the last values read
							for(m=0;m<NUMMEASCSIGF;m++) {
								if (options->csIGFMeasFreq[staType][i][j][k][m]!=prevValuesCS[l][m+2]) {
									DiffList=1;
								}
							}
							if (DiffList==0) {
								for(m=2;m<=NUMMEASCSIGF+2;m++) {
									if(m==4) continue;
									if(m<4) {
										if (options->csIGFMeasList[staType][i][j][k][m]!=(enum MeasurementType)prevValuesCS[l][m+4]) {
											DiffList=1;
										}
									} else {
										if (options->csIGFMeasList[staType][i][j][k][m]!=(enum MeasurementType)prevValuesCS[l][m+3]) {
											DiffList=1;
										}
									}
								}
							}
							if (DiffList==0) {
								PositionChecked[i][j][k]=1;
								break;
							} else {
								continue;
							}
						}
						if (k==options->numcsIGFMeasList[staType][i][j]||options->numcsIGFMeasList[staType][i][j]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
									//This is a satellite prior to the first satellite with the current measurement
									//Do nothing
								} else {
									//The current satellite did not have the checked measurement
									if(j==1) {
										//PRN 1 of new constellation
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
						} else {
							numOcurrences++;
							if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}//End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
				}//End for(i=0;i<MAX_GNSS;i++)			
				//Initialize with next measurement
				if (numOcurrences==1) {
					List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
					List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
				}
				SelectedAMeas=0;
				for(i=0;i<MAX_GNSS;i++) {
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0) continue;
						for (k=0;k<options->numcsIGFMeasList[staType][i][j];k++) {
							if (PositionChecked[i][j][k]==1) continue;
							AddRangeList((enum GNSSystem)i,j,&List);
							l=List.size-1;
							prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
							prevValuesCS[l]=NULL;
							prevValuesCS[l]=malloc(sizeof(int)*10);
							prevValuesCS[l][0]=i;
							prevValuesCS[l][1]=j;
							prevValuesCS[l][2]=options->csIGFMeasFreq[staType][i][j][k][0];
							prevValuesCS[l][3]=options->csIGFMeasFreq[staType][i][j][k][1];
							prevValuesCS[l][4]=options->csIGFMeasFreq[staType][i][j][k][2];
							prevValuesCS[l][5]=options->csIGFMeasFreq[staType][i][j][k][3];
							prevValuesCS[l][6]=options->csIGFMeasList[staType][i][j][k][2];
							prevValuesCS[l][7]=options->csIGFMeasList[staType][i][j][k][3];
							prevValuesCS[l][8]=options->csIGFMeasList[staType][i][j][k][5];
							prevValuesCS[l][9]=options->csIGFMeasList[staType][i][j][k][6];
							SelectedAMeas=1;
							PositionChecked[i][j][k]=1;
							break;
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==0) break;
			}
			if (NoMeasAvail==0) {
				//Save all the different blocks found
				strListGrouped=NULL;
				strMeas=NULL;
				strPrinted=NULL;
				strListGrouped=malloc(sizeof(char*)*List.size);
				strMeas=malloc(sizeof(char*)*List.size);
				strPrinted=malloc(sizeof(int)*List.size);
				lenMeas=lenListGrouped=0;
				for(l=0;l<List.size;l++) {
					//Alloc memory for text saving
					strListGrouped[l]=NULL;
					strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					strMeas[l]=NULL;
					strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
					//Create the list of satellites per block
					SatRangeList2String(l,&List,auxstr);
					//Save data for later grouping by measurements
					i=prevValuesCS[l][0];
					j=prevValuesCS[l][1];
					if (prevValuesCS[l][6]==NA) {
						sprintf(strMeas[l],"Auto");
					} else {
						if (options->csIGFminNoise==1) {
							if (prevValuesCS[l][6]==prevValuesCS[l][8]) {
								//Repeated measurement is in third position
								sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][6]));
								sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
								sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][9]));
								strcpy(strMeas[l],auxstr2);
							} else if (prevValuesCS[l][6]==prevValuesCS[l][9]) {
								//Repeated measurement is in fourth position
								sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][6]));
								sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
								sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][8]));
								strcpy(strMeas[l],auxstr2);
							} else if (prevValuesCS[l][7]==prevValuesCS[l][8]) {
								//Repeated measurement is in third position
								sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][6]));
								sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
								sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][9]));
								strcpy(strMeas[l],auxstr2);
							} else if (prevValuesCS[l][7]==prevValuesCS[l][9]) {
								//Repeated measurement is in fourth position
								sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][6]));
								sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
								sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][8]));
								strcpy(strMeas[l],auxstr2);
							}
						} else {
							sprintf(auxstr2,"%s",meastype2measstr(prevValuesCS[l][6]));
							sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][7]));
							sprintf(auxstr2,"%s-%s",strMeas[l],meastype2measstr(prevValuesCS[l][8]));
							sprintf(strMeas[l],"%s-%s",auxstr2,meastype2measstr(prevValuesCS[l][9]));
						}
					}
					strcpy(strListGrouped[l],auxstr);
					aux=(int)strlen(strMeas[l]);
					if (aux>lenMeas) lenMeas=aux;
					aux=(int)strlen(strListGrouped[l]);
					if (aux>lenListGrouped) lenListGrouped=aux;
				}
				//Join all lines with "Auto"
				auxstr[0]='\0';
				strListJoined=NULL;
				freqJoined=NULL;
				freqJoinedText=NULL;
				numFreqJoined=NULL;
				numAuto=0;
				lenFreq=0;
				for(l=0;l<List.size;l++) {
					if (strcmp(strMeas[l],"Auto")==0) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
							freqJoinedText[numAuto]=NULL;
							freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoinedText[numAuto][0]='\0';
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][5]+10*prevValuesCS[l][4]+100*prevValuesCS[l][3]+1000*prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText=realloc(freqJoinedText,sizeof(char*)*(numAuto+1));
								freqJoinedText[numAuto]=NULL;
								freqJoinedText[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoinedText[numAuto][0]='\0';
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][5]+10*prevValuesCS[l][4]+100*prevValuesCS[l][3]+1000*prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][5]+10*prevValuesCS[l][4]+100*prevValuesCS[l][3]+1000*prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
						strPrinted[l]=1;
					} else {
						strPrinted[l]=0;
					}
				}
				strPrintedAuto=NULL;
				strPrintedAuto=malloc(sizeof(int)*numAuto);
				for(l=0;l<numAuto;l++) {
					if ((numFreqJoined[l])>lenFreq) {
						lenFreq=numFreqJoined[l];
					}
				}
				if (options->csIGFminNoise==1) {
					lenFreq=4*lenFreq-1; //To account for the "|" separator
				} else {
					lenFreq=5*lenFreq-1; //To account for the "|" separator
				}
				for(l=0;l<numAuto;l++) {
					auxstr[0]='\0';
					qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
					for(m=0;m<numFreqJoined[l];m++) {
						if (options->csIGFminNoise==1) {
							//Remove the repeated frequency, as for min noise only three frequencies are used
							sprintf(auxstr3,"%04d",freqJoined[l][m]);
							if (auxstr3[0]==auxstr3[2]) {
								//Repeated frequency is in third character
								auxstr3[2]=auxstr3[3];
								auxstr3[3]='\0';
							} else if (auxstr3[0]==auxstr3[3]) {
								//Repeated frequency is in fourth character
								auxstr3[3]='\0';
							} else if (auxstr3[1]==auxstr3[2]) {
								//Repeated frequency is in third character
								auxstr3[2]=auxstr3[3];
								auxstr3[3]='\0';
							} else if (auxstr3[1]==auxstr3[3]) {
								//Repeated frequency is in fourth character
								auxstr3[3]='\0';
							}
							sprintf(auxstr,"%s%s%s",freqJoinedText[l],m==0?"":"|",auxstr3);
						} else {
							sprintf(auxstr,"%s%s%04d",freqJoinedText[l],m==0?"":"|",freqJoined[l][m]);
						}
						sprintf(freqJoinedText[l],"%s",auxstr);
					}
					strPrintedAuto[l]=0;
				}
				if (List.size>numAuto) aux=List.size;
				else aux=numAuto;
				//Print values sorted by first pair of frequencies
				for(k=1;k<=MAX_FREQUENCIES_PER_GNSS;k++) {
					if (k==MAX_FREQUENCIES_PER_GNSS) m=0;
					else m=k;
					for(n=1;n<=MAX_FREQUENCIES_PER_GNSS;n++) {
						if (n==MAX_FREQUENCIES_PER_GNSS) p=0;
						else p=n;
						for(r=1;r<=MAX_FREQUENCIES_PER_GNSS;r++) {
							if (r==MAX_FREQUENCIES_PER_GNSS) s=0;
							else s=r;
							for(t=1;t<=MAX_FREQUENCIES_PER_GNSS;t++) {
								if (u==MAX_FREQUENCIES_PER_GNSS) u=0;
								else u=t;
								for(l=0;l<aux;l++) {
									//Lines for auto added frequencies
									if (l<numAuto) {
										if (strPrintedAuto[l]==0 && freqJoined[l][0]==(1000*m+100*p+10*s+u)) {
											fprintf(options->outFileStream,"INFO PREPROCESSING %s IGF Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",lenFreq,freqJoinedText[l],lenListGrouped,strListJoined[l],"Auto");
											strPrintedAuto[l]=1;
										}
									}
									//Lines for user defined frequencies
									if (l<List.size) {
										if (strPrinted[l]==0 && (prevValuesCS[l][3]+10*prevValuesCS[l][2])==(1000*m+100*p+10*s+u) ) {
											if (options->csIGFminNoise==1) {
												if (prevValuesCS[l][2]==prevValuesCS[l][4]) {
													//Repeated frequency is in third frequency
													sprintf(auxstr,"%03d",prevValuesCS[l][5]+10*prevValuesCS[l][3]+100*prevValuesCS[l][2]);
												} else if (prevValuesCS[l][2]==prevValuesCS[l][5]) {
													//Repeated frequency is in fourth frequency
													sprintf(auxstr,"%03d",prevValuesCS[l][4]+10*prevValuesCS[l][3]+100*prevValuesCS[l][2]);
												} else if (prevValuesCS[l][3]==prevValuesCS[l][4]) {
													//Repeated frequency is in third frequency
													sprintf(auxstr,"%03d",prevValuesCS[l][5]+10*prevValuesCS[l][3]+100*prevValuesCS[l][2]);
												} else if (prevValuesCS[l][3]==prevValuesCS[l][5]) {
													//Repeated frequency is in fourth frequency
													sprintf(auxstr,"%03d",prevValuesCS[l][4]+10*prevValuesCS[l][3]+100*prevValuesCS[l][2]);
												}
											} else {												
												sprintf(auxstr,"%04d",prevValuesCS[l][5]+10*prevValuesCS[l][4]+100*prevValuesCS[l][3]+1000*prevValuesCS[l][2]);
											}
											fprintf(options->outFileStream,"INFO PREPROCESSING %s IGF Detector Frequencies %-*s %-*s: %s\n",staType==ROVERPOS?"Rover":"Reference Station",lenFreq,auxstr,lenListGrouped,strListGrouped[l],strMeas[l]);
											strPrinted[l]=1;
										}
									}
								}
							}
						}
					}
				}

				for(l=0;l<numAuto;l++) {
					free(freqJoined[l]);
					free(freqJoinedText[l]);
					free(strListJoined[l]);
				}
				for(l=0;l<List.size;l++) {
					free(strMeas[l]);
					free(strListGrouped[l]);
					free(prevValuesCS[l]);
				}
				free(freqJoined);
				free(freqJoinedText);
				free(strListJoined);
				free(numFreqJoined);
				free(strMeas);
				free(strListGrouped);
				free(strPrinted);
				free(strPrintedAuto);
				free(prevValuesCS);
				freeRangeList(&List);
			} else {
				free(prevValuesCS);
			}

			//Print frequencies not checked or autofilled
			for(p=0;p<2;p++) {
				if (p==0) type=options->autoFillcsIGF;
				else if(p==1) {
					if (options->autoFillcsIGF==UNCHECKFREQ) break;
					else type=UNCHECKFREQ;
				}
				prevValuesCS=NULL;
				prevValuesCS=malloc(sizeof(int*));
				SelectedAMeas=0;
				for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
					for(i=0;i<MAX_GNSS;i++) {
						for(j=1;j<=listMaxSatGNSS[i];j++) {
							if (options->includeSatellite[i][j]==0) continue;
							if (options->csIGFfreqAutoChecked[staType][i][j][k][type]==1) {
								InitRangeList((enum GNSSystem)i,j,&List);
								l=0;
								prevValuesCS[l]=NULL;
								prevValuesCS[l]=malloc(sizeof(int)*3);
								prevValuesCS[l][0]=i;
								prevValuesCS[l][1]=j;
								prevValuesCS[l][2]=k;
								SelectedAMeas=1;
								break;
							}
						}
						if (SelectedAMeas==1) break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) {
					for(k=prevValuesCS[0][2];k<MAX_FREQUENCIES_PER_GNSS;k++) {
						for(i=prevValuesCS[l][0];i<MAX_GNSS;i++) {
							for(j=1;j<=listMaxSatGNSS[i];j++) {
								if (options->csIGFfreqAutoChecked[staType][i][j][k][type]==0||options->includeSatellite[i][j]==0) {
									//Frequency checked or satellite unselected. End current range
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
									} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
										if(j==1) {
											//PRN 1 of new constellation
											if (i==prevValuesCS[l][0]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
											}
										} else {
											if (i==prevValuesCS[l][0] && j<=prevValuesCS[l][1]) {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
											} else {
												List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
												List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
											}
										}
									}
								} else {
									if (k!=prevValuesCS[l][2]) {
										//New frequency, add new range list
										if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
											//Last range has no end. Set it at the last satellite of the last constellation
											List.listSatGNSS[l][List.numJumpslist[l]-1][1]=MAX_GNSS-1;
											List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[MAX_GNSS-1];
										}
										AddRangeList((enum GNSSystem)i,j,&List);
										l=List.size-1;
										prevValuesCS=realloc(prevValuesCS,sizeof(int*)*List.size);
										prevValuesCS[l]=NULL;
										prevValuesCS[l]=malloc(sizeof(int)*3);
										prevValuesCS[l][0]=i;
										prevValuesCS[l][1]=j;
										prevValuesCS[l][2]=k;
									} else {
										//Same frequency
										numOcurrences++;
										if (i!=prevValuesCS[l][0] || j!=prevValuesCS[l][1]) {
											//The current satellite had the checked measurement
											//Check if previous satellite had it. If not, add a new range
											if (j==1) {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											} else {
												if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
													ExtendRangeList((enum GNSSystem)i,j,l,&List);
												} 
											}
										}
									}
								}
							}
						}
					}
					//Save all the different blocks found
					strListGrouped=NULL;
					strMeas=NULL;
					strListGrouped=malloc(sizeof(char*)*List.size);
					strMeas=malloc(sizeof(char*)*List.size);
					lenMeas=lenListGrouped=0;
					for(l=0;l<List.size;l++) {
						//Alloc memory for text saving
						strListGrouped[l]=NULL;
						strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strMeas[l]=NULL;
						strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
						//Create the list of satellites per block
						SatRangeList2String(l,&List,auxstr);
						strcpy(strListGrouped[l],auxstr);
						sprintf(strMeas[l],"%d",prevValuesCS[l][2]);
						aux=(int)strlen(strMeas[l]);
						if (aux>lenMeas) lenMeas=aux;
						aux=(int)strlen(strListGrouped[l]);
						if (aux>lenListGrouped) lenListGrouped=aux;
					}
					//Join all lines with same satellite ranges
					auxstr[0]='\0';
					strListJoined=NULL;
					freqJoined=NULL;
					numFreqJoined=NULL;
					numAuto=0;
					lenFreq=0;
					for(l=0;l<List.size;l++) {
						if (numAuto==0) {
							strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
							strListJoined[numAuto]=NULL;
							strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
							freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
							freqJoined[numAuto]=NULL;
							freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
							numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
							strcpy(strListJoined[numAuto],strListGrouped[l]);
							freqJoined[numAuto][0]=prevValuesCS[l][2];
							numFreqJoined[numAuto]=1;
							numAuto++;
						} else {
							for(m=0;m<numAuto;m++) {
								if (m==l) continue;
								if (strcmp(strListJoined[m],strListGrouped[l])==0) break;
							}
							if (m==numAuto) {
								strListJoined=realloc(strListJoined,sizeof(char*)*(numAuto+1));
								strListJoined[numAuto]=NULL;
								strListJoined[numAuto]=malloc(sizeof(char)*MAX_INPUT_LINE);
								freqJoined=realloc(freqJoined,sizeof(int*)*(numAuto+1));
								freqJoined[numAuto]=NULL;
								freqJoined[numAuto]=malloc(sizeof(int)*MAX_FREQUENCIES_PER_GNSS);
								numFreqJoined=realloc(numFreqJoined,sizeof(int)*(numAuto+1));
								strcpy(strListJoined[numAuto],strListGrouped[l]);
								freqJoined[numAuto][0]=prevValuesCS[l][2];
								numFreqJoined[numAuto]=1;
								numAuto++;
							} else {
								freqJoined[m][numFreqJoined[m]]=prevValuesCS[l][2];
								numFreqJoined[m]++;
							}
						}
					}
					for(l=0;l<numAuto;l++) {
						if (numFreqJoined[l]>lenFreq) {
							lenFreq=numFreqJoined[l];
						}
					}
					lenFreq=2*lenFreq-1; //To account for the "|" separator
					for(l=0;l<numAuto;l++) {
						auxstr[0]='\0';
						len=0;
						qsort(freqJoined[l],numFreqJoined[l],sizeof(int),qsort_compare_int);
						for(m=0;m<numFreqJoined[l];m++) {
							len+=sprintf(&auxstr[len],"%s%d",m==0?"":"|",freqJoined[l][m]);
						}
						fprintf(options->outFileStream,"INFO PREPROCESSING %s IGF Detector: %s Frequenc%s %-*s %s\n",staType==ROVERPOS?"Rover":"Reference Station",type==0?(p==0?"Warning Unchecked":"Warning Could not autofill"):"Autofilled",numFreqJoined[l]==1?"y  ":"ies",lenFreq,auxstr,strListJoined[l]);
					}
					for(l=0;l<numAuto;l++) {
						free(strListJoined[l]);
						free(freqJoined[l]);
					}
					for(l=0;l<List.size;l++) {
						free(strListGrouped[l]);
						free(strMeas[l]);
						free(prevValuesCS[l]);
					}
					free(numFreqJoined);
					free(strListJoined);
					free(freqJoined);
					free(strListGrouped);
					free(strMeas);
					free(prevValuesCS);
					freeRangeList(&List);
				} else {
					if(p==0) {
						fprintf(options->outFileStream,"INFO PREPROCESSING %s IGF Detector: No frequencies %s\n",staType==ROVERPOS?"Rover":"Reference Station",type==0?"left unchecked":"autofilled");
					}
					free(prevValuesCS);
				}
			}
		}
	}

	//Print SNR thresholds
	if(options->SNRminfilter == 1) {
		prevMeas=0;
		numLines=0;
		measList=NULL;
		strList=NULL;
		strListGrouped=NULL;
		strListMeasGrouped=NULL;
		ThresholdList=NULL;
		ThresholdListGrouped=NULL;
		SelectedAMeas=0;
		//Look for first selected satellite
		for (i=0;i<MAX_GNSS;i++) {
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==1) {
					initGNSS=i;
					initPRN=j;
					SelectedAMeas=1;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==1) {
			//All satellites unselected
			for (meas=2;meas<I1;meas+=4) { //Loop through all carrier phase measurements (as the other types will have the same SNR threshold)
				l=0;
				codeMeas=meas-1;
				DopplerMeas=meas+1;
				measAvail=0;
				numOcurrences=0;
				InitRangeList((enum GNSSystem)initGNSS,initPRN,&List);
				prevValuesSNR=NULL;
				prevValuesSNR=malloc(sizeof(double*));
				prevValuesSNR[0]=NULL;
				prevValuesSNR[0]=malloc(sizeof(double)*4);
				prevValuesSNR[0][3]=0.;
				for(i=initGNSS;i<MAX_GNSS;i++) {
					//Check if current measurement (or its code or Doppler type) is in the observation file
					if (epoch->measOrder[i].meas2Ind[meas]==-1 && epoch->measOrder[i].meas2Ind[codeMeas]==-1 &&
							epoch->measOrder[i].meas2Ind[DopplerMeas]==-1) {
						if (i==initGNSS || (int)prevValuesSNR[l][3]==0) {
							List.listSatGNSS[l][List.numJumpslist[l]-1][0]=i+1;
							List.listSatPRN[l][List.numJumpslist[l]-1][0]=1;
						} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							//New constellation
							if (i==(int)prevValuesSNR[l][1]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						}
						continue;
					}
					if (prevMeas!=meas) {
						//Initialize previous values with the data of the first satellite to be read
						prevValuesSNR[0][0]=options->SNRminvalues[i][1][meas];
						prevValuesSNR[0][1]=(double)i;
						prevValuesSNR[0][2]=(double)j;
						freq=getFrequencyInt(meas);
						prevMeas=meas;
						//Set measurement as available (in any constellation)
						measAvail=1;
					}
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0||options->usableFreq[i][j][freq]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==(int)prevValuesSNR[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==(int)prevValuesSNR[l][1] && j<=(int)prevValuesSNR[l][2]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						if (options->SNRminvalues[i][j][meas]!=prevValuesSNR[l][0]) {
							//Values are different. Look if these values were already saved before
							for(m=0;m<List.size;m++) {
								if (prevValuesSNR[m][0]==options->SNRminvalues[i][j][meas]) {
									//Values already saved. Extend the list
									break;
								}
							}
							if (m==List.size) {
								//Block not found. New SNR value
								AddRangeList((enum GNSSystem)i,j,&List);
								prevValuesSNR=realloc(prevValuesSNR,sizeof(double*)*List.size);
								prevValuesSNR[m]=NULL;
								prevValuesSNR[m]=malloc(sizeof(double)*4);
								prevValuesSNR[m][0]=options->SNRminvalues[i][j][meas];
								prevValuesSNR[m][1]=(double)i;
								prevValuesSNR[m][2]=(double)j;
								prevValuesSNR[m][3]=1.;
							} else {
								//Block found (SNR was already read before). Extend the list with the new start of range
								ExtendRangeList((enum GNSSystem)i,j,m,&List);
								prevValuesSNR[m][3]+=1.;
							}
							//Save the end of the range
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==(int)prevValuesSNR[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==(int)prevValuesSNR[l][1] && j<=(int)prevValuesSNR[l][2]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							//Save the index of the last type of block we are using to compare
							l=m;
						} else {
							prevValuesSNR[l][3]+=1.;
							if (i!=(int)prevValuesSNR[l][1] || j!=(int)prevValuesSNR[l][2]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}
				}
				numOcurrences=0;
				for(l=0;l<List.size;l++) {
					numOcurrences+=(int)prevValuesSNR[l][3];
					if ((int)prevValuesSNR[l][3]==1) {
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
					}
				}
				if (numOcurrences==0) measAvail=0;
				//Save all the different blocks found
				if (measAvail==1) {
					for(l=0;l<List.size;l++) {
						//Create the list of satellites per block
						SatRangeList2String(l,&List,auxstr);
						//Save data line for later grouping by measurement
						measList=realloc(measList,sizeof(enum MeasurementType)*(numLines+1));
						measList[numLines]=meas;
						strList=realloc(strList,sizeof(char*)*(numLines+1));
						strList[numLines]=NULL;
						strListGrouped=realloc(strListGrouped,sizeof(char*)*(numLines+1));
						strListGrouped[numLines]=NULL;
						strListMeasGrouped=realloc(strListMeasGrouped,sizeof(char*)*(numLines+1));
						strListMeasGrouped[numLines]=NULL;
						strList[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strListGrouped[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strListMeasGrouped[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strcpy(strList[numLines],auxstr);
						ThresholdList=realloc(ThresholdList,sizeof(double)*(numLines+1));
						ThresholdList[numLines]=prevValuesSNR[l][0];
						ThresholdListGrouped=realloc(ThresholdListGrouped,sizeof(double)*(numLines+1));
						numLines++;

						free(prevValuesSNR[l]);
					}
				} else {
					free(prevValuesSNR[0]);
				}
				free(prevValuesSNR);
				freeRangeList(&List);
			}
			//Group all string by measurement
			GroupSatRangeByMeas(1,numLines,measList,ThresholdList,strList,&numLinesGrouped,strListMeasGrouped,strListGrouped,ThresholdListGrouped);
			lenListGrouped=0;
			lenListMeasGrouped=0;
			for(l=0;l<numLinesGrouped;l++) {
				aux=(int)strlen(strListGrouped[l]);
				if (aux>lenListGrouped) lenListGrouped=aux;
				aux=(int)strlen(strListMeasGrouped[l]);
				if (aux>lenListMeasGrouped) lenListMeasGrouped=aux;
			}
			for(l=0;l<numLinesGrouped;l++) {
				sprintf(auxstr,"%s):",strListMeasGrouped[l]);
				fprintf(options->outFileStream,"INFO PREPROCESSING Minimum SNR Mask (attribute%s %-*s%-*s: %.6g (dBHz)\n",strlen(strListMeasGrouped[l])>2?"s":" ",lenListMeasGrouped+2,auxstr,lenListGrouped,strListGrouped[l],ThresholdListGrouped[l]);
			}

			//Free memory
			for(l=0;l<numLines;l++) {
				free(strList[l]);
				free(strListGrouped[l]);
				free(strListMeasGrouped[l]);
			}
			free(measList);
			free(ThresholdList);
			free(ThresholdListGrouped);
			free(strList);
			free(strListGrouped);
			free(strListMeasGrouped);
		}
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Minimum SNR Mask: OFF\n");
	}

	if(options->SNRmaxfilter == 1) {
		prevMeas=0;
		numLines=0;
		measList=NULL;
		strList=NULL;
		strListGrouped=NULL;
		strListMeasGrouped=NULL;
		ThresholdList=NULL;
		ThresholdListGrouped=NULL;
		SelectedAMeas=0;
		//Look for first selected satellite
		for (i=0;i<MAX_GNSS;i++) {
			for (j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==1) {
					initGNSS=i;
					initPRN=j;
					SelectedAMeas=1;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==1) {
			//All satellites unselected
			for (meas=2;meas<I1;meas+=4) { //Loop through all carrier phase measurements (as the other types will have the same SNR threshold)
				l=0;
				codeMeas=meas-1;
				DopplerMeas=meas+1;
				measAvail=0;
				numOcurrences=0;
				InitRangeList((enum GNSSystem)initGNSS,initPRN,&List);
				prevValuesSNR=NULL;
				prevValuesSNR=malloc(sizeof(double*));
				prevValuesSNR[0]=NULL;
				prevValuesSNR[0]=malloc(sizeof(double)*4);
				prevValuesSNR[0][3]=0.;
				for(i=initGNSS;i<MAX_GNSS;i++) {
					//Check if current measurement (or its code or Doppler type) is in the observation file
					if (epoch->measOrder[i].meas2Ind[meas]==-1 && epoch->measOrder[i].meas2Ind[codeMeas]==-1 &&
							epoch->measOrder[i].meas2Ind[DopplerMeas]==-1) {
						if (i==initGNSS || (int)prevValuesSNR[l][3]==0) {
							List.listSatGNSS[l][List.numJumpslist[l]-1][0]=i+1;
							List.listSatPRN[l][List.numJumpslist[l]-1][0]=1;
						} else if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							//New constellation
							if (i==(int)prevValuesSNR[l][1]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						}
						continue;
					}
					if (prevMeas!=meas) {
						//Initialize previous values with the data of the first satellite to be read
						prevValuesSNR[0][0]=options->SNRmaxvalues[i][1][meas];
						prevValuesSNR[0][1]=(double)i;
						prevValuesSNR[0][2]=(double)j;
						freq=getFrequencyInt(meas);
						prevMeas=meas;
						//Set measurement as available (in any constellation)
						measAvail=1;
					}
					for(j=1;j<=listMaxSatGNSS[i];j++) {
						if (options->includeSatellite[i][j]==0||options->usableFreq[i][j][freq]==0) {
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==(int)prevValuesSNR[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==(int)prevValuesSNR[l][1] && j<=(int)prevValuesSNR[l][2]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							continue;
						}
						if (options->SNRmaxvalues[i][j][meas]!=prevValuesSNR[l][0]) {
							//Values are different. Look if these values were already saved before
							for(m=0;m<List.size;m++) {
								if (prevValuesSNR[m][0]==options->SNRmaxvalues[i][j][meas]) {
									//Values already saved. Extend the list
									break;
								}
							}
							if (m==List.size) {
								//Block not found. New SNR value
								AddRangeList((enum GNSSystem)i,j,&List);
								prevValuesSNR=realloc(prevValuesSNR,sizeof(double*)*List.size);
								prevValuesSNR[m]=NULL;
								prevValuesSNR[m]=malloc(sizeof(double)*4);
								prevValuesSNR[m][0]=options->SNRmaxvalues[i][j][meas];
								prevValuesSNR[m][1]=(double)i;
								prevValuesSNR[m][2]=(double)j;
								prevValuesSNR[m][3]=1.;
							} else {
								//Block found (SNR was already read before). Extend the list with the new start of range
								ExtendRangeList((enum GNSSystem)i,j,m,&List);
								prevValuesSNR[m][3]+=1.;
							}
							//Save the end of the range
							if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
								if(j==1) {
									//PRN 1 of new constellation
									if (i==(int)prevValuesSNR[l][1]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
									}
								} else {
									if (i==(int)prevValuesSNR[l][1] && j<=(int)prevValuesSNR[l][2]) {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
									} else {
										List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
										List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
									}
								}
							}
							//Save the index of the last type of block we are using to compare
							l=m;
						} else {
							prevValuesSNR[l][3]+=1.;
							if (i!=(int)prevValuesSNR[l][1] || j!=(int)prevValuesSNR[l][2]) {
								//The current satellite had the checked measurement
								//Check if previous satellite had it. If not, add a new range
								if (j==1) {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								} else {
									if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
										ExtendRangeList((enum GNSSystem)i,j,l,&List);
									} 
								}
							}
						}
					}
				}
				numOcurrences=0;
				for(l=0;l<List.size;l++) {
					numOcurrences+=(int)prevValuesSNR[l][3];
					if ((int)prevValuesSNR[l][3]==1) {
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
					}
				}
				if (numOcurrences==0) measAvail=0;
				//Save all the different blocks found
				if (measAvail==1) {
					for(l=0;l<List.size;l++) {
						//Create the list of satellites per block
						SatRangeList2String(l,&List,auxstr);
						//Save data line for later grouping by measurement
						measList=realloc(measList,sizeof(enum MeasurementType)*(numLines+1));
						measList[numLines]=meas;
						strList=realloc(strList,sizeof(char*)*(numLines+1));
						strList[numLines]=NULL;
						strListGrouped=realloc(strListGrouped,sizeof(char*)*(numLines+1));
						strListGrouped[numLines]=NULL;
						strListMeasGrouped=realloc(strListMeasGrouped,sizeof(char*)*(numLines+1));
						strListMeasGrouped[numLines]=NULL;
						strList[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strListGrouped[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strListMeasGrouped[numLines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strcpy(strList[numLines],auxstr);
						ThresholdList=realloc(ThresholdList,sizeof(double)*(numLines+1));
						ThresholdList[numLines]=prevValuesSNR[l][0];
						ThresholdListGrouped=realloc(ThresholdListGrouped,sizeof(double)*(numLines+1));
						numLines++;

						free(prevValuesSNR[l]);
					}
				} else {
					free(prevValuesSNR[0]);
				}
				free(prevValuesSNR);
				freeRangeList(&List);
			}
			//Group all string by measurement
			GroupSatRangeByMeas(1,numLines,measList,ThresholdList,strList,&numLinesGrouped,strListMeasGrouped,strListGrouped,ThresholdListGrouped);
			lenListGrouped=0;
			lenListMeasGrouped=0;
			for(l=0;l<numLinesGrouped;l++) {
				aux=(int)strlen(strListGrouped[l]);
				if (aux>lenListGrouped) lenListGrouped=aux;
				aux=(int)strlen(strListMeasGrouped[l]);
				if (aux>lenListMeasGrouped) lenListMeasGrouped=aux;
			}
			for(l=0;l<numLinesGrouped;l++) {
				sprintf(auxstr,"%s):",strListMeasGrouped[l]);
				fprintf(options->outFileStream,"INFO PREPROCESSING Maximum SNR Mask (attribute%s %-*s%-*s: %.6g (dBHz)\n",strlen(strListMeasGrouped[l])>2?"s":" ",lenListMeasGrouped+2,auxstr,lenListGrouped,strListGrouped[l],ThresholdListGrouped[l]);
			}

			//Free memory
			for(l=0;l<numLines;l++) {
				free(strList[l]);
				free(strListGrouped[l]);
				free(strListMeasGrouped[l]);
			}
			free(measList);
			free(ThresholdList);
			free(ThresholdListGrouped);
			free(strList);
			free(strListGrouped);
			free(strListMeasGrouped);
		}
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Maximum SNR Mask: OFF\n");
	}

	fprintf(options->outFileStream,"INFO MODELLING Satellite clock offset correction: %3s\n",options->satelliteClockCorrection?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Consider satellite movement during signal flight time: %3s\n",options->timeTrans?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Consider Earth rotation during signal flight time: %3s\n",options->earthRotation?"ON":"OFF");

	numLines=numPrinted=0;
	numLinesGrouped=0;
	lenFreq=0;
	antennaValues=NULL;
	FreqTextList=NULL;
	strPrinted=NULL;
	strList=NULL;
	for (i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=MAX_FREQUENCIES_PER_GNSS;j++) {
			if(j==MAX_FREQUENCIES_PER_GNSS) k=0;
			else k=j;
			for(n=1;n<=listMaxSatGNSS[i];n++) {
				if (options->usableFreq[i][n][k]==1) {
					break;
				}
			}
			if (n<=listMaxSatGNSS[i] && epoch->measOrder[i].availFreq[k]==1 && availGNSSFreq[i][k]==1) {
				for(l=1;l<=listMaxSatGNSS[i];l++) {
					if (options->includeSatellite[i][l]==1) {
						break;
					}
				}
				if (l<=listMaxSatGNSS[i]) {
					//Any satellite for the current constellation selected
					antennaValues=realloc(antennaValues,sizeof(double*)*(numLines+1));
					antennaValues[numLines]=NULL;
					antennaValues[numLines]=malloc(sizeof(double)*5);
					antennaValues[numLines][0]=(double)i;
					antennaValues[numLines][1]=(double)k;
					antennaValues[numLines][2]=epoch->receiver.antenna.PCO[i][k][0];
					antennaValues[numLines][3]=epoch->receiver.antenna.PCO[i][k][1];
					antennaValues[numLines][4]=epoch->receiver.antenna.PCO[i][k][2];
					numLines++;
				}
			}
		}
	}
	strPrinted=malloc(sizeof(int)*numLines);
	for (i=0;i<numLines;i++) {
		strPrinted[i]=0;
	}
	while(numPrinted<numLines) {
		m=-1;
		for (i=0;i<numLines;i++) {
			if (strPrinted[i]==1) continue;
			if (m==-1) {
				GNSS=(enum GNSSystem)antennaValues[i][0];
				FreqTextList=realloc(FreqTextList,sizeof(char*)*(numLinesGrouped+1));
				FreqTextList[numLinesGrouped]=NULL;
				FreqTextList[numLinesGrouped]=malloc(sizeof(char)*MAX_INPUT_LINE);
				sprintf(FreqTextList[numLinesGrouped],"%3s F%d",gnsstype2gnssstr(GNSS),(int)antennaValues[i][1]);
				strList=realloc(strList,sizeof(char*)*(numLinesGrouped+1));
				strList[numLinesGrouped]=NULL;
				strList[numLinesGrouped]=malloc(sizeof(char)*MAX_INPUT_LINE);
				sprintf(strList[numLinesGrouped],"%8.5f %8.5f %8.5f",antennaValues[i][2],antennaValues[i][3],antennaValues[i][4]);
				strPrinted[i]=1;
				numLinesGrouped++;
				numPrinted++;
				numJoined=1;
				m=i;
			} else if (antennaValues[i][2]==antennaValues[m][2] && antennaValues[i][3]==antennaValues[m][3] && antennaValues[i][4]==antennaValues[m][4]) {
				if (GNSS==(enum GNSSystem)antennaValues[i][0]) {
					sprintf(auxstr,"%s F%d",FreqTextList[numLinesGrouped-1],(int)antennaValues[i][1]);
					 sprintf(FreqTextList[numLinesGrouped-1],"%s",auxstr);
				} else {
					if (numJoined<3) {
						GNSS=(enum GNSSystem)antennaValues[i][0];
						sprintf(auxstr,"%s | %3s F%d",FreqTextList[numLinesGrouped-1],gnsstype2gnssstr(GNSS),(int)antennaValues[i][1]);
						sprintf(FreqTextList[numLinesGrouped-1],"%s",auxstr);
						numJoined++;
					} else { //A maximum of 3 constellations in one line are allowed in order not to make the line too long
						GNSS=(enum GNSSystem)antennaValues[i][0];
						FreqTextList=realloc(FreqTextList,sizeof(char*)*(numLinesGrouped+1));
						FreqTextList[numLinesGrouped]=NULL;
						FreqTextList[numLinesGrouped]=malloc(sizeof(char)*MAX_INPUT_LINE);
						sprintf(FreqTextList[numLinesGrouped],"%3s F%d",gnsstype2gnssstr(GNSS),(int)antennaValues[i][1]);
						strList=realloc(strList,sizeof(char*)*(numLinesGrouped+1));
						strList[numLinesGrouped]=NULL;
						strList[numLinesGrouped]=malloc(sizeof(char)*MAX_INPUT_LINE);
						sprintf(strList[numLinesGrouped],"%8.5f %8.5f %8.5f",antennaValues[i][2],antennaValues[i][3],antennaValues[i][4]);
						numLinesGrouped++;
						numJoined=1;
						m=i;
					}
				}
				strPrinted[i]=1;
				numPrinted++;
			}
		}
	}
	for (i=0;i<numLinesGrouped;i++) {
		aux=(int)strlen(FreqTextList[i]);
		if(aux>lenFreq) {
			lenFreq=aux;
		}
	}
	for (i=0;i<numLinesGrouped;i++) {
		fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Phase Center Offset (PCO): %-*s %s (metres)\n",lenFreq,FreqTextList[i],strList[i]);
	}

	for (i=0;i<numLinesGrouped;i++) {
		free(FreqTextList[i]);
		free(strList[i]);
	}
	for (i=0;i<numLines;i++) {
		free(antennaValues[i]);
	}
	free(FreqTextList);
	free(strList);
	free(antennaValues);
	free(strPrinted);


	fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Phase Center variation correction: %3s\n",options->receiverPhaseVar?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Satellite mass centre to Antenna Phase Centre (APC) correction: %3s\n",options->satellitePhaseCenter?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Satellite mass centre to Antenna Phase Centre variation correction:  %3s\n",options->satellitePhaseVar?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Reference Point (ARP): %7.4f %7.4f %7.4f (metres)\n",epoch->receiver.ARP[0],epoch->receiver.ARP[1],epoch->receiver.ARP[2]);
	fprintf(options->outFileStream,"INFO MODELLING Relativistic clock correction: %3s\n",options->relativisticCorrection?"ON":"OFF");
	if (options->ionoModel == NoIonoModel) strcpy(auxstr,"OFF");
	else if (options->ionoModel == KlobucharIonoModel) strcpy(auxstr,"Klobuchar");
	else if (options->ionoModel == BeiDouIonoModel) strcpy(auxstr,"BeiDou");
	else if (options->ionoModel == neQuickIonoModel) strcpy(auxstr,"NeQuick");
	else if (options->ionoModel == IONEXIonoModel) strcpy(auxstr,"IONEX");
	else if (options->ionoModel == FPPPIonoModel) strcpy(auxstr,"FPPP");
	else if (options->ionoModel == SBASIonoModel) strcpy(auxstr,"SBAS");
	fprintf(options->outFileStream,"INFO MODELLING Ionosphere model: %s\n",auxstr);
	fprintf(options->outFileStream,"INFO MODELLING Troposphere model: %3s\n",options->troposphericCorrection?"ON":"OFF");
	if (options->troposphericCorrection  == 1) { 
		if (options->tropNominal == SimpleNominal) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Simple Nominal\n");
		else if (options->tropNominal == UNB3Nominal) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: UNB-3 Nominal\n");
		else if (options->tropNominal == TropoGalileo) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Galileo Nominal\n");
		if (options->tropMapping == SimpleMapping) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Simple Mapping\n");
		else if (options->tropMapping == NiellMapping) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Niell Mapping\n");
	}

	for(i=0;i<MAX_GNSS;i++) {
		constellationUsed[i]=0;
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==1) {
				constellationUsed[i]=1;
				break;
			}
		}
	}


	if (constellationUsed[GPS]==1) {
		if (options->GPSp1c1DCBModel == GPSp1c1NONE) strcpy(auxstr,"OFF");
		else if (options->GPSp1c1DCBModel == GPSp1c1FLEXIBLE) strcpy(auxstr,"Flexible");
		else if (options->GPSp1c1DCBModel == GPSp1c1STRICT) strcpy(auxstr,"Strict");
		fprintf(options->outFileStream,"INFO MODELLING GPS P1-C1 DCB model: %s\n",auxstr);

		if (options->FastPPP==0) {
			if (options->GPSp1p2DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSp1p2DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			else if (options->GPSp1p2DCBModel == DCBFILE) strcpy(auxstr,"P1-P2 DCB FILE");
			else if (options->GPSp1p2DCBModel == DCBIONEX) strcpy(auxstr,"IONEX");
			else if (options->GPSp1p2DCBModel == DCBFPPP) strcpy(auxstr,"FPPP");
		/*	else if (options->GPSp1p2DCBModel == DCBOSBdcbModel) { 
				if (options->OSBdcbModel==OSBNONE)  strcpy(auxstr,"OFF");
				else if (options->OSBdcbModel==OSBRINEX)  strcpy(auxstr,"RINEX");
				else if (options->OSBdcbModel==OSBSINEXBIAS)  strcpy(auxstr,"SINEX BIAS");
			}*/
			fprintf(options->outFileStream,"INFO MODELLING GPS P1-P2 DCB model: %s\n",auxstr);

			if (options->GPSISCl1caDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl1caDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L1C/A ISC DCB model: %s\n",auxstr);

			if (options->GPSISCl1cpDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl1cpDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L1Cp  ISC DCB model: %s\n",auxstr);

			if (options->GPSISCl1cdDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl1cdDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L1Cd  ISC DCB model: %s\n",auxstr);

			if (options->GPSISCl2cDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl2cDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L2C   ISC DCB model: %s\n",auxstr);

			if (options->GPSISCl5i5DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl5i5DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L5I5  ISC DCB model: %s\n",auxstr);

			if (options->GPSISCl5q5DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GPSISCl5q5DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING GPS L5Q5  ISC DCB model: %s\n",auxstr);
		}
	}
	
	if (options->FastPPP==0) {
		if (constellationUsed[Galileo]==1) {
			if (options->GALe1e5aDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GALe1e5aDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			else if (options->GALe1e5aDCBModel == DCBIONEX) strcpy(auxstr,"IONEX");
			fprintf(options->outFileStream,"INFO MODELLING Galileo E1-E5a (freq 1-5) DCB model: %s\n",auxstr);
			
			if (options->GALe1e5bDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GALe1e5bDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING Galileo E1-E5b (freq 1-7) DCB model: %s\n",auxstr);
		}
		
		if (constellationUsed[GLONASS]==1) {
			if (options->GLOp1p2DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->GLOp1p2DCBModel == DCBIONEX) strcpy(auxstr,"IONEX");
			fprintf(options->outFileStream,"INFO MODELLING GLONASS P1-P2 DCB model: %s\n",auxstr);
		}

		if (constellationUsed[BDS]==1) {
			if (options->BDSb1b6DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options-> BDSb1b6DCBModel== DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B1-B3   (freq 1-6) DCB model: %s\n",auxstr);
			
			if (options->BDSb2b6DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options-> BDSb2b6DCBModel== DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B1_2-B3 (freq 2-6) DCB model: %s\n",auxstr);
			
			if (options->BDSb5b6DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options-> BDSb5b6DCBModel== DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B2a-B3  (freq 5-6) DCB model: %s\n",auxstr);
			
			if (options->BDSb7b6DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options-> BDSb7b6DCBModel== DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B2b-B3  (freq 7-6) DCB model: %s\n",auxstr);
			
			if (options->BDSISCb1cdDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->BDSISCb1cdDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B1Cd ISC (freq 1) DCB model: %s\n",auxstr);
			
			if (options->BDSISCb2adDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->BDSISCb2adDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou B2ad ISC (freq 5) DCB model: %s\n",auxstr);
			
			if (options->BDSSP3DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->BDSSP3DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING BeiDou Single frequency precise orbits DCB model: %s\n",auxstr);
		}

		if (constellationUsed[QZSS]==1) {
			if (options->QZSc1cDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSc1cDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			else if (options->QZSc1cDCBModel == DCBRINEX) strcpy(auxstr,"IONEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L1C/A DCB model: %s\n",auxstr);
			
			if (options->QZSISCl1cpDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSISCl1cpDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L1Cp ISC DCB model: %s\n",auxstr);
			
			if (options->QZSISCl1cdDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSISCl1cdDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L1Cd ISC DCB model: %s\n",auxstr);
			
			if (options->QZSISCl2cDCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSISCl2cDCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L2C  ISC DCB model: %s\n",auxstr);
			
			if (options->QZSISCl5i5DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSISCl5i5DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L5I5 ISC DCB model: %s\n",auxstr);
			
			if (options->QZSISCl5q5DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->QZSISCl5q5DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING QZSS L5Q5 ISC DCB model: %s\n",auxstr);
		}

		if (constellationUsed[IRNSS]==1) {
			if (options->IRNc9c5DCBModel == DCBNONE) strcpy(auxstr,"OFF");
			else if (options->IRNc9c5DCBModel == DCBRINEX) strcpy(auxstr,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING IRNSS C9A-C5A DCB model: %s\n",auxstr);
		}

		for(i=0;i<MAX_GNSS;i++) {
			if (constellationUsed[i]==0) continue;
			sprintf(auxstr,"[%s]:",gnsstype2gnssname(i));
			if (options->DualFreqDCBModel[i] == DCBNONE) strcpy(auxstr2,"OFF");
			else if (options->DualFreqDCBModel[i] == DCBRINEX) strcpy(auxstr2,"RINEX");
			fprintf(options->outFileStream,"INFO MODELLING Compute Dual Frequency DCBs %-*s %s\n",maxLenghtConstName+3,auxstr,auxstr2);
		}	
	} else {
		if (options->FPPPDCBModel == DCBIONEX) strcpy(auxstr,"IONEX");
		fprintf(options->outFileStream,"INFO MODELLING Fast-PPP DCB model: %s\n",auxstr);
	}
	
/*	if (options->OSBdcbModel==OSBNONE)  strcpy(auxstr,"OFF");
	else if (options->OSBdcbModel==OSBRINEX)  strcpy(auxstr,"RINEX");
//SINEX BIAS still to be implemented
	else if (options->OSBdcbModel==OSBSINEXBIAS)  strcpy(auxstr,"SINEX BIAS");
	fprintf(options->outFileStream,"INFO MODELLING Measurement DCB model: %s\n",auxstr);
	if (options->DSBdcbModel==DSBNONE)  strcpy(auxstr,"OFF");
	else if (options->DSBdcbModel==DSBSINEXBIAS)  strcpy(auxstr,"SINEX BIAS");
	fprintf(options->outFileStream,"INFO MODELLING DCBs for measurement conversion: %s\n",auxstr);
*/	fprintf(options->outFileStream,"INFO MODELLING Wind up correction: %3s\n",options->windUpCorrection?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Solid tides correction: %3s\n",options->solidTidesCorrection?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Relativistic path range correction: %3s\n",options->gravitationalCorrection?"ON":"OFF");
	if (products->type == SP3) {
		fprintf(options->outFileStream,"INFO MODELLING Orbit interpolation degree: %2d\n",options->orbitInterpolationDegree);
		fprintf(options->outFileStream,"INFO MODELLING Clock interpolation degree: %2d\n",options->clockInterpolationDegree);
		if(options->OrbitsMaxGaps!=0) {
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps between orbit interpolation samples: %2d (%d seconds)\n",options->OrbitsMaxGaps,(int)options->OrbitsMaxDistance);
		} else {
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps between orbit interpolation samples: Unlimited\n");
		}
		if (options->OrbitsToTMaxGaps!=0) {
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all  orbit interpolation samples: %2d (%d seconds)\n",options->OrbitsToTMaxGaps,(int)options->OrbitsToTMaxDistance);
		} else {
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all  orbit interpolation samples: Unlimited\n");
		}
		if (options->clockInterpolationDegree!=0) {
			if (options->ClocksToTMaxGaps!=0) {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps between clock interpolation samples: %2d (%d seconds)\n",options->ClocksMaxGaps,(int)options->ClocksMaxDistance);
			} else {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps between clock interpolation samples: Unlimited\n");
			}
			if (options->ClocksToTMaxGaps!=0) {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all  clock interpolation samples: %2d (%d seconds)\n",options->ClocksToTMaxGaps,(int)options->ClocksToTMaxDistance);
			} else {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all  clock interpolation samples: Unlimited\n");
			}
		}
	}
	if (products->type == SP3 && tgdData->BRDC==NULL) {
		//No broadcast products for orbits and TGD
	} else {
		//Broadcast products
		if (products->type == SP3 && tgdData->BRDC!=NULL) {
			//Broadcast products for TGD only
			startPos=1;EndPos=1;
			strcpy(auxstr5,"for DCB data");
		} else if (products->BRDC==tgdData->BRDC) {
			startPos=0;EndPos=0;
			strcpy(auxstr4,"for orbits, clocks and DCB data");
		} else {
			startPos=0;EndPos=1;
			strcpy(auxstr4,"for orbits and clocks data");
			strcpy(auxstr5,"for DCB data");
		}
		for(l=startPos;l<=EndPos;l++) {
			if(l==0) {
				strcpy(auxstr3,auxstr4);
			} else {
				strcpy(auxstr3,auxstr5);
			}
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if(options->includeSatellite[i][j]==1) break;
				}
				if (j>listMaxSatGNSS[i]) continue;
				for(k=0;k<MAX_FREQUENCIES_PER_GNSS;k++) {
					if (availGNSSFreq[i][k]==1 && epoch->measOrder[i].availFreq[k]==1 && options->usableFreq[i][j][k]==1) {
						break;
					}
				}
				if (k==MAX_FREQUENCIES_PER_GNSS) continue;
				sprintf(auxstr,"[%s]:",gnsstype2gnssname(i));
				fprintf(options->outFileStream,"INFO MODELLING Broadcast message type order %s %-*s",auxstr3,maxLenghtConstName+3,auxstr);
				auxstr[0]='\0';
				len=0;
				for(k=0;k<options->BRDCAvailSelOrder[l][i][options->BrdcTypeSel[i]][MAX_BRDC_TYPES];k++) {
					len+=sprintf(&auxstr[len]," %s",BRDCType2String((enum GNSSystem)i,options->BRDCAvailSelOrder[l][i][options->BrdcTypeSel[i]][k]));
				}
				if (auxstr[0]=='\0') {
					fprintf(options->outFileStream," No navigation message available\n");
				} else {
					fprintf(options->outFileStream,"%s\n",auxstr);
				}
			}
		}
	}


	fprintf(options->outFileStream,"INFO MODELLING Check transmission time of navigation message is behind current epoch: %s\n",options->brdcBlockTransTime?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Use satellite 'SV Health' flag of navigation message: %s\n",BRDCHealthSel2String(options->satHealthMode));
	if (options->ModelAllMeas==1 && options->ForcedNoModelAllMeas==1) {
		if (options->SBAScorrections>=SBAS1Fused) {
			fprintf(options->outFileStream,"INFO MODELLING Model all RINEX observation file measurements: OFF (auto disabled due to processing in SBAS mode)\n");
		} else {
			fprintf(options->outFileStream,"INFO MODELLING Model all RINEX observation file measurements: OFF (auto disabled due to processing in DGNSS mode)\n");
		}
	} else {
		fprintf(options->outFileStream,"INFO MODELLING Model all RINEX observation file measurements: %3s\n",options->ModelAllMeas?"ON":"OFF");
	}
	if (options->MaxURABroadcast!=9999999.) {
		fprintf(options->outFileStream,"INFO MODELLING Maximum URA value of navigation message: %.1f\n",options->MaxURABroadcast);
	}
	if (options->DGNSS) {
		fprintf(options->outFileStream,"INFO MODELLING Sigma inflation during smoother convergence in DGNSS: %3s\n",options->sigmaInflation?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING Maximum age   for DGNSS corrections: %.6g\n",options->maxAgeDGNSS);
		fprintf(options->outFileStream,"INFO MODELLING Maximum value for DGNSS corrections: %.6g\n",options->maxDGNSSPRC);
	}

	if (options->SBAScorrections>=SBAS1Fused) {
		if (options->SBASmaritime==1) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS %s for Maritime enabled\n",options->SBAScorrections==SBAS1Fused?"1F":"DFMC");
		}
		fprintf(options->outFileStream,"INFO MODELLING SBAS Signal flight time: %.6g (seconds)\n",options->SBASmsgFlightTime);
		fprintf(options->outFileStream,"INFO MODELLING SBAS Navigation Mode: %3s\n",options->precisionapproach==PAMODE?"PA":"NPA");
		fprintf(options->outFileStream,"INFO MODELLING SBAS GEO switching: %3s\n",options->switchGEO==1?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING SBAS mode switching: %3s\n",options->switchmode==1?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING SBAS Ignore MT 0: %3s\n",options->usetype0messages==1?"OFF":"ON");
		if (options->SBAScorrections==SBAS1Fused) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT 0 as MT 2: %3s\n",options->useAlarmmessageForCorrections==1?"ON":"OFF");
			if (options->UDREIthreshold!=999999) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS UDREI threshold for discarding satellites: %d\n",options->UDREIthreshold);
			}
			if (options->switchmode==1 || options->UserForcedNPA==1 || options->NoMT10==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast correction sigma offset when MT10 is not used: %.6g (metres)\n",options->SigmaOffsetNoMT10);
			}
		} else {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT 0 as MT 34/35/36: %3s\n",options->useAlarmmessageForCorrections==1?"ON":"OFF");
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT37    using ED-259 version <=0.4: %3s\n",options->SBASDFMCMT37version!=MT37V1?"ON":"OFF");
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT39/40 using ED-259 version <=0.4: %3s\n",options->SBASDFMCMT3940version!=MT3940V1?"ON":"OFF");
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT42    using ED-259 version <=0.7: %3s\n",options->SBASDFMCMT42version!=MT42V1?"ON":"OFF");
			fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT47    using ED-259 version <=0.4: %3s\n",options->SBASDFMCMT47version!=MT47V1?"ON":"OFF");
		}
		fprintf(options->outFileStream,"INFO MODELLING SBAS GEO acquisiton time: %3d (seconds)\n",options->adquisitiontime);
		fprintf(options->outFileStream,"INFO MODELLING SBAS switching cooltime:  %3d (seconds)\n",options->minimumswitchtime);

		if (options->SBAScorrections==SBAS1Fused) {
			if (options->switchmode==1) {
				//Switch mode enabled. Show both timeouts
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications) timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][0],options->usertmout[0][0]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  1 (PRN Mask)                           timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][1],options->usertmout[0][1]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  6 (Integrity Info)                     timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][6],options->usertmout[0][6]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  7 (Fast Correction Degradation Factor) timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][7],options->usertmout[0][7]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  9 (GEO Navigation Message)             timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][9],options->usertmout[0][9]);
				if (options->NoMT10==1) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][10],options->usertmout[0][10]);
				}
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 12 (Network Time Parameters)            timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][12],options->usertmout[0][12]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 17 (GEO satellite Almanacs)             timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][17],options->usertmout[0][17]);
				if (options->ionoModel!=SBASIonoModel) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][18],options->usertmout[0][18]);
				}
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][25],options->usertmout[0][25]);
				if (options->ionoModel!=SBASIonoModel) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][26],options->usertmout[0][26]);
				}
				if (options->NoDeltaUDRE==1) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    Message disabled\n");
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][27],options->usertmout[0][27]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][28],options->usertmout[0][28]);
				}
			} else {
				if (options->precisionapproach==PAMODE) {
					//PA mode only
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications) timeout PA: %7d (seconds)\n",options->usertmout[1][0]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  1 (PRN Mask)                           timeout PA: %7d (seconds)\n",options->usertmout[1][1]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  6 (Integrity Info)                     timeout PA: %7d (seconds)\n",options->usertmout[1][6]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  7 (Fast Correction Degradation Factor) timeout PA: %7d (seconds)\n",options->usertmout[1][7]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  9 (GEO Navigation Message)             timeout PA: %7d (seconds)\n",options->usertmout[1][9]);
					if (options->NoMT10==1) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             timeout PA: %7d (seconds)\n",options->usertmout[1][10]);
					}
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 12 (Network Time Parameters)            timeout PA: %7d (seconds)\n",options->usertmout[1][12]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 17 (GEO satellite Almanacs)             timeout PA: %7d (seconds)\n",options->usertmout[1][17]);
					if (options->ionoModel!=SBASIonoModel) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout PA: %7d (seconds)\n",options->usertmout[1][18]);
					}
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout PA: %7d (seconds)\n",options->usertmout[1][25]);
					if (options->ionoModel!=SBASIonoModel) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      timeout PA: %7d (seconds)\n",options->usertmout[1][26]);
					}
					if (options->NoDeltaUDRE==1) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    Message disabled\n");
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    timeout PA: %7d (seconds)\n",options->usertmout[1][27]);
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  timeout PA: %7d (seconds)\n",options->usertmout[1][28]);
					}
				} else {
					//NPA mode only
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications) timeout NPA: %7d (seconds)\n",options->usertmout[0][0]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  1 (PRN Mask)                           timeout NPA: %7d (seconds)\n",options->usertmout[0][1]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  6 (Integrity Info)                     timeout NPA: %7d (seconds)\n",options->usertmout[0][6]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  7 (Fast Correction Degradation Factor) timeout NPA: %7d (seconds)\n",options->usertmout[0][7]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  9 (GEO Navigation Message)             timeout NPA: %7d (seconds)\n",options->usertmout[0][9]);
					if (options->NoMT10==1) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 10 (Degradation Parameters)             timeout NPA: %7d (seconds)\n",options->usertmout[0][10]);
					}
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 12 (Network Time Parameters)            timeout NPA: %7d (seconds)\n",options->usertmout[0][12]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 17 (GEO satellite Almanacs)             timeout NPA: %7d (seconds)\n",options->usertmout[0][17]);
					if (options->ionoModel!=SBASIonoModel) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout NPA: %7d (seconds)\n",options->usertmout[0][18]);
					}
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout NPA: %7d (seconds)\n",options->usertmout[0][25]);
					if (options->ionoModel!=SBASIonoModel) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 26 (Ionospheric Delay Corrections)      timeout NPA: %7d (seconds)\n",options->usertmout[0][26]);
					}
					if (options->NoDeltaUDRE==1) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    Message disabled\n");
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  Message disabled\n");
					} else {
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 27 (Service Message)                    timeout NPA: %7d (seconds)\n",options->usertmout[0][27]);
						fprintf(options->outFileStream,"INFO MODELLING SBAS MT 28 (Clock Ephemeris Covariance Matrix)  timeout NPA: %7d (seconds)\n",options->usertmout[0][28]);
					}
				}
			}
			if(options->FCtmout[1]!=-1 && options->FCtmout[0]==-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast corrections timeout PA: %3d (seconds)\n",options->FCtmout[1]);
			} else if (options->FCtmout[1]==-1 && options->FCtmout[0]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast corrections timeout NPA: %3d (seconds)\n",options->FCtmout[0]);
			} else if (options->FCtmout[1]!=-1 && options->FCtmout[0]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast corrections timeout PA: %3d NPA: %3d (seconds)\n",options->FCtmout[1],options->FCtmout[0]);
			}
			if(options->RRCtmout[1]!=-1 && options->RRCtmout[0]==-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS RRC  corrections timeout PA: %3d (seconds)\n",options->RRCtmout[1]);
			} else if (options->RRCtmout[1]==-1 && options->RRCtmout[0]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS RRC  corrections timeout NPA: %3d (seconds)\n",options->RRCtmout[0]);
			} else if (options->RRCtmout[1]!=-1 && options->RRCtmout[0]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS RRC  corrections timeout PA: %3d NPA: %3d (seconds)\n",options->RRCtmout[1],options->RRCtmout[0]);
			}
			if(options->NoFastCorrection == 1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast and RRC corrections set to 0\n");
			} else if (options->NoRRCCorrection==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS RRC corrections set to 0\n");
			}
			if(options->NoSlowCorrection==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS slow corrections set to 0\n");
			}
			if (options->NoIonoCorrection==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS ionosphere corrections set to 0\n");
			}
			if (options->NoFastDeg==1 && options->NoFastSigma==0) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Fast degradation term set to 0\n");
			}
			if (options->NoFastSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Sigma UDRE, Fast and RRC degradation terms set to 0\n");
			} else if (options->NoRRCSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS RRC degradation term set to 0\n");
			}
			if (options->NoSlowSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS slow degradation term set to 0\n");
			}
			if (options->NoEnRouteSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS En Route degradation term set to 0\n");
			}
			if (options->NoDeltaUDRE==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Delta UDRE set to 1\n");
			}
			if (options->NoIonoSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS ionosphere sigma set to 0\n");
			}
			if(options->NoTropoSigma==1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS troposphere sigma set to 0\n");
			}
		} else {
			//SBAS DFMC
			if (options->switchmode==1) {
				//Switch mode enabled. Show both timeouts
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications)                 timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][0],options->usertmout[0][0]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 31 (Satellite Mask)                                     timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][31],options->usertmout[0][31]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 34/35/36 (Integrity Messages)                           timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][34],options->usertmout[0][34]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 37 (OBAD parameters and DFREI scale table)              timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][37],options->usertmout[0][37]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 42 (GNSS Time Offsets)                                  timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][42],options->usertmout[0][42]);
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 47 (SBAS satellites almanacs)                           timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][47],options->usertmout[0][47]);
			} else {
				if (options->precisionapproach==PAMODE) {
					//PA mode only
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications)                 timeout PA: %7d (seconds)\n",options->usertmout[1][0]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 31 (Satellite Mask)                                     timeout PA: %7d (seconds)\n",options->usertmout[1][31]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 34/35/36 (Integrity Messages)                           timeout PA: %7d (seconds)\n",options->usertmout[1][34]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 37 (OBAD parameters and DFREI scale table)              timeout PA: %7d (seconds)\n",options->usertmout[1][37]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 42 (GNSS Time Offsets)                                  timeout PA: %7d (seconds)\n",options->usertmout[1][42]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 47 (SBAS satellites almanacs)                           timeout PA: %7d (seconds)\n",options->usertmout[1][47]);
				} else {
					//NPA mode only
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT  0 (Do not Use for Safety Applications)                 timeout NPA: %7d (seconds)\n",options->usertmout[0][0]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 31 (Satellite Mask)                                     timeout NPA: %7d (seconds)\n",options->usertmout[0][31]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 34/35/36 (Integrity Messages)                           timeout NPA: %7d (seconds)\n",options->usertmout[0][34]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 37 (OBAD parameters and DFREI scale table)              timeout NPA: %7d (seconds)\n",options->usertmout[0][37]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 42 (GNSS Time Offsets)                                  timeout NPA: %7d (seconds)\n",options->usertmout[0][42]);
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 47 (SBAS satellites almanacs)                           timeout NPA: %7d (seconds)\n",options->usertmout[0][47]);
				}
			}
			if (options->usertmout[1][32]!=-1 && options->usertmout[0][32]==-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 32 (Clock-Ephemeris corrections and covariance matrix)  timeout PA: %7d (seconds)\n",options->usertmout[1][32]);
			} else if (options->usertmout[1][32]==-1 && options->usertmout[0][32]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 32 (Clock-Ephemeris corrections and covariance matrix)  timeout NPA: %7d (seconds)\n",options->usertmout[0][32]);
			} else if (options->usertmout[1][32]!=-1 && options->usertmout[0][32]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 32 (Clock-Ephemeris corrections and covariance matrix)  timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][32],options->usertmout[0][32]);
			}

			if (options->usertmout[1][39]!=-1 && options->usertmout[0][39]==-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 39/40 (SBAS satellites ephemeris and covariance matrix) timeout PA: %7d (seconds)\n",options->usertmout[1][39]);
			} else if (options->usertmout[1][39]==-1 && options->usertmout[0][39]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 39/40 (SBAS satellites ephemeris and covariance matrix) timeout NPA: %7d (seconds)\n",options->usertmout[0][39]);
			} else if (options->usertmout[1][39]!=-1 && options->usertmout[0][39]!=-1) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 39/40 (SBAS satellites ephemeris and covariance matrix) timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][39],options->usertmout[0][39]);
			}


			if (options->SBASDFMCcer!=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 37 Cer: %.6g (metres)\n",options->SBASDFMCcer);
			}
			if (options->SBASDFMCccovariance!=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 37 Ccovariance: %.6g\n",options->SBASDFMCccovariance);
			}
			j=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (options->SBASDFMCicorr[i]!=-1.) {
					if(j==0) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 37 Icorr (seconds):      ");
						j++;
					}
					fprintf(options->outFileStream," %s: %.6g",gnsstype2gnssstr(i),options->SBASDFMCicorr[i]);
				}
			}
			if(j>0) {
				fprintf(options->outFileStream,"\n");
			}
			j=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (options->SBASDFMCccorr[i]!=-1.) {
					if(j==0) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 37 Ccorr (metres):       ");
						j++;
					}
					fprintf(options->outFileStream," %s: %.6g",gnsstype2gnssstr(i),options->SBASDFMCccorr[i]);
				}
			}
			if(j>0) {
				fprintf(options->outFileStream,"\n");
			}
			j=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (options->SBASDFMCrcorr[i]!=-1.) {
					if(j==0) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 37 Rcorr (metres/second):");
						j++;
					}
					fprintf(options->outFileStream," %s: %.6g",gnsstype2gnssstr(i),options->SBASDFMCrcorr[i]);
				}
			}
			if(j>0) {
				fprintf(options->outFileStream,"\n");
			}
			if (options->SBASDFMCdeltaRcorr!=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC MT 32 or MT39/40 DeltaRcorr: %.6g\n",options->SBASDFMCdeltaRcorr);
			}
			j=0;
			for(i=0;i<15;i++) {
				if (options->SBASDFMCdfreiTable[i]!=-1.) {
					if (j==0) {
						fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC User defined DFREIs:");
						j++;
					}
					fprintf(options->outFileStream," %d: %.6g",i,options->SBASDFMCdfreiTable[i]);
				}
			}
			if(j>0) {
				fprintf(options->outFileStream,"\n");
			}
			if (options->SBASDFMCdeltaDFRE!=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC DeltaDFRE: %.6g\n",options->SBASDFMCdeltaDFRE);
			}
			if (options->SBASDFMCsigmauire !=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC Sigma UIRE: %.6g (metres)\n",options->SBASDFMCsigmauire);
			}
			if (options->SBASDFMCsigmatropo !=-1.) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS DFMC Sigma troposphere: %.6g (metres)\n",options->SBASDFMCsigmatropo);
			}
		}

		if (options->switchmode==1) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Kh factor PA: %.6g NPA: %.6g\n",options->kfactor[PAMODE][KHORPOS],options->kfactor[NPAMODE][KHORPOS]);
			fprintf(options->outFileStream,"INFO MODELLING SBAS Kv factor PA: %.6g NPA: %.6g\n",options->kfactor[PAMODE][KVERPOS],options->kfactor[NPAMODE][KVERPOS]);
		} else {
		   if (options->precisionapproach==PAMODE) {
			   fprintf(options->outFileStream,"INFO MODELLING SBAS Kh factor PA: %.6g\n",options->kfactor[PAMODE][KHORPOS]);
			   fprintf(options->outFileStream,"INFO MODELLING SBAS Kv factor PA: %.6g\n",options->kfactor[PAMODE][KVERPOS]);
			} else {
			   fprintf(options->outFileStream,"INFO MODELLING SBAS Kh factor NPA: %.6g\n",options->kfactor[NPAMODE][KHORPOS]);
			   fprintf(options->outFileStream,"INFO MODELLING SBAS Kv factor NPA: %.6g\n",options->kfactor[NPAMODE][KVERPOS]);
		   }	   
		}
		if (options->airborneReceiverType==0) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver type: user defined\n");
		} else {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver type: %d\n",options->airborneReceiverType);
		}
		if (options->usersigmamultipath==1) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma multipath read from file\n");
		} else {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma noise:      %.6g (metres)\n",options->sigma2noise==-1?0.36:sqrt(options->sigma2noise));
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma divergence: %.6g (metres)\n",options->sigma2divergence==-1?0:sqrt(options->sigma2divergence));
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma multipath:  %.6g + %.6g*e^(-elev/%.6g) (metres)\n",options->sigma2multipath[0]==-99999.?0.13:options->sigma2multipath[0],options->sigma2multipath[1]==-99999.?0.53:options->sigma2multipath[1],1./options->sigma2multipath[2]);
			if (options->SBAScorrections==SBASDFMCused) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma multipath factor: %.6g\n",options->SBASDFMCsigmaMultipathFactor==-1.?2.59:options->SBASDFMCsigmaMultipathFactor);
			}
		}
	}

	////Print DGNSS modelling measurements
	if (options->DGNSS==1) {
		//Initialize checked measurements
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				for (k=0;k<MAX_CS_LIST;k++) {
					PositionChecked[i][j][k]=0;
				}
			}
		}

		//Initialize with first measurement available
		SelectedAMeas=0;
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
				for(k=0;k<options->numfilterMeasList[REFSTAPOS][i][j];k++) {
					prevValuesRefSta=NULL;		
					prevValuesRefSta=malloc(sizeof(int*));
					prevValuesRefSta[0]=NULL;
					prevValuesRefSta[0]=malloc(sizeof(int)*3);
					l=0;
					InitRangeList((enum GNSSystem)i,j,&List);
					prevValuesRefSta[l][0]=i;
					prevValuesRefSta[l][1]=j;
					prevValuesRefSta[l][2]=k;
					SelectedAMeas=1;
					PositionChecked[i][j][k]=1;
					break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}

		while(SelectedAMeas==1) {
			numOcurrences=0;
			for(i=prevValuesRefSta[l][0];i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) {
						//Satellite unselected. The current range ends
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if(j==1) {
								//PRN 1 of new constellation
								if (i==prevValuesRefSta[l][0]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								}
							} else {
								if (i==prevValuesRefSta[l][0] && j<=prevValuesRefSta[l][1]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
						continue;
					}
					for(k=0;k<options->numfilterMeasList[REFSTAPOS][i][j];k++) {
						MeasEqual=AreFilterMeasurementsEqual(1,REFSTAPOS,(enum GNSSystem)i,j,k,REFSTAPOS,(enum GNSSystem)prevValuesRefSta[l][0],prevValuesRefSta[l][1],prevValuesRefSta[l][2],options);
						if (MeasEqual==1) {
							//Each satellite will only have once a given measurement
							PositionChecked[i][j][k]=1;//Mark measurement as checked
							break;
						} else {
							continue;
							
						}
					} //End for(k=0;k<options->numfilterMeasList[REFSTAPOS][i][j];k++)
					if (k==options->numfilterMeasList[REFSTAPOS][i][j]||options->numfilterMeasList[REFSTAPOS][i][j]==0) {
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if (i==prevValuesRefSta[l][0] && j<=prevValuesRefSta[l][1]) {
								//This is a satellite prior to the first satellite with the current measurement
								//Do nothing
							} else {
								//The current satellite did not have the checked measurement
								if(j==1) {
									//PRN 1 of new constellation
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
					} else {
						numOcurrences++;
						if (i!=prevValuesRefSta[l][0] || j!=prevValuesRefSta[l][1]) {
							//The current satellite had the checked measurement
							//Check if previous satellite had it. If not, add a new range
							if (j==1) {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							} else {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							}
						}
					}
				} //End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
			} //End for(i=0;i<MAX_GNSS;i++) 
			//Initialize with next measurement
			if (numOcurrences==1) {
				List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
				List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
			}

			SelectedAMeas=0;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
					for(k=0;k<options->numfilterMeasList[REFSTAPOS][i][j];k++) {
						if (PositionChecked[i][j][k]==1) continue;
						AddRangeList((enum GNSSystem)i,j,&List);
						l=List.size-1;
						prevValuesRefSta=realloc(prevValuesRefSta,sizeof(int*)*List.size);
						prevValuesRefSta[l]=NULL;
						prevValuesRefSta[l]=malloc(sizeof(int)*3);
						prevValuesRefSta[l][0]=i;
						prevValuesRefSta[l][1]=j;
						prevValuesRefSta[l][2]=k;
						SelectedAMeas=1;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==0) break;
		} 

		//Save all the different blocks found
		strListGrouped=NULL;
		strMeas=NULL;
		strSmooth=NULL;
		strPrinted=NULL;
		strListGrouped=malloc(sizeof(char*)*List.size);
		strMeas=malloc(sizeof(char*)*List.size);
		strSmooth=malloc(sizeof(char*)*List.size);
		strPrinted=malloc(sizeof(int)*List.size);
		lenMeas=lenSmooth=lenListGrouped=0;	
		for(l=0;l<List.size;l++) {
			//Alloc memory for text saving
			strListGrouped[l]=NULL;
			strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strMeas[l]=NULL;
			strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strSmooth[l]=NULL;
			strSmooth[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strPrinted[l]=0;
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Save data for later grouping by filter measurement
			i=prevValuesRefSta[l][0];
			j=prevValuesRefSta[l][1];
			k=prevValuesRefSta[l][2];
			len=sprintf(auxstr2,"%s",meastype2measstr(options->filterMeasList[REFSTAPOS][i][j][k][0]));
			if (strcmp(auxstr2,"NAN")==0) {
				sprintf(auxstr2,"%s (frequency %d)",options->filterMeasKind[REFSTAPOS][i][j][k]==Pseudorange?"Pseudorange  ":"Carrier phase",options->filterMeasfreq[REFSTAPOS][i][j][k][0]);
			} else {
				if (options->filterListWithMeas[REFSTAPOS][i][j][k]==1) {
					if (options->numCombfilterMeas[REFSTAPOS][i][j][k]>1) {
						for(m=1;m<=options->numCombfilterMeas[REFSTAPOS][i][j][k];m++) {
							len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->filterMeasList[REFSTAPOS][i][j][k][m]));
						}
					}
				} else {
					if (options->filterMeasList[REFSTAPOS][i][j][k][0]>=IF12) {
						sprintf(auxstr2,"%s-Auto-%s",meastype2measstr(options->filterMeasList[REFSTAPOS][i][j][k][0]),options->filterMeasKind[REFSTAPOS][i][j][k]==Pseudorange?"Pseudorange":"Carrier phase");		
					} else {
						sprintf(auxstr2,"%s-Auto",meastype2measstr(options->filterMeasList[REFSTAPOS][i][j][k][0]));		
					}
				}
			}

			strcpy(strMeas[l],auxstr2);

			if (options->filterMeasSmoothed[REFSTAPOS][i][j][k]==1) {
				 len=sprintf(auxstr2,"%s",meastype2measstr(options->filterSmoothMeasList[REFSTAPOS][i][j][k][0]));
				 if (strcmp(auxstr2,"NAN")==0) {
					 sprintf(auxstr2,"Carrier phase (frequency %d)",options->filterSmoothMeasfreq[REFSTAPOS][i][j][k][0]);
				 } else {
					 if (options->filterSmoothListWithMeas[REFSTAPOS][i][j][k]==1) {
						 if (options->numCombfilterSmoothMeas[REFSTAPOS][i][j][k]>1) {
							 for(m=1;m<=options->numCombfilterSmoothMeas[REFSTAPOS][i][j][k];m++) {
								 len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->filterSmoothMeasList[REFSTAPOS][i][j][k][m]));
							 }
						 }
					 } else {
						 sprintf(auxstr2,"%s-Auto",meastype2measstr(options->filterSmoothMeasList[REFSTAPOS][i][j][k][0]));
					 }
				 }
				 sprintf(strSmooth[l],"Smooth: %s [n=%d]",auxstr2,options->smoothEpochs);
			} else {
				strSmooth[l][0]='\0';
			}
			strcpy(strListGrouped[l],auxstr);
			aux=(int)strlen(strMeas[l]);
			if (aux>lenMeas) lenMeas=aux;
			aux=(int)strlen(strSmooth[l]);
			if (aux>lenSmooth) lenSmooth=aux;
			aux=(int)strlen(strListGrouped[l]);
			if (aux>lenListGrouped) lenListGrouped=aux;
		}
		numPrinted=0;
		if (List.size==0) {
			if (options->workMode==wmDOPROCESSING) {
				sprintf(messagestr,"No measurement selected for correction in the reference station. Add more measurements%s%s",AnySatelliteUnselected==0?"":" or unexclude excluded satellites",AnyFrequencyUnselected==0?"":" or unexclude excluded frequencies");
				printError(messagestr,options);
			}
		} else {
			while(numPrinted<List.size) {
				for(l=0;l<List.size;l++) {
					if (strPrinted[l]==0) {
						refMeasPos=l;
						break;
					}
				}
				for(l=0;l<List.size;l++) {
					if (strPrinted[l]==1) continue;
					if (strcmp(strMeas[l],strMeas[refMeasPos])==0) {
						strPrinted[l]=1;
						numPrinted++;
						if (lenSmooth==0) {
							fprintf(options->outFileStream,"INFO MODELLING Reference Station Meas:%-*s %s\n",lenListGrouped,strListGrouped[l],strMeas[l]);
						} else {
							fprintf(options->outFileStream,"INFO MODELLING Reference Station Meas:%-*s %-*s %s\n",lenListGrouped,strListGrouped[l],lenMeas,strMeas[l],strSmooth[l]);
						}
					}
				}
			}
		}
		
		for(l=0;l<List.size;l++) {
			free(strMeas[l]);
			free(strSmooth[l]);
			free(strListGrouped[l]);
			free(prevValuesRefSta[l]);
		}
		free(strPrinted);
		free(strMeas);
		free(strSmooth);
		free(strListGrouped);
		free(prevValuesRefSta);
		freeRangeList(&List);
	}

	////Print Filter measurements
	printFilterMeas(options,NavMode);

	////Print SNR weight combinations
	//Initialize checked measurements
	for(i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			for (k=0;k<MAX_CS_LIST;k++) {
				PositionChecked[i][j][k]=0;
			}
		}
	}

	//Initialize with first measurement available
	SelectedAMeas=0;
	SNRCombinationsAvail=0;
	for(i=0;i<MAX_GNSS;i++) {
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
			for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
				if (options->weightMode[i][j][k]!=SNRWeight && options->weightMode[i][j][k]!=SNRElevWeight &&
					options->weightMode[i][j][k]!=SBASSNRWeight && options->weightMode[i][j][k]!=SBASSNRElevWeight &&
					options->weightMode[i][j][k]!=DGNSSSNRWeight && options->weightMode[i][j][k]!=DGNSSSNRElevWeight) continue; //Not an SNR weight
				l=0;
				InitRangeList((enum GNSSystem)i,j,&List);
				prevValuesSNRComb=NULL;
				prevValuesSNRComb=malloc(sizeof(double*));
				prevValuesSNRComb[0]=NULL;
				prevValuesSNRComb[0]=malloc(sizeof(double)*8);
				//Initialize previous values with the data of the first satellite to be read
				prevValuesSNRComb[l][0]=(double)options->SNRweightComb[i][j][k];
				prevValuesSNRComb[l][1]=options->SNRweightCombVal[i][j][k][0];
				prevValuesSNRComb[l][2]=options->SNRweightCombVal[i][j][k][1];
				prevValuesSNRComb[l][3]=options->SNRweightCombVal[i][j][k][2];
				prevValuesSNRComb[l][4]=options->SNRweightCombVal[i][j][k][3];
				prevValuesSNRComb[l][5]=(double)i;
				prevValuesSNRComb[l][6]=(double)j;
				prevValuesSNRComb[l][7]=(double)k;
				
				SelectedAMeas=1;
				SNRCombinationsAvail=1;
				PositionChecked[i][j][k]=1;
				break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==1) break;
	}

	while(SelectedAMeas==1) {
		numOcurrences=0;
		for(i=(int)prevValuesSNRComb[l][5];i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) { 
					//Satellite unselected or not an SNR weight. The current range ends
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if(j==1) {
							//PRN 1 of new constellation
							if (i==(int)prevValuesSNRComb[l][5]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							}
						} else {
							if (i==(int)prevValuesSNRComb[l][5] && j<=(int)prevValuesSNRComb[l][6]) {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
					continue;
				}
				for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
					if (options->weightMode[i][j][k]!=SNRWeight && options->weightMode[i][j][k]!=SNRElevWeight &&
					 options->weightMode[i][j][k]!=SBASSNRWeight && options->weightMode[i][j][k]!=SBASSNRElevWeight &&
					 options->weightMode[i][j][k]!=DGNSSSNRWeight && options->weightMode[i][j][k]!=DGNSSSNRElevWeight) continue;
					MeasEqual=AreFilterMeasurementsEqual(0,ROVERPOS,(enum GNSSystem)i,j,k,ROVERPOS,(enum GNSSystem)prevValuesSNRComb[l][5],(int)prevValuesSNRComb[l][6],(int)prevValuesSNRComb[l][7],options);
					if (MeasEqual==1) {
						//Check if any value is different than the last values read
						if ((double)(options->SNRweightComb[i][j][k])!=prevValuesSNRComb[l][0] || options->SNRweightCombVal[i][j][k][0]!=prevValuesSNRComb[l][1] ||
								options->SNRweightCombVal[i][j][k][1]!=prevValuesSNRComb[l][2] || options->SNRweightCombVal[i][j][k][2]!=prevValuesSNRComb[l][3] ||
								options->SNRweightCombVal[i][j][k][3]!=prevValuesSNRComb[l][4]) {
							continue;
						} else {
							//Each satellite will only have once a given measurement
							PositionChecked[i][j][k]=1;//Mark measurement as checked
							break;
						}
						
					}
				} //End for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++)
				if (k==options->numfilterMeasList[ROVERPOS][i][j]||options->numfilterMeasList[ROVERPOS][i][j]==0) {
					if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
						if (i==(int)prevValuesSNRComb[l][5] && j<=(int)prevValuesSNRComb[l][6]) {
							//This is a satellite prior to the first satellite with the current measurement
							//Do nothing
						} else {
							//The current satellite did not have the checked measurement
							if(j==1) {
								//PRN 1 of new constellation
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
							} else {
								List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
								List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
							}
						}
					}
				} else {
					numOcurrences++;
					if (i!=(int)(prevValuesSNRComb[l][5]) || j!=(int)(prevValuesSNRComb[l][6])) {
						//The current satellite had the checked measurement
						//Check if previous satellite had it. If not, add a new range
						if (j==1) {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							}
						} else {
							if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1) ) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
								ExtendRangeList((enum GNSSystem)i,j,l,&List);
							} 
						}
					}
				}
			} //End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
		} //End for(i=0;i<MAX_GNSS;i++) 
		//Initialize with next measurement
		if (numOcurrences==1) {
			List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
			List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
		}

		SelectedAMeas=0;
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
				for(k=0;k<options->numfilterMeasList[ROVERPOS][i][j];k++) {
					if (PositionChecked[i][j][k]==1) continue;
					if (options->weightMode[i][j][k]!=SNRWeight && options->weightMode[i][j][k]!=SNRElevWeight &&
						options->weightMode[i][j][k]!=SBASSNRWeight && options->weightMode[i][j][k]!=SBASSNRElevWeight &&
						options->weightMode[i][j][k]!=DGNSSSNRWeight && options->weightMode[i][j][k]!=DGNSSSNRElevWeight) continue; //Not an SNR weight
					AddRangeList((enum GNSSystem)i,j,&List);
					l=List.size-1;
					prevValuesSNRComb=realloc(prevValuesSNRComb,sizeof(double*)*List.size);
					prevValuesSNRComb[l]=NULL;
					prevValuesSNRComb[l]=malloc(sizeof(double)*8);
					prevValuesSNRComb[l][0]=(double)options->SNRweightComb[i][j][k];
					prevValuesSNRComb[l][1]=options->SNRweightCombVal[i][j][k][0];
					prevValuesSNRComb[l][2]=options->SNRweightCombVal[i][j][k][1];
					prevValuesSNRComb[l][3]=options->SNRweightCombVal[i][j][k][2];
					prevValuesSNRComb[l][4]=options->SNRweightCombVal[i][j][k][3];
					prevValuesSNRComb[l][5]=(double)i;
					prevValuesSNRComb[l][6]=(double)j;
					prevValuesSNRComb[l][7]=(double)k;
					SelectedAMeas=1;
					PositionChecked[i][j][k]=1;
					break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}
		if (SelectedAMeas==0) break;
	}

	if (SNRCombinationsAvail==1) {
		//Save all the different blocks found
		strListGrouped=NULL;
		strMeas=NULL;
		strPrinted=NULL;
		strListGrouped=malloc(sizeof(char*)*List.size);
		strMeas=malloc(sizeof(char*)*List.size);
		strPrinted=malloc(sizeof(int)*List.size);
		lenMeas=lenListGrouped=0;	
		for(l=0;l<List.size;l++) {
			//Alloc memory for text saving
			strListGrouped[l]=NULL;
			strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strMeas[l]=NULL;
			strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strPrinted[l]=0;
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Save data for later grouping by filter measurement
			i=(int)prevValuesSNRComb[l][5];
			j=(int)prevValuesSNRComb[l][6];
			k=(int)prevValuesSNRComb[l][7];
			len=sprintf(auxstr2,"%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]));
			if (strcmp(auxstr2,"NAN")==0) {
				sprintf(auxstr2,"%s (frequency %d)",options->filterMeasKind[ROVERPOS][i][j][k]==Pseudorange?"Pseudorange":"Carrier phase",options->filterMeasfreq[ROVERPOS][i][j][k][0]);
			} else {
				if (options->filterListWithMeas[ROVERPOS][i][j][k]==1) {
					if (options->numCombfilterMeas[ROVERPOS][i][j][k]>1) {
						for(m=1;m<=options->numCombfilterMeas[ROVERPOS][i][j][k];m++) {
							len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][m]));
						}
					}
				} else {
					if (options->filterMeasList[ROVERPOS][i][j][k][0]>=IF12) {
						sprintf(auxstr2,"%s-%s",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]),options->filterMeasKind[ROVERPOS][i][j][k]==Pseudorange?"Pseudorange":"Carrier phase");		
					} else {
						sprintf(auxstr2,"%s-Auto",meastype2measstr(options->filterMeasList[ROVERPOS][i][j][k][0]));		
					}
				}
			}

			sprintf(strMeas[l],"%s",auxstr2);
			sprintf(strListGrouped[l],"%s",auxstr);
			aux=(int)strlen(strMeas[l]);
			if (aux>lenMeas) lenMeas=aux;
			aux=(int)strlen(strListGrouped[l]);
			if (aux>lenListGrouped) lenListGrouped=aux;
		}
		numPrinted=0;
		while(numPrinted<List.size) {
			for(l=0;l<List.size;l++) {
				if (strPrinted[l]==0) {
					refMeasPos=l;
					break;
				}
			}
			for(l=0;l<List.size;l++) {
				if (strPrinted[l]==1) continue;
				if (strcmp(strMeas[l],strMeas[refMeasPos])==0) {
					strPrinted[l]=1;
					numPrinted++;
					fprintf(options->outFileStream,"INFO FILTER SNR selection for combination %-*s %-*s: %s\n",lenMeas,strMeas[l],lenListGrouped,strListGrouped[l],SNRCombModeNum2String((int)prevValuesSNRComb[l][0],options->filterMeasList[ROVERPOS][(int)prevValuesSNRComb[l][5]][(int)prevValuesSNRComb[l][6]][(int)prevValuesSNRComb[l][7]][0],prevValuesSNRComb[l][1],prevValuesSNRComb[l][2],prevValuesSNRComb[l][3],prevValuesSNRComb[l][4]));
				}
			}
		}
		
		for(l=0;l<List.size;l++) {
			free(strMeas[l]);
			free(strListGrouped[l]);
			free(prevValuesSNRComb[l]);
		}
		free(strPrinted);
		free(strMeas);
		free(strListGrouped);
		free(prevValuesSNRComb);
		freeRangeList(&List);
	}

	////Print Doppler measurements
	if (options->computeVelocity==1) {
		//Initialize checked measurements
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				for (k=0;k<MAX_CS_LIST;k++) {
					PositionChecked[i][j][k]=0;
				}
			}
		}

		//Initialize with first measurement available
		SelectedAMeas=0;
		for(i=0;i<MAX_GNSS;i++) {
			for(j=1;j<=listMaxSatGNSS[i];j++) {
				if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
				for(k=0;k<options->numDopplerMeasList[ROVERPOS][i][j];k++) {
					prevValuesRefSta=NULL;		
					prevValuesRefSta=malloc(sizeof(int*));
					prevValuesRefSta[0]=NULL;
					prevValuesRefSta[0]=malloc(sizeof(int)*3);
					l=0;
					InitRangeList((enum GNSSystem)i,j,&List);
					prevValuesRefSta[l][0]=i;
					prevValuesRefSta[l][1]=j;
					prevValuesRefSta[l][2]=k;
					SelectedAMeas=1;
					PositionChecked[i][j][k]=1;
					break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==1) break;
		}

		while(SelectedAMeas==1) {
			numOcurrences=0;
			for(i=prevValuesRefSta[l][0];i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) {
						//Satellite unselected. The current range ends
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if(j==1) {
								//PRN 1 of new constellation
								if (i==prevValuesRefSta[l][0]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								}
							} else {
								if (i==prevValuesRefSta[l][0] && j<=prevValuesRefSta[l][1]) {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
						continue;
					}
					for(k=0;k<options->numDopplerMeasList[ROVERPOS][i][j];k++) {
						MeasEqual=AreDopplerMeasurementsEqual(ROVERPOS,(enum GNSSystem)i,j,k,ROVERPOS,(enum GNSSystem)prevValuesRefSta[l][0],prevValuesRefSta[l][1],prevValuesRefSta[l][2],options);
						if (MeasEqual==1) {
							//Each satellite will only have once a given measurement
							PositionChecked[i][j][k]=1;//Mark measurement as checked
							break;
						} else {
							continue;
							
						}
					} //End for(k=0;k<options->numDopplerMeasList[ROVERPOS][i][j];k++)
					if (k==options->numDopplerMeasList[ROVERPOS][i][j]||options->numDopplerMeasList[ROVERPOS][i][j]==0) {
						if (List.listSatPRN[l][List.numJumpslist[l]-1][1]==999) {
							if (i==prevValuesRefSta[l][0] && j<=prevValuesRefSta[l][1]) {
								//This is a satellite prior to the first satellite with the current measurement
								//Do nothing
							} else {
								//The current satellite did not have the checked measurement
								if(j==1) {
									//PRN 1 of new constellation
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
								} else {
									List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
									List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
								}
							}
						}
					} else {
						numOcurrences++;
						if (i!=prevValuesRefSta[l][0] || j!=prevValuesRefSta[l][1]) {
							//The current satellite had the checked measurement
							//Check if previous satellite had it. If not, add a new range
							if (j==1) {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=listMaxSatGNSS[i-1]) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							} else {
								if ((List.listSatGNSS[l][List.numJumpslist[l]-1][1]!=(i-1) || List.listSatPRN[l][List.numJumpslist[l]-1][1]!=(j-1)) && List.listSatPRN[l][List.numJumpslist[l]-1][1]!=999) {
									ExtendRangeList((enum GNSSystem)i,j,l,&List);
								} 
							}
						}
					}
				} //End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
			} //End for(i=0;i<MAX_GNSS;i++) 
			//Initialize with next measurement
			if (numOcurrences==1) {
				List.listSatGNSS[l][List.numJumpslist[l]-1][1]=List.listSatGNSS[l][List.numJumpslist[l]-1][0];
				List.listSatPRN[l][List.numJumpslist[l]-1][1]=List.listSatPRN[l][List.numJumpslist[l]-1][0];
			}

			SelectedAMeas=0;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=1;j<=listMaxSatGNSS[i];j++) {
					if (options->includeSatellite[i][j]==0) continue; //Satellite unselected
					for(k=0;k<options->numDopplerMeasList[ROVERPOS][i][j];k++) {
						if (PositionChecked[i][j][k]==1) continue;
						AddRangeList((enum GNSSystem)i,j,&List);
						l=List.size-1;
						prevValuesRefSta=realloc(prevValuesRefSta,sizeof(int*)*List.size);
						prevValuesRefSta[l]=NULL;
						prevValuesRefSta[l]=malloc(sizeof(int)*3);
						prevValuesRefSta[l][0]=i;
						prevValuesRefSta[l][1]=j;
						prevValuesRefSta[l][2]=k;
						SelectedAMeas=1;
						PositionChecked[i][j][k]=1;
						break;
					}
					if (SelectedAMeas==1) break;
				}
				if (SelectedAMeas==1) break;
			}
			if (SelectedAMeas==0) break;
		} 

		//Save all the different blocks found
		strListGrouped=NULL;
		strMeas=NULL;
		strPrinted=NULL;
		strListGrouped=malloc(sizeof(char*)*List.size);
		strMeas=malloc(sizeof(char*)*List.size);
		strPrinted=malloc(sizeof(int)*List.size);
		lenMeas=lenSmooth=lenListGrouped=0;	
		for(l=0;l<List.size;l++) {
			//Alloc memory for text saving
			strListGrouped[l]=NULL;
			strListGrouped[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strMeas[l]=NULL;
			strMeas[l]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strPrinted[l]=0;
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Save data for later grouping by Doppler measurement
			i=prevValuesRefSta[l][0];
			j=prevValuesRefSta[l][1];
			k=prevValuesRefSta[l][2];
			len=sprintf(auxstr2,"%s",meastype2measstr(options->DopplerMeasList[ROVERPOS][i][j][k][0]));
			if (strcmp(auxstr2,"NAN")==0) {
				sprintf(auxstr2,"Doppler (frequency %d)",options->DopplerMeasfreq[ROVERPOS][i][j][k][0]);
			} else {
				if (options->DopplerListWithMeas[ROVERPOS][i][j][k]==1) {
					if (options->numCombDopplerMeas[ROVERPOS][i][j][k]>1) {
						for(m=1;m<=options->numCombDopplerMeas[ROVERPOS][i][j][k];m++) {
							len+=sprintf(&auxstr2[len],"-%s",meastype2measstr(options->DopplerMeasList[ROVERPOS][i][j][k][m]));
						}
					}
				} else {
					sprintf(auxstr2,"%s-Auto",meastype2measstr(options->DopplerMeasList[ROVERPOS][i][j][k][0]));		
				}
			}

			strcpy(strMeas[l],auxstr2);

			strcpy(strListGrouped[l],auxstr);
			aux=(int)strlen(strMeas[l]);
			if (aux>lenMeas) lenMeas=aux;
			aux=(int)strlen(strListGrouped[l]);
			if (aux>lenListGrouped) lenListGrouped=aux;
		}
		numPrinted=0;
		if (List.size==0) {
			if (options->workMode==wmDOPROCESSING) {
				sprintf(messagestr,"No measurement selected for Doppler for the rover. Add more measurements%s%s",AnySatelliteUnselected==0?"":" or unexclude excluded satellites",AnyFrequencyUnselected==0?"":" or unexclude excluded frequencies");
				printError(messagestr,options);
			}
		} else {
			while(numPrinted<List.size) {
				for(l=0;l<List.size;l++) {
					if (strPrinted[l]==0) {
						refMeasPos=l;
						break;
					}
				}
				for(l=0;l<List.size;l++) {
					if (strPrinted[l]==1) continue;
					if (strcmp(strMeas[l],strMeas[refMeasPos])==0) {
						strPrinted[l]=1;
						numPrinted++;
						fprintf(options->outFileStream,"INFO Doppler Rover Meas:%-*s %s\n",lenListGrouped,strListGrouped[l],strMeas[l]);
					}
				}
			}
		}
		
		for(l=0;l<List.size;l++) {
			free(strMeas[l]);
			free(strListGrouped[l]);
			free(prevValuesRefSta[l]);
		}
		free(strPrinted);
		free(strMeas);
		free(strListGrouped);
		free(prevValuesRefSta);
		freeRangeList(&List);
	}

	fprintf(options->outFileStream,"INFO FILTER Number of epochs of continuous code smoothing before steady-state operation%s: %d\n",options->DGNSS?" in rover":"",options->excludeSmoothingConvergence);
	if (options->DGNSS) {
		fprintf(options->outFileStream,"INFO FILTER Number of epochs of continuous code smoothing before steady-state operation in reference station: %d\n",options->excludeSmoothingConvergenceDGNSS);
	}
	if (options->stepdetector == 1) {
		fprintf(options->outFileStream,"INFO FILTER Step detector for jumps in navigation message enabled\n");
	}
	if (options->prefitOutlierDetectorAbs == 1) {
		fprintf(options->outFileStream,"INFO FILTER Absolute value prefit outlier detector threshold: %.2f (metres)\n",options->prefitOutlierDetectorAbsThreshold);
	}
	if (options->prefitOutlierDetectorMedian == 1) {
		fprintf(options->outFileStream,"INFO FILTER Median prefit outlier detector threshold: %.2f (metres)\n",options->prefitOutlierDetectorMedianThreshold);
	}
	if(options->HDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO FILTER HDOP Threshold for skipping epoch: %.2f\n",options->maxHDOP);
	} else {
		fprintf(options->outFileStream,"INFO FILTER HDOP Filter: OFF\n");
	}
	if(options->PDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO FILTER PDOP Threshold for skipping epoch: %.2f\n",options->maxPDOP);
	} else {
		fprintf(options->outFileStream,"INFO FILTER PDOP Filter: OFF\n");
	}
	if (options->GDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO FILTER GDOP Threshold for skipping epoch: %.2f\n",options->maxGDOP);
	} else {
		fprintf(options->outFileStream,"INFO FILTER GDOP Filter: OFF\n");
	}
	if(options->HDOPorPDOP == 1) {
		fprintf(options->outFileStream,"INFO FILTER HDOP and PDOP filters are ORed (i.e. only one of the conditions have to be met)\n");
	}
	fprintf(options->outFileStream,"INFO FILTER Carrierphase is used: %3s\n",options->usePhase?"YES":"NO");
	if (options->usePhase) {
		fprintf(options->outFileStream,"INFO FILTER Estimate carrier phase ambiguities: %3s\n",options->estimateAmbiguities?"ON":"OFF");
	}
	fprintf(options->outFileStream,"INFO FILTER Estimate troposphere: %3s\n",options->estimateTroposphere?"ON":"OFF");
	fprintf(options->outFileStream,"INFO FILTER %s Processing\n",(options->filterIterations==1)?"Forward Only":"Forward and Backward"); 

	aux=0;
	for (i=0;i<MAX_PAR;i++) {
		aux2=sprintf(auxstr,"%.6g",options->filterParams[0][i]);
		if (aux2>aux) {
			aux=aux2;
		}
	}
	if ((options->estimateIono==1 && options->IonoRandWalk==1) || (options->estimateSatDCB==1 && options->SatDCBRandWalk==1) || (options->estimateRecDCB==1 && options->RecDCBRandWalk==1) ) {
		aux2=10;
	} else if (options->estimateIono==1 || options->estimateSatDCB==1 || options->estimateRecDCB==1) {
		aux2=8;
	} else if ((options->ClkRandWalk==1 || options->ISCBRandWalk==1) && options->ClktimeFactor!=1.) {
		aux2=8;
	} else if (options->CoordRandWalk==1 || options->ClkRandWalk==1 || options->ISCBRandWalk==1 || options->estimateRecWindUp==1 || options->estimateTroposphere==1) {
		aux2=7;
	} else {
		aux2=5;
	}
	if (options->estimateIono==1 || options->estimateSatDCB==1 || options->estimateRecDCB==1) {
		aux3=8;
	} else if (options->ClktimeFactor!=1.) {
		aux3=6;
	} else {
		aux3=5;
	}
	for (i=0;i<MAX_PAR;i++) {
		auxstr4[0]='\0';
		auxd=1.;
		auxd2=1.;
		switch(i) {
			case DR_UNK: 
				strcpy (auxstr,"Position:");
				if (options->CoordRandWalk==1) {
					strcpy(auxstr2,"(m^2/s)");
					strcpy(auxstr4," [Random walk]");
				} else {
					strcpy(auxstr2,"(m^2)");
				}
				strcpy(auxstr3,"(m^2)");
				break;
			case DT_UNK:
				strcpy (auxstr,"Clock:");
				if (options->ClkRandWalk==1) {
					auxd=86400.;
					if (options->ClktimeFactor!=1.) {
						strcpy(auxstr2,"(ns^2/d)");
					} else {
						strcpy(auxstr2,"(m^2/d)");
					}
					strcpy(auxstr4," [Random walk]");
				} else {
					if (options->ClktimeFactor!=1.) {
						strcpy(auxstr2,"(ns^2)");
					} else {
						strcpy(auxstr2,"(m^2)");
					}
				}
				if (options->ClktimeFactor!=1.) {
					strcpy(auxstr3,"(ns^2)");
					auxd*=1E9*1E9/(c0*c0);
					auxd2=1E9*1E9/(c0*c0);
				} else {
					strcpy(auxstr3,"(m^2)");
				}
				break;
			case DT_IS_UNK:
				strcpy (auxstr,"Inter-System Clocks:");
				if (options->ISCBRandWalk==1) {
					auxd=86400.;
					if (options->ClktimeFactor!=1.) {
						strcpy(auxstr2,"(ns^2/d)");
					} else {
						strcpy(auxstr2,"(m^2/d)");
					}
					strcpy(auxstr4," [Random walk]");
				} else {
					if (options->ClktimeFactor!=1.) {
						strcpy(auxstr2,"(ns^2)");
					} else {
						strcpy(auxstr2,"(m^2)");
					}
				}
				if (options->ClktimeFactor!=1.) {
					strcpy(auxstr3,"(ns^2)");
					auxd*=1E9*1E9/(c0*c0);
					auxd2=1E9*1E9/(c0*c0);
				} else {
					strcpy(auxstr3,"(m^2)");
				}
				break;
			case TROP_UNK:
				if (options->estimateTroposphere==0) continue;
				strcpy(auxstr,"Troposphere:");
				strcpy(auxstr2,"(m^2/h)");
				strcpy(auxstr3,"(m^2)");
				strcpy(auxstr4," [Random walk]");
				auxd=3600.;
				break;
			case BIAS_UNK:
				if (options->usePhase==0||options->estimateAmbiguities==0) continue;
				strcpy(auxstr,"Ambiguity:");
				strcpy(auxstr2,"(m^2)");
				strcpy(auxstr3,"(m^2)");
				break;
			case GLOIFB_UNK:
				if (options->estimateGLOIFB==0) continue;
				strcpy(auxstr,"GLONASS IFB:");
				strcpy(auxstr2,"(m^2)");
				strcpy(auxstr3,"(m^2)");
				break;
			case WUP_UNK:
				if (options->estimateRecWindUp==0) continue;
				strcpy(auxstr,"Receiver Wind-Up:");
				strcpy(auxstr2,"(m^2/s)");
				strcpy(auxstr3,"(m^2)");
				strcpy(auxstr4," [Random walk]");
				break;
			default:
				continue;
				break;
		}
		fprintf(options->outFileStream,"INFO FILTER Parameters [Phi,Q,P0] %-20s",auxstr);
		sprintf(auxstr,"%.6g",options->filterParams[0][i]);
		fprintf(options->outFileStream," %*s",aux,auxstr);
		fprintf(options->outFileStream," %9.2e %*s",options->filterParams[1][i]*auxd,aux2,auxstr2);
		fprintf(options->outFileStream," %9.2e %*s%s\n",options->filterParams[2][i]*auxd2,aux3,auxstr3,auxstr4);
	}
	fprintf(options->outFileStream,"INFO FILTER Reference clock constellation priority list: %s",gnsstype2gnssname(options->ClkRefPriorityList[0]));
	for(i=1;i<options->numClkRefPriorityList;i++) {
		fprintf(options->outFileStream,", %s",gnsstype2gnssname(options->ClkRefPriorityList[i]));
	}
	fprintf(options->outFileStream,"\n");

	fprintf(options->outFileStream,"INFO FILTER Allow changing reference clock in solution computation: %s\n",options->AllowChangeReferenceGNSSClk==1?"ON":"OFF");

	//Inter-sytem clock bias source
	for(i=0;i<MAX_GNSS;i++) {
		constellationUsed[i]=0;
		for(j=1;j<=listMaxSatGNSS[i];j++) {
			if (options->includeSatellite[i][j]==1) {
				constellationUsed[i]=1;
				break;
			}
		}
	}
	numTotCombInterSystemClockBias=0;
	numEstimateCombInterSystemClockBias[MAX_GNSS]=0;
	numRINEXCombInterSystemClockBias[MAX_GNSS]=0;
	numUserCombInterSystemClockBias[MAX_GNSS]=0;
	for(i=0;i<MAX_GNSS;i++) {
		numEstimateCombInterSystemClockBias[i]=0;
		numRINEXCombInterSystemClockBias[i]=0;
		numUserCombInterSystemClockBias[i]=0;
		if (constellationUsed[i]==0) continue;
		for (j=0;j<MAX_GNSS;j++) {
			if (j==i) continue;
			if (constellationUsed[j]==0) continue;
			numTotCombInterSystemClockBias++;
			if (options->GNSSclockSource[i][j]==ClkSrcCalculate) {
				numEstimateCombInterSystemClockBias[MAX_GNSS]++;
				numEstimateCombInterSystemClockBias[i]++;
			} else if (options->GNSSclockSource[i][j]==ClkSrcUser) {
				numUserCombInterSystemClockBias[MAX_GNSS]++;
				numUserCombInterSystemClockBias[i]++;
			} else if (options->GNSSclockSource[i][j]==ClkSrcRINEX) {
				numRINEXCombInterSystemClockBias[MAX_GNSS]++;
				numRINEXCombInterSystemClockBias[i]++;
			}
		}
	}

	if (numEstimateCombInterSystemClockBias[MAX_GNSS]==numTotCombInterSystemClockBias) {
		fprintf(options->outFileStream,"INFO FILTER Inter-system clock bias source (All combinations): Estimate\n");
	} else if (numRINEXCombInterSystemClockBias[MAX_GNSS]==numTotCombInterSystemClockBias) {
		fprintf(options->outFileStream,"INFO FILTER Inter-system clock bias source (All combinations): RINEX\n");
	} else {
		for(i=0;i<MAX_GNSS;i++) {
			auxstr[0]='\0';
			auxstr2[0]='\0';
			auxstr3[0]='\0';
			aux=aux2=aux3=0;
			if (numEstimateCombInterSystemClockBias[i]==(MAX_GNSS-1)) {
				fprintf(options->outFileStream,"INFO FILTER Inter-system clock bias source for %-*s: Estimate for ",maxLenghtConstName,gnsstype2gnssname(i));
				for (j=0;j<MAX_GNSS;j++) {
					if (j==i) continue;
					aux+=sprintf(&auxstr[aux],"%3s/",gnsstype2gnssstr(j));
				}
				auxstr[aux-1]='\0';
				fprintf(options->outFileStream,"%s\n",auxstr);
			} else if (numRINEXCombInterSystemClockBias[i]==(MAX_GNSS-1)) {
				fprintf(options->outFileStream,"INFO FILTER Inter-system clock bias source for %-*s: RINEX for ",maxLenghtConstName,gnsstype2gnssname(i));
				for (j=0;j<MAX_GNSS;j++) {
					if (j==i) continue;
					aux+=sprintf(&auxstr[aux],"%3s/",gnsstype2gnssstr(j));
				}
				auxstr[aux-1]='\0';
				fprintf(options->outFileStream,"%s\n",auxstr);
			} else {
				for (j=0;j<MAX_GNSS;j++) {
					if (j==i) continue;
					if (options->GNSSclockSource[i][j]==ClkSrcCalculate) {
						aux+=sprintf(&auxstr[aux],"%3s/",gnsstype2gnssstr(j));
					} else if (options->GNSSclockSource[i][j]==ClkSrcRINEX) {
						aux2+=sprintf(&auxstr2[aux2],"%3s/",gnsstype2gnssstr(j));
					} else if (options->GNSSclockSource[i][j]==ClkSrcUser) {
						aux3+=sprintf(&auxstr3[aux3],"%3s: %.10g (m) ",gnsstype2gnssstr(j),options->GNSSclockValue[i][j]);
					}
				}
				fprintf(options->outFileStream,"INFO FILTER Inter-system clock bias source for %-*s: ",maxLenghtConstName,gnsstype2gnssname(i));
				if (aux>0) {
					auxstr[aux-1]='\0';
					fprintf(options->outFileStream,"Estimate %s",auxstr);
				}
				if (aux2>0) {
					auxstr2[aux2-1]='\0';
					fprintf(options->outFileStream,"%sRINEX %s",aux>0?" | ":"",auxstr2);
				}
				if (aux3>0) {
					auxstr3[aux3-1]='\0';
					fprintf(options->outFileStream,"%sUser-defined %s",(aux>0||aux2>0)?" | ":"",auxstr3);
				}
				fprintf(options->outFileStream,"\n");
			}
		}
	}

	if (options->SBAScorrections<=SBASionoOnly) {
		if ( options->FastPPP==1) {
			fprintf(options->outFileStream,"INFO FILTER Use ionosphere sigma:  ON\n");
		} else if ( options->ionoModel == IONEXIonoModel || options->ionoModel == FPPPIonoModel || options->ionoModel == SBASIonoModel) {
			fprintf(options->outFileStream,"INFO FILTER Use ionosphere sigma: %-3s\n",options->useSigmaIono?"ON":"OFF");
		}
	}	
	if ( options->stanfordesa == 1 ) {
		if ( options->stanfordesaMaxNumSat != 999999 ) {
			fprintf(options->outFileStream,"INFO FILTER Stanford-ESA Maximum number of satellites in combination to be processed: %d\n",options->stanfordesaMaxNumSat);
		}
		if ( options->stanfordesaLOI == 1 ) {
			fprintf(options->outFileStream,"INFO FILTER Stanford-ESA Horizontal Integrity Limit for writing data to file: %.3f\n",options->WIRHorThreshold);
			fprintf(options->outFileStream,"INFO FILTER Stanford-ESA Vertical   Integrity Limit for writing data to file: %.3f\n",options->WIRVerThreshold);
		}
		fprintf(options->outFileStream,"INFO OUTPUT File for Stanford-ESA plot: %s\n",stdesaFile);
		if ( options->stanfordesaLOI == 1 ) {
			fprintf(options->outFileStream,"INFO OUTPUT File for Stanford-ESA LOI values: %s\n",stdesaFileLOI);
		}
	}

	if (kmlFile[0]!='\0') {
		fprintf(options->outFileStream,"INFO OUTPUT File for KML: %s\n",kmlFile);
	}
	if (kml0File[0]!='\0') {
		fprintf(options->outFileStream,"INFO OUTPUT File for KML0: %s\n",kml0File);
	}
	if (kmlFile[0]!='\0' || kml0File[0]!='\0' ) {
		fprintf(options->outFileStream,"INFO OUTPUT KML EGM96 geoid model: %s\n",options->KMLEGM96height?"ON":"OFF");
		fprintf(options->outFileStream,"INFO OUTPUT KML Timestamps: %s\n",options->KMLTimeStamps?"ON":"OFF");
		if (options->KMLTimeStamps==1) {
			fprintf(options->outFileStream,"INFO OUTPUT KML Timestamp Decimation: %.1f\n",options->KMLTimeStampDec);
		}
		if (options->KMLTimeStamps==1) {
			for (i=0;i<options->numKMLTimeRanges;i++) {
				if (options->KMLtimeranges[i][1]==9999999999999.) {
					if (options->KMLtimeranges[i][2]==1.) {
						fprintf(options->outFileStream,"INFO OUTPUT KML Range #%d: From 'Start of file' to 'End of file'\n",i+1);
					} else {
						fprintf(options->outFileStream,"INFO OUTPUT KML Range #%d: From %.2f to 'End of file'\n",i+1,options->KMLtimeranges[i][0]);
					}
				} else {
					if (options->KMLtimeranges[i][2]==1.) {
						fprintf(options->outFileStream,"INFO OUTPUT KML Range #%d: From 'Start of file' to %.2f\n",i+1,options->KMLtimeranges[i][1]);
					} else {
						fprintf(options->outFileStream,"INFO OUTPUT KML Range #%d: From %.2f to %.2f\n",i+1,options->KMLtimeranges[i][0],options->KMLtimeranges[i][1]);
					}
				}
			}
		}
	}
	if (sp3File[0]!='\0') {
		fprintf(options->outFileStream,"INFO OUTPUT File for SP3: %s\n",sp3File);
		if (options->DGNSS) {
			fprintf(options->outFileStream,"INFO OUTPUT Write SPP solutions to SP3 file: %3s\n",options->WriteSPPsolInDGNSSmodeSP3?"YES":"NO");
		}
	}

	if (RefFile[0]!='\0') {
		fprintf(options->outFileStream,"INFO OUTPUT File for Reference Position: %s\n",RefFile);
		fprintf(options->outFileStream,"INFO OUTPUT Date format for Reference file: %s\n",options->GPSWeekRefFile?"GPSWeek/SoW":"Year/DoY/SoD");
		fprintf(options->outFileStream,"INFO OUTPUT Coordinate system for Reference file: %s\n",options->GeodeticCoordRefFile?"Geodetic WGS84 (Lon Lat Height)":"Cartesian WGS84 (X Y Z)");
		
		if (options->DGNSS) {
			fprintf(options->outFileStream,"INFO OUTPUT Write SPP solutions to Reference file: %3s\n",options->WriteSPPsolInDGNSSmodeRefFile?"YES":"NO");
		}

	}


	fprintf(options->outFileStream,"INFO OUTPUT Satellite Velocity:     %s\n",options->satVel==svINERTIAL?"Inertial":"ITRF");

	fprintf(options->outFileStream,"INFO PRINT INFO:            %-3s\n",options->printInfo?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT CS:              %-3s\n",options->printCycleslips?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SFCSDATA:        %-3s\n",options->printSFdata?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT MWCSDATA:        %-3s\n",options->printMWdata?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT LICSDATA:        %-3s\n",options->printLIdata?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT IGFCSDATA:       %-3s\n",options->printIGFdata?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT USERADDEDERROR:  %-3s\n",options->printUserError?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT INPUT:           %-3s\n",options->printInput?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT MEAS :           %-3s\n",options->printMeas?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT MODEL:           %-3s\n",options->printModel?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT EPOCHSAT:        %-3s\n",options->printSatellites?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SATSEL:          %-3s\n",options->printSatSel?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT PREFIT:          %-3s\n",options->printPrefit?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT POSTFIT:         %-3s\n",options->printPostfit?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT FILTER:          %-3s\n",options->printFilterSolution?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT OUTPUT:          %-3s\n",options->printOutput?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SATDIFF:         %-3s\n",options->printSatDiff?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SATSTAT:         %-3s\n",options->printSatStat?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SATSTATTOT:      %-3s\n",options->printSatStatTot?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASCORR:        %-3s\n",options->printSBASCORR?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASVAR:         %-3s\n",options->printSBASVAR?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASIONO:        %-3s\n",options->printSBASIONO?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASOUT:         %-3s\n",options->printSBASOUT?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASUNSEL:       %-3s\n",options->printSBASUNSEL?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASDFMCCORR:    %-3s\n",options->printSBASDFMCCORR?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASDFMCVAR:     %-3s\n",options->printSBASDFMCVAR?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASDFMCUNSEL:   %-3s\n",options->printSBASDFMCUNSEL?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SBASUNUSED:      %-3s\n",options->printSBASUNUSED?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT DGNSS:           %-3s\n",options->printDGNSS?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT DGNSSUNSED:      %-3s\n",options->printDGNSSUNUSED?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SUMMARY:         %-3s\n",options->printSummary?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT V5 Format:       %-3s\n",options->printV5format?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT Clock in ns:     %-3s\n",options->ClktimeFactor!=1.?"ON":"OFF");
}

/*****************************************************************************
 * Name        : printError
 * Description : Print an ERROR message and exit with code -1
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *message                  I  N/A  Message
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void printError (char *message, TOptions *options) {
	fprintf(options->outFileStream,"ERROR %s\n",message);
	#if !defined (__WIN32__)
		//Enable cursor and clean line
		if (printProgress==1 && options->ProgressEndCharac=='\r') {
			fprintf(options->terminalStream,"%70s\r\033[?25h","");
		}
	#endif
	exit(-1);
}
 
/*****************************************************************************
 * Name        : printInfo
 * Description : Print an INFO message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *message                  I  N/A  Message
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void printInfo (char *message, TOptions *options) {
	if (options->printInfo)
		fprintf(options->outFileStream,"INFO %s\n",message);
}

/*****************************************************************************
 * Name        : printInput
 * Description : Print the input data
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TTGDdata  *tgdData              I  N/A  Products for P1-C1 corrections, when applicable
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void printInput (TEpoch *epoch, TTGDdata *tgdData, TOptions *options) {
	int							i,j,k,l;
	int							res[10];
	int							retDCB,retDCBC1P1;
	double						measurements[10];
	double						correction1;
	const enum MeasurementType 	C1Ameas=C1A,C1Bmeas=C1B,C1Cmeas=C1C,C1Pmeas=C1P;
	const enum MeasurementType 	L1Ameas=L1A,L1Bmeas=L1B,L1Cmeas=L1C,L1Pmeas=L1P;
	const enum MeasurementType	C2Cmeas=C2C,C2Pmeas=C2P;
	const enum MeasurementType	L2Pmeas=L2P;
	const enum MeasurementType	C7Qmeas=C7Q;
	const enum MeasurementType	L7Qmeas=L7Q;
	const enum MeasurementType	C8Qmeas=C8Q;
	const enum MeasurementType	L8Qmeas=L8Q;
	const int				 	C1Afreq=1,C1Bfreq=1,C1Cfreq=1,C1Pfreq=1;
	const int				 	L1Afreq=1,L1Bfreq=1,L1Cfreq=1,L1Pfreq=1;
	const int					C2Cfreq=2,C2Pfreq=2;
	const int					L2Pfreq=2;
	const int					C7Qfreq=7;
	const int					L7Qfreq=7;
	const int					C8Qfreq=8;
	const int					L8Qfreq=8;
	
	if (options->printInput) {
		for (l=0;l<epoch->numSatellites;l++) {
			i=epoch->printIndex2satIndex[l];
			if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
			k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			if (options->printV5format==0) {
			fprintf(options->outFileStream,"INPUT     %29s %3s %2d %3d %6d",epoch->tSoDHourStr,gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,epoch->cycleslip.narc[k],epoch->cycleslip.arcLength[k]==0 ? 1:epoch->cycleslip.arcLength[k]);
			} else {
				fprintf(options->outFileStream,"INPUT     %17s %3s %2d %6d",epoch->tStr,gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,epoch->cycleslip.arcLength[k]==0 ? 1:epoch->cycleslip.arcLength[k]);
			}
			switch(epoch->sat[i].GNSS) {
				case GPS:
					res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Cmeas,&C1Cfreq,&measurements[0],NULL,0);
					res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Pmeas,&C1Pfreq,&measurements[1],NULL,0);
					res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C2Pmeas,&C2Pfreq,&measurements[2],NULL,0);
					res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L1Pmeas,&L1Pfreq,&measurements[3],NULL,0);
					res[4] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L2Pmeas,&L2Pfreq,&measurements[4],NULL,0);
					if (tgdData->GPSp1c1DCBModel == GPSp1c1STRICT) {
						getTGDfromDCB(tgdData, epoch, epoch->sat[i].GNSS, epoch->sat[i].PRN,&epoch->t, C1C, C1P, &correction1, &retDCB, &retDCBC1P1);
						if (retDCB==1) {
							if(epoch->receiver.recType==rtNOP1) {
								measurements[1]-=correction1;
							} else if (epoch->receiver.recType==rtCROSS){
								measurements[1]-=correction1;
								measurements[2]-=correction1;
							}
						}
					}
					for (j=0;j<5;j++) {
						if (measurements[j] ==-1 || res[j]<=0) measurements[j] = 0;
						fprintf(options->outFileStream," %14.4f",measurements[j]);
					}
					break;
				case Galileo:
					res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Ameas,&C1Afreq,&measurements[0],NULL,0);
					res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Bmeas,&C1Bfreq,&measurements[1],NULL,0);
					res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Cmeas,&C1Cfreq,&measurements[2],NULL,0);
					res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C7Qmeas,&C7Qfreq,&measurements[3],NULL,0);
					res[4] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C8Qmeas,&C8Qfreq,&measurements[4],NULL,0);
					res[5] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L1Ameas,&L1Afreq,&measurements[5],NULL,0);
					res[6] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L1Bmeas,&L1Bfreq,&measurements[6],NULL,0);
					res[7] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L1Cmeas,&L1Cfreq,&measurements[7],NULL,0);
					res[8] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L7Qmeas,&L7Qfreq,&measurements[8],NULL,0);
					res[9] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L8Qmeas,&L8Qfreq,&measurements[9],NULL,0);
					for (j=0;j<10;j++) {
						if (measurements[j] ==-1 || res[j]<=0) measurements[j] = 0;
						fprintf(options->outFileStream," %14.4f",measurements[j]);
					}
					break;
				case GLONASS:
					res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Cmeas,&C1Cfreq,&measurements[0],NULL,0);
					res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C2Cmeas,&C2Cfreq,&measurements[1],NULL,0);
					res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L1Pmeas,&L1Pfreq,&measurements[2],NULL,0);
					res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&L2Pmeas,&L2Pfreq,&measurements[3],NULL,0);
					for (j=0;j<4;j++) {
						if (measurements[j] ==-1 || res[j]<=0) measurements[j] = 0;
						fprintf(options->outFileStream," %14.4f",measurements[j]);
					}
					break;
				case GEO:
					res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&C1Cmeas,&C1Cfreq,&measurements[0],NULL,0);
					for (j=0;j<1;j++) {
						if (measurements[j] ==-1 || res[j]<=0) measurements[j] = 0;
						fprintf(options->outFileStream," %14.4f",measurements[j]);
					}
					break;
				default:
					break;
			}
			fprintf(options->outFileStream,"\n");
		}
	}
}

/*****************************************************************************
 * Name        : printMeas
 * Description : Print information on the measurements of the input and azimuth
 *               and elevation of the satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TTGDdata  *tgdData              I  N/A  Products for P1-C1 corrections, when applicable
 * TConstellation  *constellation  I  N/A  TConstellation structure where 
 *                                          satellite data is stored
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void printMeas (TEpoch *epoch, TTGDdata *tgdData, TConstellation *constellation, TOptions *options) {
	int						i,j,k,l;
	int						res;
	int						freq;
	int						retDCB,retDCBC1P1;
	int						LLI;
	int						SVN;
	double					measVal;
	double					correction1;
	enum SatelliteBlock		satBlock;	
	
	if (options->printMeas) {
		for (l=0;l<epoch->numSatellites;l++) {
			i=epoch->printIndex2satIndex[l];
			if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
			//Get DCB P1-C1
			correction1=0;
			if (tgdData->GPSp1c1DCBModel == GPSp1c1STRICT && epoch->sat[i].GNSS==GPS) {
				getTGDfromDCB(tgdData, epoch, epoch->sat[i].GNSS, epoch->sat[i].PRN,&epoch->t, C1C, C1P, &correction1, &retDCB, &retDCBC1P1);
				if (retDCB==0) {
					correction1=0;
				}
			} 
			k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			if (options->printV5format==0) {
				//Get satellite block and SVN
				if (constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==NULL) {
					//No previous pointer used
					constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN] = getConstellationElement(epoch->sat[i].GNSS,epoch->sat[i].PRN,&epoch->t,constellation);
					if (constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]!=NULL) {
						satBlock=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->block;
						SVN=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->SVN;
					} else {
						satBlock=UNKNOWN_BLOCK;
						SVN=-1;
					} 
				} else { 
					//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
					if (tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->tDecommissioned)>0) {
						//Not valid anymore, look for a new constellation element
						constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN] = getConstellationElement(epoch->sat[i].GNSS,epoch->sat[i].PRN,&epoch->t,constellation);
						if (constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]!=NULL) {
							satBlock=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->block;
							SVN=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->SVN;
						} else {
							//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
							satBlock=UNKNOWN_BLOCK;
							SVN=-1;
						}
					} else {
						satBlock=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->block;
						SVN=constellation->satLastUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]->SVN;
					}
				}
				
				fprintf(options->outFileStream,"MEAS      %29s %3s %2d %-15s %4d %3d %6d %8.3f %8.3f %2d %*s",epoch->tSoDHourStr,gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,satblock2satblockstr(satBlock),SVN,epoch->cycleslip.narc[k],epoch->cycleslip.arcLength[k]==0?1:epoch->cycleslip.arcLength[k],epoch->sat[i].elevation*r2d,epoch->sat[i].azimuth*r2d,options->printMeasNumMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN],options->printMeasMaxN,options->printMeasStr[epoch->sat[i].GNSS][epoch->sat[i].PRN]);
			} else {
				fprintf(options->outFileStream,"MEAS      %17s %3s %2d %8.3f %8.3f %2d %*s",epoch->tStr,gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,epoch->sat[i].elevation*r2d,epoch->sat[i].azimuth*r2d,options->printMeasNumMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN],options->printMeasMaxN,options->printMeasStr[epoch->sat[i].GNSS][epoch->sat[i].PRN]);
			}
			for (j=0;j<options->printMeasNumMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN];j++) {
				if (options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]%4==0 && options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]<I1) {
					//SNR measurement. The "-3" in the line below is to convert from SNR measurement to its
					//correspondant code measurement, so there is a value in meas2SNRInd
					measVal=epoch->sat[i].meas[epoch->measOrder[epoch->sat[i].GNSS].meas2SNRInd[options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]-3]].SNRvalue;
					if (measVal==-1.) measVal = 0;
					fprintf(options->outFileStream," %6.3f",measVal);
				} else if (options->printMeasLLIFlag[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]==1) {
					//Print LLI flag
					LLI=epoch->sat[i].meas[epoch->measOrder[epoch->sat[i].GNSS].meas2Ind[options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]]].LLI;
					if (LLI<0) LLI = 0;
					fprintf(options->outFileStream," %01d",LLI);
				} else {
					freq=getFrequencyInt(options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]);
					res = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,&options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j],&freq,&measVal,NULL,0);
					if (measVal==-1. || res<=0 ) measVal = 0;
					if(epoch->sat[i].GNSS==GPS) {
						switch (options->printMeasListMeas[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]) {
							case C1P:

								if(epoch->receiver.recType==rtNOP1||epoch->receiver.recType==rtCROSS)  measVal-=correction1;
								break;
							case C2P:
								if (epoch->receiver.recType==rtCROSS) measVal-=correction1;
								break;
							default:
								break;
						}
					}
					fprintf(options->outFileStream," %14.4f",measVal);
				}
			}
			fprintf(options->outFileStream,"\n");
		}
	}
}

/*****************************************************************************
 * Name        : printCS
 * Description : Prints the cycle-slip information when one is found
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   I  N/A  Reference epoch
 * enum GNSSystem GNSS             I  N/A  Satellite system
 * int  PRN                        I  N/A  Satellite PRN
 * int satIndex                    I  N/A  Index of satellite
 * enum CSType csType              I  N/A  Type of cycle-slip detected
 * char *measStr                   I  N/A  String with measurements to print
 * int mode                        I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 * double maxDataGap               I    s  Maximum period of time allowed before declaring CS
 * double timeDiff                 I    s  Delta time from previous usable epoch
 * char *LLImeasText               I  N/A  Text with the measurement and LLI flag
 *                                          values of the measurements with LLI
 *                                          flag enabled
 * double LIestDiff                I    m  Absolute difference between measured 
 *                                         and estimated LI values
 * double LIThreshold              I    m  Threshold for LIestDiff
 * double nMWdiff                  I  cyc  Absolute difference between measured 
 *                                         and estimated MW values
 * double nMWdiffThreshold         I  cyc  Threshold for nMWdiff
 * double SFdiff                   I    m  Absolute difference between measured 
 *                                         and estimated SF values
 * double SFThreshold              I    m  Threshold for SFdiff
 * double IGFestDiff               I    m  Absolute difference between measured 
 *                                         and estimated LI values for IGF
 * double IGFThreshold             I    m  Threshold for IGFestDiff
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
void printCS (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, enum CSType csType, int mode, char *measStr, double maxDataGap, double timeDiff, char *LLImeasText, double LIestDiff, double LIThreshold, double nMWdiff, double nMWdiffThreshold, double SFdiff, double SFThreshold, double IGFestDiff, double IGFThreshold, TOptions *options) {
	
	const char	csText[3][8]={"CS","CS_USER","CS_REF"};
	const int	csLength[3]={2,7,7};

	switch (csType+options->printV5format) {
		case CSTypeDataGap:
		 	sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d - DATA_GAP = %.2f THRESHOLD = %.2f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,timeDiff,maxDataGap);
			break;
		case CSTypeDataGapOldFormat:
		 	sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d DATA_GAP = %f THRESHOLD = %f\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN,timeDiff,maxDataGap);
			break;
		case CSTypeLLI:
		 	sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d - LLI%s\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,LLImeasText);
			break;
		case CSTypeLLIOldFormat:
		 	sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d  LLI\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN);
			break;
		case CSTypeSF:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s SF = %.4f THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,SFdiff,SFThreshold);
			break;
		case CSTypeSFOldFormat:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d  L1C1 = %f THRESHOLD = %f\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN,SFdiff,SFThreshold);
			break;
		case CSTypeMW:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s MW = %.4f THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,nMWdiff,nMWdiffThreshold);
			break;
		case CSTypeMWOldFormat:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d  Bw = %f THRESHOLD = %f\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN,nMWdiff,nMWdiffThreshold);
			break;
		case CSTypeLIEst:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s LI = %.4f THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,LIestDiff,LIThreshold);
			break;
		case CSTypeLIEstOldFormat:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d  LI = %f THRESHOLD = %f\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN,LIestDiff,LIThreshold);
			break;
		case CSTypeLINoEst:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s LI = 999999.0000 THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,LIThreshold);
			break;
		case CSTypeLINoEstOldFormat:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-8s %17s %3s %2d  LI = - THRESHOLD = %f\n",csText[mode],epoch->tStr,gnsstype2gnssstr(GNSS),PRN,LIThreshold);
			break;
		case CSTypeIGFEst:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s IGF = %.4f THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,IGFestDiff,IGFThreshold);
			break;
		case CSTypeIGFNoEst:
			sprintf(printbufferCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %s IGF = 999999.0000 THRESHOLD = %.4f\n",csLength[mode],csText[mode],epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),PRN,measStr,IGFThreshold);
			break;
		default:
			return;
			break;
	}
	linesstoredCS[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;

}

/*****************************************************************************
 * Name        : printSFCSdata
 * Description : Prints values used during the computation of the SF cycle-slip
 *                detector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   I  N/A  Reference epoch
 * enum GNSSystem GNSS             I  N/A  Satellite system
 * int  PRN                        I  N/A  Satellite PRN
 * int satIndex                    I  N/A  Index of satellite
 * int satCSIndex                  I  N/A  Index of satellite in cycle-slip array
 * int mode                        I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 * char *measStr                   I  N/A  String with measurements to print
 * double CodeValue                I    m  Code value
 * double PhaseValue               I    m  Phase value
 * double SFMean                   I    m  SF mean of the current window
 * double SFsigma                  I  m^2  SF sigma of the current window
 * double deltaSFCode              I    m  Difference between current epoch code and
 *                                           previous epoch code.
 *                                           If unconsistency check is disabled,
 *                                           value is 999999.
 * double deltaSFPhase             I    m  Difference between current epoch phase and
 *                                           previous epoch phase.
 *                                           If unconsistency check is disabled,
 *                                           value is 999999.
 * double deltaSF                  I    m  Absolute value of the difference between
 *                                           the differences of code and phase
 *                                           (deltaSFCode-deltaSFPhase)
 *                                           If unconsistency check is disabled,
 *                                           value is 999999.
 * double SFdiff                   I  m^2  Square of (PhaseValue - CodeValue
 *                                           -SFMean)
 *                                           If unconsistency flag is set,
 *                                           value is 999999.
 * double SFThreshold              I  m^2  Computed threshold
 *                                           If unconsistency flag is set,
 *                                           value is 999999.
 * int Unconsistency               I  N/A  Unconsistency flag
 *                                            0 -> No unconsistency declared
 *                                            1 -> Unconsistency declared
 * int Cycleslip                   I  N/A  Cycle-slip flag
 *                                            0 -> No cycle-slip declared
 *                                            1 -> cycle-slip declared
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
void printSFCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, double CodeValue, double PhaseValue, double SFMean, double SFsigma, double deltaSFCode, double deltaSFPhase, double deltaSF, double SFdiff, double SFThreshold, int Unconsistency, int Cycleslip, TOptions *options) {

	const char	csText[3][14]={"SFCSDATA","SFCSDATA_USER","SFCSDATA_REF"};
	const int	csLength[3]={8,13,13};

	sprintf(printbufferSFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredSFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %3d %6d %s %14.4f %14.4f %14.4f %14.4f %14.4f %11.4f %11.4f %11.4f %11.4f %8.4f %d %d\n",
	/*1*/	csLength[mode],csText[mode],
	/*2*/	epoch->tSoDHourStr,
	/*3*/	/*DoY*/
	/*4*/	/*SoD*/
	/*5*/	/*HH:MM:SS.zz*/
	/*6*/	gnsstype2gnssstr(GNSS),
	/*7*/	PRN,
	/*8*/	epoch->cycleslip.narc[satCSIndex],
	/*9*/	epoch->cycleslip.arcLength[satCSIndex],
	/*10*/	measStr,
	/*11*/	CodeValue,
	/*12*/	PhaseValue,
	/*13*/	deltaSFCode,
	/*14*/	deltaSFPhase,
	/*15*/	deltaSF,
	/*16*/	SFMean,
	/*17*/	SFsigma,
	/*18*/	SFdiff,
	/*19*/	SFThreshold,
	/*20*/	options->csUnconsistencyCheckThreshold,
	/*21*/	Unconsistency,
	/*22*/	Cycleslip);
	
	linesstoredSFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;

}

/*****************************************************************************
 * Name        : printMWCSdata
 * Description : Prints values used during the computation of the MW cycle-slip
 *                detector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   I  N/A  Reference epoch
 * enum GNSSystem GNSS             I  N/A  Satellite system
 * int  PRN                        I  N/A  Satellite PRN
 * int satIndex                    I  N/A  Index of satellite
 * int satCSIndex                  I  N/A  Index of satellite in cycle-slip array
 * int mode                        I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 * char *measStr                   I  N/A  String with measurements to print
 * enum MeasurementType *measList  I  N/A  Measurement list in detector
 * int *freqList                   I  N/A  Frequency list per measurement
 * double MWMean                   I    m  MW mean of the current arc
 * double MWMean300                I    m  MW mean of the current window
 * double MWsigma                  I    m  MW sigma of the current arc
 * double MWVal                    I    m  Current MW value
 * double nMWdiff                  I    m  Absolute value of the difference between
 *                                           current MW and the MWMean.
 *                                           If arc length is below the min arc length,
 *                                           value is 999999.
 * double nMW300diff               I    m  Absolute value of the difference between
 *                                           current MW and the MWMean300.
 *                                           If arc length is below the min arc length,
 *                                           value is 999999.
 * double nMWdiffThreshold         I    m  Square root of Mwsigma multiplied by the 
 *                                           K-factor
 *                                           If arc length is below the min arc length,
 *                                           value is 999999.
 * int Outlier                     I  N/A  Outlier flag
 *                                            0 -> No outlier declared
 *                                            1 -> Outlier declared
 * int Cycleslip                   I  N/A  Cycle-slip flag
 *                                            0 -> No cycle-slip declared
 *                                            1 -> cycle-slip declared
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
void printMWCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double MWMean, double MWMean300, double MWsigma, double MWVal, double nMWdiff, double nMW300diff, double nMWdiffThreshold, int Outlier, int Cycleslip, TOptions *options) {

	double		meas1,meas2,meas3,meas4;
	const char	csText[3][14]={"MWCSDATA","MWCSDATA_USER","MWCSDATA_REF"};
	const int	csLength[3]={8,13,13};

	getMeasModelValue(epoch,GNSS,PRN,&measList[2],&freqList[0],&meas1,NULL,0);
	getMeasModelValue(epoch,GNSS,PRN,&measList[3],&freqList[1],&meas2,NULL,0);
	getMeasModelValue(epoch,GNSS,PRN,&measList[5],&freqList[2],&meas3,NULL,0);
	getMeasModelValue(epoch,GNSS,PRN,&measList[6],&freqList[3],&meas4,NULL,0);
	sprintf(printbufferMWCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMWCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %3d %6d %s %14.4f %14.4f %14.4f %14.4f %10.4f %10.4f %10.4f %10.4f %11.4f %11.4f %11.4f %8.4f %d %d\n",
	/*1*/	csLength[mode],csText[mode],
	/*2*/	epoch->tSoDHourStr,
	/*3*/	/*DoY*/
	/*4*/	/*SoD*/
	/*5*/	/*HH:MM:SS.zz*/
	/*6*/	gnsstype2gnssstr(GNSS),
	/*7*/	PRN,
	/*8*/	epoch->cycleslip.narc[satCSIndex],
	/*9*/	epoch->cycleslip.arcLength[satCSIndex],
	/*10*/	measStr,
	/*11*/	meas1,
	/*12*/	meas2,
	/*13*/	meas3,
	/*14*/	meas4,
	/*15*/	MWVal,
	/*16*/	MWMean,
	/*17*/	MWMean300,
	/*18*/	MWsigma,
	/*19*/	nMWdiff,
	/*20*/	nMW300diff,
	/*21*/	nMWdiffThreshold,
	/*22*/	options->csMWmin,
	/*23*/	Outlier,
	/*24*/	Cycleslip);
	
	linesstoredMWCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;

}

/*****************************************************************************
 * Name        : printLICSdata
 * Description : Prints values used during the computation of the LI cycle-slip
 *                detector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   I  N/A  Reference epoch
 * enum GNSSystem GNSS             I  N/A  Satellite system
 * int  PRN                        I  N/A  Satellite PRN
 * int satIndex                    I  N/A  Index of satellite
 * int satCSIndex                  I  N/A  Index of satellite in cycle-slip array
 * int mode                        I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 * char *measStr                   I  N/A  String with measurements to print
 * enum MeasurementType *measList  I  N/A  Measurement list in detector
 * int *freqList                   I  N/A  Frequency list per measurement
 * double InitialLI                I    m  First LI in buffer for computing LI jump
 * double LIVal                    I    m  Computed LI value
 * double LIDiffAbs                I    m  Absolute value of the difference between 
 *                                           current LI and first LI in buffer
 * double LIEst                    I    m  Estimated LI value from the polynomial
 *                                          If value is 999999., no value was estimated
 * double LIDiffEstAbs             I    m  Absolute value of the difference between
 *                                           current LI and the estimated LI.
 *                                           If no LI was estimated, value will be
 *                                           999999.
 * double resThreshold             I    m  Absolute value of two times the residual
 *                                           of the estimated LI. If no LI was
 *                                           estimated, value will be 999999.
 * int Outlier                     I  N/A  Outlier flag
 *                                            0 -> No outlier declared
 *                                            1 -> Outlier declared
 * int Cycleslip                   I  N/A  Cycle-slip flag
 *                                            0 -> No cycle-slip declared
 *                                            1 -> cycle-slip declared
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
void printLICSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double InitialLI, double LIVal, double LIDiffAbs, double LIEst, double LIDiffEstAbs, double resThreshold, int Outlier, int Cycleslip, TOptions *options) {

	double		meas1,meas2;
	const char	csText[3][14]={"LICSDATA","LICSDATA_USER","LICSDATA_REF"};
	const int	csLength[3]={8,13,13};

	getMeasModelValue(epoch,GNSS,PRN,&measList[1],&freqList[0],&meas1,NULL,0);
	getMeasModelValue(epoch,GNSS,PRN,&measList[2],&freqList[1],&meas2,NULL,0);
	sprintf(printbufferLICSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredLICSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %3d %6d %s %14.4f %14.4f %8.4f %8.4f %8.4f %11.4f %11.4f %11.4f %8.4f %8.4f %d %d\n",
	/*1*/	csLength[mode],csText[mode],
	/*2*/	epoch->tSoDHourStr,
	/*3*/	/*DoY*/
	/*4*/	/*SoD*/
	/*5*/	/*HH:MM:SS.zz*/
	/*6*/	gnsstype2gnssstr(GNSS),
	/*7*/	PRN,
	/*8*/	epoch->cycleslip.narc[satCSIndex],
	/*9*/	epoch->cycleslip.arcLength[satCSIndex],
	/*10*/	measStr,
	/*11*/	meas1,
	/*12*/	meas2,
	/*13*/	InitialLI,
	/*14*/	LIVal,
	/*15*/	LIDiffAbs,
	/*16*/	LIEst,
	/*17*/	LIDiffEstAbs,
	/*18*/	resThreshold,
	/*19*/	options->csLImaxjump,
	/*20*/	options->csLIThreshold,
	/*21*/	Outlier,
	/*22*/	Cycleslip);
	
	linesstoredLICSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;

}

/*****************************************************************************
 * Name        : printIGFCSdata
 * Description : Prints values used during the computation of the IGF cycle-slip
 *                detector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   I  N/A  Reference epoch
 * enum GNSSystem GNSS             I  N/A  Satellite system
 * int  PRN                        I  N/A  Satellite PRN
 * int satIndex                    I  N/A  Index of satellite
 * int satCSIndex                  I  N/A  Index of satellite in cycle-slip array
 * int mode                        I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 * char *measStr                   I  N/A  String with measurements to print
 * enum MeasurementType *measList  I  N/A  Measurement list in detector
 * int *freqList                   I  N/A  Frequency list per measurement
 * double InitialIGF               I    m  First IGF in buffer for computing IGF jump
 * double IGF                      I    m  Computed IGF value
 * double IGFDiffAbs               I    m  Absolute value of the difference between 
 *                                           current IGF and first IGF in buffer
 * double IGFEst                   I    m  Estimated IGF value from the polynomial
 *                                          If value is 999999., no value was estimated
 * double IGFDiffEstAbs            I    m  Absolute value of the difference between
 *                                           current IGF and the estimated IGF.
 *                                           If no IGF was estimated, value will be
 *                                           999999.
 * double resThreshold             I    m  Absolute value of two times the residual
 *                                           of the estimated IGF. If no IGF was
 *                                           estimated, value will be 999999.
 * int Outlier                     I  N/A  Outlier flag
 *                                            0 -> No outlier declared
 *                                            1 -> Outlier declared
 * int Cycleslip                   I  N/A  Cycle-slip flag
 *                                            0 -> No cycle-slip declared
 *                                            1 -> cycle-slip declared
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
void printIGFCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double InitialIGF, double IGF, double IGFDiffAbs, double IGFEst, double IGFDiffEstAbs, double resThreshold, int Outlier, int Cycleslip, TOptions *options) {

	double					meas1,meas2,meas3,meas4;
	const char				csText[3][15]={"IGFCSDATA","IGFCSDATA_USER","IGFCSDATA_REF"};
	const int				csLength[3]={8,14,14};
	enum MeasurementType 	measIGF;

	if (options->csIGFminNoise==1) {
		measIGF=measList[0]-IGF1012;
		getMeasModelValue(epoch,GNSS,PRN,&measList[2],&freqList[0],&meas1,NULL,0);
		getMeasModelValue(epoch,GNSS,PRN,&measList[3],&freqList[1],&meas2,NULL,0);
		if (measList[5]!=measList[2] && measList[5]!=measList[3]) {
			getMeasModelValue(epoch,GNSS,PRN,&measList[5],&freqList[2],&meas3,NULL,0);
		} else {
			getMeasModelValue(epoch,GNSS,PRN,&measList[6],&freqList[3],&meas3,NULL,0);
		}

		sprintf(printbufferIGFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredIGFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %3d %6d %s     %14.4f %14.4f %14.4f %14.4f %8.4f %8.4f %8.4f %11.4f %11.4f %11.4f %8.4f %8.4f %d %d %7.4f %7.4f %7.4f\n",
		/*1*/	csLength[mode],csText[mode],
		/*2*/	epoch->tSoDHourStr,
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	/*HH:MM:SS.zz*/
		/*6*/	gnsstype2gnssstr(GNSS),
		/*7*/	PRN,
		/*8*/	epoch->cycleslip.narc[satCSIndex],
		/*9*/	epoch->cycleslip.arcLength[satCSIndex],
		/*10*/	measStr,
		/*11*/	meas1,
		/*12*/	meas2,
		/*13*/	meas3,
		/*14*/	999999.,
		/*15*/	InitialIGF,
		/*16*/	IGF,
		/*17*/	IGFDiffAbs,
		/*18*/	IGFEst,
		/*19*/	IGFDiffEstAbs,
		/*20*/	resThreshold,
		/*21*/	options->csIGFmaxjump,
		/*22*/	options->csIGFThreshold,
		/*23*/	Outlier,
		/*24*/	Cycleslip,
		/*25*/	epoch->measOrder[GNSS].IGFcombFactors[PRN][measIGF][0],
		/*26*/	epoch->measOrder[GNSS].IGFcombFactors[PRN][measIGF][1],
		/*27*/	epoch->measOrder[GNSS].IGFcombFactors[PRN][measIGF][2]);
	} else {
		getMeasModelValue(epoch,GNSS,PRN,&measList[2],&freqList[0],&meas1,NULL,0);
		getMeasModelValue(epoch,GNSS,PRN,&measList[3],&freqList[1],&meas2,NULL,0);
		getMeasModelValue(epoch,GNSS,PRN,&measList[5],&freqList[2],&meas3,NULL,0);
		getMeasModelValue(epoch,GNSS,PRN,&measList[6],&freqList[3],&meas4,NULL,0);

		sprintf(printbufferIGFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredIGFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"%-*s %29s %3s %2d %3d %6d %s %14.4f %14.4f %14.4f %14.4f %8.4f %8.4f %8.4f %11.4f %11.4f %11.4f %8.4f %8.4f %d %d\n",
		/*1*/	csLength[mode],csText[mode],
		/*2*/	epoch->tSoDHourStr,
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	/*HH:MM:SS.zz*/
		/*6*/	gnsstype2gnssstr(GNSS),
		/*7*/	PRN,
		/*8*/	epoch->cycleslip.narc[satCSIndex],
		/*9*/	epoch->cycleslip.arcLength[satCSIndex],
		/*10*/	measStr,
		/*11*/	meas1,
		/*12*/	meas2,
		/*13*/	meas3,
		/*14*/	meas4,
		/*15*/	InitialIGF,
		/*16*/	IGF,
		/*17*/	IGFDiffAbs,
		/*18*/	IGFEst,
		/*19*/	IGFDiffEstAbs,
		/*20*/	resThreshold,
		/*21*/	options->csIGFmaxjump,
		/*22*/	options->csIGFThreshold,
		/*23*/	Outlier,
		/*24*/	Cycleslip);
	}
	linesstoredIGFCSdata[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;
}

/*****************************************************************************
 * Name        : printModel
 * Description : Prints each of the components of the model for a specific 
 *               satellite and measurement
 * Parameters  :
 * Name                                     |Da|Unit|Description
 * TEpoch  *epoch                            I  N/A  Reference epoch
 * int  satIndex                             I  N/A  Index of the selected satellite
 * int  measIndex                            I  N/A  Index of the modelled measurement
 * enum MeasurementType meas                 I  N/A  Measurement modelled
 * char *meas                                I  N/A  Measurement modelled in text format
 * TBRDCblock *blockOrbit                    I  N/A  Broadcast block used for orbit computation
 * double  measurement                       I    m  Measurement value
 * double  flightTime                        I    s  Signal flight time
 * double  geometricDistance                 I    m  Geometric distance between satellite and receiver
 * double  satelliteClockModel               I    m  Satellite clock error
 * double  GNSSClkOffset                     I    m  Inter-system clock bias (if provided by user, otherwise 0.)
 * double  satellitePhaseCenterProjection    I    m  Projection of the satellite phase center into the LoS
 * double  satellitePhaseCenterVarProjection I    m  Projection of the satellite phase center variation into the LoS
 * double  receiverPhaseCenterProjection     I    m  Projection of the receiver phase center into the LoS 
 * double  receiverPhaseCenterVarProjection  I    m  Projection of the receiver phase center variation into the LoS 
 * double  receiverARPProjection             I    m  Projection of the receiver ARP into the LoS
 * double  relativityModel                   I    m  Relativity model
 * double  windUpMetModel                    I    m  Wind up model (for carrier phase only)
 * double  troposphereModel                  I    m  Troposphere model
 * double  ionosphereModel                   I    m  Ionosphere model
 * double  gravitationalDelayModel           I    m  Gravitational delay model
 * double  solidTidesModel                   I    m  Projection of the effect of solid tides into the LoS
 * double  TGDModel                          I    m  Full TGD model (all terms added)
 * double  GPSp1c1DCB                        I    m  GPS P1-C1 DCB
 * double  differentialDCB                   I    m  Differential DCB (any measurement or constellation)
 * double  ISCDCB                            I    m  ISC added to the differential DCB
 * double  preciseDCB                        I    m  DCB computed when using single frequency with precise orbits (BeiDou only)
 * double  ConstClockOffset                  I    m  Clock offset between GPS and another constellation
 * double  *DCBmodel                         I    m  Dual-frequency DCB computed
 * TConstellation  *constellation            I  N/A  TConstellation structure where 
 *                                                    satellite data is stored
 * TOptions  *options                        I  N/A  TOptions structure
 *****************************************************************************/
void printModel (TEpoch *epoch, int satIndex, int measIndex, enum MeasurementType meas, char *measStr, TBRDCblock *blockOrbit, double measurement, double flightTime, double geometricDistance, double satelliteClockModel, double GNSSClkOffset, double satellitePhaseCenterProjection, double satellitePhaseCenterVarProjection, double receiverPhaseCenterProjection, double  receiverPhaseCenterVarProjection, double receiverARPProjection, double relativityModel, double windUpMetModel, double troposphereModel, double ionosphereModel, double gravitationalDelayModel, double solidTidesModel, double TGDModel, double GPSp1c1DCB, double differentialDCB, double ISCDCB, double preciseDCB, double *DCBmodel, TConstellation *constellation, TOptions *options) {

	int						i,j,FilterPos,len;
	int						IODorbit,measSNRIndex;
	int						PRN=epoch->sat[satIndex].PRN;
	int						freqnumber,timeoffset;
	int						SVN;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	double 					*velocity;
	double					SNRVal;
	char					EphtypeOrbit[20],meas1[10];
	enum SatelliteBlock		satBlock;	
	
	i = epoch->satCSIndex[GNSS][PRN];

	//Get SNR measurement
	measSNRIndex = epoch->measOrder[GNSS].meas2SNRInd[meas];
	SNRVal= epoch->sat[satIndex].meas[measSNRIndex].SNRvalue;

	if (options->satVel==svINERTIAL) {
		velocity=epoch->sat[satIndex].velocity;
	} else {
		velocity=epoch->sat[satIndex].ITRFvel;
	} 
	
	if (options->printV5format==0) {

		if (blockOrbit!=NULL) {
			strcpy(EphtypeOrbit,BRDCType2String(GNSS,blockOrbit->BRDCtype));
			IODorbit=blockOrbit->IODE;
		} else {
			strcpy(EphtypeOrbit,"SP3");
			IODorbit=-1;
		}

		switch (GNSS) {
			case GLONASS:
				freqnumber=epoch->GLOfreqnumber[PRN];
				timeoffset=epoch->leapSeconds;
				break;
			case BDS:
				freqnumber=0;
				timeoffset=DIFFBDS2GPSTIME;
				break;
			default:
				freqnumber=0;
				timeoffset=0;
				break;
		}

		//Get satellite block and SVN
		if (constellation->satLastUsed[GNSS][PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
				if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
					satBlock=constellation->satLastUsed[GNSS][PRN]->block;
					SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			}
		}


		len=sprintf(printbufferMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"MODEL     %29s %3s %2d %-15s %4d %3d %6d %8.3f %8.3f %3s %9s %4d %2d %2d %11.5f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %8.3f %14.4f",
			/*2*/		epoch->tSoDHourStr,
			/*3*/		/*DoY*/
			/*4*/		/*SoD*/
			/*5*/		/*HH:MM:SS.zz*/
			/*6*/		gnsstype2gnssstr(GNSS),
			/*7*/		PRN,
			/*8*/		satblock2satblockstr(satBlock),
			/*9*/		SVN,
			/*10*/		epoch->cycleslip.narc[i],
			/*11*/		epoch->cycleslip.arcLength[i]==0?1:epoch->cycleslip.arcLength[i],
			/*12*/		epoch->sat[satIndex].elevation*r2d,
			/*13*/		epoch->sat[satIndex].azimuth*r2d,
			/*14*/		measStr,
			/*15*/		EphtypeOrbit,
			/*16*/		IODorbit,
			/*17*/		freqnumber,
			/*18*/		timeoffset,
			/*19*/		measurement,
			/*20*/		flightTime,
			/*21*/		epoch->sat[satIndex].position[0],
			/*22*/		epoch->sat[satIndex].position[1],
			/*23*/		epoch->sat[satIndex].position[2],
			/*24*/		velocity[0],
			/*25*/		velocity[1],
			/*26*/		velocity[2],
			/*27*/		geometricDistance,	//GEOMETRIC RANGE BETWEEN RECEIVER AND ANTENNA PHASE CENTERS//
			/*28*/		satelliteClockModel*options->ClktimeFactor,
			/*29*/		satellitePhaseCenterProjection,
			/*30*/		satellitePhaseCenterVarProjection,
			/*31*/		receiverPhaseCenterProjection,
			/*32*/		receiverPhaseCenterVarProjection,
			/*33*/		receiverARPProjection,
			/*34*/		relativityModel,
			/*35*/		windUpMetModel,
			/*36*/		troposphereModel,
			/*37*/		ionosphereModel,
			/*38*/		gravitationalDelayModel,
			/*39*/		solidTidesModel,
			/*40*/		0.,	//Ocean loading (to be implemented)
			/*41*/		0.,	//Polar tides (to be implemented)
			/*42*/		0., //Fractional part of the ambiguity (when it is read from a file, to be implemented)
			/*43*/		GNSSClkOffset*options->ClktimeFactor, //Inter system clock bias
			/*44*/		GPSp1c1DCB*options->ClktimeFactor,
			/*45*/		differentialDCB*options->ClktimeFactor,
			/*46*/		ISCDCB*options->ClktimeFactor,
			/*47*/		preciseDCB*options->ClktimeFactor,
			/*48*/		TGDModel*options->ClktimeFactor,
			/*49*/		SNRVal,
			/*50*/		epoch->sat[satIndex].meas[measIndex].model);

				for(j=0;j<epoch->measOrder[GNSS].numDualFreqDCBFreqList[PRN];j++) {
					FilterPos=epoch->measOrder[GNSS].DualFreqDCBFilterMeasPos[PRN][j];
					if (options->filterMeasList[ROVERPOS][GNSS][PRN][FilterPos][1]==meas||options->filterMeasList[ROVERPOS][GNSS][PRN][FilterPos][2]==meas) {
						strcpy(meas1,meastype2measstr(options->filterMeasList[ROVERPOS][GNSS][PRN][FilterPos][1]));
						len+=sprintf(&printbufferMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]][len]," %3s-%3s %9.5f %14.4f",
								meas1,
								meastype2measstr(options->filterMeasList[ROVERPOS][GNSS][PRN][FilterPos][2]),
								DCBmodel[FilterPos]*options->ClktimeFactor,
								epoch->sat[satIndex].meas[measIndex].modelAll[FilterPos]);
					}
				}
				sprintf(&printbufferMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]][len],"\n");
	} else {
		sprintf(printbufferMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"MODEL     %17s %3s %2d %3s %11.5f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %8.3f %8.3f %8.3f\n",
			/*2*/		epoch->tStr,
			/*3*/		/*DoY*/
			/*4*/		/*SoD*/
			/*5*/		gnsstype2gnssstr(GNSS),
			/*6*/		PRN,
			/*7*/		measStr,
			/*8*/		flightTime,
			/*9*/		measurement,
			/*10*/		epoch->sat[satIndex].meas[measIndex].model,
			/*11*/		epoch->sat[satIndex].position[0],
			/*12*/		epoch->sat[satIndex].position[1],
			/*13*/		epoch->sat[satIndex].position[2],
			/*14*/		velocity[0],
			/*15*/		velocity[1],
			/*16*/		velocity[2],
			/*17*/		geometricDistance,	//GEOMETRIC RANGE BETWEEN RECEIVER AND ANTENNA PHASE CENTERS//
			/*18*/		satelliteClockModel,
			/*19*/		satellitePhaseCenterProjection+satellitePhaseCenterVarProjection,
			/*20*/		receiverPhaseCenterProjection+receiverPhaseCenterVarProjection,
			/*21*/		receiverARPProjection,
			/*22*/		relativityModel,
			/*23*/		windUpMetModel,
			/*24*/		troposphereModel,
			/*25*/		ionosphereModel,
			/*26*/		gravitationalDelayModel,
			/*27*/		TGDModel,
			/*28*/		solidTidesModel,
			/*29*/		epoch->sat[satIndex].elevation*r2d,
			/*30*/		epoch->sat[satIndex].azimuth*r2d,
			/*31*/		SNRVal);
	}

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if(options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[i] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]][5]='*';
	}
	linesstoredMODEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;
}

/*****************************************************************************
 * Name        : printSatSel
 * Description : Prints debug information of the reason why a satellite has 
 *               been discarded (or selected) for processing 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  Reference epoch
 * int  selected                   I  N/A  Flag to set if the satellite was 
 *                                         selected (1) or discarded (0) 
 * int  errorcode                  I  N/A  Error code for the discard reason                                       
 * char  *message                  I  N/A  Reason of the discard (if selected==0)
 * int  satIndex                   I  N/A  Selected satellite
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatSel (TEpoch *epoch, int selected, int errorcode, char *message, int satIndex, TOptions *options) {

	enum GNSSystem	GNSS=epoch->sat[satIndex].GNSS;

	if ( options->printSatSel==0 ) return;

	if (options->printV5format==0) {
		sprintf(printbufferSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"SATSEL    %29s %3s %2d %3d \"%s\"\n",epoch->tSoDHourStr,gnsstype2gnssstr(GNSS),epoch->sat[satIndex].PRN,errorcode,message);
	} else {
		if ( !selected ) sprintf(printbufferSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"SATSEL    %17s %3s %2d discarded: %s\n",epoch->tStr,gnsstype2gnssstr(GNSS),epoch->sat[satIndex].PRN,message);
		else sprintf(printbufferSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"SATSEL    %17s %3s %2d selected\n",epoch->tStr,gnsstype2gnssstr(GNSS),epoch->sat[satIndex].PRN);
	}

	linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;
}

/*****************************************************************************
 * Name        : printPrefit
 * Description : Prints the prefilter residuals for a specific satellite/measurement
 * Parameters  :
 * Name                                |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  Reference epoch
 * int  satIndex                        I  N/A  Selected satellite
 * int  measIndex                       I  N/A  Index of the modelled measurement
 * int  csIndex                         I  N/A  Satellite index in cycle-slip array
 * int  freq                            I  N/A  Frequency number of the measurement
 * double  prefit                       I    m  Computed prefit
 * double  measurement                  I    m  Measurement value (smoothed if requires smoothing)
 * double  smoothWith                   I    m  Measurement used for smoothing
 * double  lambda                       I    m  wavelength of the measurement
 * double  model                        I    m  Modeled value
 * double  stdDev                       I    m  Assigned weight of the measurement 
 * TConstellation  *constellation       I  N/A  Constellation information of the products (for printing)
 * TOptions  *options                   I  N/A  TOptions structure
 *****************************************************************************/
void printPrefit (TEpoch  *epoch, int satIndex, int measIndex, int csIndex, int freq, double prefit, double measurement, double smoothWith, double lambda, double model, double stdDev, TConstellation *constellation, TOptions *options) {	

	int						PRN=epoch->sat[satIndex].PRN;
	int						indexPrintPos;
	int						freqnumber=0;
	int						measKindPrint;
	int						SVN;
	double					LoS;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	enum SatelliteBlock		satBlock;	

	LoS=sqrt(epoch->sat[satIndex].LoS[0]*epoch->sat[satIndex].LoS[0] + epoch->sat[satIndex].LoS[1]*epoch->sat[satIndex].LoS[1] 
			+ epoch->sat[satIndex].LoS[2]*epoch->sat[satIndex].LoS[2]);

	indexPrintPos=epoch->measOrder[GNSS].MeasPos2PrintPos[PRN][measIndex];


	measKindPrint=FilterMeasType2PrintType[options->filterMeasTypeList[ROVERPOS][GNSS][PRN][measIndex]];

	if (options->printV5format==0) {

		if (GNSS==GLONASS) {
			freqnumber=epoch->GLOfreqnumber[PRN];
		}

		//Get satellite block and SVN
		if (constellation->satLastUsed[GNSS][PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
				if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
					satBlock=constellation->satLastUsed[GNSS][PRN]->block;
					SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			}
		}

		sprintf(printbufferPREFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos][linesstoredPREFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]],"PREFIT%1s   %29s %3s %2d %-15s %4d %3d %6d %8.3f %8.3f %12s %12s %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %9.4f %9.4f %9.4f %2d %6.4f\n",
		/*1*/		epoch->sat[satIndex].available?"":"*",
		/*2*/		epoch->tSoDHourStr,
		/*3*/		/*DoY*/
		/*4*/		/*SoD*/
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		gnsstype2gnssstr(GNSS),
		/*7*/		PRN,
		/*8*/		satblock2satblockstr(satBlock),
		/*9*/		SVN,
		/*10*/		epoch->cycleslip.narc[csIndex],
		/*11*/		epoch->cycleslip.arcLength[csIndex],
		/*12*/		epoch->sat[satIndex].elevation*r2d,
		/*13*/		epoch->sat[satIndex].azimuth*r2d,
		/*14*/		options->filterMeasText[ROVERPOS][GNSS][PRN][measIndex],
		/*15*/		options->filterSmoothMeasText[ROVERPOS][GNSS][PRN][measIndex],
		/*16*/		prefit,
		/*17*/		measurement,
		/*18*/		smoothWith,
		/*19*/		model,
		/*20*/		-1.0*epoch->sat[satIndex].LoS[0],
		/*21*/		-1.0*epoch->sat[satIndex].LoS[1],
		/*22*/		-1.0*epoch->sat[satIndex].LoS[2],
		/*23*/		LoS,	
		/*24*/		stdDev==SIGMA_INF?9999.999:stdDev,
		/*25*/		epoch->sat[satIndex].tropWetMap,
		/*26*/		lambda,
		/*27*/		freqnumber,
		/*28*/		epoch->measOrder[GNSS].TECU2metres[freq][PRN]);

	} else {
		sprintf(printbufferPREFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos][linesstoredPREFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]],"PREFIT%1s   %17s %3s %2d %3s %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %8.3f %8.3f %8.3f %8.3f %5d\n",
		/*1*/		epoch->sat[satIndex].available?"":"*",
		/*2*/		epoch->tStr,
		/*3*/		/*DoY*/
		/*4*/		/*SoD*/
		/*5*/		gnsstype2gnssstr(GNSS),
		/*6*/		PRN,
		/*7*/		options->filterMeasText[ROVERPOS][GNSS][PRN][measIndex],
		/*8*/		prefit,
		/*9*/		measurement,
		/*10*/		model,
		/*11*/		-1.0*epoch->sat[satIndex].LoS[0],
		/*12*/		-1.0*epoch->sat[satIndex].LoS[1],
		/*13*/		-1.0*epoch->sat[satIndex].LoS[2],
		/*14*/		LoS,
		/*15*/		epoch->sat[satIndex].elevation*r2d,
		/*16*/		epoch->sat[satIndex].azimuth*r2d,
		/*17*/		stdDev==SIGMA_INF?9999.999:stdDev,
		/*18*/		epoch->sat[satIndex].tropWetMap,
		/*19*/		epoch->cycleslip.narc[csIndex]);
	}


	linesstoredPREFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]++;
}

/*****************************************************************************
 * Name        : printEpochsat
 * Description : Prints the satellites used for processing an epoch (per
 *                each measurement).
 *               For V5 format, only used GPS satellites are printed, as no
 *                constellation identifier was printed
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                   I  N/A  Reference epoch
 * int   measKindPrint              I  N/A  Type of measurement
 * char *measStr                    I  N/A  Selected measurement (text format)
 * char *measStrSmooth              I  N/A  Selected measurement for smoothing (text format)
 * int  *numUsedSat                 I  N/A  Array with number of used satellites used per constellation
 * int  **satUsedList               I  N/A  Array containing the used satellites PRN per constellation
 * int  *numUnusedSat               I  N/A  Array with number of unused satellites used per constellation
 * int  **satUnusedList             I  N/A  Array containing the unused satellites PRN per constellation
 * TOptions  *options               I  N/A  TOptions structure
 *****************************************************************************/
void printEpochsat (TEpoch *epoch, int measKindPrint, char *measStr, char *measStrSmooth, int *numUsedSat, int **satUsedList, int *numUnusedSat, int **satUnusedList, TOptions *options) {
	int		i,j,len;
	int		totalUsedSat=0,totalUnusedSat=0,totalSat;

	if (options->printV5format==0) {
		for(i=0;i<MAX_GNSS;i++) {
			totalUsedSat+=numUsedSat[i];
			totalUnusedSat+=numUnusedSat[i];
		}

		totalSat=totalUsedSat+totalUnusedSat;


		if (totalSat==0) return; //If total number of satellites used and unsed is 0, do not print line

		len=sprintf(printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]],"EPOCHSAT  %29s %12s %12s %2d %+3d",
					epoch->tSoDHourStr,
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
			/*5*/	/*HH:MM:SS.zz*/
			/*6*/	measStr,
			/*7*/	measStrSmooth,
			/*8*/	totalSat,
			/*9*/	totalUsedSat);

		//Print number of used satellites per each constellation
		for(i=0;i<MAX_GNSS;i++) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %c %2d",gnsstype2char(i),numUsedSat[i]);
		}

		//Print total number of satellites unused
		if (totalUnusedSat>0) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %+3d",-1*totalUnusedSat);
		} else {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %3s","-0");
		}

		//Print number of unused satellites per each constellation
		for(i=0;i<MAX_GNSS;i++) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %c %2d",gnsstype2char(i),numUnusedSat[i]);
		}

		//Print list of used satellites
		for (i=0;i<MAX_GNSS;i++) {
			for(j=0;j<numUsedSat[i];j++) {
				len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," +%c%02d",gnsstype2char(i),satUsedList[i][j]);
			}
		}
		//Print list of unused satellites
		for (i=0;i<MAX_GNSS;i++) {
			for(j=0;j<numUnusedSat[i];j++) {
				len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," -%c%02d",gnsstype2char(i),satUnusedList[i][j]);
			}
		}
		sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len],"\n");

	} else {

		if (numUsedSat[GPS]==0) return; //If number of used GPS satellites is 0, do not print line

		len=sprintf(printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]],"EPOCHSAT  %17s %3s %2d",
					epoch->tStr,
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
			/*5*/	measStr,
			/*6*/	numUsedSat[GPS]);

		for (i=0;i<numUsedSat[GPS];i++) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %2d",satUsedList[GPS][i]);
		}
		sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len],"\n");
	}

	linesstoredEPOCHSAT[measKindPrint]++;
}


/*****************************************************************************
 * Name        : printEpochsatAllSat
 * Description : Prints the satellites used for processing an epoch for all
 *                 measurements.
 *                Version V5 did not have this print
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  Reference epoch
 *****************************************************************************/
void printEpochsatAllSat (TEpoch *epoch) {
    int     i,j,len;
	int		measKindPrint=PRINT_ORDER_PHASE; //Set it tp phase measurement so this line is printed the last one of the EPOCHSAT lines

	len=sprintf(printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]],"EPOCHSAT  %29s %12s %12s %2d %+3d",
				epoch->tSoDHourStr,
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	/*HH:MM:SS.zz*/
		/*6*/	"ALL",
		/*7*/	"-",
		/*8*/	epoch->numSatSolutionFilter+epoch->numSatNotUsedFilter,
		/*9*/	epoch->numSatSolutionFilter);
	
	//Print number of used satellites per each constellation
	for(i=0;i<MAX_GNSS;i++) {
		len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %c %2d",gnsstype2char(i),epoch->numSatSolutionGNSS[i]);
	}

	//Print total number of satellites unused
	if (epoch->numSatNotUsedFilter>0) {
		len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %+3d",-1*epoch->numSatNotUsedFilter);
	} else {
		len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %3s","-0");
	}

	//Print number of unused satellites per each constellation
	for(i=0;i<MAX_GNSS;i++) {
		len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," %c %2d",gnsstype2char(i),epoch->numSatnotUsedGNSS[i]);
	}

	//Print list of used satellites
	for (i=0;i<MAX_GNSS;i++) {
		for(j=0;j<epoch->numSatSolutionGNSS[i];j++) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," +%c%02d",gnsstype2char(i),epoch->listPRNSatSolutionConst[i][j]);
		}
	}
	//Print list of unused satellites
	for (i=0;i<MAX_GNSS;i++) {
		for(j=0;j<epoch->numSatnotUsedGNSS[i];j++) {
			len+=sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len]," -%c%02d",gnsstype2char(i),epoch->listPRNSatnotUsedConst[i][j]);
		}
	}
	sprintf(&printbufferEPOCHSAT[measKindPrint][linesstoredEPOCHSAT[measKindPrint]][len],"\n");

	linesstoredEPOCHSAT[measKindPrint]++;
}


/*****************************************************************************
 * Name        : printFilter
 * Description : Prints the parameters estimated from the filter
 *                For the inter-system clock bias, a fixed space will be left
 *                for each constellation, so they are printed always in the same
 *                position
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  Reference epoch
 * int  nunk                       I  N/A  Number of unknowns in the filter
 * TFilterSolution  *solution      I  N/A  Structure storing the estimated parameters
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printFilter (TEpoch  *epoch, int nunk, TFilterSolution *solution, TOptions *options) {
	int i,j,k,len;

	if (options->printV5format==0) {
		len=sprintf(printbufferFILTER,"FILTER    %29s %3s %1d %2d",
			/*2*/	epoch->tSoDHourStr,
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
			/*5*/	/*HH:MM:SS.zz*/
			/*6*/	gnsstype2gnssstr(epoch->ReferenceGNSSClock),
			/*7*/	epoch->numInterSystemClocksFilter,
			/*8*/	nunk);
	} else {
		len=sprintf(printbufferFILTER,"FILTER    %17s",
			/*2*/	epoch->tStr);
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
	}

	//Print coordinates
	for (i=0;i<3;i++) {
		len+=sprintf(&printbufferFILTER[len]," %14.4f",solution->x[i]);
	}
	//Print receiver clock
	len+=sprintf(&printbufferFILTER[len]," %14.4f",solution->x[i]*options->ClktimeFactor);
	i++;

	//Print remaining estimated terms. In version v6 and newer, ambiguities are removed from message,
	//as in every epoch the position may change
	if (options->printV5format==0) {
		//Print inter-system clock bias. The position for all GNSS will be fixed,
		//even if they are not estimated, so the column number remains the same
		//indepently if in an epoch a constellations dissapears. 
		for(j=0;j<MAX_GNSS;j++) {
			k=epoch->InterSystemClocksUnk[j];
			len+=sprintf(&printbufferFILTER[len]," %14.4f",k==-1?0.:solution->x[k]*options->ClktimeFactor);
		}
		i+=epoch->numInterSystemClocksFilter;
		//Pending to revise when Iono and DCB are estimated
		k=i+options->estimateTroposphere+options->estimateGLOIFB+options->estimateRecWindUp;
		for(;i<k;i++) {
			len+=sprintf(&printbufferFILTER[len]," %14.4f",solution->x[i]);
		}
	} else {
		for(;i<nunk;i++) {
			len+=sprintf(&printbufferFILTER[len]," %14.4f",solution->x[i]);
		}
	}

	sprintf(&printbufferFILTER[len],"\n");
}

/*****************************************************************************
 * Name        : printPostfit
 * Description : Prints the postfilter residuals for a specific satellite/measurement
 * Parameters  :
 * Name                                |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  Reference epoch
 * int  satIndex                        I  N/A  Selected satellite
 * int  measIndex                       I  N/A  Index of the modelled measurement
 * int  csIndex                         I  N/A  Satellite index in cycle-slip array
 * double  postfit                      I  N/A  Computed postfit
 * double  measurement                  I    m  Measurement value
 * double  smoothWith                   I    m  Measurement used for smoothing
 * double  model                        I    m  Modeled value
 * double  estimatedParameters          I    m  Estimated parameters from the filter
 * double  InterSystemClock             I    m  Estimated inter-system clock bias (if applicable)
 * double  ambiguity                    I    m  Estimated ambiguity value (only for carrier phases)
 * double  Iono                         I    m  Estimated Ionosphere value (in metres of the signal frequency)
 * double  satDCB                       I    m  Estimated satellite DCB value (in metres of the signal frequency)
 * double  recDCB                       I    m  Estimated receiver DCB value (in metres of the signal frequency)
 * TConstellation  *constellation       I  N/A  Constellation information of the products (for printing)
 * TOptions  *options                   I  N/A  TOptions structure
 *****************************************************************************/
void printPostfit (TEpoch  *epoch, int satIndex, int measIndex, int csIndex, double postfit, double measurement, double smoothWith, double model, double estimatedParameters, double InterSystemClock, double ambiguity, double Iono, double satDCB, double recDCB, TConstellation *constellation, TOptions *options) {

	int						PRN=epoch->sat[satIndex].PRN;
	int						indexPrintPos;
	int						measKindPrint;
	int						SVN;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	enum SatelliteBlock		satBlock;	

	indexPrintPos=epoch->measOrder[GNSS].MeasPos2PrintPos[PRN][measIndex];

	measKindPrint=FilterMeasType2PrintType[options->filterMeasTypeList[ROVERPOS][GNSS][PRN][measIndex]];

	if (options->printV5format==0) {
		//Get satellite block and SVN
		if (constellation->satLastUsed[GNSS][PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
				if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
					satBlock=constellation->satLastUsed[GNSS][PRN]->block;
					SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			}
		}

		sprintf(printbufferPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos][linesstoredPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]],"POSTFIT%1s  %29s %3s %2d %-15s %4d %3d %6d %8.3f %8.3f %12s %12s %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f\n",
			/*1*/		epoch->sat[satIndex].available?"":"*",
			/*2*/		epoch->tSoDHourStr,
			/*3*/		/*DoY*/
			/*4*/		/*SoD*/
			/*5*/		/*HH:MM:SS.zz*/
			/*6*/		gnsstype2gnssstr(GNSS),
			/*7*/		PRN,
			/*8*/		satblock2satblockstr(satBlock),
			/*9*/		SVN,
			/*10*/		epoch->cycleslip.narc[csIndex],
			/*11*/		epoch->cycleslip.arcLength[csIndex],
			/*12*/		epoch->sat[satIndex].elevation*r2d,
			/*13*/		epoch->sat[satIndex].azimuth*r2d,
			/*14*/		options->filterMeasText[ROVERPOS][GNSS][PRN][measIndex],
			/*15*/		options->filterSmoothMeasText[ROVERPOS][GNSS][PRN][measIndex],
			/*16*/		postfit,
			/*17*/		measurement,
			/*18*/		smoothWith,
			/*19*/		model + estimatedParameters,
			/*20*/		InterSystemClock*options->ClktimeFactor,
			/*21*/		ambiguity,
			/*22*/		Iono,
			/*23*/		satDCB*options->ClktimeFactor,
			/*24*/		recDCB*options->ClktimeFactor);
	} else {

		switch (options->filterMeasKind[ROVERPOS][GNSS][PRN][measIndex]) {
			case CarrierPhase:
				sprintf(printbufferPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos][linesstoredPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]],"POSTFIT%1s  %17s %3s %2d %3s %14.4f %14.4f %14.4f %8.3f %8.3f %14.4f\n",
				/*1*/		epoch->sat[satIndex].available?"":"*",
				/*2*/		epoch->tStr,
				/*3*/		/*DoY*/
				/*4*/		/*SoD*/
				/*5*/		gnsstype2gnssstr(GNSS),
				/*6*/		PRN,
				/*7*/		options->filterMeasText[ROVERPOS][GNSS][PRN][measIndex],
				/*8*/		postfit,
				/*9*/		measurement,
				/*10*/		model + estimatedParameters,
				/*11*/		epoch->sat[satIndex].elevation*r2d,
				/*12*/		epoch->sat[satIndex].azimuth*r2d,
				/*13*/		ambiguity);
				break;
			case Pseudorange:
				sprintf(printbufferPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos][linesstoredPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]],"POSTFIT%1s  %17s %3s %2d %3s %14.4f %14.4f %14.4f %8.3f %8.3f\n",
				/*1*/		epoch->sat[satIndex].available?"":"*",
				/*2*/		epoch->tStr,
				/*3*/		/*DoY*/
				/*4*/		/*SoD*/
				/*5*/		gnsstype2gnssstr(GNSS),
				/*6*/		PRN,
				/*7*/		options->filterMeasText[ROVERPOS][GNSS][PRN][measIndex],
				/*8*/		postfit,
				/*9*/		measurement,
				/*10*/		model + estimatedParameters,
				/*11*/		epoch->sat[satIndex].elevation*r2d,
				/*12*/		epoch->sat[satIndex].azimuth*r2d);
				break;
			default:
				return;
				break;
		}
	}

	linesstoredPOSTFIT[epoch->GNSS2PrintPos[GNSS]][measKindPrint][indexPrintPos]++;
}
 
/*****************************************************************************
 * Name        : printOutput
 * Description : Prints the XYZ and NEU solutions for a station obtained by the
 *               filter, along with the dXYZ, dNEU in relation of the apriori
 *               position (if given), and formal errors of both
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TEpoch  *epochDGNSS             I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 * char *Obsfilename			   I  N/A  Filename of the observation file
 * char *version                   I  N/A  gLAB's version
 *****************************************************************************/
void printOutput (TEpoch *epoch, TEpoch *epochDGNSS, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo, char *Obsfilename, char *version) {
	double						positionNEU[3];
	int							i,j,k;
	int 						indx, indclk, indtrop;
	int							len=0;
	int							solutionModeNum;
	static enum SolutionMode 	PrevSolutionModeKMLDGNSS=DGNSSMode;
	static enum SolutionMode 	PrevSolutionModeKML0DGNSS=DGNSSMode;
	static int 					PrevSolutionModeKMLSBAS=PAMODE; 
	static int 					PrevSolutionModeKML0SBAS=PAMODE; 
	char 						solutionMode[50];
	char						GNSSusedStr[(maxLenghtConstName+1)*MAX_GNSS]; //Max length of constellation + the separator between names


	// First index of XYZ
	indx = unkinfo->par2unk[DR_UNK];
	indclk = unkinfo->par2unk[DT_UNK];
	
	// Obtain NEU coordinates
	XYZ2NEU(&solution->x[indx],positionNEU);
	
	//if ( options->receiverPositionSource == rpRTCMbaseline || options->receiverPositionSource == rpRTCMUserbaseline ) 
	switch(epoch->receiver.OUTPUTDiffFieldsMode) {
		case RTCMBaseline:
			//Compute difference between solution and reference station (DGNSS)
			if ( epochDGNSS->receiver.aproxPosition[0] == EARTH_RADIUS && epochDGNSS->receiver.aproxPosition[1] == 0. && epochDGNSS->receiver.aproxPosition[2] == 0. ) {
				// This is done in order to output dNEU and dXYZ equal to zero when gLAB is still pending to obtain the Reference station coordinates
				for ( i = 0; i < 3; i++ ) {
					epoch->SolErrorNEU[i] = 0.;
					epoch->SolErrorXYZ[i] = 0.;
				}
			} else {
				for (i=0;i<3;i++) {
					epoch->SolErrorNEU[i] = 0;
					epoch->FormalErrorNEU[i] = 0;
					for (j=0;j<3;j++) {
						epoch->SolErrorNEU[i] += (solution->x[indx+j] - epochDGNSS->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
						for (k=0;k<3;k++) {
							epoch->FormalErrorNEU[i] += epoch->receiver.orientation[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientation[k][i];
						}
					}
					epoch->FormalErrorNEU[i] = sqrt(epoch->FormalErrorNEU[i]);
					epoch->SolErrorXYZ[i] = solution->x[indx+i] - epochDGNSS->receiver.aproxPosition[i];
				}
			}
			break;
		// else if ( options.receiverPositionSource == rpCALCULATEREF || options.receiverPositionSource == rpCALCULATERINEXREF || options.receiverPositionSource == rpCALCULATEUSERREF ) 
		case CalculateWithRefFile:
			//Position set by reference file but not used for modelling
			for (i=0;i<3;i++) {
				epoch->SolErrorNEU[i] = 0;
				epoch->FormalErrorNEU[i] = 0;
				for (j=0;j<3;j++) {
					epoch->SolErrorNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
					for (k=0;k<3;k++) {
						epoch->FormalErrorNEU[i] += epoch->receiver.orientationRef[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientationRef[k][i];
					}
				}
				epoch->FormalErrorNEU[i] = sqrt(epoch->FormalErrorNEU[i]);
				epoch->SolErrorXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPositionRef[i];
			}
			break;
		// else if ( options->receiverPositionSource >= rpRTCMRINEXROVER && options->receiverPositionSource != rpRTCMUserbaseline) 
		case RTCMNoBaseline:
			//Compute difference between solution and provided rover position (DGNSS)
			for (i=0;i<3;i++) {
				epoch->SolErrorNEU[i] = 0;
				epoch->FormalErrorNEU[i] = 0;
				for (j=0;j<3;j++) {
					epoch->SolErrorNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRover[j])*epoch->receiver.orientationRover[i][j];
					for (k=0;k<3;k++) {
						epoch->FormalErrorNEU[i] += epoch->receiver.orientationRover[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientationRover[k][i];
					}
				}
				epoch->FormalErrorNEU[i] = sqrt(epoch->FormalErrorNEU[i]);
				epoch->SolErrorXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPositionRover[i];
			}
			break;
		default:
			// Compute:
			//		dNEU differences in relation to a priori position
			//		Formal errors in NEU system. For this:
			//					epoch->FormalErrorNEU = R^-1*feXYZ*R
			//					Being, R the rotation matrix (orientation matrix)
			//						   feXYZ the formal error matrix in XYZ components (the correlation matrix)
			//					As we are only interested in the diagonal of epoch->FormalErrorNEU, only these elements are computed
			for (i=0;i<3;i++) {
				epoch->SolErrorNEU[i] = 0;
				epoch->FormalErrorNEU[i] = 0;
				for (j=0;j<3;j++) {
					epoch->SolErrorNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
					for (k=0;k<3;k++) {
						epoch->FormalErrorNEU[i] += epoch->receiver.orientation[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientation[k][i];
					}
				}
				epoch->FormalErrorNEU[i] = sqrt(epoch->FormalErrorNEU[i]);
				epoch->SolErrorXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPosition[i];
			}
			break;
	}
	
	if ( epoch->receiver.RefPositionAvail==0 ) {
		for (i=0;i<3;i++) {
			epoch->SolErrorNEU[i] = 0.;
			epoch->SolErrorXYZ[i] = 0.;
		}
		epoch->SolError3DNEU=0.;
		epoch->SolHError=0.;
		epoch->SolVError=0.;
		//If using a reference file, it may occur that in an epoch there is no reference position. In this case, do not compute formal error, so the
		//result is consistent with the positioning (otherwise the formal error would have an extra epoch in comparison with positioning error)
		if (options->UseReferenceFile==0) {
			//Check if convergence time has to be computed
			if (options->computeConvergenceTime==1) {
				epoch->FormalError3DNEU=sqrt(epoch->FormalErrorNEU[0]*epoch->FormalErrorNEU[0]+epoch->FormalErrorNEU[1]*epoch->FormalErrorNEU[1]+epoch->FormalErrorNEU[2]*epoch->FormalErrorNEU[2]);
				epoch->FormalErrorHor=sqrt(epoch->FormalErrorNEU[0]*epoch->FormalErrorNEU[0]+epoch->FormalErrorNEU[1]*epoch->FormalErrorNEU[1]);
				epoch->FormalErrorVer=fabs(epoch->FormalErrorNEU[2]);
				//Horizontal Formal Error
				if (options->computeConvTimeFormalErrHor==1) {
					if (epoch->FormalErrorHor<=options->formalErrorThresholdHor) {
						memcpy(&epoch->FirstEpochConvergedFormalErrHor,&epoch->t,sizeof(TTime));
						options->computeConvTimeFormalErrHor=0;
					}
				}
				//Vertical Formal Error
				if (options->computeConvTimeFormalErrVer==1) {
					if (epoch->FormalErrorVer<=options->formalErrorThresholdVer) {
						memcpy(&epoch->FirstEpochConvergedFormalErrVer,&epoch->t,sizeof(TTime));
						options->computeConvTimeFormalErrVer=0;
					}
				}
				//3D Formal Error
				if (options->computeConvTimeFormalErr3D==1) {
					if (epoch->FormalError3DNEU<=options->formalErrorThreshold3D) {
						memcpy(&epoch->FirstEpochConvergedFormalErr3D,&epoch->t,sizeof(TTime));
						options->computeConvTimeFormalErr3D=0;
					}
				}
				//Horizontal Period Formal Error
				if (options->computeConvTimePeriodFormalErrHor==1) {
					if (epoch->FormalErrorHor<=options->formalErrorThresholdHor) {
						if (epoch->FirstEpochConvergedPeriodFormalErrHor.MJDN==-1) {
							//First epoch under threshold or period reseted
							memcpy(&epoch->FirstEpochConvergedPeriodFormalErrHor,&epoch->t,sizeof(TTime));
						} else {
							//Check that the required time under the threshold has passed
							if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErrHor))>=options->minTimeConvergedFormalErrHor) {
								options->computeConvTimePeriodFormalErrHor=0;
							}
						}
					} else {
						//We are over the threshold, reset last time
						epoch->FirstEpochConvergedPeriodFormalErrHor.MJDN=-1;
						epoch->FirstEpochConvergedPeriodFormalErrHor.SoD=0;
					}
				}
				//Vertical Period Formal Error
				if (options->computeConvTimePeriodFormalErrVer==1) {
					if (epoch->FormalErrorVer<=options->formalErrorThresholdVer) {
						if (epoch->FirstEpochConvergedPeriodFormalErrVer.MJDN==-1) {
							//First epoch under threshold or period reseted
							memcpy(&epoch->FirstEpochConvergedPeriodFormalErrVer,&epoch->t,sizeof(TTime));
						} else {
							//Check that the required time under the threshold has passed
							if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErrVer))>=options->minTimeConvergedFormalErrVer) {
								options->computeConvTimePeriodFormalErrVer=0;
							}
						}
					} else {
						//We are over the threshold, reset last time
						epoch->FirstEpochConvergedPeriodFormalErrVer.MJDN=-1;
						epoch->FirstEpochConvergedPeriodFormalErrVer.SoD=0;
					}
				}
				//3D Period Formal Error
				if (options->computeConvTimePeriodFormalErr3D==1) {
					if (epoch->FormalError3DNEU<=options->formalErrorThreshold3D) {
						if (epoch->FirstEpochConvergedPeriodFormalErr3D.MJDN==-1) {
							//First epoch under threshold or period reseted
							memcpy(&epoch->FirstEpochConvergedPeriodFormalErr3D,&epoch->t,sizeof(TTime));
						} else {
							//Check that the required time under the threshold has passed
							if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErr3D))>=options->minTimeConvergedFormalErr3D) {
								options->computeConvTimePeriodFormalErr3D=0;
							}
						}
					} else {
						//We are over the threshold, reset last time
						epoch->FirstEpochConvergedPeriodFormalErr3D.MJDN=-1;
						epoch->FirstEpochConvergedPeriodFormalErr3D.SoD=0;
					}
				}
			}
			if ((options->computeConvTimeFormalErrHor+options->computeConvTimeFormalErrVer+options->computeConvTimeFormalErr3D+
					options->computeConvTimePeriodFormalErrHor+options->computeConvTimePeriodFormalErrVer+options->computeConvTimePeriodFormalErr3D)==0) options->computeConvergenceTime=0;
		}

	} else if (options->computeConvergenceTime==1) {

		epoch->FormalErrorHor=sqrt(epoch->FormalErrorNEU[0]*epoch->FormalErrorNEU[0]+epoch->FormalErrorNEU[1]*epoch->FormalErrorNEU[1]);
		epoch->FormalErrorVer=fabs(epoch->FormalErrorNEU[2]);
		epoch->FormalError3DNEU=sqrt(epoch->FormalErrorNEU[0]*epoch->FormalErrorNEU[0]+epoch->FormalErrorNEU[1]*epoch->FormalErrorNEU[1]+epoch->FormalErrorNEU[2]*epoch->FormalErrorNEU[2]);
		epoch->SolHError=sqrt(epoch->SolErrorNEU[0]*epoch->SolErrorNEU[0]+epoch->SolErrorNEU[1]*epoch->SolErrorNEU[1]);
		epoch->SolVError=fabs(epoch->SolErrorNEU[2]);
		epoch->SolError3DNEU=sqrt(epoch->SolErrorNEU[0]*epoch->SolErrorNEU[0]+epoch->SolErrorNEU[1]*epoch->SolErrorNEU[1]+epoch->SolErrorNEU[2]*epoch->SolErrorNEU[2]);
		//Horizontal Formal Error
		if (options->computeConvTimeFormalErrHor==1) {
			if (epoch->FormalErrorHor<=options->formalErrorThresholdHor) {
				memcpy(&epoch->FirstEpochConvergedFormalErrHor,&epoch->t,sizeof(TTime));
				options->computeConvTimeFormalErrHor=0;
			}
		}
		//Vertical Formal Error
		if (options->computeConvTimeFormalErrVer==1) {
			if (epoch->FormalErrorVer<=options->formalErrorThresholdVer) {
				memcpy(&epoch->FirstEpochConvergedFormalErrVer,&epoch->t,sizeof(TTime));
				options->computeConvTimeFormalErrVer=0;
			}
		}
		//3D Formal Error
		if (options->computeConvTimeFormalErr3D==1) {
			if (epoch->FormalError3DNEU<=options->formalErrorThreshold3D) {
				memcpy(&epoch->FirstEpochConvergedFormalErr3D,&epoch->t,sizeof(TTime));
				options->computeConvTimeFormalErr3D=0;
			}
		}
		//Horizontal Period Formal Error
		if (options->computeConvTimePeriodFormalErrHor==1) {
			if (epoch->FormalErrorHor<=options->formalErrorThresholdHor) {
				if (epoch->FirstEpochConvergedPeriodFormalErrHor.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodFormalErrHor,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErrHor))>=options->minTimeConvergedFormalErrHor) {
						options->computeConvTimePeriodFormalErrHor=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodFormalErrHor.MJDN=-1;
				epoch->FirstEpochConvergedPeriodFormalErrHor.SoD=0;
			}
		}
		//Vertical Period Formal Error
		if (options->computeConvTimePeriodFormalErrVer==1) {
			if (epoch->FormalErrorVer<=options->formalErrorThresholdVer) {
				if (epoch->FirstEpochConvergedPeriodFormalErrVer.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodFormalErrVer,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErrVer))>=options->minTimeConvergedFormalErrVer) {
						options->computeConvTimePeriodFormalErrVer=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodFormalErrVer.MJDN=-1;
				epoch->FirstEpochConvergedPeriodFormalErrVer.SoD=0;
			}
		}
		//3D Period Formal Error
		if (options->computeConvTimePeriodFormalErr3D==1) {
			if (epoch->FormalError3DNEU<=options->formalErrorThreshold3D) {
				if (epoch->FirstEpochConvergedPeriodFormalErr3D.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodFormalErr3D,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodFormalErr3D))>=options->minTimeConvergedFormalErr3D) {
						options->computeConvTimePeriodFormalErr3D=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodFormalErr3D.MJDN=-1;
				epoch->FirstEpochConvergedPeriodFormalErr3D.SoD=0;
			}
		}
		//Horizontal Positioning Error
		if (options->computeConvTimePosErrHor==1) {
			if (epoch->SolHError<=options->positionErrorThresholdHor) {
				memcpy(&epoch->FirstEpochConvergedPosErrHor,&epoch->t,sizeof(TTime));
				options->computeConvTimePosErrHor=0;
			}
		}
		//Vertical Positioning Error
		if (options->computeConvTimePosErrVer==1) {
			if (epoch->SolVError<=options->positionErrorThresholdVer) {
				memcpy(&epoch->FirstEpochConvergedPosErrVer,&epoch->t,sizeof(TTime));
				options->computeConvTimePosErrVer=0;
			}
		}
		//3D Positioning Error
		if (options->computeConvTimePosErr3D==1) {
			if (epoch->SolError3DNEU<=options->positionErrorThreshold3D) {
				memcpy(&epoch->FirstEpochConvergedPosErr3D,&epoch->t,sizeof(TTime));
				options->computeConvTimePosErr3D=0;
			}
		}
		//Horizontal Period Positioning Error
		if (options->computeConvTimePeriodPosErrHor==1) {
			if (epoch->SolHError<=options->positionErrorThresholdHor) {
				if (epoch->FirstEpochConvergedPeriodPosErrHor.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodPosErrHor,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodPosErrHor))>=options->minTimeConvergedPosErrHor) {
						options->computeConvTimePeriodPosErrHor=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodPosErrHor.MJDN=-1;
				epoch->FirstEpochConvergedPeriodPosErrHor.SoD=0;
			}
		}
		//Vertical Period Positioning Error
		if (options->computeConvTimePeriodPosErrVer==1) {
			if (epoch->SolVError<=options->positionErrorThresholdVer) {
				if (epoch->FirstEpochConvergedPeriodPosErrVer.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodPosErrVer,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodPosErrVer))>=options->minTimeConvergedPosErrVer) {
						options->computeConvTimePeriodPosErrVer=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodPosErrVer.MJDN=-1;
				epoch->FirstEpochConvergedPeriodPosErrVer.SoD=0;
			}
		}
		//3D Period Positioning Error
		if (options->computeConvTimePeriodPosErr3D==1) {
			if (epoch->SolError3DNEU<=options->positionErrorThreshold3D) {
				if (epoch->FirstEpochConvergedPeriodPosErr3D.MJDN==-1) {
					//First epoch under threshold or period reseted
					memcpy(&epoch->FirstEpochConvergedPeriodPosErr3D,&epoch->t,sizeof(TTime));
				} else {
					//Check that the required time under the threshold has passed
					if (fabs(tdiff(&epoch->t,&epoch->FirstEpochConvergedPeriodPosErr3D))>=options->minTimeConvergedPosErr3D) {
						options->computeConvTimePeriodPosErr3D=0;
					}
				}
			} else {
				//We are over the threshold, reset last time
				epoch->FirstEpochConvergedPeriodPosErr3D.MJDN=-1;
				epoch->FirstEpochConvergedPeriodPosErr3D.SoD=0;
			}
		}
		if ((options->computeConvTimeFormalErrHor+options->computeConvTimeFormalErrVer+options->computeConvTimeFormalErr3D+
				options->computeConvTimePeriodFormalErrHor+options->computeConvTimePeriodFormalErrVer+options->computeConvTimePeriodFormalErr3D+
				options->computeConvTimePosErrHor+options->computeConvTimePosErrVer+options->computeConvTimePosErr3D+
				options->computeConvTimePeriodPosErrHor+options->computeConvTimePeriodPosErrVer+options->computeConvTimePeriodPosErr3D)==0) options->computeConvergenceTime=0;
	} else {
		epoch->SolError3DNEU=sqrt(epoch->SolErrorNEU[0]*epoch->SolErrorNEU[0]+epoch->SolErrorNEU[1]*epoch->SolErrorNEU[1]+epoch->SolErrorNEU[2]*epoch->SolErrorNEU[2]);
		epoch->SolHError=sqrt(epoch->SolErrorNEU[0]*epoch->SolErrorNEU[0]+epoch->SolErrorNEU[1]*epoch->SolErrorNEU[1]);
		epoch->SolVError=fabs(epoch->SolErrorNEU[2]);
	}

	if (options->printOutput) {
		if(options->printV5format==0) {
			//Create the string with the list constellations used
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->constellationUsed[i]==1) {
					len+=sprintf(&GNSSusedStr[len],"%3s+",gnsstype2gnssstr(i));
				}
			}
			GNSSusedStr[len-1]='\0'; //Remove the last "+"

			fprintf(options->outFileStream,"OUTPUT    %29s %1d %1d %2d %1d %s %9.4f %14.4f %14.4f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %14.9f %14.9f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %3s %14.4f %10.4f %9.4f %9.4f %9.4f %9.4f %9.4f",
			/*2*/		epoch->tSoDHourStr,
			/*3*/		/*DoY*/
			/*4*/		/*SoD*/
			/*5*/		/*HH:MM:SS.zz*/
			/*6*/		options->solutionMode,
			/*7*/		epoch->direction,
			/*8*/		epoch->numSatSolutionFilter,
			/*9*/		epoch->numConstellationsUsed,
			/*10*/		GNSSusedStr,
			/*11*/		solution->dop,
			/*12*/		solution->x[indx+0],
			/*13*/		solution->x[indx+1],
			/*14*/		solution->x[indx+2],
			/*15*/		epoch->SolErrorXYZ[0],
			/*16*/		epoch->SolErrorXYZ[1],
			/*17*/		epoch->SolErrorXYZ[2],
			/*18*/		sqrt(solution->correlations[m2v(indx+0,indx+0)]),
			/*19*/		sqrt(solution->correlations[m2v(indx+1,indx+1)]),
			/*20*/		sqrt(solution->correlations[m2v(indx+2,indx+2)]),
			/*21*/		positionNEU[0]*r2d, // Latitude
			/*22*/		positionNEU[1]*r2d, // Longitude
			/*23*/		positionNEU[2],     // Height
			/*24*/		epoch->SolErrorNEU[0],			// dNorth
			/*25*/		epoch->SolErrorNEU[1],			// dEast
			/*26*/		epoch->SolErrorNEU[2],			// dUp
			/*27*/		epoch->FormalErrorNEU[0],
			/*28*/		epoch->FormalErrorNEU[1],
			/*29*/		epoch->FormalErrorNEU[2],
			/*30*/		epoch->SolHError,
			/*31*/		epoch->SolVError, //Absolute value of the error in Up component
			/*32*/		epoch->SolError3DNEU,
			/*33*/		gnsstype2gnssstr(epoch->ReferenceGNSSClock),
			/*34*/		solution->x[indclk]*options->ClktimeFactor,
			/*35*/		sqrt(solution->correlations[m2v(indclk,indclk)])*options->ClktimeFactor,
			/*36*/		solution->GDOP,
			/*37*/		solution->PDOP,
			/*38*/		solution->TDOP,				
			/*39*/		solution->HDOP,
			/*40*/		solution->VDOP);
			if (options->estimateTroposphere) {
				indtrop = unkinfo->par2unk[TROP_UNK];
				fprintf(options->outFileStream," %10.4f %10.4f %10.4f\n",
			/*41*/		solution->x[indtrop],
			/*42*/		solution->x[indtrop] - epoch->ZTD,
			/*43*/		sqrt(solution->correlations[m2v(indtrop,indtrop)]));
			} else {
				fprintf(options->outFileStream," %10.4f %10.4f %10.4f\n", 
			/*41*/		0.0, 
			/*42*/		0.0, 
			/*43*/		0.0);
			}
		} else {
			//solutionMode value has changed order, set it to the old values.
			//For new modes, set them after DGNSS
			switch(options->solutionMode) {
				case SBAS1FMode:
					solutionModeNum=2;
					break;
				case DGNSSMode:
					solutionModeNum=3;
					break;
				case SBASDFMCMode:
					solutionModeNum=4;
					break;
				case PPPFixAmbMode:
					solutionModeNum=5;
					break;
				case FPPPModeFloatAmb:
					solutionModeNum=6;
					break;
				case FPPPModeFixAmb:
					solutionModeNum=7;
					break;
				default:
					solutionModeNum=options->solutionMode;
					break;
			}

			fprintf(options->outFileStream,"OUTPUT    %17s %9.4f %14.4f %14.4f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %14.9f %14.9f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %9.4f %9.4f %9.4f %9.4f %9.4f",
			/*2*/		epoch->tStr,
			/*3*/		/*DoY*/
			/*4*/		/*SoD*/
			/*5*/		solution->dop,
			/*6*/		solution->x[indx+0],
			/*7*/		solution->x[indx+1],
			/*8*/		solution->x[indx+2],
			/*9*/		epoch->SolErrorXYZ[0],
			/*10*/		epoch->SolErrorXYZ[1],
			/*11*/		epoch->SolErrorXYZ[2],
			/*12*/		sqrt(solution->correlations[m2v(indx+0,indx+0)]),
			/*13*/		sqrt(solution->correlations[m2v(indx+1,indx+1)]),
			/*14*/		sqrt(solution->correlations[m2v(indx+2,indx+2)]),
			/*15*/		positionNEU[0]*r2d, // Latitude
			/*16*/		positionNEU[1]*r2d, // Longitude
			/*17*/		positionNEU[2],     // Height
			/*18*/		epoch->SolErrorNEU[0],			// dNorth
			/*19*/		epoch->SolErrorNEU[1],			// dEast
			/*20*/		epoch->SolErrorNEU[2],			// dUp
			/*21*/		epoch->FormalErrorNEU[0],
			/*22*/		epoch->FormalErrorNEU[1],
			/*23*/		epoch->FormalErrorNEU[2],
			/*24*/		solution->GDOP,
			/*25*/		solution->PDOP,
			/*26*/		solution->TDOP,				
			/*27*/		solution->HDOP,
			/*28*/		solution->VDOP);
			if (options->estimateTroposphere) {
				indtrop = unkinfo->par2unk[TROP_UNK];
				fprintf(options->outFileStream," %10.4f %10.4f %10.4f %2d %1d\n",
			/*29*/		solution->x[indtrop],
			/*30*/		solution->x[indtrop] - epoch->ZTD,
			/*31*/		sqrt(solution->correlations[m2v(indtrop,indtrop)]),
			/*32*/		epoch->numSatSolutionFilter,
			/*33*/		solutionModeNum);
			} else {
				fprintf(options->outFileStream," %10.4f %10.4f %10.4f %2d %1d\n", 
			/*29*/		0.0, 
			/*30*/		0.0, 
			/*31*/		0.0,
			/*32*/		epoch->numSatSolutionFilter,
			/*33*/		solutionModeNum);
			}
		}
	}

	if (options->fdkml!=NULL || options->fdkml0!=NULL) {
		sprintf(solutionMode,"%s",SolutionModeNum2SolutionModeChar(options->solutionMode));
		//if((options->DGNSS && options->solutionMode==DGNSSMode) || options->DGNSS==0) {
			//Allocate memory
			epoch->KMLData=realloc(epoch->KMLData,sizeof(double*)*(epoch->numKMLData+1));
			epoch->KMLData[epoch->numKMLData]=malloc(sizeof(double)*3);
			epoch->KMLTime=realloc(epoch->KMLTime,sizeof(TTime)*(epoch->numKMLData+1));

			//Save data
			epoch->KMLData[epoch->numKMLData][0]=positionNEU[0]*r2d;
			epoch->KMLData[epoch->numKMLData][1]=positionNEU[1]*r2d;
			epoch->KMLData[epoch->numKMLData][2]=positionNEU[2];
			memcpy(&epoch->KMLTime[epoch->numKMLData],&epoch->t,sizeof(TTime));
			epoch->numKMLData++;
		//}

	}

	//Print KML file if necessary
	if (options->fdkml!=NULL) {
		if ( (PrevSolutionModeKMLDGNSS!=options->solutionMode && options->DGNSS) || (PrevSolutionModeKMLSBAS!=options->precisionapproach && (options->SBAScorrections>=SBAS1Fused && options->switchmode==1)) ) {
			//Solution changed to SPP mode
			fprintf(options->fdkml,"        </coordinates>\n");
			fprintf(options->fdkml,"      </LineString>\n");
			fprintf(options->fdkml,"    </Placemark>\n");
			fprintf(options->fdkml,"    <Placemark>\n");
			if ( options->solutionMode==SPPMode) {
				fprintf(options->fdkml,"      <name>Coordinates for file %s [Switched to SPP solution]</name>\n",Obsfilename);
				fprintf(options->fdkml,"      <description>Coordinates computed by gLAB v%s in %s mode [Switched to SPP solution]</description>\n",version,solutionMode);
				fprintf(options->fdkml,"      <styleUrl>#redLine</styleUrl>\n");
			} else if (options->DGNSS) {
				fprintf(options->fdkml,"      <name>Coordinates for file %s [Switched to DGNSS solution]</name>\n",Obsfilename);
				fprintf(options->fdkml,"      <description>Coordinates computed by gLAB v%s in %s mode [Switched to DGNSS solution]</description>\n",version,solutionMode);
				fprintf(options->fdkml,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
			} else if (options->precisionapproach==NPAMODE) {
				fprintf(options->fdkml,"      <name>Coordinates for file %s [Switched to NPA mode]</name>\n",Obsfilename);
				fprintf(options->fdkml,"      <description>Coordinates computed by gLAB v%s in SBAS NPA mode [Switched to NPA mode]</description>\n",version);
				fprintf(options->fdkml,"      <styleUrl>#redLine</styleUrl>\n");
			} else {
				fprintf(options->fdkml,"      <name>Coordinates for file %s [Switched to PA mode]</name>\n",Obsfilename);
				fprintf(options->fdkml,"      <description>Coordinates computed by gLAB v%s in SBAS PA mode [Switched to DGNSS solution]</description>\n",version);
				fprintf(options->fdkml,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
			}
			fprintf(options->fdkml,"      <LineString>\n");
			fprintf(options->fdkml,"        <extrude>0</extrude>\n");
			fprintf(options->fdkml,"        <tessellate>1</tessellate>\n");
			fprintf(options->fdkml,"        <altitudeMode>absolute</altitudeMode>\n");
			fprintf(options->fdkml,"        <coordinates>\n");
		}	
		fprintf(options->fdkml,"          %.9f,%.9f,%.9f\n",positionNEU[1]/d2r,positionNEU[0]/d2r,positionNEU[2]-(options->KMLEGM96height==1?getEGM96Height(epoch->KMLData[epoch->numKMLData-1]):0.));
		PrevSolutionModeKMLDGNSS=options->solutionMode;
		PrevSolutionModeKMLSBAS=options->precisionapproach;
	}

	//Print KML (ground projection) file if necessary
	if (options->fdkml0!=NULL) {
		if ( (PrevSolutionModeKML0DGNSS!=options->solutionMode && options->DGNSS)  || (PrevSolutionModeKML0SBAS!=options->precisionapproach && (options->SBAScorrections>=SBAS1Fused && options->switchmode==1)) ) {
			//Solution changed to SPP mode
			fprintf(options->fdkml0,"        </coordinates>\n");
			fprintf(options->fdkml0,"      </LineString>\n");
			fprintf(options->fdkml0,"    </Placemark>\n");
			fprintf(options->fdkml0,"    <Placemark>\n");
			if ( options->solutionMode==SPPMode) {
				fprintf(options->fdkml0,"      <name>Coordinates for file %s [Switched to SPP solution]</name>\n",Obsfilename);
				fprintf(options->fdkml0,"      <description>Coordinates computed by gLAB v%s in %s mode [Switched to SPP solution]</description>\n",version,solutionMode);
				fprintf(options->fdkml0,"      <styleUrl>#redLine</styleUrl>\n");
			} else if (options->DGNSS) {
				fprintf(options->fdkml0,"      <name>Coordinates for file %s [Switched to DGNSS solution]</name>\n",Obsfilename);
				fprintf(options->fdkml0,"      <description>Coordinates computed by gLAB v%s in %s mode (ground projection) [Switched to DGNSS solution]</description>\n",version,solutionMode);
				fprintf(options->fdkml0,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
			} else if (options->precisionapproach==NPAMODE) {
				fprintf(options->fdkml0,"      <name>Coordinates for file %s [Switched to NPA mode]</name>\n",Obsfilename);
				fprintf(options->fdkml0,"      <description>Coordinates computed by gLAB v%s in SBAS NPA mode (ground projection) [Switched to NPA mode]</description>\n",version);
				fprintf(options->fdkml0,"      <styleUrl>#redLine</styleUrl>\n");
			} else {
				fprintf(options->fdkml0,"      <name>Coordinates for file %s [Switched to PA mode]</name>\n",Obsfilename);
				fprintf(options->fdkml0,"      <description>Coordinates computed by gLAB v%s in SBAS PA mode (ground projection) [Switched to DGNSS solution]</description>\n",version);
				fprintf(options->fdkml0,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
			}
			fprintf(options->fdkml0,"      <LineString>\n");
			fprintf(options->fdkml0,"        <extrude>0</extrude>\n");
			fprintf(options->fdkml0,"        <tessellate>1</tessellate>\n");
			fprintf(options->fdkml0,"        <altitudeMode>clampToGround</altitudeMode>\n");
			fprintf(options->fdkml0,"        <coordinates>\n");
		}	
		fprintf(options->fdkml0,"          %.9f,%.9f,0.00\n",positionNEU[1]/d2r,positionNEU[0]/d2r);
		PrevSolutionModeKML0DGNSS=options->solutionMode;
		PrevSolutionModeKML0SBAS=options->precisionapproach;
	}
}

/*****************************************************************************
 * Name        : printSatDiff
 * Description : Prints the difference between two different satellites at a 
 *               specific time. Provides the difference in SISRE, SISRE 
 *               orbit-only, 3D orbit, clock and radial, along and cross-track
 *               components
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char **tStr                     I  N/A  Array with time in strings format (new and old format)
 * enum GNSSystem  GNSS            I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN satellite identifier
 * double  SISREDiff               I    m  Signal-in-Space Range Error difference
 * double  OrbDiff                 I    m  SISRE orbit-only difference
 * double  Orb3DDiff               I    m  3D orbit difference
 * double  ClkDiff                 I    m  Clock difference
 * double  DCBDiff                 I    m  DCB difference (for GPS and QZSS only)
 * double  *posDiff                I    m  Radial, along- and cross-track position difference 
 * double  *posDiffXYZ             I    m  X Y Z position difference 
 * TBRDCblock *block[2]            I  N/A  Broadcast block for both satellites (if broadcast are used)
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatDiff (char **tStr, enum GNSSystem GNSS, int PRN, double SISREDiff, double OrbDiff, double Orb3DDiff, double ClkDiff, double DCBDiff, double *posDiff, double *posDiffXYZ, TBRDCblock *block[2], TOptions *options) {

	char 	Ephtype1[20],Ephtype2[20],EphHealth1[30],EphHealth2[30];
	int 	i,IOD1,IOD2,len;

	if (options->printSatDiff==0) return;

	if (options->printV5format==0) {
		if (block[0]!=NULL) {
			strcpy(Ephtype1,BRDCType2String(GNSS,block[0]->BRDCtype));
			IOD1=block[0]->IODE;
			strcpy(EphHealth1,BRDCHealth2String(block[0]));
			len=(int)strlen(EphHealth1);
			for(i=0;i<len;i++) {
				if (EphHealth1[i]==' ') EphHealth1[i]='_';
			}
		} else {
			strcpy(Ephtype1,"SP3");
			IOD1=-1;
			EphHealth1[0]='\0';
		}
		
		if (block[1]!=NULL) {
			strcpy(Ephtype2,BRDCType2String(GNSS,block[1]->BRDCtype));
			IOD2=block[1]->IODE;
			strcpy(EphHealth2,BRDCHealth2String(block[1]));
			len=(int)strlen(EphHealth2);
			for(i=0;i<len;i++) {
				if (EphHealth2[i]==' ') EphHealth2[i]='_';
			}
		} else {
			strcpy(Ephtype2,"SP3");
			IOD2=-1;
			EphHealth2[0]='\0';
		}
	
		fprintf(options->outFileStream,"SATDIFF %29s %3s %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %9s-%-9s %4d %4d %s %s\n",
		/*2*/	tStr[0],
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	/*HH:MM:SS.zz*/
		/*6*/	gnsstype2gnssstr(GNSS),
		/*7*/	PRN,
		/*8*/	SISREDiff,
		/*9*/	OrbDiff,
		/*10*/	Orb3DDiff,
		/*11*/	ClkDiff*options->ClktimeFactor,
		/*12*/	DCBDiff*options->ClktimeFactor,
		/*13*/	posDiff[2],
		/*14*/	posDiff[0],
		/*15*/	posDiff[1],
		/*16*/	posDiffXYZ[0],
		/*17*/	posDiffXYZ[1],
		/*18*/	posDiffXYZ[2],
		/*19*/	Ephtype1,
		      	Ephtype2,
		/*20*/	IOD1,
		/*21*/	IOD2,
		/*22*/	EphHealth1,
		/*23*/	EphHealth2);
	} else {
		fprintf(options->outFileStream,"SATDIFF %17s %3s %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
		/*2*/	tStr[1],
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	gnsstype2gnssstr(GNSS),
		/*6*/	PRN,
		/*7*/	SISREDiff,
		/*8*/	OrbDiff,
		/*9*/	Orb3DDiff,
		/*10*/	ClkDiff,
		/*11*/	posDiff[2],
		/*12*/	posDiff[0],
		/*13*/	posDiff[1],
		/*14*/	posDiffXYZ[0],
		/*15*/	posDiffXYZ[1],
		/*16*/	posDiffXYZ[2]);
	}
}

/*****************************************************************************
 * Name        : printSatStat
 * Description : Prints the statistics of differences between two different 
 *               satellites. Provides the difference in SISRE, SISRE orbit-only, 
 *               3D orbit, clock and radial, along and cross-track components
 *               NOTE: The absolute values for the values in the square root are
 *                  for edge casese, where stddev is 0, and mean = rms, and due
 *                  to decimals sometimes the substract is negative
 * Parameters  :
 * Name                           |Da|Unit|Description
 * enum GNSSystem  GNSS            I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN satellite identifier
 * TStat  statSISRE                I  N/A  Signal-in-Space Range Error statistics
 * TStat  statOrb                  I  N/A  SISRE orbit-only statistics
 * TStat  stat3D                   I  N/A  3D orbit statistics
 * TStat  statClk                  I  N/A  Clock statistics
 * TStat  statDCB                  I  N/A  DCB statistics (GPS and QZSS only)
 * TStat  statRadOrb               I  N/A  Radial position statistics 
 * TStat  statAloOrb               I  N/A  Along-track position statistics 
 * TStat  statCroOrb               I  N/A  Cross-track position statistics 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatStat (enum GNSSystem GNSS, int PRN, TStat statSISRE, TStat statOrb, TStat stat3D, TStat statClk, TStat statDCB, TStat statRadOrb, TStat statAloOrb, TStat statCroOrb, TOptions *options) {
	if (options->printSatStat && (statSISRE.n != 0)) {
		if (options->printV5format==0) {
			fprintf(options->outFileStream,"SATSTAT %3s %2d %4d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
			/*2*/	gnsstype2gnssstr(GNSS),
			/*3*/	PRN,
			/*4*/	statSISRE.n,
			/*5*/	statSISRE.mean,
			/*6*/	sqrt(statSISRE.mean2),
			/*7*/	sqrt(fabs(statSISRE.mean2 - statSISRE.mean*statSISRE.mean)),
			/*8*/	statOrb.mean,
			/*9*/	sqrt(statOrb.mean2),
			/*10*/	sqrt(fabs(statOrb.mean2 - statOrb.mean*statOrb.mean)),
			/*11*/	stat3D.mean,
			/*12*/	sqrt(stat3D.mean2),
			/*13*/	sqrt(fabs(stat3D.mean2 - stat3D.mean*stat3D.mean)),
			/*14*/	statClk.mean*options->ClktimeFactor,
			/*15*/	sqrt(statClk.mean2)*options->ClktimeFactor,
			/*16*/	sqrt(fabs(statClk.mean2 - statClk.mean*statClk.mean))*options->ClktimeFactor,
			/*17*/	statDCB.mean*options->ClktimeFactor,
			/*18*/	sqrt(statDCB.mean2)*options->ClktimeFactor,
			/*19*/	sqrt(fabs(statDCB.mean2 - statDCB.mean*statDCB.mean))*options->ClktimeFactor,
			/*20*/	statRadOrb.mean,
			/*21*/	sqrt(statRadOrb.mean2),
			/*22*/	sqrt(fabs(statRadOrb.mean2 - statRadOrb.mean*statRadOrb.mean)),
			/*23*/	statAloOrb.mean,
			/*24*/	sqrt(statAloOrb.mean2),
			/*25*/	sqrt(fabs(statAloOrb.mean2 - statAloOrb.mean*statAloOrb.mean)),
			/*26*/	statCroOrb.mean,
			/*27*/	sqrt(statCroOrb.mean2),
			/*28*/	sqrt(fabs(statCroOrb.mean2 - statCroOrb.mean*statCroOrb.mean))); 
		} else {
			fprintf(options->outFileStream,"SATSTAT %3s %2d %4d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
			/*2*/	gnsstype2gnssstr(GNSS),
			/*3*/	PRN,
			/*4*/	statSISRE.n,
			/*5*/	statSISRE.mean,
			/*6*/	sqrt(statSISRE.mean2),
			/*7*/	sqrt(fabs(statSISRE.mean2 - statSISRE.mean*statSISRE.mean)),
			/*8*/	statOrb.mean,
			/*9*/	sqrt(statOrb.mean2),
			/*10*/	sqrt(fabs(statOrb.mean2 - statOrb.mean*statOrb.mean)),
			/*11*/	stat3D.mean,
			/*12*/	sqrt(stat3D.mean2),
			/*13*/	sqrt(fabs(stat3D.mean2 - stat3D.mean*stat3D.mean)),
			/*14*/	statClk.mean,
			/*15*/	sqrt(statClk.mean2),
			/*16*/	sqrt(fabs(statClk.mean2 - statClk.mean*statClk.mean)),
			/*17*/	statRadOrb.mean,
			/*18*/	sqrt(statRadOrb.mean2),
			/*19*/	sqrt(fabs(statRadOrb.mean2 - statRadOrb.mean*statRadOrb.mean)),
			/*20*/	statAloOrb.mean,
			/*21*/	sqrt(statAloOrb.mean2),
			/*22*/	sqrt(fabs(statAloOrb.mean2 - statAloOrb.mean*statAloOrb.mean)),
			/*23*/	statCroOrb.mean,
			/*24*/	sqrt(statCroOrb.mean2),
			/*25*/	sqrt(fabs(statCroOrb.mean2 - statCroOrb.mean*statCroOrb.mean))); 
		}
	}
}

/*****************************************************************************
 * Name        : printSatStatTot
 * Description : Prints the summary statistics of all diferences between two
 *                 orbit and clock product comparison
 *               NOTE: The absolute values for the values in the square root are
 *                  for edge casese, where stddev is 0, and mean = rms, and due
 *                  to decimals sometimes the substract is negative
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TStat  statSISRE                I  N/A  Signal-in-Space Range Error statistics
 * TStat  statOrb                  I  N/A  SISRE orbit-only statistics
 * TStat  stat3D                   I  N/A  3D orbit statistics
 * TStat  statClk                  I  N/A  Clock statistics
 * TStat  statDCB                  I  N/A  DCB statistics (GPS and QZSS only)
 * TStat  statRadOrb               I  N/A  Radial position statistics 
 * TStat  statAloOrb               I  N/A  Along-track position statistics 
 * TStat  statCroOrb               I  N/A  Cross-track position statistics 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatStatTot (TStat statSISRETot, TStat statOrbTot, TStat stat3DTot, TStat statClkTot, TStat statDCBTot, TStat statRadOrbTot, TStat statAloOrbTot, TStat statCroOrbTot, TOptions *options) {
	if (options->printSatStatTot && statSISRETot.n != 0) {
		if (options->printV5format==0) {
			fprintf(options->outFileStream,"SATSTATTOT %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
			/*2*/	statSISRETot.n,
			/*3*/	statSISRETot.mean,
			/*4*/	sqrt(statSISRETot.mean2),
			/*5*/	sqrt(fabs(statSISRETot.mean2 - statSISRETot.mean*statSISRETot.mean)),
			/*6*/	statOrbTot.mean,
			/*7*/	sqrt(statOrbTot.mean2),
			/*8*/	sqrt(fabs(statOrbTot.mean2 - statOrbTot.mean*statOrbTot.mean)),
			/*9*/	stat3DTot.mean,
			/*10*/	sqrt(stat3DTot.mean2),
			/*11*/	sqrt(fabs(stat3DTot.mean2 - stat3DTot.mean*stat3DTot.mean)),
			/*12*/	statClkTot.mean*options->ClktimeFactor,
			/*13*/	sqrt(statClkTot.mean2)*options->ClktimeFactor,
			/*14*/	sqrt(fabs(statClkTot.mean2 - statClkTot.mean*statClkTot.mean))*options->ClktimeFactor,
			/*15*/	statDCBTot.mean*options->ClktimeFactor,
			/*16*/	sqrt(statDCBTot.mean2)*options->ClktimeFactor,
			/*17*/	sqrt(fabs(statDCBTot.mean2 - statClkTot.mean*statDCBTot.mean))*options->ClktimeFactor,
			/*18*/	statRadOrbTot.mean,
			/*19*/	sqrt(statRadOrbTot.mean2),
			/*20*/	sqrt(fabs(statRadOrbTot.mean2 - statRadOrbTot.mean*statRadOrbTot.mean)),
			/*21*/	statAloOrbTot.mean,
			/*22*/	sqrt(statAloOrbTot.mean2),
			/*23*/	sqrt(fabs(statAloOrbTot.mean2 - statAloOrbTot.mean*statAloOrbTot.mean)),
			/*24*/	statCroOrbTot.mean,
			/*25*/	sqrt(statCroOrbTot.mean2),
			/*26*/	sqrt(fabs(statCroOrbTot.mean2 - statCroOrbTot.mean*statCroOrbTot.mean)));
		} else {
			fprintf(options->outFileStream,"SATSTATTOT %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
			/*2*/	statSISRETot.n,
			/*3*/	statSISRETot.mean,
			/*4*/	sqrt(statSISRETot.mean2),
			/*5*/	sqrt(fabs(statSISRETot.mean2 - statSISRETot.mean*statSISRETot.mean)),
			/*6*/	statOrbTot.mean,
			/*7*/	sqrt(statOrbTot.mean2),
			/*8*/	sqrt(fabs(statOrbTot.mean2 - statOrbTot.mean*statOrbTot.mean)),
			/*9*/	stat3DTot.mean,
			/*10*/	sqrt(stat3DTot.mean2),
			/*11*/	sqrt(fabs(stat3DTot.mean2 - stat3DTot.mean*stat3DTot.mean)),
			/*12*/	statClkTot.mean,
			/*13*/	sqrt(statClkTot.mean2),
			/*14*/	sqrt(fabs(statClkTot.mean2 - statClkTot.mean*statClkTot.mean)),
			/*15*/	statRadOrbTot.mean,
			/*16*/	sqrt(statRadOrbTot.mean2),
			/*17*/	sqrt(fabs(statRadOrbTot.mean2 - statRadOrbTot.mean*statRadOrbTot.mean)),
			/*18*/	statAloOrbTot.mean,
			/*19*/	sqrt(statAloOrbTot.mean2),
			/*20*/	sqrt(fabs(statAloOrbTot.mean2 - statAloOrbTot.mean*statAloOrbTot.mean)),
			/*21*/	statCroOrbTot.mean,
			/*22*/	sqrt(statCroOrbTot.mean2),
			/*23*/	sqrt(fabs(statCroOrbTot.mean2 - statCroOrbTot.mean*statCroOrbTot.mean)));
		}
	}
}

/*****************************************************************************
 * Name        : printSatPvt
 * Description : Prints the position, velocity (in ECEF or inertial) 
 *                 and clock correction for one satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * char **tStr                     I  N/A  Array with time in strings format (new and old format)
 * enum GNSSystem  GNSS            I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN satellite identifier
 * double  *position               I    m  XYZ position of the satellite
 * double  *velocity               I  m/s  VXVYVZ velocity of the satellite
 * double  *positionNEU            I    m  NEU position of the satellite
 * double  clockCorr               I    m  Clock offset of the satellite
 * double  elevation               I  rad  Satellite elevation w.r.t to user defined position
 * double  azimuth                 I  rad  Satellite azimuth w.r.t to user defined position
 * TConstellation  *constellation  I  N/A  TConstellation structure where 
 *                                          satellite data is stored
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatPvt (TTime *t, char **tStr, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *positionNEU, double clockCorr, double elevation, double azimuth, TBRDCblock *block, TConstellation *constellation, TOptions *options) {

	char 					Ephtype[20],EphHealth[30];
	int						IOD,i,len;
	int						SVN;
	enum SatelliteBlock		satBlock;	

	if (options->printSatPvt==0) return;

	if (options->printV5format==0) { 
		if (block!=NULL) {
			strcpy(Ephtype,BRDCType2String(GNSS,block->BRDCtype));
			IOD=block->IODE;
			strcpy(EphHealth,BRDCHealth2String(block));
			len=(int)strlen(EphHealth);
			for(i=0;i<len;i++) {
				if (EphHealth[i]==' ') EphHealth[i]='_';
			}
		} else {
			strcpy(Ephtype,"SP3");
			IOD=-1;
			EphHealth[0]='-';
			EphHealth[1]='\0';
		}

		//Get satellite block and SVN
		if (constellation->satLastUsed[GNSS][PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,t,constellation);
				if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
					satBlock=constellation->satLastUsed[GNSS][PRN]->block;
					SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			}
		}
		

		fprintf(options->outFileStream,"SATPVT %29s %3s %2d %-15s %4d %8.3f %8.3f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.9f %14.9f %14.4f %17.6f %9s %4d %s\n",
		/*2*/	tStr[0],
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	/*HH:MM:SS.zz*/
		/*6*/	gnsstype2gnssstr(GNSS),
		/*7*/	PRN,
		/*8*/	satblock2satblockstr(satBlock),
		/*9*/	SVN,
		/*10*/	elevation*r2d,
		/*11*/	azimuth*r2d,
		/*12*/	position[0],
		/*13*/	position[1],
		/*14*/	position[2],
		/*15*/	velocity[0],
		/*16*/	velocity[1],
		/*17*/	velocity[2],
		/*18*/	positionNEU[0]*r2d,
		/*19*/	positionNEU[1]*r2d,
		/*20*/	positionNEU[2],
		/*21*/	clockCorr*options->ClktimeFactor,
		/*22*/	Ephtype,
		/*23*/	IOD,
		/*24*/	EphHealth);
	} else {
		fprintf(options->outFileStream,"SATPVT %17s %3s %2d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %17.6f\n",
		/*2*/	tStr[1],
		/*3*/	/*DoY*/
		/*4*/	/*SoD*/
		/*5*/	gnsstype2gnssstr(GNSS),
		/*6*/	PRN,
		/*7*/	position[0],
		/*8*/	position[1],
		/*9*/	position[2],
		/*10*/	velocity[0],
		/*11*/	velocity[1],
		/*12*/	velocity[2],
		/*13*/	clockCorr);
	}
}

/*****************************************************************************
 * Name        : writeSBASfiles
 * Description : Checks which SBAS data files have to be written and
 *               calls the function to write the current line to them
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char **filelist                 I  N/A  List of filenames for writing data
 * char **line                     I  N/A  Data lines to be written
 * int	*linelen                   I  N/A  Length of each line
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int header                      I  N/A  Indicates if the current lines
 *                                         are from a header
 *                                         0 => Not a header line
 *                                         1 => Header line
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                         SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * int decoderesult                I  N/A  Result of the message decodification
 * int decodedmessagetype          I  N/A  Message type decoded from hexadecimal message
 * int *prevday                    O  N/A  Indicates if a RINEX H file from the
 *                                         previous day has been written
 * TSBASblock  *sbasblock          I  N/A  TSBASblock struct
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeSBASfiles (FILE  **fdlist, FILE  *readfd, char **filelist, char **line, int *linelen, int numlines, int header, int sourcefile, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options) {

	if(decoderesult<0) {
		//An incorrect message has been detected. 
		//Incorrect messages will be written to converted EMS or RINEX-B files, as the behaviour
		// of reading incorrect messages or not reading any message is different.
		//For pegasus, the data will not be written but it will be logged in the "SBAS Message Transmission Sequence File"
		//Furthermore, a log will be created with the incorrect messages
					
		if(options->writePegasusfile==1) {
			writePegasusfiles(fdlist,readfd,filelist,line,linelen,numlines,sourcefile,header,decoderesult,decodedmessagetype,prevday,sbasblock,options);
		}

		writeLogfile(fdlist,readfd,filelist[fdLOGFILE],line,linelen,numlines,sourcefile,decoderesult,sbasblock,options);			
	}

	//Check if we have to write a new RINEX-B file
	if(options->writeRinexBfile==1) {
		writeRinexBfile(fdlist,readfd,filelist[fdRINEXB],line,linelen,numlines,header,sourcefile,sbasblock,options);
	}

	//Check if we have to write a EMS file
	if(options->writeEMSfile==1) {
		writeEMSfile(fdlist,readfd,filelist[fdEMS],line,linelen,numlines,header,sourcefile,sbasblock,options);

	}

	//Check if we have to write a Pegasus file (taking out the messages with failed CRC)
	if(options->writePegasusfile==1 && decoderesult>=0) {
		writePegasusfiles(fdlist,readfd,filelist,line,linelen,numlines,sourcefile,header,decoderesult,decodedmessagetype,prevday,sbasblock,options);
	}
}



/*****************************************************************************
 * Name        : writeLogfile
 * Description : Writes corrupted messages to log file in EMS format along with
 *                the detected error at the begining of each message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char *filename                  I  N/A  Filename where the data is saved
 * char **line                     I  N/A  Data lines to be written
 * int	*linelen                   I  N/A  Length of each line
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                         SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * int decoderesult                I  N/A  Indicates the result of message decoding
 * TSBASblock  *sbasblock        I  N/A  TSBASblock struct                                      
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeLogfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int  *linelen, int numlines, int sourcefile, int decoderesult, TSBASblock  *sbasblock, TOptions  *options) {
	int			i,j;
	int			ret;
	int			numberofcolumns;
	char		aux[200],hexstring[300],error[50];
	char		*p;
	struct tm 	tm;
	int			year;
	double		doy,seconds;

	switch(decoderesult) {
		case -1:
			strcpy(error,"CRC24Q_FAILURE              ");
			break;

		case -2:
			strcpy(error,"INVALID_PREAMBLE            ");
			break;

		case -3:
			strcpy(error,"MESSAGE_IDENTIFIER_MISMATCH ");
			break;

		case -4:
			strcpy(error,"SATNUMBER_CORRECTED_EXCEEDED");
			break;

		case -5:
			strcpy(error,"INVALID_TIME_OF_DAY         ");
			break;

		case -6:
			strcpy(error,"INVALID_TIME_OF_WEEK        ");
			break;

		case -7:
			strcpy(error,"INVALID_PRN_MASK_NUMBER     ");
			break;

		case -8:
			strcpy(error,"UNKNOWN_MESSAGE_TYPE        ");
			break;

	}

	if(sourcefile==0) {
		//The origin file is a RINEX B, but time is saved in time of applicability, the same as EMS file
		t2tmnolocal(&sbasblock->t,&tm,&seconds);
		t2doy(&sbasblock->t,&year,&doy);

		//Save all the hexademical values in a single string
		for(i=1;i<numlines;i++) {
			//Compute the number of records (columns) in the current line (normally the last one is not full)
			if(i==numlines-1) {
				numberofcolumns=sbasblock->halfdatalength%18;
			} else {
				numberofcolumns=18;
			}

			//Read lines
			for(j=0;j<numberofcolumns;j++) {
				getstr(&hexstring[18*2*(i-1)+2*j],line[i],linelen[i],7+3*j,2);
			}
		}
		ret=fprintf(fdlist[fdLOGFILE],"%s %03d %02d %02d %02d %02d %02d %02d %d %s\n",error,sbasblock->PRN,year,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,sbasblock->messagetype,hexstring);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
			printError(aux,options);
		}
	} else {
		//The origin file is a EMS file
		//Take out '\r' an '\n' from end of line
		p = strchr(line[0],'\r');
		if (p==NULL) {
			p = strchr(line[0],'\n');
		}
		if (p!=NULL) *p='\0';
		ret=fprintf(fdlist[fdLOGFILE],"%s %s\n",error,line[0]);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
			printError(aux,options);
		}
	}
}

/*****************************************************************************
 * Name        : writeRinexBfile
 * Description : Writes a Rinex B file from SBAS data. This file will not
 *                 contain any corrupted message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char *filename                  I  N/A  Filename where the data is saved
 * char **line                     I  N/A  Data lines to be written
 * int	*linelen                   I  N/A  Length of each line
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int header                      I  N/A  Indicates if the current lines
 *                                         are from a RINEXB header
 *                                         0 => Not a header line
 *                                         1 => Header line
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                            SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * TSBASblock  *sbasblock          I  N/A  TSBASblock struct 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeRinexBfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int *linelen, int numlines, int header, int sourcefile, TSBASblock  *sbasblock, TOptions  *options) {
	int 		i,j;
	int 		ret;
	int			len;
	int			numpairs;
	int			numpairsleft;
	int			numlinesleft;
	char 		aux[200];
	char 		aux3[10];
	char		*monthname;
	char		*p;
	static int 	headerwritten=0;
	struct		tm tm;
	TTime 		t;
	int 		year;
	double 		doy,seconds;

	//EMS files do not contain a header. It has to be manually added to the file
	if(sourcefile==1 && headerwritten==0) {
		//Write first line of header (RINEX VERSION / TYPE)
		ret=fprintf(fdlist[fdRINEXB],"     2.10           B                                       RINEX VERSION / TYPE\n");
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write second line of header (PGM / RUN BY / DATE)
		getcurrentsystemtime(&tm);	//Get current system time
		monthname=MonthName(tm.tm_mon+1);
		ret=fprintf(fdlist[fdRINEXB],"gLAB                gAGE (www.gage.es)  %02d-%.3s-%02d %02d:%02d     PGM / RUN BY / DATE\n",tm.tm_mday,monthname,tm.tm_year%100,tm.tm_hour,tm.tm_min);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write third line of header (END OF HEADER)
		ret=fprintf(fdlist[fdRINEXB],"                                                            END OF HEADER\n");
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		headerwritten=1;
	}

	//Header will only be true when the origin data file is a RINEX B
	if(header) {
		if(strncmp(&line[0][60],"PGM / RUN BY / DATE",19)==0) {
			//Change the author of the RINEX file
			getcurrentsystemtime(&tm);	//Get current system time
			monthname=MonthName(tm.tm_mon+1);
			ret=fprintf(fdlist[fdRINEXB],"gLAB                gAGE (www.gage.es)  %02d-%.3s-%02d %02d:%02d     PGM / RUN BY / DATE\n",tm.tm_mday,monthname,tm.tm_year%100,tm.tm_hour,tm.tm_min);
		} else {
			ret=fprintf(fdlist[fdRINEXB],"%s",line[0]);
		}
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}
		return;

	} else if (header==0 && headerwritten==0) {
		//If we don't have header line means that the header has ended
		headerwritten=1;
	}

	if(sourcefile==0) {
		//The origin file is a RINEX B
		for(i=0;i<numlines;i++) {
			//Take out '\r' an '\n' from end of line
			p = strchr(line[i],'\r');
			if (p==NULL) {
				p = strchr(line[i],'\n');
			}
			if (p!=NULL) *p='\0';
			ret=fprintf(fdlist[fdRINEXB],"%s\n",line[i]);
			if(ret<0) {
				fclose(readfd);		//Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);	//Close all other files before exiting
				sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
				printError(aux,options);
			}
		}
	} else { //sourcefile==1
		//The origin file is a EMS. Time saved in time of applicability, and we have to write it in time of reception of first bit
		memcpy(&t,&sbasblock->t,sizeof(TTime));	//Make of copy of the time structure
		t.SoD--;					//Substract one second to time
		if(t.SoD<0.) {
			//If it's negative then means that we are in the previous day
			t.MJDN--;
			t.SoD+=86400;
		}
		t2tmnolocal(&t,&tm,&seconds);
		t2doy(&t,&year,&doy);

		//Write first line of data
		ret=fprintf(fdlist[fdRINEXB],"%03d %02d %02d %02d %02d %02d%5.1f  %c%1d   %3d   %3d   %3s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,sbasblock->bandflag,sbasblock->frequency,sbasblock->halfdatalength,sbasblock->receiverindex,sbasblock->sourceidentifier);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write second line of data
		len=sprintf(aux," %2d   ",sbasblock->messagetype);
		if (sbasblock->halfdatalength>=18) {
			numpairs=18;
		} else {
			numpairs=sbasblock->halfdatalength;
		}
		for(i=0;i<numpairs;i++) {
			if (line[0][21]=='.') {
				//New EMS format
				getstr(aux3,line[0],linelen[0],40+2*i,2);
			} else {
				if(sbasblock->messagetype<10) {
					if (line[0][24]==' ') {
						//QZSS extension with message type padded with space
						getstr(aux3,line[0],linelen[0],25+2*i,2);
					} else {
						getstr(aux3,line[0],linelen[0],24+2*i,2);
					}
				} else getstr(aux3,line[0],linelen[0],25+2*i,2);
			}
			len+=sprintf(&aux[len]," %2s",aux3);
		}
		
		ret=fprintf(fdlist[fdRINEXB],"%s\n",aux);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write remaining lines of data
		numpairsleft=sbasblock->halfdatalength-numpairs;
		if (numpairsleft%18==0 && numpairsleft>0) {
			numlinesleft=numpairsleft/18;
		} else if (numpairsleft==0) {
			numlinesleft=0;
		} else {
			numlinesleft=numpairsleft/18+1;
		}
		for (j=0;j<numlinesleft;j++) {
			if (numpairsleft>=18) numpairs=18;
			else numpairs=numpairsleft;
			len=sprintf(aux,"      ");
			for(i=0;i<numpairs;i++) {
				if (line[0][21]=='.') {
					//New EMS format
					getstr(aux3,line[0],linelen[0],76+j*36+2*i,2);
				} else {
					if(sbasblock->messagetype<10) {
						if (line[0][24]==' ') {
							//QZSS extension with message type padded with space
							getstr(aux3,line[0],linelen[0],61+j*36+i*2,2);
						} else {
							getstr(aux3,line[0],linelen[0],60+j*36+i*2,2);
						}
					} else getstr(aux3,line[0],linelen[0],61+j*36+i*2,2);
				}
				len+=sprintf(&aux[len]," %2s",aux3);
			}
			
			ret=fprintf(fdlist[fdRINEXB],"%s\n",aux);
			if(ret<0) {
				fclose(readfd);		//Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);	//Close all other files before exiting
				sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
				printError(aux,options);
			}
			numpairsleft-=numpairs;
		}
	}
}

/*****************************************************************************
 * Name        : writeEMSfile
 * Description : Writes a EMS file from SBAS data. This file will not
 *               contain any corrupted message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char *filename                  I  N/A  Filename where the data is saved
 * char **line                     I  N/A  Data lines to be written
 * int	*linelen                   I  N/A  Length of each line
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int header                      I  N/A  Indicates if the current lines
 *                                         are from a RINEXB header
 *                                         0 => Not a header line
 *                                         1 => Header line
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                         SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * TSBASblock  *sbasblock          I  N/A  TSBASblock struct 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeEMSfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int *linelen, int numlines, int header, int sourcefile,  TSBASblock  *sbasblock, TOptions  *options) {
	int 			i,j;
	int 			ret;
	int 			numberofcolumns;
	char 			aux[200],hexstring[300];
	struct			tm tm;
	int 			year;
	double 			doy,seconds;
	char   			*p;
	char			*numbitsstrpointer;
	static char		mopsl1l5length[5]={'0','0','F','A','\0'};

	//There are no header lines in EMS file
	if(header==1) return;

	if(sourcefile==0) {
		//The origin file is a RINEX B, but time is saved in time of applicability, the same as EMS file
		t2tmnolocal(&sbasblock->t,&tm,&seconds);
		t2doy(&sbasblock->t,&year,&doy);
		
		//Save all the hexademical values in a single string
		for(i=1;i<numlines;i++) {
			//Compute the number of records (columns) in the current line (normally the last one is not full)
			if(i==numlines-1) {
				numberofcolumns=sbasblock->halfdatalength%18;
			} else {
				numberofcolumns=18;
			}

			//Read lines
			for(j=0;j<numberofcolumns;j++) {
				getstr(&hexstring[18*2*(i-1)+2*j],line[i],linelen[i],7+3*j,2);
			}
		}
		if (sbasblock->bandflag!='L'|| (sbasblock->bandflag=='L' && sbasblock->frequency!=1) ) {
			//New EMS format. We need to compute number of useful bits
			//As we don't know the number of bits for padding, for the case different of L5 it will be the total number of bits
			if (sbasblock->bandflag=='L' && (sbasblock->frequency==1 || sbasblock->frequency==5)) {
				numbitsstrpointer=mopsl1l5length;
				ret=fprintf(fdlist[fdEMS],"%03d %02d %02d %02d %02d %02d %09.6f %c%1d %4s %02d %s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,sbasblock->bandflag,sbasblock->frequency,numbitsstrpointer,sbasblock->messagetype,hexstring);
			} else {
				//We don't know what message is (not SBAS message), print message in old EMS format as we can't compute the number of useful bits
				//NOTE: To print the total number of bits (with padding) in hexadecimal, the code will be:
				//	char	numbitshexstr[5];
				//  sprintf(numbitshexstr,"%04X",(unsigned int)(sbasblock->datalength*4));
				//  numbitsstrpointer=numbitshexstr;
				ret=fprintf(fdlist[fdEMS],"%03d %02d %02d %02d %02d %02d %02d %d %s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,sbasblock->messagetype,hexstring);
			}
		} else {
			//Legacy EMS format
			ret=fprintf(fdlist[fdEMS],"%03d %02d %02d %02d %02d %02d %02d %d %s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,sbasblock->messagetype,hexstring);
		}
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
			printError(aux,options);
		}
	} else {
		//The origin file is a EMS file
		//Take out '\r' an '\n' from end of line
		p = strchr(line[0],'\r');
		if (p==NULL) {
			p = strchr(line[0],'\n');
		}
		if (p!=NULL) *p='\0';
		ret=fprintf(fdlist[fdEMS],"%s\n",line[0]);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
			printError(aux,options);
		}
	}
}

/*****************************************************************************
 * Name        : writeSBASdecodesummary
 * Description : Writes a EMS file from SBAS data. This file will not
 *               contain any corrupted message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char *filename                  I  N/A  Filename where the data is saved
 * int  numberofbadmessages        I  N/A  Number of incorrect messages read
 * int  totalmessagesmissing       I  N/A  Total number of messages missing (detected with preamble)
 * int  msgmissingdetected         I  N/A  Number of detections of messages missing
 * int  *linesmissing              I  N/A  Line numbers where messages are missing
 * int  *listmissing               I  N/A  Vector with the messages lost for each line
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeSBASdecodesummary (FILE  **fdlist,FILE  *readfd, char *filename, int  numberofbadmessages, int  totalmessagesmissing, int  msgmissingdetected, int  *linesmissing, int  *listmissing, TOptions  *options) {

	int		i;
	int		ret;
	char	aux[300];

	if(numberofbadmessages==0 && totalmessagesmissing==0) {
		ret=fprintf(fdlist[fdLOGFILE],"All messages correctly decoded\n");
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
					printError(aux,options);
		}
		return;
	}

	if(numberofbadmessages>0) {
		if(numberofbadmessages==1) {
			ret=fprintf(fdlist[fdLOGFILE],"%d message was incorrect\n",numberofbadmessages);
		} else {
			ret=fprintf(fdlist[fdLOGFILE],"%d messages were incorrect\n",numberofbadmessages);
		}
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
					printError(aux,options);
		}
	}
	if(totalmessagesmissing>0) {
		if(totalmessagesmissing==1) {
			ret=fprintf(fdlist[fdLOGFILE],"%d message was missing at line %d\n",totalmessagesmissing,linesmissing[0]);
			if(ret<0) {
				fclose(readfd);		//Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);	//Close all other files before exiting
				sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
						printError(aux,options);
			}
		} else if (msgmissingdetected==1 && totalmessagesmissing>1) {
			ret=fprintf(fdlist[fdLOGFILE],"%d messages were missing at line %d\n",totalmessagesmissing,linesmissing[0]);
			if(ret<0) {
				fclose(readfd);		//Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);	//Close all other files before exiting
				sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
						printError(aux,options);
			}
		} else {
			for(i=0;i<msgmissingdetected;i++) {
				if(listmissing[i]==1) {
					ret=fprintf(fdlist[fdLOGFILE],"%d message was missing at line %d\n",listmissing[i],linesmissing[i]);
				} else {
					ret=fprintf(fdlist[fdLOGFILE],"%d messages were missing at line %d\n",listmissing[i],linesmissing[i]);
				}
				if(ret<0) {
					fclose(readfd);		//Close RINEXB or EMS file where the data has been read
					closefiles(fdlist,18);	//Close all other files before exiting
					sprintf(aux,"When writing SBAS data to EMS file [%s]\n",filename);
							printError(aux,options);
				}
			}
		}
	}
}


/*****************************************************************************
 * Name        : writePegasusheaders
 * Description : Writes all the headers for the Pegasus files
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char **filelist                 I  N/A  List of filenames for writing data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writePegasusheaders (FILE **fdlist, FILE *readfd, char **filelist, TOptions  *options) {

	int			ret;
	char		aux[200];
	char		*monthname;
	struct 		tm tm;

	//Write header of Message sequence
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdMESSAGESEQUENCE],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c  \"CRC_PASS\"%c  \"VALID\"%c   \"RMT\"%c   \"DMT\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdMESSAGESEQUENCE],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"CRC_PASS\"%c\"VALID\"%c\"RMT\"%c\"DMT\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdMESSAGESEQUENCE]);
		printError(aux,options);
	}

	//Write header of Alarm message (Message type 0)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdALARMMESSAGE],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"\n",options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdALARMMESSAGE],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"\n",options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdALARMMESSAGE]);
		printError(aux,options);
	}

	//Write header of PRN Mask (Message type 1)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdPRNMASK],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"SVMASK\"%c                                                 \"IODP\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdPRNMASK],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"SVMASK\"%c\"IODP\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdPRNMASK]);
		printError(aux,options);
	}

	//Write header of Fast Corrections (Message type 2,3,4,5,24)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdFASTCORRECTIONS],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"TYPE\"%c   \"IODF\"%c   \"IODP\"%c   \"PRC01\"%c \"PRC02\"%c \"PRC03\"%c \"PRC04\"%c \"PRC05\"%c \"PRC06\"%c \"PRC07\"%c \"PRC08\"%c \"PRC09\"%c \"PRC10\"%c \"PRC11\"%c \"PRC12\"%c \"PRC13\"%c \"UDREI01\"%c \"UDREI02\"%c \"UDREI03\"%c \"UDREI04\"%c \"UDREI05\"%c \"UDREI06\"%c \"UDREI07\"%c \"UDREI08\"%c \"UDREI09\"%c \"UDREI10\"%c \"UDREI11\"%c \"UDREI12\"%c \"UDREI13\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdFASTCORRECTIONS],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"TYPE\"%c\"IODF\"%c\"IODP\"%c\"PRC01\"%c\"PRC02\"%c\"PRC03\"%c\"PRC04\"%c\"PRC05\"%c\"PRC06\"%c\"PRC07\"%c\"PRC08\"%c\"PRC09\"%c\"PRC10\"%c\"PRC11\"%c\"PRC12\"%c\"PRC13\"%c\"UDREI01\"%c\"UDREI02\"%c\"UDREI03\"%c\"UDREI04\"%c\"UDREI05\"%c\"UDREI06\"%c\"UDREI07\"%c\"UDREI08\"%c\"UDREI09\"%c\"UDREI10\"%c\"UDREI11\"%c\"UDREI12\"%c\"UDREI13\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdFASTCORRECTIONS]);
		printError(aux,options);
	}

	//Write header of Integrity (Message type 6)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdINTEGRITY],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c \"IODF2\"%c \"IODF3\"%c \"IODF4\"%c \"IODF5\"%c \"UDREI01\"%c \"UDREI02\"%c \"UDREI03\"%c \"UDREI04\"%c \"UDREI05\"%c \"UDREI06\"%c \"UDREI07\"%c \"UDREI08\"%c \"UDREI09\"%c \"UDREI10\"%c \"UDREI11\"%c \"UDREI12\"%c \"UDREI13\"%c \"UDREI14\"%c \"UDREI15\"%c \"UDREI16\"%c \"UDREI17\"%c \"UDREI18\"%c \"UDREI19\"%c \"UDREI20\"%c \"UDREI21\"%c \"UDREI22\"%c \"UDREI23\"%c \"UDREI24\"%c \"UDREI25\"%c \"UDREI26\"%c \"UDREI27\"%c \"UDREI28\"%c \"UDREI29\"%c \"UDREI30\"%c \"UDREI31\"%c \"UDREI32\"%c \"UDREI33\"%c \"UDREI34\"%c \"UDREI35\"%c \"UDREI36\"%c \"UDREI37\"%c \"UDREI38\"%c \"UDREI39\"%c \"UDREI40\"%c \"UDREI41\"%c \"UDREI42\"%c \"UDREI43\"%c \"UDREI44\"%c \"UDREI45\"%c \"UDREI46\"%c \"UDREI47\"%c \"UDREI48\"%c \"UDREI49\"%c \"UDREI50\"%c \"UDREI51\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdINTEGRITY],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"IODF2\"%c\"IODF3\"%c\"IODF4\"%c\"IODF5\"%c\"UDREI01\"%c\"UDREI02\"%c\"UDREI03\"%c\"UDREI04\"%c\"UDREI05\"%c\"UDREI06\"%c\"UDREI07\"%c\"UDREI08\"%c\"UDREI09\"%c\"UDREI10\"%c\"UDREI11\"%c\"UDREI12\"%c\"UDREI13\"%c\"UDREI14\"%c\"UDREI15\"%c\"UDREI16\"%c\"UDREI17\"%c\"UDREI18\"%c\"UDREI19\"%c\"UDREI20\"%c\"UDREI21\"%c\"UDREI22\"%c\"UDREI23\"%c\"UDREI24\"%c\"UDREI25\"%c\"UDREI26\"%c\"UDREI27\"%c\"UDREI28\"%c\"UDREI29\"%c\"UDREI30\"%c\"UDREI31\"%c\"UDREI32\"%c\"UDREI33\"%c\"UDREI34\"%c\"UDREI35\"%c\"UDREI36\"%c\"UDREI37\"%c\"UDREI38\"%c\"UDREI39\"%c\"UDREI40\"%c\"UDREI41\"%c\"UDREI42\"%c\"UDREI43\"%c\"UDREI44\"%c\"UDREI45\"%c\"UDREI46\"%c\"UDREI47\"%c\"UDREI48\"%c\"UDREI49\"%c\"UDREI50\"%c\"UDREI51\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdINTEGRITY]);
		printError(aux,options);
	}


	//Write header of Fast Degradation (Message type 7)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdFASTDEGRADATION],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"TLAT\"%c   \"IODP\"%c   \"AI01\"%c \"AI02\"%c \"AI03\"%c \"AI04\"%c \"AI05\"%c \"AI06\"%c \"AI07\"%c \"AI08\"%c \"AI09\"%c \"AI10\"%c \"AI11\"%c \"AI12\"%c \"AI13\"%c \"AI14\"%c \"AI15\"%c \"AI16\"%c \"AI17\"%c \"AI18\"%c \"AI19\"%c \"AI20\"%c \"AI21\"%c \"AI22\"%c \"AI23\"%c \"AI24\"%c \"AI25\"%c \"AI26\"%c \"AI27\"%c \"AI28\"%c \"AI29\"%c \"AI30\"%c \"AI31\"%c \"AI32\"%c \"AI33\"%c \"AI34\"%c \"AI35\"%c \"AI36\"%c \"AI37\"%c \"AI38\"%c \"AI39\"%c \"AI40\"%c \"AI41\"%c \"AI42\"%c \"AI43\"%c \"AI44\"%c \"AI45\"%c \"AI46\"%c \"AI47\"%c \"AI48\"%c \"AI49\"%c \"AI50\"%c \"AI51\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdFASTDEGRADATION],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"TLAT\"%c\"IODP\"%c\"AI01\"%c\"AI02\"%c\"AI03\"%c\"AI04\"%c\"AI05\"%c\"AI06\"%c\"AI07\"%c\"AI08\"%c\"AI09\"%c\"AI10\"%c\"AI11\"%c\"AI12\"%c\"AI13\"%c\"AI14\"%c\"AI15\"%c\"AI16\"%c\"AI17\"%c\"AI18\"%c\"AI19\"%c\"AI20\"%c\"AI21\"%c\"AI22\"%c\"AI23\"%c\"AI24\"%c\"AI25\"%c\"AI26\"%c\"AI27\"%c\"AI28\"%c\"AI29\"%c\"AI30\"%c\"AI31\"%c\"AI32\"%c\"AI33\"%c\"AI34\"%c\"AI35\"%c\"AI36\"%c\"AI37\"%c\"AI38\"%c\"AI39\"%c\"AI40\"%c\"AI41\"%c\"AI42\"%c\"AI43\"%c\"AI44\"%c\"AI45\"%c\"AI46\"%c\"AI47\"%c\"AI48\"%c\"AI49\"%c\"AI50\"%c\"AI51\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdFASTDEGRADATION]);
		printError(aux,options);
	}

	//Write header of Degradation (Message type 10)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdDEGRADATION],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"BRRC\"%c   \"CLTC_LSB\"%c   \"CLTC_V1\"%c   \"ILTC_V1\"%c   \"CLTC_V0\"%c   \"ILTC_V0\"%c   \"CGEO_LSB\"%c   \"CGEO_V\"%c   \"IGEO\"%c   \"CER\"%c   \"CIONO_STEP\"%c   \"IIONO\"%c   \"CIONO_RAMP\"%c   \"RSS_UDRE\"%c   \"RSS_IONO\"%c   \"CCOV\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdDEGRADATION],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"BRRC\"%c\"CLTC_LSB\"%c\"CLTC_V1\"%c\"ILTC_V1\"%c\"CLTC_V0\"%c\"ILTC_V0\"%c\"CGEO_LSB\"%c\"CGEO_V\"%c\"IGEO\"%c\"CER\"%c\"CIONO_STEP\"%c\"IIONO\"%c\"CIONO_RAMP\"%c\"RSS_UDRE\"%c\"RSS_IONO\"%c\"CCOV\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdDEGRADATION]);
		printError(aux,options);
	}

	//Write header of Ionospheric Grid (Message type 18)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdIONOSPHERICGRID],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"NB\"%c   \"BN\"%c   \"IODI\"%c   \"IGP\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdIONOSPHERICGRID],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"NB\"%c\"BN\"%c\"IODI\"%c\"IGP\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdIONOSPHERICGRID]);
		printError(aux,options);
	}

	//Write header of SBAS Slow Corrections (Message type 24,25)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdSLOWCORRECTIONS],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"VC1\"%c \"MASK1\"%c \"IOD1\"%c \"DX1\"%c   \"DY1\"%c   \"DZ1\"%c   \"DAF01\"%c        \"DXROC1\"%c       \"DYROC1\"%c       \"DZROC1\"%c       \"DAF11\"%c        \"TOA1\"%c   \"IODP1\"%c \"VC2\"%c \"MASK2\"%c \"IOD2\"%c \"DX2\"%c   \"DY2\"%c   \"DZ2\"%c   \"DAF02\"%c        \"DXROC2\"%c       \"DYROC2\"%c       \"DZROC2\"%c       \"DAF12\"%c        \"TOA2\"%c   \"IODP2\"%c \"VC3\"%c \"MASK3\"%c \"IOD3\"%c \"DX3\"%c   \"DY3\"%c   \"DZ3\"%c   \"DAF03\"%c        \"DXROC3\"%c       \"DYROC3\"%c       \"DZROC3\"%c       \"DAF13\"%c        \"TOA3\"%c   \"IODP3\"%c \"VC4\"%c \"MASK4\"%c \"IOD4\"%c \"DX4\"%c   \"DY4\"%c   \"DZ4\"%c   \"DAF04\"%c        \"DXROC4\"%c       \"DYROC4\"%c       \"DZROC4\"%c       \"DAF14\"%c        \"TOA4\"%c   \"IODP4\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdSLOWCORRECTIONS],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"VC1\"%c\"MASK1\"%c\"IOD1\"%c\"DX1\"%c\"DY1\"%c\"DZ1\"%c\"DAF01\"%c\"DXROC1\"%c\"DYROC1\"%c\"DZROC1\"%c\"DAF11\"%c\"TOA1\"%c\"IODP1\"%c\"VC2\"%c\"MASK2\"%c\"IOD2\"%c\"DX2\"%c\"DY2\"%c\"DZ2\"%c\"DAF02\"%c\"DXROC2\"%c\"DYROC2\"%c\"DZROC2\"%c\"DAF12\"%c\"TOA2\"%c\"IODP2\"%c\"VC3\"%c\"MASK3\"%c\"IOD3\"%c\"DX3\"%c\"DY3\"%c\"DZ3\"%c\"DAF03\"%c\"DXROC3\"%c\"DYROC3\"%c\"DZROC3\"%c\"DAF13\"%c\"TOA3\"%c\"IODP3\"%c\"VC4\"%c\"MASK4\"%c\"IOD4\"%c\"DX4\"%c\"DY4\"%c\"DZ4\"%c\"DAF04\"%c\"DXROC4\"%c\"DYROC4\"%c\"DZROC4\"%c\"DAF14\"%c\"TOA4\"%c\"IODP4\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSLOWCORRECTIONS]);
		printError(aux,options);
	}

	//Write header of Ionospheric Corrections (Message type 26)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdIONOSPHERICCORRECTIONS],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c \"BN\"%c \"BI\"%c \"IODI\"%c \"DELAY01\"%c  \"GIVEI01\"%c \"DELAY02\"%c  \"GIVEI02\"%c \"DELAY03\"%c  \"GIVEI03\"%c \"DELAY04\"%c  \"GIVEI04\"%c \"DELAY05\"%c  \"GIVEI05\"%c \"DELAY06\"%c  \"GIVEI06\"%c \"DELAY07\"%c  \"GIVEI07\"%c \"DELAY08\"%c  \"GIVEI08\"%c \"DELAY09\"%c  \"GIVEI09\"%c \"DELAY10\"%c  \"GIVEI10\"%c \"DELAY11\"%c  \"GIVEI11\"%c \"DELAY12\"%c  \"GIVEI12\"%c \"DELAY13\"%c  \"GIVEI13\"%c \"DELAY14\"%c  \"GIVEI14\"%c \"DELAY15\"%c  \"GIVEI15\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdIONOSPHERICCORRECTIONS],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"BN\"%c\"BI\"%c\"IODI\"%c\"DELAY01\"%c\"GIVEI01\"%c\"DELAY02\"%c\"GIVEI02\"%c\"DELAY03\"%c\"GIVEI03\"%c\"DELAY04\"%c\"GIVEI04\"%c\"DELAY05\"%c\"GIVEI05\"%c\"DELAY06\"%c\"GIVEI06\"%c\"DELAY07\"%c\"GIVEI07\"%c\"DELAY08\"%c\"GIVEI08\"%c\"DELAY09\"%c\"GIVEI09\"%c\"DELAY10\"%c\"GIVEI10\"%c\"DELAY11\"%c\"GIVEI11\"%c\"DELAY12\"%c\"GIVEI12\"%c\"DELAY13\"%c\"GIVEI13\"%c\"DELAY14\"%c\"GIVEI14\"%c\"DELAY15\"%c\"GIVEI15\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdIONOSPHERICCORRECTIONS]);
		printError(aux,options);
	}

	//Write header of Service Region (Message type 27)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdSERVICEREGION27],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c \"IODS\"%c \"NS\"%c \"MSG\"%c \"NR\"%c \"PC\"%c \"DELTAI\"%c \"DELTAO\"%c \"LAT11\"%c \"LON11\"%c \"LAT21\"%c \"LON21\"%c \"RS1\"%c \"LAT12\"%c \"LON12\"%c \"LAT22\"%c \"LON22\"%c \"RS2\"%c \"LAT13\"%c \"LON13\"%c \"LAT23\"%c \"LON23\"%c \"RS3\"%c \"LAT14\"%c \"LON14\"%c \"LAT24\"%c \"LON24\"%c \"RS4\"%c \"LAT15\"%c \"LON15\"%c \"LAT25\"%c \"LON25\"%c \"RS5\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdSERVICEREGION27],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"IODS\"%c\"NS\"%c\"MSG\"%c\"NR\"%c\"PC\"%c\"DELTAI\"%c\"DELTAO\"%c\"LAT11\"%c\"LON11\"%c\"LAT21\"%c\"LON21\"%c\"RS1\"%c\"LAT12\"%c\"LON12\"%c\"LAT22\"%c\"LON22\"%c\"RS2\"%c\"LAT13\"%c\"LON13\"%c\"LAT23\"%c\"LON23\"%c\"RS3\"%c\"LAT14\"%c\"LON14\"%c\"LAT24\"%c\"LON24\"%c\"RS4\"%c\"LAT15\"%c\"LON15\"%c\"LAT25\"%c\"LON25\"%c\"RS5\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION27]);
		printError(aux,options);
	}

	//Write header of Service Region (Message type 28)
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdSERVICEREGION28],"\"RX_WEEK\"%c   \"RX_TOM\"%c   \"PRN\"%c   \"IODP\"%c \"MASK1\"%c \"SE1\"%c \"E111\"%c \"E221\"%c \"E331\"%c \"E441\"%c \"E121\"%c \"E131\"%c \"E141\"%c \"E231\"%c \"E241\"%c \"E341\"%c \"MASK2\"%c \"SE2\"%c \"E112\"%c \"E222\"%c \"E332\"%c \"E442\"%c \"E122\"%c \"E132\"%c \"E142\"%c \"E232\"%c \"E242\"%c \"E342\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	} else {
		ret=fprintf(fdlist[fdSERVICEREGION28],"\"RX_WEEK\"%c\"RX_TOM\"%c\"PRN\"%c\"IODP\"%c\"MASK1\"%c\"SE1\"%c\"E111\"%c\"E221\"%c\"E331\"%c\"E441\"%c\"E121\"%c\"E131\"%c\"E141\"%c\"E231\"%c\"E241\"%c\"E341\"%c\"MASK2\"%c\"SE2\"%c\"E112\"%c\"E222\"%c\"E332\"%c\"E442\"%c\"E122\"%c\"E132\"%c\"E142\"%c\"E232\"%c\"E242\"%c\"E342\"\n",options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs,options->pegasusfs);
	}
	if(ret<0) {
		fclose(readfd);		//Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION28]);
		printError(aux,options);
	}

	//Write header of Ephemeris (Message type 9) (In Rinex 2.10 format)
		//Write first line of header (RINEX VERSION / TYPE)
		ret=fprintf(fdlist[fdEPHEMERIS],"     2.10           H: GEO NAV MSG DATA                     RINEX VERSION / TYPE\n");
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERIS]);
			printError(aux,options);
		}
		ret=fprintf(fdlist[fdEPHEMERISPREVDAY],"     2.10           H: GEO NAV MSG DATA                     RINEX VERSION / TYPE\n");
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERISPREVDAY]);
			printError(aux,options);
		}

		//Write second line of header (PGM / RUN BY / DATE)
		getcurrentsystemtime(&tm);      //Get current system time
		monthname=MonthName(tm.tm_mon+1);
		ret=fprintf(fdlist[fdEPHEMERIS],"gLAB                gAGE (www.gage.es)  %02d-%.3s-%02d %02d:%02d     PGM / RUN BY / DATE\n",tm.tm_mday,monthname,tm.tm_year%100,tm.tm_hour,tm.tm_min);
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERIS]);
			printError(aux,options);
		}
		ret=fprintf(fdlist[fdEPHEMERISPREVDAY],"gLAB                gAGE (www.gage.es)  %02d-%.3s-%02d %02d:%02d     PGM / RUN BY / DATE\n",tm.tm_mday,monthname,tm.tm_year%100,tm.tm_hour,tm.tm_min);
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERISPREVDAY]);
			printError(aux,options);
		}

		//Write third line of header (END OF HEADER)
		ret=fprintf(fdlist[fdEPHEMERIS],"                                                            END OF HEADER\n");
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERIS]);
			printError(aux,options);
		}
		ret=fprintf(fdlist[fdEPHEMERISPREVDAY],"                                                            END OF HEADER\n");
		if(ret<0) {
			fclose(readfd);         //Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);  //Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX H file [%s]\n",filelist[fdEPHEMERISPREVDAY]);
			printError(aux,options);
		}
}

/*****************************************************************************
 * Name        : writePegasusfiles
 * Description : Writes data in Pegasus file format in their corresponding files
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * FILE  *readfd                   I  N/A  File descriptor of the data that is being read
 * char **filelist                 I  N/A  List of filenames for writing data
 * char **line                     I  N/A  Data lines from the data source file
 * int	*linelen                   I  N/A  Length of each line
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                         SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * int header                      I  N/A  Indicates if the current lines
 *                                         are from a header
 *                                         0 => Not a header line
 *                                         1 => Header line
 * int decoderesult                I  N/A  Result of the message decodification
 * int decodedmessagetype          I  N/A  Message type decoded from hexadecimal message 
 * int *prevday                    O  N/A  Indicates if a RINEX H file from the
 *                                         previous day has been written
 * TSBASblock  *sbasblock          I  N/A  TSBASblock struct                                      
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writePegasusfiles (FILE **fdlist, FILE *readfd, char **filelist, char **line, int *linelen, int numlines, int sourcefile, int header, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options) {
	static int	headerwritten=0;
	int			i,j;
	int			len;
	int			ret;
	int			number;
	int			type;
	int			numberofcolumns;
	int			crcpass=1,valid=1;
	int			GPSweek,GPSweektrans,GPSweektoe;
	int			previousday=0,filetoprint;
	static int	firstbrdcday=-1;
	double		SoW,SoWtrans,SoWtoe;
	double		seconds;
	double		uravalue;
	double		health;
	double		transtimesecadjusted;
	double		igpverticaldelay;
	double		scalefactor;
	char		aux[MAX_INPUT_LINE];
	char        hexstring[300];
	char        binarystring[2400];
	struct tm 	tm;
	TTime		transtime,toe;
	

	//This variable is to save the last health status read. We initialize all to 0, so if we don't have any health information (from message 18) put 31 as default (bits 4,3,2,1,0 to 1)
	//See below (on GEO Navigation message output) the Rinex specfications
	//The size of 90 is because there are 90 possible GEO PRN
	static double	lasthealthlist[91]={31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};

	//If we have header lines from RINEX B don't do nothing
	if(header) return;

	//Write the header for all file types
	if(headerwritten==0) {
		writePegasusheaders(fdlist,readfd,filelist,options);
		headerwritten=1;
	}

	//Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&sbasblock->t, &GPSweek, &SoW);

	//Print Message Transmission Sequence
	if(decoderesult<0) {
		crcpass=0;
		valid=0;	//Valid variable should contain the same info as CRCPASS. but it can be manually turned to 0 to simulate errors
	}

	//If type 0 are decoded as type2, change the decodedmessagetype value
	if(options->useAlarmmessageForCorrections==1 && decodedmessagetype==DONTUSE) {
		decodedmessagetype=2;
	}
	if(options->pegasusaligned==1) {
		ret=fprintf(fdlist[fdMESSAGESEQUENCE],"%-4d%c        %-9.2f%c  %-3d%c    %-d%c           %-d%c         %-2d%c      %-2d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,crcpass,options->pegasusfs,valid,options->pegasusfs,sbasblock->messagetype,options->pegasusfs,decodedmessagetype);
	} else {
		ret=fprintf(fdlist[fdMESSAGESEQUENCE],"%d%c%.2f%c%d%c%d%c%d%c%d%c%d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,crcpass,options->pegasusfs,valid,options->pegasusfs,sbasblock->messagetype,options->pegasusfs,decodedmessagetype);
	}
	if(ret<0) {
		fclose(readfd);         //Close RINEXB or EMS file where the data has been read
		closefiles(fdlist,18);  //Close all other files before exiting
		sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdMESSAGESEQUENCE]);
		printError(aux,options);
	}

	if(decoderesult<0) return;	//If message had errors it must not be written to Pegasus message type files


	switch(sbasblock->messagetype) {
		case(PRNMASKASSIGNMENTS):
			//First we need to extract the hexadecimal string corresponding to the SVMASK
			if(sourcefile==0) {
				//The origin file is RINEX B
				//First join the hexadecimal message in one string
				for(i=1;i<numlines;i++) {
					//Compute the number of records (columns) in the current line (normally the last one is not full)
					if(i==numlines-1) {
						numberofcolumns=sbasblock->halfdatalength%18;
					} else {
						numberofcolumns=18;
					}

					//Read lines
					for(j=0;j<numberofcolumns;j++) {
						getstr(&hexstring[18*2*(i-1)+2*j],line[i],linelen[i],7+3*j,2);
					}
				}	

			} else {
				//The origin file is EMS
				if(sbasblock->messagetype<10) {	
					if (line[0][24]==' ') {
						getstr(hexstring,line[0],linelen[0],25,sbasblock->datalength);	
					} else {
						getstr(hexstring,line[0],linelen[0],24,sbasblock->datalength);	
					}
				} else {
					getstr(hexstring,line[0],linelen[0],25,sbasblock->datalength);
				}
			}

			////Now we have the hexadecimal string. We need to convert to a binary string, then 
			////extract the corresponding bits, then add 6 trailing zeros so it is a multiple of 8 and then convert to a hexadecimal string
			
			//Convert the hexadecimal string to a binary string (1 bit per byte)
			strhextostrbin(hexstring,sbasblock->datalength,binarystring);
			
			//Extract the PRN Mask in binary string
			getstr(aux,binarystring,sbasblock->datalength*4,14,210);

			//Add the 6 trailing zeros to the PRN Mask
			len=(int)strlen(aux);
			sprintf(&aux[len],"000000");

			//Convert from binary to hexadecimal
			strbintostrhex(aux,216,hexstring,1);


			//Print PRN Mask (Message type 1)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdPRNMASK],"%-4d%c        %-9.2f%c  %-3d%c     \"%s\"%c %-d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,hexstring,options->pegasusfs,sbasblock->IODP);
			} else {
				ret=fprintf(fdlist[fdPRNMASK],"%d%c%.2f%c%d%c\"%s\"%c%d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,hexstring,options->pegasusfs,sbasblock->IODP);
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdPRNMASK]);
				printError(aux,options);
			}
			break;
		case(DONTUSE):
			//Print Alarm message (Message type 0)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdALARMMESSAGE],"%-4d%c        %-9.2f%c  %-3d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN);
			} else {
				ret=fprintf(fdlist[fdALARMMESSAGE],"%d%c%.2f%c%d\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN);
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdALARMMESSAGE]);
				printError(aux,options);
			}
			if(options->useAlarmmessageForCorrections==0) break;
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case(FASTCORRECTIONS2):case(FASTCORRECTIONS3):case(FASTCORRECTIONS4):case(FASTCORRECTIONS5):case(MIXEDFASTLONGTERMCORRECTIONS):
			//Print Fast Corrections (Message type 2,3,4,5,24)

			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				type=sbasblock->BlockID;
				number=6;
			} else {
				type=sbasblock->messagetype;
				number=13;
			}


			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdFASTCORRECTIONS],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c        %-d%c        %-d%c        ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,type,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			} else {
				ret=fprintf(fdlist[fdFASTCORRECTIONS],"%d%c%.2f%c%d%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,type,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdFASTCORRECTIONS]);
				printError(aux,options);
			}

			//Write PRC
			aux[0]='\0';		//Initialize aux to empty
			len=0;
			for(i=0;i<number;i++) {
				if(options->pegasusaligned==1) {
					len+=sprintf(&aux[len],"%-8.3f%c",sbasblock->PRC[i],options->pegasusfs);	//Write PRC
				} else {
					len+=sprintf(&aux[len],"%.3f%c",sbasblock->PRC[i],options->pegasusfs);	//Write PRC
				}
			}

			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				//In this case we only have 6 Fast Corrections, so the unavailable data (PRC 7-13) must have empty fields
				if(options->pegasusaligned==1) {
					if(options->pegasusfs==';') len+=sprintf(&aux[len],";;;;;;;                                                        ");  //Add empty fields
					else len+=sprintf(&aux[len],"                                                               ");	//Add empty fields
				} else {
					if(options->pegasusfs==';') len+=sprintf(&aux[len],";;;;;;;");  //Add empty fields
					else len+=sprintf(&aux[len],"       ");	//Add empty fields
				}
			}

			//Write UDREI
			for(i=0;i<number;i++) {
				if(i==number-1) {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d",sbasblock->UDREI[i]);      //Write UDREI
					} else {
						len+=sprintf(&aux[len],"%d",sbasblock->UDREI[i]);      //Write UDREI
					}
				} else {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d%c        ",sbasblock->UDREI[i],options->pegasusfs);	//Write UDREI
					} else {
						len+=sprintf(&aux[len],"%d%c",sbasblock->UDREI[i],options->pegasusfs);	//Write UDREI
					}
				}
			}

			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				//In this case we only have 6 UDREI, so the unavailable data (UDREI 7-13) must have empty fields
				if(options->pegasusaligned==1) {
					if(options->pegasusfs==';') len+=sprintf(&aux[len],";;;;;;;");      //Add empty fields
					else len+=sprintf(&aux[len],"                                                                           ");	//Add empty fields
				} else {
					if(options->pegasusfs==';') len+=sprintf(&aux[len],";;;;;;;");      //Add empty fields
					else len+=sprintf(&aux[len],"       ");	//Add empty fields
				}
			}

			ret=fprintf(fdlist[fdFASTCORRECTIONS],"%s\n",aux);
				if(ret<0) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdFASTCORRECTIONS]);
						printError(aux,options);
				}
			
			//If it is a Mixed Corrections message, we have to print the long term data. Skipping the break will result in executing the next case
			if(sbasblock->messagetype!=MIXEDFASTLONGTERMCORRECTIONS) break;
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case(LONGTERMSATELLITECORRECTIONS):
			//Print Slow Corrections (Message type 24,25)
			//In this case, the manual says that if there are less data sets, then they should be filled with zeros

			//Print first half of message
			if(sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]==0) {
				i=0;
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d%c       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][IODPPOSITION],options->pegasusfs);
				} else {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%d%c%.2f%c%-3d%c%-d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[1][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[1][IODPPOSITION],options->pegasusfs);
				}
			} else { //sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]==1
				i=1;
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15.7f%c%-15.7f%c%-15.7f%c%-15E%c%-5d%c    %-d%c       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF0],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF1],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION],options->pegasusfs,
						0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
				} else {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%d%c%.2f%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%.7f%c%.7f%c%.7f%c%E%c%d%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF0],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[0][DELTAAF1],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION],options->pegasusfs,
						0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
				}
			}
				if(ret<0) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSLOWCORRECTIONS]);
						printError(aux,options);
				}

			//Print second half of message
			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				//We have the mixed message (type 24), so there is no second half of message. Print zeros
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d%c       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d\n",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0);
				} else {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d\n",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0);
				}
			} else if(sbasblock->longtermsaterrcorrections[2-i][VELOCITYCODE]==0) {
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d%c       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d\n",
						(int)sbasblock->longtermsaterrcorrections[2-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][IODPPOSITION],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][IODPPOSITION]);
				} else {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d\n",
						(int)sbasblock->longtermsaterrcorrections[2-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][IODPPOSITION],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[3-i][DELTAAF0],options->pegasusfs,
						0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[3-i][IODPPOSITION]);
				}
			} else { //sbasblock->longtermsaterrcorrections[2][VELOCITYCODE]==1) 
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15.7f%c%-15.7f%c%-15.7f%c%-15E%c%-5d%c    %-d%c       %-d%c     %-2d%c      %-3d%c    %-8.3f%c%-8.3f%c%-8.3f%c%-15E%c%-15E%c%-15E%c%-15E%c%-15E%c%-5d%c    %-d\n",
						(int)sbasblock->longtermsaterrcorrections[2-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF0],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAXRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAYRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF1],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][TIMEOFDAYAPPLICABILITY],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][IODPPOSITION],options->pegasusfs,
						0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0);
				} else {
					ret=fprintf(fdlist[fdSLOWCORRECTIONS],"%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%.7f%c%.7f%c%.7f%c%E%c%d%c%d%c%d%c%d%c%d%c%.3f%c%.3f%c%.3f%c%E%c%E%c%E%c%E%c%E%c%d%c%d\n",
						(int)sbasblock->longtermsaterrcorrections[2-i][VELOCITYCODE],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][PRNMASKNUMBER],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][ISSUEOFDATA],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAX],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAY],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZ],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF0],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAXRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAYRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAZRATEOFCHANGE],options->pegasusfs,
						sbasblock->longtermsaterrcorrections[2-i][DELTAAF1],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][TIMEOFDAYAPPLICABILITY],options->pegasusfs,
						(int)sbasblock->longtermsaterrcorrections[2-i][IODPPOSITION],options->pegasusfs,
						0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0.0,options->pegasusfs,0,options->pegasusfs,0);
				}
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSLOWCORRECTIONS]);
				printError(aux,options);
			}
			break;
		case (INTEGRITYINFO):
			//Print Integrity (Message type 6)
			if(options->pegasusaligned==1) {
				len=sprintf(aux,"%-4d%c        %-9.2f%c  %-3d%c   %-d%c       %-d%c       %-d%c       %-d%c       ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODF[1],options->pegasusfs,sbasblock->IODF[2],options->pegasusfs,sbasblock->IODF[3],options->pegasusfs);
			} else {
				len=sprintf(aux,"%d%c%.2f%c%d%c%d%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODF[1],options->pegasusfs,sbasblock->IODF[2],options->pegasusfs,sbasblock->IODF[3],options->pegasusfs);
			}
			for(i=0;i<51;i++) {
				if(i==50) {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d",sbasblock->UDREIacu[i]);
					} else {
						len+=sprintf(&aux[len],"%d",sbasblock->UDREIacu[i]);
					}
				} else {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d%c        ",sbasblock->UDREIacu[i],options->pegasusfs);
					} else {
						len+=sprintf(&aux[len],"%d%c",sbasblock->UDREIacu[i],options->pegasusfs);
					}
				}
			}
			ret=fprintf(fdlist[fdINTEGRITY],"%s\n",aux);
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdINTEGRITY]);
				printError(aux,options);
			}
			break;
		case(FASTCORRECTIONSDEGRADATIONFACTOR):
			//Print Integrity (Message type 7)
			if(options->pegasusaligned==1) {
				len=sprintf(aux,"%-4d%c        %-9.2f%c  %-3d%c     %-2d%c       %-2d%c       ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->tlat,options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			} else {
				len=sprintf(aux,"%d%c%.2f%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->tlat,options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			}
			for(i=0;i<51;i++) {
				if(i==50) {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d",sbasblock->aiind[i]);
					} else {
						len+=sprintf(&aux[len],"%d",sbasblock->aiind[i]);
					}
				} else {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-2d%c     ",sbasblock->aiind[i],options->pegasusfs);
					} else {
						len+=sprintf(&aux[len],"%d%c",sbasblock->aiind[i],options->pegasusfs);
					}
				}
			}
			ret=fprintf(fdlist[fdFASTDEGRADATION],"%s\n",aux);
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdFASTDEGRADATION]);
				printError(aux,options);
			}
			break;
		case(DEGRADATIONPARAMETERS):
			//Print Degradation parameters (Message type 10)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdDEGRADATION],"%-4d%c        %-9.2f%c  %-3d%c     %-5.3f%c    %-5.3f%c        %-7.5f%c     %-3d%c         %-5.3f%c       %-3d%c         %-6.4f%c       %-7.5f%c    %-3d%c      %-4.1f%c    %-5.3f%c          %-3d%c       %-8.6f%c       %-d%c            %-d%c            %-4.1f\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					 sbasblock->degradationfactors[BRRC],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCLSB],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCV1],options->pegasusfs,
					 (int)sbasblock->degradationfactors[ILTCV1],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCV0],options->pegasusfs,
					 (int)sbasblock->degradationfactors[ILTCV0],options->pegasusfs,
					 sbasblock->degradationfactors[CGEOLSB],options->pegasusfs,
					 sbasblock->degradationfactors[CGEOV],options->pegasusfs,
					 (int)sbasblock->degradationfactors[IGEO],options->pegasusfs,
					 sbasblock->degradationfactors[CER],options->pegasusfs,
					 sbasblock->degradationfactors[CIONOSTEP],options->pegasusfs,
					 (int)sbasblock->degradationfactors[IIONO],options->pegasusfs,
					 sbasblock->degradationfactors[CIONORAMP],options->pegasusfs,
					 (int)sbasblock->degradationfactors[RSSUDRE],options->pegasusfs,
					 (int)sbasblock->degradationfactors[RSSIONO],options->pegasusfs,
					 sbasblock->degradationfactors[CCOVARIANCE]);
			} else {
				ret=fprintf(fdlist[fdDEGRADATION],"%d%c%.2f%c%d%c%.3f%c%.3f%c%.5f%c%d%c%.3f%c%d%c%.4f%c%.5f%c%d%c%.1f%c%.3f%c%d%c%.6f%c%-d%c%-d%c%.1f\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					 sbasblock->degradationfactors[BRRC],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCLSB],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCV1],options->pegasusfs,
					 (int)sbasblock->degradationfactors[ILTCV1],options->pegasusfs,
					 sbasblock->degradationfactors[CLTCV0],options->pegasusfs,
					 (int)sbasblock->degradationfactors[ILTCV0],options->pegasusfs,
					 sbasblock->degradationfactors[CGEOLSB],options->pegasusfs,
					 sbasblock->degradationfactors[CGEOV],options->pegasusfs,
					 (int)sbasblock->degradationfactors[IGEO],options->pegasusfs,
					 sbasblock->degradationfactors[CER],options->pegasusfs,
					 sbasblock->degradationfactors[CIONOSTEP],options->pegasusfs,
					 (int)sbasblock->degradationfactors[IIONO],options->pegasusfs,
					 sbasblock->degradationfactors[CIONORAMP],options->pegasusfs,
					 (int)sbasblock->degradationfactors[RSSUDRE],options->pegasusfs,
					 (int)sbasblock->degradationfactors[RSSIONO],options->pegasusfs,
					 sbasblock->degradationfactors[CCOVARIANCE]);
			}
				if(ret<0) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdDEGRADATION]);
						printError(aux,options);
				}
			break;
		case(IONOSPHERICGRIDPOINTSMASKS):
			//First we need to extract the hexadecimal string corresponding to the IGP Mask
			if(sourcefile==0) {
				//The origin file is RINEX B
				//First join the hexadecimal message in one string
				for(i=1;i<numlines;i++) {
					//Compute the number of records (columns) in the current line (normally the last one is not full)
					if(i==numlines-1) {
						numberofcolumns=sbasblock->halfdatalength%18;
					} else {
						numberofcolumns=18;
					}

					//Read lines
					for(j=0;j<numberofcolumns;j++) {
						getstr(&hexstring[18*2*(i-1)+2*j],line[i],linelen[i],7+3*j,2);
					}
				}	

			} else {
				//The origin file is EMS
				if(sbasblock->messagetype<10) {	
					if (line[0][24]==' ') {
						getstr(hexstring,line[0],linelen[0],25,sbasblock->datalength);	
					} else {
						getstr(hexstring,line[0],linelen[0],24,sbasblock->datalength);	
					}
				} else {
					getstr(hexstring,line[0],linelen[0],25,sbasblock->datalength);
				}
			}

			
			//Convert the hexadecimal string to a binary string (1 bit per byte)
			strhextostrbin(hexstring,sbasblock->datalength,binarystring);
			
			//Extract the IGP Mask in binary string
			getstr(aux,binarystring,(int)strlen(binarystring),24,201);

			//Add the 7 trailing zeros to the IGP Mask
			len=(int)strlen(aux);
			sprintf(&aux[len],"0000000");

			//Convert from binary to hexadecimal
			strbintostrhex(aux,208,hexstring,1);

			//Print Ionospheric grid (Message type 18)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdIONOSPHERICGRID],"%-4d%c        %-9.2f%c  %-3d%c     %-2d%c     %-2d%c     %-d%c        \"%s\"\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->igpmaskmessage[NUMBEROFBANDS],options->pegasusfs,
					(int)sbasblock->igpmaskmessage[BANDNUMBER],options->pegasusfs,
					(int)sbasblock->igpmaskmessage[IODIPOS],options->pegasusfs,
					hexstring);
			} else {
				ret=fprintf(fdlist[fdIONOSPHERICGRID],"%d%c%.2f%c%d%c%d%c%d%c%d%c\"%s\"\n",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->igpmaskmessage[NUMBEROFBANDS],options->pegasusfs,
					(int)sbasblock->igpmaskmessage[BANDNUMBER],options->pegasusfs,
					(int)sbasblock->igpmaskmessage[IODIPOS],options->pegasusfs,
					hexstring);
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdIONOSPHERICGRID]);
				printError(aux,options);
			}
			
			break;
		case(IONOSPHERICDELAYCORRECTIONS):
			//Print Ionospheric corrections (message type 26)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdIONOSPHERICCORRECTIONS],"%-4d%c        %-9.2f%c  %-3d%c   %-2d%c   %-2d%c   %-d%c      ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][BANDNUMBER],options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][BLOCKID],options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][IODIPOS],options->pegasusfs);
			} else {
				ret=fprintf(fdlist[fdIONOSPHERICCORRECTIONS],"%d%c%.2f%c%d%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][BANDNUMBER],options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][BLOCKID],options->pegasusfs,
					(int)sbasblock->ionodelayparameters[0][IODIPOS],options->pegasusfs);
			}
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdIONOSPHERICCORRECTIONS]);
				printError(aux,options);
			}

			//Write IGP Vertical Delay and GIVEI
			aux[0]='\0';		//Initialize aux to empty
			len=0;
			for(i=0;i<15;i++) {
				if(sbasblock->ionodelayparameters[i][IGPVERTICALDELAY]==-1)  igpverticaldelay=63.875;
				else igpverticaldelay=sbasblock->ionodelayparameters[i][IGPVERTICALDELAY];
				if(i==14) {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-6.3f%c     %-2d",igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI]); //Write IGP and GIVEI
					} else {
						len+=sprintf(&aux[len],"%.3f%c%d",igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI]); //Write IGP and GIVEI
					}
				} else {
					if(options->pegasusaligned==1) {
						len+=sprintf(&aux[len],"%-6.3f%c     %-2d%c        ",igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI],options->pegasusfs); //Write IGP and GIVEI
					} else {
						len+=sprintf(&aux[len],"%.3f%c%d%c",igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI],options->pegasusfs); //Write IGP and GIVEI
					}
				}
			}

			ret=fprintf(fdlist[fdIONOSPHERICCORRECTIONS],"%s\n",aux);
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdIONOSPHERICCORRECTIONS]);
				printError(aux,options);
			}

			break;
		case(SBASSERVICEMESSAGE):
			//Print SBAS Service message (message type 27)
			if(options->pegasusaligned==1) {
				ret=fprintf(fdlist[fdSERVICEREGION27],"%-4d%c        %-9.2f%c  %-3d%c   %-d%c      %-d%c    %-d%c     %-d%c    %-d%c    %-2d%c       %-2d%c       ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->servicemessage[IODSPOS],options->pegasusfs,
					(int)sbasblock->servicemessage[NUMBERSERVICEMESSAGES],options->pegasusfs,
					(int)sbasblock->servicemessage[SERVICEMESSAGENUMBER],options->pegasusfs,
					(int)sbasblock->servicemessage[NUMBEROFREGIONS],options->pegasusfs,
					(int)sbasblock->servicemessage[PRIORITYCODE],options->pegasusfs,
					(int)sbasblock->servicemessage[UDREINSIDEIND],options->pegasusfs,
					(int)sbasblock->servicemessage[UDREOUTSIDEIND],options->pegasusfs);
			} else {
				ret=fprintf(fdlist[fdSERVICEREGION27],"%d%c%.2f%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,
					(int)sbasblock->servicemessage[IODSPOS],options->pegasusfs,
					(int)sbasblock->servicemessage[NUMBERSERVICEMESSAGES],options->pegasusfs,
					(int)sbasblock->servicemessage[SERVICEMESSAGENUMBER],options->pegasusfs,
					(int)sbasblock->servicemessage[NUMBEROFREGIONS],options->pegasusfs,
					(int)sbasblock->servicemessage[PRIORITYCODE],options->pegasusfs,
					(int)sbasblock->servicemessage[UDREINSIDEIND],options->pegasusfs,
					(int)sbasblock->servicemessage[UDREOUTSIDEIND],options->pegasusfs);
			}
				if(ret<0) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION27]);
						printError(aux,options);
				}

			//Write LAT1 LON1 LAT2 LON2 RS 
			aux[0]='\0';		//Initialize aux to empty
			len=0;
			for(i=0;i<5;i++) {
				if(i>=(int)sbasblock->servicemessage[NUMBEROFREGIONS]) {
					//If there are not five regions fill with zeros the missing regions
					if(i==4) {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						}
					} else {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d%c     ",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						}
					}
				} else {
					if(i==4) {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d",
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE]); 
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d",
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE]); 
						}
					} else {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d%c     ",
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE],options->pegasusfs); 
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c",
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE],options->pegasusfs); 
						}

					}
				}
			}

			ret=fprintf(fdlist[fdSERVICEREGION27],"%s\n",aux);
			if(ret<0) {
				fclose(readfd);         //Close RINEXB or EMS file where the data has been read
				closefiles(fdlist,18);  //Close all other files before exiting
				sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION27]);
				printError(aux,options);
			}

			break;
		case(CLOCKEPHEMERISCOVARIANCEMATRIX):
			//Print SBAS Service Region (message type 28)
			if((int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]==-1) {
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSERVICEREGION28],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c      ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,0,options->pegasusfs);
				} else {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%d%c%.2f%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,0,options->pegasusfs);
				}
			} else {
				if ( options->pegasusaligned == 1 ) {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c      ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION],options->pegasusfs);
				} else {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%d%c%.2f%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION],options->pegasusfs);
				}
			}
				if ( ret < 0 ) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION28]);
						printError(aux,options);
				}

			aux[0]='\0';		//Initialize aux to empty
			len=0;
			for (i=0;i<2;i++) {
				if (i>=(int)sbasblock->numclockephemeriscovariance || (int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]==-1) {
					// If we exceed the number of satellites fill with zeros
					if ( i == 0 ) {
						if (options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   ",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						}
					} else {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						}

					}
				} else {
					scalefactor=sbasblock->clockephemeriscovariance[i][SCALEFACTOR];
					if ( i == 0 ) {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   ",
								(int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								(int)sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E11]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E22]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E33]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E44]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E12]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E13]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E14]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E23]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E24]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E34]/scalefactor),options->pegasusfs);
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",
								(int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								(int)sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E11]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E22]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E33]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E44]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E12]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E13]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E14]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E23]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E24]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E34]/scalefactor),options->pegasusfs);
						}
					} else {
						if(options->pegasusaligned==1) {
							len+=sprintf(&aux[len],"%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d",
								(int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								(int)sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E11]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E22]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E33]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E44]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E12]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E13]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E14]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E23]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E24]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E34]/scalefactor));
						} else {
							len+=sprintf(&aux[len],"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",
								(int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								(int)sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E11]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E22]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E33]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E44]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E12]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E13]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E14]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E23]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E24]/scalefactor),options->pegasusfs,
								(int)(sbasblock->clockephemeriscovariance[i][E34]/scalefactor));
						}
					}
				}
			}

			ret=fprintf(fdlist[fdSERVICEREGION28],"%s\n",aux);
				if(ret<0) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION28]);
						printError(aux,options);
				}

			break;

		case (GEOSATELLITEALMANACS):
			//Print SBAS Almanac (message type 17)
			for(i=0;i<sbasblock->numgeoalmanacs;i++) {
				aux[0]='\0';		//Initialize aux to empty
				len=0;
				len+=sprintf(&aux[len],"*** Week %4d almanac for PRN-%3d *******\n",GPSweek,(int)sbasblock->geoalmanacsmessage[i][PRNNUMBER]);
				len+=sprintf(&aux[len],"RX_WEEK               : %-4d\n",GPSweek);
				len+=sprintf(&aux[len],"RX_TOM                : %-9.2f\n",SoW);
				len+=sprintf(&aux[len],"PRN                   : %-3d\n",sbasblock->PRN);
				len+=sprintf(&aux[len],"DATA_PRN              : %-3d\n",(int)sbasblock->geoalmanacsmessage[i][PRNNUMBER]);
				len+=sprintf(&aux[len],"DATA_ID               : %-d\n",(int)sbasblock->geoalmanacsmessage[i][DATAID]);
				len+=sprintf(&aux[len],"HEALTH                : %-3d\n",(int)sbasblock->geoalmanacsmessage[i][HEALTHPROVIDER]);
				len+=sprintf(&aux[len],"DAYTIME_APPLICABILITY : %-5d\n",(int)sbasblock->geoalmanacsmessage[i][T0ALMANAC]);
				len+=sprintf(&aux[len],"DAY_OF_WEEK           : %-d\n",1+(int)SoW/86400);	//Day of week goes from 1 to 7
				len+=sprintf(&aux[len],"WEEK_APPLICABILITY    : %-4d\n",GPSweek);
				len+=sprintf(&aux[len],"XGEO                  : %19.12E\n",sbasblock->geoalmanacsmessage[i][XGALMANAC]);
				len+=sprintf(&aux[len],"YGEO                  : %19.12E\n",sbasblock->geoalmanacsmessage[i][YGALMANAC]);
				len+=sprintf(&aux[len],"ZGEO                  : %19.12E\n",sbasblock->geoalmanacsmessage[i][ZGALMANAC]);
				len+=sprintf(&aux[len],"XGEO_RATE             : %19.12E\n",sbasblock->geoalmanacsmessage[i][XGALMANACRATEOFCHANGE]);
				len+=sprintf(&aux[len],"YGEO_RATE             : %19.12E\n",sbasblock->geoalmanacsmessage[i][YGALMANACRATEOFCHANGE]);
				len+=sprintf(&aux[len],"ZGEO_RATE             : %19.12E\n",sbasblock->geoalmanacsmessage[i][ZGALMANACRATEOFCHANGE]);

				ret=fprintf(fdlist[fdALMANAC],"%s\n",aux);
					if(ret<0) {
							fclose(readfd);         //Close RINEXB or EMS file where the data has been read
							closefiles(fdlist,18);  //Close all other files before exiting
							sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdALMANAC]);
							printError(aux,options);
					}

				//Save the last Health status read
				lasthealthlist[(int)sbasblock->geoalmanacsmessage[i][PRNNUMBER]-120]=sbasblock->geoalmanacsmessage[i][HEALTHSTATUS];
			}

			break;

		case (GEONAVIGATIONMESSAGE):
			//Print Navigation data in Rinex 2.1 format (message type 9)
			/*Rinex v2.1 specifications (from http://igscb.jpl.nasa.gov/igscb/data/format/rinex211.txt)

			  The "Transmission Time of Message" (PRN / EPOCH / SV CLK header record) is
			  expressed in GPS seconds of the week. It marks the beginning of the message
			  transmission. It has to refer to the same GPS week as the "Epoch of
			  Ephemerides". It has to be adjusted by - or + 604800 seconds, if necessary
			  (which would make it lower than zero or larger than 604800, respectively).
			  It is a redefinition of the Version 2.10 "Message frame time".

			 "Health" shall be defined as follows:

			  - Bits 0 to 3 equal to Health in Message Type 17 (MT17)
			  - bit 4 is set to 1 if MT17 health is unavailable
			  - bit 5 is set to 1 if the URA index is equal to 15

			  In the SBAS message definitions bit 3 of the health is currently marked as
			  'reserved'.  
			  In case of bit 4 set to 1, it is recommended to set bits 0,1,2,3 to 1, too.

			"User Range Accuracy" (URA):

			  The same convention for converting the URA index to metres is used as
			  with GPS. Set URA = 32767 metres if URA index = 15.

			"IODN" (Issue Of Data Navigation)

			  The IODN is defined as the 8 first bits after the message type 9,
			  called IODN in RTCA DO229, Annex A and Annex B and called "spare" in Annex C.*/




			// Get the calendar time in transmission time (we have to take out the travelling time and the time to receive all the message)
			transtime.MJDN=sbasblock->t.MJDN;
			transtime.SoD=sbasblock->t.SoD-1.1;

			if (transtime.SoD<0) {
				transtime.SoD+=86400;
				transtime.MJDN--;
			}

			// Save the first day of ephemerides read in the file
			if (firstbrdcday==-1) firstbrdcday=sbasblock->t.MJDN;

			// Get the time of ephemerides
			toe.MJDN=transtime.MJDN;
			toe.SoD=sbasblock->geonavigationmessage[T0NAV];
			

			if (transtime.MJDN<sbasblock->t.MJDN && sbasblock->t.MJDN<=firstbrdcday && (int)transtime.SoD==86399 && sourcefile==1) {
				// This is the special case when in an EMS file, a navigation message is given in SoD 0, so the transmission time and toe are from previous day
				previousday=1;
			// Check if time given if toe (in seconds of day) is greater than the seconds of day of the transmission time
			} else if ((int)(toe.SoD-transtime.SoD)>40000) {
				// SoD of toe if greater than transmission time SoD, so the toe refers to the previous day
				toe.MJDN--;
				// We also have to set previousday=1 to indicate that we have to write data to the file of previous day,
				// If the file contains more than one day of data, the following days will be written in the current day file, not the previous one.
				if (sbasblock->t.MJDN<=firstbrdcday) {
					previousday=1;	
				}
			} else if (transtime.SoD>80000 && toe.SoD<3600) {
				//If transmission time is close to the end of the day and toe is very small, this means that toe refers to the next day
				//The limits imposed in this if statement are arbitrary
				toe.MJDN++;
			}

			
			// Get the calendar time for toe (We use t2tm without localtime due to sometimes there was an hour shift)
			t2tmnolocal(&toe,&tm,&seconds);

			// Calculate GPS Week and Seconds of Week for time of ephemeris
			ttime2gpswsnoroll(&toe, &GPSweektoe, &SoWtoe);

			// Calculate GPS Week and Seconds of Week for transmission time
			ttime2gpswsnoroll(&transtime, &GPSweektrans, &SoWtrans);

			// Check if GPS Week of toe is the same for GPS Week of transmission time
			if(GPSweektoe<GPSweektrans) {
				// GPS Week of toe is smaller than GPS Week of transmission time (due to toe referred to the previous day)
				// We have to substract 604800 seconds so the transmission time refers to the same week as the toe
				transtimesecadjusted=SoWtrans-604800;
			} else {
				transtimesecadjusted=SoWtrans;
			}

			// Set health
			health=lasthealthlist[sbasblock->PRN-120];

			// Get URA value. If URA Index is 15, set to 32767 metres (according to RINEX v2.11) and set bit 5 of health to 1 (add 32)
			uravalue=sbasblock->geonavigationmessage[URANOMINALVALUE];
			if(uravalue==-1) {
				uravalue=32767;
				health+=32;
			}

			// If we don't have the health status put zero. Else just put the last four bits (LSB) of the health status bits
			if(options->pegasuspurerinex==0) {
				if(lasthealthlist[sbasblock->PRN-120]==31) {
					//health=0;
					health=1;
				} else {
					health=lasthealthlist[sbasblock->PRN-120];
				}
			}

			// Check in what file do we have to print
			if(previousday) {		
				filetoprint=fdEPHEMERISPREVDAY;
				*prevday=1;	//Set to 1 to indicate that we have written a RINEX H file from the previous day
			} else {
				filetoprint=fdEPHEMERIS;
			}

			// Print data
			if(options->pegasuspurerinex==0) {
				//Write the file the same way as Pegasus converter
				ret=fprintf(fdlist[filetoprint],"%02d %02d %2d %2d %2d %2d%5.1f%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n", 				 	 sbasblock->PRN%100,tm.tm_year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,
						sbasblock->geonavigationmessage[AGF0],
						sbasblock->geonavigationmessage[AGF1],
							SoWtrans, /*Time in Transmission time*/ 
							//transtimesecadjusted, /*Time in Transmission time, referring to the same week as toe*/ 
						sbasblock->geonavigationmessage[XG]/1000,
						sbasblock->geonavigationmessage[XGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[XGACCELERATION]/1000,
						health, 
						sbasblock->geonavigationmessage[YG]/1000,
						sbasblock->geonavigationmessage[YGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[YGACCELERATION]/1000,
						uravalue,	/*URA in metres*/
						sbasblock->geonavigationmessage[ZG]/1000,
						sbasblock->geonavigationmessage[ZGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[ZGACCELERATION]/1000,
						sbasblock->geonavigationmessage[IODNPOS]);
			} else {
				ret = fprintf(fdlist[filetoprint],"%02d %02d %2d %2d %2d %2d%5.1f%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n   %19.12E%19.12E%19.12E%19.12E\n", 				 	 sbasblock->PRN%100,tm.tm_year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,
						sbasblock->geonavigationmessage[AGF0],
						sbasblock->geonavigationmessage[AGF1],
							transtimesecadjusted, /*Time in Transmission time, referring to the same week as toe*/ 
						sbasblock->geonavigationmessage[XG]/1000,
						sbasblock->geonavigationmessage[XGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[XGACCELERATION]/1000,
						health, 
						sbasblock->geonavigationmessage[YG]/1000,
						sbasblock->geonavigationmessage[YGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[YGACCELERATION]/1000,
						uravalue,	/*URA in metres*/
						sbasblock->geonavigationmessage[ZG]/1000,
						sbasblock->geonavigationmessage[ZGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[ZGACCELERATION]/1000,
						sbasblock->geonavigationmessage[IODNPOS]);
			}

				if ( ret < 0 ) {
					fclose(readfd);         // Close RINEXB or EMS file where the data has been read
					closefiles(fdlist,18);  // Close all other files before exiting
					sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[filetoprint]);
					printError(aux,options);
				}
			break;

		default:
			// Messages with no data or that do no have any effect. No need to print anything
			// Message WAAS Network Time/UTC/GLONASS is not read by Pegasus
			break;
	}
}

/*****************************************************************************
 * Name        : printSBASCORR
 * Description : Prints the SBASCORR data line for SBAS 1F
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * int  measIndex                           I  N/A  Selected measurement
 * double  geometricDistance                I    m  Geometric distance between satellite and receiver
 * double  satelliteClockModel              I    m  Satellite clock error
 * double  relativityModel                  I    m  Relativity model
 * double  troposphereModel                 I    m  Troposphere model
 * double  ionosphereModel                  I    m  Ionosphere model
 * double  TGDModel                         I    m  TGD model
 * TConstellation  *constellation           I  N/A  TConstellation structure where 
 *                                                   satellite data is stored
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASCORR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, int measIndex, double geometricDistance, double satelliteClockModel, double relativityModel, double troposphereModel, double ionosphereModel, double TGDModel, TConstellation *constellation, TOptions *options) {
	int						i,j;
	int						ret;
	int						IODE;
	int						freq;
	int						SVN;
	enum MeasurementType	meas;
	enum SatelliteBlock		satBlock;	
	double					measurement;
	double					model,prefit;
	double					smoothWith,smoothedVal;
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int				initialized=0;
	#pragma omp threadprivate(initialized)
	static char				receiverid[5];
	#pragma omp threadprivate(receiverid)

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized=1;
		// Convert receiver name to lower case
		for (i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}


	meas=epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex];
	freq=getFrequencyInt(meas);
	//In SBAS, only C1C measurement is used and it is in position 0 of filter list (first position)
	ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,&meas,&freq,&measurement,&model,0);
	if ( ret != 1 ) {
		return;
	}

	if ( SBAScorr->IOD != -1 ) {
		IODE = SBAScorr->IOD;
	} else if (SBAScorr->IODnoSBAS!=-1) {
		IODE = -SBAScorr->IODnoSBAS;
	} else {
		IODE = 999;
	}

	// Smoothing
	if ( options->smoothEpochs != 0 && options->filterMeasSmoothed[ROVERPOS][epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN][0] == 1 ) {
		ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,options->filterSmoothMeasList[ROVERPOS][epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN][0],&freq,&smoothWith,NULL,0);
		if ( ret != 1 ) {
			return;
		}
		prefit = epoch->cycleslip.smoothedMeas[j][0] + smoothWith - model;
		smoothedVal = epoch->cycleslip.smoothedMeas[j][0] + smoothWith;
	} else {
		prefit = measurement - model;
		smoothedVal=measurement;
	}

	if (options->printV5format==0) {
		//Get satellite block and SVN
		if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN] = getConstellationElement(epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]!=NULL) {
				satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
				SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN] = getConstellationElement(epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,&epoch->t,constellation);
				if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]!=NULL) {
					satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
					SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
				SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
			}
		}

		sprintf(printbufferSBASCORR[satIndex],"SBASCORR    %29s %3s %3d %-15s %4d %3d %6d %8.3f %8.3f %3s %3d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %7.5f %14.4f %14.4f %7.1f %7.1f %7.1f %14.4f %14.4f %14.4f %9.5f %9.5f %9.5f %9.5f %2d %2d %2d %2d %2d %4d %2d %2d %2d %2d\n",
		/*2*/		epoch->tSoDHourStr, 		//Year
		/*3*/			//DoY
		/*4*/			//Seconds of day
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*7*/		epoch->sat[satIndex].PRN,
		/*8*/		satblock2satblockstr(satBlock),
		/*9*/		SVN,
		/*10*/		epoch->cycleslip.narc[j],
		/*11*/		epoch->cycleslip.arcLength[j]==0?1:epoch->cycleslip.arcLength[j],
		/*12*/		epoch->sat[satIndex].elevation*r2d, //Elevation (in degrees)
		/*13*/		epoch->sat[satIndex].azimuth*r2d,  //Azimuth (in degrees)
		/*14*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*15*/		SBASdata[options->GEOindex].PRN,
		/*16*/		prefit,
		/*17*/		measurement,			//C1 raw + user added noise (in metres)
		/*18*/		smoothedVal,			//C1 smoothed + user added noise (if smoothing is disabled, then is C1 raw + user added noise) (in metres)
		/*19*/		geometricDistance, 		//With SBAS corrections (in metres)
		/*20*/		relativityModel,		//With SBAS corrections (in metres)
		/*21*/		satelliteClockModel, 	//With SBAS corrections (in metres)
		/*22*/		TGDModel,				//From navigation file (in metres)
		/*23*/		epoch->IPPlat,			//Ionospheric pierce point latitude (-90..90º)
		/*24*/		epoch->IPPlon,			//Ionospheric pierce point longitude (0..360º)
		/*25*/		ionosphereModel,		//In metres
		/*26*/		troposphereModel,		//In metres
		/*27*/		SBAScorr->PRC,	 		//PRC Fast Correction applied to the satellite (in metres)
		/*28*/		SBAScorr->RRCtime,		//RRC Fast Correction applied to the satellite (in metres)
		/*29*/		SBAScorr->fastcorrdegfactor,	//Fast correction degradation factor (in metres/seconds^2)
		/*30*/		SBAScorr->fastcorrtmout,	//PRC time out (in seconds)
		/*31*/		SBAScorr->fastcorrsmallertmout,	//RRC time out (smallest time out for all satellites) (in seconds)
		/*32*/		SBAScorr->tPRC,			//Time (seconds of day) used for computing PRC timeout
		/*33*/		SBAScorr->tudre,		//Time (seconds of day) used for computing sigma UDRE timeout
		/*34*/		SBAScorr->tu,			//Time (seconds of day) used for computing fast correction degradation
		/*35*/		SBAScorr->SatCoordbrdc[0]+SBAScorr->SatCoordCor[0],	//X component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres) 
		/*36*/		SBAScorr->SatCoordbrdc[1]+SBAScorr->SatCoordCor[1],	//Y component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
		/*37*/		SBAScorr->SatCoordbrdc[2]+SBAScorr->SatCoordCor[2],	//Z component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
		/*38*/		SBAScorr->SatCoordCor[0],	//Long term correction to be applied to the X component of the satellite (in metres)
		/*39*/		SBAScorr->SatCoordCor[1],	//Long term correction to be applied to the Y component of the satellite (in metres)
		/*40*/		SBAScorr->SatCoordCor[2],	//Long term correction to be applied to the Z component of the satellite (in metres)
		/*41*/		SBAScorr->ClockCor,		//Long term correction to be applied to the satellite clock (in metres)
		/*42*/		SBAScorr->fastcorIODP,		//IODP used for fast corrections
		/*43*/		SBAScorr->fastcorIODF,		//IODF in messages type 2-5,24 for fast corrections
		/*44*/		SBAScorr->fastcorPRNpos+1,	//Satellite position in the fast correction mask (1..51)
		/*45*/		SBAScorr->longtermIODP,		//IODP used for long term corrections
		/*46*/		SBAScorr->longtermPRNpos+1,	//Satellite position in the long term correction mask (1..51)
		/*47*/		IODE,				//IODE used for broadcast ephemeris
		/*48*/		SBAScorr->serviceIODS,		//IODS used for service message
		/*49*/		SBAScorr->covarianceIODP,	//IODP used for Covariance matrix
		/*50*/		SBAScorr->covariancePRNpos+1,	//Satellite position in the covariance mask (1..51)
		/*51*/		SBAScorr->ionomodelflag);        //Flag to indicate which iono model is used (-1->no model, 0->SBASiono, 1->Klobuchar, 2->Other model)	
	} else{
		sprintf(printbufferSBASCORR[satIndex],"SBASCORR    %4s %3s %3s %3d %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %7.5f %14.4f %14.4f %7.1f %7.1f %7.1f %14.4f %14.4f %14.4f %9.5f %9.5f %9.5f %9.5f %2d %2d %2d %2d %2d %4d %2d %2d %2d %2d %8.3f %8.3f\n",
		/*2*/		receiverid,
		/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*5*/		epoch->sat[satIndex].PRN,
		/*6*/		epoch->tStr, 		//Year
		/*7*/			//DoY
		/*8*/			//Seconds of day
		/*9*/		epoch->GPSweek,
		/*10*/		epoch->SoW,
		/*11*/		SBASdata[options->GEOindex].PRN,
		/*12*/		prefit,
		/*13*/		measurement,			//C1 raw + user added noise (in metres)
		/*14*/		smoothedVal,			//C1 smoothed + user added noise (if smoothing is disabled, then is C1 raw + user added noise) (in metres)
		/*15*/		geometricDistance, 		//With SBAS corrections (in metres)
		/*16*/		relativityModel,		//With SBAS corrections (in metres)
		/*17*/		satelliteClockModel, 	//With SBAS corrections (in metres)
		/*18*/		TGDModel,				//From navigation file (in metres)
		/*19*/		epoch->IPPlat,			//Ionospheric pierce point latitude (-90..90º)
		/*20*/		epoch->IPPlon,			//Ionospheric pierce point longitude (0..360º)
		/*21*/		ionosphereModel,		//In metres
		/*22*/		troposphereModel,		//In metres
		/*23*/		SBAScorr->PRC,	 		//PRC Fast Correction applied to the satellite (in metres)
		/*24*/		SBAScorr->RRCtime,		//RRC Fast Correction applied to the satellite (in metres)
		/*25*/		SBAScorr->fastcorrdegfactor,	//Fast correction degradation factor (in metres/seconds^2)
		/*26*/		SBAScorr->fastcorrtmout,	//PRC time out (in seconds)
		/*27*/		SBAScorr->fastcorrsmallertmout,	//RRC time out (smallest time out for all satellites) (in seconds)
		/*28*/		SBAScorr->tPRC,			//Time (seconds of day) used for computing PRC timeout
		/*29*/		SBAScorr->tudre,		//Time (seconds of day) used for computing sigma UDRE timeout
		/*30*/		SBAScorr->tu,			//Time (seconds of day) used for computing fast correction degradation
		/*31*/		SBAScorr->SatCoordbrdc[0]+SBAScorr->SatCoordCor[0],	//X component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres) 
		/*32*/		SBAScorr->SatCoordbrdc[1]+SBAScorr->SatCoordCor[1],	//Y component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
		/*33*/		SBAScorr->SatCoordbrdc[2]+SBAScorr->SatCoordCor[2],	//Z component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
		/*34*/		SBAScorr->SatCoordCor[0],	//Long term correction to be applied to the X component of the satellite (in metres)
		/*35*/		SBAScorr->SatCoordCor[1],	//Long term correction to be applied to the Y component of the satellite (in metres)
		/*36*/		SBAScorr->SatCoordCor[2],	//Long term correction to be applied to the Z component of the satellite (in metres)
		/*37*/		SBAScorr->ClockCor,		//Long term correction to be applied to the satellite clock (in metres)
		/*38*/		SBAScorr->fastcorIODP,		//IODP used for fast corrections
		/*39*/		SBAScorr->fastcorIODF,		//IODF in messages type 2-5,24 for fast corrections
		/*40*/		SBAScorr->fastcorPRNpos+1,	//Satellite position in the fast correction mask (1..51)
		/*41*/		SBAScorr->longtermIODP,		//IODP used for long term corrections
		/*42*/		SBAScorr->longtermPRNpos+1,	//Satellite position in the long term correction mask (1..51)
		/*43*/		IODE,				//IODE used for broadcast ephemeris
		/*44*/		SBAScorr->serviceIODS,		//IODS used for service message
		/*45*/		SBAScorr->covarianceIODP,	//IODP used for Covariance matrix
		/*46*/		SBAScorr->covariancePRNpos+1,	//Satellite position in the covariance mask (1..51)
		/*47*/		SBAScorr->ionomodelflag,        //Flag to indicate which iono model is used (-1->no model, 0->SBASiono, 1->Klobuchar, 2->Other model)	
		/*48*/		epoch->sat[satIndex].elevation*r2d, //Elevation (in degrees)
		/*49*/		epoch->sat[satIndex].azimuth*r2d);  //Azimuth (in degrees)
	}
	// Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if ( options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASCORR[satIndex][8]='*';
	}
}

/*****************************************************************************
 * Name        : printSBASVAR
 * Description : Prints the SBASVAR data line for SBAS 1F
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * TConstellation  *constellation           I  N/A  TConstellation structure where 
 *                                                   satellite data is stored
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASVAR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, TConstellation *constellation, TOptions *options) {
	int    				 	i, j;
	int						SVN;
	enum SatelliteBlock		satBlock;	
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int				initialized = 0;
	#pragma omp threadprivate(initialized)
	static char				receiverid[5];
	#pragma omp threadprivate(receiverid)

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized=1;
		// Convert receiver name to lower case
		for(i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}

	if (options->printV5format==0) {
		//Get satellite block and SVN
		if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]==NULL) {
			//No previous pointer used
			constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN] = getConstellationElement(epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]!=NULL) {
				satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
				SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
			} else {
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			} 
		} else { 
			//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
			if (tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->tDecommissioned)>0) {
				//Not valid anymore, look for a new constellation element
				constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN] = getConstellationElement(epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,&epoch->t,constellation);
				if (constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]!=NULL) {
					satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
					SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
				} else {
					//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
					satBlock=UNKNOWN_BLOCK;
					SVN=-1;
				}
			} else {
				satBlock=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->block;
				SVN=constellation->satLastUsed[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN]->SVN;
			}
		}

		sprintf(printbufferSBASVAR[satIndex],"SBASVAR     %29s %3s %3d %-15s %4d %3d %6d %8.3f %8.3f %3s %3d %14.4f %14.4f %14.4f %8.3f %3d %14.4f %14.4f %14.4f %14.4f %1d %14.4f %14.4f %14.4f %8.3f %8.3f %8.3f\n",
		/*2*/		epoch->tSoDHourStr, 		//Year
		/*3*/			//DoY
		/*4*/			//Seconds of day
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*7*/		epoch->sat[satIndex].PRN,
		/*8*/		satblock2satblockstr(satBlock),
		/*9*/		SVN,
		/*10*/		epoch->cycleslip.narc[j],
		/*11*/		epoch->cycleslip.arcLength[j]==0?1:epoch->cycleslip.arcLength[j],
		/*12*/		epoch->sat[satIndex].elevation*r2d, //Elevation (in degrees)
		/*13*/		epoch->sat[satIndex].azimuth*r2d,  //Azimuth (in degrees)
		/*14*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*15*/		SBASdata[options->GEOindex].PRN,
		/*16*/		sqrt(SBAScorr->SBASsatsigma2),					//Sigma of the total residual error associated to the satellite (in metres)
		/*17*/		sqrt(SBAScorr->sigma2flt),					//Sigma of the residual error associated to the fast and long-term corrections (in metres)
		/*18*/		sqrt(SBAScorr->UDREsigma),					//Sigma of the UDRE (in metres)
		/*19*/		SBAScorr->deltaudre,						//Delta UDRE factor
		/*20*/		SBAScorr->deltaudresource,					//Indicates the data source for Delta UDRE(27 or 28 for their respective message type,-27 or -28 if received any of these message types but there was missing data or was timed out, 0 if no message type received or both received)
		/*21*/		SBAScorr->fastcorrdeg,						//Degradation parameter for fast correction data (in metres)
		/*22*/		SBAScorr->RRCdeg,						//Degradation parameter for range rate correction data (in metres)
		/*23*/		SBAScorr->longtermdegradation+SBAScorr->geonavdegradation,	//Degradation parameter for long term correction data or GEO navigation message data (in metres)
		/*24*/		SBAScorr->enroutedegradation,					//Degradation parameter for en route through NPA applications (in metres)
		/*25*/	   	(int)SBASdata[options->GEOindex].degradationfactors[RSSUDRE],	//Root-sum-square flag
		/*26*/		sqrt(SBAScorr->sigma2iono),					//Sigma of the residual error associated to the ionosheric corrections (in metres)
		/*27*/		sqrt(SBAScorr->sigma2tropo),					//Sigma of the residual error associated to the tropospheric corrections (in metres)
		/*28*/		sqrt(SBAScorr->sigma2air),					//Sigma of the total receiver error (in metres)
		/*29*/		sqrt(SBAScorr->sigma2noise),					//Sigma of the receiver noise (in metres)
		/*30*/		sqrt(SBAScorr->sigma2multipath),				//Sigma of the receiver multipath (in metres)
		/*31*/		sqrt(SBAScorr->sigma2divergence));				//Sigma of the receiver divergence (in metres)
	} else {
		sprintf(printbufferSBASVAR[satIndex],"SBASVAR     %4s %3s %3s %3d %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %8.3f %3d %14.4f %14.4f %14.4f %14.4f %1d %14.4f %14.4f %14.4f %8.3f %8.3f %8.3f %8.3f %8.3f\n",
		/*2*/		receiverid,
		/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*5*/		epoch->sat[satIndex].PRN,
		/*6*/		epoch->tStr, 		//Year
		/*7*/						//DoY
		/*8*/						//Seconds of day
		/*9*/		epoch->GPSweek,
		/*10*/      epoch->SoW,
		/*11*/      SBASdata[options->GEOindex].PRN,
		/*12*/		sqrt(SBAScorr->SBASsatsigma2),					//Sigma of the total residual error associated to the satellite (in metres)
		/*13*/		sqrt(SBAScorr->sigma2flt),					//Sigma of the residual error associated to the fast and long-term corrections (in metres)
		/*14*/		sqrt(SBAScorr->UDREsigma),					//Sigma of the UDRE (in metres)
		/*15*/		SBAScorr->deltaudre,						//Delta UDRE factor
		/*16*/		SBAScorr->deltaudresource,					//Indicates the data source for Delta UDRE(27 or 28 for their respective message type,-27 or -28 if received any of these message types but there was missing data or was timed out, 0 if no message type received or both received)
		/*17*/		SBAScorr->fastcorrdeg,						//Degradation parameter for fast correction data (in metres)
		/*18*/		SBAScorr->RRCdeg,						//Degradation parameter for range rate correction data (in metres)
		/*19*/		SBAScorr->longtermdegradation+SBAScorr->geonavdegradation,	//Degradation parameter for long term correction data or GEO navigation message data (in metres)
		/*20*/		SBAScorr->enroutedegradation,					//Degradation parameter for en route through NPA applications (in metres)
		/*21*/	   	(int)SBASdata[options->GEOindex].degradationfactors[RSSUDRE],	//Root-sum-square flag
		/*22*/		sqrt(SBAScorr->sigma2iono),					//Sigma of the residual error associated to the ionosheric corrections (in metres)
		/*23*/		sqrt(SBAScorr->sigma2tropo),					//Sigma of the residual error associated to the tropospheric corrections (in metres)
		/*24*/		sqrt(SBAScorr->sigma2air),					//Sigma of the total receiver error (in metres)
		/*25*/		sqrt(SBAScorr->sigma2noise),					//Sigma of the receiver noise (in metres)
		/*26*/		sqrt(SBAScorr->sigma2multipath),				//Sigma of the receiver multipath (in metres)
		/*27*/		sqrt(SBAScorr->sigma2divergence),				//Sigma of the receiver divergence (in metres)
		/*28*/		epoch->sat[satIndex].elevation*r2d,				//Elevation (in degrees)
		/*29*/		epoch->sat[satIndex].azimuth*r2d);				//Azimuth (in degrees)
	}
	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if (options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j]<options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASVAR[satIndex][7]='*';
	}
}

/*****************************************************************************
 * Name        : printSBASIONO
 * Description : Prints the SBASIONO data line for SBAS 1F
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * int  satIndex                            I  N/A  Selected satellite
 * int  InterpolationMode                   I  N/A  Interpolation mode
 *                                                  0 -> Square
 *                                                  [1-4] -> Vertex not used in interpolation
 * int  IGP1                                I  N/A  IGP number for upper right corner 
 * int  BandNumber1                         I  N/A  Band number for upper right corner
 * double IGPlat1                           I    º  Latitude for upper right corner
 * double IGPlon1                           I    º  Longitude for upper right corner
 * int  IGP2                                I  N/A  IGP number for upper left corner 
 * int  BandNumber2                         I  N/A  Band number for upper left corner 
 * double IGPlat2                           I    º  Latitude for upper left corner
 * double IGPlon2                           I    º  Longitude for upper left corner
 * int  IGP3                                I  N/A  IGP number for lower right corner 
 * int  BandNumber3                         I  N/A  Band number for lower right corner 
 * double IGPlat3                           I    º  Latitude for lower right corner
 * double IGPlon3                           I    º  Longitude for lower right corner
 * int  IGP4                                I  N/A  IGP number for lower left corner 
 * int  BandNumber4                         I  N/A  Band number for lower left corner 
 * double IGPlat4                           I    º  Latitude for lower left corner
 * double IGPlon4                           I    º  Longitude for lower left corner
 * double  eps_iono[5]                      I    m  Degradation number for the four IGPs
 * double  IGPDelays[5]                     I    m  IGP delays used for interpolation for the four IGPs
 * double  IGPSigma2[5]                     I  m^2  IGP sigma used for interpolation for the four IGPs
 * double  IPPWeight[5]                     I    m  IGP weight for the four IGPs
 * double  Fpp                              I  N/A  Mapping function 
 * double  SlantDelay                       I    m  Slant Delay
 * double  SlantSigma                       I    m  Slant Sigma
 * double  elevation                        I  rad  Satellite elevation
 * double  azimuth                          I  rad  Satelite azimuth
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASIONO (TEpoch  *epoch, TSBASdata *SBASdata, int  satIndex, int  InterpolationMode, int  IGP1, int  BandNumber1, double IGPlat1, double IGPlon1, int  IGP2, int  BandNumber2, double IGPlat2, double IGPlon2, int  IGP3, int  BandNumber3, double IGPlat3, double IGPlon3, int  IGP4, int  BandNumber4, double IGPlat4, double IGPlon4, double  eps_iono[5], double  IGPDelays[5], double  IGPSigma2[5], double  IPPWeight[5], double  Fpp, double  SlantDelay, double  SlantSigma, double elevation, double azimuth, TOptions  *options) {
	int		i,j;

	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int	initialized=0;
	#pragma omp threadprivate(initialized)
	static char	receiverid[5];
	#pragma omp threadprivate(receiverid)


	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized = 1;
		if(options->SBAScorrections>=SBASMaps1freqUsed) {
			//No observation file. Set receiver name as blank
			for (i=0;i<4;i++) {
				receiverid[i]=' ';
			}
			receiverid[4]='\0';
		} else {
			//Convert receiver name to lower case
			for (i=0;i<4;i++) {
				receiverid[i] = tolower(epoch->receiver.name[i]);
			}
			receiverid[4]='\0';
		}
	}

		/* Four points:
	
				  NORTH	   
		(IGPlat2,IGPlon1)   (IGPlat2,IGPlon2)
		  W2=(1-x)*y          W1=x*y
			  v2..............v1
			  .               .
			  .               .
			  .               .
	 WEST     .   IPP         .  EAST
			  .     *         .
			  .     |         .
			  .     |         .
			  v3____..........v4
		  W3=(1-x)*(1-y)      W4=x*(1-y)
		(IGPlat1,IGPlon1)   (IGPlat1,IGPlon2)
				  SOUTH	   
	*/

	if (options->printV5format==0) {
		sprintf(printbufferSBASIONO[satIndex],"SBASIONO     %29s %3s %3d %8.3f %8.3f %3s %3d %8.3f %8.3f %d %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %8.4f %8.4f %8.4f\n",
		/*2*/		epoch->tSoDHourStr, 		//Year
		/*3*/						//DoY
		/*4*/						//Seconds of day
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*7*/		epoch->sat[satIndex].PRN,
		/*8*/		elevation*r2d,								//Elevation (in degrees)
		/*9*/		azimuth*r2d,								//Azimuth (in degrees)
		/*10*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*11*/		SBASdata[options->GEOindex].PRN,
		/*12*/		epoch->IPPlat,								//Ionospheric pierce point latitude (-90..90º)	
		/*13*/		epoch->IPPlon,								//Ionospheric pierce point longitude (0..360º)
		/*14*/		InterpolationMode,							//If 0, square interpolation. If [1-4] indicates the vertex not used
		/*15*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1],		//IODI for vertex 1
		/*16*/		BandNumber1,								//Band Number for vertex 1
		/*17*/		IGP1,									//IGP Number for vertex 1
		/*18*/		SBASdata[options->GEOindex].lastiono[BandNumber1][IGP1].SoD,		//Time of reception of last bit of vertex 1 IGP (in seconds of day)
		/*19*/		(int)IGPlat1,								//Latitude of the IGP for vertex 1 (-90..90º)
		/*20*/		(int)IGPlon1,								//Longitude of the IGP for vertex 1 (0..360º)
		/*21*/		SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP1],		//Iono delay (raw value from MT26) for vertex 1 (metres)
		/*22*/		SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP1],		//Iono sigma (raw value from MT26) for vertex 1 (metres^2)
		/*23*/		eps_iono[1],								//Degradation term for vertex 1 (metres)
		/*24*/		IGPDelays[1],								//Iono delay after interpolation (if required) for vertex 1 (metres)
		/*25*/		IGPSigma2[1],								//Iono sigma after applying degradation and interpolation (if lat=85º) for vertex 1 (metres^2)
		/*26*/		IPPWeight[1],								//Interpolation weight for vertex 1
		/*27*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2],
		/*28*/		BandNumber2,
		/*29*/		IGP2,
		/*30*/		SBASdata[options->GEOindex].lastiono[BandNumber2][IGP2].SoD,
		/*31*/		(int)IGPlat2,
		/*32*/		(int)IGPlon2,
		/*33*/		SBASdata[options->GEOindex].Ionodelay[BandNumber2][IGP2],
		/*34*/		SBASdata[options->GEOindex].Ionosigma[BandNumber2][IGP2],
		/*35*/		eps_iono[2],
		/*36*/		IGPDelays[2],
		/*37*/		IGPSigma2[2],
		/*38*/		IPPWeight[2],
		/*39*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3],
		/*40*/		BandNumber3,
		/*41*/		IGP3,
		/*42*/		SBASdata[options->GEOindex].lastiono[BandNumber3][IGP3].SoD,
		/*43*/		(int)IGPlat3,
		/*44*/		(int)IGPlon3,
		/*45*/		SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP3],
		/*46*/		SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP3],
		/*47*/		eps_iono[3],
		/*48*/		IGPDelays[3],
		/*49*/		IGPSigma2[3],
		/*50*/		IPPWeight[3],
		/*51*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4],
		/*52*/		BandNumber4,
		/*53*/		IGP4,
		/*54*/		SBASdata[options->GEOindex].lastiono[BandNumber4][IGP4].SoD,
		/*55*/		(int)IGPlat4,
		/*56*/		(int)IGPlon4,
		/*57*/		SBASdata[options->GEOindex].Ionodelay[BandNumber4][IGP4],
		/*58*/		SBASdata[options->GEOindex].Ionosigma[BandNumber4][IGP4],
		/*59*/		eps_iono[4],
		/*60*/		IGPDelays[4],
		/*61*/		IGPSigma2[4],
		/*62*/		IPPWeight[4],
		/*63*/		Fpp,									//Mapping function
		/*64*/		SlantDelay,								//Slant delay (metres of L1)
		/*65*/		SlantSigma);							//Slant Sigma (metres of L1)
	} else {
		sprintf(printbufferSBASIONO[satIndex],"SBASIONO    %4s %3s %3s %3d %19s %4d %9.2f %3d %8.3f %8.3f %d %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %8.4f %8.4f %8.4f %5.2f %5.2f\n",
		/*2*/		receiverid,
		/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*5*/		epoch->sat[satIndex].PRN,
		/*6*/		epoch->tStr, 		//Year
		/*7*/						//DoY
		/*8*/						//Seconds of day
		/*9*/		epoch->GPSweek,
		/*10*/		epoch->SoW,
		/*11*/		SBASdata[options->GEOindex].PRN,
		/*12*/		epoch->IPPlat,								//Ionospheric pierce point latitude (-90..90º)	
		/*13*/		epoch->IPPlon,								//Ionospheric pierce point longitude (0..360º)
		/*14*/		InterpolationMode,							//If 0, square interpolation. If [1-4] indicates the vertex not used
		/*15*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1],		//IODI for vertex 1
		/*16*/		BandNumber1,								//Band Number for vertex 1
		/*17*/		IGP1,									//IGP Number for vertex 1
		/*18*/		SBASdata[options->GEOindex].lastiono[BandNumber1][IGP1].SoD,		//Time of reception of last bit of vertex 1 IGP (in seconds of day)
		/*19*/		(int)IGPlat1,								//Latitude of the IGP for vertex 1 (-90..90º)
		/*20*/		(int)IGPlon1,								//Longitude of the IGP for vertex 1 (0..360º)
		/*21*/		SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP1],		//Iono delay (raw value from MT26) for vertex 1 (metres)
		/*22*/		SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP1],		//Iono sigma (raw value from MT26) for vertex 1 (metres^2)
		/*23*/		eps_iono[1],								//Degradation term for vertex 1 (metres)
		/*24*/		IGPDelays[1],								//Iono delay after interpolation (if required) for vertex 1 (metres)
		/*25*/		IGPSigma2[1],								//Iono sigma after applying degradation and interpolation (if lat=85º) for vertex 1 (metres^2)
		/*26*/		IPPWeight[1],								//Interpolation weight for vertex 1
		/*27*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2],
		/*28*/		BandNumber2,
		/*29*/		IGP2,
		/*30*/		SBASdata[options->GEOindex].lastiono[BandNumber2][IGP2].SoD,
		/*31*/		(int)IGPlat2,
		/*32*/		(int)IGPlon2,
		/*33*/		SBASdata[options->GEOindex].Ionodelay[BandNumber2][IGP2],
		/*34*/		SBASdata[options->GEOindex].Ionosigma[BandNumber2][IGP2],
		/*35*/		eps_iono[2],
		/*36*/		IGPDelays[2],
		/*37*/		IGPSigma2[2],
		/*38*/		IPPWeight[2],
		/*39*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3],
		/*40*/		BandNumber3,
		/*41*/		IGP3,
		/*42*/		SBASdata[options->GEOindex].lastiono[BandNumber3][IGP3].SoD,
		/*43*/		(int)IGPlat3,
		/*44*/		(int)IGPlon3,
		/*45*/		SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP3],
		/*46*/		SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP3],
		/*47*/		eps_iono[3],
		/*48*/		IGPDelays[3],
		/*49*/		IGPSigma2[3],
		/*50*/		IPPWeight[3],
		/*51*/		SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4],
		/*52*/		BandNumber4,
		/*53*/		IGP4,
		/*54*/		SBASdata[options->GEOindex].lastiono[BandNumber4][IGP4].SoD,
		/*55*/		(int)IGPlat4,
		/*56*/		(int)IGPlon4,
		/*57*/		SBASdata[options->GEOindex].Ionodelay[BandNumber4][IGP4],
		/*58*/		SBASdata[options->GEOindex].Ionosigma[BandNumber4][IGP4],
		/*59*/		eps_iono[4],
		/*60*/		IGPDelays[4],
		/*61*/		IGPSigma2[4],
		/*62*/		IPPWeight[4],
		/*63*/		Fpp,									//Mapping function
		/*64*/		SlantDelay,								//Slant delay (metres of L1)
		/*65*/		SlantSigma,								//Slant Sigma (metres of L1)
		/*66*/		elevation*r2d,								//Elevation (in degrees)
		/*67*/		azimuth*r2d);								//Azimuth (in degrees)
	}
	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if ( options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence ) {
		//Steady state not reached
		printbufferSBASIONO[satIndex][8]='*';
	}

	if ( options->SBAScorrections>=SBASMaps1freqUsed ) {
		//In SBAS plots mode, do not buffer data
		fprintf(options->outFileStream,"%s",printbufferSBASIONO[satIndex]);
		printbufferSBASIONO[satIndex][0]='\0';
	}
}

/*****************************************************************************
 * Name        : printSBASUNSEL
 * Description : Prints the SBASUNSEL data line for SBAS 1F (printed only when a satellite is discarded)
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * int satIndex                             I  N/A  Selected satellite
 * int errorcode                            I  N/A  Error code indicating the reason for discarding the satellite
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASUNSEL (TEpoch  *epoch, int  satIndex, int errorcode, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions  *options) {
	int				i,j;
	int				GEOPRN;
	char			GEOtext[100];
	char			Alarmtime[100];
	struct tm 		tm;
	double			seconds;
	

	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int		initialized=0;
	#pragma omp threadprivate(initialized)
	static char		receiverid[5];
	#pragma omp threadprivate(receiverid)
	static char 	errorstr[49][MAX_INPUT_LINE];
	#pragma omp threadprivate(errorstr)

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	errorcode=abs(errorcode);

	// Check for options->GEOindex value
	if ( options->GEOindex < 0 ) GEOPRN = -1;
	else GEOPRN=SBASdata[options->GEOindex].PRN;

	if ( initialized == 0 ) {
		initialized = 1;

		if(options->SBAScorrections>=SBASMaps1freqUsed) {
			//No observation file. Set receiver name as dashes
			for (i=0;i<4;i++) {
				receiverid[i]='-';
			}
			receiverid[4]='\0';
		} else {
			//Convert receiver name to lower case
			for (i=0;i<4;i++) {
				receiverid[i]=tolower(epoch->receiver.name[i]);
			}
			receiverid[4]='\0';
		}

		sprintf(errorstr[0],"Satellite selected");
		sprintf(errorstr[1],"No GEO satellites available");
		sprintf(errorstr[2],"No data for user selected GEO");
		sprintf(errorstr[3],"Not enough almanac or GEO navigation message to determine the GEO with highest elevation");
		sprintf(errorstr[7],"No PRN mask");
		sprintf(errorstr[8],"PRN mask timed out");
		sprintf(errorstr[9],"Satellite is not monitored in any of the PRN mask available");
		sprintf(errorstr[10],"No message type 10 available [PA only]");
		sprintf(errorstr[11],"Message type 10 timed out [PA only]");
		sprintf(errorstr[12],"No fast correction data received for current PRN [PA only]");
		sprintf(errorstr[13],"Sigma UDRE timed out [PA only]");
		sprintf(errorstr[14],"Satellite flagged as 'Not monitored' (UDREI=14)");
		sprintf(errorstr[15],"Satellite flagged as 'Do not use' (UDREI=15)");
		sprintf(errorstr[17],"No fast correction degradation data [PA only]");
		sprintf(errorstr[18],"Fast correction degradation data timed out [PA only]");
		sprintf(errorstr[19],"Last PRC received timed out [PA only]");
		sprintf(errorstr[20],"Only one PRC received. RRC calculation not possible [PA only]");
		sprintf(errorstr[21],"RRC timed out (under alarm condition) due to time difference between PRC used [PA only]");
		sprintf(errorstr[22],"RRC timed out (under alarm condition) due to excessive PRC propagation in time [PA only]");
		sprintf(errorstr[23],"RRC timed out due to time difference between PRC used [PA only]");
		sprintf(errorstr[24],"RRC timed out due to excessive PRC propagation in time [PA only]");
		sprintf(errorstr[25],"Service message timed out [PA only]");
		sprintf(errorstr[26],"Not received a full set of service messages with the same IODS [PA only]");
		sprintf(errorstr[27],"No clock-ephemeris covariance matrix data for current satellite [PA only]");
		sprintf(errorstr[28],"Clock-ephemeris covariance matrix data timed out [PA only]");
		sprintf(errorstr[29],"No navigation data for ranging GEO");
		sprintf(errorstr[30],"Ranging GEO navigation data timed out");
		sprintf(errorstr[32],"No long term correction data for current satellite [PA only]");
		sprintf(errorstr[33],"Long term correction data timed out [PA only]");
		sprintf(errorstr[35],"No broadcast block available for current satellite (regardless of SBAS IOD) [NPA only]");
		sprintf(errorstr[36],"Could not compute transmission time for current PRN measurement");
		sprintf(errorstr[37],"No ionospheric grid mask [PA only]");
		sprintf(errorstr[38],"Ionospheric grid mask timed out [PA only]");
		sprintf(errorstr[39],"IGPs around ionospheric pierce point not found in MOPS grid [PA only]");
		sprintf(errorstr[40],"Not enough IGPs available in ionospheric grid mask [PA only]");
		sprintf(errorstr[41],"One IGP is set as don't use [PA only]");
		sprintf(errorstr[42],"One or more IGPs is set as not monitored or has timed out [PA only]");
		sprintf(errorstr[43],"Data not available for one or more IGPs [PA only]");
		sprintf(errorstr[44],"Ionospheric pierce point is outside triangle [PA only]");
		sprintf(errorstr[45],"External ionosphere model not available");
	}

	switch(errorcode) {
		case 4:
			//In case of Mixed GEO, write the GEO from which the alarm was received
			if ( GEOPRN == 0 ) {
				sprintf(GEOtext,"GEO %3d",GEOPRN);
				t2tmnolocal(&SBASdata[0].alarmtime[SBAS1FFREQPOS],&tm,&seconds);
				sprintf(Alarmtime,"%17s / %02d:%02d:%05.2f",t2doystr(&SBASdata[0].alarmtime[SBAS1FFREQPOS]),tm.tm_hour,tm.tm_min,seconds);
			} else {
				sprintf(GEOtext,"current GEO");
				t2tmnolocal(&SBASdata[options->GEOindex].lastmsgreceived[SBAS1FFREQPOS][DONTUSE],&tm,&seconds);
				sprintf(Alarmtime,"%17s / %02d:%02d:%05.2f",t2doystr(&SBASdata[options->GEOindex].lastmsgreceived[SBAS1FFREQPOS][DONTUSE]),tm.tm_hour,tm.tm_min,seconds);
			}
			sprintf(errorstr[4],"Received alarm message for %s at epoch %31s. Time remaining to finish alarm: %2d second%s",GEOtext,Alarmtime,SBASdata[options->GEOindex].alarmTimeRemaining[SBAS1FFREQPOS],SBASdata[options->GEOindex].alarmTimeRemaining[SBAS1FFREQPOS]==1?"":"s");
			break;
		case 5:
			sprintf(errorstr[5],"Received %d consecutive messages with errors (UDREI data has been forced to timeout) [PA only]",SBASdata[0].failedmessages[SBAS1FFREQPOS][GEOPRN]);
			break;
		case 6:
			sprintf(errorstr[6],"Missed %d consecutive messages",SBASdata[0].missed4msg[SBAS1FFREQPOS][GEOPRN]);
			break;
		case 16:
			sprintf(errorstr[16],"Satellite has an UDREI value of %2d [PA only]",SBAScorr->UDREI);
			break;
		case 31:
			sprintf(errorstr[31],"URA index value of %2d for ranging GEO satellite",SBAScorr->uraindex);
			break;
		case 34:
			sprintf(errorstr[34],"No broadcast block with IOD %d [PA only]",SBAScorr->IOD);
			break;
		case 46:
			sprintf(errorstr[46],"Satellite has an UDREI value of %d (user threshold is %d)",SBAScorr->UDREI,options->UDREIthreshold);
			break;
		case 47:
			sprintf(errorstr[47],"Satellite is not in view (elevation %1.2f degrees)",epoch->sat[satIndex].elevation*r2d);
			break;
		case 48:
			sprintf(errorstr[48],"Satellite elevation (%1.2f degrees) is too low",epoch->sat[satIndex].elevation*r2d);
			break;
		default:
			break;
	}
	if (options->printV5format==1) {
		//Change last three error codes to the values in V5 format
		//Message "Satellite has an UDREI value " was moved two position back, so the last two
		//mesages are only for SBAS plots (which allows faster checks in SBAS plots mode)
		switch(errorcode) {
			case 46:
				errorcode=48;
				break;
			case 47:
				errorcode=46;
				break;
			case 48:
				errorcode=47;
				break;
			default:
				break;
		}
	}

	if (options->printV5format==0) {
		sprintf(printbufferSBASUNSEL[satIndex],"SBASUNSEL   %29s %3s %3d %3s %3d %2d \"%s\"\n",
		/*2*/		epoch->tSoDHourStr, 		//Year
		/*3*/			//DoY
		/*4*/			//Seconds of day
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*7*/		epoch->sat[satIndex].PRN,
		/*8*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*9*/		GEOPRN,
		/*10*/		errorcode,
		/*11*/		errorstr[errorcode]);
	} else {
		sprintf(printbufferSBASUNSEL[satIndex],"SBASUNSEL   %4s %3s %3s %3d %17s %4d %9.2f %3d %2d \"%s\"\n",
		/*2*/		receiverid,
		/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
		/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		/*5*/		epoch->sat[satIndex].PRN,
		/*6*/		epoch->tStr,		//Year
		/*7*/						//DoY
		/*8*/						//Seconds of day
		/*9*/		epoch->GPSweek,
		/*10*/		epoch->SoW,
		/*11*/		GEOPRN,
		/*12*/		errorcode,
		/*13*/		errorstr[errorcode]);
	}

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if(options->excludeSmoothingConvergence > 0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASUNSEL[satIndex][9]='*';
	}

	if ( options->SBAScorrections>=SBASMaps1freqUsed ) {
		//In SBAS plots mode, do not buffer data
		fprintf(options->outFileStream,"%s",printbufferSBASUNSEL[satIndex]);
		printbufferSBASUNSEL[satIndex][0]='\0';
	}
}

 /*****************************************************************************
 * Name        : printSBASDFMCCORR
 * Description : Prints the SBASDFMCCORR data line for SBAS DFMC. It will
 *                 oly print data for the combined iono-free measuremet PC15
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * double  geometricDistance                I    m  Geometric distance between satellite and receiver
 * double  satelliteClockModel              I    m  Satellite clock error
 * double  relativityModel                  I    m  Relativity model
 * double  troposphereModel                 I    m  Troposphere model
 * double  TGDModel                         I    m  TGD model
 * TConstellation  *constellation           I  N/A  TConstellation structure where 
 *                                                   satellite data is stored
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASDFMCCORR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, double geometricDistance, double satelliteClockModel, double relativityModel, double troposphereModel, double TGDModel, TConstellation *constellation, TOptions *options) {
	int						j;
	int						ret;
	int						PRN=epoch->sat[satIndex].PRN;
	int						SVN;
	double					measurement;
	double					model,prefit;
	double					smoothWith,smoothedVal;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	enum SatelliteBlock		satBlock;	
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	j = epoch->satCSIndex[GNSS][PRN];

	//In SBAS, only PC15 measurement is used and it is in position 0 of filter list (first position)
	ret = getMeasModelValue(epoch,GNSS,PRN,options->filterMeasList[ROVERPOS][GNSS][PRN][0],options->filterMeasfreq[ROVERPOS][GNSS][PRN][0],&measurement,&model,0);
	if ( ret != 1 ) {
		return;
	}

	// Smoothing
	if ( options->smoothEpochs != 0 && options->filterMeasSmoothed[ROVERPOS][GNSS][PRN][0] == 1 ) {
		ret = getMeasModelValue(epoch,GNSS,PRN,options->filterSmoothMeasList[ROVERPOS][GNSS][PRN][0],options->filterSmoothMeasfreq[ROVERPOS][GNSS][PRN][0],&smoothWith,NULL,0);
		if ( ret != 1 ) {
			return;
		}
		prefit = epoch->cycleslip.smoothedMeas[j][0] + smoothWith - model;
		smoothedVal = epoch->cycleslip.smoothedMeas[j][0] + smoothWith;
	} else {
		prefit = measurement - model;
		smoothedVal=measurement;
	}

	//Get satellite block and SVN
	if (constellation->satLastUsed[GNSS][PRN]==NULL) {
		//No previous pointer used
		constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
		if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
			satBlock=constellation->satLastUsed[GNSS][PRN]->block;
			SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
		} else {
			satBlock=UNKNOWN_BLOCK;
			SVN=-1;
		} 
	} else { 
		//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
		if (tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
			//Not valid anymore, look for a new constellation element
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			}
		} else {
			satBlock=constellation->satLastUsed[GNSS][PRN]->block;
			SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
		}
	}

	sprintf(printbufferSBASDFMCCORR[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]],"SBASDFMCCORR    %29s %3s %3d %-15s %4d %3d %6d %8.3f %8.3f %3s %3d %12s %12s %14.4f %14.4f %14.4f %14.4f %10.4f %14.4f %10.4f %10.4f %14.4f %14.4f %14.4f %8.4f %8.4f %8.4f %8.4f %2d %8.2f %8.2f %8.2f %8.2f %8.2f %1d %4d %3d\n",
	/*2*/		epoch->tSoDHourStr, 		//Year
	/*3*/			//DoY
	/*4*/			//Seconds of day
	/*5*/		/*HH:MM:SS.zz*/
	/*6*/		gnsstype2gnssstr(GNSS),
	/*7*/		PRN,
	/*8*/		satblock2satblockstr(satBlock),
	/*9*/		SVN,
	/*10*/		epoch->cycleslip.narc[j],
	/*11*/		epoch->cycleslip.arcLength[j]==0?1:epoch->cycleslip.arcLength[j],
	/*12*/		epoch->sat[satIndex].elevation*r2d, //Elevation (in degrees)
	/*13*/		epoch->sat[satIndex].azimuth*r2d,  //Azimuth (in degrees)
	/*14*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*15*/		SBASdata[options->GEOindex].PRN,
	/*16*/		options->filterMeasText[ROVERPOS][GNSS][PRN][0],
	/*17*/		options->filterSmoothMeasText[ROVERPOS][GNSS][PRN][0],
	/*18*/		prefit,
	/*19*/		measurement,			//PC15 raw + user added noise (in metres)
	/*20*/		smoothedVal,			//PC15 smoothed + user added noise (if smoothing is disabled, then is PC15 raw + user added noise) (in metres)
	/*21*/		geometricDistance, 		//With SBAS DFMC corrections (in metres)
	/*22*/		relativityModel,		//With SBAS DFMC corrections (in metres)
	/*23*/		satelliteClockModel, 	//With SBAS DFMC corrections (in metres)
	/*24*/		TGDModel,				//GPS LNAV TGD (in metres of L1). For other constellation, value is 0
	/*25*/		troposphereModel,		//Troposphere correction (in metres)
	/*26*/		SBAScorr->SatCoordbrdc[0]+SBAScorr->SatCoordCor[0],	//X component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
	/*27*/		SBAScorr->SatCoordbrdc[1]+SBAScorr->SatCoordCor[1],	//Y component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
	/*28*/		SBAScorr->SatCoordbrdc[2]+SBAScorr->SatCoordCor[2],	//Z component of the satellite position in WGS84 system at emission time with SBAS corrections (in metres)
	/*29*/		SBAScorr->SatCoordCor[0],	//Correction to be applied to the X component of the satellite (in metres)
	/*30*/		SBAScorr->SatCoordCor[1],	//Correction to be applied to the Y component of the satellite (in metres)
	/*31*/		SBAScorr->SatCoordCor[2],	//Correction to be applied to the Z component of the satellite (in metres)
	/*32*/		SBAScorr->ClockCor,			//Correction to be applied to the satellite clock (in metres)
	/*33*/		SBAScorr->DFREI,			//DFREI of the current satellite
	/*34*/		SBAScorr->tDFREI,			//Time (seconds of day) of last DFREI received
	/*35*/		SBAScorr->lastMT32,			//Time (seconds of day) of last MT32 received
	/*36*/		SBAScorr->lastMT3940,		//Time (seconds of day) of last pair of MT39/40 received
	/*37*/		SBAScorr->ValidTimeMT32,	//Validity time of MT32 (including multiplication factor of PA/NPA modes) (seconds)
	/*38*/		SBAScorr->ValidTimeMT3940,	//Validity time of MT3940 (including multiplication factor of PA/NPA modes) (seconds)
	/*39*/		SBAScorr->IODM,				//IODM used for PRN mask
	/*40*/		SBAScorr->IODN,				//IODN or IODG in MT32 or MT39/40
	/*41*/		SBASdata[options->GEOindex].PRN2SlotNumber[SBASDFMCFREQPOS][GNSS][PRN]);	//Slot number in PRN mask

	// Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if ( options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASDFMCCORR[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][12]='*';
	}
}

/*****************************************************************************
 * Name        : printSBASDFMCVAR
 * Description : Prints the SBASDFMCVAR data line for SBAS DFMC
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * TConstellation  *constellation           I  N/A  TConstellation structure where 
 *                                                   satellite data is stored
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASDFMCVAR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, TConstellation *constellation, TOptions *options) {
	int    				 	j;
	int						PRN=epoch->sat[satIndex].PRN;
	int						SVN;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	enum SatelliteBlock		satBlock;	
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread

	j = epoch->satCSIndex[GNSS][PRN];

	//Get satellite block and SVN
	if (constellation->satLastUsed[GNSS][PRN]==NULL) {
		//No previous pointer used
		constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
		if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
			satBlock=constellation->satLastUsed[GNSS][PRN]->block;
			SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
		} else {
			satBlock=UNKNOWN_BLOCK;
			SVN=-1;
		} 
	} else { 
		//Instead of directly search for a new block, check if current block is still valid and thus no need to check for a new one
		if (tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tLaunch)<0 || tdiff(&epoch->t,&constellation->satLastUsed[GNSS][PRN]->tDecommissioned)>0) {
			//Not valid anymore, look for a new constellation element
			constellation->satLastUsed[GNSS][PRN] = getConstellationElement(GNSS,PRN,&epoch->t,constellation);
			if (constellation->satLastUsed[GNSS][PRN]!=NULL) {
				satBlock=constellation->satLastUsed[GNSS][PRN]->block;
				SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
			} else {
				//This case will only occur when the RINEX observation file is corrupted and a wrong date is read
				satBlock=UNKNOWN_BLOCK;
				SVN=-1;
			}
		} else {
			satBlock=constellation->satLastUsed[GNSS][PRN]->block;
			SVN=constellation->satLastUsed[GNSS][PRN]->SVN;
		}
	}

	sprintf(printbufferSBASDFMCVAR[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]],"SBASDFMCVAR     %29s %3s %3d %-15s %4d %3d %6d %8.3f %8.3f %3s %3d %14.4f %14.4f %2d %d %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
	/*2*/		epoch->tSoDHourStr, 		//Year
	/*3*/			//DoY
	/*4*/			//Seconds of day
	/*5*/		/*HH:MM:SS.zz*/
	/*6*/		gnsstype2gnssstr(GNSS),
	/*7*/		PRN,
	/*8*/		satblock2satblockstr(satBlock),
	/*9*/		SVN,
	/*10*/		epoch->cycleslip.narc[j],
	/*11*/		epoch->cycleslip.arcLength[j]==0?1:epoch->cycleslip.arcLength[j],
	/*12*/		epoch->sat[satIndex].elevation*r2d, //Elevation (in degrees)
	/*13*/		epoch->sat[satIndex].azimuth*r2d,  //Azimuth (in degrees)
	/*14*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*15*/		SBASdata[options->GEOindex].PRN,
	/*16*/		sqrt(SBAScorr->SBASsatsigma2),				//Sigma of the total residual error associated to the satellite (in metres)
	/*17*/		sqrt(SBAScorr->sigma2DFC),					//Sigma DFC in metres
	/*18*/		SBAScorr->DFREI,							//DFREI to apply to satellite
	/*19*/		SBAScorr->DFRECIbumped,						//Flag to indicate if DFREI has been bumped in MT34
	/*20*/		SBAScorr->DFRE,								//Sigma after converting from DFREI (in metres)
	/*21*/		SBAScorr->deltaDFRE,						//Delta DFRE factor
	/*22*/		SBAScorr->Ecorr,							//Degradation parameter for corrections (in metres)
	/*23*/		SBAScorr->Eer,								//Degradation parameter for en route through NPA applications (in metres)
	/*24*/		sqrt(SBAScorr->sigma2ionoresidual),			//Sigma of the residual error associated to the ionosheric corrections (in metres)
	/*25*/		sqrt(SBAScorr->sigma2tropo),				//Sigma of the residual error associated to the tropospheric corrections (in metres)
	/*26*/		sqrt(SBAScorr->sigma2air),					//Sigma of the total receiver error (in metres)
	/*27*/		sqrt(SBAScorr->sigma2noise),				//Sigma of the receiver noise (in metres)
	/*28*/		sqrt(SBAScorr->sigma2multipath),			//Sigma of the receiver multipath (in metres)
	/*29*/		sqrt(SBAScorr->sigma2divergence),			//Sigma of the receiver divergence (in metres)
	/*30*/		SBAScorr->ccorr,							//Ccorr term (metres)
	/*31*/		SBAScorr->icorr,							//Icorr term (seconds)
	/*32*/		SBAScorr->rcorr,							//Rcorr term (metres/seconds)
	/*33*/		SBAScorr->deltarcorr,						//DeltaRcorr term (adimensional)
	/*34*/		SBAScorr->rcorrSV,							//RcorrSV term (metres/seconds)
	/*35*/		SBAScorr->cer,								//Cer term (metres)
	/*36*/		SBAScorr->ccovariance);						//Ccovariance term (metres)

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if (options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j]<options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASDFMCVAR[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][11]='*';
	}
}


/*****************************************************************************
 * Name        : printSBASDFMCUNSEL
 * Description : Prints the SBASDFMCUNSEL data line for SBAS DFMC (printed only when a satellite is discarded)
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * int satIndex                             I  N/A  Selected satellite
 * int errorcode                            I  N/A  Error code indicating the reason for discarding the satellite
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASDFMCUNSEL (TEpoch  *epoch, int  satIndex, int errorcode, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions  *options) {
	int				j;
	int				GEOPRN;
	char			GEOtext[100];
	char			Alarmtime[100];
	enum GNSSystem	GNSS=epoch->sat[satIndex].GNSS;
	struct tm 		tm;
	double			seconds;

	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int      initialized=0;
    #pragma omp threadprivate(initialized)	
	static char 	errorstr[28][MAX_INPUT_LINE];
	#pragma omp threadprivate(errorstr)

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	errorcode=abs(errorcode);

	// Check for options->GEOindex value
	if ( options->GEOindex < 0 ) GEOPRN = -1;
	else GEOPRN=SBASdata[options->GEOindex].PRN;

	if ( initialized == 0 ) {
		initialized = 1;

		sprintf(errorstr[0],"Satellite selected");
		sprintf(errorstr[1],"No GEO satellites available");
		sprintf(errorstr[2],"No data for user selected GEO");
		sprintf(errorstr[3],"Not enough almanac or GEO navigation message to determine the GEO with highest elevation");
		sprintf(errorstr[7],"No PRN mask");
		sprintf(errorstr[8],"PRN mask timed out");
		sprintf(errorstr[9],"Satellite is not monitored in any of the PRN mask available");
		sprintf(errorstr[10],"No message type 37 available");
		sprintf(errorstr[11],"Message type 37 timed out");
		sprintf(errorstr[12],"No DFREI data received for current PRN");
		sprintf(errorstr[13],"DFREI timed out");
		sprintf(errorstr[14],"Satellite flagged as 'Do not use' (DFREI=15)");
		sprintf(errorstr[15],"Received DFRECI=1 in MT34 but no new DFREI value");
		sprintf(errorstr[20],"Message type 39/40 pair timed out");
		sprintf(errorstr[21],"No message type 32 received for current PRN");
		sprintf(errorstr[22],"Message type 32 timed out");
		sprintf(errorstr[23],"IODN in Message type 32 does not match with IODG in message type 39/40");
		sprintf(errorstr[24],"Could not compute transmission time for current PRN");
	}

	switch(errorcode) {
		case 4:
			//In case of Mixed GEO, write the GEO from which the alarm was received
			if ( GEOPRN == 0 ) {
				sprintf(GEOtext,"GEO %3d",GEOPRN);
				t2tmnolocal(&SBASdata[0].alarmtime[SBASDFMCFREQPOS],&tm,&seconds);
				sprintf(Alarmtime,"%17s / %02d:%02d:%05.2f",t2doystr(&SBASdata[0].alarmtime[SBASDFMCFREQPOS]),tm.tm_hour,tm.tm_min,seconds);
			} else {
				sprintf(GEOtext,"current GEO");
				t2tmnolocal(&SBASdata[options->GEOindex].lastmsgreceived[SBASDFMCFREQPOS][DONTUSE],&tm,&seconds);
				sprintf(Alarmtime,"%17s / %02d:%02d:%05.2f",t2doystr(&SBASdata[options->GEOindex].lastmsgreceived[SBASDFMCFREQPOS][DONTUSE]),tm.tm_hour,tm.tm_min,seconds);
			}
			sprintf(errorstr[4],"Received alarm message for %s at epoch %31s. Time remaining to finish alarm: %2d second%s",GEOtext,Alarmtime,SBASdata[options->GEOindex].alarmTimeRemaining[SBASDFMCFREQPOS],SBASdata[options->GEOindex].alarmTimeRemaining[SBASDFMCFREQPOS]==1?"":"s");
			break;
		case 5:
			sprintf(errorstr[5],"Received %d consecutive messages with errors (DFREI data has been forced to timeout)",SBASdata[0].failedmessages[SBASDFMCFREQPOS][GEOPRN]);
			break;
		case 6:
			sprintf(errorstr[6],"Missed %d consecutive messages",SBASdata[0].missed4msg[SBASDFMCFREQPOS][GEOPRN]);
			break;
		case 16:
			sprintf(errorstr[16],"Satellite has an DFREI value of %d (user threshold is %d)",SBAScorr->DFREI,options->DFREIthreshold);
			break;
		case 17:
			sprintf(errorstr[17],"No MT39/40 from GEO %3d received (same GEO as source corrections)",epoch->sat[satIndex].PRN);
			break;
		case 18:
			sprintf(errorstr[18],"No data from GEO %3d received for MT39/40",epoch->sat[satIndex].PRN);
			break;
		case 19:
			sprintf(errorstr[19],"No MT39/40 message pair from GEO %3d received",epoch->sat[satIndex].PRN);
			break;
		case 25:
			sprintf(errorstr[25],"No broadcast block with IOD %d",SBAScorr->IOD);
			break;
		case 26:
			sprintf(errorstr[26],"Satellite is not in view (elevation %1.2f degrees)",epoch->sat[satIndex].elevation*r2d);
			break;
		case 27:
			sprintf(errorstr[27],"Satellite elevation (%1.2f degrees) is too low",epoch->sat[satIndex].elevation*r2d);
			break;
		default:
			break;
	}

	sprintf(printbufferSBASDFMCUNSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]],"SBASDFMCUNSEL   %29s %3s %3d %3s %3d %2d \"%s\"\n",
	/*2*/		epoch->tSoDHourStr, 		//Year
	/*3*/			//DoY
	/*4*/			//Seconds of day
	/*5*/		/*HH:MM:SS.zz*/
	/*6*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
	/*7*/		epoch->sat[satIndex].PRN,
	/*8*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*9*/		GEOPRN,
	/*10*/		errorcode,
	/*11*/		errorstr[errorcode]);

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if(options->excludeSmoothingConvergence > 0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASDFMCUNSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][13]='*';
	}

	if ( options->SBAScorrections>=SBASMaps1freqUsed ) {
		//In SBAS plots mode, do not buffer data
		fprintf(options->outFileStream,"%s",printbufferSBASDFMCUNSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]);
		printbufferSBASDFMCUNSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][0]='\0';
	}
}
 
/*****************************************************************************
 * Name        : printSBASOUT
 * Description : Prints the solution information for SBAS
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 *****************************************************************************/
void printSBASOUT (TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo) {

	int						i,j;
	int						numSatSolutionGNSS=0,numSatnotUsedGNSS=0;
	static int				initialized=0;
	static char				receiverid[5];

	if(options->printSBASOUT==0) return;

	if (initialized==0) {
		initialized=1;
		//Convert receiver name to lower case
		for(i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}

	for(i=0;i<options->numSBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos];i++) {
		numSatSolutionGNSS+=epoch->numSatSolutionGNSS[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]];
		numSatnotUsedGNSS+=epoch->numSatnotUsedGNSS[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]];
	}

	if (options->printV5format==0) {
		fprintf(options->outFileStream,"SBASOUT     %29s %4d %9.2f %4s %d %3s %3d %14.4f %14.4f %14.4f %14.4f %14.4f %6.2f %14.4f %14.4f %6.2f %14.4f %14.4f %2d %2d", 
		/*2*/		epoch->tSoDHourStr,
		/*3*/		/*DoY*/
		/*4*/		/*SoD*/
		/*5*/		/*HH:MM:SS.zz*/
		/*6*/		epoch->GPSweek,
		/*7*/		epoch->SoW,
		/*8*/		receiverid,
		/*9*/		options->solutionMode,
		/*10*/		SBASnavmode2SBASnavstr(epoch->SBASUsedMode),
		/*11*/		epoch->SBASUsedGEO,
		/*12*/		epoch->SolErrorNEU[0],	// North error (Meters)
		/*13*/		epoch->SolErrorNEU[1],	// East error (Meters)
		/*14*/		epoch->SolErrorNEU[2],	// Up error (Meters)
		/*15*/		epoch->SolHError,	//Horizontal positioning error (Metres)
		/*16*/		solution->HPL,		// Horizontal protection level (Metres)
		/*17*/		options->HorAlarmLimit,		// Horizontal alarm limit (Metres)
		/*18*/		epoch->SolVError,		// Vertical positioning error (absolute value of Up error) (Metres)
		/*19*/		solution->VPL,		// Vertical protection level (Metres)
		/*20*/		options->VerAlarmLimit,		// Vertical alarm limit (Metres)
		/*21*/		epoch->SolError3DNEU,		//3D error (Metres)
		/*22*/		solution->x[unkinfo->par2unk[DT_UNK]],	// Receiver clock offset (Metres)
		/*23*/		numSatSolutionGNSS+numSatnotUsedGNSS,	// Number of satellites in view that can be used for SBAS
		/*24*/		numSatSolutionGNSS);	// Number of satellites used to compute the solution
	} else {
		fprintf(options->outFileStream,"SBASOUT     %4s %3s %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %2d %2d", 
		/*2*/		receiverid,
		/*3*/		SBASnavmode2SBASnavstr(epoch->SBASUsedMode),
		/*4*/		epoch->tStr,
		/*5*/		/*DoY*/
		/*6*/		/*SoD*/
		/*7*/		epoch->GPSweek,
		/*8*/		epoch->SoW,
		/*9*/		epoch->SBASUsedGEO,
		/*10*/		epoch->SolErrorNEU[0],	// North error (Meters)
		/*11*/		epoch->SolErrorNEU[1],	// East error (Meters)
		/*12*/		epoch->SolErrorNEU[2],	// Up error (Meters)
		/*13*/		epoch->SolHError,	//Horizontal positioning error (Metres)
		/*14*/		solution->HPL,		// Horizontal protection level (Metres)
		/*15*/		epoch->SolVError,		// Vertical positioning error (absolute value of Up error) (Metres)
		/*16*/		solution->VPL,		// Vertical protection level (Metres)
		/*17*/		solution->x[unkinfo->par2unk[DT_UNK]],	// Receiver clock offset (Metres)
		/*18*/		numSatSolutionGNSS+numSatnotUsedGNSS,	// Number of satellites in view that can be used for SBAS
		/*19*/		numSatSolutionGNSS);	// Number of satellites used to compute the solution
	}

	for(i=0;i<options->numSBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos];i++) {
		// Print list of PRN used to compute the solution in SBAS
		for (j=0;j<epoch->numSatSolutionGNSS[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]];j++) {	
			fprintf(options->outFileStream," +%c%02d",gnsstype2char(options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]),epoch->listPRNSatSolutionConst[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]][j]);
		}
	
	}
		
	for(i=0;i<options->numSBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos];i++) {
		// Print list of PRN not used to compute the solution but are suitable for SBAS
		for (j=0;j<epoch->numSatnotUsedGNSS[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]];j++) {	
			fprintf(options->outFileStream," -%c%02d",gnsstype2char(options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]),epoch->listPRNSatnotUsedConst[options->SBASConstList[epoch->SBASUsedGEOindex][options->SBASmodePos][i]][j]);
		}
	}

	fprintf(options->outFileStream,"\n");
	
}

/*****************************************************************************
 * Name        : printBuffers
 * Description : Prints all the information saved in the buffers
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printBuffers (TEpoch *epoch, TOptions *options) {
	int i, j,k;

	if (options->printDGNSS==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				if ( printbufferDGNSS[i][j][0] == '\0' ) continue;
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferDGNSS[i][j][5] = '*';
					fprintf(options->outFileStream,"%s",printbufferDGNSS[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferDGNSS[i][j]);
				}
				printbufferDGNSS[i][j][0] = '\0';
			}
		}
	}

	if (options->printModel==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				for ( k=0;k<linesstoredMODEL[i][j];k++ ) {
					if ( printbufferMODEL[i][j][k][0] == '\0' ) continue;
					if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
						printbufferMODEL[i][j][k][5] = '*';
						fprintf(options->outFileStream,"%s",printbufferMODEL[i][j][k]);
					} else if ( options->printInBuffer == 2 ) {
						fprintf(options->outFileStream,"%s",printbufferMODEL[i][j][k]);
					}
					printbufferMODEL[i][j][k][0] = '\0';
				}
				linesstoredMODEL[i][j]=0;
			}
		}
	}

	if (options->printSBASIONO==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( printbufferSBASIONO[i][0] == '\0' ) continue;
			if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
				printbufferSBASIONO[i][8] = '*';
				fprintf(options->outFileStream,"%s",printbufferSBASIONO[i]);
			} else if ( options->printInBuffer == 2 ) {
				fprintf(options->outFileStream,"%s",printbufferSBASIONO[i]);
			}
			printbufferSBASIONO[i][0] = '\0';
		}
	}

	if (options->printSBASCORR==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( printbufferSBASCORR[i][0] == '\0' ) continue;
			if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
				printbufferSBASCORR[i][8] = '*';
				fprintf(options->outFileStream,"%s",printbufferSBASCORR[i]);
			} else if ( options->printInBuffer == 2 ) {
				fprintf(options->outFileStream,"%s",printbufferSBASCORR[i]);
			}
			printbufferSBASCORR[i][0] = '\0';
		}
	}

	if (options->printSBASVAR==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( printbufferSBASVAR[i][0] == '\0' ) continue;
			if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
				printbufferSBASVAR[i][7] = '*';
				fprintf(options->outFileStream,"%s",printbufferSBASVAR[i]);
			} else if ( options->printInBuffer == 2 ) {
				fprintf(options->outFileStream,"%s",printbufferSBASVAR[i]);
			}
			printbufferSBASVAR[i][0] = '\0';
		}
	}

	if (options->printSBASUNSEL==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( printbufferSBASUNSEL[i][0] == '\0' ) continue;
			if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
				printbufferSBASUNSEL[i][9] = '*';
				fprintf(options->outFileStream,"%s",printbufferSBASUNSEL[i]);
			} else if ( options->printInBuffer == 2 ) {
				fprintf(options->outFileStream,"%s",printbufferSBASUNSEL[i]);
			}
			printbufferSBASUNSEL[i][0] = '\0';
		}
	}

	if (options->printSBASDFMCCORR==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				if ( printbufferSBASDFMCCORR[i][j][0] == '\0' ) continue;
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferSBASDFMCCORR[i][j][12] = '*';
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCCORR[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCCORR[i][j]);
				}
				printbufferSBASDFMCCORR[i][j][0] = '\0';
			}
		}
	}

	if (options->printSBASDFMCVAR==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				if ( printbufferSBASDFMCVAR[i][j][0] == '\0' ) continue;
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferSBASDFMCVAR[i][j][11] = '*';
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCVAR[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCVAR[i][j]);
				}
				printbufferSBASDFMCVAR[i][j][0] = '\0';
			}
		}
	}

	if (options->printSBASDFMCUNSEL==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				if ( printbufferSBASDFMCUNSEL[i][j][0] == '\0' ) continue;
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferSBASDFMCUNSEL[i][j][13] = '*';
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCUNSEL[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferSBASDFMCUNSEL[i][j]);
				}
				printbufferSBASDFMCUNSEL[i][j][0] = '\0';
			}
		}
	}

	if (options->printSatSel==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];j++ ) {
				for ( k=0;k<linesstoredSATSEL[i][j];k++ ) {
					if ( printbufferSATSEL[i][j][k][0] == '\0' ) continue;
					if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
						printbufferSATSEL[i][j][k][6] = '*';
						fprintf(options->outFileStream,"%s",printbufferSATSEL[i][j][k]);
					} else if ( options->printInBuffer == 2 ) {
						fprintf(options->outFileStream,"%s",printbufferSATSEL[i][j][k]);
					}
					printbufferSATSEL[i][j][k][0] = '\0';
				}
				linesstoredSATSEL[i][j]=0;
			}
		}
	}
}


/*****************************************************************************
 * Name        : printBuffersKalman
 * Description : Prints all the information saved in the buffers related to the Kalman
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printBuffersKalman (TEpoch *epoch, TOptions *options) {
	int i,j,k,l;
	
	if (options->printPrefit==1) {
		for ( j=0;j<MAX_MEASKIND_PRINT_MEASUREMENTS;j++ ) {
			for ( i=0;i<epoch->numPrintGNSS;i++ ) {
				for (k=0;k<epoch->measOrder[epoch->PrintPos2GNSS[i]].numMeasIndexed[j];k++) {
					for ( l=0;l<linesstoredPREFIT[i][j][k];l++ ) {
						if ( printbufferPREFIT[i][j][k][l][0] == '\0' ) continue;
						if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
							printbufferPREFIT[i][j][k][l][6] = '*';
							fprintf(options->outFileStream,"%s",printbufferPREFIT[i][j][k][l]);
						} else if ( options->printInBuffer == 2 ) {
							fprintf(options->outFileStream,"%s",printbufferPREFIT[i][j][k][l]);
						}
						printbufferPREFIT[i][j][k][l][0]='\0';
					}
					linesstoredPREFIT[i][j][k]=0;
				}
			}
		}
	}

	if (options->printSatellites==1) {
		for ( i=0;i<MAX_MEASKIND_PRINT_MEASUREMENTS;i++ ) {
			for(j=0;j<linesstoredEPOCHSAT[i];j++) {
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferEPOCHSAT[i][j][8] = '*';
					fprintf(options->outFileStream,"%s",printbufferEPOCHSAT[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferEPOCHSAT[i][j]);
				}
				printbufferEPOCHSAT[i][j][0]='\0';
			}
			linesstoredEPOCHSAT[i]=0;
		}
	}
	
	if (options->printPostfit==1) {
		for ( j=0;j<MAX_MEASKIND_PRINT_MEASUREMENTS;j++ ) {
			for ( i=0;i<epoch->numPrintGNSS;i++ ) {
				for (k=0;k<epoch->measOrder[epoch->PrintPos2GNSS[i]].numMeasIndexed[j];k++) {
					for ( l=0;l<linesstoredPOSTFIT[i][j][k];l++ ) {
						if ( printbufferPOSTFIT[i][j][k][l][0] == '\0' ) continue;
						if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
							printbufferPOSTFIT[i][j][k][l][7] = '*';
							fprintf(options->outFileStream,"%s",printbufferPOSTFIT[i][j][k][l]);
						} else if ( options->printInBuffer == 2 ) {
							fprintf(options->outFileStream,"%s",printbufferPOSTFIT[i][j][k][l]);
						}
						printbufferPOSTFIT[i][j][k][l][0]='\0';
					}
					linesstoredPOSTFIT[i][j][k]=0;
				 }
			}
		}
	}

	if (options->printFilterSolution==1) {
		if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
			printbufferFILTER[6] = '*';
			fprintf(options->outFileStream,"%s",printbufferFILTER);
		} else if ( options->printInBuffer == 2 ) {
			fprintf(options->outFileStream,"%s",printbufferFILTER);
		}
		printbufferFILTER[0]='\0';
	}
}

/*****************************************************************************
 * Name        : printBuffersBestGEO
 * Description : Prints all the information saved in the buffers for the
 *                multiple iterations done. 
 *                This function is only called if option select best GEO is
 *                enabled and there is data buffered
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * int selected                             I  N/A  Index of the selected iteration
 * int prevGEOPRN                           I  N/A  GEO PRN currently selected
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printBuffersBestGEO (TEpoch *epoch, int selected, int prevGEOPRN, TOptions *options) {

	int i, j, k, l;

	if ( options->printSBASUNUSED == 1 ) {
		for(k=0;k<epoch->Buffer_NumDataStored;k++) {
			if (k==selected) continue;
			//Print data for unselected iterations
			if (options->printModel==1) {
				for ( i=0;i<epoch->numPrintGNSS;i++ ) {
					for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
						for ( l=0;l<epoch->BufferBestGEO[k].Buffer_NumMODEL[i][j];l++) {
							if ( epoch->BufferBestGEO[k].Buffer_printMODEL[i][j][l][0] == '\0' ) continue;
							epoch->BufferBestGEO[k].Buffer_printMODEL[i][j][l][5] = '*';
							fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printMODEL[i][j][l]);
						}
					}
				}
			}

			if (options->printSBASIONO==1) {
				for ( i=0;i<epoch->numSatellites;i++ ) {
					if ( epoch->BufferBestGEO[k].Buffer_printSBASIONO[i][0] == '\0' ) continue;
					epoch->BufferBestGEO[k].Buffer_printSBASIONO[i][8] = '*';
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASIONO[i]);
				}
			}

			if (options->printSBASCORR==1) {
				for ( i=0;i<epoch->numSatellites;i++ ) {
					if ( epoch->BufferBestGEO[k].Buffer_printSBASCORR[i][0] == '\0' ) continue;
					epoch->BufferBestGEO[k].Buffer_printSBASCORR[i][8] = '*';
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASCORR[i]);
				}
			}

			if (options->printSBASVAR==1) {
				for ( i=0;i<epoch->numSatellites;i++ ) {
					if ( epoch->BufferBestGEO[k].Buffer_printSBASVAR[i][0] == '\0' ) continue;
					epoch->BufferBestGEO[k].Buffer_printSBASVAR[i][7] = '*';
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASVAR[i]);
				}
			}

			if (options->printSBASUNSEL==1) {
				for ( i=0;i<epoch->numSatellites;i++ ) {
					if ( epoch->BufferBestGEO[k].Buffer_printSBASUNSEL[i][0] == '\0' ) continue;
					epoch->BufferBestGEO[k].Buffer_printSBASUNSEL[i][9] = '*';
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASUNSEL[i]);
				}
			}

			if (options->printSBASDFMCCORR==1) {
				for ( i=0;i<epoch->numPrintGNSS;i++ ) {
					for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
						if ( epoch->BufferBestGEO[k].Buffer_printSBASDFMCCORR[i][j][0] == '\0' ) continue;
						epoch->BufferBestGEO[k].Buffer_printSBASDFMCCORR[i][j][12] = '*';
						fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASDFMCCORR[i][j]);
					}
				}
			}

			if (options->printSBASDFMCVAR==1) {
				for ( i=0;i<epoch->numPrintGNSS;i++ ) {
					for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
						if ( epoch->BufferBestGEO[k].Buffer_printSBASDFMCVAR[i][j][0] == '\0' ) continue;
						epoch->BufferBestGEO[k].Buffer_printSBASDFMCVAR[i][j][11] = '*';
						fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASDFMCVAR[i][j]);
					}
				}
			}

			if (options->printSBASDFMCUNSEL==1) {
				for ( i=0;i<epoch->numPrintGNSS;i++ ) {
					for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
						if ( epoch->BufferBestGEO[k].Buffer_printSBASDFMCUNSEL[i][j][0] == '\0' ) continue;
						epoch->BufferBestGEO[k].Buffer_printSBASDFMCUNSEL[i][j][13] = '*';
						fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSBASDFMCUNSEL[i][j]);
					}
				}
			}

			if ( options->printSatSel == 1 ) {
				for ( i=0;i<epoch->numPrintGNSS;i++ ) {
					for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
						for ( l=0;l<epoch->BufferBestGEO[k].Buffer_NumSatSel[i][j];l++) {
							if ( epoch->BufferBestGEO[k].Buffer_printSATSEL[i][j][l][0] == '\0' ) continue;
							epoch->BufferBestGEO[k].Buffer_printSATSEL[i][j][l][6] = '*';
							fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[k].Buffer_printSATSEL[i][j][l]);
						}
					}
				}
			}
		}
	}

	if (prevGEOPRN!=epoch->currentGEOPRN) {
		sprintf(messagestr,"Switched from GEO %3d to GEO %3d at epoch %29s",prevGEOPRN,epoch->BufferBestGEO[selected].Buffer_GEOPRN,epoch->tSoDHourStr);
		printInfo(messagestr,options);
	}

	//Print data for selected iteration
	if ( options->printModel==1 ) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
				for ( l=0;l<epoch->BufferBestGEO[selected].Buffer_NumMODEL[i][j];l++) {
					if ( epoch->BufferBestGEO[selected].Buffer_printMODEL[i][j][l][0] != '\0' ) {
						fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printMODEL[i][j][l]);
					}
				}
			}
		}
	}

	if (options->printSBASIONO==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( epoch->BufferBestGEO[selected].Buffer_printSBASIONO[i][0] != '\0' ) {
				fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASIONO[i]);
			}
		}
	}

	if (options->printSBASCORR==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( epoch->BufferBestGEO[selected].Buffer_printSBASCORR[i][0] != '\0' ) {
				fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASCORR[i]);
			}
		}
	}

	if (options->printSBASVAR==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( epoch->BufferBestGEO[selected].Buffer_printSBASVAR[i][0] != '\0' ) {
				fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASVAR[i]);
			}
		}
	}

	if (options->printSBASUNSEL==1) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( epoch->BufferBestGEO[selected].Buffer_printSBASUNSEL[i][0] != '\0' ) {
				fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASUNSEL[i]);
			}
		}
	}

	if (options->printSBASDFMCCORR==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
				if ( epoch->BufferBestGEO[selected].Buffer_printSBASDFMCCORR[i][j][0] != '\0' ) {
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASDFMCCORR[i][j]);
				}
			}
		}
	}

	if (options->printSBASDFMCVAR==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
				if ( epoch->BufferBestGEO[selected].Buffer_printSBASDFMCVAR[i][j][0] != '\0' ) {
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASDFMCVAR[i][j]);
				}
			}
		}
	}

	if (options->printSBASDFMCUNSEL==1) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
				if ( epoch->BufferBestGEO[selected].Buffer_printSBASDFMCUNSEL[i][j][0] != '\0' ) {
					fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSBASDFMCUNSEL[i][j]);
				}
			}
		}
	}

	if ( options->printSatSel == 1 ) {
		for ( i=0;i<epoch->numPrintGNSS;i++ ) {
			for ( j=0;j<epoch->numSatellitesGNSS[i];j++ ) {
				for ( l=0;l<epoch->BufferBestGEO[selected].Buffer_NumSatSel[i][j];l++) {
					if ( epoch->BufferBestGEO[selected].Buffer_printSATSEL[i][j][l][0] != '\0' ) {
						fprintf(options->outFileStream,"%s",epoch->BufferBestGEO[selected].Buffer_printSATSEL[i][j][l]);
					}
				}
			}
		}
	}


	//Print INFO messages with the available solutions and their protections levels
	for(i=0;i<epoch->Buffer_NumDataStored;i++) {
		if(i==selected) continue; //Selected iteration will be printed the last one
		sprintf(messagestr,"%29s Solution available with GEO %3d in %sPA mode, HPL: %6.2f VPL: %6.2f (Not selected)",epoch->tSoDHourStr,epoch->BufferBestGEO[i].Buffer_GEOPRN,epoch->BufferBestGEO[i].Buffer_SBASMode==PAMODE?"":"N",epoch->BufferBestGEO[i].Buffer_HPL,epoch->BufferBestGEO[i].Buffer_VPL);
		printInfo(messagestr,options);
	}
	sprintf(messagestr,"%29s Solution available with GEO %3d in %sPA mode, HPL: %6.2f VPL: %6.2f (Selected)",epoch->tSoDHourStr,epoch->BufferBestGEO[selected].Buffer_GEOPRN,epoch->BufferBestGEO[selected].Buffer_SBASMode==PAMODE?"":"N",epoch->BufferBestGEO[selected].Buffer_HPL,epoch->BufferBestGEO[selected].Buffer_VPL);
	printInfo(messagestr,options);

	//Save GEO PRN for printing in SBASOUT message
	epoch->SBASUsedGEO=epoch->BufferBestGEO[selected].Buffer_GEOPRN;
	epoch->SBASUsedGEOindex=epoch->BufferBestGEO[selected].Buffer_GEOindex;
}


/*****************************************************************************
 * Name        : printUserError
 * Description : Prints the user added error values
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * double  **SatMeasError                   I  N/A  User added errors vector
 * int numpos                               I  N/A  Number of positions in SatMeasError vector
 * TOptions  *options                       I  N/A  TOptions structure 
 *****************************************************************************/
void printUserError (TEpoch *epoch, double **SatMeasError, int numpos, TOptions *options) {
	int				i;
	int				satIndex;
	enum GNSSystem	GNSS;

	for (i=0;i<numpos;i++) {
		GNSS=(int)SatMeasError[i][USRGNSSPOS];
		if (options->includeSatellite[GNSS][(int)SatMeasError[i][USRPRNPOS]]==0) continue; //Skip unselected satellites
		satIndex=(int)SatMeasError[i][USREPOCHPOS];
		if (GNSS==GLONASS) {
			if (whatIs((int)SatMeasError[i][USRMEASPOS])==CarrierPhase) {
				if (epoch->measOrder[GNSS].lambdaMeas[getFrequencyInt((int)SatMeasError[i][USRMEASPOS])][(int)SatMeasError[i][USRPRNPOS]]==1. ) {
					//Frequency offset not available. Do not print measurement
					continue;
				}
			}
		}
		printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=realloc(printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]],sizeof(char*)*(linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]+1));

		printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]]=NULL;
		printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]]=malloc(sizeof(char)*MAX_PRINT_LINE);

		if (options->printV5format==0) {
				sprintf(printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"USERADDEDERROR   %29s %4d %9.2f %3s %2d %3s %14.4f %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f\n",
				/*2*/			epoch->tSoDHourStr,
				/*3*/			/*DoY*/
				/*4*/			/*SoD*/
				/*5*/			/*HH:MM:SS.zz*/
				/*6*/			epoch->GPSweek,
				/*7*/			epoch->SoW,
				/*8*/			gnsstype2gnssstr(GNSS),	//GNSS system
				/*9*/			(int)SatMeasError[i][USRPRNPOS],			//PRN
				/*10*/			meastype2measstr((int)SatMeasError[i][USRMEASPOS]),	//Meas type
				/*11*/			SatMeasError[i][USRMEASRAWPOS],				//Raw measurement from RINEX
				/*12*/			SatMeasError[i][USRMEASTOTPOS],				//Raw measurement + total error value
				/*13*/			(int)SatMeasError[i][USRNUMTOTERRPOS],			//Total number of user defined error added
				/*14*/			SatMeasError[i][USRTOTERRPOS],				//Total user defined error value added
				/*15*/			(int)SatMeasError[i][USRNUMSTEPPOS],			//Number of Step function error added
				/*16*/			SatMeasError[i][USRSTEPERRPOS],				//Step function error value added
				/*17*/			(int)SatMeasError[i][USRNUMRAMPPOS],			//Number of Ramp function error added
				/*18*/			SatMeasError[i][USRRAMPERRPOS],				//Ramp function error value added
				/*19*/			(int)SatMeasError[i][USRNUMSINUPOS],			//Number of Sinusoidal function error added
				/*20*/			SatMeasError[i][USRSINUERRPOS],				//Sinusoidal function error value added
				/*21*/			(int)SatMeasError[i][USRNUMAWGNPOS],			//Number of AWGN function error added
				/*22*/			SatMeasError[i][USRAWGNERRPOS]);			//AWGN function error value added
			} else {
				sprintf(printbufferUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]][linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]],"USERADDEDERROR   %17s %4d %9.2f %3s %2d %3s %14.4f %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f\n",
				/*2*/			epoch->tStr,
				/*3*/			/*DoY*/
				/*4*/			/*SoD*/
				/*5*/			epoch->GPSweek,
				/*6*/			epoch->SoW,
				/*7*/			gnsstype2gnssstr(GNSS),	//GNSS system
				/*8*/			(int)SatMeasError[i][USRPRNPOS],			//PRN
				/*9*/			meastype2measstr((int)SatMeasError[i][USRMEASPOS]),	//Meas type
				/*10*/			SatMeasError[i][USRMEASRAWPOS],				//Raw measurement from RINEX
				/*11*/			SatMeasError[i][USRMEASTOTPOS],				//Raw measurement + total error value
				/*12*/			(int)SatMeasError[i][USRNUMTOTERRPOS],			//Total number of user defined error added
				/*13*/			SatMeasError[i][USRTOTERRPOS],				//Total user defined error value added
				/*14*/			(int)SatMeasError[i][USRNUMSTEPPOS],			//Number of Step function error added
				/*15*/			SatMeasError[i][USRSTEPERRPOS],				//Step function error value added
				/*16*/			(int)SatMeasError[i][USRNUMRAMPPOS],			//Number of Ramp function error added
				/*17*/			SatMeasError[i][USRRAMPERRPOS],				//Ramp function error value added
				/*18*/			(int)SatMeasError[i][USRNUMSINUPOS],			//Number of Sinusoidal function error added
				/*19*/			SatMeasError[i][USRSINUERRPOS],				//Sinusoidal function error value added
				/*20*/			(int)SatMeasError[i][USRNUMAWGNPOS],			//Number of AWGN function error added
				/*21*/			SatMeasError[i][USRAWGNERRPOS]);			//AWGN function error value added
		}

		linesstoredUserError[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]++;
	}
}

/*****************************************************************************
 * Name        : writeStdESA
 * Description : Writes the Stanford-ESA plot values into a file
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * FILE *fd                                 I  N/A  File descriptor where data is written
 * TStdESA *StdESA                          I  N/A  TStdESA struct                                        
 *****************************************************************************/
void writeStdESA (FILE *fd, TStdESA *StdESA) {
	unsigned int	i,j; //to avoid warning: comparison between signed and unsigned integer expressions
	double			posx,posy;

	// Print header for first line
	fprintf(fd,"#XSTEP  YSTEP  XMAX  YMAX\n");
	// Print resolution for each pixel in horizontal and vertical, and the maximum value for horizontal and vertical axis (in this order)
	fprintf(fd,"%6.3f %6.3f %5.1f %5.1f\n",StdESA->xstep,StdESA->ystep,StdESA->xmax,StdESA->ymax);

	// Print header for data
	fprintf(fd,"# XPOS   YPOS  NUM_HOR  NUM_VER\n");
	// Print values for horizontal and vertical errors
	for (i=0;i<StdESA->numpixelver;i++) {
		for (j=0;j<StdESA->numpixelhor;j++) {
			posx = (double)(j)*StdESA->xstep;
			posy = (double)(i)*StdESA->ystep;
			// Only plot ocurrences if they are greater than zero
			if ( StdESA->counthor[i][j] > 0 || StdESA->countver[i][j] > 0 ) {
				fprintf(fd,"%6.3f %6.3f %8llu %8llu\n",posx,posy,StdESA->counthor[i][j],StdESA->countver[i][j]);
			}
		}
	}
}


/*****************************************************************************
 * Name        : printDGNSS
 * Description : Prints global information related to the DGNSS
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TEpoch  *epochDGNSS             I  N/A  TEpoch structure
 * int satIndex                    I  N/A  Satellite index
 * double  dt                      I  s    Time between current epoch and PRC
 * double  deltaPRC                I  m    Delta of PRC corrections
 * double  deltaRRC                I  m    Delta of RRC corrections
 * double  dt2                     I  s    Time between current epoch and MSG type 2 from RTCM v2.x
 * double  sigmas                  I  N/A  Array with the weights of the current measurement
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printDGNSS (TEpoch *epoch, TEpoch *epochDGNSS, int satIndex, double dt, double deltaPRC, double deltaRRC, double dt2, double *sigmas, TOptions *options) {
	int j;

	if (options->printV5format==0) {
		j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
		sprintf( printbufferDGNSS[epoch->GNSS2PrintPos[epoch->sat[satIndex].GNSS]][epoch->sat2Printpos[satIndex]], "DGNSS     %29s %3s %2d %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
			/*2*/	epoch->tSoDHourStr,
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
			/*5*/	/*HH:MM:SS.zz*/
			/*6*/	gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
			/*7*/	epoch->sat[satIndex].PRN,
			/*8*/	epochDGNSS->dgnss.PRC[j],	// PRC
			/*9*/	epochDGNSS->dgnss.RRC[j],	// RRC
			/*10*/	dt,							// delta time for RRC
			/*11*/	deltaPRC,					// delta PRC
			/*12*/	deltaRRC,					// delta RRC
			/*13*/	dt2,						// delta time for RRC
			/*14*/	sigmas[0],					// Total sigma
			/*15*/	sigmas[1],					// Sigma UDRE
			/*16*/	sigmas[2],					// Sigma degradation
			/*17*/	sigmas[3],					// Sigma air
			/*18*/	sigmas[4],					// Sigma multipath
			/*19*/	sigmas[5]);					// Sigma inflation
	} else {
		j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
		sprintf( printbufferDGNSS[epoch->GNSS2PrintPos[epoch->sat[satIndex].GNSS]][epoch->sat2Printpos[satIndex]], "DGNSS     %17s %3s %2d %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
			/*2*/	epoch->tStr,
			/*3*/	/*DoY*/
			/*4*/	/*SoD*/
			/*5*/	gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
			/*6*/	epoch->sat[satIndex].PRN,
			/*7*/	epochDGNSS->dgnss.PRC[j],	// PRC
			/*8*/	epochDGNSS->dgnss.RRC[j],	// RRC
			/*9*/	dt,							// delta time for RRC
			/*10*/	deltaPRC,					// delta PRC
			/*11*/	deltaRRC,					// delta RRC
			/*12*/	dt2,						// delta time for RRC
			/*13*/	sigmas[0],					// Total sigma
			/*14*/	sigmas[1],					// Sigma UDRE
			/*15*/	sigmas[2],					// Sigma degradation
			/*16*/	sigmas[3],					// Sigma air
			/*17*/	sigmas[4],					// Sigma multipath
			/*18*/	sigmas[5]);					// Sigma inflation
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferDGNSS[epoch->GNSS2PrintPos[epoch->sat[satIndex].GNSS]][epoch->sat2Printpos[satIndex]]);
		printbufferDGNSS[epoch->GNSS2PrintPos[epoch->sat[satIndex].GNSS]][epoch->sat2Printpos[satIndex]][0]='\0';
	}
}

/*****************************************************************************
 * Name        : writeHeaderRINEXo
 * Description : Write a RINEX observation header from a RTCM binary file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       O  N/A  File descriptor
 * TRTCM3  *rtcm3                  I  N/A  TRTCM3 struct
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeHeaderRINEXo (FILE *fd, TRTCM3 *rtcm3, TOptions *options) {
	char	c1[4], l1[4], s1[4], c2[4], l2[4], s2[4];
	char	statID[60];
	struct	tm tm;
	char	*monthname;

	if ( options->rinexVersion == 2 ) fprintf(fd,"%9.2f%11s%-20s%-20s%-20s\n",2.11,"","OBSERVATION DATA","G (GPS)","RINEX VERSION / TYPE");
	if ( options->rinexVersion == 3 ) fprintf(fd,"%9.2f%11s%-20s%-20s%-20s\n",3.00,"","OBSERVATION DATA","G (GPS)","RINEX VERSION / TYPE");
	getcurrentsystemtime(&tm);      // Get current system time
	monthname=MonthName(tm.tm_mon+1);
	fprintf(fd,"gLAB                gAGE (www.gage.es)  %02d-%.3s-%02d %02d:%02d     PGM / RUN BY / DATE\n",tm.tm_mday,monthname,tm.tm_year%100,tm.tm_hour,tm.tm_min);
	fprintf(fd,"%-60s%-20s\n","RINEX GENERATED BY gLAB FROM A RTCM_3 BINARY FILE","COMMENT");
	sprintf(statID, "STATION ID: %d", rtcm3->msg1006.station_id);
	fprintf(fd,"%-60s%-20s\n",statID,"COMMENT");
	fprintf(fd,"%-60s%-20s\n","UNKNOWN","MARKER NAME");
	fprintf(fd,"%-20s%-40s%-20s\n","gAGE/UPC","gAGE/UPC","OBSERVER / AGENCY");
	fprintf(fd,"%-20s%-40s%-20s\n","UNKNOWN","UNKNOWN","REC # / TYPE / VERS");
	if ( rtcm3->msg1008.serialNum_no == 0 ) {
		strcpy(rtcm3->msg1008.serialNum,"UNKNOWN");
	}
	fprintf(fd,"%-20s%-40s%-20s\n",rtcm3->msg1008.serialNum,rtcm3->msg1008.descriptor,"ANT # / TYPE");
	fprintf(fd,"%14.4f%14.4f%14.4f%18s%-20s\n",rtcm3->msg1006.ecef_x,rtcm3->msg1006.ecef_y,rtcm3->msg1006.ecef_z,"","APPROX POSITION XYZ");
	fprintf(fd,"%14.4f%14.4f%14.4f%18s%-20s\n",rtcm3->msg1006.antenna_height,0.0,0.0,"","ANTENNA: DELTA H/E/N");
	if ( options->rinexVersion == 2 ) fprintf(fd,"%6d%6s%6s%6s%6s%6s%6s%18s%-20s\n",6,"C1","L1","S1","P2","L2","S2","","# / TYPES OF OBSERV");
	if ( options->rinexVersion == 3 ) {
		if ( rtcm3->msg1004[0].l1_code_indicator == 0 ) {
			strcpy(c1,"C1C"); strcpy(l1,"L1C"); strcpy(s1,"S1C");
		} else {
			if (options->printV5format==0) {
				strcpy(c1,"C1W"); strcpy(l1,"L1W"); strcpy(s1,"S1W");
			} else {
				strcpy(c1,"C1P"); strcpy(l1,"L1P"); strcpy(s1,"S1P");
			}
		}
		if ( rtcm3->msg1004[0].l2_code_indicator == 0 ) {
			strcpy(c2,"C2C"); strcpy(l2,"L2C"); strcpy(s2,"S2C");
		} else {
			if (options->printV5format==0) {
				strcpy(c2,"C2W"); strcpy(l2,"L2W"); strcpy(s2,"S2W");
			} else {
				strcpy(c2,"C2P"); strcpy(l2,"L2P"); strcpy(s2,"S2P");
			}
		}
		fprintf(fd,"%1s%2s%3d%1s%3s%1s%3s%1s%3s%1s%3s%1s%3s%1s%3s%30s%-20s\n","G","",6,"",c1,"",l1,"",s1,"",c2,"",l2,"",s2,"","SYS / # / OBS TYPES");
	}
}

/*****************************************************************************
 * Name        : writeRINEXo
 * Description : Write a RINEX observation epoch from a RTCM binary file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       O  N/A  File descriptor
 * TRTCM3 *rtcm3                   I  N/A  TRTCM3 struct
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeRINEXo (FILE *fd, TRTCM3 *rtcm3, TOptions *options) {
	int				totalSeconds;
	unsigned int	i;
	double			hour_d, mins_d, sec, doubleHour;
	int				mins, intHour;
	double 			C1, L1, S1, C2, L2, S2;
	int 			ind, snr1, snr2;
	int 			lli1;
	int 			lli2;
	int 			year;
	double 			doy;
	TTime 			t;
	static double 	AntPosX=0.,AntPosY=0.,AntPosZ=0.;


	// Time handling
	totalSeconds = rtcm3->header.epoch_time/1000;
	totalSeconds = totalSeconds-(86400*floor(totalSeconds/86400));
	// Hours
	hour_d = (double)totalSeconds/3600.0;
	rtcm3->hour = (int)floor(hour_d);
	intHour = (int)floor(hour_d);
	doubleHour = (double)floor(hour_d);
	// Minutes
	mins_d = (double)(hour_d-doubleHour)*60.0;
	mins = floor(mins_d);
	// Seconds
	sec = (double)(mins_d-mins)*60.0;

	// Check if a day has passed
	if ( rtcm3->doWeHaveHeader > 2 && intHour < (int)rtcm3->previousHour ) {

		year = (int)options->rtcmYear;
		doy = (double)options->rtcmDoy;

		t = cal2t(year, options->rtcmMonth, options->rtcmDay, 0, 0, 0);
		t.MJDN++;
		t2doy(&t, &year, &doy);
		options->rtcmYear = year;
		doy2date(year, (int)doy, &options->rtcmMonth, &options->rtcmDay);
	}

	// End the header message with the time of first observation
	if ( rtcm3->doWeHaveHeader == 2 ) {
		fprintf(fd,"%6d%4s%02d%4s%02d%4s%02d%4s%02d%13.7f%5s%3s%9s%-20s\n",options->rtcmYear,"",options->rtcmMonth,"",options->rtcmDay,"",intHour,"",mins,sec,"","GPS","","TIME OF FIRST OBS");
		if ( options->rinexVersion == 3 ) fprintf(fd,"%-60s%-20s\n","DBHZ","SIGNAL STRENGTH UNIT");
		fprintf(fd,"%-60s%-20s\n","","END OF HEADER");

		AntPosX=rtcm3->msg1006.ecef_x;
		AntPosY=rtcm3->msg1006.ecef_y;
		AntPosZ=rtcm3->msg1006.ecef_z;
	}

	if(rtcm3->doWeHaveHeader > 2 && (AntPosX!=rtcm3->msg1006.ecef_x || AntPosY!=rtcm3->msg1006.ecef_y || AntPosZ!=rtcm3->msg1006.ecef_z ) ) {
		// Time handling
		totalSeconds = rtcm3->header.epoch_time/1000;
		totalSeconds = totalSeconds-(86400*floor(totalSeconds/86400));
		// Hours
		hour_d = (double)totalSeconds/3600.0;
		rtcm3->hour = (int)floor(hour_d);
		intHour = (int)floor(hour_d);
		doubleHour = (double)floor(hour_d);
		// Minutes
		mins_d = (double)(hour_d-doubleHour)*60.0;
		mins = floor(mins_d);
		// Seconds
		sec = (double)(mins_d-mins)*60.0;

		if ( options->rinexVersion == 2 ) {
			fprintf(fd,"%3d%3d%3d%3d%3d%11.7f%3d%3d\n",options->rtcmYearShort,options->rtcmMonth,options->rtcmDay,intHour,mins,sec,4,2);
		} else if ( options->rinexVersion == 3 ) {
			fprintf(fd,"%-2s%-5d%02d%1s%02d%1s%02d%1s%02d%11.7f%3d%3d\n",">",options->rtcmYear,options->rtcmMonth,"",options->rtcmDay,"",intHour,"",mins,sec,4,2);
		}
		fprintf(fd,"%14.4f%14.4f%14.4f%18s%-20s\n",rtcm3->msg1006.ecef_x,rtcm3->msg1006.ecef_y,rtcm3->msg1006.ecef_z,"","APPROX POSITION XYZ");
		fprintf(fd,"%14.4f%14.4f%14.4f%18s%-20s\n",rtcm3->msg1006.antenna_height,0.0,0.0,"","ANTENNA: DELTA H/E/N");

		AntPosX=rtcm3->msg1006.ecef_x;
		AntPosY=rtcm3->msg1006.ecef_y;
		AntPosZ=rtcm3->msg1006.ecef_z;
	}

	if ( options->rinexVersion == 2 ) {
		fprintf(fd,"%3d%3d%3d%3d%3d%11.7f%3d%3d",options->rtcmYearShort,options->rtcmMonth,options->rtcmDay,intHour,mins,sec,0,rtcm3->header.gps_no);
		for (i=0;i<rtcm3->header.gps_no;i++) {
			fprintf(fd,"G%02d",rtcm3->msg1004[i].satellite_id);
			if ( i == rtcm3->header.gps_no-1 ) fprintf(fd,"\n");
		}
	} else if ( options->rinexVersion == 3 ) {
		fprintf(fd,"%-2s%-5d%02d%1s%02d%1s%02d%1s%02d%11.7f%3d%3d\n",">",options->rtcmYear,options->rtcmMonth,"",options->rtcmDay,"",intHour,"",mins,sec,0,rtcm3->header.gps_no);
	}

	// Loop for every satellite
	for (i=0;i<rtcm3->header.gps_no;i++) {
		lli1 = 0;
		lli2 = 0;

		ind = rtcm3->msg1004[i].satellite_id;

		C1 = rtcm3->msg1004[i].l1_pseudoR+rtcm3->msg1004[i].l1_N_ambiguity;
		L1 = (C1+rtcm3->msg1004[i].l1_part_phaseR)*GPSf1/c0;
		S1 = rtcm3->msg1004[i].l1_cnr;
		snr1 = min(max(floor(S1/6),1),9);
		if ( rtcm3->L1flagLLI[ind] == 1 ) lli1 = 1;
		C2 = C1+rtcm3->msg1004[i].pseudoR_differ;
		L2 = (C1+rtcm3->msg1004[i].l2Phase_l1Pseudo)*GPSf2/c0;
		S2 = rtcm3->msg1004[i].l2_cnr;
		snr2 = min(max(floor(S2/6),1),9);
		 if ( rtcm3->L2flagLLI[ind] == 1 ) lli2 = 1;
		if ( options->rinexVersion == 2 ) fprintf(fd,"%14.3f%2d%14.3f%1d%1d%14.3f%2s%14.3f%2d%14.3f%1d%1d\n%14.3f%2s\n",C1,(int)snr1,L1,lli1,(int)snr1,S1,"",C2,(int)snr2,L2,lli2,(int)snr2,S2,"");
		if ( options->rinexVersion == 3 ) fprintf(fd,"%1s%02d%14.3f%2d%14.3f%1d%1d%14.3f%2s%14.3f%2d%14.3f%1d%1d%14.3f%2s\n","G",rtcm3->msg1004[i].satellite_id,C1,(int)snr1,L1,lli1,(int)snr1,S1,"",C2,(int)snr2,L2,lli2,(int)snr2,S2,"");
	}

	// Update the previous hour to control if a day has passed
	rtcm3->previousHour = intHour;
}

/*****************************************************************************
 * Name        : writeRTCM2ascii
 * Description : write the decoded information into an output file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd_antenna                O  N/A  The pointer of the antenna output file
 * FILE *fd_corrections            O  N/A  The pointer of the data output file
 * TRTCM2 *rtcm2                   IO N/A  TRTCM2 structure
 * TEpoch  *epochDGNSS             O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
int writeRTCM2ascii (FILE *fd_antenna, FILE *fd_corrections, TRTCM2 *rtcm2, TEpoch *epochDGNSS, TOptions *options) {
	int			health = 0;
	char		*endptr;
	int			i, j, ns;
	//int			nb, np; //Commented to avoid warning "set but not used"
	int			doy, sod, mjdn, GPSweek;
	static int	lastCSindex=0;
	double		SoW;
	ns = rtcm2->header.dataword_no*CONTENTBIT / SATELLITEBIT;
	//nb = rtcm2->header.dataword_no / 3;
	//np = rtcm2->header.dataword_no / 3;
	TMSG1		sc1[ns+1];	//The +1 is to avoid size 0 when ns=0 (in this case TMSG1 and TMSG2 are not used)
	TMSG2		sc2[ns+1];
	TMSG3		sc3;
	TMSG24		sc24;


	// Write the header in the ASCII file
	if ( rtcm2->doWeHaveHeaderCorr == 0 && options->RTCMmode == ConvertRTCM2 ) {
		fprintf(fd_corrections,"GPS_week     SoW      |  MSG_number  Station_ID  Z-count  SV_health  |  PRN      PRC       RRC    IOD   UDRE\n");
		rtcm2->doWeHaveHeaderCorr = 1;
	}

	// Get the satellite health
	health = strtol(rtcm2->header.station_health, &endptr, 2);

	// Convert time to GPS week and Seconds of Week (SoW)
	if ( ( rtcm2->header.message_type == 1 || rtcm2->header.message_type == 2 ) && rtcm2->firstPass2 == 0 ) {
		doy = date2doy((int)options->rtcmYear, (int)options->rtcmMonth, (int)options->rtcmDay);
		sod = (int)(options->rtcmHour * 3600);
		mjdn = (int)yeardoy2MJDN((int)options->rtcmYear, doy, sod);
		rtcm2->t.MJDN = mjdn;
		rtcm2->t.SoD = sod;
		rtcm2->firstPass2 = 1;
	}
	if ( ( rtcm2->header.message_type == 1 || rtcm2->header.message_type == 2 ) && rtcm2->firstPass2 == 1 ) {
		if ( rtcm2->header.modi_zcount > rtcm2->prevZcount ) {
			rtcm2->t = tdadd(&rtcm2->t, rtcm2->header.modi_zcount - rtcm2->prevZcount);
		} else if ( rtcm2->header.modi_zcount < rtcm2->prevZcount ) {
			rtcm2->t = tdadd(&rtcm2->t, rtcm2->header.modi_zcount);
		}
		if ( rtcm2->header.modi_zcount != rtcm2->prevZcount ) rtcm2->prevZcount = rtcm2->header.modi_zcount;
		ttime2gpswsnoroll(&rtcm2->t, &GPSweek, &SoW);
	}

	switch ( rtcm2->header.message_type ) {
		case 1:
			initMSG1(sc1, ns);
			readMSG1(sc1, ns, rtcm2->body_str);
			for ( i=0;i<ns;i++ ) {
				if ( options->RTCMmode == ConvertRTCM2 ) {
					//                GPS_week   SoW   |  MSG_number   Station_ID  Z-count  SV_health |  PRN    PRC    RRC     IOD     UDRE
					fprintf(fd_corrections,"  %4d    %10.2f  |     01          %04d     %7.1f      %1d      |  G%02d  %8.3f  %8.4f   %03d     %1d\n",GPSweek,SoW,rtcm2->header.station_id,rtcm2->header.modi_zcount,health,sc1[i].satellite_id,sc1[i].prc,sc1[i].rrc,sc1[i].iod,sc1[i].udre);
				} else if ( options->RTCMmode == ProcessRTCM2 ) {
					epochDGNSS->sat[i].PRN = sc1[i].satellite_id;
					epochDGNSS->sat[i].GNSS = GPS;
				}
			}
			if ( options->RTCMmode == ProcessRTCM2 ) {
				epochDGNSS->numSatellites = ns;
				memcpy(&epochDGNSS->t,&rtcm2->t,sizeof(TTime));
				for ( i=0;i<ns;i++ ) {
					j = epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN];
					if (j==-1) {
						epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]=lastCSindex;
						j=lastCSindex;
						lastCSindex++;
					}
					epochDGNSS->dgnss.PRC[j] = sc1[i].prc;
					epochDGNSS->dgnss.RRC[j] = sc1[i].rrc;
					epochDGNSS->dgnss.health[j] = health;
					epochDGNSS->dgnss.UDRE[j] = sc1[i].udre;
					epochDGNSS->dgnss.msg[j] = 1;
					epochDGNSS->dgnss.IODmsg1[j] = sc1[i].iod;
					memcpy(&epochDGNSS->dgnss.tPRC[j], &rtcm2->t, sizeof(TTime));
				}
			}
			return bdrCORRECTIONSmsg1;
			break;
		case 2:
			initMSG2(sc2, ns);
			readMSG2(sc2, ns, rtcm2->body_str);
			for ( i=0;i<ns;i++ ) {
				if ( options->RTCMmode == ConvertRTCM2 ) {
					fprintf(fd_corrections,"  %4d    %10.2f  |     02          %04d     %7.1f      %1d      |  G%02d  %8.3f  %8.4f   %03d     %1d\n",GPSweek,SoW,rtcm2->header.station_id,rtcm2->header.modi_zcount,health,sc2[i].satellite_id,sc2[i].delta_prc,sc2[i].delta_rrc,sc2[i].iod,sc2[i].udre);
				} else if ( options->RTCMmode == ProcessRTCM2 ) {
					epochDGNSS->sat[i].PRN = sc2[i].satellite_id;
					epochDGNSS->sat[i].GNSS = GPS;
				}
			}
			if ( options->RTCMmode == ProcessRTCM2 ) {
				epochDGNSS->numSatellites = ns;
				for ( i=0;i<ns;i++ ) {
					j = epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN];
					if (j==-1) {
						epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]=lastCSindex;
						j=lastCSindex;
						lastCSindex++;
					}
					epochDGNSS->dgnss.deltaPRC[j] = sc2[i].delta_prc;
					epochDGNSS->dgnss.deltaRRC[j] = sc2[i].delta_rrc;
					epochDGNSS->dgnss.health[j] = health;
					epochDGNSS->dgnss.UDRE[j] = sc2[i].udre;
					epochDGNSS->dgnss.msg[j] = 2;
					epochDGNSS->dgnss.IODmsg2[j] = sc2[i].iod;
					memcpy(&epochDGNSS->dgnss.tdeltaPRC[j], &rtcm2->t, sizeof(TTime));
				}
			}
			return bdrCORRECTIONSmsg2;
			break;
		case 3:
			initMSG3(&sc3);
			readMSG3(&sc3, rtcm2->body_str);
			if ( rtcm2->antMSG3 == 0 ) {
				rtcm2->antMSG3 = 1;
				if ( options->RTCMmode == ConvertRTCM2 ) {
					if ( rtcm2->doWeHaveHeaderAnt == 0 ) fprintf(fd_antenna, "Station_ID  X_coordinate  Y_coordinate  Z_coordinate  MSG_number\n");
					fprintf(fd_antenna, "   %04d     %12.4f  %12.4f  %12.4f     MT03\n", rtcm2->header.station_id, sc3.x_coord, sc3.y_coord, sc3.z_coord);
					rtcm2->doWeHaveHeaderAnt = 1;
				} else if ( options->RTCMmode == ProcessRTCM2 && rtcm2->doWeHaveHeaderAnt == 0 ) {
					rtcm2->doWeHaveHeaderAnt = 1;
					epochDGNSS->receiver.aproxPosition[0] = sc3.x_coord;
					epochDGNSS->receiver.aproxPosition[1] = sc3.y_coord;
					epochDGNSS->receiver.aproxPosition[2] = sc3.z_coord;
				}
			}
			return bdrANTENNA;
			break;
		case 24:
			initMSG24(&sc24);
			readMSG24(&sc24, rtcm2->body_str);
			if ( rtcm2->antMSG24 == 0 ) {
				rtcm2->antMSG24 = 1;
				if ( options->RTCMmode == ConvertRTCM2 && rtcm2->doWeHaveHeaderAnt == 0 ) {
					if ( rtcm2->doWeHaveHeaderAnt == 0 ) fprintf(fd_antenna, "Station_ID  X_coordinate  Y_coordinate  Z_coordinate  MSG_number\n");
					fprintf(fd_antenna, "   %04d     %12.4f  %12.4f  %12.4f     MT24\n", rtcm2->header.station_id, sc24.x_coord, sc24.y_coord, sc24.z_coord);
					rtcm2->doWeHaveHeaderAnt = 1;
				} else if ( options->RTCMmode == ProcessRTCM2 && rtcm2->doWeHaveHeaderAnt == 0 ) {
					rtcm2->doWeHaveHeaderAnt = 1;
					epochDGNSS->receiver.aproxPosition[0] = sc24.x_coord;
					epochDGNSS->receiver.aproxPosition[1] = sc24.y_coord;
					epochDGNSS->receiver.aproxPosition[2] = sc24.z_coord;
				}
			}
			return bdrANTENNA;
			break;
		default:
			return brdrOther;
			break;
	}
}

/*****************************************************************************
 * Name        : writeRinexObsHeaderUserAddedError
 * Description : Write a RINEX observation header copying the header from the
 *                rover observation file (this is for creating an observation
 *                file with the rover data but with user adder error measurements.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       O  N/A  File descriptor
 * char **headerlines              I  N/A  char vector with the header lines
 * int numheaderlines              I  N/A  Number of header lines stored
 *****************************************************************************/
void writeRinexObsHeaderUserAddedError (FILE *fd, char **headerlines, int numheaderlines) {

	int i;

	for(i=0;i<numheaderlines;i++) {
		fprintf(fd,"%s\n",headerlines[i]);
	}
}

/*****************************************************************************
 * Name        : writeObsRinexEpochUserAddedError
 * Description : Write RINEX observation epoch from the rover observation file
 *                with user added error in measurements (in the same version
 *                and order as the rover observation file)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *outfd                    O  N/A  File descriptor for output RINEX file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeObsRinexEpochUserAddedError (FILE *outfd, TEpoch *epoch) {

    int		 	i,j;
	double		SecondsComp;
	struct tm	tm;


	//Fill tm struct
	t2tmnolocal(&epoch->t, &tm, &SecondsComp);

	if (epoch->source == RINEX2) {
		fprintf(outfd," %02d %2d %2d %2d %2d%11.7f  %d%3d",(tm.tm_year+1900)%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,0,epoch->numSatellites);
		for(i=0;i<epoch->numSatellites;i++) {
			if(i%12==0 && i>0) {
				fprintf(outfd,"\n%32s","");
			}
			fprintf(outfd,"%c%02d",gnsstype2char(epoch->sat[i].GNSS),epoch->sat[i].PRN);
		}
		fprintf(outfd,"\n");
		//Print measurements
		for (i=0;i<epoch->numSatellites;i++) {
			for(j=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurements;j++) {
				if(j%5==0 && j>0) {
					fprintf(outfd,"\n");
				}
				if (epoch->sat[i].meas[j].value==-1) {
					//If measurement is not available, print blank spaces
					fprintf(outfd,"%16s","");
				} else if (epoch->sat[i].meas[j].LLI==-2 && epoch->sat[i].meas[j].SNRflag==-1 ) {
					fprintf(outfd,"%14.3f  ",epoch->sat[i].meas[j].value);
				} else if (epoch->sat[i].meas[j].LLI==-2) {
					fprintf(outfd,"%14.3f %d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].SNRflag);
				} else if (epoch->sat[i].meas[j].SNRflag==-2) {
					fprintf(outfd,"%14.3f%d ",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI);
				} else {
					fprintf(outfd,"%14.3f%d%d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI,epoch->sat[i].meas[j].SNRflag);
				}
			}
			fprintf(outfd,"\n");
		}
	} else {
		//Header generated by gLAB
		fprintf(outfd,"> %4d %02d %02d %02d %02d%11.7f  %d%3d%6s %15s\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,0,epoch->numSatellites,"","");
		//Print measurements
		for (i=0;i<epoch->numSatellites;i++) {
			fprintf(outfd,"%c%02d",gnsstype2char(epoch->sat[i].GNSS),epoch->sat[i].PRN);
			for(j=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurements;j++) {
				if (epoch->sat[i].meas[j].value==-1) {
					//If measurement is not available, print blank spaces
					fprintf(outfd,"%16s","");
				} else if (epoch->sat[i].meas[j].LLI==-2 && epoch->sat[i].meas[j].SNRflag==-1 ) {
					fprintf(outfd,"%14.3f  ",epoch->sat[i].meas[j].value);
				} else if (epoch->sat[i].meas[j].LLI==-2) {
					fprintf(outfd,"%14.3f %d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].SNRflag);
				} else if (epoch->sat[i].meas[j].SNRflag==-2) {
					fprintf(outfd,"%14.3f%d ",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI);
				} else {
					fprintf(outfd,"%14.3f%d%d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI,epoch->sat[i].meas[j].SNRflag);
				}
			}
			fprintf(outfd,"\n");
		}
	}
}

/*****************************************************************************
 * Name        : writeKMLtags
 * Description : Write the KML XML tags into a file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd                        I  N/A  File descriptor of the output file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * char *filename                  I  N/A  Filename of the observation file
 * int mode                        I  N/A  0-> Write XML header 
 *                                         1-> Write XML footage
 * int heightmode                  I  N/A  0-> KML with height from solution
 *                                         1-> KML with height 0
 * char *version                   I  N/A  gLAB's version
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeKMLtags(FILE *fd, TEpoch  *epoch, char *filename, int mode, int heightmode, char *version, TOptions  *options) {

	int				i,j;
	int				insideRange;
	int				initMJDN;
	int				RangeLimit;
	double			offset;
	double			seconds;
	double			StaCoordNEU[3];
	struct tm		tm;
	char			auxDGNSS[50];
	char			solutionMode[50];
	long long int	nearestInt;
	long long int	TStampDec = (long long int)((options->KMLTimeStampDec+.00005)*10000.);
	long long int	TStampDecInteger = (long long int)(options->KMLTimeStampDec+.00005);
    long long int	TStampDecInterval=(long long int)((options->KMLTimeStampDec+.00005)*(double)(epoch->receiver.intervalDecimalsFactor));

	if (TStampDecInteger==0) TStampDecInteger=1;
	if (TStampDecInterval==0) TStampDecInterval=1;

	if(options->DGNSS==1) {
		sprintf(solutionMode,"%s","DGNSS");
		strcpy(auxDGNSS," [DGNSS solution]");
	} else {
		sprintf(solutionMode,"%s",SolutionModeNum2SolutionModeChar(options->solutionMode));
		auxDGNSS[0]='\0';
	}


	
	if(mode==0) {
		fprintf(fd,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(fd,"<kml xmlns=\"http://earth.google.com/kml/2.2\">\n");
		fprintf(fd,"  <Document>\n");
		fprintf(fd,"    <name>Coordinates for file %s</name>\n",filename);
		if(heightmode==0) {
			fprintf(fd,"    <description>Coordinates computed by gLAB v%s in %s mode</description>\n",version,solutionMode);
		} else {
			fprintf(fd,"    <description>Coordinates computed by gLAB v%s in %s mode (ground projection)</description>\n",version,solutionMode);
		}
		fprintf(fd,"    <Style id=\"yellowLineGreenPoly\">\n");
		fprintf(fd,"      <LineStyle>\n");
		fprintf(fd,"        <color>7f00ffff</color>\n");
		fprintf(fd,"        <width>4</width>\n");
		fprintf(fd,"      </LineStyle>\n");
		fprintf(fd,"      <PolyStyle>\n");
		fprintf(fd,"        <color>7f00ff00</color>\n");
		fprintf(fd,"      </PolyStyle>\n");
		fprintf(fd,"    </Style>\n");
		fprintf(fd,"    <Style id=\"redLine\">\n");
		fprintf(fd,"      <LineStyle>\n");
		fprintf(fd,"        <color>411400ff</color>\n");
		fprintf(fd,"        <width>4</width>\n");
		fprintf(fd,"      </LineStyle>\n");
		fprintf(fd,"      <PolyStyle>\n");
		fprintf(fd,"        <color>411400ff</color>\n");
		fprintf(fd,"      </PolyStyle>\n");
		fprintf(fd,"    </Style>\n");
		fprintf(fd,"    <Placemark>\n");
		fprintf(fd,"      <name>Coordinates for file %s</name>\n",filename);
		if(heightmode==0) {
			fprintf(fd,"      <description>Coordinates computed by gLAB v%s in %s mode%s</description>\n",version,solutionMode,auxDGNSS);
		} else {
			fprintf(fd,"      <description>Coordinates computed by gLAB v%s in %s mode (ground projection)%s</description>\n",version,solutionMode,auxDGNSS);
		}
		fprintf(fd,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
		fprintf(fd,"      <LineString>\n");
		fprintf(fd,"        <extrude>0</extrude>\n");
		fprintf(fd,"        <tessellate>1</tessellate>\n");
		if(heightmode==0) {
			fprintf(fd,"        <altitudeMode>absolute</altitudeMode>\n");
		} else {
			fprintf(fd,"        <altitudeMode>clampToGround</altitudeMode>\n");
		}
		fprintf(fd,"        <coordinates>\n");
	} else {
		fprintf(fd,"        </coordinates>\n");
		fprintf(fd,"      </LineString>\n");
		fprintf(fd,"    </Placemark>\n");

		if(options->KMLTimeStamps==1) {
			//Write TimeStamps
			initMJDN=epoch->firstEpochFile.MJDN;
			for(i=0;i<epoch->numKMLData;i++) {
					
				//Check time stamps are inside the time stamp ranges
				insideRange=1;
				RangeLimit=0;
				for(j=0;j<options->numKMLTimeRanges;j++) {
					insideRange=0;
					offset=((double)(epoch->KMLTime[i].MJDN-initMJDN))*86400.;
					if((epoch->KMLTime[i].SoD+offset)>options->KMLtimeranges[j][0] && (epoch->KMLTime[i].SoD+offset)<options->KMLtimeranges[j][1] ) {
						insideRange=1;
						RangeLimit=0;
						break;
					} else if((epoch->KMLTime[i].SoD+offset)==options->KMLtimeranges[j][0] || (epoch->KMLTime[i].SoD+offset)==options->KMLtimeranges[j][1] ) {
						//This is to make gLAB write always timestamps in the limits of the ranges
						insideRange=1;
						RangeLimit=1;
						break;
					}
				}

				if(insideRange==0) continue;

				//Check if we have to decimate timestamps (first and last epoch will always have the timestamp)
				if(options->KMLTimeStampDec>0. && i!=0 && i!=epoch->numKMLData && RangeLimit==0) {
					//The following "if" statements are for filtering decimals in timestamps due to
					//unconsistent timestamps (see function "isEpochDecimated" in preprocessing.c for details)
					nearestInt = (long long int)((epoch->KMLTime[i].SoD+.00005)*10000.);
					if ( (nearestInt%TStampDec) != 0 ) {
						if (epoch->receiver.interval>=1.) {
							nearestInt = (long long int)(epoch->KMLTime[i].SoD+.00005);
							if ( (nearestInt%TStampDecInteger) != 0 ) continue;
						} else if (epoch->receiver.interval>0.) {
							nearestInt = (long long int)((epoch->KMLTime[i].SoD+.00005)*epoch->receiver.intervalDecimalsFactor);
							if ( (nearestInt%TStampDecInterval) != 0 ) continue;
						} else {
							continue;
						}
					}
				}

				// Get the calendar time for toe (We use t2tm without localtime due to sometimes there was an hour shift)
				t2tmnolocal(&epoch->KMLTime[i],&tm,&seconds);

				fprintf(fd,"    <Placemark>\n");
				fprintf(fd,"      <TimeStamp>\n");
				fprintf(fd,"        <when>%04d-%02d-%02dT%02d:%02d:%02dZ</when>\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,(int)(fabs(modulo(epoch->KMLTime[i].SoD,60))));
				fprintf(fd,"      </TimeStamp>\n");
				fprintf(fd,"      <name>%s</name>\n",t2doystr(&epoch->KMLTime[i]));
				fprintf(fd,"      <description>%02d/%02d/%04d %02d:%02d:%02d (GPS time)</description>\n",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min,(int)(fabs(modulo(epoch->KMLTime[i].SoD,60))));
				//fprintf(options->fdkml,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
				fprintf(fd,"      <Point>\n");
				fprintf(fd,"        <coordinates>\n");
				if(heightmode==0) {
					fprintf(fd,"          %.9f,%.9f,%.9f\n",epoch->KMLData[i][1],epoch->KMLData[i][0],epoch->KMLData[i][2]-(options->KMLEGM96height==1?getEGM96Height(epoch->KMLData[i]):0.));
				} else {
					fprintf(fd,"          %.9f,%.9f,0.00\n",epoch->KMLData[i][1],epoch->KMLData[i][0]);
				}
				fprintf(fd,"        </coordinates>\n");
				if(heightmode==0) {
					fprintf(fd,"        <altitudeMode>absolute</altitudeMode>\n");
				}
				fprintf(fd,"      </Point>\n");
				fprintf(fd,"    </Placemark>\n");
			}
		}

		if(options->DGNSS==1) {
			//Write reference stations to KML file if the option is set
			if (options->referenceStations==1) {
				if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
					//Reference coordinates read from RINEX or RTCM
					for(i=0;i<epoch->receiver.numRecStation;i++) {
						XYZ2NEU(epoch->receiver.RecStationCoord[i],StaCoordNEU);
						StaCoordNEU[0]=StaCoordNEU[0]*r2d;
						StaCoordNEU[1]=StaCoordNEU[1]*r2d;
						fprintf(fd,"    <Placemark>\n");
						if(epoch->receiver.numRecStation==1) {
							fprintf(fd,"      <name>Reference Station</name>\n");
						} else {
							fprintf(fd,"      <name>Reference Station #%d</name>\n",i+1);
						}
						fprintf(fd,"      <description>Lon: %.4fº Lat: %.4fº Height %.4f m</description>\n",StaCoordNEU[1],StaCoordNEU[0],StaCoordNEU[2]);
						fprintf(fd,"      <Point>\n");
						fprintf(fd,"        <coordinates>\n");
						fprintf(fd,"          %.9f,%.9f,%.9f\n",StaCoordNEU[1],StaCoordNEU[0],StaCoordNEU[2]-(options->KMLEGM96height==1?getEGM96Height(StaCoordNEU):0.));
						fprintf(fd,"        </coordinates>\n");
						fprintf(fd,"        <altitudeMode>absolute</altitudeMode>\n");
						fprintf(fd,"      </Point>\n");
						fprintf(fd,"    </Placemark>\n");
					}
				} else {
					//Reference station set by user
					XYZ2NEU(options->ReferenceStationPosition,StaCoordNEU);
					StaCoordNEU[0]=StaCoordNEU[0]*r2d;
					StaCoordNEU[1]=StaCoordNEU[1]*r2d;
					fprintf(fd,"    <Placemark>\n");
					fprintf(fd,"      <name>Reference Station</name>\n");
					fprintf(fd,"      <description>Lon: %.4fº Lat: %.4fº Height %.4f m</description>\n",StaCoordNEU[1],StaCoordNEU[0],StaCoordNEU[2]);
					fprintf(fd,"      <Point>\n");
					fprintf(fd,"        <coordinates>\n");
					fprintf(fd,"          %.9f,%.9f,%.9f\n",StaCoordNEU[1],StaCoordNEU[0],StaCoordNEU[2]-(options->KMLEGM96height==1?getEGM96Height(StaCoordNEU):0.));
					fprintf(fd,"        </coordinates>\n");
					fprintf(fd,"        <altitudeMode>absolute</altitudeMode>\n");
					fprintf(fd,"      </Point>\n");
					fprintf(fd,"    </Placemark>\n");

				}
			}

			if(epoch->receiver.numRecStation>1) {
				if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
					//Write the epochs where we started to use the new reference stations
					j=0;
					for(i=0;i<epoch->receiver.numRecStation-1;i++) {
						//Search for coordinates
						for(;j<epoch->numKMLData;j++) {
							if(tdiff(&epoch->KMLTime[j],&epoch->receiver.ChangedStaEpoch[i])>=0.) {
								t2tmnolocal(&epoch->KMLTime[j],&tm,&seconds);
								fprintf(fd,"    <Placemark>\n");
								fprintf(fd,"      <name>Started to use reference station #%d</name>\n",i+2);
								fprintf(fd,"      <description>Epoch %s, %02d:%02d:%02d (GPS time)</description>\n",t2doystr(&epoch->KMLTime[j]),tm.tm_hour,tm.tm_min,(int)(fabs(modulo(epoch->KMLTime[j].SoD,60))));
								fprintf(fd,"      <Point>\n");
								fprintf(fd,"        <coordinates>\n");
								fprintf(fd,"          %.9f,%.9f,%.9f\n",epoch->KMLData[j][1],epoch->KMLData[j][0],epoch->KMLData[j][2]-(options->KMLEGM96height==1?getEGM96Height(epoch->KMLData[i]):0.));
								fprintf(fd,"        </coordinates>\n");
								if(heightmode==0) {
									fprintf(fd,"        <altitudeMode>absolute</altitudeMode>\n");
								}
								fprintf(fd,"      </Point>\n");
								fprintf(fd,"    </Placemark>\n");
								break;
							}
						}
					}
				}
			}
		}

		fprintf(fd,"  </Document>\n");
		fprintf(fd,"</kml>");
	}
}


/*****************************************************************************
 * Name        : writeSP3file
 * Description : Write gLAB's navigation solution in SP3 format
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd                        I  N/A  File descriptor of the output file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Solution of the filter
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 * int EndofFile                   I  N/A  0-> Write data 1-> Write End of file
 * char *version                   I  N/A  gLAB's version
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeSP3file(FILE *fd, TEpoch  *epoch, TFilterSolution  *solution, TUnkinfo  *unkinfo, int EndofFile, char *version, TOptions  *options) {

	static int 			header=0;
	static unsigned int	numepochs=0;
	int					indx;
	double				seconds;
	double				datainterval;
	struct tm 			tm;


	if (header==0) {
		//Write header

		//Get interval
		if (options->decimate>=epoch->receiver.interval) {
			//Epochs are decimated
			datainterval=options->decimate;
		} else {
			datainterval=epoch->receiver.interval;
		}

		// Get the calendar time for first epoch
		t2tmnolocal(&epoch->t,&tm,&seconds);

		fprintf(fd,"#cP%4d %2d %2d %2d %2d %11.8f -------     u WGS84 BCT gLAB\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,fabs(modulo(epoch->t.SoD,60)));
		fprintf(fd,"## %4d %15.8f %14.8f %5d %15.13f\n",epoch->GPSweek,epoch->SoW,datainterval,epoch->t.MJDN,epoch->t.SoD/86400.);
		fprintf(fd,"+    1   %c%02d  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n",options->SP3Letter,options->SP3PRN);
		fprintf(fd,"+          0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"+          0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"+          0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"+          0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n");
		fprintf(fd,"%%c %c  cc GPS ccc cccc cccc cccc cccc ccccc ccccc ccccc ccccc\n",options->SP3Letter);
		fprintf(fd,"%%c cc cc ccc ccc cccc cccc cccc cccc ccccc ccccc ccccc ccccc\n");
		fprintf(fd,"%%f  0.0000000  0.000000000  0.00000000000  0.000000000000000\n");
		fprintf(fd,"%%f  0.0000000  0.000000000  0.00000000000  0.000000000000000\n");
		fprintf(fd,"%%i    0    0    0    0      0      0      0      0         0\n");
		fprintf(fd,"%%i    0    0    0    0      0      0      0      0         0\n");
		fprintf(fd,"/* NOTE: File generated by gLAB v%-27s\n",version);
		fprintf(fd,"/* The position and clock values in this file are the       \n");
		fprintf(fd,"/* navigation solution from gLAB. The data rate is the same \n");
		fprintf(fd,"/* as the decimation set in gLAB.                           \n");
		header=1;
	}

	if (EndofFile==0) {
		//Write epoch
		numepochs++;

		// First index of XYZ
		indx = unkinfo->par2unk[DR_UNK];
		
		// Get the calendar time for currennt epoch
		t2tmnolocal(&epoch->t,&tm,&seconds);
		fprintf(fd,"*  %4d %2d %2d %2d %2d %11.8f\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,fabs(modulo(epoch->t.SoD,60)));
		fprintf(fd,"P%c%02d%14.6f%14.6f%14.6f%14.6f\n",options->SP3Letter,options->SP3PRN,solution->x[indx+0]/1000,solution->x[indx+1]/1000,solution->x[indx+2]/1000,solution->x[indx+3]*1E6/c0);

	} else {
		//Write END OF FILE and the number of epochs written in the header
		fprintf(fd,"EOF");
		fseek(fd,32,SEEK_SET);
		fprintf(fd,"%7d",numepochs);
	}
}

/*****************************************************************************
 * Name        : writeReffile
 * Description : Write gLAB's navigation solution in a columnar text format
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd                        I  N/A  File descriptor of the output file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Solution of the filter
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeReffile(FILE *fd, TEpoch  *epoch, TFilterSolution  *solution, TUnkinfo  *unkinfo, TOptions  *options) {

	int			indx;
	int			year;
	double		coordNEU[3];
	double		doy;
	double		seconds;
	struct tm	tm;

	// First index of XYZ
	indx = unkinfo->par2unk[DR_UNK];

	if (options->GPSWeekRefFile==1) {
		//Take out decimals from third decimal (to avoid 0.999 .001 bad timestamps)
		if ((epoch->SoW-(double)((int)(epoch->SoW)))>0.999) {
			seconds=(double)((int)(epoch->SoW))+1.;
		} else {
			seconds=epoch->SoW;
		}
		if (options->GeodeticCoordRefFile==1) {
			XYZ2NEU(&solution->x[indx],coordNEU);
			fprintf(fd,"%4d %10.3f %14.9f %14.9f %14.4f\n",epoch->GPSweek,seconds,coordNEU[1]*r2d,coordNEU[0]*r2d,coordNEU[2]);
		} else {
			fprintf(fd,"%4d %10.3f %14.4f %14.4f %14.4f\n",epoch->GPSweek,seconds,solution->x[indx+0],solution->x[indx+1],solution->x[indx+2]);
		}
	} else if (options->CalendarTimeRefFile==1) {
		//Fill tm struct of calendar time
		t2tmnolocal(&epoch->t, &tm, &seconds);
		//Take out decimals from third decimal (to avoid 0.999 .001 bad timestamps)
		if ((seconds-(double)((int)(seconds)))>0.999) {
			seconds=(double)((int)(seconds))+1.;
		}
		if (options->GeodeticCoordRefFile==1) {
			XYZ2NEU(&solution->x[indx],coordNEU);
			fprintf(fd,"%4d/%02d/%02d %02d:%02d:%06.3f %14.9f %14.9f %14.4f\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,coordNEU[1]*r2d,coordNEU[0]*r2d,coordNEU[2]);
		} else {
			fprintf(fd,"%4d/%02d/%02d %02d:%02d:%06.3f %14.4f %14.4f %14.4f\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,solution->x[indx+0],solution->x[indx+1],solution->x[indx+2]);
		}
	} else {
		//Compute Year/DoY/SoD
		t2doy(&epoch->t,&year,&doy);
		//Take out decimals from third decimal (to avoid 0.999 .001 bad timestamps)
		if ((epoch->t.SoD-(double)((int)(epoch->t.SoD)))>0.999) {
			seconds=(double)((int)(epoch->t.SoD))+1.;
		} else {
			seconds=epoch->t.SoD;
		}
		if (options->GeodeticCoordRefFile==1) {
			XYZ2NEU(&solution->x[indx],coordNEU);
			fprintf(fd,"%04d %03d %9.3f %14.9f %14.9f %14.4f\n",year,(int)(doy),seconds,coordNEU[1]*r2d,coordNEU[0]*r2d,coordNEU[2]);
		} else {
			fprintf(fd,"%04d %03d %9.3f %14.4f %14.4f %14.4f\n",year,(int)(doy),seconds,solution->x[indx+0],solution->x[indx+1],solution->x[indx+2]);
		}
	}
}

/*****************************************************************************
 * Name        : writeSBASAvailFile (for SBAS plots mode only)
 * Description : Write the file with SBAS Availability map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fdAvail                   I  N/A  File descriptor of the output Availability file
 * FILE *fdRisk                    I  N/A  File descriptor of the output Risk file
 * FILE *fdRiskMar                 I  N/A  File descriptor of the output Risk file (maritime mode)
 * FILE *fdDiscont                 I  N/A  File descriptor of the output discontinuity file
 * FILE *fdHDOP                    I  N/A  File descriptor of the output HDOP file
 * FILE *fdPDOP                    I  N/A  File descriptor of the output PDOP file
 * FILE *fdGDOP                    I  N/A  File descriptor of the output GDOP file
 * FILE *fdCombDOP                 I  N/A  File descriptor of the output combined DOP file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TSBASPlots *SBASplots           I  N/A  TSBASPlots struct
 * int totalAvailabilityEpochs     I  N/A  Number of epochs computed
 * int hour						   I  N/A  Current hour of map (-1 is for the hole day)
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeSBASAvailFile (FILE *fdAvail, FILE *fdRisk, FILE *fdRiskMar, FILE *fdDiscont, FILE *fdHDOP, FILE *fdPDOP, FILE *fdGDOP, FILE *fdCombDOP, TEpoch  *epoch, TSBASPlots *SBASplots, int totalAvailabilityEpochs, int hour, TOptions *options) {

    int         latPos;
    int         lonPos;
    int         Year;
	int			GEOused;
	int			HAlarmformat;
	int			VAlarmformat;
	int			percentileSamples;
	int			percentileSamplesHourly;
    double      DoY;
    double      latitude;
    double      longitude;
	double		LastEpochHour;
	double		DiscontinuityDuration; 		//Duration in seconds of the discontinuity
	double		NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double		HDOPPercentile,PDOPPercentile,GDOPPercentile;
	double		HDOPPercentileHourly,PDOPPercentileHourly,GDOPPercentileHourly;

    t2doy(&epoch->t,&Year,&DoY);

	if (options->switchGEO==1) {
		GEOused=0;
	} else {
		GEOused=options->GEOPRN;
	}

	if (options->HorAlarmLimit>=1000) {
		HAlarmformat=0;
	} else {
		HAlarmformat=2;
	}

	if (options->VerAlarmLimit>=1000) {
		VAlarmformat=0;
	} else {
		VAlarmformat=2;
	}

    //Write files header
	if (hour==-1) {
		fprintf(fdAvail,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK\n");
		fprintf(fdAvail," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d);
	} else {
		fprintf(fdAvail,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK HOUR\n");
		fprintf(fdAvail," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,hour);
	}
    fprintf(fdAvail,"#  LAT     LON AVAIL%% NUMAVAIL NUMEPOCHS\n");

	if(options->NoContRiskPlot==0) {
		if (hour==-1) {
			if (fdRisk!=NULL) {
			    fprintf(fdRisk,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE\n");
				fprintf(fdRisk," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f %11d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,options->ContRiskWindowSize);
			}
			if (fdRiskMar!=NULL) {
			    fprintf(fdRiskMar,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE\n");
				fprintf(fdRiskMar," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f %11d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,options->ContRiskWindowSize);
			}
		} else {
			if (fdRisk!=NULL) {
			    fprintf(fdRisk,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE HOUR\n");
				fprintf(fdRisk," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f %11d   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,options->ContRiskWindowSize,hour);
			}
			if (fdRiskMar!=NULL) {
			    fprintf(fdRiskMar,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE HOUR\n");
				fprintf(fdRiskMar," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f %11d   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,options->ContRiskWindowSize,hour);
			}
		}
		if (fdRisk!=NULL) {
        	fprintf(fdRisk,"#  LAT     LON      CONT-RISK    NUMRISK NUMEPOCHS\n");
		}
		if (fdRiskMar!=NULL) {
        	fprintf(fdRiskMar,"#  LAT     LON      CONT-RISK NUMDISCONT NUMEPOCHS\n");
		}
	}

	if(hour==-1) {
		if(fdHDOP!=NULL) {
			fprintf(fdHDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK\n");
			fprintf(fdHDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d);
		}
		if(fdPDOP!=NULL) {
			fprintf(fdPDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK\n");
			fprintf(fdPDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d);
		}
		if(fdGDOP!=NULL) {
			fprintf(fdGDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK\n");
			fprintf(fdGDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d);
		}
		if(fdCombDOP!=NULL) {
			fprintf(fdCombDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK\n");
			fprintf(fdCombDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d);
		}
	} else {
		if(fdHDOP!=NULL) {
			fprintf(fdHDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK HOUR\n");
			fprintf(fdHDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,hour);
		}
		if(fdPDOP!=NULL) {
			fprintf(fdPDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK HOUR\n");
			fprintf(fdPDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,hour);
		}
		if(fdGDOP!=NULL) {
			fprintf(fdGDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK HOUR\n");
			fprintf(fdGDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,hour);
		}
		if(fdCombDOP!=NULL) {
			fprintf(fdCombDOP,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK HOUR\n");
			fprintf(fdCombDOP," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.*f %6.*f %03d %4d %9d %7d %9.2f   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->AvailabilityPlotStep,options->SBASPlotsRecHeight,HAlarmformat,options->HorAlarmLimit,VAlarmformat,options->VerAlarmLimit,(int)DoY,Year,totalAvailabilityEpochs,GEOused,options->elevationMask*r2d,hour);
		}
	}
	if(fdHDOP!=NULL) {
    	fprintf(fdHDOP,"#  LAT     LON    MEANHDOP       TOTALHDOP NUMEPOCHS   %sPERCENT%02d\n",options->percentile==100.?"":" ",(int)options->percentile);
	}
	if(fdPDOP!=NULL) {
    	fprintf(fdPDOP,"#  LAT     LON    MEANPDOP       TOTALPDOP NUMEPOCHS   %sPERCENT%02d\n",options->percentile==100.?"":" ",(int)options->percentile);
	}
	if(fdGDOP!=NULL) {
    	fprintf(fdGDOP,"#  LAT     LON    MEANGDOP       TOTALGDOP NUMEPOCHS   %sPERCENT%02d\n",options->percentile==100.?"":" ",(int)options->percentile);
	}
	if(fdCombDOP!=NULL) {
		fprintf(fdCombDOP,"#  LAT     LON    MEANHDOP       TOTALHDOP   %sPERCENT%02d    MEANPDOP       TOTALPDOP   %sPERCENT%02d    MEANGDOP       TOTALGDOP   %sPERCENT%02d NUMEPOCHS\n",options->percentile==100.?"":" ",(int)options->percentile,options->percentile==100.?"":" ",(int)options->percentile,options->percentile==100.?"":" ",(int)options->percentile);
	}

    //Write data. One entry of longitude,latitude per line
    latPos=-1;
    for(latitude=options->minLatplots;latitude<=options->maxLatplots;latitude+=options->AvailabilityPlotStep) {
        latPos++;
        lonPos=-1;
		for(longitude=options->minLonplots;longitude<=options->maxLonplots;longitude+=options->AvailabilityPlotStep) {
			lonPos++;
			//Write Availability plot
			if(totalAvailabilityEpochs!=0) {
				if (hour==-1) {
					fprintf(fdAvail,"%6.2f %7.2f %6.1f %8d %9d\n",
							latitude,
							longitude,
							100.*(double)(SBASplots->SBASNumEpochsAvail[latPos][lonPos])/((double)(totalAvailabilityEpochs)),
							SBASplots->SBASNumEpochsAvail[latPos][lonPos],
							totalAvailabilityEpochs);
				} else {
					fprintf(fdAvail,"%6.2f %7.2f %6.1f %8d %9d\n",
							latitude,
							longitude,
							100.*(double)(SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos])/((double)(totalAvailabilityEpochs)),
							SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos],
							totalAvailabilityEpochs);
				}
			} else {
				fprintf(fdAvail,"%6.2f %7.2f %6.1f %8d %9d\n",
						latitude,
						longitude,
						0.,
						0,
						0);
			}

			if(options->NoContRiskPlot==0) {
				//Continuity Risk plot has been computed. Write it in its file

				if (hour==-1) {
					//Check if there has been a discontinuity in the last epoch. In that case, update values and write it to file
					if(SBASplots->LastEpochAvailPrevCurrDisc[latPos][lonPos]!=86399.) {
						//There has been a discontinuity
						DiscontinuityDuration=epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDisc[latPos][lonPos];
						NoDiscontinuityDuration=SBASplots->LastEpochAvailPrevCurrDisc[latPos][lonPos]-SBASplots->FirstEpochAvailAfterPrevDisc[latPos][lonPos]+1.;
						if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
							SBASplots->SBASNumEpochsRisk[latPos][lonPos]+=options->ContRiskWindowSize;
						} else {
							SBASplots->SBASNumEpochsRisk[latPos][lonPos]+=(int)NoDiscontinuityDuration;
						}
						SBASplots->SBASNumEpochsRiskMar[latPos][lonPos]++;
						fprintf(fdDiscont,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDisc[latPos][lonPos]+1.,epoch->t.SoD,DiscontinuityDuration,NoDiscontinuityDuration);
					}
					if (fdRisk!=NULL) {
						if(SBASplots->SBASNumEpochsAvail[latPos][lonPos]!=0) {
							fprintf(fdRisk,"%6.2f %7.2f %14.1E %10d %9d\n",
									latitude,
									longitude,
									(double)(SBASplots->SBASNumEpochsRisk[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsAvail[latPos][lonPos])),
									SBASplots->SBASNumEpochsRisk[latPos][lonPos],
									SBASplots->SBASNumEpochsAvail[latPos][lonPos]);
						} else {
							//SBASplots->SBASNumEpochsAvail[latPos][lonPos]=0, which means there was no epochs available in PA. Therefore the continuity risk is 1
							fprintf(fdRisk,"%6.2f %7.2f %14.1f %10d %9d\n",
									latitude,
									longitude,
									1.,
									0,
									0);
						}
					}
					if (fdRiskMar!=NULL) {
						if(SBASplots->SBASNumEpochsAvail[latPos][lonPos]!=0) {
							fprintf(fdRiskMar,"%6.2f %7.2f %14.1E %10d %9d\n",
									latitude,
									longitude,
									(double)(SBASplots->SBASNumEpochsRiskMar[latPos][lonPos]*options->ContRiskWindowSizeMar)/epoch->numEpochsfile,
									SBASplots->SBASNumEpochsRiskMar[latPos][lonPos],
									(int)epoch->numEpochsfile);
						} else {
							//SBASplots->SBASNumEpochsAvail[latPos][lonPos]=0, which means there was no epochs available in PA. Therefore the continuity risk is 1
							fprintf(fdRiskMar,"%6.2f %7.2f %14.1f %10d %9d\n",
									latitude,
									longitude,
									1.,
									0,
									0);
						}
					}
				} else {
					//Check if there has been a discontinuity in the last epoch of the current hour. In that case, update values and write it to file
					if(SBASplots->LastEpochAvailPrevCurrDiscHourly[latPos][lonPos]!=(double)(hour*3600+3599)) {
						//There has been a discontinuity
						if (hour!=23) {
							//For each hourly map (except for hour 23 -the last one-), the discontinuity file is written the next epoch,
							//When it is detected that the hour changed.
							//In the last hour, hour 23, it doesn't occur due to it is the end of the processing, so no more epochs are processed
							LastEpochHour=epoch->t.SoD-1.;
						} else {
							LastEpochHour=epoch->t.SoD;
						}
						DiscontinuityDuration=LastEpochHour-SBASplots->LastEpochAvailPrevCurrDiscHourly[latPos][lonPos];
						NoDiscontinuityDuration=SBASplots->LastEpochAvailPrevCurrDiscHourly[latPos][lonPos]-SBASplots->FirstEpochAvailAfterPrevDiscHourly[latPos][lonPos]+1.;
						if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
							SBASplots->SBASNumEpochsRiskHourly[latPos][lonPos]+=options->ContRiskWindowSize;
						} else {
							SBASplots->SBASNumEpochsRiskHourly[latPos][lonPos]+=(int)NoDiscontinuityDuration;
						}
						SBASplots->SBASNumEpochsRiskHourlyMar[latPos][lonPos]++;
						fprintf(fdDiscont,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDiscHourly[latPos][lonPos]+1.,LastEpochHour,DiscontinuityDuration,NoDiscontinuityDuration);
					}
					if(fdRisk!=NULL) {
						if(SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos]!=0) {
							fprintf(fdRisk,"%6.2f %7.2f %14.1E %10d %9d\n",
									latitude,
									longitude,
									(double)(SBASplots->SBASNumEpochsRiskHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos])),
									SBASplots->SBASNumEpochsRiskHourly[latPos][lonPos],
									SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos]);
						} else {
							//SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos]=0, which means there was no epochs available in PA. Therefore the continuity risk is 1
							fprintf(fdRisk,"%6.2f %7.2f %14.1f %10d %9d\n",
									latitude,
									longitude,
									1.,
									0,
									0);
						}
					}
					if(fdRiskMar!=NULL) {
						if(SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos]!=0) {
							fprintf(fdRiskMar,"%6.2f %7.2f %14.1E %10d %9d\n",
									latitude,
									longitude,
									(double)(SBASplots->SBASNumEpochsRiskHourlyMar[latPos][lonPos]*options->ContRiskWindowSizeMar)/((double)totalAvailabilityEpochs),
									SBASplots->SBASNumEpochsRiskHourlyMar[latPos][lonPos],
									totalAvailabilityEpochs);
						} else {
							//SBASplots->SBASNumEpochsAvailHourly[latPos][lonPos]=0, which means there was no epochs available in PA. Therefore the continuity risk is 1
							fprintf(fdRiskMar,"%6.2f %7.2f %14.1f %10d %9d\n",
									latitude,
									longitude,
									1.,
									0,
									0);
						}
					}
				}
			}
			if(options->CombinedDOPPlot==1) {
				if(hour==-1) {
					if(SBASplots->SBASNumEpochsDOP[latPos][lonPos]!=0) {
						if(options->DOPPercentile) {
							//Compute percentiles
							if(options->percentile==100.) {
								percentileSamples=SBASplots->SBASNumEpochsDOP[latPos][lonPos]-1;
							} else {
								percentileSamples=(int)((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])*options->percentile/100.);
							}
							qsort(SBASplots->HDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
							qsort(SBASplots->PDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
							qsort(SBASplots->GDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
							HDOPPercentile=(double)SBASplots->HDOPValues[latPos][lonPos][percentileSamples];
							PDOPPercentile=(double)SBASplots->PDOPValues[latPos][lonPos][percentileSamples];
							GDOPPercentile=(double)SBASplots->GDOPValues[latPos][lonPos][percentileSamples];
						} else {
							HDOPPercentile=PDOPPercentile=GDOPPercentile=0.;
						}
						fprintf(fdCombDOP,"%6.2f %7.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %9d\n",
								latitude,
								longitude,
								(double)(SBASplots->HDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->HDOPMean[latPos][lonPos],
								HDOPPercentile,
								(double)(SBASplots->PDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->PDOPMean[latPos][lonPos],
								PDOPPercentile,
								(double)(SBASplots->GDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->GDOPMean[latPos][lonPos],
								GDOPPercentile,
								SBASplots->SBASNumEpochsDOP[latPos][lonPos]);
					} else {
						fprintf(fdCombDOP,"%6.2f %7.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %9d\n",
							latitude,
							longitude,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0);
					}
				} else {
					if(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]!=0) {
						if(options->DOPPercentile) {
							//Compute hourly percentiles
							if(options->percentile==100.) {
								percentileSamplesHourly=SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]-1;
							} else {
								percentileSamplesHourly=(int)((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])*options->percentile/100.);
							}
							qsort(SBASplots->HDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
							qsort(SBASplots->PDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
							qsort(SBASplots->GDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
							HDOPPercentileHourly=(double)SBASplots->HDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
							PDOPPercentileHourly=(double)SBASplots->PDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
							GDOPPercentileHourly=(double)SBASplots->GDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
						} else {
							HDOPPercentileHourly=PDOPPercentileHourly=GDOPPercentileHourly=0.;
						}
						fprintf(fdCombDOP,"%6.2f %7.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %9d\n",
								latitude,
								longitude,
								(double)(SBASplots->HDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->HDOPMeanHourly[latPos][lonPos],
								HDOPPercentileHourly,
								(double)(SBASplots->PDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->PDOPMeanHourly[latPos][lonPos],
								PDOPPercentileHourly,
								(double)(SBASplots->GDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->GDOPMeanHourly[latPos][lonPos],
								GDOPPercentileHourly,
								SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]);
					} else {
						fprintf(fdCombDOP,"%6.2f %7.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %11.2f %15.2f %12.2f %9d\n",
							latitude,
							longitude,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0.,
							0);
					}
				}
			}
			if(options->HDOPPlot==1) {
				if(hour==-1) {
					if(SBASplots->SBASNumEpochsDOP[latPos][lonPos]!=0) {
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								//Compute percentiles
								if(options->percentile==100.) {
									percentileSamples=SBASplots->SBASNumEpochsDOP[latPos][lonPos]-1;
								} else {
									percentileSamples=(int)((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->HDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
								HDOPPercentile=(double)SBASplots->HDOPValues[latPos][lonPos][percentileSamples];
							} else {
								HDOPPercentile=0.;
							}
						}
						fprintf(fdHDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->HDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->HDOPMean[latPos][lonPos],
								SBASplots->SBASNumEpochsDOP[latPos][lonPos],
								HDOPPercentile);
					} else {
						fprintf(fdHDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				} else {
					if(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]!=0) {
						//Compute hourly percentiles
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								if(options->percentile==100.) {
									percentileSamplesHourly=SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]-1;
								} else {
									percentileSamplesHourly=(int)((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->HDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
								HDOPPercentileHourly=(double)SBASplots->HDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
							} else {
								HDOPPercentileHourly=0.;
							}
						}
						fprintf(fdHDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->HDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->HDOPMeanHourly[latPos][lonPos],
								SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],
								HDOPPercentileHourly);
					} else {
						fprintf(fdHDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				}
			}
			if(options->PDOPPlot==1) {
				if(hour==-1) {
					if(SBASplots->SBASNumEpochsDOP[latPos][lonPos]!=0) {
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								//Compute percentiles
								if(options->percentile==100.) {
									percentileSamples=SBASplots->SBASNumEpochsDOP[latPos][lonPos]-1;
								} else {
									percentileSamples=(int)((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->PDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
								PDOPPercentile=(double)SBASplots->PDOPValues[latPos][lonPos][percentileSamples];
							} else {
								PDOPPercentile=0.;
							}
						}
						fprintf(fdPDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->PDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->PDOPMean[latPos][lonPos],
								SBASplots->SBASNumEpochsDOP[latPos][lonPos],
								PDOPPercentile);
					} else {
						fprintf(fdPDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				} else {
					if(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]!=0) {
						//Compute hourly percentiles
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								if(options->percentile==100.) {
									percentileSamplesHourly=SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]-1;
								} else {
									percentileSamplesHourly=(int)((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->PDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
								PDOPPercentileHourly=(double)SBASplots->PDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
							} else {
								PDOPPercentileHourly=0.;
							}
						}
						fprintf(fdPDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->PDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->PDOPMeanHourly[latPos][lonPos],
								SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],
								PDOPPercentileHourly);
					} else {
						fprintf(fdPDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				}
			}
			if(options->GDOPPlot==1) {
				if(hour==-1) {
					if(SBASplots->SBASNumEpochsDOP[latPos][lonPos]!=0) {
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								//Compute percentiles
								if(options->percentile==100.) {
									percentileSamples=SBASplots->SBASNumEpochsDOP[latPos][lonPos]-1;
								} else {
									percentileSamples=(int)((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->GDOPValues[latPos][lonPos],SBASplots->SBASNumEpochsDOP[latPos][lonPos],sizeof(float),qsort_compare_float);
								GDOPPercentile=(double)SBASplots->GDOPValues[latPos][lonPos][percentileSamples];
							} else {
								GDOPPercentile=0.;
							}
						}
						fprintf(fdGDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->GDOPMean[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOP[latPos][lonPos])),
								SBASplots->GDOPMean[latPos][lonPos],
								SBASplots->SBASNumEpochsDOP[latPos][lonPos],
								GDOPPercentile);
					} else {
						fprintf(fdGDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				} else {
					if(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]!=0) {
						//Compute hourly percentiles
						if(fdCombDOP==NULL) {
							if(options->DOPPercentile) {
								if(options->percentile==100.) {
									percentileSamplesHourly=SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos]-1;
								} else {
									percentileSamplesHourly=(int)((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])*options->percentile/100.);
								}
								qsort(SBASplots->GDOPValuesHourly[latPos][lonPos],SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],sizeof(float),qsort_compare_float);
								GDOPPercentileHourly=(double)SBASplots->GDOPValuesHourly[latPos][lonPos][percentileSamplesHourly];
							} else {
								GDOPPercentileHourly=0.;
							}
						}
						fprintf(fdGDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
								latitude,
								longitude,
								(double)(SBASplots->GDOPMeanHourly[latPos][lonPos])/((double)(SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos])),
								SBASplots->GDOPMeanHourly[latPos][lonPos],
								SBASplots->SBASNumEpochsDOPHourly[latPos][lonPos],
								GDOPPercentileHourly);
					} else {
						fprintf(fdGDOP,"%6.2f %7.2f %11.2f %15.2f %9d %12.2f\n",
							latitude,
							longitude,
							0.,
							0.,
							0,
							0.);
					}
				}
			}
		}
    }
}

/*****************************************************************************
 * Name        : writeSBASIonoAvailFile (for SBAS plots mode only)
 * Description : Write the file with SBAS Ionosphere correction availability map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd                        I  N/A  File descriptor of the output file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TSBASPlots *SBASplots           I  N/A  TSBASPlots struct
 * int totalIonoEpochs             I  N/A  Number of epochs computed
 * int hour						   I  N/A  Current hour of map (-1 is for the hole day)
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeSBASIonoAvailFile (FILE *fd, TEpoch  *epoch, TSBASPlots *SBASplots, int totalIonoEpochs, int hour, TOptions *options) {

	int			latPos;
	int			lonPos;
	int			Year;
	int			GEOused;
	double		DoY;
	double 		latitude;
	double		longitude;

	t2doy(&epoch->t,&Year,&DoY);

	if (options->switchGEO==1) {
		GEOused=0;
	} else {
		GEOused=options->GEOPRN;
	}

	//Write file header
	if (hour==-1) {
	    fprintf(fd,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION DoY YEAR NUMEPOCHS GEO-PRN\n");
		fprintf(fd," %6.2f %6.2f %7.2f %7.2f %10.2f %03d %4d %9d %7d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->IonoPlotStep,(int)DoY,Year,totalIonoEpochs,GEOused);
	} else {
		fprintf(fd,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION DoY YEAR NUMEPOCHS GEO-PRN HOUR\n");
		fprintf(fd," %6.2f %6.2f %7.2f %7.2f %10.2f %03d %4d %9d %7d   %02d\n",options->minLatplots,options->maxLatplots,options->minLonplots,options->maxLonplots,options->IonoPlotStep,(int)DoY,Year,totalIonoEpochs,GEOused,hour);
	}
	fprintf(fd,"#  LAT     LON AVAIL%% NUMAVAIL NUMEPOCHS\n");

	//Write data. One entry of longitude,latitude per line
	latPos=-1;
	for(latitude=options->minLatplots;latitude<=options->maxLatplots;latitude+=options->IonoPlotStep) {
		latPos++;
		lonPos=-1;
		for(longitude=options->minLonplots;longitude<=options->maxLonplots;longitude+=options->IonoPlotStep) {
			lonPos++;
			if(totalIonoEpochs!=0) {
				if (hour==-1) {
					fprintf(fd,"%6.2f %7.2f %6.1f %8d %9d\n",
							latitude,
							longitude,
							100.*(double)(SBASplots->IonoNumEpochsAvail[latPos][lonPos])/((double)(totalIonoEpochs)),
							SBASplots->IonoNumEpochsAvail[latPos][lonPos],
							totalIonoEpochs);
				} else {
					fprintf(fd,"%6.2f %7.2f %6.1f %8d %9d\n",
							latitude,
							longitude,
							100.*(double)(SBASplots->IonoNumEpochsAvailHourly[latPos][lonPos])/((double)(totalIonoEpochs)),
							SBASplots->IonoNumEpochsAvailHourly[latPos][lonPos],
							totalIonoEpochs);
				}
			} else {
				fprintf(fd,"%6.2f %7.2f %6.1f %8d %9d\n",
						latitude,
						longitude,
						0.,
						0,
						0);
			}
		}
	}
}

/*****************************************************************************
 * Name        : printSBASSummary
 * Description : print SBAS summary at the end of the output file
 * Parameters  :
 * Name                                       |Da|Unit|Description
 * long long unsigned int StartTimeRealPCTime  I  N/A  Program start time in number of 
 *                                                      microseconds since 1 January 1970 
 * int *ProcTimeLength                         O  N/A  Number of characters used for printing
 *                                                      total processing time
 * int *PosProcTime                            O  N/A  Position where processing time text
 *                                                      starts in last line of summary                                                     
 * TEpoch  *epoch                              I  N/A  TEpoch structure
 * TSBASdatabox *SBASdatabox                   I  N/A  Struct with SBAS data and summary
 * TStdESA *StdESA                             I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options                          I  N/A  TOptions structure
 *****************************************************************************/
void printSBASSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch *epoch, TSBASdatabox *SBASdatabox,  TStdESA *StdESA, TOptions *options) {

	int						i;
	int						aux,maxLengthConstComb=0,lenMaxNumber;
	int						GPSWeek;
	int						percentileSamples,percentile50Samples;
	int						year,DoW;
	int						NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation,TotalEpochsSkipped;
	int						NumEpochsDataGapSummary,numEpochsDecimatedAfterLastEpochSummary;
	int						PercentileDecimals=2,PercentileDigits=6;
	int						numEpochsFirstFix;
	int						maxErrorlen,maxDOPlen,maxIRlen,len;
	unsigned int			j;
	double					DataInterval;
	double					percentage;
	double 					SoW,DoY;
	double					RefPercentage;
	double					PAPercentage,NPAPercentage,PALimitsPercentage,RiskVal,RiskMarVal;
	double					NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double					MIEpochsPercentage,HMIEpochsPercentage,VMIEpochsPercentage;
	double					FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double					SamplesSolPercentage,SamplesSkippedPercentage,SamplesMIPercentage,SamplesHMIPercentage,SamplesVMIPercentage;
	double					NoRefSolEpochPercentage,NoRefSumEpochPercentage,NoRefConstPercentage;
	double					TimeDiff;
	double					TimeToFirstFix;
	double					SecondsComp;
	char					receiverid[5],auxstr[50];
	char					NPAletter[2];
	char					minPDOPsatStr[MAX_GNSS*8],minGDOPsatStr[MAX_GNSS*8],minTDOPsatStr[MAX_GNSS*8],minHDOPsatStr[MAX_GNSS*8],minVDOPsatStr[MAX_GNSS*8];
	char					maxPDOPsatStr[MAX_GNSS*8],maxGDOPsatStr[MAX_GNSS*8],maxTDOPsatStr[MAX_GNSS*8],maxHDOPsatStr[MAX_GNSS*8],maxVDOPsatStr[MAX_GNSS*8];
	char					MaxNErrorStr[MAX_GNSS*8],MaxEErrorStr[MAX_GNSS*8],MaxHErrorStr[MAX_GNSS*8],MaxVErrorStr[MAX_GNSS*8],Max3DErrorStr[MAX_GNSS*8];
	char					MinHPLStr[MAX_GNSS*8],MaxHPLStr[MAX_GNSS*8],MinVPLStr[MAX_GNSS*8],MaxVPLStr[MAX_GNSS*8];
	char					HBIRStr[MAX_GNSS*8],VBIRStr[MAX_GNSS*8],HWIRStr[MAX_GNSS*8],VWIRStr[MAX_GNSS*8];
	char					procTimestr[50];
	TTime					FirstEpoch,LastEpoch;
	struct tm			 	tm;
	long long unsigned int	totalprocessingTime;


	if (options->UserForcedNPA==1) {
		NPAletter[0]='N';
		NPAletter[1]='\0';
	} else {
		NPAletter[0]='\0';
	}

	//Convert receiver name to lower case
	for(i=0;i<4;i++) {
		receiverid[i]=tolower(epoch->receiver.name[i]);
	}
	receiverid[4]='\0';

	//Get data interval
	DataInterval=epoch->receiver.interval;
	if (options->decimate>epoch->receiver.interval && options->decimate!=0.) {
		//If decimation is higher than file data rate, then set the value to the epoch decimation
		DataInterval=options->decimate;
	} else {
		DataInterval=epoch->receiver.interval;
	}

	//Get last epoch processed
	if (options->EndEpoch.MJDN!=-1) {
		if (tdiff(&options->EndEpoch,&epoch->t)>0.) {
			//Last epoch processed is prior to the end epoch
			memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
		} else {
			memcpy(&LastEpoch,&options->EndEpoch,sizeof(TTime));
		}
	} else {
		memcpy(&LastEpoch,&epoch->LastSummaryEpoch,sizeof(TTime));
	}

	//Get number of epochs passed in the summary interval
	if (epoch->StartSummaryEpoch.MJDN!=-1) {
		NumEpochsSummaryPeriod=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/DataInterval)+1;
	} else {
		NumEpochsSummaryPeriod=0;
	}

	//Get number of epochs missing in file in summary interval
	if (NumEpochsSummaryPeriod!=0) {
		NumEpochsMissingSummary=NumEpochsSummaryPeriod-epoch->TotalEpochs;
	} else {
		NumEpochsMissingSummary=0;
	}

	//Get number of epochs missing in file in summary interval that were decimated
	if (NumEpochsSummaryPeriod!=0) {
		if (isEpochDecimated(epoch,options)==1) {
			numEpochsDecimatedAfterLastEpochSummary=(int)(tdiff(&epoch->t,&LastEpoch)/epoch->receiver.interval);
		} else {
			numEpochsDecimatedAfterLastEpochSummary=0;
		}

		NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1+numEpochsDecimatedAfterLastEpochSummary-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstEpochFile)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
	} else {
		NumEpochsMissingFile=0;
	}

	//Get total number of epochs in data gaps in summary
	if(DataInterval>epoch->receiver.interval) {
		NumEpochsDataGapSummary=NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation;
	} else {
		NumEpochsDataGapSummary=NumEpochsMissingSummary;
	}

	//Check number of decimals to be printed for percentile
	if (options->percentile==(double)((int)(options->percentile+0.005))) {
		PercentileDecimals=0;
		PercentileDigits=3;
	}

	// Check number of TotalPAEpochs for printable values
	if(SBASdatabox->TotalPAEpochs==0) {
		epoch->MaxNError=0.;
		epoch->MaxEError=0.;
		epoch->MaxHError=0.;
		epoch->MaxVError=0.;
		epoch->Max3DError=0.;
		epoch->HDOPPercentileSamples=0.;
		epoch->PDOPPercentileSamples=0.;
		epoch->GDOPPercentileSamples=0.;
		epoch->TDOPPercentileSamples=0.;
		epoch->VDOPPercentileSamples=0.;
		epoch->NumSatUsedPercentSamples=0;
		epoch->NumSatNotUsedPercentSamples=0;
		epoch->NumSatUsed50PercentSamples=0;
		epoch->NumSatNotUsed50PercentSamples=0;
		epoch->MinNumSatUsed=0;
		epoch->MaxNumSatUsed=0;
		epoch->MinNumSatNotUsed=0;
		epoch->MaxNumSatNotUsed=0;
		SBASdatabox->MaxHPL=0.;
		SBASdatabox->MaxVPL=0.;
		SBASdatabox->MinHPL=0.;
		SBASdatabox->MinVPL=0.;
		SBASdatabox->HWIR=0.;
		SBASdatabox->VWIR=0.;
		numEpochsFirstFix=0;
		TimeToFirstFix=0.;
		lenMaxNumber=1;
	} else {
		//Compute time to first fix
		TimeToFirstFix=tdiff(&epoch->FirstEpochSolution,&epoch->firstEpochFile);
		numEpochsFirstFix=(int)(TimeToFirstFix/DataInterval)+1;

		//Compute mean values
		epoch->MeanNumSatUsed/=(double)SBASdatabox->TotalPAEpochs;
		epoch->MeanNumSatNotUsed/=(double)SBASdatabox->TotalPAEpochs;
		for(i=0;i<MAX_GNSS;i++) {
			epoch->MeanNumSatUsedGNSS[i]/=(double)SBASdatabox->TotalPAEpochs;
			epoch->MeanNumSatNotUsedGNSS[i]/=(double)SBASdatabox->TotalPAEpochs;
		}
		epoch->MeanNumConstUsed/=(double)SBASdatabox->TotalPAEpochs;
		epoch->MeanNumConstNotUsed/=(double)SBASdatabox->TotalPAEpochs;

		//Compute max lengths for constellations combinations
		if (epoch->numconstCombUsed>4) {
			for(j=0;j<epoch->numconstCombUsed;j++) {
				aux=(int)strlen(epoch->constCombinationText[j]);
				if (aux>maxLengthConstComb) {
					maxLengthConstComb=aux;
				}
			}
			sprintf(auxstr,"%d",epoch->TotalEpochsRef);
			lenMaxNumber=(int)strlen(auxstr);
		} else {
			maxLengthConstComb=1;
			lenMaxNumber=1;
		}

		if (epoch->TotalEpochsRef==0) {
			epoch->MaxNError=0.;
			epoch->MaxEError=0.;
			epoch->MaxHError=0.;
			epoch->MaxVError=0.;
			epoch->Max3DError=0.;
			SBASdatabox->HBIR=0.;
			SBASdatabox->VBIR=0.;
			SBASdatabox->HWIR=0.;
			SBASdatabox->VWIR=0.;
			SBASdatabox->HIRPercentileSamples=0.;
			SBASdatabox->VIRPercentileSamples=0.;
		} else {
			if (options->recPosProvided==1) {
				if(options->percentile==100.) {
					percentileSamples=epoch->TotalEpochsRef-1;
				} else {
					percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
				}
				//Compute NPE percentile of the samples
				qsort(epoch->NError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->NPEPercentileSamples=epoch->NError[percentileSamples];
				//Compute EPE percentile of the samples
				qsort(epoch->EError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->EPEPercentileSamples=epoch->EError[percentileSamples];
				//Compute HPE percentile of the samples
				qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
				//Compute VPE percentile of the samples
				qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
				//Compite HIR percentile of the samples
				qsort(SBASdatabox->HIR,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				SBASdatabox->HIRPercentileSamples=SBASdatabox->HIR[percentileSamples];
				//Compite VIR percentile of the samples
				qsort(SBASdatabox->VIR,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				SBASdatabox->VIRPercentileSamples=SBASdatabox->VIR[percentileSamples];
				//Compute 3D PE percentile of the samples
				qsort(epoch->Error3D,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->PE3DPercentileSamples=epoch->Error3D[percentileSamples];
			}
		}
		if(options->percentile==100.) {
			percentileSamples=SBASdatabox->TotalPAEpochs-1;
		} else {
			percentileSamples=(int)((double)(SBASdatabox->TotalPAEpochs)*options->percentile/100.);
		}
		percentile50Samples=(int)((double)(SBASdatabox->TotalPAEpochs)*50./100.);
		//Compute HPL percentile of the samples
		qsort(SBASdatabox->HPL,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		SBASdatabox->HPLPercentileSamples=SBASdatabox->HPL[percentileSamples];
		//Compute VPL percentile of the samples
		qsort(SBASdatabox->VPL,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		SBASdatabox->VPLPercentileSamples=SBASdatabox->VPL[percentileSamples];
		//Compute HDOP percentile of the samples
		qsort(epoch->HDOP,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		epoch->HDOPPercentileSamples=epoch->HDOP[percentileSamples];
		//Compute PDOP percentile of the samples
		qsort(epoch->PDOP,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		epoch->PDOPPercentileSamples=epoch->PDOP[percentileSamples];
		//Compute GDOP percentile of the samples
		qsort(epoch->GDOP,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		epoch->GDOPPercentileSamples=epoch->GDOP[percentileSamples];
		//Compute TDOP percentile of the samples
		qsort(epoch->TDOP,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		epoch->TDOPPercentileSamples=epoch->TDOP[percentileSamples];
		//Compute VDOP percentile of the samples
		qsort(epoch->VDOP,SBASdatabox->TotalPAEpochs,sizeof(double),qsort_compare_double);
		epoch->VDOPPercentileSamples=epoch->VDOP[percentileSamples];
		//Compute used satellites used percentile
		qsort(epoch->NumSatUsed,SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int_reverse);//Use reverse order so the percentile refers to at least N satellites used
		epoch->NumSatUsedPercentSamples=epoch->NumSatUsed[percentileSamples];
		epoch->NumSatUsed50PercentSamples=epoch->NumSatUsed[percentile50Samples];
		//Compute not used satellites used percentile
		qsort(epoch->NumSatNotUsed,SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int);
		epoch->NumSatNotUsedPercentSamples=epoch->NumSatNotUsed[percentileSamples];
		epoch->NumSatNotUsed50PercentSamples=epoch->NumSatNotUsed[percentile50Samples];
		//Compute used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue; //Skip not used constellations to save computation time
			qsort(epoch->NumSatUsedGNSS[i],SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
			epoch->NumSatUsedPercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentileSamples];
			epoch->NumSatUsed50PercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentile50Samples];
		}
		//Compute not used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue; //Skip unselected constellations to save computation time
			qsort(epoch->NumSatNotUsedGNSS[i],SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int);
			epoch->NumSatNotUsedPercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentileSamples];
			epoch->NumSatNotUsed50PercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentile50Samples];
		}
		//Compute used constellations percentile 
		qsort(epoch->NumConstUsed,SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
		epoch->NumConstUsedPercentSamples=epoch->NumConstUsed[percentileSamples];
		epoch->NumConstUsed50PercentSamples=epoch->NumConstUsed[percentile50Samples];
		//Compute not used constellations percentile 
		qsort(epoch->NumConstNotUsed,SBASdatabox->TotalPAEpochs,sizeof(int),qsort_compare_int);
		epoch->NumConstNotUsedPercentSamples=epoch->NumConstNotUsed[percentileSamples];
		epoch->NumConstNotUsed50PercentSamples=epoch->NumConstNotUsed[percentile50Samples];
	}

	//Compute availability percentages
	if(epoch->TotalEpochs==0) {
		PAPercentage=0.;
		NPAPercentage=0.;
		RefPercentage=0.;
		PALimitsPercentage=0.;
		MIEpochsPercentage=0.;
		HMIEpochsPercentage=0.;
		VMIEpochsPercentage=0.;
		FewSatEpochsPercentage=0.;
		SingularEpochsPercentage=0.;
		NoRefConstPercentage=0.;
        DOPEpochsPercentage=0.;
        HDOPEpochsPercentage=0.;
        PDOPEpochsPercentage=0.;
        GDOPEpochsPercentage=0.;
        HDOPorPDOPEpochsPercentage=0.;
		NumEpochsSummaryPeriod=0;
		NoRefSolEpochPercentage=0;
		NoRefSumEpochPercentage=0;

	} else {
		PAPercentage=100.*(double)(SBASdatabox->TotalPAEpochs)/((double)(epoch->TotalEpochs));
		NPAPercentage=100.*(double)(SBASdatabox->TotalNPAEpochs)/((double)(epoch->TotalEpochs));
		PALimitsPercentage=100.*(double)(SBASdatabox->TotalPAEpochsAvail)/((double)(epoch->TotalEpochs));
		RefPercentage=100.*(double)(epoch->TotalEpochsRef)/((double)(epoch->TotalEpochs));
		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			MIEpochsPercentage=100.*(double)(SBASdatabox->NumMI)/((double)(epoch->TotalEpochsRef));
			HMIEpochsPercentage=100.*(double)(SBASdatabox->NumHMI)/((double)(epoch->TotalEpochsRef));
			VMIEpochsPercentage=100.*(double)(SBASdatabox->NumVMI)/((double)(epoch->TotalEpochsRef));
		} else {
			MIEpochsPercentage=0.;
			HMIEpochsPercentage=0.;
			VMIEpochsPercentage=0;
		}
		FewSatEpochsPercentage=100.*(double)(epoch->NumNoSatSkipped)/((double)(epoch->TotalEpochs));
		SingularEpochsPercentage=100.*(double)(epoch->NumSingularMatrixSkipped)/((double)(epoch->TotalEpochs));
		NoRefConstPercentage=100.*(double)(epoch->NumNoRefGNSSSkipped)/((double)(epoch->TotalEpochs));
        DOPEpochsPercentage=100.*(double)(epoch->NumDOPSkipped)/((double)(epoch->TotalEpochs));;
        HDOPEpochsPercentage=100.*(double)(epoch->NumHDOPSkipped)/((double)(epoch->TotalEpochs));
        PDOPEpochsPercentage=100.*(double)(epoch->NumPDOPSkipped)/((double)(epoch->TotalEpochs));
        GDOPEpochsPercentage=100.*(double)(epoch->NumGDOPSkipped)/((double)(epoch->TotalEpochs));
        HDOPorPDOPEpochsPercentage=100.*(double)(epoch->NumHDOPorPDOPSkipped)/((double)(epoch->TotalEpochs));
		NoRefSumEpochPercentage=100.*(double)(epoch->NumNoRefSumSkipped)/((double)(epoch->TotalEpochs));
		NoRefSolEpochPercentage=100.*(double)(epoch->NumNoRefSolSkipped)/((double)(epoch->TotalEpochs));
	}

	//Compute availability percentages for Stanford-ESA if required
	if(options->stanfordesa==1) {
		if(StdESA->numsamplesProcessed==0) {
			SamplesSolPercentage=0.;
			SamplesSkippedPercentage=0.;
			SamplesMIPercentage=0.;
			SamplesHMIPercentage=0.;
			SamplesVMIPercentage=0.;
		} else {
			SamplesSolPercentage=100.*(double)(StdESA->numsamplesComputed)/((double)(StdESA->numsamplesProcessed));
			SamplesSkippedPercentage=100.*(double)(StdESA->numsamplesSingular)/((double)(StdESA->numsamplesProcessed));
			if(options->recPosProvided==1 ) {
				SamplesMIPercentage=100.*(double)(StdESA->numsamplesMI)/((double)(StdESA->numsamplesProcessed));
				SamplesHMIPercentage=100.*(double)(StdESA->numsamplesHMI)/((double)(StdESA->numsamplesProcessed));
				SamplesVMIPercentage=100.*(double)(StdESA->numsamplesVMI)/((double)(StdESA->numsamplesProcessed));
			} else {
				SamplesMIPercentage=0.;
				SamplesHMIPercentage=0.;
				SamplesVMIPercentage=0.;
			}
		}
	}

	if(SBASdatabox->TotalPAEpochsAvail==0) {
		RiskVal=1.;
		RiskMarVal=1.;
	} else {
		//Check if there has been a discontinuity in the last epoch
		TimeDiff=tdiff(&epoch->t,&SBASdatabox->LastEpochAvailPrevCurrDisc);
		if(TimeDiff>SBASdatabox->decimation) {
			//There has been a discontinuity
			TimeDiff=tdiff(&SBASdatabox->LastEpochAvailPrevCurrDisc,&SBASdatabox->FirstEpochAvailAfterPrevDisc);
			NoDiscontinuityDuration=TimeDiff/SBASdatabox->decimation+1.;

			if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
				SBASdatabox->NumEpochsRisk+=options->ContRiskWindowSize;
			} else {
				SBASdatabox->NumEpochsRisk+=(int)NoDiscontinuityDuration;
			}
			SBASdatabox->NumEpochsRiskMar++;
		}
		RiskVal=(double)(SBASdatabox->NumEpochsRisk)/((double)(SBASdatabox->TotalPAEpochsAvail));
		RiskMarVal=(double)(SBASdatabox->NumEpochsRiskMar*options->ContRiskWindowSizeMar)/((double)(NumEpochsSummaryPeriod));
	}


	//Set values to 0 if receiver position is not set
	if(options->recPosProvided==0) {
		 SBASdatabox->HWIR=0.;
		 SBASdatabox->VWIR=0.;
		 epoch->HPEPercentileSamples=0.;
		 epoch->VPEPercentileSamples=0.;
		 epoch->MaxHError=0.;
		 epoch->MaxVError=0.;
	}
	
	//Compute total epochs skipped (any reason)
	TotalEpochsSkipped=epoch->NumNoRefSolSkipped+epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumNoRefGNSSSkipped+epoch->NumDOPSkipped;

	// Print SBAS Summary heading
	fprintf(options->outFileStream,"INFO --------------------- SBAS Summary ---------------------\n");

	//Print Alarm limits provided
	fprintf(options->outFileStream,"INFO Horizontal Alarm limit: %6.2f metres\n",options->HorAlarmLimit);
	fprintf(options->outFileStream,"INFO Vertical   Alarm limit: %6.2f metres\n",options->VerAlarmLimit);
    //Print DOP thresholds
	if(options->HDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO HDOP Threshold: %6.2f\n",options->maxHDOP);
	}
	if(options->PDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO PDOP Threshold: %6.2f\n",options->maxPDOP);
	}
	if(options->GDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO GDOP Threshold: %6.2f\n",options->maxGDOP);
	}

	//Print first epoch processed
	if (options->firstEpochSummary.MJDN!=-1 && epoch->StartSummaryEpoch.MJDN==-1) {
		memcpy(&FirstEpoch,&options->firstEpochSummary,sizeof(TTime));
		//Get GPSWeek
		ttime2gpswsnoroll(&options->firstEpochSummary, &GPSWeek, &SoW);
		//Compute calendar date
		t2tmnolocal(&options->firstEpochSummary, &tm, &SecondsComp);
		//Get DoY
		t2doy(&options->firstEpochSummary,&year,&DoY);
		//Start epoch of summary provided by user is ahead of all epochs in observation file
		fprintf(options->outFileStream,"INFO First epoch of summary provided by user: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&options->firstEpochSummary),GPSWeek,SoW);
		if (epoch->StartSummaryEpoch.MJDN==-1) {
			if (epoch->TotalEpochs>0 && epoch->TotalEpochsSol>0) {
				fprintf(options->outFileStream,"INFO First epoch of summary provided by user is ahead of all epochs in observation file. No epochs included in the summary\n");
			}
		}
	} else if (epoch->StartSummaryEpoch.MJDN==-1) {
		if (epoch->t.MJDN!=-1) {
			fprintf(options->outFileStream,"INFO No epochs after convergence time (from 0h onwards)\n");
			memcpy(&FirstEpoch,&epoch->firstEpochFile,sizeof(TTime));
		} else {
			fprintf(options->outFileStream,"INFO No data available in observation file\n");
			FirstEpoch.MJDN=-1;
			FirstEpoch.SoD=0;
		}
	} else {
		memcpy(&FirstEpoch,&epoch->StartSummaryEpoch,sizeof(TTime));
		//Get GPSWeek of start epoch
		ttime2gpswsnoroll(&epoch->StartSummaryEpoch, &GPSWeek, &SoW);
		//Compute calendar date of start epoch
		t2tmnolocal(&epoch->StartSummaryEpoch, &tm, &SecondsComp);
		//Get DoY of start epoch
		t2doy(&epoch->StartSummaryEpoch,&year,&DoY);
		//Print start epoch
		fprintf(options->outFileStream,"INFO First epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryEpoch),GPSWeek,SoW);
		//Get GPSWeek of last epoch
		ttime2gpswsnoroll(&LastEpoch, &GPSWeek, &SoW);
		//Compute calendar date of last epoch
		t2tmnolocal(&LastEpoch,&tm, &SecondsComp);
		//Get DoY of last epoch
		t2doy(&LastEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Last  epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&LastEpoch),GPSWeek,SoW);
	}

	//Print total epochs processed
	fprintf(options->outFileStream,"INFO Total epochs processed: %d\n",epoch->TotalEpochs);

	//Print total epochs with PA solution
	fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution: %d ( %.*f%% )\n",NPAletter,SBASdatabox->TotalPAEpochs,PAPercentage>=99.9995?0:3,PAPercentage);

	//Print total epochs with PA solution and under alarm limits
	fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution under alarm limits: %d ( %.*f%% )\n",NPAletter,SBASdatabox->TotalPAEpochsAvail,PALimitsPercentage>=99.9995?0:3,PALimitsPercentage);

	if (options->UserForcedNPA==0 && options->switchmode==1) {
		//Print NPA epochs if user didn't force the use of NPA and mode switching is enabled
		fprintf(options->outFileStream,"INFO Total epochs processed with NPA solution: %d ( %.*f%% )\n",SBASdatabox->TotalNPAEpochs,NPAPercentage>=99.9995?0:3,NPAPercentage);
	}

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (options->UseReferenceFile==1) {
	   	if (options->receiverPositionSource != rpSETREF) {
			fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution and position from reference file: %d ( %.*f%% )\n",NPAletter,epoch->TotalEpochsRef,RefPercentage>=99.9995?0:3,RefPercentage);
			fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.*f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage>=99.9995?0:3,NoRefSumEpochPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to no position from reference file for modelling: %d ( %.*f%% )\n",epoch->NumNoRefSolSkipped,NoRefSolEpochPercentage>=99.9995?0:3,NoRefSolEpochPercentage);
		}
	}

	//Print epochs skipped due to lack of satellites
	fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.*f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage>=99.9995?0:3,FewSatEpochsPercentage);

	//Print epochs skipped due to singular geometry matrix
	fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.*f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage>=99.9995?0:3,SingularEpochsPercentage);

    //Print epochs skipped due to reference constellation not available
    fprintf(options->outFileStream,"INFO Total epochs skipped due to reference constellation not available: %d ( %.*f%% )\n",epoch->NumNoRefGNSSSkipped,NoRefConstPercentage>=99.9995?0:3,NoRefConstPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage>=99.9995?0:3,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage>=99.9995?0:3,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage>=99.9995?0:3,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	percentage=NoRefSolEpochPercentage+FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage;
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.*f%% )\n",TotalEpochsSkipped,percentage>=99.9995?0:3,percentage);

	if(DataInterval>epoch->receiver.interval) {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period and not decimated): %3d\n",NumEpochsMissingSummary);

		//Print total number of epochs missing in summary but were decimated
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period and decimated):     %3d\n",NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period):                   %3d\n",NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (all the file):                            %3d\n",NumEpochsMissingFile);
	} else {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period): %3d\n",NumEpochsMissingSummary);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (all the file):          %3d\n",NumEpochsMissingFile);
	}

	//Print number of data gaps in summary
	fprintf(options->outFileStream,"INFO Number of data gaps in observation file (during summary period): %3d\n",epoch->NumDataGapsSum);

	//Print number of data gaps in all file
	fprintf(options->outFileStream,"INFO Number of data gaps in observation file (all the file):          %3d\n",epoch->NumDataGapsTotal);

	if (epoch->MaxDataGapSizeSum>0) {
		//Print maximum data gap size in summary
		ttime2gpswsnoroll(&epoch->DataGapSum, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapSum,&tm, &SecondsComp);
		t2doy(&epoch->DataGapSum,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
		t2doy(&epoch->DataGapTotal,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapTotal),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d\n",epoch->MaxDataGapSizeTotal);
	}

	//Print Time To First Fix
	if (numEpochsFirstFix>0) {
		ttime2gpswsnoroll(&epoch->FirstEpochSolution, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->FirstEpochSolution,&tm, &SecondsComp);
		t2doy(&epoch->FirstEpochSolution,&year,&DoY);
		fprintf(options->outFileStream,"INFO Time To First Fix: %.6g seconds (%d epoch%s) at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",TimeToFirstFix,numEpochsFirstFix,numEpochsFirstFix==1?"":"s",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochSolution),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Time To First Fix: no epochs with solution\n");
	}

	if (SBASdatabox->TotalPAEpochs!=0) {
		//Print number of epochs with each constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations used:");
		for(j=0;j<epoch->numconstCombUsed;j++) {
			percentage=100.*(double)(epoch->numEpochsconstCombination[j])/((double)SBASdatabox->TotalPAEpochs);
			fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constCombinationText[j],lenMaxNumber,epoch->numEpochsconstCombination[j],percentage>=99.9995?0:3,percentage);
			if ((j%4)==0 && j>0 && j!=(epoch->numconstCombUsed-1)) {
				fprintf(options->outFileStream,"\nINFO Number of epochs with constellations used:");
			}
		}
		fprintf(options->outFileStream,"\n");

		//Print number of epochs with each not used constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations not used:");
		if (epoch->numconstCombNotUsed==0) {
			fprintf(options->outFileStream," 0 ( 0%% )\n");
		} else {
			for(j=0;j<epoch->numconstCombNotUsed;j++) {
				percentage=100.*(double)(epoch->numEpochsconstNotUsedCombination[j])/((double)SBASdatabox->TotalPAEpochs);
				fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constNotUsedCombinationText[j],lenMaxNumber,epoch->numEpochsconstNotUsedCombination[j],percentage>=99.9995?0:3,percentage);
				if ((j%4)==0 && j>0 && j!=(epoch->numconstCombNotUsed-1)) {
					fprintf(options->outFileStream,"\nINFO Number of epochs with constellations not used:");
				}
			}
			fprintf(options->outFileStream,"\n");
		}

		//Print number of epochs where each constellation was used as reference clock
		fprintf(options->outFileStream,"INFO Constellations used as reference clock:");
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->numEpochsRefClock[i]==0) continue;
			percentage=100.*(double)epoch->numEpochsRefClock[i]/((double)(SBASdatabox->TotalPAEpochs));
			fprintf(options->outFileStream," %s %d ( %.*f%% )",gnsstype2gnssstr(i),epoch->numEpochsRefClock[i],percentage>=99.9995?0:3,percentage);
		}
		fprintf(options->outFileStream,"\n");

		//Print percentiles for satellites used and unused
		fprintf(options->outFileStream,"INFO Satellites used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamples,epoch->MeanNumSatUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamplesGNSS[i],epoch->MeanNumSatUsedGNSS[i]);
		}
		fprintf(options->outFileStream,"INFO Satellites not used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatNotUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamples,epoch->MeanNumSatNotUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites not used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatNotUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamplesGNSS[i],epoch->MeanNumSatNotUsedGNSS[i]);
		}
		//Print satellites used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites used
			if (epoch->MinNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MinSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MinSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites used (%s)                %2d %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites used
			if (epoch->MaxNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites not used
			if (epoch->MinNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		if (epoch->MinNumSatNotUsed==9999) {
			//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
			epoch->MinNumSatNotUsed=epoch->MaxNumSatNotUsed;
			memcpy(&epoch->MinSatNotUsedEpoch,&epoch->MaxSatNotUsedEpoch,sizeof(TTime));
		}
		ttime2gpswsnoroll(&epoch->MinSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			if (epoch->MinNumSatNotUsedGNSS[i]==9999) {
				//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
				epoch->MinNumSatNotUsedGNSS[i]=epoch->MaxNumSatNotUsedGNSS[i];
				memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->MaxSatNotUsedEpochGNSS[i],sizeof(TTime));
			}
			ttime2gpswsnoroll(&epoch->MinSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites not used
			if (epoch->MaxNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}

		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		
		//Create strings with number of satellites per constellation of min and max DOP and save the maximum string length
		//Min PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinPDOPGNSS[i]==0) continue;
			len+=sprintf(&minPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinPDOPGNSS[i]);
		}
		minPDOPsatStr[0]='(';
		minPDOPsatStr[len]=')';
		len++;
		minPDOPsatStr[len]='\0';
		maxDOPlen=len;
		//Max PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxPDOPGNSS[i]==0) continue;
			len+=sprintf(&maxPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxPDOPGNSS[i]);
		}
		maxPDOPsatStr[0]='(';
		maxPDOPsatStr[len]=')';
		len++;
		maxPDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinGDOPGNSS[i]==0) continue;
			len+=sprintf(&minGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinGDOPGNSS[i]);
		}
		minGDOPsatStr[0]='(';
		minGDOPsatStr[len]=')';
		len++;
		minGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxGDOPGNSS[i]==0) continue;
			len+=sprintf(&maxGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxGDOPGNSS[i]);
		}
		maxGDOPsatStr[0]='(';
		maxGDOPsatStr[len]=')';
		len++;
		maxGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinTDOPGNSS[i]==0) continue;
			len+=sprintf(&minTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinTDOPGNSS[i]);
		}
		minTDOPsatStr[0]='(';
		minTDOPsatStr[len]=')';
		len++;
		minTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxTDOPGNSS[i]==0) continue;
			len+=sprintf(&maxTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxTDOPGNSS[i]);
		}
		maxTDOPsatStr[0]='(';
		maxTDOPsatStr[len]=')';
		len++;
		maxTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinHDOPGNSS[i]==0) continue;
			len+=sprintf(&minHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinHDOPGNSS[i]);
		}
		minHDOPsatStr[0]='(';
		minHDOPsatStr[len]=')';
		len++;
		minHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxHDOPGNSS[i]==0) continue;
			len+=sprintf(&maxHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHDOPGNSS[i]);
		}
		maxHDOPsatStr[0]='(';
		maxHDOPsatStr[len]=')';
		len++;
		maxHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinVDOPGNSS[i]==0) continue;
			len+=sprintf(&minVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinVDOPGNSS[i]);
		}
		minVDOPsatStr[0]='(';
		minVDOPsatStr[len]=')';
		len++;
		minVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxVDOPGNSS[i]==0) continue;
			len+=sprintf(&maxVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVDOPGNSS[i]);
		}
		maxVDOPsatStr[0]='(';
		maxVDOPsatStr[len]=')';
		len++;
		maxVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;

		//Print PDOP min value
		ttime2gpswsnoroll(&epoch->MinPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinPDOP,epoch->NumSatMinPDOP,maxDOPlen,minPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinPDOPEpoch),GPSWeek,SoW);
		//Print GDOP min value
		ttime2gpswsnoroll(&epoch->MinGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinGDOP,epoch->NumSatMinGDOP,maxDOPlen,minGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinGDOPEpoch),GPSWeek,SoW);
		//Print TDOP min value
		ttime2gpswsnoroll(&epoch->MinTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinTDOP,epoch->NumSatMinTDOP,maxDOPlen,minTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print HDOP min value
		ttime2gpswsnoroll(&epoch->MinHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinHDOP,epoch->NumSatMinHDOP,maxDOPlen,minHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinHDOPEpoch),GPSWeek,SoW);
		//Print VDOP min value
		ttime2gpswsnoroll(&epoch->MinVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinVDOP,epoch->NumSatMinVDOP,maxDOPlen,minVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->MaxPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,epoch->NumSatMaxPDOP,maxDOPlen,maxPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxPDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->MaxGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,epoch->NumSatMaxGDOP,maxDOPlen,maxGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxGDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->MaxTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,epoch->NumSatMaxTDOP,maxDOPlen,maxTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->MaxHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,epoch->NumSatMaxHDOP,maxDOPlen,maxHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->MaxVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,epoch->NumSatMaxVDOP,maxDOPlen,maxVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);
	}

	//Print Continuity Risk
	if (RiskVal==0. || RiskVal==1.) {
		fprintf(options->outFileStream,"INFO Continuity Risk Airborne (%d epochs sliding window): %d (NumEpochsRisk:      %4d TotalEpochsAvailable: %5d)\n",options->ContRiskWindowSize,(int)RiskVal,SBASdatabox->NumEpochsRisk,SBASdatabox->TotalPAEpochsAvail);
	} else {
		fprintf(options->outFileStream,"INFO Continuity Risk Airborne (%d epochs sliding window): %.4E (NumEpochsRisk:      %4d TotalEpochsAvailable: %5d)\n",options->ContRiskWindowSize,RiskVal,SBASdatabox->NumEpochsRisk,SBASdatabox->TotalPAEpochsAvail);
	}

	//Print Continuity Risk (maritime mode)
	if (RiskMarVal==0. || RiskMarVal==1.) {
		fprintf(options->outFileStream,"INFO Continuity Risk Maritime (%d epochs fixed window):   %d (NumDiscontinuities: %4d TotalEpochsSummary:   %5d)\n",options->ContRiskWindowSizeMar,(int)RiskMarVal,SBASdatabox->NumEpochsRiskMar,NumEpochsSummaryPeriod);
	} else {
		fprintf(options->outFileStream,"INFO Continuity Risk Maritime (%d epochs fixed window):   %.4E (NumDiscontinuities: %4d TotalEpochsSummary:   %5d)\n",options->ContRiskWindowSizeMar,RiskMarVal,SBASdatabox->NumEpochsRiskMar,NumEpochsSummaryPeriod);
	}

    if(options->recPosProvided==1) {
		if (epoch->TotalEpochsRef==0) {
				fprintf(options->outFileStream,"INFO No epochs with solution %sfor computing MIs, PE, PL%s percentiles%s\n",options->UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?",":" and",options->stanfordesa==1?" and Stanford-ESA statistics":"");
		} else {
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->StartSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->StartSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->StartSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO First epoch of summary for computing MIs, PE, PL%s percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?",":" and",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryPercentileEpoch),GPSWeek,SoW);
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->LastSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->LastSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->LastSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Last  epoch of summary for computing MIs, PE, PL%s percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?",":" and",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->LastSummaryPercentileEpoch),GPSWeek,SoW);
		}
	}

	if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
		//Print number of MIs
		fprintf(options->outFileStream,"INFO Total epochs with MIs: %d ( %.*f%% )\n",SBASdatabox->NumMI,MIEpochsPercentage>=99.9995?0:3,MIEpochsPercentage);

		//Print number of Horizontal MIs
		fprintf(options->outFileStream,"INFO Total epochs with Horizontal MIs: %d ( %.*f%% )\n",SBASdatabox->NumHMI,HMIEpochsPercentage>=99.9995?0:3,HMIEpochsPercentage);

		//Print number of Vertical MIs
		fprintf(options->outFileStream,"INFO Total epochs with Vertical   MIs: %d ( %.*f%% )\n",SBASdatabox->NumVMI,VMIEpochsPercentage>=99.9995?0:3,VMIEpochsPercentage);
	}

	//Print epochs skipped due to bad GDOP
	if(options->stanfordesa==1) {
		//Print total geometries processed
		fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %llu\n",StdESA->numsamplesProcessed);

		//Print total geometries with solution
		if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
			//If percentage is 100%, print 100% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.*f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage==100.?0:3,SamplesSolPercentage);
		} else if (SamplesSolPercentage>=99.999) {
			//This is to avoid printing 1.00E+02% when rounding 99.999%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( 99.999%% )\n",StdESA->numsamplesComputed);
		} else {
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
		}

		//Print epochs skipped due to singular geometry matrix
		if(SamplesSkippedPercentage==0.) {
			//If percentage is 0, print 0.000% instead of 0.000E+00%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
		}

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			//Print number of MIs for Stanford-ESA
			if(SamplesMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with MIs: %llu ( %.3f%% )\n",StdESA->numsamplesMI,SamplesMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with MIs: %llu ( %.3E%% )\n",StdESA->numsamplesMI,SamplesMIPercentage);
			}

			//Print number of Horizontal MIs for Stanford-ESA
			if(SamplesHMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Horizontal MIs: %llu ( %.3f%% )\n",StdESA->numsamplesHMI,SamplesHMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Horizontal MIs: %llu ( %.3E%% )\n",StdESA->numsamplesHMI,SamplesHMIPercentage);
			}

			//Print number of Vertical MIs for Stanford-ESA
			if(SamplesVMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Vertical   MIs: %llu ( %.3f%% )\n",StdESA->numsamplesVMI,SamplesVMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Vertical   MIs: %llu ( %.3E%% )\n",StdESA->numsamplesVMI,SamplesVMIPercentage);
			}
		

			// Print value and with worst horizontal integrity ratio in Stanford-ESA
			fprintf(options->outFileStream,"INFO Stanford-ESA Worst Horizontal Integrity Ratio: %.4f\n",StdESA->HWIR);

			// Print value with worst vertical integrity ratio in Stanford-ESA
			fprintf(options->outFileStream,"INFO Stanford-ESA Worst Vertical   Integrity Ratio: %.4f\n",StdESA->VWIR);
		}
	}

	if(SBASdatabox->TotalPAEpochs!=0) {
		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			//Print Horizontal error Percentile
			fprintf(options->outFileStream,"INFO Horizontal %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HPEPercentileSamples);

			//Print Vertical error Percentile
			fprintf(options->outFileStream,"INFO Vertical   %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VPEPercentileSamples);

			//Print North error Percentile
			fprintf(options->outFileStream,"INFO North      %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->NPEPercentileSamples);

			//Print East error Percentile
			fprintf(options->outFileStream,"INFO East       %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->EPEPercentileSamples);

			//Print 3D error Percentile
			fprintf(options->outFileStream,"INFO 3D         %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PE3DPercentileSamples);
		}
		//Print Horizontal protection level Percentile
		fprintf(options->outFileStream,"INFO Horizontal %*.*f Protection  Level Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->HPLPercentileSamples);

		//Print Vertical protection level Percentile
		fprintf(options->outFileStream,"INFO Vertical   %*.*f Protection  Level Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->VPLPercentileSamples);

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			//Create strings with number of satellites per constellation of error and PL metrics and save the maximum string length
			//Max North Error satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatMaxNErrorGNSS[i]==0) continue;
				len+=sprintf(&MaxNErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxNErrorGNSS[i]);
			}
			MaxNErrorStr[0]='(';
			MaxNErrorStr[len]=')';
			len++;
			MaxNErrorStr[len]='\0';
			maxErrorlen=len;
			//Max East Error satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatMaxEErrorGNSS[i]==0) continue;
				len+=sprintf(&MaxEErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxEErrorGNSS[i]);
			}
			MaxEErrorStr[0]='(';
			MaxEErrorStr[len]=')';
			len++;
			MaxEErrorStr[len]='\0';
			if (len>maxErrorlen) maxErrorlen=len;
			//Max Horizontal Error satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatMaxHErrorGNSS[i]==0) continue;
				len+=sprintf(&MaxHErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHErrorGNSS[i]);
			}
			MaxHErrorStr[0]='(';
			MaxHErrorStr[len]=')';
			len++;
			MaxHErrorStr[len]='\0';
			if (len>maxErrorlen) maxErrorlen=len;
			//Max Vertical Error satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatMaxVErrorGNSS[i]==0) continue;
				len+=sprintf(&MaxVErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVErrorGNSS[i]);
			}
			MaxVErrorStr[0]='(';
			MaxVErrorStr[len]=')';
			len++;
			MaxVErrorStr[len]='\0';
			if (len>maxErrorlen) maxErrorlen=len;
			//Max 3D Error satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatMax3DErrorGNSS[i]==0) continue;
				len+=sprintf(&Max3DErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMax3DErrorGNSS[i]);
			}
			Max3DErrorStr[0]='(';
			Max3DErrorStr[len]=')';
			len++;
			Max3DErrorStr[len]='\0';
			if (len>maxErrorlen) maxErrorlen=len;
		}

		//Min Horizontal Protection Level satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinHPLGNSS[i]==0) continue;
			len+=sprintf(&MinHPLStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinHPLGNSS[i]);
		}
		MinHPLStr[0]='(';
		MinHPLStr[len]=')';
		len++;
		MinHPLStr[len]='\0';
		if (len>maxErrorlen) maxErrorlen=len;
		//Max Horizontal Protection Level satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxHPLGNSS[i]==0) continue;
			len+=sprintf(&MaxHPLStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHPLGNSS[i]);
		}
		MaxHPLStr[0]='(';
		MaxHPLStr[len]=')';
		len++;
		MaxHPLStr[len]='\0';
		if (len>maxErrorlen) maxErrorlen=len;
		//Min Vertical Protection Level satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinVPLGNSS[i]==0) continue;
			len+=sprintf(&MinVPLStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinVPLGNSS[i]);
		}
		MinVPLStr[0]='(';
		MinVPLStr[len]=')';
		len++;
		MinVPLStr[len]='\0';
		if (len>maxErrorlen) maxErrorlen=len;
		//Max Vertical Protection Level satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxVPLGNSS[i]==0) continue;
			len+=sprintf(&MaxVPLStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVPLGNSS[i]);
		}
		MaxVPLStr[0]='(';
		MaxVPLStr[len]=')';
		len++;
		MaxVPLStr[len]='\0';
		if (len>maxErrorlen) maxErrorlen=len;

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {

			// Print value and epoch with maximum horizontal error
			ttime2gpswsnoroll(&epoch->MaxHerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxHerrorEpoch,&tm, &SecondsComp);
			t2doy(&epoch->MaxHerrorEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,epoch->NumSatMaxHError,maxErrorlen,MaxHErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHerrorEpoch),GPSWeek,SoW);

			// Print value and epoch with maximum vertical error
			ttime2gpswsnoroll(&epoch->MaxVerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxVerrorEpoch,&tm, &SecondsComp);
			t2doy(&epoch->MaxVerrorEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,epoch->NumSatMaxVError,maxErrorlen,MaxVErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVerrorEpoch),GPSWeek,SoW);

			// Print value and epoch with maximum north error
			ttime2gpswsnoroll(&epoch->MaxNerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxNerrorEpoch,&tm, &SecondsComp);
			t2doy(&epoch->MaxNerrorEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum North      Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNError,epoch->NumSatMaxNError,maxErrorlen,MaxNErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxNerrorEpoch),GPSWeek,SoW);

			// Print value and epoch with maximum east error
			ttime2gpswsnoroll(&epoch->MaxEerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxEerrorEpoch,&tm, &SecondsComp);
			t2doy(&epoch->MaxEerrorEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum East       Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxEError,epoch->NumSatMaxEError,maxErrorlen,MaxEErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxEerrorEpoch),GPSWeek,SoW);

			// Print value and epoch with maximum 3D error
			ttime2gpswsnoroll(&epoch->Max3DerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->Max3DerrorEpoch,&tm, &SecondsComp);
			t2doy(&epoch->Max3DerrorEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum 3D         Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->Max3DError,epoch->NumSatMax3DError,maxErrorlen,Max3DErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->Max3DerrorEpoch),GPSWeek,SoW);
		}

		// Print value and epoch with minimum horizontal protection level
		ttime2gpswsnoroll(&SBASdatabox->MinHPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MinHPLEpoch,&tm, &SecondsComp);
		t2doy(&SBASdatabox->MinHPLEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum Horizontal Protection  Level: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MinHPL,epoch->NumSatMinHPL,maxErrorlen,MinHPLStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MinHPLEpoch),GPSWeek,SoW);

		// Print value and epoch with minimum vertical protection level
		ttime2gpswsnoroll(&SBASdatabox->MinVPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MinVPLEpoch,&tm, &SecondsComp);
		t2doy(&SBASdatabox->MinVPLEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum Vertical   Protection  Level: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MinVPL,epoch->NumSatMinVPL,maxErrorlen,MinVPLStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MinVPLEpoch),GPSWeek,SoW);

		// Print value and epoch with maximum horizontal protection level
		ttime2gpswsnoroll(&SBASdatabox->MaxHPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MaxHPLEpoch,&tm, &SecondsComp);
		t2doy(&SBASdatabox->MaxHPLEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum Horizontal Protection  Level: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MaxHPL,epoch->NumSatMaxHPL,maxErrorlen,MaxHPLStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MaxHPLEpoch),GPSWeek,SoW);

		// Print value and epoch with maximum vertical error
		ttime2gpswsnoroll(&SBASdatabox->MaxVPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MaxVPLEpoch,&tm, &SecondsComp);
		t2doy(&SBASdatabox->MaxVPLEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum Vertical   Protection  Level: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MaxVPL,epoch->NumSatMaxVPL,maxErrorlen,MaxVPLStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MaxVPLEpoch),GPSWeek,SoW);

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			//Print Horizontal integrity Percentile
			fprintf(options->outFileStream,"INFO Horizontal %*.*f Integrity Ratio Percentile: %6.4f\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->HIRPercentileSamples);

			//Print Vertical integrity Percentile
			fprintf(options->outFileStream,"INFO Vertical   %*.*f Integrity Ratio Percentile: %6.4f\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->VIRPercentileSamples);

			//Create strings with number of satellites per constellation of WIR and BIR metrics and save the maximum string length
			//Best Horizontal Integrity Ratio satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatHBIRGNSS[i]==0) continue;
				len+=sprintf(&HBIRStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatHBIRGNSS[i]);
			}
			HBIRStr[0]='(';
			HBIRStr[len]=')';
			len++;
			HBIRStr[len]='\0';
			maxIRlen=len;
			//Best Vertical Integrity Ratio satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatVBIRGNSS[i]==0) continue;
				len+=sprintf(&VBIRStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatVBIRGNSS[i]);
			}
			VBIRStr[0]='(';
			VBIRStr[len]=')';
			len++;
			VBIRStr[len]='\0';
			if (len>maxIRlen) maxIRlen=len;
			//Worst Horizontal Integrity Ratio satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatHWIRGNSS[i]==0) continue;
				len+=sprintf(&HWIRStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatHWIRGNSS[i]);
			}
			HWIRStr[0]='(';
			HWIRStr[len]=')';
			len++;
			HWIRStr[len]='\0';
			if (len>maxIRlen) maxIRlen=len;
			//Worst Vertical Integrity Ratio satellite string
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->NumSatVWIRGNSS[i]==0) continue;
				len+=sprintf(&VWIRStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatVWIRGNSS[i]);
			}
			VWIRStr[0]='(';
			VWIRStr[len]=')';
			len++;
			VWIRStr[len]='\0';
			if (len>maxIRlen) maxIRlen=len;

			// Print value and epoch with best horizontal integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->HBIREpoch, &GPSWeek, &SoW);
			t2tmnolocal(&SBASdatabox->HBIREpoch,&tm, &SecondsComp);
			t2doy(&SBASdatabox->HBIREpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Best  Horizontal Integrity Ratio: %11.4E with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->HBIR,epoch->NumSatHBIR,maxIRlen,HBIRStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->HBIREpoch),GPSWeek,SoW);

			// Print value and epoch with best vertical integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->VBIREpoch, &GPSWeek, &SoW);
			t2tmnolocal(&SBASdatabox->VBIREpoch,&tm, &SecondsComp);
			t2doy(&SBASdatabox->VBIREpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Best  Vertical   Integrity Ratio: %11.4E with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->VBIR,epoch->NumSatVBIR,maxIRlen,VBIRStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->VBIREpoch),GPSWeek,SoW);

			// Print value and epoch with worst horizontal integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->HWIREpoch, &GPSWeek, &SoW);
			t2tmnolocal(&SBASdatabox->HWIREpoch,&tm, &SecondsComp);
			t2doy(&SBASdatabox->HWIREpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Worst Horizontal Integrity Ratio: %11.4f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->HWIR,epoch->NumSatHWIR,maxIRlen,HWIRStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->HWIREpoch),GPSWeek,SoW);

			// Print value and epoch with worst vertical integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->VWIREpoch, &GPSWeek, &SoW);
			t2tmnolocal(&SBASdatabox->VWIREpoch,&tm, &SecondsComp);
			t2doy(&SBASdatabox->VWIREpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Worst Vertical   Integrity Ratio: %11.4f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->VWIR,epoch->NumSatVWIR,maxIRlen,VWIRStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->VWIREpoch),GPSWeek,SoW);
		}
	}

	//Print processing time 
	computeProcessingTime(StartTimeRealPCTime,&totalprocessingTime,0,options);
	sprintf(procTimestr,"%.3f",(double)(totalprocessingTime)/1.0E6);
	*ProcTimeLength=(int)strlen(procTimestr)+1; //The +1 is to leave an extra slot in case when the final processing time is computed, one more character is needed

	// Print MIs, percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	if (options->printV5format==0) {
		if (FirstEpoch.MJDN==-1) {
			GPSWeek=0;
			SoW=0;
			DoW=0;
			year=0;
			DoY=0.;
			tm.tm_mday=0;
			tm.tm_mon=-1;
			SecondsComp=0.;
		} else {
			ttime2gpswsnoroll(&FirstEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&FirstEpoch, &tm, &SecondsComp);
			t2doy(&FirstEpoch,&year,&DoY);
			DoW=(int)(SoW/86400.);
		} 
		
		
		//sprintf(messagestr,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f Day: %2d Month: %2d Year: %4d DoY: %3d GPSWeek: %4d DoW: %d Percentile: %*.*f HPE_Percentile: %6.2f VPE_Percentile: %6.2f NPE_Percentile: %6.2f EPE_Percentile: %6.2f 3DPE_Percentile: %6.2f MaxHPE: %6.2f MaxVPE: %6.2f MaxNPE: %6.2f MaxEPE: %6.2f Max3DPE: %6.2f Avail%%: %7.3f PDOP_Percentile: %6.2f Min_PDOP: %6.2f Max_PDOP: %6.2f GDOP_Percentile: %6.2f Min_GDOP: %6.2f Max_GDOP: %6.2f TDOP_Percentile: %6.2f Min_TDOP: %6.2f Max_TDOP: %6.2f HDOP_Percentile: %6.2f Min_HDOP: %6.2f Max_HDOP: %6.2f VDOP_Percentile: %6.2f Min_VDOP: %6.2f Max_VDOP: %6.2f Sat_used_All_Const_Percentile: %d Sat_not_used_All_Const_Percentile: %d Min_sat_used_All_Const: %d Min_sat_not_used_All_Const: %d Max_sat_used_All_Const: %d Max_sat_not_used_All_Const: %d Epochs_processed: %d Epochs_with_solution: %d Epochs_with_solution_reference_file: %d Epochs_omitted_no_data_reference_file: %d Epochs_skipped_no_data_reference_file: %d Epochs_no_satellites: %d Epochs_singular_matrix: %d Epochs_No_Reference_GNSS: %d Epochs_Over_HDOPorPDOP: %d Epochs_Over_HDOP: %d Epochs_Over_PDOP: %d Epochs_Over_GDOP: %d Total_Epochs_skipped: %d Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s Time_To_First_Fix: %.6g Epochs_First_Fix: %d Processing_time: %n%*.3f HIR_Percentile: %6.4f VIR_Percentile: %6.4f HWIR: %7.4f VWIR: %7.4f HBIR: %6.4E VBIR: %6.4E MIs: %3d Hor_MIs: %3d Ver_MIs: %3d HWIR_ESA: %7.4f VWIR_ESA: %7.4f MIs_ESA: %4llu Hor_MIs_ESA: %4llu Ver_MIs_ESA: %4llu HPL_Percentile: %6.2f VPL_Percentile: %6.2f MinHPL: %6.2f MaxHPL: %6.2f MinVPL: %6.2f MaxVPL: %6.2f Cont_Risk: %6.4E Cont_Risk_Mar: %6.4E\n",
		sprintf(messagestr,"INFO (2)_Station: %4s (4)_Lon: %12.8f (6)_Lat: %13.8f (8)_Height: %9.4f (10)_Day: %2d (12)_Month: %2d (14)_Year: %4d (16)_DoY: %3d (18)_GPSWeek: %4d (20)_DoW: %d (22)_Percentile: %*.*f (24)_HPE_Percentile: %6.2f (26)_VPE_Percentile: %6.2f (28)_NPE_Percentile: %6.2f (30)_EPE_Percentile: %6.2f (32)_3DPE_Percentile: %6.2f (34)_MaxHPE: %6.2f (36)_MaxVPE: %6.2f (38)_MaxNPE: %6.2f (40)_MaxEPE: %6.2f (42)_Max3DPE: %6.2f (44)_Avail%%: %7.3f (46)_PDOP_Percentile: %6.2f (48)_Min_PDOP: %6.2f (50)_Max_PDOP: %6.2f (52)_GDOP_Percentile: %6.2f (54)_Min_GDOP: %6.2f (56)_Max_GDOP: %6.2f (58)_TDOP_Percentile: %6.2f (60)_Min_TDOP: %6.2f (62)_Max_TDOP: %6.2f (64)_HDOP_Percentile: %6.2f (66)_Min_HDOP: %6.2f (68)_Max_HDOP: %6.2f (70)_VDOP_Percentile: %6.2f (72)_Min_VDOP: %6.2f (74)_Max_VDOP: %6.2f (76)_Sat_used_All_Const_Percentile: %d (78)_Sat_not_used_All_Const_Percentile: %d (80)_Min_sat_used_All_Const: %d (82)_Min_sat_not_used_All_Const: %d (84)_Max_sat_used_All_Const: %d (86)_Max_sat_not_used_All_Const: %d (88)_Epochs_processed: %d (90)_Epochs_with_solution: %d (92)_Epochs_with_solution_reference_file: %d (94)_Epochs_omitted_no_data_reference_file: %d (96)_Epochs_skipped_no_data_reference_file: %d (98)_Epochs_no_satellites: %d (100)_Epochs_singular_matrix: %d (102)_Epochs_No_Reference_GNSS: %d (104)_Epochs_Over_HDOPorPDOP: %d (106)_Epochs_Over_HDOP: %d (108)_Epochs_Over_PDOP: %d (110)_Epochs_Over_GDOP: %d (112)_Total_Epochs_skipped: %d (114)_Epochs_missing_Sum: %3d (116)_Epochs_missing_All_file: %3d (118)_Num_DataGaps_Sum: %3d (120)_Num_DataGaps_All_file: %3d (122)_MaxSize_DataGap_Sum: %3d (124)_MaxSize_DataGap_All_file: %3d (126)_Station_Network_Name: %s (128)_Time_To_First_Fix: %.6g (130)_Epochs_First_Fix: %d (132)_Processing_time: %n%*.3f (134)_HIR_Percentile: %6.4f (136)_VIR_Percentile: %6.4f (138)_HWIR: %7.4f (140)_VWIR: %7.4f (142)_HBIR: %6.4E (144)_VBIR: %6.4E (146)_MIs: %3d (148)_Hor_MIs: %3d (150)_Ver_MIs: %3d (152)_HWIR_ESA: %7.4f (154)_VWIR_ESA: %7.4f (156)_MIs_ESA: %4llu (158)_Hor_MIs_ESA: %4llu (160)_Ver_MIs_ESA: %4llu (162)_HPL_Percentile: %6.2f (164)_VPL_Percentile: %6.2f (166)_MinHPL: %6.2f (168)_MaxHPL: %6.2f (170)_MinVPL: %6.2f (172)_MaxVPL: %6.2f (174)_Cont_Risk: %6.4E (176)_Cont_Risk_Mar: %6.4E\n",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 tm.tm_mday,
			 tm.tm_mon+1,
			 year,
			 (int)DoY,
			 GPSWeek,
			 DoW,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 epoch->VPEPercentileSamples,
			 epoch->NPEPercentileSamples,
			 epoch->EPEPercentileSamples,
			 epoch->PE3DPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 epoch->MaxNError,
			 epoch->MaxEError,
			 epoch->Max3DError,
			 PALimitsPercentage,
			 epoch->PDOPPercentileSamples,
			 epoch->MinPDOP,
			 epoch->MaxPDOP,
			 epoch->GDOPPercentileSamples,
			 epoch->MinGDOP,
			 epoch->MaxGDOP,
			 epoch->TDOPPercentileSamples,
			 epoch->MinTDOP,
			 epoch->MaxTDOP,
			 epoch->HDOPPercentileSamples,
			 epoch->MinHDOP,
			 epoch->MaxHDOP,
			 epoch->VDOPPercentileSamples,
			 epoch->MinVDOP,
			 epoch->MaxVDOP,
			 epoch->NumSatUsed50PercentSamples,
			 epoch->NumSatNotUsed50PercentSamples,
			 epoch->MinNumSatUsed,
			 epoch->MinNumSatNotUsed,
			 epoch->MaxNumSatUsed,
			 epoch->MaxNumSatNotUsed,
			 epoch->TotalEpochs,
			 epoch->TotalEpochsSol,
			 epoch->TotalEpochsRef,
			 epoch->NumNoRefSumSkipped,
			 epoch->NumNoRefSolSkipped,
			 epoch->NumNoSatSkipped,
			 epoch->NumSingularMatrixSkipped,
			 epoch->NumNoRefGNSSSkipped,
			 epoch->NumHDOPorPDOPSkipped,
			 epoch->NumHDOPSkipped,
			 epoch->NumPDOPSkipped,
			 epoch->NumGDOPSkipped,
			 TotalEpochsSkipped,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 options->StationNetworkName,
			 TimeToFirstFix,
			 numEpochsFirstFix,
			 PosProcTime,
			 *ProcTimeLength,
			 (double)(totalprocessingTime)/1.0E6,
			 SBASdatabox->HIRPercentileSamples,
			 SBASdatabox->VIRPercentileSamples,
			 SBASdatabox->HWIR,
			 SBASdatabox->VWIR,
			 SBASdatabox->HBIR,
			 SBASdatabox->VBIR,
			 SBASdatabox->NumMI,
			 SBASdatabox->NumHMI,
			 SBASdatabox->NumVMI,
		 	 StdESA->HWIR,
			 StdESA->VWIR,
			 StdESA->numsamplesMI,
			 StdESA->numsamplesHMI,
			 StdESA->numsamplesVMI,
			 SBASdatabox->HPLPercentileSamples,
			 SBASdatabox->VPLPercentileSamples,
			 SBASdatabox->MinHPL,
			 SBASdatabox->MaxHPL,
			 SBASdatabox->MinVPL,
			 SBASdatabox->MaxVPL,
			 RiskVal,
			 RiskMarVal);
	} else {
		sprintf(messagestr,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HWIR: %7.4f VWIR: %7.4f MIs: %3d Hor_MIs: %3d Ver_MIs: %3d HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f HPL_Percentile: %*.*f %6.2f VPL_Percentile: %*.*f %6.2f MaxHPL: %6.2f MaxVPL: %6.2f Avail%%: %7.3f Cont_Risk: %6.4E HWIR_ESA: %7.4f VWIR_ESA: %7.4f MIs_ESA: %4llu Hor_MIs_ESA: %4llu Ver_MIs_ESA: %4llu Cont_Risk_Mark: %6.4E PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s\n",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 SBASdatabox->HWIR,
			 SBASdatabox->VWIR,
			 SBASdatabox->NumMI,
			 SBASdatabox->NumHMI,
			 SBASdatabox->NumVMI,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VPEPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 SBASdatabox->HPLPercentileSamples,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 SBASdatabox->VPLPercentileSamples,
			 SBASdatabox->MaxHPL,
			 SBASdatabox->MaxVPL,
			 PALimitsPercentage,
			 RiskVal,
		 	 StdESA->HWIR,
			 StdESA->VWIR,
			 StdESA->numsamplesMI,
			 StdESA->numsamplesHMI,
			 StdESA->numsamplesVMI,
			 RiskMarVal,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->PDOPPercentileSamples,
			 epoch->MaxPDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->GDOPPercentileSamples,
			 epoch->MaxGDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->TDOPPercentileSamples,
			 epoch->MaxTDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HDOPPercentileSamples,
			 epoch->MaxHDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VDOPPercentileSamples,
			 epoch->MaxVDOP,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 options->StationNetworkName);
	}
}

/*****************************************************************************
 * Name        : printDGNSSSummary
 * Description : print DGNSS summary at the end of the output file
 * Parameters  :
 * Name                                       |Da|Unit|Description
 * long long unsigned int StartTimeRealPCTime  I  N/A  Program start time in number of 
 *                                                      microseconds since 1 January 1970 
 * int *ProcTimeLength                         O  N/A  Number of characters used for printing
 *                                                      total processing time 
 * int *PosProcTime                            O  N/A  Position where processing time text
 *                                                      starts in last line of summary 
 * TEpoch  *epoch                              I  N/A  TEpoch structure
 * TEpoch  *epochDGNSS                         I  N/A  TEpoch structure from reference station
 * TStdESA *StdESA                             I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options                          I  N/A  TOptions structure
 *****************************************************************************/
void printDGNSSSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch *epoch, TEpoch *epochDGNSS, TStdESA *StdESA, TOptions *options) {

    int						i;
	int						aux,maxLengthConstComb=0,lenMaxNumber;
    int      				GPSWeek;
    int        			 	percentileSamples,percentile50Samples;
	int						year,DoW;
	int						NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation,TotalEpochsSkipped;
	int						NumEpochsDataGapSummary,numEpochsDecimatedAfterLastEpochSummary;
	int						PercentileDecimals=2,PercentileDigits=6;
	int						numEpochsFirstFix;
	int						maxErrorlen,maxDOPlen,len;
	unsigned int			j;
	double					DataInterval;
	double					percentage;
	double 					SoW,DoY;
	double					DGNSSPercentage,SPPPercentage,RefPercentage;
	double					FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double					NoRefSumEpochPercentage,NoRefConstPercentage;
    double   	 			SamplesSolPercentage,SamplesSkippedPercentage;
	double					SecondsComp;
	double					TimeToFirstFix;
    char    			    receiverid[5],auxstr[50];
	char					minPDOPsatStr[MAX_GNSS*8],minGDOPsatStr[MAX_GNSS*8],minTDOPsatStr[MAX_GNSS*8],minHDOPsatStr[MAX_GNSS*8],minVDOPsatStr[MAX_GNSS*8];
	char					maxPDOPsatStr[MAX_GNSS*8],maxGDOPsatStr[MAX_GNSS*8],maxTDOPsatStr[MAX_GNSS*8],maxHDOPsatStr[MAX_GNSS*8],maxVDOPsatStr[MAX_GNSS*8];
	char					MaxNErrorStr[MAX_GNSS*8],MaxEErrorStr[MAX_GNSS*8],MaxHErrorStr[MAX_GNSS*8],MaxVErrorStr[MAX_GNSS*8],Max3DErrorStr[MAX_GNSS*8];
	char					procTimestr[50];
	TTime					FirstEpoch,LastEpoch;
	struct tm 				tm;
	long long unsigned int	totalprocessingTime;

    //Convert receiver name to lower case
    for(i=0;i<4;i++) {
        receiverid[i]=tolower(epoch->receiver.name[i]);
    }
    receiverid[4]='\0';

	//Get data interval
	DataInterval=epoch->receiver.interval;
	if (options->decimate>epoch->receiver.interval && options->decimate!=0.) {
		//If decimation is higher than file data rate, then set the value to the epoch decimation
		DataInterval=options->decimate;
	} else {
		DataInterval=epoch->receiver.interval;
	}

	//Check number of decimals to be printed for percentile
	if (options->percentile==(double)((int)(options->percentile+0.005))) {
		PercentileDecimals=0;
		PercentileDigits=3;
	}

    // Check number of TotalEpochsDGNSS for printable values
    if(epoch->TotalEpochsRef==0) {
        epoch->MaxNError=0.;
        epoch->MaxEError=0.;
        epoch->MaxHError=0.;
        epoch->MaxVError=0.;
        epoch->Max3DError=0.;
        epoch->HPEPercentileSamples=0.;
        epoch->VPEPercentileSamples=0.;
    } else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsRef-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
		}
        if (options->recPosProvided==1) {
			//Compute NPE percentile of the samples
			qsort(epoch->NError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->NPEPercentileSamples=epoch->NError[percentileSamples];
			//Compute EPE percentile of the samples
			qsort(epoch->EError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->EPEPercentileSamples=epoch->EError[percentileSamples];
            //Compute HPE percentile of the samples
            qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
            //Compute VPE percentile of the samples
            qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
			//Compute 3D PE percentile of the samples
			qsort(epoch->Error3D,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->PE3DPercentileSamples=epoch->Error3D[percentileSamples];
        }
    }

	//Get last epoch processed
	if (options->EndEpoch.MJDN!=-1) {
		if (tdiff(&options->EndEpoch,&epoch->t)>0.) {
			//Last epoch processed is prior to the end epoch
			memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
		} else {
			memcpy(&LastEpoch,&options->EndEpoch,sizeof(TTime));
		}
	} else {
		memcpy(&LastEpoch,&epoch->LastSummaryEpoch,sizeof(TTime));
	}

	//Get number of epochs passed in the summary interval
	if (epoch->StartSummaryEpoch.MJDN!=-1) {
		NumEpochsSummaryPeriod=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/DataInterval)+1;
	} else {
		NumEpochsSummaryPeriod=0;
	}

	//Get number of epochs missing in file in summary interval
	if (NumEpochsSummaryPeriod!=0) {
		NumEpochsMissingSummary=NumEpochsSummaryPeriod-epoch->TotalEpochs;
	} else {
		NumEpochsMissingSummary=0;
	}

	//Get number of epochs missing in file in summary interval but decimated
	if (NumEpochsSummaryPeriod!=0) {
		if (isEpochDecimated(epoch,options)==1) {
			numEpochsDecimatedAfterLastEpochSummary=(int)(tdiff(&epoch->t,&LastEpoch)/epoch->receiver.interval);
		} else {
			numEpochsDecimatedAfterLastEpochSummary=0;
		}

		NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1+numEpochsDecimatedAfterLastEpochSummary-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstEpochFile)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
	} else {
		NumEpochsMissingFile=0;
	}

	//Get total number of epochs in data gaps in summary
	if(DataInterval>epoch->receiver.interval) {
		NumEpochsDataGapSummary=NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation;
	} else {
		NumEpochsDataGapSummary=NumEpochsMissingSummary;
	}

    //Compute availability percentages
    if(epoch->TotalEpochs==0) {
        DGNSSPercentage=0.;
        SPPPercentage=0.;
		RefPercentage=0.;
        FewSatEpochsPercentage=0.;
        SingularEpochsPercentage=0.;
		NoRefConstPercentage=0.;
        DOPEpochsPercentage=0.;
        HDOPEpochsPercentage=0.;
        PDOPEpochsPercentage=0.;
        GDOPEpochsPercentage=0.;
        HDOPorPDOPEpochsPercentage=0.;
		NoRefSumEpochPercentage=0.;
    } else {
        DGNSSPercentage=100.*(double)(epoch->TotalEpochsDGNSS)/((double)(epoch->TotalEpochs));
        SPPPercentage=100.*(double)(epoch->TotalEpochsSPP)/((double)(epoch->TotalEpochs));
		RefPercentage=100.*(double)(epoch->TotalEpochsRef)/((double)(epoch->TotalEpochs));
        FewSatEpochsPercentage=100.*(double)(epoch->NumNoSatSkipped)/((double)(epoch->TotalEpochs));
        SingularEpochsPercentage=100.*(double)(epoch->NumSingularMatrixSkipped)/((double)(epoch->TotalEpochs));
		NoRefConstPercentage=100.*(double)(epoch->NumNoRefGNSSSkipped)/((double)(epoch->TotalEpochs));
        DOPEpochsPercentage=100.*(double)(epoch->NumDOPSkipped)/((double)(epoch->TotalEpochs));;
        HDOPEpochsPercentage=100.*(double)(epoch->NumHDOPSkipped)/((double)(epoch->TotalEpochs));
        PDOPEpochsPercentage=100.*(double)(epoch->NumPDOPSkipped)/((double)(epoch->TotalEpochs));
        GDOPEpochsPercentage=100.*(double)(epoch->NumGDOPSkipped)/((double)(epoch->TotalEpochs));
        HDOPorPDOPEpochsPercentage=100.*(double)(epoch->NumHDOPorPDOPSkipped)/((double)(epoch->TotalEpochs));
		NoRefSumEpochPercentage=100.*(double)(epoch->NumNoRefSumSkipped)/((double)(epoch->TotalEpochs));
    }

	if (epoch->TotalEpochsDGNSS==0) {
		epoch->HDOPPercentileSamples=0.;
		epoch->PDOPPercentileSamples=0.;
		epoch->GDOPPercentileSamples=0.;
		epoch->TDOPPercentileSamples=0.;
		epoch->VDOPPercentileSamples=0.;
		epoch->NumSatUsedPercentSamples=0;
		epoch->NumSatNotUsedPercentSamples=0;
		epoch->NumSatUsed50PercentSamples=0;
		epoch->NumSatNotUsed50PercentSamples=0;
		epoch->MinNumSatUsed=0;
		epoch->MaxNumSatUsed=0;
		epoch->MinNumSatNotUsed=0;
		epoch->MaxNumSatNotUsed=0;
		numEpochsFirstFix=0;
		TimeToFirstFix=0.;
		lenMaxNumber=1;
	} else {
		//Compute time to first fix
		TimeToFirstFix=tdiff(&epoch->FirstEpochSolution,&epoch->firstEpochFile);
		numEpochsFirstFix=(int)(TimeToFirstFix/DataInterval)+1;

		//Compute mean values
		epoch->MeanNumSatUsed/=(double)epoch->TotalEpochsDGNSS;
		epoch->MeanNumSatNotUsed/=(double)epoch->TotalEpochsDGNSS;
		for(i=0;i<MAX_GNSS;i++) {
			epoch->MeanNumSatUsedGNSS[i]/=(double)epoch->TotalEpochsDGNSS;
			epoch->MeanNumSatNotUsedGNSS[i]/=(double)epoch->TotalEpochsDGNSS;
		}
		epoch->MeanNumConstUsed/=(double)epoch->TotalEpochsDGNSS;
		epoch->MeanNumConstNotUsed/=(double)epoch->TotalEpochsDGNSS;

		//Compute max lengths for constellations combinations
		if (epoch->numconstCombUsed>4) {
			for(j=0;j<epoch->numconstCombUsed;j++) {
				aux=(int)strlen(epoch->constCombinationText[j]);
				if (aux>maxLengthConstComb) {
					maxLengthConstComb=aux;
				}
			}
			sprintf(auxstr,"%d",epoch->TotalEpochsRef);
			lenMaxNumber=(int)strlen(auxstr);
		} else {
			maxLengthConstComb=1;
			lenMaxNumber=1;
		}

		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsDGNSS-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsDGNSS)*options->percentile/100.);
		}
		percentile50Samples=(int)((double)(epoch->TotalEpochsDGNSS)*50./100.);
		//Compute HDOP percentile of the samples
		qsort(epoch->HDOP,epoch->TotalEpochsDGNSS,sizeof(double),qsort_compare_double);
		epoch->HDOPPercentileSamples=epoch->HDOP[percentileSamples];
		//Compute PDOP percentile of the samples
		qsort(epoch->PDOP,epoch->TotalEpochsDGNSS,sizeof(double),qsort_compare_double);
		epoch->PDOPPercentileSamples=epoch->PDOP[percentileSamples];
		//Compute GDOP percentile of the samples
		qsort(epoch->GDOP,epoch->TotalEpochsDGNSS,sizeof(double),qsort_compare_double);
		epoch->GDOPPercentileSamples=epoch->GDOP[percentileSamples];
		//Compute TDOP percentile of the samples
		qsort(epoch->TDOP,epoch->TotalEpochsDGNSS,sizeof(double),qsort_compare_double);
		epoch->TDOPPercentileSamples=epoch->TDOP[percentileSamples];
		//Compute VDOP percentile of the samples
		qsort(epoch->VDOP,epoch->TotalEpochsDGNSS,sizeof(double),qsort_compare_double);
		epoch->VDOPPercentileSamples=epoch->VDOP[percentileSamples];
		//Compute used satellites used percentile
		qsort(epoch->NumSatUsed,epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int_reverse);//Use reverse order so the percentile refers to at least N satellites used
		epoch->NumSatUsedPercentSamples=epoch->NumSatUsed[percentileSamples];
		epoch->NumSatUsed50PercentSamples=epoch->NumSatUsed[percentile50Samples];
		//Compute not used satellites used percentile
		qsort(epoch->NumSatNotUsed,epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int);
		epoch->NumSatNotUsedPercentSamples=epoch->NumSatNotUsed[percentileSamples];
		epoch->NumSatNotUsed50PercentSamples=epoch->NumSatNotUsed[percentile50Samples];
		//Compute used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue; //Skip not used constellations to save computation time
			qsort(epoch->NumSatUsedGNSS[i],epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
			epoch->NumSatUsedPercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentileSamples];
			epoch->NumSatUsed50PercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentile50Samples];
		}
		//Compute not used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue; //Skip unselected constellations to save computation time
			qsort(epoch->NumSatNotUsedGNSS[i],epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int);
			epoch->NumSatNotUsedPercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentileSamples];
			epoch->NumSatNotUsed50PercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentile50Samples];
		}
		//Compute used constellations percentile 
		qsort(epoch->NumConstUsed,epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
		epoch->NumConstUsedPercentSamples=epoch->NumConstUsed[percentileSamples];
		epoch->NumConstUsed50PercentSamples=epoch->NumConstUsed[percentile50Samples];
		//Compute not used constellations percentile 
		qsort(epoch->NumConstNotUsed,epoch->TotalEpochsDGNSS,sizeof(int),qsort_compare_int);
		epoch->NumConstNotUsedPercentSamples=epoch->NumConstNotUsed[percentileSamples];
		epoch->NumConstNotUsed50PercentSamples=epoch->NumConstNotUsed[percentile50Samples];
	}

    //Compute availability percentages for Stanford-ESA if required
    if(options->stanfordesa==1) {
        if(StdESA->numsamplesProcessed==0) {
            SamplesSolPercentage=0.;
            SamplesSkippedPercentage=0.;
        } else {
            SamplesSolPercentage=100.*(double)(StdESA->numsamplesComputed)/((double)(StdESA->numsamplesProcessed));
            SamplesSkippedPercentage=100.*(double)(StdESA->numsamplesSingular)/((double)(StdESA->numsamplesProcessed));
        }
    }

	//Set values to 0 if receiver position is not set
	if(options->recPosProvided==0) {
		 epoch->HPEPercentileSamples=0.;
		 epoch->VPEPercentileSamples=0.;
		 epoch->MaxHError=0.;
		 epoch->MaxVError=0.;
	}

	//Compute total epochs skipped (any reason)
	TotalEpochsSkipped=epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumNoRefGNSSSkipped+epoch->NumDOPSkipped;

    // Print DGNSS Summary heading
    fprintf(options->outFileStream,"INFO --------------------- DGNSS Summary ---------------------\n");

    //Print DOP thresholds
	if(options->HDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO HDOP Threshold: %6.2f\n",options->maxHDOP);
	}
	if(options->PDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO PDOP Threshold: %6.2f\n",options->maxPDOP);
	}
    if(options->GDOPthreshold == 1) {
        fprintf(options->outFileStream,"INFO GDOP Threshold: %6.2f\n",options->maxGDOP);
    }

	//Print first epoch processed
	if (options->firstEpochSummary.MJDN!=-1 && epoch->StartSummaryEpoch.MJDN==-1) {
		memcpy(&FirstEpoch,&options->firstEpochSummary,sizeof(TTime));
		//Get GPSWeek
		ttime2gpswsnoroll(&options->firstEpochSummary, &GPSWeek, &SoW);
		//Compute calendar date
		t2tmnolocal(&options->firstEpochSummary, &tm, &SecondsComp);
		//Get DoY
		t2doy(&options->firstEpochSummary,&year,&DoY);
		//Start epoch of summary provided by user is ahead of all epochs in observation file
		fprintf(options->outFileStream,"INFO First epoch of summary provided by user: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&options->firstEpochSummary),GPSWeek,SoW);
		if (epoch->StartSummaryEpoch.MJDN==-1) {
			if (epoch->TotalEpochs>0 && epoch->TotalEpochsSol>0) {
				fprintf(options->outFileStream,"INFO First epoch of summary provided by user is ahead of all epochs in observation file. No epochs included in the summary\n");
			}
		}
	} else if (epoch->StartSummaryEpoch.MJDN==-1) {
		if (epoch->t.MJDN!=-1) {
			fprintf(options->outFileStream,"INFO No epochs after convergence time (from 0h onwards)\n");
			memcpy(&FirstEpoch,&epoch->firstEpochFile,sizeof(TTime));
		} else {
			fprintf(options->outFileStream,"INFO No data available in observation file\n");
			 FirstEpoch.MJDN=-1;
			 FirstEpoch.SoD=0;
		}
	} else {
		memcpy(&FirstEpoch,&epoch->StartSummaryEpoch,sizeof(TTime));
		//Get GPSWeek of start epoch
		ttime2gpswsnoroll(&epoch->StartSummaryEpoch, &GPSWeek, &SoW);
		//Compute calendar date of start epoch
		t2tmnolocal(&epoch->StartSummaryEpoch, &tm, &SecondsComp);
		//Get DoY of start epoch
		t2doy(&epoch->StartSummaryEpoch,&year,&DoY);
		//Print start epoch
		fprintf(options->outFileStream,"INFO First epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryEpoch),GPSWeek,SoW);
		//Get GPSWeek of last epoch
		ttime2gpswsnoroll(&LastEpoch, &GPSWeek, &SoW);
		//Compute calendar date of last epoch
		t2tmnolocal(&LastEpoch,&tm, &SecondsComp);
		//Get DoY of last epoch
		t2doy(&LastEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Last  epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&LastEpoch),GPSWeek,SoW);
	}

    //Print total epochs processed
    fprintf(options->outFileStream,"INFO Total epochs processed: %d\n",epoch->TotalEpochs);

    //Print total epochs with DGNSS solution
    fprintf(options->outFileStream,"INFO Total epochs processed with DGNSS solution: %d ( %.*f%% )\n",epoch->TotalEpochsDGNSS,DGNSSPercentage>=99.9995?0:3,DGNSSPercentage);

    //Print total epochs with SPP solution
    fprintf(options->outFileStream,"INFO Total epochs processed with SPP solution: %d ( %.*f%% )\n",epoch->TotalEpochsSPP,SPPPercentage>=99.9995?0:3,SPPPercentage);

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (options->UseReferenceFile==1) {
		fprintf(options->outFileStream,"INFO Total epochs processed with DGNSS solution and position from reference file: %d ( %.*f%% )\n",epoch->TotalEpochsRef,RefPercentage>=99.9995?0:3,RefPercentage);
		fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.*f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage>=99.9995?0:3,NoRefSumEpochPercentage);
	}

    //Print epochs skipped due to lack of satellites
    fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.*f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage>=99.9995?0:3,FewSatEpochsPercentage);

    //Print epochs skipped due to singular geometry matrix
    fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.*f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage>=99.9995?0:3,SingularEpochsPercentage);

    //Print epochs skipped due to reference constellation not available
    fprintf(options->outFileStream,"INFO Total epochs skipped due to reference constellation not available: %d ( %.*f%% )\n",epoch->NumNoRefGNSSSkipped,NoRefConstPercentage>=99.9995?0:3,NoRefConstPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage>=99.9995?0:3,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage>=99.9995?0:3,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage>=99.9995?0:3,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	percentage=FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage;
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.*f%% )\n",TotalEpochsSkipped,percentage>=99.9995?0:3,percentage);

	if(DataInterval>epoch->receiver.interval) {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in rover observation file (during summary period and not decimated): %3d\n",NumEpochsMissingSummary);

		//Print total number of epochs missing in summary but were decimated
		fprintf(options->outFileStream,"INFO Total epochs missing in rover observation file (during summary period and decimated):     %3d\n",NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in rover observation file (during summary period):                   %3d\n",NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing in rover observation file (all the file):                            %3d\n",NumEpochsMissingFile);
	} else {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing  in rover observation file (during summary period):  %3d\n",NumEpochsMissingSummary);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing  in rover observation file (all the file):           %3d\n",NumEpochsMissingFile);
	}
	
	//Print number of data gaps in summary
	fprintf(options->outFileStream,"INFO Number of data gaps in rover observation file (during summary period):    %3d\n",epoch->NumDataGapsSum);

	//Print number of data gaps in all file
	fprintf(options->outFileStream,"INFO Number of data gaps in rover observation file (all the file):             %3d\n",epoch->NumDataGapsTotal);

	if (epoch->MaxDataGapSizeSum>0) {
		//Print maximum data gap size in summary
		ttime2gpswsnoroll(&epoch->DataGapSum, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapSum,&tm, &SecondsComp);
		t2doy(&epoch->DataGapSum,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (during summary period):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
		t2doy(&epoch->DataGapTotal,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (all the file):           %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapTotal),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (all the file):           %3d\n",epoch->MaxDataGapSizeTotal);
	}

	if (options->RTCMmode == ProcessRINEX) {
		//At the current moment, data gaps an epochs missing are only counted in reference file if it is a RINEX file
		//Print total number of epochs missing in summary of reference station
		fprintf(options->outFileStream,"INFO Total epochs missing  in reference station %s file (during summary period): %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->NumEpochsMissingSum);

		//Print total number of epochs missing in file of reference station
		fprintf(options->outFileStream,"INFO Total epochs missing  in reference station %s file (all the file):          %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->NumEpochsMissingTotal);

		//Print number of data gaps in summary of reference station
		fprintf(options->outFileStream,"INFO Number of data gaps   in reference station %s file (during summary period): %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->NumDataGapsSum);

		//Print number of data gaps in all file of reference station
		fprintf(options->outFileStream,"INFO Number of data gaps   in reference station %s file (all the file):          %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->NumDataGapsTotal);
	

		if (epochDGNSS->MaxDataGapSizeSum>0) {
			//Print maximum data gap size in summary of reference station
			ttime2gpswsnoroll(&epochDGNSS->DataGapSum, &GPSWeek, &SoW);
			t2tmnolocal(&epochDGNSS->DataGapSum,&tm, &SecondsComp);
			t2doy(&epochDGNSS->DataGapSum,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (during summary period): %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epochDGNSS->DataGapSum),GPSWeek,SoW);
		} else {
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (during summary period): %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeSum);
		}

		if (epochDGNSS->MaxDataGapSizeTotal>0) {
			//Print maximum data gap size in file of reference station
			ttime2gpswsnoroll(&epochDGNSS->DataGapTotal, &GPSWeek, &SoW);
			t2tmnolocal(&epochDGNSS->DataGapTotal,&tm, &SecondsComp);
			t2doy(&epochDGNSS->DataGapTotal,&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (all the file):          %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epochDGNSS->DataGapTotal),GPSWeek,SoW);
		} else {
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (all the file):          %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeTotal);
		}
	}
		
	//Print Time To First Fix
	if (numEpochsFirstFix>0) {
		ttime2gpswsnoroll(&epoch->FirstEpochSolution, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->FirstEpochSolution,&tm, &SecondsComp);
		t2doy(&epoch->FirstEpochSolution,&year,&DoY);
		fprintf(options->outFileStream,"INFO Time To First Fix: %.6g seconds (%d epoch%s) at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",TimeToFirstFix,numEpochsFirstFix,numEpochsFirstFix==1?"":"s",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochSolution),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Time To First Fix: no epochs with solution\n");
	}

	if (epoch->TotalEpochsDGNSS!=0) {
		//Print number of epochs with each constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations used:");
		for(j=0;j<epoch->numconstCombUsed;j++) {
			percentage=100.*(double)(epoch->numEpochsconstCombination[j])/((double)epoch->TotalEpochsDGNSS);
			fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constCombinationText[j],lenMaxNumber,epoch->numEpochsconstCombination[j],percentage>=99.9995?0:3,percentage);
			if ((j%4)==0 && j>0 && j!=(epoch->numconstCombUsed-1)) {
				fprintf(options->outFileStream,"\nINFO Number of epochs with constellations used:");
			}
		}
		fprintf(options->outFileStream,"\n");

		//Print number of epochs with each not used constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations not used:");
		if (epoch->numconstCombNotUsed==0) {
			fprintf(options->outFileStream," 0 ( 0%% )\n");
		} else {
			for(j=0;j<epoch->numconstCombNotUsed;j++) {
				percentage=100.*(double)(epoch->numEpochsconstNotUsedCombination[j])/((double)epoch->TotalEpochsDGNSS);
				fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constNotUsedCombinationText[j],lenMaxNumber,epoch->numEpochsconstNotUsedCombination[j],percentage>=99.9995?0:3,percentage);
				if ((j%4)==0 && j>0 && j!=(epoch->numconstCombNotUsed-1)) {
					fprintf(options->outFileStream,"\nINFO Number of epochs with constellations not used:");
				}
			}
			fprintf(options->outFileStream,"\n");
		}

		//Print number of epochs where each constellation was used as reference clock
		fprintf(options->outFileStream,"INFO Constellations used as reference clock:");
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->numEpochsRefClock[i]==0) continue;
			percentage=100.*(double)epoch->numEpochsRefClock[i]/((double)(epoch->TotalEpochsDGNSS));
			fprintf(options->outFileStream," %s %d ( %.*f%% )",gnsstype2gnssstr(i),epoch->numEpochsRefClock[i],percentage>=99.9995?0:3,percentage);
		}
		fprintf(options->outFileStream,"\n");

		//Print percentiles for satellites used and unused
		fprintf(options->outFileStream,"INFO Satellites used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamples,epoch->MeanNumSatUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamplesGNSS[i],epoch->MeanNumSatUsedGNSS[i]);
		}
		fprintf(options->outFileStream,"INFO Satellites not used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatNotUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamples,epoch->MeanNumSatNotUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites not used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatNotUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamplesGNSS[i],epoch->MeanNumSatNotUsedGNSS[i]);
		}
		//Print satellites used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites used
			if (epoch->MinNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MinSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MinSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites used
			if (epoch->MaxNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites not used
			if (epoch->MinNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		if (epoch->MinNumSatNotUsed==9999) {
			//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
			epoch->MinNumSatNotUsed=epoch->MaxNumSatNotUsed;
			memcpy(&epoch->MinSatNotUsedEpoch,&epoch->MaxSatNotUsedEpoch,sizeof(TTime));
		}
		ttime2gpswsnoroll(&epoch->MinSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			if (epoch->MinNumSatNotUsedGNSS[i]==9999) {
				//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
				epoch->MinNumSatNotUsedGNSS[i]=epoch->MaxNumSatNotUsedGNSS[i];
				memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->MaxSatNotUsedEpochGNSS[i],sizeof(TTime));
			}
			ttime2gpswsnoroll(&epoch->MinSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites not used
			if (epoch->MaxNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}

		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		//Create strings with number of satellites per constellation of min and max DOP and save the maximum string length
		//Min PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinPDOPGNSS[i]==0) continue;
			len+=sprintf(&minPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinPDOPGNSS[i]);
		}
		minPDOPsatStr[0]='(';
		minPDOPsatStr[len]=')';
		len++;
		minPDOPsatStr[len]='\0';
		maxDOPlen=len;
		//Max PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxPDOPGNSS[i]==0) continue;
			len+=sprintf(&maxPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxPDOPGNSS[i]);
		}
		maxPDOPsatStr[0]='(';
		maxPDOPsatStr[len]=')';
		len++;
		maxPDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinGDOPGNSS[i]==0) continue;
			len+=sprintf(&minGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinGDOPGNSS[i]);
		}
		minGDOPsatStr[0]='(';
		minGDOPsatStr[len]=')';
		len++;
		minGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxGDOPGNSS[i]==0) continue;
			len+=sprintf(&maxGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxGDOPGNSS[i]);
		}
		maxGDOPsatStr[0]='(';
		maxGDOPsatStr[len]=')';
		len++;
		maxGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinTDOPGNSS[i]==0) continue;
			len+=sprintf(&minTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinTDOPGNSS[i]);
		}
		minTDOPsatStr[0]='(';
		minTDOPsatStr[len]=')';
		len++;
		minTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxTDOPGNSS[i]==0) continue;
			len+=sprintf(&maxTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxTDOPGNSS[i]);
		}
		maxTDOPsatStr[0]='(';
		maxTDOPsatStr[len]=')';
		len++;
		maxTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinHDOPGNSS[i]==0) continue;
			len+=sprintf(&minHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinHDOPGNSS[i]);
		}
		minHDOPsatStr[0]='(';
		minHDOPsatStr[len]=')';
		len++;
		minHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxHDOPGNSS[i]==0) continue;
			len+=sprintf(&maxHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHDOPGNSS[i]);
		}
		maxHDOPsatStr[0]='(';
		maxHDOPsatStr[len]=')';
		len++;
		maxHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinVDOPGNSS[i]==0) continue;
			len+=sprintf(&minVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinVDOPGNSS[i]);
		}
		minVDOPsatStr[0]='(';
		minVDOPsatStr[len]=')';
		len++;
		minVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxVDOPGNSS[i]==0) continue;
			len+=sprintf(&maxVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVDOPGNSS[i]);
		}
		maxVDOPsatStr[0]='(';
		maxVDOPsatStr[len]=')';
		len++;
		maxVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		
		//Print PDOP min value
		ttime2gpswsnoroll(&epoch->MinPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinPDOP,epoch->NumSatMinPDOP,maxDOPlen,minPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinPDOPEpoch),GPSWeek,SoW);
		//Print GDOP min value
		ttime2gpswsnoroll(&epoch->MinGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinGDOP,epoch->NumSatMinGDOP,maxDOPlen,minGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinGDOPEpoch),GPSWeek,SoW);
		//Print TDOP min value
		ttime2gpswsnoroll(&epoch->MinTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinTDOP,epoch->NumSatMinTDOP,maxDOPlen,minTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print HDOP min value
		ttime2gpswsnoroll(&epoch->MinHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinHDOP,epoch->NumSatMinHDOP,maxDOPlen,minHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinHDOPEpoch),GPSWeek,SoW);
		//Print VDOP min value
		ttime2gpswsnoroll(&epoch->MinVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinVDOP,epoch->NumSatMinVDOP,maxDOPlen,minVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->MaxPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,epoch->NumSatMaxPDOP,maxDOPlen,maxPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxPDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->MaxGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,epoch->NumSatMaxGDOP,maxDOPlen,maxGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxGDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->MaxTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,epoch->NumSatMaxTDOP,maxDOPlen,maxTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->MaxHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,epoch->NumSatMaxHDOP,maxDOPlen,maxHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->MaxVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,epoch->NumSatMaxVDOP,maxDOPlen,maxVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);

	}

    if(options->recPosProvided==1) {
		if (epoch->TotalEpochsRef==0) {
				fprintf(options->outFileStream,"INFO No epochs with DGNSS solution %sfor computing positioning error percentiles%s\n",options->UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?" and Stanford-ESA statistics":"");
		} else {
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->StartSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->StartSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->StartSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO First epoch of summary for computing positioning error percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryPercentileEpoch),GPSWeek,SoW);
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->LastSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->LastSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->LastSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Last  epoch of summary for computing positioning error percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->LastSummaryPercentileEpoch),GPSWeek,SoW);
		}
	}

    if(options->stanfordesa==1) {
        //Print total geometries processed
        fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %llu\n",StdESA->numsamplesProcessed);

        //Print total geometries with solution
        if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
            //If percentage is 100%, print 100.000% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.3f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        } else if (SamplesSolPercentage>=99.999) {
            //This is to avoid printing 1.00E+02% when rounding 99.999%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( 99.999%% )\n",StdESA->numsamplesComputed);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        }

        //Print epochs skipped due to singular geometry matrix
        if(SamplesSkippedPercentage==0.) {
            //If percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        }
    }

    if(epoch->TotalEpochsDGNSS!=0) {
        if(options->recPosProvided==1) {
			if (epoch->TotalEpochsRef!=0) {	
        	    //Print Horizontal error Percentile
        	    fprintf(options->outFileStream,"INFO Horizontal %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HPEPercentileSamples);

            	//Print Vertical error Percentile
	            fprintf(options->outFileStream,"INFO Vertical   %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VPEPercentileSamples);

				//Print North error Percentile
				fprintf(options->outFileStream,"INFO North      %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->NPEPercentileSamples);

				//Print East error Percentile
				fprintf(options->outFileStream,"INFO East       %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->EPEPercentileSamples);

        	    //Print 3D error Percentile
        	    fprintf(options->outFileStream,"INFO 3D         %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PE3DPercentileSamples);

				//Create strings with number of satellites per constellation of error metrics and save the maximum string length
				//Max North Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxNErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxNErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxNErrorGNSS[i]);
				}
				MaxNErrorStr[0]='(';
				MaxNErrorStr[len]=')';
				len++;
				MaxNErrorStr[len]='\0';
				maxErrorlen=len;
				//Max East Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxEErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxEErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxEErrorGNSS[i]);
				}
				MaxEErrorStr[0]='(';
				MaxEErrorStr[len]=')';
				len++;
				MaxEErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max Horizontal Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxHErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxHErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHErrorGNSS[i]);
				}
				MaxHErrorStr[0]='(';
				MaxHErrorStr[len]=')';
				len++;
				MaxHErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max Vertical Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxVErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxVErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVErrorGNSS[i]);
				}
				MaxVErrorStr[0]='(';
				MaxVErrorStr[len]=')';
				len++;
				MaxVErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max 3D Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMax3DErrorGNSS[i]==0) continue;
					len+=sprintf(&Max3DErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMax3DErrorGNSS[i]);
				}
				Max3DErrorStr[0]='(';
				Max3DErrorStr[len]=')';
				len++;
				Max3DErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;

    	        // Print value and epoch with maximum horizontal error
       		    ttime2gpswsnoroll(&epoch->MaxHerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxHerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxHerrorEpoch,&year,&DoY);
           		fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,epoch->NumSatMaxHError,maxErrorlen,MaxHErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHerrorEpoch),GPSWeek,SoW);

            	// Print value and epoch with maximum vertical error
            	ttime2gpswsnoroll(&epoch->MaxVerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxVerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxVerrorEpoch,&year,&DoY);
            	fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,epoch->NumSatMaxVError,maxErrorlen,MaxVErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVerrorEpoch),GPSWeek,SoW);

				// Print value and epoch with maximum north error
				ttime2gpswsnoroll(&epoch->MaxNerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxNerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxNerrorEpoch,&year,&DoY);
				fprintf(options->outFileStream,"INFO Maximum North      Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNError,epoch->NumSatMaxNError,maxErrorlen,MaxNErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxNerrorEpoch),GPSWeek,SoW);

				// Print value and epoch with maximum east error
				ttime2gpswsnoroll(&epoch->MaxEerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxEerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxEerrorEpoch,&year,&DoY);
				fprintf(options->outFileStream,"INFO Maximum East       Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxEError,epoch->NumSatMaxEError,maxErrorlen,MaxEErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxEerrorEpoch),GPSWeek,SoW);

				// Print value and epoch with maximum 3D error
				ttime2gpswsnoroll(&epoch->Max3DerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->Max3DerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->Max3DerrorEpoch,&year,&DoY);
				fprintf(options->outFileStream,"INFO Maximum 3D         Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->Max3DError,epoch->NumSatMax3DError,maxErrorlen,Max3DErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->Max3DerrorEpoch),GPSWeek,SoW);
			}
        }
    }

	//Print processing time 
	computeProcessingTime(StartTimeRealPCTime,&totalprocessingTime,0,options);
	sprintf(procTimestr,"%.3f",(double)(totalprocessingTime)/1.0E6);
	*ProcTimeLength=(int)strlen(procTimestr)+1; //The +1 is to leave an extra slot in case when the final processing time is computed, one more character is needed
	

	// Print percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	if (options->printV5format==0) {
		if (FirstEpoch.MJDN==-1) {
			GPSWeek=0;
			SoW=0;
			DoW=0;
			year=0;
			DoY=0.;
			tm.tm_mday=0;
			tm.tm_mon=-1;
			SecondsComp=0.;
		} else {
			ttime2gpswsnoroll(&FirstEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&FirstEpoch, &tm, &SecondsComp);
			t2doy(&FirstEpoch,&year,&DoY);
			DoW=(int)(SoW/86400.);
		} 
		//sprintf(messagestr,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f Day: %2d Month: %2d Year: %4d DoY: %3d GPSWeek: %4d DoW: %d Percentile: %*.*f HPE_Percentile: %6.2f VPE_Percentile: %6.2f NPE_Percentile: %6.2f EPE_Percentile: %6.2f 3DPE_Percentile: %6.2f MaxHPE: %6.2f MaxVPE: %6.2f MaxNPE: %6.2f MaxEPE: %6.2f Max3DPE: %6.2f Avail%%: %7.3f PDOP_Percentile: %6.2f Min_PDOP: %6.2f Max_PDOP: %6.2f GDOP_Percentile: %6.2f Min_GDOP: %6.2f Max_GDOP: %6.2f TDOP_Percentile: %6.2f Min_TDOP: %6.2f Max_TDOP: %6.2f HDOP_Percentile: %6.2f Min_HDOP: %6.2f Max_HDOP: %6.2f VDOP_Percentile: %6.2f Min_VDOP: %6.2f Max_VDOP: %6.2f Sat_used_All_Const_Percentile: %d Sat_not_used_All_Const_Percentile: %d Min_sat_used_All_Const: %d Min_sat_not_used_All_Const: %d Max_sat_used_All_Const: %d Max_sat_not_used_All_Const: %d Epochs_processed: %d Epochs_with_solution: %d Epochs_with_solution_reference_file: %d Epochs_omitted_no_data_reference_file: %d Epochs_skipped_no_data_reference_file: %d Epochs_no_satellites: %d Epochs_singular_matrix: %d Epochs_No_Reference_GNSS: %d Epochs_Over_HDOPorPDOP: %d Epochs_Over_HDOP: %d Epochs_Over_PDOP: %d Epochs_Over_GDOP: %d Total_Epochs_skipped: %d Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s Time_To_First_Fix: %.6g Epochs_First_Fix: %d Processing_time: %n%*.3f Epochs_missing_Ref_Sum: %3d Epochs_missing_Ref_All_file: %3d Num_DataGaps_Ref_Sum: %3d Num_DataGaps_Ref_All_file: %3d MaxSize_DataGap_Ref_Sum: %3d MaxSize_DataGap_Ref_All_file: %3d\n",
		sprintf(messagestr,"INFO (2)_Station: %4s (4)_Lon: %12.8f (6)_Lat: %13.8f (8)_Height: %9.4f (10)_Day: %2d (12)_Month: %2d (14)_Year: %4d (16)_DoY: %3d (18)_GPSWeek: %4d (20)_DoW: %d (22)_Percentile: %*.*f (24)_HPE_Percentile: %6.2f (26)_VPE_Percentile: %6.2f (28)_NPE_Percentile: %6.2f (30)_EPE_Percentile: %6.2f (32)_3DPE_Percentile: %6.2f (34)_MaxHPE: %6.2f (36)_MaxVPE: %6.2f (38)_MaxNPE: %6.2f (40)_MaxEPE: %6.2f (42)_Max3DPE: %6.2f (44)_Avail%%: %7.3f (46)_PDOP_Percentile: %6.2f (48)_Min_PDOP: %6.2f (50)_Max_PDOP: %6.2f (52)_GDOP_Percentile: %6.2f (54)_Min_GDOP: %6.2f (56)_Max_GDOP: %6.2f (58)_TDOP_Percentile: %6.2f (60)_Min_TDOP: %6.2f (62)_Max_TDOP: %6.2f (64)_HDOP_Percentile: %6.2f (66)_Min_HDOP: %6.2f (68)_Max_HDOP: %6.2f (70)_VDOP_Percentile: %6.2f (72)_Min_VDOP: %6.2f (74)_Max_VDOP: %6.2f (76)_Sat_used_All_Const_Percentile: %d (78)_Sat_not_used_All_Const_Percentile: %d (80)_Min_sat_used_All_Const: %d (82)_Min_sat_not_used_All_Const: %d (84)_Max_sat_used_All_Const: %d (86)_Max_sat_not_used_All_Const: %d (88)_Epochs_processed: %d (90)_Epochs_with_solution: %d (92)_Epochs_with_solution_reference_file: %d (94)_Epochs_omitted_no_data_reference_file: %d (96)_Epochs_skipped_no_data_reference_file: %d (98)_Epochs_no_satellites: %d (100)_Epochs_singular_matrix: %d (102)_Epochs_No_Reference_GNSS: %d (104)_Epochs_Over_HDOPorPDOP: %d (106)_Epochs_Over_HDOP: %d (108)_Epochs_Over_PDOP: %d (110)_Epochs_Over_GDOP: %d (112)_Total_Epochs_skipped: %d (114)_Epochs_missing_Sum: %3d (116)_Epochs_missing_All_file: %3d (118)_Num_DataGaps_Sum: %3d (120)_Num_DataGaps_All_file: %3d (122)_MaxSize_DataGap_Sum: %3d (124)_MaxSize_DataGap_All_file: %3d (126)_Station_Network_Name: %s (128)_Time_To_First_Fix: %.6g (130)_Epochs_First_Fix: %d (132)_Processing_time: %n%*.3f (134)_Epochs_missing_Ref_Sum: %3d (136)_Epochs_missing_Ref_All_file: %3d (138)_Num_DataGaps_Ref_Sum: %3d (140)_Num_DataGaps_Ref_All_file: %3d (142)_MaxSize_DataGap_Ref_Sum: %3d (144)_MaxSize_DataGap_Ref_All_file: %3d\n",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 tm.tm_mday,
			 tm.tm_mon+1,
			 year,
			 (int)DoY,
			 GPSWeek,
			 DoW,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 epoch->VPEPercentileSamples,
			 epoch->NPEPercentileSamples,
			 epoch->EPEPercentileSamples,
			 epoch->PE3DPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 epoch->MaxNError,
			 epoch->MaxEError,
			 epoch->Max3DError,
			 DGNSSPercentage,
			 epoch->PDOPPercentileSamples,
			 epoch->MinPDOP,
			 epoch->MaxPDOP,
			 epoch->GDOPPercentileSamples,
			 epoch->MinGDOP,
			 epoch->MaxGDOP,
			 epoch->TDOPPercentileSamples,
			 epoch->MinTDOP,
			 epoch->MaxTDOP,
			 epoch->HDOPPercentileSamples,
			 epoch->MinHDOP,
			 epoch->MaxHDOP,
			 epoch->VDOPPercentileSamples,
			 epoch->MinVDOP,
			 epoch->MaxVDOP,
			 epoch->NumSatUsed50PercentSamples,
			 epoch->NumSatNotUsed50PercentSamples,
			 epoch->MinNumSatUsed,
			 epoch->MinNumSatNotUsed,
			 epoch->MaxNumSatUsed,
			 epoch->MaxNumSatNotUsed,
			 epoch->TotalEpochs,
			 epoch->TotalEpochsSol,
			 epoch->TotalEpochsRef,
			 epoch->NumNoRefSumSkipped,
			 epoch->NumNoRefSolSkipped,
			 epoch->NumNoSatSkipped,
			 epoch->NumSingularMatrixSkipped,
			 epoch->NumNoRefGNSSSkipped,
			 epoch->NumHDOPorPDOPSkipped,
			 epoch->NumHDOPSkipped,
			 epoch->NumPDOPSkipped,
			 epoch->NumGDOPSkipped,
			 TotalEpochsSkipped,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 options->StationNetworkName,
			 TimeToFirstFix,
			 numEpochsFirstFix,
			 PosProcTime,
			 *ProcTimeLength,
			 (double)(totalprocessingTime)/1.0E6,
			 epochDGNSS->NumEpochsMissingSum,
			 epochDGNSS->NumEpochsMissingTotal,
			 epochDGNSS->NumDataGapsSum,
			 epochDGNSS->NumDataGapsTotal,
			 epochDGNSS->MaxDataGapSizeSum,
			 epochDGNSS->MaxDataGapSizeTotal);
	 } else {
		sprintf(messagestr,"INFO Rover: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f Avail%%: %7.3f PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Rover_Sum: %3d Epochs_missing_Rover_All_file: %3d Num_DataGaps_Rover_Sum: %3d Num_DataGaps_Rover_All_file: %3d MaxSize_DataGap_Rover_Sum: %3d MaxSize_DataGap_Rover_All_file: %3d Epochs_missing_Ref_Sum: %3d Epochs_missing_Ref_All_file: %3d Num_DataGaps_Ref_Sum: %3d Num_DataGaps_Ref_All_file: %3d MaxSize_DataGap_Ref_Sum: %3d MaxSize_DataGap_Ref_All_file: %3d Station_Network_Name: %s\n",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VPEPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 DGNSSPercentage,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->PDOPPercentileSamples,
			 epoch->MaxPDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->GDOPPercentileSamples,
			 epoch->MaxGDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->TDOPPercentileSamples,
			 epoch->MaxTDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HDOPPercentileSamples,
			 epoch->MaxHDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VDOPPercentileSamples,
			 epoch->MaxVDOP,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 epochDGNSS->NumEpochsMissingSum,
			 epochDGNSS->NumEpochsMissingTotal,
			 epochDGNSS->NumDataGapsSum,
			 epochDGNSS->NumDataGapsTotal,
			 epochDGNSS->MaxDataGapSizeSum,
			 epochDGNSS->MaxDataGapSizeTotal,
			 options->StationNetworkName);
	}
}

/*****************************************************************************
 * Name        : printSummary
 * Description : print summary at the end of the output file
 * Parameters  :
 * Name                                       |Da|Unit|Description
 * long long unsigned int StartTimeRealPCTime  I  N/A  Program start time in number of 
 *                                                      microseconds since 1 January 1970 
 * int *ProcTimeLength                         O  N/A  Number of characters used for printing
 *                                                      total processing time 
 * int *PosProcTime                            O  N/A  Position where processing time text
 *                                                      starts in last line of summary 
 * TEpoch  *epoch                              I  N/A  TEpoch structure
 * TStdESA *StdESA                             I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options                          I  N/A  TOptions structure
 *****************************************************************************/
void printSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch *epoch, TStdESA *StdESA, TOptions *options) {

    int    				    i;
	int						aux,maxLengthConstComb=0,lenMaxNumber;
    int    				    GPSWeek;
    int   		 	    	percentileSamples,percentile50Samples;
	int						year,DoW;
	int						NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation;
	int						NumEpochsDataGapSummary,numEpochsDecimatedAfterLastEpochSummary,TotalEpochsSkipped;
	int						PercentileDecimals=2,PercentileDigits=6;
	int						numEpochsFirstFix;
	int						numEpochsConvTimeFormalErrorHor,numEpochsConvTimeFormalErrorVer,numEpochsConvTimeFormalError3D;
	int						numEpochsConvTimePeriodFormalErrorHor,numEpochsConvTimePeriodFormalErrorVer,numEpochsConvTimePeriodFormalError3D;
	int						numEpochsConvTimePosErrorHor,numEpochsConvTimePosErrorVer,numEpochsConvTimePosError3D;
	int						numEpochsConvTimePeriodPosErrorHor,numEpochsConvTimePeriodPosErrorVer,numEpochsConvTimePeriodPosError3D;
	int						lenText1ConvTimeFormalErrorHor,lenText1ConvTimeFormalErrorVer,lenText1ConvTimeFormalError3D;
	int						lenText2ConvTimeFormalErrorHor,lenText2ConvTimeFormalErrorVer,lenText2ConvTimeFormalError3D;
	int						lenText3ConvTimeFormalErrorHor,lenText3ConvTimeFormalErrorVer,lenText3ConvTimeFormalError3D;
	int						lenText1ConvTimePeriodFormalErrorHor,lenText1ConvTimePeriodFormalErrorVer,lenText1ConvTimePeriodFormalError3D;
	int						lenText2ConvTimePeriodFormalErrorHor,lenText2ConvTimePeriodFormalErrorVer,lenText2ConvTimePeriodFormalError3D;
	int						lenText3ConvTimePeriodFormalErrorHor,lenText3ConvTimePeriodFormalErrorVer,lenText3ConvTimePeriodFormalError3D;
	int						lenText1ConvTimePosErrorHor,lenText1ConvTimePosErrorVer,lenText1ConvTimePosError3D;
	int						lenText2ConvTimePosErrorHor,lenText2ConvTimePosErrorVer,lenText2ConvTimePosError3D;
	int						lenText3ConvTimePosErrorHor,lenText3ConvTimePosErrorVer,lenText3ConvTimePosError3D;
	int						lenText1ConvTimePeriodPosErrorHor,lenText1ConvTimePeriodPosErrorVer,lenText1ConvTimePeriodPosError3D;
	int						lenText2ConvTimePeriodPosErrorHor,lenText2ConvTimePeriodPosErrorVer,lenText2ConvTimePeriodPosError3D;
	int						lenText3ConvTimePeriodPosErrorHor,lenText3ConvTimePeriodPosErrorVer,lenText3ConvTimePeriodPosError3D;
	int						maxlenText1Convergence,maxlenText2Convergence,maxlenText3Convergence;
	int						maxErrorlen,maxDOPlen,len;
	int						charPrinted;
	unsigned int			j;
	double					DataInterval;
	double			 		SoW,DoY;
	double					percentage;
	double					SolPercentage,RefPercentage;
	double					FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double					NoRefSolEpochPercentage,NoRefSumEpochPercentage,NoRefConstPercentage;
    double 					SamplesSolPercentage,SamplesSkippedPercentage;
	double					SecondsComp;
	double					TimeToFirstFix;
	double					ConvTimeFormalErrorHor,ConvTimeFormalErrorVer,ConvTimeFormalError3D;
	double					ConvTimePeriodFormalErrorHor,ConvTimePeriodFormalErrorVer,ConvTimePeriodFormalError3D;
	double					ConvTimePosErrorHor,ConvTimePosErrorVer,ConvTimePosError3D;
	double					ConvTimePeriodPosErrorHor,ConvTimePeriodPosErrorVer,ConvTimePeriodPosError3D;
    char      		 		receiverid[5],auxstr[50];
	char					Text1ConvTimeFormalErrorHor[MAX_PRINT_LINE],Text1ConvTimeFormalErrorVer[MAX_PRINT_LINE],Text1ConvTimeFormalError3D[MAX_PRINT_LINE];
	char					Text2ConvTimeFormalErrorHor[MAX_PRINT_LINE],Text2ConvTimeFormalErrorVer[MAX_PRINT_LINE],Text2ConvTimeFormalError3D[MAX_PRINT_LINE];
	char					Text3ConvTimeFormalErrorHor[MAX_PRINT_LINE],Text3ConvTimeFormalErrorVer[MAX_PRINT_LINE],Text3ConvTimeFormalError3D[MAX_PRINT_LINE];
	char					Text1ConvTimePeriodFormalErrorHor[MAX_PRINT_LINE],Text1ConvTimePeriodFormalErrorVer[MAX_PRINT_LINE],Text1ConvTimePeriodFormalError3D[MAX_PRINT_LINE];
	char					Text2ConvTimePeriodFormalErrorHor[MAX_PRINT_LINE],Text2ConvTimePeriodFormalErrorVer[MAX_PRINT_LINE],Text2ConvTimePeriodFormalError3D[MAX_PRINT_LINE];
	char					Text3ConvTimePeriodFormalErrorHor[MAX_PRINT_LINE],Text3ConvTimePeriodFormalErrorVer[MAX_PRINT_LINE],Text3ConvTimePeriodFormalError3D[MAX_PRINT_LINE];
	char					Text1ConvTimePosErrorHor[MAX_PRINT_LINE],Text1ConvTimePosErrorVer[MAX_PRINT_LINE],Text1ConvTimePosError3D[MAX_PRINT_LINE];
	char					Text2ConvTimePosErrorHor[MAX_PRINT_LINE],Text2ConvTimePosErrorVer[MAX_PRINT_LINE],Text2ConvTimePosError3D[MAX_PRINT_LINE];
	char					Text3ConvTimePosErrorHor[MAX_PRINT_LINE],Text3ConvTimePosErrorVer[MAX_PRINT_LINE],Text3ConvTimePosError3D[MAX_PRINT_LINE];
	char					Text1ConvTimePeriodPosErrorHor[MAX_PRINT_LINE],Text1ConvTimePeriodPosErrorVer[MAX_PRINT_LINE],Text1ConvTimePeriodPosError3D[MAX_PRINT_LINE];
	char					Text2ConvTimePeriodPosErrorHor[MAX_PRINT_LINE],Text2ConvTimePeriodPosErrorVer[MAX_PRINT_LINE],Text2ConvTimePeriodPosError3D[MAX_PRINT_LINE];
	char					Text3ConvTimePeriodPosErrorHor[MAX_PRINT_LINE],Text3ConvTimePeriodPosErrorVer[MAX_PRINT_LINE],Text3ConvTimePeriodPosError3D[MAX_PRINT_LINE];
	char					minPDOPsatStr[MAX_GNSS*8],minGDOPsatStr[MAX_GNSS*8],minTDOPsatStr[MAX_GNSS*8],minHDOPsatStr[MAX_GNSS*8],minVDOPsatStr[MAX_GNSS*8];
	char					maxPDOPsatStr[MAX_GNSS*8],maxGDOPsatStr[MAX_GNSS*8],maxTDOPsatStr[MAX_GNSS*8],maxHDOPsatStr[MAX_GNSS*8],maxVDOPsatStr[MAX_GNSS*8];
	char					MaxNErrorStr[MAX_GNSS*8],MaxEErrorStr[MAX_GNSS*8],MaxHErrorStr[MAX_GNSS*8],MaxVErrorStr[MAX_GNSS*8],Max3DErrorStr[MAX_GNSS*8];
	char					procTimestr[50];
	TTime					FirstEpoch,LastEpoch,LastEpochDataGaps;
	struct tm				tm;
	long long unsigned int	totalprocessingTime;

    //Convert receiver name to lower case
    for(i=0;i<4;i++) {
        receiverid[i]=tolower(epoch->receiver.name[i]);
    }
    receiverid[4]='\0';

	//Get data interval
	DataInterval=epoch->receiver.interval;
	if (options->decimate>epoch->receiver.interval && options->decimate!=0.) {
		//If decimation is higher than file data rate, then set the value to the epoch decimation
		DataInterval=options->decimate;
	} else {
		DataInterval=epoch->receiver.interval;
	}

	//Check number of decimals to be printed for percentile
	if (options->percentile==(double)((int)(options->percentile+0.005))) {
		PercentileDecimals=0;
		PercentileDigits=3;
	}

    // Check number of TotalEpochsSol for printable values
    if(epoch->TotalEpochsRef==0) {
        epoch->MaxNError=0.;
        epoch->MaxEError=0.;
        epoch->MaxHError=0.;
        epoch->MaxVError=0.;
        epoch->Max3DError=0.;
        epoch->HPEPercentileSamples=0.;
        epoch->VPEPercentileSamples=0.;
    } else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsRef-1;
		} else {
	        percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
		}
        if (options->recPosProvided==1) {
			//Compute NPE percentile of the samples
			qsort(epoch->NError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->NPEPercentileSamples=epoch->NError[percentileSamples];
			//Compute EPE percentile of the samples
			qsort(epoch->EError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->EPEPercentileSamples=epoch->EError[percentileSamples];
            //Compute HPE percentile of the samples
            qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
            //Compute VPE percentile of the samples
            qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
			//Compute 3D PE percentile of the samples
			qsort(epoch->Error3D,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
			epoch->PE3DPercentileSamples=epoch->Error3D[percentileSamples];
        }
    }

	//Get last epoch processed
	if (options->EndEpoch.MJDN!=-1) {
		if (tdiff(&options->EndEpoch,&epoch->t)>0.) {
			//Last epoch processed is prior to the end epoch
			memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
			memcpy(&LastEpochDataGaps,&epoch->t,sizeof(TTime));
		} else {
			memcpy(&LastEpoch,&options->EndEpoch,sizeof(TTime));
			memcpy(&LastEpochDataGaps,&options->EndEpoch,sizeof(TTime));
		}
	} else {
		memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
		if (options->filterIterations == 2) {
			//Backward filtering enabled. The last epoch must be the turning point
			memcpy(&LastEpochDataGaps,&epoch->BackwardTurningEpoch,sizeof(TTime));
		} else {
			memcpy(&LastEpochDataGaps,&epoch->LastSummaryEpoch,sizeof(TTime));
		}
	}

	//Get number of epochs passed in the summary interval
	if (epoch->StartSummaryEpoch.MJDN!=-1) {
		NumEpochsSummaryPeriod=(int)(tdiff(&LastEpochDataGaps,&epoch->StartSummaryEpoch)/DataInterval)+1;
	} else {
		NumEpochsSummaryPeriod=0;
	}

	//Get number of epochs missing in file in summary interval
	if (NumEpochsSummaryPeriod!=0) {
		if (options->filterIterations == 2) {
			NumEpochsMissingSummary=NumEpochsSummaryPeriod-epoch->TotalEpochsForward;
		} else {
			NumEpochsMissingSummary=NumEpochsSummaryPeriod-epoch->TotalEpochs;
		}
	} else {
		NumEpochsMissingSummary=0;
	}

	//Get number of epochs missing in file in summary interval that were decimated
	if (NumEpochsSummaryPeriod!=0) {
		if (isEpochDecimated(epoch,options)==1) {
			numEpochsDecimatedAfterLastEpochSummary=(int)(tdiff(&epoch->t,&LastEpochDataGaps)/epoch->receiver.interval);
		} else {
			numEpochsDecimatedAfterLastEpochSummary=0;
		}

		if (options->filterIterations == 2) {
			NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpochDataGaps,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1+numEpochsDecimatedAfterLastEpochSummary-epoch->TotalEpochsForward-epoch->TotalEpochsDecimatedForward-NumEpochsMissingSummary;
		} else {
			NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpochDataGaps,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1+numEpochsDecimatedAfterLastEpochSummary-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
		}
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		if (options->filterIterations == 2) {
			NumEpochsMissingFile=(int)(tdiff(&epoch->BackwardTurningEpoch,&epoch->firstEpochFile)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
		} else {
			NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstEpochFile)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
		}
	} else {
		NumEpochsMissingFile=0;
	}

	//Get total number of epochs in data gaps in summary
	if(DataInterval>epoch->receiver.interval) {
		NumEpochsDataGapSummary=NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation;
	} else {
		NumEpochsDataGapSummary=NumEpochsMissingSummary;
	}

    //Compute availability percentages
    if(epoch->TotalEpochs==0) {
		SolPercentage=0.;
		RefPercentage=0.;
        FewSatEpochsPercentage=0.;
        SingularEpochsPercentage=0.;
		NoRefConstPercentage=0.;
        DOPEpochsPercentage=0.;
        HDOPEpochsPercentage=0.;
        PDOPEpochsPercentage=0.;
        GDOPEpochsPercentage=0.;
        HDOPorPDOPEpochsPercentage=0.;
		NoRefSumEpochPercentage=0.;
		NoRefSolEpochPercentage=0.;
    } else {
		SolPercentage=100.*(double)(epoch->TotalEpochsSol)/((double)(epoch->TotalEpochs));
		RefPercentage=100.*(double)(epoch->TotalEpochsRef)/((double)(epoch->TotalEpochs));
        FewSatEpochsPercentage=100.*(double)(epoch->NumNoSatSkipped)/((double)(epoch->TotalEpochs));
        SingularEpochsPercentage=100.*(double)(epoch->NumSingularMatrixSkipped)/((double)(epoch->TotalEpochs));
		NoRefConstPercentage=100.*(double)(epoch->NumNoRefGNSSSkipped)/((double)(epoch->TotalEpochs));
        DOPEpochsPercentage=100.*(double)(epoch->NumDOPSkipped)/((double)(epoch->TotalEpochs));;
        HDOPEpochsPercentage=100.*(double)(epoch->NumHDOPSkipped)/((double)(epoch->TotalEpochs));
        PDOPEpochsPercentage=100.*(double)(epoch->NumPDOPSkipped)/((double)(epoch->TotalEpochs));
        GDOPEpochsPercentage=100.*(double)(epoch->NumGDOPSkipped)/((double)(epoch->TotalEpochs));
        HDOPorPDOPEpochsPercentage=100.*(double)(epoch->NumHDOPorPDOPSkipped)/((double)(epoch->TotalEpochs));
		NoRefSumEpochPercentage=100.*(double)(epoch->NumNoRefSumSkipped)/((double)(epoch->TotalEpochs));
		NoRefSolEpochPercentage=100.*(double)(epoch->NumNoRefSolSkipped)/((double)(epoch->TotalEpochs));
    }

	if(epoch->TotalEpochsSol==0) {
		epoch->HDOPPercentileSamples=0.;
		epoch->PDOPPercentileSamples=0.;
		epoch->GDOPPercentileSamples=0.;
		epoch->TDOPPercentileSamples=0.;
		epoch->VDOPPercentileSamples=0.;
		epoch->NumSatUsedPercentSamples=0;
		epoch->NumSatNotUsedPercentSamples=0;
		epoch->NumSatUsed50PercentSamples=0;
		epoch->NumSatNotUsed50PercentSamples=0;
		epoch->MinNumSatUsed=0;
		epoch->MaxNumSatUsed=0;
		epoch->MinNumSatNotUsed=0;
		epoch->MaxNumSatNotUsed=0;
		numEpochsFirstFix=0;
		TimeToFirstFix=0.;
		maxLengthConstComb=1;
		lenMaxNumber=1;
		ConvTimeFormalErrorHor=0;
		ConvTimeFormalErrorVer=0;
		ConvTimeFormalError3D=0;
		numEpochsConvTimeFormalErrorHor=0;
		numEpochsConvTimeFormalErrorVer=0;
		numEpochsConvTimeFormalError3D=0;
		ConvTimePeriodFormalErrorHor=0;
		ConvTimePeriodFormalErrorVer=0;
		ConvTimePeriodFormalError3D=0;
		numEpochsConvTimePeriodFormalErrorHor=0;
		numEpochsConvTimePeriodFormalErrorVer=0;
		numEpochsConvTimePeriodFormalError3D=0;
		ConvTimePosErrorHor=0;
		ConvTimePosErrorVer=0;
		ConvTimePosError3D=0;
		numEpochsConvTimePosErrorHor=0;
		numEpochsConvTimePosErrorVer=0;
		numEpochsConvTimePosError3D=0;
		ConvTimePeriodPosErrorHor=0;
		ConvTimePeriodPosErrorVer=0;
		ConvTimePeriodPosError3D=0;
		numEpochsConvTimePeriodPosErrorHor=0;
		numEpochsConvTimePeriodPosErrorVer=0;
		numEpochsConvTimePeriodPosError3D=0;
	} else {
		//Compute time to first fix
		TimeToFirstFix=tdiff(&epoch->FirstEpochSolution,&epoch->firstEpochFile);
		numEpochsFirstFix=(int)(TimeToFirstFix/DataInterval)+1;

		//Compute mean values
		epoch->MeanNumSatUsed/=(double)epoch->TotalEpochsSol;
		epoch->MeanNumSatNotUsed/=(double)epoch->TotalEpochsSol;
		for(i=0;i<MAX_GNSS;i++) {
			epoch->MeanNumSatUsedGNSS[i]/=(double)epoch->TotalEpochsSol;
			epoch->MeanNumSatNotUsedGNSS[i]/=(double)epoch->TotalEpochsSol;
		}
		epoch->MeanNumConstUsed/=(double)epoch->TotalEpochsSol;
		epoch->MeanNumConstNotUsed/=(double)epoch->TotalEpochsSol;

		//Compute max lengths for constellations combinations
		if (epoch->numconstCombUsed>4) {
			for(j=0;j<epoch->numconstCombUsed;j++) {
				aux=(int)strlen(epoch->constCombinationText[j]);
				if (aux>maxLengthConstComb) {
					maxLengthConstComb=aux;
				}
			}
			sprintf(auxstr,"%d",epoch->TotalEpochsRef);
			lenMaxNumber=(int)strlen(auxstr);
		} else {
			maxLengthConstComb=1;
			lenMaxNumber=1;
		}


		if (options->solutionMode==PPPMode) {
			//Compute convergence time with horizontal formal error
			if (options->computeConvTimeFormalErrHor==0) {
				ConvTimeFormalErrorHor=fabs(tdiff(&epoch->FirstEpochConvergedFormalErrHor,&epoch->FirstEpochSolution));
				numEpochsConvTimeFormalErrorHor=(int)(ConvTimeFormalErrorHor/DataInterval)+1;
			} else {
				//Not converged
				ConvTimeFormalErrorHor=0;
				numEpochsConvTimeFormalErrorHor=0;
			}
			//Compute convergence time with vertical formal error
			if (options->computeConvTimeFormalErrVer==0) {
				ConvTimeFormalErrorVer=fabs(tdiff(&epoch->FirstEpochConvergedFormalErrVer,&epoch->FirstEpochSolution));
				numEpochsConvTimeFormalErrorVer=(int)(ConvTimeFormalErrorVer/DataInterval)+1;
			} else {
				//Not converged
				ConvTimeFormalErrorVer=0;
				numEpochsConvTimeFormalErrorVer=0;
			}
			//Compute convergence time with 3D formal error
			if (options->computeConvTimeFormalErr3D==0) {
				ConvTimeFormalError3D=fabs(tdiff(&epoch->FirstEpochConvergedFormalErr3D,&epoch->FirstEpochSolution));
				numEpochsConvTimeFormalError3D=(int)(ConvTimeFormalError3D/DataInterval)+1;
			} else {
				//Not converged
				ConvTimeFormalError3D=0;
				numEpochsConvTimeFormalError3D=0;
			}
			//Compute convergence time with horizontal formal error with time period
			if (options->computeConvTimePeriodFormalErrHor==0) {
				ConvTimePeriodFormalErrorHor=fabs(tdiff(&epoch->FirstEpochConvergedPeriodFormalErrHor,&epoch->FirstEpochSolution));
				numEpochsConvTimePeriodFormalErrorHor=(int)(ConvTimePeriodFormalErrorHor/DataInterval)+1;
			} else {
				//Not converged
				ConvTimePeriodFormalErrorHor=0;
				numEpochsConvTimePeriodFormalErrorHor=0;
			}
			//Compute convergence time with vertical formal error with time period
			if (options->computeConvTimePeriodFormalErrVer==0) {
				ConvTimePeriodFormalErrorVer=fabs(tdiff(&epoch->FirstEpochConvergedPeriodFormalErrVer,&epoch->FirstEpochSolution));
				numEpochsConvTimePeriodFormalErrorVer=(int)(ConvTimePeriodFormalErrorVer/DataInterval)+1;
			} else {
				//Not converged
				ConvTimePeriodFormalErrorVer=0;
				numEpochsConvTimePeriodFormalErrorVer=0;
			}
			//Compute convergence time with 3D formal error with time period
			if (options->computeConvTimePeriodFormalErr3D==0) {
				ConvTimePeriodFormalError3D=fabs(tdiff(&epoch->FirstEpochConvergedPeriodFormalErr3D,&epoch->FirstEpochSolution));
				numEpochsConvTimePeriodFormalError3D=(int)(ConvTimePeriodFormalError3D/DataInterval)+1;
			} else {
				//Not converged
				ConvTimePeriodFormalError3D=0;
				numEpochsConvTimePeriodFormalError3D=0;
			}
			if (epoch->receiver.RefPositionAvail==1) {
				//Reference position available
				//Compute convergence time with horizontal position error
				if (options->computeConvTimePosErrHor==0) {
					ConvTimePosErrorHor=fabs(tdiff(&epoch->FirstEpochConvergedPosErrHor,&epoch->FirstEpochSolution));
					numEpochsConvTimePosErrorHor=(int)(ConvTimePosErrorHor/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePosErrorHor=0;
					numEpochsConvTimePosErrorHor=0;
				}
				//Compute convergence time with vertical position error
				if (options->computeConvTimePosErrVer==0) {
					ConvTimePosErrorVer=fabs(tdiff(&epoch->FirstEpochConvergedPosErrVer,&epoch->FirstEpochSolution));
					numEpochsConvTimePosErrorVer=(int)(ConvTimePosErrorVer/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePosErrorVer=0;
					numEpochsConvTimePosErrorVer=0;
				}
				//Compute convergence time with 3D position error
				if (options->computeConvTimePosErr3D==0) {
					ConvTimePosError3D=fabs(tdiff(&epoch->FirstEpochConvergedPosErr3D,&epoch->FirstEpochSolution));
					numEpochsConvTimePosError3D=(int)(ConvTimePosError3D/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePosError3D=0;
					numEpochsConvTimePosError3D=0;
				}
				//Compute convergence time with horizontal position error with time period
				if (options->computeConvTimePeriodPosErrHor==0) {
					ConvTimePeriodPosErrorHor=fabs(tdiff(&epoch->FirstEpochConvergedPeriodPosErrHor,&epoch->FirstEpochSolution));
					numEpochsConvTimePeriodPosErrorHor=(int)(ConvTimePeriodPosErrorHor/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePeriodPosErrorHor=0;
					numEpochsConvTimePeriodPosErrorHor=0;
				}
				//Compute convergence time with vertical position error with time period
				if (options->computeConvTimePeriodPosErrVer==0) {
					ConvTimePeriodPosErrorVer=fabs(tdiff(&epoch->FirstEpochConvergedPeriodPosErrVer,&epoch->FirstEpochSolution));
					numEpochsConvTimePeriodPosErrorVer=(int)(ConvTimePeriodPosErrorVer/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePeriodPosErrorVer=0;
					numEpochsConvTimePeriodPosErrorVer=0;
				}
				//Compute convergence time with 3D position error with time period
				if (options->computeConvTimePeriodPosErr3D==0) {
					ConvTimePeriodPosError3D=fabs(tdiff(&epoch->FirstEpochConvergedPeriodPosErr3D,&epoch->FirstEpochSolution));
					numEpochsConvTimePeriodPosError3D=(int)(ConvTimePeriodPosError3D/DataInterval)+1;
				} else {
					//Not converged
					ConvTimePeriodPosError3D=0;
					numEpochsConvTimePeriodPosError3D=0;
				}
			} else {
				ConvTimePosErrorHor=0;
				numEpochsConvTimePosErrorHor=0;
				ConvTimePosErrorVer=0;
				numEpochsConvTimePosErrorVer=0;
				ConvTimePosError3D=0;
				numEpochsConvTimePosError3D=0;
				ConvTimePeriodPosErrorHor=0;
				numEpochsConvTimePeriodPosErrorHor=0;
				ConvTimePeriodPosErrorVer=0;
				numEpochsConvTimePeriodPosErrorVer=0;
				ConvTimePeriodPosError3D=0;
				numEpochsConvTimePeriodPosError3D=0;
			}
		} else {
			ConvTimeFormalErrorHor=0;
			ConvTimeFormalErrorVer=0;
			ConvTimeFormalError3D=0;
			numEpochsConvTimeFormalErrorHor=0;
			numEpochsConvTimeFormalErrorVer=0;
			numEpochsConvTimeFormalError3D=0;
			ConvTimePeriodFormalErrorHor=0;
			ConvTimePeriodFormalErrorVer=0;
			ConvTimePeriodFormalError3D=0;
			numEpochsConvTimePeriodFormalErrorHor=0;
			numEpochsConvTimePeriodFormalErrorVer=0;
			numEpochsConvTimePeriodFormalError3D=0;
			ConvTimePosErrorHor=0;
			ConvTimePosErrorVer=0;
			ConvTimePosError3D=0;
			numEpochsConvTimePosErrorHor=0;
			numEpochsConvTimePosErrorVer=0;
			numEpochsConvTimePosError3D=0;
			ConvTimePeriodPosErrorHor=0;
			ConvTimePeriodPosErrorVer=0;
			ConvTimePeriodPosError3D=0;
			numEpochsConvTimePeriodPosErrorHor=0;
			numEpochsConvTimePeriodPosErrorVer=0;
			numEpochsConvTimePeriodPosError3D=0;
		}

		//Compute then number of samples according to the percentile
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsSol-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsSol)*options->percentile/100.);
		}
		percentile50Samples=(int)((double)(epoch->TotalEpochsSol)*50./100.);
		//Compute HDOP percentile of the samples
		qsort(epoch->HDOP,epoch->TotalEpochsSol,sizeof(double),qsort_compare_double);
		epoch->HDOPPercentileSamples=epoch->HDOP[percentileSamples];
		//Compute PDOP percentile of the samples
		qsort(epoch->PDOP,epoch->TotalEpochsSol,sizeof(double),qsort_compare_double);
		epoch->PDOPPercentileSamples=epoch->PDOP[percentileSamples];
		//Compute GDOP percentile of the samples
		qsort(epoch->GDOP,epoch->TotalEpochsSol,sizeof(double),qsort_compare_double);
		epoch->GDOPPercentileSamples=epoch->GDOP[percentileSamples];
		//Compute TDOP percentile of the samples
		qsort(epoch->TDOP,epoch->TotalEpochsSol,sizeof(double),qsort_compare_double);
		epoch->TDOPPercentileSamples=epoch->TDOP[percentileSamples];
		//Compute VDOP percentile of the samples
		qsort(epoch->VDOP,epoch->TotalEpochsSol,sizeof(double),qsort_compare_double);
		epoch->VDOPPercentileSamples=epoch->VDOP[percentileSamples];
		//Compute used satellites used percentile
		qsort(epoch->NumSatUsed,epoch->TotalEpochsSol,sizeof(int),qsort_compare_int_reverse);//Use reverse order so the percentile refers to at least N satellites used
		epoch->NumSatUsedPercentSamples=epoch->NumSatUsed[percentileSamples];
		epoch->NumSatUsed50PercentSamples=epoch->NumSatUsed[percentile50Samples];
		//Compute not used satellites used percentile
		qsort(epoch->NumSatNotUsed,epoch->TotalEpochsSol,sizeof(int),qsort_compare_int);
		epoch->NumSatNotUsedPercentSamples=epoch->NumSatNotUsed[percentileSamples];
		epoch->NumSatNotUsed50PercentSamples=epoch->NumSatNotUsed[percentile50Samples];
		//Compute used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue; //Skip not used constellations to save computation time
			qsort(epoch->NumSatUsedGNSS[i],epoch->TotalEpochsSol,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
			epoch->NumSatUsedPercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentileSamples];
			epoch->NumSatUsed50PercentSamplesGNSS[i]=epoch->NumSatUsedGNSS[i][percentile50Samples];
		}
		//Compute not used satellites percentile per constellations
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue; //Skip unselected constellations to save computation time
			qsort(epoch->NumSatNotUsedGNSS[i],epoch->TotalEpochsSol,sizeof(int),qsort_compare_int);
			epoch->NumSatNotUsedPercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentileSamples];
			epoch->NumSatNotUsed50PercentSamplesGNSS[i]=epoch->NumSatNotUsedGNSS[i][percentile50Samples];
		}
		//Compute used constellations percentile 
		qsort(epoch->NumConstUsed,epoch->TotalEpochsSol,sizeof(int),qsort_compare_int_reverse); //Use reverse order so the percentile refers to at least N satellites used
		epoch->NumConstUsedPercentSamples=epoch->NumConstUsed[percentileSamples];
		epoch->NumConstUsed50PercentSamples=epoch->NumConstUsed[percentile50Samples];
		//Compute not used constellations percentile 
		qsort(epoch->NumConstNotUsed,epoch->TotalEpochsSol,sizeof(int),qsort_compare_int);
		epoch->NumConstNotUsedPercentSamples=epoch->NumConstNotUsed[percentileSamples];
		epoch->NumConstNotUsed50PercentSamples=epoch->NumConstNotUsed[percentile50Samples];
	}


    //Compute availability percentages for Stanford-ESA if required
    if(options->stanfordesa==1) {
        if(StdESA->numsamplesProcessed==0) {
            SamplesSolPercentage=0.;
            SamplesSkippedPercentage=0.;
        } else {
            SamplesSolPercentage=100.*(double)(StdESA->numsamplesComputed)/((double)(StdESA->numsamplesProcessed));
            SamplesSkippedPercentage=100.*(double)(StdESA->numsamplesSingular)/((double)(StdESA->numsamplesProcessed));
        }
    }

	//Set values to 0 if receiver position is not set
	if(options->recPosProvided==0) {
		 epoch->HPEPercentileSamples=0.;
		 epoch->VPEPercentileSamples=0.;
		 epoch->MaxHError=0.;
		 epoch->MaxVError=0.;
	}

	//Compute total epochs skipped (any reason)
	TotalEpochsSkipped=epoch->NumNoRefSolSkipped+epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumNoRefGNSSSkipped+epoch->NumDOPSkipped;

    // Print Summary heading
    fprintf(options->outFileStream,"INFO --------------------- %s Summary ---------------------\n",SolutionModeNum2SolutionModeChar(options->solutionMode));

	//Print DOP thresholds
	if(options->HDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO HDOP Threshold: %6.2f\n",options->maxHDOP);
	}
	if(options->PDOPthreshold == 1) {
		fprintf(options->outFileStream,"INFO PDOP Threshold: %6.2f\n",options->maxPDOP);
	}
    if(options->GDOPthreshold == 1) {
        fprintf(options->outFileStream,"INFO GDOP Threshold: %6.2f\n",options->maxGDOP);
    }

	//Print first epoch processed
	if (options->firstEpochSummary.MJDN!=-1 && epoch->StartSummaryEpoch.MJDN==-1) {
		memcpy(&FirstEpoch,&options->firstEpochSummary,sizeof(TTime));
		//Get GPSWeek
		ttime2gpswsnoroll(&options->firstEpochSummary, &GPSWeek, &SoW);
		//Compute calendar date
		t2tmnolocal(&options->firstEpochSummary, &tm, &SecondsComp);
		//Get DoY
		t2doy(&options->firstEpochSummary,&year,&DoY);
		//Start epoch of summary provided by user is ahead of all epochs in observation file
		fprintf(options->outFileStream,"INFO First epoch of summary provided by user: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&options->firstEpochSummary),GPSWeek,SoW);
		if (epoch->StartSummaryEpoch.MJDN==-1) {
			if (epoch->TotalEpochs>0 && epoch->TotalEpochsSol>0) {
				fprintf(options->outFileStream,"INFO First epoch of summary provided by user is ahead of all epochs in observation file. No epochs included in the summary\n");
			}
		}
	} else if (epoch->StartSummaryEpoch.MJDN==-1) {
		if (epoch->t.MJDN!=-1) {
			fprintf(options->outFileStream,"INFO No epochs after convergence time (from 0h onwards)\n");
			memcpy(&FirstEpoch,&epoch->firstEpochFile,sizeof(TTime));
		} else {
			 fprintf(options->outFileStream,"INFO No data available in observation file\n");
			 FirstEpoch.MJDN=-1;
			 FirstEpoch.SoD=0;
		}
	} else {
		memcpy(&FirstEpoch,&epoch->StartSummaryEpoch,sizeof(TTime));
		//Get GPSWeek of start epoch
		ttime2gpswsnoroll(&epoch->StartSummaryEpoch, &GPSWeek, &SoW);
		//Compute calendar date of start epoch
		t2tmnolocal(&epoch->StartSummaryEpoch, &tm, &SecondsComp);
		//Get DoY of start epoch
		t2doy(&epoch->StartSummaryEpoch,&year,&DoY);
		//Print start epoch
		fprintf(options->outFileStream,"INFO First epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryEpoch),GPSWeek,SoW);
		//Get GPSWeek of last epoch
		ttime2gpswsnoroll(&LastEpoch, &GPSWeek, &SoW);
		//Compute calendar date of last epoch
		t2tmnolocal(&LastEpoch,&tm, &SecondsComp);
		//Get DoY of last epoch
		t2doy(&LastEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Last  epoch of summary: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&LastEpoch),GPSWeek,SoW);
	}



    //Print total epochs processed
    fprintf(options->outFileStream,"INFO Total epochs processed: %d\n",epoch->TotalEpochs);

    //Print total epochs with solution
    fprintf(options->outFileStream,"INFO Total epochs processed with solution: %d ( %.*f%% )\n",epoch->TotalEpochsSol,SolPercentage>=99.9995?0:3,SolPercentage);

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (options->UseReferenceFile==1) {
	   	if (options->receiverPositionSource != rpSETREF) {
			fprintf(options->outFileStream,"INFO Total epochs processed with solution and position from reference file: %d ( %.*f%% )\n",epoch->TotalEpochsRef,RefPercentage>=99.9995?0:3,RefPercentage);
			fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.*f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage>=99.9995?0:3,NoRefSumEpochPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to no position from reference file for modelling: %d ( %.*f%% )\n",epoch->NumNoRefSolSkipped,NoRefSolEpochPercentage>=99.9995?0:3,NoRefSolEpochPercentage);
		}
	}

    //Print epochs skipped due to lack of satellites
    fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.*f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage>=99.9995?0:3,FewSatEpochsPercentage);

    //Print epochs skipped due to singular geometry matrix
    fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.*f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage>=99.9995?0:3,SingularEpochsPercentage);

    //Print epochs skipped due to reference constellation not available
    fprintf(options->outFileStream,"INFO Total epochs skipped due to reference constellation not available: %d ( %.*f%% )\n",epoch->NumNoRefGNSSSkipped,NoRefConstPercentage>=99.9995?0:3,NoRefConstPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage>=99.9995?0:3,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.*f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage>=99.9995?0:3,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage>=99.9995?0:3,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage>=99.9995?0:3,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.*f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage>=99.9995?0:3,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	percentage=NoRefSolEpochPercentage+FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage;
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.*f%% )\n",TotalEpochsSkipped,percentage>=99.9995?0:3,percentage);

	if(DataInterval>epoch->receiver.interval) {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period and not decimated%s): %3d\n",options->filterIterations==2?" -forward direction only-":"",NumEpochsMissingSummary);

		//Print total number of epochs missing in summary but were decimated
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period and decimated%s):     %3d\n",options->filterIterations==2?" -forward direction only-":"",NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period%s):                   %3d\n",options->filterIterations==2?" -forward direction only-":"",NumEpochsMissingSummary+NumEpochsMissingSumNoDecimation);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (all the file):%s                            %3d\n",options->filterIterations==2?"                         ":"",NumEpochsMissingFile);

	} else {
		//Print total number of epochs missing in summary
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (during summary period%s): %3d\n",options->filterIterations==2?" -forward direction only-":"",NumEpochsMissingSummary);

		//Print total number of epochs missing in file
		fprintf(options->outFileStream,"INFO Total epochs missing in observation file (all the file):%s          %3d\n",options->filterIterations==2?"                         ":"",NumEpochsMissingFile);
	}

	//Print number of data gaps in summary
	fprintf(options->outFileStream,"INFO Number of data gaps in observation file (during summary period%s): %3d\n",options->filterIterations==2?" -forward direction only-":"",epoch->NumDataGapsSum);

	//Print number of data gaps in all file
	fprintf(options->outFileStream,"INFO Number of data gaps in observation file (all the file):%s          %3d\n",options->filterIterations==2?"                         ":"",epoch->NumDataGapsTotal);

	if (epoch->MaxDataGapSizeSum>0) {
		//Print maximum data gap size in summary
		ttime2gpswsnoroll(&epoch->DataGapSum, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapSum,&tm, &SecondsComp);
		t2doy(&epoch->DataGapSum,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period%s):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->filterIterations==2?" -forward direction only-":"",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
		t2doy(&epoch->DataGapTotal,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):%s           %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->filterIterations==2?"                         ":"",epoch->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapTotal),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d\n",epoch->MaxDataGapSizeTotal);
	}


	//Print Time To First Fix
	if (numEpochsFirstFix>0) {
		ttime2gpswsnoroll(&epoch->FirstEpochSolution, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->FirstEpochSolution,&tm, &SecondsComp);
		t2doy(&epoch->FirstEpochSolution,&year,&DoY);
		fprintf(options->outFileStream,"INFO Time To First Fix: %.6g seconds (%d epoch%s) at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",TimeToFirstFix,numEpochsFirstFix,numEpochsFirstFix==1?"":"s",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochSolution),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Time To First Fix: no epochs with solution\n");
	}

	if (epoch->TotalEpochsSol!=0) {
		//Print percentiles for constellations used and unused
		fprintf(options->outFileStream,"INFO Constellations     used 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumConstUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumConstUsedPercentSamples,epoch->MeanNumConstUsed);
		fprintf(options->outFileStream,"INFO Constellations not used 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumConstNotUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumConstNotUsedPercentSamples,epoch->MeanNumConstNotUsed);

		//Print number of epochs with each constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations used:");
		for(j=0;j<epoch->numconstCombUsed;j++) {
			percentage=100.*(double)(epoch->numEpochsconstCombination[j])/((double)epoch->TotalEpochsSol);
			fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constCombinationText[j],lenMaxNumber,epoch->numEpochsconstCombination[j],percentage>=99.9995?0:3,percentage);
			if ((j%4)==0 && j>0 && j!=(epoch->numconstCombUsed-1)) {
				fprintf(options->outFileStream,"\nINFO Number of epochs with constellations used:");
			}
		}
		fprintf(options->outFileStream,"\n");

		//Print number of epochs with each not used constellation combination
		fprintf(options->outFileStream,"INFO Number of epochs with constellations not used:");
		if (epoch->numconstCombNotUsed==0) {
			fprintf(options->outFileStream," 0 ( 0%% )\n");
		} else {
			for(j=0;j<epoch->numconstCombNotUsed;j++) {
				percentage=100.*(double)(epoch->numEpochsconstNotUsedCombination[j])/((double)epoch->TotalEpochsSol);
				fprintf(options->outFileStream," %-*s %*d ( %.*f%% )",maxLengthConstComb,epoch->constNotUsedCombinationText[j],lenMaxNumber,epoch->numEpochsconstNotUsedCombination[j],percentage>=99.9995?0:3,percentage);
				if ((j%4)==0 && j>0 && j!=(epoch->numconstCombNotUsed-1)) {
					fprintf(options->outFileStream,"\nINFO Number of epochs with constellations not used:");
				}
			}
			fprintf(options->outFileStream,"\n");
		}

		//Print number of epochs where each constellation was used as reference clock
		fprintf(options->outFileStream,"INFO Constellations used as reference clock:");
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->numEpochsRefClock[i]==0) continue;
			percentage=100.*(double)epoch->numEpochsRefClock[i]/((double)(epoch->TotalEpochsSol));
			fprintf(options->outFileStream," %s %d ( %.*f%% )",gnsstype2gnssstr(i),epoch->numEpochsRefClock[i],percentage>=99.9995?0:3,percentage);
		}
		fprintf(options->outFileStream,"\n");

		//Print percentiles for satellites used and unused
		fprintf(options->outFileStream,"INFO Satellites used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamples,epoch->MeanNumSatUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatUsedPercentSamplesGNSS[i],epoch->MeanNumSatUsedGNSS[i]);
		}
		fprintf(options->outFileStream,"INFO Satellites not used (all constellations) 50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",epoch->NumSatNotUsed50PercentSamples,PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamples,epoch->MeanNumSatNotUsed);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0) continue;
			fprintf(options->outFileStream,"INFO Satellites not used (%s)                50 Percentile: %2d | %*.*f Percentile: %2d | Mean: %5.2f\n",gnsstype2gnssstr(i),epoch->NumSatNotUsed50PercentSamplesGNSS[i],PercentileDigits,PercentileDecimals,options->percentile,epoch->NumSatNotUsedPercentSamplesGNSS[i],epoch->MeanNumSatNotUsedGNSS[i]);
		}

		//Print satellites used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites used
			if (epoch->MinNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MinSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MinSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites used
			if (epoch->MaxNumAllSatUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->MaxNumSatUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used min value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total minimum number of satellites not used
			if (epoch->MinNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MinNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		if (epoch->MinNumSatNotUsed==9999) {
			//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
			epoch->MinNumSatNotUsed=epoch->MaxNumSatNotUsed;
			memcpy(&epoch->MinSatNotUsedEpoch,&epoch->MaxSatNotUsedEpoch,sizeof(TTime));
		}
		ttime2gpswsnoroll(&epoch->MinSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			if (epoch->MinNumSatNotUsedGNSS[i]==9999) {
				//Value 9999 means that satellites not used has always been 0 and therefore always was set the maximum value as 0, but not the minimum value. Copy the value from maximum value
				epoch->MinNumSatNotUsedGNSS[i]=epoch->MaxNumSatNotUsedGNSS[i];
				memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->MaxSatNotUsedEpochGNSS[i],sizeof(TTime));
			}
			ttime2gpswsnoroll(&epoch->MinSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MinSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MinSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Minimum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MinNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}
		//Print satellites not used max value
		len=0;
		auxstr[0]='\0';
		for(i=0;i<MAX_GNSS;i++) {
			//Create the string with the number of satellites used per constellation in the epoch with total maximum number of satellites not used
			if (epoch->MaxNumAllSatNotUsedGNSS[i]==0) continue;
			len+=sprintf(&auxstr[len]," %c %d",gnsstype2char(i),epoch->MaxNumAllSatNotUsedGNSS[i]);
		}
		auxstr[0]='(';
		auxstr[len]=')';
		auxstr[len+1]='\0';
		if (len==0) auxstr[0]=' ';
		ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxSatNotUsedEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxSatNotUsedEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum satellites not used (all constellations) %2d %s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNumSatNotUsed,auxstr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpoch),GPSWeek,SoW);
		for(i=0;i<MAX_GNSS;i++) {
			if (options->ConstellationUsed[i]==0||epoch->MaxNumSatNotUsedGNSS[i]==0) continue;
			ttime2gpswsnoroll(&epoch->MaxSatNotUsedEpochGNSS[i], &GPSWeek, &SoW);
			t2tmnolocal(&epoch->MaxSatNotUsedEpochGNSS[i],&tm, &SecondsComp);
			t2doy(&epoch->MaxSatNotUsedEpochGNSS[i],&year,&DoY);
			fprintf(options->outFileStream,"INFO Maximum satellites not used (%s)                %2d %*s  at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",gnsstype2gnssstr(i),epoch->MaxNumSatNotUsedGNSS[i],len,"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxSatNotUsedEpochGNSS[i]),GPSWeek,SoW);
		}

		if (options->solutionMode==PPPMode) {
			//Compute text length for convergence time with horizontal formal error
			lenText1ConvTimeFormalErrorHor=sprintf(Text1ConvTimeFormalErrorHor,"Convergence time with horizontal formal error from first fix to %.6g metres:",options->formalErrorThresholdHor);
			if (numEpochsConvTimeFormalErrorHor!=0) {
				lenText2ConvTimeFormalErrorHor=sprintf(Text2ConvTimeFormalErrorHor,"%.6g",ConvTimeFormalErrorHor);
				lenText3ConvTimeFormalErrorHor=sprintf(Text3ConvTimeFormalErrorHor,"(%d epoch%s)",numEpochsConvTimeFormalErrorHor,numEpochsConvTimeFormalErrorHor==1?"":"s");
			} else {
				lenText2ConvTimeFormalErrorHor=sprintf(Text2ConvTimeFormalErrorHor,"no convergence");
				lenText3ConvTimeFormalErrorHor=0;
				Text3ConvTimeFormalErrorHor[0]='\0';
			}
			//Compute text length for convergence time with vertical formal error
			lenText1ConvTimeFormalErrorVer=sprintf(Text1ConvTimeFormalErrorVer,"Convergence time with vertical formal error from first fix to %.6g metres:",options->formalErrorThresholdVer);
			if (numEpochsConvTimeFormalErrorVer!=0) {
				lenText2ConvTimeFormalErrorVer=sprintf(Text2ConvTimeFormalErrorVer,"%.6g",ConvTimeFormalErrorVer);
				lenText3ConvTimeFormalErrorVer=sprintf(Text3ConvTimeFormalErrorVer,"(%d epoch%s)",numEpochsConvTimeFormalErrorVer,numEpochsConvTimeFormalErrorVer==1?"":"s");
			} else {
				lenText2ConvTimeFormalErrorVer=sprintf(Text2ConvTimeFormalErrorVer,"no convergence");
				lenText3ConvTimeFormalErrorVer=0;
				Text3ConvTimeFormalErrorVer[0]='\0';
			}
			//Compute text length for convergence time with 3D formal error
			lenText1ConvTimeFormalError3D=sprintf(Text1ConvTimeFormalError3D,"Convergence time with 3D formal error from first fix to %.6g metres:",options->formalErrorThreshold3D);
			if (numEpochsConvTimeFormalError3D!=0) {
				lenText2ConvTimeFormalError3D=sprintf(Text2ConvTimeFormalError3D,"%.6g",ConvTimeFormalError3D);
				lenText3ConvTimeFormalError3D=sprintf(Text3ConvTimeFormalError3D,"(%d epoch%s)",numEpochsConvTimeFormalError3D,numEpochsConvTimeFormalError3D==1?"":"s");
			} else {
				lenText2ConvTimeFormalError3D=sprintf(Text2ConvTimeFormalError3D,"no convergence");
				lenText3ConvTimeFormalError3D=0;
				Text3ConvTimeFormalError3D[0]='\0';
			}

			//Compute text length for convergence time with formal error with horiziontal time period
			lenText1ConvTimePeriodFormalErrorHor=sprintf(Text1ConvTimePeriodFormalErrorHor,"Convergence time with horizontal formal error from first fix to %.6g metres and maintained %.6g seconds:",options->formalErrorThresholdHor,options->minTimeConvergedFormalErrHor);
			if (numEpochsConvTimePeriodFormalErrorHor!=0) {
				lenText2ConvTimePeriodFormalErrorHor=sprintf(Text2ConvTimePeriodFormalErrorHor,"%.6g",ConvTimePeriodFormalErrorHor);
				lenText3ConvTimePeriodFormalErrorHor=sprintf(Text3ConvTimePeriodFormalErrorHor,"(%d epoch%s)",numEpochsConvTimePeriodFormalErrorHor,numEpochsConvTimePeriodFormalErrorHor==1?"":"s");
			} else {
				lenText2ConvTimePeriodFormalErrorHor=sprintf(Text2ConvTimePeriodFormalErrorHor,"no convergence");
				lenText3ConvTimePeriodFormalErrorHor=0;
				Text3ConvTimePeriodFormalErrorHor[0]='\0';
			}
			//Compute text length for convergence time with formal error with vertical time period
			lenText1ConvTimePeriodFormalErrorVer=sprintf(Text1ConvTimePeriodFormalErrorVer,"Convergence time with vertical formal error from first fix to %.6g metres and maintained %.6g seconds:",options->formalErrorThresholdVer,options->minTimeConvergedFormalErrVer);
			if (numEpochsConvTimePeriodFormalErrorVer!=0) {
				lenText2ConvTimePeriodFormalErrorVer=sprintf(Text2ConvTimePeriodFormalErrorVer,"%.6g",ConvTimePeriodFormalErrorVer);
				lenText3ConvTimePeriodFormalErrorVer=sprintf(Text3ConvTimePeriodFormalErrorVer,"(%d epoch%s)",numEpochsConvTimePeriodFormalErrorVer,numEpochsConvTimePeriodFormalErrorVer==1?"":"s");
			} else {
				lenText2ConvTimePeriodFormalErrorVer=sprintf(Text2ConvTimePeriodFormalErrorVer,"no convergence");
				lenText3ConvTimePeriodFormalErrorVer=0;
				Text3ConvTimePeriodFormalErrorVer[0]='\0';
			}
			//Compute text length for convergence time with formal error with 3D time period
			lenText1ConvTimePeriodFormalError3D=sprintf(Text1ConvTimePeriodFormalError3D,"Convergence time with 3D formal error from first fix to %.6g metres and maintained %.6g seconds:",options->formalErrorThreshold3D,options->minTimeConvergedFormalErr3D);
			if (numEpochsConvTimePeriodFormalError3D!=0) {
				lenText2ConvTimePeriodFormalError3D=sprintf(Text2ConvTimePeriodFormalError3D,"%.6g",ConvTimePeriodFormalError3D);
				lenText3ConvTimePeriodFormalError3D=sprintf(Text3ConvTimePeriodFormalError3D,"(%d epoch%s)",numEpochsConvTimePeriodFormalError3D,numEpochsConvTimePeriodFormalError3D==1?"":"s");
			} else {
				lenText2ConvTimePeriodFormalError3D=sprintf(Text2ConvTimePeriodFormalError3D,"no convergence");
				lenText3ConvTimePeriodFormalError3D=0;
				Text3ConvTimePeriodFormalError3D[0]='\0';
			}
			
			if (epoch->receiver.RefPositionAvail==1) {
				//Compute text length for convergence time with horizontal positioning error
				lenText1ConvTimePosErrorHor=sprintf(Text1ConvTimePosErrorHor,"Convergence time with horizontal positioning error from first fix to %.6g metres:",options->formalErrorThresholdHor);
				if (numEpochsConvTimePosErrorHor!=0) {
					lenText2ConvTimePosErrorHor=sprintf(Text2ConvTimePosErrorHor,"%.6g",ConvTimePosErrorHor);
					lenText3ConvTimePosErrorHor=sprintf(Text3ConvTimePosErrorHor,"(%d epoch%s)",numEpochsConvTimePosErrorHor,numEpochsConvTimePosErrorHor==1?"":"s");
				} else {
					lenText2ConvTimePosErrorHor=sprintf(Text2ConvTimePosErrorHor,"no convergence");
					lenText3ConvTimePosErrorHor=0;
					Text3ConvTimePosErrorHor[0]='\0';
				}
				//Compute text length for convergence time with vertical positioning error
				lenText1ConvTimePosErrorVer=sprintf(Text1ConvTimePosErrorVer,"Convergence time with vertical positioning error from first fix to %.6g metres:",options->formalErrorThresholdVer);
				if (numEpochsConvTimePosErrorVer!=0) {
					lenText2ConvTimePosErrorVer=sprintf(Text2ConvTimePosErrorVer,"%.6g",ConvTimePosErrorVer);
					lenText3ConvTimePosErrorVer=sprintf(Text3ConvTimePosErrorVer,"(%d epoch%s)",numEpochsConvTimePosErrorVer,numEpochsConvTimePosErrorVer==1?"":"s");
				} else {
					lenText2ConvTimePosErrorVer=sprintf(Text2ConvTimePosErrorVer,"no convergence");
					lenText3ConvTimePosErrorVer=0;
					Text3ConvTimePosErrorVer[0]='\0';
				}
				//Compute text length for convergence time with 3D positioning error
				lenText1ConvTimePosError3D=sprintf(Text1ConvTimePosError3D,"Convergence time with 3D positioning error from first fix to %.6g metres:",options->formalErrorThreshold3D);
				if (numEpochsConvTimePosError3D!=0) {
					lenText2ConvTimePosError3D=sprintf(Text2ConvTimePosError3D,"%.6g",ConvTimePosError3D);
					lenText3ConvTimePosError3D=sprintf(Text3ConvTimePosError3D,"(%d epoch%s)",numEpochsConvTimePosError3D,numEpochsConvTimePosError3D==1?"":"s");
				} else {
					lenText2ConvTimePosError3D=sprintf(Text2ConvTimePosError3D,"no convergence");
					lenText3ConvTimePosError3D=0;
					Text3ConvTimePosError3D[0]='\0';
				}
				//Compute text length for convergence time with horizontal positioning error with time period
				lenText1ConvTimePeriodPosErrorHor=sprintf(Text1ConvTimePeriodPosErrorHor,"Convergence time with horizontal positioning error from first fix to %.6g metres and maintained %.6g seconds:",options->positionErrorThresholdHor,options->minTimeConvergedPosErrHor);
				if (numEpochsConvTimePeriodPosErrorHor!=0) {
					lenText2ConvTimePeriodPosErrorHor=sprintf(Text2ConvTimePeriodPosErrorHor,"%.6g",ConvTimePeriodPosErrorHor);
					lenText3ConvTimePeriodPosErrorHor=sprintf(Text3ConvTimePeriodPosErrorHor,"(%d epoch%s)",numEpochsConvTimePeriodPosErrorHor,numEpochsConvTimePeriodPosErrorHor==1?"":"s");
				} else {
					lenText2ConvTimePeriodPosErrorHor=sprintf(Text2ConvTimePeriodPosErrorHor,"no convergence");
					lenText3ConvTimePeriodPosErrorHor=0;
					Text3ConvTimePeriodPosErrorHor[0]='\0';
				}
				//Compute text length for convergence time with vertical positioning error with time period
				lenText1ConvTimePeriodPosErrorVer=sprintf(Text1ConvTimePeriodPosErrorVer,"Convergence time with vertical positioning error from first fix to %.6g metres and maintained %.6g seconds:",options->positionErrorThresholdVer,options->minTimeConvergedPosErrVer);
				if (numEpochsConvTimePeriodPosErrorVer!=0) {
					lenText2ConvTimePeriodPosErrorVer=sprintf(Text2ConvTimePeriodPosErrorVer,"%.6g",ConvTimePeriodPosErrorVer);
					lenText3ConvTimePeriodPosErrorVer=sprintf(Text3ConvTimePeriodPosErrorVer,"(%d epoch%s)",numEpochsConvTimePeriodPosErrorVer,numEpochsConvTimePeriodPosErrorVer==1?"":"s");
				} else {
					lenText2ConvTimePeriodPosErrorVer=sprintf(Text2ConvTimePeriodPosErrorVer,"no convergence");
					lenText3ConvTimePeriodPosErrorVer=0;
					Text3ConvTimePeriodPosErrorVer[0]='\0';
				}
				//Compute text length for convergence time with 3D positioning error with time period
				lenText1ConvTimePeriodPosError3D=sprintf(Text1ConvTimePeriodPosError3D,"Convergence time with 3D positioning error from first fix to %.6g metres and maintained %.6g seconds:",options->positionErrorThreshold3D,options->minTimeConvergedPosErr3D);
				if (numEpochsConvTimePeriodPosError3D!=0) {
					lenText2ConvTimePeriodPosError3D=sprintf(Text2ConvTimePeriodPosError3D,"%.6g",ConvTimePeriodPosError3D);
					lenText3ConvTimePeriodPosError3D=sprintf(Text3ConvTimePeriodPosError3D,"(%d epoch%s)",numEpochsConvTimePeriodPosError3D,numEpochsConvTimePeriodPosError3D==1?"":"s");
				} else {
					lenText2ConvTimePeriodPosError3D=sprintf(Text2ConvTimePeriodPosError3D,"no convergence");
					lenText3ConvTimePeriodPosError3D=0;
					Text3ConvTimePeriodPosError3D[0]='\0';
				}
			} else {
				lenText1ConvTimePosErrorHor=0;
				lenText1ConvTimePosErrorVer=0;
				lenText1ConvTimePosError3D=0;
				lenText2ConvTimePosErrorHor=0;
				lenText2ConvTimePosErrorVer=0;
				lenText2ConvTimePosError3D=0;
				lenText3ConvTimePosErrorHor=0;
				lenText3ConvTimePosErrorVer=0;
				lenText3ConvTimePosError3D=0;
				lenText1ConvTimePeriodPosErrorHor=0;
				lenText1ConvTimePeriodPosErrorVer=0;
				lenText1ConvTimePeriodPosError3D=0;
				lenText2ConvTimePeriodPosErrorHor=0;
				lenText2ConvTimePeriodPosErrorVer=0;
				lenText2ConvTimePeriodPosError3D=0;
				lenText3ConvTimePeriodPosErrorHor=0;
				lenText3ConvTimePeriodPosErrorVer=0;
				lenText3ConvTimePeriodPosError3D=0;
			}

			//Compute max length of all convergence time texts so they are aligned
			maxlenText1Convergence=max(lenText1ConvTimeFormalErrorHor,lenText1ConvTimePeriodFormalErrorHor);
			maxlenText1Convergence=max(maxlenText1Convergence,max(lenText1ConvTimeFormalErrorVer,lenText1ConvTimePeriodFormalErrorVer));
			maxlenText1Convergence=max(maxlenText1Convergence,max(lenText1ConvTimeFormalError3D,lenText1ConvTimePeriodFormalError3D));
			maxlenText1Convergence=max(maxlenText1Convergence,max(lenText1ConvTimePosErrorHor,lenText1ConvTimePeriodPosErrorHor));
			maxlenText1Convergence=max(maxlenText1Convergence,max(lenText1ConvTimePosErrorVer,lenText1ConvTimePeriodPosErrorVer));
			maxlenText1Convergence=max(maxlenText1Convergence,max(lenText1ConvTimePosError3D,lenText1ConvTimePeriodPosError3D));

			maxlenText2Convergence=max(lenText2ConvTimeFormalErrorHor,lenText2ConvTimePeriodFormalErrorHor);
			maxlenText2Convergence=max(maxlenText2Convergence,max(lenText2ConvTimeFormalErrorVer,lenText2ConvTimePeriodFormalErrorVer));
			maxlenText2Convergence=max(maxlenText2Convergence,max(lenText2ConvTimeFormalError3D,lenText2ConvTimePeriodFormalError3D));
			maxlenText2Convergence=max(maxlenText2Convergence,max(lenText2ConvTimePosErrorHor,lenText2ConvTimePeriodPosErrorHor));
			maxlenText2Convergence=max(maxlenText2Convergence,max(lenText2ConvTimePosErrorVer,lenText2ConvTimePeriodPosErrorVer));
			maxlenText2Convergence=max(maxlenText2Convergence,max(lenText2ConvTimePosError3D,lenText2ConvTimePeriodPosError3D));

			maxlenText3Convergence=max(lenText3ConvTimeFormalErrorHor,lenText3ConvTimePeriodFormalErrorHor);
			maxlenText3Convergence=max(maxlenText3Convergence,max(lenText3ConvTimeFormalErrorVer,lenText3ConvTimePeriodFormalErrorVer));
			maxlenText3Convergence=max(maxlenText3Convergence,max(lenText3ConvTimeFormalError3D,lenText3ConvTimePeriodFormalError3D));
			maxlenText3Convergence=max(maxlenText3Convergence,max(lenText3ConvTimePosErrorHor,lenText3ConvTimePeriodPosErrorHor));
			maxlenText3Convergence=max(maxlenText3Convergence,max(lenText3ConvTimePosErrorVer,lenText3ConvTimePeriodPosErrorVer));
			maxlenText3Convergence=max(maxlenText3Convergence,max(lenText3ConvTimePosError3D,lenText3ConvTimePeriodPosError3D));

			//Print convergence time with horizontal formal error
			if (numEpochsConvTimeFormalErrorHor!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedFormalErrHor, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedFormalErrHor,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedFormalErrHor,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimeFormalErrorHor,maxlenText2Convergence,Text2ConvTimeFormalErrorHor,maxlenText3Convergence,Text3ConvTimeFormalErrorHor,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedFormalErrHor),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimeFormalErrorHor,maxlenText2Convergence,Text2ConvTimeFormalErrorHor);
			}

			//Print convergence time with horizontal formal error with time period
			if (numEpochsConvTimePeriodFormalErrorHor!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodFormalErrHor, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedPeriodFormalErrHor,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedPeriodFormalErrHor,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodFormalErrorHor,maxlenText2Convergence,Text2ConvTimePeriodFormalErrorHor,maxlenText3Convergence,Text3ConvTimePeriodFormalErrorHor,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodFormalErrHor),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodFormalErrorHor,maxlenText2Convergence,Text2ConvTimePeriodFormalErrorHor);
			}

			if (epoch->receiver.RefPositionAvail==1) {
				//Print convergence time with horizontal positioning error
				if (numEpochsConvTimePosErrorHor!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPosErrHor, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPosErrHor,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPosErrHor,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePosErrorHor,maxlenText2Convergence,Text2ConvTimePosErrorHor,maxlenText3Convergence,Text3ConvTimePosErrorHor,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPosErrHor),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePosErrorHor,maxlenText2Convergence,Text2ConvTimePosErrorHor);
				}
				//Print convergence time with horizontal positioning error with time period
				if (numEpochsConvTimePeriodPosErrorHor!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodPosErrHor, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPeriodPosErrHor,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPeriodPosErrHor,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodPosErrorHor,maxlenText2Convergence,Text2ConvTimePeriodPosErrorHor,maxlenText3Convergence,Text3ConvTimePeriodPosErrorHor,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodPosErrHor),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodPosErrorHor,maxlenText2Convergence,Text2ConvTimePeriodPosErrorHor);
				}
			}
			//Print convergence time with vertical formal error
			if (numEpochsConvTimeFormalErrorVer!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedFormalErrVer, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedFormalErrVer,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedFormalErrVer,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimeFormalErrorVer,maxlenText2Convergence,Text2ConvTimeFormalErrorVer,maxlenText3Convergence,Text3ConvTimeFormalErrorVer,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedFormalErrVer),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimeFormalErrorVer,maxlenText2Convergence,Text2ConvTimeFormalErrorVer);
			}

			//Print convergence time with vertical formal error with time period
			if (numEpochsConvTimePeriodFormalErrorVer!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodFormalErrVer, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedPeriodFormalErrVer,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedPeriodFormalErrVer,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodFormalErrorVer,maxlenText2Convergence,Text2ConvTimePeriodFormalErrorVer,maxlenText3Convergence,Text3ConvTimePeriodFormalErrorVer,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodFormalErrVer),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodFormalErrorVer,maxlenText2Convergence,Text2ConvTimePeriodFormalErrorVer);
			}

			if (epoch->receiver.RefPositionAvail==1) {
				//Print convergence time with vertical positioning error
				if (numEpochsConvTimePosErrorVer!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPosErrVer, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPosErrVer,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPosErrVer,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePosErrorVer,maxlenText2Convergence,Text2ConvTimePosErrorVer,maxlenText3Convergence,Text3ConvTimePosErrorVer,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPosErrVer),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePosErrorVer,maxlenText2Convergence,Text2ConvTimePosErrorVer);
				}
				//Print convergence time with vertical positioning error with time period
				if (numEpochsConvTimePeriodPosErrorVer!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodPosErrVer, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPeriodPosErrVer,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPeriodPosErrVer,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodPosErrorVer,maxlenText2Convergence,Text2ConvTimePeriodPosErrorVer,maxlenText3Convergence,Text3ConvTimePeriodPosErrorVer,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodPosErrVer),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodPosErrorVer,maxlenText2Convergence,Text2ConvTimePeriodPosErrorVer);
				}
			}
			//Print convergence time with 3D formal error
			if (numEpochsConvTimeFormalError3D!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedFormalErr3D, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedFormalErr3D,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedFormalErr3D,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimeFormalError3D,maxlenText2Convergence,Text2ConvTimeFormalError3D,maxlenText3Convergence,Text3ConvTimeFormalError3D,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedFormalErr3D),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimeFormalError3D,maxlenText2Convergence,Text2ConvTimeFormalError3D);
			}

			//Print convergence time with 3D formal error with time period
			if (numEpochsConvTimePeriodFormalError3D!=0) {
				ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodFormalErr3D, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->FirstEpochConvergedPeriodFormalErr3D,&tm, &SecondsComp);
				t2doy(&epoch->FirstEpochConvergedPeriodFormalErr3D,&year,&DoY);
				fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodFormalError3D,maxlenText2Convergence,Text2ConvTimePeriodFormalError3D,maxlenText3Convergence,Text3ConvTimePeriodFormalError3D,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodFormalErr3D),GPSWeek,SoW);
			} else {
				fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodFormalError3D,maxlenText2Convergence,Text2ConvTimePeriodFormalError3D);
			}

			if (epoch->receiver.RefPositionAvail==1) {
				//Print convergence time with 3D positioning error
				if (numEpochsConvTimePosError3D!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPosErr3D, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPosErr3D,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPosErr3D,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePosError3D,maxlenText2Convergence,Text2ConvTimePosError3D,maxlenText3Convergence,Text3ConvTimePosError3D,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPosErr3D),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePosError3D,maxlenText2Convergence,Text2ConvTimePosError3D);
				}
				//Print convergence time with 3D positioning error with time period
				if (numEpochsConvTimePeriodPosError3D!=0) {
					ttime2gpswsnoroll(&epoch->FirstEpochConvergedPeriodPosErr3D, &GPSWeek, &SoW);
					t2tmnolocal(&epoch->FirstEpochConvergedPeriodPosErr3D,&tm, &SecondsComp);
					t2doy(&epoch->FirstEpochConvergedPeriodPosErr3D,&year,&DoY);
					fprintf(options->outFileStream,"INFO %-*s %*s seconds %*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",maxlenText1Convergence,Text1ConvTimePeriodPosError3D,maxlenText2Convergence,Text2ConvTimePeriodPosError3D,maxlenText3Convergence,Text3ConvTimePeriodPosError3D,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->FirstEpochConvergedPeriodPosErr3D),GPSWeek,SoW);
				} else {
					fprintf(options->outFileStream,"INFO %-*s %-*s\n",maxlenText1Convergence,Text1ConvTimePeriodPosError3D,maxlenText2Convergence,Text2ConvTimePeriodPosError3D);
				}
			}
		}

		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		//Create strings with number of satellites per constellation of min and max DOP and save the maximum string length
		//Min PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinPDOPGNSS[i]==0) continue;
			len+=sprintf(&minPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinPDOPGNSS[i]);
		}
		minPDOPsatStr[0]='(';
		minPDOPsatStr[len]=')';
		len++;
		minPDOPsatStr[len]='\0';
		maxDOPlen=len;
		//Max PDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxPDOPGNSS[i]==0) continue;
			len+=sprintf(&maxPDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxPDOPGNSS[i]);
		}
		maxPDOPsatStr[0]='(';
		maxPDOPsatStr[len]=')';
		len++;
		maxPDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinGDOPGNSS[i]==0) continue;
			len+=sprintf(&minGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinGDOPGNSS[i]);
		}
		minGDOPsatStr[0]='(';
		minGDOPsatStr[len]=')';
		len++;
		minGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max GDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxGDOPGNSS[i]==0) continue;
			len+=sprintf(&maxGDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxGDOPGNSS[i]);
		}
		maxGDOPsatStr[0]='(';
		maxGDOPsatStr[len]=')';
		len++;
		maxGDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinTDOPGNSS[i]==0) continue;
			len+=sprintf(&minTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinTDOPGNSS[i]);
		}
		minTDOPsatStr[0]='(';
		minTDOPsatStr[len]=')';
		len++;
		minTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max TDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxTDOPGNSS[i]==0) continue;
			len+=sprintf(&maxTDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxTDOPGNSS[i]);
		}
		maxTDOPsatStr[0]='(';
		maxTDOPsatStr[len]=')';
		len++;
		maxTDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinHDOPGNSS[i]==0) continue;
			len+=sprintf(&minHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinHDOPGNSS[i]);
		}
		minHDOPsatStr[0]='(';
		minHDOPsatStr[len]=')';
		len++;
		minHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max HDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxHDOPGNSS[i]==0) continue;
			len+=sprintf(&maxHDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHDOPGNSS[i]);
		}
		maxHDOPsatStr[0]='(';
		maxHDOPsatStr[len]=')';
		len++;
		maxHDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Min VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMinVDOPGNSS[i]==0) continue;
			len+=sprintf(&minVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMinVDOPGNSS[i]);
		}
		minVDOPsatStr[0]='(';
		minVDOPsatStr[len]=')';
		len++;
		minVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;
		//Max VDOP satellite string
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->NumSatMaxVDOPGNSS[i]==0) continue;
			len+=sprintf(&maxVDOPsatStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVDOPGNSS[i]);
		}
		maxVDOPsatStr[0]='(';
		maxVDOPsatStr[len]=')';
		len++;
		maxVDOPsatStr[len]='\0';
		if (len>maxDOPlen) maxDOPlen=len;

		//Print PDOP min value
		ttime2gpswsnoroll(&epoch->MinPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinPDOP,epoch->NumSatMinPDOP,maxDOPlen,minPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinPDOPEpoch),GPSWeek,SoW);
		//Print GDOP min value
		ttime2gpswsnoroll(&epoch->MinGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinGDOP,epoch->NumSatMinGDOP,maxDOPlen,minGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinGDOPEpoch),GPSWeek,SoW);
		//Print TDOP min value
		ttime2gpswsnoroll(&epoch->MinTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinTDOP,epoch->NumSatMinTDOP,maxDOPlen,minTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print HDOP min value
		ttime2gpswsnoroll(&epoch->MinHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinHDOP,epoch->NumSatMinHDOP,maxDOPlen,minHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinHDOPEpoch),GPSWeek,SoW);
		//Print VDOP min value
		ttime2gpswsnoroll(&epoch->MinVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MinVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MinVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Minimum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MinVDOP,epoch->NumSatMinVDOP,maxDOPlen,minVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MinVDOPEpoch),GPSWeek,SoW);
		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->MaxPDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxPDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxPDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,epoch->NumSatMaxPDOP,maxDOPlen,maxPDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxPDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->MaxGDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxGDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxGDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,epoch->NumSatMaxGDOP,maxDOPlen,maxGDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxGDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->MaxTDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxTDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxTDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,epoch->NumSatMaxTDOP,maxDOPlen,maxTDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->MaxHDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxHDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxHDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,epoch->NumSatMaxHDOP,maxDOPlen,maxHDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->MaxVDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->MaxVDOPEpoch,&tm, &SecondsComp);
		t2doy(&epoch->MaxVDOPEpoch,&year,&DoY);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,epoch->NumSatMaxVDOP,maxDOPlen,maxVDOPsatStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVDOPEpoch),GPSWeek,SoW);
	}

    if(options->recPosProvided==1) {
		if (epoch->TotalEpochsRef==0) {
				fprintf(options->outFileStream,"INFO No epochs with solution %sfor computing positioning error percentiles%s\n",options->UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?" and Stanford-ESA statistics":"");
		} else {
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->StartSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->StartSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->StartSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO First epoch of summary for computing positioning error percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->StartSummaryPercentileEpoch),GPSWeek,SoW);
			//Get GPSWeek of start epoch
			ttime2gpswsnoroll(&epoch->LastSummaryPercentileEpoch, &GPSWeek, &SoW);
			//Compute calendar date of start epoch
			t2tmnolocal(&epoch->LastSummaryPercentileEpoch, &tm, &SecondsComp);
			//Get DoY of start epoch
			t2doy(&epoch->LastSummaryPercentileEpoch,&year,&DoY);
			fprintf(options->outFileStream,"INFO Last  epoch of summary for computing positioning error percentiles%s: %02d/%02d/%4d %02d:%02d:%02d.%02d / %s / %4d %9.2f\n",options->stanfordesa==1?" and Stanford-ESA statistics":"",tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->LastSummaryPercentileEpoch),GPSWeek,SoW);
		}
	}

    if(options->stanfordesa==1) {
        //Print total geometries processed
        fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %llu\n",StdESA->numsamplesProcessed);

        //Print total geometries with solution
        if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
            //If percentage is 100%, print 100% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.*f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage>=100.?0:3,SamplesSolPercentage);
        } else if (SamplesSolPercentage>=99.999) {
            //This is to avoid printing 1.00E+02% when rounding 99.999%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( 99.999%% )\n",StdESA->numsamplesComputed);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %llu ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        }

        //Print epochs skipped due to singular geometry matrix
        if(SamplesSkippedPercentage==0.) {
            //If percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %llu ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        }
    }


    if(epoch->TotalEpochsSol!=0) {
        if(options->recPosProvided==1) {
			if (epoch->TotalEpochsRef!=0) {
        	    //Print Horizontal error Percentile
        	    fprintf(options->outFileStream,"INFO Horizontal %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HPEPercentileSamples);

            	//Print Vertical error Percentile
	            fprintf(options->outFileStream,"INFO Vertical   %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VPEPercentileSamples);

        	    //Print North error Percentile
        	    fprintf(options->outFileStream,"INFO North      %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->NPEPercentileSamples);

        	    //Print East error Percentile
        	    fprintf(options->outFileStream,"INFO East       %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->EPEPercentileSamples);

        	    //Print 3D error Percentile
        	    fprintf(options->outFileStream,"INFO 3D         %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PE3DPercentileSamples);

				//Create strings with number of satellites per constellation of error metrics and save the maximum string length
				//Max North Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxNErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxNErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxNErrorGNSS[i]);
				}
				MaxNErrorStr[0]='(';
				MaxNErrorStr[len]=')';
				len++;
				MaxNErrorStr[len]='\0';
				maxErrorlen=len;
				//Max East Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxEErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxEErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxEErrorGNSS[i]);
				}
				MaxEErrorStr[0]='(';
				MaxEErrorStr[len]=')';
				len++;
				MaxEErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max Horizontal Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxHErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxHErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxHErrorGNSS[i]);
				}
				MaxHErrorStr[0]='(';
				MaxHErrorStr[len]=')';
				len++;
				MaxHErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max Vertical Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMaxVErrorGNSS[i]==0) continue;
					len+=sprintf(&MaxVErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMaxVErrorGNSS[i]);
				}
				MaxVErrorStr[0]='(';
				MaxVErrorStr[len]=')';
				len++;
				MaxVErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;
				//Max 3D Error satellite string
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->NumSatMax3DErrorGNSS[i]==0) continue;
					len+=sprintf(&Max3DErrorStr[len]," %c %2d",gnsstype2char(i),epoch->NumSatMax3DErrorGNSS[i]);
				}
				Max3DErrorStr[0]='(';
				Max3DErrorStr[len]=')';
				len++;
				Max3DErrorStr[len]='\0';
				if (len>maxErrorlen) maxErrorlen=len;

    	        // Print value and epoch with maximum horizontal error
       		    ttime2gpswsnoroll(&epoch->MaxHerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxHerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxHerrorEpoch,&year,&DoY);
           		fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,epoch->NumSatMaxHError,maxErrorlen,MaxHErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxHerrorEpoch),GPSWeek,SoW);

            	// Print value and epoch with maximum vertical error
            	ttime2gpswsnoroll(&epoch->MaxVerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxVerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxVerrorEpoch,&year,&DoY);
            	fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,epoch->NumSatMaxVError,maxErrorlen,MaxVErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxVerrorEpoch),GPSWeek,SoW);

    	        // Print value and epoch with maximum North error
       		    ttime2gpswsnoroll(&epoch->MaxNerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxNerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxNerrorEpoch,&year,&DoY);
           		fprintf(options->outFileStream,"INFO Maximum North      Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxNError,epoch->NumSatMaxNError,maxErrorlen,MaxNErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxNerrorEpoch),GPSWeek,SoW);

    	        // Print value and epoch with maximum East error
       		    ttime2gpswsnoroll(&epoch->MaxEerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->MaxEerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->MaxEerrorEpoch,&year,&DoY);
           		fprintf(options->outFileStream,"INFO Maximum East       Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxEError,epoch->NumSatMaxEError,maxErrorlen,MaxEErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->MaxEerrorEpoch),GPSWeek,SoW);

    	        // Print value and epoch with maximum 3D error
       		    ttime2gpswsnoroll(&epoch->Max3DerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->Max3DerrorEpoch,&tm, &SecondsComp);
				t2doy(&epoch->Max3DerrorEpoch,&year,&DoY);
           		fprintf(options->outFileStream,"INFO Maximum 3D         Positioning Error: %6.2f metres with %2d satellites %-*s at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->Max3DError,epoch->NumSatMax3DError,maxErrorlen,Max3DErrorStr,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->Max3DerrorEpoch),GPSWeek,SoW);
			}
        }
    }

	//Print processing time 
	computeProcessingTime(StartTimeRealPCTime,&totalprocessingTime,0,options);
	sprintf(procTimestr,"%.3f",(double)(totalprocessingTime)/1.0E6);
	*ProcTimeLength=(int)strlen(procTimestr)+1; //The +1 is to leave an extra slot in case when the final processing time is computed, one more character is needed


	// Print percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	if (options->printV5format==0) {
		if (FirstEpoch.MJDN==-1) {
			GPSWeek=0;
			SoW=0;
			DoW=0;
			year=0;
			DoY=0.;
			tm.tm_mday=0;
			tm.tm_mon=-1;
			SecondsComp=0.;
		} else {
			ttime2gpswsnoroll(&FirstEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&FirstEpoch, &tm, &SecondsComp);
			t2doy(&FirstEpoch,&year,&DoY);
			DoW=(int)(SoW/86400.);
		}
		//charPrinted=sprintf(messagestr,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f Day: %2d Month: %2d Year: %4d DoY: %3d GPSWeek: %4d DoW: %d Percentile: %*.*f HPE_Percentile: %6.2f VPE_Percentile: %6.2f NPE_Percentile: %6.2f EPE_Percentile: %6.2f 3DPE_Percentile: %6.2f MaxHPE: %6.2f MaxVPE: %6.2f MaxNPE: %6.2f MaxEPE: %6.2f Max3DPE: %6.2f Avail%%: %7.3f PDOP_Percentile: %6.2f Min_PDOP: %6.2f Max_PDOP: %6.2f GDOP_Percentile: %6.2f Min_GDOP: %6.2f Max_GDOP: %6.2f TDOP_Percentile: %6.2f Min_TDOP: %6.2f Max_TDOP: %6.2f HDOP_Percentile: %6.2f Min_HDOP: %6.2f Max_HDOP: %6.2f VDOP_Percentile: %6.2f Min_VDOP: %6.2f Max_VDOP: %6.2f Sat_used_All_Const_Percentile: %d Sat_not_used_All_Const_Percentile: %d Min_sat_used_All_Const: %d Min_sat_not_used_All_Const: %d Max_sat_used_All_Const: %d Max_sat_not_used_All_Const: %d Epochs_processed: %d Epochs_with_solution: %d Epochs_with_solution_reference_file: %d Epochs_omitted_no_data_reference_file: %d Epochs_skipped_no_data_reference_file: %d Epochs_no_satellites: %d Epochs_singular_matrix: %d Epochs_No_Reference_GNSS: %d Epochs_Over_HDOPorPDOP: %d Epochs_Over_HDOP: %d Epochs_Over_PDOP: %d Epochs_Over_GDOP: %d Total_Epochs_skipped: %d Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s Time_To_First_Fix: %.6g Epochs_First_Fix: %d Processing_time: %n%*.3f",
		charPrinted=sprintf(messagestr,"INFO (2)_Station: %4s (4)_Lon: %12.8f (6)_Lat: %13.8f (8)_Height: %9.4f (10)_Day: %2d (12)_Month: %2d (14)_Year: %4d (16)_DoY: %3d (18)_GPSWeek: %4d (20)_DoW: %d (22)_Percentile: %*.*f (24)_HPE_Percentile: %6.2f (26)_VPE_Percentile: %6.2f (28)_NPE_Percentile: %6.2f (30)_EPE_Percentile: %6.2f (32)_3DPE_Percentile: %6.2f (34)_MaxHPE: %6.2f (36)_MaxVPE: %6.2f (38)_MaxNPE: %6.2f (40)_MaxEPE: %6.2f (42)_Max3DPE: %6.2f (44)_Avail%%: %7.3f (46)_PDOP_Percentile: %6.2f (48)_Min_PDOP: %6.2f (50)_Max_PDOP: %6.2f (52)_GDOP_Percentile: %6.2f (54)_Min_GDOP: %6.2f (56)_Max_GDOP: %6.2f (58)_TDOP_Percentile: %6.2f (60)_Min_TDOP: %6.2f (62)_Max_TDOP: %6.2f (64)_HDOP_Percentile: %6.2f (66)_Min_HDOP: %6.2f (68)_Max_HDOP: %6.2f (70)_VDOP_Percentile: %6.2f (72)_Min_VDOP: %6.2f (74)_Max_VDOP: %6.2f (76)_Sat_used_All_Const_Percentile: %d (78)_Sat_not_used_All_Const_Percentile: %d (80)_Min_sat_used_All_Const: %d (82)_Min_sat_not_used_All_Const: %d (84)_Max_sat_used_All_Const: %d (86)_Max_sat_not_used_All_Const: %d (88)_Epochs_processed: %d (90)_Epochs_with_solution: %d (92)_Epochs_with_solution_reference_file: %d (94)_Epochs_omitted_no_data_reference_file: %d (96)_Epochs_skipped_no_data_reference_file: %d (98)_Epochs_no_satellites: %d (100)_Epochs_singular_matrix: %d (102)_Epochs_No_Reference_GNSS: %d (104)_Epochs_Over_HDOPorPDOP: %d (106)_Epochs_Over_HDOP: %d (108)_Epochs_Over_PDOP: %d (110)_Epochs_Over_GDOP: %d (112)_Total_Epochs_skipped: %d (114)_Epochs_missing_Sum: %3d (116)_Epochs_missing_All_file: %3d (118)_Num_DataGaps_Sum: %3d (120)_Num_DataGaps_All_file: %3d (122)_MaxSize_DataGap_Sum: %3d (124)_MaxSize_DataGap_All_file: %3d (126)_Station_Network_Name: %s (128)_Time_To_First_Fix: %.6g (130)_Epochs_First_Fix: %d (132)_Processing_time: %n%*.3f",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 tm.tm_mday,
			 tm.tm_mon+1,
			 year,
			 (int)DoY,
			 GPSWeek,
			 DoW,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 epoch->VPEPercentileSamples,
			 epoch->NPEPercentileSamples,
			 epoch->EPEPercentileSamples,
			 epoch->PE3DPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 epoch->MaxNError,
			 epoch->MaxEError,
			 epoch->Max3DError,
			 SolPercentage,
			 epoch->PDOPPercentileSamples,
			 epoch->MinPDOP,
			 epoch->MaxPDOP,
			 epoch->GDOPPercentileSamples,
			 epoch->MinGDOP,
			 epoch->MaxGDOP,
			 epoch->TDOPPercentileSamples,
			 epoch->MinTDOP,
			 epoch->MaxTDOP,
			 epoch->HDOPPercentileSamples,
			 epoch->MinHDOP,
			 epoch->MaxHDOP,
			 epoch->VDOPPercentileSamples,
			 epoch->MinVDOP,
			 epoch->MaxVDOP,
			 epoch->NumSatUsed50PercentSamples,
			 epoch->NumSatNotUsed50PercentSamples,
			 epoch->MinNumSatUsed,
			 epoch->MinNumSatNotUsed,
			 epoch->MaxNumSatUsed,
			 epoch->MaxNumSatNotUsed,
			 epoch->TotalEpochs,
			 epoch->TotalEpochsSol,
			 epoch->TotalEpochsRef,
			 epoch->NumNoRefSumSkipped,
			 epoch->NumNoRefSolSkipped,
			 epoch->NumNoSatSkipped,
			 epoch->NumSingularMatrixSkipped,
			 epoch->NumNoRefGNSSSkipped,
			 epoch->NumHDOPorPDOPSkipped,
			 epoch->NumHDOPSkipped,
			 epoch->NumPDOPSkipped,
			 epoch->NumGDOPSkipped,
			 TotalEpochsSkipped,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 options->StationNetworkName,
			 TimeToFirstFix,
			 numEpochsFirstFix,
			 PosProcTime,
			 *ProcTimeLength,
			 (double)(totalprocessingTime)/1.0E6);

		if (options->solutionMode==PPPMode) {
			//sprintf(&messagestr[charPrinted]," Convergence_Time_&_Epochs_Formal_Error_Hor: %.6g %d Convergence_Time_&_Epochs_Period_Formal_Error_Hor: %.6g %d Convergence_Time_&_Epochs_Position_Error_Hor: %.6g %d Convergence_Time_&_Epochs_Period_Position_Error_Hor: %.6g %d Convergence_Time_&_Epochs_Formal_Error_Ver: %.6g %d Convergence_Time_&_Epochs_Period_Formal_Error_Ver: %.6g %d Convergence_Time_&_Epochs_Position_Error_Ver: %.6g %d Convergence_Time_&_Epochs_Period_Position_Error_Ver: %.6g %d Convergence_Time_&_Epochs_Formal_Error_3D: %.6g %d Convergence_Time_&_Epochs_Period_Formal_Error_3D: %.6g %d Convergence_Time_&_Epochs_Position_Error_3D: %.6g %d Convergence_Time_&_Epochs_Period_Position_Error_3D: %.6g %d\n",
			sprintf(&messagestr[charPrinted]," (134)_Convergence_Time_&_Epochs_Formal_Error_Hor: %.6g %d (137)_Convergence_Time_&_Epochs_Period_Formal_Error_Hor: %.6g %d (140)_Convergence_Time_&_Epochs_Position_Error_Hor: %.6g %d (143)_Convergence_Time_&_Epochs_Period_Position_Error_Hor: %.6g %d (146)_Convergence_Time_&_Epochs_Formal_Error_Ver: %.6g %d (149)_Convergence_Time_&_Epochs_Period_Formal_Error_Ver: %.6g %d (152)_Convergence_Time_&_Epochs_Position_Error_Ver: %.6g %d (155)_Convergence_Time_&_Epochs_Period_Position_Error_Ver: %.6g %d (158)_Convergence_Time_&_Epochs_Formal_Error_3D: %.6g %d (161)_Convergence_Time_&_Epochs_Period_Formal_Error_3D: %.6g %d (164)_Convergence_Time_&_Epochs_Position_Error_3D: %.6g %d (167)_Convergence_Time_&_Epochs_Period_Position_Error_3D: %.6g %d\n",
			 ConvTimeFormalErrorHor,
			 numEpochsConvTimeFormalErrorHor,
			 ConvTimePeriodFormalErrorHor,
			 numEpochsConvTimePeriodFormalErrorHor,
			 ConvTimePosErrorHor,
			 numEpochsConvTimePosErrorHor,
			 ConvTimePeriodPosErrorHor,
			 numEpochsConvTimePeriodPosErrorHor,
			 ConvTimeFormalErrorVer,
			 numEpochsConvTimeFormalErrorVer,
			 ConvTimePeriodFormalErrorVer,
			 numEpochsConvTimePeriodFormalErrorVer,
			 ConvTimePosErrorVer,
			 numEpochsConvTimePosErrorVer,
			 ConvTimePeriodPosErrorVer,
			 numEpochsConvTimePeriodPosErrorVer,
			 ConvTimeFormalError3D,
			 numEpochsConvTimeFormalError3D,
			 ConvTimePeriodFormalError3D,
			 numEpochsConvTimePeriodFormalError3D,
			 ConvTimePosError3D,
			 numEpochsConvTimePosError3D,
			 ConvTimePeriodPosError3D,
			 numEpochsConvTimePeriodPosError3D);
		} else {
			sprintf(&messagestr[charPrinted]," \n");
		}
	} else {
		sprintf(messagestr,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f Avail%%: %7.3f PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s\n",
			 receiverid,
			 epoch->receiver.aproxPositionNEU[1]*r2d,
			 epoch->receiver.aproxPositionNEU[0]*r2d,
			 epoch->receiver.aproxPositionNEU[2],
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HPEPercentileSamples,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VPEPercentileSamples,
			 epoch->MaxHError,
			 epoch->MaxVError,
			 SolPercentage,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->PDOPPercentileSamples,
			 epoch->MaxPDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->GDOPPercentileSamples,
			 epoch->MaxGDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->TDOPPercentileSamples,
			 epoch->MaxTDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->HDOPPercentileSamples,
			 epoch->MaxHDOP,
			 PercentileDigits,
			 PercentileDecimals,
			 options->percentile,
			 epoch->VDOPPercentileSamples,
			 epoch->MaxVDOP,
			 NumEpochsDataGapSummary,
			 NumEpochsMissingFile,
			 epoch->NumDataGapsSum,
			 epoch->NumDataGapsTotal,
			 epoch->MaxDataGapSizeSum,
			 epoch->MaxDataGapSizeTotal,
			 options->StationNetworkName);
	}
}


/*****************************************************************************
 * Name        : printDates
 * Description : print dates in all formats (date conversion only)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int year                        I  N/A  Current year
 * int month                       I  N/A  Current month number
 * int day                         I  N/A  Current day number
 * int hour                        I  N/A  Current hour
 * int minute                      I  N/A  Current minute
 * double seconds                  I  N/A  Current second
 * int DoY                         I  N/A  Current day of year
 * double SoD                      I  N/A  Current Second of day
 * int GPSweek                     I  N/A  Current GPS week
 * int DoW                         I  N/A  Current day of week
 * double SoW                      I  N/A  Current second of week
 * int MJDN                        I  N/A  Current Modified Julian Day
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printDates(int year, int month, int day, int hour, int minute, double seconds, int DoY, double SoD, int GPSweek, int DoW, double SoW, int MJDNVal, TOptions  *options) {

	//The +0.00005 is to avoid problems when rounding to integer
	fprintf(options->outFileStream,"Calendar Date (DD/MM/YYYY HH:MM:SS.zzz): %02d/%02d/%4d %02d:%02d:%02d.%03d\n\n",day,month,year,hour,minute,(int)(seconds+.00005),(int)((seconds-((double)((int)seconds)))*1000.+0.00005));
	fprintf(options->outFileStream,"Year:    %6d DoY: %3d SoD: %9.3f\n\n",year,DoY,SoD);
	fprintf(options->outFileStream,"GPSWeek: %6d DoW: %3d SoW: %10.3f\n\n",GPSweek,DoW,SoW);
	fprintf(options->outFileStream,"MJDN:    %6d SoD: %9.3f\n",MJDNVal,SoD);
}



/*****************************************************************************
 * Name        : printCoordinates
 * Description : print coordinates in all systems (coordinate conversion only)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *positionXYZ            O  m    Station position in XYZ
 * double  *positionNEU            O  rd/m Station position in NEU
 *                                         0=>N(Lat)  1=>E(Lon)   2=>U
 * double  *positionSph            I  rd/m Station position in Spherical
 *                                         0=>Latitude  1=>Longitude   2=>Radius
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printCoordinates(double *positionXYZ, double *positionNEU, double *positionSph, TOptions  *options) {

	fprintf(options->outFileStream,"Cartesian: X:         %15.4f Y:        %14.4f Z:      %14.4f\n\n",positionXYZ[0],positionXYZ[1],positionXYZ[2]);
	fprintf(options->outFileStream,"Geodetic:  Longitude: %15.10f Latitude: %14.10f Height: %14.4f\n\n",positionNEU[1]*r2d,positionNEU[0]*r2d,positionNEU[2]);
	fprintf(options->outFileStream,"Spherical: Longitude: %15.10f Latitude: %14.10f Radius: %14.4f\n",positionSph[1]*r2d,positionSph[0]*r2d,positionSph[2]);
}

/*****************************************************************************
 * Name        : computeProcessingTime
 * Description : Compute and print processing time
 * Parameters  :
 * Name                                       |Da|Unit|Description
 * long long unsigned int StartTimeRealPCTime  I  N/A  Program start time in number of 
 *                                                      microseconds since 1 January 1970 
 * long long unsigned int *totalprocessingTime 0  s    Total number of seconds of processing time                                                    
 * int printProcTime                           I  N/A  0 -> Do not print processing time
 *                                                     1 -> Print processing time
 * TOptions  *options                          I  N/A  TOptions structure
 *****************************************************************************/
void computeProcessingTime (long long unsigned int StartTimeRealPCTime, long long unsigned int *totalprocessingTime, int printProcTime, TOptions *options) {
	
	long long unsigned int		processingTimeUser,processingTimeKernel,hoursPassed,minutesPassed,secondsPassed;
	long long unsigned int		EndTimeRealPCTime,WallTimeProcessingTime;

	#if defined __WIN32__ 
		FILETIME 				ProcCreationTime,ProcEndTime, ProcKernelTime, ProcUserTime;
		FILETIME 				WinStartTimeRealPCTime,WinEndTimeRealPCTime;
	#else
		struct timeval 			POSIXEndTimeRealPCTime;
		struct rusage 			rUsage;
	#endif

	#if defined _OPENMP
		double					PercentagePer1;
	#endif

	#if defined __WIN32__
		//Get PC real timestamp
		GetSystemTimeAsFileTime(&WinEndTimeRealPCTime);
		//Get process time
		GetProcessTimes(GetCurrentProcess(),&ProcCreationTime,&ProcEndTime, &ProcKernelTime, &ProcUserTime);
		//The structure FILETIME provides the value in number of 100 nanoseconds or 0.1 microseconds in a 64 bit number splitted in two 32 bit variables
		//dwHighDateTime of FILETIME structure has the upper 32 bits and dwLowDateTime have the lower 32 bits
		//To add them toguether in a 64 bit unsigned integer, convert the upper 32 bits to a 64 bits unsigned integer and shift them 32 bits, so they occupy the upper 32 bits on the 64 bit integer.
		//Then, make an OR operation of the latter value with the lower 32 bits, so we have the 64 bit integer with the upper and lower values
		EndTimeRealPCTime=((long long unsigned int)(WinEndTimeRealPCTime.dwHighDateTime)<< 32) | WinEndTimeRealPCTime.dwLowDateTime;
		//Convert from Windows start epoch to Linux start epoch (1st January 1601 to 1st January 1970)
		EndTimeRealPCTime-=(long long unsigned int)(116444736000000000);
		//As Linux timestamps are in microseconds and windows timestamps are in 0.1 microseconds, divide by 10 so precision in Windows matches the one in Linux
		EndTimeRealPCTime/=10;
		//Repeat process with data from GetProcessTimes
		processingTimeUser=((long long unsigned int)(ProcUserTime.dwHighDateTime)<< 32) | ProcUserTime.dwLowDateTime;
		processingTimeKernel=((long long unsigned int)(ProcKernelTime.dwHighDateTime)<< 32) | ProcKernelTime.dwLowDateTime;
		//As Linux timestamps are in microseconds and windows timestamps are in 0.1 microseconds, divide by 10 so precision in Windows matches the one in Linux
		processingTimeUser/=10;
		processingTimeKernel/=10;
	#else
		//Get PC real timestamp
		gettimeofday(&POSIXEndTimeRealPCTime, NULL);
		EndTimeRealPCTime=(long long unsigned int)(POSIXEndTimeRealPCTime.tv_sec)*(long long unsigned int)(1E6) + (long long unsigned int)(POSIXEndTimeRealPCTime.tv_usec);
		//Get process time
		getrusage(RUSAGE_SELF,&rUsage);
		//rUsage structure provided time in seconds and microseconds in two different variables. 
		//To sum them in a single integer variable, convert the seconds to microseconds and then add the two terms toguether
		processingTimeUser=(long long unsigned int)(rUsage.ru_utime.tv_sec)*(long long unsigned int)(1E6)+(long long unsigned int)(rUsage.ru_utime.tv_usec);
		processingTimeKernel=(long long unsigned int)(rUsage.ru_stime.tv_sec)*(long long unsigned int)(1E6)+(long long unsigned int)(rUsage.ru_stime.tv_usec);
	#endif

	WallTimeProcessingTime=EndTimeRealPCTime-StartTimeRealPCTime; 	//Processing time by comparing real ellapsed time
	*totalprocessingTime=processingTimeUser+processingTimeKernel;	//Processing time counted by process (which has time added up from all threads)

	#if defined _OPENMP
		if (*totalprocessingTime>WallTimeProcessingTime) {
			//totalprocessingTime can be greater than WallTimeProcessingTime due to multiple threads running in parallel have their time added to the total time.
			//In this case, use the percentages of time computed from totalprocessingTime, but use the processing time from WallTimeProcessingTime.
			//This is done to avoid printing processing times larger than the real (human perceived) ellapsed time, which in practice, is useless
			PercentagePer1=(double)(processingTimeUser)/((double)(*totalprocessingTime));
			processingTimeUser=(long long unsigned int)((double)(WallTimeProcessingTime)*PercentagePer1);
			processingTimeKernel=(long long unsigned int)((double)(WallTimeProcessingTime)*(1.-PercentagePer1));
			*totalprocessingTime=WallTimeProcessingTime;
		}
	#else
		WallTimeProcessingTime+=1; //To avoid warning variable set but not used
	#endif
	if (printProcTime==1) {
		if (*totalprocessingTime<(long long unsigned int)(60*1E6)) {
			//Less than 1 minute of processing time
			fprintf(options->outFileStream,"INFO Total Processing time: %.3f second%s [User time: %.3f seconds (%.3f%%) Kernel time: %.3f seconds (%.3f%%)]\n", (double)(*totalprocessingTime)/1.0E6,*totalprocessingTime==1?"":"s",(double)(processingTimeUser)/1.0E6,100.*(double)(processingTimeUser)/((double)(*totalprocessingTime)),(double)(processingTimeKernel)/1.0E6,100.0*(double)(processingTimeKernel)/((double)(*totalprocessingTime)));
		} else if (*totalprocessingTime<(long long unsigned int)(60*60*1E6)) {
			//Less than 1 hour of processing time
			minutesPassed=(long long unsigned int)(((double)*totalprocessingTime)/(60.0*1.0E6));
			secondsPassed=*totalprocessingTime-minutesPassed*(long long unsigned int)(60*1E6);
			fprintf(options->outFileStream,"INFO Total Processing time: %llu minute%s and %.3f second%s (%.3f seconds) [User time: %.3f seconds (%.3f%%) Kernel time: %.3f seconds (%.3f%%)]\n",minutesPassed,minutesPassed==1?"":"s",(double)(secondsPassed)/1.0E6,secondsPassed==1?"":"s",(double)(*totalprocessingTime)/1.0E6,(double)(processingTimeUser)/1.0E6,100.*(double)(processingTimeUser)/((double)(*totalprocessingTime)),(double)(processingTimeKernel)/1.0E6,100.0*(double)(processingTimeKernel)/((double)(*totalprocessingTime)));
		} else {
			//1 hour or more of processing time
			hoursPassed=(long long unsigned int)(((double)*totalprocessingTime)/(60.0*60.0*1.0E6));
			minutesPassed=(long long unsigned int)(((double)(*totalprocessingTime-hoursPassed*(long long unsigned int)(60*60*1E6)))/(60.0*1.0E6));
			secondsPassed=*totalprocessingTime-hoursPassed*(long long unsigned int)(60*60*1E6)-minutesPassed*(long long unsigned int)(60*1E6);
			fprintf(options->outFileStream,"INFO Total Processing time: %llu hour%s %llu minute%s and %.3f second%s (%.3f seconds) [User time: %.3f seconds (%.3f%%) Kernel time: %.3f seconds (%.3f%%)]\n",hoursPassed,hoursPassed==1?"":"s",minutesPassed,minutesPassed==1?"":"s",(double)(secondsPassed)/1.0E6,secondsPassed==1?"":"s",(double)(*totalprocessingTime)/1.0E6,(double)(processingTimeUser)/1.0E6,100.*(double)(processingTimeUser)/((double)(*totalprocessingTime)),(double)(processingTimeKernel)/1.0E6,100.0*(double)(processingTimeKernel)/((double)(*totalprocessingTime)));
		}
	}
}
