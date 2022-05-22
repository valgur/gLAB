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
 * File: filter.c
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
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
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "filter.h"
extern int	linesstoredSATSEL[MAX_SATELLITES_VIEWED];
extern char	printbufferSATSEL[MAX_SATELLITES_VIEWED][MAX_LINES_BUFFERED][MAX_INPUT_LINE]; 

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
 * Description : Optimized version of m2v (much faster). It suposes i>j.
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
 * int  n                          I  N/A  Matrix size
 * Returned value (int)            O  N/A  Status of the function
 *                                         0  => Cholesky worked properly
 *                                         -1 => Cholesky inversion failed (singular
 *                                               matrix)
 *****************************************************************************/
int cholinv_opt (double *mat, int n) {
 	int 	i,j,k;
 	double 	sum;
 	double 	*aux;
 
 	// Reserving space 
 	aux = malloc((m2v_opt(n-1,n-1)+1)*sizeof(double));
 	memset(aux,0,(m2v_opt(n-1,n-1)+1)*sizeof(double));

 	for (i=0;i<n;i++) {
		for (j=i;j<n;j++) {
	  		for (sum=mat[m2v_opt(j,i)],k=i-1;k>=0;k--) sum -= mat[m2v_opt(i,k)]*mat[m2v_opt(j,k)];
	  		if (i==j) {
				if (sum <= 0) {
					free(aux);
					return -1;  // Cholesky decomposition failed
				}
				mat[m2v_opt(i,i)]=sqrt(sum);
	  		} else mat[m2v_opt(j,i)]=sum/mat[m2v_opt(i,i)];
		}
	}	

	// Upper Inversion and multiplication of U^-1 * UT^-1

	for (i=0;i<n;i++) {
		mat[m2v_opt(i,i)]=1/mat[m2v_opt(i,i)];
		for (k=0;k<=i;k++) aux[m2v_opt(i,k)]+=mat[m2v_opt(i,i)]*mat[m2v_opt(i,k)];
		for (j=i+1;j<n;j++) {
	  		sum=0;
	  		for (k=i;k<j;k++) sum -= mat[m2v_opt(j,k)]*mat[m2v_opt(k,i)];
	  		mat[m2v_opt(j,i)]=sum/mat[m2v_opt(j,j)];
	  		for (k=0;k<=i;k++) aux[m2v_opt(i,k)]+=mat[m2v_opt(j,i)]*mat[m2v_opt(j,k)];
		}
	}	

  	memcpy(mat,aux,(m2v_opt(n-1,n-1)+1)*sizeof(double));

  	free (aux);
  	return 0;
}

/*****************************************************************************
 * Name        : mxv
 * Description : Multiplies a matrix in vectorial form and a vector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *mat                    I  N/A  Matrix in vector form
 * double  *vec                    IO N/A  Vector (overwritten)
 * int  n                          I  N/A  Matrix and vector size
 *****************************************************************************/
void mxv (double *mat, double *vec, int n) {
	int		i,j;
	double	*aux;

	aux=(double *)(malloc(sizeof(double)*n));

	for (i=0;i<n;i++) {
		aux[i]=0;
		for (j=0;j<n;j++) {
			aux[i] += mat[m2v(i,j)] * vec[j];
		}
	}
	for (i=0;i<n;i++) vec[i]=aux[i];
	free(aux);
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
 *               With this method a big step will not affect other satellites, but it
 *               the drawback that it assumes that only one satellite will fail or that
 *               more than one satellite may fail but not the reference ones.
 *               The problem with any step detector is that it will only trigger when there
 *               is a jump when changing the ephemerides to ones which have incorrect values, 
 *               but in the next epochs where previous and current epochs use the same bad
 *               ephemerides, the step detector will not trigger.
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void StepDetector (TEpoch *epoch, TOptions *options) {

	int				i,j,k;
	int				ind,ret;
	int				numsats=0;
	int				C1Cused=0;
	int				maxelevationpos=-1,secondmaxelevationpos=-1,thirdmaxelevationpos=-1;
	int				SatUsed[MAX_GNSS][MAX_SBAS_PRN];
	static int		PrevSatUsed[MAX_GNSS][MAX_SBAS_PRN];

	double			Threshold=73.8;
	double			measurement,smoothWith,model;
	double			diff1,diff2,Rescurrfirst,Resprevfirst,Rescurrsecond,Resprevsecond;
	double			Prefits[MAX_GNSS][MAX_SBAS_PRN];
	static double	PrevPrefits[MAX_GNSS][MAX_SBAS_PRN];

	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;
	
	//Check that C1C measurement is used in the filter. Otherwise the step detector has no use
	for(i=0;i<options->totalFilterMeasurements;i++) {
		if(options->measurement[i]==C1C) {
			C1Cused=1;
			break;
		}
	}

	if(C1Cused==0) return;

	//Initialize SatUsed
	for(i=0;i<MAX_GNSS;i++) {
		for(j=0;j<MAX_SBAS_PRN;j++) {
			SatUsed[i][j]=0;
			Prefits[i][j]=0;
		}
	}

	ind = epoch->measOrder[GPS].meas2Ind[C1C];
	k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];

	//Retrieve all the prefits available
	for(i=0;i<epoch->numSatellites;i++) {
		if(epoch->sat[i].available==0) {
			SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=0;
			continue;
		}
		ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[ind],&measurement,&model);
		if (ret!=1) {
			SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=0;
			continue;
		}

		// Smoothing
		if (options->smoothEpochs!=0 && options->smoothMeas[0]!=NA) {
			ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,options->smoothMeas[0],&smoothWith,NULL);
			if (ret!=1) {
				SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=0;
				continue;
			}
			Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN] = epoch->cycleslip.smoothedMeas[k][0] + smoothWith - model;
		} else {
			Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN] = measurement - model;
		}

		if(PrevSatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
			numsats++;
			//Look for the three satellites with higher elevation
			if(maxelevationpos==-1) {
				maxelevationpos=i;
			} else if (secondmaxelevationpos==-1) {
				secondmaxelevationpos=i;
			} else if (thirdmaxelevationpos==-1) {
				thirdmaxelevationpos=i;
			} else {
				if(epoch->sat[i].elevation>epoch->sat[maxelevationpos].elevation) {
					maxelevationpos=i;
				} else if (epoch->sat[i].elevation>epoch->sat[secondmaxelevationpos].elevation) {
					secondmaxelevationpos=i;
				} else if (epoch->sat[i].elevation>epoch->sat[thirdmaxelevationpos].elevation) {
					thirdmaxelevationpos=i;
				}
			}
		}
		SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=1;
	}

	if(numsats>=3) {
		for(i=0;i<epoch->numSatellites;i++) {
			if(SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
			if(PrevSatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
			if(i==maxelevationpos) {
				//Current satellite is the one with highest elevation.
				//We have to compare with satellites with second and third highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Resprevfirst=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Rescurrsecond=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
			} else if (i==secondmaxelevationpos) {
				//Current satellite is the one with second highest elevation.
				//We have to compare with satellites with first and third highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Resprevfirst=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Rescurrsecond=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[thirdmaxelevationpos].GNSS][epoch->sat[thirdmaxelevationpos].PRN];
			} else {
				//We have to compare with satellites with first and second highest elevation
				//First compute the prefit difference between satellites for current and previous epoch
				Rescurrfirst=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Resprevfirst=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[maxelevationpos].GNSS][epoch->sat[maxelevationpos].PRN];
				Rescurrsecond=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-Prefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
				Resprevsecond=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-PrevPrefits[epoch->sat[secondmaxelevationpos].GNSS][epoch->sat[secondmaxelevationpos].PRN];
			}

			//Compute the difference between prefit differences
			diff1=fabs(Rescurrfirst-Resprevfirst);
			diff2=fabs(Rescurrsecond-Resprevsecond);

			//Check that differences do not exceed the threshold
			if(diff1>Threshold && diff2>Threshold) {
				linesstoredSATSEL[i]=0;
				sprintf(messagestr,"STEP detected (jump of %7.3f greater than %7.3f)",max(diff1,diff2),Threshold);
				printSatSel(epoch,0,messagestr,i,options);
				epoch->sat[i].available=0;
				epoch->usableSatellites--;
			}
		}

	} else {
		//Step detector not available
	}

	memcpy(PrevSatUsed,SatUsed,sizeof(SatUsed));
	memcpy(PrevPrefits,Prefits,sizeof(Prefits));


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

	int 		i,j,k;
	int		ind,ret;
	int		numsats=0;
	int		SatUsed[MAX_GNSS][MAX_SBAS_PRN];
	static int	PrevSatUsed[MAX_GNSS][MAX_SBAS_PRN];

	double		Threshold=73.8;
	double		dtCurrent=0,dtPrev=0;
	double		measurement,smoothWith,model;
	double		diff,Rescurr,Resprev;
	double		Prefits[MAX_GNSS][MAX_SBAS_PRN];
	static double	PrevPrefits[MAX_GNSS][MAX_SBAS_PRN];

	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;

	//Initialize SatUsed
	for(i=0;i<MAX_GNSS;i++) {
		for(j=0;j<MAX_SBAS_PRN;j++) {
			SatUsed[i][j]=0;
			Prefits[i][j]=0;
		}
	}

	ind = epoch->measOrder[GPS].meas2Ind[C1C];
	k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];

	//Retrieve all the prefits available
	for(i=0;i<epoch->numSatellites;i++) {
		if(epoch->sat[i].available==0) {
			SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=0;
			continue;
		}
		ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[ind],&measurement,&model);
		if (ret!=1) {
			SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=0;
			continue;
		}

		// Smoothing
		if (options->smoothEpochs!=0 && options->smoothMeas[0]!=NA) {
			ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,options->smoothMeas[0],&smoothWith,NULL);
			if (ret!=1) {
				return;
			}
			Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN] = epoch->cycleslip.smoothedMeas[k][0] + smoothWith - model;
		} else {
			Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN] = measurement - model;
		}

		if(PrevSatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
			dtCurrent+=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			dtPrev+=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			numsats++;
		}
		SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]=1;
	}

	if(numsats>=3) {
		dtCurrent/=numsats;
		dtPrev/=numsats;
		//Compute for each satellite the prefit minus the receiver clock estimate and compare it with previous one (if available)
		for(i=0;i<epoch->numSatellites;i++) {
			if(SatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==0) continue;
			//Substract the receiver clock estimate from the prefits
			if(PrevSatUsed[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
				Rescurr=Prefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-dtCurrent;
				Resprev=PrevPrefits[epoch->sat[i].GNSS][epoch->sat[i].PRN]-dtPrev;
				diff=fabs(Rescurr-Resprev);
				if(diff>Threshold) {
					linesstoredSATSEL[i]=0;
					sprintf(messagestr,"STEP detected (jump of %7.3f)",diff);
					printSatSel(epoch,0,messagestr,i,options);
					epoch->sat[i].available=0;
					epoch->usableSatellites--;
				}
			}
		}
	} else {
		//Step detector not available
	}

	memcpy(PrevSatUsed,SatUsed,sizeof(SatUsed));
	memcpy(PrevPrefits,Prefits,sizeof(Prefits));
*/
}


