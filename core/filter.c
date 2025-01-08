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
 * File: filter.c
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2024/11/22
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
 * Release: 2010/03/23
 * Change Log: PREFIT message now prints the weight to be applied in the filter
 *             FILTER message now prints the total ZTD and the estimated ZTD (substracting the modeled value)
 *             PREFIT message now prints non-GPS satellites
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: Included usable measurement index to select/deselect individual measurements
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
 * Change Log: Filter adjustments to new DCB management.
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
 * Change Log: Modified fillUsableSatellites function in order to discard satellites without IONEX or F-PPP model data
 *			(in case those models are used).
 * -----------
 *          gLAB v2.2.1
 * Release: 2014/12/23
 * Change Log: Fixed initialization to given value per parameter of covariance of coordinates Y and Z (before only coordinate X was initialized, Y and Z were 0)
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
 *	       Added Stanford-ESA computation.
 *	       Modified structure definitions for handling Cycle Slip variables.
 *	       Modified printSatSel calls.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: Modified Kalman function to allow model recomputation in NPA mode
 *               if after calling fillUsableSatellites and we were in PA mode, there 
 *               were not enough satellites for computing navigation solution (only in SBAS).
 *             Eliminated "preauxEpoch" struct from Kalman function, improving performance
 *               (specially when computing trajectories).
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: 'Elevation too low' SATSEL message is not shown if ephemerides are not available.
 *             Added quantization check in Stanford-ESA plots generation for points greater than the
 *                maximum X and Y. For example, (60,100) and (100,60) with a max X and Y of 50, 
 *                would both result in the plot in the point (50,50) or (Xmax,Ymax), which made
 *                it impossible to distinguish the MI from the non-MI. Now, MI points will result
 *                in (Xmax,Ymax) while non MI will result in (Xmax-1,Ymax)
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added DGNSS checks within function fillUsableSatellites.
 *             Added an INFO message when a solution could not be computed due to lack of available satellites.
 *             Added an INFO message when a solution could not be computed due to geometry matrix is singular.
 *             Added an INFO message when a solution could not be computed due to GDOP is over the threshold.
 *             Compution of DOP is now done before entering the computeSolution function, and checks if geometry
 *               matrix is singular. This allows to skip the epoch due to singular matrix or bad GDOP without
 *               affecting the filter.
 *             Fixed a bug which made the filter reset some of the satellite carrier ambiguitys at each epoch
 *                This ocurred when the observation file was multiconstellation and affected only the GPS satellites
 *                that were at the end of the list of satellites available.
 *             INFO message in StdESA of a singular matrix now prints epoch and the list of satellites.
 *             INFO message in step detector now prints current epoch and threshold.
 *             Stanford-ESA computation now writes to files all combinations that produce an integrity ratio higher than a threshold.
 *             Stanford-ESA computation can be done now outside of SBAS mode.
 *             Added a quantization check to avoid the generation of false MIs in Stanford-ESA output file. This ocurred due to the
 *               process of quantizing (for saving the data in memory) and de-quantizing (for writing data in output file). This
 *               tipically ocurred when protection level and error values had very similar values.
 *             Fixed a bug when checking if SBAS mode or GEO switch should be tried in Kalman function that provoked an infinite loop
 *               of tries to change mode or GEO.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Added functions PrefitOutlierDetectorMedian and PrefitOutlierDetectorAbsolute for prefit outlier detection.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log: Changed SATSEL message from 'Steady-state operation not reached. X epochs passed, still Y epochs to go'
 *               to 'Steady-state operation not reached. X epochs passed, still Y epochs to achieve X+Y'.
 *             Added SATSEL message 'Satellite phase center corrections unavailable'.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Changed "Outlier" SATSEL message to "Outlier in Bw detector" and "Outlier in LI detector" in order to
 *                 show which cycle-slip detector detected an outlier.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Fixed bug not computing Stanford-ESA when SBAS summary was not enabled.
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
 * Change Log:   Added discard reason "URA value (<value>) is equal or greater than the threshold (<threshold>)" in SATSEL message.
 *               Added functions 'DGNSSSummaryDataUpdate' and 'SummaryDataUpdate' for computing summary statistics in SPP,
 *                 PPP and DGNSS modes.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log:   Fixed a bug when quantizing Stanford-ESA values due to an unsigned integer overflow when very large
 *                 values of error or protection level occurred. This made that in the Stanford-ESA output plot file
 *                 MIs with very large error did not appear.
 *               Fixed incorrect INFO message generated when DOP threshold was exceeded and gLAB tried to do a GEO
 *                 or mode switch. gLAB wrote in the info message "Trying to switch GEO or to NPA mode" even if
 *                 one of the options (GEO switching or mode switching) was not enabled, instead of writing just
 *                 "Trying to switch GEO" or "Trying to switch to NPA mode". Nevertheless, the bug affected only
 *                 when writing the INFO message, not at processing level.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log:   In SBAS availability maps, the epochs to be taken into account for computation
 *                 for the HDOP, PDOP or GDOP mean or percentile computation must be the epochs
 *                 that are under the protection levels. Before, any epoch whose DOP could be
 *                 computed was taken into account for the mean and percentile. This made that
 *                 epochs with very large DOP (e.g more than one million) would totally bias
 *                 the mean DOP value.
 *               Initialization of epoch values for computing the continuity risk is now done
 *                 in the gLAB.c instead. This is faster, as the initialization is checked only
 *                 once, while before it was checked every time there was a PA solution. This
 *                 applies for SBAS navigation and SBAS availability maps modes.
 *               In SBAS or DGNSS modes, if geometry matrix is singular, it will try to change GEO
 *                 or mode in SBAS or to SPP mode in DGNSS instead of directly skipping the solution.
 *               If option to select best GEO is enabled, for each iteration where there is an
 *                 available solution, it will save the modelled data and protection levels, and keep
 *                 looping through all GEOs. Then, from the GEOs with solution, it will selected the
 *                 one with smallest protection levels.
 *               Fixed initialization of values for computing the continuity risk. Before the initial
 *                 value for the last epoch with PA solution was the first epoch with PA solution,
 *                 while now it is one epoch before the first epoch processed. This applies for SBAS 
 *                 navigation and SBAS availability maps modes.
 *               Fixed discontinuities that started in the first epoch processed were not detected. It
 *                 only affected the maritime continuity risk computation, as there was a discontinuity
 *                 not taken into account. It didn't affect the aviation continuity risk computation,
 *                 as there were no PA epochs before that discontinuity. This applies for SBAS
 *                 navigation and SBAS availability maps modes. The error was due to the initialization
 *                 of values for computing the continuity risk.
 *               Fixed computation of stable period in the first discontinuity computed (only occurred
 *                 if the first processed epoch had a PA solution). Before, the size of the stable
 *                 period prior to the discontinuity would be one epoch smaller than the real value.
 *                 This would affect the aviation continuity risk computation only if the length of
 *                 the stable period was smaller than the window size, thus affecting one epoch less
 *                 (due to that when the stable period is smaller than the window size, the number
 *                 of affected epochs is the lenght of the stable period). This applies for SBAS
 *                 navigation and SBAS availability maps modes. The error was due to the initialization
 *                 of values for computing the continuity risk.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log:   SATSEL message "SBAS corrections unavailable" now also print the GEO PRN.
 *               INFO messages for SBAS stating that a GEO change or mode change or that
 *                 an epoch is going to be skipped now prints the GEO PRN used.
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
 * Change Log:   The SATSEL message "SBAS iono unavailable" will now show the GEO PRN used.
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
 *               Added SATSEL messages regarding SNR, cycle-slips, N-consecutive and arc-length
 *                 for the reference station in DGNSS mode using RTCM3 or RINEX observation file.
 *               Added SATSEL message for satellites missing in the reference station in DGNSS mode
 *                 using RTCM3 or RINEX observation file.
 *               Added SATSEL message for epochs in rover that cannot be aligned with the reference
 *                 station, that is, epochs missing in the reference station in DGNSS mode using
 *                 RTCM3 or RINEX observation file.
 *               Added SATSEL message for not being able to apply weighted elevation due to
 *                 elevation is too low.
 *               Added SATSEL message for missing SNR measurement when used for weight computation. 
 *               Added SATSEL message for outlier in IGF detector.
 *               Added SATSEL message for missing frequency numbers for GLONASS.
 *               Added SATSEL messages for measurement selection not completed, measurements
 *                 missing (the latter provided the list of measurements missing) or no
 *                 measurements selected for current satellite.
 *               "SNR not met" SATSEL message now provided the full list of SNR measurements
 *                 not complying the SNR requirements (along with the SNR value and threshold).
 *               SATSEL messages are enumerated (a field is added with the message number), and
 *                 the discard reason is between quotes.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "dataHandling.h"
#include "filter.h"

/**************************************
 * Declarations of internal operations
 **************************************/

/*****************************************************************************
 * Name        : m2v
 * Description : Transforms the indices from matrix to vector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  i                          I  N/A  Matrix row
 * int  j                          I  N/A  Matrix column
 * Returned value (int)            O  N/A  Vector index
 *****************************************************************************/
int m2v (int i, int j) {
  return i>j ? i*(i+1)/2+j : j*(j+1)/2+i;
}

/*****************************************************************************
 * Name        : m2v_opt
 * Description : Optimized version of m2v (much faster). It suposes i>=j.
 *               It is specially useful when inverting matrixes.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  i                          I  N/A  Matrix row
 * int  j                          I  N/A  Matrix column
 * Returned value (int)            O  N/A  Vector index
 *****************************************************************************/
static inline int m2v_opt (int i, int j) {
  return i*(i+1)/2+j;
}

/*****************************************************************************
 * Name        : m2v_opt_inv
 * Description : Optimized version of m2v (much faster). It suposes i<=j.
 *               It is specially useful filling the matrixes.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  i                          I  N/A  Matrix row
 * int  j                          I  N/A  Matrix column
 * Returned value (int)            O  N/A  Vector index
 *****************************************************************************/
static inline int m2v_opt_inv (int i, int j) {
  return j*(j+1)/2+i;
}

/*****************************************************************************
 * Name        : cholinv
 * Description : Cholesky matrix inversion
 *               Version inspired from "Numerical Recipes in C" P.97-98
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *mat                    IO N/A  Matrix in vector form (overwritten)
 * int  n                          I  N/A  Matrix size
 * Returned value (int)            O  N/A  Status of the function
 *                                         0  => Cholesky worked properly
 *                                         -1 => Cholesky inversion failed (singular
 *                                               matrix)
 *****************************************************************************/
int cholinv (double *mat, int n) {
  int i,j,k;
  double sum;

  for (i=0;i<n;i++) {
	for (j=i;j<n;j++) {
	  for (sum=mat[m2v(i,j)],k=i-1;k>=0;k--) {sum -= mat[m2v(i,k)]*mat[m2v(j,k)]; } 
	  if (i==j) {
		if (sum <= 0) return -1;  // Cholesky decomposition failed
		mat[m2v(i,i)]=sqrt(sum);
	  } else mat[m2v(j,i)]=sum/mat[m2v(i,i)];
	}
  }

// Beginning Upper Inversion

  for (i=0;i<n;i++) {
	mat[m2v(i,i)]=1/mat[m2v(i,i)];
	for (j=i+1;j<n;j++) {
	  sum=0;
	  for (k=i;k<j;k++) sum -= mat[m2v(j,k)]*mat[m2v(k,i)];
	  mat[m2v(j,i)]=sum/mat[m2v(j,j)];
	}
  }

// Multiplying U^-1 * UT^-1

  for (i=0;i<n;i++) {
	for (j=i;j<n;j++) {
	  sum=0;
	  for (k=j;k<n;k++) sum += mat[m2v(i,k)]*mat[m2v(k,j)];
	  mat[m2v(i,j)]=sum;
	}
  }

  return 0;
}

/*****************************************************************************
 * Name        : cholinv_opt
 * Description : Optimized version of cholinv. It uses m2v_opt
 *               Version inspired from "Numerical Recipes in C" P.97-98
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *mat                    IO N/A  Matrix in vector form (overwritten)
 * const int  n                    I  N/A  Matrix size
 * Returned value (int)            O  N/A  Status of the function
 *                                          0 => Cholesky worked properly
 *                                         -1 => Cholesky inversion failed (singular
 *                                               matrix)
 *****************************************************************************/
int cholinv_opt (double *mat, const int n) {
	int					matrixsizebytes;
 	double 				sum,auxval;
 	static double 		aux[MAX_VECTOR_UNK]; //Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	#pragma omp threadprivate(aux)
 
 	// Reserving space 
	matrixsizebytes=(m2v_opt(n-1,n-1)+1)*sizeof(double);
	memset(aux,0,matrixsizebytes);

 	for (register int i=0;i<n;i++) {
		for (register int j=i;j<n;j++) {
			sum=mat[m2v_opt(j,i)];
	  		for (register int k=i-1;k>=0;k--) sum -= mat[m2v_opt(i,k)]*mat[m2v_opt(j,k)];
	  		if (i==j) {
				if (sum <= 0) {
					return -1;  // Cholesky decomposition failed
				}
				mat[m2v_opt(i,i)]=sqrt(sum);
	  		} else mat[m2v_opt(j,i)]=sum/mat[m2v_opt(i,i)];
		}
	}	

	// Upper Inversion and multiplication of U^-1 * UT^-1

	for (register int i=0;i<n;i++) {
		mat[m2v_opt(i,i)]=1/mat[m2v_opt(i,i)];
		auxval=mat[m2v_opt(i,i)];
		for (register int k=0;k<=i;k++) aux[m2v_opt(i,k)]+=auxval*mat[m2v_opt(i,k)];
		for (register int j=i+1;j<n;j++) {
	  		sum=0;
	  		for (register int k=i;k<j;k++) sum -= mat[m2v_opt(j,k)]*mat[m2v_opt(k,i)];
	  		mat[m2v_opt(j,i)]=sum/mat[m2v_opt(j,j)];
			auxval=mat[m2v_opt(j,i)];
	  		for (register int k=0;k<=i;k++) aux[m2v_opt(i,k)]+=auxval*mat[m2v_opt(j,k)];
		}
	}	

  	memcpy(mat,aux,matrixsizebytes);

  	return 0;
}

/*****************************************************************************
 * Name        : mxv
 * Description : Multiplies a matrix in vectorial form and a vector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *restrict mat           I  N/A  Matrix in vector form
 * double  *restrict vec           IO N/A  Vector (overwritten)
 * const int  n                    I  N/A  Matrix and vector size
 *****************************************************************************/
void mxv (double *restrict mat, double *restrict vec, const int n) {
	int				i,j;
	static double	aux[MAX_VECTOR_UNK]; //Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	#pragma omp threadprivate(aux)

	for (i=0;i<n;i++) {
		aux[i]=0;
		for (j=0;j<i;j++) {
			aux[i] += mat[m2v_opt(i,j)] * vec[j];
		}
		for (;j<n;j++) {
			aux[i] += mat[m2v_opt_inv(i,j)] * vec[j];
		}
	}
  	memcpy(vec,aux,n*sizeof(double));
}

/*****************************************************************************
 * Name        : StepDetector
 * Description : Check for jumps greater than 700 meters. The step detector
 *               is useful for detecting jumps in navigation message. 
 *               The threshold for comparing is 73.8 meters (see MOPS-C, 
 *                Appendix I, page I-3). To be used only with C1C code.
 *               The step detector computes the difference of prefits between 
 *               the current and previous epoch (only with satellites that have been 
 *               used in the navigation solution in both epochs) with reference satellites
 *               (the two ones with highest elevation in current epoch). Then computes
 *               the difference between prefit difference with both satellites. If
 *               both differences are over the threshold, then there has been a step.
 *               With this method a big step will not affect other satellites, but it has
 *               the drawback that it assumes that only one satellite will fail or that
 *               more than one satellite may fail but not the reference ones.
 *               The problem with any step detector is that it will only trigger when there
 *               is a jump when changing the ephemerides to ones which have incorrect values, 
 *               but in the next epochs where previous and current epochs use the same bad
 *               ephemerides, the step detector will not trigger.
 *
 *               For multiconstellation, all C1C measurements of all constellations are
 *               added toguether, as are we are looking for very big jumps, the inter-system
 *               clock bias will not be a problem
 *
 *               Note that the step detector looks for steps using all constellation at once,
 *                therefore it might occur the case that the reference constellation used has
 *                one or two satellites and these satellites are removed. In this case, we will
 *                need to change the reference constellation used
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A   0 => All OK
 *                                         -1 => No satellites with reference clock and
 *                                                changing satellite clock is disabled (only
 *                                                for the case when the reference constellation
 *                                                has been removed
 *****************************************************************************/
int StepDetector (TEpoch *epoch, TOptions *options) {

	int							i,j,k,l;
	int							ret;
	int							numsats=0;
	int							maxelevationpos=-1,secondmaxelevationpos=-1,thirdmaxelevationpos=-1;
	int							SatUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int							removedReferenceCLockGNSS=0;
	int							TotalSatRemoved=0;
	static int					PrevSatUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//Static variables default initialized to 0

	const double				Threshold=73.8;
	double						measurement,smoothWith,model;
	double						diff1,diff2,Rescurrfirst,Resprevfirst,Rescurrsecond,Resprevsecond;
	double						Prefits[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	static double				PrevPrefits[MAX_GNSS][MAX_SATELLITES_PER_GNSS]; //Static variables default initialized to 0
	enum GNSSystem				lastGNSSselected;
	TSatellite					*sat;

	const enum MeasurementType	C1Cmeas=C1C;
	const int					C1Cfreq=1;

	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;
	
	//Initialize SatUsed
	for(i=0;i<MAX_GNSS;i++) {
		for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			SatUsed[i][j]=0;
			Prefits[i][j]=0;
		}
	}

	//Retrieve all the prefits available
	for(i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		if(sat->available==0) {
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}
		l=options->C1CfilterMeasPos[ROVERPOS][sat->GNSS][sat->PRN];
		if (l==-1) {
			//C1C measurement not available
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}
		ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,&C1Cmeas,&C1Cfreq,&measurement,&model,l);
		if (ret!=1) {
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}
		// Smoothing
		if (options->smoothEpochs!=0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][l] == 1) {
			ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][l],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][l],&smoothWith,NULL,0);
			if (ret!=1) {
				SatUsed[sat->GNSS][sat->PRN]=0;
				continue;
			}
			k = epoch->satCSIndex[sat->GNSS][sat->PRN];
			Prefits[sat->GNSS][sat->PRN] = epoch->cycleslip.smoothedMeas[k][0] + smoothWith - model;
		} else {
			Prefits[sat->GNSS][sat->PRN] = measurement - model;
		}

		if(PrevSatUsed[sat->GNSS][sat->PRN]==1) {
			numsats++;
			//Look for the three satellites with higher elevation
			if(maxelevationpos==-1) {
				maxelevationpos=i;
			} else if (secondmaxelevationpos==-1) {
				secondmaxelevationpos=i;
			} else if (thirdmaxelevationpos==-1) {
				thirdmaxelevationpos=i;
			} else {
				if(sat->elevation>epoch->sat[maxelevationpos].elevation) {
					maxelevationpos=i;
				} else if (sat->elevation>epoch->sat[secondmaxelevationpos].elevation) {
					secondmaxelevationpos=i;
				} else if (sat->elevation>epoch->sat[thirdmaxelevationpos].elevation) {
					thirdmaxelevationpos=i;
				}
			}
		}
		SatUsed[sat->GNSS][sat->PRN]=1;
	}

	if(numsats>=3) {
		for(i=0;i<epoch->numSatellites;i++) {
			sat = &epoch->sat[i];
			if(SatUsed[sat->GNSS][sat->PRN]==0) continue;
			if(PrevSatUsed[sat->GNSS][sat->PRN]==0) continue;
			if(i==maxelevationpos) {
				//Current satellite is the one with highest elevation.
				//We have to compare with satellites with second and third highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Resprevfirst=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Rescurrsecond=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
			} else if (i==secondmaxelevationpos) {
				//Current satellite is the one with second highest elevation.
				//We have to compare with satellites with first and third highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Resprevfirst=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Rescurrsecond=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
			} else {
				//We have to compare with satellites with first and second highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Resprevfirst=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Rescurrsecond=Prefits[sat->GNSS][sat->PRN]-Prefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[sat->GNSS][sat->PRN]-PrevPrefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
			}

			//Compute the difference between prefit differences
			diff1=fabs(Rescurrfirst-Resprevfirst);
			diff2=fabs(Rescurrsecond-Resprevsecond);

			//Check that differences do not exceed the threshold
			if(diff1>Threshold && diff2>Threshold) {
				linesstoredSATSEL[sat->GNSS][i]=0;
				sprintf(messagestr,"STEP detected (jump of %7.3f greater than %7.3f)",max(diff1,diff2),Threshold);
				printSatSel(epoch,0,80,messagestr,i,options);
				sat->available=0;
				epoch->usableSatellites--;
				if (epoch->usableSatellitesGNSS[sat->GNSS]==1) {
					//Last satellite of a constellation. Add 1 to the number of constellations unselected
					epoch->constellationUsed[sat->GNSS]=0;
					epoch->constellationNotUsed[sat->GNSS]=1;
					epoch->constellationNotUsedList[epoch->numConstellationsNotUsed]=sat->GNSS;
					epoch->numConstellationsNotUsed++;
					//Rebuild used constellation list
					for(j=0;j<epoch->numConstellationsUsed;j++) {
						if (epoch->constellationUsedList[j]==sat->GNSS) {
							break;
						}
					}
					epoch->numConstellationsUsed--;
					for(;j<epoch->numConstellationsUsed;j++) {
						epoch->constellationUsedList[j]=epoch->constellationUsedList[j+1];
					}
					if (sat->GNSS==epoch->ReferenceGNSSClock) {
						//Constellation used as reference clock removed. Set flag to change reference clock
						removedReferenceCLockGNSS=1;
					}
				}
				epoch->usableSatellitesGNSS[sat->GNSS]--;
				epoch->discardedSatellites++;
				epoch->discardedSatellitesGNSS[sat->GNSS]++;
				epoch->totalNumAmbiguitiesEpoch-=options->numfilterCarrierPhaseMeas[ROVERPOS][sat->GNSS][sat->PRN];
				TotalSatRemoved++;
			} else {
				lastGNSSselected=sat->GNSS;
			}
		}
	}

	if (removedReferenceCLockGNSS==1) {
		ret=changeReferenceConstellationFilter(lastGNSSselected,epoch,options);
	} else {
		ret=0;
	}

	memcpy(PrevSatUsed,SatUsed,sizeof(SatUsed));
	memcpy(PrevPrefits,Prefits,sizeof(Prefits));

	//Rebuild epoch->usedSat2DataPos array, as positions will have moved due to the removed satellites
	if (TotalSatRemoved>0) {
		j=0;
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==1) {
				epoch->usedSat2DataPos[j]=i;
				j++;
			}
		}
	}

	return ret;


/*
 * ALTERNATIVE METHOD FOR STEP DETECTOR: 
 * Description : Check for jumps greater than 700 meters. The step detector
 *               is useful for detecting jumps in navigation message. 
 *               The threshold for comparing is 73.8 meters (see MOPS-C, 
 *                Appendix I, page I-3).
 *               The step detector compares the value of the current and previous epoch
 *               (only with satellites that have been used in the navigation solution in both epochs)
 *               of the prefit minus the receiver clock, which is estimated from the mean 
 *               of all prefits. This mean has to be computed using only satellites available
 *               in the current and previous epoch. The problem with this approach is that as the
 *               receiver clock is computed with the mean of the prefits, if a satellite has a very
 *               high jump, a jump will be detected in all satellites 

	int 						i,j,k,l;
	int							ret;
	int							numsats=0;
	int							removedReferenceCLockGNSS=0;
	int							TotalSatRemoved=0;
	int							SatUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	static int					PrevSatUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS];

	double						Threshold=73.8;
	double						dtCurrent=0,dtPrev=0;
	double						measurement,smoothWith,model;
	double						diff,Rescurr,Resprev;
	double						Prefits[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	static double				PrevPrefits[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	const enum MeasurementType	C1Cmeas=C1C;
	const int					C1Cfreq=1;
	enum GNSSystem				lastGNSSselected;
	TSatellite					*sat;

	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;

	//Initialize SatUsed
	for(i=0;i<MAX_GNSS;i++) {
		for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			SatUsed[i][j]=0;
			Prefits[i][j]=0;
		}
	}

	//Retrieve all the prefits available
	for(i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		if(sat->available==0) {
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}
		l=options->C1CfilterMeasPos[ROVERPOS][sat->GNSS][sat->PRN];
		if (l==-1) {
			//C1C measurement not available
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}
		ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,&C1Cmeas,&C1Cfreq,&measurement,&model,l);
		if (ret!=1) {
			SatUsed[sat->GNSS][sat->PRN]=0;
			continue;
		}

		// Smoothing
		if (options->smoothEpochs!=0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][l] == 1) {
			ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][l],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][l],&smoothWith,NULL,0);
			if (ret!=1) {
				return;
			}
			k = epoch->satCSIndex[sat->GNSS][sat->PRN];
			Prefits[sat->GNSS][sat->PRN] = epoch->cycleslip.smoothedMeas[k][0] + smoothWith - model;
		} else {
			Prefits[sat->GNSS][sat->PRN] = measurement - model;
		}

		if(PrevSatUsed[sat->GNSS][sat->PRN]==1) {
			dtCurrent+=Prefits[sat->GNSS][sat->PRN];
			dtPrev+=PrevPrefits[sat->GNSS][sat->PRN];
			numsats++;
		}
		SatUsed[sat->GNSS][sat->PRN]=1;
	}

	if(numsats>=3) {
		dtCurrent/=numsats;
		dtPrev/=numsats;
		//Compute for each satellite the prefit minus the receiver clock estimate and compare it with previous one (if available)
		for(i=0;i<epoch->numSatellites;i++) {
			sat = &epoch->sat[i];
			if(SatUsed[sat->GNSS][sat->PRN]==0) continue;
			//Substract the receiver clock estimate from the prefits
			if(PrevSatUsed[sat->GNSS][sat->PRN]==1) {
				Rescurr=Prefits[sat->GNSS][sat->PRN]-dtCurrent;
				Resprev=PrevPrefits[sat->GNSS][sat->PRN]-dtPrev;
				diff=fabs(Rescurr-Resprev);
				if(diff>Threshold) {
					linesstoredSATSEL[sat->GNSS][i]=0;
					sprintf(messagestr,"STEP detected (jump of %7.3f)",diff);
					printSatSel(epoch,0,80,messagestr,i,options);
					sat->available=0;
					epoch->usableSatellites--;
					if (epoch->usableSatellitesGNSS[sat->GNSS]==1) {
						//Last satellite of a constellation. Add 1 to the number of constellations unselected
						epoch->constellationUsed[sat->GNSS]=0;
						epoch->constellationNotUsed[sat->GNSS]=1;
						epoch->constellationNotUsedList[epoch->numConstellationsNotUsed]=sat->GNSS;
						epoch->numConstellationsNotUsed++;
						//Rebuild used constellation list
						for(j=0;j<epoch->numConstellationsUsed;j++) {
							if (epoch->constellationUsedList[j]==sat->GNSS) {
								break;
							}
						}
						epoch->numConstellationsUsed--;
						for(;j<epoch->numConstellationsUsed;j++) {
							epoch->constellationUsedList[j]=epoch->constellationUsedList[j+1];
						}
						if (sat->GNSS==epoch->ReferenceGNSSClock) {
							//Constellation used as reference clock removed. Set flag to change reference clock
							removedReferenceCLockGNSS=1;
						}
					}
					epoch->usableSatellitesGNSS[sat->GNSS]--;
					epoch->discardedSatellites++;
					epoch->discardedSatellitesGNSS[sat->GNSS]++;
					epoch->totalNumAmbiguitiesEpoch-=options->numfilterCarrierPhaseMeas[ROVERPOS][sat->GNSS][sat->PRN];
					TotalSatRemoved++;
				} else {
					lastGNSSselected=sat->GNSS;
				}
			}
		}
	} else {
		//Step detector not available
	}

	if (removedReferenceCLockGNSS==1) {
		ret=changeReferenceConstellationFilter(lastGNSSselected,epoch,options);
	} else {
		ret=0;
	}

	memcpy(PrevSatUsed,SatUsed,sizeof(SatUsed));
	memcpy(PrevPrefits,Prefits,sizeof(Prefits));

	//Rebuild epoch->usedSat2DataPos array, as positions will have moved due to the removed satellites
	if (TotalSatRemoved>0) {
		j=0;
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==1) {
				epoch->usedSat2DataPos[j]=i;
				j++;
			}
		}
	}

	return ret;
*/
}


