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
 * File: preprocessing.c
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
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
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
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
	if ( options->prealignCP ) prealignEpoch(epoch);
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
	int 			i, index, maxMatch;
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
		index = 0;
		maxMatch = 0;
		for ( i = 0; i < 10; i++ ) {
			if ( arraySR[i] != 0.0 ) {
				if ( counter[i] > maxMatch ) {
					index = i;
					maxMatch = counter[i];
				}
			}
		}
		// Stop the evaluation
		if ( maxMatch > 11 ) {
			epoch->receiver.look4interval = 0;
			//Disable N-con if interval is greater than or equal than 15 seconds
			if ( arraySR[index] >= 15.0 ) {
				options->csNcon = 0;
			} else if (options->csNconAutoDisabled==1) {
				options->csNcon = 1;
			}
		}

		epoch->receiver.interval = arraySR[index];
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
		diff = fabs(tdiff(t,&satInfo->lastEclipse));
		if ( diff <= 1800 ) { // 30 minutes
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
	int						i,j;
	enum GNSSystem			GNSS;
	enum MeasurementType	meas;
	double					CP,PR;
	double					lambda;
	int						ret1,ret2;
	i = epoch->satCSIndex[epoch->sat[ind].GNSS][epoch->sat[ind].PRN];
	
	if ( epoch->prealign == 0 ) return;
	if ( epoch->cycleslip.arcLength[i] == 0 || ( epoch->cycleslip.arcLength[i] == 1 && epoch->cycleslip.CSPrealignFlag[i] == 1 ) ) {
		GNSS = epoch->sat[ind].GNSS;
		for ( j=0;j<epoch->measOrder[GNSS].nDiffMeasurements;j++ ) {
			meas = epoch->measOrder[GNSS].ind2Meas[j];
			//if (epoch->measOrder[GNSS].usable[meas]==1) { // Measurement has NOT been invalidated
				if ( whatIs(meas) == CarrierPhase ) {
					// Set prealign value to 0
					epoch->cycleslip.preAlign[i][j] = 0.0;
					ret1 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,meas,&CP,NULL);
					ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,meas-1,&PR,NULL);
					// Special cases: 
					// For the case of L1P, for GPS, if it cannot prealign with C1P (P1 code), it
					// will try to prealign it with C1C (C1 code).
					if ( meas == L1P && ret2 == 0 ) {
						ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,C1C,&PR,NULL);
					}
					// For the case of L2P, for GPS, if it cannot prealign with C2P (P2 code), it
					// will try to prealign it with C2C (C2 code).
					if ( meas == L2P && ret2 == 0 ) {
						ret2 = getMeasModelValue(epoch,GNSS,epoch->sat[ind].PRN,C2C,&PR,NULL);
					}
					// Obtain prealign value
					if ( ret1 != 0 && ret2 != 0 ) { 
						lambda = getLambda(GNSS,meas);
						epoch->cycleslip.preAlign[i][j] = ((int)((PR-CP)/lambda));
			//		} else { // Mark CP as invalid if it was not
			//			epoch->sat[ind].meas[j].value = -1;
			//			initSatellite(epoch,ind);
			//			epoch->sat[ind].arcLength = 0; // This is to invalidate current epoch
					}
				}		
			//}
		}
	}
}

/*****************************************************************************
 * Name        : prealignEpoch
 * Description : Pre-align pseudorange and carrier-phase an entire epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 *****************************************************************************/
void prealignEpoch (TEpoch *epoch) {
	int		i;
	
	epoch->prealign = 1;
	for ( i=0;i<epoch->numSatellites;i++ ) {
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
	double		*xPrev,x;
	TTime		tRef;
	
	yEst = 0;
	xPrev = malloc(sizeof(double)*(degree+1));

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

	free(xPrev);
	
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
	int						mode;
	static int				clockupdatems[2] = {0,0};
	static int				firstepoch = 1;
	enum MeasurementType	meas;
	double					Threshold = 200000;	//Threshold is 200Km
	double					MeansmsJump = 0;		//Mean correction of the clock in milliseconds
	double					diffCode, diffPhase, diffCodePhase;
	static double			PrevC1[2][MAX_GNSS][MAX_SBAS_PRN];
	static double			PrevL1[2][MAX_GNSS][MAX_SBAS_PRN];
	double					clockupdateMeters;

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
				if ( whatIs(meas) == CarrierPhase ) {
					if ( epoch->sat[i].meas[j].rawvalue != -1 ) {
						epoch->sat[i].meas[j].value+=(double)clockupdateMeters/epoch->measOrder[epoch->sat[i].GNSS].conversionFactor[meas];
					}
				}
			}
		}
	}

	return returnvalue;
}