/*****************************************************************************
 * Name        : PrefitOutlierDetectorAbsolute
 * Description : Check for outliers in the prefits. A prefit outlier is defined 
 *               as a value being too high compared to the other values.
 *               A arbitrary threshold (parametrizable). If it is too high, only
 *                very big outliers will be detected. If it is too low, there will
                  be fault detections. In nominal conditions, a possible threshold is 30 metres.
 *               It is only applied to code measurements, as 
 *               carrier phase measurements may differ a lot due to
 *               ambiguities. The detector works this way:
 *
 *               for each satellite available:
 *                Select one satellite as reference
 *                compute the absolute value of its prefit.
 *                Set a range for all other valid prefits as: 
 *                   Range=[abs(prefitR)-threshold,abs(prefitR)+threshold]
 *                For each satellite (except the reference one):
 *                  Check if prefits are inside the range
 *                If half or more of the satellites are unvalid, then the current satellite is an outlier
 *                Else discard the selected satellite.
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void PrefitOutlierDetectorAbsolute (TEpoch *epoch, TOptions *options) {

	int 					i,j,k,l,m;
	int						ret;
	enum MeasurementType    meas;
	double 					smoothWith,measurement,model;
	double					lowerLimit,upperLimit;
	double					currentPrefitAbs;
	double					prefits[epoch->usableSatellites];
	int						OutlierDetected[epoch->usableSatellites];
	int						List2EpochPos[epoch->usableSatellites];
	int						numOutliers,numDisabledSat,HalfAvailSat;
	int						NumSatUnselected;

	//Put this option to 1 so all prints are buffered
	options->printInBuffer=1;

	//Loop for all measurements
	for(j=0;j<options->totalFilterMeasurements;j++) {
		meas=options->measurement[j];
		if (whatIs(meas)!=Pseudorange) continue; //Only check prefits on code measurements
		k=0;
		NumSatUnselected=0;
    	//Retrieve all the prefits from available satellites
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==0) {
				continue;
			}
			ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,meas,&measurement,&model);
			if (ret!=1) {
				continue;
			}
			m = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			// Smoothing
			if (options->smoothEpochs!=0 && options->smoothMeas[0]!=NA) {
				ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,options->smoothMeas[0],&smoothWith,NULL);
				if (ret!=1) {
					continue;
				}
				prefits[k] = epoch->cycleslip.smoothedMeas[m][0] + smoothWith - model;
			} else {
				prefits[k] = measurement - model;
			}
			List2EpochPos[k]=i;
			k++;
		} 
		HalfAvailSat=(int)((double)(k)/2.);
		for(i=0;i<k;i++) {
			numOutliers=0;
			numDisabledSat=0;
			currentPrefitAbs=fabs(prefits[i]);
			lowerLimit=currentPrefitAbs-options->prefitOutlierDetectorAbsThreshold;
			upperLimit=currentPrefitAbs+options->prefitOutlierDetectorAbsThreshold;
			for(l=0;l<k;l++) {
				OutlierDetected[l]=0;
				if(l==i) continue; //We do not compare the prefit with itself
				currentPrefitAbs=fabs(prefits[l]);
				if(currentPrefitAbs<lowerLimit || currentPrefitAbs>upperLimit) {
					//Outlier detected
					numOutliers++;
					OutlierDetected[l]=1;
				}
			}
			if(numOutliers>=HalfAvailSat) {
				//Too many outliers. Means that the current satellite is the outlier
				if(epoch->sat[List2EpochPos[i]].available==1) {
					//The satellite has not been unselected, so we must print the SATSEL message
					linesstoredSATSEL[List2EpochPos[i]]=0;
					sprintf(messagestr,"Prefit too high in comparation with other satellites");
					printSatSel(epoch,0,messagestr,List2EpochPos[i],options);
					epoch->sat[List2EpochPos[i]].available=0;
					epoch->usableSatellites--;
					NumSatUnselected++;
				}
			} else if (numOutliers>0) {
				//Outliers detected
				for(l=0;l<k;l++) {
					if(OutlierDetected[l]==1) {
						if(epoch->sat[List2EpochPos[l]].available==1) {
							//The satellite has not been unselected, so we must unselect it and print the SATSEL message
							linesstoredSATSEL[List2EpochPos[l]]=0;
							sprintf(messagestr,"Prefit too high in comparation with other satellites (threshold %.2f metres)",options->prefitOutlierDetectorAbsThreshold);
							printSatSel(epoch,0,messagestr,List2EpochPos[l],options);
							epoch->sat[List2EpochPos[l]].available=0;
							epoch->usableSatellites--;
							NumSatUnselected++;
						}
						numDisabledSat++;
						if(numDisabledSat==numOutliers) break;
					}
				}
			}
		} //End for all available prefits
		//Check if we have unselected more than HalfAvailSat. If receiver position is fixed, we can unselect all, 
		//but if receiver position is not fixed we will not unselect none, as we may be in convergence time
		//or receiver is moving very fast (e.g. a LEO satellite)
		if (NumSatUnselected>HalfAvailSat && options->receiverPositionSource > rpSET) {
			//Too much satellites unselected. Select them all again
			for(i=0;i<k;i++) {
				linesstoredSATSEL[List2EpochPos[i]]=0;
				printSatSel(epoch,1,"",List2EpochPos[i],options);
				epoch->sat[List2EpochPos[i]].available=1;
			}	
			epoch->usableSatellites+=NumSatUnselected;
		}
	} //End for totalFilterMeasurements
}

/*****************************************************************************
 * Name        : PrefitOutlierDetectorMedian
 * Description : Check for outliers in the prefits. A prefit outlier is defined 
 *               as a value being too high compared to the other values.
 *               It is only applied to code measurements, as 
 *               carrier phase measurements may differ a lot due to
 *               ambiguities. The detector works this way:
 *     
 *               Compute the median of all prefits
 *               For each satellite:
 *                Compute absolute value of the difference between the prefit and the median
 *                If the difference is higher than the threshold, unselect the satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void PrefitOutlierDetectorMedian (TEpoch *epoch, TOptions *options) {

	int 					i,j,k,m;
	int						ret;
	enum MeasurementType    meas;
	double 					smoothWith,measurement,model,Median,Difference;
	double					prefits[epoch->usableSatellites],prefitsSorted[epoch->usableSatellites];
	int						List2EpochPos[epoch->usableSatellites];
	int						HalfAvailSat;
	int						NumSatUnselected;

	//Loop for all measurements
	for(j=0;j<options->totalFilterMeasurements;j++) {
		meas=options->measurement[j];
		if (whatIs(meas)!=Pseudorange) continue; //Only check prefits on code measurements
		k=0;
		NumSatUnselected=0;
    	//Retrieve all the prefits from available satellites
		for(i=0;i<epoch->numSatellites;i++) {
			if(epoch->sat[i].available==0) {
				continue;
			}
			ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,meas,&measurement,&model);
			if (ret!=1) {
				continue;
			}
			m = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
			// Smoothing
			if (options->smoothEpochs!=0 && options->smoothMeas[0]!=NA) {
				ret = getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,options->smoothMeas[0],&smoothWith,NULL);
				if (ret!=1) {
					continue;
				}
				prefitsSorted[k] = prefits[k] = epoch->cycleslip.smoothedMeas[m][0] + smoothWith - model;
			} else {
				prefitsSorted[k] = prefits[k] = measurement - model;
			}
			List2EpochPos[k]=i;
			k++;
		} 
		HalfAvailSat=(int)((double)(k)/2.);

		qsort(prefitsSorted,k,sizeof(double),qsort_compare_double);

		if(k%2==0) {
			//Numer of prefits is even
			Median=(prefitsSorted[HalfAvailSat-1]+prefitsSorted[HalfAvailSat])/2.;
		} else {
			//Numer of prefits is odd
			Median=prefitsSorted[HalfAvailSat];
		}

		for(i=0;i<k;i++) {
			//Discard satellites which are N times over the median
			Difference=fabs(prefits[i]-Median);
			if( Difference > options->prefitOutlierDetectorMedianThreshold ) {
				linesstoredSATSEL[List2EpochPos[i]]=0;
				sprintf(messagestr,"Prefit too different (%.2f) with respect to the prefit median (%.2f), threshold %.2f metres",Difference,Median,options->prefitOutlierDetectorMedianThreshold);
				printSatSel(epoch,0,messagestr,List2EpochPos[i],options);
				epoch->sat[List2EpochPos[i]].available=0;
				epoch->usableSatellites--;
				NumSatUnselected++;
			}
		}
		//Check if we have unselected more than HalfAvailSat. If receiver position is fixed, we can unselect all, 
		//but if receiver position is not fixed we will not unselect none, as we may be in convergence time
		//or receiver is moving very fast (e.g. a LEO satellite)
		if (NumSatUnselected>HalfAvailSat  && options->receiverPositionSource > rpSET ) {
			//Too much satellites unselected. Select them all again
			for(i=0;i<k;i++) {
				linesstoredSATSEL[List2EpochPos[i]]=0;
				printSatSel(epoch,1,"",List2EpochPos[i],options);
				epoch->sat[List2EpochPos[i]].available=1;
			}	
			epoch->usableSatellites+=NumSatUnselected;
		}
	} //End for totalFilterMeasurements
}

/*****************************************************************************
 * Name        : fillUsableSatellites
 * Description : Check for the usable satellites in the specified epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  Reference epoch
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void fillUsableSatellites (TEpoch *epoch, TOptions *options) {
	int		i, j, k;
	int		check,check1;
	double	sunPos[3];
	double	auxT;
	int		onlyHasPCorPCC;
	enum 	MeasurementType	meas;
	int 	numNconSamples = -1 * options->csNconMin + 1;
	int		printC1C;

	// Put this option to 1 so all prints are buffered
	options->printInBuffer = 1;
	
	epoch->usableSatellites = 0;

	if ( options->discardEclipsedSatellites ) {
		findSun(&epoch->t,sunPos);
	}

	for ( i = 0; i < epoch->numSatellites; i++ ) {
		check = 1;
		printC1C=0;
		k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];

		// Arc length sanity check
		if ( (epoch->cycleslip.arcLength[k] <= options->minArcLength) && epoch->sat[i].GNSS==GPS ) {
			sprintf(messagestr,"Arc too short (%d)",epoch->cycleslip.arcLength[k]);
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// Cycle slip sanity check
		if ( epoch->cycleslip.CS[k] == 1 ) {
			sprintf(messagestr,"Cycle-slip");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// Satellite Pre-Check sanity check
		if ( epoch->cycleslip.preCheck[k] == 1 && !epoch->cycleslip.consistency[k] ) {
			sprintf(messagestr,"Pre-Check; measurements missing for CS detection");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
			printC1C=1;
		} else {
			//If there is a data gap after the outlier, do not print
			//the outlier message while we are waiting for N-consecutive epochs
			if ( epoch->cycleslip.Nconsecutive[k] == 0 ) {
				// Outlier sanity check
				if ( epoch->cycleslip.outlierLI[k] == 1) { 
					sprintf(messagestr,"Outlier in LI detector");
					printSatSel(epoch,0,messagestr,i,options);
					check = 0;
				}
				if ( epoch->cycleslip.outlierBw[k] == 1)  {
					sprintf(messagestr,"Outlier in Bw detector");
					printSatSel(epoch,0,messagestr,i,options);
					check = 0;
				}
			}
		}

		// N-consecutive sanity check
		if ( epoch->cycleslip.Nconsecutive[k] < 0 ) {
			sprintf(messagestr,"Not enough consecutive samples (current %d, minimum %d)", numNconSamples + epoch->cycleslip.Nconsecutive[k], numNconSamples);
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// Satellite Consistency of Measurements sanity check
		if ( epoch->cycleslip.consistency[k] == 1 ) {
			sprintf(messagestr,"Unconsistency of measurements");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// Data availability check
		for ( j=0;j<options->totalFilterMeasurements;j++ ) {
			// Check if there are valid measurements for navigating
			if (getMeasModelValue(epoch,epoch->sat[i].GNSS,epoch->sat[i].PRN,options->measurement[j],NULL,NULL)!=1) {
				sprintf(messagestr,"Measurement unavailable (%s)",meastype2measstr(options->measurement[j]));
				printSatSel(epoch,0,messagestr,i,options);
				check = 0; 
			}
		}
		
		// Satellite selection check
		if ( !options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN] ) {
			printSatSel(epoch,0,"Deselection forced",i,options);
			check = 0;
		}

		// SNR check
		if ( options->SNRfilter==1 && epoch->sat[i].hasSNR==0 ) {
			sprintf(messagestr,"SNR too low (%.1f)",epoch->sat[i].lowSNR);
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// URA check
		if ( epoch->sat[i].URAValue>=options->MaxURABroadcast) {
			sprintf(messagestr,"URA value (%.1f) is equal or greater than the threshold (%.1f)",epoch->sat[i].URAValue,options->MaxURABroadcast);
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// Steady-state operation check
		if ( options->excludeSmoothingConvergence > 0 && (( epoch->cycleslip.arcLength[k] - options->minArcLength ) < options->excludeSmoothingConvergence) ) {
			// Satellite not reached steady-state operation
			sprintf(messagestr,"Steady-state operation not reached. %d epochs passed, still %d epochs to achieve %d",(int)max(1.0,epoch->cycleslip.arcLength[k]-options->minArcLength),options->excludeSmoothingConvergence-((int)max(1,epoch->cycleslip.arcLength[k]-options->minArcLength)),options->excludeSmoothingConvergence);
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// SBAS correction availability
		if ( options->SBAScorrections==1 && options->onlySBASiono==0 && (epoch->sat[i].GNSS == GPS || epoch->sat[i].GNSS == GEO)) {
			if (epoch->sat[i].hasSBAScor == 0) {
				sprintf(messagestr,"SBAS corrections unavailable (GEO %3d)",epoch->SBASUsedGEO);
				printSatSel(epoch,0,messagestr,i,options);
				check = 0;
			} else if ( epoch->sat[i].hasC1C == 0 ) { //Check if we have C1C measurement for SBAS
				printSatSel(epoch,0,"C1C measurement unavailable",i,options);
				printC1C=1;
				check = 0;
			}
		}

		//Check if we have code measurements (if we don't have them, transmission time can not be computed)
		if ( epoch->sat[i].hasC1C==0 && printC1C==0 ) {
			 printSatSel(epoch,0,"No code measurement available",i,options);
			 check = 0;
		}

		// Ephemeris availability check
		if ( epoch->sat[i].hasOrbitsAndClocks == 0 && epoch->sat[i].GNSS == GPS) {
			printSatSel(epoch,0,"Ephemerides unavailable",i,options);
			check = 0;
		} else if (epoch->sat[i].hasSatPhaseCenterCor==0 ) {
			printSatSel(epoch,0,"Satellite phase center corrections unavailable",i,options);
			check = 0;
		}
		
		// DCBs availability check
		if ( epoch->sat[i].hasDCBs == 0 && epoch->sat[i].hasOrbitsAndClocks != 0 && epoch->sat[i].GNSS == GPS) {
			if (epoch->sat[i].hasDCBsofC1P1 == 1) {
				onlyHasPCorPCC = 1;
				for (j=0;j<options->totalFilterMeasurements;j++) {
					meas = options->measurement[j];
					if (whatIs(meas)==Pseudorange && meas!=PC && meas!=PCC) onlyHasPCorPCC = 0;
				}
			}
			if (!(epoch->sat[i].hasDCBs==1 || (epoch->sat[i].hasDCBsofC1P1==1 && onlyHasPCorPCC==1))) {
				printSatSel(epoch,0,"DCBs unavailable (strict TGD treatment)",i,options);
				check = 0;
			}
		}
		
		// Elevation check (if approximate position is good enough, ie <100Km)
		if ( (epoch->sat[i].elevation < options->elevationMask) && (epoch->receiver.aproxPositionError < MAXAPROXPOSERROR) && (epoch->sat[i].hasOrbitsAndClocks == 1) ) { // 100Km
			if (epoch->sat[i].hasC1C == 1 && epoch->sat[i].GNSS == GPS && epoch->sat[i].elevation!=0.) {
				sprintf(messagestr,"Elevation too low (%7.2f)",epoch->sat[i].elevation/d2r);
				printSatSel(epoch,0,messagestr,i,options);
				check = 0;
			}
		} else if (fabs(epoch->sat[i].elevation) < MIN_ELEVATION_WEIGHT) {
			check1=0;
			for (j=0;j<options->totalFilterMeasurements;j++) {
				switch(options->weightMode[epoch->sat[i].GNSS][epoch->sat[i].PRN][j]) {
					case Elevation2Weight: case SBASElev2Weight: case DGNSSElev2Weight:
						//All case where elevation weight is applied as 1/(sin(elev)^2)
						sprintf(messagestr,"Elevation too low (%7.2f) for applying weight 1/(sin(elev)^2)",epoch->sat[i].elevation/d2r);
						printSatSel(epoch,0,messagestr,i,options);
						check=0;
						check1=1;
						break;
					case SNRElevWeight: case SBASSNRElevWeight: case DGNSSSNRElevWeight:
						//All case where elevation weight is applied as 10^(-SNR/10)/(sin(elev)^2)
						sprintf(messagestr,"Elevation too low (%7.2f) for applying weight 10^(-SNR/10)/(sin(elev)^2)",epoch->sat[i].elevation/d2r);
						printSatSel(epoch,0,messagestr,i,options);
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
			printSatSel(epoch,0,messagestr,i,options);
			check=0;
		}
		
		// Eclipsed satellite check
		if ( options->discardEclipsedSatellites ) {
			if (isEclipsed(&epoch->t,&epoch->sat[i],&epoch->satInfo[epoch->sat[i].GNSS][epoch->sat[i].PRN],sunPos,&auxT)) {
				if (auxT==0) {
					printSatSel(epoch,0,"Satellite under eclipse",i,options);
				} else {
					sprintf(messagestr,"Satellite was under eclipse %4.0f seconds ago",auxT);
					printSatSel(epoch,0,messagestr,i,options);
				}
				check = 0;
			}
		}

		// Ionex check (in case a IONEX file is used)
		if ( options->ionoModel == IONEX && epoch->sat[i].validIono == 0 ) {
			sprintf(messagestr,"Missing IONEX data");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		} else if ( options->ionoModel == neQuick && epoch->sat[i].validIono == 0 ) {
			// NeQuick check (in case NeQuick iono is used)
			sprintf(messagestr,"No NeQuick ionosphere");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		} else if ( options->ionoModel == FPPP && epoch->sat[i].validIono == 0 ) {
			// FPPP check (in case a FPPP file is used)
			sprintf(messagestr,"Missing FPPP data");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 0 && epoch->sat[i].GNSS == GPS ) {
			sprintf(messagestr,"No DGNSS corrections");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 2 ) {
			sprintf(messagestr,"No DGNSS corrections: Time out");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 3 ) {
			sprintf(messagestr,"No DGNSS corrections: Excluded during the smoother conversion in the Reference Station");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 4 ) {
			sprintf(messagestr,"No DGNSS corrections: Excluded during the smoother conversion in the User Station");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 5 && epoch->sat[i].hasOrbitsAndClocks != 0 ) {
			sprintf(messagestr,"No DGNSS corrections: IODE from BRDC and RTCM do not match");
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// DGNSS check (in case a DGNSS file is used)
		if ( options->DGNSS == 1 && epoch->sat[i].hasDGNSScor == 6 ) {
		    sprintf(messagestr,"No DGNSS corrections: Excluded due to differential correction is too large");
		    printSatSel(epoch,0,messagestr,i,options);
		    check = 0;
		}

		// SBAS iono availability (if we are not in SBAS mode processing)
		if ( options->onlySBASiono == 1 ) {
			if (epoch->sat[i].hasSBAScor == 0) {
				sprintf(messagestr,"SBAS iono unavailable (GEO %3d)",epoch->SBASUsedGEO);
				printSatSel(epoch,0,messagestr,i,options);
				check = 0;
			}
		}

		// GNSS System check (only prepared for GPS processing)
		if ( epoch->sat[i].GNSS != GPS ) {
			sprintf(messagestr,"Invalid GNSS System: %s",gnsstype2gnssstr(epoch->sat[i].GNSS));
			printSatSel(epoch,0,messagestr,i,options);
			check = 0;
		}

		// If everything is available satellite can be used
		if ( check ) {
			epoch->sat[i].available = 1;
			printSatSel(epoch,1,"",i,options);
			epoch->usableSatellites++;
		} else {
			epoch->sat[i].available = 0;
		}
	}
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
	if (epoch->usableSatellites>=4) return 1;
	else return 0;
}

/*****************************************************************************
 * Name        : calculateUnknowns
 * Description : Computes, from the options specified, how many unknowns the 
 *               filter has.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  obs                        I  N/A  Usable observations
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Number of unknowns in the filter
 *****************************************************************************/
