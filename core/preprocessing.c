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
 * File: preprocessing.c
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
 *     - Inconsistent pseudorange/carrier-phase jump detection (for Septentrio receivers)
 *     - Epoch decimation
 *     - Carrier-phase pre-alignment
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
 * Change Log: Changed the time to start of the Li and L1-C1 from the 3rd epoch
 *                of the arch to the forth.
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: Included prealignCP option to set/unset carrier-phase pre-alignment.
 *             Cycle-slip detector changed to specify when it does not have enough measurements.
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
 * Change Log: Modified checkCycleSlips function in order to weight current sigma with an initial value.
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
 * Change Log: Completely rewritten checkPseudorangeJumps function.
 *             Completely rewritten L1C1, Melbourne-Wubbena and Geometry-free Cycle Slip Detectors.
 *             Added polyfit function. It fits a polynomial and estimates the geometry-free (LI) prediction.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: In SBAS mode, C1P was used instead of C1C when computing cycle-slips.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added sigmaInflation function, to inflate the sigma during the convergence of the smoother.
 *             INFO message in checkPseudorangeJump now prints current epoch.
 *             Changed LLI cycle-slip detector to not trigger if there is a data gap for any other active cycle-slip detector.
 *             Fixed minor bug, now satellite availability is only modified in the filter.c file.
 *             Fixed bug when handling arc length when an outlier was detected.
 *             If LI prediction cannot be computed, declare cycle-slip instead of exiting the program.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Added function look4interval to compute the file sampling rate.
 *             Added N-consecutive check in cycle-slip detectors. This forces N consecutive samples of a satellite before
 *               it can be used. This check only applies to files with sampling rate below 15 seconds (data rate is detected
 *               automatically). It is a very simple yet very effective way to discard outliers in RINEX measuremnts.
 *             Fixed bug in function checkPseudorangeJumps which was mixing Rover measurements with reference station measurements
 *               in DGNSS mode, thus detecting false code/carrier phase inconsistencies.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   Fixed arclength not increasing when N-consecutive filter was enabled, no cycle-slip detectors were
 *                 active and data rate of the observation file was 15 seconds or lower.
 *               Fixed data rate interval of RTCM3 file not being computed. This made discard all reference
 *                 station measurements if N-consecutive filter was enabled.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Added outlier detection in Melbourne-Wubbena cycle-slip detector.
 *               Fixed bug in the computation of the Melbourne-Wubbena sigma.
 *               In RINEX observation files with a data rate equal or higher than 1 second, when checking if an epoch
 *                 has to be decimated, gLAB will not take into account the decimals in the timestamp in order to
 *                 avoid wrong decimation of epochs with decimals (for example, a file with 1.01, 2.01, etc. timestamps).
 *               Changed L1C1 consistency check threshold from 20 metres (hardcoded) to the value given by parameter.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   SNR is now checked in the cycle-slip detector function. If a satellite does not have
 *                 the minimum SNR, the sample is discarded and counts as a data gap.
 *               During the computation of the file interval ('look4interval' function), in the first
 *                 epoch it will set the rough estimation of the interval (second epoch minus the
 *                first one). This ensures that first epoch is not wrongly decimated due to missing
 *                file interval.
 *               Fixed data gap cycle-slip detector not triggering when L1-C1 cycle slip detector had
 *                 detected an unconsistency in measurements.
 *               Fixed wrong decimation for observation files with interval below 1Hz and inconsistent
 *                 timestamps (for example, a file with 0.2 second interval and timestamps such as 1.203,
 *                 1.204, etc). For decimation on these files, gLAB will now only take into account as much 
 *                 decimals as the file interval (for example, a file with 0.2 second interval will only
 *                 take into consideration the first decimal of the timestamp).
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   Fixed crash (due to division by zero) when observation file timestamps where inconsistent
 *                 (for example 1.000304, 2.000304, ...), file interval was equal or greater than 1 second
 *                 and user had set a decimate value smaller than 1.
 *               Fixed crash (due to division by zero) when observation file timestamps where inconsistent
 *                 (for example 1.000304, 2.000304, ...), file interval was smaller than 1 second and user 
 *                 had set a decimate value of an order of magnitude smaller (or more) than the file interval.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log:   Added a OpenMP preprocessor directive for multithread cycle-slip processing (gLAB needs to be
 *                 rebuild with '-fopenmp' in order to enable multithreading).
 *               'checkCycleSlips' function now does not return any value (before it returned if the last
 *                 satellite processed had had a cycle-slip, which was useless).
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log: Optimised function 'checkPseudorangeJumps'. If total value to be added to measurements is 0,
 *               gLAB will not loop throught the satellite measurements adding 0 to measurements. Also, prints
 *               distinguishing between reference station and rover now have the if as a parameter for the printf,
 *               instead of an external 'if' statement.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log: Function 'checkCycleSlips' now have most of the local variables declared inside the main for loop.
 *               This allows the compiler to do small optimizations, and also simplify the '#pragma omp' directive.
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
 *               Added IGF cycle-slip detector.
 *               Added maximum SNR filtering.
 *               All cycle-slip detectors now allow multiple iterations per satellite, so they can check all carrier
 *                 phases used in the filter or set by user.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "dataHandling.h"
#include "preprocessing.h"

/**************************************
 * Declarations of internal operations
 **************************************/
 
/*****************************************************************************
 * Name        : preprocess
 * Description : Batch that runs a set of general preprocess functions
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch reference structure
 * TOptions  *options              I  N/A  TOptions structure for preprocessing configuration
 * int  mode                       I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS)
 *                                         1 => Process Rover (User) (DGNSS)
 *                                         2 => Process Reference Station (DGNSS)
 *****************************************************************************/
void preprocess (TEpoch *epoch, TOptions *options, int mode) {
	if ( epoch->receiver.look4interval ) look4interval(epoch, options);
	if ( options->checkPhaseCodeJumps ) checkPseudorangeJumps(epoch, options);
	if ( options->prealignCP ) prealignEpoch(epoch,options);
	checkCycleSlips(epoch, options, mode);
	smoothEpoch(epoch, options);
	if ( options->sigmaInflation && mode != 0 ) sigmaInflation(epoch, options);
}

/*****************************************************************************
 * Name        : look4interval
 * Description : Determines the file data sampling rate
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch reference structure
 * TOptions  *options              I  N/A  TOptions structure for preprocessing configuration
 *****************************************************************************/
void look4interval (TEpoch *epoch, TOptions *options) {
	int 			i, indexPos, maxMatch;
	char			aux[100];
	double 			SR = 0.0; // Sampling Rate
	double			auxinterval;
	static int 		counter[10] = {0};
	static int		firstentry=1;
	static double 	arraySR[10] = {0.0};

	// Avoid checking data sampling rate since it comes in the RINEX header
	if ( epoch->receiver.interval != -1 && firstentry==1 ) {
		epoch->receiver.look4interval = 0;
		return;
	} 

	
	// Compute the sampling rate
	if ( epoch->t.MJDN > 0 && epoch->PreviousEpoch.MJDN > 0 ) {
		SR = tdiff(&epoch->t, &epoch->PreviousEpoch);
	}

	// Avoid repeated epoch
	if ( SR > 0.0 ) {
		// Find the SR index in the array. If so, increase the counter
		for ( i = 0; i < 10; i++ ) {
			if ( arraySR[i] == SR ) {
				counter[i]++;
				break;
			}
		}
		// Gone to the end
		if ( i == 10 ) {
			// Look for the first zero
			for ( i = 0; i < 10; i++ ) {
				if ( arraySR[i] == 0.0 ) {
					arraySR[i] = SR;
					counter[i]++;
					break;
				}
			}
		}
		// Get the most repeated sampling rate
		indexPos = 0;
		maxMatch = 0;
		for ( i = 0; i < 10; i++ ) {
			if ( arraySR[i] != 0.0 ) {
				if ( counter[i] > maxMatch ) {
					indexPos = i;
					maxMatch = counter[i];
				}
			}
		}
		// Stop the evaluation
		if ( maxMatch > 11 ) {
			epoch->receiver.look4interval = 0;
			//Disable N-con if interval is greater than or equal than 15 seconds
			if ( arraySR[indexPos] >= 15.0 ) {
				options->csNcon = 0;
			} else if (options->csNconAutoDisabled==1) {
				options->csNcon = 1;
			}
		}

		epoch->receiver.interval = arraySR[indexPos];
		if (epoch->receiver.interval<1.) {
			//Get the number of decimals
			auxinterval=epoch->receiver.interval-(double)((int)(epoch->receiver.interval+.00005));
			epoch->receiver.intervalDecimalsFactor=sprintf(aux,"%.4g",auxinterval)-2;
			epoch->receiver.intervalDecimalsFactor=(int)(pow(10,(double)epoch->receiver.intervalDecimalsFactor));
			epoch->receiver.DecimateVal=(long long int)((options->decimate+.00005)*(double)(epoch->receiver.intervalDecimalsFactor));
			if (epoch->receiver.DecimateVal==0) {
				//This is the case where user set an interval smaller than the number of decimals in the interval
				//Therefore, set this value to 1, so all epochs are used (and also avoid dividing by 0)
				epoch->receiver.DecimateVal=1;
			}
		}
	} else if (firstentry==1) {
		//Set the interval in first epoch as the estimated value, so we make sure
		//no epochs are wrongly decimated due to missing interval 
		epoch->receiver.interval = epoch->receiver.intervalEstimate;
	}


	firstentry=0;

	return;
}

/*****************************************************************************
 * Name        : isEpochDecimated
 * Description : Returns if the current is decimated or not depending on the
 *               chosen value of the options structure 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch reference structure
 * TOptions  *options              I  N/A  TOptions structure for configuration
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Epoch valid
 *                                         1 => Epoch to decimate  
 *****************************************************************************/
