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
 * File: output.c
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
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
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "input.h"
#include "output.h"
#include <ctype.h>

// Global variables for printing MODEL buffer
char	printbufferMODEL[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASCORR buffer
char	printbufferSBASCORR[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASVAR buffer
char	printbufferSBASVAR[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASIONO buffer
char	printbufferSBASIONO[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing MODEL buffer
char	printbufferSBASUNSEL[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing DGNSS buffer
char	printbufferDGNSS[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SATSEL buffer
int		linesstoredSATSEL[MAX_SATELLITES_VIEWED];
char	printbufferSATSEL[MAX_SATELLITES_VIEWED][MAX_LINES_BUFFERED][MAX_INPUT_LINE];

// Global variables for printing PREFIT buffer
char	printbufferPREFIT[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing POSTFIT buffer
char	printbufferPOSTFIT[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing EPOCHSAT buffer
char	printbufferEPOCHSAT[MAX_INPUT_LINE];

// Global variables for printing FILTER buffer
char	printbufferFILTER[MAX_INPUT_LINE];

//Import global variable printProgress
extern int printProgress;

/**************************************
 * Declarations of internal operations
 **************************************/

/*****************************************************************************
 * Name        : printParameters
 * Description : Print Input parameters
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              I  N/A  TOptions structure
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * char *stdesaFile                I  N/A  Filename for Stanford-ESA plot
 * char *stdesaFileLOI             I  N/A  Filename for Stanford-ESA values
 * char *kmlFile                   I  N/A  Filename for KML file
 * char *kml0File                  I  N/A  Filename for KML0 file
 * char *sp3File                   I  N/A  Filename for SP3 file
 * char *RefFile                   I  N/A  Filename for Reference file
 *****************************************************************************/
void printParameters (TOptions *options, TEpoch *epoch, TGNSSproducts *products, char *stdesaFile, char *stdesaFileLOI, char *kmlFile, char *kml0File, char *sp3File, char *RefFile) {
	int					i, j, k, l, m;
	int					aux;
	int					numsat[MAX_GNSS];
	int					SNRWeightused[MAX_FILTER_MEASUREMENTS];
	double				**prevValuesSNR;
	double				**prevValuesSNRComb;
	static int			listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};
	double				**prevValuesWeight;
	char				auxstr[900],auxstrWeight[200];
	char				satlist[MAX_GNSS][MAX_SATELLITES_PER_GNSS*50];
	char				satlistaux[MAX_SATELLITES_PER_GNSS*50];
	TRangeList 			List;
	
	if (!options->printInfo) return;
	
	if (strcmp(epoch->receiver.name,DEFAULTMARKERNAME)==0) {
		strcpy(auxstr,"Unknown");
	} else {
		strcpy(auxstr,epoch->receiver.name);
	}
	#if defined _OPENMP
		fprintf(options->outFileStream,"INFO Number of threads used: %d\n",options->numthreads);
	#endif

	if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
		fprintf(options->outFileStream,"INFO SBAS processing mode activated\n");
	}

	fprintf(options->outFileStream,"INFO INPUT Station marker: %s\n",auxstr);
	if (epoch->receiver.antenna.type[0] == '\0') {
		strcpy(auxstr,"Unknown");
	} else {
		strcpy(auxstr,epoch->receiver.antenna.type);
	}
	fprintf(options->outFileStream,"INFO INPUT Antenna type:   %s\n",auxstr);
	if (epoch->receiver.type[0] == '\0') {
		fprintf(options->outFileStream,"INFO INPUT Receiver type:  0-Unknown\n");
	} else {
		if (epoch->receiver.recType == rtCROSS) strcpy(auxstr,"1-Cross-correlated");
		else if (epoch->receiver.recType == rtNOP1) strcpy(auxstr,"2-No P1");
		else if (epoch->receiver.recType == rtNOMINAL) strcpy(auxstr,"3-Consistent measurements");
		else strcpy(auxstr,"Unknown");
		fprintf(options->outFileStream,"INFO INPUT Receiver type:  %s [%s]\n",epoch->receiver.type,auxstr);
	}
	fprintf(options->outFileStream,"INFO PREPROCESSING Prealign carrier phase measurements: %3s\n",options->prealignCP?"ON":"OFF");
	if (options->decimate>=1. || options->decimate==0.) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Decimation %d\n",(int)options->decimate);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Decimation %.7f\n",options->decimate);
	}
	aux = 0;
	for (i=0;i<MAX_GNSS;i++) {
		if(i>GPS) break;
		numsat[i]=0;
		satlist[i][0]='\0';
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			if (options->includeSatellite[i][j]==0) {
				aux++;
				if (aux==1) {
					fprintf(options->outFileStream,"INFO PREPROCESSING Excluding satellites:");
				}
				sprintf(satlistaux,"%s %c%02d",satlist[i],gnsstype2char(i),j);
				sprintf(satlist[i],"%s",satlistaux);
				numsat[i]++;
			}
		}
		if(numsat[i]==MAX_SATELLITES_PER_GNSS) {
			sprintf(satlist[i]," All %s",gnsstype2gnssstr(i));
		}
		if(numsat[i]>0) {
			fprintf(options->outFileStream,"%s",satlist[i]);
		}
	}
	if (aux) fprintf(options->outFileStream,"\n");
	if (options->SBAScorrections == 1) {
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
	fprintf(options->outFileStream,"INFO PREPROCESSING Usable frequencies [GPS]:");
	if (options->usableFreq[GPS][1]) fprintf(options->outFileStream," F%1d",1);
	if (options->usableFreq[GPS][2]) fprintf(options->outFileStream," F%1d",2);
	if (options->usableFreq[GPS][5]) fprintf(options->outFileStream," F%1d",5);
	
	fprintf(options->outFileStream,"\n");
	fprintf(options->outFileStream,"INFO PREPROCESSING Elevation mask: %.2f\n",options->elevationMask/d2r);
	fprintf(options->outFileStream,"INFO PREPROCESSING Discard satellites under eclipse conditions: %3s\n",options->discardEclipsedSatellites?"YES":"NO");
	if ( options->receiverPositionSource == rpSETREF) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position: [Position from reference file, used for modelling and for dXYZ, dNEU");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position: %14.4f %14.4f %14.4f  [",epoch->receiver.aproxPosition[0],epoch->receiver.aproxPosition[1],epoch->receiver.aproxPosition[2]);
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
	else if (options->receiverPositionSource == rpRTCMbaseline || options->receiverPositionSource == rpRTCMUserbaseline) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ, dNEU compared with reference station");
	else if (options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ, dNEU compared with RINEX Rover position");
	else if (options->receiverPositionSource == rpRTCMRoverUSER || options->receiverPositionSource == rpRTCMRefRoverUSER ) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ, dNEU compared with user defined position");
	else if (options->receiverPositionSource == rpRTCMRoverUSERREF || options->receiverPositionSource == rpRTCMRefUSERRoverREF ) fprintf(options->outFileStream,"TO_BE_CALCULATED, dXYZ, dNEU compared with position from reference file");
	fprintf(options->outFileStream,"]\n");
	if ( options->receiverPositionSource == rpRTCMRoverUSER || options->receiverPositionSource == rpRTCMRefRoverUSER ) {
		if (options->aprioriReceiverPositionGeod[2]!=-999999) {
			//User has given geodetic coordinates
			fprintf(options->outFileStream,"INFO PREPROCESSING Receiver a priori position (Geodetic Lon[º],Lat[º],Height[m]): %14.10f %15.10f %14.4f\n",options->aprioriReceiverPositionGeod[1]*r2d,options->aprioriReceiverPositionGeod[0]*r2d,options->aprioriReceiverPositionGeod[2]);
		}
		fprintf(options->outFileStream,"INFO PREPROCESSING User defined position for computing dXYZ, dNEU: %14.4f %14.4f %14.4f\n",options->aprioriReceiverPosition[0],options->aprioriReceiverPosition[1],options->aprioriReceiverPosition[2]);
	} else if ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) {
		fprintf(options->outFileStream,"INFO PREPROCESSING RINEX position for computing dXYZ, dNEU: %14.4f %14.4f %14.4f\n",epoch->receiver.aproxPositionRover[0],epoch->receiver.aproxPositionRover[1],epoch->receiver.aproxPositionRover[2]);
	}
	if ( options->receiverPositionSource >= rpRTCMUserbaseline) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Reference station user defined position: %14.4f %14.4f %14.4f\n",options->ReferenceStationPosition[0],options->ReferenceStationPosition[1],options->ReferenceStationPosition[2]);
		if (options->ReferenceStationPositionGeod[2]!=-999999) {
			//User has given geodetic coordinates
			fprintf(options->outFileStream,"INFO PREPROCESSING Reference station user defined position (Geodetic Lon[º],Lat[º],Height[m]): %14.10f %15.10f %14.4f\n",options->ReferenceStationPositionGeod[1]*r2d,options->ReferenceStationPositionGeod[0]*r2d,options->ReferenceStationPositionGeod[2]);
		}
	}
	if (options->csNcon ) {
		fprintf(options->outFileStream,"INFO PREPROCESSING N-consecutive: ON  [Min:%d]\n", -1 * options->csNconMin + 1);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING N-consecutive: OFF\n");
	}
	if (options->csLLI==0 && options->csL1C1==0 && options->csBW==0 && options->csLI==0) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip Data Gap: OFF (all cycle-slip detectors disabled)\n");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip Data Gap: %.1f\n",options->csDataGap);
	}	
	if (options->csLLI) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LLI:   ON\n");
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LLI:   OFF\n");
	}
	if (options->csL1C1) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip L1C1:  ON  [Init:%.3lf  Window:%d  K-factor:%.3lf  Samples:%d]\n",options->csL1C1init,options->csL1C1window,options->csL1C1kfactor,options->csL1C1samples);
		if (options->csUnconsistencyCheck) {
			fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip L1C1 Unconsistency check threshold: %.2f\n",options->csUnconsistencyCheckThreshold);
		} else {
			fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip L1C1 Unconsistency check: OFF\n");
		}
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip L1C1:  OFF\n");
	}
	if (options->csBW) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip BW:    ON  [SigMin:%.3lf  Window:%.d  K-factor:%.3lf  Samples:%d]\n",options->csBWmin,options->csBWwindow,options->csBWkfactor,options->csBWsamples);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip BW:    OFF\n");
	}
	if (options->csLI) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LI:    ON  [MaxJump:%.3lf  Max:%.3lf  To:%.3lf  Samples:%d]\n",options->csLImaxjump,options->csLImax,options->csLIt,options->csLIsamples);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING Cycle-slip LI:    OFF\n");
	}
	if (epoch->receiver.recType == rtNOP1) {
		fprintf(options->outFileStream,"INFO PREPROCESSING Receiver type does not provide P1... I will use C1 instead of P1\n"); 
	}


	if(options->SNRfilter == 1) {
		l=0;
		InitRangeList(&List);
		prevValuesSNR=NULL;
		prevValuesSNR=malloc(sizeof(double*));
		prevValuesSNR[0]=NULL;
		prevValuesSNR[0]=malloc(sizeof(double));
		//Initialize previous values with the data of the first satellite to be read
		prevValuesSNR[0][0]=options->SNRvalues[0][1];
		for(i=0;i<MAX_GNSS;i++) {
			if(i>GPS) break;
			for(j=1;j<MAX_SATELLITES_PER_GNSS;j++) {
				if (j>listMaxSatGNSS[i]) break;
				if (options->SNRvalues[i][j]!=prevValuesSNR[l][0]) {
					//Values are different. Look if these values were already saved before
					for(m=0;m<List.size;m++) {
						if (prevValuesSNR[m][0]==options->SNRvalues[i][j]) {
							//Values already saved. Extend the list
							break;
						}
					}
					if (m==List.size) {
						//Block not found. New weight values or weight type
						AddRangeList(i,j,&List);
						prevValuesSNR=realloc(prevValuesSNR,sizeof(double*)*List.size);
						prevValuesSNR[m]=NULL;
						prevValuesSNR[m]=malloc(sizeof(double));
						prevValuesSNR[m][0]=options->SNRvalues[i][j];
					} else {
						//Block found (SNR was already read before). Extend the list with the new start of range
						ExtendRangeList(i,j,m,&List);
					}
					//Save the end of the range
					if(j==1) {
						//PRN 1 of new constellation
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
					} else {
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
					}
					//Save the index of the last type of block we are using to compare
					l=m;
				}
			}
		}
		//Print all the different blocks found
		//fprintf(options->outFileStream,"INFO PREPROCESSING SNR Mask (dBHz):");
		for(l=0;l<List.size;l++) {
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Print INFO line with the list of satellites
			//fprintf(options->outFileStream," %s: %.6g",auxstr,prevValuesSNR[l][0]);
			fprintf(options->outFileStream,"INFO PREPROCESSING SNR Mask (dBHz): %s: %.6g\n",auxstr,prevValuesSNR[l][0]);
			free(prevValuesSNR[l]);
			prevValuesSNR[l]=NULL;
		}
		//fprintf(options->outFileStream,"\n");
		free(prevValuesSNR);
		freeRangeList(&List);
	} else {
		fprintf(options->outFileStream,"INFO PREPROCESSING SNR Mask: OFF\n");
	}

	fprintf(options->outFileStream,"INFO MODELLING Satellite clock offset correction: %3s\n",options->satelliteClockCorrection?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Consider satellite movement during signal flight time: %3s\n",options->timeTrans?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Consider Earth rotation during signal flight time: %3s\n",options->earthRotation?"ON":"OFF");
	for (i=1;i<3;i++)
		fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Phase Center Offset (PCO): F%1d %8.5f %8.5f %8.5f\n",i,epoch->receiver.antenna.PCO[GPS][i][0],epoch->receiver.antenna.PCO[GPS][i][1],epoch->receiver.antenna.PCO[GPS][i][2]);
	fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Phase Center variation correction: %3s\n",options->receiverPhaseVar?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Satellite mass centre to Antenna Phase Centre (APC) correction: %3s\n",options->satellitePhaseCenter?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Satellite mass centre to Antenna Phase Centre variation correction:  %3s\n",options->satellitePhaseVar?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Receiver Antenna Reference Point (ARP): %7.4f %7.4f %7.4f\n",epoch->receiver.ARP[0],epoch->receiver.ARP[1],epoch->receiver.ARP[2]);
	fprintf(options->outFileStream,"INFO MODELLING Relativistic clock correction: %3s\n",options->relativisticCorrection?"ON":"OFF");
	if (options->ionoModel == NoIono) strcpy(auxstr,"OFF");
	else if (options->ionoModel == Klobuchar) strcpy(auxstr,"Klobuchar");
	else if (options->ionoModel == BeiDou) strcpy(auxstr,"BeiDou");
	else if (options->ionoModel == neQuick) strcpy(auxstr,"NeQuick");
	else if (options->ionoModel == IONEX) strcpy(auxstr,"IONEX");
	else if (options->ionoModel == FPPP) strcpy(auxstr,"FPPP");
	else if (options->ionoModel == SBASiono) strcpy(auxstr,"SBAS");
	fprintf(options->outFileStream,"INFO MODELLING Ionosphere model: %s\n",auxstr);
	fprintf(options->outFileStream,"INFO MODELLING Troposphere model: %3s\n",options->troposphericCorrection?"ON":"OFF");
	if (options->troposphericCorrection  == 1) { 
		if (options->tropNominal == SimpleNominal) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Simple Nominal\n");
		else if (options->tropNominal == UNB3Nominal) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: UNB-3 Nominal\n");
		else if (options->tropNominal == TropoGalileo) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Galileo Nominal\n");
		if (options->tropMapping == SimpleMapping) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Simple Mapping\n");
		else if (options->tropMapping == NiellMapping) fprintf(options->outFileStream,"INFO MODELLING Troposphere model: Niell Mapping\n");
	}
	if (options->p1c1dcbModel == p1c1NONE) strcpy(auxstr,"OFF");
	else if (options->p1c1dcbModel == p1c1FLEXIBLE) strcpy(auxstr,"Flexible");
	else if (options->p1c1dcbModel == p1c1STRICT) strcpy(auxstr,"Strict");
	fprintf(options->outFileStream,"INFO MODELLING P1-C1 DCB model: %s\n",auxstr);
	if (options->p1p2dcbModel == p1p2NONE) strcpy(auxstr,"OFF");
	else if (options->p1p2dcbModel == p1p2RINEX) strcpy(auxstr,"RINEX");
	else if (options->p1p2dcbModel == p1p2DCB) strcpy(auxstr,"DCB");
	else if (options->p1p2dcbModel == p1p2IONEX) strcpy(auxstr,"IONEX");
	else if (options->p1p2dcbModel == p1p2FPPP) strcpy(auxstr,"FPPP");
	fprintf(options->outFileStream,"INFO MODELLING P1-P2 DCB model: %s\n",auxstr);
	fprintf(options->outFileStream,"INFO MODELLING Wind up correction: %3s\n",options->windUpCorrection?"ON":"OFF");
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
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all orbit interpolation samples:  %2d (%d seconds)\n",options->OrbitsToTMaxGaps,(int)options->OrbitsToTMaxDistance);
		} else {
			fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all orbit interpolation samples: Unlimited\n");
		}
		if (options->clockInterpolationDegree!=0) {
			if (options->ClocksToTMaxGaps!=0) {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps between clock interpolation samples: %2d (%d seconds)\n",options->ClocksMaxGaps,(int)options->ClocksMaxDistance);
			} else {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps between clock interpolation samples: Unlimited\n");
			}
			if (options->ClocksToTMaxGaps!=0) {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all clock interpolation samples:  %2d (%d seconds)\n",options->ClocksToTMaxGaps,(int)options->ClocksToTMaxDistance);
			} else {
				fprintf(options->outFileStream,"INFO MODELLING Max data gaps in all clock interpolation samples: Unlimited\n");
			}
		}
	}
	fprintf(options->outFileStream,"INFO MODELLING Check transmission time of navigation message is behind current epoch: %s\n",options->brdcBlockTransTime?"ON":"OFF");
	fprintf(options->outFileStream,"INFO MODELLING Use satellite 'SV Health' flag of navigation message: %s\n",options->satelliteHealth?"ON":"OFF");
	if (options->MaxURABroadcast!=9999999.) {
		fprintf(options->outFileStream,"INFO MODELLING Maximum URA value of navigation message: %.1f\n",options->MaxURABroadcast);
	}
	if (options->DGNSS) {
		fprintf(options->outFileStream,"INFO MODELLING Sigma inflation during smoother convergence in DGNSS: %3s\n",options->sigmaInflation?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING Maximum age   for DGNSS corrections: %f\n",options->maxAgeDGNSS);
		fprintf(options->outFileStream,"INFO MODELLING Maximum value for DGNSS corrections: %f\n",options->maxDGNSSPRC);
	}

	if (options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
		if (options->SBASmaritime==1) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS for Maritime enabled\n");
		}
		fprintf(options->outFileStream,"INFO MODELLING SBAS Navigation Mode: %3s\n",options->precisionapproach==PAMODE?"PA":"NPA");
		fprintf(options->outFileStream,"INFO MODELLING SBAS GEO switching: %3s\n",options->switchGEO==1?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING SBAS mode switching: %3s\n",options->switchmode==1?"ON":"OFF");
		fprintf(options->outFileStream,"INFO MODELLING SBAS Ignore MT 0: %3s\n",options->usetype0messages==1?"OFF":"ON");
		fprintf(options->outFileStream,"INFO MODELLING SBAS Read MT 0 as MT 2: %3s\n",options->alarmmessageastype2==1?"ON":"OFF");
		if (options->UDREIthreshold!=999999) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS UDREI threshold for discarding satellites: %d\n",options->UDREIthreshold);
		}
		if (options->switchmode==1 || options->UserForcedNPA==1 || options->NoMT10==1) {
			fprintf(options->outFileStream,"INFO MODELLING SBAS Fast correction sigma offset when MT10 is not used: %.6g (metres)\n",options->SigmaOffsetNoMT10);
		}
		fprintf(options->outFileStream,"INFO MODELLING SBAS GEO acquisiton time: %3d (seconds)\n",options->adquisitiontime);
		fprintf(options->outFileStream,"INFO MODELLING SBAS switching cooltime:  %3d (seconds)\n",options->minimumswitchtime);

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
			if (options->ionoModel!=SBASiono) {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
			} else {
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][18],options->usertmout[0][18]);
			}
			fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout PA: %7d NPA: %7d (seconds)\n",options->usertmout[1][25],options->usertmout[0][25]);
			if (options->ionoModel!=SBASiono) {
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
				if (options->ionoModel!=SBASiono) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout PA: %7d (seconds)\n",options->usertmout[1][18]);
				}
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout PA: %7d (seconds)\n",options->usertmout[1][25]);
				if (options->ionoModel!=SBASiono) {
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
				if (options->ionoModel!=SBASiono) {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       Message disabled\n");
				} else {
					fprintf(options->outFileStream,"INFO MODELLING SBAS MT 18 (Ionospheric Grid Points Mask)       timeout NPA: %7d (seconds)\n",options->usertmout[0][18]);
				}
				fprintf(options->outFileStream,"INFO MODELLING SBAS MT 25 (Long Term Satellite Corrections)    timeout NPA: %7d (seconds)\n",options->usertmout[0][25]);
				if (options->ionoModel!=SBASiono) {
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
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma multipath:  %.6g + %.6g*e^(-elev/%.6g) (metres)\n",options->sigma2multipath[0]==-99999.?0.13:options->sigma2multipath[0],options->sigma2multipath[1]==-99999.?0.53:options->sigma2multipath[1],1./options->sigma2multipath[2]);
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma noise:      %.6g (metres)\n",options->sigma2noise==-1?0.36:sqrt(options->sigma2noise));
			fprintf(options->outFileStream,"INFO MODELLING SBAS Receiver sigma divergence: %.6g (metres)\n",options->sigma2divergence==-1?0:sqrt(options->sigma2divergence));
		}
	}

	//Print weight types and their values
	//A list of satellites for each weight and values is made, so only one line per
	//each weight and value is printed with all the satellites that apply
	for (k=0;k<options->totalFilterMeasurements;k++) {
		SNRWeightused[k]=0;
		prevValuesWeight=NULL;		
		prevValuesWeight=malloc(sizeof(double*));
		prevValuesWeight[0]=NULL;
		prevValuesWeight[0]=malloc(sizeof(double)*6);
		l=0;
		InitRangeList(&List);
		//Initialize previous values with the data of the first satellite to be read
		prevValuesWeight[0][0]=(double)options->weightMode[0][1][k];
		prevValuesWeight[0][1]=options->WeightConstantsValues[0][1][k][0];
		prevValuesWeight[0][2]=options->WeightConstantsValues[0][1][k][1];
		prevValuesWeight[0][3]=options->WeightConstantsValues[0][1][k][2];
		prevValuesWeight[0][4]=0.;
		prevValuesWeight[0][5]=1.;
		for(i=0;i<MAX_GNSS;i++) {
			if(i>GPS) break;
			for(j=1;j<MAX_SATELLITES_PER_GNSS;j++) {
				if (j>listMaxSatGNSS[i]) break;
				//Check if any value is different than the last values read
				if ((double)(options->weightMode[i][j][k])!=prevValuesWeight[l][0] || options->WeightConstantsValues[i][j][k][0]!=prevValuesWeight[l][1] ||
						options->WeightConstantsValues[i][j][k][1]!=prevValuesWeight[l][2] || options->WeightConstantsValues[i][j][k][2]!=prevValuesWeight[l][3]) {

					//Values are different. Look if these values were already saved before
					for(m=0;m<List.size;m++) {
						if ((double)(options->weightMode[i][j][k])==prevValuesWeight[m][0] && options->WeightConstantsValues[i][j][k][0]==prevValuesWeight[m][1] &&
								options->WeightConstantsValues[i][j][k][1]==prevValuesWeight[m][2] && options->WeightConstantsValues[i][j][k][2]==prevValuesWeight[m][3]) {
							//Values already saved. Extend the list
							break;
						}
					}
					if (m==List.size) {
						//Block not found. New weight values or weight type
						AddRangeList(i,j,&List);
						prevValuesWeight=realloc(prevValuesWeight,sizeof(double*)*List.size);
						prevValuesWeight[m]=NULL;
						prevValuesWeight[m]=malloc(sizeof(double)*6);
						prevValuesWeight[m][0]=(double)options->weightMode[i][j][k];
						prevValuesWeight[m][1]=options->WeightConstantsValues[i][j][k][0];
						prevValuesWeight[m][2]=options->WeightConstantsValues[i][j][k][1];
						prevValuesWeight[m][3]=options->WeightConstantsValues[i][j][k][2];
						prevValuesWeight[m][4]=(double)i;
						prevValuesWeight[m][5]=(double)j;
					} else {
						//Block found (weight and values were already read before). Extend the list with the new start of range
						ExtendRangeList(i,j,m,&List);
					}
					//Save the end of the range
					if(j==1) {
						//PRN 1 of new constellation
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
					} else {
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
					}
					//Save the index of the last type of block we are using to compare
					l=m;
				}
			} //End for(j=1;j<MAX_SATELLITES_PER_GNSS;j++)
		} //End for(i=0;i<MAX_GNSS;i++) 

		//Print all the different blocks found
		for(l=0;l<List.size;l++) {
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Print INFO line with the list of satellites
			WeightType2String((int)prevValuesWeight[l][4],(int)prevValuesWeight[l][5],k,&SNRWeightused[k],auxstrWeight,options);
			fprintf(options->outFileStream,"INFO FILTER Measurement: %1d %3s%s: %s",k+1,meastype2measstr(options->measurement[k]),auxstr,auxstrWeight);
			if (options->smoothMeas[k]!=NA) {
				 fprintf(options->outFileStream," SmoothWith: %3s [n=%d]\n",meastype2measstr(options->smoothMeas[k]),options->smoothEpochs);
			} else {
				 fprintf(options->outFileStream,"\n");
			}
			free(prevValuesWeight[l]);
			prevValuesWeight[l]=NULL;
		}
		free(prevValuesWeight);
		freeRangeList(&List);
	}

	//Print SNR selection type for combinations
	for (k=0;k<options->totalFilterMeasurements;k++) {
		if (SNRWeightused[k]==0) continue; //SNR weight not used for this measurement
		if (options->measurement[k]<ENDMEAS || options->measurement[i]==G1C || options->measurement[i]==G1P
				|| options->measurement[i]==G2C || options->measurement[i]==G2P) continue;	//It is a measurement or a graphic combination
		l=0;
		InitRangeList(&List);
		prevValuesSNRComb=NULL;
		prevValuesSNRComb=malloc(sizeof(double*));
		prevValuesSNRComb[0]=NULL;
		prevValuesSNRComb[0]=malloc(sizeof(double)*3);
		//Initialize previous values with the data of the first satellite to be read
		prevValuesSNRComb[0][0]=(double)options->SNRweightComb[0][1][k];
		prevValuesSNRComb[0][1]=options->SNRweightCombVal[0][1][k][0];
		prevValuesSNRComb[0][2]=options->SNRweightCombVal[0][1][k][1];
		for(i=0;i<MAX_GNSS;i++) {
			if(i>GPS) break;
			for(j=1;j<MAX_SATELLITES_PER_GNSS;j++) {
				if (j>listMaxSatGNSS[i]) break;
				if ((double)options->SNRweightComb[i][j][k]!=prevValuesSNRComb[l][0] || options->SNRweightCombVal[i][j][k][0]!=prevValuesSNRComb[l][1]
						|| options->SNRweightCombVal[i][j][k][1]!=prevValuesSNRComb[l][2]) {
					//Values are different. Look if these values were already saved before
					for(m=0;m<List.size;m++) {
						if (prevValuesSNRComb[m][0]==(double)options->SNRweightComb[i][j][k] && prevValuesSNRComb[m][1]==options->SNRweightCombVal[i][j][k][0]
								&& prevValuesSNRComb[m][2]==options->SNRweightCombVal[0][1][k][1]) {
							//Values already saved. Extend the list
							break;
						}
					}
					if (m==List.size) {
						//Block not found. New weight values or weight type
						AddRangeList(i,j,&List);
						prevValuesSNRComb=realloc(prevValuesSNRComb,sizeof(double*)*List.size);
						prevValuesSNRComb[m]=NULL;
						prevValuesSNRComb[m]=malloc(sizeof(double)*3);
						prevValuesSNRComb[m][0]=(double)options->SNRweightComb[i][j][k];
						prevValuesSNRComb[m][1]=options->SNRweightCombVal[i][j][k][0];
						prevValuesSNRComb[m][2]=options->SNRweightCombVal[i][j][k][1];
					} else {
						//Block found (weight and values were already read before). Extend the list with the new start of range
						ExtendRangeList(i,j,m,&List);
					}
					//Save the end of the range
					if(j==1) {
						//PRN 1 of new constellation
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i-1;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=listMaxSatGNSS[i-1];
					} else {
						List.listSatGNSS[l][List.numJumpslist[l]-1][1]=i;
						List.listSatPRN[l][List.numJumpslist[l]-1][1]=j-1;
					}
					//Save the index of the last type of block we are using to compare
					l=m;
				}
			}
		}
		//Print all the different blocks found
		for(l=0;l<List.size;l++) {
			//Create the list of satellites per block
			SatRangeList2String(l,&List,auxstr);
			//Print INFO line with the list of satellites
			fprintf(options->outFileStream,"INFO FILTER SNR selection for %s combination: %s: %s\n",meastype2measstr(options->measurement[k]),auxstr,SNRCombModeNum2String((int)prevValuesSNRComb[l][0],prevValuesSNRComb[l][1],prevValuesSNRComb[l][2]));
			free(prevValuesSNRComb[l]);
			prevValuesSNRComb[l]=NULL;
		}
		free(prevValuesSNRComb);
		freeRangeList(&List);
	}

	fprintf(options->outFileStream,"INFO FILTER Number of seconds of continuous code smoothing before steady-state operation: %d\n",options->excludeSmoothingConvergence);
	if (options->stepdetector == 1) {
		fprintf(options->outFileStream,"INFO FILTER Step detector for jumps in navigation message enabled\n");
	}
	if (options->prefitOutlierDetectorAbs == 1) {
		fprintf(options->outFileStream,"INFO FILTER Absolute value prefit outlier detector threshold: %.2f\n",options->prefitOutlierDetectorAbsThreshold);
	}
	if (options->prefitOutlierDetectorMedian == 1) {
		fprintf(options->outFileStream,"INFO FILTER Median prefit outlier detector threshold: %.2f\n",options->prefitOutlierDetectorMedianThreshold);
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
	fprintf(options->outFileStream,"INFO FILTER Estimate troposphere: %3s\n",options->estimateTroposphere?"ON":"OFF");
	fprintf(options->outFileStream,"INFO FILTER %s Processing\n",(options->filterIterations==1)?"Forward":"Backward"); 
	for (i=0;i<MAX_PAR;i++) {
		if (i==DR_UNK) strcpy (auxstr,"Position:");
		else if (i==DT_UNK) strcpy (auxstr,"Clock:");
		else if (i==TROP_UNK) strcpy (auxstr,"Troposphere:");
		else if (i==BIAS_UNK) strcpy (auxstr,"Ambiguity:"); 
		fprintf(options->outFileStream,"INFO FILTER Parameters [Phi,Q,P0] %-14s",auxstr);
		for (j=0;j<3;j++) {
				fprintf(options->outFileStream," %9.2e",options->filterParams[j][i]);
		}
		fprintf(options->outFileStream,"\n");
	}
	if (options->SBAScorrections == 0) {
		if ( options->ionoModel == IONEX || options->ionoModel == FPPP || options->ionoModel == SBASiono) {
				fprintf(options->outFileStream,"INFO FILTER Use ionosphere sigma: %-3s\n",options->useSigmaIono?"ON":"OFF");
			}
	}
	if ( options->stanfordesa == 1 ) {
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
	fprintf(options->outFileStream,"INFO PRINT SBASUNUSED:      %-3s\n",options->printSBASUNUSED?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT DGNSS:           %-3s\n",options->printDGNSS?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT DGNSSUNSED:      %-3s\n",options->printDGNSSUNUSED?"ON":"OFF");
	fprintf(options->outFileStream,"INFO PRINT SUMMARY:         %-3s\n",options->printSummary?"ON":"OFF");
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
		//Enable cursor 
		if (printProgress==1 && options->ProgressEndCharac=='\r') {
			fprintf(options->terminalStream,"\033[?25h");
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
	int		i,j,k;
	double	measurements[10];
	int		res[10];
	double	correction1;
	int		retDCB,retDCBC1P1;
	
	if (options->printInput) {
		for (i=0;i<epoch->numSatellites;i++) {
			k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			fprintf(options->outFileStream,"INPUT     %17s %3s %2d %6d",t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,epoch->cycleslip.arcLength[k]==0 ? 1:epoch->cycleslip.arcLength[k]);
			if (epoch->sat[i].GNSS == GPS) {
				res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1C,&measurements[0],NULL);
				res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1P,&measurements[1],NULL);
				res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C2P,&measurements[2],NULL);
				res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L1P,&measurements[3],NULL);
				res[4] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L2P,&measurements[4],NULL);
				if (tgdData->p1c1dcbModel == p1c1STRICT) {
					getTGDfromDCB(tgdData, &epoch->receiver, epoch->sat[i].GNSS, epoch->sat[i].PRN,&epoch->t, C1C, C1P, &correction1, &retDCB, &retDCBC1P1);
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
					if (measurements[j] ==-1 || res[j]==0) measurements[j] = 0;
					fprintf(options->outFileStream," %14.4f",measurements[j]);
				}
			} else if (epoch->sat[i].GNSS == Galileo) {
				res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1A,&measurements[0],NULL);
				res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1B,&measurements[1],NULL);
				res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1C,&measurements[2],NULL);
				res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C7Q,&measurements[3],NULL);
				res[4] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C8Q,&measurements[4],NULL);
				res[5] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L1A,&measurements[5],NULL);
				res[6] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L1B,&measurements[6],NULL);
				res[7] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L1C,&measurements[7],NULL);
				res[8] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L7Q,&measurements[8],NULL);
				res[9] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L8Q,&measurements[9],NULL);
				for (j=0;j<10;j++) {
					if (measurements[j] ==-1 || res[j]==0) measurements[j] = 0;
					fprintf(options->outFileStream," %14.4f",measurements[j]);
				}
			} else if (epoch->sat[i].GNSS == GLONASS) {
				res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1C,&measurements[0],NULL);
				res[1] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C2C,&measurements[1],NULL);
				res[2] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L1P,&measurements[2],NULL);
				res[3] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,L2P,&measurements[3],NULL);
				for (j=0;j<4;j++) {
					if (measurements[j] ==-1 || res[j]==0) measurements[j] = 0;
					fprintf(options->outFileStream," %14.4f",measurements[j]);
				}
			} else if (epoch->sat[i].GNSS == GEO) {
				res[0] = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,C1C,&measurements[0],NULL);
				for (j=0;j<1;j++) {
					if (measurements[j] ==-1 || res[j]==0) measurements[j] = 0;
					fprintf(options->outFileStream," %14.4f",measurements[j]);
				}
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
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void printMeas (TEpoch *epoch, TTGDdata *tgdData, TOptions *options) {
	int						i,j,k;
	int						n[MAX_GNSS];
	int						maxN = 0;
	char					measStr[MAX_GNSS][MAX_MEASUREMENTS_PER_SATELLITE*2*3+1];
	int						len;
	enum MeasurementType	measChain[MAX_GNSS][MAX_MEASUREMENTS_PER_SATELLITE*2];
	double					measVal;
	char					mS[2][4];
	int						res;
	double					correction1;
	int						retDCB,retDCBC1P1;
	
	if (options->printMeas) {
		for (i=0;i<MAX_GNSS;i++) {
			n[i] = 0;
			measStr[i][0] = '\0';
			len = 0;
			for (j=1;j<ENDMEAS;j+=4) {
				// j=1 is a pseudorange, and then pseudoranges come every 4 identifiers.
				// See the "enum MeasurementType" enumerator at dataHandling.h file for
				// more details 
				if (epoch->measOrder[i].meas2Ind[j]!=-1 || epoch->measOrder[i].meas2Ind[j+1]!=-1) {
					// See if the Pseudorange OR the associated Carrier Phase (j+1) are available
					measChain[i][n[i]] = j;
					measChain[i][n[i]+1] = j+1;
					n[i]+=2;
					strcpy(mS[0], meastype2measstr(j));
					strcpy(mS[1], meastype2measstr(j+1));
					if (len!=0) {
						len += sprintf(&measStr[i][len],":");
					}
					len += sprintf(&measStr[i][len],"%s:%s",mS[0],mS[1]);
				}
			}
			if (n[i]>maxN) maxN = n[i];
		}
		for (i=0;i<epoch->numSatellites;i++) {
			//Get DCB P1-C1
			correction1=0;
			if (tgdData->p1c1dcbModel == p1c1STRICT) {
				getTGDfromDCB(tgdData, &epoch->receiver, epoch->sat[i].GNSS, epoch->sat[i].PRN,&epoch->t, C1C, C1P, &correction1, &retDCB, &retDCBC1P1);
				if (retDCB==0) {
					correction1=0;
				}
			}
			k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			if (epoch->cycleslip.consistency[k]) continue;
			fprintf(options->outFileStream,"MEAS      %17s %3s %2d %8.3f %8.3f %2d ",t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[i].GNSS),epoch->sat[i].PRN,epoch->sat[i].elevation/d2r,epoch->sat[i].azimuth/d2r,n[epoch->sat[i].GNSS]);
			fprintf(options->outFileStream,"%*s",maxN*4,measStr[epoch->sat[i].GNSS]);
			for (j=0;j<n[epoch->sat[i].GNSS];j++) {
				res = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,measChain[epoch->sat[i].GNSS][j],&measVal,NULL);
				if (measVal==-1 || res==0) measVal = 0;
				if(epoch->sat[i].GNSS==GPS) {
					if(epoch->receiver.recType==rtNOP1 && measChain[epoch->sat[i].GNSS][j]==C1P) measVal-=correction1;
					else if (epoch->receiver.recType==rtCROSS && measChain[epoch->sat[i].GNSS][j]==C1P) measVal-=correction1;
					else if (epoch->receiver.recType==rtCROSS && measChain[epoch->sat[i].GNSS][j]==C2P) measVal-=correction1;
				}
				fprintf(options->outFileStream," %14.4f",measVal);
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
 * TEpoch  *epoch                  I  N/A  Reference epoch
 * int  satIndex                   I  N/A  Satellite index
 * int  LiCheck                    I  N/A  Li Flag (1-> cycle-slip found in Li)
 * double  LiLiestDiff             I    m  Absolute difference between measured 
 *                                         and estimated Li values
 * double  LiThreshold             I    m  Threshold for LiLiestDiff
 * int  BwCheck                    I  N/A  Bw Flag (1-> cycle-slip found in Bw)
 * double  nBwdiff                 I  cyc  Absolute difference between measured 
 *                                         and estimated Bw values
 * double  nBwdiffThreshold        I  cyc  Threshold for nBwdiff
 * int  L1C1Check                  I  N/A  L1C1 Flag (1->cycle-slip found in L1C1)
 * double  L1C1diff                I    m  Absolute difference between measured 
 *                                         and estimated L1C1 values
 * double  L1C1Threshold           I    m  Threshold for L1C1diff
 * TOptions  *options              I  N/A  TOptions structure
 * int  DataGapCheck               I  N/A  DataGap Flag (1-> cycle-slip found in DataGap)
 * double maxDataGap               I    s  Maximum period of time allowed before declaring CS
 * double timeDiff                 I    s  Delta time from previous usable epoch
 * int  LLICheck                   I  N/A  LLI Flag (1-> cycle-slip found in LLI)
 * int  mode                       I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS, then Rover)
 *                                         1 => Process Rover (user)
 *                                         2 => Process Base Station (for DGNSS)
 *****************************************************************************/
void printCS (TEpoch *epoch, int satIndex, int LiCheck, double LiLiestDiff, double LiThreshold, int BwCheck, double nBwdiff, double nBwdiffThreshold, int L1C1Check, double L1C1diff, double L1C1Threshold, TOptions *options, int DataGapCheck, double maxDataGap, double timeDiff, int LLICheck, int mode) {
	if (options->printCycleslips) {
		char cs[8];

		if ( mode == 2 ) strcpy(cs,"CS_REF"); // Reference station
		else if ( mode == 1 ) strcpy(cs,"CS_USER"); // Rover (user)
		else strcpy(cs,"CS"); // Standalone

		if ( DataGapCheck ) {
			 fprintf(options->outFileStream,"%-9s%17s %3s %2d  DATA_GAP = %f THRESHOLD = %f\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,timeDiff,maxDataGap);
		} else if ( LLICheck ) {
			 fprintf(options->outFileStream,"%-9s%17s %3s %2d  LLI\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN);
		} else {
			if ( options->csLI && LiCheck ) {
				if(LiLiestDiff==999999.) {
					fprintf(options->outFileStream,"%-9s%17s %3s %2d  LI = - THRESHOLD = %f\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,LiThreshold);
				} else {
					fprintf(options->outFileStream,"%-9s%17s %3s %2d  LI = %f THRESHOLD = %f\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,LiLiestDiff,LiThreshold);
				}
			}
			if ( options->csBW && BwCheck ) {
				fprintf(options->outFileStream,"%-9s%17s %3s %2d  Bw = %f THRESHOLD = %f\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,nBwdiff,nBwdiffThreshold);
			}
			if ( options->csL1C1 && L1C1Check ) {
				fprintf(options->outFileStream,"%-9s%17s %3s %2d  L1C1 = %f THRESHOLD = %f\n",cs,t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,L1C1diff,L1C1Threshold);
			}
		}
	}
}
/*****************************************************************************
 * Name        : printModel
 * Description : Prints each of the components of the model for a specific 
 *               satellite and measurement
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * int  satIndex                            I  N/A  Selected satellite
 * int  measIndex                           I  N/A  Selected measurement
 * double  flightTime                       I    s  Signal flight time
 * double  geometricDistance                I    m  Geometric distance between satellite and receiver
 * double  satelliteClockModel              I    m  Satellite clock error
 * double  satellitePhaseCenterProjection   I    m  Projection of the satellite phase center into the LoS
 * double  receiverPhaseCenterProjection    I    m  Projection of the receiver phase center into the LoS 
 * double  receiverARPProjection            I    m  Projection of the receiver ARP into the LoS
 * double  relativityModel                  I    m  Relativity model
 * double  windUpMetModel                   I    m  Wind up model (for carrier phase only)
 * double  troposphereModel                 I    m  Troposphere model
 * double  ionosphereModel                  I    m  Ionosphere model
 * double  gravitationalDelayModel          I    m  Gravitational delay model
 * double  TGDModel                         I    m  TGD model
 * double  solidTidesModel                  I    m  Projection of the effect of solid tides into the LoS
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printModel (TEpoch *epoch, int satIndex, int measIndex, double flightTime, double geometricDistance, double satelliteClockModel, double satellitePhaseCenterProjection, double receiverPhaseCenterProjection, double receiverARPProjection, double relativityModel, double windUpMetModel, double troposphereModel, double ionosphereModel, double gravitationalDelayModel, double TGDModel, double solidTidesModel, TOptions *options) {

	double 	velocity[3];
	double	measurement;
	double	model;
	double	SNR;
	int		ind,res,i;
	enum	MeasurementType meas;
	
	i = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	//Get SNR measurement
	meas = epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex];
	switch ( whatIs(meas) ) {
		case CarrierPhase:
			ind = epoch->measOrder[epoch->sat[satIndex].GNSS].meas2Ind[meas+2];
			if(ind==-1) {
				SNR=epoch->sat[satIndex].meas[measIndex].SNRdBHz;
			} else {
				SNR=epoch->sat[satIndex].meas[ind].value;
			}
			break;
		case Pseudorange:
			ind = epoch->measOrder[epoch->sat[satIndex].GNSS].meas2Ind[meas+3];
			if(ind==-1) {
				if (meas==C1C) {
					ind = epoch->measOrder[epoch->sat[satIndex].GNSS].meas2Ind[meas+7];
					if(ind==-1) {
						SNR=epoch->sat[satIndex].meas[measIndex].SNRdBHz;
					} else {
						SNR=epoch->sat[satIndex].meas[ind].value;
					}
				} else {
					SNR=epoch->sat[satIndex].meas[measIndex].SNRdBHz;
				}
			} else {
				SNR=epoch->sat[satIndex].meas[ind].value;
			}
			break;
		default:
			SNR=999;
			break;
	}

	if (options->satVel==svINERTIAL) {
		memcpy(velocity,epoch->sat[satIndex].velocity,3*sizeof(double));
	} else {
		memcpy(velocity,epoch->sat[satIndex].ITRFvel,3*sizeof(double));
	}	 
	if (options->printModel) {
		res = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex],&measurement,&model);
		if (res==1) {
			sprintf(printbufferMODEL[satIndex],"MODEL     %17s %3s %2d %3s %11.5f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %9.5f %8.3f %8.3f %8.3f\n",
					t2doystr(&epoch->t),
					gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
					epoch->sat[satIndex].PRN,
					meastype2measstr(epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex]),
					flightTime,
					getMeasurementValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex]),
					getModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex]),
					epoch->sat[satIndex].position[0],
					epoch->sat[satIndex].position[1],
					epoch->sat[satIndex].position[2],
					velocity[0],
					velocity[1],
					velocity[2],
										//JAUME//
					geometricDistance,
										//GEOMETRIC RANGE BETWEEN RECEIVER AND ANTENNA PHASE CENTERS//
										//geometricDistance+satellitePhaseCenterProjection+receiverPhaseCenterProjection+receiverARPProjection+solidTidesModel,//
										//JAUME//
					satelliteClockModel,
					satellitePhaseCenterProjection,
					receiverPhaseCenterProjection,
					receiverARPProjection,
					relativityModel,
					//windUpRadModel,
					windUpMetModel,
					troposphereModel,
					ionosphereModel,
					gravitationalDelayModel,
					TGDModel,
					solidTidesModel,
					epoch->sat[satIndex].elevation/d2r,
					epoch->sat[satIndex].azimuth/d2r,
					SNR);

			//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
			if(options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[i] < options->excludeSmoothingConvergence) {
				//Steady state not reached
				printbufferMODEL[satIndex][5]='*';
			}

			if(options->printInBuffer!=1) {
				fprintf(options->outFileStream,"%s",printbufferMODEL[satIndex]);
				printbufferMODEL[satIndex][0]='\0';
			}
		}
	}
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
 * int  satellite                  I  N/A  PRN of the satellite
 * char  *message                  I  N/A  Reason of the discard (if selected==0)
 * int  satIndex                   I  N/A  Selected satellite
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatSel (TEpoch *epoch, int selected, char *message, int satIndex, TOptions *options) {
	if ( options->printSatSel ) {

		if ( !selected ) sprintf(printbufferSATSEL[satIndex][linesstoredSATSEL[satIndex]],"SATSEL    %17s %3s %2d discarded: %s\n",t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN,message);
		else sprintf(printbufferSATSEL[satIndex][linesstoredSATSEL[satIndex]],"SATSEL    %17s %3s %2d selected\n",t2doystr(&epoch->t),gnsstype2gnssstr(epoch->sat[satIndex].GNSS),epoch->sat[satIndex].PRN);

		if ( options->printInBuffer != 1 ) {
			fprintf(options->outFileStream,"%s",printbufferSATSEL[satIndex][linesstoredSATSEL[satIndex]]);
			printbufferSATSEL[satIndex][linesstoredSATSEL[satIndex]][0]='\0';
			linesstoredSATSEL[satIndex]=0;
		} else {
			linesstoredSATSEL[satIndex]++;
		}
	}
}

/*****************************************************************************
 * Name        : printPrefit
 * Description : Prints the prefilter residuals for a specific satellite/measurement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * int  satIndex                   I  N/A  Selected satellite
 * TSatellite  *sat                I  N/A  Selected satellite structure
 * enum MeasurementType  measType  I  N/A  Selected measurement
 * double  prefit                  I    m  Computed prefit
 * double  measurement             I    m  Measurement value
 * double  model                   I    m  Modeled value
 * double  stdDev                  I    m  Assigned weight of the measurement 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printPrefit (TTime *t, int satIndex, TSatellite *sat, enum MeasurementType measType, double prefit, double measurement, double model, double stdDev, int narc, TOptions *options) {	
	char buffer[MAX_INPUT_LINE];

	if (options->printPrefit) {
		sprintf(printbufferPREFIT[satIndex],"PREFIT%1s   %17s %3s %2d %3s %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %8.3f %8.3f",
				sat->available?"":"*",
				t2doystr(t),
				gnsstype2gnssstr(sat->GNSS),
				sat->PRN,
				meastype2measstr(measType),
				prefit,
				measurement,
				model,
				-1.0*sat->LoS[0],
				-1.0*sat->LoS[1],
				-1.0*sat->LoS[2],
				sqrt(sat->LoS[0]*sat->LoS[0] + sat->LoS[1]*sat->LoS[1] + sat->LoS[2]*sat->LoS[2]),				
				sat->elevation/d2r,
				sat->azimuth/d2r
				);


		if (stdDev==SIGMA_INF) {
			sprintf(buffer,"%s 9999.999 %8.3f %5d\n",printbufferPREFIT[satIndex],sat->tropWetMap,narc);
		} else {
			sprintf(buffer,"%s %8.3f %8.3f %5d\n",printbufferPREFIT[satIndex],stdDev,sat->tropWetMap,narc);
		}
		sprintf(printbufferPREFIT[satIndex],"%s",buffer);
	}


	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferPREFIT[satIndex]);
		printbufferPREFIT[satIndex][0]='\0';
	}
}

/*****************************************************************************
 * Name        : printEpochsat
 * Description : Prints the satellites used for processing an epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * enum MeasurementType  measType  I  N/A  Selected measurement
 * int  ns                         I  N/A  Number of satellites used
 * int  *sats                      I  N/A  Vector containing the satellites PRN
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printEpochsat (TTime *t, enum MeasurementType measType, int ns, int *sats, TOptions *options) {
	int i;
	char buffer[MAX_INPUT_LINE];
	
	if (options->printSatellites) {
		sprintf(printbufferEPOCHSAT,"EPOCHSAT  %17s %3s %2d",t2doystr(t),meastype2measstr(measType),ns);
		for (i=0;i<ns;i++) {
			sprintf(buffer,"%s %2d",printbufferEPOCHSAT,sats[i]);
			sprintf(printbufferEPOCHSAT,"%s",buffer);
		}
		sprintf(buffer,"%s\n",printbufferEPOCHSAT);
		sprintf(printbufferEPOCHSAT,"%s",buffer);
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferEPOCHSAT);
		printbufferEPOCHSAT[0]='\0';
	}
}

/*****************************************************************************
 * Name        : printFilter
 * Description : Prints the parameters estimated from the filter
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * int  nunk                       I  N/A  Number of unknowns in the filter
 * TFilterSolution  *solution      I  N/A  Structure storing the estimated parameters
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printFilter (TTime *t, int nunk, TFilterSolution *solution, TOptions *options) {
	int i;
	char buffer[MAX_INPUT_LINE];

	if (options->printFilterSolution) {
		sprintf(printbufferFILTER,"FILTER    %17s",t2doystr(t));
		for (i=0;i<nunk;i++) {
			sprintf(buffer,"%s %14.4f",printbufferFILTER,solution->x[i]);
			sprintf(printbufferFILTER,"%s",buffer);
		}
		sprintf(buffer,"%s\n",printbufferFILTER);
		sprintf(printbufferFILTER,"%s",buffer);
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferFILTER);
		printbufferFILTER[0]='\0';
	}
}

/*****************************************************************************
 * Name        : printPostfit
 * Description : Prints the postfilter residuals for a specific satellite/measurement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * int  satIndex                   I  N/A  Selected satellite
 * TSatellite  *sat                I  N/A  Selected satellite
 * enum MeasurementType  measType  I  N/A  Selected measurement
 * double  postfit                 I  N/A  Computed postfit
 * double  measurement             I  N/A  Measurement value
 * double  model                   I  N/A  Modeled value
 * double  estimatedParameters     I  N/A  Estimated parameters from the filter
 * double  ambiguity               I  N/A  Estimated ambiguity value (only for carrier phases)
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printPostfit (TTime *t, int satIndex, TSatellite *sat, enum MeasurementType measType, double postfit, double measurement, double model, double estimatedParameters, double ambiguity, TOptions *options) {
	if (options->printPostfit) {
		if (whatIs(measType)==CarrierPhase) {
			sprintf(printbufferPOSTFIT[satIndex],"POSTFIT%1s  %17s %3s %2d %3s %14.4f %14.4f %14.4f %8.3f %8.3f %14.4f\n",
					sat->available?"":"*",
					t2doystr(t),
					gnsstype2gnssstr(sat->GNSS),
					sat->PRN,
					meastype2measstr(measType),
					postfit,
					measurement,
					model + estimatedParameters,
					sat->elevation/d2r,
					sat->azimuth/d2r,
					ambiguity);
		} else if (whatIs(measType)==Pseudorange) {
			sprintf(printbufferPOSTFIT[satIndex],"POSTFIT%1s  %17s %3s %2d %3s %14.4f %14.4f %14.4f %8.3f %8.3f\n",
					sat->available?"":"*",
					t2doystr(t),
					gnsstype2gnssstr(sat->GNSS),
					sat->PRN,
					meastype2measstr(measType),
					postfit,
					measurement,
					model + estimatedParameters,
					sat->elevation/d2r,
					sat->azimuth/d2r);
		}
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferPOSTFIT[satIndex]);
		printbufferPOSTFIT[satIndex][0]='\0';
	}
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
	double						dNEU[3];
	double  					dXYZ[3];
	double  					feNEU[3];
	int							i,j,k;
	int 						indx;
	int							indtrop;
	static enum SolutionMode 	PrevSolutionModeKMLDGNSS=DGNSSMode;
	static enum SolutionMode 	PrevSolutionModeKML0DGNSS=DGNSSMode;
	static int 					PrevSolutionModeKMLSBAS=PAMODE; 
	static int 					PrevSolutionModeKML0SBAS=PAMODE; 
	char 						solutionMode[50];
	
	// First index of XYZ
	indx = unkinfo->par2unk[DR_UNK];
	
	// Index of troposphere
	if (options->estimateTroposphere) {
		indtrop = unkinfo->par2unk[TROP_UNK];
	}
	
	// Obtain NEU coordinates
	XYZ2NEU(&solution->x[indx],positionNEU);
	
	//if ( options->receiverPositionSource == rpRTCMbaseline || options->receiverPositionSource == rpRTCMUserbaseline ) 
	switch(epoch->receiver.OUTPUTDiffFieldsMode) {
		case RTCMBaseline:
			//Compute difference between solution and reference station (DGNSS)
			if ( epochDGNSS->receiver.aproxPosition[0] == EARTH_RADIUS && epochDGNSS->receiver.aproxPosition[1] == 0. && epochDGNSS->receiver.aproxPosition[2] == 0. ) {
				// This is done in order to output dNEU and dXYZ equal to zero when gLAB is still pending to obtain the Reference station coordinates
				for ( i = 0; i < 3; i++ ) {
					dNEU[i] = 0.;
					dXYZ[i] = 0.;
				}
			} else {
				for (i=0;i<3;i++) {
					dNEU[i] = 0;
					feNEU[i] = 0;
					for (j=0;j<3;j++) {
						dNEU[i] += (solution->x[indx+j] - epochDGNSS->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
						for (k=0;k<3;k++) {
							feNEU[i] += epoch->receiver.orientation[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientation[k][i];
						}
					}
					feNEU[i] = sqrt(feNEU[i]);
					dXYZ[i] = solution->x[indx+i] - epochDGNSS->receiver.aproxPosition[i];
				}
			}
			break;
		// else if ( options.receiverPositionSource == rpCALCULATEREF || options.receiverPositionSource == rpCALCULATERINEXREF || options.receiverPositionSource == rpCALCULATEUSERREF ) 
		case CalculateWithRefFile:
			//Position set by reference file but not used for modelling
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				feNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
					for (k=0;k<3;k++) {
						feNEU[i] += epoch->receiver.orientationRef[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientationRef[k][i];
					}
				}
				feNEU[i] = sqrt(feNEU[i]);
				dXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPositionRef[i];
			}
			break;
		// else if ( options->receiverPositionSource >= rpRTCMRINEXROVER && options->receiverPositionSource != rpRTCMUserbaseline) 
		case RTCMNoBaseline:
			//Compute difference between solution and provided rover position (DGNSS)
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				feNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRover[j])*epoch->receiver.orientationRover[i][j];
					for (k=0;k<3;k++) {
						feNEU[i] += epoch->receiver.orientationRover[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientationRover[k][i];
					}
				}
				feNEU[i] = sqrt(feNEU[i]);
				dXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPositionRover[i];
			}
			break;
		default:
			// Compute:
			//		dNEU differences in relation to a priori position
			//		Formal errors in NEU system. For this:
			//					feNEU = R^-1*feXYZ*R
			//					Being, R the rotation matrix (orientation matrix)
			//						   feXYZ the formal error matrix in XYZ components (the correlation matrix)
			//					As we are only interested in the diagonal of feNEU, only these elements are computed
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				feNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
					for (k=0;k<3;k++) {
						feNEU[i] += epoch->receiver.orientation[j][i] * solution->correlations[m2v(indx+j,indx+k)] * epoch->receiver.orientation[k][i];
					}
				}
				feNEU[i] = sqrt(feNEU[i]);
				dXYZ[i] = solution->x[indx+i] - epoch->receiver.aproxPosition[i];
			}
			break;
	}
	
	if ( epoch->receiver.RefPositionAvail==0 ) {
		for (i=0;i<3;i++) {
			dNEU[i] = 0;
			dXYZ[i] = 0;
		}
	}
	
	if (options->printOutput) {
		fprintf(options->outFileStream,"OUTPUT    %17s %9.4f %14.4f %14.4f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %14.9f %14.9f %14.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %9.4f %9.4f %9.4f %9.4f %9.4f",
				t2doystr(&epoch->t),
				solution->dop,
				solution->x[indx+0],
				solution->x[indx+1],
				solution->x[indx+2],
				dXYZ[0],
				dXYZ[1],
				dXYZ[2],
				sqrt(solution->correlations[m2v(indx+0,indx+0)]),
				sqrt(solution->correlations[m2v(indx+1,indx+1)]),
				sqrt(solution->correlations[m2v(indx+2,indx+2)]),
				positionNEU[0]/d2r, // Latitude
				positionNEU[1]/d2r, // Longitude
				positionNEU[2],     // Height
				dNEU[0],			// dNorth
				dNEU[1],			// dEast
				dNEU[2],			// dUp
				feNEU[0],
				feNEU[1],
				feNEU[2],
				solution->GDOP,
				solution->PDOP,
				solution->TDOP,				
				solution->HDOP,
				solution->VDOP);
		if (options->estimateTroposphere) {
			fprintf(options->outFileStream," %10.4f %10.4f %10.4f",
					solution->x[indtrop],
					solution->x[indtrop] - epoch->ZTD,
					sqrt(solution->correlations[m2v(indtrop,indtrop)]));
		} else {
			fprintf(options->outFileStream," %10.4f %10.4f %10.4f", 0.0, 0.0, 0.0);
		}
		fprintf(options->outFileStream," %2d %1d\n", epoch->numSatSolutionFilter,options->solutionMode);
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
		if ( (PrevSolutionModeKMLDGNSS!=options->solutionMode && options->DGNSS) || (PrevSolutionModeKMLSBAS!=options->precisionapproach && (options->SBAScorrections==1 && options->onlySBASiono==0 && options->switchmode==1)) ) {
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
		//if((options->DGNSS && options->solutionMode==DGNSSMode) || options->DGNSS==0) {
		fprintf(options->fdkml,"          %.9f,%.9f,%.9f\n",positionNEU[1]/d2r,positionNEU[0]/d2r,positionNEU[2]-(options->KMLEGM96height==1?getEGM96Height(epoch->KMLData[epoch->numKMLData-1]):0.));
		PrevSolutionModeKMLDGNSS=options->solutionMode;
		PrevSolutionModeKMLSBAS=options->precisionapproach;
		//}
	}

	//Print KML (ground projection) file if necessary
	if (options->fdkml0!=NULL) {
		//if((options->DGNSS && options->solutionMode==DGNSSMode) || options->DGNSS==0) {
		if ( (PrevSolutionModeKML0DGNSS!=options->solutionMode && options->DGNSS)  || (PrevSolutionModeKML0SBAS!=options->precisionapproach && (options->SBAScorrections==1 && options->onlySBASiono==0 && options->switchmode==1)) ) {
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
		//}
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
 * TTime  *t                       I  N/A  Reference time
 * enum GNSSystem  GNSS            I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN satellite identifier
 * double  SISREDiff               I    m  Signal-in-Space Range Error difference
 * double  OrbDiff                 I    m  SISRE orbit-only difference
 * double  Orb3DDiff               I    m  3D orbit difference
 * double  ClkDiff                 I    m  Clock difference
 * double  posDiff[3]              I    m  Radial, along- and cross-track position difference 
 * double  posDiffXYZ[3]           I    m  X Y Z position difference 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatDiff (TTime *t, enum GNSSystem GNSS, int PRN, double SISREDiff, double OrbDiff, double Orb3DDiff, double ClkDiff, double posDiff[3], double posDiffXYZ[3], TOptions *options) {
	if (options->printSatDiff) {
		fprintf(options->outFileStream,"SATDIFF %17s %3s %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
				t2doystr(t),
				gnsstype2gnssstr(GNSS),
				PRN,
				SISREDiff,
				OrbDiff,
				Orb3DDiff,
				ClkDiff,
				posDiff[2],
				posDiff[0],
				posDiff[1],
				posDiffXYZ[0],
				posDiffXYZ[1],
				posDiffXYZ[2]
				);
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
 * TStat  statRadOrb               I  N/A  Radial position statistics 
 * TStat  statAloOrb               I  N/A  Along-track position statistics 
 * TStat  statCroOrb               I  N/A  Cross-track position statistics 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatStat (enum GNSSystem GNSS, int PRN, TStat statSISRE, TStat statOrb, TStat stat3D, TStat statClk, TStat statRadOrb, TStat statAloOrb, TStat statCroOrb, TOptions *options) {
	if (options->printSatStat && (statSISRE.n != 0)) {
		fprintf(options->outFileStream,"SATSTAT %3s %2d %4d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
				gnsstype2gnssstr(GNSS),
				PRN,
				statSISRE.n,
				statSISRE.mean,
				sqrt(statSISRE.mean2),
				sqrt(fabs(statSISRE.mean2 - statSISRE.mean*statSISRE.mean)),
				statOrb.mean,
				sqrt(statOrb.mean2),
				sqrt(fabs(statOrb.mean2 - statOrb.mean*statOrb.mean)),
				stat3D.mean,
				sqrt(stat3D.mean2),
				sqrt(fabs(stat3D.mean2 - stat3D.mean*stat3D.mean)),
				statClk.mean,
				sqrt(statClk.mean2),
				sqrt(fabs(statClk.mean2 - statClk.mean*statClk.mean)),
				statRadOrb.mean,
				sqrt(statRadOrb.mean2),
				sqrt(fabs(statRadOrb.mean2 - statRadOrb.mean*statRadOrb.mean)),
				statAloOrb.mean,
				sqrt(statAloOrb.mean2),
				sqrt(fabs(statAloOrb.mean2 - statAloOrb.mean*statAloOrb.mean)),
				statCroOrb.mean,
				sqrt(statCroOrb.mean2),
				sqrt(fabs(statCroOrb.mean2 - statCroOrb.mean*statCroOrb.mean))
				); 
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
 * TStat  statRadOrb               I  N/A  Radial position statistics 
 * TStat  statAloOrb               I  N/A  Along-track position statistics 
 * TStat  statCroOrb               I  N/A  Cross-track position statistics 
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatStatTot (TStat statSISRETot, TStat statOrbTot, TStat stat3DTot, TStat statClkTot, TStat statRadOrbTot, TStat statAloOrbTot, TStat statCroOrbTot, TOptions *options) {
	if (options->printSatStatTot && statSISRETot.n != 0) {
		fprintf(options->outFileStream,"SATSTATTOT %2d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
				statSISRETot.n,
				statSISRETot.mean,
				sqrt(statSISRETot.mean2),
				sqrt(fabs(statSISRETot.mean2 - statSISRETot.mean*statSISRETot.mean)),
				statOrbTot.mean,
				sqrt(statOrbTot.mean2),
				sqrt(fabs(statOrbTot.mean2 - statOrbTot.mean*statOrbTot.mean)),
				stat3DTot.mean,
				sqrt(stat3DTot.mean2),
				sqrt(fabs(stat3DTot.mean2 - stat3DTot.mean*stat3DTot.mean)),
				statClkTot.mean,
				sqrt(statClkTot.mean2),
				sqrt(fabs(statClkTot.mean2 - statClkTot.mean*statClkTot.mean)),
				statRadOrbTot.mean,
				sqrt(statRadOrbTot.mean2),
				sqrt(fabs(statRadOrbTot.mean2 - statRadOrbTot.mean*statRadOrbTot.mean)),
				statAloOrbTot.mean,
				sqrt(statAloOrbTot.mean2),
				sqrt(fabs(statAloOrbTot.mean2 - statAloOrbTot.mean*statAloOrbTot.mean)),
				statCroOrbTot.mean,
				sqrt(statCroOrbTot.mean2),
				sqrt(fabs(statCroOrbTot.mean2 - statCroOrbTot.mean*statCroOrbTot.mean))
				);
	}
}

/*****************************************************************************
 * Name        : printSatPvt
 * Description : Prints the position, velocity (in ECEF or inertial) 
 *                 and clock correction for one satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * enum GNSSystem  GNSS            I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN satellite identifier
 * double  position[3]             I    m  XYZ position of the satellite
 * double  velocity[3]             I  m/s  VXVYVZ velocity of the satellite
 * double  clock                   I    m  Clock offset of the satellite
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSatPvt (TTime *t, enum GNSSystem GNSS, int PRN, double position[3], double velocity[3], double clock, TOptions *options) {
	if (options->printSatPvt) {
		fprintf(options->outFileStream,"SATPVT %17s %3s %2d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %17.6f\n",
				t2doystr(t),
				gnsstype2gnssstr(GNSS),
				PRN,
				position[0],
				position[1],
				position[2],
				velocity[0],
				velocity[1],
				velocity[2],
				clock
				);
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
void writeSBASfiles (FILE  **fdlist, FILE  *readfd, char **filelist, char **line, int numlines, int header, int sourcefile, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options) {

	if(decoderesult<0) {
		//An incorrect message has been detected. 
		//Incorrect messages will be written to converted EMS or RINEX-B files, as the behaviour
		// of reading incorrect messages or not reading any message is different.
		//For pegasus, the data will not be written but it will be logged in the "SBAS Message Transmission Sequence File"
		//Furthermore, a log will be created with the incorrect messages
					
		if(options->writePegasusfile==1) {
			writePegasusfiles(fdlist,readfd,filelist,line,numlines,sourcefile,header,decoderesult,decodedmessagetype,prevday,sbasblock,options);
		}

		writeLogfile(fdlist,readfd,filelist[fdLOGFILE],line,numlines,sourcefile,decoderesult,sbasblock,options);			
	}

	//Check if we have to write a new RINEX-B file
	if(options->writeRinexBfile==1) {
		writeRinexBfile(fdlist,readfd,filelist[fdRINEXB],line,numlines,header,sourcefile,sbasblock,options);
	}

	//Check if we have to write a EMS file
	if(options->writeEMSfile==1) {
		writeEMSfile(fdlist,readfd,filelist[fdEMS],line,numlines,header,sourcefile,sbasblock,options);

	}

	//Check if we have to write a Pegasus file (taking out the messages with failed CRC)
	if(options->writePegasusfile==1 && decoderesult>=0) {
		writePegasusfiles(fdlist,readfd,filelist,line,numlines,sourcefile,header,decoderesult,decodedmessagetype,prevday,sbasblock,options);
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
 * int numlines                    I  N/A  Number of lines given in string "line"
 * int sourcefile                  I  N/A  Indicates from what type file the
 *                                         SBAS data has been read.
 *                                         0 => RINEXB
 *                                         1 => EMS
 * int decoderesult                I  N/A  Indicates the result of message decoding
 * TSBASblock  *sbasblock        I  N/A  TSBASblock struct                                      
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeLogfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int numlines, int sourcefile, int decoderesult, TSBASblock  *sbasblock, TOptions  *options) {
	int			i,j;
	int			ret;
	int			numberofcolumns;
	char		aux[200],hexstring[300],error[50];
	char		*p;
	struct tm 	tm;
	int			year;
	double		doy,seconds;

	switch(decoderesult) {
		case(-1):
			strcpy(error,"CRC24Q_FAILURE              ");
			break;

		case(-2):
			strcpy(error,"INVALID_PREAMBLE            ");
			break;

		case(-3):
			strcpy(error,"MESSAGE_IDENTIFIER_MISMATCH ");
			break;

		case(-4):
			strcpy(error,"SATNUMBER_CORRECTED_EXCEEDED");
			break;

		case(-5):
			strcpy(error,"INVALID_TIME_OF_DAY         ");
			break;

		case(-6):
			strcpy(error,"INVALID_TIME_OF_WEEK        ");
			break;

		case(-7):
			strcpy(error,"INVALID_PRN_MASK_NUMBER     ");
			break;

		case(-8):
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
				numberofcolumns=sbasblock->datalength%18;
			} else {
				numberofcolumns=18;
			}

			//Read lines
			for(j=0;j<numberofcolumns;j++) {
				getstr(&hexstring[18*2*(i-1)+2*j],line[i],7+3*j,2);
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
void writeRinexBfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int numlines, int header, int sourcefile, TSBASblock  *sbasblock, TOptions  *options) {
	int 		i;
	int 		ret;
	char 		aux[200];
	char 		aux2[200];
	char 		aux3[10];
	char		monthname[10];
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
		MonthName(tm.tm_mon+1,monthname);
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
			MonthName(tm.tm_mon+1,monthname);
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
		ret=fprintf(fdlist[fdRINEXB],"%03d %02d %02d %02d %02d %02d%5.1f  L%1d   %3d   %3d   %3s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,sbasblock->frequency,sbasblock->datalength,sbasblock->receiverindex,sbasblock->sourceidentifier);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write second line of data
		sprintf(aux," %2d   ",sbasblock->messagetype);
		for(i=0;i<18;i++) {
			if(sbasblock->messagetype<10) getstr(aux3,line[0],24+2*i,2);
			else getstr(aux3,line[0],25+2*i,2);
			sprintf(aux2,"%s %2s",aux,aux3);
			sprintf(aux,"%s",aux2);
		}
		
		ret=fprintf(fdlist[fdRINEXB],"%s\n",aux);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
		}

		//Write third line of data
		sprintf(aux,"      ");
		for(i=0;i<14;i++) {
			if(sbasblock->messagetype<10) getstr(aux3,line[0],60+i*2,2);
			else getstr(aux3,line[0],61+i*2,2);
			sprintf(aux2,"%s %2s",aux,aux3);
			sprintf(aux,"%s",aux2);
		}
		
		ret=fprintf(fdlist[fdRINEXB],"%s\n",aux);
		if(ret<0) {
			fclose(readfd);		//Close RINEXB or EMS file where the data has been read
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When writing SBAS data to RINEX B file [%s]\n",filename);
			printError(aux,options);
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
void writeEMSfile (FILE **fdlist, FILE *readfd, char *filename, char **line, int numlines, int header, int sourcefile,  TSBASblock  *sbasblock, TOptions  *options) {
	int 	i,j;
	int 	ret;
	int 	numberofcolumns;
	char 	aux[200],hexstring[300];
	struct	tm tm;
	int 	year;
	double 	doy,seconds;
	char    *p;

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
				numberofcolumns=sbasblock->datalength%18;
			} else {
				numberofcolumns=18;
			}

			//Read lines
			for(j=0;j<numberofcolumns;j++) {
				getstr(&hexstring[18*2*(i-1)+2*j],line[i],7+3*j,2);
			}
		}
		ret=fprintf(fdlist[fdEMS],"%03d %02d %02d %02d %02d %02d %02d %d %s\n",sbasblock->PRN,year%100,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,sbasblock->messagetype,hexstring);
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

	int		ret;
	char		aux[200];
	char		monthname[10];
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
		MonthName(tm.tm_mon+1,monthname);
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
void writePegasusfiles (FILE **fdlist, FILE *readfd, char **filelist, char **line, int numlines, int sourcefile, int header, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options) {
	static int	headerwritten=0;
	int		i,j;
	int		ret;
	int		number;
	int		type;
	int		numberofcolumns;
	int		crcpass=1,valid=1;
	int		GPSweek,GPSweektrans,GPSweektoe;
	int		previousday=0,filetoprint;
	static int	firstbrdcday=-1;
	double		SoW,SoWtrans,SoWtoe;
	double		seconds;
	double		uravalue;
	double		health;
	double		transtimesecadjusted;
	double		igpverticaldelay;
	char		aux[1000];
	char		aux2[1000];
	char            hexstring[300];
	char            binarystring[2400];
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
	if(options->alarmmessageastype2==1 && decodedmessagetype==DONTUSE) {
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
						numberofcolumns=sbasblock->datalength%18;
					} else {
						numberofcolumns=18;
					}

					//Read lines
					for(j=0;j<numberofcolumns;j++) {
						getstr(&hexstring[18*2*(i-1)+2*j],line[i],7+3*j,2);
					}
				}	

			} else {
				//The origin file is EMS
				if(sbasblock->messagetype<10) {	
					getstr(hexstring,line[0],24,64);	
				} else {
					getstr(hexstring,line[0],25,64);
				}
			}

			////Now we have the hexadecimal string. We need to convert to a binary string, then 
			////extract the corresponding bits, then add 6 trailing zeros so it is a multiple of 8 and then convert to a hexadecimal string
			
			//Convert the hexadecimal string to a binary string (1 bit per byte)
			strhextostrbin(hexstring,binarystring);
			
			//Extract the PRN Mask in binary string
			getstr(aux2,binarystring,14,210);

			//Add the 6 trailing zeros to the PRN Mask
			sprintf(aux,"%s000000",aux2);

			//Convert from binary to hexadecimal
			strbintostrhex(aux,hexstring,1);


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
			if(options->alarmmessageastype2==0) break;
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
			for(i=0;i<number;i++) {
				if(options->pegasusaligned==1) {
					sprintf(aux2,"%s%-8.3f%c",aux,sbasblock->PRC[i],options->pegasusfs);	//Write PRC
				} else {
					sprintf(aux2,"%s%.3f%c",aux,sbasblock->PRC[i],options->pegasusfs);	//Write PRC
				}
				sprintf(aux,"%s",aux2);					//Copy to aux
			}

			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				//In this case we only have 6 Fast Corrections, so the unavailable data (PRC 7-13) must have empty fields
				if(options->pegasusaligned==1) {
					if(options->pegasusfs==';') sprintf(aux2,"%s;;;;;;;                                                        ",aux);  //Add empty fields
					else sprintf(aux2,"%s                                                               ",aux);	//Add empty fields
				} else {
					if(options->pegasusfs==';') sprintf(aux2,"%s;;;;;;;",aux);  //Add empty fields
					else sprintf(aux2,"%s       ",aux);	//Add empty fields
				}
				sprintf(aux,"%s",aux2);					//Copy to aux
			}

			//Write UDREI
			for(i=0;i<number;i++) {
				if(i==number-1) {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d",aux,sbasblock->UDREI[i]);      //Write UDREI
					} else {
						sprintf(aux2,"%s%d",aux,sbasblock->UDREI[i]);      //Write UDREI
					}
				} else {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d%c        ",aux,sbasblock->UDREI[i],options->pegasusfs);	//Write UDREI
					} else {
						sprintf(aux2,"%s%d%c",aux,sbasblock->UDREI[i],options->pegasusfs);	//Write UDREI
					}

				}
				sprintf(aux,"%s",aux2);						//Copy to aux
			}

			if(sbasblock->messagetype==MIXEDFASTLONGTERMCORRECTIONS) {
				//In this case we only have 6 UDREI, so the unavailable data (UDREI 7-13) must have empty fields
				if(options->pegasusaligned==1) {
					if(options->pegasusfs==';') sprintf(aux2,"%s;;;;;;;",aux);      //Add empty fields
					else sprintf(aux2,"%s                                                                           ",aux);	//Add empty fields
				} else {
					if(options->pegasusfs==';') sprintf(aux2,"%s;;;;;;;",aux);      //Add empty fields
					else sprintf(aux2,"%s       ",aux);	//Add empty fields
				}
				sprintf(aux,"%s",aux2);					//Copy to aux
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
			} else { //sbasblock->longtermsaterrcorrections[2][VELOCITYCODE]==1) {
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
				sprintf(aux,"%-4d%c        %-9.2f%c  %-3d%c   %-d%c       %-d%c       %-d%c       %-d%c       ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODF[1],options->pegasusfs,sbasblock->IODF[2],options->pegasusfs,sbasblock->IODF[3],options->pegasusfs);
			} else {
				sprintf(aux,"%d%c%.2f%c%d%c%d%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->IODF[0],options->pegasusfs,sbasblock->IODF[1],options->pegasusfs,sbasblock->IODF[2],options->pegasusfs,sbasblock->IODF[3],options->pegasusfs);
			}
			for(i=0;i<51;i++) {
				if(i==50) {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d",aux,sbasblock->UDREIacu[i]);
					} else {
						sprintf(aux2,"%s%d",aux,sbasblock->UDREIacu[i]);
					}
				} else {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d%c        ",aux,sbasblock->UDREIacu[i],options->pegasusfs);
					} else {
						sprintf(aux2,"%s%d%c",aux,sbasblock->UDREIacu[i],options->pegasusfs);
					}
				}
				sprintf(aux,"%s",aux2);
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
				sprintf(aux,"%-4d%c        %-9.2f%c  %-3d%c     %-2d%c       %-2d%c       ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->tlat,options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			} else {
				sprintf(aux,"%d%c%.2f%c%d%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->tlat,options->pegasusfs,sbasblock->IODP,options->pegasusfs);
			}
			for(i=0;i<51;i++) {
				if(i==50) {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d",aux,sbasblock->aiind[i]);
					} else {
						sprintf(aux2,"%s%d",aux,sbasblock->aiind[i]);
					}
				} else {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-2d%c     ",aux,sbasblock->aiind[i],options->pegasusfs);
					} else {
						sprintf(aux2,"%s%d%c",aux,sbasblock->aiind[i],options->pegasusfs);
					}
				}
				sprintf(aux,"%s",aux2);
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
						numberofcolumns=sbasblock->datalength%18;
					} else {
						numberofcolumns=18;
					}

					//Read lines
					for(j=0;j<numberofcolumns;j++) {
						getstr(&hexstring[18*2*(i-1)+2*j],line[i],7+3*j,2);
					}
				}	

			} else {
				//The origin file is EMS
				if(sbasblock->messagetype<10) {	
					getstr(hexstring,line[0],24,64);	
				} else {
					getstr(hexstring,line[0],25,64);
				}
			}

			
			//Convert the hexadecimal string to a binary string (1 bit per byte)
			strhextostrbin(hexstring,binarystring);
			
			//Extract the IGP Mask in binary string
			getstr(aux2,binarystring,24,201);

			//Add the 6 trailing zeros to the IGP Mask
			sprintf(aux,"%s0000000",aux2);

			//Convert from binary to hexadecimal
			strbintostrhex(aux,hexstring,1);

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
			for(i=0;i<15;i++) {
				if(sbasblock->ionodelayparameters[i][IGPVERTICALDELAY]==-1)  igpverticaldelay=63.875;
				else igpverticaldelay=sbasblock->ionodelayparameters[i][IGPVERTICALDELAY];
				if(i==14) {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-6.3f%c     %-2d",aux,igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI]); //Write IGP and GIVEI
					} else {
						sprintf(aux2,"%s%.3f%c%d",aux,igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI]); //Write IGP and GIVEI
					}
				} else {
					if(options->pegasusaligned==1) {
						sprintf(aux2,"%s%-6.3f%c     %-2d%c        ",aux,igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI],options->pegasusfs); //Write IGP and GIVEI
					} else {
						sprintf(aux2,"%s%.3f%c%d%c",aux,igpverticaldelay,options->pegasusfs,(int)sbasblock->ionodelayparameters[i][GIVEI],options->pegasusfs); //Write IGP and GIVEI
					}

				}
				sprintf(aux,"%s",aux2);					//Copy to aux
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
			for(i=0;i<5;i++) {
				if(i>=(int)sbasblock->servicemessage[NUMBEROFREGIONS]) {
					//If there are not five regions fill with zeros the missing regions
					if(i==4) {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						}
					} else {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d%c     ",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						}
					}
				} else {
					if(i==4) {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d",aux,
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE]); 
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d",aux,
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE]); 
						}
					} else {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-3d%c     %-4d%c    %-3d%c     %-4d%c    %-d%c     ",aux,
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE],options->pegasusfs); 
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c",aux,
								(int)sbasblock->regioncoordinates[i][COORD1LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD1LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LAT],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][COORD2LON],options->pegasusfs,
								(int)sbasblock->regioncoordinates[i][REGIONSHAPE],options->pegasusfs); 
						}

					}
				}
				sprintf(aux,"%s",aux2);					//Copy to aux
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
			if(sbasblock->clockephemeriscovariance[0][IODPPOSITION]==-1) {
				if(options->pegasusaligned==1) {
					ret=fprintf(fdlist[fdSERVICEREGION28],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c      ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,0,options->pegasusfs);
				} else {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%d%c%.2f%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,0,options->pegasusfs);
				}
			} else {
				if ( options->pegasusaligned == 1 ) {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%-4d%c        %-9.2f%c  %-3d%c     %-d%c      ",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->clockephemeriscovariance[0][IODPPOSITION],options->pegasusfs);
				} else {
					ret = fprintf(fdlist[fdSERVICEREGION28],"%d%c%.2f%c%d%c%d%c",GPSweek,options->pegasusfs,SoW,options->pegasusfs,sbasblock->PRN,options->pegasusfs,sbasblock->clockephemeriscovariance[0][IODPPOSITION],options->pegasusfs);
				}
			}
				if ( ret < 0 ) {
						fclose(readfd);         //Close RINEXB or EMS file where the data has been read
						closefiles(fdlist,18);  //Close all other files before exiting
						sprintf(aux,"When writing SBAS data to Pegasus file [%s]\n",filelist[fdSERVICEREGION28]);
						printError(aux,options);
				}

			aux[0]='\0';		//Initialize aux to empty
			for (i=0;i<2;i++) {
				if (i>=sbasblock->numclockephemeriscovariance || sbasblock->clockephemeriscovariance[0][IODPPOSITION]==-1) {
					// If we exceed the number of satellites fill with zeros
					if ( i == 0 ) {
						if (options->pegasusaligned==1) {
							sprintf(aux2,"%s%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   ",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs);
						}
					} else {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",aux,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0,options->pegasusfs,0);
						}

					}
				} else {
					if ( i == 0 ) {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   ",aux,
								sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E11],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E22],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E33],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E44],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E12],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E13],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E14],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E23],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E24],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E34],options->pegasusfs);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",aux,
								sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E11],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E22],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E33],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E44],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E12],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E13],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E14],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E23],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E24],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E34],options->pegasusfs);
						}
					} else {
						if(options->pegasusaligned==1) {
							sprintf(aux2,"%s%-2d%c      %-d%c     %-3d%c    %-3d%c    %-3d%c    %-3d%c    %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d%c   %-4d",aux,
								sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E11],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E22],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E33],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E44],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E12],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E13],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E14],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E23],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E24],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E34]);
						} else {
							sprintf(aux2,"%s%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",aux,
								sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][SCALEEXPONENT],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E11],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E22],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E33],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E44],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E12],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E13],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E14],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E23],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E24],options->pegasusfs,
								sbasblock->clockephemeriscovariance[i][E34]);
						}
					}
				}
				sprintf(aux,"%s",aux2);					//Copy to aux
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
				sprintf(aux2,"%s*** Week %4d almanac for PRN-%3d *******\n",aux,GPSweek,(int)sbasblock->geoalmanacsmessage[i][PRNNUMBER]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sRX_WEEK               : %-4d\n",aux,GPSweek);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sRX_TOM                : %-9.2f\n",aux,SoW);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sPRN                   : %-3d\n",aux,sbasblock->PRN);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sDATA_PRN              : %-3d\n",aux,(int)sbasblock->geoalmanacsmessage[i][PRNNUMBER]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sDATA_ID               : %-d\n",aux,(int)sbasblock->geoalmanacsmessage[i][DATAID]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sHEALTH                : %-3d\n",aux,(int)sbasblock->geoalmanacsmessage[i][HEALTHPROVIDER]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sDAYTIME_APPLICABILITY : %-5d\n",aux,(int)sbasblock->geoalmanacsmessage[i][T0ALMANAC]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sDAY_OF_WEEK           : %-d\n",aux,1+(int)SoW/86400);	//Day of week goes from 1 to 7
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sWEEK_APPLICABILITY    : %-4d\n",aux,GPSweek);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sXGEO                  : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][XGALMANAC]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sYGEO                  : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][YGALMANAC]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sZGEO                  : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][ZGALMANAC]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sXGEO_RATE             : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][XGALMANACRATEOFCHANGE]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sYGEO_RATE             : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][YGALMANACRATEOFCHANGE]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux
				sprintf(aux2,"%sZGEO_RATE             : %19.12E\n",aux,sbasblock->geoalmanacsmessage[i][ZGALMANACRATEOFCHANGE]);
				sprintf(aux,"%s",aux2);                                 //Copy to aux

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

			  The same convention for converting the URA index to meters is used as
			  with GPS. Set URA = 32767 meters if URA index = 15.

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

			// Get URA value. If URA Index is 15, set to 32767 meters (according to RINEX v2.11) and set bit 5 of health to 1 (add 32)
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
						uravalue,	/*URA in meters*/
						sbasblock->geonavigationmessage[ZG]/1000,
						sbasblock->geonavigationmessage[ZGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[ZGACCELERATION]/1000,
						sbasblock->geonavigationmessage[IODN]);
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
						uravalue,	/*URA in meters*/
						sbasblock->geonavigationmessage[ZG]/1000,
						sbasblock->geonavigationmessage[ZGRATEOFCHANGE]/1000,
						sbasblock->geonavigationmessage[ZGACCELERATION]/1000,
						sbasblock->geonavigationmessage[IODN]);
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
 * Description : Prints the SBASCORR data line for SBAS
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * int  measIndex                           I  N/A  Selected measurement
 * double  flightTime                       I    s  Signal flight time
 * double  geometricDistance                I    m  Geometric distance between satellite and receiver
 * double  satelliteClockModel              I    m  Satellite clock error
 * double  satellitePhaseCenterProjection   I    m  Projection of the satellite phase center into the LoS
 * double  receiverPhaseCenterProjection    I    m  Projection of the receiver phase center into the LoS 
 * double  receiverARPProjection            I    m  Projection of the receiver ARP into the LoS
 * double  relativityModel                  I    m  Relativity model
 * double  windUpMetModel                   I    m  Wind up model (for carrier phase only)
 * double  troposphereModel                 I    m  Troposphere model
 * double  ionosphereModel                  I    m  Ionosphere model
 * double  gravitationalDelayModel          I    m  Gravitational delay model
 * double  TGDModel                         I    m  TGD model
 * double  solidTidesModel                  I    m  Projection of the effect of solid tides into the LoS
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASCORR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, int measIndex, double flightTime, double geometricDistance, double satelliteClockModel, double satellitePhaseCenterProjection, double receiverPhaseCenterProjection, double receiverARPProjection, double relativityModel, double windUpMetModel, double troposphereModel, double ionosphereModel, double gravitationalDelayModel, double TGDModel, double solidTidesModel, TOptions *options) {
	int			i,j;
	//int		ind;
	int			ret;
	int			GPSweek;
	int			IODE;
	double		SoW;
	double		measurement;
	double		model,prefit;
	double		smoothWith,smoothedVal;
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int	initialized=0;
	#pragma omp threadprivate(initialized)
	static char	receiverid[5];
	#pragma omp threadprivate(receiverid)

	// Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized=1;
		// Convert receiver name to lower case
		for (i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}


	ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex],&measurement,&model);
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
		


	// ind = epoch->measOrder[GPS].meas2Ind[C1C];

	// Smoothing
	if ( options->smoothEpochs != 0 && options->smoothMeas[0] != NA ) {
		ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,options->smoothMeas[0],&smoothWith,NULL);
		if ( ret != 1 ) {
			return;
		}
		prefit = epoch->cycleslip.smoothedMeas[j][0] + smoothWith - model;
		smoothedVal = epoch->cycleslip.smoothedMeas[j][0] + smoothWith;
	} else {
		prefit = measurement - model;
		// smoothedVal=epoch->sat[satIndex].meas[ind].value;
		smoothedVal=measurement;
	}

	sprintf(printbufferSBASCORR[satIndex],"SBASCORR    %4s %3s %3s %3d %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %7.5f %14.4f %14.4f %7.1f %7.1f %7.1f %14.4f %14.4f %14.4f %9.5f %9.5f %9.5f %9.5f %2d %2d %2d %2d %2d %4d %2d %2d %2d %2d %8.3f %8.3f\n",
	/*2*/		receiverid,
	/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
	/*5*/		epoch->sat[satIndex].PRN,
	/*6*/		t2doystr(&epoch->t), 		//Year
	/*7*/						//DoY
	/*8*/						//Seconds of day
	/*9*/		GPSweek,
	/*10*/		SoW,
	/*11*/		SBASdata[options->GEOindex].PRN,
	/*12*/		prefit,
	/*13*/		measurement,			//C1 raw + user added noise (in meters)
	/*14*/		smoothedVal,			//C1 smooothed + user added noise (if smoothing is disabled, then is C1 raw + user added noise) (in meters)
	/*15*/		geometricDistance, 		//With SBAS corrections (in meters)
	/*16*/		relativityModel,		//With SBAS corrections (in meters)
	/*17*/		satelliteClockModel, 		//With SBAS corrections (in meters)
	/*18*/		TGDModel,			//From navigation file (in meters)
	/*19*/		epoch->IPPlat,			//Ionospheric pierce point latitude (-90..90º)
	/*20*/		epoch->IPPlon,			//Ionospheric pierce point longitude (0..360º)
	/*21*/		ionosphereModel,		//In meters
	/*22*/		troposphereModel,		//In meters
	/*23*/		SBAScorr->PRC,	 		//PRC Fast Correction applied to the satellite (in meters)
	/*24*/		SBAScorr->RRCtime,		//RRC Fast Correction applied to the satellite (in meters)
	/*25*/		SBAScorr->fastcorrdegfactor,	//Fast correction degradation factor (in meters/seconds^2)
	/*26*/		SBAScorr->fastcorrtmout,	//PRC time out (in seconds)
	/*27*/		SBAScorr->fastcorrsmallertmout,	//RRC time out (smallest time out for all satellites) (in seconds)
	/*28*/		SBAScorr->tPRC,			//Time (seconds of day) used for computing PRC timeout
	/*29*/		SBAScorr->tudre,		//Time (seconds of day) used for computing sigma UDRE timeout
	/*30*/		SBAScorr->tu,			//Time (seconds of day) used for computing fast correction degradation
	/*31*/		SBAScorr->SatCoordbrdc[0]+SBAScorr->SatCoordCor[0],	//X component of the satellite position in WGS84 system at emission time with SBAS corrections (in meters) 
	/*32*/		SBAScorr->SatCoordbrdc[1]+SBAScorr->SatCoordCor[1],	//Y component of the satellite position in WGS84 system at emission time with SBAS corrections (in meters)
	/*33*/		SBAScorr->SatCoordbrdc[2]+SBAScorr->SatCoordCor[2],	//Z component of the satellite position in WGS84 system at emission time with SBAS corrections (in meters)
	/*34*/		SBAScorr->SatCoordCor[0],	//Long term correction to be applied to the X component of the satellite (in meters)
	/*35*/		SBAScorr->SatCoordCor[1],	//Long term correction to be applied to the Y component of the satellite (in meters)
	/*36*/		SBAScorr->SatCoordCor[2],	//Long term correction to be applied to the Z component of the satellite (in meters)
	/*37*/		SBAScorr->ClockCor,		//Long term correction to be applied to the satellite clock (in meters)
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
	/*48*/		epoch->sat[satIndex].elevation/d2r, //Elevation (in degrees)
	/*49*/		epoch->sat[satIndex].azimuth/d2r);  //Azimuth (in degrees)

	// Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if ( options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASCORR[satIndex][8]='*';
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferSBASCORR[satIndex]);
		printbufferSBASCORR[satIndex][0]='\0';
	}
}