int calculateUnknowns (int obs, TOptions *options) {
	int	value = 4;

	if (options->usePhase==1) value+=obs;
	if (options->estimateTroposphere==1) value++;
	return value;
}

/*****************************************************************************
 * Name        : initUnkinfo
 * Description : Initialises the information for the unknowns of the filter
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TUnkinfo  *unkinfo              O  N/A  TUnkinfo structure to store unknows
 * int  nunk                       I  N/A  Number of unknowns
 * int  observations               I  N/A  Number of observations
 * double  t                       I  s    Time since last filter run
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void initUnkinfo (TEpoch *epoch, TUnkinfo *unkinfo, int nunk, int observations, double t, TOptions *options){
	int	i;

	unkinfo->nunk=nunk;
	unkinfo->nunkvector=m2v(nunk-1,nunk-1)+1;
	unkinfo->par2unk[DR_UNK]=0;
	unkinfo->par2unk[DT_UNK]=3;
	i=4;
	if (options->estimateTroposphere==1) {
		unkinfo->par2unk[TROP_UNK]=i;
		i++;
	}
	if (options->usePhase==1) {
		unkinfo->par2unk[BIAS_UNK]=i;
		i+=observations;
	}
	
	// Forming PHI and QNOISE MATRIX (ONLY DIAGONAL)
	for (i=0;i<3;i++) {
		unkinfo->phi[unkinfo->par2unk[DR_UNK]+i] = options->filterParams[PHI_PAR][DR_UNK];
		unkinfo->qnoise[unkinfo->par2unk[DR_UNK]+i] = options->filterParams[Q_PAR][DR_UNK];
	}
	unkinfo->phi[unkinfo->par2unk[DT_UNK]] = options->filterParams[PHI_PAR][DT_UNK];
	unkinfo->qnoise[unkinfo->par2unk[DT_UNK]] = options->filterParams[Q_PAR][DT_UNK];

	if (options->estimateTroposphere==1) {
		unkinfo->phi[unkinfo->par2unk[TROP_UNK]] = options->filterParams[PHI_PAR][TROP_UNK];
		unkinfo->qnoise[unkinfo->par2unk[TROP_UNK]] = options->filterParams[Q_PAR][TROP_UNK]*(t/3600.);
	}
	if (options->usePhase==1) {
		for (i=0;i<observations;i++) {
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
 * int  *PRNlist                   I  N/A  List of satellites of the previous epoch
 * TUnkinfo  *unkinfo              I  N/A  TUnkinfo structure with information on 
 *                                         the current epoch unknowns
 * TUnkinfo  *prevUnkinfo          I  N/A  TUnkinfo structure with information on 
 *                                         the previous epoch unknowns
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void prepareCorrelation (TEpoch *epoch, TFilterSolution *solution, int *PRNlist, TUnkinfo *unkinfo, TUnkinfo *prevUnkinfo, TOptions *options) {
	int		i,j,alti,altj,k;
	double	updatedCorrelations[MAX_VECTOR_UNK];
	double	updatedParameterValues[MAX_UNK];
	int		new2old[MAX_SATELLITES_VIEWED];
	int		iniBiasUnk,endBiasUnk;
	int		new;
	int		found;
	int		ind;
	int		res;
	
	// Check for FIRST time
	if (solution->prevNumSatellitesGPS==0) {
		if (options->estimateTroposphere==1) {
			solution->correlations[m2v(unkinfo->par2unk[TROP_UNK],unkinfo->par2unk[TROP_UNK])] = 1/(options->filterParams[P0_PAR][TROP_UNK]);
		}
		//Loop to initialize covariance for all coordinates
		for (i=0;i<3;i++) {
			solution->correlations[m2v(unkinfo->par2unk[DR_UNK]+i,unkinfo->par2unk[DR_UNK]+i)] = 1/(options->filterParams[P0_PAR][DR_UNK]);
		}
		solution->correlations[m2v(unkinfo->par2unk[DT_UNK],unkinfo->par2unk[DT_UNK])] = 1/(options->filterParams[P0_PAR][DT_UNK]);
	}

	// Vector new2old will have the dictionary from new PRN positions to previous PRN positions
	for (i=0;i<epoch->numSatellites;i++) {
		new2old[i]=-1;
		k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
		if ( epoch->sat[i].GNSS == GPS ) {
			for (j=0;j<solution->prevNumSatellites;j++) {
				if ( PRNlist[j] == epoch->sat[i].PRN && epoch->sat[i].available &&
					 epoch->cycleslip.outlierLI[k] == 0 && epoch->cycleslip.outlierBw[k] == 0 && epoch->cycleslip.hasBeenCycleslip[k] == 0 ) {
					new2old[i]=j;
				}
			}
		}
		if ( epoch->cycleslip.hasBeenCycleslip[k] != 0 ) {
			epoch->cycleslip.hasBeenCycleslip[k] = 0; // clear cycle slip flag
		}
	}
	if (options->usePhase==1) {
		iniBiasUnk=unkinfo->par2unk[BIAS_UNK];
		endBiasUnk=unkinfo->par2unk[BIAS_UNK]+epoch->numSatellites-1;
	} else {
		iniBiasUnk=1;
		endBiasUnk=0;
	}
	
	// Updating correlations (including Phi and Q)
	if (solution->prevNumSatellitesGPS!=0) {
		for (i=0;i<prevUnkinfo->nunk;i++) {
			for (j=i;j<prevUnkinfo->nunk;j++) {
				solution->correlations[m2v(i,j)] *= prevUnkinfo->phi[i]*prevUnkinfo->phi[j];
			}
			solution->correlations[m2v(i,i)] += prevUnkinfo->qnoise[i];
		}
	}
	
	// Updating parameters
	for (i=0;i<prevUnkinfo->nunk;i++) {
		solution->parameters[i] *= prevUnkinfo->phi[i];
	}
	
	if (solution->prevNumSatellitesGPS!=0) { // If not in the first epoch
		// Update position parameters
		for(i=0,j=unkinfo->par2unk[DR_UNK];i<3;i++,j++) {
			solution->parameters[j] = solution->x[j] - epoch->receiver.aproxPosition[i];
		}
		// Update tropospheric parameter
		if (options->estimateTroposphere) {
			j = unkinfo->par2unk[TROP_UNK];
			solution->parameters[j] =  solution->x[j] - epoch->ZTD;
		}
	}
	
	// Satellite ambiguities that have disappeared or that have had a cycle-slip will be decorrelated from the
	// rest of ambiguities by putting an infinite in its self-correlation
	if (solution->prevNumSatellitesGPS!=0 && options->usePhase) {
		for (j=0;j<solution->prevNumSatellites;j++) {
			found = 0;
			for (i=0;i<epoch->numSatellites;i++) {
				if (new2old[i]==j) {
					found = 1;
					break;
				}
			}
			if (!found) {
				ind = prevUnkinfo->par2unk[BIAS_UNK]+j;
				solution->correlations[m2v(ind,ind)] = (options->filterParams[P0_PAR][BIAS_UNK]);
			}
		}
	}
	
	// Inverting correlation matrix from the former epoch
	res = cholinv_opt(solution->correlations,prevUnkinfo->nunk);
	if (res==-1) {
		sprintf(messagestr,"Problem in CHOLESKI2 res=%d\n",res);
		printError(messagestr,options);
		return;
	}
	
	// Creating new correlation matrix
	for (i=0;i<unkinfo->nunk;i++) {
		if (i>=iniBiasUnk && i<=endBiasUnk) {
			if (new2old[i-iniBiasUnk]!=-1) {
				updatedParameterValues[i] = solution->parameters[new2old[i-iniBiasUnk]+iniBiasUnk];
			} else {
				updatedParameterValues[i] = 0;
			}
		} else {
			updatedParameterValues[i] = solution->parameters[i];
		}
		for (j=i;j<unkinfo->nunk;j++) {
			new=0;
			if ((i>=iniBiasUnk && i<=endBiasUnk) || (j>=iniBiasUnk && j<=endBiasUnk)) {
				if (i>=iniBiasUnk && i<=endBiasUnk) {
					if (new2old[i-iniBiasUnk]==-1) {
						new=1;
					} else { 
						alti = prevUnkinfo->par2unk[BIAS_UNK]+new2old[i-iniBiasUnk]; 
					}
				} else { 
					alti = i;
				}
				if (j>=iniBiasUnk && j<=endBiasUnk) {
					if (new2old[j-iniBiasUnk]==-1) { 
						new=1;
					} else { 
						altj = prevUnkinfo->par2unk[BIAS_UNK]+new2old[j-iniBiasUnk];
					}
				} else { 
					altj = j;
				}
				if (new) {
					if (i==j) updatedCorrelations[m2v(i,j)] = 1/(options->filterParams[P0_PAR][BIAS_UNK]);
					else updatedCorrelations[m2v(i,j)] = 0;
				} else {
					updatedCorrelations[m2v(i,j)] = solution->correlations[m2v(alti,altj)];
				}
			} else {
				updatedCorrelations[m2v(i,j)] = solution->correlations[m2v(i,j)];
			}
		}
	}

	memcpy(solution->correlations,updatedCorrelations,sizeof(double)*unkinfo->nunkvector);
	memcpy(solution->parameters,updatedParameterValues,sizeof(double)*unkinfo->nunk);
}

/*****************************************************************************
 * Name        : atwa_atwy_insertline
 * Description : Insert an equation (prefilter values and design vector) into 
 *               the AtWA matrix and AtWY vector
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *atwa                   IO N/A  At*W*A matrix
 * double  *atwy                   IO N/A  At*W*Y vector
 * double  *unk                    I  N/A  Design vector
 * double  prefit                  I  N/A  Prefit value
 * int  nunk                       I  N/A  Number of unknowns
 * double  sigma2                  I  N/A  Sigma^2 associated with the prefit
 *****************************************************************************/