int isEpochDecimated (TEpoch *epoch, TOptions *options) {
	long long int			nearestInt;
	static  int				initialized=0;
	static  long long int	Decimateval;
	static  long long int	DecimatevalInteger;

	//NOTE: max resolution set to 10000 Hz (.1 microseconds) to avoid going over the maximum value
	// of an unsigned integer

	if (initialized==0) {
		Decimateval = (long long int)((options->decimate+.00005)*10000.);
		DecimatevalInteger = (long long int)(options->decimate+.00005);
		if (DecimatevalInteger==0) {
			//If options->decimate is less than 1, we will set its integer value
			//to 1 (instead of 0, as this will create a division by 0) as this
			//value will be used for files with Intervals equal or greater than 1
			DecimatevalInteger=1;
		}
		initialized=1;
	}
	
	if ( options->decimate == 0. ) return 0;
	else {
		nearestInt = (long long int)((epoch->t.SoD+.00005)*10000.);
		if ( (nearestInt%Decimateval) == 0 ) return 0;
		else {
			if (epoch->receiver.interval>=1.) {
				//If receiver interval is 1 or greater, do not take
				//into account decimals in the RINEX epochs (for
				//example, a 1Hz file with timestamps like this: 1.01, 2.01, etc.
				nearestInt = (long long int)(epoch->t.SoD+.00005);
				if ( (nearestInt%DecimatevalInteger) == 0 ) return 0;
				else return 1;	
			} else if (epoch->receiver.interval>0.) {
				//If receiver interval is less than 1, we will take into account 
				//only decimals at the same level of the decimation in the RINEX epochs.
				//For example, a 5Hz (0.2 second interval) file with timestamps 
				//like this: 0.203, 0.403, etc. will only read the first decimal
				nearestInt = (long long int)((epoch->t.SoD+.00005)*epoch->receiver.intervalDecimalsFactor);
				if ( (nearestInt%epoch->receiver.DecimateVal) == 0 ) return 0;
				else return 1;
			} else {
				return 1;
			}
		}
	}
}

/*****************************************************************************
 * Name        : isEclipsed
 * Description : Check if a satellite is under eclipse (or has been for the
 *               last 30 minutes)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * TSatellite  *sat                I  N/A  Reference satellite
 * TSatInfo  *satInfo              I  N/A  Information of last eclipse
 * double  sunPos[3]               I  km   Sun position
 * double  *tLast                  O  s    Time from last eclipse (0 if it is
 *                                         currently in eclipse). Unmodified
 *                                         if no eclipse
 * Returned value (int)            O  N/A  Status of the function
 *                                    0 => Satellite OK
 *                                    1 => Satellite under eclipse
 *****************************************************************************/
int isEclipsed (TTime *t, TSatellite *sat, TSatInfo *satInfo, double sunPos[3], double *tLast) {
	double	satPosU[3];
	double	modSat;
	double	sunPosU[3];
	double	cosT;
	double	val;
	double	diff;

	if ( !sat->hasOrbitsAndClocks ) return 0; // Unable to know if it is eclipsed

	// Check if it is now in eclipse
	modSat = sqrt(sat->position[0]*sat->position[0] + sat->position[1]*sat->position[1] + sat->position[2]*sat->position[2]);
	
	memcpy(satPosU,sat->position,sizeof(double)*3);
	memcpy(sunPosU,sunPos,sizeof(double)*3);
	
	unitary(satPosU);
	unitary(sunPosU);
	cosT = scalarProd(satPosU,sunPosU);
	
	if ( cosT < 0 ) {
		val = modSat*sqrt(1-cosT*cosT);
		if (val < EARTH_RADIUS) {
			memcpy(&satInfo->lastEclipse,t,sizeof(TTime));
			*tLast = 0;
			return 1;
		}
	}
	
	// Check if it has been in eclipse in the last 30 minutes
	if ( satInfo->lastEclipse.MJDN != 0 ) { // This would mean still no eclipse found for this satellite
		diff = tdiff(t,&satInfo->lastEclipse);
		if ( diff < 0. ) {
			//If value is negative is because we are going in backwards direction
			//We don't have to leave a margin of 30 minutes prior to the eclipse
			return 0;
		} else if ( diff <= 1800 ) { // 30 minutes
			*tLast = diff;
			return 1;
		} 
	}
	
	return 0;
}

/*****************************************************************************
 * Name        : prealignSat
 * Description : Pre-align pseudorange and carrier-phase from a single satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  ind                        I  N/A  Index of the satellite
 *****************************************************************************/
void prealignSat (TEpoch *epoch, int ind) {
	int							i,j;
	int							ret1,ret2;
	int							freq;
	double						CP,PR;
	double						lambda;
	enum GNSSystem				GNSS;
	enum MeasurementType		meas,meas2;
	const int					freq1=1;
	const int					freq2=2;
	const enum MeasurementType 	C1Cmeas=C1C,C2Cmeas=C2C;
	
	if ( epoch->prealign == 0 ) return;

	i = epoch->satCSIndex[epoch->sat[ind].GNSS][epoch->sat[ind].PRN];
	if ( epoch->cycleslip.arcLength[i] == 0 || ( epoch->cycleslip.arcLength[i] == 1 && epoch->cycleslip.CSPrealignFlag[i] == 1 ) ) {
		GNSS = epoch->sat[ind].GNSS;
		for ( j=0;j<epoch->measOrder[GNSS].nDiffMeasurements;j++ ) {
			meas = epoch->measOrder[GNSS].ind2Meas[j];
			if ( whatIs(meas) == CarrierPhase ) {
				// Set prealign value to 0
				epoch->cycleslip.preAlign[i][j] = 0.0;
				freq=getFrequencyInt(meas);
				ret1 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,&meas,&freq,&CP,NULL,0);
				meas2=meas-1;
				ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,&meas2,&freq,&PR,NULL,0);
				if ( (GNSS==GPS || GNSS==GLONASS) && ret2 == 0 ) {
					// Special cases: 
					switch (meas) {
						case L1P:
							// For the case of L1P, for GPS, if it cannot prealign with C1P (P1 code), it
							// will try to prealign it with C1C (C1 code).
							ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,&C1Cmeas,&freq1,&PR,NULL,0);
							break;
						case L2P:
							// For the case of L2P, for GPS, if it cannot prealign with C2P (P2 code), it
							// will try to prealign it with C2C (C2 code).
							ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,&C2Cmeas,&freq2,&PR,NULL,0);
							break;
						default:
							break;
					}
				}
				// Obtain prealign value
				if ( ret1 != 0 && ret2 != 0 ) { 
					lambda = epoch->measOrder[GNSS].lambdaMeas[freq][epoch->sat[ind].PRN];
					if (lambda!=1.) {
						//Frequency offset available
						epoch->cycleslip.preAlign[i][j] = ((double)((int)((PR-CP)/lambda)));
					}
				}
			}		
		}
	}
}

/*****************************************************************************
 * Name        : prealignEpoch
 * Description : Pre-align pseudorange and carrier-phase an entire epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure 
 *****************************************************************************/
void prealignEpoch (TEpoch *epoch, TOptions  *options) {
	int		i;
	
	epoch->prealign = 1;
	for ( i=0;i<epoch->numSatellites;i++ ) {
		if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
		prealignSat(epoch,i);
	}
}

/*****************************************************************************
 * Name        : lagrangeInterpolation
 * Description : Performs a Lagrange interpolation of specified degree
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  degree                     I  N/A  Degree of the interpolation
 * TTime  t                        I  N/A  Target x point to interpolate in TTime
 *                                         format
 * TTime  *tPrev                   I  N/A  x axis in TTime format
 * double  *yPrev                  I  N/A  y axis
 * Returned value (double)         O  N/A  Interpolated value at t
 *****************************************************************************/
double lagrangeInterpolation (int degree, TTime t, TTime *tPrev, double *yPrev) {
	int			i,j;
	double		yEst,prod;
	double		xPrev[MAX_INTERPOLATION_DEGREE+1];
	double		x;
	TTime		tRef;
	
	yEst = 0;

	// Fill xPrev and x with tPrev and t values   
	memcpy(&tRef,&tPrev[0],sizeof(TTime)); // Reference time
	x = tdiff(&t,&tRef);
	for (i=0;i<=degree;i++)
		xPrev[i] = tdiff(&tPrev[i],&tRef);
				
	// Perform the interpolation
	for ( i=0;i<=degree;i++ ) {
		prod = 1;
		for ( j=0;j<=degree;j++ ) {
			if ( i != j ) {
				prod *= (x-xPrev[j])/(xPrev[i]-xPrev[j]); 
			}
		}
		prod *= yPrev[i];
		yEst += prod;
	}

	return yEst;
}

/*****************************************************************************
 * Name        : checkPseudorangeJumps
 * Description : Check for carrier-phase / pseudorange inconsistencies
 *               Some receivers do not output a set of physically consistent 
 *               measurements, when they adjust their clock, a "jump" should 
 *               appear both in pseudorange and carrier-phase measurements,
 *               but it only appears in pseudorange.
 *               This creates a massive cycle-slip for all satellites in this 
 *               epoch if it is not corrected.
 *               This function detects and corrects this behaviour, providing a 
 *               set of consistent observables.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure 
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => No pseudorange jump found
 *                                         1 => Pseudorange jump found and corrected
 *****************************************************************************/