/*****************************************************************************
 * Name        : printSBASVAR
 * Description : Prints the SBASVAR data line for SBAS
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
 * int  satIndex                            I  N/A  Selected satellite
 * int  measIndex                           I  N/A  Selected measurement
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void printSBASVAR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, int measIndex, TOptions *options) {
	int     	i, j;
	int     	ind;
	int     	ret;
	int     	GPSweek;
	double  	SoW;
	double  	measurement;
	double  	model;
	double 		smoothWith;
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int	initialized = 0;
	#pragma omp threadprivate(initialized)
	static char	receiverid[5];
	#pragma omp threadprivate(receiverid)

	// Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized=1;
		// Convert receiver name to lower case
		for(i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}

	ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[measIndex],&measurement,&model);
	if ( ret != 1 ) {
		return;
	}

	ind = epoch->measOrder[GPS].meas2Ind[C1C];

	// Smoothing
	if (options->smoothEpochs!=0 && options->smoothMeas[ind]!=NA) {
		ret = getMeasModelValue(epoch,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,options->smoothMeas[ind],&smoothWith,NULL);
		if (ret!=1) {
			return;
		}
	}

	sprintf(printbufferSBASVAR[satIndex],"SBASVAR     %4s %3s %3s %3d %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %8.3f %3d %14.4f %14.4f %14.4f %14.4f %1d %14.4f %14.4f %14.4f %8.3f %8.3f %8.3f %8.3f %8.3f\n",
	/*2*/		receiverid,
	/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
	/*5*/		epoch->sat[satIndex].PRN,
	/*6*/		t2doystr(&epoch->t), 		//Year
	/*7*/						//DoY
	/*8*/						//Seconds of day
	/*9*/		GPSweek,
	/*10*/      SoW,
	/*11*/      SBASdata[options->GEOindex].PRN,
	/*12*/		sqrt(SBAScorr->SBASsatsigma2),					//Sigma of the total residual error associated to the satellite (in meters)
	/*13*/		sqrt(SBAScorr->sigma2flt),					//Sigma of the residual error associated to the fast and long-term corrections (in meters)
	/*14*/		sqrt(SBAScorr->UDREsigma),					//Sigma of the UDRE (in meters)
	/*15*/		SBAScorr->deltaudre,						//Delta UDRE factor
	/*16*/		SBAScorr->deltaudresource,					//Indicates the data source for Delta UDRE(27 or 28 for their respective message type,-27 or -28 if received any of these message types but there was missing data or was timed out, 0 if no message type received or both received)
	/*17*/		SBAScorr->fastcorrdeg,						//Degradation parameter for fast correction data (in meters)
	/*18*/		SBAScorr->RRCdeg,						//Degradation parameter for range rate correction data (in meters)
	/*19*/		SBAScorr->longtermdegradation+SBAScorr->geonavdegradation,	//Degradation parameter for long term correction data or GEO navigation message data (in meters)
	/*20*/		SBAScorr->enroutedegradation,					//Degradation parameter for en route through NPA applications (in meters)
	/*21*/	   	(int)SBASdata[options->GEOindex].degradationfactors[RSSUDRE],	//Root-sum-square flag
	/*22*/		sqrt(SBAScorr->sigma2iono),					//Sigma of the residual error associated to the ionosheric corrections (in meters)
	/*23*/		sqrt(SBAScorr->sigma2tropo),					//Sigma of the residual error associated to the tropospheric corrections (in meters)
	/*24*/		sqrt(SBAScorr->sigma2air),					//Sigma of the total receiver error (in meters)
	/*25*/		sqrt(SBAScorr->sigma2noise),					//Sigma of the receiver noise (in meters)
	/*26*/		sqrt(SBAScorr->sigma2multipath),				//Sigma of the receiver multipath (in meters)
	/*27*/		sqrt(SBAScorr->sigma2divergence),				//Sigma of the receiver divergence (in meters)
	/*28*/		epoch->sat[satIndex].elevation/d2r,				//Elevation (in degrees)
	/*29*/		epoch->sat[satIndex].azimuth/d2r);				//Azimuth (in degrees)

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if (options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j]<options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASVAR[satIndex][7]='*';
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferSBASVAR[satIndex]);
		printbufferSBASVAR[satIndex][0]='\0';
	}
}