void atwa_atwy_insertline (double *atwa, double *atwy, double *unk, double prefit, int nunk, double sigma2) {
	int j,k;

	for (j=0;j<nunk;j++) {
		atwy[j] = atwy[j] + unk[j]*prefit/sigma2;
		for (k=0;k<=j;k++) {
			atwa[m2v(k,j)] = atwa[m2v(k,j)] + unk[j]*unk[k]/sigma2;
		}
	}
}

/*****************************************************************************
 * Name        : atwa_atwy_insertLineWithCorrelation
 * Description : Similar to atwa_atwy_insert for apriori values (with a full 
 *               correlations vector)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *atwa                   IO N/A  At*W*A matrix
 * double  *atwy                   IO N/A  At*W*Y vector
 * double  *corr                   I  N/A  Correlations vector
 * double  apriorivalue            I  N/A  Apriori value (equivalent to prefit)
 * int  nunk                       I  N/A  Number of unknowns
 * double  multiplier              I  N/A  Multiplier in the Fi matrix (equivalent
 *                                         to the design vector)
 * int  iniunk                     I  N/A  Initial unk to start updating
 *****************************************************************************/
void atwa_atwy_insertLineWithCorrelation (double *atwa, double *atwy, double *corr, double apriorivalue, int nunk, double multiplier, int iniunk) {
	int i;

	for (i=0;i<nunk;i++) {
		atwy[i] += multiplier*apriorivalue*corr[i];
	}

	for (i=iniunk;i<nunk;i++) {
		atwa[m2v(iniunk,i)] += multiplier*multiplier*corr[i];
	}
}