int checkPseudorangeJumps (TEpoch *epoch, TOptions *options) {
	int						i, j;
	int						indGPSC1;
	int						indGPSL1;
	int						NumsatAdjusted = 0;	//Number of satellites which have been adjusted only on code measurement
	int						PhasenotUpdated;	// 0->phase updated 1->phase not updated
	int						NumbermsCode;		//Number of milliseconds of adjustment in the clock in code measurement
	int						returnvalue = 0;
	int						mode,freq;
	static int				clockupdatems[2] = {0,0};
	static int				firstepoch = 1;
	enum MeasurementType	meas;
	double					Threshold = 200000;	//Threshold is 200Km
	double					MeansmsJump = 0;		//Mean correction of the clock in milliseconds
	double					diffCode, diffPhase, diffCodePhase;
	static double			PrevC1[2][MAX_GNSS][MAX_SBAS_PRN];
	static double			PrevL1[2][MAX_GNSS][MAX_SBAS_PRN];
	double					clockupdateMeters;
	double					lambda;

	//Check if we are with Rover or Reference station
	// 0 -> Rover (with or without DGNSS)
	// 1 -> Reference station
	mode=epoch->DGNSSstruct;

	// We will detect pseudorange jumps comparing C1C and L1C (the most common measurements)
	// First check that it is not the first measurement read for both C1C and L1C
	if ( firstepoch == 1 ) {
		// Initialize previous measurements
		for ( i=0;i<MAX_GNSS;i++ ) {
			for ( j=0;j<MAX_SBAS_PRN;j++ ) {
				PrevC1[0][i][j] = -1;
				PrevC1[1][i][j] = -1;
				PrevL1[0][i][j] = -1;
				PrevL1[1][i][j] = -1;
			}
		}
		firstepoch = 0;
	}

	indGPSC1 = epoch->measOrder[GPS].meas2Ind[C1C];
	indGPSL1 = epoch->measOrder[GPS].meas2Ind[L1C];
	if ( indGPSL1 == -1 ) indGPSL1 = epoch->measOrder[GPS].meas2Ind[L1P];
	for ( i=0;i<epoch->numSatellites;i++ ) {
		if ( epoch->sat[i].GNSS != GPS ) continue; //We will compute the jump using only GPS
		if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue; 
		if ( epoch->sat[i].meas[indGPSC1].rawvalue != -1 && epoch->sat[i].meas[indGPSL1].rawvalue != -1 ) {
			// We have got data available in the current epoch for C1 and L1
			if ( PrevC1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN] != -1 && PrevL1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN] != -1 ) {
				// We have got data available in the previous epoch for C1 and L1
				NumbermsCode = 0;
				PhasenotUpdated = 0;
				diffCode = epoch->sat[i].meas[indGPSC1].rawvalue - PrevC1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN];
				if ( fabs(diffCode) > Threshold ) {
					// Code has had a jump (due to clock update or maybe other reasons, we need to check later)
					NumbermsCode = (int)(round(diffCode*1E3/c0));
					// Check if phase has been updated
					diffPhase = (epoch->sat[i].meas[indGPSL1].rawvalue-PrevL1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN]) * GPSl1;
					diffCodePhase = fabs(diffCode-diffPhase);
					if ( diffCodePhase > Threshold ) {
						// Phase has not been updated
						PhasenotUpdated = 1;
					}
					if ( NumbermsCode != 0 ) {
						NumsatAdjusted++;
						MeansmsJump = (NumbermsCode*PhasenotUpdated+MeansmsJump*(NumsatAdjusted-1)) / NumsatAdjusted;
					}
				}
			}
		}
		PrevC1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN] = epoch->sat[i].meas[indGPSC1].rawvalue;
		PrevL1[mode][epoch->sat[i].GNSS][epoch->sat[i].PRN] = epoch->sat[i].meas[indGPSL1].rawvalue;
	}

	if ( NumsatAdjusted >= 3 && ( (int)(MeansmsJump) != 0) ) {
		if ( fabs(MeansmsJump - (int)(MeansmsJump)) < 0.001 ) { //This is to check that the adjust has been an integer number of milliseconds
			clockupdatems[mode] += (int)(MeansmsJump);
			sprintf(messagestr,"%17s Inconsistent clock update in %s input measurements. It was only updated on code but not in phase (%d ms adjustment)",t2doystr(&epoch->t),mode?"Reference station":"Rover",(int)MeansmsJump);
			printInfo(messagestr,options);
			returnvalue = 1;
		} else {
			//Code jump adjustment has not been an integer number of milliseconds
			sprintf(messagestr,"%17s Inconsistent clock update on %s measurements",t2doystr(&epoch->t),mode?"Reference station":"Rover");
			printInfo(messagestr,options);
		}
	}

	clockupdateMeters = (double)(clockupdatems[mode]) * c0 * 1E-3;

	if (clockupdateMeters>0.) {
	// Update measurements. The jump is common for all satellites of all constellations (because it is in the receiver clock)
		for ( i=0;i<epoch->numSatellites;i++ ) {
			for ( j=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurements;j++ ) {
				meas = epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[j];
				freq = getFrequencyInt(meas);
				if ( whatIs(meas) == CarrierPhase ) {
					if ( epoch->sat[i].meas[j].rawvalue != -1 ) {
						if (epoch->sat[i].GNSS==GLONASS) {
							lambda = epoch->measOrder[epoch->sat[i].GNSS].lambdaMeas[freq][epoch->sat[i].PRN];
							if (lambda==1.) {
								//Glonnas frequency offset not available. Do not update
								sprintf(messagestr,"WARNING: No phase offset for GLO %2d. Could not update clock jump in %s (%d ms adjustment) for measurement %3s",epoch->sat[i].PRN,mode?"Reference station":"Rover",clockupdatems[mode],meastype2measstr(meas));
								printInfo(messagestr,options);
							} else {
								epoch->sat[i].meas[j].value+=(double)clockupdateMeters/lambda;
							}
						} else {
							epoch->sat[i].meas[j].value+=(double)clockupdateMeters/epoch->measOrder[epoch->sat[i].GNSS].conversionFactor[meas];
						}
					}
				}
			}
		}
	}

	return returnvalue;
}

/*****************************************************************************
 * Name        : polyfit
 * Description : Fits a polynomial (with degree 2) and estimates the Li prediction
                  using least squares
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime *t                        I  N/A  Current epoch
 * TTime *tSamples                 I  N/A  Array with the timestamp of each sample
 * double *Samples                 I    m  Array with the samples
 * int  outlier                    I  N/A  Flag to indicate if an outlier occurred
 * int  numsamples                 I  N/A  Number of samples
 * double  *res                    O  N/A  Polynomial residual
 * Returned value (double)         O  N/A  Polynomial prediction
 *****************************************************************************/
double polyfit (TTime *t, TTime *tSamples, double *Samples, int outlier, int numsamples, double *res) {
	int		j,k,l,istart,resi;
	int		flipJ[numsamples];
	double	a[numsamples][3];
	double	y[numsamples];
	double	va[6] = {0, 0, 0, 0, 0, 0};
	double	aty[3] = {0, 0, 0};
	double	coef[3] = {0, 0, 0};
	double	x0 = 0.0;
	double	tempo, Est;

	// Initialize
	for ( j=0;j<numsamples;j++ ) {
		flipJ[j] = numsamples-j-1;
		y[j] = 0;
	}

	// Build the matricial equations
	for ( j=numsamples-1;j>=0;j-- ) {
			tempo = tdiff(&tSamples[flipJ[j]],&tSamples[0]);
		for ( k=0;k<3;k++ ) {
			// Build Vandermonde matrix for time samples
			a[j][k] = pow(tempo,k);
		}

		// Build array of measurements
		y[j] = Samples[flipJ[j]] - Samples[0];
	}

	// Avoid outlier in fitting the polynomial
	if ( outlier >= 1 ) {
		istart = 1;
	} else {
		istart = 0;
	}

	// Build at * a and at * y
	for ( k=0;k<3;k++ ) {
		for ( j=0;j<=k;j++ ) {
			for ( l=istart;l<numsamples;l++ ) {
				va[m2v(k,j)] += a[l][j] * a[l][k];
			}
		}
		for ( l=istart;l<numsamples;l++ ) {
			aty[k] += a[l][k] * y[l];
		}
	}

	// Solve the inv(at*a) with Cholesky 
	resi = cholinv_opt(va,3);
	if (resi==-1) {
		return 999999.;
	}

	// Build inv(va) * aty
	for ( k=0;k<3;k++) {
		for ( j=0;j<3;j++ ) {
			coef[k] += va[m2v(k,j)] * aty[j];
		}
	}

	/////////////////////////////////////////////
	// Post-fit residuals
	//rms = 0.0;
	//for (j=istart;j<numsamples;j++) {
	//	ye = 0.0;
	//	for (k=0;k<3;k++) {
	//		ye += a[j][k] * coef[k];
	//	}
	//	rms += pow(ye-y[j],2);
	//}
	//*res = sqrt(rms);
	/////////////////////////////////////////////

	// First coefficient instead of the residual (detection is more accurate)
	*res = coef[0];

	// Calculate the prediction Est
	for ( j=2; j>=0; j-- ) {
		x0 += coef[j] * pow(tdiff(t,&tSamples[0]), j);
	}
	Est = x0 + Samples[0];

	return Est;
}

/*****************************************************************************
 * Name        : checkCycleSlips
 * Description : Check for carrier-phase cycle slips.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 * int  mode                       I  N/A  Mode of processing
 *                                         0 => Standalone mode (No DGNSS)
 *                                         1 => Process Rover (User) (DGNSS)
 *                                         2 => Process Reference Station (DGNSS)
 *****************************************************************************/