/*****************************************************************************
 * Name        : printSBASIONO
 * Description : Prints the SBASIONO data line for SBAS
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * TEpoch  *epoch                           I  N/A  Reference epoch
 * TSBASdata *SBASdata                      I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr                      I  N/A  Struct with the SBAS corrections to be applied
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
void printSBASIONO (TEpoch  *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int  satIndex, int  InterpolationMode, int  IGP1, int  BandNumber1, double IGPlat1, double IGPlon1, int  IGP2, int  BandNumber2, double IGPlat2, double IGPlon2, int  IGP3, int  BandNumber3, double IGPlat3, double IGPlon3, int  IGP4, int  BandNumber4, double IGPlat4, double IGPlon4, double  eps_iono[5], double  IGPDelays[5], double  IGPSigma2[5], double  IPPWeight[5], double  Fpp, double  SlantDelay, double  SlantSigma, double elevation, double azimuth, TOptions  *options) {
	int		i,j;
	int     	GPSweek;
	double		SoW;
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int	initialized=0;
	#pragma omp threadprivate(initialized)
	static char	receiverid[5];
	#pragma omp threadprivate(receiverid)

	//Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if ( initialized == 0 ) {
		initialized = 1;
		if(options->onlySBASplots==1) {
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

	sprintf(printbufferSBASIONO[satIndex],"SBASIONO    %4s %3s %3s %3d %17s %4d %9.2f %3d %8.3f %8.3f %d %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %d %2d %3d %7.1f %3d %3d %6.3f %8.4f %6.3f %8.4f %8.4f %6.4f %8.4f %8.4f %8.4f %5.2f %5.2f\n",
	/*2*/		receiverid,
	/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
	/*5*/		epoch->sat[satIndex].PRN,
	/*6*/		t2doystr(&epoch->t), 		//Year
	/*7*/						//DoY
	/*8*/						//Seconds of day
	/*9*/		GPSweek,
	/*10*/		SoW,
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
	/*21*/		SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP1],		//Iono delay (raw value from MT26) for vertex 1 (meters)
	/*22*/		SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP1],		//Iono sigma (raw value from MT26) for vertex 1 (meters^2)
	/*23*/		eps_iono[1],								//Degradation term for vertex 1 (meters)
	/*24*/		IGPDelays[1],								//Iono delay after interpolation (if required) for vertex 1 (meters)
	/*25*/		IGPSigma2[1],								//Iono sigma after applying degradation and interpolation (if lat=85º) for vertex 1 (meters^2)
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
	/*64*/		SlantDelay,								//Slant delay (meters of L1)
	/*65*/		SlantSigma,								//Slant Sigma (meters of L1)
	/*66*/		elevation/d2r,								//Elevation (in degrees)
	/*67*/		azimuth/d2r);								//Azimuth (in degrees)

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if ( options->excludeSmoothingConvergence>0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence ) {
		//Steady state not reached
		printbufferSBASIONO[satIndex][8]='*';
	}

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferSBASIONO[satIndex]);
		printbufferSBASIONO[satIndex][0]='\0';
	}
}