/*****************************************************************************
 * Name        : designSystem
 * Description : Designs the system for a specific measurement marked in the filter.
 *               Computes At*W*A and At*W*Y for the specified epoch 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * double  *atwa                   IO N/A  At*W*A matrix
 * double  *atwy                   IO N/A  At*W*Y vector
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of
 *                                         the unknowns 
 * MeasurementType  measType       I  N/A  Measurement to be included in the filter
 * int  filterInd                  I  N/A  Index of the measurement of the filter
 * double *prefits                 O  m    Vector with the prefits
 * double *weights	               O  m    Vector with the measurement weights
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void designSystem (TEpoch *epoch, double *atwa, double *atwy, TUnkinfo *unkinfo, enum MeasurementType measType, int filterInd, double **G, double *prefits, double *weights, TOptions *options) {
	int			i, j, k, l = 0;
	double		unk[MAX_UNK], prefit, measurement, model;
	int			ns = 0;
	TSatellite	*sat;
	double		weight;
	double		stdDev;
	int			ret;
	int			sats[MAX_SATELLITES_VIEWED];
	double		smoothWith;
	int			dontuse;

	epoch->numSatSolutionSBAS = 0;
	epoch->numSatnotUsedSBAS = 0;

	for ( i = 0; i < epoch->numSatellites; i++ ) {
		dontuse = 0;
		sat = &epoch->sat[i];
		k = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
		
		// If not GPS, the satellite will not be included in the filter
		if ( sat->GNSS != GPS ) dontuse = 1;


		ret = getMeasModelValue(epoch, sat->GNSS, sat->PRN, measType, &measurement, &model);
		if (ret!=1) {
			sat->available = 0;
			model = 0;
			measurement = 0;
		}
		// Smoothing
		if ( options->smoothEpochs != 0 && options->smoothMeas[filterInd] != NA ) {
			ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->smoothMeas[filterInd],&smoothWith,NULL);
			if (ret!=1) {
				sat->available = 0;
				model = 0;
				smoothWith = 0;
			}
			prefit = epoch->cycleslip.smoothedMeas[k][filterInd] + smoothWith - model;
		} else {
			prefit = measurement - model;
		}

		// Compute weights and available satellites
		if ( sat->available ) {
			stdDev = sat->measurementWeights[filterInd];
			sats[ns] = sat->PRN;
			ns++;
			//Count the number in satellites suitable for SBAS (currently only GPS) and used in solution computation
			if ( sat->GNSS == GPS ) {
				epoch->listPRNSatSolutionSBAS[epoch->numSatSolutionSBAS] = sat->PRN;
				epoch->listConsSatSolutionSBAS[epoch->numSatSolutionSBAS] = gnsstype2char(sat->GNSS);
				epoch->numSatSolutionSBAS += 1;
			}
		} else {
			// Satellite not counted for number of satellites
			stdDev = SIGMA_INF;
			//Count the number in satellites suitable for SBAS (currently only GPS) but not used in solution computation
			if ( sat->GNSS == GPS ) {
				epoch->listPRNSatnotUsedSBAS[epoch->numSatnotUsedSBAS] = sat->PRN;
				epoch->listConsSatnotUsedSBAS[epoch->numSatnotUsedSBAS] = gnsstype2char(sat->GNSS);
				epoch->numSatnotUsedSBAS += 1;
			}
		}
		weight = stdDev * stdDev;
	
		// Stop if it is declared as Don't Use
		if (dontuse) continue;

		
		// Print prefit residuals
		printPrefit(&epoch->t,i,sat,measType,prefit,measurement,model,stdDev,epoch->cycleslip.narc[k],options);


		// unk vector is the a row of the design matrix
		for (j=0;j<unkinfo->nunk;j++) unk[j]=0;

		// Position unknowns
		unk[unkinfo->par2unk[DR_UNK]] = -sat->LoS[0];
		unk[unkinfo->par2unk[DR_UNK]+1] = -sat->LoS[1];
		unk[unkinfo->par2unk[DR_UNK]+2] = -sat->LoS[2];

		if (options->stanfordesa==1 && sat->available && sat->GNSS == GPS) {
			G[l][0] = cos ( epoch->sat[i].elevation ) * sin ( epoch->sat[i].azimuth ) ;
			G[l][1] = cos ( epoch->sat[i].elevation ) * cos ( epoch->sat[i].azimuth ) ;
			G[l][2] = sin ( epoch->sat[i].elevation ) ;
			G[l][3] = 1 ;

			prefits[l]=prefit;
			weights[l]=weight;
			l++;
		}

		// Time unknown
		unk[unkinfo->par2unk[DT_UNK]] = 1;

		// Troposphere unknown
		if (options->estimateTroposphere)
			unk[unkinfo->par2unk[TROP_UNK]] = sat->tropWetMap;
			
		// Carrier-phase ambiguities unknowns - if applicable
		if (whatIs(measType)==CarrierPhase) {
			unk[unkinfo->par2unk[BIAS_UNK]+i] = 1;
		}
		
		// Insert the data in atwa and atwy. Only include if available or it is a carrierphase
		if (sat->available || whatIs(measType)==CarrierPhase) {
			atwa_atwy_insertline(atwa,atwy,unk,prefit,unkinfo->nunk,weight);
		}
		
	}

	epoch->numSatSolutionFilter=ns;
	printEpochsat(&epoch->t, measType, ns, sats, options);
}




/*****************************************************************************
 * Name        : designSystemIniValues
 * Description : Updates the filter with the information of the former epoch 
 *               (initial values for the current one)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * double  *atwa                   IO N/A  At*W*A matrix
 * double  *atwy                   IO N/A  At*W*Y vector
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of
 *                                         the unknowns 
 * TFilterSolution  *solution      I  N/A  Structure with the information of the 
 *                                         solution of the previous epoch
 *****************************************************************************/
void designSystemIniValues (TEpoch *epoch, double *atwa, double *atwy, TUnkinfo *unkinfo, TFilterSolution *solution) {
	int			i,j;
	double		corr[MAX_UNK];

	for (i=0;i<unkinfo->nunk;i++) {
		for (j=0;j<unkinfo->nunk;j++) {
			corr[j]=solution->correlations[m2v(i,j)];
		}
		atwa_atwy_insertLineWithCorrelation(atwa,atwy,corr,solution->parameters[i],unkinfo->nunk,1,i);
	}
}

/*****************************************************************************
 * Name        : calculatePostfits
 * Description : Calculate and print the postfits after the filtering process
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * double  *solution               I  N/A  Solution of the filter
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of
 *                                         the unknowns
 * MeasurementType  measType       I  N/A  Measurement type of the postfit
 * int  filterInd                  I  N/A  Index of the measurement of the filter
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  m    Standard deviation of the postfits
 *****************************************************************************/
double calculatePostfits (TEpoch *epoch, double *solution, TUnkinfo *unkinfo, enum MeasurementType measType, int filterInd, TOptions *options) {
	double		stddev2postfit=0;
	double		postfit;
	double		measurement,model;
	double		estimatedParameters;
	double		geometricCorrection;
	double		smoothWith;
	TSatellite	*sat;
	int			i,j,k;
	int			ret;

	for (i=0;i<epoch->numSatellites;i++) {
		sat = &epoch->sat[i];
		j = epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
		if (sat->available) {
			estimatedParameters = solution[unkinfo->par2unk[DT_UNK]];
			geometricCorrection = 0;
			for (k=0;k<3;k++) {
				geometricCorrection += -sat->LoS[k]*solution[unkinfo->par2unk[DR_UNK]+k];
			}
			estimatedParameters += geometricCorrection;
			if(options->estimateTroposphere) {
				estimatedParameters += sat->tropWetMap * solution[unkinfo->par2unk[TROP_UNK]];
			}
			if(whatIs(measType)==CarrierPhase) {
				estimatedParameters += solution[unkinfo->par2unk[BIAS_UNK]+i];
			}
			
			getMeasModelValue(epoch,sat->GNSS,sat->PRN,measType,&measurement,&model);
			
			// Smoothing
			if (options->smoothEpochs!=0 && options->smoothMeas[filterInd]!=NA) {
				ret = getMeasModelValue(epoch,sat->GNSS,sat->PRN,options->smoothMeas[filterInd],&smoothWith,NULL);
				if (ret!=1) {
					sat->available = 0;
					model = 0;
					smoothWith = 0;
					epoch->cycleslip.smoothedMeas[j][filterInd] = 0.0;
				}
				postfit = epoch->cycleslip.smoothedMeas[j][filterInd] + smoothWith - (model + estimatedParameters);
			} else {
				postfit = measurement - (model + estimatedParameters);
			}
			
			if (whatIs(measType)==CarrierPhase) {
				printPostfit(&epoch->t, i, sat, measType, postfit, measurement, model, estimatedParameters, solution[unkinfo->par2unk[BIAS_UNK]+i], options);
			} else {
				printPostfit(&epoch->t, i, sat, measType, postfit, measurement, model, estimatedParameters, 0, options);
			}

			stddev2postfit += postfit*postfit;
		}
	}
	stddev2postfit /= epoch->usableSatellites;
	return stddev2postfit;
}

/*****************************************************************************
 * Name        : computeSolution
 * Description : Obtain the filter solution for the specified epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * double  *stddev2postfit         O  m    Standard deviation of the postfits
 * TFilterSolution  *solution      IO N/A  Structure with the information of the 
 *                                         solution of the previous epoch (it is 
 *                                         updated with the solution of the present epoch)
 * double  *newcorrelations        O  N/A  Correlations after the filter run
 * double  *newparameters          O  N/A  Parameters after the filter run
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of
 *                                         the unknowns
 * TStdESA *StdESA                 O  N/A  TStdESA struct                                        
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Problem in the matrix inversion
 *                                         1 => Solution found
 *****************************************************************************/