/*****************************************************************************
 * Name        : PrefitOutlierDetectorAbsolute
 * Description : Check for outliers in the prefits. A prefit outlier is defined 
 *               as a value being too high compared to the other values.
 *               A arbitrary threshold (parametrizable). If it is too high, only
 *                very big outliers will be detected. If it is too low, there will
 *                be fault detections. In nominal conditions, a possible threshold is 30 metres.
 *               It is only applied to code measurements, as 
 *                 carrier phase measurements may differ a lot due to
 *                 ambiguities (except for the case that ambiguities are not computed,
 *                 which makes consider carrier phases as absolute measurements).
 *               It is also necessary to group the prefits by constellation and measurement
 *                 type (C1C,C5X, PC12, ...), as there is the inter-system clock bias and
 *                 the different DCBs for each measurement which could produce false
 *                 detection if all prefits was mixed toguether.
 *
 *               The detector works this way:
 *
 *               Group prefits by constellation and measurement type
 *               
 *               for each constellation:
 *                 for each mesurement type in the filter:
 *                   for each satellite available with this measurement type:
 *                     Select one satellite as reference and
 *                       compute the absolute value of its prefit.
 *                     Set a range for all other valid prefits as: 
 *                       Range=[abs(prefitR)-threshold,abs(prefitR)+threshold]
 *                     For each satellite (except the reference one):
 *                       Check if prefits are inside the range
 *
 *                   If half or more of the satellites are unvalid, then the current satellite is an outlier
 *                   Else discard the selected satellite.
 *
 *               Note that the outlier detector needs more than one satellite with the same constellation
 *                and type of measurement, therefore when discarding a satellite it will not remove the
 *                last satellite of a constellation. This is important for the filter, as if a constellation
 *                would be removed, we would need to remove its inter-system clock bias from the filter
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void PrefitOutlierDetectorAbsolute (TEpoch *epoch, TOptions *options) {

	int 					i,j,k,l,m;
	int						satIndex;
	int						ret;
	int						TotalSatRemoved=0;
	enum MeasurementType    measList[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
	double 					smoothWith,measurement,model;
	double					lowerLimit,upperLimit;
	double					currentPrefitAbs;
	double					prefits[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						OutlierDetected[epoch->usableSatellites];
	int						List2EpochPos[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						numOutliers,numDisabledSat,HalfAvailSat;
	int						NumSatUnselected;
	int						NumDiffMeas[MAX_GNSS];
	int						MeasInd2PosInd[MAX_GNSS+1][MAX_FILTER_MEASUREMENTS_SAT]; //The +1 is to have a inital position when Const2Pos is not set for a constellation
	int						NumSatMeas[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
	int						satPrinted[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						NumConst=0;
	int						NumAmbiguitiesRemoved;
	int						Const2Pos[MAX_GNSS];
	enum GNSSystem			Pos2Const[MAX_GNSS];
	enum GNSSystem          GNSS;
	int						ConstUsed[MAX_GNSS];
	TSatellite				*sat;
	
	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;

	//Initialize counters
	for(m=0;m<MAX_GNSS;m++) {
		ConstUsed[m]=0;
		NumDiffMeas[m]=0;
		Const2Pos[m]=MAX_GNSS;//Set value to MAX_GNSS, a position where no constellation will point to when Const2Pos is set for a given GNSS
		for(i=0;i<MAX_FILTER_MEASUREMENTS_SAT;i++) {
			MeasInd2PosInd[m][i]=-1;
			for(j=0;j<epoch->usableSatellites;j++) {
				satPrinted[m][i][j]=0;
			}
		}
	}
	for(i=0;i<MAX_FILTER_MEASUREMENTS_SAT;i++) {
		MeasInd2PosInd[MAX_GNSS][i]=-1;
	}

	//Loop through all satellites and measurements and group them by constellation and measurement type
	for(i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		if(sat->available==0) {
			continue;
		}
		k = epoch->satCSIndex[sat->GNSS][sat->PRN];
		for (j=0;j<options->numfilterMeasList[ROVERPOS][sat->GNSS][sat->PRN];j++) {	

			if (options->filterListAllMeasSelected[ROVERPOS][sat->GNSS][sat->PRN][j]!=MEASSELECTED) continue;

			if (options->usePhase==1 && options->estimateAmbiguities==0) {
				//Carrier phases are absolute, so they can be checked too
				//No need to check if it is pseudorange or carrier phase, as they will be the only types of measurements in the filter
			} else {
				//Only check with code measurements because they are absolute measurements
				if (options->filterMeasKind[ROVERPOS][sat->GNSS][sat->PRN][j]!=Pseudorange) continue;
			}

			ret = getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j], options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&measurement, &model,j);
			if (ret!=1) {
				continue;
			}
			//We are using the MeasPos2PrintPos, as it already separates by type of measurement
			l=epoch->measOrder[sat->GNSS].MeasPos2PrintPos[sat->PRN][j];
			if (MeasInd2PosInd[Const2Pos[sat->GNSS]][l]==-1) {
				if (ConstUsed[sat->GNSS]==0) {
					ConstUsed[sat->GNSS]=1;
					Const2Pos[sat->GNSS]=NumConst;
					Pos2Const[NumConst]=sat->GNSS;
					NumConst++;
				}
				MeasInd2PosInd[Const2Pos[sat->GNSS]][l]=NumDiffMeas[Const2Pos[sat->GNSS]];
				NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]=0;
				measList[Const2Pos[sat->GNSS]][NumDiffMeas[Const2Pos[sat->GNSS]]]=options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j][0];
				NumDiffMeas[Const2Pos[sat->GNSS]]++;

			}
			// Smoothing
			if ( options->smoothEpochs != 0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][j] == 1 ) {
				ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][j],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&smoothWith,NULL,0);
				if (ret!=1) {
					continue;
				} else {
					measurement = epoch->cycleslip.smoothedMeas[k][j] + smoothWith;
					prefits[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
				}
			} else {
				prefits[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
			}
			List2EpochPos[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]]=i;
			NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]++;
		}
	}

	//Loop for each constellation
	for(m=0;m<NumConst;m++) {
		//Loop for each different measurement
		for(i=0;i<NumDiffMeas[m];i++) {
			NumSatUnselected=0;
			NumAmbiguitiesRemoved=0;
			HalfAvailSat=(int)((double)(NumSatMeas[m][i])/2.);
			for(j=0;j<NumSatMeas[m][i];j++) {
				numOutliers=0;
				numDisabledSat=0;
				currentPrefitAbs=fabs(prefits[m][i][j]);
				lowerLimit=currentPrefitAbs-options->prefitOutlierDetectorAbsThreshold;
				upperLimit=currentPrefitAbs+options->prefitOutlierDetectorAbsThreshold;
				for(l=0;l<NumSatMeas[m][i];l++) {
					OutlierDetected[l]=0;
					if(l==j) continue; //We do not compare the prefit with itself
					currentPrefitAbs=fabs(prefits[m][i][l]);
					if(currentPrefitAbs<lowerLimit || currentPrefitAbs>upperLimit) {
						//Outlier detected
						numOutliers++;
						OutlierDetected[l]=1;
					}
				}
				if(numOutliers>=HalfAvailSat) {
					//Too many outliers. Means that the current satellite is the outlier
					if(epoch->sat[List2EpochPos[m][i][j]].available==1||satPrinted[m][i][j]==0) {
						if (epoch->sat[List2EpochPos[m][i][j]].available==1) {
							//The satellite has not been unselected, unselect it and set SATSEL num messages to 0
							satIndex=List2EpochPos[m][i][j];
							GNSS=epoch->sat[satIndex].GNSS;
							epoch->sat[satIndex].available=0;
							linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=0;
							epoch->usableSatellites--;
							epoch->usableSatellitesGNSS[Pos2Const[m]]--;
							epoch->discardedSatellites++;
							epoch->discardedSatellitesGNSS[Pos2Const[m]]++;
							epoch->totalNumAmbiguitiesEpoch-=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
							NumAmbiguitiesRemoved+=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
							NumSatUnselected++;
							TotalSatRemoved++;
						}
						if (satPrinted[m][i][l]==0) {
							//Message not printed for current satellite and measurement type
							satPrinted[m][i][l]=1;
						}
						sprintf(messagestr,"Prefit too high for measurement %s in comparison with other satellites",meastype2measstr(measList[m][i]));
						printSatSel(epoch,0,81,messagestr,List2EpochPos[m][i][j],options);
					}
				} else if (numOutliers>0) {
					//Outliers detected
					for(l=0;l<NumSatMeas[m][i];l++) {
						if(OutlierDetected[l]==1) {
							if(epoch->sat[List2EpochPos[m][i][l]].available==1||satPrinted[m][i][l]==0) {
								if (epoch->sat[List2EpochPos[m][i][l]].available==1) {
									//The satellite has not been unselected, unselect it and set SATSEL num messages to 0
									satIndex=List2EpochPos[m][i][j];
									GNSS=epoch->sat[satIndex].GNSS;
									epoch->sat[satIndex].available=0;
									linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=0;
									epoch->usableSatellites--;
									epoch->usableSatellitesGNSS[Pos2Const[m]]--;
									epoch->discardedSatellites++;
									epoch->discardedSatellitesGNSS[Pos2Const[m]]++;
									epoch->totalNumAmbiguitiesEpoch-=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
									NumAmbiguitiesRemoved+=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
									NumSatUnselected++;
									TotalSatRemoved++;
								}
								if (satPrinted[m][i][l]==0) {
									//Message not printed for current satellite and measurement type
									satPrinted[m][i][l]=1;
								}
								sprintf(messagestr,"Prefit too high for measurement %s in comparison with other satellites (threshold %.2f metres)",meastype2measstr(measList[m][i]),options->prefitOutlierDetectorAbsThreshold);
								printSatSel(epoch,0,82,messagestr,List2EpochPos[m][i][l],options);
							}
							numDisabledSat++;
							if(numDisabledSat==numOutliers) break;
						}
					}
				}
			}
			//Check if we have unselected more than HalfAvailSat. If receiver position is fixed, we can unselect all, 
			//but if receiver position is not fixed we will not unselect none, as we may be in convergence time
			//or receiver is moving very fast (e.g. a LEO satellite)
			if (NumSatUnselected>HalfAvailSat && options->receiverPositionSource > rpSET) {
				//Too much satellites unselected. Select them all again
				for(j=0;j<NumSatMeas[m][i];j++) {
					satIndex=List2EpochPos[m][i][j];
					GNSS=epoch->sat[satIndex].GNSS;
					linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=0;
					printSatSel(epoch,1,0,"Selected",satIndex,options);
					epoch->sat[satIndex].available=1;
					satPrinted[m][i][j]=0;
				}	
				epoch->usableSatellites+=NumSatUnselected;
				epoch->usableSatellitesGNSS[Pos2Const[m]]+=NumSatUnselected;
				epoch->discardedSatellites-=NumSatUnselected;
				epoch->discardedSatellitesGNSS[Pos2Const[m]]-=NumSatUnselected;
				epoch->totalNumAmbiguitiesEpoch+=NumAmbiguitiesRemoved;
				TotalSatRemoved-=NumSatUnselected;
			}
		} //End for all available prefits
	}

	//Rebuild epoch->usedSat2DataPos array, as positions will have moved due to the removed satellites
	if (TotalSatRemoved>0) {
		j=0;
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==1) {
				epoch->usedSat2DataPos[j]=i;
				j++;
			}
		}
	}
}

/*****************************************************************************
 * Name        : PrefitOutlierDetectorMedian
 * Description : Check for outliers in the prefits. A prefit outlier is defined 
 *               as a value being too high compared to the other values.
 *               It is only applied to code measurements, as 
 *               carrier phase measurements may differ a lot due to
 *                 ambiguities (except for the case that ambiguities are not computed,
 *                 which makes consider carrier phases as absolute measurements).
 *               It is also necessary to group the prefits by constellation and measurement
 *                 type (C1C,C5X, PC12, ...), as there is the inter-system clock bias and
 *                 the different DCBs for each measurement which could produce false
 *                 detection if all prefits was mixed toguether.
 *
 *               The detector works this way:
 *
 *               Group prefits by constellation and measurement type
 *     
 *               for each constellation:
 *                 for each mesurement type in the filter:
 *                   Compute the median of all prefits
 *                   For each satellite:
 *                     Compute absolute value of the difference between the prefit and the median
 *                     If the difference is higher than the threshold, unselect the satellite
 *
 *                   If half or more of the satellites are unvalid, then the current satellite is an outlier
 *                   Else discard the selected satellite.
 *
 *               Note that the outlier detector needs more than one satellite with the same constellation
 *                and type of measurement, therefore when discarding a satellite it will not remove the
 *                last satellite of a constellation. This is important for the filter, as if a constellation
 *                would be removed, we would need to remove its inter-system clock bias from the filter
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void PrefitOutlierDetectorMedian (TEpoch *epoch, TOptions *options) {

	int 					i,j,k,l,m;
	int						satIndex;
	int						ret;
	int						TotalSatRemoved=0;
	enum MeasurementType    measList[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
	double 					smoothWith,measurement,model,Median,Difference;
	double					prefits[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	double					prefitsSorted[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						List2EpochPos[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						HalfAvailSat;
	int						NumSatUnselected;
	int						NumDiffMeas[MAX_GNSS];
	int						MeasInd2PosInd[MAX_GNSS+1][MAX_FILTER_MEASUREMENTS_SAT]; //The +1 is to have a inital position when Const2Pos is not set for a constellation
	int						NumSatMeas[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
	int						satPrinted[MAX_GNSS][MAX_FILTER_MEASUREMENTS_SAT][epoch->usableSatellites];
	int						NumConst=0;
	int						NumAmbiguitiesRemoved;
	int						Const2Pos[MAX_GNSS];
	enum GNSSystem			Pos2Const[MAX_GNSS];
	enum GNSSystem			GNSS;
	int						ConstUsed[MAX_GNSS];
	TSatellite				*sat;
	
	//Put this option to 1 so all prints are buffered

	//Initialize counters
	for(m=0;m<MAX_GNSS;m++) {
		ConstUsed[m]=0;
		NumDiffMeas[m]=0;
		Const2Pos[m]=MAX_GNSS;//Set value to MAX_GNSS, a position where no constellation will point to when Const2Pos is set for a given GNSS
		for(i=0;i<MAX_FILTER_MEASUREMENTS_SAT;i++) {
			MeasInd2PosInd[m][i]=-1;
			for(j=0;j<epoch->usableSatellites;j++) {
				satPrinted[m][i][j]=0;
			}
		}
	}
	for(i=0;i<MAX_FILTER_MEASUREMENTS_SAT;i++) {
		MeasInd2PosInd[MAX_GNSS][i]=-1;
	}

	//Loop through all satellites and measurements and group them by constellation and measurement type
	for(i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		if(sat->available==0) {
			continue;
		}
		k = epoch->satCSIndex[sat->GNSS][sat->PRN];
		for (j=0;j<options->numfilterMeasList[ROVERPOS][sat->GNSS][sat->PRN];j++) {	

			if (options->filterListAllMeasSelected[ROVERPOS][sat->GNSS][sat->PRN][j]!=MEASSELECTED) continue;

			if (options->usePhase==1 && options->estimateAmbiguities==0) {
				//Carrier phases are absolute, so they can be checked too
				//No need to check if it is pseudorange or carrier phase, as they will be the only types of measurements in the filter
			} else {
				//Only check with code measurements because they are absolute measurements
				if (options->filterMeasKind[ROVERPOS][sat->GNSS][sat->PRN][j]!=Pseudorange) continue;
			}

			ret = getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j], options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&measurement, &model,j);
			if (ret!=1) {
				continue;
			}
			//We are using the MeasPos2PrintPos, as it already separates by type of measurement
			l=epoch->measOrder[sat->GNSS].MeasPos2PrintPos[sat->PRN][j];
			if (MeasInd2PosInd[Const2Pos[sat->GNSS]][l]==-1) {
				if (ConstUsed[sat->GNSS]==0) {
					ConstUsed[sat->GNSS]=1;
					Const2Pos[sat->GNSS]=NumConst;
					Pos2Const[NumConst]=sat->GNSS;
					NumConst++;
				}
				MeasInd2PosInd[Const2Pos[sat->GNSS]][l]=NumDiffMeas[Const2Pos[sat->GNSS]];
				NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]=0;
				measList[Const2Pos[sat->GNSS]][NumDiffMeas[Const2Pos[sat->GNSS]]]=options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j][0];
				NumDiffMeas[Const2Pos[sat->GNSS]]++;

			}
			// Smoothing
			if ( options->smoothEpochs != 0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][j] == 1 ) {
				ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][j],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&smoothWith,NULL,0);
				if (ret!=1) {
					continue;
				} else {
					measurement = epoch->cycleslip.smoothedMeas[k][j] + smoothWith;
					prefits[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
					prefitsSorted[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
				}
			} else {
				prefits[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
				prefitsSorted[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]] = measurement - model;
			}
			List2EpochPos[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]][NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]]=i;
			NumSatMeas[Const2Pos[sat->GNSS]][MeasInd2PosInd[Const2Pos[sat->GNSS]][l]]++;
		}
	}


	//Loop for each constellation
	for(m=0;m<NumConst;m++) {
		//Loop for each different measurement
		for(i=0;i<NumDiffMeas[m];i++) {
			NumSatUnselected=0;
			NumAmbiguitiesRemoved=0;
			HalfAvailSat=(int)((double)(NumSatMeas[m][i])/2.);

			qsort(prefitsSorted[m][i],NumSatMeas[m][i],sizeof(double),qsort_compare_double);

			if(NumSatMeas[m][i]%2==0) {
				//Number of prefits is even
				Median=(prefitsSorted[m][i][HalfAvailSat-1]+prefitsSorted[m][i][HalfAvailSat])/2.;
			} else {
				//Number of prefits is odd
				Median=prefitsSorted[m][i][HalfAvailSat];
			}

			for(j=0;j<NumSatMeas[m][i];j++) {
				//Discard satellites which are N times over the median
				Difference=fabs(prefits[m][i][j]-Median);
				if( Difference > options->prefitOutlierDetectorMedianThreshold ) {
					if(epoch->sat[List2EpochPos[m][i][j]].available==1||satPrinted[m][i][j]==0) {
						if (epoch->sat[List2EpochPos[m][i][j]].available==1) {
							//The satellite has not been unselected, unselect it and set SATSEL num messages to 0
							satIndex=List2EpochPos[m][i][j];
							GNSS=epoch->sat[satIndex].GNSS;
							epoch->sat[satIndex].available=0;
							linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=0;
							epoch->usableSatellites--;
							epoch->usableSatellitesGNSS[Pos2Const[m]]--;
							epoch->discardedSatellites++;
							epoch->discardedSatellitesGNSS[Pos2Const[m]]++;
							epoch->totalNumAmbiguitiesEpoch-=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
							NumAmbiguitiesRemoved+=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSS][epoch->sat[satIndex].PRN];
							NumSatUnselected++;
							TotalSatRemoved++;
						}
						if (satPrinted[m][i][j]==0) {
							//Message not printed for current satellite and measurement type
							satPrinted[m][i][j]=1;
						}
						sprintf(messagestr,"Prefit too different (%.2f) for measurement %s with respect to the prefit median (%.2f), threshold %.2f metres",Difference,meastype2measstr(measList[m][i]),Median,options->prefitOutlierDetectorMedianThreshold);
						printSatSel(epoch,0,83,messagestr,List2EpochPos[m][i][j],options);
					}
				}
			}
			//Check if we have unselected more than HalfAvailSat. If receiver position is fixed, we can unselect all, 
			//but if receiver position is not fixed we will not unselect none, as we may be in convergence time
			//or receiver is moving very fast (e.g. a LEO satellite)
			if (NumSatUnselected>HalfAvailSat  && options->receiverPositionSource > rpSET ) {
				//Too much satellites unselected. Select them all again
				for(j=0;j<NumSatMeas[m][i];j++) {
					satIndex=List2EpochPos[m][i][j];
					GNSS=epoch->sat[satIndex].GNSS;
					linesstoredSATSEL[epoch->GNSS2PrintPos[GNSS]][epoch->sat2Printpos[satIndex]]=0;
					printSatSel(epoch,1,0,"Selected",satIndex,options);
					epoch->sat[satIndex].available=1;
				}	
				epoch->usableSatellites+=NumSatUnselected;
				epoch->usableSatellitesGNSS[Pos2Const[m]]+=NumSatUnselected;
				epoch->discardedSatellites-=NumSatUnselected;
				epoch->discardedSatellitesGNSS[Pos2Const[m]]-=NumSatUnselected;
				epoch->totalNumAmbiguitiesEpoch+=NumAmbiguitiesRemoved;
				TotalSatRemoved-=NumSatUnselected;
			}
		}
	} 

	//Rebuild epoch->usedSat2DataPos array, as positions will have moved due to the removed satellites
	if (TotalSatRemoved>0) {
		j=0;
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==1) {
				epoch->usedSat2DataPos[j]=i;
				j++;
			}
		}
	}
}

/*****************************************************************************
 * Name        : fillUsableSatellites
 * Description : Check for the usable satellites in the specified epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TEpoch  *epochDGNSS             I  N/A  Reference epoch for DGNSS
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A   0 => All OK
 *                                         -1 => No satellites with reference clock and
 *                                                changing satellite clock is disabled
 *****************************************************************************/
int fillUsableSatellites (TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options) {
	int						i, j, k, m, n;
   	int						l=FIRST_POS_IS_CLK;	//First position of inter clock bias is 4 (starting at 0 and after x,y,z,dt)
	int						check,check1;
	int 					numNconSamples = -1 * options->csNconMin + 1;
	int						printC1C;
	int						ret;
	int						NoMeasSelectedInFilter;
	double					sunPos[3];
	double					auxT;
	enum GNSSystem			lastGNSSselected;

	// Put this option to 1 so all prints are buffered
	options->printInBuffer = 1;
	
	if ( options->discardEclipsedSatellites ) {
		findSun(&epoch->t,sunPos);
	}

	for(i=0;i<MAX_GNSS;i++) {
		epoch->InterSystemClocksPosDOP[i]=-1;
		epoch->InterSystemClocksUnk2GNSS[i+FIRST_POS_IS_CLK]=-1;
		epoch->InterSystemClocksUnk[i]=-1;
		epoch->hasInterSystemClocksUnk[i]=0;
		epoch->usableSatellitesGNSS[i]=0;
		epoch->discardedSatellitesGNSS[i]=0;
		epoch->constellationUsed[i]=0;
		epoch->constellationNotUsed[i]=0;
	}

	epoch->InterSystemClocksPosDOP[options->ClkRefPriorityList[0]]=3;
	epoch->ReferenceGNSSClock=options->ClkRefPriorityList[0];
	epoch->numInterSystemClocksFilter=0;
	epoch->totalNumAmbiguitiesEpoch=0;
	epoch->usableSatellites = 0;
	epoch->discardedSatellites=0;
	epoch->numConstellationsUsed=0;
	epoch->numConstellationsNotUsed=0;

	for (i=0;i<epoch->numSatellites;i++) {
		check = 1;
		printC1C=0;
		NoMeasSelectedInFilter=0;
		k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];

		// Satellite selection check
		if ( !options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN] ) {
			printSatSel(epoch,0,1,"Deselection forced",i,options);
			epoch->sat[i].available = 0;
			//When a satellite is unselected, no cycle-slip or modelling is done
			//Satellites forced to be unselected will not count to the number of satellites used
			continue;
		}

		//Measurement selection check
		if ( options->MeasSelected[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN]!=MEASSELECTED) {
			printSatSel(epoch,0,2,"Measurement selection for rover not finished",i,options);
			epoch->sat[i].available = 0;
			//When a satellite has measurement pending to be selected, no cycle-slip or modelling is done
			//Add 1 to unselected satellites, as no more conditions are checked
			epoch->discardedSatellites++;
			epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
			continue;
		}

		//Check for missing measurements in rover
		if (epoch->sat[i].MissingMeasText[0]!='\0') {
			sprintf(messagestr,"Measurements missing%s:%s",epochDGNSS==NULL?"":" in rover",epoch->sat[i].MissingMeasText);
			printSatSel(epoch,0,3,messagestr,i,options);
			check = 0;
		} else {
			//If measurements are missing, no cycle-slip or pre-check is done

			// SNR check. If not met, no modelling or cycle-slip detection is done
			if ( epoch->sat[i].hasSNR==0 ) {
				epoch->sat[i].badSNRText[0]='[';
				sprintf(messagestr,"SNR not met%s %s]",epochDGNSS==NULL?"":" in rover",epoch->sat[i].badSNRText);
				printSatSel(epoch,0,4,messagestr,i,options);
				check = 0;
				//Do not skip if reference station data is available, so it can be printed too
				if (epochDGNSS==NULL) {
					epoch->sat[i].available = 0;
					//Add 1 to unselected satellites, as no more conditions are checked
					epoch->discardedSatellites++;
					epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
					continue; 
				}
			}


			// Cycle slip sanity check
			if ( epoch->cycleslip.CS[k] == 1 ) {
				sprintf(messagestr,"Cycle-slip%s",epochDGNSS==NULL?"":" in rover");
				printSatSel(epoch,0,11,messagestr,i,options);
				check = 0;
			} else {
				//If there is a data gap after the outlier, do not print
				//the outlier message while we are waiting for N-consecutive epochs
				if ( epoch->cycleslip.Nconsecutive[k] == 0 ) {
					// Satellite Consistency of Measurements sanity check
					if ( epoch->cycleslip.consistency[k] == 1 ) {
						sprintf(messagestr,"Unconsistency of measurements%s",epochDGNSS==NULL?"":" in rover");
						printSatSel(epoch,0,7,messagestr,i,options);
						check = 0;
					}
					// Outlier check
					if ( epoch->cycleslip.outlierMW[k] == 1)  {
						sprintf(messagestr,"Outlier in MW detector%s",epochDGNSS==NULL?"":" in rover");
						printSatSel(epoch,0,8,messagestr,i,options);
						check = 0;
					}
					if ( epoch->cycleslip.outlierLI[k] == 1) { 
						sprintf(messagestr,"Outlier in LI detector%s",epochDGNSS==NULL?"":" in rover");
						printSatSel(epoch,0,9,messagestr,i,options);
						check = 0;
					}
					if ( epoch->cycleslip.outlierIGF[k] == 1)  {
						sprintf(messagestr,"Outlier in IGF detector%s",epochDGNSS==NULL?"":" in rover");
						printSatSel(epoch,0,10,messagestr,i,options);
						check = 0;
					}
				} else if ( epoch->cycleslip.Nconsecutive[k] < 0 ) {
					// N-consecutive sanity check
					sprintf(messagestr,"Not enough consecutive samples%s (current %d, minimum %d)",epochDGNSS==NULL?"":" in rover",numNconSamples + epoch->cycleslip.Nconsecutive[k],numNconSamples);
					printSatSel(epoch,0,5,messagestr,i,options);
					check = 0;
				}
			}
	
			// Arc length sanity check
			if ( epoch->cycleslip.arcLength[k] <= options->minArcLength ) {
				sprintf(messagestr,"Arc too short%s (%d). Min arc length: %d",epochDGNSS==NULL?"":" in rover",epoch->cycleslip.arcLength[k],options->minArcLength==0?1:(options->minArcLength+1));
				printSatSel(epoch,0,6,messagestr,i,options);
				check = 0;
			}

		}
		if (epochDGNSS!=NULL && options->solutionMode==DGNSSMode) {
			m = epochDGNSS->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			if (m>=0) {
				n = epochDGNSS->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
				//Check for missing measurements in reference station
				if (epochDGNSS->sat[m].MissingMeasText[0]!='\0') {
					sprintf(messagestr,"Measurements missing in reference station:%s",epochDGNSS->sat[m].MissingMeasText);
					printSatSel(epoch,0,21,messagestr,i,options);
					check = 0;
				} else {
					//If measurements are missing, no cycle-slip or pre-check is done

					// SNR check. If not met, no modelling or cycle-slip detection is done
					if ( epochDGNSS->sat[m].hasSNR==0 ) {
						epochDGNSS->sat[m].badSNRText[0]='[';
						sprintf(messagestr,"SNR not met in reference station %s]",epochDGNSS->sat[m].badSNRText);
						printSatSel(epoch,0,22,messagestr,i,options);
						epoch->sat[i].available = 0;
						//Add 1 to unselected satellites, as no more conditions are checked
						epoch->discardedSatellites++;
						epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
						continue;
					}


					// Cycle slip sanity check
					if ( epochDGNSS->cycleslip.CS[n] == 1 ) {
						sprintf(messagestr,"Cycle-slip in reference station");
						printSatSel(epoch,0,29,messagestr,i,options);
						check = 0;
					} else {
						//If there is a data gap after the outlier, do not print
						//the outlier message while we are waiting for N-consecutive epochs
						if ( epochDGNSS->cycleslip.Nconsecutive[n] == 0 ) {
							// Satellite Consistency of Measurements sanity check
							if ( epochDGNSS->cycleslip.consistency[n] == 1 ) {
								sprintf(messagestr,"Unconsistency of measurements in reference station");
								printSatSel(epoch,0,25,messagestr,i,options);
								check = 0;
							}
							// Outlier check
							if ( epochDGNSS->cycleslip.outlierMW[n] == 1)  {
								sprintf(messagestr,"Outlier in MW detector in reference station");
								printSatSel(epoch,0,26,messagestr,i,options);
								check = 0;
							}
							if ( epochDGNSS->cycleslip.outlierLI[n] == 1) { 
								sprintf(messagestr,"Outlier in LI detector in reference station");
								printSatSel(epoch,0,27,messagestr,i,options);
								check = 0;
							}
							if ( epochDGNSS->cycleslip.outlierIGF[n] == 1)  {
								sprintf(messagestr,"Outlier in IGF detector in reference station");
								printSatSel(epoch,0,28,messagestr,i,options);
								check = 0;
							}
						} else if ( epochDGNSS->cycleslip.Nconsecutive[n] < 0 ) {
							// N-consecutive sanity check
							sprintf(messagestr,"Not enough consecutive samples in reference station (current %d, minimum %d)", numNconSamples + epochDGNSS->cycleslip.Nconsecutive[n],numNconSamples);
							printSatSel(epoch,0,23,messagestr,i,options);
							check = 0;
						}
					}
			
					// Arc length sanity check
					if ( epochDGNSS->cycleslip.arcLength[n] <= options->minArcLength ) {
						sprintf(messagestr,"Arc too short in reference station (%d). Min arc length: %d",epochDGNSS->cycleslip.arcLength[n],options->minArcLength==0?1:(options->minArcLength+1));
						printSatSel(epoch,0,24,messagestr,i,options);
						check = 0;
					}

				}
			}
		}

		// Steady-state operation check
		if ( options->excludeSmoothingConvergence > 0 && (( epoch->cycleslip.arcLength[k] - options->minArcLength ) < options->excludeSmoothingConvergence) ) {
			// Satellite not reached steady-state operation
			sprintf(messagestr,"Steady-state operation not reached. %d epochs passed, still %d epochs to achieve %d",(int)max(1.0,epoch->cycleslip.arcLength[k]-options->minArcLength),options->excludeSmoothingConvergence-((int)max(1,epoch->cycleslip.arcLength[k]-options->minArcLength)),options->excludeSmoothingConvergence);
			printSatSel(epoch,0,12,messagestr,i,options);
			check = 0;
		}

		//Check if we have code measurements (if we don't have them, transmission time can not be computed)
		if ( epoch->sat[i].hasAnyCodeMeas==0 && printC1C==0 ) {
			if (options->usePhase==1 && options->estimateAmbiguities==0) {
				 printSatSel(epoch,0,41,"No code and carrier phase measurements available for computing transmission time",i,options);
				 check = 0;
			} else {
				 printSatSel(epoch,0,40,"No code measurement available for computing transmission time",i,options);
				 check = 0;
			}
		}

		// Ephemeris availability check
		if ( epoch->sat[i].hasOrbitsAndClocks == 0 ) {
			printSatSel(epoch,0,42,"Ephemerides unavailable",i,options);
			check = 0;
		} else if (epoch->sat[i].hasSatPhaseCenterCor==0 ) {
			printSatSel(epoch,0,43,"Satellite phase center corrections unavailable",i,options);
			check = 0;
		}
		
		// DCBs availability check
		if ( epoch->sat[i].hasDCBs == 0 && epoch->sat[i].hasOrbitsAndClocks != 0) {
			if (epoch->sat[i].GNSS==GPS) {
			   	if ( epoch->sat[i].hasDCBsofC1P1 ==0 && options->GPSp1c1DCBModel == GPSp1c1STRICT) {
					printSatSel(epoch,0,44,"GPS P1-C1 DCB unavailable",i,options);
				} 
				printSatSel(epoch,0,45,"DCB unavailable",i,options);
			} else {
				printSatSel(epoch,0,45,"DCB unavailable",i,options);
			}
			check = 0;
		}
		
		// Eclipsed satellite check
		if ( options->discardEclipsedSatellites ) {
			if (isEclipsed(&epoch->t,&epoch->sat[i],&epoch->satInfo[epoch->sat[i].GNSS][epoch->sat[i].PRN],sunPos,&auxT)) {
				if (auxT==0) {
					printSatSel(epoch,0,46,"Satellite under eclipse",i,options);
				} else {
					sprintf(messagestr,"Satellite was under eclipse %.0f seconds ago",auxT);
					printSatSel(epoch,0,47,messagestr,i,options);
				}
				check = 0;
			}
		}


		// Elevation check (if approximate position is good enough, ie <100Km)
		if ( (epoch->sat[i].elevation < options->elevationMask) && (epoch->receiver.aproxPositionError < MAXAPROXPOSERROR) && (epoch->sat[i].hasOrbitsAndClocks == 1) ) { // 100Km
			if (epoch->sat[i].hasAnyCodeMeas == 1 && epoch->sat[i].elevation!=0.) {
				sprintf(messagestr,"Elevation too low (%.2f degrees)",epoch->sat[i].elevation*r2d);
				printSatSel(epoch,0,48,messagestr,i,options);
				check = 0;
			}
		} else if (fabs(epoch->sat[i].elevation) < MIN_ELEVATION_WEIGHT) {
			check1=0;
			for (j=0;j<options->numfilterMeasList[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN];j++) {
				switch(options->weightMode[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]) {
					case Elevation2Weight: case SBASElev2Weight: case DGNSSElev2Weight:
						//All case where elevation weight is applied as 1/(sin(elev)^2)
						sprintf(messagestr,"Elevation too low (%.2f degrees) for applying weight 1/(sin(elev)^2)",epoch->sat[i].elevation*r2d);
						printSatSel(epoch,0,49,messagestr,i,options);
						check=0;
						check1=1;
						break;
					case SNRElevWeight: case SBASSNRElevWeight: case DGNSSSNRElevWeight:
						//All case where elevation weight is applied as 10^(-SNR/10)/(sin(elev)^2)
						sprintf(messagestr,"Elevation too low (%.2f degrees) for applying weight 10^(-SNR/10)/(sin(elev)^2)",epoch->sat[i].elevation*r2d);
						printSatSel(epoch,0,50,messagestr,i,options);
						check=0;
						check1=1;
						break;
					default:
						break;
				}
				if (check1) break; //This is for only printing once the SATSEL message
			}
		}

		//Check if SNR was available for computing the weight
		if (epoch->sat[i].NoSNRforWeightMeas!=NA) {
			sprintf(messagestr,"No SNR available for computing the weight for measurement %s",meastype2measstr(-epoch->sat[i].NoSNRforWeightMeas));
			printSatSel(epoch,0,51,messagestr,i,options);
			check=0;
		}
		
		if (epoch->sat[i].validIono == 0 ) {
			switch(options->ionoModel) {
				case IONEXIonoModel:
					// Ionex check (in case a IONEX file is used)
					sprintf(messagestr,"Missing IONEX data");
					printSatSel(epoch,0,52,messagestr,i,options);
					check = 0;
					break;
				case FPPPIonoModel:
					// FPPP check (in case a FPPP file is used)
					sprintf(messagestr,"Missing ionosphere F-PPP data");
					printSatSel(epoch,0,53,messagestr,i,options);
					check = 0;
					break;
				case neQuickIonoModel:
					// NeQuick check (in case NeQuick is used)
					sprintf(messagestr,"NeQuick ionosphere could not be computed");
					printSatSel(epoch,0,84,messagestr,i,options);
					check = 0;
					break;
				default:
					break;
			}
		}

		// SBAS iono availability (if we are not in SBAS mode processing)
		if ( options->SBAScorrections == SBASionoOnly ) {
			if (epoch->sat[i].hasSBAScor == 0) {
				sprintf(messagestr,"SBAS iono unavailable (GEO %3d)",epoch->SBASUsedGEO);
				printSatSel(epoch,0,54,messagestr,i,options);
				check = 0;
			}
		}

		// URA check
		if ( epoch->sat[i].URAValue>=options->MaxURABroadcast) {
			sprintf(messagestr,"URA value (%.1f) is equal or greater than the threshold (%.1f)",epoch->sat[i].URAValue,options->MaxURABroadcast);
			printSatSel(epoch,0,55,messagestr,i,options);
			check = 0;
		}

		//Check satellite health
		switch(epoch->sat[i].hasHealthStr[0]) {
			case '\0':
				//Satellite is usable (healthy or marginal or unhealthy status are allowed)
				break;
			case 'M':
				//Satellite is marginal and marginal state is not allowed
				sprintf(messagestr,"Satellite is in marginal mode %s",epoch->sat[i].hasHealthStr);
				printSatSel(epoch,0,56,messagestr,i,options);
				check = 0;
				break;
			default:
				//Satellite is unhealthy and unhealthy state is not allowed
				sprintf(messagestr,"Satellite is unhealthy %s",epoch->sat[i].hasHealthStr);
				printSatSel(epoch,0,57,messagestr,i,options);
				check = 0;
		}

		//Check if measurements have been selected for the filter
		if (options->numfilterMeasSelected[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) {
			//Check if GLONASS has FDMA frequency offset
			if (epoch->sat[i].GNSS==GLONASS && 
					(options->GLOsatFDMAdisabled[GLONASS][epoch->sat[i].PRN][1]==1 || options->GLOsatFDMAdisabled[GLONASS][epoch->sat[i].PRN][2]==1)) {
				sprintf(messagestr,"Missing frequency number (k) for FDMA signals");
				printSatSel(epoch,0,58,messagestr,i,options);
				check = 0;
			} else {
				sprintf(messagestr,"No measurements selected for the filter");
				printSatSel(epoch,0,59,messagestr,i,options);
				check = 0;
			}
			NoMeasSelectedInFilter=1;
		} else if (options->filterMeasFreqMissng[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
			//GLONASS has measurements selected but any of its frequencies has missing frequency numbers
			sprintf(messagestr,"Missing frequency number (k) for FDMA signals");
			printSatSel(epoch,0,58,messagestr,i,options);
			check=0;	
		}


		// SBAS correction availability
		if ( options->SBAScorrections>=SBAS1Fused) {
		   if (options->SBASConstUsed[epoch->SBASUsedGEOindex][options->SBASmodePos][epoch->sat[i].GNSS]==1 ) {
				if (epoch->sat[i].hasSBAScor == 0) {
					sprintf(messagestr,"SBAS corrections unavailable (GEO %3d)",epoch->SBASUsedGEO);
					printSatSel(epoch,0,100,messagestr,i,options);
					check = 0;
				} else if ( epoch->sat[i].hasAnyCodeMeas == 0 ) { //Check if we have C1C measurement for SBAS
					printSatSel(epoch,0,101,"C1C measurement unavailable",i,options);
					printC1C=1;
					check = 0;
				}
		   } else {
				sprintf(messagestr,"%s constellation not monitored by SBAS (GEO %3d)",gnsstype2gnssname(epoch->sat[i].GNSS),epoch->SBASUsedGEO);
				printSatSel(epoch,0,102,messagestr,i,options);
				check = 0;
		   }
		}

		if (options->DGNSS == 1) {
			//Measurement selection check
			if ( epochDGNSS->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]==-1) {
				printSatSel(epoch,0,19,"Satellite missing in reference station",i,options);
				epoch->sat[i].available = 0;
				//There is no data in reference station file (the data line for current satellite is not reference station file)
				//Add 1 to unselected satellites, as no more conditions are checked
				epoch->discardedSatellites++;
				epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
				continue;

			} else if ( options->MeasSelected[REFSTAPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN]!=MEASSELECTED) {
				printSatSel(epoch,0,20,"Measurement selection for reference station not finished",i,options);
				epoch->sat[i].available = 0;
				//When a satellite has measurement pending to be selected, no cycle-slip or modelling is done
				//Add 1 to unselected satellites, as no more conditions are checked
				epoch->discardedSatellites++;
				epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
				continue;
			}

			// DGNSS check (in case a DGNSS file is used)
			switch (epoch->sat[i].hasDGNSScor) {
				case 0:
					sprintf(messagestr,"No DGNSS corrections");
					printSatSel(epoch,0,110,messagestr,i,options);
					check = 0;
					break;
				case 2:
					sprintf(messagestr,"No DGNSS corrections: Time out");
					printSatSel(epoch,0,111,messagestr,i,options);
					check = 0;
					break;
				case 3:	
					sprintf(messagestr,"No DGNSS corrections: Excluded during the smoother convergence in the Reference Station");
					printSatSel(epoch,0,112,messagestr,i,options);
					check = 0;
					break;
				case 4:
					sprintf(messagestr,"No DGNSS corrections: Excluded during the smoother convergence in the Rover Station");
					printSatSel(epoch,0,113,messagestr,i,options);
					check = 0;
					break;
				case 5:
					if ( epoch->sat[i].hasOrbitsAndClocks != 0 ) {
						sprintf(messagestr,"No DGNSS corrections: IODE from BRDC and RTCM do not match");
						printSatSel(epoch,0,114,messagestr,i,options);
						check = 0;
					} 
					break;
				case 6:
					sprintf(messagestr,"No DGNSS corrections: Excluded due to differential correction is too large");
					printSatSel(epoch,0,115,messagestr,i,options);
					check = 0;
					break;
				case 7:
					sprintf(messagestr,"No DGNSS corrections: Epoch in reference station (last read %29s) cannot be aligned with rover",epochDGNSS->tSoDHourStr);
					printSatSel(epoch,0,116,messagestr,i,options);
					check = 0;
					break;
				default:
					break;
			}
		}

		// If everything is available satellite can be used
		if ( check ) {
			epoch->sat[i].available = 1;
			printSatSel(epoch,1,0,"Selected",i,options);
			epoch->usedSat2DataPos[epoch->usableSatellites]=i;
			epoch->usableSatellites++;
			epoch->usableSatellitesGNSS[epoch->sat[i].GNSS]++;
			epoch->totalNumAmbiguitiesEpoch+=options->numfilterCarrierPhaseMeas[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN];
			if (epoch->constellationUsed[epoch->sat[i].GNSS]==0) {
				if (epoch->sat[i].GNSS!=options->ClkRefPriorityList[0] && options->GNSSclockSource[options->ClkRefPriorityList[0]][epoch->sat[i].GNSS]==ClkSrcCalculate) {
					epoch->numInterSystemClocksFilter++;
					epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]=l;
					epoch->InterSystemClocksUnk[epoch->sat[i].GNSS]=l;
					epoch->InterSystemClocksUnk2GNSS[l]=epoch->sat[i].GNSS;
					epoch->hasInterSystemClocksUnk[epoch->sat[i].GNSS]=1;
					l++;
					}
					epoch->constellationUsed[epoch->sat[i].GNSS]=1;
				lastGNSSselected=epoch->sat[i].GNSS;
				epoch->constellationUsedList[epoch->numConstellationsUsed]=epoch->sat[i].GNSS;
				epoch->numConstellationsUsed++;
			}
		} else {
			epoch->sat[i].available = 0;
			if(NoMeasSelectedInFilter==0) {
				//Add 1 to unselected satellites only if the satellite has measurement selected in the filter
				epoch->discardedSatellites++;
				epoch->discardedSatellitesGNSS[epoch->sat[i].GNSS]++;
			}
		}
	}

	//Compute number of constellations unused and not manually unselected
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->constellationUsed[i]==0 && options->ConstellationUsed[i]==1) {
			epoch->constellationNotUsed[i]=1;
			epoch->constellationNotUsedList[epoch->numConstellationsNotUsed]=i;
			epoch->numConstellationsNotUsed++;
		}
	}

	//If the reference constellation is not available, switch to the next one available in the preference list
	//The "-1" in "4+epoch->numInterSystemClocksFilter-1" is due to that the reference clock is not available, so another
	//constellation will be used as reference one and therefore an inter-system clock bias will be removed
	if (epoch->constellationUsed[options->ClkRefPriorityList[0]]==0 && epoch->usableSatellites>=(4+epoch->numInterSystemClocksFilter-1)) {
		if (options->AllowChangeReferenceGNSSClk) {
			ret=changeReferenceConstellationFilter(lastGNSSselected,epoch,options);
			return ret;
		} else {
			return -1;
		}
	}
	return 0;
}