void checkCycleSlips (TEpoch *epoch, TOptions *options, int mode) {

	int			i,m,n;
	int			DGNSSstruct=epoch->DGNSSstruct;
	int			AnyMessageToPrint=0;

	// Loop over all satellites
	#pragma omp parallel for 
	for ( i=0;i<epoch->numSatellites;i++ ) {
		
		//In this case, variable are declared inside the loop. This is done to allow some compiler optimizations in single thread (as
		//by declaring the variable inside the for loop we are stating to the compiler that the scope of the variable is only inside the for loop)
		//and also, in multithread, as all variables have to be private, the compiler can optimize the code as variables are declared inside
		//the loop, it does not need to make a local copy of the variable when the thread starts (if the variables were declared outside
		//the for loop, the variables would be in the "private" OpenMP directive -see gLAB version 5.3.0-, making the '#pragma' directive shorter)
		//Note that in each loop, the variables will NOT keep the value of the previous iteration (even in single thread mode)

		int 					j,k,l;
		int 					cycleSlipFound = 0;
		int						PRN=epoch->sat[i].PRN;
		enum GNSSystem 			GNSS=epoch->sat[i].GNSS;
		char					auxstr[MAX_INPUT_LINE+50]; //The +50 is to avoid -Wformat-overflow warning
		char					auxmeas[4][10];

		double					auxMean;
		double					auxMean2;
		int						samples;
		int						indexPos;
		int						NoOutlierAndNconOk=0;
		double					tdiffNcon;
		double					SNRVal;
		double					measValue;
		enum MeasurementType	meas;

		// Data Gap
		double					timeDiff;
		int 					DataGapCheck = 0;	// 0 => no CS detected by Data gap detector
													// 1 => CS detected by Data gap detector

		// Loss of Lock Indicator (LLI)
		int						LLI;
		int 					LLICheck = 0;		// 0 => no CS detected by LLI detector
													// 1 => CS detected by LLI detector
		char					LLIText[MAX_INPUT_LINE];

		// Melbourne-Wubbena (MW)
		int						OutlierMWFoundAll,OutlierMWFound[MAX_CS_LIST];
		double					MWVal[MAX_CS_LIST];
		double					nMWdiff;
		double					nMW300diff;
		double					nMWdiffThreshold;
		int						MWCheck[MAX_CS_LIST];
		int 					MWCheckAll = 0;		// 0 => no CS detected by Melbourne-Wubbena detector
													// 1 => CS detected by Melbourne-Wubbena detector

		// Geometry-free (LI)
		int						OutlierLIFoundAll,OutlierLIFound[MAX_CS_LIST];
		double					LIVal[MAX_CS_LIST];
		double					LIEst;
		double					res,resThreshold;
		double					LIDiff[MAX_CS_LIST];
		double					LIDiffAbs[MAX_CS_LIST];
		double					LIDiffEst[MAX_CS_LIST];
		double					LIDiffEstAbs[MAX_CS_LIST];
		int						LICheck[MAX_CS_LIST];
		int 					LICheckAll = 0;		// 0 => no CS detected by Geometry-free detector
													// 1 => CS detected by Geometry-free detector

		// Iono Geometry-free (IGF)
		int						OutlierIGFFoundAll,OutlierIGFFound[MAX_CS_LIST];
		double					IGF[MAX_CS_LIST];
		double					IGFEst;
		double					IGFDiff[MAX_CS_LIST];
		double					IGFDiffAbs[MAX_CS_LIST];
		double					IGFDiffEst[MAX_CS_LIST];
		double					IGFDiffEstAbs[MAX_CS_LIST];
		int						IGFCheck[MAX_CS_LIST];
		int 					IGFCheckAll = 0;	// 0 => no CS detected by Iono Geometry-free detector
													// 1 => CS detected by Iono Geometry-free detector
		// Single Frequency (SF) detector
		int						SFdiffFactor;
		double					SFPhase[MAX_CS_LIST];
		double					SFCode[MAX_CS_LIST];
		double					SFdiff[MAX_CS_LIST];
		double					sigma2;
		double					deltaSFCode[MAX_CS_LIST];
		double					deltaSFPhase[MAX_CS_LIST];
		double					deltaSF[MAX_CS_LIST];
		double 					SFThreshold[MAX_CS_LIST];	// Threshold of SF difference detector
		int						SFCheck[MAX_CS_LIST];
		int 					SFCheckAll=0;				// 0 => no CS detected by SF difference detector
															// 1 => CS detected by SF difference detector

		//If satellite is unselected, do not detect cycle-slips
		if (options->includeSatellite[GNSS][PRN]==0) continue;

		//If satellite has not selected measurements, wait for all measurements to be selected
		if (options->MeasSelected[DGNSSstruct][GNSS][PRN]!=MEASSELECTED) continue;


		// Index of the satellite in the dictionary
		j = epoch->satCSIndex[GNSS][PRN];

		// Initialise several checks
		epoch->cycleslip.preCheck[j] = 0;
		epoch->cycleslip.CS[j] = 0;
		epoch->cycleslip.use4smooth[j] = 1;
		epoch->cycleslip.anyOutlier[j] = 0;
		epoch->sat[i].hasSNR = 1;
		epoch->sat[i].badSNRText[0] = '\0';
		epoch->sat[i].MissingMeasText[0] = '\0';
		epoch->sat[i].SFUnconsistencyText[0] = '\0';
		LLIText[0] = '\0';

		// Check missing measurements
		for(k=0;k<epoch->measOrder[GNSS].numMeasListDataGap[PRN];k++) {
			measValue=epoch->sat[i].meas[epoch->measOrder[GNSS].measIndListDataGap[PRN][k]].value;
			if (measValue==-1.) {
				//It is below the minimum or over the maximum
				meas=epoch->measOrder[GNSS].measListDataGap[PRN][k];
				sprintf(auxstr,"%s %3s",epoch->sat[i].MissingMeasText,meastype2measstr(meas));
				strcpy(epoch->sat[i].MissingMeasText,auxstr);
			}
		}

		if (epoch->sat[i].MissingMeasText[0]!='\0') {
			//Some of the measurements are missing
			epoch->cycleslip.preCheck[j] = 1;
			epoch->cycleslip.use4smooth[j] = 0;
			continue;
		}

		// Check SNR. No need to check if option 'SNRfilter' is enabled, as if it is disabled, the list will be empty
		for(k=0;k<epoch->measOrder[GNSS].numMeasListToCheckSNR[PRN];k++) {
			meas=epoch->measOrder[GNSS].measListToCheckSNR[PRN][k];
			SNRVal=epoch->sat[i].meas[epoch->measOrder[GNSS].meas2SNRInd[meas]].SNRvalue;
			if (SNRVal<options->SNRminvalues[GNSS][PRN][meas] || SNRVal>options->SNRmaxvalues[GNSS][PRN][meas]) {
				//It is below the minimum or over the maximum
				switch (options->SNRchecktype) {
					case SNRCheckMinMax:
						sprintf(auxstr,"%s %3s-%.2f (min: %.2f max: %.2f)",epoch->sat[i].badSNRText,meastype2measstr(meas),SNRVal,options->SNRminvalues[GNSS][PRN][meas],options->SNRmaxvalues[GNSS][PRN][meas]);
						break;
					case SNRCheckMin:
						sprintf(auxstr,"%s %3s-%.2f (min: %.2f)",epoch->sat[i].badSNRText,meastype2measstr(meas),SNRVal,options->SNRminvalues[GNSS][PRN][meas]);
						break;
					case SNRCheckMax:
						sprintf(auxstr,"%s %3s-%.2f (max: %.2f)",epoch->sat[i].badSNRText,meastype2measstr(meas),SNRVal,options->SNRmaxvalues[GNSS][PRN][meas]);
						break;
					default:
						break;
				}
				strcpy(epoch->sat[i].badSNRText,auxstr);
			}
		}

		if (epoch->sat[i].badSNRText[0]!='\0') {
			//Some measurements do not meet the required SNR
			epoch->sat[i].hasSNR = 0;
			epoch->cycleslip.use4smooth[j] = 0;
			continue;
		}

		if (options->allCSDetectorsOff == 1) {
			if (options->csNcon==0) {
				epoch->cycleslip.arcLength[j]++;
				continue;
			} else {
				//Check N-con with no cycle-slip enabled
				tdiffNcon=fabs(tdiff(&epoch->t,&epoch->cycleslip.previousEpochNconsecutive[j]));
				// Check if there are N-consecutive samples
				if ( (tdiffNcon - epoch->receiver.interval) > DIFFEQTHRESHOLD ) {  //The DIFFEQTHRESHOLD is to avoid problems with decimals
					epoch->cycleslip.Nconsecutive[j] = options->csNconMin;
					epoch->cycleslip.use4smooth[j] = 0;
				} else if ( epoch->cycleslip.Nconsecutive[j] < 0 ) {
					// Increase N-consecutive to avoid the following N epochs after data hole
					epoch->cycleslip.Nconsecutive[j]++;
					epoch->cycleslip.use4smooth[j] = 0;
					if (epoch->cycleslip.Nconsecutive[j] == 0 ) epoch->cycleslip.arcLength[j]++;
				} else {
					epoch->cycleslip.arcLength[j]++;
				}
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[j],&epoch->t,sizeof(TTime));
				continue;
			}
		}

		// Data Gap Cycle Slip Detector
		timeDiff = fabs(tdiff(&epoch->t,&epoch->cycleslip.previousEpoch[j]));;
		if ( (timeDiff - options->csDataGap) > DIFFEQTHRESHOLD && //The DIFFEQTHRESHOLD is to avoid problems with decimals
			 epoch->cycleslip.arcLength[j] > 0) {
			DataGapCheck = 1; // Cycle slip detected
			// Update previous epoch (time) to check if there is data gap
			memcpy(&epoch->cycleslip.previousEpoch[j],&epoch->t,sizeof(TTime));
			// Update previous epoch (time) to check if there is N-consecutive epochs
			memcpy(&epoch->cycleslip.previousEpochNconsecutive[j],&epoch->t,sizeof(TTime));
			//Set N-consecutive
			epoch->cycleslip.Nconsecutive[j] = options->csNconMin * options->csNcon;
			//Print cycle-slip
			if (options->printCycleslips) {
				printCS(epoch,GNSS,PRN,i,CSTypeDataGap,mode,NULL,options->csDataGap,timeDiff,NULL,0.,0.,0.,0.,0.,0.,0.,0.,options);
			}
		} 
		// N-consecutive data with any cycle-slip detector enabled. If there has been a data gap, no need to check N-con
		else if ( options->csNcon ) {
			tdiffNcon=fabs(tdiff(&epoch->t,&epoch->cycleslip.previousEpochNconsecutive[j]));
			// Check if there are N-consecutive samples
			if ( (tdiffNcon - epoch->receiver.interval) > DIFFEQTHRESHOLD &&  //The DIFFEQTHRESHOLD is to avoid problems with decimals
				 (tdiffNcon - options->csDataGap) <= DIFFEQTHRESHOLD && epoch->cycleslip.arcLength[j] > 0 ) {
				epoch->cycleslip.Nconsecutive[j] = options->csNconMin;
				epoch->cycleslip.use4smooth[j] = 0;
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[j],&epoch->t,sizeof(TTime));
			} else if ( epoch->cycleslip.Nconsecutive[j] < 0 ) {
				// Increase N-consecutive to avoid the following N epochs after data hole
				epoch->cycleslip.Nconsecutive[j]++;
				epoch->cycleslip.use4smooth[j] = 0;
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[j],&epoch->t,sizeof(TTime));
			}
		} else {
			// Update previous epoch (time) to check if there is data gap
			memcpy(&epoch->cycleslip.previousEpoch[j],&epoch->t,sizeof(TTime));
			//N-con not enabled if entering here, so we need to update previousEpochNconsecutive
		}

		// Update the Loss of Lock Indicator
		// Loss of Lock Indicator (LLI)
		//   Range: 0-7
		//      0 or blank: OK or not known
		//      1, 3, 5 and 7: Lost lock between previous and current observation: cycle slip possible
		//If arc length is 0 (no measurement read, skip LLI, as even though the flag is enabled, as it
		//is the first sample of the new arc, no need to trigger cycle-slip, which typically has the
		//side effect that the first epoch read has arc number equal to 2 instead of 1
		if (epoch->cycleslip.arcLength[j] > 0) {
			for ( k=0;k<epoch->measOrder[GNSS].numMeasListToCheckLLI[PRN];k++ ) {
				LLI=epoch->sat[i].meas[epoch->measOrder[GNSS].measIndListToCheckLLI[PRN][k]].LLI;
				if (LLI%2!= 0) {
					meas=epoch->measOrder[GNSS].ind2Meas[epoch->measOrder[GNSS].measIndListToCheckLLI[PRN][k]];
					sprintf(auxstr,"%s %3s-%1d",LLIText,meastype2measstr(meas),LLI);
					strcpy(LLIText,auxstr);
				}
			}

			if ( LLIText[0]!='\0' ) {
				LLICheck = 1; // Cycle slip detected
				//Print cycle-slip
				if (options->printCycleslips) {
					printCS(epoch,GNSS,PRN,i,CSTypeLLI,mode,NULL,0.,0.,LLIText,0.,0.,0.,0.,0.,0.,0.,0.,options);
				}
			}
		}


		if (epoch->cycleslip.Nconsecutive[j]==0) {
			//Melbourne-Wubbena
			for(k=0;k<options->numcsMWMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csMWMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				MWVal[k] = getMeasurementValue(epoch,GNSS,PRN,options->csMWMeasList[DGNSSstruct][GNSS][PRN][k],options->csMWMeasFreq[DGNSSstruct][GNSS][PRN][k]);
			}

			//Geometry-free
			for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				LIVal[k] = getMeasurementValue(epoch,GNSS,PRN,options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k]);
				// Geometry-free max jump detection
				LIDiff[k] = epoch->cycleslip.initialLI[j][k] - LIVal[k];
				LIDiffAbs[k] = fabs(LIDiff[k]);
				//If data gap was declared, do not check for jumps, as a cycle-slip has been declared
				if (DataGapCheck == 0) { //If data gap was declared, do not check for jumps
					if ( LIDiffAbs[k] > options->csLImaxjump && epoch->cycleslip.arcLength[j] > 0 ) {
						LICheckAll = 1;
						//Print cycle-slip
						if (options->printCycleslips) {
							printCS(epoch,GNSS,PRN,i,CSTypeLIEst,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,LIDiffAbs[k],options->csLImaxjump,0.,0.,0.,0.,0.,0.,options);
						}
						//Print LI data
						if (options->printLIdata) {
							printLICSdata(epoch,GNSS,PRN,i,j,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialLI[j][k],LIVal[k],LIDiffAbs[k],999999.,999999.,999999.,0,1,options);
						}
					}
				}
			}

			//Iono Geometry-free
			for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				IGF[k] = getMeasurementValue(epoch,GNSS,PRN,options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k]);
				// Geometry-free max jump detection
				IGFDiff[k] = epoch->cycleslip.initialIGF[j][k] - IGF[k];
				IGFDiffAbs[k] = fabs(IGFDiff[k]);
				//If data gap was declared, do not check for jumps, as a cycle-slip has been declared
				if (DataGapCheck == 0) { //If data gap was declared, do not check for jumps
					if ( IGFDiffAbs[k] > options->csIGFmaxjump && epoch->cycleslip.arcLength[j] > 0 ) {
						IGFCheckAll = 1;
						//Print cycle-slip
						if (options->printCycleslips) {
							printCS(epoch,GNSS,PRN,i,CSTypeIGFEst,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,0.,0.,IGFDiffAbs[k],options->csIGFmaxjump,options);
						}
						//Print IGF data
						if (options->printIGFdata) {
							printIGFCSdata(epoch,GNSS,PRN,i,j,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialIGF[j][k],IGF[k],IGFDiffAbs[k],999999.,999999.,999999.,0,1,options);
						}
					}
				}
			}

			//Single Frequency
			//Get measurements for SF cycle-slip. If unconsistency check is enabled, check consistency
			if (epoch->cycleslip.arcLength[j] > 0 && options->csUnconsistencyCheck ) {
				for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					SFCode[k] = getMeasurementValue(epoch,GNSS,PRN,&options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][0],&options->csSFMeasFreq[DGNSSstruct][GNSS][PRN][k][0]);
					SFPhase[k] = getMeasurementValue(epoch,GNSS,PRN,&options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][1],&options->csSFMeasFreq[DGNSSstruct][GNSS][PRN][k][1]);
					deltaSFCode[k] = SFCode[k]-epoch->cycleslip.SFCodePrev[j][k];
					deltaSFPhase[k] = SFPhase[k]-epoch->cycleslip.SFPhasePrev[j][k];
					deltaSF[k]=fabs(deltaSFCode[k]-deltaSFPhase[k]);
					if ( deltaSF[k] > options->csUnconsistencyCheckThreshold) {
						strcpy(auxmeas[0],meastype2measstr(options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][0]));
						sprintf(auxstr,"%s %3s-%3s (%.2f)",epoch->sat[i].SFUnconsistencyText,auxmeas[0],meastype2measstr(options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][1]),deltaSF[k]);
						strcpy(epoch->sat[i].SFUnconsistencyText,auxstr);
					} else {
						epoch->cycleslip.SFPhasePrev[j][k] = SFPhase[k];
						epoch->cycleslip.SFCodePrev[j][k] = SFCode[k];
					}
				}
				if (epoch->sat[i].SFUnconsistencyText[0]!='\0') {
					epoch->cycleslip.use4smooth[j] = 0;
					//If data gap or LLI or LI or IGF precheck were triggered, let the cycle-slip trigger
					if (DataGapCheck==0 && LLICheck==0 && LICheckAll==0 && IGFCheckAll==0 && epoch->cycleslip.consistency[j]==0) {
						//If there was no data gap or LLI or LI or IGF precheck detection, then do not check for cycle-slips 
						//(consider it as data-gap but without triggering N-con)
						epoch->cycleslip.consistency[j] = 1;
						//Print SF data
						if (options->printSFdata) {
							for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
								if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
								SFdiff[k] = pow((SFPhase[k]-SFCode[k]) - epoch->cycleslip.SFmean[j][k],2);
								SFThreshold[k] = min(epoch->cycleslip.SFsigma[j][k] * pow(options->csSFkfactor,2), pow(options->csSFinit,2) * pow(options->csSFkfactor,2));
								printSFCSdata(epoch,GNSS,PRN,i,j,mode,options->csSFMeasText[DGNSSstruct][GNSS][PRN][k],SFCode[k],SFPhase[k],epoch->cycleslip.SFmean[j][k],epoch->cycleslip.SFsigma[j][k],deltaSFCode[k],deltaSFPhase[k],deltaSF[k],SFdiff[k],SFThreshold[k],1,0,options);
							}
						}
						continue;
					} else {
						//If a cycle-slip is already declared or consistency was triggered last epoch, do not trigger unconsistency in this epoch
						epoch->sat[i].SFUnconsistencyText[0]='\0';
					}
				} else {
					epoch->cycleslip.consistency[j] = 0;
				}
			} else {
				for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					SFCode[k] = getMeasurementValue(epoch,GNSS,PRN,&options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][0],&options->csSFMeasFreq[DGNSSstruct][GNSS][PRN][k][0]);
					SFPhase[k] = getMeasurementValue(epoch,GNSS,PRN,&options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][1],&options->csSFMeasFreq[DGNSSstruct][GNSS][PRN][k][1]);
					deltaSFCode[k]=deltaSFPhase[k]=deltaSF[k]=999999.;
					epoch->cycleslip.SFPhasePrev[j][k] = SFPhase[k];
					epoch->cycleslip.SFCodePrev[j][k] = SFCode[k];
				}
			}

			// Everything OK
			if ( DataGapCheck == 0 && LLICheck == 0 ) {
				// Update the arc length
				epoch->cycleslip.arcLength[j]++;
				// Update previous epoch (time) to check if there is data gap
				memcpy(&epoch->cycleslip.previousEpoch[j],&epoch->t,sizeof(TTime));
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[j],&epoch->t,sizeof(TTime));
				

				// Melbourne-Wubbena (MW) [dual-frequency]
				if ( epoch->cycleslip.arcLength[j] > options->minArcLength ) {
					OutlierMWFoundAll=0;
					for(k=0;k<options->numcsMWMeasList[DGNSSstruct][GNSS][PRN];k++) {
						if (options->csMWMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
						// Melbourne-Wubbena cycle slip detector
						OutlierMWFound[k] = 0;
						MWCheck[k]=0;
						nMWdiff = fabs(MWVal[k]-epoch->cycleslip.MWmean[j][k]);
						nMW300diff = fabs(MWVal[k]-epoch->cycleslip.MWmean300[j][k]);
						nMWdiffThreshold = options->csMWkfactor * sqrt(epoch->cycleslip.MWsigma[j][k]);

						if ( (nMWdiff > nMWdiffThreshold &&
							 nMW300diff > options->csMWmin &&
							 sqrt(epoch->cycleslip.MWsigma[j][k]) <= options->csMWmin) ||
							 (nMWdiff > 10.0*options->csMWmin ) ) {
							if (options->csMWenableOutlier==1) {
								if ( epoch->cycleslip.outlierMW[j] == 1) {
									// Cycle slip confirmed
									MWCheckAll = 1;
									MWCheck[k]=1;
									//Print cycle-slip
									if (options->printCycleslips) {
										printCS(epoch,GNSS,PRN,i,CSTypeMW,mode,options->csMWMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,nMWdiff,nMWdiffThreshold,0.,0.,0.,0.,options);
									}
								} else {
									// Outlier
									OutlierMWFoundAll = 1;
									OutlierMWFound[k] = 1;
								}
							} else {
								// Cycle slip (no outliers)
								MWCheckAll = 1;
								MWCheck[k]=1;
								//Print cycle-slip
								if (options->printCycleslips) {
									printCS(epoch,GNSS,PRN,i,CSTypeMW,mode,options->csMWMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,nMWdiff,nMWdiffThreshold,0.,0.,0.,0.,options);
								}
							}
						}
						//Print MW data
						if (options->printMWdata) {
							printMWCSdata(epoch,GNSS,PRN,i,j,mode,options->csMWMeasText[DGNSSstruct][GNSS][PRN][k],options->csMWMeasList[DGNSSstruct][GNSS][PRN][k],options->csMWMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.MWmean[j][k],epoch->cycleslip.MWmean300[j][k],epoch->cycleslip.MWsigma[j][k],MWVal[k],nMWdiff,nMW300diff,nMWdiffThreshold,OutlierMWFound[k],MWCheck[k],options);
						}
					}
					if (epoch->cycleslip.outlierMW[j] == 1) {
						if ( MWCheckAll==0 && OutlierMWFoundAll==0 ) {
							epoch->cycleslip.outlierMW[j] = 0;
							epoch->cycleslip.use4smooth[j] = 1;
							epoch->sat[i].available = 1;
						}
					} else  {
						epoch->cycleslip.outlierMW[j] = OutlierMWFoundAll;
					}
				} else {
					for(k=0;k<options->numcsMWMeasList[DGNSSstruct][GNSS][PRN];k++) {
						if (options->csMWMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
						//Print MW data
						if (options->printMWdata) {
							printMWCSdata(epoch,GNSS,PRN,i,j,mode,options->csMWMeasText[DGNSSstruct][GNSS][PRN][k],options->csMWMeasList[DGNSSstruct][GNSS][PRN][k],options->csMWMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.MWmean[j][k],epoch->cycleslip.MWmean300[j][k],epoch->cycleslip.MWsigma[j][k],MWVal[k],999999.,999999.,999999.,0,0,options);
						}
					}
				}

				// Geometry-free carrier-phase combination (LI) [dual-frequency]
				if ( !LICheckAll ) {
					for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
						if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
						// Update both historical LI and epochs
						if ( epoch->cycleslip.arcLength[j] <= (options->csLIsamples+1) ) {
							indexPos = epoch->cycleslip.arcLength[j]-1;
							epoch->cycleslip.LIPrev[j][k][indexPos] = LIVal[k];
							memcpy(&epoch->cycleslip.tPrevLI[j][k][indexPos],&epoch->t,sizeof(TTime));
						} else {
							for (l=0;l<options->csLIsamples;l++) {
								epoch->cycleslip.LIPrev[j][k][l] = epoch->cycleslip.LIPrev[j][k][l+1];
								memcpy(&epoch->cycleslip.tPrevLI[j][k][l],&epoch->cycleslip.tPrevLI[j][k][l+1],sizeof(TTime));
							}
							epoch->cycleslip.LIPrev[j][k][options->csLIsamples] = LIVal[k];
							memcpy(&epoch->cycleslip.tPrevLI[j][k][options->csLIsamples],&epoch->t,sizeof(TTime));
						}
					}

					// Enough data to build polynomial fit
					if ( epoch->cycleslip.arcLength[j] > options->minArcLength ) {
						OutlierLIFoundAll=0;
						for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							// Fit polynomial and estimate the LI prediction
							OutlierLIFound[k]=0;
							LICheck[k] = 0;
							LIEst = polyfit(&epoch->t, epoch->cycleslip.tPrevLI[j][k], epoch->cycleslip.LIPrev[j][k],epoch->cycleslip.outlierMW[j]+epoch->cycleslip.outlierLI[j]+epoch->cycleslip.outlierIGF[j],options->csLIsamples, &res);
							// Geometry-free cycle slip detector
							LIDiffEst[k] = LIVal[k] - LIEst;
							LIDiffEstAbs[k] = fabs(LIDiffEst[k]);
							resThreshold=fabs(2.0 * res);
							if ( (LIDiffEstAbs[k] > options->csLIThreshold && 
								 LIDiffEstAbs[k] > resThreshold) || LIEst==999999. ) {
								if (options->csLIenableOutlier==1) {
									if ( epoch->cycleslip.outlierLI[j] == 1 || LIEst==999999.) {
										// Cycle slip confirmed
										LICheckAll = 1;
										LICheck[k] = 1;
										if(LIEst==999999.) {
											LIDiffEst[k]=LIDiffEstAbs[k]=999999.;
											//Print cycle-slip
											if (options->printCycleslips) {
												printCS(epoch,GNSS,PRN,i,CSTypeLINoEst,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,LIDiffEst[k],options->csLIThreshold,0.,0.,0.,0.,0.,0.,options);
											}
										} else {
											//Print cycle-slip
											if (options->printCycleslips) {
												printCS(epoch,GNSS,PRN,i,CSTypeLIEst,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,LIDiffEstAbs[k],options->csLIThreshold,0.,0.,0.,0.,0.,0.,options);
											}
										}
									} else {
										// Outlier
										OutlierLIFoundAll=1;
										OutlierLIFound[k]=1;
									}
								} else {
									// Cycle slip (no outliers)
									LICheckAll = 1;
									LICheck[k] = 1;
									if(LIEst==999999.) {
										LIDiffEst[k]=LIDiffEstAbs[k]=999999.;
										//Print cycle-slip
										if (options->printCycleslips) {
											printCS(epoch,GNSS,PRN,i,CSTypeLINoEst,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,LIDiffEst[k],options->csLIThreshold,0.,0.,0.,0.,0.,0.,options);
										}
									} else {
										//Print cycle-slip
										if (options->printCycleslips) {
											printCS(epoch,GNSS,PRN,i,CSTypeLIEst,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,LIDiffEstAbs[k],options->csLIThreshold,0.,0.,0.,0.,0.,0.,options);
										}
									}
								}
							}
							//Print LI data
							if (options->printLIdata) {
								printLICSdata(epoch,GNSS,PRN,i,j,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialLI[j][k],LIVal[k],LIDiffAbs[k],LIEst,LIDiffEstAbs[k],resThreshold,OutlierLIFound[k],LICheck[k],options);
							}
						}
						if (epoch->cycleslip.outlierLI[j] == 1) {
							if ( LICheckAll==0 && OutlierLIFoundAll==0 ) {
								epoch->cycleslip.outlierLI[j] = 0;
								epoch->cycleslip.use4smooth[j] = 1;
								epoch->sat[i].available = 1;
							}
						} else  {
							epoch->cycleslip.outlierLI[j] = OutlierLIFoundAll;
						}

					} else { 
						for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							//Print LI data
							if (options->printLIdata) {
								printLICSdata(epoch,GNSS,PRN,i,j,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialLI[j][k],LIVal[k],LIDiffAbs[k],999999.,999999.,999999.,0,0,options);
							}
						}
					}
				}

				// Iono-Geometry-free carrier-phase combination (IGF) [triple/quadruple frequency]
				if ( !IGFCheckAll ) {
					for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
						if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
						// Update both historical IGF and epochs
						if ( epoch->cycleslip.arcLength[j] <= (options->csIGFsamples+1) ) {
							indexPos = epoch->cycleslip.arcLength[j]-1;
							epoch->cycleslip.IGFPrev[j][k][indexPos] = IGF[k];
							memcpy(&epoch->cycleslip.tPrevIGF[j][k][indexPos],&epoch->t,sizeof(TTime));
						} else {
							for (l=0;l<options->csIGFsamples;l++) {
								epoch->cycleslip.IGFPrev[j][k][l] = epoch->cycleslip.IGFPrev[j][k][l+1];
								memcpy(&epoch->cycleslip.tPrevIGF[j][k][l],&epoch->cycleslip.tPrevIGF[j][k][l+1],sizeof(TTime));
							}
							epoch->cycleslip.IGFPrev[j][k][options->csIGFsamples] = IGF[k];
							memcpy(&epoch->cycleslip.tPrevIGF[j][k][options->csIGFsamples],&epoch->t,sizeof(TTime));
						}
					}

					// Enough data to build polynomial fit
					if ( epoch->cycleslip.arcLength[j] > options->minArcLength ) {
						OutlierIGFFoundAll=0;
						for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							// Fit polynomial and estimate the IGF prediction
							OutlierIGFFound[k]=0;
							IGFCheck[k] = 0;
							IGFEst = polyfit(&epoch->t, epoch->cycleslip.tPrevIGF[j][k], epoch->cycleslip.IGFPrev[j][k],epoch->cycleslip.outlierMW[j]+epoch->cycleslip.outlierLI[j]+epoch->cycleslip.outlierIGF[j],options->csIGFsamples, &res);
							// Geometry-free cycle slip detector
							IGFDiffEst[k] = IGF[k] - IGFEst;
							IGFDiffEstAbs[k] = fabs(IGFDiffEst[k]);
							resThreshold=fabs(2.0 * res);
							if ( (IGFDiffEstAbs[k] > options->csIGFThreshold && 
								 IGFDiffEstAbs[k] > resThreshold) || IGFEst==999999. ) {
								if (options->csIGFenableOutlier==1) {
									if ( epoch->cycleslip.outlierIGF[j] == 1 || IGFEst==999999.) {
										// Cycle slip confirmed
										IGFCheckAll = 1;
										IGFCheck[k] = 1;
										if(IGFEst==999999.) {
											IGFDiffEst[k]=IGFDiffEstAbs[k]=999999.;
											//Print cycle-slip
											if (options->printCycleslips) {
												printCS(epoch,GNSS,PRN,i,CSTypeIGFNoEst,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,0.,0.,IGFDiffEst[k],options->csIGFThreshold,options);
											}
										} else {
											//Print cycle-slip
											if (options->printCycleslips) {
												printCS(epoch,GNSS,PRN,i,CSTypeIGFEst,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,0.,0.,IGFDiffEstAbs[k],options->csIGFThreshold,options);
											}
										}
									} else {
										// Outlier
										OutlierIGFFoundAll=1;
										OutlierIGFFound[k]=1;
									}
								} else {
									// Cycle slip (no outliers)
									IGFCheckAll = 1;
									IGFCheck[k] = 1;
									if(IGFEst==999999.) {
										IGFDiffEst[k]=IGFDiffEstAbs[k]=999999.;
										//Print cycle-slip
										if (options->printCycleslips) {
											printCS(epoch,GNSS,PRN,i,CSTypeIGFNoEst,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,0.,0.,IGFDiffEst[k],options->csIGFThreshold,options);
										}
									} else {
										//Print cycle-slip
										if (options->printCycleslips) {
											printCS(epoch,GNSS,PRN,i,CSTypeIGFEst,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,0.,0.,IGFDiffEstAbs[k],options->csIGFThreshold,options);
										}
									}
								}
							}
							//Print IGF data
							if (options->printIGFdata) {
								printIGFCSdata(epoch,GNSS,PRN,i,j,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialIGF[j][k],IGF[k],IGFDiffAbs[k],IGFEst,IGFDiffEstAbs[k],resThreshold,OutlierIGFFound[k],IGFCheck[k],options);
							}
						}
						if (epoch->cycleslip.outlierIGF[j] == 1) {
							if ( IGFCheckAll==0 && OutlierIGFFoundAll==0 ) {
								epoch->cycleslip.outlierIGF[j] = 0;
								epoch->cycleslip.use4smooth[j] = 1;
								epoch->sat[i].available = 1;
							}
						} else  {
							epoch->cycleslip.outlierIGF[j] = OutlierIGFFoundAll;
						}

					} else { 
						for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							//Print IGF data
							if (options->printIGFdata) {
								printIGFCSdata(epoch,GNSS,PRN,i,j,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k],epoch->cycleslip.initialIGF[j][k],IGF[k],IGFDiffAbs[k],999999.,999999.,999999.,0,0,options);
							}
						}
					}
				}
				//When any of the detectors detects an outlier, the arclength only has to be decreased once
				if (epoch->cycleslip.outlierMW[j]==1) {
					if (MWCheckAll==0) {
						//MW has detected an outlier
						//If MWCheckAll==1 then there is a cycle-slip
						epoch->cycleslip.use4smooth[j] = 0;
						epoch->cycleslip.arcLength[j]--;
						epoch->cycleslip.anyOutlier[j]=1;
					}
				} else if (epoch->cycleslip.outlierLI[j]==1) {
					if (LICheckAll==0) {
						//LI has detected an outlier
						//If LICheckAll==1 then there is a cycle-slip
						epoch->cycleslip.use4smooth[j] = 0;
						epoch->cycleslip.arcLength[j]--;
						epoch->cycleslip.anyOutlier[j]=1;
					}
				} else if (epoch->cycleslip.outlierIGF[j]==1) {
					if (IGFCheckAll==0) {
						//IGF has detected an outlier
						//If IGFCheckAll==1 then there is a cycle-slip
						epoch->cycleslip.use4smooth[j] = 0;
						epoch->cycleslip.arcLength[j]--;
						epoch->cycleslip.anyOutlier[j]=1;
					}
				}

				if (epoch->cycleslip.anyOutlier[j]==0) {
					NoOutlierAndNconOk=1;
					// SF Cycle slip detector
					if ( epoch->cycleslip.arcLength[j] > options->minArcLength ) {
						for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							SFdiff[k] = pow((SFPhase[k]-SFCode[k]) - epoch->cycleslip.SFmean[j][k],2);
							SFThreshold[k] = min(epoch->cycleslip.SFsigma[j][k] * pow(options->csSFkfactor,2), pow(options->csSFinit,2) * pow(options->csSFkfactor,2));
							SFCheck[k] = 0;
							if ( SFdiff[k] > SFThreshold[k] ) {
								// Cycle slip detected
								SFCheckAll=1; 
								SFCheck[k] = 1;
								//Print cycle-slip
								if (options->printCycleslips) {
									printCS(epoch,GNSS,PRN,i,CSTypeSF,mode,options->csSFMeasText[DGNSSstruct][GNSS][PRN][k],0.,0.,NULL,0.,0.,0.,0.,SFdiff[k],SFThreshold[k],0.,0.,options);
								}
							}
							//Print SF data
							if (options->printSFdata) {
								printSFCSdata(epoch,GNSS,PRN,i,j,mode,options->csSFMeasText[DGNSSstruct][GNSS][PRN][k],SFCode[k],SFPhase[k],epoch->cycleslip.SFmean[j][k],epoch->cycleslip.SFsigma[j][k],deltaSFCode[k],deltaSFPhase[k],deltaSF[k],SFdiff[k],SFThreshold[k],0,SFCheck[k],options);
							}
						}
					} else if (options->printSFdata) {
						//Print SF data
						if (epoch->cycleslip.arcLength[j]==1) {
							SFdiffFactor=0;//In the first epoch, the SFdiff is zero, as we only have one sample
						} else {
							SFdiffFactor=1.;
						}
						for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
							if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
							SFdiff[k] = (pow((SFPhase[k]-SFCode[k]) - epoch->cycleslip.SFmean[j][k],2))*SFdiffFactor;
							SFThreshold[k] = min(epoch->cycleslip.SFsigma[j][k] * pow(options->csSFkfactor,2), pow(options->csSFinit,2) * pow(options->csSFkfactor,2));
							printSFCSdata(epoch,GNSS,PRN,i,j,mode,options->csSFMeasText[DGNSSstruct][GNSS][PRN][k],SFCode[k],SFPhase[k],epoch->cycleslip.SFmean[j][k],epoch->cycleslip.SFsigma[j][k],deltaSFCode[k],deltaSFPhase[k],deltaSF[k],SFdiff[k],SFThreshold[k],0,0,options);
						}
					}
				}

			} else {
				//If DataGap or LLI triggered, no outlier is set
				NoOutlierAndNconOk=1;
			}
		}

		if (DataGapCheck || LLICheck || LICheckAll || MWCheckAll || SFCheckAll || IGFCheckAll) {
			// Cycle slip detected so reset all satellite's associated variables
			initSatellite(epoch,i,j,options);
			prealignSat(epoch,i);
			epoch->cycleslip.CSPrealignFlag[j] = 0;
			epoch->cycleslip.use4smooth[j] = 0;
			epoch->cycleslip.consistency[j]= 0;
			cycleSlipFound = 1;
			if (DataGapCheck && epoch->cycleslip.Nconsecutive[j]!=0) epoch->cycleslip.arcLength[j]=0;

			if (epoch->cycleslip.arcLength[j]!=0) {
				for(k=0;k<options->numcsMWMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csMWMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					MWVal[k]= getMeasurementValue(epoch,GNSS,PRN,options->csMWMeasList[DGNSSstruct][GNSS][PRN][k],options->csMWMeasFreq[DGNSSstruct][GNSS][PRN][k]);
					epoch->cycleslip.MWmean[j][k] = MWVal[k];
					epoch->cycleslip.MWsigma[j][k] = options->csMWInitStd*options->csMWInitStd;
					epoch->cycleslip.MWPrev[j][k][0] = MWVal[k];
					memcpy(&epoch->cycleslip.tPrevMW[j][k][0],&epoch->t,sizeof(TTime));
					//Print MW data
					if (options->printMWdata) {
						printMWCSdata(epoch,GNSS,PRN,i,j,mode,options->csMWMeasText[DGNSSstruct][GNSS][PRN][k],options->csMWMeasList[DGNSSstruct][GNSS][PRN][k],options->csMWMeasFreq[DGNSSstruct][GNSS][PRN][k],MWVal[k],MWVal[k],epoch->cycleslip.MWsigma[j][k],MWVal[k],999999.,999999.,999999.,0,0,options);
					}
				}
				for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					LIVal[k] =  getMeasurementValue(epoch,GNSS,PRN,options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k]);
					epoch->cycleslip.LIPrev[j][k][0] = LIVal[k];
					memcpy(&epoch->cycleslip.tPrevLI[j][k][0],&epoch->t,sizeof(TTime));
					//LI data has to be printed again, as the first sample of the new arc is the current epoch,so the next cycle-slip iteration 
					//goes directly to arc length 2, so the first sample, if not printed here, it is skipped
					if (options->printLIdata) {
						printLICSdata(epoch,GNSS,PRN,i,j,mode,options->csLIMeasText[DGNSSstruct][GNSS][PRN][k],options->csLIMeasList[DGNSSstruct][GNSS][PRN][k],options->csLIMeasFreq[DGNSSstruct][GNSS][PRN][k],LIVal[k],LIVal[k],0.,999999.,999999.,999999.,0,0,options);
					}
				}
				for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					IGF[k] =  getMeasurementValue(epoch,GNSS,PRN,options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k]);
					epoch->cycleslip.IGFPrev[j][k][0] = IGF[k];
					memcpy(&epoch->cycleslip.tPrevIGF[j][k][0],&epoch->t,sizeof(TTime));
					//IGF data has to be printed again, as the first sample of the new arc is the current epoch,so the next cycle-slip iteration 
					//goes directly to arc length 2, so the first sample, if not printed here, it is skipped
					if (options->printIGFdata) {
						printIGFCSdata(epoch,GNSS,PRN,i,j,mode,options->csIGFMeasText[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasList[DGNSSstruct][GNSS][PRN][k],options->csIGFMeasFreq[DGNSSstruct][GNSS][PRN][k],IGF[k],IGF[k],0.,999999.,999999.,999999.,0,0,options);
					}
				}
				// This is done to store both code and phase for SF detector for the next epoch, after the pre-alignment, in case of cycle slip
				for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
					if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
					epoch->cycleslip.SFCodePrev[j][k] = SFCode[k]; //Code is not prealigned, so the value remains the same after pre-alignment
					epoch->cycleslip.SFPhasePrev[j][k] = SFPhase[k] = getMeasurementValue(epoch,GNSS,PRN,&options->csSFMeasList[DGNSSstruct][GNSS][PRN][k][1],&options->csSFMeasFreq[DGNSSstruct][GNSS][PRN][k][1]);
					//Print SF data
					if (options->printSFdata) {
						printSFCSdata(epoch,GNSS,PRN,i,j,mode,options->csSFMeasText[DGNSSstruct][GNSS][PRN][k],SFCode[k],SFPhase[k],SFPhase[k]-SFCode[k],pow(options->csSFinit,2),999999.,999999.,999999.,0.,pow(options->csSFinit,2) * pow(options->csSFkfactor,2),0,0,options);
					}
				}
			}
			//Set print flag
			#if defined _OPENMP
				#if _OPENMP<OPENMP_VERSION_4
					#pragma omp critical (CycleSlipsAnyMessageToPrint)
					//OpenMP versions<4 do not support atomic writes, therefore we need to set an exclusive area (critical section)
					{
						AnyMessageToPrint=options->printCycleslips;
					}
				#else
					#pragma omp atomic write
					AnyMessageToPrint=options->printCycleslips;
				#endif
			#else
				AnyMessageToPrint=options->printCycleslips;
			#endif

		}

		// Update the SF detector parameters
		if ( NoOutlierAndNconOk ) {
			// Update sliding window
			for(k=0;k<options->numcsSFMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csSFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				for ( l=0;l<MAX_SLIDING_WINDOW-1;l++ ) {
					epoch->cycleslip.windowSF[j][k][l] = epoch->cycleslip.windowSF[j][k][l+1];
					epoch->cycleslip.windowSFtime[j][k][l] = epoch->cycleslip.windowSFtime[j][k][l+1];
				}
				epoch->cycleslip.windowSF[j][k][MAX_SLIDING_WINDOW-1] = SFPhase[k]-SFCode[k];
				epoch->cycleslip.windowSFtime[j][k][MAX_SLIDING_WINDOW-1] = tsec(&epoch->t);

				// Computing the number of samples in inside the sliding window
				samples = 0;
				for ( l=0;l<MAX_SLIDING_WINDOW;l++ ) {
					if ( tsec(&epoch->t)-epoch->cycleslip.windowSFtime[j][k][l] < options->csSFwindow ) {
						samples++;
					}
				}

				// Computing the mean and quadratic mean in the sliding window
				auxMean = 0.0;
				auxMean2 = 0.0;
				for ( l=MAX_SLIDING_WINDOW-1;l>MAX_SLIDING_WINDOW-samples-1;l-- ) {
					auxMean += epoch->cycleslip.windowSF[j][k][l];
					auxMean2 += pow(epoch->cycleslip.windowSF[j][k][l],2);
				}
				if ( cycleSlipFound || samples == 0 ) {
					epoch->cycleslip.SFmean[j][k] = SFPhase[k]-SFCode[k];
					epoch->cycleslip.SFsigma[j][k] = pow(options->csSFinit,2);
				} else {
					epoch->cycleslip.SFmean[j][k] = auxMean / ((double)samples);
					sigma2 = (auxMean2 / ((double)samples)) - pow(epoch->cycleslip.SFmean[j][k],2);
					epoch->cycleslip.SFsigma[j][k] = sigma2 - (sigma2-pow(options->csSFinit,2))/((double)samples);
				}
			}

			// Update arithmetic mean and standard deviation for Melbourne-Wubbena
			for(k=0;k<options->numcsMWMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csMWMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				if ( epoch->cycleslip.arcLength[j] > 1 ) {
					epoch->cycleslip.MWsigma[j][k] += (pow(MWVal[k]-epoch->cycleslip.MWmean[j][k],2) - epoch->cycleslip.MWsigma[j][k]) / epoch->cycleslip.arcLength[j];
					epoch->cycleslip.MWmean[j][k] += (MWVal[k]-epoch->cycleslip.MWmean[j][k]) / epoch->cycleslip.arcLength[j];
				} else if ( epoch->cycleslip.arcLength[j]==0 ) {
					epoch->cycleslip.MWmean[j][k] = MWVal[k];
				}

				// Update sliding window
				for ( l=0;l<MAX_SLIDING_WINDOW-1;l++ ) {
					epoch->cycleslip.windowMW[j][k][l] = epoch->cycleslip.windowMW[j][k][l+1];
					epoch->cycleslip.windowMWtime[j][k][l] = epoch->cycleslip.windowMWtime[j][k][l+1];
				}
				epoch->cycleslip.windowMW[j][k][MAX_SLIDING_WINDOW-1] = MWVal[k];
				epoch->cycleslip.windowMWtime[j][k][MAX_SLIDING_WINDOW-1] = tsec(&epoch->t);

				// Computing the number of samples in inside the sliding window
				samples = 0;
				for ( l=0;l<MAX_SLIDING_WINDOW;l++ ) {
					if ( tsec(&epoch->t)-epoch->cycleslip.windowMWtime[j][k][l] < options->csMWwindow ) {
						samples++;
					}
				}

				// Computing the mean value for the sliding window
				auxMean = 0.0;
				for ( l=MAX_SLIDING_WINDOW-1;l>MAX_SLIDING_WINDOW-samples-1;l-- ) {
					auxMean += epoch->cycleslip.windowMW[j][k][l];
				}
				if ( cycleSlipFound || samples == 0 ) {
					epoch->cycleslip.MWmean300[j][k] = MWVal[k];
				} else {
					epoch->cycleslip.MWmean300[j][k] = auxMean / ((double)samples);
				}
			}

			// Update previous LI for Geometry-free
			for(k=0;k<options->numcsLIMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csLIMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				epoch->cycleslip.initialLI[j][k] = LIVal[k];
			}

			// Update previous IGF for Iono-Geometry-free
			for(k=0;k<options->numcsIGFMeasList[DGNSSstruct][GNSS][PRN];k++) {
				if (options->csIGFMeasSelected[DGNSSstruct][GNSS][PRN][k]!=MEASSELECTED) continue;
				epoch->cycleslip.initialIGF[j][k] = IGF[k];
			}
		}
	}

	//Print messages. They are printed outside the loop in order to maintain printing order even with multithreading (and for printing messages grouped by constellation)
	if (options->printSFdata) {
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(m=0;m<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];m++) {
				for (n=0;n<linesstoredSFCSdata[i][m];n++) {
					fprintf(options->outFileStream,"%s",printbufferSFCSdata[i][m][n]);
				}
				linesstoredSFCSdata[i][m]=0;
			}
		}
	}

	if (options->printMWdata) {
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(m=0;m<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];m++) {
				for (n=0;n<linesstoredMWCSdata[i][m];n++) {
					fprintf(options->outFileStream,"%s",printbufferMWCSdata[i][m][n]);
				}
				linesstoredMWCSdata[i][m]=0;
			}
		}
	}

	if (options->printLIdata) {
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(m=0;m<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];m++) {
				for (n=0;n<linesstoredLICSdata[i][m];n++) {
					fprintf(options->outFileStream,"%s",printbufferLICSdata[i][m][n]);
				}
				linesstoredLICSdata[i][m]=0;
			}
		}
	}

	if (options->printIGFdata) {
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(m=0;m<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];m++) {
				for (n=0;n<linesstoredIGFCSdata[i][m];n++) {
					fprintf(options->outFileStream,"%s",printbufferIGFCSdata[i][m][n]);
				}
				linesstoredIGFCSdata[i][m]=0;
			}
		}
	}

	if (AnyMessageToPrint) {
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(m=0;m<epoch->numSatellitesGNSS[epoch->PrintPos2GNSS[i]];m++) {
				for (n=0;n<linesstoredCS[i][m];n++) {
					fprintf(options->outFileStream,"%s",printbufferCS[i][m][n]);
				}
				linesstoredCS[i][m]=0;
			}
		}
	}
	
	return;
}