int computeSolution (TEpoch *epoch,double *stddev2postfit, TFilterSolution *solution, double *newcorrelations, double *newparameterValues, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions *options) {
	double 		*atwa;
	double 		*atwy;
	//double 		*aux;
	double		*prefits;
	double		*weights;
	double		**G;
	double		SoW;
	int			GPSweek;
	int			*k;
	int			*kmask;
	int 		i,j;
	int			res;
	char		epochString[50];

	atwy=malloc(sizeof(double)*unkinfo->nunk);
	atwa=malloc(sizeof(double)*unkinfo->nunkvector);
	prefits=malloc(sizeof(double)*epoch->numSatellites);
	weights=malloc(sizeof(double)*epoch->numSatellites);
	G=malloc(sizeof(double *)*epoch->numSatellites);
	for(i=0;i<epoch->numSatellites;i++) {
		G[i]=malloc(sizeof(double)*4);
	}


	// Initializing At*W*A and At*W*Y
	for (i=0;i<unkinfo->nunk;i++) {
		atwy[i]=0;
	}
	for (i=0;i<unkinfo->nunkvector;i++) {
		atwa[i]=0;
	}
	
	// Forming At*W*A and At*W*Y
	for (i=0;i<options->totalFilterMeasurements;i++) {
		designSystem(epoch,atwa,atwy,unkinfo,options->measurement[i],i,G,prefits,weights,options);
	}

	designSystemIniValues(epoch,atwa,atwy,unkinfo,solution);

	res = cholinv_opt(atwa,unkinfo->nunk);

	if (res==-1) {
		free(atwa);
		free(atwy);
		sprintf(messagestr,"Problem in CHOLESKI1 res=%d\n",res);
		printError(messagestr,options);
		return 0;
	}
	
	// Saving parameters formal errors
//	for (i=0;i<unkinfo->nunk;i++) {
//		solution->formalError[i] = sqrt(atwa[m2v(i,i)]);
//	}
	
	mxv(atwa,atwy,unkinfo->nunk);


	// Updating correlations
	//if (solution->correlations!=NULL) {
		for (i=0;i<unkinfo->nunk;i++) {
			for (j=0;j<=i;j++) {
				newcorrelations[m2v(i,j)] = atwa[m2v(i,j)];
			}
		}
		
		memcpy (newparameterValues,atwy,sizeof(double)*unkinfo->nunk);
	//}

	// Building solution vector
	for (i=0;i<unkinfo->nunk;i++) {
		solution->x[i] = atwy[i];
	}
	for (i=0;i<3;i++) {
		solution->x[unkinfo->par2unk[DR_UNK]+i] = epoch->receiver.aproxPosition[i] + atwy[unkinfo->par2unk[DR_UNK]+i];
	}

	if (options->estimateTroposphere) solution->x[unkinfo->par2unk[TROP_UNK]] += epoch->ZTD;

	// High 'dr' checking => Initial aproximate position far from estimated position
//	aux = &atwy[unkinfo->par2unk[DR_UNK]];
//	if (aux[0]*aux[0]+aux[1]*aux[1]+aux[2]*aux[2] > options->maxdr2) {
//		for (i=0;i<3;i++) epoch->receiver.aproxPosition[i] = solution->x[unkinfo->par2unk[DR_UNK]+i];
//			printf("MAXDR FOUND: %f>%f\n",aux[0]*aux[0]+aux[1]*aux[1]+aux[2]*aux[2],options->maxdr2);
//		computeSolution (epoch,stddev2postfit,solution,newcorrelations,newparameterValues,unkinfo,options);
//	}

	// Postfit calculation
	for (i=0;i<options->totalFilterMeasurements;i++) {
		*stddev2postfit = calculatePostfits(epoch,atwy,unkinfo,options->measurement[i],i,options);
	}
	// Formal Error Calculation
	solution->dop=0;

	for (i=0;i<3;i++) {
		solution->dop += atwa[m2v(unkinfo->par2unk[DR_UNK]+i,unkinfo->par2unk[DR_UNK]+i)];
	}
	solution->dop = sqrt(solution->dop);

	//Compute Stanford-ESA plots
	if(options->stanfordesa==1 && options->useDatasummary>=1) {
		k=malloc(sizeof(int)*(epoch->numSatSolutionSBAS+1));
		kmask=malloc(sizeof(int)*(epoch->numSatSolutionSBAS+1));
		k[0]=0;
		for(i=0;i<=epoch->numSatSolutionSBAS;i++) {
			kmask[i]=1;
		}
		//Calculate GPS Week and Seconds of Week
		ttime2gpswsnoroll(&epoch->t, &GPSweek, &SoW);

		//Save epoch in printable format (Year/Doy/SoD - GPSWeek/SoW) in string, so it not needed to
		//be done at each interation of the Stanford-ESA
		sprintf(epochString,"%17s    %4d %9.2f",t2doystr(&epoch->t),GPSweek,SoW);
		StanfordESAComputationRecursive(epoch,epochString,k,kmask,epoch->numSatSolutionSBAS,0,G,prefits,weights,unkinfo,StdESA,options);
		free(k);
		free(kmask);
	}


	// Freeing memory
	free(atwa);
	free(atwy);
	free(weights);
	free(prefits);
	for(i=0;i<epoch->numSatellites;i++) {
		free(G[i]);
	}
	free(G);

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
	int		i, j;
	int		res;
	double	dmajor, weight;
	double	RowMatrixG_NEU[4], RowMatrixG_XYZ[4];
	double	VectorGtG_NEU[10], VectorGtG_XYZ[10], FalsePrefit[4];
	double	VectorGtWG_NEU[10];


	// Initialise Variables
	solution->GDOP = 0.0; solution->PDOP = 0.0; solution->TDOP = 0.0; solution->VPL = 0.0;
	solution->HDOP = 0.0; solution->VDOP = 0.0; solution->HPL = 0.0;

	for ( j = 0; j < 4; j++ )	{RowMatrixG_NEU[j] = 0.0; RowMatrixG_XYZ[j] = 0.0; FalsePrefit[j] = 0.0;}
	for ( j = 0; j < 10; j++ )	{VectorGtG_NEU[j] = 0.0; VectorGtG_XYZ[j] = 0.0; VectorGtWG_NEU[j] = 0.0;}

	// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
	for ( i = 0; i < epoch->numSatellites; i++ ) {
		if ( epoch->sat[i].available ) {
			RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
			RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
			RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
			RowMatrixG_NEU[3] = 1;

			RowMatrixG_XYZ[0] = epoch->sat[i].LoS[0];
			RowMatrixG_XYZ[1] = epoch->sat[i].LoS[1];
			RowMatrixG_XYZ[2] = epoch->sat[i].LoS[2];
			RowMatrixG_XYZ[3] = 1;

			atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, 4, 1.0);
			atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, 1.0);

			weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
			atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, weight);
		}
	}

	epoch->TryGEOChange=0;		//Reset flag for changing GEO (can be for DOP, singular matrix or protection levels over alarm limits)
	epoch->overMaxHDOP=epoch->overMaxPDOP=epoch->overMaxGDOP=epoch->overMaxHDOPorPDOP=0; //Reset flag for DOP thresholds

	// Invert the Gt*G Matrixes:
	res=cholinv_opt(VectorGtG_NEU, 4);
	if(res==-1) {
		epoch->TryGEOChange=1;
		sprintf(errorstr,"Geometry with singular matrix");
		return -1;
	}
	res=cholinv_opt(VectorGtG_XYZ, 4);
	if(res==-1) {
		epoch->TryGEOChange=1;
		sprintf(errorstr,"Geometry with singular matrix");
		return -1;
	}

	// Compute DOPs
	solution->HDOP = sqrt(VectorGtG_NEU[0] + VectorGtG_NEU[2]);
	solution->VDOP = sqrt(VectorGtG_NEU[5]);
	solution->GDOP = sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5] + VectorGtG_XYZ[9]);
	solution->PDOP = sqrt(VectorGtG_XYZ[0] + VectorGtG_XYZ[2] + VectorGtG_XYZ[5]);
	solution->TDOP = sqrt(VectorGtG_XYZ[9]);


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
	if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
		cholinv_opt(VectorGtWG_NEU, 4);
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
 * Name        : StanfordESAComputationRecursive
 * Description : Recursive function to compute all the possible navigation
 *               solution with all geometries for Stanford-ESA plot
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * char *epochString               I  N/A  String with date in format Year DoY SoD GPSWeek SoW
 * int *k                          IO N/A  Vector indicating the current combination number for a given depth
 * int *kmask                      IO N/A  Vector indicating if a satellite (a row of data)
 *                                           is selected (1) or not (0) for current combination
 * int numsat                      I  N/A  Number of satellites available for computing SBAS solution
 * int depth                       IO N/A  Number of satellites excluded in current combination (until 4 satellites are left)
 * double **G                      I  N/A  Geometry matrix (in NEU) of the satellites used in SBAS solution
 * double *prefits                 I    m  Vector with the prefits of the satellites used in SBAS solution
 * double *weights                 I  m^-2 Vector with the weights of the satellites used in SBAS solution
 *                                         solution of the previous epoch (it is 
 *                                         updated with the solution of the present epoch)
 * TUnkinfo  *unkinfo              I  N/A  Structure containing the information of the unknowns
 * TStdESA *StdESA                 O  N/A  TStdESA struct                                        
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void StanfordESAComputationRecursive (TEpoch *epoch, char *epochString, int *k, int *kmask, int numsat, int depth, double **G, double *prefits, double *weights, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions  *options) {
	int						i;
	int						res1;
	int						nunkvector,nunk;
	unsigned long long int	posx,posy; //Declared as long long int to avoid overflow when PE or PL are very high
	double					dmajor,HPL,VPL,Herror,Verror;
	double					*Vector_GtWG;
	double					*Vector_GtY;
	double					HIR,VIR,quantError,quantPL;
	char					strmask[300],auxstr[300];

	//nkvector=unkinfo->nunkvector;
	//nunk=unkinfo->nunk;
	//This forces to compute the values using only 4 unknowns (X,Y,Z,deltaT).
	//Maybe later Stanford-ESA could be computed taken into account phases or other unknowns
	nunkvector=10;	
	nunk=4;

	//Mount matrix data
	Vector_GtWG=malloc(sizeof(double)*nunkvector);
	Vector_GtY=malloc(sizeof(double)*nunk);

	// Initializing At*W*A and At*W*Y
	for (i=0;i<nunk;i++) {
		Vector_GtY[i]=0;
	}
	for (i=0;i<nunkvector;i++) {
		Vector_GtWG[i]=0;
	}
	
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
				sprintf(auxstr,"%s%c%02d ",strmask,epoch->listConsSatSolutionSBAS[i],epoch->listPRNSatSolutionSBAS[i]);
				sprintf(strmask,"%s",auxstr);
			}
		}
		sprintf(messagestr,"%17s Geometry with singular matrix in Stanford-ESA computation when using %d satellites, with satellites %s",t2doystr(&epoch->t),numsat-depth,strmask);
		printInfo(messagestr,options);
		StdESA->numsamplesSingular++;
	}

	if((numsat-depth)>4) {
		for(i=k[depth];i<=(numsat-depth-1);i++) {
			k[depth+1]=i;
			kmask[i+depth]=0;
			StanfordESAComputationRecursive(epoch,epochString,k,kmask,numsat,depth+1,G,prefits,weights,unkinfo,StdESA,options);
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
						sprintf(auxstr,"%s%c%02d ",strmask,epoch->listConsSatSolutionSBAS[i],epoch->listPRNSatSolutionSBAS[i]);
						sprintf(strmask,"%s",auxstr);
					}
				}
				//Write to file
				fprintf(options->fdstdESALOI," %35s %7.4f %7.4f %6.2f %6.2f %6.2f %6.2f %7.4f %7.4f %8d %7d %s\n",epochString,options->WIRHorThreshold,options->WIRVerThreshold,Herror,Verror,HPL,VPL,HIR,VIR,numsat,numsat-depth,strmask);
			}

		}
	}


	//Free memory
	free(Vector_GtWG);
	free(Vector_GtY);
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
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TSBASdatabox *SBASdatabox       IO N/A  Struct with SBAS data and summary
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 *****************************************************************************/
void SBASSummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TSBASdatabox *SBASdatabox, TOptions *options, TUnkinfo *unkinfo) {

	int			i,j;
	int			indx;
	double		dNEU[3];
	double		HIR,VIR;
	double		Herror,Verror;
	//double		DiscontinuityDuration; 		//Duration in seconds of the discontinuity
	double		NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double		TimeDiff,RinexInputDataTimeDiff;
	static int	NoDataRate=1;
	static int	FirstEpochSum=1;

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

	//Save DOP values
	epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*SBASdatabox->TotalPAEpochs);
	epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*SBASdatabox->TotalPAEpochs);
	epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*SBASdatabox->TotalPAEpochs);
	epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*SBASdatabox->TotalPAEpochs);
	epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*SBASdatabox->TotalPAEpochs);

	epoch->HDOP[SBASdatabox->TotalPAEpochs-1]=solution->HDOP;
	epoch->PDOP[SBASdatabox->TotalPAEpochs-1]=solution->PDOP;
	epoch->GDOP[SBASdatabox->TotalPAEpochs-1]=solution->GDOP;
	epoch->VDOP[SBASdatabox->TotalPAEpochs-1]=solution->VDOP;
	epoch->TDOP[SBASdatabox->TotalPAEpochs-1]=solution->TDOP;

	//Save maximum values of DOP
	if (solution->HDOP>=epoch->MaxHDOP) {
		epoch->MaxHDOP=solution->HDOP;
		memcpy(&epoch->HDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->PDOP>=epoch->MaxPDOP) {
		epoch->MaxPDOP=solution->PDOP;
		memcpy(&epoch->PDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->GDOP>=epoch->MaxGDOP) {
		epoch->MaxGDOP=solution->GDOP;
		memcpy(&epoch->GDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->VDOP>=epoch->MaxVDOP) {
		epoch->MaxVDOP=solution->VDOP;
		memcpy(&epoch->VDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->TDOP>=epoch->MaxTDOP) {
		epoch->MaxTDOP=solution->TDOP;
		memcpy(&epoch->TDOPEpoch,&epoch->t,sizeof(TTime));
	}


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


	    // First index of XYZ
	    indx = unkinfo->par2unk[DR_UNK];

		if (UseReferenceFile==0) {
		    // dNEU differences in relation to apriori position
		    for (i=0;i<3;i++) {
		        dNEU[i] = 0;
   		    	for (j=0;j<3;j++) {
   		        	dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
   		 		}
   			}
		} else {
			// dNEU differences in relation to apriori position from reference file
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
				}
			}
		}

		//Compute error and integrity ratios
		Herror=sqrt(dNEU[0]*dNEU[0]+dNEU[1]*dNEU[1]);
		Verror=fabs(dNEU[2]);

		HIR=Herror/solution->HPL;
		VIR=Verror/solution->VPL;

		//If errors are greater than previous epochs, save value and epoch
		if(Herror>=epoch->MaxHError) {
			epoch->MaxHError=Herror;
			memcpy(&epoch->HerrorEpoch,&epoch->t,sizeof(TTime));
		}

		if(Verror>=epoch->MaxVError) {
			epoch->MaxVError=Verror;
			memcpy(&epoch->VerrorEpoch,&epoch->t,sizeof(TTime));
		}

		if(HIR>=SBASdatabox->HWIR) {
			SBASdatabox->HWIR=HIR;
			memcpy(&SBASdatabox->HWIREpoch,&epoch->t,sizeof(TTime));
		}
	
		if(VIR>=SBASdatabox->VWIR) {
			SBASdatabox->VWIR=VIR;
			memcpy(&SBASdatabox->VWIREpoch,&epoch->t,sizeof(TTime));
		}

		//Update number of MIs
		if(Herror>=solution->HPL) {
			SBASdatabox->NumHMI++;
		}

		if(Verror>=solution->VPL) {
			SBASdatabox->NumVMI++;
		}

		if(Herror>=solution->HPL || Verror>=solution->VPL) {
			SBASdatabox->NumMI++;
		}

		//Save horizontal and vertical error values for percentile computation
		epoch->HError=realloc(epoch->HError,sizeof(double)*epoch->TotalEpochsRef);
		epoch->VError=realloc(epoch->VError,sizeof(double)*epoch->TotalEpochsRef);

		epoch->HError[epoch->TotalEpochsRef-1]=Herror;
		epoch->VError[epoch->TotalEpochsRef-1]=Verror;

	} else if (options->recPosProvided==1 && UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
		epoch->NumNoRefSumSkipped++;
	}

	if(solution->HPL>=SBASdatabox->MaxHPL) {
		SBASdatabox->MaxHPL=solution->HPL;
		memcpy(&SBASdatabox->MaxHPLEpoch,&epoch->t,sizeof(TTime));
	}

	if(solution->VPL>=SBASdatabox->MaxVPL) {
		SBASdatabox->MaxVPL=solution->VPL;
		memcpy(&SBASdatabox->MaxVPLEpoch,&epoch->t,sizeof(TTime));
	}


	//Save horizontal and vertical protection values for percentile computation
	SBASdatabox->HPL=realloc(SBASdatabox->HPL,sizeof(double)*SBASdatabox->TotalPAEpochs);
	SBASdatabox->VPL=realloc(SBASdatabox->VPL,sizeof(double)*SBASdatabox->TotalPAEpochs);

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
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 *****************************************************************************/
void DGNSSSummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo) {

    int         i,j;
    int         indx;
    double      dNEU[3];
    double      Herror,Verror;
	static int	FirstEpochSum=1;


    //If we are in DGNSS mode, only take into account epoch with DGNSS solution
    if (options->solutionMode==DGNSSMode) {
        epoch->TotalEpochsDGNSS++;

		//Save DOP values
		epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*epoch->TotalEpochsDGNSS);
		epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*epoch->TotalEpochsDGNSS);
		epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*epoch->TotalEpochsDGNSS);
		epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*epoch->TotalEpochsDGNSS);
		epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*epoch->TotalEpochsDGNSS);

		epoch->HDOP[epoch->TotalEpochsDGNSS-1]=solution->HDOP;
		epoch->PDOP[epoch->TotalEpochsDGNSS-1]=solution->PDOP;
		epoch->GDOP[epoch->TotalEpochsDGNSS-1]=solution->GDOP;
		epoch->VDOP[epoch->TotalEpochsDGNSS-1]=solution->VDOP;
		epoch->TDOP[epoch->TotalEpochsDGNSS-1]=solution->TDOP;

		//Save maximum values of DOP
		if (solution->HDOP>=epoch->MaxHDOP) {
			epoch->MaxHDOP=solution->HDOP;
			memcpy(&epoch->HDOPEpoch,&epoch->t,sizeof(TTime));
		}
		if (solution->PDOP>=epoch->MaxPDOP) {
			epoch->MaxPDOP=solution->PDOP;
			memcpy(&epoch->PDOPEpoch,&epoch->t,sizeof(TTime));
		}
		if (solution->GDOP>=epoch->MaxGDOP) {
			epoch->MaxGDOP=solution->GDOP;
			memcpy(&epoch->GDOPEpoch,&epoch->t,sizeof(TTime));
		}
		if (solution->VDOP>=epoch->MaxVDOP) {
			epoch->MaxVDOP=solution->VDOP;
			memcpy(&epoch->VDOPEpoch,&epoch->t,sizeof(TTime));
		}
		if (solution->TDOP>=epoch->MaxTDOP) {
			epoch->MaxTDOP=solution->TDOP;
			memcpy(&epoch->TDOPEpoch,&epoch->t,sizeof(TTime));
		}

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

            // First index of XYZ
            indx = unkinfo->par2unk[DR_UNK];

			if (UseReferenceFile==0) {
            	// dNEU differences in relation to apriori position
				for (i=0;i<3;i++) {
					dNEU[i] = 0;
					for (j=0;j<3;j++) {
						dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRover[j])*epoch->receiver.orientationRover[i][j];
					}
				}
			} else {
				// dNEU differences in relation to apriori position from reference file
				for (i=0;i<3;i++) {
					dNEU[i] = 0;
					for (j=0;j<3;j++) {
						dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
					}
				}
			}

            //Compute error and integrity ratios
            Herror=sqrt(dNEU[0]*dNEU[0]+dNEU[1]*dNEU[1]);
            Verror=fabs(dNEU[2]);

            //If errors are greater than previous epochs, save value and epoch
            if(Herror>=epoch->MaxHError) {
                epoch->MaxHError=Herror;
                memcpy(&epoch->HerrorEpoch,&epoch->t,sizeof(TTime));
            }

            if(Verror>=epoch->MaxVError) {
                epoch->MaxVError=Verror;
                memcpy(&epoch->VerrorEpoch,&epoch->t,sizeof(TTime));
            }

            //Save horizontal and vertical error values for percentile computation
            epoch->HError=realloc(epoch->HError,sizeof(double)*epoch->TotalEpochsRef);
            epoch->VError=realloc(epoch->VError,sizeof(double)*epoch->TotalEpochsRef);

            epoch->HError[epoch->TotalEpochsRef-1]=Herror;
            epoch->VError[epoch->TotalEpochsRef-1]=Verror;


		} else if (options->recPosProvided==1 && UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
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
 * int UseReferenceFile            I  N/A  Flag to indicate if a reference file was used
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution *solution       I  N/A  Solution of the filter
 * TOptions  *options              I  N/A  TOptions structure
 * TUnkinfo  *unkinfo              I  N/A  Information on the unknowns of the filter
 *****************************************************************************/
void SummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo) {

    int         i,j;
    int         indx;
    double      dNEU[3];
    double      Herror,Verror;
	static int	FirstEpochSum=1;


	epoch->TotalEpochsSol++;

	//Save DOP values
	epoch->HDOP=realloc(epoch->HDOP,sizeof(double)*epoch->TotalEpochsSol);
	epoch->PDOP=realloc(epoch->PDOP,sizeof(double)*epoch->TotalEpochsSol);
	epoch->GDOP=realloc(epoch->GDOP,sizeof(double)*epoch->TotalEpochsSol);
	epoch->VDOP=realloc(epoch->VDOP,sizeof(double)*epoch->TotalEpochsSol);
	epoch->TDOP=realloc(epoch->TDOP,sizeof(double)*epoch->TotalEpochsSol);

	epoch->HDOP[epoch->TotalEpochsSol-1]=solution->HDOP;
	epoch->PDOP[epoch->TotalEpochsSol-1]=solution->PDOP;
	epoch->GDOP[epoch->TotalEpochsSol-1]=solution->GDOP;
	epoch->VDOP[epoch->TotalEpochsSol-1]=solution->VDOP;
	epoch->TDOP[epoch->TotalEpochsSol-1]=solution->TDOP;

	//Save maximum values of DOP
	if (solution->HDOP>=epoch->MaxHDOP) {
		epoch->MaxHDOP=solution->HDOP;
		memcpy(&epoch->HDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->PDOP>=epoch->MaxPDOP) {
		epoch->MaxPDOP=solution->PDOP;
		memcpy(&epoch->PDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->GDOP>=epoch->MaxGDOP) {
		epoch->MaxGDOP=solution->GDOP;
		memcpy(&epoch->GDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->VDOP>=epoch->MaxVDOP) {
		epoch->MaxVDOP=solution->VDOP;
		memcpy(&epoch->VDOPEpoch,&epoch->t,sizeof(TTime));
	}
	if (solution->TDOP>=epoch->MaxTDOP) {
		epoch->MaxTDOP=solution->TDOP;
		memcpy(&epoch->TDOPEpoch,&epoch->t,sizeof(TTime));
	}


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

		// First index of XYZ
		indx = unkinfo->par2unk[DR_UNK];

		if (UseReferenceFile==0) {
			// dNEU differences in relation to apriori position
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPosition[j])*epoch->receiver.orientation[i][j];
				}
			}
		} else {
			// dNEU differences in relation to apriori position from reference file
			for (i=0;i<3;i++) {
				dNEU[i] = 0;
				for (j=0;j<3;j++) {
					dNEU[i] += (solution->x[indx+j] - epoch->receiver.aproxPositionRef[j])*epoch->receiver.orientationRef[i][j];
				}
			}
		}

		//Compute error and integrity ratios
		Herror=sqrt(dNEU[0]*dNEU[0]+dNEU[1]*dNEU[1]);
		Verror=fabs(dNEU[2]);

		//If errors are greater than previous epochs, save value and epoch
		if(Herror>=epoch->MaxHError) {
			epoch->MaxHError=Herror;
			memcpy(&epoch->HerrorEpoch,&epoch->t,sizeof(TTime));
		}

		if(Verror>=epoch->MaxVError) {
			epoch->MaxVError=Verror;
			memcpy(&epoch->VerrorEpoch,&epoch->t,sizeof(TTime));
		}

		//Save horizontal and vertical error values for percentile computation
		epoch->HError=realloc(epoch->HError,sizeof(double)*epoch->TotalEpochsRef);
		epoch->VError=realloc(epoch->VError,sizeof(double)*epoch->TotalEpochsRef);

		epoch->HError[epoch->TotalEpochsRef-1]=Herror;
		epoch->VError[epoch->TotalEpochsRef-1]=Verror;
	} else if (options->recPosProvided==1 && UseReferenceFile==1 && epoch->receiver.RefPositionAvail==0) {
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
    int     	i,ret;
	int			DOPPos,DOPPosHour;
    double  	dmajor, weight;
    double  	RowMatrixG_NEU[4],RowMatrixG_XYZ[4],FalsePrefit[4];
    double  	VectorGtWG_NEU[10],VectorGtG_NEU[10],VectorGtG_XYZ[10];
	double		DiscontinuityDuration; 		//Duration in seconds of the discontinuity
	double		NoDiscontinuityDuration;	//Number of continuous seconds without discontinuity before the current discontinuity
	double		HDOP,PDOP,GDOP;


	//NOTE: Each of the cases have code in common, but they have been separated in order to avoid losing computation time in if statements,
	//which much of them would have to be inside for loops
	switch(options->SBASplotsDOP) {
		case(SBASplotsHDOPOnly):
			for ( i = 0; i < 4; i++ )   {RowMatrixG_NEU[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < 10; i++ )  {VectorGtWG_NEU[i] = 0.0; VectorGtG_NEU[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, weight);
					atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_NEU, 4);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, 4);
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
			for ( i = 0; i < 4; i++ )   {RowMatrixG_NEU[i] = 0.0; RowMatrixG_XYZ[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < 10; i++ )  {VectorGtWG_NEU[i] = 0.0; VectorGtG_XYZ[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					getLineOfSight(epoch->sat[i].position,epoch->receiver.aproxPosition,RowMatrixG_XYZ);
					RowMatrixG_XYZ[3] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, weight);
					atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, 4, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_XYZ, 4);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, 4);
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
			for ( i = 0; i < 4; i++ )   {RowMatrixG_NEU[i] = 0.0; RowMatrixG_XYZ[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < 10; i++ )  {VectorGtWG_NEU[i] = 0.0; VectorGtG_XYZ[i] = 0.0; VectorGtG_NEU[i] = 0.0;}
			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					getLineOfSight(epoch->sat[i].position,epoch->receiver.aproxPosition,RowMatrixG_XYZ);
					RowMatrixG_XYZ[3] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, weight);
					atwa_atwy_insertline(VectorGtG_XYZ, FalsePrefit, RowMatrixG_XYZ, 0.0, 4, 1.0);
					atwa_atwy_insertline(VectorGtG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, 1.0);
				}
			}
			ret=cholinv_opt(VectorGtG_XYZ, 4);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtG_NEU, 4);
			if(ret==-1) return -1;	//Matrix inverse could no be computed, so no solution is available
			ret=cholinv_opt(VectorGtWG_NEU, 4);
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
			for ( i = 0; i < 4; i++ )   {RowMatrixG_NEU[i] = 0.0; FalsePrefit[i] = 0.0;}
			for ( i = 0; i < 10; i++ )  {VectorGtWG_NEU[i] = 0.0;}

			// Build Geometry Matrix and its Transpose, then store its multiplication in a vector
			for ( i = 0; i < epoch->numSatellites; i++ ) {
				if ( epoch->sat[i].available ) {
					RowMatrixG_NEU[0] = cos(epoch->sat[i].elevation) * sin(epoch->sat[i].azimuth);
					RowMatrixG_NEU[1] = cos(epoch->sat[i].elevation) * cos(epoch->sat[i].azimuth);
					RowMatrixG_NEU[2] = sin(epoch->sat[i].elevation);
					RowMatrixG_NEU[3] = 1;

					weight = epoch->sat[i].measurementWeights[0] * epoch->sat[i].measurementWeights[0];
					atwa_atwy_insertline(VectorGtWG_NEU, FalsePrefit, RowMatrixG_NEU, 0.0, 4, weight);
				}
			}
			ret=cholinv_opt(VectorGtWG_NEU, 4);
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
		if(epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]>=1.1) {
			//There has been a discontinuity
			//Compute DiscontinuityDuration and NoDiscontinuityDuration (stable period before the current discontinuity) for the current discontinuity
			DiscontinuityDuration=epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]-1.;
			NoDiscontinuityDuration=SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]-SBASplots->FirstEpochAvailAfterPrevDisc[LatPos][LonPos]+1.;

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
			fprintf(fdDiscont,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDisc[LatPos][LonPos]+1.,epoch->t.SoD-1.,DiscontinuityDuration,NoDiscontinuityDuration);

			//Update FirstEpochAvailAfterDisc. The current epoch will be the last epoch after the discontinuity
			SBASplots->FirstEpochAvailAfterPrevDisc[LatPos][LonPos]=epoch->t.SoD;
		}

		if (options->SBASHourlyMaps==1) {
			if(epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]>=1.1) {
				//There has been a discontinuity
				//Compute DiscontinuityDuration and NoDiscontinuityDuration (stable period before the current discontinuity) for the current discontinuity
				DiscontinuityDuration=epoch->t.SoD-SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]-1.;
				NoDiscontinuityDuration=SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]-SBASplots->FirstEpochAvailAfterPrevDiscHourly[LatPos][LonPos]+1.;

				//Update the number of epochs affected by the discontinuity (we consider a sliding window of 15 seconds -which starts in the previous epoch-,
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
				fprintf(fdDiscontHour,"%6.2f %7.2f %10.1f %9.1f %8.1f %13.1f\n",latitude,longitude,SBASplots->LastEpochAvailPrevCurrDiscHourly[LatPos][LonPos]+1.,epoch->t.SoD-1.,DiscontinuityDuration,NoDiscontinuityDuration);

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
 * int  *PRNlist                   O  N/A  List of satellites
 * TFilterSolution  *solution      I  N/A  Structure with the information of the 
 *                                         solution
 *****************************************************************************/