/*****************************************************************************
 * Name        : changeReferenceConstellationFilter
 * Description : Change the reference constellation in the filter (and all
 *                its inter-system clock bias)
 * Parameters  :
 * Name                             |Da|Unit|Description
 * enum GNSSystem lastGNSSselected   I  N/A  Constellation of the last satellite used
 * TEpoch  *epoch                    IO N/A  Reference epoch
 * TOptions  *options                I  N/A  TOptions structure
 * Returned value (int)              O  N/A   0 => All OK
 *                                           -1 => No satellites with reference clock and
 *                                                  changing satellite clock is disabled
 *****************************************************************************/
int changeReferenceConstellationFilter (enum GNSSystem lastGNSSselected, TEpoch *epoch, TOptions *options) {

	int 					i,j,k;
	int						l=FIRST_POS_IS_CLK;
	int						len;
	int						measIndex,FilterPos;
	int						pos1,pos2;
	double					clockISCBdiff;
	double					auxd;
	enum MeasurementType	meas;
	char					auxstr[20];

	if (epoch->numConstellationsUsed==1) {
		//Only one constellation, use it as a reference
		epoch->numInterSystemClocksFilter=0;
		epoch->ReferenceGNSSClock=lastGNSSselected;
		epoch->InterSystemClocksPosDOP[lastGNSSselected]=3;
		epoch->InterSystemClocksUnk[lastGNSSselected]=-1;
		epoch->InterSystemClocksUnk2GNSS[FIRST_POS_IS_CLK]=-1;
		epoch->hasInterSystemClocksUnk[lastGNSSselected]=0;
	} else {
		//Search in the priority list
		for(i=1;i<options->numClkRefPriorityList;i++) { //Start in 1 because position 0 is the preferred constellation for reference clock, which is missing
			if (epoch->constellationUsed[options->ClkRefPriorityList[i]]==1) break;
		}
		if (i==options->numClkRefPriorityList) return -1; //No constellation available in reference list
		//Set the constellation as the reference one
		epoch->ReferenceGNSSClock=options->ClkRefPriorityList[i];
		//Recompute InterSystemClocks variables, as the source for for the inter-system clock bias may be different
		epoch->numInterSystemClocksFilter=0;
		l=FIRST_POS_IS_CLK;
		for(i=0;i<MAX_GNSS;i++) {
			epoch->InterSystemClocksPosDOP[i]=-1;
			epoch->InterSystemClocksUnk2GNSS[i+FIRST_POS_IS_CLK]=-1;
			epoch->InterSystemClocksUnk[i]=-1;
			epoch->hasInterSystemClocksUnk[i]=0;
		}
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->constellationUsed[i]==0) continue;
			if (i==epoch->ReferenceGNSSClock) continue;
			if (options->GNSSclockSource[epoch->ReferenceGNSSClock][i]==ClkSrcCalculate) {
				epoch->numInterSystemClocksFilter++;
				epoch->InterSystemClocksPosDOP[i]=l;
				epoch->InterSystemClocksUnk[i]=l;
				epoch->InterSystemClocksUnk2GNSS[l]=i;
				epoch->hasInterSystemClocksUnk[i]=1;
				l++;
			}
		}
		epoch->InterSystemClocksPosDOP[epoch->ReferenceGNSSClock]=3;
		//As inter-system clock bias source may have changed, if for any satellite the source changes, then we need to remove
		//the previous correction applied (if not estimated) and apply the new one (if not estimated)
		for(i=0;i<epoch->numSatellites;i++) {
			//Note that when modelling, it will always apply the inter-system correction using options->ClkRefPriorityList[0] as reference clock
			if (!(options->GNSSclockSource[epoch->ReferenceGNSSClock][epoch->sat[i].GNSS]==ClkSrcCalculate && options->GNSSclockSource[options->ClkRefPriorityList[0]][epoch->sat[i].GNSS]==ClkSrcCalculate)) {
				//If previous reference inter-sytem clock bias was not estimated, remove it from model
				switch(options->GNSSclockSource[options->ClkRefPriorityList[0]][epoch->sat[i].GNSS]) {
					case ClkSrcRINEX:
						//To be implemented
						clockISCBdiff=0.;
						break;
					case ClkSrcUser:
						clockISCBdiff=-options->GNSSclockValue[options->ClkRefPriorityList[0]][epoch->sat[i].GNSS];
						break;
					default:
						clockISCBdiff=0.;
						break;
				}
				//If new reference inter-sytem clock bias is not estimated, add it to model
				switch(options->GNSSclockSource[epoch->ReferenceGNSSClock][epoch->sat[i].GNSS]) {
					case ClkSrcRINEX:
						//To be implemented
						clockISCBdiff+=0.;
						break;
					case ClkSrcUser:
						clockISCBdiff+=options->GNSSclockValue[epoch->ReferenceGNSSClock][epoch->sat[i].GNSS];
						break;
					default:
						clockISCBdiff+=0.;
						break;
				}
				//Loop through all modelled measurements
				for (j=0;j<epoch->measOrder[epoch->sat[i].GNSS].numMeasListToBeModelled[epoch->sat[i].PRN];j++) {
					meas = epoch->measOrder[epoch->sat[i].GNSS].measListToBeModelled[epoch->sat[i].PRN][i];
					measIndex = epoch->measOrder[epoch->sat[i].GNSS].meas2Ind[meas];
					for(k=0;k<epoch->measOrder[epoch->sat[i].GNSS].numMeasPosToFilterPos[epoch->sat[i].PRN][j];k++) {
						FilterPos=epoch->measOrder[epoch->sat[i].GNSS].MeasPosToFilterPos[epoch->sat[i].PRN][j][k];
						epoch->sat[i].meas[measIndex].modelAll[FilterPos]+=clockISCBdiff;
					}
					epoch->sat[i].meas[measIndex].model+=clockISCBdiff;

				}
				//If print MODEL is enabled, we will need to change the iscb value and the total model value computed directly in the string
				if (options->printModel==1 && options->printV5format==0) {
					pos1=epoch->GNSS2PrintPos[epoch->sat[i].GNSS];
					pos2=epoch->sat2Printpos[i];
					for(j=0;j<linesstoredMODEL[pos1][pos2];j++) {
						if ( printbufferMODEL[pos1][pos2][j][0] == '\0' ) continue;
						len=(int)strlen(printbufferMODEL[pos1][pos2][j]);
						//Change inter-system clock bias
						getstr(auxstr,printbufferMODEL[pos1][pos2][j],len,412,9);
						auxd=clockISCBdiff+atof(auxstr);
						sprintf(&printbufferMODEL[pos1][pos2][j][412],"%9.5f",auxd);
						printbufferMODEL[pos1][pos2][j][421]=' '; //For removing the '\0' added by the sprintf
						//Change full model value without dual-frequency DCB
						getstr(auxstr,printbufferMODEL[pos1][pos2][j],len,481,14);
						auxd=clockISCBdiff+atof(auxstr);
						sprintf(&printbufferMODEL[pos1][pos2][j][481],"%14.4f",auxd);
						if (len>496) { //This line length includes the newline at the end
							//There are dual-frequency DCBs, it is not the end of the string
							printbufferMODEL[pos1][pos2][j][495]=' '; //For removing the '\0' added by the sprintf
							for(k=0;k<epoch->measOrder[epoch->sat[i].GNSS].numDualFreqDCBFreqList[epoch->sat[i].PRN];k++) {
								//Change dual frequency DCB model values
								getstr(auxstr,printbufferMODEL[pos1][pos2][j],len,495+k*33+19,14);
								auxd=clockISCBdiff+atof(auxstr);
								sprintf(&printbufferMODEL[pos1][pos2][j][495+k*33+19],"%14.4f",auxd);
								if (k<(epoch->measOrder[epoch->sat[i].GNSS].numDualFreqDCBFreqList[epoch->sat[i].PRN]-1)) {
									printbufferMODEL[pos1][pos2][j][495+k*33+19+14]=' '; //For removing the '\0' added by the sprintf
								}
							}
						}
						//The '\n' has been replace by a '\0' due to the last sprintf
						printbufferMODEL[pos1][pos2][j][len-1]='\n';
					}
				}
			}
		}
	}
	return 0;
} 


/*****************************************************************************
 * Name        : isEpochComputable
 * Description : Check (taking into account the usable satellites) if the 
 *               specified epoch can be computed
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  Reference epoch
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Epoch not computable
 *                                         1 => Epoch computable
 *****************************************************************************/
int isEpochComputable (TEpoch *epoch) {
	if (epoch->usableSatellites>=(4+epoch->numInterSystemClocksFilter)) return 1;
	else return 0;
}

/*****************************************************************************
 * Name        : calculateUnknowns
 * Description : Computes, from the options specified, how many unknowns the 
 *               filter has.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  Reference epoch
 * int obs                         I  N/A  Usable observations
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Number of unknowns in the filter
 *****************************************************************************/
int calculateUnknowns (TEpoch  *epoch, TOptions *options) {
	int	value = 4 + epoch->numInterSystemClocksFilter;

	if (options->estimateAmbiguities==1) value+=epoch->totalNumAmbiguitiesEpoch;
	if (options->estimateTroposphere==1) value++;
	if (options->estimateGLOIFB==1) value++;
	if (options->estimateRecWindUp==1) value++;
	return value;
}

/*****************************************************************************
 * Name        : initUnkinfo
 * Description : Initialises the information for the unknowns of the filter
 * Parameters  :
 * Name                                     |Da|Unit|Description
 * TEpoch  *epoch                             I  N/A  TEpoch structure
 * TUnkinfo  *unkinfo                         O  N/A  TUnkinfo structure to store unknows
 * double  t                                  I  s    Time since last filter run
 * TOptions  *options                         I  N/A  TOptions structure
 *****************************************************************************/
void initUnkinfo (TEpoch  *epoch, TUnkinfo *unkinfo, double t, TOptions *options) {
	int		i,j;
	double 	q;

	unkinfo->nunkvector=m2v_opt(unkinfo->nunk-1,unkinfo->nunk-1)+1;

	//First three positions will be always the position unknowns
	unkinfo->pos2unktype[0]=DR_UNK;
	unkinfo->pos2unktype[1]=DR_UNK;
	unkinfo->pos2unktype[2]=DR_UNK;
	//Fourth position will be always the receiver clock unknow
	unkinfo->pos2unktype[3]=DT_UNK;

	//Coordinates
	unkinfo->par2unk[DR_UNK]=0;
	unkinfo->par2unk[DT_UNK]=3;

	//Reset position for GNSS inter-system clock bias
	for(i=0;i<MAX_GNSS;i++) {
		unkinfo->GNSS2ISCBunk[i]=-1;
	}

	//Reference clock position
	unkinfo->GNSS2ISCBunk[epoch->ReferenceGNSSClock]=3; 
	i=4;


	//Inter-system clock bias
	for(j=0;j<epoch->numInterSystemClocksFilter;j++) {
		if (j==0) {
			unkinfo->par2unk[DT_IS_UNK]=i;
		}
		unkinfo->GNSS2ISCBunk[epoch->InterSystemClocksUnk2GNSS[FIRST_POS_IS_CLK+j]]=i;
		unkinfo->pos2unktype[i]=DT_IS_UNK;
		i++;
	}

	//Troposphere
	if (options->estimateTroposphere==1) {
		unkinfo->par2unk[TROP_UNK]=i;
		unkinfo->pos2unktype[i]=TROP_UNK;
		i++;
	}

	//Receiver WindUp
	if (options->estimateRecWindUp==1) {
		unkinfo->par2unk[WUP_UNK]=i;
		unkinfo->pos2unktype[i]=WUP_UNK;
		i++;
	}

	//Receiver GLONASS IFB
	if (options->estimateGLOIFB==1) {
		unkinfo->par2unk[GLOIFB_UNK]=i;
		unkinfo->pos2unktype[i]=GLOIFB_UNK;
		i++;
	}

	//Ambiguities
	if (options->estimateAmbiguities==1) {
		unkinfo->par2unk[BIAS_UNK]=i;
		i+=epoch->totalNumAmbiguitiesEpoch;
		for(j=unkinfo->par2unk[BIAS_UNK];j<i;j++) {
			unkinfo->pos2unktype[j]=BIAS_UNK;
		}
	}

	
	//Forming PHI and QNOISE matrix (only diagonal)
	//Coordinate values
	if (options->CoordRandWalk==1) {
		q=options->filterParams[Q_PAR][DR_UNK]*t;
		//Set a max value for Q in coordinates to (1E4)^2 to avoid too big Q in the filter (possible inestabilities)
		if (q>(SIGMA_INF_DR*SIGMA_INF_DR)) {
			q=SIGMA_INF_DR*SIGMA_INF_DR;
		}
	} else {
		q=options->filterParams[Q_PAR][DR_UNK];
	}
	for (i=0;i<3;i++) {
		unkinfo->phi[unkinfo->par2unk[DR_UNK]+i] = options->filterParams[PHI_PAR][DR_UNK];
		unkinfo->qnoise[unkinfo->par2unk[DR_UNK]+i] = q;
	}

	//Clock values
	if (options->ClkRandWalk==1) {
		q=options->filterParams[Q_PAR][DT_UNK]*t;
		//Set a max value for Q in coordinates to (1E4)^2 to avoid too big Q in the filter (possible inestabilities)
		if (q>(SIGMA_INF_DT*SIGMA_INF_DT)) {
			q=SIGMA_INF_DT*SIGMA_INF_DT;
		}
	} else {
		q=options->filterParams[Q_PAR][DT_UNK];
	}
	unkinfo->phi[unkinfo->par2unk[DT_UNK]] = options->filterParams[PHI_PAR][DT_UNK];
	unkinfo->qnoise[unkinfo->par2unk[DT_UNK]] = q;

	//Inter-system clock bias
	if (options->ISCBRandWalk==1) {
		q=options->filterParams[Q_PAR][DT_IS_UNK]*t;
		//Set a max value for Q in coordinates to (1E4)^2 to avoid too big Q in the filter (possible inestabilities)
		if (q>(SIGMA_INF_DT*SIGMA_INF_DT)) {
			q=SIGMA_INF_DT*SIGMA_INF_DT;
		}
	} else {
		q=options->filterParams[Q_PAR][DT_IS_UNK];
	}
	for (i=0;i<epoch->numInterSystemClocksFilter;i++) {
		unkinfo->phi[unkinfo->par2unk[DT_IS_UNK]+i] = options->filterParams[PHI_PAR][DT_IS_UNK];
		unkinfo->qnoise[unkinfo->par2unk[DT_IS_UNK]+i] = q;
	}

	//Troposphere
	if (options->estimateTroposphere==1) {
		unkinfo->phi[unkinfo->par2unk[TROP_UNK]] = options->filterParams[PHI_PAR][TROP_UNK];
		unkinfo->qnoise[unkinfo->par2unk[TROP_UNK]] = options->filterParams[Q_PAR][TROP_UNK]*t;
	}

	//Receiver WindUp
	if (options->estimateRecWindUp==1) {
		q=options->filterParams[Q_PAR][WUP_UNK]*t;
		//Set a max value for Q in receiver wind-up to (1E4)^2/3600. to avoid too big Q in the filter (possible inestabilities)
		if (q>(SIGMA_INF_REC_WIND_UP*SIGMA_INF_REC_WIND_UP)) {
			q=SIGMA_INF_REC_WIND_UP*SIGMA_INF_REC_WIND_UP;
		}
		unkinfo->phi[unkinfo->par2unk[WUP_UNK]] = options->filterParams[PHI_PAR][WUP_UNK];
		unkinfo->qnoise[unkinfo->par2unk[WUP_UNK]] = q;
	}

	//Receiver GLONASS IFB
	if (options->estimateGLOIFB==1) {
		unkinfo->phi[unkinfo->par2unk[GLOIFB_UNK]] = options->filterParams[PHI_PAR][GLOIFB_UNK];
		unkinfo->qnoise[unkinfo->par2unk[GLOIFB_UNK]] = options->filterParams[Q_PAR][GLOIFB_UNK];
	}

	//Ambiguities
	if (options->estimateAmbiguities==1) {
		for (i=0;i<epoch->totalNumAmbiguitiesEpoch;i++) {
			unkinfo->phi[unkinfo->par2unk[BIAS_UNK]+i] = options->filterParams[PHI_PAR][BIAS_UNK];
			unkinfo->qnoise[unkinfo->par2unk[BIAS_UNK]+i] = options->filterParams[Q_PAR][BIAS_UNK];
		}
	}
}

/*****************************************************************************
 * Name        : prepareCorrelation
 * Description : Updates the correlations for the solution computation
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      IO N/A  Structure containing the filter 
 *                                         information of the previous epoch
 * enum GNSSystem *GNSSlist        I  N/A  List of satellite constellations of the previous epoch
 * int  *PRNlist                   I  N/A  List of satellites of the previous epoch
 * TUnkinfo  *unkinfo              I  N/A  TUnkinfo structure with information on 
 *                                         the current epoch unknowns
 * TUnkinfo  *prevUnkinfo          I  N/A  TUnkinfo structure with information on 
 *                                         the previous epoch unknowns
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  0 -> Could not invert correlation matrix
 *                                         1 -> Everything OK
 *****************************************************************************/