/*****************************************************************************
 * Name        : printSBASUNSEL
 * Description : Prints the SBASUNSEL data line for SBAS (printed only when a satellite is discarded)
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
	int				GPSweek;
	int				GEOPRN;
	double			SoW;
	char			GEOtext[100];
	char			Alarmtime[100];

	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int		initialized=0;
	#pragma omp threadprivate(initialized)
	static char		receiverid[5];
	#pragma omp threadprivate(receiverid)
	static char 	errorstr[49][MAX_INPUT_LINE];
	#pragma omp threadprivate(errorstr)

	//Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	errorcode=abs(errorcode);

	// Check for options->GEOindex value
	if ( options->GEOindex < 0 ) GEOPRN = -1;
	else GEOPRN=SBASdata[options->GEOindex].PRN;

	if ( initialized == 0 ) {
		initialized = 1;

		if(options->onlySBASplots==1) {
			//No observation file. Set receiver name as blank
			for (i=0;i<4;i++) {
				receiverid[i]=' ';
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
				sprintf(Alarmtime,"%17s",t2doystr(&SBASdata[0].alarmtime));
			} else {
				sprintf(GEOtext,"current GEO");
				sprintf(Alarmtime,"%17s",t2doystr(&SBASdata[options->GEOindex].lastmsgreceived[DONTUSE]));
			}
			sprintf(errorstr[4],"Received alarm message for %s at epoch %17s. Time remaining to finish alarm: %2d second%s",GEOtext,Alarmtime,SBASdata[options->GEOindex].alarmTimeRemaining,SBASdata[options->GEOindex].alarmTimeRemaining==1?"":"s");
			break;
		case 5:
			sprintf(errorstr[5],"Received %d consecutive messages with errors (UDREI data has been forced to timeout) [PA only]",SBASdata[0].failedmessages[GEOPRN]);
			break;
		case 6:
			sprintf(errorstr[6],"Missed %d consecutive messages",SBASdata[0].missed4msg[GEOPRN]);
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
			sprintf(errorstr[46],"Satellite is not in view (elevation %1.2f degrees)",epoch->sat[satIndex].elevation*r2d);
			break;
		case 47:
			sprintf(errorstr[47],"Satellite elevation (%1.2f degrees) is too low",epoch->sat[satIndex].elevation*r2d);
			break;
		case 48:
			sprintf(errorstr[48],"Satellite has an UDREI value of %d (user threshold is %d)",SBAScorr->UDREI,options->UDREIthreshold);
			break;
		default:
			break;
	}

	sprintf(printbufferSBASUNSEL[satIndex],"SBASUNSEL   %4s %3s %3s %3d %17s %4d %9.2f %3d %2d \"%s\"\n",
	/*2*/		receiverid,
	/*3*/		SBASnavmode2SBASnavstr(options->precisionapproach),
	/*4*/		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
	/*5*/		epoch->sat[satIndex].PRN,
	/*6*/		t2doystr(&epoch->t),		//Year
	/*7*/						//DoY
	/*8*/						//Seconds of day
	/*9*/		GPSweek,
	/*10*/		SoW,
	/*11*/		GEOPRN,
	/*12*/		errorcode,
	/*13*/		errorstr[errorcode]);

	//Check if satellite has reached steady-state operation. If not, put an '*' to indicate that it will not be used
	if(options->excludeSmoothingConvergence > 0 && epoch->cycleslip.arcLength[j] < options->excludeSmoothingConvergence) {
		//Steady state not reached
		printbufferSBASUNSEL[satIndex][9]='*';
	}

	if(options->printInBuffer!=1) {
		fprintf(options->outFileStream,"%s",printbufferSBASUNSEL[satIndex]);
		printbufferSBASUNSEL[satIndex][0]='\0';
	}
}
 