void updatePRNlist (TEpoch *epoch, int *PRNlist, TFilterSolution *solution) {
	int i;

	solution->prevNumSatellites = 0;
	solution->prevNumSatellitesGPS = 0;
	for ( i = 0; i < epoch->numSatellites; i++ ) {
		solution->prevNumSatellites++;
		if ( epoch->sat[i].GNSS == GPS ) {
			solution->prevNumSatellitesGPS++;
			PRNlist[i] = epoch->sat[i].PRN;
		} else {
			PRNlist[i] = 0;
		}
	}
}

/*****************************************************************************
 * Name        : Kalman
 * Description : Process the filter for the specified epoch
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TFilterSolution  *solution      IO N/A  Structure with the information of the 
 *                                         previous solution (updated)
 * int  *PRNlist                   IO N/A  List of satellites of the previous epoch
 *                                         (updated)
 * TUnkinfo  *prevUnkinfo          IO N/A  Structure containing the information
 *                                         of the unknowns of the previous epoch
 *                                         (updated)
 * TStdESA *StdESA                 O  N/A  TStdESA struct                                        
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         4 => In SBAS mode and option select best GEO is enabled, process with next GEO or mode
 *                                         3 => Not enough satellites for positioning or DOP too high or geometry with singular matrix.
 *                                              
 *                                              Try to change mode or GEO in SBAS mode or change to SPP in DGNSS mode
 *                                         2 => Initial position wrong, model and Kalman must be relaunched
 *                                         1 => Epoch computed
 *                                         0 => Epoch not computable due to lack of satellites
 *                                        -1 => Epoch not computable due to geometry matrix is singular
 *                                        -2 => Epoch not computable due to GDOP over threshold
 *****************************************************************************/