/*****************************************************************************
 * Name        : polyfit
 * Description : Fits a polynomial and estimates the Li/Lc prediction
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 * int  i                          I  N/A  Index for current satellite
 * int  type                       I  N/A  0 -> Li prediction
 *                                         1 -> Lc prediction
 * int  numsamples                 I  N/A  Number of samples
 * double  *res                    O  N/A  Polynomial residual
 * Returned value (double)         O  N/A  Li/Lc prediction
 *****************************************************************************/
double polyfit (TEpoch *epoch, TOptions *options, int i, int type, int numsamples, double *res) {
	int		j,k,l,istart,resi;
	int		flipJ[numsamples];
	int		outlier;
	double	a[numsamples][3];
	//double	x[numsamples]; //Commented to avoid the warning "set but not used"
	double	y[numsamples];
	double	va[6] = {0, 0, 0, 0, 0, 0};
	double	aty[3] = {0, 0, 0};
	double	coef[3] = {0, 0, 0};
	double	x0 = 0.0;
	double	tempo, Est;

	// Initialize
	for ( j=0;j<numsamples;j++ ) {
		flipJ[j] = numsamples-j-1;
		//x[j] = 0;
		y[j] = 0;
	}

	//LC detector is disabled at the moment. The following line is to avoid warning
	type+=0;

	// Build the matricial equations
	for ( j=numsamples-1;j>=0;j-- ) {
		//if(type==0) {
			tempo = tdiff(&epoch->cycleslip.tPrevLI[i][flipJ[j]],&epoch->cycleslip.tPrevLI[i][0]);
		//} else {
			//tempo = tdiff(&epoch->cycleslip.tPrevLC[i][flipJ[j]],&epoch->cycleslip.tPrevLC[i][0]);
		//}
		//x[j] = tempo;
		for ( k=0;k<3;k++ ) {
			// Build Vandermonde matrix for time samples
			a[j][k] = pow(tempo,k);
		}

		//if(type==0) {
			// Build array of LI
			y[j] = epoch->cycleslip.LiPrev[i][flipJ[j]] - epoch->cycleslip.LiPrev[i][0];
		//} else {
			// Build array of LC
			//y[j] = epoch->cycleslip.LcPrev[i][flipJ[j]] - epoch->cycleslip.LcPrev[i][0];
		//}
	}

	//if(type==0) {
		outlier= epoch->cycleslip.outlierLI[i]+epoch->cycleslip.outlierBw[i];
	//} else {
		//outlier= epoch->cycleslip.outlierLC[i];
	//}
	// Avoid outlier in fitting the polynomial (any outlier detected in LI or Bw)
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
		//sprintf(messagestr,"Problem in CHOLESKI3 res=%d\n",resi);
		//printError(messagestr,options);
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

	//if(type==0) {
		for ( j=2; j>=0; j-- ) {
			x0 += coef[j] * pow(tdiff(&epoch->t,&epoch->cycleslip.tPrevLI[i][0]), j);
		}
		Est = x0 + epoch->cycleslip.LiPrev[i][0];
	/*} else {
		for ( j=2; j>=0; j-- ) {
			x0 += coef[j] * pow(tdiff(&epoch->t,&epoch->cycleslip.tPrevLC[i][0]), j);
		}
		Est = x0 + epoch->cycleslip.LcPrev[i][0];
	}*/

	return Est;
}