int prepareCorrelation (TEpoch *epoch, TFilterSolution *solution, enum GNSSystem *GNSSlist, int *PRNlist, TUnkinfo *unkinfo, TUnkinfo *prevUnkinfo, TOptions *options) {
	int						i,j,alti,altj,k,l,m,n;
	int						new2oldSat[MAX_SATELLITES_VIEWED];
	int						new2oldParam[FIRST_POS_IS_CLK+MAX_GNSS+3]; //Only used for parameters (troposphere, GLONASS IFB and Receiver Wind-Up)
	int						prevNumSatellites;
	int						lastPosIndex,posPrevAmb;
	int						new,found,res;
	int						ind,indPrev;
	int						refClockChanged=0;
	static enum GNSSystem	AmbPos2GNSS[MAX_AMBIGUITIES_FILTER]; 		//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static int				new2oldSatAmb[MAX_SATELLITES_VIEWED*MAX_AMBIGUITIES_FILTER];	//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static int				AmbPos2PRN[MAX_AMBIGUITIES_FILTER]; 		//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static int				AmbPos2NumAmbSat[MAX_AMBIGUITIES_FILTER];	//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static int				numParameters=0;
	enum GNSSystem			GNSScurr;
	static double			updatedCorrelations[MAX_VECTOR_UNK]; 	//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static double			updatedParameterValues[MAX_UNK];		//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)

	double					Initcorrelation;

	prevNumSatellites=solution->prevNumSatellites;

	// Check for FIRST time
	if (prevNumSatellites==0) {
		//Loop to initialize covariance for all coordinates
		for (i=0;i<3;i++) {
			solution->correlations[m2v_opt(unkinfo->par2unk[DR_UNK]+i,unkinfo->par2unk[DR_UNK]+i)] = options->filterParams[P0_PAR][DR_UNK];
		}
		//Initialize receiver clock
		solution->correlations[m2v_opt(unkinfo->par2unk[DT_UNK],unkinfo->par2unk[DT_UNK])] = options->filterParams[P0_PAR][DT_UNK];
		//Initialize inter-system bias (the ones available in current epoch)
		for (i=0;i<epoch->numInterSystemClocksFilter;i++) {
			solution->correlations[m2v_opt(unkinfo->par2unk[DT_IS_UNK]+i,unkinfo->par2unk[DT_IS_UNK]+i)] = options->filterParams[P0_PAR][DT_IS_UNK];
		}
		//Initialize Troposphere
		if (options->estimateTroposphere==1) {
			solution->correlations[m2v_opt(unkinfo->par2unk[TROP_UNK],unkinfo->par2unk[TROP_UNK])] = options->filterParams[P0_PAR][TROP_UNK];
		}
		//Initialize GLONASS IFB
		if (options->estimateGLOIFB==1) { 
			solution->correlations[m2v_opt(unkinfo->par2unk[GLOIFB_UNK],unkinfo->par2unk[GLOIFB_UNK])] = options->filterParams[P0_PAR][GLOIFB_UNK]; 
		} 
		//Initialize Receiver Wind-Up
		if (options->estimateRecWindUp==1) { 
			solution->correlations[m2v_opt(unkinfo->par2unk[WUP_UNK],unkinfo->par2unk[WUP_UNK])] = options->filterParams[P0_PAR][WUP_UNK];
		} 
		//Initialize Ambiguities
		if (options->estimateAmbiguities==1) {
			for (i=0;i<epoch->totalNumAmbiguitiesEpoch;i++) {
				solution->correlations[m2v_opt(unkinfo->par2unk[BIAS_UNK]+i,unkinfo->par2unk[BIAS_UNK]+i)] = options->filterParams[P0_PAR][BIAS_UNK];
			}
		}
		//Initialize prevUnkinfo the first time by copying the current unkinfo
		TUnkinfoPartialCopy(prevUnkinfo,unkinfo);

		numParameters=options->estimateTroposphere+options->estimateGLOIFB+options->estimateRecWindUp;
	}

	// Vector new2oldSat will have the dictionary from new PRN positions to previous PRN positions
	lastPosIndex=0;
	n=0;
	for (l=0;l<epoch->usableSatellites;l++) {
		i=epoch->usedSat2DataPos[l];
		new2oldSat[l]=-1;
		for(m=0;m<options->numfilterCarrierPhaseMeas[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN];m++) {
			n=lastPosIndex+m;
			//Save the positions of the ambiguities, so they can be restored for satellites which are back in
			AmbPos2GNSS[n]=epoch->sat[i].GNSS;
			AmbPos2PRN[n]=epoch->sat[i].PRN;
			AmbPos2NumAmbSat[n]=m;
			new2oldSatAmb[n]=-1;
		}
		k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
		posPrevAmb=0;
		for (j=0;j<prevNumSatellites;j++) {
			if ( GNSSlist[j] == epoch->sat[i].GNSS && PRNlist[j] == epoch->sat[i].PRN && epoch->sat[i].available &&
				 epoch->cycleslip.anyOutlier[k] == 0 && epoch->cycleslip.hasBeenCycleslip[k] == 0 ) {
				new2oldSat[l]=j;
				for(m=0;m<options->numfilterCarrierPhaseMeas[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN];m++) {
					new2oldSatAmb[lastPosIndex+m]=posPrevAmb+m;
				}
				break;
			}
			posPrevAmb+=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSSlist[j]][PRNlist[j]];
		}
		if ( epoch->cycleslip.hasBeenCycleslip[k] != 0 ) {
			epoch->cycleslip.hasBeenCycleslip[k] = 0; // clear cycle slip flag
		}
		lastPosIndex+=options->numfilterCarrierPhaseMeas[ROVERPOS][epoch->sat[i].GNSS][epoch->sat[i].PRN];

	}


	//Get index positions for parameters
	if (numParameters>0) {
		if (options->estimateTroposphere==1) {
			new2oldParam[unkinfo->par2unk[TROP_UNK]]=prevUnkinfo->par2unk[TROP_UNK];
		}

		if (options->estimateGLOIFB==1) { //GLONASS IFB (to be revised)
			new2oldParam[unkinfo->par2unk[GLOIFB_UNK]]=prevUnkinfo->par2unk[GLOIFB_UNK];
		}

		if (options->estimateRecWindUp==1) { //Receiver Wind Up (to be revised)
			new2oldParam[unkinfo->par2unk[WUP_UNK]]=prevUnkinfo->par2unk[WUP_UNK];
		}
	}

	// Updating parameters
	for (i=0;i<prevUnkinfo->nunk;i++) {
		solution->parameters[i] *= prevUnkinfo->phi[i];
	}

	if (prevNumSatellites!=0) { // If not in the first epoch
	
		// Updating correlations (including Phi and Q)
		for (i=0;i<prevUnkinfo->nunk;i++) {
			for (j=i;j<prevUnkinfo->nunk;j++) {
				solution->correlations[m2v_opt_inv(i,j)] *= prevUnkinfo->phi[i]*prevUnkinfo->phi[j];
			}
			solution->correlations[m2v_opt(i,i)] += prevUnkinfo->qnoise[i];
		}

		// Update position parameters
		for(i=0,j=prevUnkinfo->par2unk[DR_UNK];i<3;i++,j++) {
			solution->parameters[j] = solution->x[j] - epoch->receiver.aproxPosition[i];
		}
		// Update tropospheric parameter
		if (options->estimateTroposphere) {
			//Tropospheric parameter may not be in the same position due to constellations appearing/disappearing
			j = prevUnkinfo->par2unk[TROP_UNK];
			solution->parameters[j] =  solution->x[j] - epoch->ZTD;
		}

		//For receiver Wind-up, check that epoch is not repeated
		if (options->estimateRecWindUp) {
			j = prevUnkinfo->par2unk[WUP_UNK];
			if (epoch->IterationInSameEpoch) {
				//When iterating in the same epoch, the wind-up has to be the same as the computed in the previous epoch,
				//not the one computed in the previous iteration
				solution->parameters[j] = epoch->lastRecWindUpEstimated;
				solution->correlations[m2v_opt(j,j)] = epoch->lastRecWindUpAutoCorrel;
			} else {
				//Save value so it can be reused in iterations
				epoch->lastRecWindUpEstimated = solution->parameters[j];
				epoch->lastRecWindUpAutoCorrel = solution->correlations[m2v_opt(j,j)];
			}
		}

		if (epoch->ReferenceGNSSClock!=epoch->prevReferenceGNSSClock) {
			//Reference clock changed. Reset inter system clock biases
			refClockChanged=1;						
			for (i=0;i<MAX_GNSS;i++) {
				ind = prevUnkinfo->GNSS2ISCBunk[i];
				if (ind!=-1) {
					solution->correlations[m2v_opt(ind,ind)] = options->filterParams[P0_PAR][DT_IS_UNK];
				}
			}
		} else {
			//Inter system clock biases from a constellation that dissappears will be decorrelated
			//by setting a huge value to self-correlation (Po for clocks is big enough)
			for (i=0;i<MAX_GNSS;i++) { 
				if (i==epoch->ReferenceGNSSClock) continue; //If it is the reference clock, skip it
				if(unkinfo->GNSS2ISCBunk[i]!=prevUnkinfo->GNSS2ISCBunk[i]) {
					//Values differ. The constellation appeared or disappeared
					if (unkinfo->GNSS2ISCBunk[i]==-1) {
						//Constellation disappeared. Set the sigma to high value
						ind = prevUnkinfo->GNSS2ISCBunk[i];
						solution->correlations[m2v_opt(ind,ind)] = options->filterParams[P0_PAR][DT_IS_UNK];
					}
				}
			}
		}

		l=0;
		m=0;
		for (j=0;j<prevNumSatellites;j++) {
			found = 0;
			for (i=0;i<epoch->usableSatellites;i++) {
				if (new2oldSat[i]==j) {
					found = 1;
					break;
				}
			}
			if (!found) {
				// Satellite ambiguities that have disappeared or that have had a cycle-slip will be decorrelated from the
				// rest of ambiguities by putting an infinite in its self-correlation
				if (options->estimateAmbiguities) {
					//Loop through all ambiguities that the satellite has (which may differ from other satellites).
					//Before removing the value, save the computed ambiguity value and its autocorrelation
					for(k=0;k<options->numfilterCarrierPhaseMeas[ROVERPOS][GNSSlist[j]][PRNlist[j]];k++) {
						ind = prevUnkinfo->par2unk[BIAS_UNK]+l+k;
						if (epoch->satHasBeenUsedInFilter[GNSSlist[j]][PRNlist[j]]==1) {
							epoch->lastAmbValEstimatedNotInFilter[GNSSlist[j]][PRNlist[j]][k]=solution->parameters[ind];
							epoch->lastAmbCorEstimatedNotInFilter[GNSSlist[j]][PRNlist[j]][k]=solution->correlations[m2v_opt(ind,ind)];
						}
						solution->correlations[m2v_opt(ind,ind)] = options->filterParams[P0_PAR][BIAS_UNK];
					}
				}
			}
			l+=options->numfilterCarrierPhaseMeas[ROVERPOS][GNSSlist[j]][PRNlist[j]];
			m+=epoch->numSatDCBEpoch[GNSSlist[j]][PRNlist[j]];
		}
	}
	
	// Inverting correlation matrix from the former epoch
	res = cholinv_opt(solution->correlations,prevUnkinfo->nunk);
	if (res==-1) {
		sprintf(messagestr,"Skipping epoch %s due to correlation matrix could not be inverted\n",epoch->tSoDHourStr);
		printInfo(messagestr,options);
		return 0;
	}
	
	// Creating new correlation matrix
	for (i=0;i<unkinfo->nunk;i++) {
		switch(unkinfo->pos2unktype[i]) {
			case BIAS_UNK:
				//Ambiguiites
				if (new2oldSatAmb[i-unkinfo->par2unk[BIAS_UNK]]!=-1) {
					updatedParameterValues[i] = solution->parameters[prevUnkinfo->par2unk[BIAS_UNK]+new2oldSatAmb[i-unkinfo->par2unk[BIAS_UNK]]];
				} else {
					//updatedParameterValues[i] = 0;
					updatedParameterValues[i] = epoch->lastAmbValEstimatedNotInFilter[AmbPos2GNSS[i-unkinfo->par2unk[BIAS_UNK]]][AmbPos2PRN[i-unkinfo->par2unk[BIAS_UNK]]][AmbPos2NumAmbSat[i-unkinfo->par2unk[BIAS_UNK]]];
				}
				break;
			case DR_UNK:
				//Coordinates
				updatedParameterValues[i] = solution->parameters[i];
				break;
			case DT_IS_UNK:	
				//Inter-system clock bias
				GNSScurr=epoch->InterSystemClocksUnk2GNSS[i];
				indPrev=epoch->prevInterSystemClocksUnk[GNSScurr];
				if (indPrev==-1) {
					//Current constellation was not in previous epoch. 
					updatedParameterValues[i] = 0;
				} else {
					updatedParameterValues[i] = solution->parameters[indPrev];
				}
				break;
			case DT_UNK:
				//Receiver clock
				if (refClockChanged==1) {
					updatedParameterValues[i] = 0;
				} else {
					updatedParameterValues[i] = solution->parameters[i];
				}
				break;
			case TROP_UNK: case WUP_UNK: case GLOIFB_UNK:
				//Troposphere, GLONASS IFB and receiver Wind-Up
				updatedParameterValues[i] = solution->parameters[new2oldParam[i]];
				break;
			default:
				break;
		}
		for (j=i;j<unkinfo->nunk;j++) {
			new=0;
			switch(unkinfo->pos2unktype[i]) {
				case BIAS_UNK:	
					//Ambiguiites
					if (new2oldSatAmb[i-unkinfo->par2unk[BIAS_UNK]]==-1) {
						new=1;
						//Initcorrelation=1./options->filterParams[P0_PAR][BIAS_UNK];
						Initcorrelation=1./(epoch->lastAmbCorEstimatedNotInFilter[AmbPos2GNSS[i-unkinfo->par2unk[BIAS_UNK]]][AmbPos2PRN[i-unkinfo->par2unk[BIAS_UNK]]][AmbPos2NumAmbSat[i-unkinfo->par2unk[BIAS_UNK]]]);
					} else { 
						alti = prevUnkinfo->par2unk[BIAS_UNK]+new2oldSatAmb[i-unkinfo->par2unk[BIAS_UNK]]; 
					}
					break;
				case DR_UNK:
					//Coordinates
					alti=i;
					break;
				case DT_IS_UNK:
					//Inter-system clock bias
					GNSScurr=epoch->InterSystemClocksUnk2GNSS[i];
					indPrev=epoch->prevInterSystemClocksUnk[GNSScurr];
					if (indPrev==-1) {
						new=1;
						Initcorrelation=1./options->filterParams[P0_PAR][DT_IS_UNK];
					} else {
						alti=indPrev;
					}
					break;
				case DT_UNK:
					//Receiver clock
					if (refClockChanged==1) {
						new=1;
						Initcorrelation=1./options->filterParams[P0_PAR][DT_UNK];
					} else {
						alti=i;
					}
					break;
				case TROP_UNK: case WUP_UNK: case GLOIFB_UNK:
					//Troposphere, GLONASS IFB and receiver Wind-Up
					alti=new2oldParam[i];
					break;
				default:
					break;
			}
			switch(unkinfo->pos2unktype[j]) {
				case BIAS_UNK:
					//Ambiguiites
					if (new2oldSatAmb[j-unkinfo->par2unk[BIAS_UNK]]==-1) {
						new=1;
						//Initcorrelation=1./options->filterParams[P0_PAR][BIAS_UNK];
						Initcorrelation=1./(epoch->lastAmbCorEstimatedNotInFilter[AmbPos2GNSS[j-unkinfo->par2unk[BIAS_UNK]]][AmbPos2PRN[j-unkinfo->par2unk[BIAS_UNK]]][AmbPos2NumAmbSat[j-unkinfo->par2unk[BIAS_UNK]]]);
					} else { 
						altj = prevUnkinfo->par2unk[BIAS_UNK]+new2oldSatAmb[j-unkinfo->par2unk[BIAS_UNK]]; 
					}
					break;
				case DR_UNK:
					//Coordinates
					altj=j;
					break;
				case DT_IS_UNK:
					//Inter-system clock bias
					GNSScurr=epoch->InterSystemClocksUnk2GNSS[j];
					indPrev=epoch->prevInterSystemClocksUnk[GNSScurr];
					if (indPrev==-1) {
						new=1;
						Initcorrelation=1./options->filterParams[P0_PAR][DT_IS_UNK];
					} else {
						altj=indPrev;
					}
					break;
				case DT_UNK:
					//Receiver clock
					if (refClockChanged==1) {
						new=1;
						Initcorrelation=1./options->filterParams[P0_PAR][DT_UNK];
					} else {
						altj=j;
					}
					break;
				case TROP_UNK: case WUP_UNK: case GLOIFB_UNK:
					//Troposphere, GLONASS IFB and receiver Wind-Up
					altj=new2oldParam[j];
					break;
				default:
					break;
			}
			//After obtaining the previous correlation (or the reseted one, if not found), apply it the new correlation matrix
			if (new) {
				if (i==j) updatedCorrelations[m2v_opt(i,j)] = Initcorrelation;
				else updatedCorrelations[m2v(i,j)] = 0.;
			} else {
				updatedCorrelations[m2v(i,j)] = solution->correlations[m2v(alti,altj)];
			}
		}
	}

	memcpy(solution->correlations,updatedCorrelations,sizeof(double)*unkinfo->nunkvector);
	memcpy(solution->parameters,updatedParameterValues,sizeof(double)*unkinfo->nunk);


	return 1;
}

/*****************************************************************************
 * Name        : atwa_atwy_insertline
 * Description : Insert an equation (prefilter values and design vector) into 
 *               the AtWA matrix and AtWY vector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *restrict atwa          IO N/A  At*W*A matrix
 * double  *restrict atwy          IO N/A  At*W*Y vector
 * const double  *restrict unk     I  N/A  Design vector
 * const double  prefit            I  N/A  Prefit value
 * const int  nunk                 I  N/A  Number of unknowns
 * const double  sigma2            I  N/A  Sigma^2 associated with the prefit
 *****************************************************************************/
void atwa_atwy_insertline (double *restrict atwa, double *restrict atwy, const double *restrict unk, const double prefit, const int nunk, const double sigma2) {

	for (register int j=0;j<nunk;j++) {
		atwy[j] = atwy[j] + unk[j]*prefit/sigma2;
		for (register int k=0;k<=j;k++) {
			atwa[m2v_opt_inv(k,j)] += unk[j]*unk[k]/sigma2;
		}
	}
}

/*****************************************************************************
 * Name        : atwa_atwy_insertLineWithCorrelation
 * Description : Similar to atwa_atwy_insert for apriori values (with a full 
 *               correlations vector)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *restrict atwa          IO N/A  At*W*A matrix
 * double  *restrict atwy          IO N/A  At*W*Y vector
 * const double  *restrict corr    I  N/A  Correlations vector
 * const double  apriorivalue      I  N/A  Apriori value (equivalent to prefit)
 * const int  nunk                 I  N/A  Number of unknowns
 * const double  multiplier        I  N/A  Multiplier in the Fi matrix (equivalent
 *                                         to the design vector)
 * const int  iniunk               I  N/A  Initial unk to start updating
 *****************************************************************************/
void atwa_atwy_insertLineWithCorrelation (double *restrict atwa, double *restrict atwy, const double *restrict corr, const double apriorivalue, const int nunk, const double multiplier, const int iniunk) {

	register int 	i;
	double 			aux=multiplier*apriorivalue;
	double 			multiplier2=multiplier*multiplier;

	for (i=0;i<nunk;i++) {
		atwy[i] += aux*corr[i];
	}

	for (i=iniunk;i<nunk;i++) {
		atwa[m2v_opt_inv(iniunk,i)] += multiplier2*corr[i];
	}
}

/*****************************************************************************
 * Name        : designSystem
 * Description : Designs the system for a specific measurement marked in the filter.
 *               Computes At*W*A and At*W*Y for the specified epoch 
 * Parameters  :
 * Name                                |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  TEpoch structure
 * double  *atwa                        IO N/A  At*W*A matrix
 * double  *atwy                        IO N/A  At*W*Y vector
 * TUnkinfo  *unkinfo                   I  N/A  Structure containing the information of
 *                                              the unknowns 
 * double *prefits                      O  m    Vector with the prefits
 * double *weights	                    O  m    Vector with the measurement weights
 * int computeStanfordESA               I  N/A  Flag to indicate if Stanford-ESA has to be computed
 *                                                0 -> Stanford-ESA not computed
 *                                                1 -> Stanford-ESA computed
 * TConstellation  *constellationPrint  I  N/A  Constellation information of the products (for printing)
 * TOptions  *options                   I  N/A  TOptions structure
 *****************************************************************************/
void designSystem (TEpoch *epoch, double *atwa, double *atwy, TUnkinfo *unkinfo, double **G, double *prefits, double *weights, int computeStanfordESA, TConstellation *constellationPrint, TOptions *options) {

	int						i, j, k, l , m=0;
	int						ret;
	int						printPrefits;
	int						measPos;
	int						satUsedWithAnyMeas;
	int						numAmbiguity=0;
	int						printType;
	int						usedSats=-1;
	int						freq;
	static double			unk[MAX_UNK]; //Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	double					prefit, measurement, model;
	double					weight;
	double					stdDev;
	double					smoothWith;
	double					lambda;
	double					sign;
	double					DCBSigma;
	TSatellite				*sat;

	//Initiliaze counters
	epoch->numSatSolutionFilter=0;
	epoch->numSatNotUsedFilter=0;
	for(i=0;i<MAX_GNSS;i++) {
		epoch->numSatSolutionGNSS[i]=0;
		epoch->numSatnotUsedGNSS[i]=0;
	}
	if (options->printSatellites==1) {
		if (epoch->numMeasAllGNSSIndexed>epoch->maxNumMeasAllGNSSIndexed) {
			//The '+10' is to provide extra space so the number times required to perform the realloc is reduced
			epoch->numSatsMeasUsed=realloc(epoch->numSatsMeasUsed,sizeof(int*)*(epoch->numMeasAllGNSSIndexed+10));
			epoch->numSatsMeasUnused=realloc(epoch->numSatsMeasUnused,sizeof(int*)*(epoch->numMeasAllGNSSIndexed+10));
			epoch->PRNMeasUsed=realloc(epoch->PRNMeasUsed,sizeof(int*)*(epoch->numMeasAllGNSSIndexed+10));
			epoch->PRNMeasUnused=realloc(epoch->PRNMeasUnused,sizeof(int*)*(epoch->numMeasAllGNSSIndexed+10));
			for(i=epoch->maxNumMeasAllGNSSIndexed;i<(epoch->numMeasAllGNSSIndexed+10);i++) {
				epoch->numSatsMeasUsed[i]=NULL;
				epoch->numSatsMeasUsed[i]=malloc(sizeof(int)*MAX_GNSS);
				epoch->numSatsMeasUnused[i]=NULL;
				epoch->numSatsMeasUnused[i]=malloc(sizeof(int)*MAX_GNSS);
				epoch->PRNMeasUsed[i]=NULL;
				epoch->PRNMeasUsed[i]=malloc(sizeof(int*)*MAX_GNSS);
				epoch->PRNMeasUnused[i]=NULL;
				epoch->PRNMeasUnused[i]=malloc(sizeof(int*)*MAX_GNSS);
				for(j=0;j<MAX_GNSS;j++) {
					epoch->PRNMeasUsed[i][j]=NULL;
					epoch->PRNMeasUsed[i][j]=malloc(sizeof(int)*MAX_SATELLITES_PER_GNSS);
					epoch->PRNMeasUnused[i][j]=NULL;
					epoch->PRNMeasUnused[i][j]=malloc(sizeof(int)*MAX_SATELLITES_PER_GNSS);
				}
			}
			epoch->maxNumMeasAllGNSSIndexed=epoch->numMeasAllGNSSIndexed+10;
		}
		//Initialize counters
		for(i=0;i<epoch->numMeasAllGNSSIndexed;i++) {
			for(j=0;j<MAX_GNSS;j++) {
				epoch->numSatsMeasUsed[i][j]=0;
				epoch->numSatsMeasUnused[i][j]=0;
			}
		}
	}

	for (i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		k = epoch->satCSIndex[sat->GNSS][sat->PRN];
		satUsedWithAnyMeas=0;
		
		for (j=0;j<options->numfilterMeasList[ROVERPOS][sat->GNSS][sat->PRN];j++) {

			if (options->filterListAllMeasSelected[ROVERPOS][sat->GNSS][sat->PRN][j]!=MEASSELECTED) continue;

			ret = getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j], options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&measurement, &model,j);

			if (ret!=1) {
				sat->available = 0;
				model = 0.;
				measurement = 0.;
				smoothWith = 0.;
				prefit = 0.;
			}
			// Smoothing
			if ( options->smoothEpochs != 0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][j] == 1 ) {
				ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][j],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&smoothWith,NULL,0);
				if (ret!=1) {
					sat->available = 0;
					model = 0.;
					smoothWith = 0.;
					prefit = 0.;
				} else {
					measurement = epoch->cycleslip.smoothedMeas[k][j] + smoothWith;
					prefit = measurement - model;
				}
			} else {
				prefit = measurement - model;
				smoothWith = 0.;
			}
			lambda=epoch->measOrder[sat->GNSS].filterMeaslambda[sat->PRN][j];

			// Compute weights and available satellites
			if ( sat->available ) {
				stdDev = sat->measurementWeights[j];
				if (satUsedWithAnyMeas==0) usedSats++;
				satUsedWithAnyMeas=1;

				//Add satellite to the list of used satellites with current measurement
				if (options->printSatellites==1) {
					//Check if satellite had all its measurements selected. If there are still
					//pending measurements to select, the index of the measurement position (measPos) 
					//will not have been built (but it may have selected part of the necessary measurements)
					if (options->MeasSelected[ROVERPOS][sat->GNSS][sat->PRN]==MEASSELECTED) {
						measPos=epoch->MeasPosAllGNSS2PrintPos[sat->GNSS][sat->PRN][j];
						epoch->PRNMeasUsed[measPos][sat->GNSS][epoch->numSatsMeasUsed[measPos][sat->GNSS]]=sat->PRN;
						epoch->numSatsMeasUsed[measPos][sat->GNSS]++;
					}
				}
				//Set printPrefit value
				printPrefits=options->printPrefit;
			} else {
				// Satellite not counted for number of satellites
				stdDev = SIGMA_INF;
				//Add satellite to the list of unused satellites with current measurement
				if (options->printSatellites==1) {
					//Check if satellite had all its measurements selected. If there are still
					//pending measurements to select, the index of the measurement position (measPos) 
					//will not have been built (but it may have selected part of the necessary measurements)
					if (options->MeasSelected[ROVERPOS][sat->GNSS][sat->PRN]==MEASSELECTED) {
						measPos=epoch->MeasPosAllGNSS2PrintPos[sat->GNSS][sat->PRN][j];
						epoch->PRNMeasUnused[measPos][sat->GNSS][epoch->numSatsMeasUnused[measPos][sat->GNSS]]=sat->PRN;
						epoch->numSatsMeasUnused[measPos][sat->GNSS]++;
					}
				}
				//Set printPrefit value
				printPrefits=options->printPrefit*options->printPrefitUnsel;
				if (!isfinite(measurement)) {
					//For GLONASS, when frequency factors are missing, they are set on both frequencies to 1,
					//which will create a division by 0 when computing the iono-free combination
					model = 0.;
					measurement = 0.;
					smoothWith = 0.;
					prefit = 0.;
				}
			}
			weight = stdDev * stdDev;
		
			freq=options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0];
			
			// Print prefit residuals
			if (printPrefits) {
				printPrefit(epoch,i,j,k,freq,prefit,measurement,smoothWith,lambda,model,stdDev,constellationPrint,options);
			}


			if (sat->available) {

				sign=1.;

				// unk vector is the a row of the design matrix
				for (l=0;l<unkinfo->nunk;l++) unk[l]=0;

				// Position unknowns
				unk[unkinfo->par2unk[DR_UNK]] = -sat->LoS[0];
				unk[unkinfo->par2unk[DR_UNK]+1] = -sat->LoS[1];
				unk[unkinfo->par2unk[DR_UNK]+2] = -sat->LoS[2];

				if (computeStanfordESA==1) {
					G[m][0] = cos ( epoch->sat[i].elevation ) * sin ( epoch->sat[i].azimuth ) ;
					G[m][1] = cos ( epoch->sat[i].elevation ) * cos ( epoch->sat[i].azimuth ) ;
					G[m][2] = sin ( epoch->sat[i].elevation ) ;
					G[m][3] = 1;
					for(l=0;l<epoch->numInterSystemClocksFilter;l++) {
						//Set all inter system clock bias to 0
						G[m][l+4]=0;
					}
					//Set the inter system clock bias of current constellation to 1 
					if (unkinfo->GNSS2ISCBunk[sat->GNSS]!=-1) {
						G[m][unkinfo->GNSS2ISCBunk[sat->GNSS]]=1;
					}

					prefits[m]=prefit;
					weights[m]=weight;
					m++;
				}

				// Time unknown
				unk[unkinfo->par2unk[DT_UNK]] = 1;

				//Set inter-system clock bias of current constellation to 1
				if (unkinfo->GNSS2ISCBunk[sat->GNSS]!=-1) {
					unk[unkinfo->GNSS2ISCBunk[sat->GNSS]]=1;
				}

				// Troposphere unknown
				if (options->estimateTroposphere) {
					unk[unkinfo->par2unk[TROP_UNK]] = sat->tropWetMap;
				}

				//GLONASS IFB unknown (to be revised)
				if (options->estimateGLOIFB==1) {
					if (sat->GNSS==GLONASS) { 
						if ( options->filterMeasfreq[ROVERPOS][GLONASS][sat->PRN][j][0]==1  || options->filterMeasfreq[ROVERPOS][GLONASS][sat->PRN][j][0]==2 ) {
							//Compute IFB only for GLONASS FDMA signals (frequencies 1 and 2)
							unk[unkinfo->par2unk[GLOIFB_UNK]] = epoch->GLOfreqnumber[sat->PRN]; //to be revised
						}
					}
				}

				//Phase only terms
				if (options->filterMeasKind[ROVERPOS][sat->GNSS][sat->PRN][j]==CarrierPhase) {
					sign=-1.;
					// Carrier-phase ambiguities unknowns
					if (options->estimateAmbiguities==1) {
						unk[unkinfo->par2unk[BIAS_UNK]+numAmbiguity] = 1;
						numAmbiguity++;
					}
					//Receiver wind-up unknown
					if (options->estimateRecWindUp==1) {
						unk[unkinfo->par2unk[WUP_UNK]] = lambda;
					}
				}

				//Ionosphere unknown (carrier phase has ionosphere with opposite sign in respect to pseudorange)
				if (options->estimateIono==1) {
					unk[unkinfo->par2unk[IONO_UNK]+usedSats] = sign*epoch->measOrder[sat->GNSS].TECU2metres[freq][sat->PRN];
				}

				//Satellite DCB unknown (carrier phase has satellite DCB with opposite sign in respect to pseudorange)
				if (options->estimateSatDCB==1) {
					unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][j]] = sign*epoch->measOrder[sat->GNSS].TECU2metres[freq][sat->PRN];
				}

				//Receiver DCB unknown (carrier phase has receiver DCB with opposite sign in respect to pseudorange)
				if (options->estimateRecDCB==1) {
					unk[unkinfo->par2unk[RECDCB_UNK]+epoch->filterMeasPosToRecDCBlistPos[sat->GNSS][sat->PRN][j]] = sign*epoch->measOrder[sat->GNSS].TECU2metres[freq][sat->PRN];
				}
					
				
				// Insert the data in atwa and atwy 
				atwa_atwy_insertline(atwa,atwy,unk,prefit,unkinfo->nunk,weight);
			}

		} //End for (j=0;j<options->numfilterMeasList[ROVERPOS][sat->GNSS][sat->PRN];j++)
		if (satUsedWithAnyMeas==1) {
			//Satellite has been used with any measurement, add it to the list of satellite used (for all measurements)
			epoch->listPRNSatSolutionConst[sat->GNSS][epoch->numSatSolutionGNSS[sat->GNSS]]=sat->PRN;
			epoch->listPRNSatSolution[epoch->numSatSolutionFilter]=sat->PRN;
			epoch->listGNSSsatSolution[epoch->numSatSolutionFilter]=gnsstype2char(sat->GNSS);
			epoch->listGNSSsatSolutionEnum[epoch->numSatSolutionFilter]=sat->GNSS;
			epoch->numSatSolutionGNSS[sat->GNSS]++;
			epoch->numSatSolutionFilter++;

			if (options->FastPPP==1) {
				//Link satellite DCB
				for (l=0;l<unkinfo->nunk;l++) unk[l]=0;
				unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][options->IFRefMeasPos[sat->GNSS][sat->PRN][0]]]=1;
				unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][options->IFRefMeasPos[sat->GNSS][sat->PRN][1]]]=-1;
				atwa_atwy_insertline(atwa,atwy,unk,0,unkinfo->nunk,1E-4); //1E-4 is 1centiTECU squared (DCBs are estimated in TECU, so DCB weights are in TECU)

				//Set satellite DCB value constraint
				for (l=0;l<unkinfo->nunk;l++) unk[l]=0;
				unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][options->IFRefMeasPos[sat->GNSS][sat->PRN][0]]]=1;
				//sat->DCBsigma is in m*(Hz)^2, we have to convert to it to metres and then to TECUs
				DCBSigma=sat->DCBSigma/(epoch->measOrder[sat->GNSS].freqMeas[options->IFRefMeasFreqUsed[sat->GNSS][sat->PRN][0]][sat->PRN]*epoch->measOrder[sat->GNSS].freqMeas[options->IFRefMeasFreqUsed[sat->GNSS][sat->PRN][0]][sat->PRN]*epoch->measOrder[sat->GNSS].TECU2metres[options->IFRefMeasFreqUsed[sat->GNSS][sat->PRN][0]][sat->PRN]);
				atwa_atwy_insertline(atwa,atwy,unk,0,unkinfo->nunk,DCBSigma*DCBSigma); 

				//Set Iono value constraint
				for (l=0;l<unkinfo->nunk;l++) unk[l]=0;
				unk[unkinfo->par2unk[IONO_UNK]+usedSats]=1;
				atwa_atwy_insertline(atwa,atwy,unk,0,unkinfo->nunk,sat->ionoSigma*sat->ionoSigma); 


			} else if (options->estimateSatDCB==1) {
				//Link satellite DCB
				for (l=0;l<unkinfo->nunk;l++) unk[l]=0;
				unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][options->IFRefMeasPos[sat->GNSS][sat->PRN][0]]]=1;
				unk[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][options->IFRefMeasPos[sat->GNSS][sat->PRN][1]]]=-1;
				atwa_atwy_insertline(atwa,atwy,unk,0,unkinfo->nunk,1E-4); //1E-4 is 1centiTECU squared (DCBs are estimated in TECU, so DCB weights are in TECU)
			}

		} else {
			//Satellite has not been used with any measurement, add it to the list of satellites not used (for all measurements)
			epoch->listPRNSatnotUsedConst[sat->GNSS][epoch->numSatnotUsedGNSS[sat->GNSS]]=sat->PRN;
			epoch->listPRNSatnotUsed[epoch->numSatNotUsedFilter]=sat->PRN;
			epoch->listGNSSsatnotUsed[epoch->numSatNotUsedFilter]=gnsstype2char(sat->GNSS);
			epoch->listGNSSsatnotUsedEnum[epoch->numSatSolutionFilter]=sat->GNSS;
			epoch->numSatnotUsedGNSS[sat->GNSS]++;
			epoch->numSatNotUsedFilter++;
		}

	}
	//Link receiver DCB
	if (options->estimateRecDCB==1) {
		for(i=0;i<epoch->numConstellationsUsed;i++) {
			for (l=0;l<unkinfo->nunk;l++) unk[l]=0;
			unk[unkinfo->par2unk[RECDCB_UNK]+epoch->RecDCBPosToLink[epoch->constellationUsedList[i]][0]]=1;
			unk[unkinfo->par2unk[RECDCB_UNK]+epoch->RecDCBPosToLink[epoch->constellationUsedList[i]][1]]=-1;
			atwa_atwy_insertline(atwa,atwy,unk,0,unkinfo->nunk,1E-4); //1E-4 is 1centiTECU squared (DCBs are estimated in TECU, so DCB weights are in TECU)
		}
	}


	if (options->printSatellites) {
		//Print list of satellites for each measurement used in the filter
		for(i=0;i<epoch->numMeasAllGNSSIndexed;i++) {
			printType=epoch->printTypeAllGNSSAllIndexed[i];
			printEpochsat(epoch, printType, epoch->MeasStrAllGNSSIndexed[i], epoch->MeasStrSmoothAllGNSSIndexed[i], epoch->numSatsMeasUsed[i], epoch->PRNMeasUsed[i], epoch->numSatsMeasUnused[i], epoch->PRNMeasUnused[i], options);
		}

		//Print list of satellites for all measurements (version v5 and older did not print this line)
		if (options->printV5format==0) {
			printEpochsatAllSat(epoch);
		}
	}
}




/*****************************************************************************
 * Name        : designSystemIniValues
 * Description : Updates the filter with the information of the former epoch 
 *               (initial values for the current one)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *atwa                   IO N/A  At*W*A matrix
 * double  *atwy                   IO N/A  At*W*Y vector
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of
 *                                         the unknowns 
 * TFilterSolution  *solution      I  N/A  Structure with the information of the 
 *                                         solution of the previous epoch
 *****************************************************************************/
void designSystemIniValues (double *restrict atwa, double *restrict atwy, const TUnkinfo *unkinfo, const TFilterSolution *solution) {
	int					i,j;
	static double		corr[MAX_UNK]; //Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)

	for (i=0;i<unkinfo->nunk;i++) {
		for (j=0;j<i;j++) {
			corr[j]=solution->correlations[m2v_opt(i,j)];
		}
		for (;j<unkinfo->nunk;j++) {
			corr[j]=solution->correlations[m2v_opt_inv(i,j)];
		}
		atwa_atwy_insertLineWithCorrelation(atwa,atwy,corr,solution->parameters[i],unkinfo->nunk,1,i);
	}
}