int Kalman (TEpoch *epoch, TFilterSolution *solution, int *PRNlist, TUnkinfo *prevUnkinfo, TStdESA *StdESA, TOptions *options) {
	double			newcorrelations[MAX_VECTOR_UNK];
	double			stddev2postfit;
	double			newparameterValues[MAX_UNK];
	TUnkinfo		unkinfo;
	TFilterSolution	aux;
	static int		first = 1;
	static TTime	prevT;
	double			distance;
	int				i;
	int				res;
	char			errorstr[200];

	
	if (first) {
		memcpy(&prevT, &epoch->t, sizeof(TTime)); 
	}

	fillUsableSatellites(epoch, options);

	// Step detector for SBAS
	if ( options->stepdetector == 1 ) {
		StepDetector(epoch, options);
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

	// If we are in SBAS processing, and we have less than 4 satellites, 
	// check if we can switch mode, we are in PA, and if adding the unselected satellites due to SBAS we can reach 4 satellites
	// If we are in DGNSS processing, and we have less than 4 satellites, change to SPP 
	if ( epoch->usableSatellites < 4 ) {
		if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
			if ((epoch->usableSatellites+epoch->numsatdiscardedSBAS >= 4 ) && epoch->SwitchPossible == 1 ) {
				if ( (options->switchmode == 1 && options->precisionapproach == PAMODE) || options->switchGEO == 1 ) {
					// Empty print buffers for SATSEL messages
					options->printInBuffer = 3;
					printBuffers(epoch, options);
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
			sprintf(messagestr, "Solution moved from DGNSS to SPP at %17s due to lack of satellites (%d available)", t2doystr(&epoch->t), epoch->usableSatellites);
			printInfo(messagestr, options);
			return 3;
		}
	}

	if (isEpochComputable(epoch)) {
		//Calculate DOP and protection levels
		res = calculateDOP(epoch,solution,errorstr,options);
		if (res<0) {
			//DOP is over the thresholds or geometry with singular matrix
			if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
				if ((epoch->usableSatellites+epoch->numsatdiscardedSBAS >= 4 ) && epoch->SwitchPossible == 1 ) {
					if ( (options->switchmode == 1 && options->precisionapproach == PAMODE) || options->switchGEO == 1 ) {
						if(options->switchmode == 1 && options->switchGEO <= 0) {
							sprintf(messagestr,"%17s %s for GEO %3d. Trying to switch to NPA mode",t2doystr(&epoch->t),errorstr,epoch->SBASUsedGEO);
						} else if ( options->switchmode <=0 && options->switchGEO == 1) {
							sprintf(messagestr,"%17s %s for GEO %3d. Trying to switch GEO",t2doystr(&epoch->t),errorstr,epoch->SBASUsedGEO);
						} else {
							sprintf(messagestr,"%17s %s for GEO %3d. Trying to switch GEO or to NPA mode",t2doystr(&epoch->t),errorstr,epoch->SBASUsedGEO);
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
					sprintf(messagestr,"%17s %s for GEO %3d. Skipping epoch",t2doystr(&epoch->t),errorstr,epoch->SBASUsedGEO);
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
				sprintf(messagestr, "Solution moved from DGNSS to SPP at %17s due to %s", t2doystr(&epoch->t),errorstr);
				printInfo(messagestr, options);
				return 3;
			} else if (options->DGNSS==0) {
				// SPP, PPP (DGNSS switched to SPP will not enter here)
				// Empty print buffers for SATSEL messages
				options->printInBuffer = 2;
				printBuffers(epoch, options);
				printBuffersKalman(epoch, options);
				sprintf(messagestr,"%17s %s. Skipping epoch",t2doystr(&epoch->t),errorstr);
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
						sprintf(messagestr,"%17s %s for GEO %3d. Skipping epoch",t2doystr(&epoch->t),errorstr,epoch->SBASUsedGEO);
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

		// Empty print buffers for SATSEL messages
		options->printInBuffer = 2;
		printBuffers(epoch, options);
		printBuffersKalman(epoch, options);

		memcpy(&aux, solution, sizeof(TFilterSolution));	
		initUnkinfo(epoch, &unkinfo, calculateUnknowns(epoch->numSatellites, options), epoch->numSatellites, fabs(tdiff(&epoch->t,&prevT)), options);
		prepareCorrelation(epoch, solution, PRNlist, &unkinfo, prevUnkinfo, options);
		if (!computeSolution(epoch, &stddev2postfit, solution, newcorrelations, newparameterValues, &unkinfo, StdESA, options)) {
			memcpy(solution, &aux, sizeof(TFilterSolution));
			return 0;
		}
		
		if ( options->receiverPositionSource >= rpCALCULATE ) {
			distance = sqrt((solution->x[0] - epoch->receiver.aproxPosition[0]) * (solution->x[0] - epoch->receiver.aproxPosition[0]) + 
							(solution->x[1] - epoch->receiver.aproxPosition[1]) * (solution->x[1] - epoch->receiver.aproxPosition[1]) + 
							(solution->x[2] - epoch->receiver.aproxPosition[2]) * (solution->x[2] - epoch->receiver.aproxPosition[2]));
			for ( i=0; i<3; i++ ) {
				epoch->receiver.aproxPosition[i] = solution->x[i];
			}
			epoch->receiver.aproxPositionError = solution->dop;
			sprintf(messagestr, "%17s Apriori position updated to: %13.4f %13.4f %13.4f   Distance: %13.4f",t2doystr(&epoch->t),epoch->receiver.aproxPosition[0], epoch->receiver.aproxPosition[1], epoch->receiver.aproxPosition[2], distance);
			printInfo(messagestr, options);
			if (distance > 100) {
				options->printInBuffer = 2;
				printBuffers(epoch, options);
				printBuffersKalman(epoch, options);
				memcpy(solution,&aux,sizeof(TFilterSolution));
				return 2;
			}
			epoch->receiver.receiverSolConverged = 1;
		}

		printFilter(&epoch->t, unkinfo.nunk, solution, options);

		// Preparing values for next epoch
		memcpy(prevUnkinfo,&unkinfo,sizeof(TUnkinfo));
		memcpy(solution->correlations,newcorrelations,sizeof(double)*unkinfo.nunkvector);
		memcpy(solution->parameters,newparameterValues,sizeof(double)*unkinfo.nunk);

		updatePRNlist(epoch, PRNlist, solution);
		
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
		sprintf(messagestr,"%17s Not enough satellites (%d available) to compute solution",t2doystr(&epoch->t),epoch->usableSatellites);
		printInfo(messagestr,options);
		return 0;
	}
}