/*****************************************************************************
 * Name        : checkCycleSlips
 * Description : Check for carrier-phase cycle slips. At the moment it is only 
 *               prepared for GPS
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

	int				ii;
	int				allCSDetectorsOff=0; //This variable is not changed, no need to declare it private in the for loop for multithreading

	if ( options->csL1C1 == 0 && options->csBW == 0 && options->csLI == 0 && options->csLLI == 0 ) {
		allCSDetectorsOff=1;
	}
	

	// Go over all the satellites
	#pragma omp parallel for 
	for ( ii=0;ii<epoch->numSatellites;ii++ ) {
		
		//In this case, variable are declared inside the loop. This is done to allow some compiler optimizations in single thread (as
		//by declaring the variable inside the for we are telling the variable that the scope of the variable is only inside the for loop)
		//and also, in multithread, as all variables have to be private, the compiler can optimize the code as variables are declared inside
		//the loop, it does not need to make a local copy of the variable when the thread starts (if the variables were declared outside
		//the for loop, the variables would be in the "private" OpenMP directive -see gLAB version 5.3.0-, making now the '#pragma' directive shorter)

		int 			i,j;
		int 			cycleSlipFound = 0;
		int 			measCheck = 0;		// Global measurement check
		enum GNSSystem system = epoch->sat[ii].GNSS;

		double			auxMean;
		double			auxMean2;
		int				samples;
		enum			MeasurementType	meas;
		int				index;
		double			tdiffNcon;
		double			SNR;

		// Data Gap
		double			timeDiff;
		int 			DataGapCheck = 0;	// 0 => no CS detected by Data gap detector
											// 1 => CS detected by Data gap detector

		// Loss of Lock Indicator (LLI)
		int				lli;
		int 			LLICheck = 0;		// 0 => no CS detected by LLI detector
											// 1 => CS detected by LLI detector

		int 			measLLI = 0;		// 0 => at least one measurement (L1, C1) is missed or not OK
											// 1 => all measurements (L1 and C1) are OK
		
		// Melbourne-Wubbena (BW)
		double			Bw;
		double			nBwdiff;
		double			nBw300diff;
		double			nBwdiffThreshold;
		double			C2;
		int 			BwCheck = 0;		// 0 => no CS detected by Melbourne-Wubbena detector
											// 1 => CS detected by Melbourne-Wubbena detector

		int 			measBW = 0;			// 0 => at least one measurement (L1, C1, L2 and C2) is missed or not OK
											// 1 => all measurements (L1, C1, L2 and C2) are OK

		// Geometry-free (LI)
		double			Li, LiEst;
		double			LiThreshold;
		double			res;
		double			LiDiff;
		int 			LiCheck = 0;		// 0 => no CS detected by Geometry-free detector
											// 1 => CS detected by Geometry-free detector

		int 			measLI = 0;			// 0 => at least one measurement (L1, L2) is missed or not OK
											// 1 => all measurements (L1 and L2) are OK
		
		// L1-C1
		double			L1, C1;
		double			L1C1diff;
		double			sigma2;
		double			deltaC1;
		double			deltaL1;
		double 			L1C1Threshold = 0;	// Threshold of C1L1 difference detector
		int 			L1C1Check = 0;		// 0 => no CS detected by L1C1 difference detector
											// 1 => CS detected by L1C1 difference detector

		int 			measL1C1 = 0;		// 0 => at least one measurement (L1, C1) is missed or not OK
											// 1 => all measurements (L1 and C1) are OK

		//Ncon
		int 			measNcon = 1;		// 0 => at least one measurement (C1C or C1P) is missed or not OK
											// 1 => all measurements (C1C or C1P) are OK

		// Index of the satellite in the dictionary
		i = epoch->satCSIndex[epoch->sat[ii].GNSS][epoch->sat[ii].PRN];

		// Initialise several checks
		epoch->cycleslip.preCheck[i] = 0;
		epoch->cycleslip.consistency[i] = 0;
		epoch->cycleslip.CS[i] = 0;
		epoch->cycleslip.use4smooth[i] = 1;
		epoch->sat[ii].hasSNR = 1;

		// Check SNR 
		if ( options->SNRfilter == 1 ) {
			//Check first is 'S' measurement with SNR is available
			if (epoch->sat[ii].GNSS==GPS) { //GPS Only!!
				if(epoch->measOrder[epoch->sat[ii].GNSS].hasSNRmeas==1) {
					SNR=epoch->sat[ii].meas[epoch->measOrder[epoch->sat[ii].GNSS].SNRmeaspos[1]].value;
					if (SNR<options->SNRvalues[epoch->sat[ii].GNSS][epoch->sat[ii].PRN]) {
						if (SNR!=-1.) {
							//F1 is under SNR threshold
							epoch->sat[ii].hasSNR = 0;
							epoch->sat[ii].lowSNR = SNR;
							epoch->cycleslip.use4smooth[i] = 0;
							continue;
						}
					}	
					if (options->solutionMode==PPPMode) {
						SNR=epoch->sat[ii].meas[epoch->measOrder[epoch->sat[ii].GNSS].SNRmeaspos[2]].value;
						if (SNR<options->SNRvalues[epoch->sat[ii].GNSS][epoch->sat[ii].PRN]) {
							if (SNR!=-1.) {
								//F2 is under SNR threshold
								epoch->sat[ii].hasSNR = 0;
								epoch->sat[ii].lowSNR = SNR;
								epoch->cycleslip.use4smooth[i] = 0;
								continue;
							}
						}	
					}
				} else {
					//Look for quantizied SNR measurement (the number next to the measurement)
					for ( j=0;j<epoch->measOrder[epoch->sat[ii].GNSS].nDiffMeasurements;j++ ) {
						if ( epoch->sat[ii].meas[j].SNRdBHz<options->SNRvalues[epoch->sat[ii].GNSS][epoch->sat[ii].PRN] ) {
							// SNR below user threshold
							// Check if SBAS mode is activated, and if it is a measurement used in SBAS
							if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
								meas = epoch->measOrder[epoch->sat[ii].GNSS].ind2Meas[j];
								if ( meas != C1C && meas != L1C && meas != L1P ) continue;
							}
							epoch->sat[ii].hasSNR = 0;
							epoch->sat[ii].lowSNR = (double)epoch->sat[ii].meas[j].SNRdBHz;
							epoch->cycleslip.use4smooth[i] = 0;
							continue;
						}
					}
				}
			}
		}

		// If any detector is enabled, just go ahead
		if ( allCSDetectorsOff == 1 ) {
			if ( options->csNcon ) {
				if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1C);
				} else {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1P);
				}
				if ( C1==-1) measNcon=0;
			} else {
				epoch->cycleslip.arcLength[i]++;
				continue;
			}
		}

		if ( system == GPS ) {
			// Update the Loss of Lock Indicator
			lli = 0;
			for ( j=0;j<epoch->measOrder[epoch->sat[ii].GNSS].nDiffMeasurements;j++ ) {
				if ( options->csLLI == 1 && options->csL1C1 == 0 && options->csBW == 0 && options->csLI == 0 ) {
					lli = (int)epoch->sat[ii].meas[j].LLI;
					if ( lli%2 != 0 ) break;
				} else {
					meas = epoch->measOrder[epoch->sat[ii].GNSS].ind2Meas[j];
					if ( meas == L1P && options->csL1C1 && epoch->sat[ii].meas[j].LLI != 0 ) {
						lli = (int)epoch->sat[ii].meas[j].LLI;
						break;
					}
					if ( meas == L2P && (options->csBW || options->csLI ) && epoch->sat[ii].meas[j].LLI != 0 ) {
						lli = (int)epoch->sat[ii].meas[j].LLI;
						break;
					}
				}
			}

			// Measurements Pre-Check
			if ( options->csLLI ) { // LLI
				if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1C);
				} else {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1P);
				}
				L1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,L1P);
				measLLI = 1;
				if ( L1 == -1 || C1 == -1 ) {
					measLLI = 0;
				}
			}
			if ( options->csL1C1 ) { // L1-C1
				if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1C);
				} else {
					C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1P);
				}
				L1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,L1P);
				measL1C1 = 1;
				if ( L1 == -1 || C1 == -1 ) {
					measL1C1 = 0;
				}
				// Consistency of measurements (only for single-frequency)
				else if ( epoch->cycleslip.arcLength[i] > 0 && options->csUnconsistencyCheck ) {
					deltaC1 = C1-epoch->cycleslip.C1Prev[i];
					deltaL1 = L1-epoch->cycleslip.L1Prev[i];
					if ( fabs(deltaC1-deltaL1) > options->csUnconsistencyCheckThreshold) {
						//measL1C1 = 0;
						epoch->cycleslip.consistency[i] = 1;
					}
				}
				if ( L1 != -1 && C1 != -1 && options->csUnconsistencyCheck ) {
					epoch->cycleslip.L1Prev[i] = L1;
					epoch->cycleslip.C1Prev[i] = C1;
				}
			}
			if ( options->csBW ) { // Melbourne-Wubbena
				Bw = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,BW);
				C1 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1P);
				C2 = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C2P);
				measBW = 1;
				if ( Bw == -1 || C1 == -1 || C2 == -1 ) {
					measBW = 0;
				}
			}
			if ( options->csLI ) { // Geometry-free
				Li = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,LI);
				measLI = 1;
				if ( Li == -1 ) {
					measLI = 0;
				}
				// Geometry-free cycle slip detector
				if ( fabs(epoch->cycleslip.initialLi[i] - Li) > options->csLImaxjump && 
					 epoch->cycleslip.arcLength[i] > 0 && measLI ) {
					LiCheck = 1;
					LiThreshold = options->csLImaxjump;
					LiDiff = epoch->cycleslip.initialLi[i] - Li;
					// Update previous epoch (time) to check if there is data gap
					memcpy(&epoch->cycleslip.previousEpoch[i],&epoch->t,sizeof(TTime));
					// Update previous epoch (time) to check if there is N-consecutive epochs
					memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
				}
			}

			// Loss of Lock Indicator (LLI)
			//   Range: 0-7
			//      0 or blank: OK or not known
 			//      1, 3, 5 and 7: Lost lock between previous and current observation: cycle slip possible
			if ( ( lli==1 || lli==3 || lli==5 || lli==7 ) && options->csLLI ) {
				LLICheck = 1; // Cycle slip detected
				// Update previous epoch (time) to check if there is data gap
				memcpy(&epoch->cycleslip.previousEpoch[i],&epoch->t,sizeof(TTime));
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
			}

			// Measurements Pre-Check. Check if all necessary measurements are available
			measCheck = 1; // Initialize as OK
			// LLI flag availability
			if ( options->csLLI && !measLLI ) measCheck = 0;
			// L1-C1 difference availability
			if ( options->csL1C1 && !measL1C1 ) measCheck = 0;
			// Melbourne-Wubbena availability
			if ( options->csBW && !measBW ) measCheck = 0;
			// Geometry-free availability
			if ( options->csLI && !measLI )	measCheck = 0;
			// Ncon availability
			if ( options->csNcon && !measNcon )	measCheck = 0;
			// Pre-Check of measurements (check measurements availability)
			if ( !measCheck ) {
				epoch->cycleslip.preCheck[i] = 1;
				epoch->cycleslip.use4smooth[i] = 0;
			}

			// Data Gap Cycle Slip Detector
			if ( (tdiff(&epoch->t,&epoch->cycleslip.previousEpoch[i]) - options->csDataGap) > 1E-4 && //The 1E-4 is to avoid problems with decimals
				 epoch->cycleslip.arcLength[i] > 0 && measCheck && allCSDetectorsOff==0 ) {
				DataGapCheck = 1; // Cycle slip detected
				timeDiff = tdiff(&epoch->t,&epoch->cycleslip.previousEpoch[i]);
				// Update previous epoch (time) to check if there is data gap
				memcpy(&epoch->cycleslip.previousEpoch[i],&epoch->t,sizeof(TTime));
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
			}

			// N-consecutive data
			if ( options->csNcon ) {
				if ( epoch->receiver.interval < 15.0  && measCheck ) {
					tdiffNcon=tdiff(&epoch->t,&epoch->cycleslip.previousEpochNconsecutive[i]);
					// Check if there are N-consecutive samples
					if ( (tdiffNcon - epoch->receiver.interval) > 1E-4 &&  //The 1E-4 is to avoid problems with decimals
						 tdiffNcon <= options->csDataGap &&
						 epoch->cycleslip.arcLength[i] > 0 ) {
						epoch->cycleslip.Nconsecutive[i] = options->csNconMin;
						epoch->cycleslip.use4smooth[i] = 0;
						// Update previous epoch (time) to check if there is N-consecutive epochs
						memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
					} else if ( (tdiffNcon - epoch->receiver.interval) > 1E-4 &&  //The 1E-4 is to avoid problems with decimals
						   allCSDetectorsOff == 1 ) {
						epoch->cycleslip.Nconsecutive[i] = options->csNconMin;
						epoch->cycleslip.use4smooth[i] = 0;
						// Update previous epoch (time) to check if there is N-consecutive epochs
						memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
					} else if ( epoch->cycleslip.Nconsecutive[i] < 0 ) {
						// Increase N-consecutive to avoid the following N epochs after data hole
						epoch->cycleslip.Nconsecutive[i]++;
						epoch->cycleslip.use4smooth[i] = 0;
						// Update previous epoch (time) to check if there is N-consecutive epochs
						memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
						if (allCSDetectorsOff == 1 && epoch->cycleslip.Nconsecutive[i] == 0 ) epoch->cycleslip.arcLength[i]++;
					} else if ( allCSDetectorsOff == 1 ) {
						epoch->cycleslip.arcLength[i]++;
						epoch->cycleslip.use4smooth[i] = 1;
						// Update previous epoch (time) to check if there is N-consecutive epochs
						memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
					}
				} else if ( epoch->receiver.interval >= 15.0  && measCheck && allCSDetectorsOff == 1) {
					epoch->cycleslip.arcLength[i]++;
				}
				if ( allCSDetectorsOff == 1 ) continue;
			}

			if ( options->csL1C1 && epoch->cycleslip.consistency[i]) {
				//Consistency check was triggered
				epoch->cycleslip.use4smooth[i] = 0;
				//If  data gap or LLI or Li precheck were triggered, leave measCheck=1 so cycle-slip is triggered
				if (DataGapCheck==0 && LLICheck==0 && LiCheck==0 ) {
					//If there was no data gap or LLI or Li precheck detection, then do not check for cycle-slips
					measCheck=0;
					measL1C1 = 0;
					epoch->cycleslip.preCheck[i] = 1;
				}
			}
			
			// Everything OK
			if ( DataGapCheck == 0 && LLICheck == 0 && measCheck && epoch->cycleslip.Nconsecutive[i] == 0 ) {
				// Update the arc length
				epoch->cycleslip.arcLength[i]++;
				// Update previous epoch (time) to check if there is data gap
				memcpy(&epoch->cycleslip.previousEpoch[i],&epoch->t,sizeof(TTime));
				// Update previous epoch (time) to check if there is N-consecutive epochs
				memcpy(&epoch->cycleslip.previousEpochNconsecutive[i],&epoch->t,sizeof(TTime));
				

				// L1-C1 Cycle slip detector [single-frequency]
				if ( options->csL1C1 && measL1C1 && !epoch->cycleslip.outlierLI[i] && !epoch->cycleslip.outlierBw[i] ) {
					// Calculate the difference between the mean and the current L1-C1
					L1C1diff = pow((L1-C1) - epoch->cycleslip.L1C1mean[i],2);

					// Update threshold
					L1C1Threshold = min(epoch->cycleslip.L1C1sigma[i] * pow(options->csL1C1kfactor,2), pow(options->csL1C1init,2) * pow(options->csL1C1kfactor,2));

					// Check if there is cycle slip
					if ( epoch->cycleslip.arcLength[i] > options->minArcLength ) {
						if ( L1C1diff > L1C1Threshold ) {
							L1C1Check = 1; // Cycle slip detected
						}
					}
				}

				// Melbourne-Wubbena (BW) [dual-frequency]
				if ( options->csBW && measBW ) {
					if ( epoch->cycleslip.arcLength[i] > options->minArcLength ) {
						// Melbourne-Wubbena cycle slip detector
						nBwdiff = fabs(Bw-epoch->cycleslip.BWmean[i]);
						nBw300diff = fabs(Bw-epoch->cycleslip.BWmean300[i]);
						nBwdiffThreshold = options->csBWkfactor * sqrt(epoch->cycleslip.BWsigma[i]);
						//nBwdiffThreshold = min(options->csBWkfactor * sqrt(epoch->cycleslip.BWsigma[i]), 240.0);

						if ( (nBwdiff > nBwdiffThreshold &&
							 nBw300diff > options->csBWmin &&
							 sqrt(epoch->cycleslip.BWsigma[i]) <= options->csBWmin) ||
							 (nBwdiff > 10.0*options->csBWmin && epoch->cycleslip.arcLength[i] > 2) ) {
							if ( epoch->cycleslip.outlierBw[i] == 1) {
								// Cycle slip confirmed
								BwCheck = 1;
							} else {
								// Outlier
								epoch->cycleslip.outlierBw[i] = 1;
							}
						} else if ( epoch->cycleslip.outlierBw[i] == 1) {
							epoch->cycleslip.outlierBw[i] = 0;
							epoch->cycleslip.use4smooth[i] = 1;
							epoch->sat[ii].available = 1;
						}
					}
				}

				// Geometry-free carrier-phase combination (LI) [dual-frequency]
				if ( options->csLI && measLI && !LiCheck ) {
					// Update both historical LI and epochs
					if ( epoch->cycleslip.arcLength[i] <= options->csLIsamples+1 ) {
						index = epoch->cycleslip.arcLength[i]-1;
						epoch->cycleslip.LiPrev[i][index] = Li;
						memcpy(&epoch->cycleslip.tPrevLI[i][index],&epoch->t,sizeof(TTime));
					} else {
						for (j=0;j<options->csLIsamples;j++) {
							epoch->cycleslip.LiPrev[i][j] = epoch->cycleslip.LiPrev[i][j+1];
							memcpy(&epoch->cycleslip.tPrevLI[i][j],&epoch->cycleslip.tPrevLI[i][j+1],sizeof(TTime));
						}
						epoch->cycleslip.LiPrev[i][options->csLIsamples] = Li;
						memcpy(&epoch->cycleslip.tPrevLI[i][options->csLIsamples],&epoch->t,sizeof(TTime));
					}

					// Enough data to build polynomial fit
					if ( epoch->cycleslip.arcLength[i] > options->minArcLength ) {
						// Fit polynomial and estimate the Li prediction
						LiEst = polyfit(epoch, options, i, 0, options->csLIsamples, &res);
						// Compute the threshold
						LiThreshold = options->csLImax / (1.0 + exp(-options->csDataGap/options->csLIt));

						// Geometry-free cycle slip detector
						if ( (fabs(Li-LiEst) > LiThreshold && 
							 fabs(Li-LiEst) > fabs(2.0 * res)) || LiEst==999999. ) {
							if ( epoch->cycleslip.outlierLI[i] == 1 || LiEst==999999.) {
								// Cycle slip confirmed
								LiCheck = 1;
								if(LiEst==999999.) {
									LiDiff=999999.;
								} else {
									LiDiff = Li-LiEst;
								}
							} else {
								// Outlier
								epoch->cycleslip.outlierLI[i] = 1;
							}
						} else if ( epoch->cycleslip.outlierLI[i] == 1 ) {
							epoch->cycleslip.outlierLI[i] = 0;
							epoch->cycleslip.use4smooth[i] = 1;
							epoch->sat[ii].available = 1;
						}
					}
				}
				//When any of the detectors detects an outlier, the arclength only has to be decreased once
				if (epoch->cycleslip.outlierBw[i]==1) {
					if (BwCheck==0) {
						//Bw has detected an outlier
						//If BwCheck==1 then there is a cycle-slip
						epoch->cycleslip.use4smooth[i] = 0;
						epoch->cycleslip.arcLength[i]--;
					}
				} else if (epoch->cycleslip.outlierLI[i]==1) {
					if (LiCheck==0) {
						//LI has detected an outlier
						//If LiCheck==1 then there is a cycle-slip
						epoch->cycleslip.use4smooth[i] = 0;
						epoch->cycleslip.arcLength[i]--;
					}
				}
			}

			if ( measCheck && (DataGapCheck || LLICheck || LiCheck || BwCheck || L1C1Check) ) {
				// Cycle slip detected so reset all satellite's associated variables
				initSatellite(epoch,ii,i);
				prealignSat(epoch,ii);
				epoch->cycleslip.CSPrealignFlag[i] = 0;
				printCS(epoch,ii,LiCheck,fabs(LiDiff),LiThreshold,BwCheck,fabs(nBwdiff),nBwdiffThreshold,L1C1Check,fabs(L1C1diff),L1C1Threshold,options,DataGapCheck,options->csDataGap,timeDiff,LLICheck,mode);
				epoch->cycleslip.LiPrev[i][0] = Li;
				epoch->cycleslip.BwPrev[i][0] = Bw;
				memcpy(&epoch->cycleslip.tPrevLI[i][0],&epoch->t,sizeof(TTime));
				memcpy(&epoch->cycleslip.tPrevBw[i][0],&epoch->t,sizeof(TTime));
				epoch->cycleslip.BWmean[i] = Bw;
				epoch->cycleslip.BWsigma[i] = options->csBWInitStd*options->csBWInitStd;
				epoch->cycleslip.use4smooth[i] = 0;
				epoch->cycleslip.consistency[i]= 0;
				cycleSlipFound = 1;
				// This is done to store both C1 and L1 for the next epoch, after the pre-alignment, in case of cycle slip
				if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
					epoch->cycleslip.C1Prev[i] = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1C);
				} else {
					epoch->cycleslip.C1Prev[i] = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,C1P);
				}
				epoch->cycleslip.L1Prev[i] = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,L1P);

			}

			// Update the L1C1 parameters
			if ( options->csL1C1 && measL1C1 && epoch->cycleslip.Nconsecutive[i] == 0 && epoch->cycleslip.outlierLI[i] != 1 && epoch->cycleslip.outlierBw[i] != 1 ) {
				// Update sliding window
				for ( j=0;j<MAX_SLIDING_WINDOW-1;j++ ) {
					epoch->cycleslip.windowL1C1[i][j] = epoch->cycleslip.windowL1C1[i][j+1];
					epoch->cycleslip.windowL1C1time[i][j] = epoch->cycleslip.windowL1C1time[i][j+1];
				}
				epoch->cycleslip.windowL1C1[i][MAX_SLIDING_WINDOW-1] = L1-C1;
				epoch->cycleslip.windowL1C1time[i][MAX_SLIDING_WINDOW-1] = tsec(&epoch->t);

				// Computing the number of samples in inside the sliding window
				samples = 0;
				for ( j=0;j<MAX_SLIDING_WINDOW;j++ ) {
					if ( tsec(&epoch->t)-epoch->cycleslip.windowL1C1time[i][j] < options->csL1C1window ) {
						samples++;
					}
				}

				// Computing the mean and quadratic mean in the sliding window
				auxMean = 0.0;
				auxMean2 = 0.0;
				for ( j=MAX_SLIDING_WINDOW-1;j>MAX_SLIDING_WINDOW-samples-1;j-- ) {
					auxMean += epoch->cycleslip.windowL1C1[i][j];
					auxMean2 += pow(epoch->cycleslip.windowL1C1[i][j],2);
				}
				if ( samples > 0 ) {
					epoch->cycleslip.L1C1mean[i] = auxMean / ((double)samples);
					sigma2 = (auxMean2 / ((double)samples)) - pow(epoch->cycleslip.L1C1mean[i],2);
					epoch->cycleslip.L1C1sigma[i] = sigma2 - (sigma2-pow(options->csL1C1init,2))/((double)samples);
				}
				if ( cycleSlipFound || samples == 0 ) {
					epoch->cycleslip.L1C1mean[i] = L1-C1;
					epoch->cycleslip.L1C1sigma[i] = pow(options->csL1C1init,2);
				}
			}

			// Update arithmetic mean and standard deviation for Melbourne-Wubbena
			if ( options->csBW && epoch->cycleslip.Nconsecutive[i] == 0 && measBW && epoch->cycleslip.outlierLI[i] != 1 && epoch->cycleslip.outlierBw[i] != 1 ) {
				if ( epoch->cycleslip.arcLength[i] > 1 ) {
					epoch->cycleslip.BWsigma[i] += (pow(Bw-epoch->cycleslip.BWmean[i],2) - epoch->cycleslip.BWsigma[i]) / epoch->cycleslip.arcLength[i];
					epoch->cycleslip.BWmean[i] += (Bw-epoch->cycleslip.BWmean[i]) / epoch->cycleslip.arcLength[i];
				} else if ( epoch->cycleslip.narc[i] == 0 ) {
					//This is for the first epoch in the first arc, where the mean has to be updated to the current value of Bw
					epoch->cycleslip.BWmean[i] = Bw;
				}

				// Update sliding window
				for ( j=0;j<MAX_SLIDING_WINDOW-1;j++ ) {
					epoch->cycleslip.windowMW[i][j] = epoch->cycleslip.windowMW[i][j+1];
					epoch->cycleslip.windowMWtime[i][j] = epoch->cycleslip.windowMWtime[i][j+1];
				}
				epoch->cycleslip.windowMW[i][MAX_SLIDING_WINDOW-1] = Bw;
				epoch->cycleslip.windowMWtime[i][MAX_SLIDING_WINDOW-1] = tsec(&epoch->t);

				// Computing the number of samples in inside the sliding window
				samples = 0;
				for ( j=0;j<MAX_SLIDING_WINDOW;j++ ) {
					if ( tsec(&epoch->t)-epoch->cycleslip.windowMWtime[i][j] < options->csBWwindow ) {
						samples++;
					}
				}

				// Computing the mean value for the sliding window
				auxMean = 0.0;
				for ( j=MAX_SLIDING_WINDOW-1;j>MAX_SLIDING_WINDOW-samples-1;j-- ) {
					auxMean += epoch->cycleslip.windowMW[i][j];
				}
				if ( samples > 0 )
					epoch->cycleslip.BWmean300[i] = auxMean / ((double)samples);
				if ( cycleSlipFound || samples == 0 )
					epoch->cycleslip.BWmean300[i] = Bw;
			}

			// Update previous LI for Geometry-free
			if ( options->csLI && epoch->cycleslip.Nconsecutive[i] == 0 && measLI ) {
				epoch->cycleslip.initialLi[i] = Li;
				// This is done to store the LI for the next epoch, after the pre-alignment, in case of cycle slip
				if ( cycleSlipFound ) epoch->cycleslip.initialLi[i] = getMeasurementValue(epoch,system,epoch->sat[ii].PRN,LI);
			}
		} else { // System unsupported
			epoch->cycleslip.arcLength[i]++;
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
	int			i, j, k;
	int			smoothN;
	double		smoothWith;
	double		measurement;
	TSatellite	*sat;
	
	for ( i = 0; i < options->totalFilterMeasurements; i++ ) {
		if ( options->smoothEpochs != 0 && options->smoothMeas[i] != NA ) {
			for ( j = 0; j < epoch->numSatellites; j++ ) {
				k = epoch->satCSIndex[epoch->sat[j].GNSS][epoch->sat[j].PRN];
				sat = &epoch->sat[j];
				getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->smoothMeas[i], &smoothWith, NULL);
				getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->measurement[i], &measurement, NULL);
				if ( epoch->cycleslip.use4smooth[k] == 1 && epoch->cycleslip.arcLength[k] > options->minArcLength ) {
					smoothN = epoch->cycleslip.arcLength[k] - options->minArcLength;
					if ( smoothN > options->smoothEpochs ) {
						smoothN = options->smoothEpochs;
					}
					// Sanity check
					if ( smoothN == 0 ) smoothN = 1;
					
					epoch->cycleslip.smoothedMeas[k][i] = (((double)(smoothN-1)) * epoch->cycleslip.smoothedMeas[k][i] + (measurement-smoothWith)) / ((double)(smoothN));
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
				fsigN = 1.0 / ( (double)( epoch->cycleslip.arcLength[i] ) );
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