/*****************************************************************************
 * Name        : smoothEpoch
 * Description : Smooth the pseudorange measurements to be used in the filter
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void smoothEpoch (TEpoch *epoch, TOptions *options) {
	int			i, j, k,l;
	int			smoothN;
	double		smoothWith;
	double		measurement;
	int			DGNSSstruct=epoch->DGNSSstruct;
	TSatellite	*sat;
	
	if ( options->smoothEpochs != 0 ) {
		for (j=0;j<epoch->numSatellites;j++) {
			sat = &epoch->sat[j];
			if (options->includeSatellite[sat->GNSS][sat->PRN]==0) continue;	
			l = epoch->satCSIndex[sat->GNSS][sat->PRN];
			for(k=0;k<options->numfilterMeasWithSmoothing[DGNSSstruct][sat->GNSS][sat->PRN];k++) {
				i=options->filterIndListWithSmoothing[DGNSSstruct][sat->GNSS][sat->PRN][k];
				getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterSmoothMeasList[DGNSSstruct][sat->GNSS][sat->PRN][i], options->filterSmoothMeasfreq[DGNSSstruct][sat->GNSS][sat->PRN][i],&smoothWith, NULL,0);
				getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterMeasList[DGNSSstruct][sat->GNSS][sat->PRN][i], options->filterMeasfreq[DGNSSstruct][sat->GNSS][sat->PRN][i], &measurement, NULL,0);
				if ( epoch->cycleslip.use4smooth[l] == 1 && epoch->cycleslip.arcLength[l] > options->minArcLength ) {
					smoothN = epoch->cycleslip.arcLength[l] - options->minArcLength;
					if ( smoothN > options->smoothEpochs ) {
						smoothN = options->smoothEpochs;
					}
					// Sanity check
					if ( smoothN == 0 ) smoothN = 1;
					
					epoch->cycleslip.smoothedMeas[l][i] = (((double)(smoothN-1)) * epoch->cycleslip.smoothedMeas[l][i] + (measurement-smoothWith)) / ((double)(smoothN));
				}
			}
		}
	}
}

/*****************************************************************************
 * Name        : sigmaInflation
 * Description : Sigma inflation factor during smoother convergence
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void sigmaInflation (TEpoch *epoch, TOptions *options) {
	int			i, j;
	int			Nstdy;
	int			nexpN, nexpS;
	double		fsigN, fsigS;
	double		fact1, fact2;

	if ( options->smoothEpochs != 0 && options->sigmaInflation == 1 ) {
		Nstdy = (int)( 3.6 * options->smoothEpochs );
		nexpS = 2 * ( Nstdy - options->smoothEpochs ) + 1;
		fact1 = 1.0 / ( (double)( 2 * options->smoothEpochs - 1 ) );
		fact2 = ( (double)( options->smoothEpochs - 1 ) ) / ( (double)(options->smoothEpochs) );
		fsigS = fact1 * ( 1.0 + pow(fact2, nexpS) );


		for ( j = 0; j < epoch->numSatellites; j++ ) {
			i = epoch->satCSIndex[epoch->sat[j].GNSS][epoch->sat[j].PRN];
			nexpN = 2 * ( epoch->cycleslip.arcLength[i] - options->smoothEpochs ) + 1;
			fsigN = 0.0;
			if ( epoch->cycleslip.use4smooth[i] == 1 && epoch->cycleslip.arcLength[i] >= options->smoothEpochs ) {
				fsigN = fact1 * ( 1.0 + pow(fact2, nexpN) );
			} else if ( epoch->cycleslip.use4smooth[i] == 1 && epoch->cycleslip.arcLength[i] < options->smoothEpochs ) {
				if (epoch->cycleslip.arcLength[i]==0) fsigN = 1.0;
				else {
					fsigN = 1.0 / ( (double)( epoch->cycleslip.arcLength[i] ) );
				}
			}
			epoch->dgnss.sigmaInflation[i] = fsigN / fsigS;
		}
	} else {
		for ( j = 0; j < epoch->numSatellites; j++ ) {
			i = epoch->satCSIndex[epoch->sat[j].GNSS][epoch->sat[j].PRN];
			epoch->dgnss.sigmaInflation[i] = 1.0;
		}
	}
}