/*****************************************************************************
 * Name        : calculatePostfits
 * Description : Calculate and print the postfits after the filtering process
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  TEpoch structure
 * double  *solution                    I  N/A  Solution of the filter
 * TUnkinfo  *unkinfo                   I  N/A  Structure containing the information of
 *                                              the unknowns
 * TOptions  *options                   I  N/A  TOptions structure
 * TConstellation  *constellationPrint  I  N/A  Constellation information of the products (for printing)
 * Returned value (double)              O  m    Standard deviation of the postfits
 *****************************************************************************/
double calculatePostfits (TEpoch *epoch, double *solution, TUnkinfo *unkinfo, TConstellation *constellationPrint, TOptions *options) {

	int			i,j,k,l;
	int			ret;
	int 		usedSats=-1;
	int			numMeasurements=0;
	int			numAmbiguity=0;
	double		stddev2postfit=0;
	double		postfit;
	double		measurement,model;
	double		estimatedParameters;
	double		geometricCorrection;
	double		smoothWith;
	double		InterSystemClock;
	double		ambiguity,Iono,satDCB,recDCB;
	double		lambda;
	double		sign;
	TSatellite	*sat;

	for (i=0;i<epoch->numSatellites;i++) {

		sat = &epoch->sat[i];

		if (sat->available==0) continue;
		
		usedSats++;

		k = epoch->satCSIndex[sat->GNSS][sat->PRN];

		for (j=0;j<options->numfilterMeasList[ROVERPOS][sat->GNSS][sat->PRN];j++) {

			if (options->filterListAllMeasSelected[ROVERPOS][sat->GNSS][sat->PRN][j]!=MEASSELECTED) continue;			

			sign=1.;
			
			//Receiver clock
			estimatedParameters = solution[unkinfo->par2unk[DT_UNK]];

			//Inter-system clock bias
			if (sat->GNSS!=epoch->ReferenceGNSSClock && options->GNSSclockSource[epoch->ReferenceGNSSClock][sat->GNSS]==ClkSrcCalculate) {
				InterSystemClock = solution[unkinfo->GNSS2ISCBunk[sat->GNSS]];
				estimatedParameters += InterSystemClock;
			} else {
				InterSystemClock = 0.;
			
			}
			//Coordinates
			geometricCorrection = 0;
			for (l=0;l<3;l++) {
				geometricCorrection += -sat->LoS[l]*solution[unkinfo->par2unk[DR_UNK]+l];
			}
			estimatedParameters += geometricCorrection;

			//Troposphere
			if(options->estimateTroposphere) {
				estimatedParameters += sat->tropWetMap * solution[unkinfo->par2unk[TROP_UNK]];
			}
			//GLONASS IFB unknown (to be revised)
			if (options->estimateGLOIFB==1) {
				if (sat->GNSS==GLONASS && (options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]==1  || options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]==2)) {
					estimatedParameters += epoch->GLOfreqnumber[sat->PRN]*solution[unkinfo->par2unk[GLOIFB_UNK]];
				}
			}

			//Phase only terms
			if(options->filterMeasKind[ROVERPOS][sat->GNSS][sat->PRN][j]==CarrierPhase) {
				sign=-1;
				//Carrier phase ambiguities unknowns
				if (options->estimateAmbiguities==1) {
					ambiguity = solution[unkinfo->par2unk[BIAS_UNK]+numAmbiguity];
					estimatedParameters += ambiguity;
					numAmbiguity++;
				} else {
					ambiguity = 0.;
				}
				//Receiver wind-up unknown (to be revised)
				if (options->estimateRecWindUp==1) {
					lambda=epoch->measOrder[sat->GNSS].filterMeaslambda[sat->PRN][j];
					estimatedParameters += lambda*solution[unkinfo->par2unk[WUP_UNK]];
				}
			} else {
				ambiguity = 0.;
			}

			//Ionosphere unknown
			if (options->estimateIono==1) {
				//Iono = sign*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN]*solution[unkinfo->par2unk[IONO_UNK]+usedSats];
				Iono = sign*solution[unkinfo->par2unk[IONO_UNK]+usedSats];
				estimatedParameters += Iono*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN];
			} else {
				Iono=0.;
			}

			//Satellite DCB unknown
			if (options->estimateSatDCB==1) {
				//satDCB = sign*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN]*solution[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][j]];
				satDCB = sign*solution[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToSatDCBlistPos[sat->GNSS][sat->PRN][j]];
				estimatedParameters += satDCB*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN];
			} else {
				satDCB=0.;
			}
			
			//Receiver DCB unknown
			if (options->estimateSatDCB==1) {
				//recDCB = sign*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN]*solution[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToRecDCBlistPos[sat->GNSS][sat->PRN][j]];
				recDCB = sign*solution[unkinfo->par2unk[SATDCB_UNK]+epoch->filterMeasPosToRecDCBlistPos[sat->GNSS][sat->PRN][j]];
				estimatedParameters += recDCB*epoch->measOrder[sat->GNSS].TECU2metres[options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j][0]][sat->PRN];
			} else {
				recDCB=0.;
			}

			ret = getMeasModelValue(epoch, sat->GNSS, sat->PRN, options->filterMeasList[ROVERPOS][sat->GNSS][sat->PRN][j], options->filterMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&measurement, &model,j);
			// Smoothing
			if (options->smoothEpochs!=0 && options->filterMeasSmoothed[ROVERPOS][sat->GNSS][sat->PRN][j]!=NA) {
				ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->filterSmoothMeasList[ROVERPOS][sat->GNSS][sat->PRN][j],options->filterSmoothMeasfreq[ROVERPOS][sat->GNSS][sat->PRN][j],&smoothWith,NULL,0);
				if (ret!=1) {
					sat->available = 0;
					model = 0.;
					smoothWith = 0.;
					epoch->cycleslip.smoothedMeas[k][j] = 0.0;
				}
				postfit = epoch->cycleslip.smoothedMeas[k][j] + smoothWith - (model + estimatedParameters);
			} else {
				postfit = measurement - (model + estimatedParameters);
				smoothWith = 0.;
			}
			
			printPostfit(epoch, i, j, k, postfit, measurement, smoothWith, model, estimatedParameters, InterSystemClock, ambiguity, Iono, satDCB, recDCB, constellationPrint, options);

			stddev2postfit += postfit*postfit;
			numMeasurements++;
		}
	}
	stddev2postfit /= numMeasurements;
	return stddev2postfit;
}

/*****************************************************************************
 * Name        : computeSolution
 * Description : Obtain the filter solution for the specified epoch
 * Parameters  :
 * Name                                |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  TEpoch structure
 * double  *stddev2postfit              O  m    Standard deviation of the postfits
 * TFilterSolution  *solution           IO N/A  Structure with the information of the 
 *                                              solution of the previous epoch (it is 
 *                                              updated with the solution of the present epoch)
 * double  *newcorrelations             O  N/A  Correlations after the filter run
 * double  *newparameters               O  N/A  Parameters after the filter run
 * TUnkinfo  *unkinfo                   I  N/A  Structure containing the information of
 *                                              the unknowns
 * TStdESA *StdESA                      O  N/A  TStdESA struct
 * TConstellation  *constellationPrint  I  N/A  Constellation information of the products (for printing)
 * TOptions  *options                   I  N/A  TOptions structure
 * Returned value (int)                 O  N/A  Status of the function
 *                                              0 => Problem in the matrix inversion
 *                                              1 => Solution found
 *****************************************************************************/
int computeSolution (TEpoch *epoch, double *stddev2postfit, TFilterSolution *solution, double *newcorrelations, double *newparameterValues, TUnkinfo *unkinfo, TStdESA *StdESA, TConstellation *constellationPrint, TOptions *options) {

	static double	atwa[MAX_VECTOR_UNK];				//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static double	atwy[MAX_UNK]; 						//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static double	prefits[MAX_FILTER_MEASUREMENTS]; 	//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	static double	weights[MAX_FILTER_MEASUREMENTS];	//Declared as static to store it in the static memory, as its size may be too large for the stack (and it avoids to do malloc/free)
	int 			i,j;
	int				res;
	int				computeStanfordESA=0;
	char			epochString[100];

	if (options->stanfordesa==1 && options->useDatasummary>=1) {
		computeStanfordESA=1;
	}

	//Resize G matrix if needed
	if(computeStanfordESA==1) {
		//Check values for G matrix
		if (epoch->usableSatellites>StdESA->numUsablesSatellites) {
			//Current iteration uses more satellites than any other previous epoch
			//The '+20' is to provide extra space so the number times required to perform the realloc is reduced
			StdESA->G=realloc(StdESA->G,sizeof(double *)*(epoch->usableSatellites+20));
			for(i=StdESA->numUsablesSatellites;i<(epoch->usableSatellites+20);i++) {
				//Each position will be sized with 4+MAX_GNSS, which is the maximum size possible of XYZ + dt + inter-system clock bias
				StdESA->G[i]=malloc(sizeof(double)*(4+MAX_GNSS));
			}
			StdESA->numUsablesSatellites=epoch->usableSatellites+20;
		}
	}


	// Initializing At*W*A and At*W*Y
	memset(atwy,0,sizeof(double)*unkinfo->nunk);
	memset(atwa,0,sizeof(double)*unkinfo->nunkvector);
	
	// Forming At*W*A and At*W*Y
	designSystem(epoch,atwa,atwy,unkinfo,StdESA->G,prefits,weights,computeStanfordESA,constellationPrint,options);

	designSystemIniValues(atwa,atwy,unkinfo,solution);

	res = cholinv_opt(atwa,unkinfo->nunk);

	if (res==-1) {
		sprintf(messagestr,"Skipping epoch %s due to design matrix with correlations could not be inverted\n",epoch->tSoDHourStr);
		printInfo(messagestr,options);
		return 0;
	}
	
	mxv(atwa,atwy,unkinfo->nunk);


	// Updating correlations
	for (i=0;i<unkinfo->nunk;i++) {
		for (j=0;j<=i;j++) {
			newcorrelations[m2v(i,j)] = atwa[m2v(i,j)];
		}
	}
		
	memcpy(newparameterValues,atwy,sizeof(double)*unkinfo->nunk);

	// Building solution vector
	for (i=0;i<unkinfo->nunk;i++) {
		solution->x[i] = atwy[i];
	}
	for (i=0;i<3;i++) {
		solution->x[unkinfo->par2unk[DR_UNK]+i] = epoch->receiver.aproxPosition[i] + atwy[unkinfo->par2unk[DR_UNK]+i];
	}

	// Postfit calculation
	if (options->printPostfit) {
		*stddev2postfit = calculatePostfits(epoch,atwy,unkinfo,constellationPrint,options);
	}

	//Add zenith tropospheric delay. It has to be added after postfit calculation, so only the estimated residual is added to the model
	if (options->estimateTroposphere) solution->x[unkinfo->par2unk[TROP_UNK]] += epoch->ZTD;

	// Formal Error Calculation
	solution->dop=0;

	for (i=0;i<3;i++) {
		solution->dop += atwa[m2v_opt(unkinfo->par2unk[DR_UNK]+i,unkinfo->par2unk[DR_UNK]+i)];
	}
	solution->dop = sqrt(solution->dop);

	//Compute Stanford-ESA plots
	if(computeStanfordESA) {
		//Resize k and kmask if needed
		if (epoch->numSatSolutionFilter>StdESA->numSatSolutionFilter) {
			//The '+20' is to provide extra space so the number times required to perform the realloc is reduced
			StdESA->k=realloc(StdESA->k,sizeof(int)*(epoch->numSatSolutionFilter+1+20));
			StdESA->kmask=realloc(StdESA->kmask,sizeof(int)*(epoch->numSatSolutionFilter+1+20));
			StdESA->numSatSolutionFilter=epoch->numSatSolutionFilter+20;
		}
		StdESA->k[0]=0;
		for(i=0;i<=epoch->numSatSolutionFilter;i++) {
			StdESA->kmask[i]=1;
		}
		//Save epoch in printable format (Year/Doy/SoD - GPSWeek/SoW) in string, so it is not needed to
		//be done at each iteration of the Stanford-ESA
		if (options->printV5format==0) {
			sprintf(epochString,"%29s    %4d %9.2f",epoch->tSoDHourStr,epoch->GPSweek,epoch->SoW);
		} else {
			sprintf(epochString,"%17s    %4d %9.2f",epoch->tStr,epoch->GPSweek,epoch->SoW);
		}
		if (epoch->numConstellationsUsed==1 || epoch->numInterSystemClocksFilter==0 ) {
			StanfordESAComputationRecursiveSingleConst(epoch,epochString,StdESA->k,StdESA->kmask,epoch->numSatSolutionFilter,0,StdESA->G,prefits,weights,unkinfo,StdESA,options);
		} else {
			StanfordESAComputationRecursiveMultiConst(epoch,epochString,StdESA->k,StdESA->kmask,epoch->numSatSolutionFilter,0,epoch->numInterSystemClocksFilter,StdESA->G,prefits,weights,unkinfo,StdESA,options);
		}
	}

	return 1;
}

/*****************************************************************************
 * Name        : calculateDOP
 * Description : Computes the Dilution of Precision of the current epoch  
 *               obtain the solution (only for the used satellites)
 *               It also checks that DOP requirements are met
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      I  N/A  Structure with the information of the 
 *                                         solution of the previous epoch (it is 
 *                                         updated with the solution of the present epoch)
 * char *errorstr                  O  N/A  String explaining which DOP was not met
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  -1  => Any of the matrix GtG,GtG_NEU,GtWG are not invertible
 *                                         -2  => DOP requirements not met
 *                                          1  => Everything OK 
 *                                          2  => Protection levels over alarm limits
 *****************************************************************************/
int calculateDOP (TEpoch *epoch, TFilterSolution *solution, char *errorstr, TOptions *options) {
	int		i,j,k;
	int		res;
	int		RowMatrixSize=4+epoch->numInterSystemClocksFilter;
	int		VectorGSize=m2v_opt(RowMatrixSize-1,RowMatrixSize-1)+1;
	double	dmajor, weight;
	double	RowMatrixG_NEU[RowMatrixSize], RowMatrixG_XYZ[RowMatrixSize];
	double	VectorGtG_NEU[VectorGSize], VectorGtG_XYZ[VectorGSize], FalsePrefit[RowMatrixSize];
	double	VectorGtWG_NEU[VectorGSize];

	// Initialise Variables
	solution->GDOP = 0.0; solution->PDOP = 0.0; solution->TDOP = 0.0; solution->VPL = 0.0;
	solution->HDOP = 0.0; solution->VDOP = 0.0; solution->HPL = 0.0;

	for ( j = 0; j < RowMatrixSize; j++ )	{RowMatrixG_NEU[j] = 0.0; RowMatrixG_XYZ[j] = 0.0; FalsePrefit[j] = 0.0;}
	for ( j = 0; j < VectorGSize; j++ )		{VectorGtG_NEU[j] = 0.0; VectorGtG_XYZ[j] = 0.0; VectorGtWG_NEU[j] = 0.0;}

	// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
	for ( k = 0; k < epoch->usableSatellites; k++ ) {
		i = epoch->usedSat2DataPos[k];
		RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
		RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
		RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
		RowMatrixG_NEU[3] = 1;

		RowMatrixG_XYZ[0] = epoch->sat[i].LoS[0];
		RowMatrixG_XYZ[1] = epoch->sat[i].LoS[1];
		RowMatrixG_XYZ[2] = epoch->sat[i].LoS[2];
		RowMatrixG_XYZ[3] = 1;

		//First set all inter system values to 0
		for(j=4;j<RowMatrixSize;j++) {
			RowMatrixG_NEU[j] = 0;
			RowMatrixG_XYZ[j] = 0;
		}
		//Set for the current constellation its inter system clock to 1 (for GPS, it will set again the position 3 (clock) to 1)
		RowMatrixG_NEU[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1; 	
		RowMatrixG_XYZ[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1;

		atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, RowMatrixSize, 1.0);
		atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, 1.0);

		weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
		atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, weight);
	}

	epoch->TryGEOChange=0;		//Reset flag for changing GEO (can be for DOP, singular matrix or protection levels over alarm limits)
	epoch->overMaxHDOP=epoch->overMaxPDOP=epoch->overMaxGDOP=epoch->overMaxHDOPorPDOP=0; //Reset flag for DOP thresholds

	// Invert the Gt*G Matrixes:
	res=cholinv_opt(VectorGtG_NEU, RowMatrixSize);
	if(res==-1) {
		epoch->TryGEOChange=1;
		sprintf(errorstr,"Geometry with singular matrix");
		return -1;
	}
	res=cholinv_opt(VectorGtG_XYZ, RowMatrixSize);
	if(res==-1) {
		epoch->TryGEOChange=1;
		sprintf(errorstr,"Geometry with singular matrix");
		return -1;
	}

	// Compute DOPs
	solution->HDOP = sqrt(VectorGtG_NEU[0] + VectorGtG_NEU[2]);
	solution->VDOP = sqrt(VectorGtG_NEU[5]);
	//solution->GDOP = sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5] + VectorGtG_XYZ[9]);
	solution->GDOP = VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5] + VectorGtG_XYZ[9];
	solution->PDOP = sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5]);
	//solution->TDOP = sqrt(VectorGtG_XYZ[9]);
	solution->TDOP = VectorGtG_XYZ[9];
	for(i=0;i<epoch->numInterSystemClocksFilter;i++) {
		j=m2v_opt(4+i,4+i);
		solution->TDOP+=VectorGtG_XYZ[j];
		solution->GDOP+=VectorGtG_XYZ[j];
	}
	solution->TDOP=sqrt(solution->TDOP);
	solution->GDOP=sqrt(solution->GDOP);



	//HDOPorPDOP flag is disabled if any HDOP or PDOP is disabled
	if(options->HDOPorPDOP==1) {
		if (solution->HDOP>=options->maxHDOP && solution->PDOP>=options->maxPDOP) {
			epoch->TryGEOChange=1;
			epoch->overMaxHDOPorPDOP=1;
			sprintf(errorstr,"HDOP (%.2f) and PDOP (%.2f) are over their thresholds (%.2f / %.2f)",solution->HDOP,solution->PDOP,options->maxHDOP,options->maxPDOP);
		}
		if(options->GDOPthreshold==1) {
			if(solution->GDOP>=options->maxGDOP) {
				epoch->overMaxGDOP=1;
				if (epoch->TryGEOChange==1) {
					sprintf(errorstr,"HDOP (%.2f), PDOP (%.2f) and GDOP (%.2f) are over their thresholds (%.2f / %.2f / %.2f)",solution->HDOP,solution->PDOP,solution->GDOP,options->maxHDOP,options->maxPDOP,options->maxGDOP);
				} else {
					epoch->TryGEOChange=1;
					sprintf(errorstr,"GDOP (%.2f) is over the threshold (%.2f)",solution->GDOP,options->maxGDOP);
				}
			}
		}
		if (epoch->TryGEOChange==1) {
			return -2;
		}
	} else {
		if(options->HDOPthreshold==1) {
			if(solution->HDOP>=options->maxHDOP) {
				epoch->TryGEOChange=1;
				epoch->overMaxHDOP=1;
				sprintf(errorstr,"HDOP (%.2f) is over the threshold (%.2f)",solution->HDOP,options->maxHDOP);
			}
		}
		if(options->PDOPthreshold==1) {
			if(solution->PDOP>=options->maxPDOP) {
				epoch->TryGEOChange=1;
				epoch->overMaxPDOP=1;
				sprintf(errorstr,"PDOP (%.2f) is over the threshold (%.2f)",solution->PDOP,options->maxPDOP);
			}
		}
		if(options->GDOPthreshold==1) {
			if(solution->GDOP>=options->maxGDOP) {
				epoch->TryGEOChange=1;
				epoch->overMaxGDOP=1;
				sprintf(errorstr,"GDOP (%.2f) is over the threshold (%.2f)",solution->GDOP,options->maxGDOP);
			}
		}
		if (epoch->TryGEOChange==1) {
			if ((epoch->overMaxHDOP+epoch->overMaxPDOP+epoch->overMaxGDOP)==3) {
				//All DOPs over threshold
				sprintf(errorstr,"HDOP (%.2f), PDOP (%.2f) and GDOP (%.2f) are over their thresholds (%.2f / %.2f / %.2f)",solution->HDOP,solution->PDOP,solution->GDOP,options->maxHDOP,options->maxPDOP,options->maxGDOP);
			} else if (epoch->overMaxHDOP==1 && epoch->overMaxPDOP==1) {
				//HDOP and PDOP over threshold
				sprintf(errorstr,"HDOP (%.2f) and PDOP (%.2f) are over their thresholds (%.2f / %.2f)",solution->HDOP,solution->PDOP,options->maxHDOP,options->maxPDOP);
			} else if (epoch->overMaxHDOP==1 && epoch->overMaxGDOP==1) {
				//HDOP and GDOP over threshold
				sprintf(errorstr,"HDOP (%.2f) and GDOP (%.2f) are over their thresholds (%.2f / %.2f)",solution->HDOP,solution->GDOP,options->maxHDOP,options->maxGDOP);
			} else if (epoch->overMaxPDOP==1 && epoch->overMaxGDOP==1) {
				//PDOP and GDOP over threshold
				sprintf(errorstr,"PDOP (%.2f) and GDOP (%.2f) are over their thresholds (%.2f / %.2f)",solution->PDOP,solution->GDOP,options->maxPDOP,options->maxGDOP);
			}
			return -2;
		}
	}

	// Compute protection level for SBAS only if SBAS is selected
	if ( options->SBAScorrections>=SBAS1Fused ) {
		cholinv_opt(VectorGtWG_NEU, RowMatrixSize);
		if(res==-1) {
			epoch->TryGEOChange=1;
			sprintf(errorstr,"Geometry with singular matrix");
			return -1;
		}
		dmajor = sqrt(0.5 * (VectorGtWG_NEU[2] + VectorGtWG_NEU[0]) + sqrt(0.25 * pow(VectorGtWG_NEU[2] - VectorGtWG_NEU[0], 2) + VectorGtWG_NEU[1] * VectorGtWG_NEU[1]));

		solution->HPL = options->kfactor[options->precisionapproach][KHORPOS] * dmajor;
		solution->VPL = options->kfactor[options->precisionapproach][KVERPOS] * sqrt(VectorGtWG_NEU[5]);

		if (solution->HPL>=options->HorAlarmLimit || solution->VPL>=options->VerAlarmLimit) {
			epoch->TryGEOChange=1;
		}
	}
	return 1;
}