/*****************************************************************************
 * Name        : printSBASOUT
 * Description : Prints the solution information for SBAS
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Solution of the filter
 * TSBASdata *SBASdata             I  N/A  Struct with SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 *****************************************************************************/
void printSBASOUT (TEpoch *epoch, TFilterSolution *solution, TSBASdata *SBASdata, TOptions *options, TUnkinfo *unkinfo) {
	int			i,j;
	int			GPSweek;
	double		SoW;
	static int	initialized=0;
	static char	receiverid[5];

	double		positionNEU[3];
	double		dNEU[3];
	int 		indx;
	
	if(options->printSBASOUT==0) return;

	//Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);


	if (initialized==0) {
		initialized=1;
		//Convert receiver name to lower case
		for(i=0;i<4;i++) {
			receiverid[i]=tolower(epoch->receiver.name[i]);
		}
		receiverid[4]='\0';
	}

	// First index of XYZ
	indx = unkinfo->par2unk[DR_UNK];
	
	// Obtaing NEU coordinates
	XYZ2NEU(&solution->x[indx],positionNEU);
	
	// Compute:
	//		dNEU differences in relation to apriori position
	if ( epoch->receiver.OUTPUTDiffFieldsMode == CalculateWithRefFile ) {
		for (i=0;i<3;i++) {
			dNEU[i] = 0;
			for (j=0;j<3;j++) {
				dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
			}
		}
	} else { 
		for (i=0;i<3;i++) {
			dNEU[i] = 0;
			for (j=0;j<3;j++) {
				dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
			}
		}
	}
	
	if (epoch->receiver.RefPositionAvail==0) {
		for (i=0;i<3;i++) {
			dNEU[i] = 0;
		}
	}

	fprintf(options->outFileStream,"SBASOUT     %4s %3s %17s %4d %9.2f %3d %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %14.4f %2d %2d", 
	/*2*/		receiverid,
	/*3*/		SBASnavmode2SBASnavstr(epoch->SBASUsedMode),
	/*4*/		t2doystr(&epoch->t),
	/*5*/
	/*6*/
	/*7*/		GPSweek,
	/*8*/		SoW,
	/*9*/		epoch->SBASUsedGEO,
	/*10*/		dNEU[0],	// North error (Meters)
	/*11*/		dNEU[1],	// East error (Meters)
	/*12*/		dNEU[2],	// Up error (Meters)
	/*13*/		sqrt(dNEU[0]*dNEU[0]+dNEU[1]*dNEU[1]),	//Horizontal positioning error (Metres)
	/*14*/		solution->HPL,		// Horizontal protection level (Metres)
	/*15*/		fabs(dNEU[2]),		// Vertical positioning error (Metres)
	/*16*/		solution->VPL,		// Vertical protection level (Metres)
	/*17*/		solution->x[unkinfo->par2unk[DT_UNK]],	// Receiver clock offset (Metres)
	/*18*/		epoch->numSatSolutionSBAS+epoch->numSatnotUsedSBAS,	// Number of satellites in view that can be used for SBAS
	/*19*/		epoch->numSatSolutionSBAS);	// Number of satellites used to compute the solution

	// Print list of PRN used to compute the solution in SBAS
	for (i=0;i<epoch->numSatSolutionSBAS;i++) {	
		fprintf(options->outFileStream," +%c%02d",epoch->listConsSatSolutionSBAS[i],epoch->listPRNSatSolutionSBAS[i]);
	}

	// Print list of PRN not used to compute the solution but are suitable for SBAS
	for (i=0;i<epoch->numSatnotUsedSBAS;i++) {	
		fprintf(options->outFileStream," -%c%02d",epoch->listConsSatnotUsedSBAS[i],epoch->listPRNSatnotUsedSBAS[i]);
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
	int i, j;

	if ( options->printDGNSS == 1 ) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			if ( printbufferDGNSS[i][0] == '\0' ) continue;
			if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
				printbufferDGNSS[i][5] = '*';
				fprintf(options->outFileStream,"%s",printbufferDGNSS[i]);
			} else if ( options->printInBuffer == 2 ) {
				fprintf(options->outFileStream,"%s",printbufferDGNSS[i]);
			}
			printbufferDGNSS[i][0] = '\0';
		}
	}

	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( printbufferMODEL[i][0] == '\0' ) continue;
		if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
			printbufferMODEL[i][5] = '*';
			fprintf(options->outFileStream,"%s",printbufferMODEL[i]);
		} else if ( options->printInBuffer == 2 ) {
			fprintf(options->outFileStream,"%s",printbufferMODEL[i]);
		}
		printbufferMODEL[i][0] = '\0';
	}

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

	if ( options->printSatSel == 1 ) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			for ( j=0;j<linesstoredSATSEL[i];j++ ) {
				if ( printbufferSATSEL[i][j][0] == '\0' ) continue;
				if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
					printbufferSATSEL[i][j][6] = '*';
					fprintf(options->outFileStream,"%s",printbufferSATSEL[i][j]);
				} else if ( options->printInBuffer == 2 ) {
					fprintf(options->outFileStream,"%s",printbufferSATSEL[i][j]);
				}
				printbufferSATSEL[i][j][0] = '\0';
			}
			linesstoredSATSEL[i]=0;
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
	int i;

	
	for (i=0;i<epoch->numSatellites;i++) {
		if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
			printbufferPREFIT[i][6] = '*';
			fprintf(options->outFileStream,"%s",printbufferPREFIT[i]);
		} else if ( options->printInBuffer == 2 ) {
			fprintf(options->outFileStream,"%s",printbufferPREFIT[i]);
		}
		printbufferPREFIT[i][0]='\0';
	}

	if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
		printbufferEPOCHSAT[8] = '*';
		fprintf(options->outFileStream,"%s",printbufferEPOCHSAT);
	} else if ( options->printInBuffer == 2 ) {
		fprintf(options->outFileStream,"%s",printbufferEPOCHSAT);
	}
	printbufferEPOCHSAT[0]='\0';

	for (i=0;i<epoch->numSatellites;i++) {
		if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
			printbufferPOSTFIT[i][7] = '*';
			fprintf(options->outFileStream,"%s",printbufferPOSTFIT[i]);
		} else if ( options->printInBuffer == 2 ) {
			fprintf(options->outFileStream,"%s",printbufferPOSTFIT[i]);
		}
		printbufferPOSTFIT[i][0]='\0';
	}

	if ( options->printInBuffer == 3 && options->printSBASUNUSED == 1 ) {
		printbufferFILTER[6] = '*';
		fprintf(options->outFileStream,"%s",printbufferFILTER);
	} else if ( options->printInBuffer == 2 ) {
		fprintf(options->outFileStream,"%s",printbufferFILTER);
	}
	printbufferFILTER[0]='\0';
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

	int i, j, k;

	if ( options->printSBASUNUSED == 1 ) {
		for(k=0;k<epoch->Buffer_NumDataStored;k++) {
			if (k==selected) continue;
			//Print data for unselected iterations
			for ( i=0;i<epoch->numSatellites;i++ ) {
				if ( epoch->Buffer_printMODEL[k][i][0] == '\0' ) continue;
				epoch->Buffer_printMODEL[k][i][5] = '*';
				fprintf(options->outFileStream,"%s",epoch->Buffer_printMODEL[k][i]);
			}

			for ( i=0;i<epoch->numSatellites;i++ ) {
				if ( epoch->Buffer_printSBASIONO[k][i][0] == '\0' ) continue;
				epoch->Buffer_printSBASIONO[k][i][8] = '*';
				fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASIONO[k][i]);
			}

			for ( i=0;i<epoch->numSatellites;i++ ) {
				if ( epoch->Buffer_printSBASCORR[k][i][0] == '\0' ) continue;
				epoch->Buffer_printSBASCORR[k][i][8] = '*';
				fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASCORR[k][i]);
			}

			for ( i=0;i<epoch->numSatellites;i++ ) {
				if ( epoch->Buffer_printSBASVAR[k][i][0] == '\0' ) continue;
				epoch->Buffer_printSBASVAR[k][i][7] = '*';
				fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASVAR[k][i]);
			}

			for ( i=0;i<epoch->numSatellites;i++ ) {
				if ( epoch->Buffer_printSBASUNSEL[k][i][0] == '\0' ) continue;
				epoch->Buffer_printSBASUNSEL[k][i][9] = '*';
				fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASUNSEL[k][i]);
			}

			if ( options->printSatSel == 1 ) {
				for ( i=0;i<epoch->numSatellites;i++ ) {
					for ( j=0;j<epoch->Buffer_NumSatSel[k][i];j++ ) {
						if ( epoch->Buffer_printSATSEL[k][i][j][0] == '\0' ) continue;
						epoch->Buffer_printSATSEL[k][i][j][6] = '*';
						fprintf(options->outFileStream,"%s",epoch->Buffer_printSATSEL[k][i][j]);
					}
				}
			}
		}
	}

	if (prevGEOPRN!=epoch->currentGEOPRN) {
		sprintf(messagestr,"Switched from GEO %3d to GEO %3d at epoch %17s",prevGEOPRN,epoch->Buffer_GEOPRN[selected],t2doystr(&epoch->t));
		printInfo(messagestr,options);
	}

	//Print data for selected iteration
	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->Buffer_printMODEL[selected][i][0] != '\0' ) {
			fprintf(options->outFileStream,"%s",epoch->Buffer_printMODEL[selected][i]);
		}
	}

	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->Buffer_printSBASIONO[selected][i][0] != '\0' ) {
			fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASIONO[selected][i]);
		}
	}

	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->Buffer_printSBASCORR[selected][i][0] != '\0' ) {
			fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASCORR[selected][i]);
		}
	}

	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->Buffer_printSBASVAR[selected][i][0] != '\0' ) {
			fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASVAR[selected][i]);
		}
	}

	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->Buffer_printSBASUNSEL[selected][i][0] != '\0' ) {
			fprintf(options->outFileStream,"%s",epoch->Buffer_printSBASUNSEL[selected][i]);
		}
	}

	if ( options->printSatSel == 1 ) {
		for ( i=0;i<epoch->numSatellites;i++ ) {
			for ( j=0;j<epoch->Buffer_NumSatSel[selected][i];j++ ) {
				if ( epoch->Buffer_printSATSEL[selected][i][j][0] != '\0' ) {
					fprintf(options->outFileStream,"%s",epoch->Buffer_printSATSEL[selected][i][j]);
				}
			}
		}
	}


	//Print INFO messages with the available solutions and their protections levels
	for(i=0;i<epoch->Buffer_NumDataStored;i++) {
		if(i==selected) continue; //Selected iteration will be printed the last one
		sprintf(messagestr,"%17s Solution available with GEO %3d in %sPA mode, HPL: %6.2f VPL: %6.2f (Not selected)",t2doystr(&epoch->t),epoch->Buffer_GEOPRN[i],epoch->Buffer_SBASMode[i]==PAMODE?"":"N",epoch->Buffer_HPL[i],epoch->Buffer_VPL[i]);
		printInfo(messagestr,options);
	}
	sprintf(messagestr,"%17s Solution available with GEO %3d in %sPA mode, HPL: %6.2f VPL: %6.2f (Selected)",t2doystr(&epoch->t),epoch->Buffer_GEOPRN[selected],epoch->Buffer_SBASMode[selected]==PAMODE?"":"N",epoch->Buffer_HPL[selected],epoch->Buffer_VPL[selected]);
	printInfo(messagestr,options);

	//Save GEO PRN for printing in SBASOUT message
	epoch->SBASUsedGEO=epoch->Buffer_GEOPRN[selected];
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
	int			i;
	int			GPSweek;
	double		SoW;

	//Calculate GPS Week and Seconds of Week
	ttime2gpswsnoroll(&epoch->t,&GPSweek,&SoW);

	for (i=0;i<numpos;i++) {
		fprintf(options->outFileStream,"USERADDEDERROR   %17s %4d %9.2f %3s %2d %3s %14.4f %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f %2d %14.4f\n",
		/*2*/			t2doystr(&epoch->t),
		/*3*/
		/*4*/
		/*5*/			GPSweek,
		/*6*/			SoW,
		/*7*/			gnsstype2gnssstr((int)SatMeasError[i][USRGNSSPOS]),	//GNSS system
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
}

/*****************************************************************************
 * Name        : writeStdESA
 * Description : Writes the Stanford-ESA plot values into a file
 * Parameters  :
 * Name                                    |Da|Unit|Description
 * FILE *fd                                 I  N/A  File descriptor where data is written
 * TStdESA *StdESA                          I  N/A  TStdESA struct                                        
 * TOptions  *options                       I  N/A  TOptions structure
 *****************************************************************************/
void writeStdESA (FILE *fd, TStdESA *StdESA, TOptions *options) {
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
				fprintf(fd,"%6.3f %6.3f %8d %8d\n",posx,posy,StdESA->counthor[i][j],StdESA->countver[i][j]);
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

	j = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
	sprintf( printbufferDGNSS[satIndex], "DGNSS     %17s %3s %2d %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
		t2doystr(&epoch->t),
		gnsstype2gnssstr(epoch->sat[satIndex].GNSS),
		epoch->sat[satIndex].PRN,
		epochDGNSS->dgnss.PRC[j],	// PRC
		epochDGNSS->dgnss.RRC[j],	// RRC
		dt,							// delta time for RRC
		deltaPRC,					// delta PRC
		deltaRRC,					// delta RRC
		dt2,						// delta time for RRC
		sigmas[0],					// Total sigma
		sigmas[1],					// Sigma UDRE
		sigmas[2],					// Sigma degradation
		sigmas[3],					// Sigma air
		sigmas[4],					// Sigma multipath
		sigmas[5]					// Sigma inflation
		);

	if ( options->printInBuffer != 1 ) {
		fprintf(options->outFileStream,"%s",printbufferDGNSS[satIndex]);
		printbufferDGNSS[satIndex][0]='\0';
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
	char	monthname[10];

	if ( options->rinexVersion == 2 ) fprintf(fd,"%9.2f%11s%-20s%-20s%-20s\n",2.11,"","OBSERVATION DATA","G (GPS)","RINEX VERSION / TYPE");
	if ( options->rinexVersion == 3 ) fprintf(fd,"%9.2f%11s%-20s%-20s%-20s\n",3.00,"","OBSERVATION DATA","G (GPS)","RINEX VERSION / TYPE");
	getcurrentsystemtime(&tm);      // Get current system time
	MonthName(tm.tm_mon+1,monthname);
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
			strcpy(c1,"C1P"); strcpy(l1,"L1P"); strcpy(s1,"S1P");
		}
		if ( rtcm3->msg1004[0].l2_code_indicator == 0 ) {
			strcpy(c2,"C2C"); strcpy(l2,"L2C"); strcpy(s2,"S2C");
		} else {
			strcpy(c2,"C2P"); strcpy(l2,"L2P"); strcpy(s2,"S2P");
		}
		fprintf(fd,"%1s%2s%3d%1s%3s%1s%3s%1s%3s%1s%3s%1s%3s%1s%3s%30s%-20s\n","G","",6,"",c1,"",l1,"",s1,"",c2,"",l2,"",s2,"","SYS / # / OBS TYPES");
	}
}