/*****************************************************************************
 * Name        : StanfordESAComputationRecursiveSingleConst
 * Description : Recursive function to compute all the possible navigation
 *               solution with all geometries for Stanford-ESA plot.
 *               It only works with a single constellation, as there is no
 *               check for inter-system clock bias term (therefore it is 
 *               faster than the multi-constellation version of this function)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * char *epochString               I  N/A  String with date in format Year DoY SoD GPSWeek SoW
 * int *restrict k                 IO N/A  Vector indicating the current combination number for a given depth
 * int *restrict kmask             IO N/A  Vector indicating if a satellite (a row of data)
 *                                           is selected (1) or not (0) for current combination
 * const int numsat                I  N/A  Number of satellites available for computing SBAS solution
 * const int depth                 IO N/A  Number of satellites excluded in current combination (until 4 satellites are left)
 * double **restrict G             I  N/A  Geometry matrix (in NEU) of the satellites used in SBAS solution
 * const double *restrict prefits  I    m  Vector with the prefits of the satellites used in SBAS solution
 * const double *restrict weights  I  m^-2 Vector with the weights of the satellites used in SBAS solution
 *                                         solution of the previous epoch (it is 
 *                                         updated with the solution of the present epoch)
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of the unknowns
 * TStdESA *StdESA                 O  N/A  TStdESA struct                                        
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void StanfordESAComputationRecursiveSingleConst (TEpoch *epoch, char *epochString, int *restrict k, int *restrict kmask, const int numsat, const int depth, double **restrict G, const double *restrict prefits, const double *restrict weights, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions  *options) {
	int						i;
	int						res1=-1;
	int						nunkvector,nunk;
	int						availSat;
	int						strpos=0;
	unsigned long long int	posx,posy; //Declared as long long int to avoid overflow when PE or PL are very high
	double					dmajor,HPL,VPL,Herror,Verror;
	static double			Vector_GtY[MAX_UNK_STFDESA];
	#pragma omp threadprivate(Vector_GtY)
	static double			Vector_GtWG[MAX_VECTOR_UNK_STFDESA];
	#pragma omp threadprivate(Vector_GtWG)
	double					HIR,VIR,quantError,quantPL;
	char					strmask[300];

	availSat=numsat-depth;

	if (availSat<=options->stanfordesaMaxNumSat) {
		nunk=4;
		nunkvector=m2v_opt(nunk-1,nunk-1)+1;	

		//Initialize matrix data
		memset(Vector_GtY,0,nunk*sizeof(double));
		memset(Vector_GtWG,0,nunkvector*sizeof(double));

		//Increase counter for number of samples
		StdESA->numsamplesProcessed++;

		for(i=0;i<numsat;i++) {
			if(kmask[i]==1) {
				atwa_atwy_insertline(Vector_GtWG,Vector_GtY,G[i],prefits[i],nunk,weights[i]);
			}
		}	

		res1=cholinv_opt(Vector_GtWG,nunk);

		if(res1==0) {
			dmajor=sqrt(0.5*(Vector_GtWG[2]+Vector_GtWG[0])+sqrt(0.25*pow(Vector_GtWG[2]-Vector_GtWG[0],2)+Vector_GtWG[1]*Vector_GtWG[1]));
			
			HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(Vector_GtWG[5]);

			mxv(Vector_GtWG,Vector_GtY,nunk);
		
			Herror=sqrt(Vector_GtY[0]*Vector_GtY[0]+Vector_GtY[1]*Vector_GtY[1]);
			Verror=fabs(Vector_GtY[2]);

			//Increase counter for number of samples
			StdESA->numsamplesComputed++;

			if(Herror>=HPL || Verror>=VPL) {
				StdESA->numsamplesMI++;
			}

			if(Herror>=HPL) {
				StdESA->numsamplesHMI++;
			}

			if(Verror>=VPL) {
				StdESA->numsamplesVMI++;
			}

		} else {
			//Singular matrix not positive defined
			strmask[0]='\0';
			for(i=0;i<numsat;i++) {
				if(kmask[i]==1) {
					strpos+=sprintf(&strmask[strpos],"%c%02d ",epoch->listGNSSsatSolution[i],epoch->listPRNSatSolution[i]);
				}
			}
			sprintf(messagestr,"%29s Geometry with singular matrix in Stanford-ESA computation when using %d satellites, with satellites %s",epoch->tSoDHourStr,availSat,strmask);
			printInfo(messagestr,options);
			StdESA->numsamplesSingular++;
		}

	}
	if(availSat>4) {
		for(i=k[depth];i<=(availSat-1);i++) {
			k[depth+1]=i;
			kmask[i+depth]=0;
			StanfordESAComputationRecursiveSingleConst(epoch,epochString,k,kmask,numsat,depth+1,G,prefits,weights,unkinfo,StdESA,options);
			kmask[i+depth]=1;
		}
	}

	if(res1==0) {
		
		HIR=Herror/HPL;
		VIR=Verror/VPL;
		//Save worst horizontal integrity ratio
		if(HIR>StdESA->HWIR) {
			StdESA->HWIR=HIR;
		}

		//Save worst vertical integrity ratio
		if(VIR>StdESA->VWIR) {
			StdESA->VWIR=VIR;
		}

		//Locate pixel position in grid and add 1 to the number of ocurrencies in that pixel
		//Horizontal error grid
		posx=(unsigned long long int)(Herror/StdESA->xstep);
		posy=(unsigned long long int)(HPL/StdESA->ystep);
		quantError=(double)(posx)*StdESA->xstep;
		quantPL=(double)(posy)*StdESA->ystep;
		if(posx>=(StdESA->numpixelhor-1)) {
			if((HPL-Herror)>0.) {
				//It is not an MI. Put in position StdESA->numpixelhor-2 to avoid
				//confusing it with an MI point
				posx=StdESA->numpixelhor-2;
			} else {
				posx=StdESA->numpixelhor-1;
			}
		}
        if( (HPL-Herror)>0. && quantError>=quantPL ) {
            //After quantized, the error is equal or greater than the protection level but it is not an MI
            //The quantization value of the protection level has to be moved over the error,
            //so there is no MI shown when the plots are done
            if(StdESA->ystep==StdESA->xstep) {
                //Steps are equal. Set posy value one postion above posx to make it greater
                posy=posx+1;
            } else {
                //Vertical step is different. Convert the quantized error value with the vertical step and add 1
                posy=(unsigned long long int)(quantError/StdESA->ystep)+1;
            }
        }
		if(posy>=StdESA->numpixelver) posy=StdESA->numpixelver-1;
		StdESA->counthor[posy][posx]+=1;
		//Vertical error grid
		posx=(unsigned long long int)(Verror/StdESA->xstep);
		posy=(unsigned long long int)(VPL/StdESA->ystep);
		quantError=(double)(posx)*StdESA->xstep;
		quantPL=(double)(posy)*StdESA->ystep;
		if(posx>=(StdESA->numpixelhor-1)) {
			if((VPL-Verror)>0.) {
				//It is not an MI. Put in position StdESA->numpixelhor-2 to avoid
				//confusing it with an MI point
				posx=StdESA->numpixelhor-2;
			} else {
				posx=StdESA->numpixelhor-1;
			}
		}
        if( (VPL-Verror)>0. && quantError>=quantPL ) {
            //After quantized, the error is equal or greater than the protection level but it is not an MI
            //The quantization value of the protection level has to be moved over the error,
            //so there is no MI shown when the plots are done
            if(StdESA->ystep==StdESA->xstep) {
                //Steps are equal. Set posy value one postion above posx to make it greater
                posy=posx+1;
            } else {
                //Vertical step is different. Convert the quantized error value with the vertical step and add 1
                posy=(unsigned long long int)(quantError/StdESA->ystep)+1;
            }
        }
		if(posy>=StdESA->numpixelver) posy=StdESA->numpixelver-1;
		StdESA->countver[posy][posx]+=1;

		if( options->stanfordesaLOI == 1) {
			//Write to file if any horizontal or vertical integrity ratio are over the thresholds
			if(HIR>=options->WIRHorThreshold || VIR>=options->WIRVerThreshold ) {
				//Get the list of satellites
				strmask[0]='\0';
				for(i=0;i<numsat;i++) {
					if(kmask[i]==1) {
						strpos+=sprintf(&strmask[strpos],"%c%02d ",epoch->listGNSSsatSolution[i],epoch->listPRNSatSolution[i]);
					}
				}
				//Write to file
				fprintf(options->fdstdESALOI," %s %7.4f %7.4f %9.2f %9.2f %9.2f %9.2f %9.4f %9.4f %8d %7d %s\n",epochString,options->WIRHorThreshold,options->WIRVerThreshold,Herror,Verror,HPL,VPL,HIR,VIR,numsat,availSat,strmask);
			}

		}
	}
}

/*****************************************************************************
 * Name        : StanfordESAComputationRecursiveMultiConst
 * Description : Recursive function to compute all the possible navigation
 *               solution with all geometries for Stanford-ESA plot.
 *               It supports multi-constellations (it checks for the
 *               inter-system clock bias)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * char *epochString               I  N/A  String with date in format Year DoY SoD GPSWeek SoW
 * int *k                          IO N/A  Vector indicating the current combination number for a given depth
 * int *kmask                      IO N/A  Vector indicating if a satellite (a row of data)
 *                                           is selected (1) or not (0) for current combination
 * const int numsat                I  N/A  Number of satellites available for computing SBAS solution
 * const int depth                 I  N/A  Number of satellites excluded in current combination (until 4 satellites are left)
 * int numInterSystemClocks        I  N/A  Number of inter-system clock bias in the current combination
 * double **restrict G             I  N/A  Geometry matrix (in NEU) of the satellites used in SBAS solution
 * const double *restrict prefits  I    m  Vector with the prefits of the satellites used in SBAS solution
 * const double *restrict weights  I  m^-2 Vector with the weights of the satellites used in SBAS solution
 *                                         solution of the previous epoch (it is 
 *                                         updated with the solution of the present epoch)
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of the unknowns
 * TStdESA *StdESA                 O  N/A  TStdESA struct                                        
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void StanfordESAComputationRecursiveMultiConst (TEpoch *epoch, char *epochString, int *restrict k, int *restrict kmask, const int numsat, const int depth, int numInterSystemClocks, double **restrict G, const double *restrict prefits, const double *restrict weights, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions  *options) {
	int						i,j;
	int						res1=-1;
	int						nunkvector,nunk;
	int						availSat;
	int						constUsedandHasInterSystemClockBias[MAX_GNSS]={0,0,0,0,0,0,0};
	int						strpos=0;
	unsigned long long int	posx,posy; //Declared as long long int to avoid overflow when PE or PL are very high
	double					dmajor,HPL,VPL,Herror,Verror;
	static double			Vector_GtY[MAX_UNK_STFDESA];
	#pragma omp threadprivate(Vector_GtY)
	static double			Vector_GtWG[MAX_VECTOR_UNK_STFDESA];
	#pragma omp threadprivate(Vector_GtWG)
	double					HIR,VIR,quantError,quantPL;
	char					strmask[300];

	availSat=numsat-depth;

	nunk=4+numInterSystemClocks;
	if (availSat<=options->stanfordesaMaxNumSat) {
		nunkvector=m2v_opt(nunk-1,nunk-1)+1;

		//Initialize matrix data
		memset(Vector_GtY,0,nunk*sizeof(double));
		memset(Vector_GtWG,0,nunkvector*sizeof(double));

		//Increase counter for number of samples
		StdESA->numsamplesProcessed++;

		for(i=0;i<numsat;i++) {
			if(kmask[i]==1) {
				atwa_atwy_insertline(Vector_GtWG,Vector_GtY,G[i],prefits[i],nunk,weights[i]);
			}
		}	

		res1=cholinv_opt(Vector_GtWG,nunk);

		if(res1==0) {
			dmajor=sqrt(0.5*(Vector_GtWG[2]+Vector_GtWG[0])+sqrt(0.25*pow(Vector_GtWG[2]-Vector_GtWG[0],2)+Vector_GtWG[1]*Vector_GtWG[1]));
			
			HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(Vector_GtWG[5]);

			mxv(Vector_GtWG,Vector_GtY,nunk);
		
			Herror=sqrt(Vector_GtY[0]*Vector_GtY[0]+Vector_GtY[1]*Vector_GtY[1]);
			Verror=fabs(Vector_GtY[2]);

			//Increase counter for number of samples
			StdESA->numsamplesComputed++;

			if(Herror>=HPL || Verror>=VPL) {
				StdESA->numsamplesMI++;
			}

			if(Herror>=HPL) {
				StdESA->numsamplesHMI++;
			}

			if(Verror>=VPL) {
				StdESA->numsamplesVMI++;
			}

		} else {
			//Singular matrix not positive defined
			for(i=0;i<numsat;i++) {
				if(kmask[i]==1) {
					//sprintf(auxstr,"%s%c%02d ",strmask,epoch->listConsSatSolutionSBAS[i],epoch->listPRNSatSolutionSBAS[i]);
					strpos+=sprintf(&strmask[strpos],"%c%02d ",epoch->listGNSSsatSolution[i],epoch->listPRNSatSolution[i]);
				}
			}
			sprintf(messagestr,"%29s Geometry with singular matrix in Stanford-ESA computation when using %d satellites, with satellites %s",epoch->tSoDHourStr,availSat,strmask);
			printInfo(messagestr,options);
			StdESA->numsamplesSingular++;
		}
	}

	if(availSat>nunk) {
		for(i=k[depth];i<=(availSat-1);i++) {
			k[depth+1]=i;
			kmask[i+depth]=0;
			//Check if there are enough satellites taking into account inter-system clock bias
			for(j=0;j<numsat;j++) {
				if (kmask[j]==1) {
					constUsedandHasInterSystemClockBias[epoch->listGNSSsatSolutionEnum[j]]=epoch->hasInterSystemClocksUnk[epoch->listGNSSsatSolutionEnum[j]];
				}
			}
			numInterSystemClocks=0; 
			for(j=0;j<MAX_GNSS;j++) {
				numInterSystemClocks+=constUsedandHasInterSystemClockBias[j];
			}
			//The following line is equivalent to 'if ((availSat-1)>=(4+numInterSystemClocks))'. We have disabled one satellite, so available satellites is availSat-1 
			if (availSat>=(5+numInterSystemClocks)) {
				StanfordESAComputationRecursiveMultiConst(epoch,epochString,k,kmask,numsat,depth+1,numInterSystemClocks,G,prefits,weights,unkinfo,StdESA,options);
			}
			kmask[i+depth]=1;
		}
	}

	if(res1==0) {
		
		HIR=Herror/HPL;
		VIR=Verror/VPL;
		//Save worst horizontal integrity ratio
		if(HIR>StdESA->HWIR) {
			StdESA->HWIR=HIR;
		}

		//Save worst vertical integrity ratio
		if(VIR>StdESA->VWIR) {
			StdESA->VWIR=VIR;
		}

		//Locate pixel position in grid and add 1 to the number of ocurrencies in that pixel
		//Horizontal error grid
		posx=(unsigned long long int)(Herror/StdESA->xstep);
		posy=(unsigned long long int)(HPL/StdESA->ystep);
		quantError=(double)(posx)*StdESA->xstep;
		quantPL=(double)(posy)*StdESA->ystep;
		if(posx>=(StdESA->numpixelhor-1)) {
			if((HPL-Herror)>0.) {
				//It is not an MI. Put in position StdESA->numpixelhor-2 to avoid
				//confusing it with an MI point
				posx=StdESA->numpixelhor-2;
			} else {
				posx=StdESA->numpixelhor-1;
			}
		}
        if( (HPL-Herror)>0. && quantError>=quantPL ) {
            //After quantized, the error is equal or greater than the protection level but it is not an MI
            //The quantization value of the protection level has to be moved over the error,
            //so there is no MI shown when the plots are done
            if(StdESA->ystep==StdESA->xstep) {
                //Steps are equal. Set posy value one postion above posx to make it greater
                posy=posx+1;
            } else {
                //Vertical step is different. Convert the quantized error value with the vertical step and add 1
                posy=(unsigned long long int)(quantError/StdESA->ystep)+1;
            }
        }
		if(posy>=StdESA->numpixelver) posy=StdESA->numpixelver-1;
		StdESA->counthor[posy][posx]+=1;
		//Vertical error grid
		posx=(unsigned long long int)(Verror/StdESA->xstep);
		posy=(unsigned long long int)(VPL/StdESA->ystep);
		quantError=(double)(posx)*StdESA->xstep;
		quantPL=(double)(posy)*StdESA->ystep;
		if(posx>=(StdESA->numpixelhor-1)) {
			if((VPL-Verror)>0.) {
				//It is not an MI. Put in position StdESA->numpixelhor-2 to avoid
				//confusing it with an MI point
				posx=StdESA->numpixelhor-2;
			} else {
				posx=StdESA->numpixelhor-1;
			}
		}
        if( (VPL-Verror)>0. && quantError>=quantPL ) {
            //After quantized, the error is equal or greater than the protection level but it is not an MI
            //The quantization value of the protection level has to be moved over the error,
            //so there is no MI shown when the plots are done
            if(StdESA->ystep==StdESA->xstep) {
                //Steps are equal. Set posy value one postion above posx to make it greater
                posy=posx+1;
            } else {
                //Vertical step is different. Convert the quantized error value with the vertical step and add 1
                posy=(unsigned long long int)(quantError/StdESA->ystep)+1;
            }
        }
		if(posy>=StdESA->numpixelver) posy=StdESA->numpixelver-1;
		StdESA->countver[posy][posx]+=1;

		if( options->stanfordesaLOI == 1) {
			//Write to file if any horizontal or vertical integrity ratio are over the thresholds
			if(HIR>=options->WIRHorThreshold || VIR>=options->WIRVerThreshold ) {
				//Get the list of satellites
				for(i=0;i<numsat;i++) {
					if(kmask[i]==1) {
						strpos+=sprintf(&strmask[strpos],"%c%02d ",epoch->listGNSSsatSolution[i],epoch->listPRNSatSolution[i]);
					}
				}
				//Write to file
				fprintf(options->fdstdESALOI," %s %7.4f %7.4f %9.2f %9.2f %9.2f %9.2f %9.4f %9.4f %8d %7d %s\n",epochString,options->WIRHorThreshold,options->WIRVerThreshold,Herror,Verror,HPL,VPL,HIR,VIR,numsat,availSat,strmask);
			}

		}
	}
}

/*****************************************************************************
 * Name        : SBASSummaryDataUpdate
 * Description : Updates variables for SBAS summary and
 *                 checks for discontinuities
 *               NOTE: If user forced NPA mode through parameters, all the values
 *               with PA names will have values from NPA epochs, as all epochs will
 *               be in NPA mode.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TSBASdatabox *SBASdatabox       IO N/A  Struct with SBAS data and summary
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void SBASSummaryDataUpdate (TEpoch *epoch, TFilterSolution *solution, TSBASdatabox *SBASdatabox, TOptions *options) {

	int				i;
	int				len;
	int				MI=0;
	unsigned int	k,l,hash=0;
	double			HIR,VIR;
	double			Nerror,Eerror;
	//double		DiscontinuityDuration; 		//Duration in seconds of the discontinuity
	double			NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double			TimeDiff,RinexInputDataTimeDiff;
	static int		NoDataRate=1;
	static int		FirstEpochSum=1;
	static int		Buffersize=0;

	//Check if we have the real data rate from file
	if(NoDataRate) {
		//Set decimation to file data rate
		if (epoch->receiver.interval != -1.) {
			SBASdatabox->decimation=epoch->receiver.interval;
			NoDataRate=0;
			if (options->decimate>epoch->receiver.interval && options->decimate!=0.) {
				//If decimation is higher than file data rate, then set the value to the epoch decimation
				SBASdatabox->decimation=options->decimate;
			}
		} else if(options->decimate!=0.) {
			SBASdatabox->decimation=options->decimate;
		}
	}

	//Add 1 to total number of PA epochs
	SBASdatabox->TotalPAEpochs++;

	if (SBASdatabox->TotalPAEpochs>Buffersize) {
		Buffersize+=86400;
		//Note that Herror and Verror will higher size than needed, but
		//resising with the highest size makes it much more efficient
		epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*Buffersize);
		epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*Buffersize);
		epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*Buffersize);
		epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*Buffersize);
		epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*Buffersize);
		SBASdatabox->HPL=realloc(SBASdatabox->HPL,sizeof(double)*Buffersize);
		SBASdatabox->VPL=realloc(SBASdatabox->VPL,sizeof(double)*Buffersize);
		SBASdatabox->HIR=realloc(SBASdatabox->HIR,sizeof(double)*Buffersize);
		SBASdatabox->VIR=realloc(SBASdatabox->VIR,sizeof(double)*Buffersize);
		epoch->NError=realloc(epoch->NError,sizeof(double)*Buffersize);
		epoch->EError=realloc(epoch->EError,sizeof(double)*Buffersize);
		epoch->HError=realloc(epoch->HError,sizeof(double)*Buffersize);
		epoch->VError=realloc(epoch->VError,sizeof(double)*Buffersize);
		epoch->Error3D=realloc(epoch->Error3D,sizeof(double)*Buffersize);
		epoch->NumSatUsed=realloc(epoch->NumSatUsed,sizeof(int)*Buffersize);
		epoch->NumSatNotUsed=realloc(epoch->NumSatNotUsed,sizeof(int)*Buffersize);
		for(i=0;i<MAX_GNSS;i++) {
			epoch->NumSatUsedGNSS[i]=realloc(epoch->NumSatUsedGNSS[i],sizeof(int)*Buffersize);
			epoch->NumSatNotUsedGNSS[i]=realloc(epoch->NumSatNotUsedGNSS[i],sizeof(int)*Buffersize);
		}
		epoch->NumConstUsed=realloc(epoch->NumConstUsed,sizeof(int)*Buffersize);
		epoch->NumConstNotUsed=realloc(epoch->NumConstNotUsed,sizeof(int)*Buffersize);
	}

	//Save DOP values
	epoch->HDOP[SBASdatabox->TotalPAEpochs-1]=solution->HDOP;
	epoch->PDOP[SBASdatabox->TotalPAEpochs-1]=solution->PDOP;
	epoch->GDOP[SBASdatabox->TotalPAEpochs-1]=solution->GDOP;
	epoch->VDOP[SBASdatabox->TotalPAEpochs-1]=solution->VDOP;
	epoch->TDOP[SBASdatabox->TotalPAEpochs-1]=solution->TDOP;

	//Save maximum values of DOP
	if (solution->HDOP>=epoch->MaxHDOP) {
		epoch->MaxHDOP=solution->HDOP;
		memcpy(&epoch->MaxHDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxHDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->HDOP<=epoch->MinHDOP) {
		epoch->MinHDOP=solution->HDOP;
		memcpy(&epoch->MinHDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinHDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->PDOP>=epoch->MaxPDOP) {
		epoch->MaxPDOP=solution->PDOP;
		memcpy(&epoch->MaxPDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxPDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->PDOP<=epoch->MinPDOP) {
		epoch->MinPDOP=solution->PDOP;
		memcpy(&epoch->MinPDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinPDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->GDOP>=epoch->MaxGDOP) {
		epoch->MaxGDOP=solution->GDOP;
		memcpy(&epoch->MaxGDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxGDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->GDOP<=epoch->MinGDOP) {
		epoch->MinGDOP=solution->GDOP;
		memcpy(&epoch->MinGDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinGDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->VDOP>=epoch->MaxVDOP) {
		epoch->MaxVDOP=solution->VDOP;
		memcpy(&epoch->MaxVDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxVDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->VDOP<=epoch->MinVDOP) {
		epoch->MinVDOP=solution->VDOP;
		memcpy(&epoch->MinVDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinVDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->TDOP>=epoch->MaxTDOP) {
		epoch->MaxTDOP=solution->TDOP;
		memcpy(&epoch->MaxTDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxTDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->TDOP<=epoch->MinTDOP) {
		epoch->MinTDOP=solution->TDOP;
		memcpy(&epoch->MinTDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinTDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	//Save number of satellites used
	epoch->NumSatUsed[SBASdatabox->TotalPAEpochs-1]=epoch->usableSatellites;
	epoch->NumSatNotUsed[SBASdatabox->TotalPAEpochs-1]=epoch->discardedSatellites;
	epoch->MeanNumSatUsed+=(double)epoch->usableSatellites;
	epoch->MeanNumSatNotUsed+=(double)epoch->discardedSatellites;
	for(i=0;i<MAX_GNSS;i++) {
		epoch->NumSatUsedGNSS[i][SBASdatabox->TotalPAEpochs-1]=epoch->usableSatellitesGNSS[i];
		epoch->NumSatNotUsedGNSS[i][SBASdatabox->TotalPAEpochs-1]=epoch->discardedSatellitesGNSS[i];
		epoch->MeanNumSatUsedGNSS[i]+=(double)epoch->usableSatellitesGNSS[i];
		epoch->MeanNumSatNotUsedGNSS[i]+=(double)epoch->discardedSatellitesGNSS[i];
	}
	
	//Save maximum values of satellites used
	if (epoch->usableSatellites>=epoch->MaxNumSatUsed) {
		epoch->MaxNumSatUsed=epoch->usableSatellites;
		memcpy(epoch->MaxNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MaxSatUsedEpoch,&epoch->t,sizeof(TTime));
	} 
	if (epoch->usableSatellites<=epoch->MinNumSatUsed) {
		epoch->MinNumSatUsed=epoch->usableSatellites;
		memcpy(epoch->MinNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MinSatUsedEpoch,&epoch->t,sizeof(TTime));
	}
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->usableSatellitesGNSS[i]>=epoch->MaxNumSatUsedGNSS[i]) {
			epoch->MaxNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
			memcpy(&epoch->MaxSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		} 
		if (epoch->usableSatellitesGNSS[i]<=epoch->MinNumSatUsedGNSS[i]) {
			epoch->MinNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
			memcpy(&epoch->MinSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		}
	}

	//Save maximum values of satellites unused
	if (epoch->discardedSatellites>=epoch->MaxNumSatNotUsed) {
		epoch->MaxNumSatNotUsed=epoch->discardedSatellites;
		memcpy(epoch->MaxNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MaxSatNotUsedEpoch,&epoch->t,sizeof(TTime));
	} 
	if (epoch->discardedSatellites<=epoch->MinNumSatNotUsed) {
		epoch->MinNumSatNotUsed=epoch->discardedSatellites;
		memcpy(epoch->MinNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MinSatNotUsedEpoch,&epoch->t,sizeof(TTime));
	}
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->discardedSatellitesGNSS[i]>=epoch->MaxNumSatNotUsedGNSS[i]) {
			epoch->MaxNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
			memcpy(&epoch->MaxSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		} 
		if (epoch->discardedSatellitesGNSS[i]<=epoch->MinNumSatNotUsedGNSS[i]) {
			epoch->MinNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
			memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		}
	}

	//Compute hash of current constellation combination
	for(i=0;i<epoch->numConstellationsUsed;i++) {
		hash+=1<<epoch->constellationUsedList[i];
	}

	//Check if current constellation combination has appeared. If not, add it
	for(k=0;k<epoch->numconstCombUsed;k++) {
		if (epoch->constCombination[k]==hash) break;
	}

	if (k==epoch->numconstCombUsed) {
		//Constellation combination not found
		epoch->constCombination=realloc(epoch->constCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
		epoch->numEpochsconstCombination=realloc(epoch->numEpochsconstCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
		epoch->constCombinationText=realloc(epoch->constCombinationText,sizeof(char*)*(epoch->numconstCombUsed+1));
		epoch->constCombinationText[epoch->numconstCombUsed]=NULL;
		epoch->constCombinationText[epoch->numconstCombUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

		epoch->numEpochsconstCombination[epoch->numconstCombUsed]=1;
		epoch->constCombination[epoch->numconstCombUsed]=hash;
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->constellationUsed[i]==1) {
				len+=sprintf(&epoch->constCombinationText[epoch->numconstCombUsed][len],"%3s+",gnsstype2gnssstr(i));
			}
		}
		epoch->constCombinationText[epoch->numconstCombUsed][len-1]='\0'; //Remove the last "+"
		epoch->numconstCombUsed++;
		k++;
	} else {
		//Constellation combination already occurred before
		epoch->numEpochsconstCombination[k]++;
	}

	if (epoch->numConstellationsNotUsed>0) {
		hash=0;
		//Compute hash of current not used constellation combination
		for(i=0;i<epoch->numConstellationsNotUsed;i++) {
			hash+=1<<epoch->constellationNotUsedList[i];
		}

		//Check if current not used constellation combinations has appeared. If not, add it
		for(l=0;l<epoch->numconstCombNotUsed;l++) {
			if (epoch->constNotUsedCombination[l]==hash) break;
		}

		if (l==epoch->numconstCombNotUsed) {
			//Constellation combination not found
			epoch->constNotUsedCombination=realloc(epoch->constNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
			epoch->numEpochsconstNotUsedCombination=realloc(epoch->numEpochsconstNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
			epoch->constNotUsedCombinationText=realloc(epoch->constNotUsedCombinationText,sizeof(char*)*(epoch->numconstCombNotUsed+1));
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=NULL;
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

			epoch->numEpochsconstNotUsedCombination[epoch->numconstCombNotUsed]=1;
			epoch->constNotUsedCombination[epoch->numconstCombNotUsed]=hash;
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->constellationNotUsed[i]==1) {
					len+=sprintf(&epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len],"%3s+",gnsstype2gnssstr(i));
				}
			}
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len-1]='\0'; //Remove the last "+"
			epoch->numconstCombNotUsed++;
			l++;
		} else {
			//Constellation combination already occurred before
			epoch->numEpochsconstNotUsedCombination[l]++;
		}
	}

	//Save number of constellations used and not used
	epoch->NumConstUsed[SBASdatabox->TotalPAEpochs-1]=epoch->numConstellationsUsed;
	epoch->NumConstNotUsed[SBASdatabox->TotalPAEpochs-1]=epoch->numConstellationsNotUsed;
	epoch->MeanNumConstUsed+=(double)epoch->numConstellationsUsed;
	epoch->MeanNumConstNotUsed+=(double)epoch->numConstellationsNotUsed;

	//Save maximum values of constellations used
	if (epoch->numConstellationsUsed>=epoch->MaxNumConstUsed) {
		epoch->MaxNumConstUsed=epoch->numConstellationsUsed;
		memcpy(&epoch->MaxGNSSUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MaxNumConstUsedListPos=(int)k;
	} 
	if (epoch->numConstellationsUsed<=epoch->MinNumConstUsed) {
		epoch->MinNumConstUsed=epoch->numConstellationsUsed;
		memcpy(&epoch->MinGNSSUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MinNumConstUsedListPos=(int)k;
	}

	//Save maximum values of constellations unused
	if (epoch->numConstellationsNotUsed>=epoch->MaxNumConstNotUsed) {
		epoch->MaxNumConstNotUsed=epoch->numConstellationsNotUsed;
		memcpy(&epoch->MaxGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MaxNumConstNotUsedListPos=(int)l;
	} 
	if (epoch->numConstellationsNotUsed<=epoch->MinNumConstNotUsed) {
		epoch->MinNumConstNotUsed=epoch->numConstellationsNotUsed;
		memcpy(&epoch->MinGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MinNumConstNotUsedListPos=(int)l;
	}

	//Add 1 to the number of times a constellation is used as reference clock
	epoch->numEpochsRefClock[epoch->ReferenceGNSSClock]++;

	//Check if a reference position is available 
	if (options->recPosProvided==1 && epoch->receiver.RefPositionAvail==1) {
		epoch->TotalEpochsRef++;

		if (FirstEpochSum) {
			//Save first epoch of summary with data for the percentiles
			memcpy(&epoch->StartSummaryPercentileEpoch,&epoch->t,sizeof(TTime));
			FirstEpochSum=0;
		}

		//Save last epoch of summary with data for the percentiles
		memcpy(&epoch->LastSummaryPercentileEpoch,&epoch->t,sizeof(TTime));

		//Compute error and integrity ratios
		Nerror=fabs(epoch->SolErrorNEU[0]);
		Eerror=fabs(epoch->SolErrorNEU[1]);

		HIR=epoch->SolHError/solution->HPL;
		VIR=epoch->SolVError/solution->VPL;

		//If errors are greater than previous epochs, save value and epoch
		if(Nerror>=epoch->MaxNError) {
			epoch->MaxNError=Nerror;
			memcpy(&epoch->MaxNerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxNError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxNErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(Eerror>=epoch->MaxEError) {
			epoch->MaxEError=Eerror;
			memcpy(&epoch->MaxEerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxEError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxEErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolHError>=epoch->MaxHError) {
			epoch->MaxHError=epoch->SolHError;
			memcpy(&epoch->MaxHerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxHError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxHErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolVError>=epoch->MaxVError) {
			epoch->MaxVError=epoch->SolVError;
			memcpy(&epoch->MaxVerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxVError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxVErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolError3DNEU>=epoch->Max3DError) {
			epoch->Max3DError=epoch->SolError3DNEU;
			memcpy(&epoch->Max3DerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMax3DError=epoch->usableSatellites;
			memcpy(epoch->NumSatMax3DErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(HIR>=SBASdatabox->HWIR) {
			SBASdatabox->HWIR=HIR;
			memcpy(&SBASdatabox->HWIREpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatHWIR=epoch->usableSatellites;
			memcpy(epoch->NumSatHWIRGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (HIR<=SBASdatabox->HBIR) {
			SBASdatabox->HBIR=HIR;
			memcpy(&SBASdatabox->HBIREpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatHBIR=epoch->usableSatellites;
			memcpy(epoch->NumSatHBIRGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}
	
		if(VIR>=SBASdatabox->VWIR) {
			SBASdatabox->VWIR=VIR;
			memcpy(&SBASdatabox->VWIREpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatVWIR=epoch->usableSatellites;
			memcpy(epoch->NumSatVWIRGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (VIR<=SBASdatabox->VBIR) {
			SBASdatabox->VBIR=VIR;
			memcpy(&SBASdatabox->VBIREpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatVBIR=epoch->usableSatellites;
			memcpy(epoch->NumSatVBIRGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		//Save horizontal and vertical integrity ratio values for percentile computation
		SBASdatabox->HIR[epoch->TotalEpochsRef-1]=HIR;
		SBASdatabox->VIR[epoch->TotalEpochsRef-1]=VIR;

		//Update number of MIs
		if(epoch->SolHError>=solution->HPL) {
			SBASdatabox->NumHMI++;
			MI=1;
		}

		if(epoch->SolVError>=solution->VPL) {
			SBASdatabox->NumVMI++;
			MI=1;
		}

		if(MI) {
			SBASdatabox->NumMI++;
		}

		//Save horizontal and vertical error values for percentile computation
		epoch->NError[epoch->TotalEpochsRef-1]=Nerror;
		epoch->EError[epoch->TotalEpochsRef-1]=Eerror;
		epoch->HError[epoch->TotalEpochsRef-1]=epoch->SolHError;
		epoch->VError[epoch->TotalEpochsRef-1]=epoch->SolVError;
		epoch->Error3D[epoch->TotalEpochsRef-1]=epoch->SolError3DNEU;

	} else if (options->recPosProvided==1 && options->UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
		epoch->NumNoRefSumSkipped++;
	}

	if(solution->HPL>=SBASdatabox->MaxHPL) {
		SBASdatabox->MaxHPL=solution->HPL;
		memcpy(&SBASdatabox->MaxHPLEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxHPL=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxHPLGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if(solution->HPL<=SBASdatabox->MinHPL) {
		SBASdatabox->MinHPL=solution->HPL;
		memcpy(&SBASdatabox->MinHPLEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinHPL=epoch->usableSatellites;
		memcpy(epoch->NumSatMinHPLGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if(solution->VPL>=SBASdatabox->MaxVPL) {
		SBASdatabox->MaxVPL=solution->VPL;
		memcpy(&SBASdatabox->MaxVPLEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxVPL=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxVPLGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if(solution->VPL<=SBASdatabox->MinVPL) {
		SBASdatabox->MinVPL=solution->VPL;
		memcpy(&SBASdatabox->MinVPLEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinVPL=epoch->usableSatellites;
		memcpy(epoch->NumSatMinVPLGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}


	//Save horizontal and vertical protection values for percentile computation
	SBASdatabox->HPL[SBASdatabox->TotalPAEpochs-1]=solution->HPL;
	SBASdatabox->VPL[SBASdatabox->TotalPAEpochs-1]=solution->VPL;

	//Check if current epoch is under alarm limits
	if(solution->HPL<options->HorAlarmLimit && solution->VPL<options->VerAlarmLimit) {
		//Horizontal and Vertical Protection limits are below the threshold. Epoch available
		SBASdatabox->TotalPAEpochsAvail++;

		//Check if we had a discontinuity.
		//To do it, we compute the difference between the current epoch and the last valid epoch before a discontinity.
		//The difference must be greater than the decimation step.
		TimeDiff=tdiff(&epoch->t,&SBASdatabox->LastEpochAvailPrevCurrDisc);

		//We also need to take into account data gaps from input file. 
		//If the input data file has a data gap larger than the decimation, then there is no discontinuity
		//due to there was no data
		RinexInputDataTimeDiff=tdiff(&epoch->t,&epoch->PreviousEpoch);

		if(TimeDiff>SBASdatabox->decimation && RinexInputDataTimeDiff<=SBASdatabox->decimation) {
			//There has been a discontinuity
			//Compute DiscontinuityDuration and NoDiscontinuityDuration (stable period before the current discontinuity) for the current discontinuity
			//DiscontinuityDuration and NoDiscontinuityDuration are computed in number of epochs. Decimation is taken into account
			//DiscontinuityDuration=TimeDiff/SBASdatabox->decimation-1.;
			TimeDiff=tdiff(&SBASdatabox->LastEpochAvailPrevCurrDisc,&SBASdatabox->FirstEpochAvailAfterPrevDisc);
			NoDiscontinuityDuration=TimeDiff/SBASdatabox->decimation+1.;

			//Update the number of epochs affected by the discontinuity (we consider a sliding window of 15 epochs by default) -which starts in the previous epoch-,
			//so all the previous epochs until the last discontinuity (or until the previous valid 15 epochs) will be affected
			if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
				//The stable period without discontinuity was larger than 15 epochs (default size), so we only consider that the last 15 epochs are affected
				SBASdatabox->NumEpochsRisk+=options->ContRiskWindowSize;
			} else {
				//The stable period without discontinuity was smaller than 15 epochs (default size), so we only need to add these epochs (the previous one were already
				//affected in the previous discontinuity so we don't have to count them twice)
				SBASdatabox->NumEpochsRisk+=(int)NoDiscontinuityDuration;
			}

			//In Maritime computation, it is counted the number of discontinuities
			SBASdatabox->NumEpochsRiskMar++;

			//Update LastEpochAvailAfterDisc. The current epoch will be the last epoch after the discontinuity
			memcpy(&SBASdatabox->FirstEpochAvailAfterPrevDisc,&epoch->t,sizeof(TTime));
		}

		//Update LastEpochAvailPrevDisc. The current epoch will be the last epoch before the discontinuity
		//If there has been a discontinuity, LastEpochAvailPrevDisc and LastEpochAvailAfterDisc will have the same value
		memcpy(&SBASdatabox->LastEpochAvailPrevCurrDisc,&epoch->t,sizeof(TTime));
	}
}

/*****************************************************************************
 * Name        : DGNSSSummaryDataUpdate
 * Description : Updates variables for DGNSS summary
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void DGNSSSummaryDataUpdate (TEpoch *epoch, TFilterSolution *solution, TOptions *options) {

    int     	    i;
    int 	        len;
	unsigned int	k,l,hash=0;
	double			Nerror,Eerror;
	static int		FirstEpochSum=1;
	static int		Buffersize=0;


    //If we are in DGNSS mode, only take into account epoch with DGNSS solution
    if (options->solutionMode==DGNSSMode) {
        epoch->TotalEpochsDGNSS++;

		if (epoch->TotalEpochsDGNSS>Buffersize) {
			Buffersize+=86400;
			//Note that Herror and Verror will higher size than needed, but
			//resising with the highest size makes it much more efficient
			epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*Buffersize);
			epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*Buffersize);
			epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*Buffersize);
			epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*Buffersize);
			epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*Buffersize);
			epoch->NError=realloc(epoch->NError,sizeof(double)*Buffersize);
			epoch->EError=realloc(epoch->EError,sizeof(double)*Buffersize);
			epoch->HError=realloc(epoch->HError,sizeof(double)*Buffersize);
			epoch->VError=realloc(epoch->VError,sizeof(double)*Buffersize);
			epoch->Error3D=realloc(epoch->Error3D,sizeof(double)*Buffersize);
			epoch->NumSatUsed=realloc(epoch->NumSatUsed,sizeof(int)*Buffersize);
			epoch->NumSatNotUsed=realloc(epoch->NumSatNotUsed,sizeof(int)*Buffersize);
			for(i=0;i<MAX_GNSS;i++) {
				epoch->NumSatUsedGNSS[i]=realloc(epoch->NumSatUsedGNSS[i],sizeof(int)*Buffersize);
				epoch->NumSatNotUsedGNSS[i]=realloc(epoch->NumSatNotUsedGNSS[i],sizeof(int)*Buffersize);
			}
			epoch->NumConstUsed=realloc(epoch->NumConstUsed,sizeof(int)*Buffersize);
			epoch->NumConstNotUsed=realloc(epoch->NumConstNotUsed,sizeof(int)*Buffersize);
		}

		//Save DOP values
		epoch->HDOP[epoch->TotalEpochsDGNSS-1]=solution->HDOP;
		epoch->PDOP[epoch->TotalEpochsDGNSS-1]=solution->PDOP;
		epoch->GDOP[epoch->TotalEpochsDGNSS-1]=solution->GDOP;
		epoch->VDOP[epoch->TotalEpochsDGNSS-1]=solution->VDOP;
		epoch->TDOP[epoch->TotalEpochsDGNSS-1]=solution->TDOP;

		//Save maximum values of DOP
		if (solution->HDOP>=epoch->MaxHDOP) {
			epoch->MaxHDOP=solution->HDOP;
			memcpy(&epoch->MaxHDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxHDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (solution->HDOP<=epoch->MinHDOP) {
			epoch->MinHDOP=solution->HDOP;
			memcpy(&epoch->MinHDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMinHDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMinHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if (solution->PDOP>=epoch->MaxPDOP) {
			epoch->MaxPDOP=solution->PDOP;
			memcpy(&epoch->MaxPDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxPDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (solution->PDOP<=epoch->MinPDOP) {
			epoch->MinPDOP=solution->PDOP;
			memcpy(&epoch->MinPDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMinPDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMinPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if (solution->GDOP>=epoch->MaxGDOP) {
			epoch->MaxGDOP=solution->GDOP;
			memcpy(&epoch->MaxGDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxGDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (solution->GDOP<=epoch->MinGDOP) {
			epoch->MinGDOP=solution->GDOP;
			memcpy(&epoch->MinGDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMinGDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMinGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if (solution->VDOP>=epoch->MaxVDOP) {
			epoch->MaxVDOP=solution->VDOP;
			memcpy(&epoch->MaxVDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxVDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (solution->VDOP<=epoch->MinVDOP) {
			epoch->MinVDOP=solution->VDOP;
			memcpy(&epoch->MinVDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMinVDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMinVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if (solution->TDOP>=epoch->MaxTDOP) {
			epoch->MaxTDOP=solution->TDOP;
			memcpy(&epoch->MaxTDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxTDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		} 
		if (solution->TDOP<=epoch->MinTDOP) {
			epoch->MinTDOP=solution->TDOP;
			memcpy(&epoch->MinTDOPEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMinTDOP=epoch->usableSatellites;
			memcpy(epoch->NumSatMinTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		//Save number of satellites used
		epoch->NumSatUsed[epoch->TotalEpochsDGNSS-1]=epoch->usableSatellites;
		epoch->NumSatNotUsed[epoch->TotalEpochsDGNSS-1]=epoch->discardedSatellites;
		epoch->MeanNumSatUsed+=(double)epoch->usableSatellites;
		epoch->MeanNumSatNotUsed+=(double)epoch->discardedSatellites;
		for(i=0;i<MAX_GNSS;i++) {
			epoch->NumSatUsedGNSS[i][epoch->TotalEpochsDGNSS-1]=epoch->usableSatellitesGNSS[i];
			epoch->NumSatNotUsedGNSS[i][epoch->TotalEpochsDGNSS-1]=epoch->discardedSatellitesGNSS[i];
			epoch->MeanNumSatUsedGNSS[i]+=(double)epoch->usableSatellitesGNSS[i];
			epoch->MeanNumSatNotUsedGNSS[i]+=(double)epoch->discardedSatellitesGNSS[i];
		}

		//Save maximum values of satellites used
		if (epoch->usableSatellites>=epoch->MaxNumSatUsed) {
			epoch->MaxNumSatUsed=epoch->usableSatellites;
			memcpy(epoch->MaxNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
			memcpy(&epoch->MaxSatUsedEpoch,&epoch->t,sizeof(TTime));
		} 
		if (epoch->usableSatellites<=epoch->MinNumSatUsed) {
			epoch->MinNumSatUsed=epoch->usableSatellites;
			memcpy(epoch->MinNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
			memcpy(&epoch->MinSatUsedEpoch,&epoch->t,sizeof(TTime));
		}
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->usableSatellitesGNSS[i]>=epoch->MaxNumSatUsedGNSS[i]) {
				epoch->MaxNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
				memcpy(&epoch->MaxSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
			} 
			if (epoch->usableSatellitesGNSS[i]<=epoch->MinNumSatUsedGNSS[i]) {
				epoch->MinNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
				memcpy(&epoch->MinSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
			}
		}

		//Save maximum values of satellites unused
		if (epoch->discardedSatellites>=epoch->MaxNumSatNotUsed) {
			epoch->MaxNumSatNotUsed=epoch->discardedSatellites;
			memcpy(epoch->MaxNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
			memcpy(&epoch->MaxSatNotUsedEpoch,&epoch->t,sizeof(TTime));
		} 
		if (epoch->discardedSatellites<=epoch->MinNumSatNotUsed) {
			epoch->MinNumSatNotUsed=epoch->discardedSatellites;
			memcpy(epoch->MinNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
			memcpy(&epoch->MinSatNotUsedEpoch,&epoch->t,sizeof(TTime));
		}
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->discardedSatellitesGNSS[i]>=epoch->MaxNumSatNotUsedGNSS[i]) {
				epoch->MaxNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
				memcpy(&epoch->MaxSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
			} 
			if (epoch->discardedSatellitesGNSS[i]<=epoch->MinNumSatNotUsedGNSS[i]) {
				epoch->MinNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
				memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
			}
		}


		//Compute hash of current constellation combination
		for(i=0;i<epoch->numConstellationsUsed;i++) {
			hash+=1<<epoch->constellationUsedList[i];
		}

		//Check if current constellation combinations has appeared. If not, add it
		for(k=0;k<epoch->numconstCombUsed;k++) {
			if (epoch->constCombination[k]==hash) break;
		}

		if (k==epoch->numconstCombUsed) {
			//Constellation combination not found
			epoch->constCombination=realloc(epoch->constCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
			epoch->numEpochsconstCombination=realloc(epoch->numEpochsconstCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
			epoch->constCombinationText=realloc(epoch->constCombinationText,sizeof(char*)*(epoch->numconstCombUsed+1));
			epoch->constCombinationText[epoch->numconstCombUsed]=NULL;
			epoch->constCombinationText[epoch->numconstCombUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

			epoch->numEpochsconstCombination[epoch->numconstCombUsed]=1;
			epoch->constCombination[epoch->numconstCombUsed]=hash;
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->constellationUsed[i]==1) {
					len+=sprintf(&epoch->constCombinationText[epoch->numconstCombUsed][len],"%3s+",gnsstype2gnssstr(i));
				}
			}
			epoch->constCombinationText[epoch->numconstCombUsed][len-1]='\0'; //Remove the last "+"
			epoch->numconstCombUsed++;
			k++;
		} else {
			//Constellation combination already occurred before
			epoch->numEpochsconstCombination[k]++;
		}

		if (epoch->numConstellationsNotUsed>0) {
			hash=0;
			//Compute hash of current not used constellation combination
			for(i=0;i<epoch->numConstellationsNotUsed;i++) {
				hash+=1<<epoch->constellationNotUsedList[i];
			}

			//Check if current not used constellation combinations has appeared. If not, add it
			for(l=0;l<epoch->numconstCombNotUsed;l++) {
				if (epoch->constNotUsedCombination[l]==hash) break;
			}

			if (l==epoch->numconstCombNotUsed) {
				//Constellation combination not found
				epoch->constNotUsedCombination=realloc(epoch->constNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
				epoch->numEpochsconstNotUsedCombination=realloc(epoch->numEpochsconstNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
				epoch->constNotUsedCombinationText=realloc(epoch->constNotUsedCombinationText,sizeof(char*)*(epoch->numconstCombNotUsed+1));
				epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=NULL;
				epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

				epoch->numEpochsconstNotUsedCombination[epoch->numconstCombNotUsed]=1;
				epoch->constNotUsedCombination[epoch->numconstCombNotUsed]=hash;
				len=0;
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->constellationNotUsed[i]==1) {
						len+=sprintf(&epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len],"%3s+",gnsstype2gnssstr(i));
					}
				}
				epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len-1]='\0'; //Remove the last "+"
				epoch->numconstCombNotUsed++;
				l++;
			} else {
				//Constellation combination already occurred before
				epoch->numEpochsconstNotUsedCombination[l]++;
			}
		}

		//Save number of constellations used and not used
		epoch->NumConstUsed[epoch->TotalEpochsDGNSS-1]=epoch->numConstellationsUsed;
		epoch->NumConstNotUsed[epoch->TotalEpochsDGNSS-1]=epoch->numConstellationsNotUsed;
		epoch->MeanNumConstUsed+=(double)epoch->numConstellationsUsed;
		epoch->MeanNumConstNotUsed+=(double)epoch->numConstellationsNotUsed;

		//Save maximum values of constellations used
		if (epoch->numConstellationsUsed>=epoch->MaxNumConstUsed) {
			epoch->MaxNumConstUsed=epoch->numConstellationsUsed;
			memcpy(&epoch->MaxGNSSUsedEpoch,&epoch->t,sizeof(TTime));
			epoch->MaxNumConstUsedListPos=(int)k;
		} 
		if (epoch->numConstellationsUsed<=epoch->MinNumConstUsed) {
			epoch->MinNumConstUsed=epoch->numConstellationsUsed;
			memcpy(&epoch->MinGNSSUsedEpoch,&epoch->t,sizeof(TTime));
			epoch->MinNumConstUsedListPos=(int)k;
		}

		//Save maximum values of constellations unused
		if (epoch->numConstellationsNotUsed>=epoch->MaxNumConstNotUsed) {
			epoch->MaxNumConstNotUsed=epoch->numConstellationsNotUsed;
			memcpy(&epoch->MaxGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
			epoch->MaxNumConstNotUsedListPos=(int)l;
		} 
		if (epoch->numConstellationsNotUsed<=epoch->MinNumConstNotUsed) {
			epoch->MinNumConstNotUsed=epoch->numConstellationsNotUsed;
			memcpy(&epoch->MinGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
			epoch->MinNumConstNotUsedListPos=(int)l;
		}

		//Add 1 to the number of times a constellation is used as reference clock
		epoch->numEpochsRefClock[epoch->ReferenceGNSSClock]++;

		//Check if a reference position is available (and we are not using the reference station coordinates as reference coordinates)
		if (options->recPosProvided==1 && epoch->receiver.RefPositionAvail==1) {
			epoch->TotalEpochsRef++;

			if (FirstEpochSum) {
				//Save first epoch of summary with data for the percentiles
				memcpy(&epoch->StartSummaryPercentileEpoch,&epoch->t,sizeof(TTime));
				FirstEpochSum=0;
			}

			//Save last epoch of summary with data for the percentiles
			memcpy(&epoch->LastSummaryPercentileEpoch,&epoch->t,sizeof(TTime));

            //Compute error and integrity ratios
			Nerror=fabs(epoch->SolErrorNEU[0]);
			Eerror=fabs(epoch->SolErrorNEU[1]);

            //If errors are greater than previous epochs, save value and epoch
			if(Nerror>=epoch->MaxNError) {
				epoch->MaxNError=Nerror;
				memcpy(&epoch->MaxNerrorEpoch,&epoch->t,sizeof(TTime));
				epoch->NumSatMaxNError=epoch->usableSatellites;
				memcpy(epoch->NumSatMaxNErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
			}

			if(Eerror>=epoch->MaxEError) {
				epoch->MaxEError=Eerror;
				memcpy(&epoch->MaxEerrorEpoch,&epoch->t,sizeof(TTime));
				epoch->NumSatMaxEError=epoch->usableSatellites;
				memcpy(epoch->NumSatMaxEErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
			}

            if(epoch->SolHError>=epoch->MaxHError) {
                epoch->MaxHError=epoch->SolHError;
                memcpy(&epoch->MaxHerrorEpoch,&epoch->t,sizeof(TTime));
				epoch->NumSatMaxHError=epoch->usableSatellites;
				memcpy(epoch->NumSatMaxHErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
            }

            if(epoch->SolVError>=epoch->MaxVError) {
                epoch->MaxVError=epoch->SolVError;
                memcpy(&epoch->MaxVerrorEpoch,&epoch->t,sizeof(TTime));
				epoch->NumSatMaxVError=epoch->usableSatellites;
				memcpy(epoch->NumSatMaxVErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
            }

			if(epoch->SolError3DNEU>=epoch->Max3DError) {
				epoch->Max3DError=epoch->SolError3DNEU;
				memcpy(&epoch->Max3DerrorEpoch,&epoch->t,sizeof(TTime));
				epoch->NumSatMax3DError=epoch->usableSatellites;
				memcpy(epoch->NumSatMax3DErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
			}

            //Save horizontal and vertical error values for percentile computation
			epoch->NError[epoch->TotalEpochsRef-1]=Nerror;
			epoch->EError[epoch->TotalEpochsRef-1]=Eerror;
            epoch->HError[epoch->TotalEpochsRef-1]=epoch->SolHError;
            epoch->VError[epoch->TotalEpochsRef-1]=epoch->SolVError;
			epoch->Error3D[epoch->TotalEpochsRef-1]=epoch->SolError3DNEU;


		} else if (options->recPosProvided==1 && options->UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
			epoch->NumNoRefSumSkipped++;
        }
    } else if (options->solutionMode==SPPMode) {
		epoch->TotalEpochsSPP++;
	}
}

/*****************************************************************************
 * Name        : SummaryDataUpdate
 * Description : Updates variables for summary (except for DGNSS/SBAS summary)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void SummaryDataUpdate (TEpoch *epoch, TFilterSolution *solution, TOptions *options) {

    int        		i;
    int         	len;
	unsigned int	k,l,hash=0;
	double			Nerror,Eerror;
	static int		FirstEpochSum=1;
	static int		Buffersize=0;


	epoch->TotalEpochsSol++;

	if (epoch->TotalEpochsSol>Buffersize) {
		Buffersize+=86400;
		//Note that Herror and Verror will higher size than needed, but
		//resising with the highest size makes it much more efficient
		epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*Buffersize);
		epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*Buffersize);
		epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*Buffersize);
		epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*Buffersize);
		epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*Buffersize);
		epoch->NError=realloc(epoch->NError,sizeof(double)*Buffersize);
		epoch->EError=realloc(epoch->EError,sizeof(double)*Buffersize);
		epoch->HError=realloc(epoch->HError,sizeof(double)*Buffersize);
		epoch->VError=realloc(epoch->VError,sizeof(double)*Buffersize);
		epoch->Error3D=realloc(epoch->Error3D,sizeof(double)*Buffersize);
		epoch->NumSatUsed=realloc(epoch->NumSatUsed,sizeof(int)*Buffersize);
		epoch->NumSatNotUsed=realloc(epoch->NumSatNotUsed,sizeof(int)*Buffersize);
		for(i=0;i<MAX_GNSS;i++) {
			epoch->NumSatUsedGNSS[i]=realloc(epoch->NumSatUsedGNSS[i],sizeof(int)*Buffersize);
			epoch->NumSatNotUsedGNSS[i]=realloc(epoch->NumSatNotUsedGNSS[i],sizeof(int)*Buffersize);
		}
		epoch->NumConstUsed=realloc(epoch->NumConstUsed,sizeof(int)*Buffersize);
		epoch->NumConstNotUsed=realloc(epoch->NumConstNotUsed,sizeof(int)*Buffersize);
	}

	//Save DOP values
	epoch->HDOP[epoch->TotalEpochsSol-1]=solution->HDOP;
	epoch->PDOP[epoch->TotalEpochsSol-1]=solution->PDOP;
	epoch->GDOP[epoch->TotalEpochsSol-1]=solution->GDOP;
	epoch->VDOP[epoch->TotalEpochsSol-1]=solution->VDOP;
	epoch->TDOP[epoch->TotalEpochsSol-1]=solution->TDOP;

	//Save maximum values of DOP and the number of satellites used
	if (solution->HDOP>=epoch->MaxHDOP) {
		epoch->MaxHDOP=solution->HDOP;
		memcpy(&epoch->MaxHDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxHDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->HDOP<=epoch->MinHDOP) {
		epoch->MinHDOP=solution->HDOP;
		memcpy(&epoch->MinHDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinHDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinHDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->PDOP>=epoch->MaxPDOP) {
		epoch->MaxPDOP=solution->PDOP;
		memcpy(&epoch->MaxPDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxPDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->PDOP<=epoch->MinPDOP) {
		epoch->MinPDOP=solution->PDOP;
		memcpy(&epoch->MinPDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinPDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinPDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->GDOP>=epoch->MaxGDOP) {
		epoch->MaxGDOP=solution->GDOP;
		memcpy(&epoch->MaxGDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxGDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->GDOP<=epoch->MinGDOP) {
		epoch->MinGDOP=solution->GDOP;
		memcpy(&epoch->MinGDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinGDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinGDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->VDOP>=epoch->MaxVDOP) {
		epoch->MaxVDOP=solution->VDOP;
		memcpy(&epoch->MaxVDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxVDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->VDOP<=epoch->MinVDOP) {
		epoch->MinVDOP=solution->VDOP;
		memcpy(&epoch->MinVDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinVDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinVDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	if (solution->TDOP>=epoch->MaxTDOP) {
		epoch->MaxTDOP=solution->TDOP;
		memcpy(&epoch->MaxTDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMaxTDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMaxTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	} 
	if (solution->TDOP<=epoch->MinTDOP) {
		epoch->MinTDOP=solution->TDOP;
		memcpy(&epoch->MinTDOPEpoch,&epoch->t,sizeof(TTime));
		epoch->NumSatMinTDOP=epoch->usableSatellites;
		memcpy(epoch->NumSatMinTDOPGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
	}

	//Save number of satellites used
	epoch->NumSatUsed[epoch->TotalEpochsSol-1]=epoch->usableSatellites;
	epoch->NumSatNotUsed[epoch->TotalEpochsSol-1]=epoch->discardedSatellites;
	epoch->MeanNumSatUsed+=(double)epoch->usableSatellites;
	epoch->MeanNumSatNotUsed+=(double)epoch->discardedSatellites;
	for(i=0;i<MAX_GNSS;i++) {
		epoch->NumSatUsedGNSS[i][epoch->TotalEpochsSol-1]=epoch->usableSatellitesGNSS[i];
		epoch->NumSatNotUsedGNSS[i][epoch->TotalEpochsSol-1]=epoch->discardedSatellitesGNSS[i];
		epoch->MeanNumSatUsedGNSS[i]+=(double)epoch->usableSatellitesGNSS[i];
		epoch->MeanNumSatNotUsedGNSS[i]+=(double)epoch->discardedSatellitesGNSS[i];
	}

	//Save maximum values of satellites used
	if (epoch->usableSatellites>=epoch->MaxNumSatUsed) {
		epoch->MaxNumSatUsed=epoch->usableSatellites;
		memcpy(epoch->MaxNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MaxSatUsedEpoch,&epoch->t,sizeof(TTime));
	} 
	if (epoch->usableSatellites<=epoch->MinNumSatUsed) {
		epoch->MinNumSatUsed=epoch->usableSatellites;
		memcpy(epoch->MinNumAllSatUsedGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MinSatUsedEpoch,&epoch->t,sizeof(TTime));
	}
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->usableSatellitesGNSS[i]>=epoch->MaxNumSatUsedGNSS[i]) {
			epoch->MaxNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
			memcpy(&epoch->MaxSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		} 
		if (epoch->usableSatellitesGNSS[i]<=epoch->MinNumSatUsedGNSS[i]) {
			epoch->MinNumSatUsedGNSS[i]=epoch->usableSatellitesGNSS[i];
			memcpy(&epoch->MinSatUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		}
	}

	//Save maximum values of satellites unused
	if (epoch->discardedSatellites>=epoch->MaxNumSatNotUsed) {
		epoch->MaxNumSatNotUsed=epoch->discardedSatellites;
		memcpy(epoch->MaxNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MaxSatNotUsedEpoch,&epoch->t,sizeof(TTime));
	} 
	
	if (epoch->discardedSatellites<=epoch->MinNumSatNotUsed) {
		epoch->MinNumSatNotUsed=epoch->discardedSatellites;
		memcpy(epoch->MinNumAllSatNotUsedGNSS,epoch->discardedSatellitesGNSS,sizeof(int)*MAX_GNSS);
		memcpy(&epoch->MinSatNotUsedEpoch,&epoch->t,sizeof(TTime));
	}
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->discardedSatellitesGNSS[i]>=epoch->MaxNumSatNotUsedGNSS[i]) {
			epoch->MaxNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
			memcpy(&epoch->MaxSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		} 
		if (epoch->discardedSatellitesGNSS[i]<=epoch->MinNumSatNotUsedGNSS[i]) {
			epoch->MinNumSatNotUsedGNSS[i]=epoch->discardedSatellitesGNSS[i];
			memcpy(&epoch->MinSatNotUsedEpochGNSS[i],&epoch->t,sizeof(TTime));
		}
	}

	//Compute hash of current constellation combination
	for(i=0;i<epoch->numConstellationsUsed;i++) {
		hash+=1<<epoch->constellationUsedList[i];
	}

	//Check if current constellation combinations has appeared. If not, add it
	for(k=0;k<epoch->numconstCombUsed;k++) {
		if (epoch->constCombination[k]==hash) break;
	}

	if (k==epoch->numconstCombUsed) {
		//Constellation combination not found
		epoch->constCombination=realloc(epoch->constCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
		epoch->numEpochsconstCombination=realloc(epoch->numEpochsconstCombination,sizeof(unsigned int)*(epoch->numconstCombUsed+1));
		epoch->constCombinationText=realloc(epoch->constCombinationText,sizeof(char*)*(epoch->numconstCombUsed+1));
		epoch->constCombinationText[epoch->numconstCombUsed]=NULL;
		epoch->constCombinationText[epoch->numconstCombUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

		epoch->numEpochsconstCombination[epoch->numconstCombUsed]=1;
		epoch->constCombination[epoch->numconstCombUsed]=hash;
		len=0;
		for(i=0;i<MAX_GNSS;i++) {
			if (epoch->constellationUsed[i]==1) {
				len+=sprintf(&epoch->constCombinationText[epoch->numconstCombUsed][len],"%3s+",gnsstype2gnssstr(i));
			}
		}
		epoch->constCombinationText[epoch->numconstCombUsed][len-1]='\0'; //Remove the last "+"
		epoch->numconstCombUsed++;
		k++;
	} else {
		//Constellation combination already occurred before
		epoch->numEpochsconstCombination[k]++;
	}

	if (epoch->numConstellationsNotUsed>0) {
		hash=0;
		//Compute hash of current not used constellation combination
		for(i=0;i<epoch->numConstellationsNotUsed;i++) {
			hash+=1<<epoch->constellationNotUsedList[i];
		}

		//Check if current not used constellation combinations has appeared. If not, add it
		for(l=0;l<epoch->numconstCombNotUsed;l++) {
			if (epoch->constNotUsedCombination[l]==hash) break;
		}

		if (l==epoch->numconstCombNotUsed) {
			//Constellation combination not found
			epoch->constNotUsedCombination=realloc(epoch->constNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
			epoch->numEpochsconstNotUsedCombination=realloc(epoch->numEpochsconstNotUsedCombination,sizeof(unsigned int)*(epoch->numconstCombNotUsed+1));
			epoch->constNotUsedCombinationText=realloc(epoch->constNotUsedCombinationText,sizeof(char*)*(epoch->numconstCombNotUsed+1));
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=NULL;
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed]=malloc(sizeof(char)*((maxLenghtConstName+1)*MAX_GNSS));

			epoch->numEpochsconstNotUsedCombination[epoch->numconstCombNotUsed]=1;
			epoch->constNotUsedCombination[epoch->numconstCombNotUsed]=hash;
			len=0;
			for(i=0;i<MAX_GNSS;i++) {
				if (epoch->constellationNotUsed[i]==1) {
					len+=sprintf(&epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len],"%3s+",gnsstype2gnssstr(i));
				}
			}
			epoch->constNotUsedCombinationText[epoch->numconstCombNotUsed][len-1]='\0'; //Remove the last "+"
			epoch->numconstCombNotUsed++;
			l++;
		} else {
			//Constellation combination already occurred before
			epoch->numEpochsconstNotUsedCombination[l]++;
		}
	}

	//Save number of constellations used and not used
	epoch->NumConstUsed[epoch->TotalEpochsSol-1]=epoch->numConstellationsUsed;
	epoch->NumConstNotUsed[epoch->TotalEpochsSol-1]=epoch->numConstellationsNotUsed;
	epoch->MeanNumConstUsed+=(double)epoch->numConstellationsUsed;
	epoch->MeanNumConstNotUsed+=(double)epoch->numConstellationsNotUsed;

	//Save maximum values of constellations used
	if (epoch->numConstellationsUsed>=epoch->MaxNumConstUsed) {
		epoch->MaxNumConstUsed=epoch->numConstellationsUsed;
		memcpy(&epoch->MaxGNSSUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MaxNumConstUsedListPos=(int)k;
	} 
	if (epoch->numConstellationsUsed<=epoch->MinNumConstUsed) {
		epoch->MinNumConstUsed=epoch->numConstellationsUsed;
		memcpy(&epoch->MinGNSSUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MinNumConstUsedListPos=(int)k;
	}

	//Save maximum values of constellations unused
	if (epoch->numConstellationsNotUsed>=epoch->MaxNumConstNotUsed) {
		epoch->MaxNumConstNotUsed=epoch->numConstellationsNotUsed;
		memcpy(&epoch->MaxGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MaxNumConstNotUsedListPos=(int)l;
	} 
	if (epoch->numConstellationsNotUsed<=epoch->MinNumConstNotUsed) {
		epoch->MinNumConstNotUsed=epoch->numConstellationsNotUsed;
		memcpy(&epoch->MinGNSSNotUsedEpoch,&epoch->t,sizeof(TTime));
		epoch->MinNumConstNotUsedListPos=(int)l;
	}

	//Add 1 to the number of times a constellation is used as reference clock
	epoch->numEpochsRefClock[epoch->ReferenceGNSSClock]++;


	//Check if a reference position is available 
	if (options->recPosProvided==1 && epoch->receiver.RefPositionAvail==1) {

		if (FirstEpochSum) {
			//Save first epoch of summary with data for the percentiles
			memcpy(&epoch->StartSummaryPercentileEpoch,&epoch->t,sizeof(TTime));
			FirstEpochSum=0;
		}

		//Save last epoch of summary with data for the percentiles
		memcpy(&epoch->LastSummaryPercentileEpoch,&epoch->t,sizeof(TTime));

		epoch->TotalEpochsRef++;

		//Compute error and integrity ratios
		Nerror=fabs(epoch->SolErrorNEU[0]);
		Eerror=fabs(epoch->SolErrorNEU[1]);

		//If errors are greater than previous epochs, save value and epoch
		if(Nerror>=epoch->MaxNError) {
			epoch->MaxNError=Nerror;
			memcpy(&epoch->MaxNerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxNError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxNErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(Eerror>=epoch->MaxEError) {
			epoch->MaxEError=Eerror;
			memcpy(&epoch->MaxEerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxEError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxEErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolHError>=epoch->MaxHError) {
			epoch->MaxHError=epoch->SolHError;
			memcpy(&epoch->MaxHerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxHError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxHErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolVError>=epoch->MaxVError) {
			epoch->MaxVError=epoch->SolVError;
			memcpy(&epoch->MaxVerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMaxVError=epoch->usableSatellites;
			memcpy(epoch->NumSatMaxVErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		if(epoch->SolError3DNEU>=epoch->Max3DError) {
			epoch->Max3DError=epoch->SolError3DNEU;
			memcpy(&epoch->Max3DerrorEpoch,&epoch->t,sizeof(TTime));
			epoch->NumSatMax3DError=epoch->usableSatellites;
			memcpy(epoch->NumSatMax3DErrorGNSS,epoch->usableSatellitesGNSS,sizeof(int)*MAX_GNSS);
		}

		//Save horizontal and vertical error values for percentile computation
		epoch->NError[epoch->TotalEpochsRef-1]=Nerror;
		epoch->EError[epoch->TotalEpochsRef-1]=Eerror;
		epoch->HError[epoch->TotalEpochsRef-1]=epoch->SolHError;
		epoch->VError[epoch->TotalEpochsRef-1]=epoch->SolVError;
		epoch->Error3D[epoch->TotalEpochsRef-1]=epoch->SolError3DNEU;

	} else if (options->recPosProvided==1 && options->UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
		epoch->NumNoRefSumSkipped++;
	}
}

/*****************************************************************************
 * Name        : calculateSBASAvailability (for SBAS plots mode only)
 * Description : Computes the horizontal and vertical protection levels for SBAS
 *               and checks if a solution is available. If available, checks if
 *               there was a discontinuity in previous epochs. If found, updates
 *               the continuity risk probability value and prints the discontinuity
 *               in the output file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fdDiscont                 I  N/A  File descriptor of the output discontinuity file
 * FILE *fdDiscontHour             I  N/A  File descriptor of the output discontinuity file for current hour
 * int LatPos					   I  N/A  Position in the Availability matrix (first dimension)
 * int LonPos					   I  N/A  Position in the Availability matrix (second dimension)
 * double latitude                 I    º  Current latitude in map
 * double longitude                I    º  Current longitude in map
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TSBASPlots *SBASplots           O  N/A  TSBASPlots structure
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A   0  => Everything OK
 *                                         -1  => Any of the matrix GtG,GtG_NEU,GtWG are not invertible
 *                                         -2  => Protection levels not met
 *                                         -3  => DOP requirements not met
 *****************************************************************************/
int calculateSBASAvailability (FILE *fdDiscont, FILE *fdDiscontHour, int LatPos, int LonPos, double latitude, double longitude, TEpoch *epoch, TSBASPlots *SBASplots, TOptions *options) {
    int     	i,j,ret;
	int			DOPPos,DOPPosHour;
	int			RowMatrixSize=4+epoch->numInterSystemClocksFilter;
	int			VectorGSize=m2v_opt(RowMatrixSize-1,RowMatrixSize-1)+1;
    double  	dmajor, weight;
    double  	RowMatrixG_NEU[RowMatrixSize],RowMatrixG_XYZ[RowMatrixSize],FalsePrefit[RowMatrixSize];
    double  	VectorGtWG_NEU[VectorGSize],VectorGtG_NEU[VectorGSize],VectorGtG_XYZ[VectorGSize];
	double		DiscontinuityDuration; 		//Duration in seconds of the discontinuity
	double		NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double		HDOP,PDOP,GDOP;


	//NOTE: Each of the cases have code in common, but they have been separated in order to avoid losing computation time in if statements,
	//which much of them would have to be inside for loops
	switch(options->SBASplotsDOP) {
		case(SBASplotsHDOPOnly):
			for ( i = 0; i < RowMatrixSize; i++ )   {RowMatrixG_NEU[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < VectorGSize; i++ )  	{VectorGtWG_NEU[i] = 0.0; VectorGtG_NEU[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					//First set all inter system values to 0
					for(j=4;j<RowMatrixSize;j++) {
						RowMatrixG_NEU[j] = 0;
					}
					//Set for the current constellation its inter system clock to 1 (for GPS, it will set again the position 3 (clock) to 1)
					RowMatrixG_NEU[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1; 	

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, weight);
					atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			//Compute protection levels
			dmajor = sqrt(0.5 * (VectorGtWG_NEU[2] + VectorGtWG_NEU[0]) + sqrt(0.25 * pow(VectorGtWG_NEU[2] - VectorGtWG_NEU[0], 2) + VectorGtWG_NEU[1] * VectorGtWG_NEU[1]));
			SBASplots->HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			SBASplots->VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(VectorGtWG_NEU[5]);
			if(SBASplots->HPL>=options->HorAlarmLimit || SBASplots->VPL>=options->VerAlarmLimit) {
				return -2;
			}
			HDOP=sqrt(VectorGtG_NEU[0] + VectorGtG_NEU[2]);
			if(options->HDOPthreshold==1) {
				//Check if HDOP threshold is excedeed
				if(HDOP>=options->maxHDOP) return -3;
			}
			DOPPos=SBASplots->SBASNumEpochsDOP[LatPos][LonPos];
			SBASplots->SBASNumEpochsDOP[LatPos][LonPos]++;
			if(options->HDOPPlot==1) {
				SBASplots->HDOPMean[LatPos][LonPos]+=HDOP;
				if(options->DOPPercentile) {
					SBASplots->HDOPValues[LatPos][LonPos][DOPPos]=(float)HDOP;
				}
				if (options->SBASHourlyMaps==1) {
					DOPPosHour=SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos];
					SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos]++;
					SBASplots->HDOPMeanHourly[LatPos][LonPos]+=HDOP;
					if(options->DOPPercentile) {
						SBASplots->HDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)HDOP;
					}
				}
			}
			break;	
		case(SBASplotsPDOPOnly): case(SBASplotsGDOPOnly): case (SBASplotsPDOPandGDOP):
			for ( i = 0; i < RowMatrixSize; i++ )   {RowMatrixG_NEU[i] = 0.0; RowMatrixG_XYZ[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < VectorGSize; i++ )  	{VectorGtWG_NEU[i] = 0.0; VectorGtG_XYZ[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					getLineOfSight(epoch->sat[i].position,epoch->receiver.aproxPosition,RowMatrixG_XYZ);
					RowMatrixG_XYZ[3] = 1;

					//First set all inter system values to 0
					for(j=4;j<RowMatrixSize;j++) {
						RowMatrixG_NEU[j] = 0;
						RowMatrixG_XYZ[j] = 0;
					}

					//Set for the current constellation its inter system clock to 1 (for GPS, it will set again the position 3 (clock) to 1)
					RowMatrixG_NEU[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1; 	
					RowMatrixG_XYZ[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, weight);
					atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, RowMatrixSize, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_XYZ, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			//Compute protection levels
			dmajor = sqrt(0.5 * (VectorGtWG_NEU[2] + VectorGtWG_NEU[0]) + sqrt(0.25 * pow(VectorGtWG_NEU[2] - VectorGtWG_NEU[0], 2) + VectorGtWG_NEU[1] * VectorGtWG_NEU[1]));
			SBASplots->HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			SBASplots->VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(VectorGtWG_NEU[5]);
			if(SBASplots->HPL>=options->HorAlarmLimit || SBASplots->VPL>=options->VerAlarmLimit) {
				return -2;	
			}
			PDOP=sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5]);
			GDOP=sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5] + VectorGtG_XYZ[9]);
			if(options->PDOPthreshold==1) {
				//Check if PDOP threshold is excedeed
				if(PDOP>=options->maxPDOP) return -3;
			}
			if(options->GDOPthreshold==1) {
				//Check if GDOP threshold is excedeed
				if(GDOP>=options->maxGDOP) return -3;
			}
			DOPPos=SBASplots->SBASNumEpochsDOP[LatPos][LonPos];
			SBASplots->SBASNumEpochsDOP[LatPos][LonPos]++;
			if(options->PDOPPlot==1) {
				SBASplots->PDOPMean[LatPos][LonPos]+=PDOP;
				if(options->DOPPercentile) {
					SBASplots->PDOPValues[LatPos][LonPos][DOPPos]=(float)PDOP;
				}
			}
			if(options->GDOPPlot==1) {
				SBASplots->GDOPMean[LatPos][LonPos]+=GDOP;
				if(options->DOPPercentile) {
					SBASplots->GDOPValues[LatPos][LonPos][DOPPos]=(float)GDOP;
				}
			}
			if (options->SBASHourlyMaps==1) {
				DOPPosHour=SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos];
				SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos]++;
				if(options->PDOPPlot==1) {
					SBASplots->PDOPMeanHourly[LatPos][LonPos]+=PDOP;
					if(options->DOPPercentile) {
						SBASplots->PDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)PDOP;
					}
				}
				if(options->GDOPPlot==1) {
					SBASplots->GDOPMeanHourly[LatPos][LonPos]+=GDOP;
					if(options->DOPPercentile) {
						SBASplots->GDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)GDOP;
					}
				}
			}
			break;	
		case(SBASplotsHDOPandPDOP): case(SBASplotsHDOPandGDOP): case(SBASplotsHDOPPDOPGDOP):
			for ( i = 0; i < RowMatrixSize; i++ )   {RowMatrixG_NEU[i] = 0.0; RowMatrixG_XYZ[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < VectorGSize; i++ )		{VectorGtWG_NEU[i] = 0.0; VectorGtG_XYZ[i] = 0.0; VectorGtG_NEU[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					getLineOfSight(epoch->sat[i].position,epoch->receiver.aproxPosition,RowMatrixG_XYZ);
					RowMatrixG_XYZ[3] = 1;

					//First set all inter system values to 0
					for(j=4;j<RowMatrixSize;j++) {
						RowMatrixG_NEU[j] = 0;
						RowMatrixG_XYZ[j] = 0;
					}
					//Set for the current constellation its inter system clock to 1 (for GPS, it will set again the position 3 (clock) to 1)
					RowMatrixG_NEU[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1; 	
					RowMatrixG_XYZ[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, weight);
					atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, RowMatrixSize, 1.0);
					atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_XYZ, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			//Compute protection levels
			dmajor = sqrt(0.5 * (VectorGtWG_NEU[2] + VectorGtWG_NEU[0]) + sqrt(0.25 * pow(VectorGtWG_NEU[2] - VectorGtWG_NEU[0], 2) + VectorGtWG_NEU[1] * VectorGtWG_NEU[1]));
			SBASplots->HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			SBASplots->VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(VectorGtWG_NEU[5]);
			if(SBASplots->HPL>=options->HorAlarmLimit || SBASplots->VPL>=options->VerAlarmLimit) {
				return -2;
			}
			HDOP=sqrt(VectorGtG_NEU[0] + VectorGtG_NEU[2]);
			PDOP=sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5]);
			GDOP=sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5] + VectorGtG_XYZ[9]);
			if(options->HDOPorPDOP==1 && options->SBASplotsDOP!=SBASplotsHDOPandGDOP) {
					if ((HDOP>=options->maxHDOP) && (PDOP>=options->maxPDOP)) return -3;
					if (options->SBASplotsDOP!=SBASplotsHDOPandPDOP) {
						if(options->GDOPthreshold==1) {
							//Check if GDOP threshold is excedeed
							if(GDOP>=options->maxGDOP) return -3;
						}
					}
			} else {
				if(options->HDOPthreshold==1) {
					//Check if HDOP threshold is excedeed
					if(HDOP>=options->maxHDOP) return -3;
				}
				if(options->PDOPthreshold==1) {
					//Check if PDOP threshold is excedeed
					if(PDOP>=options->maxPDOP) return -3;
				}
			}
			if(options->GDOPthreshold==1) {
				//Check if GDOP threshold is excedeed
				if(GDOP>=options->maxGDOP) return -3;
			}
			DOPPos=SBASplots->SBASNumEpochsDOP[LatPos][LonPos];
			SBASplots->SBASNumEpochsDOP[LatPos][LonPos]++;
			if (options->CombinedDOPPlot==1) {
				SBASplots->HDOPMean[LatPos][LonPos]+=HDOP;
				SBASplots->PDOPMean[LatPos][LonPos]+=PDOP;
				SBASplots->GDOPMean[LatPos][LonPos]+=GDOP;
				if(options->DOPPercentile) {
					SBASplots->HDOPValues[LatPos][LonPos][DOPPos]=(float)HDOP;
					SBASplots->PDOPValues[LatPos][LonPos][DOPPos]=(float)PDOP;
					SBASplots->GDOPValues[LatPos][LonPos][DOPPos]=(float)GDOP;
				}
				if (options->SBASHourlyMaps==1) {
					DOPPosHour=SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos];
					SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos]++;
					SBASplots->HDOPMeanHourly[LatPos][LonPos]+=HDOP;
					SBASplots->PDOPMeanHourly[LatPos][LonPos]+=PDOP;
					SBASplots->GDOPMeanHourly[LatPos][LonPos]+=GDOP;
					if(options->DOPPercentile) {
						SBASplots->HDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)HDOP;
						SBASplots->PDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)PDOP;
						SBASplots->GDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)GDOP;
					}
				}
			} else {
				if(options->HDOPPlot==1) {
					SBASplots->HDOPMean[LatPos][LonPos]+=HDOP;
					if(options->DOPPercentile) {
						SBASplots->HDOPValues[LatPos][LonPos][DOPPos]=(float)HDOP;
					}
				}
				if(options->PDOPPlot==1) {
					SBASplots->PDOPMean[LatPos][LonPos]+=PDOP;
					if(options->DOPPercentile) {
						SBASplots->PDOPValues[LatPos][LonPos][DOPPos]=(float)PDOP;
					}
				}
				if(options->GDOPPlot==1) {
					 SBASplots->GDOPMean[LatPos][LonPos]+=GDOP;
					 if(options->DOPPercentile) {
						 SBASplots->GDOPValues[LatPos][LonPos][DOPPos]=(float)GDOP;
					 }
				}
				if (options->SBASHourlyMaps==1) {
					DOPPosHour=SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos];
					SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos]++;
					if(options->HDOPPlot==1) {
						SBASplots->HDOPMeanHourly[LatPos][LonPos]+=HDOP;
						if(options->DOPPercentile) {
							SBASplots->HDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)HDOP;
						}
					}
					if(options->PDOPPlot==1) {
						SBASplots->PDOPMeanHourly[LatPos][LonPos]+=PDOP;
						if(options->DOPPercentile) {
							SBASplots->PDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)PDOP;
						}
					}
					if(options->GDOPPlot==1) {
						SBASplots->GDOPMeanHourly[LatPos][LonPos]+=GDOP;
						if(options->DOPPercentile) {
							SBASplots->GDOPValuesHourly[LatPos][LonPos][DOPPosHour]=(float)GDOP;
						}
					}
				}
			}
			break;	
		default://case(SBASplotsNoDOP):
			for ( i = 0; i < RowMatrixSize; i++ )   {RowMatrixG_NEU[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < VectorGSize; i++ )  {VectorGtWG_NEU[i] = 0.0;}

			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					//First set all inter system values to 0
					for(j=4;j<RowMatrixSize;j++) {
						RowMatrixG_NEU[j] = 0;
					}
					//Set for the current constellation its inter system clock to 1 (for GPS, it will set again the position 3 (clock) to 1)
					RowMatrixG_NEU[epoch->InterSystemClocksPosDOP[epoch->sat[i].GNSS]] = 1; 	

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, RowMatrixSize, weight);
				}
			}
			ret=cholinv_opt(VectorGtWG_NEU, RowMatrixSize);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			//Compute protection levels
			dmajor = sqrt(0.5 * (VectorGtWG_NEU[2] + VectorGtWG_NEU[0]) + sqrt(0.25 * pow(VectorGtWG_NEU[2] - VectorGtWG_NEU[0], 2) + VectorGtWG_NEU[1] * VectorGtWG_NEU[1]));
			SBASplots->HPL = options->kfactor[options->precisionapproach][KHORPOS]*dmajor;
			SBASplots->VPL = options->kfactor[options->precisionapproach][KVERPOS]*sqrt(VectorGtWG_NEU[5]);
			if(SBASplots->HPL>=options->HorAlarmLimit || SBASplots->VPL>=options->VerAlarmLimit) {
				return -2;
			}
			SBASplots->SBASNumEpochsDOP[LatPos][LonPos]++;
			if (options->SBASHourlyMaps==1) {
				SBASplots->SBASNumEpochsDOPHourly[LatPos][LonPos]++;
			}
			break;	
	}


	//Protection levels were checked before. If they were above the thresholds, the function would have ended with a return statement.
	SBASplots->SBASNumEpochsAvail[LatPos][LonPos]++;
	if (options->SBASHourlyMaps==1) {
		SBASplots->SBASNumEpochsAvailHourly[LatPos][LonPos]++;
	}

	if(options->ComputeRiskPlots==1) {
		//Check if we had a discontinuity. 
		//To do it, we compute the difference between the current epoch and the last valid epoch before a discontinity.
		//The difference must be greater than one second (as we compute the values each second). We set the difference larger than 1.1 instead of 1.0 to avoid problems with decimals
		if((epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos])>=options->AvailPlotTimeStepCmp) {
			//There has been a discontinuity
			//Compute DiscontinuityDuration and NoDiscontinuityDuration (stable period before the current discontinuity) for the current discontinuity
			DiscontinuityDuration=(epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]-options->AvailPlotTimeStepDec)/options->AvailPlotTimeStepDec;
			NoDiscontinuityDuration=(SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]-SBASplots->FirstEpochAvailAfterPrevDisc[LatPos][LonPos]+options->AvailPlotTimeStepDec)/options->AvailPlotTimeStepDec;

			//Update the number of epochs affected by the discontinuity (we consider a sliding window of 15 seconds -which starts in the previous epoch-,
			//so all the previous epochs until the last discontinuity (or until the previous valid 15 epochs) will be affected
			if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
				//The stable period without discontinuity was larger than 15 seconds, so we only consider that the last 15 seconds are affected
				SBASplots->SBASNumEpochsRisk[LatPos][LonPos]+=options->ContRiskWindowSize;
			} else {
				//The stable period without discontinuity was smaller than 15 seconds, so we only need to add these epochs (the previous one were already
				//affected in the previous discontinuity so we don't have to count them twice)
				SBASplots->SBASNumEpochsRisk[LatPos][LonPos]+=(int)NoDiscontinuityDuration;
			}

			//In Maritime computation, it is counted the number of discontinuities
			SBASplots->SBASNumEpochsRiskMar[LatPos][LonPos]++;

			//Write discontinuity to file
			fprintf(fdDiscont,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]+options->AvailPlotTimeStepDec,epoch->t.SoD-options->AvailPlotTimeStepDec,DiscontinuityDuration,NoDiscontinuityDuration);

			//Update FirstEpochAvailAfterDisc. The current epoch will be the last epoch after the discontinuity
			SBASplots->FirstEpochAvailAfterPrevDisc[LatPos][LonPos]=epoch->t.SoD;
		}

		if (options->SBASHourlyMaps==1) {
			if((epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos])>=options->AvailPlotTimeStepCmp) {
				//There has been a discontinuity
				//Compute DiscontinuityDuration and NoDiscontinuityDuration (stable period before the current discontinuity) for the current discontinuity
				DiscontinuityDuration=(epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]-options->AvailPlotTimeStepDec)/options->AvailPlotTimeStepDec;
				NoDiscontinuityDuration=(SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]-SBASplots->FirstEpochAvailAfterPrevDiscHourly[LatPos][LonPos]+options->AvailPlotTimeStepDec)/options->AvailPlotTimeStepDec;

				//Update the number of epochs affected by the discontinuity (we consider a sliding window of 15 seconds -which starts in the previous epoch-),
				//so all the previous epochs until the last discontinuity (or until the previous valid 15 epochs) will be affected
				if((int)NoDiscontinuityDuration>=options->ContRiskWindowSize) {
					//The stable period without discontinuity was larger than 15 seconds, so we only consider that the last 15 seconds are affected
					SBASplots->SBASNumEpochsRiskHourly[LatPos][LonPos]+=options->ContRiskWindowSize;
				} else {
					//The stable period without discontinuity was smaller than 15 seconds, so we only need to add these epochs (the previous one were already
					//affected in the previous discontinuity so we don't have to count them twice)
					SBASplots->SBASNumEpochsRiskHourly[LatPos][LonPos]+=(int)NoDiscontinuityDuration;
				}

				//In Maritime computation, it is counted the number of discontinuities
				SBASplots->SBASNumEpochsRiskHourlyMar[LatPos][LonPos]++;

				//Write discontinuity to file
				fprintf(fdDiscontHour,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]+options->AvailPlotTimeStepDec,epoch->t.SoD-options->AvailPlotTimeStepDec,DiscontinuityDuration,NoDiscontinuityDuration);

				//Update FirstEpochAvailAfterDisc. The current epoch will be the last epoch after the discontinuity
				SBASplots->FirstEpochAvailAfterPrevDiscHourly[LatPos][LonPos]=epoch->t.SoD;
			}
			//Update LastEpochAvailPrevDiscHourly. The current epoch will be the last epoch before the discontinuity
			//If there has been a discontinuity, LastEpochAvailPrevDiscHourly and LastEpochAvailAfterDiscHourly will have the same value
			SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]=epoch->t.SoD;
		}
		//Update LastEpochAvailPrevDisc. The current epoch will be the last epoch before the discontinuity
		//If there has been a discontinuity, LastEpochAvailPrevDisc and LastEpochAvailAfterDisc will have the same value
		SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]=epoch->t.SoD;
	}

	return 0;
}