/*****************************************************************************
 * Name        : writeRINEXo
 * Description : Write a RINEX observation from a RTCM binary file
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
	int 			*year;
	double 			*doy;
	TTime 			*t;
	static double 	AntPosX=0.,AntPosY=0.,AntPosZ=0.;


	// Time handling
	totalSeconds = rtcm3->header.epoch_time/1000;
	totalSeconds = totalSeconds-(86400*floor(totalSeconds/86400));
	// Hours
	hour_d = (double)totalSeconds/3600.0;
	*rtcm3->hour = (int)floor(hour_d);
	intHour = (int)floor(hour_d);
	doubleHour = (double)floor(hour_d);
	// Minutes
	mins_d = (double)(hour_d-doubleHour)*60.0;
	mins = floor(mins_d);
	// Seconds
	sec = (double)(mins_d-mins)*60.0;

	// Check if a day has passed
	if ( rtcm3->doWeHaveHeader > 2 && intHour < (int)*rtcm3->previousHour ) {
		t = malloc(sizeof(TTime));
		year = malloc(sizeof(int));
		doy = malloc(sizeof(double));

		*year = (int)options->rtcmYear;
		*doy = (double)options->rtcmDoy;

		*t = cal2t(*year, options->rtcmMonth, options->rtcmDay, 0, 0, 0);
		t->MJDN++;
		t2doy(t, year, doy);
		options->rtcmYear = *year;
		doy2date(*year, (int)*doy, &options->rtcmMonth, &options->rtcmDay);
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
		*rtcm3->hour = (int)floor(hour_d);
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
	*rtcm3->previousHour = intHour;
}

/*****************************************************************************
 * Name        : writeRTCM2ascii
 * Description : write the decoded information into an output file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd_antenna                O  N/A  The pointer of the antenna output file
 * FILE *fd_corrections            O  N/A  The pointer of the data output file
 * TRTCM2 *rtcm2                   IO N/A  TRTCM2 structure
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * TEpoch  *epochDGNSS             O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
int writeRTCM2ascii (FILE *fd_antenna, FILE *fd_corrections, TRTCM2 *rtcm2, TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options) {
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
	TMSG1		sc1[ns];
	TMSG2		sc2[ns];
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
 * FILE  *roverfd                  I  N/A  File descriptor for input RINEX file
 * FILE  *outfd                    O  N/A  File descriptor for output RINEX file
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void writeObsRinexEpochUserAddedError (FILE *roverfd, FILE *outfd, TEpoch *epoch, TOptions *options) {

    int		 	i,j;
	int			numsat;
	double		SecondsComp;
	struct tm	tm;
	char        line[MAX_INPUT_LINE];
	char		aux[100];
	int         len = 0;


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
				} else if (epoch->sat[i].meas[j].LLI==0 && epoch->sat[i].meas[j].SNR==0 ) {
					fprintf(outfd,"%14.3f  ",epoch->sat[i].meas[j].value);
				} else if (epoch->sat[i].meas[j].LLI==0) {
					fprintf(outfd,"%14.3f %d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].SNR);
				} else if (epoch->sat[i].meas[j].SNR==0) {
					fprintf(outfd,"%14.3f%d ",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI);
				} else {
					fprintf(outfd,"%14.3f%d%d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI,epoch->sat[i].meas[j].SNR);
				}
			}
			fprintf(outfd,"\n");
		}
	} else {
		//To be erased in future versions: re-read epoch in order to print data from not supported satellites
		rewindEpochRinexObs(roverfd,epoch->source);
		getL(line,&len,roverfd);
		fprintf(outfd,"%s",line);
		getstr(aux,line,33,2);
		numsat = atoi(aux);
		for(i=0;i<numsat;i++) {
			getL(line,&len,roverfd);
			//Print data for not supported constellations
			if(line[0]=='C' || line[0]=='I'|| line[0]=='J') {
				fprintf(outfd,"%s",line);
			}
		}
		//End to be erased
		//Header generated by gLAB (when gLAB can handle all measurements)
		//fprintf(outfd,"> %4d %02d %02d %02d %02d%11.7f  %d%3d%6s %15s\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,0,epoch->numSatellites,"","");
		//Print measurements
		for (i=0;i<epoch->numSatellites;i++) {
			fprintf(outfd,"%c%02d",gnsstype2char(epoch->sat[i].GNSS),epoch->sat[i].PRN);
			for(j=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurements;j++) {
				if (epoch->sat[i].meas[j].value==-1) {
					//If measurement is not available, print blank spaces
					fprintf(outfd,"%16s","");
				} else if (epoch->sat[i].meas[j].LLI==0 && epoch->sat[i].meas[j].SNR==0 ) {
					fprintf(outfd,"%14.3f  ",epoch->sat[i].meas[j].value);
				} else if (epoch->sat[i].meas[j].LLI==0) {
					fprintf(outfd,"%14.3f %d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].SNR);
				} else if (epoch->sat[i].meas[j].SNR==0) {
					fprintf(outfd,"%14.3f%d ",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI);
				} else {
					fprintf(outfd,"%14.3f%d%d",epoch->sat[i].meas[j].value,epoch->sat[i].meas[j].LLI,epoch->sat[i].meas[j].SNR);
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
			initMJDN=epoch->firstepoch.MJDN;
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
	int					GPSWeek;
	int					indx;
	double				SoW,seconds;
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

		// Calculate GPS Week and Seconds of Week for first epoch
		ttime2gpswsnoroll(&epoch->t, &GPSWeek, &SoW);

		// Get the calendar time for first epoch
		t2tmnolocal(&epoch->t,&tm,&seconds);

		fprintf(fd,"#cP%4d %2d %2d %2d %2d %11.8f -------     u WGS84 BCT gLAB\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,fabs(modulo(epoch->t.SoD,60)));
		fprintf(fd,"## %4d %15.8f %14.8f %5d %15.13f\n",GPSWeek,SoW,datainterval,epoch->t.MJDN,epoch->t.SoD/86400.);
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

	int			GPSWeek;
	int			indx;
	int			year;
	double		SoW;
	double		coordNEU[3];
	double		doy;
	double		seconds;
	struct tm	tm;

	// First index of XYZ
	indx = unkinfo->par2unk[DR_UNK];

	if (options->GPSWeekRefFile==1) {
		// Calculate GPS Week and Seconds of Week for first epoch
		ttime2gpswsnoroll(&epoch->t, &GPSWeek, &SoW);
		//Take out decimals from third decimal (to avoid 0.999 .001 bad timestamps)
		if ((SoW-(double)((int)(SoW)))>0.999) {
			seconds=(double)((int)(SoW))+1.;
		} else {
			seconds=SoW;
		}
		if (options->GeodeticCoordRefFile==1) {
			XYZ2NEU(&solution->x[indx],coordNEU);
			fprintf(fd,"%4d %10.3f %14.9f %14.9f %14.4f\n",GPSWeek,seconds,coordNEU[1]*r2d,coordNEU[0]*r2d,coordNEU[2]);
		} else {
			fprintf(fd,"%4d %10.3f %14.4f %14.4f %14.4f\n",GPSWeek,seconds,solution->x[indx+0],solution->x[indx+1],solution->x[indx+2]);
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
 * Name                           |Da|Unit|Description
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TSBASdatabox *SBASdatabox       I  N/A  Struct with SBAS data and summary
 * TStdESA *StdESA                 I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSBASSummary (int UseReferenceFile, TEpoch *epoch, TSBASdatabox *SBASdatabox,  TStdESA *StdESA, TOptions *options) {

	int			i;
	int			GPSWeek;
	int			percentileSamples;
	int			year;
	int			NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation;
	int			NumEpochsDataGapSummary;
	int			PercentileDecimals=2,PercentileDigits=6;
	double		DataInterval;
	double 		SoW,DoY;
	double		RefPercentage;
	double		PAPercentage,NPAPercentage,PALimitsPercentage,RiskVal,RiskMarVal;
	double		NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double		MIEpochsPercentage,HMIEpochsPercentage,VMIEpochsPercentage;
	double		FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double		SamplesSolPercentage,SamplesSkippedPercentage,SamplesMIPercentage,SamplesHMIPercentage,SamplesVMIPercentage;
	double		NoRefSolEpochPercentage,NoRefSumEpochPercentage;
	double		TimeDiff;
	double		SecondsComp;
	char		receiverid[5];
	char		NPAletter[2];
	TTime		LastEpoch;
	struct tm   tm;

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
		memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
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
		NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstepoch)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
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
		epoch->MaxHError=0.;
		epoch->MaxVError=0.;
		epoch->HDOPPercentileSamples=0.;
		epoch->PDOPPercentileSamples=0.;
		epoch->GDOPPercentileSamples=0.;
		epoch->TDOPPercentileSamples=0.;
		epoch->VDOPPercentileSamples=0.;
		SBASdatabox->MaxHPL=0.;
		SBASdatabox->MaxVPL=0.;
		SBASdatabox->HWIR=0.;
		SBASdatabox->VWIR=0.;
	} else {
		if (epoch->TotalEpochsRef==0) {
			epoch->MaxHError=0.;
			epoch->MaxVError=0.;
			SBASdatabox->HWIR=0.;
			SBASdatabox->VWIR=0.;
		} else {
			if (options->recPosProvided==1) {
				if(options->percentile==100.) {
					percentileSamples=epoch->TotalEpochsRef-1;
				} else {
					percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
				}
				//Compute HPE percentile of the samples
				qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
				//Compute VPE percentile of the samples
				qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
				epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
			}
		}
		if(options->percentile==100.) {
			percentileSamples=SBASdatabox->TotalPAEpochs-1;
		} else {
			percentileSamples=(int)((double)(SBASdatabox->TotalPAEpochs)*options->percentile/100.);
		}
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
		} else {
			 fprintf(options->outFileStream,"INFO No data available in observation file\n");
		}
	} else {
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
	fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution: %d ( %.3f%% )\n",NPAletter,SBASdatabox->TotalPAEpochs,PAPercentage);

	//Print total epochs with PA solution and under alarm limits
	fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution under alarm limits: %d ( %.3f%% )\n",NPAletter,SBASdatabox->TotalPAEpochsAvail,PALimitsPercentage);

	if (options->UserForcedNPA==0 && options->switchmode==1) {
		//Print NPA epochs if user didn't force the use of NPA and mode switching is enabled
		fprintf(options->outFileStream,"INFO Total epochs processed with NPA solution: %d ( %.3f%% )\n",SBASdatabox->TotalNPAEpochs,NPAPercentage);
	}

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (UseReferenceFile==1) {
	   	if (options->receiverPositionSource != rpSETREF) {
			fprintf(options->outFileStream,"INFO Total epochs processed with %sPA solution and position from reference file: %d ( %.3f%% )\n",NPAletter,epoch->TotalEpochsRef,RefPercentage);
			fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.3f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to no position from reference file for modelling: %d ( %.3f%% )\n",epoch->NumNoRefSolSkipped,NoRefSolEpochPercentage);
		}
	}

	//Print epochs skipped due to lack of satellites
	fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.3f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage);

	//Print epochs skipped due to singular geometry matrix
	fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.3f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.3f%% )\n",epoch->NumNoRefSolSkipped+epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumDOPSkipped,NoRefSolEpochPercentage+FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage);

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
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapTotal),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d\n",epoch->MaxDataGapSizeTotal);
	}

	if(SBASdatabox->TotalPAEpochs!=0) {
		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->PDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->PDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->PDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->GDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->GDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->GDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->TDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->TDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->HDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->HDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->VDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->VDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
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
				fprintf(options->outFileStream,"INFO No epochs with solution %sfor computing MIs, PE, PL%s percentiles%s\n",UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?",":" and",options->stanfordesa==1?" and Stanford-ESA statistics":"");
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
		fprintf(options->outFileStream,"INFO Total epochs with MIs: %d ( %.3f%% )\n",SBASdatabox->NumMI,MIEpochsPercentage);

		//Print number of Horizontal MIs
		fprintf(options->outFileStream,"INFO Total epochs with Horizontal MIs: %d ( %.3f%% )\n",SBASdatabox->NumHMI,HMIEpochsPercentage);

		//Print number of Vertical MIs
		fprintf(options->outFileStream,"INFO Total epochs with Vertical   MIs: %d ( %.3f%% )\n",SBASdatabox->NumVMI,VMIEpochsPercentage);
	}

	//Print epochs skipped due to bad GDOP
	if(options->stanfordesa==1) {
		//Print total geometries processed
		fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %d\n",StdESA->numsamplesProcessed);

		//Print total geometries with solution
		if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
			//If percentage is 100%, print 100.000% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
		} else if (SamplesSolPercentage>=99.999) {
			//This is to avoid printing 1.00E+02% when rounding 99.999%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( 99.999%% )\n",StdESA->numsamplesComputed);
		} else {
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
		}

		//Print epochs skipped due to singular geometry matrix
		if(SamplesSkippedPercentage==0.) {
			//If percentage is 0, print 0.000% instead of 0.000E+00%
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
		}

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			//Print number of MIs for Stanford-ESA
			if(SamplesMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with MIs: %d ( %.3f%% )\n",StdESA->numsamplesMI,SamplesMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with MIs: %d ( %.3E%% )\n",StdESA->numsamplesMI,SamplesMIPercentage);
			}

			//Print number of Horizontal MIs for Stanford-ESA
			if(SamplesHMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Horizontal MIs: %d ( %.3f%% )\n",StdESA->numsamplesHMI,SamplesHMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Horizontal MIs: %d ( %.3E%% )\n",StdESA->numsamplesHMI,SamplesHMIPercentage);
			}

			//Print number of Vertical MIs for Stanford-ESA
			if(SamplesVMIPercentage==0.) {
				//If percentage is 0, print 0.000% instead of 0.000E+00%
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Vertical   MIs: %d ( %.3f%% )\n",StdESA->numsamplesVMI,SamplesVMIPercentage);
			} else {
				fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA with Vertical   MIs: %d ( %.3E%% )\n",StdESA->numsamplesVMI,SamplesVMIPercentage);
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
		}
		//Print Horizontal protection level Percentile
		fprintf(options->outFileStream,"INFO Horizontal %*.*f Protection  Level Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->HPLPercentileSamples);

		//Print Vertical protection level Percentile
		fprintf(options->outFileStream,"INFO Vertical   %*.*f Protection  Level Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,SBASdatabox->VPLPercentileSamples);

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			// Print value and epoch with highest horizontal error
			ttime2gpswsnoroll(&epoch->HerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->HerrorEpoch,&tm, &SecondsComp);
			fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HerrorEpoch),GPSWeek,SoW);

			// Print value and epoch with highest vertical error
			ttime2gpswsnoroll(&epoch->VerrorEpoch, &GPSWeek, &SoW);
			t2tmnolocal(&epoch->VerrorEpoch,&tm, &SecondsComp);
			fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VerrorEpoch),GPSWeek,SoW);
		}

		// Print value and epoch with highest horizontal protection level
		ttime2gpswsnoroll(&SBASdatabox->MaxHPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MaxHPLEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum Horizontal Protection  Level: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MaxHPL,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MaxHPLEpoch),GPSWeek,SoW);

		// Print value and epoch with highest vertical error
		ttime2gpswsnoroll(&SBASdatabox->MaxVPLEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->MaxVPLEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum Vertical   Protection  Level: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->MaxVPL,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->MaxVPLEpoch),GPSWeek,SoW);

		if(options->recPosProvided==1 && epoch->TotalEpochsRef!=0) {
			// Print value and epoch with worst horizontal integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->HWIREpoch, &GPSWeek, &SoW);
		t2tmnolocal(&SBASdatabox->HWIREpoch,&tm, &SecondsComp);
			fprintf(options->outFileStream,"INFO Worst Horizontal Integrity Ratio: %7.4f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->HWIR,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->HWIREpoch),GPSWeek,SoW);

			// Print value and epoch with worst vertical integrity ratio
			ttime2gpswsnoroll(&SBASdatabox->VWIREpoch, &GPSWeek, &SoW);
			t2tmnolocal(&SBASdatabox->VWIREpoch,&tm, &SecondsComp);
			fprintf(options->outFileStream,"INFO Worst Vertical   Integrity Ratio: %7.4f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",SBASdatabox->VWIR,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&SBASdatabox->VWIREpoch),GPSWeek,SoW);
		}
	}

	// Print MIs, percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	fprintf(options->outFileStream,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HWIR: %7.4f VWIR: %7.4f MIs: %3d Hor_MIs: %3d Ver_MIs: %3d HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f HPL_Percentile: %*.*f %6.2f VPL_Percentile: %*.*f %6.2f MaxHPL: %6.2f MaxVPL: %6.2f Avail%%: %7.3f Cont_Risk: %6.4E HWIR_ESA: %7.4f VWIR_ESA: %7.4f MIs_ESA: %4d Hor_MIs_ESA: %4d Ver_MIs_ESA: %4d Cont_Risk_Mark: %6.4E PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s\n",
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

/*****************************************************************************
 * Name        : printDGNSSSummary
 * Description : print DGNSS summary at the end of the output file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TEpoch  *epochDGNSS             I  N/A  TEpoch structure from reference station
 * TStdESA *StdESA                 I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printDGNSSSummary (int UseReferenceFile, TEpoch *epoch, TEpoch *epochDGNSS, TStdESA *StdESA, TOptions *options) {

    int         i;
    int         GPSWeek;
    int         percentileSamples;
	int			year;
	int			NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation;
	int			NumEpochsDataGapSummary;
	int			PercentileDecimals=2,PercentileDigits=6;
	double		DataInterval;
	double 		SoW,DoY;
	double		DGNSSPercentage,SPPPercentage,RefPercentage;
	double		FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double		NoRefSumEpochPercentage;
    double      SamplesSolPercentage,SamplesSkippedPercentage;
	double		SecondsComp;
    char        receiverid[5];
	TTime		LastEpoch;
	struct tm   tm;

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
        epoch->MaxHError=0.;
        epoch->MaxVError=0.;
        //epoch->HPEPercentileValues=0.;
        //epoch->VPEPercentileValues=0.;
        epoch->HPEPercentileSamples=0.;
        epoch->VPEPercentileSamples=0.;
    } else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsRef-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
		}
        if (options->recPosProvided==1) {
            //Compute HPE percentile of the samples
            qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
            //Compute VPE percentile of the samples
            qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
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
		memcpy(&LastEpoch,&epoch->t,sizeof(TTime));
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
		NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpoch,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstepoch)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
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
	} else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsDGNSS-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsDGNSS)*options->percentile/100.);
		}
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
		} else {
			 fprintf(options->outFileStream,"INFO No data available in observation file\n");
		}
	} else {
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
    fprintf(options->outFileStream,"INFO Total epochs processed with DGNSS solution: %d ( %.3f%% )\n",epoch->TotalEpochsDGNSS,DGNSSPercentage);

    //Print total epochs with SPP solution
    fprintf(options->outFileStream,"INFO Total epochs processed with SPP solution: %d ( %.3f%% )\n",epoch->TotalEpochsSPP,SPPPercentage);

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (UseReferenceFile==1) {
		fprintf(options->outFileStream,"INFO Total epochs processed with DGNSS solution and position from reference file: %d ( %.3f%% )\n",epoch->TotalEpochsRef,RefPercentage);
		fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.3f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage);
	}

    //Print epochs skipped due to lack of satellites
    fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.3f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage);

    //Print epochs skipped due to singular geometry matrix
    fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.3f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.3f%% )\n",epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumDOPSkipped,FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage);

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
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (during summary period):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in rover observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
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
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (during summary period): %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epochDGNSS->DataGapSum),GPSWeek,SoW);
		} else {
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (during summary period): %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeSum);
		}

		if (epochDGNSS->MaxDataGapSizeTotal>0) {
			//Print maximum data gap size in file of reference station
			ttime2gpswsnoroll(&epochDGNSS->DataGapTotal, &GPSWeek, &SoW);
			t2tmnolocal(&epochDGNSS->DataGapTotal,&tm, &SecondsComp);
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (all the file):          %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epochDGNSS->DataGapTotal),GPSWeek,SoW);
		} else {
			fprintf(options->outFileStream,"INFO Maximum data gap size in reference station %s file (all the file):          %3d\n",options->RTCMmode==ProcessRTCM3?"RTCM3":"RINEX observation",epochDGNSS->MaxDataGapSizeTotal);
		}
	}
		

    if(epoch->TotalEpochsDGNSS!=0) {
		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->PDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->PDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->PDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->GDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->GDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->GDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->TDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->TDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->HDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->HDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->VDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->VDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
	}

    if(options->recPosProvided==1) {
		if (epoch->TotalEpochsRef==0) {
				fprintf(options->outFileStream,"INFO No epochs with DGNSS solution %sfor computing positioning error percentiles%s\n",UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?" and Stanford-ESA statistics":"");
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
        fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %d\n",StdESA->numsamplesProcessed);

        //Print total geometries with solution
        if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
            //If percentage is 100%, print 100.000% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        } else if (SamplesSolPercentage>=99.999) {
            //This is to avoid printing 1.00E+02% when rounding 99.999%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( 99.999%% )\n",StdESA->numsamplesComputed);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        }

        //Print epochs skipped due to singular geometry matrix
        if(SamplesSkippedPercentage==0.) {
            //If percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        }
    }

    if(epoch->TotalEpochsDGNSS!=0) {
        if(options->recPosProvided==1) {
			if (epoch->TotalEpochsRef!=0) {	
        	    //Print Horizontal error Percentile
        	    fprintf(options->outFileStream,"INFO Horizontal %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HPEPercentileSamples);

            	//Print Vertical error Percentile
	            fprintf(options->outFileStream,"INFO Vertical   %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VPEPercentileSamples);

    	        // Print value and epoch with highest horizontal error
       		    ttime2gpswsnoroll(&epoch->HerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->HerrorEpoch,&tm, &SecondsComp);
           		fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HerrorEpoch),GPSWeek,SoW);

            	// Print value and epoch with highest vertical error
            	ttime2gpswsnoroll(&epoch->VerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->VerrorEpoch,&tm, &SecondsComp);
            	fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VerrorEpoch),GPSWeek,SoW);
			}
        }
    }

	// Print percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	fprintf(options->outFileStream,"INFO Rover: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f Avail%%: %7.3f PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Rover_Sum: %3d Epochs_missing_Rover_All_file: %3d Num_DataGaps_Rover_Sum: %3d Num_DataGaps_Rover_All_file: %3d MaxSize_DataGap_Rover_Sum: %3d MaxSize_DataGap_Rover_All_file: %3d Epochs_missing_Ref_Sum: %3d Epochs_missing_Ref_All_file: %3d Num_DataGaps_Ref_Sum: %3d Num_DataGaps_Ref_All_file: %3d MaxSize_DataGap_Ref_Sum: %3d MaxSize_DataGap_Ref_All_file: %3d Station_Network_Name: %s\n",
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

/*****************************************************************************
 * Name        : printSummary
 * Description : print summary at the end of the output file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TStdESA *StdESA                 I  N/A  Struct with the data from Stanford-ESA
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void printSummary (int UseReferenceFile, TEpoch *epoch, TStdESA *StdESA, TOptions *options) {

    int         i;
    int         GPSWeek;
    int         percentileSamples;
	int			year;
	int			NumEpochsSummaryPeriod,NumEpochsMissingSummary,NumEpochsMissingFile,NumEpochsMissingSumNoDecimation;
	int			NumEpochsDataGapSummary;
	int			PercentileDecimals=2,PercentileDigits=6;
	double		DataInterval;
	double 		SoW,DoY;
	double		SolPercentage,RefPercentage;
	double		FewSatEpochsPercentage,SingularEpochsPercentage,DOPEpochsPercentage,HDOPEpochsPercentage,PDOPEpochsPercentage,GDOPEpochsPercentage,HDOPorPDOPEpochsPercentage;
	double		NoRefSolEpochPercentage,NoRefSumEpochPercentage;
    double      SamplesSolPercentage,SamplesSkippedPercentage;
	double		SecondsComp;
    char        receiverid[5];
	TTime		LastEpoch,LastEpochDataGaps;
	struct tm   tm;

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
        epoch->MaxHError=0.;
        epoch->MaxVError=0.;
        //epoch->HPEPercentileValues=0.;
        //epoch->VPEPercentileValues=0.;
        epoch->HPEPercentileSamples=0.;
        epoch->VPEPercentileSamples=0.;
    } else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsRef-1;
		} else {
	        percentileSamples=(int)((double)(epoch->TotalEpochsRef)*options->percentile/100.);
		}
        if (options->recPosProvided==1) {
            //Compute HPE percentile of the samples
            qsort(epoch->HError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->HPEPercentileSamples=epoch->HError[percentileSamples];
            //Compute VPE percentile of the samples
            qsort(epoch->VError,epoch->TotalEpochsRef,sizeof(double),qsort_compare_double);
            epoch->VPEPercentileSamples=epoch->VError[percentileSamples];
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
			memcpy(&LastEpochDataGaps,&epoch->t,sizeof(TTime));
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
		if (options->filterIterations == 2) {
			NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpochDataGaps,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1-epoch->TotalEpochsForward-epoch->TotalEpochsDecimatedForward-NumEpochsMissingSummary;
		} else {
			NumEpochsMissingSumNoDecimation=(int)(tdiff(&LastEpochDataGaps,&epoch->StartSummaryEpoch)/epoch->receiver.interval)+1-epoch->TotalEpochs-epoch->TotalEpochsDecimated-NumEpochsMissingSummary;
		}
	} else {
		NumEpochsMissingSumNoDecimation=0;
	}

	//Get number of epochs missing in all the file
	if (epoch->t.MJDN!=-1) {
		if (options->filterIterations == 2) {
			NumEpochsMissingFile=(int)(tdiff(&epoch->BackwardTurningEpoch,&epoch->firstepoch)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
		} else {
			NumEpochsMissingFile=(int)(tdiff(&epoch->t,&epoch->firstepoch)/epoch->receiver.interval)+1-epoch->TotalEpochsFile;
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
	} else {
		if(options->percentile==100.) {
			percentileSamples=epoch->TotalEpochsSol-1;
		} else {
			percentileSamples=(int)((double)(epoch->TotalEpochsSol)*options->percentile/100.);
		}
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
		} else {
			 fprintf(options->outFileStream,"INFO No data available in observation file\n");
		}
	} else {
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
    fprintf(options->outFileStream,"INFO Total epochs processed with solution: %d ( %.3f%% )\n",epoch->TotalEpochsSol,SolPercentage);

	//Print total epochs with solution and reference position (for the case that reference position is not used for modelling)
	if (UseReferenceFile==1) {
	   	if (options->receiverPositionSource != rpSETREF) {
			fprintf(options->outFileStream,"INFO Total epochs processed with solution and position from reference file: %d ( %.3f%% )\n",epoch->TotalEpochsRef,RefPercentage);
			fprintf(options->outFileStream,"INFO Total epochs omitted in summary due to no position from reference file: %d ( %.3f%% )\n",epoch->NumNoRefSumSkipped,NoRefSumEpochPercentage);
		} else {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to no position from reference file for modelling: %d ( %.3f%% )\n",epoch->NumNoRefSolSkipped,NoRefSolEpochPercentage);
		}
	}

    //Print epochs skipped due to lack of satellites
    fprintf(options->outFileStream,"INFO Total epochs skipped due to less than 4 valid satellites available: %d ( %.3f%% )\n",epoch->NumNoSatSkipped,FewSatEpochsPercentage);

    //Print epochs skipped due to singular geometry matrix
    fprintf(options->outFileStream,"INFO Total epochs skipped due to singular geometry matrix: %d ( %.3f%% )\n",epoch->NumSingularMatrixSkipped,SingularEpochsPercentage);

	//Print epochs skipped due to DOP
	if (options->HDOPthreshold == 1 || options->PDOPthreshold == 1 || options->GDOPthreshold == 1) {
	    if(options->HDOPorPDOP == 1) {
			fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold:       %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
			
    	    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP and PDOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumHDOPorPDOPSkipped,HDOPorPDOPEpochsPercentage);
	    	if(options->GDOPthreshold == 1) {
    	    	fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:          %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
		    }
	    } else {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to any DOP exceeding the threshold: %d ( %.3f%% )\n",epoch->NumDOPSkipped,DOPEpochsPercentage);
		    if(options->HDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to HDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumHDOPSkipped,HDOPEpochsPercentage);
		    }
		    if(options->PDOPthreshold == 1) {
    		    fprintf(options->outFileStream,"INFO Total epochs skipped due to PDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumPDOPSkipped,PDOPEpochsPercentage);
		    }
			if(options->GDOPthreshold == 1) {
				fprintf(options->outFileStream,"INFO Total epochs skipped due to GDOP exceeding the threshold:    %d ( %.3f%% )\n",epoch->NumGDOPSkipped,GDOPEpochsPercentage);
			}
		}
	}

	//Print total number of epochs skipped
	fprintf(options->outFileStream,"INFO Total epochs skipped (any reason): %d ( %.3f%% )\n",epoch->NumNoRefSolSkipped+epoch->NumNoSatSkipped+epoch->NumSingularMatrixSkipped+epoch->NumDOPSkipped,NoRefSolEpochPercentage+FewSatEpochsPercentage+SingularEpochsPercentage+DOPEpochsPercentage);

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
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period%s):  %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->filterIterations==2?" -forward direction only-":"",epoch->MaxDataGapSizeSum,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapSum),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (during summary period):  %3d\n",epoch->MaxDataGapSizeSum);
	}

	if (epoch->MaxDataGapSizeTotal>0) {
		//Print maximum data gap size in file
		ttime2gpswsnoroll(&epoch->DataGapTotal, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->DataGapTotal,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):%s           %3d at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",options->filterIterations==2?"                         ":"",epoch->MaxDataGapSizeTotal,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->DataGapTotal),GPSWeek,SoW);
	} else {
		fprintf(options->outFileStream,"INFO Maximum data gap size in observation file (all the file):           %3d\n",epoch->MaxDataGapSizeTotal);
	}

	if(epoch->TotalEpochsSol!=0) {
		//Print DOP percentiles
		fprintf(options->outFileStream,"INFO PDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->PDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO GDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->GDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO TDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->TDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO HDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HDOPPercentileSamples);
		fprintf(options->outFileStream,"INFO VDOP %*.*f Percentile: %6.2f\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VDOPPercentileSamples);

		//Print PDOP max value
		ttime2gpswsnoroll(&epoch->PDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->PDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum PDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxPDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->PDOPEpoch),GPSWeek,SoW);
		//Print GDOP max value
		ttime2gpswsnoroll(&epoch->GDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->GDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum GDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxGDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->GDOPEpoch),GPSWeek,SoW);
		//Print TDOP max value
		ttime2gpswsnoroll(&epoch->TDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->TDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum TDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxTDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
		//Print HDOP max value
		ttime2gpswsnoroll(&epoch->HDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->HDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum HDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HDOPEpoch),GPSWeek,SoW);
		//Print VDOP max value
		ttime2gpswsnoroll(&epoch->VDOPEpoch, &GPSWeek, &SoW);
		t2tmnolocal(&epoch->VDOPEpoch,&tm, &SecondsComp);
		fprintf(options->outFileStream,"INFO Maximum VDOP %6.2f at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVDOP,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VDOPEpoch),GPSWeek,SoW);
	}

    if(options->recPosProvided==1) {
		if (epoch->TotalEpochsRef==0) {
				fprintf(options->outFileStream,"INFO No epochs with solution %sfor computing positioning error percentiles%s\n",UseReferenceFile==1?"and position from reference file ":"",options->stanfordesa==1?" and Stanford-ESA statistics":"");
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
        fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed: %d\n",StdESA->numsamplesProcessed);

        //Print total geometries with solution
        if(SamplesSolPercentage==100. || SamplesSolPercentage==0.) {
            //If percentage is 100%, print 100.000% instead of 1.00E+02%, or if percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3f%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        } else if (SamplesSolPercentage>=99.999) {
            //This is to avoid printing 1.00E+02% when rounding 99.999%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( 99.999%% )\n",StdESA->numsamplesComputed);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA processed with solution: %d ( %.3E%% )\n",StdESA->numsamplesComputed,SamplesSolPercentage);
        }

        //Print epochs skipped due to singular geometry matrix
        if(SamplesSkippedPercentage==0.) {
            //If percentage is 0, print 0.000% instead of 0.000E+00%
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3f%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        } else {
            fprintf(options->outFileStream,"INFO Total geometries in Stanford-ESA skipped due to singular geometry matrix: %d ( %.3E%% )\n",StdESA->numsamplesSingular,SamplesSkippedPercentage);
        }
    }


    if(epoch->TotalEpochsSol!=0) {
        if(options->recPosProvided==1) {
			if (epoch->TotalEpochsRef!=0) {
        	    //Print Horizontal error Percentile
        	    fprintf(options->outFileStream,"INFO Horizontal %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->HPEPercentileSamples);

            	//Print Vertical error Percentile
	            fprintf(options->outFileStream,"INFO Vertical   %*.*f Positioning Error Percentile: %6.2f metres\n",PercentileDigits,PercentileDecimals,options->percentile,epoch->VPEPercentileSamples);

    	        // Print value and epoch with highest horizontal error
       		    ttime2gpswsnoroll(&epoch->HerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->HerrorEpoch,&tm, &SecondsComp);
           		fprintf(options->outFileStream,"INFO Maximum Horizontal Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxHError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->HerrorEpoch),GPSWeek,SoW);

            	// Print value and epoch with highest vertical error
            	ttime2gpswsnoroll(&epoch->VerrorEpoch, &GPSWeek, &SoW);
				t2tmnolocal(&epoch->VerrorEpoch,&tm, &SecondsComp);
            	fprintf(options->outFileStream,"INFO Maximum Vertical   Positioning Error: %6.2f metres at epoch %02d/%02d/%4d %02d:%02d:%02d.%02d / %17s / %4d %9.2f\n",epoch->MaxVError,tm.tm_mday,tm.tm_mon+1,year,tm.tm_hour,tm.tm_min,(int)(SecondsComp+.00005),(int)((SecondsComp-((double)((int)SecondsComp)))*1000.+0.00005),t2doystr(&epoch->VerrorEpoch),GPSWeek,SoW);
			}
        }
    }

	// Print percentile, station name and geodetic latitude and longitude. This line is useful for making maps
	fprintf(options->outFileStream,"INFO Station: %4s Lon: %12.8f Lat: %13.8f Height: %9.4f HPE_Percentile: %*.*f %6.2f VPE_Percentile: %*.*f %6.2f MaxHPE: %6.2f MaxVPE: %6.2f Avail%%: %7.3f PDOP_Percentile:  %*.*f %6.2f Max_PDOP: %6.2f GDOP_Percentile:  %*.*f %6.2f Max_GDOP: %6.2f TDOP_Percentile:  %*.*f %6.2f Max_TDOP: %6.2f HDOP_Percentile:  %*.*f %6.2f Max_HDOP: %6.2f VDOP_Percentile:  %*.*f %6.2f Max_VDOP: %6.2f Epochs_missing_Sum: %3d Epochs_missing_All_file: %3d Num_DataGaps_Sum: %3d Num_DataGaps_All_file: %3d MaxSize_DataGap_Sum: %3d MaxSize_DataGap_All_file: %3d Station_Network_Name: %s\n",
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
 *****************************************************************************/

void printDates(int year, int month, int day, int hour, int minute, double seconds, int DoY, double SoD, int GPSweek, int DoW, double SoW, int MJDN) {

	//The +0.00005 is to avoid problems when rounding to integer
	printf("Calendar Date (DD/MM/YYYY HH:MM:SS.zzz): %02d/%02d/%4d %02d:%02d:%02d.%03d\n\n",day,month,year,hour,minute,(int)(seconds+.00005),(int)((seconds-((double)((int)seconds)))*1000.+0.00005));
	printf("Year:    %6d DoY: %3d SoD: %9.3f\n\n",year,DoY,SoD);
	printf("GPSWeek: %6d DoW: %3d SoW: %10.3f\n\n",GPSweek,DoW,SoW);
	printf("MJDN:    %6d SoD: %9.3f\n",MJDN,SoD);

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
 *****************************************************************************/
void printCoordinates(double *positionXYZ, double *positionNEU, double *positionSph) {

	printf("Cartesian: X:         %15.4f Y:        %14.4f Z:      %14.4f\n\n",positionXYZ[0],positionXYZ[1],positionXYZ[2]);
	printf("Geodetic:  Longitude: %15.10f Latitude: %14.10f Height: %14.4f\n\n",positionNEU[1]*r2d,positionNEU[0]*r2d,positionNEU[2]);
	printf("Spherical: Longitude: %15.10f Latitude: %14.10f Radius: %14.4f\n",positionSph[1]*r2d,positionSph[0]*r2d,positionSph[2]);

}