/*****************************************************************************
 * Name        : updatePRNlist
 * Description : Update the PRNlist vector for the list of satellites visible 
 *               in the current epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * enum GNSSystem *GNSSlist        O  N/A  List of satellite constellations
 * int  *PRNlist                   O  N/A  List of satellite PRNs
 * TFilterSolution  *solution      I  N/A  Structure with the information of the 
 *                                         solution
 *****************************************************************************/
void updatePRNlist (TEpoch *epoch, enum GNSSystem *GNSSlist, int *PRNlist, TFilterSolution *solution) {
	int i,j;

	solution->prevNumSatellites = epoch->usableSatellites;
	for ( i = 0; i < epoch->usableSatellites; i++ ) {
		j=epoch->usedSat2DataPos[i];
		GNSSlist[i] = epoch->sat[j].GNSS;
		PRNlist[i] = epoch->sat[j].PRN;
		epoch->satHasBeenUsedInFilter[epoch->sat[j].GNSS][epoch->sat[j].PRN]=1;
	}
}

/*****************************************************************************
 * Name        : Kalman
 * Description : Process the filter for the specified epoch
 * Parameters  :
 * Name                                |Da|Unit|Description
 * TEpoch  *epoch                       I  N/A  TEpoch structure
 * TEpoch  *epochDGNSS                  I  N/A  TEpoch structure for DGNSS
 * TFilterSolution  *solution           IO N/A  Structure with the information of the 
 *                                              previous solution (updated)
 * TUnkinfo  *prevUnkinfo               IO N/A  Structure containing the information
 *                                              of the unknowns of the previous epoch
 *                                              (updated)
 * TStdESA *StdESA                      O  N/A  TStdESA struct                                        
 * TConstellation  *constellationPrint  I  N/A  Constellation information of the products (for printing)
 * TOptions  *options                   I  N/A  TOptions structure
 * Returned value (int)                 O  N/A  Status of the function
 *                                              4 => In SBAS mode and option select best GEO is enabled, process with next GEO or mode
 *                                              3 => Not enough satellites for positioning or DOP too high or geometry with singular matrix.
 *                                                   Try to change mode or GEO in SBAS mode or change to SPP in DGNSS mode
 *                                              2 => Initial position wrong, model and Kalman must be relaunched
 *                                              1 => Epoch computed
 *                                              0 => Epoch not computable due to lack of satellites
 *                                             -1 => Epoch not computable due to geometry matrix is singular
 *                                             -2 => Epoch not computable due to GDOP over threshold
 *                                             -3 => Epoch not computable due to correlation matrix is singular
 *                                             -4 => Epoch not computable due to design matrix with correlations is singular
 *                                             -5 => Epoch not computable due to reference clock is not available
 *****************************************************************************/
int Kalman (TEpoch *epoch, TEpoch *epochDGNSS, TFilterSolution *solution, TUnkinfo *prevUnkinfo, TStdESA *StdESA, TConstellation *constellationPrint, TOptions *options) {
	static double			newcorrelations[MAX_VECTOR_UNK]; //It may be too large for the stack, and as it has a fixed size value, we can set as static to avoid free/malloc
	static double			newparameterValues[MAX_UNK]; //It may be too large for the stack, and as it has a fixed size value, we can set as static to avoid free/malloc
	double					stddev2postfit=0.;
	double					distance;
	int						i;
	int						res,retUsableSat;
	char					errorstr[200];
	TUnkinfo				unkinfo;
	static TFilterSolution	aux; //It may be too large for the stack, and as it has a fixed size value, we can set as static to avoid free/malloc
	static int				first = 1;
	static TTime			prevT;
	static enum GNSSystem	GNSSlist[MAX_SATELLITES_VIEWED];
	static int				PRNlist[MAX_SATELLITES_VIEWED];

	
	if (first) {
		memcpy(&prevT, &epoch->t, sizeof(TTime)); 
		first=0;
	}

	retUsableSat=fillUsableSatellites(epoch, epochDGNSS, options);

	// Step detector for SBAS
	if ( options->stepdetector == 1 && retUsableSat!=-1 ) {
		retUsableSat=StepDetector(epoch, options);
	}

	// Prefit Outlier detector with absolute value
	if ( options->prefitOutlierDetectorAbs == 1 ) {
		//Only check for outliers if we can compute solution
		if (epoch->usableSatellites >= 4 ) {
			PrefitOutlierDetectorAbsolute(epoch, options);
		}
	}

	// Prefit Outlier detector with median
	if ( options->prefitOutlierDetectorMedian == 1 ) {
		//Only check for outliers if we can compute solution
		if (epoch->usableSatellites >= 4 ) {
			PrefitOutlierDetectorMedian(epoch, options);
		}
	}


	// If we are in SBAS 1F/DFMC processing, and we have less than 4 satellites, 
	// check if we can switch mode, we are in PA, and if adding the unselected satellites due to SBAS we can reach 4 satellites
	// If we are in DGNSS processing, and we have less than 4 satellites, change to SPP 
	// Or we are in SBAS DFMC or DGNSS and the reference constellation is not available 
	if ( (epoch->usableSatellites < (4+epoch->numInterSystemClocksFilter)) || retUsableSat==-1 ) {
		if ( options->SBAScorrections>=SBAS1Fused ) {
			if ((epoch->usableSatellites+epoch->numsatdiscardedSBAS >= (4+epoch->numInterSystemClocksFilter) ) && epoch->SwitchPossible == 1 ) {
				if ( (options->switchmode == 1 && options->precisionapproach == PAMODE) || options->switchGEO == 1 ) {
					// Empty print buffers for SATSEL messages
					options->printInBuffer = 3;
					printBuffers(epoch, options);
					printBuffersKalman(epoch, options);
					return 3;
				}
			} else if ( options->selectBestGEO==1 ) {
				if (epoch->Buffer_NumDataStored>0) {
					//Solution available with other GEO or mode. Select the one with smallest protection levels
					//Empty print buffers for SATSEL messages
					options->printInBuffer = 3;
					printBuffers(epoch, options);
					printBuffersKalman(epoch, options);
					//Select best GEO
					SelectBestGEO(epoch,solution,options);
				}
			}
		} else  if (options->DGNSS && options->solutionMode != SPPMode) {
			//DGNSS and we can switch to SPP
			options->solutionMode=SPPMode;
			if (options->stanfordesa==1) {
				//Disable temporary Stanford-ESA when solution moves to SPP
				options->stanfordesa=3;
			}
			// Empty print buffers for SATSEL messages
			options->printInBuffer = 3;
			printBuffers(epoch, options);
			printBuffersKalman(epoch, options);
			sprintf(messagestr, "Solution moved from DGNSS to SPP at %29s due to lack of satellites (%d available)", epoch->tSoDHourStr, epoch->usableSatellites);
			printInfo(messagestr, options);
			return 3;
		}
	}

	if (isEpochComputable(epoch)) {
		//Calculate DOP and protection levels
		res = calculateDOP(epoch,solution,errorstr,options);
		if (res<0) {
			//DOP is over the thresholds or geometry with singular matrix
			if ( options->SBAScorrections>=SBAS1Fused ) {
				if ((epoch->usableSatellites+epoch->numsatdiscardedSBAS >= (4+epoch->numInterSystemClocksFilter) ) && epoch->SwitchPossible == 1 ) {
					if ( (options->switchmode == 1 && options->precisionapproach == PAMODE) || options->switchGEO == 1 ) {
						if(options->switchmode == 1 && options->switchGEO <= 0) {
							sprintf(messagestr,"%29s %s for GEO %3d. Trying to switch to NPA mode",epoch->tSoDHourStr,errorstr,epoch->SBASUsedGEO);
						} else if ( options->switchmode <=0 && options->switchGEO == 1) {
							sprintf(messagestr,"%29s %s for GEO %3d. Trying to switch GEO",epoch->tSoDHourStr,errorstr,epoch->SBASUsedGEO);
						} else {
							sprintf(messagestr,"%29s %s for GEO %3d. Trying to switch GEO or to NPA mode",epoch->tSoDHourStr,errorstr,epoch->SBASUsedGEO);
						}
						printInfo(messagestr,options);
						// Empty print buffers for SATSEL messages
						options->printInBuffer = 3;
						printBuffers(epoch, options);
						printBuffersKalman(epoch, options);
						return 3;
					}
				}
				if ( options->selectBestGEO==0 ) {
					//If we get here means that we cannot swith mode or GEO in SBAS. Skip solution
					// Empty print buffers for SATSEL messages
					options->printInBuffer = 2;
					printBuffers(epoch, options);
					printBuffersKalman(epoch, options);
					sprintf(messagestr,"%29s %s for GEO %3d. Skipping epoch",epoch->tSoDHourStr,errorstr,epoch->SBASUsedGEO);
					printInfo(messagestr,options);
					return res;
				}
			} else if (options->DGNSS && options->solutionMode != SPPMode) {
				//DGNSS and we can switch to SPP
				options->solutionMode=SPPMode;
				if (options->stanfordesa==1) {
					//Disable temporary Stanford-ESA when solution moves to SPP
					options->stanfordesa=3;
				}
				// Empty print buffers for SATSEL messages
				options->printInBuffer = 3;
				printBuffers(epoch, options);
				printBuffersKalman(epoch, options);
				sprintf(messagestr, "Solution moved from DGNSS to SPP at %29s due to %s", epoch->tSoDHourStr,errorstr);
				printInfo(messagestr, options);
				return 3;
			} else if (options->DGNSS==0) {
				// SPP, PPP (DGNSS switched to SPP will not enter here)
				// Empty print buffers for SATSEL messages
				options->printInBuffer = 2;
				printBuffers(epoch, options);
				printBuffersKalman(epoch, options);
				sprintf(messagestr,"%29s %s. Skipping epoch",epoch->tSoDHourStr,errorstr);
				printInfo(messagestr,options);
				return res;
			}
		} 
		if ( options->selectBestGEO==1 ) {
			//If solution is not available and switching is possible, it will not get into this function
			//as it will have executed the "return 3" command above
			if (epoch->SwitchPossible == 1) {
				//Solution available, we are in SBAS mode and option to select best GEO is enabled
				//Save the current modelled data, the output messages and reprocess with next GEO
				epoch->TryGEOChange=1;
				SaveDataforGEOselection(epoch,solution,res,options);
				return 4;
			} else {
				//No more switches possible
				if(res<0) {
					//Solution not available. Check if we had any solution available
					if (epoch->Buffer_NumDataStored==0) {
						//No data buffered from previous GEO. No solution available. Empty print buffers from current GEO and exit function
						options->printInBuffer = 2;
						printBuffers(epoch, options);
						printBuffersKalman(epoch, options);
						sprintf(messagestr,"%29s %s for GEO %3d. Skipping epoch",epoch->tSoDHourStr,errorstr,epoch->SBASUsedGEO);
						printInfo(messagestr,options);
						return res;
					} else {
						//Solution available with other GEO or mode. Select the one with smallest protection levels
						//Empty print buffers for SATSEL messages
						options->printInBuffer = 3;
						printBuffers(epoch, options);
						printBuffersKalman(epoch, options);
						//Select best GEO
						SelectBestGEO(epoch,solution,options);
					}
				} else {
					//Solution available
					if (epoch->Buffer_NumDataStored==0) {
						//No data buffered from previous GEO. Use current GEO.
						//Empty print buffers for SATSEL messages
						options->printInBuffer = 2;
						printBuffers(epoch, options);
						printBuffersKalman(epoch, options);
					} else {
						//Solution available with current GEO and other GEO or mode. Select the one with smallest protection levels
						SaveDataforGEOselection(epoch,solution,res,options);
						SelectBestGEO(epoch,solution,options);
					}
				}
			}
		} else {
			// Empty print buffers for SATSEL messages
			options->printInBuffer = 2;
			printBuffers(epoch, options);
			printBuffersKalman(epoch, options);
		}

		options->printInBuffer = 1; //Force buffering of messages so PREFIT and POSTFIT messages are printed after being grouped by measurement type

		//Save data from previous solution, in case no solution can be computed or a new iteration is needed
		TFilterSolutionPartialCopy(&aux,solution,prevUnkinfo);

		unkinfo.nunk=calculateUnknowns(epoch, options);
		initUnkinfo(epoch, &unkinfo, fabs(tdiff(&epoch->t,&prevT)), options);
		if (!prepareCorrelation(epoch, solution, GNSSlist, PRNlist, &unkinfo, prevUnkinfo, options)) {
			return -3;
		}
		if (!computeSolution(epoch, &stddev2postfit, solution, newcorrelations, newparameterValues, &unkinfo, StdESA, constellationPrint, options)) {
			TFilterSolutionPartialCopy(solution,&aux,prevUnkinfo);
			options->printInBuffer = 2;
			printBuffersKalman(epoch, options);
			return -4;
		}

		//Save values for reference clock and intersytem clock bias for next iteration
		for(i=0;i<MAX_GNSS;i++) {
			epoch->prevInterSystemClocksUnk2GNSS[i+FIRST_POS_IS_CLK]=epoch->InterSystemClocksUnk2GNSS[i+FIRST_POS_IS_CLK];
			epoch->prevInterSystemClocksUnk[i]=epoch->InterSystemClocksUnk[i];
		}
		epoch->prevReferenceGNSSClock=epoch->ReferenceGNSSClock;
		epoch->prevNumInterSystemClocksFilter=epoch->numInterSystemClocksFilter;
		
		
		if ( options->receiverPositionSource >= rpCALCULATE ) {
			distance = sqrt((solution->x[0] - epoch->receiver.aproxPosition[0]) * (solution->x[0] - epoch->receiver.aproxPosition[0]) + 
							(solution->x[1] - epoch->receiver.aproxPosition[1]) * (solution->x[1] - epoch->receiver.aproxPosition[1]) + 
							(solution->x[2] - epoch->receiver.aproxPosition[2]) * (solution->x[2] - epoch->receiver.aproxPosition[2]));
			for ( i=0; i<3; i++ ) {
				epoch->receiver.aproxPosition[i] = solution->x[i];
			}
			epoch->receiver.aproxPositionError = solution->dop;
			sprintf(messagestr, "%29s Apriori position updated to: %13.4f %13.4f %13.4f   Distance: %13.4f",epoch->tSoDHourStr,epoch->receiver.aproxPosition[0], epoch->receiver.aproxPosition[1], epoch->receiver.aproxPosition[2], distance);
			printInfo(messagestr, options);
			if (distance > 100) {
				epoch->IterationInSameEpoch=1;	//Set flag to indicate that it is another iteration in the same epoch
				if (options->printFilterSolution) {
					printFilter(epoch, unkinfo.nunk, solution, options);
				}
				options->printInBuffer = 2;
				printBuffersKalman(epoch, options);
				TFilterSolutionPartialCopy(solution,&aux,prevUnkinfo);
				return 2;
			}
			epoch->receiver.receiverSolConverged = 1;
			epoch->IterationInSameEpoch=0;
			/*if (sqrt(solution->x[0]*solution->x[0]+solution->x[1]*solution->x[1]+solution->x[2]*solution->x[2]) >= MIN_LEO_ORBIT_RADIUS) {
				//Radius of receiver is greater than the minimum LEO orbit radius, which means the receiver is a LEO
				//Reset the aproximate position error, so in the next iteration satellites are not discarded by elevation
				epoch->receiver.aproxPositionError = 1e10;
			}*/
		}

		options->printInBuffer = 2;

		if (options->printFilterSolution) {
			printFilter(epoch, unkinfo.nunk, solution, options);
		}
		printBuffersKalman(epoch, options);

		// Preparing values for next epoch
		TUnkinfoPartialCopy(prevUnkinfo,&unkinfo);
		memcpy(solution->correlations,newcorrelations,sizeof(double)*unkinfo.nunkvector);
		memcpy(solution->parameters,newparameterValues,sizeof(double)*unkinfo.nunk);

		updatePRNlist(epoch, GNSSlist, PRNlist, solution);
		
		// Clean first flag
		first = 0;
		
		// Save last computed time
		memcpy(&prevT, &epoch->t, sizeof(TTime));
		return 1;
	} else {
		//Not enough satellites to compute solution
		options->printInBuffer = 2;
		printBuffers(epoch, options);
		printBuffersKalman(epoch, options);
		if (retUsableSat==-1) {
			sprintf(messagestr,"%29s No %3s satellites available for computing solution (as they are needed for reference clock)",epoch->tSoDHourStr,gnsstype2gnssname(options->ClkRefPriorityList[0]));
			printInfo(messagestr,options);
			return -5;
		} else {
			sprintf(messagestr,"%29s Not enough satellites (%d available) to compute solution",epoch->tSoDHourStr,epoch->usableSatellites);
			printInfo(messagestr,options);
			return 0;
		}
	}
}
