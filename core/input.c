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
 * File: input.c
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2024/11/22
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: input
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to serve as "driver" from the different ways
 *  that the data can be stored in the form of files and the rest of the program
 *
 * Function:
 *  This class is in charge of reading the different data formats in which the 
 *  data can be stored, and save it to the internal data structures.
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
 * Change Log: Corrected problem of not properly reading years below 2000
 *                  for RINEX observation and navigation files (Y2K effect).
 *             Changed whatFileTypeIs to improve detection of SP3 files.
 *             Fine-tune in automatically detecting file types.
 *             Security check to better read RINEX clock files not following 
 *                  the standard.
 *             Included input files: SINEX, DCB and GPS_Receiver_Type.
 *             Forward/Backward processing included.
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: Included usable measurement index in TMeasOrder structure to select/deselect
 *                  individual measurements.
 *             Corrected a bug when reading Galileo observations in a RINEX v2.11 file.
 *             Corrected a bug in elevation/azimuth initialisation, which appeared when new 
 *                  satellites without ephemeris data appeared.
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
 * --------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: Included new DCB management.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: No changes in this file.
 * -----------
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
 * Change Log: Added capability to read RINEX 3.02 observation and navigation files.
 *             Added capability to read Fast-PPP columnar files.
 *             Added functions to read files for ESA's tropospheric model.
 *             Modified IONEX read function in order to save all information in header.
 *                      (even though it is not used later on)
 * -----------
 *          gLAB v2.2.1
 * Release: 2014/12/23
 * Change Log: Fixed the disappearance of satellites when interpollating clocks with precise clocks file.
 *                      This ocurred when there were data gap for one satellite, where in that case time stamps
 *                      were not correctly processed
 *             Fixed problem where GPS measurements didn't appear when reading observation files. It only
 *                      happened when the header line SYS / # / OBS TYPES with GPS data was not the first one
 *             Fixed problem reading RINEX 2.11 Navigation files in the case where the values where positive and with no leading zero.
 *             Added initalization value to 9999 to IONEX input data, so in case the IONEX file is empty, it will not compute ionospheric values, instead of using a VTEC of 0
 * -----------
 *          gLAB v2.2.2
 * Release: 2015/03/02
 * Change Log: Fixed gLAB not skipping data when event appeared when reading an epoch in an observation file
 * -----------
 *          gLAB v2.2.3
 * Release: 2015/05/28
 * Change Log: Modified readAntex function in order to read satellite and receiver phase center variations
 * 	       Modified readDCB function in order to be able to read the new header
 * -----------
 *          gLAB v2.2.4
 * Release: 2015/07/01
 * Change Log: Fixed bug in getLback function when the current line was the first line in file
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: Added protection against buffer overflow in getL function.
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
 *             Added addUserError function for reading user-defined error from text file.
 *             Deleted function beforeReadEpochUpdate.
 *             Deleted function afterReadEpochUpdate.
 *             Added function dictionaryUpdate.
 *             Concatenated RINEX, SP3 and CLK files can be read now.
 *             QZSS and IRNSS constellation data is now recognized and properly skipped.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: Added lecture of RINEX v2 GLONASS and GEO navigation files.
 *             Improved data handling for GEO and GLONASS navigation files in RINEX v2 and v3.
 *             Satellite phase center corrections for all constellations are now processed.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added functions to decode RTCM binary files.
 *             Added check for number of entries in SP3 header.
 *             Added check for number of entries in IONEX header.
 *             If a IONEX file has no 'END OF FILE' line, a warning will be printed instead of showing an error.
 *             Fixed GLONASS phase conversion factor to 1 to all frquencys instead of 0, to avoid division by zero
 *                after cheking for pseudorange jumps in checkPseudorangeJumps function.
 *             Clocks from all constellations are now read in RINEX clock files.
 *             Orbits and clock event flags are now read from SP3 and precise clock files (precise clock files from MGEX
 *               have event flags, even though it is not in the RINEX clocks standard).
 *             Start time of SP3 files is now set to the first epoch read, instead of the value given in the header.
 *             Fixed incorrect memory allocation in readAntex function.
 *             Fixed unnecessary memory freeing in readAntex (this made gLAB crash when applying phase center zenital variations)
 *             Fixed bug that made gLAB skip the next line of the observation file after reading a header line with 'SYS / # / OBS TYPES' 
 *               or '# / TYPES OF OBSERV' which had a number of observation types equal to 13 or 9 respectively.
 *             Fixed bug which made gLAB leave a measurement as still available when it had dissapeared in the following RINEX observation header (concatenated file).
 *             Fixed bug in addUserError function that made not to remove a finished user added error measurement in the last satellite
 *               when all used adder error of all satellites ended in the same epoch.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Fixed rare bug that made gLAB crash when handling end of file with SBAS files. It ocurred sometimes when the SBAS data file ended before the observation file.
 *             Fixed incorrect SBAS message time handling when the RINEX-B file did not have the 0.1 second (signal travel time) in the timestamp. This made gLAB use SBAS
 *               messages from the future.
 *             Fixed false detection of missing SBAS messages when reading SBAS files with more than one GEO.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   Fixed a bug that made sometimes gLAB crash when an invalid message was read.
 *               RTCM3 epoch read from binary file is now rouded up to 4th decimal (minimum decimation of gLAB).
 *                 Differences at the 11th decimal were making to discard all reference measurements if
 *                 N-consecutive filter was enabled.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Added check for incorrect header when reading an IONEX file. If all necessary header records are not in the
 *                 file, an error message will be shown instead of crashing.
 *               Fixed a bug when reading a EMS file in SBAS Availability plots mode that made gLAB show an error message
 *                 saying that there were no GEO available for processing.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added functions 'readReferenceFile' and 'readPosFile' for reading a reference 
 *                 position file.
 *               User defined error files and sigma multipath error files now also accept
 *                 commas (',') and semicolons (';') as column separators.
 *               In function 'readRinexObsHeader', gLAB will now estimate the file interval
 *                 (if it is not in the header) by substracting the second epoch minus the
 *                 first epoch. This will be used for computing the total number of epochs
 *                 for the progress bar and for having a rough interval value in the first
 *                 epoch.
 *               When reading the observation header for the first time, gLAB will now estimate
 *                 the file interval, so file interval is available for the decimation funtion
 *                 in the first epoch.
 *               Detection of consecutive missing messages or consecutive is now done for all
 *             	GEO available in the SBAS file, even if they are not used.
 *               An INFO message is printed when a missing or wrong messages is detected for
 *                 any GEO. If consecutive missing or wrong messages are detected, the number
 *                 of consecutive missing or wrong messages will be printed.
 *               SNR can now also be read from S1, S2,... measurements instead of just the flag
 *                 next to the measurements. If both measurements are available, gLAB will
 *                 prefer the S1,S2... measurements (the non quantizied values).
 *               Fixed crash when reading non standard RINEX-B files which do not contain
 *                 the any of these fields in every first line of data: frequency, datalength, 
 *                 receiverindex and source identifier.
 *               Fixed getLback function (backwards line reading) not working when a RINEX-3 
 *                 observation line was very long.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   gLAB can now read backwards RINEX observation files with multiple headers.
 *               Fixed rare bug when reading backwards a file searching for the start of an epoch (the line
 *                 with the timestamp), some measurements with many 0's (for example 20010008.523) could make
 *                 gLAB confuse a line with measurements with the line of start of epoch.
 *               Fixed rare bug not showing progress with some observation files. It ocurred when searching 
 *                 for the start of an epoch (the line with the timestamp) for computing the number of epochs
 *                 in file for computing the current progress.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: gLAB can now read DCB files with the new header format (for example:
 *               'CODE'S 30-DAY GPS P1-C1 DCB SOLUTION, ENDING DAY 306, 2017')
 *             If header format is not recognized when reading a DCB file, gLAB will show an error and exit
 *               instead of continuing and producing undefined behaviour (incorrect results or crashing).
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log:   'readIONEX' function can now read concatenated IONEX files.
 *               Removed 'readIONEXFile' function because it is no longer used.
 *               Removed 'readRinexNavFile' function because it is no longer used.
 *               All input files are now opened "rb" options instead of just "r" (to avoid problems with Linux end of line
 *                 in Windows).
 *               Fixed crash when reading RINEX precise clock files and there was a line entry of a station whose name
 *                 started with 'G' or 'R' or 'E' or 'S' or 'C' or 'J' or 'I' and the remaining three letters of the
 *                 station name where all numbers (for example 'AR S011 2008 05 12 00 10  0.000000  2    0.764667861953E-03').
 *                 This made gLAB believe that it was a satellite data entry instead of station data entry.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log:   Sigma multipath files now accepts comments (starting with '#' symbol) next to the data.
 *               User added error files now accepts comments (starting with '#' symbol) next to the data.
 *               Reference position files now accepts comments (starting with '#' symbol) next to the data.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log:   Added an INFO message when a data gap in the observation RINEX file is found. It
 *                 includes the number of epochs missing and the epoch where the data gap was detected.
 *               Added check for SBAS messages that are not from L1 when reading a RINEX-B file. Now,
 *                 if a message from L5 is found, it will be ignored, instead of decoding it an mixing
 *                 its data with the L1 messages (which disrupted L1 data if messages from L5 had
 *                 the same message types as in L1).
 *               Added capatibility to use RTKlib's output file with geodetic coordinates (in the file,
 *                 they appear as 'lat/lon/height=WGS84/geodetic') as a reference position file. In this
 *                 output file format, the coordinates have the EGM96 geoid model added to the height
 *                 coordinate.
 *               When mixed is not enabled (which nearly always occur), the update of SBAS messages for 
 *                 the mixed GEO is disabled in the 'updateSBASdata' function. This reduces around 20% 
 *                 the processing time in SBAS mode.
 *               In function 'converterRTCM3', some checks and progress bar percentage update now are 
 *                 done every time a start of message is detected, instead of every time a byte of data
 *                 is read from the RTCM3 file (when searching for a new message). This reduces processing
 *                 time when using a RTCM3 file around 50%.
 *               Removed 'dictionaryUpdate' function. The dictionary is now updated when a satellite is read.
 *               Fixed an infinite loop when processing in DGNSS mode with RTCM2 and the RTCM2 file ended before
 *                 the rover observation file. It ocurred after the current epoch was ahead of the last RTCM2
 *                 correction, thus making gLAB infinitely trying to read the next correction even though
 *                 the file had ended.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log:   Added check in SBAS plots mode for data for convergence time in SBAS data file. If there
 *                 is a convergence time of 15 minutes or more, a message is printed with the detected
 *                 convergence time. Otherwise a warning is printed stating that there is no data for
 *                 convergence time.
 *               Added function 'getEpochFromObsFile'. This function reads one line of the observation
 *                 file, reads the timestamp and then moves the file pointer one line back.
 *               Added support for SP3 version d.
 *               If number of entries in the header of the SP3 file does not match the number of entries
 *                 read in the file, gLAB will shown a warning message, instead of showing an error
 *                 message and exiting.
 *               Updated 'readPosFile' function to the save the reference position data with the new
 *                 internal format for SP3 orbits (data is now saved equally spaced in time, adding 0s
 *                  when necessary).
 *               Changed behaviour with SBAS message type 0 (alarm message). Before, if the alarm message
 *                 was not filled with 0, the alarm flag is not triggered. Now, anytime an alarm message
 *                 is received, the alarm will be triggered except when the alarm message is not filled
 *                 with zeros and the alarm message is read as type 2 message.
 *               Fixed memory leak in functions 'readRINEXB' and 'readEMS' due to the condition to free
 *                 memory was never met.
 *               Fixed gLAB not printing the progress bar when the first epoch was an event epoch and the
 *                 following had the same timestamp. This made that the file interval estimation was 0,
 *                 and the number of estimated epochs in file was infinite (double variable overflow),
 *                 therefore, the 0.1% increase percentage of epochs completed was never reached and
 *                 thus the progress bar was not updated.
 *               Fixed infinite loop in backwards processing when an event epoch and the following had the
 *                 same timestamp.
 *               Fixed bug that made not to enable the internal gLAB flag that an alarm message had been
 *                 received when mixed GEO was not enabled. This made that if a GEO received an alarm, it
 *                 entered the one minute cooldown time, but the minute cooldown never ended (due to the
 *                 alarm flag was not enabled). During the cooldown time, all GEO messages must be ignored,
 *                 therefore the GEO data buffer got frozen since the epoch of the alarm received until the 
 *                 end of file. This bug only occured in version 5.3.0.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log:   Added check for wrong measurements or for combinations for the destination
 *                measurement when reading the file for adding user defined error.
 *               SP3 file interval is now computed instead of reading it from the header. If the
 *                 interval in the header did not match the real data interval, SP3 orbit 
 *                 computation did not work.
 *               When converting RTCM2 files to text, the ouput files will now be overwritten instead
 *                of appending the new data at the end.
 *               Fixed infinite loop when a non concatenaded SP3 file had no EOF line at the end (when
 *                 this occurred, the last epoch of data was not saved).
 *               Fixed error message "not a valid RTCM2.x message" with a valid RTCM2.x file. It was due
 *                 to the two last parity bits from the previous message needed to compute the current
 *                 message parity bits. In the first message read (or if a message was reading), the last
 *                 two parity bits wre not known, therefore it is necessary to try with all possible four
 *                 combinations (00, 01, 10 and 11), but it was being checked just with one of them.
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
 * Change Log:   Fixed wrong allocation of satellite slots when header lines '# OF SOLN SATS' and 'PRN LIST'
 *                 were not present in the RINEX clock file.
 *               Fixed satellite clock data being omitted in RINEX clock files when the satellite number
 *                 was below 10 and the PRN number was padded with a space character instead of a '0'.
 *               Fixed SBAS handling of special events (UDREI=15 or alarm message) not being treated every
 *                 second if decimation to 1 or less and the RINEX observation file had a data rate smaller
 *                 than 1 Hz.
 *               Fixed SBAS handling of special events (UDREI=15 or alarm message) being checked twice on the 
 *                 epochs to be processed and decimation was set to a value greater than 1.
 *               Fixed gLAB getting sttuck in an infinite loop when detecting the last epoch of file (in RINEX3
 *                 format only) and the last epoch was an event epoch and it did not have the timestamp on it.
 * -----------
 *          gLAB v5.5.1
 * Release: 2020/12/11
 * Change Log:   Fixed not separating the receiver APC corrections by constellations. This made that
 *                 the last frequency read from the last constellation was the value saved.
 * -----------
 *          gLAB v6.0.0
 * Release: 2024/11/22
 * Change Log:   Added preprocessor directive READNOLOCKENABLED in function 'getL' to select between
 *               Added multi-constellation support (Galileo, GLONASS, GEO, BDS, QZSS and IRNSS).
 *               Added multi-frequency support (all RINEX frequencies).
 *               Added SBAS DFMC processing.
 *                 using or not using non thread locking reading functions (these are not available in
 *                 MAC). To use non thread locking reading functions (which is faster), provide the
 *                 parameter '-DREADNOLOCK' to the compiler.
 *               Optimized 'getL' function code.
 *               Fixed not using SNR data when SNR as a measurement was given in the header, but all
 *                 these measurements were empty in the data lines and the SNR was provided as a flag.
 *               Fixed bug in SBAS 1F which made to discard all corrections when a message type 0 was
 *                 read as a type 2.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#if defined __WIN32__
 	//This is to allow %lld, %llu and %n format specifiers in printf with MinGW
	#define __USE_MINGW_ANSI_STDIO  1
#endif

/* External classes */
#include "dataHandling.h"
#include "input.h"
#include "output.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>


/**************************************
 * Declarations of internal operations
 **************************************/

/*******************************************************************************
 * Name        : twoComplement
 * Description : 2's complement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * unsigned long long int orig      I  N/A  Unsigned integer
 * int n                            I  N/A  Sign bit
 * Returned value (long long int)   O  N/A  Returns the value of 2's complement
 *****************************************************************************/
long long int twoComplement (unsigned long long int orig, int n) {
	long long int result;
	int sign;

	sign = (orig>>(n-1) & 0x01);
	if ( sign == 1 ) result = orig-pow(2,n);
	else result = orig;

	return result;
}

/*****************************************************************************
 * Name       : bitInt
 * Description: Function that returns the value of bit number "bp" in "bt"
 *              as an integer
 * Parameters :
 * Name                           |Da|Unit|Description
 * char bt                         I  N/A  Char byte
 * int bp                          I  N/A  Integer
 * Returned value (int)            O  N/A  Returns the value of bit number "bp" in "bt"
 *****************************************************************************/
int bitInt (char bt, int bp) {
	return (bt >> bp) & 0x01;
}

/*****************************************************************************
 * Name       : bitChar
 * Description: Function that returns the value of bit number "bp" in "bt"
 *              as an char
 * Parameters :
 * Name                           |Da|Unit|Description
 * char bt                         I  N/A  Char byte
 * int bp                          I  N/A  Integer
 * Returned value (char)           O  N/A  Returns the value of bit number "bp" in "bt"
 *****************************************************************************/
char bitChar (char bt, int bp) {
	if ( ( (bt >> bp) & 0x01 ) == 1 ) return '1';
	else return '0';
}

/*****************************************************************************
 * Name        : crc24q
 * Description : parity check of message according to the rtcm standard 10403.1
 * Parameters  :
 * Name                           |Da|Unit|Description
 * unsigned char *msg              I  N/A   Unsigned char array for one message
 *                                          From the preamble to the end of parity bits,
 *                                          one unsigned char includes 8 bits of the message
 * int len                         I  bytes Message length in bytes(0-1023)
 * Returned value (int)            O  N/A   Returns the value of check. 
 *                                          check==0, fail the parity check
 *                                          check==1, pass the parity check
 *****************************************************************************/
int crc24q (unsigned char *msg, int len) {
	int key = 0x1864CFB;
	//25 bit polynomial for this CRC, with bits 0,1,3,4,5,6,7,10,11,14,17,18,23,24 equal to 1
	unsigned long int parity = 0;
	unsigned long int data = 0;
	unsigned long int remainderVal = 0;
	int check = 0;
	int pos = 0;
	int j;
	unsigned int a, b;
	int shift = 1;
	int n = 0;

	for (j=0;j<3;j++) {
		a = msg[len+3+j];
		b = msg[j];
		parity += ( a<<(16-j*8) );
		remainderVal += ( b<<(16-j*8) );
	}

	data = remainderVal;
	for (shift=1;shift<=BYTEBITS*(len+3);shift++) {
		pos = shift%BYTEBITS;
		n = shift/BYTEBITS;
		if ( pos == 0 ) {
			pos = 8;
			n = n-1;
		}
		if (shift > BYTEBITS*len) data = ( data<<1 );
		else data = ( data<<1 ) + bitInt(msg[3+n], 8-pos);

		if ( (data & 0x1000000) != 0 ) {
			remainderVal = data^key;
			data = remainderVal;
		}
		else if( shift == BYTEBITS*(len+3) ) remainderVal = data;
	}

	if ( remainderVal == parity ) check = 1;

	return check;
}

/*****************************************************************************
 * Name       : getMSGtype
 * Description: get the message type
 * Parameters :
 * Name                      |Da|Unit|Description
 * unsigned char *msg         I  N/A   The pointer of the array of one message
 *                                     The message bits are kept in bytes, 
 *                                     i.e. every unsigned char in array 
 *                                     includes 8 bits of binary information.
 * Returned value (int)       O  N/A   The message type
 *****************************************************************************/
int getMSGtype (unsigned char *msg) {
	unsigned int message_type;
	unsigned int a = 0;
	unsigned int b = 0;

	a = msg[3];
	b = msg[4];
	message_type = (a<<4) + (b>>4);

	return message_type;
}

/*****************************************************************************
 * Name       : getRTCMheader
 * Description: decode the header of Type 1001,1002,1003,1004
 * Parameters :
 * Name                      |Da|Unit|Description
 * TRTCM2header *header       IO  N/A  The pointer of structure TRTCM2header
 * unsigned char *msg         I   N/A  The pointer of the array of one message
 *                                     The message bits are kept in bytes, 
 *                                     i.e. every unsigned char in array 
 *                                     includes 8 bits of binary information.
 *****************************************************************************/
TRTCM3header *getRTCMheader (TRTCM3header *header, unsigned char *msg) {
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int d = 0;
	unsigned int e = 0;

	a = msg[4];
	b = msg[5];
	header->station_id = ((a<<8) & 0xF00) + b;
	a = msg[6];
	b = msg[7];
	d = msg[8];
	e = msg[9];
	header->epoch_time = (a<<22) + (b<<14) + (d<<6) + (e>>2);
	//header->synchronous = bitChar(msg[8], 1);
	header->synchronous = bitChar(msg[9], 1); // Yixie find a bug in the previous one
	a = msg[10];
	header->gps_no = bitInt(msg[9], 0) * 16 + (a>>4);
	header->smooth_indicator = bitChar(msg[10], 3);
	//header->smooth_interval = (msg[10] & 0x03);
	header->smooth_interval = (msg[10] & 0x07); // Yixie find a bug in the previous one

	return header;
}

/*****************************************************************************
 * Name       : getBitStr
 * Description: get the message binary string, one bit per char.
 * Parameters :
 * Name                      |Da|Unit|Description
 * char *out_arr              IO  N/A  The pointer of the char array.
 *                                     one message bit per char
 * unsigned char *in_arr      I   N/A  The pointer of the unsigned char array.
 *                                     Each char contains 8 bits of information.
 * int n                      I   N/A  Number of bytes
 *****************************************************************************/
char *getBitStr (char *out_str, unsigned char *in_arr, int n) {
	int i, j;

	for ( j = 0; j < n; j++ ) {
		for ( i = 0; i < 8; i++ ) {
			out_str[8 * ( j + 1 ) - ( i + 1 )] = bitChar(in_arr[j], i);
		}
	}
	out_str[8 * n] = '\0';

	return out_str;
}

/*****************************************************************************
 * Name       : getLockT
 * Description: get minimum lock time and the range of the lock time.
 * Parameters :
 * Name                 |Da|Unit|Description
 * TlockTime *lt         IO  N/A  The pointer of structure TlockTime
 * int indicator         I   N/A  The lock time indicator which is 
 *                                obtained from the message
 *****************************************************************************/
TlockTime *getLockT (TlockTime *lt, int indicator) {
	int level;
	level = indicator / 24;

	switch(level) {
		case 0:
		lt->minimum = indicator;
		lt->range_lowerLimit = 0;
		lt->range_upperLimit = 24;
		break;
	case 1:
		lt->minimum = indicator * 2 - 24;
		lt->range_lowerLimit = 24;
		lt->range_upperLimit = 72;
		break;
	case 2:
		lt->minimum = indicator * 4 - 120;
		lt->range_lowerLimit = 72;
		lt->range_upperLimit = 168;
		break;
	case 3:
		lt->minimum = indicator * 8 - 408;
		lt->range_lowerLimit = 168;
		lt->range_upperLimit = 360;
		break;
	case 4:
		lt->minimum = indicator * 16 - 1176;
		lt->range_lowerLimit = 360;
		lt->range_upperLimit = 744;
		break;
	case 5:
		if ( indicator != 127 ) {
			lt->minimum = indicator * 32 - 3096;
			lt->range_lowerLimit = 744;
			lt->range_upperLimit = 937;
		}
		else {
			lt->minimum = 9999; //means no minimum
			lt->range_lowerLimit = 937;
			lt->range_upperLimit = 9999; //means no upper limit
		}
		break;
	}

	return lt;
}

/*****************************************************************************
 * Name       : readMSG1004
 * Description: decode the body of message type 1004
 * Parameters :
 * Name                |Da|Unit|Description
 * TMSG1004 *sc         IO  N/A  The pointer of structure TMSG1004
 * int ns               I   N/A  Number of satellites
 * char *body_str       I   N/A  The pointer of the binary string
 *                               of body information for MSG1004.
 *                               one bit of binary per char
 *****************************************************************************/
TMSG1004 *readMSG1004 (TMSG1004 *sc, int ns, char *body_str) {
	char 	sid[7];
	char 	l1_code;
	char 	l1_pseudo[25];
	char 	l1_partPhase[21];
	char 	l1_lock[8];
	char 	l1_N[9];
	char 	l1_cnr[9];
	char 	l2_code[3];
	char 	differ[15];
	char 	l2_partPhase[21];
	char 	l2_lock[8];
	char 	l2_cnr[9];
	char 	*endptr;
	int 	i,len;
	unsigned long long int a;

	len=(int)strlen(body_str);

	for ( i = 0; i < ns; i++ ) {
		getstr(sid,body_str,len, 125 * i, 6);
		l1_code=body_str[6 + 125 * i];
		getstr(l1_pseudo, body_str,len, 7 + 125 * i, 24);
		getstr(l1_partPhase, body_str,len, 31 + 125 * i, 20);
		getstr(l1_lock, body_str,len, 51 + 125 * i, 7);
		getstr(l1_N, body_str,len, 58 + 125 * i, 8);
		getstr(l1_cnr, body_str,len, 66 + 125 * i, 8);
		getstr(l2_code, body_str,len, 74 + 125 * i, 2);
		getstr(differ, body_str,len, 76 + 125 * i, 14);
		getstr(l2_partPhase, body_str,len, 90 + 125 * i, 20);
		getstr(l2_lock, body_str,len, 110 + 125 * i, 7);
		getstr(l2_cnr, body_str,len, 117 + 125 * i, 8);

		sc[i].satellite_id = strtol(sid, &endptr, 2);
		if ( l1_code == '0' ) sc[i].l1_code_indicator = 0;
		else sc[i].l1_code_indicator = 1;

		sc[i].l1_pseudoR = strtol(l1_pseudo, &endptr, 2) * 0.02; 
		sc[i].l1_lock_indicator = strtol(l1_lock, &endptr, 2); 
		sc[i].l1_N_ambiguity = strtol(l1_N, &endptr, 2) * 299792.458; 
		sc[i].l1_cnr = strtol(l1_cnr, &endptr, 2) * 0.25; 
		sc[i].l2_code_indicator = strtol(l2_code, &endptr, 2); 
		sc[i].l2_lock_indicator = strtol(l2_lock, &endptr, 2); 
		sc[i].l2_cnr = strtol(l2_cnr, &endptr, 2) * 0.25; 
		a = strtol(l1_partPhase, &endptr, 2);
		sc[i].l1_part_phaseR = twoComplement(a, 20) * 0.0005;
		a = strtol(differ, &endptr, 2);
		sc[i].pseudoR_differ = twoComplement(a, 14) * 0.02;       
		a = strtol(l2_partPhase, &endptr, 2);
		sc[i].l2Phase_l1Pseudo = twoComplement(a, 20) * 0.0005;
	}

	return &sc[0];
}

/*****************************************************************************
 * Name       : readMSG1005
 * Description: decode message type 1005
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG1006 *sc           IO  N/A  The pointer of structure TMSG1006
 * unsigned char *msg     I  N/A   the pointer of the array of one message
 *                                 The message bits are kept in bytes, 
 *                                 i.e. every unsigned char in array 
 *                                 includes 8 bits of binary information.
 *****************************************************************************/
TMSG1006 *readMSG1005 (TMSG1006 *sc, unsigned char *msg) {
	long long int x, y, z;
	unsigned long long int a, b, d, e, f;
	
	a = msg[4];
	b = msg[5];
	sc->station_id = ((a<<8) & 0xF00)+b;
	sc->gps_indicator = bitChar(msg[6], 1);
	sc->glonass_indicator = bitChar(msg[6], 0);
	sc->referStation_indicator = bitChar(msg[7], 6);
	a = (msg[7] & 0x3F);
	b = msg[8];
	d = msg[9];
	e = msg[10];
	f = msg[11];
	x = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_x = twoComplement(x, 38) * 0.0001;
	sc->oscillator_indicator = bitChar(msg[12], 7);
	a = (msg[12] & 0x3F);
	b = msg[13];
	d = msg[14];
	e = msg[15];
	f = msg[16];
	y = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_y = twoComplement(y, 38) * 0.0001;
	a = (msg[17] & 0x3F);
	b = msg[18];
	d = msg[19];
	e = msg[20];
	f = msg[21];
	z = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_z = twoComplement(z, 38) * 0.0001;
	sc->antenna_height = 0.000;

	return sc;
}

/*****************************************************************************
 * Name       : readMSG1006
 * Description: decode message type 1006
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG1006 *sc           IO  N/A  The pointer of structure TMSG1006
 * unsigned char *msg     I  N/A   the pointer of the array of one message
 *                                 The message bits are kept in bytes, 
 *                                 i.e. every unsigned char in array 
 *                                 includes 8 bits of binary information.
 *****************************************************************************/
TMSG1006 *readMSG1006 (TMSG1006 *sc, unsigned char *msg) {
	long long int x, y, z;
	unsigned long long int a, b, d, e, f;
	
	a = msg[4];
	b = msg[5];
	sc->station_id = ((a<<8) & 0xF00)+b;
	sc->gps_indicator = bitChar(msg[6], 1);
	sc->glonass_indicator = bitChar(msg[6], 0);
	sc->referStation_indicator = bitChar(msg[7], 6);
	a = (msg[7] & 0x3F);
	b = msg[8];
	d = msg[9];
	e = msg[10];
	f = msg[11];
	x = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_x = twoComplement(x, 38) * 0.0001;
	sc->oscillator_indicator = bitChar(msg[12], 7);
	a = (msg[12] & 0x3F);
	b = msg[13];
	d = msg[14];
	e = msg[15];
	f = msg[16];
	y = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_y = twoComplement(y, 38) * 0.0001;
	a = (msg[17] & 0x3F);
	b = msg[18];
	d = msg[19];
	e = msg[20];
	f = msg[21];
	z = (a<<32) + (b<<24) + (d<<16) + (e<<8) + f;
	sc->ecef_z = twoComplement(z, 38) * 0.0001;
	a = msg[22];
	b = msg[23];
	sc->antenna_height = ((a<<8) + b) * 0.0001;

	return sc;
}

/*****************************************************************************
 * Name       : readMSG1008
 * Description: decode message type 1008
 * Parameters :
 * Name                 |Da|Unit|Description
 * TMSG1008 *sc          IO  N/A  The pointer of structure TMSG1008
 * unsigned char *msg    I  N/A   the pointer of the array of one message
 *                                The message bits are kept in bytes, 
 *                                i.e. every unsigned char in array 
 *                                includes 8 bits of binary information.
 *****************************************************************************/
TMSG1008 *readMSG1008 (TMSG1008 *sc, unsigned char *msg) {
	int n, m;
	unsigned long long int a, b;
	int i;

	a = msg[4];
	b = msg[5];
	sc->station_id = ((a<<8) & 0xF00)+b;
	n = msg[6];
	sc->descriptor_no = n;
	for (i=0;i<n;i++) sc->descriptor[i] = msg[7+i];
	sc->descriptor[n] = '\0';
	sc->setup_id = msg[7+n];
	m = msg[8+n];
	sc->serialNum_no = m;
	for (i=0;i<m;i++) sc->serialNum[i] = msg[9+i];
	sc->serialNum[m] = '\0';

	return sc;
}

/*****************************************************************************
 * Name        : readRTCM3header
 * Description : Read the information of the RINEX observation header from a RTCM binary file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   O  N/A  TEpoch structure
 * TEpoch *epochDGNSS              O  N/A  TEpoch structure
 * TRTCM3 *rtcm3                   I  N/A  TRTCM3 structure
 *****************************************************************************/
void readRTCM3header (TEpoch *epoch, TEpoch *epochDGNSS, TRTCM3 *rtcm3) {
	char					*ca;
	enum MeasurementType	meas;

	if(epochDGNSS->receiver.aproxPosition[0]==rtcm3->msg1006.ecef_x && epochDGNSS->receiver.aproxPosition[1]==rtcm3->msg1006.ecef_y 
			&& epochDGNSS->receiver.aproxPosition[2]==rtcm3->msg1006.ecef_z && rtcm3->numObsHeaderRead>0) {
		return;
	}

	rtcm3->numObsHeaderRead++;

	// Source of file
	epochDGNSS->source = RTCM3;
	
	// Antenna type
	strcpy(epochDGNSS->receiver.antenna.type,rtcm3->msg1008.descriptor);

	// Separate the anntena.type into antenna and radome
	strcpy(epochDGNSS->receiver.antenna.type_ant,epochDGNSS->receiver.antenna.type);
	ca = strstr(epochDGNSS->receiver.antenna.type_ant," ");
	if ( ca != NULL ) {
		*ca = '\0';
		strcpy(epochDGNSS->receiver.antenna.type_radome,&ca[1]);
		trim(epochDGNSS->receiver.antenna.type_radome,(int)strlen(epochDGNSS->receiver.antenna.type_radome));
	}

	// ARP
	epochDGNSS->receiver.ARP[2] = rtcm3->msg1006.antenna_height; // H
	epochDGNSS->receiver.ARP[1] = 0.0; // E
	epochDGNSS->receiver.ARP[0] = 0.0; // N

	// Types of Observations
	// "C1C","L1C","S1C","C2P","L2P","S2P"
	epochDGNSS->measOrder[GPS].nDiffMeasurements = 6;
	epochDGNSS->measOrder[GPS].nDiffMeasurementsRINEXHeader = 6;
	epochDGNSS->measOrder[GPS].GNSS = GPS;
	epochDGNSS->numGNSSHeader = 1;
	epochDGNSS->numPrintGNSS = 1;
	meas = C1C;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 0;
	epochDGNSS->measOrder[GPS].ind2Meas[0] = meas;
	meas = L1C;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = GPSl1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 1;
	epochDGNSS->measOrder[GPS].ind2Meas[1] = meas;
	meas = S1C;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 2;
	epochDGNSS->measOrder[GPS].ind2Meas[2] = meas;
	meas = C2P;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 3;
	epochDGNSS->measOrder[GPS].ind2Meas[3] = meas;
	meas = L2P;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = GPSl2;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 4;
	epochDGNSS->measOrder[GPS].ind2Meas[4] = meas;
	meas = S2P;
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 5;
	epochDGNSS->measOrder[GPS].ind2Meas[5] = meas;

	// Antenna a priori position
	epochDGNSS->receiver.aproxPosition[0] = rtcm3->msg1006.ecef_x;
	epochDGNSS->receiver.aproxPosition[1] = rtcm3->msg1006.ecef_y;
	epochDGNSS->receiver.aproxPosition[2] = rtcm3->msg1006.ecef_z;

	//Save reference station (if it is new)
	if(epoch->receiver.numRecStation==0) {
		epoch->receiver.RecStationCoord=malloc(sizeof(double*));
		epoch->receiver.RecStationCoord[0]=malloc(sizeof(double)*3);
		memcpy(epoch->receiver.RecStationCoord[0],epochDGNSS->receiver.aproxPosition,sizeof(double)*3);
		epoch->receiver.numRecStation++;
	} else {
		if(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][0]!=epochDGNSS->receiver.aproxPosition[0] 
				|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][1]!=epochDGNSS->receiver.aproxPosition[1]
				|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][2]!=epochDGNSS->receiver.aproxPosition[2]) {
			//Station coordinates are differents from the previous read
			epoch->receiver.RecStationCoord=realloc(epoch->receiver.RecStationCoord,sizeof(double*)*(epoch->receiver.numRecStation+1));
			epoch->receiver.RecStationCoord[epoch->receiver.numRecStation]=malloc(sizeof(double)*3);
			memcpy(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation],epochDGNSS->receiver.aproxPosition,sizeof(double)*3);
			epoch->receiver.ChangedStaEpoch=realloc(epoch->receiver.ChangedStaEpoch,sizeof(TTime)*epoch->receiver.numRecStation);
			memcpy(&epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1],&epoch->t,sizeof(TTime));
			epoch->receiver.numRecStation++;
		}
	}

	//Build SNR lookup index
	epochDGNSS->measOrder[GPS].meas2SNRInd[C1C]=epochDGNSS->measOrder[GPS].meas2Ind[S1C];
	epochDGNSS->measOrder[GPS].meas2SNRInd[L1C]=epochDGNSS->measOrder[GPS].meas2Ind[S1C];
	epochDGNSS->measOrder[GPS].meas2SNRInd[C2P]=epochDGNSS->measOrder[GPS].meas2Ind[S2P];
	epochDGNSS->measOrder[GPS].meas2SNRInd[L2P]=epochDGNSS->measOrder[GPS].meas2Ind[S2P];
}

/*****************************************************************************
 * Name        : readRTCM3obs
 * Description : Read the information of the RINEX observation header from a RTCM binary file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epochDGNSS              O  N/A  TEpoch structure
 * TRTCM3 *rtcm3                   I  N/A  TRTCM3 structure
 * TOptions *options               I  N/A  TOptions structure
 *****************************************************************************/
int readRTCM3obs (TEpoch *epochDGNSS, TRTCM3 *rtcm3, TOptions *options) {
	int						totalSeconds;
	int						mins, intHour;
	unsigned int			i;
	int						j,k,l;
	int						lli1, lli2;
	int						ind, snr1, snr2;
	static int				lastCSindex=0;
	double					hour_d, mins_d, sec, doubleHour;
	double					C1, L1, S1, C2, L2, S2;
	struct tm				tm;
	char 					auxstr[15];

	// Time handling
	totalSeconds = (int)((double)(rtcm3->header.epoch_time) / 1000.);
	totalSeconds = totalSeconds-(int)((86400. * floor(totalSeconds / 86400.)));
	// Hours
	hour_d = (double)(totalSeconds) / 3600.0;
	rtcm3->hour = (int)(floor(hour_d));
	intHour = (int)(floor(hour_d));
	doubleHour = floor(hour_d);
	// Minutes
	mins_d = (hour_d-doubleHour) * 60.0;
	mins = (int)(floor(mins_d));
	// Seconds
	sec = (mins_d-(double)(mins)) * 60.0;

	// Check if a day has passed
	if ( rtcm3->doWeHaveHeader > 2 && intHour < (int)rtcm3->previousHour ) {
		doy2date((int)options->rtcmYear, (int)options->rtcmDoy + 1, &options->rtcmMonth, &options->rtcmDay);
	}

	//Save previous epoch
	memcpy(&epochDGNSS->PreviousEpoch,&epochDGNSS->t,sizeof(TTime));

	// Fill up both MJDN and SoD
	tm.tm_year = options->rtcmYear - 1900; // Julian date 2415020.0, generally referred to as J1900.0
	tm.tm_mon  = options->rtcmMonth - 1; // January corresponds to 0
	tm.tm_mday = options->rtcmDay;
	tm.tm_hour = intHour;
	tm.tm_min  = mins;
	tm.tm_sec  = (int)sec;
	options->rtcmDoy = date2doy(options->rtcmYear, options->rtcmMonth, options->rtcmDay);
	epochDGNSS->t.MJDN = MJDN(&tm);
	epochDGNSS->t.SoD = (double)tm.tm_hour * 3600.0 + (double)tm.tm_min * 60.0 + sec;

	//Round seconds to the 4th decimal (minimum decimation of gLAB) to avoid problems
	// with decimals when comparing the epoch with another read from a RINEX file
	sprintf(auxstr,"%.4f",epochDGNSS->t.SoD);
	epochDGNSS->t.SoD=atof(auxstr);

	//Remove index values from previous epoch
	for (j=0;j<epochDGNSS->numSatellites;j++) {
		epochDGNSS->satIndex[epochDGNSS->sat[j].GNSS][epochDGNSS->sat[j].PRN]=-1;
		epochDGNSS->sat2Printpos[j]=-1;
	}

	//Set variables for number of satellites
	epochDGNSS->numPrintGNSS=1;
	epochDGNSS->GNSS2PrintPos[GPS]=0;
	epochDGNSS->numSatellites = rtcm3->header.gps_no;
	epochDGNSS->numSatellitesGNSS[GPS]=rtcm3->header.gps_no;
	//Set satellite number for all other constellations to 0
	for(j=1;j<MAX_GNSS;j++) {
		epochDGNSS->numSatellitesGNSS[j]=0;
	}

	// Loop for every satellite
	for ( i = 0; i < rtcm3->header.gps_no; i++ ) {
		lli1 = 0; lli2 = 0;

		epochDGNSS->sat[i].PRN = rtcm3->msg1004[i].satellite_id;
		ind = rtcm3->msg1004[i].satellite_id;
		epochDGNSS->sat[i].GNSS = GPS;
		epochDGNSS->satIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]=i;
		C1 = rtcm3->msg1004[i].l1_pseudoR + rtcm3->msg1004[i].l1_N_ambiguity;
		L1 = (C1 + rtcm3->msg1004[i].l1_part_phaseR) * GPSf1 / c0;
		S1 = rtcm3->msg1004[i].l1_cnr;
		snr1 = min(max(floor(S1/6),1),9);
		if ( rtcm3->L1flagLLI[ind] == 1 ) lli1 = 1;
		C2 = C1 + rtcm3->msg1004[i].pseudoR_differ;
		L2 = (C1 + rtcm3->msg1004[i].l2Phase_l1Pseudo) * GPSf2 / c0;
		S2 = rtcm3->msg1004[i].l2_cnr;
		snr2 = min(max(floor(S2/6),1),9);
		if ( rtcm3->L2flagLLI[ind] == 1 ) lli2 = 1;

		// C1C
		ind = 0;
		epochDGNSS->sat[i].meas[ind].value = C1;
		epochDGNSS->sat[i].meas[ind].rawvalue = C1;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 1;
		epochDGNSS->sat[i].meas[ind].SNRflag = (int)snr1;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = SNRtable[(int)snr1];
		epochDGNSS->sat[i].meas[ind].SNRvalue = S1; //SNR will be read from SNR measurement
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// L1C
		ind = 1;
		epochDGNSS->sat[i].meas[ind].value = L1;
		epochDGNSS->sat[i].meas[ind].rawvalue = L1;
		epochDGNSS->sat[i].meas[ind].LLI = lli1;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 1;
		epochDGNSS->sat[i].meas[ind].SNRflag = (int)snr1;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = SNRtable[(int)snr1];
		epochDGNSS->sat[i].meas[ind].SNRvalue = S1; //SNR will be read from this variable
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// S1C
		ind = 2;
		epochDGNSS->sat[i].meas[ind].value = S1;
		epochDGNSS->sat[i].meas[ind].rawvalue = S1;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 0;
		epochDGNSS->sat[i].meas[ind].SNRflag = 0;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = 0;
		epochDGNSS->sat[i].meas[ind].SNRvalue = S1; //SNR will be read from this variable
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// C2P
		ind = 3;
		epochDGNSS->sat[i].meas[ind].value = C2;
		epochDGNSS->sat[i].meas[ind].rawvalue = C2;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 1;
		epochDGNSS->sat[i].meas[ind].SNRflag = (int)snr2;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = SNRtable[(int)snr2];
		epochDGNSS->sat[i].meas[ind].SNRvalue = S2; //SNR will be read from SNR measurement
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// L2P
		ind = 4;
		epochDGNSS->sat[i].meas[ind].value = L2;
		epochDGNSS->sat[i].meas[ind].rawvalue = L2;
		epochDGNSS->sat[i].meas[ind].LLI = lli2;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 1;
		epochDGNSS->sat[i].meas[ind].SNRflag = (int)snr2;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = SNRtable[(int)snr2];
		epochDGNSS->sat[i].meas[ind].SNRvalue = S2; //SNR will be read from SNR measurement
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// S2P
		ind = 5;
		epochDGNSS->sat[i].meas[ind].value = S2;
		epochDGNSS->sat[i].meas[ind].rawvalue = S2;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].hasSNRflag = 0;
		epochDGNSS->sat[i].meas[ind].SNRflag = 0;
		epochDGNSS->sat[i].meas[ind].SNRflagdBHz = 0;
		epochDGNSS->sat[i].meas[ind].SNRvalue = S2; //SNR will be read from this variable
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// Update satellites' dictionary
		if (epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]==-1) {
			epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]=lastCSindex;
			lastCSindex++;
		}

		//Fill pending measurements
		if (options->MeasSelected[REFSTAPOS][epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]==MEASUNSELECTED) {
			FillMeasurements(epochDGNSS->sat[i].GNSS,epochDGNSS->sat[i].PRN,i,epochDGNSS,options);
		}
	}

	//Create list with order of printing for satellites
	l=0;
	for(j=0;j<epochDGNSS->numPrintGNSS;j++) {
		for(k=0;k<epochDGNSS->numSatellites;k++) {
			if (epochDGNSS->GNSS2PrintPos[epochDGNSS->sat[k].GNSS]==j) {
				epochDGNSS->printIndex2satIndex[l]=k;
				l++;
			}
		}
	}

	// Update the previous hour to control if a day has passed
	rtcm3->previousHour = intHour;

	return 1;
}

/*****************************************************************************
 * Name        : converterRTCM3
 * Description : Converter from RTCM v3.x to RINEX v2.11 and v3.00
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor of the data that is being read
 * TRTCM3  *rtcm3                  I  N/A  TRTCM3 structure
 * char  *fileRINEXpointer         I  N/A  Indicates the full path and filename where to save the RINEX
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * TEpoch  *epochDGNSS             O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Return the status of the corrections
 *                                         1 => Corrections read
 *                                         2 => End of file
 *                                         3 => RTCM version 3 detected succesfully
 *****************************************************************************/
int converterRTCM3 (FILE *fd, TRTCM3 *rtcm3, char *fileRINEXpointer, TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options) {
	FILE			*frin=NULL;
	int				i;
	unsigned int	j;
	int				chk = 0;
	int				out = 0;
	int 			ind;
	int				ret;
	unsigned char	ch;
	unsigned char	frame[1030];
	unsigned int	len1, len2, len;
	unsigned int	msgType;

	struct stat 	filestat;	//This is to get the file size
	double			filesize;
	unsigned int	CurrentPos=0;
	double			CurrentPercentage;
	double			PreviousPercentage=-1;

	if (printProgressConvert==1 ) {
		fstat(fileno(fd), &filestat);
		filesize = (double)filestat.st_size;
		fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",0.0,"",options->ProgressEndCharac);
		fflush_function(options->terminalStream);
	}

	if ( options->RTCMmode == ConvertRTCM3 ) {
		frin = fopen(fileRINEXpointer, "wa");
	}
	
	while ( !feof_function(fd) && out == 0 ) {

		ch = fgetc_function(fd);
		CurrentPos++;
		if ( feof_function(fd) != 0 ) {
			if (options->RTCMmode == ConvertRTCM3) fclose(frin);
			return 2;
		}
		if ( ch == 0xD3 ) {
			//moved code
			if (printProgressConvert==1) {
				//Update counter after reading 10KB. As this check is entered every time a byte is read,
				//this avoids slowing a lot the processing due to constant progress bar updating
				//if (CurrentPos%1024==0) {
					CurrentPercentage=100.*(double)(CurrentPos)/filesize;
					if ((CurrentPercentage-PreviousPercentage)>=0.1) {
						if (options->ProgressEndCharac=='\r') {
							//Printing to a terminal
							fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
							//In Windows, cursor is not disabled
							fflush_function(options->terminalStream);
						} else {
							//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
							if ((int)CurrentPercentage!=(int)PreviousPercentage) {
								fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
								fflush_function(options->terminalStream);
							}
						}
						PreviousPercentage=CurrentPercentage;
					}
				//}
			}

			for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
				rtcm3->L1flagLLI[i] = 0;
				rtcm3->L2flagLLI[i] = 0;
			}
			if ( rtcm3->doWeHaveAntennaPos && rtcm3->doWeHaveAntennaName && rtcm3->doWeHaveHeader == 0 ) rtcm3->doWeHaveHeader = 1;
			if ( rtcm3->doWeHaveHeader >= 1 ) {
				if ( options->RTCMmode == ProcessRTCM3 ) {
					readRTCM3header(epoch, epochDGNSS, rtcm3);
					if(rtcm3->doWeHaveHeader == 1 ) out = 1;
				} else if(rtcm3->doWeHaveHeader == 1 ) {
					if ( options->RTCMmode == RTCMCheckVersion ) return 3;
					writeHeaderRINEXo(frin, rtcm3, options);
					rtcm3->doWeHaveHeader = 2;
					//continue;
				}
				if(rtcm3->doWeHaveHeader == 1 ) rtcm3->doWeHaveHeader = 2;
			}
			if ( rtcm3->counter > 200 && rtcm3->doWeHaveHeader == 0 ) {
				if ( rtcm3->doWeHaveAntennaPos == 0 ) {
					rtcm3->msg1006.ecef_x = 0.0;
					rtcm3->msg1006.ecef_y = 0.0;
					rtcm3->msg1006.ecef_z = 0.0;
					rtcm3->doWeHaveAntennaPos = 1;
				}
				if ( rtcm3->doWeHaveAntennaName == 0 && rtcm3->doWeHaveHeader == 0 ) {
					rtcm3->msg1008.station_id = 0;
					strcpy(rtcm3->msg1008.descriptor, "UNKNOWN");
					rtcm3->doWeHaveAntennaName = 1;
				}
			}
			//end of moved code

			frame[0] = ch;
			ret = fread(frame + 1, 1, 2, fd); //The return value is read to avoid warning of not read return value
			len1 = (frame[1] & 0x03);
			len2 = (frame[2] & 0xFF);
			len = len1 * 256 + len2;
			ret = fread(frame + 3, 1, len + 3, fd); //The return value is read to avoid warning of not read return value
			chk = crc24q(frame, len);

			if ( chk == 1 ) {
				msgType = getMSGtype(frame);
				switch ( msgType ) {
					case 1004:
						rtcm3->header.message_type = msgType;
						getRTCMheader(&rtcm3->header, frame);
						getBitStr(rtcm3->content_str, frame + 11, len - 8);
						readMSG1004(rtcm3->msg1004, rtcm3->header.gps_no, rtcm3->content_str);
						for ( j = 0; j < rtcm3->header.gps_no; j++ ) {
							ind = rtcm3->msg1004[j].satellite_id;
							if ( rtcm3->L1prevLLI[ind] == -9999 ) rtcm3->L1prevLLI[ind] = (int)rtcm3->msg1004[j].l1_lock_indicator;
							else if ( rtcm3->msg1004[j].l1_lock_indicator < (unsigned int)rtcm3->L1prevLLI[ind] || rtcm3->msg1004[j].l1_lock_indicator == 0 ) {
								rtcm3->L1flagLLI[ind] = 1;
								rtcm3->L1prevLLI[ind] = (int)rtcm3->msg1004[j].l1_lock_indicator;
							}
							if ( rtcm3->L2prevLLI[ind] == -9999 ) rtcm3->L2prevLLI[ind] = (int)rtcm3->msg1004[j].l2_lock_indicator;
							else if ( rtcm3->msg1004[j].l2_lock_indicator < (unsigned int)rtcm3->L2prevLLI[ind] || rtcm3->msg1004[j].l2_lock_indicator == 0 ) {
								rtcm3->L2flagLLI[ind] = 1;
								rtcm3->L2prevLLI[ind] = (int)rtcm3->msg1004[j].l2_lock_indicator;
							}
						}
						if ( rtcm3->doWeHaveHeader >= 2 && out == 0 ) {
							if ( options->RTCMmode == ProcessRTCM3 ) {
								//ret = readRTCM3obs(epochDGNSS, rtcm3, options);
								readRTCM3obs(epochDGNSS, rtcm3, options);
								out = 1;
							} else {
								if ( options->RTCMmode == RTCMCheckVersion ) return 3;
								writeRINEXo(frin, rtcm3, options);
							}
							rtcm3->doWeHaveHeader++;
						}
						rtcm3->counter++;
						break;
					case 1005:
						rtcm3->msg1006.message_type = msgType;
						readMSG1005(&rtcm3->msg1006, frame);
						rtcm3->doWeHaveAntennaPos = 1;
						rtcm3->counter++;
						break;
					case 1006:
						rtcm3->msg1006.message_type = msgType;
						readMSG1006(&rtcm3->msg1006, frame);
						rtcm3->doWeHaveAntennaPos = 1;
						rtcm3->counter++;
						break;
					case 1008:
						rtcm3->msg1008.message_type = msgType;
						readMSG1008(&rtcm3->msg1008, frame);
						rtcm3->doWeHaveAntennaName = 1;
						rtcm3->counter++;
						break;
					default:
						break;	
				}
			}
		}
	}
	
	ret +=1; //This to avoid variable not used warning
	if ( options->RTCMmode == ConvertRTCM3 ) fclose(frin);
	else if ( feof_function(fd) != 0 ) return 2;

	return 1;
}

/******************************************************************************
 * Name        : readFile
 * Description : Read the input file. Starts from the point which has 
 *               an offset from the beginning of the file and get READWORDSNO
 *               bytes, write per byte in one char of the array. 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fp                        I   N/A  The pointer of the input file
 * TdataRead *data                 IO  N/A  The pointer of the struct TdataRead
 * int *checkControl               O   N/A  The pointer to readFile status
 *****************************************************************************/
TdataRead *readFile (FILE *fp, TdataRead *data, int *checkControl) { 
	int i = 0;
	int l = 0;
	char ch;
	int fs;

	fs = fseek(fp, data->offset, SEEK_SET);
	if ( fs == 0 ) {
		while ( l < READWORDSNO ) {
			ch = fgetc_function(fp);
			if ( feof_function(fp) ) {
				*checkControl = 1;
				data->indicator_end = 1;
				break;
			}
			i++;
			if ( ferror_function(fp) != 0 ) {
				*checkControl = -1;
				break;
			}
			if ( (ch & 0x40)==0x40 ) {
				data->ch_str[l] = ch;
				l++;
			}
		}
		data->ch_str[READWORDSNO] = '\0';
		data->offset = data->offset + i;
	}

	return data;
}

/*****************************************************************************
 * Name        : decodeWords
 * Description : decode the encrypted bytes which follow "Byte Format Rule" 
 *               ("6" of "8" format)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *out_arr                   IO  N/A  The pointer of the char array.
 *                                          one message bit per char  
 * char *in_arr                    I   N/A  The pointer of the char array.
 *                                          Each char contains one encrypted byte.
 * int n                           I   N/A  Number of bytes 
 *****************************************************************************/
char decodeWords (char *out_arr, char *in_arr, int n) {
	int 	i, j;
	char 	indicator_word = '1';
	
	for ( j = 0; j < n; j++ ) {
		if ( (bitChar(in_arr[j], 6) == '1' ) && (bitChar(in_arr[j], 7) == '0') ) {
			for ( i = 0; i < BYTEFORMATBIT; i++ ) {
				out_arr[BYTEFORMATBIT*j+i] = bitChar(in_arr[j], i);
			}
		} else indicator_word = '0';
	}

	return indicator_word;
}

/*****************************************************************************
 * Name        : parityCheck
 * Description : parity check of message according to the RTCM standard 2.3
 *               is identical as the one in GPS/SPS signal specification
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *msg                       I   N/A String with the binary values 
 *                                         one message bit per char
 * char *cw                        IO  N/A The pointer of char array cw
 *                                         cw[0]-cw[23] are the decoded bits of 
 *                                         information
 *                                         cw[24] is the bit containing the 
 *                                         parity check result.
 *                                         cw[24]=='0', fail the parity check
 *                                         cw[24]=='1', pass the parity check
 * int *last2bits                  I   N/A Last two bits of parity bits from 
 *                                         last word.
 *                                         last2bits[0]: bit 30
 *                                         last2bits[1]: bit 29
 *****************************************************************************/
char *parityCheck (char *msg, char *cw, int *last2bits) {
	const int 	a = 2;
	int 		i;
	char 		check = '0';
	int 		old_d29 = last2bits[1];
	int 		old_d30 = last2bits[0];
	char 		ch[31];
	int 		aux[30];
	char 		originalParity[PARITYBIT+1];
	char 		computedParity[PARITYBIT+1];

	for ( i = 0; i < 24; i++ ) {
		switch ( msg[i] ) {
			case '0': 
				 aux[i] = old_d30 - 0;
				 break;
			case '1':
				 aux[i] = 1 - old_d30;
				 break;
			default:
				 //This is for the case we are checking if file is RTCM v2.x, but ends up being RTCM v3.x
				 aux[i] = 0;
				 break;
		}
	}

	aux[24] = (old_d29+aux[0]+aux[1]+aux[2]+aux[4]+aux[5]+aux[9]+aux[10]+aux[11]+aux[12]+aux[13]+aux[16]+aux[17]+aux[19]+aux[22])%a;
	aux[25] = (old_d30+aux[1]+aux[2]+aux[3]+aux[5]+aux[6]+aux[10]+aux[11]+aux[12]+aux[13]+aux[14]+aux[17]+aux[18]+aux[20]+aux[23])%a;
	aux[26] = (old_d29+aux[0]+aux[2]+aux[3]+aux[4]+aux[6]+aux[7]+aux[11]+aux[12]+aux[13]+aux[14]+aux[15]+aux[18]+aux[19]+aux[21])%a;
	aux[27] = (old_d30+aux[1]+aux[3]+aux[4]+aux[5]+aux[7]+aux[8]+aux[12]+aux[13]+aux[14]+aux[15]+aux[16]+aux[19]+aux[20]+aux[22])%a;
	aux[28] = (old_d30+aux[0]+aux[2]+aux[4]+aux[5]+aux[6]+aux[8]+aux[9]+aux[13]+aux[14]+aux[15]+aux[16]+aux[17]+aux[20]+aux[21]+aux[23])%a;
	aux[29] = (old_d29+aux[2]+aux[4]+aux[5]+aux[7]+aux[8]+aux[9]+aux[10]+aux[12]+aux[14]+aux[18]+aux[21]+aux[22]+aux[23])%a;

	for ( i = 0; i < 30; i++ ) {
		switch ( aux[i] ) {
			case 0:
				ch[i] = '0';
				break;
			case 1:
				ch[i] = '1';
				break;
		}
	}

	ch[30] = '\0';

	getstr(computedParity,  ch, (int)strlen(ch), 24, PARITYBIT);
	getstr(originalParity, msg, (int)strlen(msg), 24, PARITYBIT);
	if (strcmp( computedParity,originalParity) == 0 ) check = '1';
	memcpy(cw, ch, 24);
	cw[24] = check;

	return &cw[0];
}

/*****************************************************************************
 * Name        : getLast2bits
 * Description : get the last two bits from the parity bits of last word.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *msg                       I   N/A String with the binary values 
 *                                         one message bit per char. 
 * int *last2bits                  IO  N/A Last two bits of parity bits
 *                                         last2bits[0]: bit 30
 *                                         last2bits[1]: bit 29  
 *****************************************************************************/
int *getLast2bits (char *msg, int *last2bits) {
	int i;

	for ( i=28;i<30;i++ ) {
		switch ( msg[i] ) {
			case '0':
				last2bits[29-i] = 0;
				break;
			case '1':
				last2bits[29-i] = 1;
				break;
		}
	}

	return &last2bits[0];
}

/*****************************************************************************
 * Name        : decodeHeader
 * Description : decode the header of message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TRTCM2header *head              IO  N/A The pointer of struct TRTCM2header
 * char *header_str                I   N/A String with the binary values 
 *                                         one message bit per char
 *                                         only includes the two words for
 *                                         header of each message
 *****************************************************************************/
TRTCM2header *decodeHeader (TRTCM2header *head, char *header_str) {
	char 	type[MSGTYPEBIT+1];
	char 	sid[STATIONIDBIT+1];
	char 	zcount[ZCOUNTBIT+1];
	char 	sequence[SEQUENCENOBIT+1];
	char 	dataword[DATAWORDNOBIT+1];
	char 	*endptr;
	int		len;

	len=(int)strlen(header_str);

	getstr(type,header_str,len,8,MSGTYPEBIT);
	head->message_type = strtol(type,&endptr,2);
	if ( head->message_type == 0 ) head->message_type = 64;
	getstr(sid,header_str,len,14,STATIONIDBIT);
	head->station_id = strtol(sid,&endptr,2);
	getstr(zcount,header_str,len,24,ZCOUNTBIT);
	head->modi_zcount = 0.6 * strtol(zcount,&endptr,2);
	getstr(sequence,header_str,len,37,SEQUENCENOBIT);
	head->sequence_no = strtol(sequence,&endptr,2);
	getstr(dataword,header_str,len,40,DATAWORDNOBIT);
	head->dataword_no = strtol(dataword,&endptr,2);
	getstr(head->station_health,header_str,len,45,STATIONHEALTHBIT);

	return head;
}

 /****************************************************************************
 * Name       : readMSG1
 * Description: decode RTCM v2.x message type 1
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG1 *sc              O  N/A  The pointer of structure TMSG1
 * int ns                 I  N/A  Number of satellites in the message
 * char *body_str         I  N/A  String with the binary values one message bit per char
 *                                only includes the words for body of each message
 *****************************************************************************/
TMSG1 *readMSG1 (TMSG1 *sc, int ns, char *body_str) {
	char 					scale;
	char 					udre[3];
	int  					number_udre;
	char 					sid[6];
	char 					prc[17];
	char 					rrc[9];
	char 					iod[9];
	char 					*endptr;
	int 					i,len;
	unsigned long long int 	a;

	len=(int)strlen(body_str);

	for (i=0;i<ns;i++){
		scale = body_str[0+SATELLITEBIT*i];
		getstr(udre,body_str,len,1+SATELLITEBIT*i,2);
		getstr(sid,body_str,len,3+SATELLITEBIT*i,5);
		getstr(prc,body_str,len,8+SATELLITEBIT*i,16);
		getstr(rrc,body_str,len,24+SATELLITEBIT*i,8);
		getstr(iod,body_str,len,32+SATELLITEBIT*i,8);
		
		if ( scale == '0' ) sc[i].scale_factor = 0.002;
		else sc[i].scale_factor = 0.032;
		
		number_udre = strtol(udre,&endptr,2);
		switch( number_udre ) {
			case 0:
//				sc[i].udre_upperlimit = 1.0;
//				sc[i].udre_lowerlimit = 0.0;
				sc[i].udre = 0;
				break;
			case 1:
//				sc[i].udre_upperlimit = 4.0;
//				sc[i].udre_lowerlimit = 1.0;
				sc[i].udre = 1;
				break;
			case 2:
//				sc[i].udre_upperlimit = 8.0;
//				sc[i].udre_lowerlimit = 4.0;
				sc[i].udre = 2;
				break;
			case 3:
//				sc[i].udre_upperlimit = 10.0;
//				sc[i].udre_lowerlimit = 8.0;
				sc[i].udre = 3;
				break;
		} 
		sc[i].satellite_id = strtol(sid,&endptr,2);
		if ( sc[i].satellite_id == 0 ) sc[i].satellite_id = 32;
		a = strtol(prc,&endptr,2);
		sc[i].prc = twoComplement(a,16) * sc[i].scale_factor * 10;
		a = strtol(rrc,&endptr,2);
		sc[i].rrc = twoComplement(a,8) * sc[i].scale_factor;
		sc[i].iod = strtol(iod,&endptr,2); 
	}

	return &sc[0];	
}

 /****************************************************************************
 * Name       : readMSG2
 * Description: decode RTCM v2.x message type 1
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG2 *sc              O  N/A  The pointer of structure TMSG2
 * int ns                 I  N/A  Number of satellites in the message
 * char *body_str         I  N/A  String with the binary values one message bit per char
 *                                only includes the words for body of each message
 *****************************************************************************/
TMSG2 *readMSG2 (TMSG2 *sc, int ns, char *body_str) {
	char 					scale;
	char 					udre[3];
	int  					number_udre;
	char 					sid[6];
	char 					dprc[17];
	char 					drrc[9];
	char 					iod[9];
	char 					*endptr;
	int 					i,len;
	unsigned long long int 	a;

	len=(int)strlen(body_str);

	for (i=0;i<ns;i++) {
		scale = body_str[0+SATELLITEBIT*i];
		getstr(udre,body_str,len,1+SATELLITEBIT*i,2);
		getstr(sid,body_str,len,3+SATELLITEBIT*i,5);
		getstr(dprc,body_str,len,8+SATELLITEBIT*i,16);
		getstr(drrc,body_str,len,24+SATELLITEBIT*i,8);
		getstr(iod,body_str,len,32+SATELLITEBIT*i,8);
		
		if ( scale == '0' ) sc[i].scale_factor = 0.002;
		else sc[i].scale_factor = 0.032;
		
		number_udre = strtol(udre,&endptr,2);
		switch( number_udre ) {
			case 0:
//				sc[i].udre_upperlimit = 1.0;
//				sc[i].udre_lowerlimit = 0.0;
				sc[i].udre = 0;
				break;
			case 1:
//				sc[i].udre_upperlimit = 4.0;
//				sc[i].udre_lowerlimit = 1.0;
				sc[i].udre = 1;
				break;
			case 2:
//				sc[i].udre_upperlimit = 8.0;
//				sc[i].udre_lowerlimit = 4.0;
				sc[i].udre = 2;
				break;
			case 3:
//				sc[i].udre_upperlimit = 10.0;
//				sc[i].udre_lowerlimit = 8.0;
				sc[i].udre = 3;
				break;
		} 
		sc[i].satellite_id = strtol(sid,&endptr,2);
		if ( sc[i].satellite_id == 0 ) sc[i].satellite_id = 32;
		a = strtol(dprc,&endptr,2);
		sc[i].delta_prc = twoComplement(a,16) * sc[i].scale_factor * 10;
		a = strtol(drrc,&endptr,2);
		sc[i].delta_rrc = twoComplement(a,8) * sc[i].scale_factor;
		sc[i].iod = strtol(iod,&endptr,2); 
	}

	return &sc[0];	
}

 /****************************************************************************
 * Name       : readMSG3
 * Description: decode RTCM v2.x message type 1
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG3 *sc              O  N/A  The pointer of structure TMSG3
 * char *body_str         I  N/A  String with the binary values one message bit per char
 *                                only includes the words for body of each message
 *****************************************************************************/
TMSG3 *readMSG3 (TMSG3 *sc, char *body_str) {
	char 					x[33];
	char 					y[33];
	char 					z[33];
	char 					*endptr;
	int						len;
	unsigned long long int 	a;

	len=(int)strlen(body_str);

	getstr(x,body_str,len,0,32);
	getstr(y,body_str,len,32,32);
	getstr(z,body_str,len,64,32);
	a = strtol(x,&endptr,2);
	sc->x_coord = twoComplement(a,32) * 0.01;
	a = strtol(y,&endptr,2);
	sc->y_coord = twoComplement(a,32) * 0.01;
	a = strtol(z,&endptr,2);
	sc->z_coord = twoComplement(a,32) * 0.01;

	return sc;
}

 /****************************************************************************
 * Name       : readMSG24
 * Description: decode RTCM v2.x message type 1
 * Parameters :
 * Name                  |Da|Unit|Description
 * TMSG24 *sc             O  N/A  The pointer of structure TMSG24
 * char *body_str         I  N/A  String with the binary values one message bit per char
 *                                only includes the words for body of each message
 *****************************************************************************/
TMSG24 *readMSG24 (TMSG24 *sc, char *body_str) {
	char 					x[39];
	char 					y[39];
	char 					z[39];
	char 					ah[19];
	char 					*endptr;
	int						len;
	unsigned long long int 	a;

	len=(int)strlen(body_str);

	getstr(x,body_str,len,0,38);
	getstr(y,body_str,len,40,38);
	getstr(z,body_str,len,80,38);
	a = strtol(x,&endptr,2);
	sc->x_coord = twoComplement(a,38) * 0.0001;
	a = strtol(y,&endptr,2);
	sc->y_coord = twoComplement(a,38) * 0.0001;
	a = strtol(z,&endptr,2);   
	sc->z_coord = twoComplement(a,38) * 0.0001; 
	sc->system_indicator = body_str[118];
	sc->AH_indicator = body_str[119];
	if ( sc->AH_indicator == '1' ) {
		getstr(ah,body_str,len,120,18);
		sc->antenna_height = strtol(ah,&endptr,2) * 0.0001;
	}

	return sc;
}

/*****************************************************************************
 * Name        : converterRTCM2
 * Description : Converter from RTCM v2.x to ASCII file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE *fd                        I  N/A  File descriptor of the data that is being read
 * TRTCM2 *rtcm2                   I  N/A  TRTCM2 structure
 * char *fileASCIIcorrections      O  N/A  Indicates the full path and filename where to save the corrections in ASCII
 * char *fileASCIIantenna          O  N/A  Indicates the full path and filename where to save the antenna in ASCII
 * TEpoch  *epochDGNSS             O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Return the status of the corrections
 *                                        -1 => Error reading file
 *                                         1 => Corrections read / End of file
 *                                         2 => RTCM version 2 detected succesfully
 *                                         3 => RTCM version 2 not detected
 *****************************************************************************/
int converterRTCM2 (FILE *fd, TRTCM2 *rtcm2, char *fileASCIIcorrections, char *fileASCIIantenna, TEpoch *epochDGNSS, TOptions *options) {

	int				i;
	int 			ret, out = 0;
	double			filesize;
	double			CurrentPos;
	double			CurrentPercentage;
	double			PreviousPercentage=-1;
	struct stat 	filestat;	//This is to get the file size
	FILE 			*fout, *fnew;
	
	if (printProgressConvert==1 ) {
		fstat(fileno(fd), &filestat);
		filesize = (double)filestat.st_size;
		fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",0.0,"",options->ProgressEndCharac);
		//In Windows, cursor is not disabled
		fflush_function(options->terminalStream);
	}

	
	if ( options->RTCMmode == ConvertRTCM2 ) {
		fnew = fopen(fileASCIIcorrections, "w");
		fout = fopen(fileASCIIantenna, "w");
	}

	if ( rtcm2->firstPass == 0 ) {
		readFile(fd, &rtcm2->dataRead, &rtcm2->checkControl);
		strcpy(rtcm2->allwords_str, rtcm2->dataRead.ch_str);
		rtcm2->l = strlen(rtcm2->allwords_str);
		rtcm2->firstPass = 1;
	}

	while ( rtcm2->i < (READWORDSNO+LEFTLIMIT) && out == 0 ) {
		if (printProgressConvert==1) {
			CurrentPos = (double)ftell(fd);
			CurrentPercentage=100.*CurrentPos/filesize;
			if ((CurrentPercentage-PreviousPercentage)>=0.1) {
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
					//In Windows, cursor is not disabled
					fflush_function(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
						fflush_function(options->terminalStream);
					}
				}
				PreviousPercentage=CurrentPercentage;
			}
		}
			

		switch ( rtcm2->my_state ) {
			case Initial:
				if ( ((unsigned int)rtcm2->i + LEFTLIMIT) > rtcm2->l ) {
					// Check binary RTCM version
					if ( options->RTCMmode == RTCMCheckVersion ) return 3;
					rtcm2->my_state = EndOfString;
				} else {
					//RTCM2 parity computation depends on the last 2 bits of the previous message, therefore we need
					//to try with the four possibilities, as with the first message decode we don't know the last
					//two bits or a message in between may have been lost
					for(i=0;i<4;i++) {
						switch(i) {
							case 0:
							 	rtcm2->last2bits[0]=0; rtcm2->last2bits[1]=0;
							 	break;
							case 1:
								rtcm2->last2bits[0]=1; rtcm2->last2bits[1]=0;
								break;
							case 2:
								rtcm2->last2bits[0]=0; rtcm2->last2bits[1]=1;
								break;
							default: //i==3
								rtcm2->last2bits[0]=1; rtcm2->last2bits[1]=1;
								break;
						}
						rtcm2->indicator_word = decodeWords(rtcm2->word_current, rtcm2->allwords_str + rtcm2->i, 5);
						parityCheck(rtcm2->word_current, rtcm2->correctedWord, rtcm2->last2bits);
						getLast2bits(rtcm2->word_current, rtcm2->last2bits);
						if ( rtcm2->indicator_word == '0' ) {
							if(i==3) rtcm2->i = rtcm2->i + 1;
						} else {
							if ( rtcm2->correctedWord[24] == '0') {
								if(i==3) rtcm2->i = rtcm2->i + 1;
							} else { 
								rtcm2->correctedWord[24] = '\0';
								getstr(rtcm2->preamble, rtcm2->correctedWord, (int)strlen(rtcm2->correctedWord), 0, PREAMBLEBIT); 
								if ( strcmp(rtcm2->preamble, "01100110") == 0 ) {
									rtcm2->my_state = HeaderReading;
									rtcm2->i = rtcm2->i + 5;
									break;
								} else {
									if(i==3) rtcm2->i = rtcm2->i + 1;
								}
							}
						}
					}
				}
				break;
			case HeaderReading:
				strncpy(rtcm2->header_str, rtcm2->correctedWord, 24);
				rtcm2->indicator_word = decodeWords(rtcm2->word_current, rtcm2->allwords_str + rtcm2->i, 5);
				parityCheck(rtcm2->word_current, rtcm2->correctedWord, rtcm2->last2bits);
				getLast2bits(rtcm2->word_current, rtcm2->last2bits);
				rtcm2->i = rtcm2->i + 5;
				rtcm2->my_state = Initial;
				if ( rtcm2->indicator_word == '1' ) {
					if ( rtcm2->correctedWord[24] == '1' ) {
						strncpy(rtcm2->header_str+24,rtcm2->correctedWord, 24);
						rtcm2->header_str[2*CONTENTBIT] = '\0';
						decodeHeader(&rtcm2->header, rtcm2->header_str);
						rtcm2->my_state = BodyReading;
						rtcm2->indicator_message = '1';
					}
				}
				break;
			case BodyReading:
				for ( rtcm2->k = 0; rtcm2->k < rtcm2->header.dataword_no; rtcm2->k++ ) {
					rtcm2->indicator_word = decodeWords(rtcm2->word_current, rtcm2->allwords_str+rtcm2->i + rtcm2->k * 5, 5);
					parityCheck(rtcm2->word_current, rtcm2->correctedWord, rtcm2->last2bits);
					getLast2bits(rtcm2->word_current, rtcm2->last2bits);
					if ( rtcm2->indicator_word == '1' ) {
						if ( rtcm2->indicator_message == '1' ) {
							if ( rtcm2->correctedWord[24] == '0' ) rtcm2->indicator_message = '0';
							strncpy(rtcm2->body_str+CONTENTBIT*rtcm2->k, rtcm2->correctedWord, CONTENTBIT);   
						} 
					} else rtcm2->indicator_message = '0';
				} 
				rtcm2->i = rtcm2->i + rtcm2->header.dataword_no * 5;
				rtcm2->body_str[rtcm2->header.dataword_no*CONTENTBIT] = '\0';
				rtcm2->my_state = EndOneMessage;
				break;
			case EndOneMessage:
				// Check binary RTCM version
				if ( options->RTCMmode == RTCMCheckVersion ) return 2;
				ret = writeRTCM2ascii(fout, fnew, rtcm2, epochDGNSS, options);
				if ( options->RTCMmode == ProcessRTCM2 && ret == bdrCORRECTIONSmsg1 ) out = 1;
				if ( ((unsigned int)rtcm2->i + LEFTLIMIT) > rtcm2->l ) rtcm2->my_state = EndOfString;
				else rtcm2->my_state = Initial;
				break;
			case EndOfString:
				if ( rtcm2->dataRead.indicator_end == 1 ) rtcm2->my_state = EndOfFile;
				else {
					getstr(rtcm2->leftwords_str, rtcm2->allwords_str, (int)strlen(rtcm2->allwords_str), rtcm2->i, rtcm2->l - rtcm2->i);
					readFile(fd, &rtcm2->dataRead, &rtcm2->checkControl);
					rtcm2->l1 = strlen(rtcm2->leftwords_str);
					memcpy(rtcm2->allwords_str, rtcm2->leftwords_str, rtcm2->l1);
					memcpy(rtcm2->allwords_str + rtcm2->l1, rtcm2->dataRead.ch_str, READWORDSNO);
					rtcm2->allwords_str[rtcm2->l1 + READWORDSNO] = '\0';
					rtcm2->l = strlen(rtcm2->allwords_str);
					rtcm2->my_state = Initial;
					rtcm2->i = 0;
				}
				break;
			case EndOfFile:
				rtcm2->i = READWORDSNO + LEFTLIMIT;
				break;
		}
	}

	if ( options->RTCMmode == ConvertRTCM2 ) {
		fclose(fout);
		fclose(fnew);
	} else if ( options->RTCMmode == ProcessRTCM2 ) {
		if ( rtcm2->i >= READWORDSNO + LEFTLIMIT || rtcm2->dataRead.indicator_end == 1 ) {
			if(feof_function(fd)){
				rtcm2->checkControl = 2;
			} else {
				rtcm2->checkControl = 1;
			}
		}
	}

	return rtcm2->checkControl;
}

/*****************************************************************************
 * Name        : getL
 * Description : Standard multipurpose input reader from files. Valid for 
 *               Windows, Linux and Mac files.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *lineptr                  O  N/A  Buffer to write to
 * int  *n                         O  N/A  Length of buffer (excluding '\n' and '\r')
 * FILE  *stream                   I  N/A  Input stream file
 * Returned value (int)            O  N/A  Return the number of characters read
 *                                         -1 on failure to read
 *****************************************************************************/
int getL (char *lineptr, int *n, FILE *stream) {
	
	#ifndef READNOLOCKENABLED
		//If READNOLOCK is not enabled, use fgets to get similar performance as the fgetc loop
		if(fgets(lineptr,MAX_INPUT_LINE,stream)==NULL) return -1;
		*n=strcspn(lineptr,"\r\n");
		if(*n>=(MAX_INPUT_LINE-3)) return -1; //Line too long, quit reading because line does not fit in buffer
		lineptr[*n]='\0';
		return (*n);
	#else
		//If fgetc_unlocked is enabled, use the fgetc loop instead of fgets as it outperforms the fgets
		register int	rd; 	//The "register" keyword is to indicate the compiler to try to save this variable in a CPU
								//register instead of in memory, so it has faster access times
		*n = 0;
		do {
			rd=fgetc_function(stream);
			switch(rd) {
				case '\r':
					lineptr[*n] = '\0';
					fgetc_function(stream);
					return (*n);
					break;
				case '\n':
					lineptr[*n]='\0';
					return (*n);
					break;
				case '\0':
					lineptr[*n]=rd;
					return (*n);
					break;
				case EOF:
					if (*n==0) return -1;
					else {
						lineptr[*n]='\0';
						return (*n);
					}
					break;
				default:
					lineptr[*n] = rd;
					(*n)++;
					if(*n>=MAX_INPUT_LINE-3) return -1; //Line too long, quit reading to avoid buffer overflow
					break;
			}
		} while (1);

		return -1;

		/*while ((rd=fgetc_function(stream))!=EOF) {
			if (rd=='\r' || rd=='\0' || rd=='\n') { // Character 13 is ^M (for Windows)
				if(rd=='\r') {
					lineptr[*n] = '\n';
					(*n)++;
					lineptr[*n]='\0';
					fgetc_function(stream);
				} else {
					lineptr[*n]=rd;
					if (rd!='\0') {
						(*n)++;
						lineptr[*n]='\0';
					}
				}
				break;
			} else {
				lineptr[*n] = rd;
				(*n)++;
				if(*n>=MAX_INPUT_LINE-3) return -1; //Line too long, quit reading to avoid buffer overflow
			}
		}
		
		if (rd==EOF && (*n)==0) return -1;
		else return (*n);*/
	#endif
}

/*****************************************************************************
 * Name        : getLNoComments
 * Description : Standard multipurpose input reader from files. Valid for
 *               Windows, Linux and Mac files. When a hash ('#') is found in the line,
 *               from this character from the end of line the data read will be
 *               ommited in the data buffer.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *lineptr                  O  N/A  Buffer to write to
 * int  *n                         O  N/A  Length of buffer (excluding '\n' and '\r')
 * FILE  *stream                   I  N/A  Input stream file
 * Returned value (int)            O  N/A  Return the number of characters read
 *                                         -1 on failure to read
 *****************************************************************************/
int getLNoComments (char *lineptr, int *n, FILE *stream) {

	#ifndef READNOLOCKENABLED
		//If READNOLOCK is not enabled, use fgets to get similar performance as the fgetc loop
		if(fgets(lineptr,MAX_INPUT_LINE,stream)==NULL) return -1;
		*n=strcspn(lineptr,"#\r\n");
		if(*n>=(MAX_INPUT_LINE-3)) return -1; //Line too long, quit reading because line does not fit in buffer
		lineptr[*n]='\0';
		return (*n);
	#else
		//If fgetc_unlocked is enabled, use the fgetc loop instead of fgets as it outperforms the fgets
		int rd,HashFound=0;
		*n = 0;
		do {
			rd=fgetc_function(stream);
			switch(rd) {
				case '\r':
					lineptr[*n] = '\n';
					lineptr[(*n)+1]='\0';
					fgetc_function(stream);
					return (*n);
					break;
				case '\n':
					lineptr[*n]=rd;
					lineptr[(*n)+1]='\0';
					return (*n);
					break;
				case '\0':
					lineptr[*n]=rd;
					return (*n);
					break;
				case EOF:
					if ((*n)==0) return -1;
					else return (*n);
					break;
				default:
					if (HashFound==0) {
						if (rd=='#') {
							HashFound=1;
							lineptr[*n] = '\n';
							lineptr[(*n)+1]='\0';
						} else {
							lineptr[*n] = rd;
							(*n)++;
							if(*n>=MAX_INPUT_LINE-3) return -1; //Line too long, quit reading to avoid buffer overflow
						}
					}
					break;
			}
		} while (1);
		return -1;
		/*while ((rd=fgetc_function(stream))!=EOF) {
			if (rd=='\r' || rd=='\0' || rd=='\n') { // Character 13 is ^M (for Windows)
				if(rd=='\r') {
					lineptr[*n] = '\n';
					lineptr[(*n)+1]='\0';
					fgetc_function(stream);
				} else {
					lineptr[*n]=rd;
					if (rd!='\0') {
						lineptr[(*n)+1]='\0';
					}
				}
				break;
			} else if (HashFound==0) {
				if (rd=='#') {
					HashFound=1;
					lineptr[*n] = '\n';
					lineptr[(*n)+1]='\0';
				} else {
					lineptr[*n] = rd;
					(*n)++;
					if(*n>=MAX_INPUT_LINE-3) return -1; //Line too long, quit reading to avoid buffer overflow
				}
			}
		}

		if (rd==EOF && (*n)==0) return -1;
		else return (*n);*/
	#endif
}


/*****************************************************************************
 * Name        : getLback
 * Description : Standard multipurpose input reader from files. Valid for 
 *               windows and linux files. It reads a line backwards.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *lineptr                  O  N/A  Buffer to write to
 * int  *n                         O  N/A  Length of buffer
 * FILE  *stream                   I  N/A  Input stream file
 * Returned value (int)            O  N/A  Return the number of characters read
 *                                         -1 on failure to read
 *****************************************************************************/
int getLback (char *lineptr, int *n, FILE *stream) {
	int		enters = 0;
	int		rd;
	char	buffer[MAX_INPUT_LINE];
	int		i;
	long	pos;
	int		seek;
	char	*enter1;
	char	*enter2;
	
	pos = ftell(stream);
	if (pos<BACKWARD_READ_BATCH) seek = pos;
	else seek = BACKWARD_READ_BATCH;
	buffer[seek] = '\0';
	//res = fseek(stream,-seek,SEEK_CUR);
	fseek(stream,pos-seek,SEEK_SET);
	for (i=0;i<seek;i++) {
		rd = fgetc_function(stream);
		buffer[i] = rd;
		if (rd=='\n') {
			enter2 = enter1;
			enter1 = &buffer[i];
			enters++;
		}
	}
	if (enters>=2) {
		*n=(int)(enter1-enter2);
		strncpy(lineptr,enter2+1,*n);
	} else if (pos<BACKWARD_READ_BATCH && enters==1) {
		//This is the case where we rewind one line and we are at the beginning of the file
		*n=(int)pos;
		strncpy(lineptr,buffer,*n);
	} else return -1;

	lineptr[*n]='\0';
	
	//res = fseek(stream,-*n,SEEK_CUR);
	fseek(stream,pos-*n,SEEK_SET);

	return *n;
}

/*****************************************************************************
 * Name        : whatFileTypeIs
 * Description : Identifies the file type
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * Returned value (fileType)       O  N/A  Type of file
 *****************************************************************************/
enum fileType whatFileTypeIs (char *filename) {
	int				i;
	FILE			*fd = NULL;
	char			line[MAX_INPUT_LINE];
	char			line2[MAX_INPUT_LINE];
	int				len = 0,len2;
	int				res;
	char			aux[100];
	char			aux2[100];
	enum fileType	ft;

	ft = ftUNKNOWN;	// Default value

	fd = fopen(filename,"rb");
	
	if (fd==NULL) return ft;
	
	for(i=0;i<MAX_INPUT_LINE;i++) line[i]='\0';//To avoid comparing string with uninitialized values

	res = getL(line,&len,fd); 

	
	if (res!=-1) {
		getstr(aux,line,len,60,13);
		getstr(aux2,line,len,60,12);
		// RINEX check
		if (strcmp(aux,"RINEX VERSION")==0) {
			getstr(aux,line,len,20,11);
			if (strncmp(aux,"O",1)==0) ft = ftRINEXobservation;
			else if (strncmp(aux,"N",1)==0) ft = ftRINEXbroadcast;
			else if (strncmp(aux,"H",1)==0) ft = ftRINEXbroadcast; // Rinex v2 GEO nav data
			else if (strncmp(aux,"G",1)==0) ft = ftRINEXbroadcast; // Rinex v2 GLONASS nav data
			else if (strncmp(aux,"E",1)==0) ft = ftRINEXbroadcast; // Rinex v2 Galileo nav data
			else if (strncmp(aux,"J",1)==0) ft = ftRINEXbroadcast; // Rinex v2 QZSS nav data
			else if (strncmp(aux,"C",1)==0 && strstr(line,"NAV")!=NULL)  ft = ftRINEXbroadcast; // Rinex v2 BeiDou nav data
			else if (strncmp(aux,"C",1)==0) ft = ftRINEXclocks;    
			else if (strncmp(aux,"B",1)==0) ft = ftRINEXB;
			
		// IONEX check
		} else if (strcmp(aux,"IONEX VERSION")==0) {
						ft = ftIONEX;
		// FPPP check
				} else if (strcmp(aux2,"FPPP VERSION")==0) {
						ft = ftFPPP;
		// ANTEX check
		} else if (strcmp(aux,"ANTEX VERSION")==0) {
			ft = ftANTEX;
		// SP3 check
		} else if (line[0]=='#' &&  ((line[1]>='a' && line[1]<='z') || line[1]==' ') && (line[2]=='P' || line[2]=='V' || line[2]==' ')) {
			ft = ftSP3;
		// DCB check
		} else if (strstr(line,"DCB SOLUTION")!=NULL) {
				if (strstr(line,"P1-C1")!=NULL) {
					ft = ftP1C1DCB;
			} else if (strstr(line,"P1-P2")!=NULL) {
					 ft = ftP1P2DCB;
			 } else {
			  ft = ftGENDCB;
			 }
		// GPS Receiver file type
		} else if (strncmp(line,"#$Id: GPS_Receiver_Types",24)==0) {
			ft = ftRECEIVERTYPE;
		// SINEX check
		} else if (strncmp(line,"%=SNX",5)==0) {
			ft = ftSINEX;
		// SINEX BIAS check
		} else if (strncmp(line,"%=BIA",5)==0) {
			//SINEX BIAS file. Read lines until the first line of data is read, so we can distinguish 
			//it is has absolute biases or differential biases
			res = getL(line,&len,fd);
			while (res!=-1) {
				if(strncmp(line,"+BIAS/SOLUTION",14)==0) {
					//Read next header line. This will be the last line before data starts
					res = getL(line,&len,fd);
					if (res==-1) break;
					//Read first line of data
					res = getL(line,&len,fd);
					if (res==-1) break;

					if(strncmp(&line[1],"OSB",3)==0) {
						//SINEX BIAS contains Observable specific biases
						ft=ftSINEXBIASOSB;
						break;
					} else if (strncmp(&line[1],"DSB",3)==0 || strncmp(&line[1],"DCB",3)==0 || strncmp(&line[1],"ISB",3)==0 || strncmp(&line[1],"ICB",3)==0) {
						//SINEX BIAS contains differential signal biases
						ft=ftSINEXBIASDSB;
						break;
					}
				}
				res = getL(line,&len,fd);
			}
		} else {
			strcpy(line2,line);	//This is to save the first line, it might be needed for checking EMS message
			len2=len;
			res = getL(line,&len,fd); 
			if (res!=-1) {
				if (strstr(line,"Navstar GPS Constellation Status")!=NULL) ft = ftConstellation;
			}

			// SBAS EMS message
			if(len2>50 && line2[0]!='#') ft = ftSBASEMSMESSAGE;
		}
		if ( fd != NULL ) fclose(fd);
		return ft;
	}

	if ( fd != NULL ) fclose(fd);

	return ftINVALID;
}

/*****************************************************************************
 * Name        : readRinexObsHeader
 * Description : Read a RINEX observation header from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor for observation file
 * FILE  *fdout                    O  N/A  File descriptor for output observation file (with user added error)
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readRinexObsHeader (FILE *fd, FILE *fdout, TEpoch *epoch, TOptions *options) {
	int						numheaderlines=0;
	int						actSysObs = 1;
	int						len = 0;
	int						properlyRead = 0;
	int						error = 0;
	int						readingHeader = 1;
	int						numLinesTypesofObsr = 0;
	int						obs,i,j,k,n;
	int						auxN,auxN2;
	int						OffsetToSNR;
	int						freq;
	int						cleanedIndex=0;
	int						ErrorReadingEpochs;
	int						SNRMeasFound=0;
	int						initMeas,endMeas,numSatellites,Epochflag;
	int						yy=-1,mm=-1,dd=-1,hour=-1,minute=-1;
	int						S1ind,S2ind,nextRead;
	int						freqnumber;
	int						epochflag;
	static int				firstProgressCheck=1,firstProgressCheckDGNSS=1;
	enum MeasurementType	meas,measaux;
	long					posEndHeader;
	off_t					filesize;
	struct tm   			tm;
	struct stat 			filestat;	//This is to get the file size
	TTime					firstEpoch;
	TTime					secondEpoch;
	TTime					lastEpoch;
	double					seconds;
	double					interval;
	double					auxinterval;
	double					S1value,S2value,value;
	char					line[MAX_INPUT_LINE];
	char					aux[100];
	char					*ca;
	char					**headerlines=NULL;

	if (epoch->bufferHeaderLineLen>0) {
		strcpy(line,epoch->bufferHeaderLine);
		len=epoch->bufferHeaderLineLen;
		epoch->bufferHeaderLineLen=0;
		epoch->bufferHeaderLine[0]='\0';
	} else {
		if (getL(line,&len,fd)==-1) return 0;
	}
	epoch->numGNSSHeader=0;

	do {
		if (len<2) continue; //Skip blank lines
		if (fdout!=NULL && epoch->DGNSSstruct==0) {
			//Save header lines for creating an output RINEX files with user added error
			headerlines=realloc(headerlines,sizeof(char *)*(numheaderlines+1));
			headerlines[numheaderlines]=malloc(sizeof(char)*MAX_INPUT_LINE);
			strcpy(headerlines[numheaderlines],line);
			//if(headerlines[numheaderlines][len-1]=='\r'||headerlines[numheaderlines][len-1]=='\n') {
			//	headerlines[numheaderlines][len-1]='\0';
			//}
			numheaderlines++;
		}
		if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
			getstr(aux,line,len,0,9);
			epoch->RINEXobsVersion = atof(aux);
			if ((int)(epoch->RINEXobsVersion)==2) epoch->source = RINEX2;
			else if ((int)(epoch->RINEXobsVersion)==3) epoch->source = RINEX3;
			else {
				epoch->source = UNKNOWN_SOURCE;
				sprintf(aux,"Rinex observation file version %1.2f not supported. Supported versions are 2 and 3",epoch->RINEXobsVersion);
				printError(aux,options);
			}
		} else if (strncmp(&line[60],"MARKER NAME",11)==0) {
			getstr(aux,line,len,0,60);
			//Do not copy empty marker name
			if (aux[0]!='\0') {
				strcpy(epoch->receiver.name,aux);
			}
		} else if (strncmp(&line[60],"ANT # / TYPE",12)==0) {
			getstr(aux,line,len,20,20);
			strcpy(epoch->receiver.antenna.type,aux);
			// Separate the anntena.type into antenna and radome
			strcpy(epoch->receiver.antenna.type_ant,epoch->receiver.antenna.type);
			ca = strstr(epoch->receiver.antenna.type_ant," ");
			if (ca != NULL) {
				*ca = '\0';
				strcpy(epoch->receiver.antenna.type_radome,&ca[1]);
				trim(epoch->receiver.antenna.type_radome,(int)strlen(epoch->receiver.antenna.type_radome));
			}
		} else if (strncmp(&line[60],"REC # / TYPE / VERS",19)==0) {
			getstr(aux,line,len,20,20);
			strcpy(epoch->receiver.type,aux);
		} else if (strncmp(&line[60],"ANTENNA: DELTA H/E/N",20)==0) {
			if (options->ARPData == arpRINEX) {
				getstr(aux,line,len,0,14);
				epoch->receiver.ARP[2] = atof(aux);
				getstr(aux,line,len,14,14);
				epoch->receiver.ARP[1] = atof(aux);
				getstr(aux,line,len,28,14);
				epoch->receiver.ARP[0] = atof(aux);
			}

		} else if (strncmp(&line[60],"TIME OF FIRST OBS",17)==0) {
			getstr(aux,line,len,22,2);
			//Read first epoch
			getstr(aux,line,len,2,4);
			tm.tm_year = atoi(aux)-1900;
			getstr(aux,line,len,10,2);
			tm.tm_mon  = atoi(aux)-1;
			getstr(aux,line,len,16,2);
			tm.tm_mday = atoi(aux);
			getstr(aux,line,len,22,2);
			tm.tm_hour = atoi(aux);
			getstr(aux,line,len,28,2);
			tm.tm_min  = atoi(aux);
			getstr(aux,line,len,30,13);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
			epoch->FirstEpochHeader.MJDN = MJDN(&tm);
			epoch->FirstEpochHeader.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			//Get observation file time system. If it is not
			getstr(aux,line,len,48,3);
			epoch->SystemTime=gnssstr2gnsstype(aux);
			switch(epoch->SystemTime) {
				case BDS:
					epoch->ObsTimeToGPSTime=DIFFBDS2GPSTIME;
					break;
				case GLONASS:
					//After reading the header, if leap seconds from RINEX navigation header is available, this value will be overwritten
					epoch->ObsTimeToGPSTime=getLeapSeconds(&epoch->FirstEpochHeader,epoch->LeapSecondsTimeList,epoch->LeapSecondsNumList);
					break;
				default:
					epoch->ObsTimeToGPSTime=0.;
					break;
			}
		} else if (strncmp(&line[60],"# / TYPES OF OBSERV",19)==0) {  // Only for RINEX v2.11
			//      5    L1    L2    P1    P2    C1                        # / TYPES OF OBSERV
			numLinesTypesofObsr++;
			getstr(aux,line,len,0,6);
			if (numLinesTypesofObsr==1) { // if this is the first line of observations
				auxN = atoi(aux);
				epoch->measOrder[GPS].nDiffMeasurements = auxN;
				epoch->measOrder[GPS].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[GPS].GNSS = GPS;
				epoch->measOrder[Galileo].nDiffMeasurements = auxN;
				epoch->measOrder[Galileo].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[Galileo].GNSS = Galileo;
				epoch->measOrder[GEO].nDiffMeasurements = auxN;
				epoch->measOrder[GEO].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[GEO].GNSS = GEO;
				epoch->measOrder[GLONASS].nDiffMeasurements = auxN;
				epoch->measOrder[GLONASS].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[GLONASS].GNSS = GLONASS;
				epoch->measOrder[BDS].nDiffMeasurements = auxN;
				epoch->measOrder[BDS].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[BDS].GNSS = BDS;
				epoch->measOrder[QZSS].nDiffMeasurements = auxN;
				epoch->measOrder[QZSS].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[QZSS].GNSS = QZSS;
				epoch->measOrder[IRNSS].nDiffMeasurements = auxN;
				epoch->measOrder[IRNSS].nDiffMeasurementsRINEXHeader = auxN;
				epoch->measOrder[IRNSS].GNSS = IRNSS;
				epoch->numGNSSHeader = 7;
				obs = 0;
			} 

			//Initialize meas2Ind factor, so previous index are not maintained when reading concatenated files
			if(cleanedIndex==0) {
				cleanedIndex=1;
				for (j=0;j<MAX_GNSS;j++) {
					for (i=0;i<MAX_MEASUREMENTS_NO_COMBINATIONS;i++) {
						epoch->measOrder[j].meas2Ind[i] = -1;
						epoch->measOrder[j].conversionFactor[i] = 1.;
					}
				}
			}

			obs = 0;
			for (i=0,j=0;i<auxN;i++,j++) {
				getstr(aux,line,len,10+j*6,2);
				meas = measstr2meastype(aux);
				measaux=meas;
				if (meas != NA) {
					// Carrier-phase are stored in cycles instead of metres, as
					// they are on RINEX files.
					//    aux[0]=='L'   => Measurement is carrier phase
					for (k=0;k<epoch->numGNSSHeader;k++) {
						switch(k) {
							case GPS:
								//teqc converts the new L1C signal to frequency 7
								if (strncmp("C7",aux,2)==0) meas=C1X;
								else if (strncmp("L7",aux,2)==0) meas=L1X;
								else if (strncmp("D7",aux,2)==0) meas=D1X;
								else if (strncmp("S7",aux,2)==0) meas=S1X;
								else meas=measaux;
								break;
							case GLONASS:
								//teqc converts the G3 signal to frequency 7
								if (strncmp("C7",aux,2)==0) meas=C3X;
								else if (strncmp("L7",aux,2)==0) meas=L3X;
								else if (strncmp("D7",aux,2)==0) meas=D3X;
								else if (strncmp("S7",aux,2)==0) meas=S3X;
								else meas=measaux;
								break;
							case Galileo:
								if (strncmp("L1",aux,2)==0) meas=L1C; //L1P does not exist in Galileo
								else if (strncmp("D1",aux,2)==0) meas=D1C; //D1P does not exist in Galileo
								else if (strncmp("S1",aux,2)==0) meas=S1C; //S1P does not exist in Galileo
								else meas=measaux;
								break;
							case GEO:
								if (strncmp("L1",aux,2)==0) meas=L1C; //L1P does not exist in GEO
								else if (strncmp("D1",aux,2)==0) meas=D1C; //D1P does not exist in GEO
								else if (strncmp("S1",aux,2)==0) meas=S1C; //S1P does not exist in GEO
								else meas=measaux;
								break;
							case BDS:
								if (strncmp("C1",aux,2)==0) meas=C1X; //C1C does not exist in BDS
								else if (strncmp("L1",aux,2)==0) meas=L1X; //Set all freq 1 meas to X attribute
								else if (strncmp("D1",aux,2)==0) meas=D1X; //Set all freq 1 meas to X attribute
								else if (strncmp("S1",aux,2)==0) meas=S1X; //Set all freq 1 meas to X attribute
								else if (strncmp("C2",aux,2)==0) meas=C2X; //C2P does not exist in BDS
								else if (strncmp("L2",aux,2)==0) meas=L2X; //L2P does not exist in BDS
								else if (strncmp("D2",aux,2)==0) meas=D2X; //D2P does not exist in BDS
								else if (strncmp("S2",aux,2)==0) meas=S2X; //S2P does not exist in BDS
								else meas=measaux;
								break;
							case QZSS:
								if (strncmp("L1",aux,2)==0) meas=L1C; //L1P does not exist in QZSS
								else if (strncmp("D1",aux,2)==0) meas=D1C; //D1P does not exist in QZSS
								else if (strncmp("S1",aux,2)==0) meas=S1C; //S1P does not exist in QZSS
								else if (strncmp("C2",aux,2)==0) meas=C2X; //C2P does not exist in QZSS
								else if (strncmp("L2",aux,2)==0) meas=L2X; //L2P does not exist in QZSS
								else if (strncmp("D2",aux,2)==0) meas=D2X; //D2P does not exist in QZSS
								else if (strncmp("S2",aux,2)==0) meas=S2X; //S2P does not exist in QZSS
								//teqc converts the new L1C signal to frequency 7
								else if (strncmp("C7",aux,2)==0) meas=C1X;
								else if (strncmp("L7",aux,2)==0) meas=L1X;
								else if (strncmp("D7",aux,2)==0) meas=D1X;
								else if (strncmp("S7",aux,2)==0) meas=S1X;
								//teqc converts the QZSS L1-SAIF signal to frequency 8
								else if (strncmp("C8",aux,2)==0) meas=C1Z;
								else if (strncmp("L8",aux,2)==0) meas=L1Z;
								else if (strncmp("D8",aux,2)==0) meas=D1Z;
								else if (strncmp("S8",aux,2)==0) meas=S1Z;
								else meas=measaux;
								break;
							default:
								meas=measaux;
								break;
						}
						if (aux[0]=='L') {
							switch(k) {
								case GPS:
									if (aux[1]=='1') {
										epoch->measOrder[k].conversionFactor[L1C] = GPSl1;
										epoch->measOrder[k].conversionFactor[L1P] = GPSl1;
									}
									else if (aux[1]=='2') {
										epoch->measOrder[k].conversionFactor[L2C] = GPSl2;
										epoch->measOrder[k].conversionFactor[L2P] = GPSl2;
									}
									else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = GPSl5;
									else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = GPSl1; //teqc F7 is new L1C signal
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								case Galileo:
									if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = GALl1;
									else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = GALl5a;
									else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = GALl5b;
									else if (aux[1]=='8') epoch->measOrder[k].conversionFactor[meas] = GALl5;
									else if (aux[1]=='6') epoch->measOrder[k].conversionFactor[meas] = GALl6;
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								case GEO:
									if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = SBASl1;
									else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = SBASl5;
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
							 	case GLONASS:
									if (aux[1]=='1') {
										epoch->measOrder[k].conversionFactor[L1C] = 1.; //Frequency offset to be applied according to PRN
										epoch->measOrder[k].conversionFactor[L1P] = 1.; //Frequency offset to be applied according to PRN
									} else if (aux[1]=='2') {
										epoch->measOrder[k].conversionFactor[L2C] = 1.; //Frequency offset to be applied according to PRN
										epoch->measOrder[k].conversionFactor[L2P] = 1.; //Frequency offset to be applied according to PRN
									}
									else if (aux[1]=='3') epoch->measOrder[k].conversionFactor[meas] = GLOl3;
									else if (aux[1]=='4') epoch->measOrder[k].conversionFactor[meas] = GLOl1a;
									else if (aux[1]=='6') epoch->measOrder[k].conversionFactor[meas] = GLOl2a;
									else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = GLOl3; //teqc f7 is G3
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								case BDS:
									//NOTE: BDS is not officially in RINEX 2, but some rinex files do use RINEX 2 with BeiDou
									if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = BDSl1;
									else if (aux[1]=='2') epoch->measOrder[k].conversionFactor[meas] = BDSl1_2;
									else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = BDSl2a;
									else if (aux[1]=='6') epoch->measOrder[k].conversionFactor[meas] = BDSl3;
									else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = BDSl2b;
									else if (aux[1]=='8') epoch->measOrder[k].conversionFactor[meas] = BDSl2;
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								case QZSS:
									//NOTE: QZSS is not officially in RINEX 2, but some japanese rinex files do use RINEX 2 with QZSS
									if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = QZSl1;
									else if (aux[1]=='2') epoch->measOrder[k].conversionFactor[meas] = QZSl2;
									else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = QZSl5;
									else if (aux[1]=='6') epoch->measOrder[k].conversionFactor[meas] = QZSl6;
									else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = QZSl1; //teqc new L1C signal
									else if (aux[1]=='8') epoch->measOrder[k].conversionFactor[meas] = QZSl1; //teqc QZSS L1-SAIF signal
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								case IRNSS:
									//NOTE: IRNSS is not officially in RINEX 2, but some rinex files do use RINEX 2 with IRNSS
									if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = IRNl5; 
									else if(aux[1]=='9') epoch->measOrder[k].conversionFactor[meas] = IRNl9; 
									else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
									break;
								default:
									epoch->measOrder[k].conversionFactor[meas] = 1.0;
									break;
							}
						} else { // If measurement is not carrier-phase, conversionFactor is 1
							epoch->measOrder[k].conversionFactor[meas] = 1.0;
							if(aux[0]=='S') {
								//SNR measurement in file
								SNRMeasFound=1;
							}
						}
						// Update dictionaries 
						//For GPS and GLONASS, we set L1C and L1P in the same position, as in RINEX 2 only L1 phase is provided
					   	//but C1 and P1 codes are given. The same occurs for L2. These need to be copied as they need
						//their own slot for the model value. SNR measurements (S1,S2,...) don't need to be copied as they
						//are not modelled, they are only read
						//For the case of the Doppler, it can be shared, as Doppler it is the derivative of the phase, the
						//difference between D1C and D1P is none, as the difference between phases was the P1-C1 bias
						freq=getFrequencyInt(meas);
						epoch->measOrder[k].ind2Meas[obs] = meas;
						epoch->measOrder[k].availFreq[freq]=1;
						epoch->measOrder[k].meas2Ind[meas] = obs;
					}
				} else {
					sprintf(messagestr,"Reading RINEX %4.2f file: Unrecognized measurement type: '%s'",epoch->RINEXobsVersion,aux);
					printError(messagestr,options);
					error = 1;
				}				
				obs++;
				if ((j+1)%9==0 && auxN>(j+1)) { // Following observables are in the next lines (max 9 per line)
					j=-1; // j will be increased in the for loop
					if(getL(line,&len,fd)==-1) return 0; //If line fails to read exit function
					if (fdout!=NULL && epoch->DGNSSstruct==0) {
						//Save header lines for creating an output RINEX files with user added error
						headerlines=realloc(headerlines,sizeof(char *)*(numheaderlines+1));
						headerlines[numheaderlines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strcpy(headerlines[numheaderlines],line);
						if(headerlines[numheaderlines][len-1]=='\r'||headerlines[numheaderlines][len-1]=='\n') {
							headerlines[numheaderlines][len-1]='\0';
						}
						numheaderlines++;
					}
				}
			}
		} else if (strncmp(&line[60],"SYS / # / OBS TYPES",19)==0) { // Rinex version 3.00 can have multiple systems
			// G    4 C1C L1C D1C S1C                                      SYS / # / OBS TYPES
			// E   36 C1B L1B D1B S1B C1C L1C D1C S1C C5I L5I D5I S5I C5Q  SYS / # / OBS TYPES
			//        L5Q D5Q S5Q C7I L7I D7I S7I C7Q L7Q D7Q S7Q C6A L6A  SYS / # / OBS TYPES
			//        D6A S6A C6B L6B D6B S6B C6C L6C D6C S6C              SYS / # / OBS TYPES
			actSysObs = gnsschar2gnsstype(line[0]); 
			getstr(aux,line,len,1,5);
			epoch->measOrder[actSysObs].nDiffMeasurements = atoi(aux);
			epoch->measOrder[actSysObs].nDiffMeasurementsRINEXHeader = atoi(aux);
			epoch->measOrder[actSysObs].GNSS = actSysObs;
			epoch->numGNSSHeader++;
			obs = 0;

		
			//Initialize meas2Ind factor, so previous index are not maintained when reading concatenated files
			if(cleanedIndex==0) {
				cleanedIndex=1;
				for (j=0;j<MAX_GNSS;j++) {
					for (i=0;i<MAX_MEASUREMENTS_NO_COMBINATIONS;i++) {
						epoch->measOrder[j].meas2Ind[i] = -1;
						epoch->measOrder[j].conversionFactor[i] = 1.;
					}
				}
			}

			for (i=0,j=0;i<epoch->measOrder[actSysObs].nDiffMeasurementsRINEXHeader;j++,i++) {
				getstr(aux,line,len,7+4*j,3);
				meas = measstr2meastype(aux);
				if (meas != NA) {
					// Carrier-phase are stored in cycles instead of metres, as
					// they are on RINEX files.
					//    aux[0]=='L'||aux[0]=='I'   => Measurement is carrier phase or Ionosphere measurement (both in carrier-phase cycles)
					if (aux[0]=='L'||aux[0]=='I') {
						switch (actSysObs) {
							case GPS:
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl1;
								else if (aux[1]=='2') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl2;
								else if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl5;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
								break;
							case Galileo:
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl1;
								else if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5a;
								else if (aux[1]=='7') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5b;
								else if (aux[1]=='8') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5;
								else if (aux[1]=='6') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl6;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
								break;
							case GLONASS:
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = 1.; //Frequency offset to be applied according to PRN
								else if(aux[1]=='2') epoch->measOrder[actSysObs].conversionFactor[meas] = 1.; //Frequency offset to be applied according to PRN
								else if(aux[1]=='3') epoch->measOrder[actSysObs].conversionFactor[meas] = GLOl3;
								else if(aux[1]=='4') epoch->measOrder[actSysObs].conversionFactor[meas] = GLOl1a;
								else if(aux[1]=='6') epoch->measOrder[actSysObs].conversionFactor[meas] = GLOl2a;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
								break;
							case GEO:
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = SBASl1;
								else if(aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = SBASl5;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
								break;
							case BDS:
								if (aux[1]=='1' && epoch->RINEXobsVersion<=3.02) {
									aux[1]='2'; //To convert X1X to X2X (Rinex v3.02 was with freq 1, RINEX >=3.03 with freq 2)
									meas = measstr2meastype(aux);
								}
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl1;
								else if (aux[1]=='2') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl1_2;
								else if(aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl2a;
								else if(aux[1]=='6') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl3;
								else if(aux[1]=='7') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl2b;
								else if(aux[1]=='8') epoch->measOrder[actSysObs].conversionFactor[meas] = BDSl2;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
								break;
							case QZSS:
								if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = QZSl1;
								else if (aux[1]=='2') epoch->measOrder[actSysObs].conversionFactor[meas] = QZSl2;
								else if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = QZSl5;
								else if (aux[1]=='6') epoch->measOrder[actSysObs].conversionFactor[meas] = QZSl6;
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
								break;
							case IRNSS:
								if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = IRNl5; 
								else if(aux[1]=='9') epoch->measOrder[actSysObs].conversionFactor[meas] = IRNl9; 
								else epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
								break;
							default:
								//Other constellations not known
								epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
								break;
						}
					} else { // If measurement is not carrier-phase or ionosphere measurement, conversionFactor is 1
						if(epoch->measOrder[actSysObs].GNSS==BDS) {
							if (aux[1]=='1' && epoch->RINEXobsVersion<=3.02) {
								aux[1]='2'; //To convert X1X to X2X (Rinex v3.02 was with freq 1, RINEX v>=3.03 with freq 2)
								meas = measstr2meastype(aux);
							}
						}
						epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
						if(aux[0]=='S') {
							//SNR measurement in file
							SNRMeasFound=1;
						}
					}
					// Update dictionaries 
					freq=getFrequencyInt(meas);
					epoch->measOrder[actSysObs].availFreq[freq]=1;
					epoch->measOrder[actSysObs].meas2Ind[meas] = obs;
					epoch->measOrder[actSysObs].ind2Meas[obs] = meas;
				} else {
					sprintf(messagestr,"Reading RINEX %4.2f file: Unrecognized measurement type: '%s'",epoch->RINEXobsVersion,aux);
					printError(messagestr,options);
					error = 1;
				}				
				obs++;
				if ((j+1)%13==0 && epoch->measOrder[actSysObs].nDiffMeasurementsRINEXHeader>(j+1)) { // Following observables are in the next lines (max 13 per line)
					j=-1; // j will be increased in the for loop
					if(getL(line,&len,fd)==-1) return 0; //If line fails to read exit function
					if (fdout!=NULL && epoch->DGNSSstruct==0) {
						//Save header lines for creating an output RINEX files with user added error
						headerlines=realloc(headerlines,sizeof(char *)*(numheaderlines+1));
						headerlines[numheaderlines]=malloc(sizeof(char)*MAX_INPUT_LINE);
						strcpy(headerlines[numheaderlines],line);
						if(headerlines[numheaderlines][len-1]=='\r'||headerlines[numheaderlines][len-1]=='\n') {
							headerlines[numheaderlines][len-1]='\0';
						}
						numheaderlines++;
					}
				}
			}
			
		} else if (strncmp(&line[60],"INTERVAL",8)==0) {
			getstr(aux,line,len,0,10);
			if(atof(aux)>0.) { //In case Interval is 0, ignore the value
				epoch->receiver.interval = atof(aux); 
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
			if ( epoch->receiver.interval >= 15.0 ) {
				if (options->csNcon==1) options->csNconAutoDisabled=1;
				options->csNcon = 0;
			}
		} else if (strncmp(&line[60],"APPROX POSITION XYZ",19)==0) {
			if (options->receiverPositionSource==rpRINEX || ( ( (options->receiverPositionSource == rpCALCULATERINEX) || (options->receiverPositionSource == rpCALCULATERINEXREF)  ) && epoch->numAproxPosRead==0)) {
				getstr(aux,line,len,1,14);
				epoch->receiver.aproxPosition[0] = atof(aux);
				getstr(aux,line,len,14,14);
				epoch->receiver.aproxPosition[1] = atof(aux);
				getstr(aux,line,len,28,14);
				epoch->receiver.aproxPosition[2] = atof(aux);
				if (options->receiverPositionSource==rpRINEX) {
					epoch->receiver.aproxPositionError = 1e4; // 10 Km
				} else {
					epoch->receiver.aproxPositionError = 1e6;
				}
				epoch->numAproxPosRead++;
			} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
				getstr(aux,line,len,1,14);
				epoch->receiver.aproxPosition[0] = atof(aux);
				getstr(aux,line,len,14,14);
				epoch->receiver.aproxPosition[1] = atof(aux);
				getstr(aux,line,len,28,14);
				epoch->receiver.aproxPosition[2] = atof(aux);
				epoch->receiver.aproxPositionError = 0.1; // 10 cm
				epoch->numAproxPosRead++;
			}
			if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
				getstr(aux,line,len,1,14);
				epoch->receiver.aproxPositionRover[0] = atof(aux);
				getstr(aux,line,len,14,14);
				epoch->receiver.aproxPositionRover[1] = atof(aux);
				getstr(aux,line,len,28,14);
				epoch->receiver.aproxPositionRover[2] = atof(aux);
			}
			if(epoch->DGNSSstruct==1) { //This is to avoid reading the rover approx position as reference position
				if(epoch->receiver.numRecStation==0) {
					epoch->receiver.RecStationCoord=malloc(sizeof(double*));
					epoch->receiver.RecStationCoord[0]=malloc(sizeof(double)*3);
					memcpy(epoch->receiver.RecStationCoord[0],epoch->receiver.aproxPosition,sizeof(double)*3);
					epoch->receiver.numRecStation++;
				} else {
					if(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][0]!=epoch->receiver.aproxPosition[0] 
						|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][1]!=epoch->receiver.aproxPosition[1]
						|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][2]!=epoch->receiver.aproxPosition[2]) {
						//Station coordinates are differents from the previous read
						epoch->receiver.RecStationCoord=realloc(epoch->receiver.RecStationCoord,sizeof(double*)*(epoch->receiver.numRecStation+1));
						epoch->receiver.RecStationCoord[epoch->receiver.numRecStation]=malloc(sizeof(double)*3);
						memcpy(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation],epoch->receiver.aproxPosition,sizeof(double)*3);
						epoch->receiver.ChangedStaEpoch=realloc(epoch->receiver.ChangedStaEpoch,sizeof(TTime)*epoch->receiver.numRecStation);
						memcpy(&epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1],&epoch->t,sizeof(TTime));
						epoch->receiver.numRecStation++;
					}
				}
			}
		} else if ( strncmp(&line[60], "GLONASS SLOT / FRQ #", 20) == 0 ) {
			if (epoch->DGNSSstruct==0) { //Only read if it is rover, the data will then be copied to the DGNSS if necessary
				//K factor for frequency offset in GLONASS
				getstr(aux,line,len,0,3);
				auxN=atoi(aux);
				if (auxN==0) continue; //No data provided
				epoch->measOrder[GLONASS].hasGlonassSlotsFreq=1;
				epoch->measOrder[GLONASS].numFreqOffsetRead=auxN;
				//Read new values
				for (j=0,i=0;j<auxN && i<auxN;j++,i++) {
					getstr(aux,line,len,5+7*j,2); //get PRN
					auxN2=atoi(aux);
					getstr(aux,line,len,8+7*j,2); //get K
					freqnumber=atoi(aux);
					epoch->measOrder[GLONASS].freqMeas[1][auxN2]=GLOf1+(double)(freqnumber)*1e6*9./16.;
					epoch->measOrder[GLONASS].freqMeas[2][auxN2]=GLOf2+(double)(freqnumber)*1e6*7./16.;
					epoch->measOrder[GLONASS].lambdaMeas[1][auxN2]=c0/(GLOf1+(double)(freqnumber)*1e6*9./16.);
					epoch->measOrder[GLONASS].lambdaMeas[2][auxN2]=c0/(GLOf2+(double)(freqnumber)*1e6*7./16.);
					epoch->measOrder[GLONASS].mfreqMeas[1][auxN2]=epoch->measOrder[GLONASS].freqMeas[1][auxN2]/f0;
					epoch->measOrder[GLONASS].mfreqMeas[2][auxN2]=epoch->measOrder[GLONASS].freqMeas[2][auxN2]/f0;
					epoch->measOrder[GLONASS].TECU2metres[1][auxN2]=40.3*1E16/(epoch->measOrder[GLONASS].freqMeas[1][auxN2]*epoch->measOrder[GLONASS].freqMeas[1][auxN2]);
					epoch->measOrder[GLONASS].TECU2metres[2][auxN2]=40.3*1E16/(epoch->measOrder[GLONASS].freqMeas[2][auxN2]*epoch->measOrder[GLONASS].freqMeas[2][auxN2]);
					epoch->GLOfreqnumber[auxN2]=freqnumber;
					if ((j+1)%8==0 && auxN>(i+1)) { // Following k are in the next lines (max 8 per line)
						j=-1; // j will be increased in the for loop
						if(getL(line,&len,fd)==-1) return 0; //If line fails to read exit function
						if (fdout!=NULL && epoch->DGNSSstruct==0) {
							//Save header lines for creating an output RINEX files with user added error
							headerlines=realloc(headerlines,sizeof(char *)*(numheaderlines+1));
							headerlines[numheaderlines]=malloc(sizeof(char)*MAX_INPUT_LINE);
							strcpy(headerlines[numheaderlines],line);
							if(headerlines[numheaderlines][len-1]=='\r'||headerlines[numheaderlines][len-1]=='\n') {
								headerlines[numheaderlines][len-1]='\0';
							}
							numheaderlines++;
						}
					}
				}
			}
		} else if ( strncmp(&line[60], "END OF HEADER", 13) == 0 ) {
			readingHeader = 0;
			properlyRead = 1;
			if (fdout!=NULL && epoch->DGNSSstruct==0) {
				//Add header comment line indicating that user defined error has been added to measurements
				headerlines=realloc(headerlines,sizeof(char *)*(numheaderlines+1));
				headerlines[numheaderlines]=malloc(sizeof(char)*MAX_INPUT_LINE);
				strcpy(headerlines[numheaderlines],headerlines[numheaderlines-1]); //Copy END OF HEADER line to the last line
				sprintf(headerlines[numheaderlines-1],"%-60sCOMMENT","User defined error added to measurements (with gLAB tool)");
				numheaderlines++;
			}
			break;
		}
	} while (getL(line,&len,fd)!=-1 && readingHeader);

	//Write header lines for RINEX observation file with user added error
	if (fdout!=NULL && epoch->DGNSSstruct==0) {
		writeRinexObsHeaderUserAddedError(fdout,headerlines,numheaderlines);
		for(i=0;i<numheaderlines;i++) {
			free(headerlines[i]);
		}
		free(headerlines);
	}

	//Some rare RINEX files in the RINEX header they state that SNR measurements
	//are provided, but later in the file the measurements are all zero. Therefore, before creating the
	//index, we need to read an epoch of the file to check if SNR measurements are really provided
	if (SNRMeasFound==1) {
		//SNR measurements provided. Read an epoch and check if measurements exist
		//Save current position in file
		posEndHeader = ftell(fd);
		//Read lines until first line with measurements is found
		if (getL(line,&len,fd)==-1) return 0;
		if (epoch->source == RINEX2) {
			//Check if epoch is an event epoch
			getstr(aux,line,len,27,2);
			Epochflag=atoi(aux);
			if (Epochflag>1) { //Event epoch. Skip it
				getstr(aux,line,len,30,2);
				n = atoi(aux);
				for (i=0;i<=n;i++) {
					if (getL(line,&len,fd)==-1) return 0;
				}
			}
			getstr(aux,line,len,30,2);
			numSatellites = atoi(aux);
			//Skip lines for satellites PRN list until first measurement is found
			for (i=0;i<=(int)(numSatellites/12);i++) {
				if (getL(line,&len,fd)==-1) return 0;
			}
			S1ind=epoch->measOrder[GPS].meas2Ind[S1P];
			S2ind=epoch->measOrder[GPS].meas2Ind[S2P];
			nextRead=0;
			for (j=0,k=0;j<epoch->measOrder[GPS].nDiffMeasurementsRINEXHeader;j++,k++) {
				if (nextRead) {
					if (getL(line,&len,fd)==-1) return 0;
					nextRead = 0;
				}
				getstr(aux,line,len,16*k,14);
				value = atof(aux);
				if (value==0) value = -1.;
				if (j==S1ind) S1value=value;
				else if (j==S2ind) S2value=value;
				if ((k+1)%5==0) { // Following observables are in the next lines (max 5 per line)
					nextRead = 1;
					k=-1; // k will be increased in the for loop
				}
			}
			if (S1ind!=-1 && S2ind !=-1) {
				if (S1value==-1. && S2value==-1.) {
					//No SNR meas provided. Use flag instead
					SNRMeasFound=0;
				} else if (S1ind!=-1 && S2ind ==-1) {
					if (S1value==-1.) {
						//No SNR meas provided. Use flag instead
						SNRMeasFound=0;
					}
				} else {
					if (S2value==-1.) {
						//No SNR meas provided. Use flag instead
						SNRMeasFound=0;
					}
				}
			}
		} else { //RINEX3
			//Check if epoch is an event epoch
			getstr(aux,line,len,30,2);
			Epochflag=atoi(aux);
			if (Epochflag>1) { //Event epoch. Skip it
				getstr(aux,line,len,33,2);
				n = atoi(aux);
				for (i=0;i<=n;i++) {
					if (getL(line,&len,fd)==-1) return 0;
				}
			}
			getstr(aux,line,len,33,2);
			numSatellites = atoi(aux);
			//Skip epoch line 
			if (getL(line,&len,fd)==-1) return 0;
			actSysObs = gnsschar2gnsstype(line[0]);
			value=-1.;
			for (j=0;j<epoch->measOrder[actSysObs].nDiffMeasurementsRINEXHeader;j++) {
				//Loop until a SNR measurement is found
				if (epoch->measOrder[actSysObs].ind2Meas[j]%4!=0) continue;
				getstr(aux,line,len,3+16*j,14);
				value = atof(aux);
				if (value==0) value = -1.;
				else break;
			}
			if (value==-1.) {
				//No SNR meas provided. Use flag instead
				SNRMeasFound=0;
			}
		}
		//Set the file position back to the first epoch
		fseek(fd,posEndHeader,SEEK_SET);
	}
	//Create a look up table for SNR measurements.
	//If SNR as a measurement is given, both code, phase and Doppler will point to its SNR measurements.
	//In RINEX 2, C1/P1/L1/D1 and other frequencies share the same SNR measurement
	//If SNR is given only as a flag, code, phase and Doppler will point to the phase measurement, which
	//will have the SNR value. For the case where a measurement is not paired (e.g C1W), it will pint to
	//a phase measurement of the same frequency
	if (SNRMeasFound==1) {
		//SNR as as measurement available. Use it as it more precise than the quantized value
		for(n=0;n<MEASTYPELISTS;n++) {
			OffsetToSNR=3-n;
			for (meas=1+n;meas<I1;meas+=4) {
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->measOrder[i].meas2Ind[meas]==-1) {
						if (meas==C1P && epoch->source==RINEX2) {
							//For RINEX 2 without C1P, add also the SNR index as it will be used by S1P (due to the conversion of S1 to S1P)
						} else {
							epoch->measOrder[i].meas2SNRInd[meas]=-1; //If in new header a measurement dissapears, remove its pointer
							continue;
						}
					}
					epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[meas+OffsetToSNR];
					if (epoch->measOrder[i].meas2SNRInd[meas]==-1) {
						//Measurement not paired (e.g C1W in RINEX3)
						//Loop through all phase measurements in the same frequency and select the first one found
						freq=getFrequencyInt(meas);
						if (freq==0) {
							initMeas=S1N*9+1+n;
							endMeas=S0N;
						} else {
							initMeas=S1N*(freq-1)+1+n;
							endMeas=S1N*freq;
						}
						if (i==GPS && (meas==C1C||meas==C1P||meas==C1W||meas==C2W||meas==C2P)) {
							//For the case of GPS, if S1C is not available and if S1X is available 
							//(according to teqc extension, S7 is S1X in RINEX2), it will find first S1X instead of S1P or S1W
							//Idem for L2
							for(k=initMeas;k<endMeas;k+=4) {
								if ((k+OffsetToSNR)==S1S||(k+OffsetToSNR)==S1L||(k+OffsetToSNR)==S1X) continue;
								else if ((k+OffsetToSNR)==S2S||(k+OffsetToSNR)==S2L||(k+OffsetToSNR)==S2X) continue;
								epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
								if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
							}
							//If no measurement found, use any measurement found without excluding anyone
							if (epoch->measOrder[i].meas2SNRInd[meas]==-1) {
								for(k=initMeas;k<endMeas;k+=4) {
									epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
									if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
								}
							}
						} else {
							for(k=initMeas;k<endMeas;k+=4) {
								epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
								if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
							}
						}
					}
				}
			}
		}
	} else {
		//SNR only as a flag available. Point to phase measurement
		OffsetToSNR=2;
		for(n=0;n<MEASTYPELISTS;n++) {
			OffsetToSNR--;
			for (meas=1+n;meas<I1;meas+=4) {
				for(i=0;i<MAX_GNSS;i++) {
					if (epoch->measOrder[i].meas2Ind[meas]==-1) {
						if (meas==C1P && epoch->source==RINEX2) {
							//For RINEX 2 without C1P, add also the SNR index as it will be used by S1P (due to the conversion of S1 to S1P)
						} else {
							epoch->measOrder[i].meas2SNRInd[meas]=-1; //If in new header a measurement dissapears, remove its pointer
							continue;
						}
					}
					epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[meas+OffsetToSNR];
					if (epoch->measOrder[i].meas2SNRInd[meas]==-1) {
						//Measurement not paired (e.g C1W in RINEX3)
						//Loop through all phase measurements in the same frequency and select the first one found
						freq=getFrequencyInt(meas);
						if (freq==0) {
							initMeas=S1N*9+1+n;
							endMeas=S0N;
						} else {
							initMeas=S1N*(freq-1)+1+n;
							endMeas=S1N*freq;
						}
						if (i==GPS && (meas==C1C||meas==C1P||meas==C1W||meas==C2W||meas==C2P)) {
							//For the case of GPS, if L1C is not available and if L1X is available 
							//(according to teqc extension, L7 is L1X in RINEX2), it will find first L1X instead of L1P or L1W
							//Idem for L2
							for(k=initMeas;k<endMeas;k+=4) {
								if ((k+OffsetToSNR)==L1S||(k+OffsetToSNR)==L1L||(k+OffsetToSNR)==L1X) continue;
								else if ((k+OffsetToSNR)==L2S||(k+OffsetToSNR)==L2L||(k+OffsetToSNR)==L2X) continue;
								epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
								if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
							}
							//If no measurement found, use any measurement found without excluding anyone
							if (epoch->measOrder[i].meas2SNRInd[meas]==-1) {
								for(k=initMeas;k<endMeas;k+=4) {
									epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
									if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
								}
							}
						} else {
							for(k=initMeas;k<endMeas;k+=4) {
								epoch->measOrder[i].meas2SNRInd[meas]=epoch->measOrder[i].meas2Ind[k+OffsetToSNR];
								if (epoch->measOrder[i].meas2SNRInd[meas]!=-1) break;
							}
						}
					}
				}
			}
		}
	}

	if (epoch->DGNSSstruct==0 && firstProgressCheck==1) {
		firstProgressCheck=0;
		//We need to enter if printProgress is enabled or if it is disabled but want to compute receiver interval
		if (printProgress==1 || (printProgress==0 && epoch->receiver.interval==-1.) ) {
			//Check that there was no error when reading the header
			if (properlyRead==1 && error==0) {
				//Compute number of epochs.
				//Save current position in file
				posEndHeader = ftell(fd);
				for(i=0;i<3;i++) {
					if (i==1) {
						if (epoch->receiver.interval!=-1 && epoch->receiver.interval!=0.) {
							interval=epoch->receiver.interval;	
							continue;
						} else {
							//Interval is not in the header, read first and second epoch and compute the interval
							//Maybe some observation files have a data gap for all satellite in second, but that is extremely rare
						}
					} else if (i==2) {
						//We need to go to the end of the file.
						//NOTE that fseek(fd, 0L, SEEK_END); does not work as we have opened the file in binary mode!!!
						fstat(fileno(fd), &filestat);
						filesize = filestat.st_size;
						fseek(fd,filesize,SEEK_SET);
						//Seek the beginning of the last epoch
						rewindEpochRinexObs(fd, epoch->source);
					}
					ErrorReadingEpochs=0;
					while(1) {
						if (getL(line,&len,fd)==-1) {
							#if !defined (__WIN32__)
								if (printProgress==1 && options->ProgressEndCharac=='\r') {
									//If print progress was enabled, reenable the cursor
									fprintf(options->terminalStream,"\033[?25h");
								}
							#endif
							printProgress=0;
							ErrorReadingEpochs=1;
							break;
						}
						//Read epoch time
						if (epoch->source == RINEX2) {
							getstr(aux,line,len,0,4);
							yy = tm.tm_year = atoi(aux);
							if (tm.tm_year <= 70) tm.tm_year += 100;
							getstr(aux,line,len,3,4);
							mm = atoi(aux);
							tm.tm_mon  = mm - 1;
							getstr(aux,line,len,6,4);
							dd = tm.tm_mday = atoi(aux);
							getstr(aux,line,len,9,4);
							if(aux[1]=='.'||aux[2]=='.') {
								hour= tm.tm_hour = -1;
							} else {
								hour = tm.tm_hour = atoi(aux);
							}
							getstr(aux,line,len,12,4);
							minute = tm.tm_min  = atoi(aux);
							getstr(aux,line,len,16,10);
							tm.tm_sec  = atoi(aux);
							seconds = atof(aux);
						} else {
							//RINEX v3
							if (line[0]=='>' && len<60) {
								//Line with valid epoch
								getstr(aux,line,len,2,4);
								yy =  atoi(aux);
								if (yy>=2000) yy-=2000;
								else yy-=1900;
								tm.tm_year = atoi(aux)-1900;
								getstr(aux,line,len,7,2);
								mm = atoi(aux);
								tm.tm_mon = mm-1;
								getstr(aux,line,len,10,2);
								dd = tm.tm_mday = atoi(aux);
								getstr(aux,line,len,13,2);
								hour = tm.tm_hour = atoi(aux);
								getstr(aux,line,len,16,2);
								minute = tm.tm_min  = atoi(aux);
								getstr(aux,line,len,19,10);
								tm.tm_sec  = atoi(aux);
								seconds = atof(aux);
							} else {
								hour=-1;
							}
						}
						if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && minute>=0 &&minute<=59) {
							//Epoch timestamp found
							break;
						} else if (i==2 && epoch->source == RINEX3) {
							//Check if last epoch is an event epoch without date
							getstr(aux,line,len,30,2);
							epochflag=atoi(aux);
							if (line[0]=='>' && len<60 && epochflag>1 ) {
								//Event epoch is the last epoch in file and it does not have the date in the epoch recod, 
								//so we need to go another epoch back to get an epoch with data and full date
								getLback(line,&len,fd);
								rewindEpochRinexObs(fd, epoch->source);
							}

						}
					}
					if (ErrorReadingEpochs==1) {
						//Error when looking for epochs
						if (i<2) {
							//Interval could not be computed. Set interval to 1 to avoid division by zero
							interval=epoch->receiver.intervalEstimate=1.;
							//Disable Ncon filter as we don't know the file interval
							options->csNcon = 0;
							break;
						}
					} else if (printProgress==0 && i>1) {
						break;
					}
					if (i==0) {
						firstEpoch.MJDN = MJDN(&tm);
						firstEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
						if (epoch->FirstEpochHeader.MJDN==-1) {
							//If TIME OF FIRST OBS header is not in file, use first epoch in file instead
							memcpy(&epoch->FirstEpochHeader,&firstEpoch,sizeof(TTime));
						}
					} else if (i==1) {
						secondEpoch.MJDN = MJDN(&tm);
						secondEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
						interval=tdiff(&secondEpoch,&firstEpoch);
						if (interval<DIFFEQTHRESHOLD) {
							//Epoch repeated due to an event epoch just in the first epoch
							//Keep reading epochs until the epoch changes
							i=0;
							continue;
						}
						epoch->receiver.intervalEstimate=interval;
						if ( epoch->receiver.intervalEstimate >= 15.0 ) {
							options->csNcon = 0;
						}
						if (interval>=1.) {
							epoch->receiver.intervalDecimalsFactor=1;
							epoch->receiver.DecimateVal=1;
						} else {
							//Get the number of decimals
							auxinterval=interval-(double)((int)(interval+.00005));
							epoch->receiver.intervalDecimalsFactor=sprintf(aux,"%.4g",auxinterval)-2;
							epoch->receiver.intervalDecimalsFactor=(int)(pow(10,(double)epoch->receiver.intervalDecimalsFactor));
							epoch->receiver.DecimateVal=(long long int)((options->decimate+.00005)*(double)(epoch->receiver.intervalDecimalsFactor));
							if (epoch->receiver.DecimateVal==0) {
								//This is the case where user set an interval smaller than the number of decimals in the interval
								//Therefore, set this value to 1, so all epochs are used (and also avoid dividing by 0)
								epoch->receiver.DecimateVal=1;
							}
						}
						if (printProgress==0) break;
					} else {
						if (options->StartEpoch.MJDN!=-1) {
							//User selected an start epoch. Check if first epoch is before or after first epoch of file
							if (tdiff(&firstEpoch,&options->StartEpoch)<0) {
								//First epoch of file is before start epoch. Use user start epoch as first epoch
								memcpy(&firstEpoch,&options->StartEpoch,sizeof(TTime));
							}
						}
						lastEpoch.MJDN = MJDN(&tm);
						lastEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
						if (options->EndEpoch.MJDN!=-1) {
							//User selected and ending epoch. Check if last epoch of file is before or after user selected epoch
							if (tdiff(&lastEpoch,&options->EndEpoch)<0) {
								//Last epoch of file is before user last epoch. Use file last epoch to compute number of epochs
								epoch->numEpochsfile=(tdiff(&lastEpoch,&firstEpoch))/interval+1.;
							} else {
								//Last epoch of file is after user last epoch. Use user last epoch to compute number of epochs
								epoch->numEpochsfile=(tdiff(&options->EndEpoch,&firstEpoch))/interval+1.;
							}
						} else {
							epoch->numEpochsfile=(tdiff(&lastEpoch,&firstEpoch))/interval+1.;
						}
					}
				}
				//Set the file position back to the first epoch
				fseek(fd,posEndHeader,SEEK_SET);
				//If backward filtering is enabled, double the number of epochs in file
				if (options->filterIterations==2) {
					if (options->StartEpoch.MJDN!=-1) {
						//Backwards filtering. It will process from the start of the file (or the first epoch set by user) to the end
						//and then reprocess the whole file backwards
						epoch->numEpochsfile+=(tdiff(&lastEpoch,&epoch->FirstEpochHeader))/interval+1.;
					} else {
						epoch->numEpochsfile*=2;
					}
				}
			} else {
				//If error reading header, disable printing progress for precaution
				#if !defined (__WIN32__)
					if (printProgress==1 && options->ProgressEndCharac=='\r') {
						//If print progress was enabled, reenable the cursor
						fprintf(options->terminalStream,"\033[?25h");
					}
				#endif
				printProgress=0;
			}
		}
	} else if (epoch->DGNSSstruct==1 && firstProgressCheckDGNSS==1) {
		firstProgressCheckDGNSS=0;
		if (epoch->receiver.interval<=0.) {
			//Receiver interval not available. Compute it
			//Save current position in file
			posEndHeader = ftell(fd);
			for(i=0;i<2;i++) {
				while(1) {
					if (getL(line,&len,fd)==-1) {
						//Interval cannot be computed. Set 1 to avoid division by 0
						epoch->receiver.interval=1.;
						return 0;
					}
					//Read epoch time
					if (epoch->source == RINEX2) {
						getstr(aux,line,len,0,4);
						yy = tm.tm_year = atoi(aux);
						if (tm.tm_year <= 70) tm.tm_year += 100;
						getstr(aux,line,len,3,4);
						mm = atoi(aux);
						tm.tm_mon  = mm - 1;
						getstr(aux,line,len,6,4);
						dd = tm.tm_mday = atoi(aux);
						getstr(aux,line,len,9,4);
						if(aux[1]=='.'||aux[2]=='.') {
							hour= tm.tm_hour = -1;
						} else {
							hour = tm.tm_hour = atoi(aux);
						}
						getstr(aux,line,len,12,4);
						minute = tm.tm_min  = atoi(aux);
						getstr(aux,line,len,16,10);
						tm.tm_sec  = atoi(aux);
						seconds = atof(aux);
					} else {
						//RINEX v3
						if (line[0]=='>' && len<60) {
							//Line with valid epoch
							getstr(aux,line,len,2,4);
							yy =  atoi(aux);
							if (yy>=2000) yy-=2000;
							else yy-=1900;
							tm.tm_year = atoi(aux)-1900;
							getstr(aux,line,len,7,2);
							mm = atoi(aux);
							tm.tm_mon = mm-1;
							getstr(aux,line,len,10,2);
							dd = tm.tm_mday = atoi(aux);
							getstr(aux,line,len,13,2);
							hour = tm.tm_hour = atoi(aux);
							getstr(aux,line,len,16,2);
							minute = tm.tm_min  = atoi(aux);
							getstr(aux,line,len,19,10);
							tm.tm_sec  = atoi(aux);
							seconds = atof(aux);
						} else {
							hour=-1;
						}
					}
					if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && minute>=0 &&minute<=59) {
						//Epoch timestamp found
						break;
					}
				}
				if (i==0) {
					firstEpoch.MJDN = MJDN(&tm);
					firstEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				} else {
					secondEpoch.MJDN = MJDN(&tm);
					secondEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					interval=tdiff(&secondEpoch,&firstEpoch);
					if (interval<DIFFEQTHRESHOLD) {
						//Epoch repeated due to an event epoch just in the first epoch
						//Keep reading epochs until the epoch changes
						i=0;
						continue;
					}
					epoch->receiver.interval=interval;
				}
			}
			//Set the file position back to the first epoch
			fseek(fd,posEndHeader,SEEK_SET);
		}
	}

	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readRinexObsEpoch
 * Description : Read a RINEX observation epoch from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * char *Epochstr                  O  N/A  String to save the current epoch processed
 *                                         which whill be shown in the progress bar
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error or EOF (no more epochs)
 *****************************************************************************/
int readRinexObsEpoch (FILE *fd, TEpoch *epoch, char *Epochstr, TOptions *options) {
	char					line[MAX_INPUT_LINE];
	char					aux[100];
	char					cons;
	int						len = 0;
	int						properlyRead = 0;
	int						error = 0;
	int						i, j, k;
	int						n;
	int						numEpochsMissing;
	int						invalidDate=0;
	struct tm				tm;
	double					seconds;
	double					value;
	int						nextRead;
	//int						ret;
	int						posMeasSrc,posMeasDest;
	enum MeasurementType	meas;
	enum GNSSystem			GNSS;

	// For converting from SNR flag in RINEX to dBHz. The don't care value (0 in RINEX) is set to 53 so the max SNR
	// filter (with the default value) does not filter measurements without SNR.
	// There is no fixed value for very high SNR (9 in RINEX). A value is 60 is set in order to give a higher enough
	// value when computing the satellite weight using the SNR (but they will be filtered by the maximum SNR filter
	// with the default value)

	static int	twoepochs=1;	//Variable to read only the first two epochs to compute data rate file
	static int	lastCSindex[NUM_OBSRINEX]={0,0};	//Variable holding the first free index of all satellites viewed

	for(i=0;i<MAX_INPUT_LINE;i++) line[i]='\0'; //To avoid using uninitialized values when comparing substrings in "line" 

	// Rewind for backward processing
	if ( epoch->direction == pBACKWARD ) {
		//ret = rewindEpochRinexObs(fd,epoch->source);
		//if ( ret == 0 ) return 0;
		//ret = rewindEpochRinexObs(fd,epoch->source);
		//if ( ret == 0 ) return 0;
		if (epoch->numEpochReadFilePos<0) return 0;
		fseek(fd,epoch->epochReadFilePos[epoch->numEpochReadFilePos],SEEK_SET);
		epoch->numEpochReadFilePos--;
	}

	//Remove index values from previous epoch
	for (i=0;i<epoch->numSatellites;i++) {
		epoch->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=-1;
		epoch->sat2Printpos[i]=-1;
	}
	//Set number of satellites per GNSS to 0 and GNSS print position to -1
	for (i=0;i<MAX_GNSS;i++) {
		epoch->numSatellitesGNSS[i]=0;
		epoch->GNSS2PrintPos[i]=-1;
		epoch->GNSSinEpoch[i]=0;
	}
	//Set number of constellations to 0
	epoch->numPrintGNSS=0;
	epoch->numGNSSinEpoch=0;

	
	if (getL(line,&len,fd)!=-1) {
		properlyRead = 1;
		// Block to detect new RINEX header, it only affects when large RINEX are used
		if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
			strcpy(epoch->bufferHeaderLine,line);
			epoch->bufferHeaderLineLen=len;
			return 2;
		}
		if (epoch->source == RINEX2) {

			//////////////////////////////////
			////RINEX 2 observation file

			getstr(aux,line,len,27,2);
			epoch->flag = atoi(aux);
			
			if (epoch->flag>1) { // Unusable epoch
				while(epoch->flag>1) { //There can be multiple event epochs
					if ( epoch->direction == pBACKWARD ) {
						//Save previous epoch
						memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));
						//When going backwards, skip epoch events and look for previous epoch in RINEX observation file
						//If next valid epoch was read, it would make an infinite loop as we want back one epoch, but read two,
						//and the next time we enter this function, we would go back two epochs, which results in always reading 
						//the same epoch
						/*ret = rewindEpochRinexObs(fd,epoch->source);
						if ( ret == 0 ) return 0;
						ret = rewindEpochRinexObs(fd,epoch->source);
						if ( ret == 0 ) return 0;
						if (getL(line,&len,fd)==-1) return 0;*/
					} else {
						invalidDate=0;
						getstr(aux,line,len,1,2);
						tm.tm_year = atoi(aux);
						if (tm.tm_year<=0) invalidDate=1;
						else if (tm.tm_year <= 70) tm.tm_year += 100;
						getstr(aux,line,len,4,2);
						tm.tm_mon  = atoi(aux);
						if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
						tm.tm_mon  -= 1;
						getstr(aux,line,len,7,2);
						tm.tm_mday = atoi(aux);
						if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
						getstr(aux,line,len,10,2);
						tm.tm_hour = atoi(aux);
						if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
						getstr(aux,line,len,13,2);
						tm.tm_min  = atoi(aux);
						if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
						getstr(aux,line,len,16,10);
						tm.tm_sec  = atoi(aux);
						if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
						if (!options->integerRINEXObsSeconds) {
							seconds = atof(aux);
						} else {
							seconds=(double)tm.tm_sec;
						}
						if (invalidDate==1) {
							sprintf(messagestr,"Invalid date in line '%.80s' in %s observation file",line,epoch->DGNSSstruct==0?"rover":"DGNSS");
							printError(messagestr,options);
						}
						getstr(aux,line,len,30,2);
						n = atoi(aux);
						for (i=0;i<=n;i++) {
							if (i==n) {
								//Update position of epoch start to remove event epoch
								epoch->epochReadFilePos[epoch->numEpochReadFilePos-1]=ftell(fd);
							}
							if (getL(line,&len,fd)==-1) {
								return 0;
							}
							if (strncmp(&line[60],"APPROX POSITION XYZ",19)==0) {
								if (options->receiverPositionSource==rpRINEX || ( ( (options->receiverPositionSource == rpCALCULATERINEX) || (options->receiverPositionSource == rpCALCULATERINEXREF)  ) && epoch->numAproxPosRead==0)) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPosition[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPosition[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPosition[2] = atof(aux);
									epoch->receiver.aproxPositionError = 1e4; // 10 Km
									epoch->numAproxPosRead++;
								} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPosition[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPosition[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPosition[2] = atof(aux);
									epoch->receiver.aproxPositionError = 0.1; // 10 cm
									epoch->numAproxPosRead++;
								} 
								if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPositionRover[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPositionRover[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPositionRover[2] = atof(aux);
								}
								if(epoch->DGNSSstruct==1) {
									if(epoch->receiver.numRecStation==0) {
										epoch->receiver.RecStationCoord=malloc(sizeof(double*));
										epoch->receiver.RecStationCoord[0]=malloc(sizeof(double)*3);
										memcpy(epoch->receiver.RecStationCoord[0],epoch->receiver.aproxPosition,sizeof(double)*3);
										epoch->receiver.numRecStation++;
									} else {
										if(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][0]!=epoch->receiver.aproxPosition[0] 
												|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][1]!=epoch->receiver.aproxPosition[1]
												|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][2]!=epoch->receiver.aproxPosition[2]) {
											//Station coordinates are differents from the previous read
											epoch->receiver.RecStationCoord=realloc(epoch->receiver.RecStationCoord,sizeof(double*)*(epoch->receiver.numRecStation+1));
											epoch->receiver.RecStationCoord[epoch->receiver.numRecStation]=malloc(sizeof(double)*3);
											memcpy(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation],epoch->receiver.aproxPosition,sizeof(double)*3);
											epoch->receiver.ChangedStaEpoch=realloc(epoch->receiver.ChangedStaEpoch,sizeof(TTime)*epoch->receiver.numRecStation);
											memcpy(&epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1],&epoch->t,sizeof(TTime));
											epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1].MJDN=MJDN(&tm);
											epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1].SoD=(double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
											epoch->receiver.numRecStation++;
										}
									}
								}
							}
						}
					}
					//Check for more event epochs
					getstr(aux,line,len,27,2);
					epoch->flag = atoi(aux);
				}
				// Check again for RINEX header, as it can occur after an event epoch
				if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
					strcpy(epoch->bufferHeaderLine,line);
					epoch->bufferHeaderLineLen=len;
					return 2;
				}
			}
			
			//Save previous epoch
			memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));

			invalidDate=0;
			getstr(aux,line,len,1,2);
			tm.tm_year = atoi(aux);
			if (tm.tm_year<=0) invalidDate=1;
			if (tm.tm_year <= 70) tm.tm_year += 100;
			getstr(aux,line,len,4,2);
			tm.tm_mon  = atoi(aux);
			if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
			tm.tm_mon  -= 1;
			getstr(aux,line,len,7,2);
			tm.tm_mday = atoi(aux);
			if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
			getstr(aux,line,len,10,2);
			tm.tm_hour = atoi(aux);
			if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
			getstr(aux,line,len,13,2);
			tm.tm_min  = atoi(aux);
			if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
			getstr(aux,line,len,16,10);
			tm.tm_sec  = atoi(aux);
			if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
            if (!options->integerRINEXObsSeconds) {
				seconds = atof(aux);
            } else {
                seconds=(double)tm.tm_sec;
			}
			epoch->t.MJDN = MJDN(&tm);
			epoch->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			if (epoch->t.MJDN<FIRSTMJDNGPS || invalidDate==1) {
				sprintf(messagestr,"Invalid date in line '%.80s' in %s observation file",line,epoch->DGNSSstruct==0?"rover":"DGNSS");
				printError(messagestr,options);
			}
			//To convert observation time to GPS time
			epoch->t=tdadd(&epoch->t,epoch->ObsTimeToGPSTime);
			//Fill current epoch string for printing
			strcpy(epoch->tStr,t2doystr(&epoch->t));
			sprintf(epoch->tSoDHourStr,"%s %02d:%02d:%05.2f",epoch->tStr,tm.tm_hour,tm.tm_min,seconds);
			// Calculate GPS Week and Seconds of Week
			ttime2gpswsnoroll(&epoch->t, &epoch->GPSweek, &epoch->SoW);

			//Look for data gaps
			if (epoch->PreviousEpoch.MJDN!=-1) {
				numEpochsMissing=abs((int)(tdiff(&epoch->t,&epoch->PreviousEpoch)/epoch->receiver.interval))-1;
			} else {
				numEpochsMissing=0;
			}
			if (numEpochsMissing>0) {
				if (epoch->PreviousEpoch.MJDN!=-1) {
					epoch->CurrentDataGapSize=numEpochsMissing;
					sprintf(messagestr,"Data gap of %d epoch%s in %s at %17s / %4d %02d %02d %02d:%02d:%04.1f",numEpochsMissing,numEpochsMissing==1?"":"s",epoch->DGNSSstruct==0?"rover observation file":"reference station RINEX observation file",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
					printInfo(messagestr,options);
				} else {
					epoch->CurrentDataGapSize=0;
				}
			} else {
				epoch->CurrentDataGapSize=0;
			}

			if (printProgress==1) {
				//Only save current epoch if it we are reading Rover file, not reference file
				if (epoch->DGNSSstruct==0) {
					if (options->StartEpoch.MJDN!=-1) {
						if(tdiff(&epoch->t,&options->StartEpoch)>=0.) {
							epoch->numEpochsprocessed++;
							epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
							if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
								sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
								epoch->NewPercentage=1;
							}
						} else {
							sprintf(Epochstr,"Skipping epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f                  ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
							epoch->NewPercentage=1;
						}
					} else {
						epoch->numEpochsprocessed++;
						epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
						if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
							sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
							epoch->NewPercentage=1;
						}
					}
				}
			}


			if (twoepochs) {
				if(epoch->firstEpochFile.SoD==-1.) {
					memcpy(&epoch->firstEpochFile,&epoch->t,sizeof(TTime));
				} else {
					if (tdiff(&epoch->t,&epoch->firstEpochFile)>DIFFEQTHRESHOLD) {
						//This is for the case we read the first epoch two times.
						//This occurs if we need to read the first epoch in order to look for Glonass k factors in the navigation file
						twoepochs=0;
						memcpy(&epoch->secondEpochFile,&epoch->t,sizeof(TTime));
					}
				}
			}
				
			getstr(aux,line,len,30,2);
			epoch->numSatellites = atoi(aux);
			for (i=0,j=0;i<epoch->numSatellites;i++,j++) { // Get satellite PRNs
				if ((i%12)==0 && i!=0) {
					if (getL(line,&len,fd)==-1) error = 1; // The next satellites are in the following line
					j = 0;
				}
				cons = line[32+3*j];
				getstr(aux,line,len,33+3*j,2);
				epoch->sat[i].PRN = atoi(aux);
				epoch->sat[i].GNSS=gnsschar2gnsstype(cons);
				epoch->sat2Printpos[i]=epoch->numSatellitesGNSS[epoch->sat[i].GNSS];
				epoch->numSatellitesGNSS[epoch->sat[i].GNSS]++;
				if (cons=='S') {
					if(epoch->sat[i].PRN>QZSSSBASPRNOFFSET) {
						//In RINEX <=3.03,SBAS QZSS signal was mapped to PRN S83-S87.
						//To avoid having a matrix of size 87 for the maximum number PRN,
						//these satellites are mapped to S01-S05
						epoch->sat[i].PRN-=QZSSSBASPRNOFFSET;
					} else if (epoch->sat[i].PRN<=0 || epoch->sat[i].PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in epoch %17s / %4d %02d %02d %02d:%02d:%04.1f in %s observation file",aux,epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->DGNSSstruct==0?"rover":"DGNSS");
						printError(messagestr,options);
					}
				} else if (epoch->sat[i].PRN<=0 || epoch->sat[i].PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in epoch %17s / %4d %02d %02d %02d:%02d:%04.1f in %s observation file",aux,epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->DGNSSstruct==0?"rover":"DGNSS");
					printError(messagestr,options);
				}
				if (epoch->GNSS2PrintPos[epoch->sat[i].GNSS]==-1) {
					epoch->GNSS2PrintPos[epoch->sat[i].GNSS]=epoch->numPrintGNSS;
					epoch->numPrintGNSS++;
					epoch->GNSSinEpoch[epoch->sat[i].GNSS]=1;
					epoch->numGNSSinEpoch++;
				}
			}
			for (i=0;i<epoch->numSatellites;i++) { // Get satellite measurements
				if (getL(line,&len,fd)==-1) error = 1;
				nextRead = 0;
				//If satellite is unselected, don't parse its measurements, as it will not be used, even for printing
				if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) { 
					for (j=0,k=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurementsRINEXHeader;j++,k++) {
						if (nextRead) {
							if (getL(line,&len,fd)==-1) error = 1;
							nextRead = 0;
						}
						getstr(aux,line,len,16*k,14);
						value = atof(aux);
						if (value==0) value = -1.;
						epoch->sat[i].meas[j].value = value;
						epoch->sat[i].meas[j].rawvalue = value;
						if (len<(15+16*k) || line[14+16*k]==' ') {
							epoch->sat[i].meas[j].LLI = -2; //Negative but multiple of 2 so no LLI is detected
						} else {
							getstr(aux,line,len,14+16*k,1);
							epoch->sat[i].meas[j].LLI = atoi(aux);
						}
						if (len<(16+16*k) || line[15+16*k]==' ') {
							epoch->sat[i].meas[j].hasSNRflag=0;
							epoch->sat[i].meas[j].SNRflag = -1;
							epoch->sat[i].meas[j].SNRflagdBHz = SNRtable[0];
							if (epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[j]%4==0) {
								//It is a SNR measurement
								epoch->sat[i].meas[j].SNRvalue=value;
							} else {
								epoch->sat[i].meas[j].SNRvalue = SNRtable[0];
							}
						} else {
							getstr(aux,line,len,15+16*k,1);
							epoch->sat[i].meas[j].hasSNRflag=1;
							epoch->sat[i].meas[j].SNRflag = atoi(aux);
							epoch->sat[i].meas[j].SNRflagdBHz = SNRtable[epoch->sat[i].meas[j].SNRflag];
							if (epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[j]%4==0) {
								//It is a SNR measurement
								epoch->sat[i].meas[j].SNRvalue=value;
							} else {
								epoch->sat[i].meas[j].SNRvalue = epoch->sat[i].meas[j].SNRflagdBHz;
							}
						}
						epoch->sat[i].meas[j].dataFlag = 0;
						if ((k+1)%5==0) { // Following observables are in the next lines (max 5 per line)
							nextRead = 1;
							k=-1; // k will be increased in the for loop
						}
					}
				} else {
					//If satellite is skipped, skip the next data lines from the satellite
					j=(int)((double)epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurementsRINEXHeader)/5.;
					if((epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurementsRINEXHeader%5)==0) {
						j--;
					}
					for(k=0;k<j;k++) {
						if (getL(line,&len,fd)==-1) error = 1;
					}
				}

				for(j=options->noMixedGEOdata;j<=epoch->numSBASsatellites;j++) {
					if (options->SBASConstUsed[j][options->SBASmodePos][epoch->sat[i].GNSS]==1 && options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
						epoch->lastSBASindex[j]=i; 
					}
				}
					
				epoch->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=i;

				if (epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]==-1) {
					//Satellite not seen before
					if (lastCSindex[epoch->DGNSSstruct]==MAX_SATELLITES_VIEWED) {
						sprintf(messagestr,"Maximum different satellites viewed (of all constellations) is %d (MAX_SATELLITES_VIEWED constant), but RINEX observation file has more than this maximum",MAX_SATELLITES_VIEWED);
						printError(messagestr,options);
					}
					epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=lastCSindex[epoch->DGNSSstruct];
					lastCSindex[epoch->DGNSSstruct]++;
					//Fill measurements
					FillMeasurements(epoch->sat[i].GNSS,epoch->sat[i].PRN,i,epoch,options);
				} else if (options->MeasSelected[epoch->DGNSSstruct][epoch->sat[i].GNSS][epoch->sat[i].PRN]==MEASUNSELECTED) {
					//Fill pending measurements
					FillMeasurements(epoch->sat[i].GNSS,epoch->sat[i].PRN,i,epoch,options);
				}
			}
		} else if (epoch->source==RINEX3) {
			
			//////////////////////////////////
			////RINEX 3 observation file

			getstr(aux,line,len,30,2);
			epoch->flag = atoi(aux);
			
			if (epoch->flag>1) { // Unusable epoch
				while(epoch->flag>1) { //There can be multiple event epochs
					if ( epoch->direction == pBACKWARD ) {
						//Save previous epoch
						memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));
						//When going backwards, skip epoch events and look for previous epoch in RINEX observation file
						//If next valid epoch was read, it would make an infinite loop as we want back one epoch, but read two,
						//and the next time we enter this function, we would go back two epochs, which results in always reading 
						//the same epoch
						/*ret = rewindEpochRinexObs(fd,epoch->source);
						if ( ret == 0 ) return 0;
						ret = rewindEpochRinexObs(fd,epoch->source);
						if ( ret == 0 ) return 0;
						if (getL(line,&len,fd)==-1) return 0;*/
					} else {
						invalidDate=0;
						getstr(aux,line,len,2,4);
						tm.tm_year = atoi(aux);
						if (tm.tm_year<1900) invalidDate=1;
						tm.tm_year -= 1900;
						getstr(aux,line,len,7,2);
						tm.tm_mon  = atoi(aux);
						if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
						tm.tm_mon  -= 1;
						getstr(aux,line,len,10,2);
						tm.tm_mday = atoi(aux);
						if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
						getstr(aux,line,len,13,2);
						tm.tm_hour = atoi(aux);
						if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
						getstr(aux,line,len,16,2);
						tm.tm_min  = atoi(aux);
						if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
						getstr(aux,line,len,19,10);
						tm.tm_sec  = atoi(aux);
						if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
						if (!options->integerRINEXObsSeconds) {
							seconds = atof(aux);
						} else {
							seconds=(double)tm.tm_sec;
						}
						if (invalidDate==1) {
							sprintf(messagestr,"Invalid date in line '%.80s' in %s observation file",line,epoch->DGNSSstruct==0?"rover":"DGNSS");
							printError(messagestr,options);
						}

						getstr(aux,line,len,33,2);
						n = atoi(aux);
						for (i=0;i<=n;i++) {
							if (i==n) {
								//Update position of epoch start to remove event epoch
								epoch->epochReadFilePos[epoch->numEpochReadFilePos-1]=ftell(fd);
							}
							if (getL(line,&len,fd)==-1) {
								return 0;
							}
							if (strncmp(&line[60],"APPROX POSITION XYZ",19)==0) {
								if (options->receiverPositionSource==rpRINEX || ( ( (options->receiverPositionSource == rpCALCULATERINEX) || (options->receiverPositionSource == rpCALCULATERINEXREF)  ) && epoch->numAproxPosRead==0)) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPosition[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPosition[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPosition[2] = atof(aux);
									epoch->receiver.aproxPositionError = 1e4; // 10 Km
									epoch->numAproxPosRead++;
								} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPosition[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPosition[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPosition[2] = atof(aux);
									epoch->receiver.aproxPositionError = 0.1; // 10 cm
									epoch->numAproxPosRead++;
								}
								if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
									getstr(aux,line,len,1,14);
									epoch->receiver.aproxPositionRover[0] = atof(aux);
									getstr(aux,line,len,14,14);
									epoch->receiver.aproxPositionRover[1] = atof(aux);
									getstr(aux,line,len,28,14);
									epoch->receiver.aproxPositionRover[2] = atof(aux);
								}
								if(epoch->DGNSSstruct==1) {
									if(epoch->receiver.numRecStation==0) {
										epoch->receiver.RecStationCoord=malloc(sizeof(double*));
										epoch->receiver.RecStationCoord[0]=malloc(sizeof(double)*3);
										memcpy(epoch->receiver.RecStationCoord[0],epoch->receiver.aproxPosition,sizeof(double)*3);
										epoch->receiver.numRecStation++;
									} else {
										if(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][0]!=epoch->receiver.aproxPosition[0] 
												|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][1]!=epoch->receiver.aproxPosition[1]
												|| epoch->receiver.RecStationCoord[epoch->receiver.numRecStation-1][2]!=epoch->receiver.aproxPosition[2]) {
											//Station coordinates are differents from the previous read
											epoch->receiver.RecStationCoord=realloc(epoch->receiver.RecStationCoord,sizeof(double*)*(epoch->receiver.numRecStation+1));
											epoch->receiver.RecStationCoord[epoch->receiver.numRecStation]=malloc(sizeof(double)*3);
											memcpy(epoch->receiver.RecStationCoord[epoch->receiver.numRecStation],epoch->receiver.aproxPosition,sizeof(double)*3);
											epoch->receiver.ChangedStaEpoch=realloc(epoch->receiver.ChangedStaEpoch,sizeof(TTime)*epoch->receiver.numRecStation);
											epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1].MJDN=MJDN(&tm);
											epoch->receiver.ChangedStaEpoch[epoch->receiver.numRecStation-1].SoD=(double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
											epoch->receiver.numRecStation++;
										}
									}
								}
							}
						}
					}
					//Check for more event epochs
					getstr(aux,line,len,30,2);
					epoch->flag = atoi(aux);
				}
				// Check again for RINEX header, as it can occur after an event epoch
				if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
					strcpy(epoch->bufferHeaderLine,line);
					epoch->bufferHeaderLineLen=len;
					return 2;
				}
			}
			
			// Save previous epoch
			memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));

			invalidDate=0;
			getstr(aux,line,len,2,4);
			tm.tm_year = atoi(aux);
			if (tm.tm_year<=1900) invalidDate=1;
			tm.tm_year -= 1900;
			getstr(aux,line,len,7,2);
			tm.tm_mon  = atoi(aux);
			if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
			tm.tm_mon  -= 1;
			getstr(aux,line,len,10,2);
			tm.tm_mday = atoi(aux);
			if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
			getstr(aux,line,len,13,2);
			tm.tm_hour = atoi(aux);
			if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
			getstr(aux,line,len,16,2);
			tm.tm_min  = atoi(aux);
			if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
			getstr(aux,line,len,19,10);
			tm.tm_sec  = atoi(aux);
			if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
            if (!options->integerRINEXObsSeconds) {
				seconds = atof(aux);
            } else {
                seconds=(double)tm.tm_sec;
			}
			epoch->t.MJDN = MJDN(&tm);
			epoch->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			if (epoch->t.MJDN<FIRSTMJDNGPS || invalidDate==1) {
				sprintf(messagestr,"Invalid date in line '%.80s' in %s observation file",line,epoch->DGNSSstruct==0?"rover":"DGNSS");
				printError(messagestr,options);
			}
			//To convert observation time to GPS time
			epoch->t=tdadd(&epoch->t,epoch->ObsTimeToGPSTime);
			//Fill current epoch string for printing
			strcpy(epoch->tStr,t2doystr(&epoch->t));
			sprintf(epoch->tSoDHourStr,"%s %02d:%02d:%05.2f",epoch->tStr,tm.tm_hour,tm.tm_min,seconds);
			// Calculate GPS Week and Seconds of Week
			ttime2gpswsnoroll(&epoch->t, &epoch->GPSweek, &epoch->SoW);
			
			//Look for data gaps
			if (epoch->PreviousEpoch.MJDN!=-1) {
				numEpochsMissing=abs((int)(tdiff(&epoch->t,&epoch->PreviousEpoch)/epoch->receiver.interval))-1;
			} else {
				numEpochsMissing=0;
			}
			if (numEpochsMissing>0) {
				if (epoch->PreviousEpoch.MJDN!=-1) {
					epoch->CurrentDataGapSize=numEpochsMissing;
					sprintf(messagestr,"Data gap of %d epoch%s in %s at %17s / %4d %02d %02d %02d:%02d:%04.1f",numEpochsMissing,numEpochsMissing==1?"":"s",epoch->DGNSSstruct==0?"rover observation file":"reference station RINEX observation file",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
					printInfo(messagestr,options);
				} else {
					epoch->CurrentDataGapSize=0;
				}
			} else {
				epoch->CurrentDataGapSize=0;
			}

			if (printProgress==1) {
				//Only save current epoch if it we are reading Rover file, not reference file
				if (epoch->DGNSSstruct==0) {
					if (options->StartEpoch.MJDN!=-1) {
						if(tdiff(&epoch->t,&options->StartEpoch)>=0.) {
							epoch->numEpochsprocessed++;
							epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
							if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
								sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
								epoch->NewPercentage=1;
							}
						} else {
							sprintf(Epochstr,"Skipping epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f                  ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
							epoch->NewPercentage=1;
						}
					} else {
						epoch->numEpochsprocessed++;
						epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
						if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
							sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
							epoch->NewPercentage=1;
						}
					}
				}
			}

			if (twoepochs) {
				if(epoch->firstEpochFile.SoD==-1.) {
					memcpy(&epoch->firstEpochFile,&epoch->t,sizeof(TTime));
				} else {
					twoepochs=0;
					memcpy(&epoch->secondEpochFile,&epoch->t,sizeof(TTime));
				}
			}
				
			getstr(aux,line,len,33,2);
			epoch->numSatellites = atoi(aux);
			for (i=0;i<epoch->numSatellites;i++) { // Get satellite measurements and PRNs
				if (getL(line,&len,fd)==-1) error = 1;
				epoch->sat[i].GNSS = gnsschar2gnsstype(line[0]);
				getstr(aux,line,len,1,2);
				epoch->sat[i].PRN = atoi(aux);
				epoch->sat2Printpos[i]=epoch->numSatellitesGNSS[epoch->sat[i].GNSS];
				epoch->numSatellitesGNSS[epoch->sat[i].GNSS]++;
				if (line[0]=='S') {
					if(epoch->sat[i].PRN>QZSSSBASPRNOFFSET) {
						//In RINEX <=3.03,SBAS QZSS signal was mapped to PRN S83-S87.
						//To avoid having a matrix of size 87 for the maximum number PRN,
						//these satellites are mapped to S01-S05
						epoch->sat[i].PRN-=QZSSSBASPRNOFFSET;
					} else if (epoch->sat[i].PRN<=0 || epoch->sat[i].PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in epoch %17s / %4d %02d %02d %02d:%02d:%04.1f in %s observation file",aux,epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->DGNSSstruct==0?"rover":"DGNSS");
						printError(messagestr,options);
					}
				} else if (epoch->sat[i].PRN<=0 || epoch->sat[i].PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in epoch %17s / %4d %02d %02d %02d:%02d:%04.1f in %s observation file",aux,epoch->tStr,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->DGNSSstruct==0?"rover":"DGNSS");
					printError(messagestr,options);
				}
				if (epoch->GNSS2PrintPos[epoch->sat[i].GNSS]==-1) {
					epoch->GNSS2PrintPos[epoch->sat[i].GNSS]=epoch->numPrintGNSS;
					epoch->numPrintGNSS++;
					epoch->GNSSinEpoch[epoch->sat[i].GNSS]=1;
					epoch->numGNSSinEpoch++;
				}
				//If satellite is unselected, don't parse its measurements, as it will not be used, even for printing
				if (options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) { 
					for (j=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurementsRINEXHeader;j++) {
						getstr(aux,line,len,3+16*j,14);
						value = atof(aux);
						if (value==0) value = -1.;
						epoch->sat[i].meas[j].value = value;
						epoch->sat[i].meas[j].rawvalue = value;
						if (len<(18+16*j) || line[17+16*j]==' ') {
							epoch->sat[i].meas[j].LLI = -2; //Negative but multiple of 2 so no LLI is detected
						} else {
							getstr(aux,line,len,17+16*j,1);
							epoch->sat[i].meas[j].LLI = atoi(aux);
						}
						if (len<(19+16*j) || line[18+16*j]==' ') {
							epoch->sat[i].meas[j].hasSNRflag=0;
							epoch->sat[i].meas[j].SNRflag = -1;
							epoch->sat[i].meas[j].SNRflagdBHz = SNRtable[0];
							if (epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[j]%4==0) {
								//It is a SNR measurement
								epoch->sat[i].meas[j].SNRvalue=value;
							} else {
								epoch->sat[i].meas[j].SNRvalue = SNRtable[0];
							}
						} else {
							getstr(aux,line,len,18+16*j,1);
							epoch->sat[i].meas[j].hasSNRflag=1;
							epoch->sat[i].meas[j].SNRflag = atoi(aux);
							epoch->sat[i].meas[j].SNRflagdBHz = SNRtable[epoch->sat[i].meas[j].SNRflag];
							if (epoch->measOrder[epoch->sat[i].GNSS].ind2Meas[j]%4==0) {
								//It is a SNR measurement
								epoch->sat[i].meas[j].SNRvalue=value;
							} else {
								epoch->sat[i].meas[j].SNRvalue = epoch->sat[i].meas[j].SNRflagdBHz;
							}
						}
						epoch->sat[i].meas[j].dataFlag = 0;
					}
				}

				for(j=options->noMixedGEOdata;j<=epoch->numSBASsatellites;j++) {
					if (options->SBASConstUsed[j][options->SBASmodePos][epoch->sat[i].GNSS]==1 && options->includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]==1) {
						epoch->lastSBASindex[j]=i; 
					}
				}

				epoch->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=i;

				if (epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]==-1) {
					//Satellite not seen before
					if (lastCSindex[epoch->DGNSSstruct]==MAX_SATELLITES_VIEWED) {
						sprintf(messagestr,"Maximum different satellites viewed (of all constellations) is %d, but RINEX observation file has more than this maximum",MAX_SATELLITES_VIEWED);
						printError(messagestr,options);
					}
					epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=lastCSindex[epoch->DGNSSstruct];
					lastCSindex[epoch->DGNSSstruct]++;
					//Fill measurements
					FillMeasurements(epoch->sat[i].GNSS,epoch->sat[i].PRN,i,epoch,options);
				} else if (options->MeasSelected[epoch->DGNSSstruct][epoch->sat[i].GNSS][epoch->sat[i].PRN]==MEASUNSELECTED) {
					//Fill pending measurements
					FillMeasurements(epoch->sat[i].GNSS,epoch->sat[i].PRN,i,epoch,options);
				}
			}
		} // (epoch->source==RINEX3)
	}

	//Sort GNSS print list position so it is always in order GPS,GAL,GLO,GEO,BDS,QZS,IRN instead of the order of the satellites read in the current RINEX observation file
	j=0;
	for(i=0;i<MAX_GNSS;i++) {
		if (epoch->GNSS2PrintPos[i]!=-1) {
			epoch->GNSS2PrintPos[i]=j;
			epoch->PrintPos2GNSS[j]=i;
			j++;
		}
	}
	//Create list with order of printing for satellites
	k=0;
	for(i=0;i<epoch->numPrintGNSS;i++) {
		for(j=0;j<epoch->numSatellites;j++) {
			if (epoch->GNSS2PrintPos[epoch->sat[j].GNSS]==i) {
				epoch->printIndex2satIndex[k]=j;
				k++;
			}
		}
	}

	//Duplicate measurements if needed (e.g. C1C to C1P, or whatever measurement not in file but is creaing with DCBs)
	if (epoch->MeasToBeDuplicated==1) {
		for(i=0;i<epoch->numSatellites;i++) {
			GNSS=epoch->sat[i].GNSS;
			for(j=0;j<epoch->measOrder[GNSS].numMeasToCopy;j++) {
				meas=epoch->measOrder[GNSS].measListToCopy[j];
				posMeasDest=epoch->measOrder[GNSS].meas2Ind[meas];
				posMeasSrc=epoch->measOrder[GNSS].meas2SourceInd[meas];
				epoch->sat[i].meas[posMeasDest].value=epoch->sat[i].meas[posMeasSrc].value;
				epoch->sat[i].meas[posMeasDest].rawvalue=epoch->sat[i].meas[posMeasSrc].rawvalue;
				epoch->sat[i].meas[posMeasDest].SNRvalue=epoch->sat[i].meas[posMeasSrc].SNRvalue;
				epoch->sat[i].meas[posMeasDest].LLI=epoch->sat[i].meas[posMeasSrc].LLI;
			}
		}
	}

	return (properlyRead && !error); // properly read AND no error	
}

/*****************************************************************************
 * Name        : rewindEpochRinexObs
 * Description : Rewind one epoch backward in a RINEX observation file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * enum Source  src                I  N/A  Source of the RINEX file (RINEX2 or RINEX3)
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error or EOF (no more epochs)
 *****************************************************************************/
int rewindEpochRinexObs (FILE *fd, enum Source src) {
	int			ret;
	int			yy=-1,mm=-1,dd=-1,hour=-1,minute=-1;
	char 		line[MAX_INPUT_LINE];
	char    	aux[100];
	int 		len = 0;
	
	while (1) {
		ret = getLback(line,&len,fd);
		if (ret==-1) return 0;
		if (len>72 && strncmp(&line[60],"END OF HEADER",13)==0) {
			//Read backward until beginning of header is found
			while (1) {
				ret = getLback(line,&len,fd);
				if (ret==-1) return 0;
				if (len>79 && strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
					break;
				}
			}
		} else {
			// Check if date is within margins to detect init of epoch
			// RINEX 2.11
			if (src==RINEX2) {
				getstr(aux,line,len,0,4);
				yy = atoi(aux);
				getstr(aux,line,len,3,4);
				mm = atoi(aux);
				getstr(aux,line,len,6,4);
				dd = atoi(aux);
				getstr(aux,line,len,9,4);
				//The '.' detection is to avoid some measurements with many 0's to produce a valid date
				//With the check of the dot, the date string will never have a '.' 
				//For example, the following line in a RINEX 2:
				//   20010008.523   105153351.772         472.098          50.585    20010006.448
				//This produced a valid date, when clearly is not the line where an epoch starts
				if(aux[1]=='.'||aux[2]=='.') {
					hour=-1;
				} else {
					hour = atoi(aux);
				}
				getstr(aux,line,len,12,4);
				minute = atoi(aux);
				if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && minute>=0 &&minute<=59) {
					return 1;
				}
			// RINEX 3.00
			} else if (src==RINEX3) {
				//The len<60 is to avoid potential header or comment lines starting with ">"
				if (line[0]=='>' && len<60) return 1;
			} else return 0;
		}
	}
}

/*****************************************************************************
 * Name        : getEpochFromObsFile
 * Description : This function reads the timestamp of the start of an epoch,
 *                and leaves the file pointer to the same position. The epoch
 *                is written in the TTime structure parameter
 *               IMPORTANT: This function assumes that the next line to be
 *                read is the start of the next epoch. If it is not the case,
 *                this function will give an error.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * enum Source  src                I  N/A  Source of the RINEX file (RINEX2 or RINEX3)
 * TTime *t                        O  N/A  Timestamp read of the current epoch
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Timestamp of start of epoch read
 *                                         0 => No start of epoch found
 *****************************************************************************/
int getEpochFromObsFile (FILE *fd, enum Source src, TTime *t) {
	int			i,n;
	int			ret;
	int			yy=-1,mm=-1,dd=-1,hour=-1,minute=-1;
	int 		len = 0;
	int			epochflag=0;
	off_t		posFile;
	char 		line[MAX_INPUT_LINE];
	char    	aux[100];
	double		seconds;
	struct tm   tm;

	posFile = ftell(fd);

	ret = getL(line,&len,fd);

	//Check line is not an event epoch
	if (ret==-1) {
		fseek(fd,posFile,SEEK_SET);
		return 0;
	} else if (src == RINEX2) {
		getstr(aux,line,len,27,2);
		epochflag = atoi(aux);
		getstr(aux,line,len,30,2);
		n = atoi(aux);
	} else {
		getstr(aux,line,len,30,2);
		epochflag = atoi(aux);
		getstr(aux,line,len,33,2);
		n = atoi(aux);
	}

	if (epochflag>1) {
		for (i=0;i<=n;i++) {
			if (getL(line,&len,fd)==-1) {
				fseek(fd,posFile,SEEK_SET);
				return 0;
			}
		}
	}
	
	if (src == RINEX2) {
		getstr(aux,line,len,0,4);
		yy = tm.tm_year = atoi(aux);
		if (tm.tm_year <= 70) tm.tm_year += 100;
		getstr(aux,line,len,3,4);
		mm = atoi(aux);
		tm.tm_mon  = mm - 1;
		getstr(aux,line,len,6,4);
		dd = tm.tm_mday = atoi(aux);
		getstr(aux,line,len,9,4);
		if(aux[1]=='.'||aux[2]=='.') {
			hour= tm.tm_hour = -1;
		} else {
			hour = tm.tm_hour = atoi(aux);
		}
		getstr(aux,line,len,12,4);
		minute = tm.tm_min  = atoi(aux);
		getstr(aux,line,len,16,10);
		tm.tm_sec  = atoi(aux);
		seconds = atof(aux);
	} else {
		//RINEX v3
		if (line[0]=='>' && len<60) {
			//Line with valid epoch
			getstr(aux,line,len,2,4);
			yy =  atoi(aux);
			if (yy>=2000) yy-=2000;
			else yy-=1900;
			tm.tm_year = atoi(aux)-1900;
			getstr(aux,line,len,7,2);
			mm = atoi(aux);
			tm.tm_mon = mm-1;
			getstr(aux,line,len,10,2);
			dd = tm.tm_mday = atoi(aux);
			getstr(aux,line,len,13,2);
			hour = tm.tm_hour = atoi(aux);
			getstr(aux,line,len,16,2);
			minute = tm.tm_min  = atoi(aux);
			getstr(aux,line,len,19,10);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
		} else {
			hour=-1;
		}
	}
	if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && minute>=0 &&minute<=59) {
		//Epoch timestamp found
		t->MJDN = MJDN(&tm);
		t->SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
		fseek(fd,posFile,SEEK_SET);
		return 1;
	}
	fseek(fd,posFile,SEEK_SET);
	return 0;
}

/*****************************************************************************
 * Name        : readRinexNav
 * Description : Read a RINEX navigation file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * char *filename                  I  N/A  Navigation filename
 * TGNSSproducts  *products        O  N/A  Structure to save the data
 * double *rinexNavVersion         O  N/A  Rinex Navigation version number
 * int newDay                      I  N/A  Flag to indicate if it is a new day
 *                                          day read or it is another file for
 *                                          the same day (this flag is necessary
 *                                          for not freeing memory)
 *                                          NEWDAYNAV  -> Reading new day. Free memory
 *                                          SAMEDAYNAV -> Reading same day. 
 *                                                        Do not free memory
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error
 *****************************************************************************/
int readRinexNav (FILE *fd, char *filename, TGNSSproducts *products, double *rinexNavVersion, int newDay, TOptions  *options) {
	int 						len = 0, ret, msgtype,IODE;
	int							returnValue = 0;
	int							readingHeader = 1;
	int							i,j,l;
	int							GPSweek;
	int							DoW;	//Day of Week
	int							row;
	int							indSat, indBlock,indBlockIOD;
	int							offsetRinex2=0; //QZSS RINEX2 have in the first line the constellation character (not official)
	int							leapSecond;
	int							invalidDate=0;
	//int							DataTypeRead[MAX_GNSS*MAX_SATELLITES_PER_GNSS][MAX_BRDC_TYPES];
	unsigned int				k;  //to avoid warning: comparison between signed and unsigned integer expressions
	TBRDCblock					block;
	struct tm					tm;
	double						seconds;
	double						SoW;
	double						frameTimeGLO=0.;
	enum TimeSystemCorrection	timecorr;	
	enum GNSSystem				satSystem;
	char						line[MAX_INPUT_LINE];
	char						aux[100], aux2[100], a0[100], a1[100], a2[100], a3[100];
	char						ConstellationType[2];
	static int					numline=0;
	static int					bufferHeaderLineLen=0;
	static char					bufferHeaderLine[MAX_INPUT_LINE];

	products->type = BRDC;
	// If to avoid overwritten products structure when RINEX navigation are concatennated
	if ( products->BRDC == NULL ) {
		products->BRDC = malloc(sizeof(TBRDCproducts));
		initBRDCproducts(products->BRDC,options->GLOintStep);
	} else {
		if ( products->BRDC->numblocks!=NULL && newDay==NEWDAYNAV) {
			//This is the second or more day we are reading. We need to free memory
			freeBRDCproducts(FREEPREVNAV,products);
		
			memcpy(&products->BRDC->indexPast,&products->BRDC->index,sizeof(int)*MAX_GNSS*MAX_SATELLITES_PER_GNSS);
			memcpy(&products->BRDC->AvailBRDCTypePast,&products->BRDC->AvailBRDCType,sizeof(int)*MAX_GNSS*MAX_BRDC_TYPES);

			products->BRDC->blockPast=products->BRDC->block;
			products->BRDC->blockPastPointer=products->BRDC->blockPointer;
			products->BRDC->blockPastIOD=products->BRDC->blockIOD;
			products->BRDC->numblocksPast=products->BRDC->numblocks;
			products->BRDC->numblocksPastIOD=products->BRDC->numblocksIOD;

			products->BRDC->numsatsPast=products->BRDC->numsats;
			products->BRDC->AT_LSpast=products->BRDC->AT_LS;
			products->BRDC->AT_LSFpast=products->BRDC->AT_LSF;
			products->BRDC->WN_LSFpast=products->BRDC->WN_LSF;
			products->BRDC->leapSecondsPast=products->BRDC->leapSeconds;
			products->BRDC->LeapSecondsAvailPast=products->BRDC->LeapSecondsAvail;
			products->BRDC->LeapSecondsAvail=0;
			products->BRDC->numsats = 0;
			products->BRDC->block = NULL;
			products->BRDC->blockPointer = NULL;
			products->BRDC->blockIOD = NULL;
			products->BRDC->numblocks = NULL;
			products->BRDC->numblocksIOD = NULL;
			for (i=0;i<MAX_GNSS;i++) {
				for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					products->BRDC->index[i][j] = -1;
				}
				for (j=0;j<MAX_BRDC_TYPES;j++) {
					products->BRDC->AvailBRDCType[i][j]=0;
				}
			}
		}
	}

	ConstellationType[0] = '\0';
	/*for(i=0;i<MAX_GNSS*MAX_SATELLITES_PER_GNSS;i++) {
		for(j=0;j<MAX_BRDC_TYPES;j++) {
			DataTypeRead[i][j]=0;
		}
	}*/

	if (bufferHeaderLineLen>0) {
		strcpy(line,bufferHeaderLine);
		len=bufferHeaderLineLen;
		bufferHeaderLineLen=0;
		bufferHeaderLine[0]='\0';
	} else {
		if (getL(line,&len,fd)==-1) return 0;
	}

	do {
		numline++;
		if (len<2) continue; //Skip blank lines
		if (strncmp(&line[60],"COMMENT",7)==0) continue; //Comment can also be in the middle of the file
		if (readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,len,0,9);
				*rinexNavVersion = atof(aux);
				if ((int)(*rinexNavVersion)>5) {return 0;} //Version check (version 4 is allowed for non-official CNAV/LNAV RINEX)
				if((int)*(rinexNavVersion)==2 && line[20]=='G') {
					// GLONASS Rinex v2 navigation file
					satSystem=GLONASS;
				} else if ((int)(*rinexNavVersion)==2 && line[20]=='H') {
					// GEO Rinex v2 navigation file
					satSystem=GEO;
				} else if ((int)(*rinexNavVersion)==2 && (line[20]=='E'|| line[40]=='E')) {
					// Galileo Rinex v2 unofficial navigation file
					satSystem=Galileo;
				} else if ((int)(*rinexNavVersion)==2 && (line[20]=='J' || line[40]=='J') ) {
					// QZSS Rinex v2 unofficial navigation file
					satSystem=QZSS;
					offsetRinex2=1;
				} else if ((int)(*rinexNavVersion)==2 && (line[20]=='C' || line[40]=='C') ) {
					// BDS Rinex v2 unofficial navigation file
					satSystem=BDS;
					offsetRinex2=1;
				} else if ((int)(*rinexNavVersion)==2 && (line[20]=='I' || line[40]=='I') ) {
					// IRNSS Rinex v2 unofficial navigation file
					satSystem=IRNSS;
					offsetRinex2=1;
				} else if ((int)(*rinexNavVersion)==2) {
					satSystem=GPS;
				}
			} else if (strncmp(&line[60],"ION ALPHA",9)==0) {  // Rinex v2
				for (i=0;i<4;i++) {
					getstr(aux,line,len,2+12*i,12);
					for (k=0;k<strlen(aux);k++) {
						if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
					}
					products->BRDC->ionA[i] = atof(aux);
				}
			} else if (strncmp(&line[60],"ION BETA",8)==0) {  // Rinex v2
				for (i=0;i<4;i++) {
					getstr(aux,line,len,2+12*i,12);
					for (k=0;k<strlen(aux);k++) {
						if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
					}
					products->BRDC->ionB[i] = atof(aux);
				}
			} else if (strncmp(&line[60],"IONOSPHERIC CORR",16)==0) {  // Rinex v3
				if (strncmp(&line[0],"GPSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ionA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"GPSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ionB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"GAL",3)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ai[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"BDSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->bdsA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"BDSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->bdsB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"QZSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->qzsA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"QZSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->qzsB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"IRNA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->irnA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"IRNB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,len,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->irnB[i] = atof(aux);
					}
				}
			} else if (strncmp(&line[60],"TIME SYSTEM CORR",16)==0) {  //Rinex v3
				getstr(aux,line,len,0,4);
				timecorr = timecorrstr2timecorrtype(aux); 
				if ( timecorr != UNKNOWN_TIME_CORR){
					getstr(aux,line,len,5,17);
					products->BRDC->timeSysCorr[timecorr].acoff[0] = atof(aux);
					getstr(aux,line,len,22,16);
					products->BRDC->timeSysCorr[timecorr].acoff[1] = atof(aux);
					getstr(aux,line,len,38,7);
					products->BRDC->timeSysCorr[timecorr].timeref = atoi(aux);
					getstr(aux,line,len,45,5);
					products->BRDC->timeSysCorr[timecorr].weekref = atoi(aux);
				}
			} else if (strncmp(&line[60],"LEAP SECONDS",12)==0) {  
				getstr(aux,line,len,0,6);
				if(aux[0] != '\0') { // Check if no number given
					products->BRDC->AT_LS = atoi(aux);
					products->BRDC->leapSeconds=products->BRDC->AT_LS;
					if(products->BRDC->AT_LS>0) {
						products->BRDC->LeapSecondsAvail=1;
					}
				}
				getstr(aux,line,len,6,6);
				if(aux[0] != '\0') { // Check if no number given
					products->BRDC->AT_LSF = atoi(aux);
				}
				getstr(aux,line,len,12,6);
				if(aux[0] != '\0') { // Check if no number given
					products->BRDC->WN_LSF = atoi(aux);
				}
				getstr(aux,line,len,18,6);
				if(aux[0] != '\0') { // Check if no number given
					products->BRDC->DN = atoi(aux);
				}
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
				row = 0;
				returnValue = 1;
			}
		} else {  // Reading body
			// Block to detect new RINEX header, it only affects when large RINEX are used
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				strcpy(bufferHeaderLine,line);
				bufferHeaderLineLen=len;
				numline--;
				returnValue=2;
				break;
			}
			if ((int)(*rinexNavVersion)==2) {
				if ( row == 0 ) {
					initBRDCblock(&block);
					block.GNSS=satSystem;
					getstr(aux,line,len,0+offsetRinex2,2);
					block.PRN = atoi(aux);
					if (block.PRN<=0 || block.PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN '%s' in line %d in navigation file [%s]",aux,numline,filename);
						printError(messagestr,options);
					}
					invalidDate=0;
					getstr(aux,line,len,3+offsetRinex2,2);
					tm.tm_year = atoi(aux);
					if (tm.tm_year<=0) invalidDate=1;
					else if (tm.tm_year <= 70) tm.tm_year += 100;
					getstr(aux,line,len,6+offsetRinex2,2);
					tm.tm_mon  = atoi(aux);
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,line,len,9+offsetRinex2,2);
					tm.tm_mday = atoi(aux);
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,line,len,12+offsetRinex2,2);
					tm.tm_hour = atoi(aux);
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,line,len,15+offsetRinex2,2);
					tm.tm_min  = atoi(aux);
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,line,len,18+offsetRinex2,4);
					tm.tm_sec  = atoi(aux);
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
					seconds = atof(aux);
					if (satSystem==GLONASS) {
						block.TtocUTC.MJDN = MJDN(&tm);
						block.TtocUTC.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					} else {
						block.Ttoc.MJDN = MJDN(&tm);
						block.Ttoc.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					}
					if (invalidDate==1) {
						sprintf(messagestr,"Invalid date '%.22s' in line %d in navigation file [%s]",line,numline,filename);
						printError(messagestr,options);
					}
				}
				getstr(a0,line,len,3+offsetRinex2,19);
				if (a0[13]=='D' || a0[13]=='e') a0[13]='E';
				if (a0[14]=='D' || a0[14]=='e') a0[14]='E';
				if (a0[15]=='D' || a0[15]=='e') a0[15]='E';      // '-' sign can appear or not
				getstr(a1,line,len,22+offsetRinex2,19);
				if (a1[13]=='D' || a1[13]=='e') a1[13]='E';
				if (a1[14]=='D' || a1[14]=='e') a1[14]='E';
				if (a1[15]=='D' || a1[15]=='e') a1[15]='E';      // '-' sign can appear or not
				getstr(a2,line,len,41+offsetRinex2,19);
				if (a2[13]=='D' || a2[13]=='e') a2[13]='E';
				if (a2[14]=='D' || a2[14]=='e') a2[14]='E';
				if (a2[15]=='D' || a2[15]=='e') a2[15]='E';      // '-' sign can appear or not
				getstr(a3,line,len,60+offsetRinex2,19);
				if (a3[13]=='D' || a3[13]=='e') a3[13]='E';
				if (a3[14]=='D' || a3[14]=='e') a3[14]='E';
				if (a3[15]=='D' || a3[15]=='e') a3[15]='E';      // '-' sign can appear or not

				//Galileo is not officially in RINEX 2 navigation files, but some ftp servers do give Galileo navigation data in RINEX v2
				//QZSS is not officially in RINEX 2 navigation files, but some ftp servers do give QZSS navigation data in RINEX v2
				switch (satSystem) {
					case GPS: case Galileo: case BDS: case QZSS: case IRNSS:
						switch (row) {
							case 0:		
								block.clockbias					= atof(a1);
								block.clockdrift				= atof(a2);
								block.clockdriftrate			= atof(a3);
								break;
							case 1:
								switch (satSystem) {
									case GPS: case QZSS:
										block.IODE              = (int)atof(a0);
										break;
									case BDS:
										block.IODE		        = -1; //No IODE provided
										block.AODE				= (int)atof(a0);
										break;
									default:
										block.IODE				= (int)atof(a0);
										break;
								}
								block.crs						= atof(a1);
								block.deltan					= atof(a2);
								block.M0						= atof(a3);
								break;
							case 2:
								block.cuc						= atof(a0);
								block.e							= atof(a1);
								block.cus						= atof(a2);
								block.sqrta						= atof(a3);
								break;
							case 3:
								block.toe						= atof(a0);
								block.cic						= atof(a1);
								block.OMEGA						= atof(a2);
								block.cis						= atof(a3);
								break;
							case 4:
								block.i0						= atof(a0);
								block.crc						= atof(a1);
								block.omega						= atof(a2);
								block.OMEGADOT					= atof(a3);
								break;
							case 5:
								//GPS, Galileo, and QZSS all in GPS time
								//BDS in BeiDou time
								block.IDOT						= atof(a0);
								switch(satSystem) {
									case GPS: case QZSS:
										block.codesOnL2			= (int)atof(a1);
										block.GPSweek			= (int)atof(a2);
										block.L2Pdataflag		= (int)atof(a3);
										break;
									case Galileo:
										block.dataSources		= (int)atof(a1);
										block.GALweek			= (int)atof(a2);
										block.GPSweek			= block.GALweek;
										break;
									case BDS:
										block.BDSweek			= (int)atof(a2);
										block.GPSweek			= block.BDSweek+1356;
										break;
									case IRNSS:
										block.GPSweek           = (int)atof(a2);
										break;
									default:
										break;

								}
								break;
							case 6:
								switch(satSystem) {
									case GPS: case QZSS:
										block.SVaccuracy		= atof(a0);
										block.SVhealth			= (int)atof(a1);
										block.TGD				= atof(a2);
										block.IODC				= (int)atof(a3);
										break;
									case Galileo:
										block.SVaccuracy		= atof(a0);
										block.SVhealth			= (int)atof(a1);
										block.SISASignal		= block.SVaccuracy;
										block.BGDE5a			= atof(a2);
										block.BGDE5b			= atof(a3);
										break;
									case BDS:
										block.SVaccuracy		= atof(a0);
										block.SVhealth			= (int)atof(a1);
										block.TGD26             = atof(a2);
										block.TGD76            	= atof(a3);
										block.TGD16            	= 0.;
										block.TGD56            	= 0.;
										block.ISCB1Cd			= 0.;
										block.ISCB2ad			= 0.;
										break;
									case IRNSS:
										block.IRNURA			= atof(a0);
										block.SVaccuracy		= block.IRNURA;
										block.SVhealth			= (int)atof(a1);
										block.TGD				= atof(a2);
										break;
									default:
										break;
								}
								break;
							case 7:
								//GPS, Galileo, and QZSS all in GPS time
								block.transTime					= atof(a0);
								switch(satSystem) {
									case GPS:
										block.fitInterval		= atof(a1);
										if ( block.fitInterval == 0 ) block.fitInterval = 4;
										//Set broadcast message type
										block.BRDCtype = GPSLNAV;
										products->BRDC->AvailBRDCType[GPS][GPSLNAV]=1;
										//Check if IODC%256 matches with IODE
										if (block.IODC%256!=block.IODE) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid GPS message (IODC%%256 (%d) does not match IODE (%d)) in line %d in navigation file [%s]. Message discarded",block.IODC%256,block.IODE,numline,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										} else if (block.IODE<0 || block.IODE>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid GPS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									case QZSS:
										block.fitInterval		= atof(a1);
										if ( block.fitInterval == 0 ) block.fitInterval = 2;
										else block.fitInterval 	= 4;
										//Set broadcast message type
										block.BRDCtype = QZSLNAV;
										products->BRDC->AvailBRDCType[QZSS][QZSLNAV]=1;
										//Check if IODC%256 matches with IODE
										if (block.IODC%256!=block.IODE) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid QZSS message (IODC%%256 (%d) does not match IODE (%d)) in line %d in navigation file [%s]. Message discarded",block.IODC%256,block.IODE,numline,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										} else if (block.IODE<0 || block.IODE>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid QZSS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									case Galileo:
										block.fitInterval		= 4;
										//Set broadcast message type
										switch (block.dataSources & GALILEOBRDCMSGMASK) {
											case 258:
												//FNAV E5a
												block.BRDCtype = GalFNAV;
												products->BRDC->AvailBRDCType[Galileo][GalFNAV]=1;
												break;
											case 513:
												//INAV E1-B only
												block.BRDCtype = GalINAVE1;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE1]=1;
												break;
											case 516:
												//INAV E5b only
												block.BRDCtype = GalINAVE5b;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE5b]=1;
												break;
											case 517:
												//INAV E1-B+E5b
												block.BRDCtype = GalINAVE1E5b;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE1E5b]=1;
												break;
											default:
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid Galileo message type (Data Sources has invalid value %d) in line %d in navigation file [%s]. Message discarded",block.dataSources,numline-2,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
												break;
										} 
										if (block.IODE<0 || block.IODE>1023) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid Galileo message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									case BDS:
										block.transTime			= atof(a0);
										block.AODC              = (int)atof(a1);
										block.IODC              = -1; //No IODC provided
										block.fitInterval		= 4; //Fit interval is not provided
										//Set broadcast message type
										block.BRDCtype = BDSD1;
										products->BRDC->AvailBRDCType[BDS][BDSD1]=1;
										break;
									case IRNSS:
										block.transTime			= atof(a0);
										block.IODC              = -1; //No IODC provided
										block.fitInterval		= 4; //Fit interval is not provided
										//Set broadcast message type
										block.BRDCtype = IRNCNAV;
										products->BRDC->AvailBRDCType[IRNSS][IRNCNAV]=1;
										if (block.IODE<0 || block.IODE>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid IRNSS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									default:
										break;
								}
								if (block.transTime>=0.9999E9) {
									//Invalid transmission time
									switch(satSystem) {
										case GPS:
											sprintf(messagestr,"WARNING: Invalid %s tranmission time (%f) in line %d in navigation file [%s]. Toe - FitInterval/2 will be used as transmission time",gnsstype2gnssname(block.GNSS),block.transTime,numline,filename);
											block.transTime=block.toe-block.fitInterval*3600./2.;
											break;
										case Galileo:
											sprintf(messagestr,"WARNING: Invalid %s tranmission time (%f) in line %d in navigation file [%s]. Toe will be used as transmission time",gnsstype2gnssname(block.GNSS),block.transTime,numline,filename);
											block.transTime=block.toe;
											break;
										default:
											sprintf(messagestr,"WARNING: Invalid %s tranmission time (%f) in line %d in navigation file [%s]. Toe - 2h will be used as transmission time",gnsstype2gnssname(block.GNSS),block.transTime,numline,filename);
											block.transTime=block.toe-7200.;
											break;
									}
									printInfo(messagestr,options);
								}
								break;
							default:
								break;
						}
						break;
					case GLONASS: case GEO:
						switch(row){
							case 0:
								//Glonass in UTC time. GEO in GPS time
								block.clockbias					= atof(a1);
								switch(satSystem) {
									case GLONASS:
										block.clockdrift    	= atof(a2);
										frameTimeGLO			= atof(a3);
										break;
									case GEO:
										block.clockdrift    	= atof(a2);
										block.transTime			= atof(a3);
										break;
									default:
										break;
								}
								block.clockdriftrate			= 0.0;
								//No IODE and IODC provided. Set it to -1
								block.IODE								= -1;
								block.IODC         			           	= -1; 
								block.SVaccuracy						= 0.;
								break;
							case 1:
								block.satPos[0]           		= atof(a0)*1000;
								block.satVel[0]           		= atof(a1)*1000;
								block.satAcc[0]           		= atof(a2)*1000;
								block.SVhealth          		= (int)atof(a3);
								break;
							case 2:
								block.satPos[1]           		= atof(a0)*1000;
								block.satVel[1]           		= atof(a1)*1000;
								block.satAcc[1]    		    	= atof(a2)*1000;
								switch(satSystem) {
									case GLONASS:
										block.freqnumber    	= (int)atof(a3);
										block.SVaccuracy		= 0.;
										break;
									case GEO:
										block.URAGEO			= (int)atof(a3);
										block.SVaccuracy		= (int)atof(a3);;
										break;
									default:
										break;
								}
								break;
							case 3:
								block.satPos[2]           		= atof(a0)*1000;
								block.satVel[2]           		= atof(a1)*1000;
								block.satAcc[2]           		= atof(a2)*1000;
								switch(satSystem) {
									case GLONASS:
										block.ageofoperation	= (int)atof(a3);
										block.fitInterval 		= 0.5; //For GLONASS, fit interval is 30 min
										//Set broadcast message type
										block.BRDCtype = GLOFDMA;
										products->BRDC->AvailBRDCType[GLONASS][GLOFDMA]=1;
										break;
									case GEO:
										block.IODNGEO			= (int)atof(a3);
										block.IODE				= block.IODNGEO;
										block.fitInterval 		= 4;
										//Set broadcast message type
										block.BRDCtype = GEOCNAV;
										products->BRDC->AvailBRDCType[GEO][GEOCNAV]=1;
										if (block.IODNGEO<0 || block.IODNGEO>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid GEO message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODNGEO,numline,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									default:
										break;
								}
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
				row++;
				if ( row == 8 || (row==4 && (satSystem == GLONASS || satSystem == GEO ))) {
					row = 0;
					switch(satSystem) {
						case GLONASS:
							//TocGLO and ToeGLO of GLONASS will be left in UTC because orbits will be computed in UTC time
							block.TtoeUTC = block.TtocUTC;
							ttime2gpswsnoroll(&block.TtocUTC,&GPSweek,&SoW);
							//In Rinex v2, GLONASS frame time is in UTC seconds of day!! We need to change to seconds of GPS Week
							DoW=(int)(SoW/86400); //Get Day of Week from Toc
							if(frameTimeGLO<0) {
								frameTimeGLO+=86400;
								DoW--;
								if(DoW<0) {
									DoW=6;
									GPSweek--;
								}
							}
							//Get leap seconds value
							if (products->BRDC->LeapSecondsAvail==1) {
								leapSecond=products->BRDC->AT_LS;
							} else {
								//Use the hardcoded values for leap seconds
								if (products->BRDC->leapSeconds==-1) {
									leapSecond=getLeapSeconds(&block.TtocUTC,products->BRDC->LeapSecondsTimeList,products->BRDC->LeapSecondsNumList);
									if (products->BRDC->LeapSecondsAvailPast==1) {
										//Check if hardocded value is smaller then the one read in previous header.
										//In that case use the last one read
										if (products->BRDC->AT_LSpast>leapSecond) {
											leapSecond=products->BRDC->AT_LSpast;
										}
									}
									products->BRDC->leapSeconds=leapSecond;
								} else {
									leapSecond=products->BRDC->leapSeconds;
								}
							}
							//Transform Toc to GPS time
							block.Ttoc=tdadd(&block.TtoeUTC,leapSecond);
							//Copy Ttoc to Toe
							block.Ttoe = block.Ttoc;
							//Get frametime and convert it to GPS time
							frameTimeGLO+=DoW*86400;//Convert to seconds of week
							block.TframeTime = gpsws2ttime(GPSweek,frameTimeGLO);
							block.TframeTime=tdadd(&block.TframeTime,leapSecond);
							//Transmission time is 15 minutes prior to the time of clock
							block.TtransTime=tdadd(&block.Ttoc,-900.);
							break;
						case GEO:
							block.Ttoe = block.Ttoc;
							ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
							block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
							break;
						case Galileo:
							block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							block.Ttoe = tdadd (&block.Ttoe,7200.); //Add 2 hours to Toe so Toe time is centered in the valid period
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
						default:
							block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
					}
					//Sanity check. Discard messages with 0's in some parameters that should never be 0
					switch(satSystem) {
						case GPS: case Galileo: case QZSS: 
							if (block.deltan==0.||block.M0==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (%s) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),block.deltan==0?"DeltaN=0":"M0=0",numline-7,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						case GLONASS: case GEO:
							if (block.satPos[0]==0. && block.satPos[1]==0. && block.satPos[2]==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (X=Y=0) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),numline-3,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						default:
							break;
					}
					fillBroadcastHealth(&block);
					if (options->brdcHealthSkip[block.GlobalHealth]==0) {
						indSat = products->BRDC->index[satSystem][block.PRN];
						if (indSat == -1) {
							products->BRDC->index[satSystem][block.PRN] = products->BRDC->numsats;
							indSat = products->BRDC->index[satSystem][block.PRN];
							products->BRDC->block = realloc(products->BRDC->block,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->blockPointer = realloc(products->BRDC->blockPointer,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->numblocks = realloc(products->BRDC->numblocks,sizeof(int *)*(products->BRDC->numsats+1));
							products->BRDC->numblocks[indSat] = NULL;
							products->BRDC->numblocks[indSat]= malloc(sizeof(int)*MAX_BRDC_TYPES);
							products->BRDC->block[indSat]= NULL;
							products->BRDC->block[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							products->BRDC->blockPointer[indSat]= NULL;
							products->BRDC->blockPointer[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							for(i=0;i<MAX_BRDC_TYPES;i++) {
								products->BRDC->block[indSat][i] = NULL;
								products->BRDC->blockPointer[indSat][i] = NULL;
								products->BRDC->numblocks[indSat][i] = 0;
							}
							products->BRDC->numsats++;
							//Navigation message contains IOD. Add space also for IOD ordered array
							products->BRDC->blockIOD = realloc(products->BRDC->blockIOD,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->numblocksIOD = realloc(products->BRDC->numblocksIOD,sizeof(int *)*(products->BRDC->numsats+1));
							products->BRDC->numblocksIOD[indSat] = NULL;
							products->BRDC->numblocksIOD[indSat]= malloc(sizeof(int*)*MAX_BRDC_TYPES);
							products->BRDC->blockIOD[indSat]= NULL;
							products->BRDC->blockIOD[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							for(i=0;i<MAX_BRDC_TYPES;i++) {
								products->BRDC->blockIOD[indSat][i] = NULL;
								products->BRDC->blockIOD[indSat][i] = malloc(sizeof(TBRDCblock*)*MAX_IODE_VALUE);
								products->BRDC->numblocksIOD[indSat][i]= malloc(sizeof(int)*MAX_IODE_VALUE);
								for(j=0;j<MAX_IODE_VALUE;j++) {
									products->BRDC->numblocksIOD[indSat][i][j] = 0;
									products->BRDC->blockIOD[indSat][i][j] = NULL;
								}
							}
						}
						//DataTypeRead[indSat][block.BRDCtype]=1;
						indBlock = products->BRDC->numblocks[indSat][block.BRDCtype];
						products->BRDC->block[indSat][block.BRDCtype] = realloc(products->BRDC->block[indSat][block.BRDCtype],sizeof(TBRDCblock)*(indBlock+1));
						memcpy(&products->BRDC->block[indSat][block.BRDCtype][indBlock], &block,sizeof(TBRDCblock));
						products->BRDC->numblocks[indSat][block.BRDCtype]++;
					}
				}
			}// End Nav Rinex v2
			 // Start Nav Rinex v3
			else if ((int)(*rinexNavVersion)==3||(int)(*rinexNavVersion)==4) {
				if (row==0) {
					initBRDCblock(&block);
					getstr(ConstellationType,line,len,0,1);	//GNSS type letter
					satSystem = gnsschar2gnsstype(ConstellationType[0]);
					block.GNSS=satSystem;
					getstr(aux,line,len,1,2);	//PRN
					block.PRN = atoi(aux);
					if (block.PRN<=0 || block.PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN '%s' in line %d in navigation file [%s]",aux,numline,filename);
						printError(messagestr,options);
					}
					//Check if navigation file contains LNAV, CNAV or CNAV2
					if (strncmp(&line[5],"NAV",3)==0) {
						strncpy(aux2,&line[4],4);
						if (strncmp(&line[4],"LNAV",4)==0) {
							msgtype=(int)GPSLNAV; //GPSLNAV or QZSLNAV
						} else if (strncmp(&line[4],"CNAV2",5)==0 ) {
							switch(satSystem) {
								case GPS:
									msgtype=(int)GPSCNAV2;
									break;
								case BDS:
									msgtype=(int)BDSCNAV2;
									break;
								case QZSS:
									msgtype=(int)QZSCNAV2;
									break;
								default:
									msgtype=0; //GEO and IRNSS have CNAV on position 0
									break;
							}
						} else if (strncmp(&line[4],"CNAV1",5)==0 ) {
							switch(satSystem) {
								case GPS:
									msgtype=(int)GPSCNAV; 
									break;
								case QZSS:
									msgtype=(int)QZSCNAV;
									break;
								case BDS:
									msgtype=(int)BDSCNAV1;
									break;
								default:
									msgtype=0; //GEO and IRNSS have CNAV on position 0
									break;
							}
						} else if (strncmp(&line[4],"CNAV",4)==0 ) {
							switch(satSystem) {
								case GPS:
									msgtype=(int)GPSCNAV; 
									break;
								case QZSS:
									msgtype=(int)QZSCNAV;
									break;
								case Galileo:
									msgtype=(int)GalCNAV;
									break;
								case BDS:
									msgtype=(int)BDSCNAV1;
									break;
								default:
									msgtype=0; //GEO and IRNSS have CNAV on position 0
									break;
							}
						} else if (strncmp(&line[4],"FNAV",4)==0) {
							msgtype=0; //0 is GALFNAV
						} else if (strncmp(&line[4],"INAV",4)==0) {
							msgtype=1; //1 is GALINAV
						} else if (aux2[0]=='\0') {
							msgtype=0; //Any other constellation which has not defined message type
						} else {
							sprintf(messagestr,"WARNING: Invalid %s message type '%s' in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),aux2,numline,filename);
							printInfo(messagestr,options);
							row = 0;
							switch(satSystem) {
								case GLONASS: case GEO:
									j=5;
									break;
								default:
									j=8;
									break;
							}
							//Skip lines for the discarded navigation message
							for(i=0;i<j;i++) {
								ret = getL(line,&len,fd);
								if (ret==-1) return 0;
								numline++;
							}
							//CNAV messages have an extra line. Check if we have to discard another extra line	
							ret = getL(line,&len,fd);
							if (ret==-1 && feof_function(fd)==0) return 0;
							else if (feof_function(fd)>0) break; //End of file
							if (line[0]!=' ') {
								//We were already in the last line of the navigation message
								getLback(line,&len,fd);
							} else {
								numline++;
							}
							continue;
						}
						//Data is in next line
						ret = getL(line,&len,fd);
						if (ret==-1) return 0;
						numline++;
					} else {
						switch(satSystem) {
							case GPS:
								msgtype=GPSLNAV;
								break;
							case QZSS:
								msgtype=QZSLNAV;
								break;
							default:
								//To be filled when navigation messages RINEX format is updated
								break;
						}
					}


					invalidDate=0;
					getstr(aux,line,len,4,4);	//Year
					tm.tm_year = atoi(aux);
					if (tm.tm_year<1900) invalidDate=1;
					tm.tm_year -= 1900;
					getstr(aux,line,len,9,2);	//Month
					tm.tm_mon  = atoi(aux);
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,line,len,12,2);	//Day
					tm.tm_mday = atoi(aux);
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,line,len,15,2);	//Hour
					tm.tm_hour = atoi(aux);
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,line,len,18,2);	//Minute
					tm.tm_min  = atoi(aux);
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,line,len,21,2);	//Second
					tm.tm_sec  = atoi(aux);
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
					seconds = atof(aux);
					if (satSystem==GLONASS) {
						block.TtocUTC.MJDN = MJDN(&tm);
						block.TtocUTC.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					} else {
						block.Ttoc.MJDN = MJDN(&tm);
						block.Ttoc.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					}
					if (invalidDate==1) {
						sprintf(messagestr,"Invalid date '%.23s' in line %d in navigation file [%s]",line,numline,filename);
						printError(messagestr,options);
					}
				}
				getstr(a0,line,len,4,19);
				if (a0[13]=='D' || a0[13]=='e') a0[13]='E';
				if (a0[14]=='D' || a0[14]=='e') a0[14]='E';
				if (a0[15]=='D' || a0[15]=='e') a0[15]='E';	// '-' sign can appear or not
				getstr(a1,line,len,23,19);
				if (a1[13]=='D' || a1[13]=='e') a1[13]='E';
				if (a1[14]=='D' || a1[14]=='e') a1[14]='E';
				if (a1[15]=='D' || a1[15]=='e') a1[15]='E';	// '-' sign can appear or not
				getstr(a2,line,len,42,19);
				if (a2[13]=='D' || a2[13]=='e') a2[13]='E';
				if (a2[14]=='D' || a2[14]=='e') a2[14]='E';
				if (a2[15]=='D' || a2[15]=='e') a2[15]='E';	// '-' sign can appear or not
				getstr(a3,line,len,61,19);
				if (a3[13]=='D' || a3[13]=='e') a3[13]='E';
				if (a3[14]=='D' || a3[14]=='e') a3[14]='E';
				if (a3[15]=='D' || a3[15]=='e') a3[15]='E';	// '-' sign can appear or not

				

				switch (satSystem) {
					case GPS: case Galileo: case BDS: case QZSS: case IRNSS:
						switch (row) {
							case 0:
								block.clockbias							= atof(a1);
								block.clockdrift						= atof(a2);
								block.clockdriftrate					= atof(a3);
								break;
							case 1:
								switch (satSystem) {
									case GPS: case QZSS:
										if (msgtype==GPSLNAV) { //LNAV
											block.IODE                  = (int)atof(a0);
										} else { //CNAV
											block.IODE					= -1; //No IODE provided
											block.aDot					= atof(a0);
										}
										break;
									case BDS:
										block.IODE		                = -1; //No IODE provided
										block.AODE						= (int)atof(a0);
										break;
									default:
										block.IODE						= (int)atof(a0);
										break;
								}
								block.crs								= atof(a1);
								block.deltan							= atof(a2);
								block.M0								= atof(a3);
								break;
							case 2:
								block.cuc								= atof(a0);
								block.e									= atof(a1);
								block.cus								= atof(a2);
								block.sqrta								= atof(a3);
								break;
							case 3:
								switch (satSystem) {
									case GPS: case QZSS:
										if (msgtype==GPSLNAV) { //LNAV
											block.toe                   = (int)atof(a0);
										} else { //CNAV
											block.top					= atof(a0); //Time of ephemeris prediction
										}
										break;
									default:
										block.toe						= (int)atof(a0);
										break;
								}
								block.cic								= atof(a1);
								block.OMEGA								= atof(a2);
								block.cis								= atof(a3);
								break;
							case 4:
								block.i0								= atof(a0);
								block.crc								= atof(a1);
								block.omega								= atof(a2);
								block.OMEGADOT							= atof(a3);
								break;
							case 5:
								//GPS, Galileo, QZSS and IRNSS are all in GPS time
								//BDS in BeiDou time
								block.IDOT								= atof(a0);
								switch(satSystem) {
									case GPS: case QZSS:
										if (msgtype==GPSLNAV) { //LNAV
											block.codesOnL2				= (int)atof(a1);
											block.GPSweek				= (int)atof(a2);
											block.L2Pdataflag			= (int)atof(a3);
										} else { //CNAV
											block.nDot					= atof(a1);
											block.URANED0				= (int)atof(a2);
											block.URANED1				= (int)atof(a3);
											//GPSweek not provided. Get it from Toc
											ttime2gpswsnoroll(&block.Ttoc,&block.GPSweek,&block.toe);
										}
										break;
									case Galileo:
										block.dataSources				= (int)atof(a1);
										block.GALweek					= (int)atof(a2);
										block.GPSweek					= block.GALweek;
										break;
									case BDS:
										block.BDSweek					= (int)atof(a2);
										block.GPSweek					= block.BDSweek+1356;
										break;
									case IRNSS:
										block.GPSweek                   = (int)atof(a2);
										break;
									default:
										break;
								}
								break;
							case 6:
								switch(satSystem) {	
									case GPS: case QZSS:
										if (msgtype==GPSLNAV) { //LNAV
											block.SVaccuracy 			= atof(a0);
											block.SVhealth				= (int)atof(a1);
											block.TGD					= atof(a2);
											block.IODC					= (int)atof(a3);
										} else {	//CNAV
											block.URAIndexED			= atof(a0);
											block.SVhealth              = (int)atof(a1);
											block.TGD                   = atof(a2);
											block.URANED2				= (int)atof(a3);
											block.SVaccuracy 			= 0.;
										}
										break;
									case Galileo:
										block.SISASignal				= atof(a0);
										block.SVaccuracy				= block.SISASignal;
										block.SVhealth					= (int)atof(a1);
										block.BGDE5a					= atof(a2);
										block.BGDE5b					= atof(a3);
										break;
									case BDS:
										block.SVaccuracy				= atof(a0);
										block.SVhealth					= (int)atof(a1);
										block.TGD26         		    = atof(a2);
										block.TGD76        		    	= atof(a3);
										block.TGD16        		    	= 0.;
										block.TGD56     		       	= 0.;
										block.ISCB1Cd					= 0.;
										block.ISCB2ad					= 0.;
										break;
									case IRNSS:
										block.IRNURA					= atof(a0);
										block.SVaccuracy				= block.IRNURA;
										block.SVhealth					= (int)atof(a1);
										block.TGD						= atof(a2);
										break;
									default:
										break;
									}
								break;
							case 7:
								//GPS, Galileo, QZSS and IRNSS are all in GPS time
								//BDS in BeiDou time
								switch(satSystem) {
									case GPS:
										if (msgtype==GPSLNAV) { //LNAV
											block.transTime				= atof(a0);
											block.fitInterval			= atof(a1);
											block.ISCL1CA				= 0.;
											block.ISCL1CD				= 0.;
											block.ISCL1CP				= 0.;
											block.ISCL2C				= 0.;
											block.ISCL5I5				= 0.;
											block.ISCL5Q5				= 0.;
											//Check if IODC%256 matches with IODE
											if (block.IODC%256!=block.IODE) {
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid GPS message (IODC%%256 does not match IODE) in line %d in navigation file [%s]. Message discarded",numline-1,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
											} else if (block.IODE<0 || block.IODE>255) {
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid GPS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-6,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
											}
										} else { //CNAV
											block.ISCL1CA				= atof(a0);
											block.ISCL1CD				= 0.;
											block.ISCL1CP				= 0.;
											block.ISCL2C				= atof(a1);
											block.ISCL5I5				= atof(a2);
											block.ISCL5Q5				= atof(a3);
											//Get next line of data
											ret = getL(line,&len,fd);
											if (ret==-1) return 0;
											numline++;
											block.transTime             = atof(a0);
											block.fitInterval           = 0; //Fit interval not provided in CNAV
										}
										if ( block.fitInterval == 0 ) block.fitInterval = 4;
										//Set broadcast message type
										block.BRDCtype = msgtype;
										products->BRDC->AvailBRDCType[GPS][msgtype]=1;
										break;
									case QZSS:
										if (msgtype==QZSLNAV) { //LNAV
											block.transTime				= atof(a0);
											block.fitInterval			= atof(a1);
											block.ISCL1CA				= 0.;
											block.ISCL1CD				= 0.;
											block.ISCL1CP				= 0.;
											block.ISCL2C				= 0.;
											block.ISCL5I5				= 0.;
											block.ISCL5Q5				= 0.;
											//Check if IODC%256 matches with IODE
											if (block.IODC%256!=block.IODE) {
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid QZSS message (IODC%%256 (%d) does not match IODE (%d)) in line %d in navigation file [%s]. Message discarded",block.IODC%256,block.IODE,numline,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
											} else if (block.IODE<0 || block.IODE>255) {
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid QZSS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
											}
										} else { //CNAV
											block.ISCL1CA				= 0.; //L1 C/A is reference signal in QZSS
											block.ISCL1CD				= 0.;
											block.ISCL1CP				= 0.;
											block.ISCL2C				= atof(a1);
											block.ISCL5I5				= atof(a2);
											block.ISCL5Q5				= atof(a3);
											//Get next line of data
											ret = getL(line,&len,fd);
											if (ret==-1) return 0;
											numline++;
											block.transTime             = atof(a0);
											block.fitInterval           = 0; //Fit interval not provided in CNAV

										}
										if ( block.fitInterval == 0 ) block.fitInterval = 2;
										else block.fitInterval = 4;
										//Set broadcast message type
										block.BRDCtype = msgtype;
										products->BRDC->AvailBRDCType[QZSS][msgtype]=1;
										break;
									case Galileo:
										block.transTime					= atof(a0);
										block.fitInterval				= 4;
										block.IODC                    	= -1; //No IODC provided
										//Set broadcast message type
										switch (block.dataSources & GALILEOBRDCMSGMASK) {
											case 258:
												//FNAV
												block.BRDCtype = GalFNAV;
												products->BRDC->AvailBRDCType[Galileo][GalFNAV]=1;
												break;
											case 513:
												//INAV E1-B only
												block.BRDCtype = GalINAVE1;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE1]=1;
												break;
											case 516:
												//INAV E5b only
												block.BRDCtype = GalINAVE5b;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE5b]=1;
												break;
											case 517:
												//INAV E1-B+E5b
												block.BRDCtype = GalINAVE1E5b;
												products->BRDC->AvailBRDCType[Galileo][GalINAVE1E5b]=1;
												break;
											default:
												//Invalid message type
												sprintf(messagestr,"WARNING: Invalid Galileo message type (Data Sources has invalid value %d) in line %d in navigation file [%s]. Message discarded",block.dataSources,numline-2,filename);
												printInfo(messagestr,options);
												row = 0;
												continue;
												break;
										} 
										if (block.IODE<0 || block.IODE>1023) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid Galileo message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-6,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									case BDS:
										block.transTime					= atof(a0);
										block.AODC                    	= (int)atof(a1);
										block.IODC                    	= -1; //No IODC provided
										block.fitInterval				= 4; //Fit interval is not provided
										//Set broadcast message type
										block.BRDCtype = BDSD1;
										products->BRDC->AvailBRDCType[BDS][BDSD1]=1;
										break;
									case IRNSS:
										block.transTime					= atof(a0);
										block.IODC                    	= -1; //No IODC provided
										block.fitInterval				= 4; //Fit interval is not provided
										//Set broadcast message type
										block.BRDCtype = IRNCNAV;
										products->BRDC->AvailBRDCType[IRNSS][IRNCNAV]=1;
										if (block.IODE<0 || block.IODE>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid IRNSS message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODE,numline-5,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									default:
										break;
								}
								if (block.transTime>=0.9999E9) {
									//Invalid transmission time
									switch(satSystem) {
										case Galileo:
											sprintf(messagestr,"WARNING: Invalid %s tranmission time (%f) in line %d in navigation file [%s]. Toe will be used as transmission time",gnsstype2gnssname(block.GNSS),block.transTime,numline,filename);
											block.transTime=block.toe;
											break;
										default:
											sprintf(messagestr,"WARNING: Invalid %s tranmission time (%f) in line %d in navigation file [%s]. Toe-2h will be used as transmission time",gnsstype2gnssname(block.GNSS),block.transTime,numline,filename);
											block.transTime=block.toe-7200.;
											break;
									}
									printInfo(messagestr,options);
								}
								break;
							default:
								break;
						}
						break;
					case GLONASS: case GEO:
						switch(row){
							case 0:
								//Glonass in UTC time. GEO in GPS time
								block.clockbias     		    	    = atof(a1);
								switch(satSystem) {
									case GLONASS:
										block.clockdrift         	 	= atof(a2);
										frameTimeGLO					= atof(a3);
										break;
									case GEO:
										block.clockdrift               	= atof(a2);
										block.transTime					= atof(a3);
										break;
									default:
										break;
								}
								block.clockdriftrate					= 0.0;
								//No IODE and IODC provided. Set it to -1
								block.IODE								= -1;
								block.IODC         			           	= -1; 
								block.SVaccuracy						= 0.;
								break;
							case 1:
								block.satPos[0]                         = atof(a0)*1000;
								block.satVel[0]                         = atof(a1)*1000;
								block.satAcc[0]                         = atof(a2)*1000;
								block.SVhealth                          = (int)atof(a3);
								break;
							case 2:
								block.satPos[1]                         = atof(a0)*1000;
								block.satVel[1]                         = atof(a1)*1000;
								block.satAcc[1]                         = atof(a2)*1000;
								switch(satSystem) {
									case GLONASS:
										block.freqnumber               	= (int)atof(a3);
										break;
									case GEO:
										block.URAGEO					= (int)atof(a3);
										block.SVaccuracy				= block.URAGEO;
										break;
									default:
										break;
								}
								break;
							case 3:
								block.satPos[2]                         = atof(a0)*1000;
								block.satVel[2]                         = atof(a1)*1000;
								block.satAcc[2]                         = atof(a2)*1000;
								switch(satSystem) {
									case GLONASS:
										block.ageofoperation          	= (int)atof(a3);
										block.fitInterval 				= 0.5; //For GLONASS, fit interval is 30 min
										//Set broadcast message type
										block.BRDCtype = GLOFDMA;
										products->BRDC->AvailBRDCType[GLONASS][GLOFDMA]=1;
										break;
									case GEO:
										block.IODNGEO					= (int)atof(a3);
										block.IODE						= block.IODNGEO;
										block.fitInterval 				= 4;
										//Set broadcast message type
										block.BRDCtype = GEOCNAV;
										products->BRDC->AvailBRDCType[GEO][GEOCNAV]=1;
										if (block.IODNGEO<0 || block.IODNGEO>255) {
											//Invalid message type
											sprintf(messagestr,"WARNING: Invalid GEO message (Invalid IODE value %d) in line %d in navigation file [%s]. Message discarded",block.IODNGEO,numline,filename);
											printInfo(messagestr,options);
											row = 0;
											continue;
										}
										break;
									default:
										break;
								}
								break;
							case 4:
								//This line is only for GLONASS since RINEX 3.05
								switch(satSystem) {
									case GLONASS:
										block.GLOfifthLineAvail			= 1;
										block.GLOstatusflags			=(int)atof(a0);
										block.TGD						=atof(a1);
										block.URAI						=atof(a2);
										block.GLOextraHealthFlags		=(int)atof(a3);
										if (block.TGD>=0.9999E9) block.TGD=0.;
										break;
									default:
										break;
								}
							default:
								break;
						}
						break;
					default:
						break;
				}
				row++;
				if (row==8 || (row==4 && satSystem == GEO ) || (satSystem == GLONASS && ( (row==4 && *rinexNavVersion<=3.04) || row==5 ) ) ) {
					row = 0;
					switch(satSystem) {
						case GLONASS:
							//Get leap seconds value
							if (products->BRDC->LeapSecondsAvail==1) {
								leapSecond=products->BRDC->AT_LS;
							} else {
								//Use the hardcoded values for leap seconds
								if (products->BRDC->leapSeconds==-1) {
									leapSecond=getLeapSeconds(&block.TtocUTC,products->BRDC->LeapSecondsTimeList,products->BRDC->LeapSecondsNumList);
									if (products->BRDC->LeapSecondsAvailPast==1) {
										//Check if hardocded value is smaller then the one read in previous header.
										//In that case use the last one read
										if (products->BRDC->AT_LSpast>leapSecond) {
											leapSecond=products->BRDC->AT_LSpast;
										}
									}
									products->BRDC->leapSeconds=leapSecond;
								} else {
									leapSecond=products->BRDC->leapSeconds;
								}
							}
							//TocGLO and ToeGLO of GLONASS will be left in UTC because orbits will be computed in UTC time
							block.TtoeUTC = block.TtocUTC;
							ttime2gpswsnoroll(&block.TtocUTC,&GPSweek,&SoW);
							//Transform Toc to GPS time
							block.Ttoc=tdadd(&block.TtoeUTC,leapSecond);
							//Copy Ttoc to Toe
							block.Ttoe = block.Ttoc;
							//Get frametime and convert it to GPS time
							//In Rinex v3, GLONASS transmission time is in UTC seconds of week!
							block.TframeTime = gpsws2ttime(GPSweek,frameTimeGLO);
							//Transmission time is 15 minutes prior to the time of clock
							block.TtransTime=tdadd(&block.Ttoc,-900.);
							break;
						case GEO:
							block.Ttoe = block.Ttoc;
							ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
							block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
							break;
						case BDS:
							//Convert from BeiDou time to GPS time
							//block.toe (toe in in seconds of BDS week) must be left untouched for computing satellite coordinates correctly
							block.Ttoc = tdadd(&block.Ttoc,DIFFBDS2GPSTIME);
							block.Ttoe = gpsws2ttime(block.GPSweek,block.toe+DIFFBDS2GPSTIME);
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime+DIFFBDS2GPSTIME);
							break;
						case GPS: 
							if (block.BRDCtype==GPSCNAV || block.BRDCtype==GPSCNAV2) {
								//CNAV
								//The top (Time of ephemeris prediction) is the time where the message is estimated, not the actual Toe
								//We need to use as Toe the Toc
								block.Ttoe = block.Ttoc; 
							} else {
								//LNAV
								block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							}
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
						case QZSS:
							if (block.BRDCtype==QZSCNAV || block.BRDCtype==QZSCNAV2) {
								//CNAV
								//The top (Time of ephemeris prediction) is the time where the message is estimated, not the actual Toe
								//We need to use as Toe the Toc
								block.Ttoe = block.Ttoc; 
							} else {
								//LNAV
								block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							}
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
						case Galileo:
							block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							block.Ttoe = tdadd (&block.Ttoe,7200.); //Add 2 hours to Toe so Toe time is centered in the valid period
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
						default:
							//IRNSS
							block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
							block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
							break;
					}
					//Sanity check. Discard messages with 0's in some parameters that should never be 0
					switch(satSystem) {
						case GPS:
							if (block.deltan==0.||block.M0==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (%s) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),block.deltan==0?"DeltaN=0":"M0=0",msgtype==GPSLNAV?numline-7:numline-8,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						case QZSS: 
							//In QZSS some of these values may be 0 due to they can be GEO satellites
							if (block.deltan==0.||block.M0==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (%s) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),block.deltan==0?"DeltaN=0":"M0=0",msgtype==QZSLNAV?numline-7:numline-8,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						case Galileo: case BDS: case IRNSS:
							if (block.deltan==0.||block.M0==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (%s) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),block.deltan==0?"DeltaN=0":"M0=0",numline-7,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						case GLONASS: case GEO:
							if (block.satPos[0]==0. && block.satPos[1]==0. && block.satPos[2]==0.) {
								//Bad package. Skip it
								sprintf(messagestr,"WARNING: Invalid %s message (X=Y=Z=0) in line %d in navigation file [%s]. Message discarded",gnsstype2gnssname(satSystem),numline-3,filename);
								printInfo(messagestr,options);
								continue;
							}
							break;
						default:
							break;
					}
					fillBroadcastHealth(&block);
					if (options->brdcHealthSkip[block.GlobalHealth]==0) {
						indSat = products->BRDC->index[satSystem][block.PRN];
						if (indSat == -1) {
							products->BRDC->index[satSystem][block.PRN] = products->BRDC->numsats;
							indSat = products->BRDC->index[satSystem][block.PRN];
							products->BRDC->block = realloc(products->BRDC->block,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->blockPointer = realloc(products->BRDC->blockPointer,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->numblocks = realloc(products->BRDC->numblocks,sizeof(int *)*(products->BRDC->numsats+1));
							products->BRDC->numblocks[indSat] = NULL;
							products->BRDC->numblocks[indSat]= malloc(sizeof(int)*MAX_BRDC_TYPES);
							products->BRDC->block[indSat]= NULL;
							products->BRDC->block[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							products->BRDC->blockPointer[indSat]= NULL;
							products->BRDC->blockPointer[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							for(i=0;i<MAX_BRDC_TYPES;i++) {
								products->BRDC->block[indSat][i] = NULL;
								products->BRDC->blockPointer[indSat][i] = NULL;
								products->BRDC->numblocks[indSat][i] = 0;
							}
							//Navigation message contains IOD. Add space also for IOD ordered array
							products->BRDC->blockIOD = realloc(products->BRDC->blockIOD,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
							products->BRDC->numblocksIOD = realloc(products->BRDC->numblocksIOD,sizeof(int *)*(products->BRDC->numsats+1));
							products->BRDC->numblocksIOD[indSat] = NULL;
							products->BRDC->numblocksIOD[indSat]= malloc(sizeof(int*)*MAX_BRDC_TYPES);
							products->BRDC->blockIOD[indSat]= NULL;
							products->BRDC->blockIOD[indSat]= malloc(sizeof(TBRDCblock*)*MAX_BRDC_TYPES);
							for(i=0;i<MAX_BRDC_TYPES;i++) {
								products->BRDC->blockIOD[indSat][i] = NULL;
								products->BRDC->blockIOD[indSat][i] = malloc(sizeof(TBRDCblock*)*MAX_IODE_VALUE);
								products->BRDC->numblocksIOD[indSat][i]= malloc(sizeof(int)*MAX_IODE_VALUE);
								for(j=0;j<MAX_IODE_VALUE;j++) {
									products->BRDC->numblocksIOD[indSat][i][j] = 0;
									products->BRDC->blockIOD[indSat][i][j] = NULL;
								}
							}
							products->BRDC->numsats++;
						}
						//DataTypeRead[indSat][block.BRDCtype]=1;
						indBlock = products->BRDC->numblocks[indSat][block.BRDCtype];
						products->BRDC->block[indSat][block.BRDCtype] = realloc(products->BRDC->block[indSat][block.BRDCtype],sizeof(TBRDCblock)*(indBlock+1));
						memcpy(&products->BRDC->block[indSat][block.BRDCtype][indBlock], &block,sizeof(TBRDCblock));
						products->BRDC->numblocks[indSat][block.BRDCtype]++;
					}
				}
			}// End Nav Rinex v3
		}
	} while(getL(line,&len,fd)!=-1);

	//Build a list of pointer to the navigation messages by IOD, so when searching a message by
	//IOD, the search is almost instantaneous (as even during two or three consecutive days a
	//satellite does not repeat an IOD).
	//This list of pointer has to be done after reading all navigation messages, as pointers
	//to the navigation messages change every time a new navigation message is read for a 
	//given satellite (due to realloc function call)
	for(i=0;i<products->BRDC->numsats;i++) {
		for(j=0;j<MAX_BRDC_TYPES;j++) {
			//Free data from list (for the case multiple navigation files are read,
			//the list has to be rebuilt each time a file is read
			if (products->BRDC->blockPointer[i][j]!=NULL) {
				free(products->BRDC->blockPointer[i][j]);
				products->BRDC->blockPointer[i][j]=NULL;
			}
			for(l=0;l<MAX_IODE_VALUE;l++) {
				if (products->BRDC->blockIOD[i][j][l]!=NULL) {
					free(products->BRDC->blockIOD[i][j][l]);
					products->BRDC->blockIOD[i][j][l]=NULL;
					products->BRDC->numblocksIOD[i][j][l]=0;
				}
			}
			products->BRDC->blockPointer[i][j]=malloc(sizeof(TBRDCblock*)*products->BRDC->numblocks[i][j]);
			for(l=0;l<products->BRDC->numblocks[i][j];l++) {
				//Build blockPointer list of unordered messages, so blockPointer is a pointer
				//list as blockIOD is (but with different ordering)
				products->BRDC->blockPointer[i][j][l]=&products->BRDC->block[i][j][l];
				//Build blockIOD list
				IODE=products->BRDC->block[i][j][l].IODE;
				if (IODE!=-1) {
					indBlockIOD = products->BRDC->numblocksIOD[i][j][IODE];
					products->BRDC->blockIOD[i][j][IODE]=realloc(products->BRDC->blockIOD[i][j][IODE],sizeof(TBRDCblock*)*(indBlockIOD+1));
					products->BRDC->blockIOD[i][j][IODE][indBlockIOD]=&products->BRDC->block[i][j][l];
					products->BRDC->numblocksIOD[i][j][IODE]++;
				} else if (products->BRDC->block[i][j][l].GNSS==GLONASS) {
					//For GLONASS, compute an IODE based on the formula
					// modulo((Tpackage-900/1800.),1024)
					//The substraction of 900 seconds is due to time given corresponds to central time of validity not the first epoch of validity
					//The 1800 corresponds to 30 minutes, which is the total validity time of one package
					IODE=((int)((tsec(&products->BRDC->block[i][j][l].TtocUTC)-900)/1800.))%MAX_IODE_VALUE;
					products->BRDC->block[i][j][l].IODEGLONASS=IODE;
					indBlockIOD = products->BRDC->numblocksIOD[i][j][IODE];
					products->BRDC->blockIOD[i][j][IODE]=realloc(products->BRDC->blockIOD[i][j][IODE],sizeof(TBRDCblock*)*(indBlockIOD+1));
					products->BRDC->blockIOD[i][j][IODE][indBlockIOD]=&products->BRDC->block[i][j][l];
					products->BRDC->numblocksIOD[i][j][IODE]++;
				}
			}
		}
	}

	//Sort navigation messages by transmission time (currently disabled until
	//optimization in selectBRDCBlock taking advantange of sorted navigation
	//message is implemented)
	/*for(i=0;i<products->BRDC->numsats;i++) {
		for(j=0;j<MAX_BRDC_TYPES;j++) {
			if (DataTypeRead[i][j]==1) {
				qsort(products->BRDC->block[i][j],products->BRDC->numblocks[i][j],sizeof(TBRDCblock),qsort_compare_transtime);
			}
		}
	}*/

	return (returnValue); // properly read 
}

/*****************************************************************************
 * Name        : readRinexNavLastEpoch
 * Description : Find last epoch of RINEX navigation file. It will read the last
 *                day of data, as it can't assume that data is ordered 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TTime *lastEpoch                O  N/A  Last Epoch in SP3 file
 * char *filename                  I  N/A  Navigation filename
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Last Epoch read
 *                                         0 => Error
 *****************************************************************************/
int readRinexNavLastEpoch (FILE *fd, TTime *lastEpoch, char *filename, TOptions  *options) {

    struct stat             filestat;   //This is to get the file size
    off_t                   filesize;
    long                    CurrentPos;
    int                     len = 0;
    char                    line[MAX_INPUT_LINE];
	double					rinexNavVersion; 						
	TGNSSproducts 			products;

	initGNSSproducts(&products);


    CurrentPos = ftell(fd);
    //We need to go to the end of the file.
    //NOTE that fseek(fd, 0L, SEEK_END); does not work as we have opened the file in binary mode!!!
    fstat(fileno(fd), &filestat);
    filesize = filestat.st_size;
    fseek(fd,filesize,SEEK_SET);

    while(1) {
        if (getLback(line,&len,fd)==-1) {
			fseek(fd,CurrentPos,SEEK_SET);
			return 0;
		}
		if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
			if (getLback(line,&len,fd)==-1) {
				fseek(fd,CurrentPos,SEEK_SET);
				return 0;
			}
			break;
		}
	}
	if (readRinexNav(fd, filename, &products, &rinexNavVersion,NEWDAYNAV,options)<1) {
		//Free memory
		freeBRDCproducts(FREEALLNAV,&products);
		free(products.BRDC);
		fseek(fd,CurrentPos,SEEK_SET);
		return 0;
	}
	fseek(fd,CurrentPos,SEEK_SET);
	*lastEpoch=getProductsLastEpochBRDC(&products);
	//Free memory
	freeBRDCproducts(FREEALLNAV,&products);
	free(products.BRDC);
	return 1;
}

/*****************************************************************************
 * Name        : readSP3
 * Description : Read an SP3 precise products file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TGNSSproducts  *products        O  N/A  Structure to save the data
 * int  readOrbits                 I  N/A  Flag to read the position and 
 *                                         velocities (0 or 1)
 * int  readClocks                 I  N/A  Flag to read the clocks (0 or 1)
 * int  readingRefFile             I  N/A  Flag to indicate if we are reading a reference position file (0 or 1)
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error
 *                                        -2 => Number of entries in header is incorrect (deprecated)
 *                                        -3 => If reading reference position file, there is more than
 *                                                one satellite available
 *                                        -4 => No epoch data in SP3
 *****************************************************************************/
int readSP3 (FILE *fd, TGNSSproducts *products, int readOrbits, int readClocks, int readingRefFile, TOptions *options) {
	char 			line[MAX_INPUT_LINE];
	char    		aux[100];
	int 			len = 0;
	int				properlyRead = 0;
	int				error = 0;
	int				readingHeader = 1;
	int				i,k;
	int				PRN;
	int				HeaderNumRecords;
	int				FirstHeaderfline=1;
	int				invalidDate=0;
	TTime			t,lastT;
	int				ind;
	struct tm		tm;
	double			seconds;
	double			interval;
	int				readedLine = 0;
	int				readedSatellites;
	//char			versionId;
	enum GNSSystem	GNSS;
	int				usedRecords;
	int				CurrentInd;
	int				auxN;
	int				blankOffset=0;
	double			BaseSigmaOrbit;
	double			BaseSigmaClock;

	if (!readOrbits && !readClocks) return 0;

	products->type = SP3;
	products->SP3 = malloc(sizeof(TSP3products));
	initSP3products(products->SP3);
	lastT.MJDN = 0;
	lastT.SoD = 0;
	//This characters are initialized to NULL to avoid comparing strncmp against unintialized values
	line[70]=line[71]='\0';
	line[74]=line[75]='\0';
	line[78]=line[79]='\0';

	while(getL(line,&len,fd)!=-1) {
		readedLine++;
		if (readingHeader) {
			if (readedLine==1) {
				// #bP2008  8 27 00 00 00.00000000      96   d   ITR91 FIT  JPL
				if (line[0]!='#') error = 1;
				if (line[2]=='V') products->SP3->orbits.velocityAvailable = 1;
				else products->SP3->orbits.velocityAvailable = 0;
				getstr(aux,line,len,32,7);
				HeaderNumRecords=atoi(aux);
				if (readOrbits) products->SP3->orbits.numRecords = atoi(aux);
				if (readClocks) products->SP3->clocks.numRecords = atoi(aux);
			} else if (readedLine==2) {
				// ## 1494 259200.00000000   900.00000000 54705 0.0000000000000
				getstr(aux,line,len,39,5);
				if (readOrbits) products->SP3->orbits.startTime.MJDN = atoi(aux);
				if (readClocks) products->SP3->clocks.startTime.MJDN = atoi(aux);
				getstr(aux,line,len,45,15);
				if (readOrbits) {
					products->SP3->orbits.startTime.SoD = atof(aux)*86400.0;
					if (products->SP3->orbits.startTime.MJDN<FIRSTMJDNGPS || products->SP3->orbits.startTime.SoD<0 || products->SP3->orbits.startTime.SoD>=86400) {
						sprintf(messagestr,"Invalid start date '%s' in header line number 2 of SP3 file",line);
						printError(messagestr,options);
					}
				}
				if (readClocks) {
					products->SP3->clocks.startTime.SoD = atof(aux)*86400.0;
					if (products->SP3->clocks.startTime.MJDN<FIRSTMJDNGPS || products->SP3->clocks.startTime.SoD<0 || products->SP3->clocks.startTime.SoD>=86400) {
						sprintf(messagestr,"Invalid start date '%s' in header line number 2 of SP3 file",line);
						printError(messagestr,options);
					}
				}
			} else if (strncmp(line,"+ ",2)==0) {
				// +   31   G02G03G04G05G06G07G08G09G10G11G12G13G14G15G16G17G18
				if (readedLine==3) {
					//The blankOffset variable is for a workaround for a bug when generating the SP3 file when it has 
					//more than 100 satellites, where the first line of satellites get moved one character to the
					//right due to the number of satellites having three characters and not being properly aligned
					if (line[9]==' ' && (line[10]>=65 && line[10]<=90)) { //65 is ASCII 'A' and 90 is ASCII 'Z'
						blankOffset=1;
					} else {
						blankOffset=0;
					}
					getstr(aux,line,len,3+blankOffset,3);
					auxN = atoi(aux);
					if(auxN<=0) {
						sprintf(messagestr,"Invalid number of satellites '%s' in header line number %d of SP3 file",aux,readedLine);
						printError(messagestr,options);
					}
					if(readingRefFile==1) {
						//If we are reading reference file only one satellite must be in the SP3 file
						if (auxN>1) {
							return -3;
						}
					}
					if (readOrbits) products->SP3->orbits.numSatellites = products->SP3->orbits.numSatellitesRead = auxN;
					if (readClocks) products->SP3->clocks.numSatellites = products->SP3->clocks.numSatellitesRead = auxN;
					// Reserve memory for satellites
					if (readOrbits) {
						products->SP3->orbits.block = malloc(sizeof(TSP3orbitblock*)*products->SP3->orbits.numSatellites);
						for (i=0;i<products->SP3->orbits.numSatellites;i++) {
							products->SP3->orbits.block[i]=NULL;
						}
						products->SP3->orbits.accuracy = malloc(sizeof(double)*products->SP3->orbits.numSatellites);
					}
					if (readClocks) {
						products->SP3->clocks.block = malloc(sizeof(TSP3clockblock*)*products->SP3->clocks.numSatellites);
						for (i=0;i<products->SP3->clocks.numSatellites;i++) {
							products->SP3->clocks.block[i]=NULL;
						}
					}
					readedSatellites = 0;
				} else {
					blankOffset=0;
				}
				for (i=0;i<17 && readedSatellites<auxN;i++,readedSatellites++) { //auxN = products->SP3->XXXX.numSatellites;
					GNSS = gnsschar2gnsstype(line[9+blankOffset+3*i]);
					getstr(aux,line,len,10+blankOffset+3*i,2);
					PRN=atoi(aux);
					if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in header line number %d of SP3 file",aux,readedLine);
						printError(messagestr,options);
					}
					if (readOrbits) {
						if (products->SP3->orbits.index[GNSS][PRN] != -1 ) {
							sprintf(messagestr,"Satellite %c%02d is repeated twice in header line number %d of SP3 file",gnsstype2char(GNSS),PRN,readedLine);
							printError(messagestr,options);
						}
						products->SP3->orbits.index[GNSS][PRN] = readedSatellites;
					}
					if (readClocks) {
						if (products->SP3->clocks.index[GNSS][PRN] != -1 ) {
							sprintf(messagestr,"Satellite %c%02d is repeated twice in header line number %d of SP3 file",gnsstype2char(GNSS),PRN,readedLine);
							printError(messagestr,options);
						}
						products->SP3->clocks.index[GNSS][PRN] = readedSatellites;
					}
				}
			} else if (strncmp(line,"++",2)==0) {
				if (readedSatellites==auxN) readedSatellites=0; //This is the first line with "++" read
				for (i=0;i<17 && readedSatellites<auxN;i++,readedSatellites++) { //auxN = products->SP3->XXXX.numSatellites;
					// Accuracy is 2^val mm.
					getstr(aux,line,len,10+3*i,2);
					if (readOrbits) products->SP3->orbits.accuracy[readedSatellites] = pow(2,atoi(aux))*1e-3;
				}
			} else if (strncmp(line,"%f",2)==0) {
				if (FirstHeaderfline==1) {
					FirstHeaderfline=0;
					if (readOrbits) {
						getstr(aux,line,len,3,10);
						BaseSigmaOrbit=atof(aux);
						if (BaseSigmaOrbit==0.) {
							BaseSigmaOrbit=2.;
						}
					}
					if (readClocks) {
						getstr(aux,line,len,14,10);
						BaseSigmaClock=atof(aux);
						if (BaseSigmaClock==0.) {
							BaseSigmaClock=2.;
						}
					}
				}
			} else if (strncmp(line,"/*",2)==0) {
				// /* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
				// ++         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
				do {
					if (getL(line,&len,fd)==-1) {
						error=1;
						return 0;
					}
				} while(strncmp(line,"/*",2)==0);
				getLback(line,&len,fd);
				properlyRead = 1;
				readingHeader = 0;
				usedRecords = 0;
			}
		} else { // !readingHeader
			if (line[0]=='*') { // Epoch starting
				// *  2008 08 27 00 00 00.00000000
				invalidDate=0;
				getstr(aux,line,len,3,4);
				tm.tm_year = atoi(aux);
				if (tm.tm_year<1900) invalidDate=1;
				tm.tm_year -= 1900;
				getstr(aux,line,len,8,2);
				tm.tm_mon  = atoi(aux);
				if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
				tm.tm_mon  -= 1;
				getstr(aux,line,len,11,2);
				tm.tm_mday = atoi(aux);
				if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
				getstr(aux,line,len,14,2);
				tm.tm_hour = atoi(aux);
				if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
				getstr(aux,line,len,17,2);
				tm.tm_min  = atoi(aux);
				if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
				getstr(aux,line,len,20,11);
				tm.tm_sec  = atoi(aux);
				if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
				seconds = atof(aux);
				t.MJDN = MJDN(&tm);
				t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				if (t.MJDN<FIRSTMJDNGPS || t.SoD<.0 || invalidDate==1 ) {
					sprintf(messagestr,"Invalid epoch '%.26s' in precise SP3 file",&line[3]);
					printError(messagestr,options);
				}
				if (lastT.MJDN!=0) { //It is not the first epoch
					//Compute interval (do not trust header)
					if (products->SP3->orbits.interval == 0.) { // If interval is still not known
						interval = tdiff(&t,&lastT);
						if (interval>=1.) {
							//Take out decimals if interval is greater than 1
							if (readOrbits) products->SP3->orbits.interval = (double)((int)(interval));
							if (readClocks) products->SP3->clocks.interval = (double)((int)(interval));
						} else {
							if (readOrbits) products->SP3->orbits.interval = interval;
							if (readClocks) products->SP3->clocks.interval = interval;
						}
	
					}	
					//Check that new epoch is not before the last epoch read
					if (tdiff(&t,&lastT)<-DIFFEQTHRESHOLD) {
						t2tmnolocal(&lastT,&tm,&seconds);
						sprintf(messagestr,"Epoch '%.26s' is previous to the last epoch read '%4d %02d %02d %02d %02d %9.6f' in precise orbit file",&line[3],tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
						printError(messagestr,options);
					}
				}

				memcpy(&lastT,&t,sizeof(TTime));
				for (i=0;i<products->SP3->orbits.numSatellites;i++) {
					if(readOrbits) {
						products->SP3->orbits.block[i] = realloc(products->SP3->orbits.block[i],sizeof(TSP3orbitblock)*(usedRecords+1));
						initSP3orbitblock(&products->SP3->orbits.block[i][usedRecords]);
						memcpy(&products->SP3->orbits.block[i][usedRecords].t,&t,sizeof(TTime));
					}
					if (readClocks) {
						products->SP3->clocks.block[i] = realloc(products->SP3->clocks.block[i],sizeof(TSP3clockblock)*(usedRecords+1));
						initSP3clockblock(&products->SP3->clocks.block[i][usedRecords]);
						memcpy(&products->SP3->clocks.block[i][usedRecords].t,&t,sizeof(TTime));
					}
				}
				usedRecords++;
				if (usedRecords==1) {
					//Copy first epoch read as start time, do not trust header
					if(readOrbits) memcpy(&products->SP3->orbits.startTime,&t,sizeof(TTime));
					if(readClocks) memcpy(&products->SP3->clocks.startTime,&t,sizeof(TTime));
				}
			} else if (line[0]=='P') { // Position record
				CurrentInd=usedRecords-1;
				if(readingRefFile==1) {
					//Reference position is saved in position [0][0]
					GNSS=0;
					PRN=0;
					ind=0;
				} else {
					GNSS = gnsschar2gnsstype(line[1]);
					getstr(aux,line,len,2,2);
					PRN = atoi(aux);
					if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in SP3 file",aux);
						printError(messagestr,options);
					}
					if (readOrbits) ind = products->SP3->orbits.index[GNSS][PRN];
					else ind = products->SP3->clocks.index[GNSS][PRN];
					if (ind==-1) {
						sprintf(messagestr,"Satellite '%c%02d' data read, but it is not in the header of SP3 file",line[1],PRN);
						printError(messagestr,options);
					}
				}
				if (readOrbits) {
					if (CurrentInd==0) {
						//Check if sigmas per epoch are provided
						getstr(aux,line,len,46,14);
						products->SP3->orbits.hasSigmaPerEpoch=0;
						if (atof(aux)!=INVALID_CLOCK) {
							if (strncmp(&line[61],"  ",2)!=0) {
								products->SP3->orbits.hasSigmaPerEpoch=1;
							}
						}
					}
					getstr(aux,line,len,4,14);
					products->SP3->orbits.block[ind][CurrentInd].x[0] = atof(aux)*1e3;
					getstr(aux,line,len,18,14);
					products->SP3->orbits.block[ind][CurrentInd].x[1] = atof(aux)*1e3;
					getstr(aux,line,len,32,14);
					products->SP3->orbits.block[ind][CurrentInd].x[2] = atof(aux)*1e3;
					memcpy(&products->SP3->orbits.block[ind][usedRecords-1].t,&t,sizeof(TTime));

					getstr(aux,line,len,46,14);
					if (products->SP3->orbits.hasSigmaPerEpoch==1) {
						getstr(aux,line,len,46,14);
						if (atof(aux)!=INVALID_CLOCK) {
							getstr(aux,line,len,61,2);
							products->SP3->orbits.block[ind][CurrentInd].xsigma[0] = pow(BaseSigmaOrbit,atof(aux))*1e-3;
							getstr(aux,line,len,64,2);
							products->SP3->orbits.block[ind][CurrentInd].xsigma[1] = pow(BaseSigmaOrbit,atof(aux))*1e-3;
							getstr(aux,line,len,67,2);
							products->SP3->orbits.block[ind][CurrentInd].xsigma[2] = pow(BaseSigmaOrbit,atof(aux))*1e-3;
						} else {
							//When an invalid clock is given, also sigmas are not provided. Use the default ones
							products->SP3->orbits.block[ind][CurrentInd].xsigma[0]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
							products->SP3->orbits.block[ind][CurrentInd].xsigma[1]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
							products->SP3->orbits.block[ind][CurrentInd].xsigma[2]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
						}
					} else {
						//No sigmas per epochs. use the default ones
						products->SP3->orbits.block[ind][CurrentInd].xsigma[0]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
						products->SP3->orbits.block[ind][CurrentInd].xsigma[1]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
						products->SP3->orbits.block[ind][CurrentInd].xsigma[2]=pow(BaseSigmaOrbit,products->SP3->orbits.accuracy[ind])*1e-3;
					}

					//Read orbit flags
					if(len>=80 && strncmp(&line[78],"  ",2)!=0) {
						strncpy(products->SP3->orbits.block[ind][CurrentInd].orbitflags,&line[78],2);
						products->SP3->orbits.block[ind][CurrentInd].orbitflags[2]='\0';
					} else {
						products->SP3->orbits.block[ind][CurrentInd].orbitflags[0]='\0';
					}
				}
				if (readClocks) {
					getstr(aux,line,len,46,14);
					if (CurrentInd==0) {
						//Check if sigmas per epoch are provided
						products->SP3->clocks.hasSigmaPerEpoch=0;
						if (atof(aux)!=INVALID_CLOCK) {
							if (strncmp(&line[70],"  ",2)!=0) {
								products->SP3->clocks.hasSigmaPerEpoch=1;
							}
						}
					}
					if (atof(aux)==INVALID_CLOCK) {
						products->SP3->clocks.block[ind][CurrentInd].clock = INVALID_CLOCK;
						//clocksigma is initialized by default to 0
					} else {
						products->SP3->clocks.block[ind][CurrentInd].clock = atof(aux)*(c0/1e6);
						if (products->SP3->clocks.hasSigmaPerEpoch==1) {
							getstr(aux,line,len,70,3);
							products->SP3->clocks.block[ind][CurrentInd].clocksigma=pow(BaseSigmaClock,atof(aux))*1e-12*c0;
						}
					}
					memcpy(&products->SP3->clocks.block[ind][CurrentInd].t,&t,sizeof(TTime));

					//Read clock flags
					if(len>=76 && strncmp(&line[74],"  ",2)!=0) {
						strncpy(products->SP3->clocks.block[ind][CurrentInd].clockflags,&line[74],2);
						products->SP3->clocks.block[ind][CurrentInd].clockflags[2]='\0';
					} else {
						products->SP3->clocks.block[ind][CurrentInd].clockflags[0]='\0';
					}
				}
				
			} else if (line[0]=='V') { // Velocity record
				CurrentInd=usedRecords-1;
				if(readingRefFile==1) {
					//Reference position is saved in position [0][0]
					GNSS=0;
					PRN=0;
					ind=0;
				} else {					
					GNSS = gnsschar2gnsstype(line[1]);
					getstr(aux,line,len,2,2);
					PRN = atoi(aux);
					if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in SP3 file",aux);
						printError(messagestr,options);
					}
					if (readOrbits) ind = products->SP3->orbits.index[GNSS][PRN];
					else ind = products->SP3->clocks.index[GNSS][PRN];
					if (ind==-1) {
						sprintf(messagestr,"Satellite '%c%02d' data read, but it is not in the header of SP3 file",line[1],PRN);
						printError(messagestr,options);
					}

				}
				if (readOrbits) {
					getstr(aux,line,len,4,14);
					products->SP3->orbits.block[ind][CurrentInd].v[0] = atof(aux)*1e-1;
					getstr(aux,line,len,18,14);
					products->SP3->orbits.block[ind][CurrentInd].v[1] = atof(aux)*1e-1;
					getstr(aux,line,len,32,14);
					products->SP3->orbits.block[ind][CurrentInd].v[2] = atof(aux)*1e-1;
					memcpy(&products->SP3->orbits.block[ind][CurrentInd].t,&t,sizeof(TTime));
				}
				if (readClocks) {
					getstr(aux,line,len,46,14);
					products->SP3->clocks.block[ind][CurrentInd].clockrate = atof(aux)*(c0/1e7);
					memcpy(&products->SP3->clocks.block[ind][CurrentInd].t,&t,sizeof(TTime));
				}
			} else if (strncmp(line,"EOF",3)==0) { // End of File
				if (usedRecords==0) return -4;
				if (readOrbits) {
					products->SP3->orbits.numRecords = usedRecords;
					memcpy(&products->SP3->orbits.endTime,&t,sizeof(TTime));
				}
				if (readClocks) {
					products->SP3->clocks.numRecords = usedRecords;
					memcpy(&products->SP3->clocks.endTime,&t,sizeof(TTime));
				}
				if(usedRecords!=HeaderNumRecords) {
					//Header had incorrect number of entries
					sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d) in SP3 file",HeaderNumRecords,usedRecords);
					printInfo(messagestr,options);
				}
				for (k=0;k<5;k++) {
					if (getL(line,&len,fd)==-1) {
						return 1;
					}
				}
				for (k=0;k<5;k++) getLback(line,&len,fd);
				return 2;
			} else if (line[0]=='#') {
				printInfo("WARNING SP3 file has no 'EOF' line at the end. SP3 file may be incomplete",options);
				if (usedRecords==0) return -4;
				if(usedRecords!=HeaderNumRecords) {
					//Header had incorrect number of entries
					sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d) in SP3 file",HeaderNumRecords,usedRecords);
					printInfo(messagestr,options);
				}
				//Concatenated file
				if (readOrbits) {
					products->SP3->orbits.numRecords = usedRecords;
					memcpy(&products->SP3->orbits.endTime,&t,sizeof(TTime));
				}
				if (readClocks) {
					products->SP3->clocks.numRecords = usedRecords;
					memcpy(&products->SP3->clocks.endTime,&t,sizeof(TTime));
				}
				getLback(line,&len,fd);
				return 2;
			} else { // Record unidentified
				error = 1;
			}
		} //End if (readingHeader) 
	}
	//End of file but no EOF found
	printInfo("WARNING SP3 file has no 'EOF' line at the end. SP3 file may be incomplete",options);
	if(usedRecords!=HeaderNumRecords) {
		//Header had incorrect number of entries
		sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d) in SP3 file",HeaderNumRecords,usedRecords);
		printInfo(messagestr,options);
	}
	if (readOrbits) {
		products->SP3->orbits.numRecords = usedRecords;
		memcpy(&products->SP3->orbits.endTime,&t,sizeof(TTime));
	}
	if (readClocks) {
		products->SP3->clocks.numRecords = usedRecords;
		memcpy(&products->SP3->clocks.endTime,&t,sizeof(TTime));
	}

	if (usedRecords==0) return -4;
	
	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readSP3LastEpoch
 * Description : Read last epoch from SP3 file. This function is called when the
                  SP3 files is concatenated more than 3 days
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TTime *lastEpoch                O  N/A  Last Epoch in SP3 file
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Last Epoch read
 *                                         0 => Error
 *****************************************************************************/
int readSP3LastEpoch (FILE *fd, TTime *lastEpoch) {

	struct stat 			filestat;	//This is to get the file size
	off_t					filesize;
	struct tm   			tm;
	long					CurrentPos;
	int						len = 0;
	double					seconds;
	char		    		aux[100];
	char					line[MAX_INPUT_LINE];
	int						invalidDate=0;


	CurrentPos = ftell(fd);
	//We need to go to the end of the file.
	//NOTE that fseek(fd, 0L, SEEK_END); does not work as we have opened the file in binary mode!!!
	fstat(fileno(fd), &filestat);
	filesize = filestat.st_size;
	fseek(fd,filesize,SEEK_SET);

	while(1) {
		if (getLback(line,&len,fd)==-1) {
			fseek(fd,CurrentPos,SEEK_SET);
			return 0;
		}
		if (line[0]=='*') { // Epoch starting
			// *  2008 08 27 00 00 00.00000000
			invalidDate=0;
			getstr(aux,line,len,3,4);
			tm.tm_year = atoi(aux);
			if (tm.tm_year<1900) invalidDate=1;
			tm.tm_year -= 1900;
			getstr(aux,line,len,8,2);
			tm.tm_mon  = atoi(aux);
			if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
			tm.tm_mon  -= 1;
			getstr(aux,line,len,11,2);
			tm.tm_mday = atoi(aux);
			if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
			getstr(aux,line,len,14,2);
			tm.tm_hour = atoi(aux);
			if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
			getstr(aux,line,len,17,2);
			tm.tm_min  = atoi(aux);
			if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
			getstr(aux,line,len,20,11);
			tm.tm_sec  = atoi(aux);
			if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
			seconds = atof(aux);
			if (invalidDate==0) {
				lastEpoch->MJDN = MJDN(&tm);
				lastEpoch->SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				fseek(fd,CurrentPos,SEEK_SET);
				return 1;
			}
		}
	}
	return 0;
}

/*****************************************************************************
 * Name        : readRinexClocks
 * Description : Read a RINEX Clocks file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TGNSSproducts  *products        O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error
 *****************************************************************************/
int readRinexClocks (FILE *fd, TGNSSproducts *products, TOptions *options) {
	char 			line[MAX_INPUT_LINE];
	char	 	   	aux[100];
	char	 	   	aux2[100];
	char	 	   	aux3[100];
	int 			len = 0;
	//double			rinexVersion;
	int				properlyRead = 0;
	int				error = 0;
	int				readingHeader = 1;
	enum GNSSystem	GNSS;
	int				PRN;
	struct tm		tm;
	int				i,j;
	int				ind;
	double			seconds;
	double			interval;
	TTime			t, lastT;
	int				readedSatellites;
	int 			found_prn_list = 0;
	int				invalidDate=0;

	//The following variables are for the field start position. 
	//Default values are for version <3.04. If version >=3.04, they will be updated accordingly
	int				headerLabelStartPos=60;
	int				numSatPRNList=15;
	int				initPosYear=8;
	int				initPosMonth=13;
	int				initPosDay=16;
	int				initPosHour=19;
	int				initPosMin=22;
	int				initPosSec=25;
	int				initPosClkCorr=37;
	//int				initPosClkSigma=60;
	int				initPosClkFlags=81;
	int				minLenFlags=83;
	
	lastT.MJDN = 0;
	lastT.SoD = 0;
	
	while(getL(line,&len,fd)!=-1) {
		if (!readingHeader) {
			if (strncmp(&line[headerLabelStartPos],"RINEX VERSION / TYPE",20)==0) {
				//Save last epoch
				memcpy(&products->SP3->clocks.endTime,&t,sizeof(TTime));
				getLback(line,&len,fd);

				// If the time stamp of a satellite block of the last epoch has not the right value, 
				// then there has been no data for that satellite, so the satellite block time stamp has to be fixed 
				for (i=0;i<products->SP3->clocks.numSatellites;i++) {
					if (tdiff(&t,&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t)!=0) {
						memcpy(&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t,&t,sizeof(TTime));
					}
				}
				return 2;
			}
		}
		if (readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,len,0,9);
				//rinexVersion = atof(aux); //Commented to avoid not used variable warning
			} else if (strncmp(&line[65],"RINEX VERSION / TYPE",20)==0) {
				//This second header check is because from version 3.04 header names are moved 5 characters to the right
				getstr(aux,line,len,0,9);
				//rinexVersion = atof(aux); //Commented to avoid not used variable warning
				//Set fields position for version >=3.04
				headerLabelStartPos=65;
				numSatPRNList=16;
				initPosYear=13;
				initPosMonth=18;
				initPosDay=21;
				initPosHour=24;
				initPosMin=27;
				initPosSec=30;
				initPosClkCorr=42;
				//initPosClkSigma=65;
				initPosClkFlags=86;
				minLenFlags=88;
			} else if (strncmp(&line[headerLabelStartPos],"# OF SOLN SATS",14)==0) {
				getstr(aux,line,len,0,6);
				products->SP3->clocks.numSatellites = products->SP3->clocks.numSatellitesRead = atoi(aux);
				if (products->SP3->clocks.numSatellites<=0) {
					sprintf(messagestr,"Invalid number of satellites '%s' in precise clocks file",aux);
					printError(messagestr,options);
				}
				// Reserve memory for satellites
				products->SP3->clocks.block = malloc(sizeof(TSP3clockblock*)*products->SP3->clocks.numSatellites);
				// Reserve initial memory for blocks
				for (i=0;i<products->SP3->clocks.numSatellites;i++) {
					products->SP3->clocks.block[i] = NULL;
				}
				readedSatellites = 0;
			} else if (strncmp(&line[headerLabelStartPos],"PRN LIST",8)==0) {
				found_prn_list = 1;
				for (i=0;i<numSatPRNList && readedSatellites<products->SP3->clocks.numSatellites;i++,readedSatellites++) {
					GNSS = gnsschar2gnsstype(line[4*i]);
					getstr(aux,line,len,1+4*i,2);
					PRN=atoi(aux);

					if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
						sprintf(messagestr,"Invalid PRN number '%s' in precise clocks file",aux);
						printError(messagestr,options);
					}
					if (products->SP3->clocks.index[GNSS][PRN] != -1 ) {
						sprintf(messagestr,"Satellite %c%02d is repeated twice in header of CLK file",gnsstype2char(GNSS),PRN);
						printError(messagestr,options);
					}
					products->SP3->clocks.index[GNSS][PRN] = readedSatellites;
				}
			} else if (strncmp(&line[headerLabelStartPos],"END OF HEADER",13)==0) {
				readingHeader = 0;
				properlyRead = 1;
				products->SP3->clocks.numRecords = 0;
				// The standard forces that the field 'PRN LIST' is present in the header, so the next section would
				// never be executed...
				if (!found_prn_list) {
					readedSatellites = 0;
					for (i=0;i<MAX_GNSS;i++) {
						for (j=1;j<=listMaxSatGNSS[i];j++) {
							products->SP3->clocks.index[i][j] = readedSatellites;
							readedSatellites++;
						}
					}
					products->SP3->clocks.numSatellites = readedSatellites;
					// Reserve memory for satellites
					products->SP3->clocks.block = malloc(sizeof(TSP3clockblock*)*products->SP3->clocks.numSatellites);
					for (i=0;i<products->SP3->clocks.numSatellites;i++) {
						products->SP3->clocks.block[i] = NULL;
					}
				}
			}
		} else { // !readingHeader
			getstr(aux,line,len,3,4);
			getstr(aux2,line,len,0,2);
			getstr(aux3,line,len,4,2);
			PRN = atoi(aux3);
			if ( checkConstellationChar(aux[0])==1 && PRN>0 && strncmp(aux2,"AS",2)==0 )  {
				// AS G02  2008 10 10 00 00  0.000000  2    1.813604156067e-04  3.113411106060e-11
				GNSS = gnsschar2gnsstype(aux[0]);
				if (PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in precise clock file",aux);
					printError(messagestr,options);
				}
				ind = products->SP3->clocks.index[GNSS][PRN];
				if (ind==-1) {
					sprintf(messagestr,"Satellite '%c%02d' data read, but it is not in the header of CLK file",aux[0],PRN);
					printError(messagestr,options);
				}

				invalidDate=0;
				getstr(aux,line,len,initPosYear,4);
				tm.tm_year = atoi(aux);
				if (tm.tm_year<1900) invalidDate=1;
				tm.tm_year -= 1900;
				getstr(aux,line,len,initPosMonth,2);
				tm.tm_mon  = atoi(aux);
				if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
				tm.tm_mon  -= 1;
				getstr(aux,line,len,initPosDay,2);
				tm.tm_mday = atoi(aux);
				if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
				getstr(aux,line,len,initPosHour,2);
				tm.tm_hour = atoi(aux);
				if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
				getstr(aux,line,len,initPosMin,2);
				tm.tm_min  = atoi(aux);
				if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
				getstr(aux,line,len,initPosSec,9);
				tm.tm_sec  = atoi(aux);
				if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
				seconds = atof(aux);
				t.MJDN = MJDN(&tm);
				t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				if (t.MJDN<FIRSTMJDNGPS || t.SoD<0. || invalidDate==1 ) {
					sprintf(messagestr,"Invalid epoch '%.26s' for satellite %c%2d in precise clock file",&line[initPosYear],line[3],PRN);
					printError(messagestr,options);
				}
				
				if (lastT.MJDN != t.MJDN || lastT.SoD != t.SoD) { // New Epoch
					if (lastT.MJDN!=0) {  //It is not the first epoch
						if (products->SP3->clocks.interval == 0.) { // If interval is still not known
							interval = tdiff(&t,&lastT);
							if (interval>=1.) {
								//Take out decimals if interval is greater than 1
								products->SP3->clocks.interval = (double)((int)(interval));
							} else {
								products->SP3->clocks.interval = interval;
							}
						}
						//Check that new epoch is not before the last epoch read
						if (tdiff(&t,&lastT)<-DIFFEQTHRESHOLD) {
							t2tmnolocal(&lastT,&tm,&seconds);
							sprintf(messagestr,"Epoch '%.26s' for satellite %c%2d is previous to the last epoch read '%4d %02d %02d %02d %02d %9.6f' in precise clock file",&line[initPosYear],line[3],PRN,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds);
							printError(messagestr,options);
						}
					}

					// Added check: If in one epoch there is no data for a given satellite, it will have an invalid clock value but it will not
					// have the correct time stamp, which will be a problem when interpolating clocks
					if ( lastT.MJDN != 0 ) { //It is not the first epoch
						for (i=0;i<products->SP3->clocks.numSatellites;i++) {
							// If the time stamp of a satellite block of the previous epoch has not the right value, 
								// then there has been no data for that satellite, so the satellite block time stamp has to be fixed 
							if (tdiff(&lastT,&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t)!=0) {
								memcpy(&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t,&lastT,sizeof(TTime));
							}
						}
					} else {
						//First epoch. Save start time
						memcpy(&products->SP3->clocks.startTime,&t,sizeof(TTime));
					}

					memcpy(&lastT,&t,sizeof(TTime));
					products->SP3->clocks.numRecords++;
					// Reserve memory for blocks
					for (i=0;i<products->SP3->clocks.numSatellites;i++) {
						products->SP3->clocks.block[i] = realloc(products->SP3->clocks.block[i],sizeof(TSP3clockblock)*products->SP3->clocks.numRecords);
						initSP3clockblock(&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1]);
					}
				}
			
				getstr(aux,line,len,initPosClkCorr,22);
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clock = atof(aux)*c0;
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockrate = 0.0;
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockdriftrate = 0.0;

				//Read clock flags if available (NOTE: This is not in RINEX standard, but appear in MGEX clock files)
				if(len>=minLenFlags && strncmp(&line[initPosClkFlags],"  ",2)!=0) {
					strncpy(products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags,&line[initPosClkFlags],2);
					products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags[2]='\0';
				} else {
					products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags[0]='\0';
				}
			
				memcpy(&products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].t,&t,sizeof(TTime));
			}
		}
	}

	for (i=0;i<products->SP3->clocks.numSatellites;i++) {
		// If the time stamp of a satellite block of the last epoch has not the right value, 
		// then there has been no data for that satellite, so the satellite block time stamp has to be fixed 
		if (tdiff(&t,&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t)!=0) {
			memcpy(&products->SP3->clocks.block[i][products->SP3->clocks.numRecords-1].t,&t,sizeof(TTime));
		}
	}
	//Save last epoch
	memcpy(&products->SP3->clocks.endTime,&t,sizeof(TTime));

	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readRinexClocksFile
 * Description : Read a RINEX Clocks file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TGNSSproducts  *products        O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readRinexClocksFile (char *filename, TGNSSproducts *products, TOptions *options) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftRINEXclocks) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readRinexClocks (fd, products,options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readGalileoTroposphericData
 * Description : Read tropospheric data files extracted from ESA's Matlab
 *	             tropospheric model (version 2.5, 07/09/2007). These data files
 *               are created exporting to text files the content of the
 *	             variables created when loading 'meteo_esa' library
 *	             (for data exporting, the following Octave's command must be used: 
 *                'save data_<Variable Name>.txt <Variable Name>')
 *	             These files were first exported with Octave v3.2.3
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTROPOGal *TropoGal             O  N/A  Structure to save the data
 * char *filename                  O  N/A  File name (only in case of failure)
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readGalileoTroposphericData (TTROPOGal *TropoGal, char *filename, TOptions *options) {

	return 0;
}

/*****************************************************************************
 * Name        : readIONEX
 * Description : Read a IONEX file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TIONEX  *IONEX                  O  N/A  Structure to save the data
 * double *ionexVersion            O  N/A  IONEX file version
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         4 => File is concatenated but no END OF FILE found
 *                                         3 => File is concatenated
 *                                         2 => properly read but no END OF FILE found
 *                                         1 => Properly read
 *                                         0 => Error
 *                                        -2 => Number of records read do not match the number given in the header
 *                                        -3 => Something wrong or missing in Header
 *****************************************************************************/
int readIONEX (FILE *fd, TIONEX *IONEX, double *ionexVersion, TOptions *options) {
	char			line[MAX_INPUT_LINE];
	char			aux[100];
	int				len = 0;
	int				properlyRead = 0;
	int				i, j;
	int				PRN;
	int				HeaderLinesNecessary=-13;
	struct tm		tm;
	double			seconds;
	int				readingCells = 0;
	int				mapType; // 0->TEC 1->RMS 2->HGT
	int				RMSstarted=0,HGTstarted=0;
	int				numFirstLineHeaderRead=0;
	int				EndofFileFound=0;
	TIonoMap		ionoMap;
	TIonexStation	ionexStation;
	int				ind;
	double			lat;
	double			lon1, lon2, dlon, lon;
	int				nlon, ilon;
	double			h;
	double			ionoValue;
	char			ConstellationType[2];
	enum GNSSystem	satSystem;
	static int		firstTimeRead=1;
	
	initIonoMap(&ionoMap);
	initIonexStation(&ionexStation);
	ConstellationType[0] = '\0';

	while(getL(line,&len,fd)!=-1) {
		if(len<2) continue;
		if (!readingCells) {
			if (strncmp(&line[60],"IONEX VERSION / TYPE",20)==0) {
				numFirstLineHeaderRead++;
				if (numFirstLineHeaderRead>1) {
					//Second time "IONEX VERSION / TYPE" line appears. 
					//It is a concatenated file and we have already read one file
					getLback(line,&len,fd);
					if (EndofFileFound==1) {
						properlyRead=3;
					} else {
						properlyRead=4;
					}
					break;
				}
				getstr(aux,line,len,0,9);
				*ionexVersion = atof(aux);
				if (firstTimeRead==0) {
					//Free memory from the previous day read
					for (i=0;i<IONEX->numMaps;i++) {
						free(IONEX->map[i].TEC);
						free(IONEX->map[i].RMS);
						free(IONEX->map[i].HGT);
					}
					if (IONEX->ionexStation!=NULL) {
						free(IONEX->ionexStation);
					}
					free(IONEX->map);
					initIONEX(IONEX);
				}
				if (*ionexVersion != 1.0 ) return 0;
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"EPOCH OF FIRST MAP",18)==0) {
				getstr(aux,line,len,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,len,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,len,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,len,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,len,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,len,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->startTime.MJDN = MJDN(&tm);
				IONEX->startTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"EPOCH OF LAST MAP",17)==0) {
				getstr(aux,line,len,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,len,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,len,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,len,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,len,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,len,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->endTime.MJDN = MJDN(&tm);
				IONEX->endTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"INTERVAL",8)==0) {
				getstr(aux,line,len,0,6);
				IONEX->interval = atoi(aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"# OF MAPS IN FILE",17)==0) {
				getstr(aux,line,len,0,6);
				IONEX->numMaps = atoi(aux); 
				// Reserve memory for maps
				IONEX->map = malloc(sizeof(TIonoMap)*IONEX->numMaps);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"MAPPING FUNCTION",16)==0) {
				getstr(aux,line,len,2,4);
				IONEX->mappingFunctionType=mappingFunctionStr2Type(aux);
				if (IONEX->mappingFunctionType==MappingFunctionUnknown) {
					sprintf(messagestr,"Mapping function type \"%s\" in IONEX file not supported\n",aux); 
					printError(messagestr,options);
				}
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"ELEVATION CUTOFF",16)==0) {
				getstr(aux,line,len,0,8);
				IONEX->elevationCutoff = atof(aux);
			} else if (strncmp(&line[60],"OBSERVABLES USED",16)==0) {
				getstr(aux,line,len,0,60);
				strcpy(IONEX->observablesUsed,aux);
			} else if (strncmp(&line[60],"# OF STATIONS",13)==0) {
				getstr(aux,line,len,0,6);
				IONEX->stationNumber = atoi(aux);
			} else if (strncmp(&line[60],"# OF SATELLITES",15)==0) {
				getstr(aux,line,len,0,6);
				IONEX->satNumber = atoi(aux);
			} else if (strncmp(&line[60],"BASE RADIUS",11)==0) {
				getstr(aux,line,len,0,8);
				IONEX->baseRadius = atof(aux)*1000.; //Convert to metres
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"MAP DIMENSION",13)==0) {
				getstr(aux,line,len,0,6);
				IONEX->mapDimension = atoi(aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"EXPONENT",8)==0) {
				getstr(aux,line,len,0,6);
				IONEX->exponent = atoi(aux);
				IONEX->conversionFactor = E(IONEX->exponent);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"HGT1 / HGT2 / DHGT",18)==0) {
				getstr(aux,line,len,2,6);			// HGT1
				ionoMap.hgt1 = atof(aux);
				getstr(aux,line,len,8,6);			// HGT2
				ionoMap.hgt2 = atof(aux);
				getstr(aux,line,len,14,6);			// DHGT
				ionoMap.dhgt = atof(aux);
				ionoMap.nhgt = numSteps(ionoMap.hgt1,ionoMap.hgt2,ionoMap.dhgt);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"LAT1 / LAT2 / DLAT",18)==0) {
				getstr(aux,line,len,2,6);			// LAT1
				ionoMap.lat1 = atof(aux);
				getstr(aux,line,len,8,6);			// LAT2
				ionoMap.lat2 = atof(aux);
				getstr(aux,line,len,14,6);			// DLAT
				ionoMap.dlat = atof(aux);
				ionoMap.nlat = numSteps(ionoMap.lat1,ionoMap.lat2,ionoMap.dlat);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"LON1 / LON2 / DLON",18)==0) {
				getstr(aux,line,len,2,6);			// LON1
				ionoMap.lon1 = atof(aux);
				getstr(aux,line,len,8,6);			// LON2
				ionoMap.lon2 = atof(aux);
				getstr(aux,line,len,14,6);			// DLON
				ionoMap.dlon = atof(aux);
				ionoMap.nlon = numSteps(ionoMap.lon1,ionoMap.lon2,ionoMap.dlon);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"START OF TEC MAP",16)==0) {
				if(HeaderLinesNecessary!=0) break;
				getstr(aux,line,len,0,6);
				ind = atoi(aux) -1;
				mapType = 0;  // 0->TEC
				//Check if number of records read is not greater than the number given in the header
				if(ind+1>IONEX->numMaps) {
					return -2;
				}
			} else if (strncmp(&line[60],"START OF RMS MAP",16)==0) {
				if(HeaderLinesNecessary!=0) break;
				//Check if number of TEC records read match the number given in the header
				if(ind+1<IONEX->numMaps && RMSstarted==0) {
					return -2;
				}
				RMSstarted=1;
				getstr(aux,line,len,0,6);
				ind = atoi(aux) -1;
				mapType = 1;  // 1->RMS
				IONEX->RMSavailable = 1; 
				//Check if number of records read is not greater than the number given in the header
				if(ind+1>IONEX->numMaps) {
					return -2;
				}
			} else if (strncmp(&line[60],"START OF HEIGHT MAP",19)==0) {
				if(HeaderLinesNecessary!=0) break;
				//Check if number of RMS records read match the number given in the header
				if(ind+1<IONEX->numMaps && HGTstarted==0) {
					return -2;
				}
				HGTstarted=1;
				getstr(aux,line,len,0,6);
				ind = atoi(aux) -1;
				mapType = 2;  // 2->HGT
				IONEX->HGTavailable = 1;
				//Check if number of records read is not greater than the number given in the header
				if(ind+1>IONEX->numMaps) {
					return -2;
				}
			} else if (strncmp(&line[60],"END OF TEC MAP",14)==0) {
				if(HeaderLinesNecessary!=0) break;

			} else if (strncmp(&line[60],"END OF RMS MAP",14)==0) {
				if(HeaderLinesNecessary!=0) break;

			} else if (strncmp(&line[60],"END OF HEIGHT MAP",17)==0) {
				if(HeaderLinesNecessary!=0) break;
		
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				properlyRead=2;
				HeaderLinesNecessary++;
				for (i=0;i<IONEX->numMaps;i++) {
					memcpy(&IONEX->map[i],&ionoMap,sizeof(TIonoMap));
					IONEX->map[i].TEC = malloc(sizeof(double)*getIonoMapTotalSize(&IONEX->map[i]));
					IONEX->map[i].RMS = malloc(sizeof(double)*getIonoMapTotalSize(&IONEX->map[i]));
					IONEX->map[i].HGT = malloc(sizeof(double)*getIonoMapTotalSize(&IONEX->map[i]));
					for(j=0;j<getIonoMapTotalSize(&IONEX->map[i]);j++) {
						//Initialize everything to 9999, so if there are any value missing in the IONEX file, the value stored will be 9999 and not 0
						IONEX->map[i].TEC[j]=9999;
						IONEX->map[i].RMS[j]=9999;
						IONEX->map[i].HGT[j]=9999;
					}
				}
			} else if (strncmp(&line[60],"EPOCH OF CURRENT MAP",20)==0) {
				if(HeaderLinesNecessary!=0) break;
				getstr(aux,line,len,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,len,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,len,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,len,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,len,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,len,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->map[ind].t.MJDN = MJDN(&tm);
				IONEX->map[ind].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			} else if (strncmp(&line[60],"LAT/LON1/LON2/DLON/H",20)==0) {
				if(HeaderLinesNecessary!=0) break;
				getstr(aux,line,len,2,6);
				lat = atof(aux);
				getstr(aux,line,len,8,6);
				lon1 = atof(aux);
				getstr(aux,line,len,14,6);
				lon2 = atof(aux);
				getstr(aux,line,len,20,6);
				dlon = atof(aux);
				getstr(aux,line,len,26,6);
				h = atof(aux);
				if (IONEX->map[ind].hgt1==0) { IONEX->map[ind].hgt1=IONEX->map[ind].hgt2=h; } //To avoid 0 values in case HGT1=HGT2=DHGT=0 in IONEX file
				nlon = numSteps(lon1,lon2,dlon);
				ilon = 0;
				readingCells = 1;
			} else if (strncmp(&line[60],"PRN / BIAS / RMS",16)==0) {
				getstr(ConstellationType,line,len,3,1);     //GNSS type letter
				satSystem = gnsschar2gnsstype(ConstellationType[0]);
				getstr(aux,line,len,4,2);
				PRN = atoi(aux);
				if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in IONEX file",aux);
					printError(messagestr,options);
				}
				getstr(aux,line,len,6,10);
				IONEX->ionexDCB.DCB[satSystem][PRN] = atof(aux);
				getstr(aux,line,len,16,10);
				IONEX->ionexDCB.DCBRMS[satSystem][PRN] = atof(aux);
				IONEX->ionexDCB.DCBavailable = 1;
			} else if (strncmp(&line[60],"STATION / BIAS / RMS",20)==0) {
				IONEX->numStationData++;
				IONEX->ionexStation = realloc(IONEX->ionexStation,sizeof(TIonexStation)*IONEX->numStationData);
				getstr(aux,line,len,6,4);
				strcpy(IONEX->ionexStation[IONEX->numStationData -1].stationInitials,aux);
				getstr(aux,line,len,11,10);
				strcpy(IONEX->ionexStation[IONEX->numStationData -1].stationcode,aux);
				getstr(aux,line,len,26,10);
				IONEX->ionexStation[IONEX->numStationData -1].stationBias = atof(aux);
				getstr(aux,line,len,36,10);
				IONEX->ionexStation[IONEX->numStationData -1].stationRMS = atof(aux);
			} else if (strncmp(&line[60],"END OF FILE",11)==0) {
				properlyRead = 1;
				firstTimeRead=0;
				EndofFileFound=1;
			}
		} else {  // readingCells
			if(HeaderLinesNecessary!=0) break;
			for (i=0;i<16 && ilon<nlon;i++,ilon++) {
				getstr(aux,line,len,i*5,5);
				lon = ilon*dlon + lon1;
				ionoValue = atof(aux);
				if (ionoValue>=9999.) {
					setIonoValue(&IONEX->map[ind],mapType,h,lat,lon,ionoValue);
				} else {
					setIonoValue(&IONEX->map[ind],mapType,h,lat,lon,ionoValue*IONEX->conversionFactor);
				}
			}
			if (ilon==nlon) readingCells = 0;
		}
	}

	if (HeaderLinesNecessary!=0) properlyRead=-3;
	return (properlyRead); 
}

/*****************************************************************************
 * Name        : readFPPP
 * Description : Read a FPPP file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TFPPP  *FPPP                    O  N/A  Structure to save the data
 * double *FPPPVersion             O  N/A  FPPP file version
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readFPPP (FILE *fd, TFPPPIONEX *FPPP, double *FPPPVersion, TOptions *options) {
	char		line[MAX_INPUT_LINE];
	char 		aux[100];
	int 		len = 0;
	int			properlyRead = 0;
	int			error = 0;
	int			PRN;
	struct tm	tm;
	double		seconds;
	int			readingHeader = 1, readingDCB = 0, lastMapNotStarted = 1;
	int			mapType;
	TFPPPMap	FPPPMap;
	int			ind, mapPosition;
	double		lt, lat, sigma, exponent, tec, mapHeight;
	char		ConstellationType[2];
	enum GNSSystem  satSystem;

	
	initFPPPMap(&FPPPMap);
	ConstellationType[0] = '\0';

	while(getL(line,&len,fd)!=-1) {
		if (readingHeader) {
			if (strncmp(&line[60],"FPPP VERSION / TYPE",19)==0) {
				getstr(aux,line,len,0,9);
				*FPPPVersion = atof(aux);
				if (*FPPPVersion != 1.0 ) return 0;
			} else if (strncmp(&line[60],"EPOCH OF FIRST MAP",18)==0) {
				getstr(aux,line,len,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,len,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,len,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,len,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,len,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,len,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				FPPP->startTime.MJDN = MJDN(&tm);
				FPPP->startTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			} else if (strncmp(&line[60],"INTERVAL",8)==0) {
				getstr(aux,line,len,0,6);
				FPPP->interval = atoi(aux);
			} else if (strncmp(&line[60],"BASE RADIUS",11)==0) {
				getstr(aux,line,len,0,8);
				FPPP->baseRadius = atof(aux)*1000.; //Convert to metres
			} else if (strncmp(&line[60],"HGT1 / HGT2",11)==0) {
				getstr(aux,line,len,0,8);			// HGT1
				FPPPMap.hgt1 = atof(aux);
				getstr(aux,line,len,8,8);			// HGT2
				FPPPMap.hgt2 = atof(aux);
				FPPPMap.dhgt = FPPPMap.hgt2 - FPPPMap.hgt1;
		/*	} else if (strncmp(&line[60],"LAT1 / LAT2 / DLAT",18)==0) {
				getstr(aux,line,len,2,6);			// LAT1
				ionoMap.lat1 = atof(aux);
				getstr(aux,line,len,8,6);			// LAT2
				ionoMap.lat2 = atof(aux);
				getstr(aux,line,len,14,6);			// DLAT
				ionoMap.dlat = atof(aux);
				ionoMap.nlat = numSteps(ionoMap.lat1,ionoMap.lat2,ionoMap.dlat);*/
			} else if (strncmp(&line[60],"DLT / DLAT",10)==0) {
				getstr(aux,line,len,0,8);			// DLT
				FPPPMap.dlt = atof(aux);
				FPPPMap.lt2 = FPPPMap.lt2 - FPPPMap.dlt;
				getstr(aux,line,len,8,8);			// DLAT
				FPPPMap.dlat = atof(aux);
			} else if (strncmp(&line[60],"MIN/MAX  LAT",12)==0) {
				getstr(aux,line,len,0,8);			// LAT1
				FPPPMap.lat1 = atof(aux);
				getstr(aux,line,len,8,8);			// LAT2
				FPPPMap.lat2 = atof(aux);
				FPPPMap.nlt = numSteps(FPPPMap.lt1,FPPPMap.lt2,FPPPMap.dlt);
				FPPPMap.nlat = numSteps(FPPPMap.lat1,FPPPMap.lat2,FPPPMap.dlat);
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
			}
		
		} else {
			if (strncmp(&line[60],"START OF TEC MAP",16)==0 && len>60) {
				getstr(aux,line,len,0,7);
				ind = atoi(aux) -1;
				//Reserve memory for new map, copy variables and initialize all points to 9999
				FPPP->map = (TFPPPMap*) (realloc(FPPP->map,sizeof(TFPPPMap)*(ind+1)));
				memcpy(&FPPP->map[ind],&FPPPMap,sizeof(TFPPPMap));
				FPPP->map[ind].TEC = malloc(sizeof(double)*getFPPPMapTotalSize(&FPPP->map[ind]));
				FPPP->map[ind].SIGMA = malloc(sizeof(double)*getFPPPMapTotalSize(&FPPP->map[ind]));
				initFPPPMapData(&FPPP->map[ind]);

				//Prepare for reading DCB (if there are any available)
				readingDCB = 1;

				//Check if really this last map has data (due to FPPP is real time generated, it includes the Header but not the data)
				lastMapNotStarted=1;
			} else if (strncmp(&line[60],"EPOCH OF CURRENT MAP",20)==0 && len>60) {
				getstr(aux,line,len,2,4);		// Year
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,len,10,2);		// Month
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,len,16,2);		// Day
				tm.tm_mday = atoi(aux);
				getstr(aux,line,len,22,2);		// Hour
				tm.tm_hour = atoi(aux);
				getstr(aux,line,len,28,2);		// Minute
				tm.tm_min  = atoi(aux);
				getstr(aux,line,len,34,2);		// Second
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				FPPP->map[ind].t.MJDN = MJDN(&tm);
				FPPP->map[ind].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				//DCB data ended
				readingDCB = 0;
			} else if (readingDCB){
				getstr(ConstellationType,line,len,0,1);     //GNSS type letter
				satSystem = gnsschar2gnsstype(ConstellationType[0]);
				getstr(aux,line,len,1,2); // PRN 
				PRN = atoi(aux);	
				if (PRN<=0||PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in Fast-PPP file",aux);
					printError(messagestr,options);
				}
				getstr(aux,line,len,4,9); // frac1 	
				FPPP->fpppDCB.frac1[satSystem][PRN] = atof(aux);
				getstr(aux,line,len,14,9); // frac2
				FPPP->fpppDCB.fracw[satSystem][PRN] = atof(aux);
				getstr(aux,line,len,24,9); // IFB
				FPPP->fpppDCB.IFB[satSystem][PRN] = atof(aux);
				FPPP->fpppDCB.DCBavailable = 1;
		/*	} else if (strncmp(&line[60],"LAT/LON1/LON2/DLON/H",20)==0) {
				getstr(aux,line,len,2,6);
				lat = atof(aux);
				getstr(aux,line,len,8,6);
				lon1 = atof(aux);
				getstr(aux,line,len,14,6);
				lon2 = atof(aux);
				getstr(aux,line,len,20,6);
				dlon = atof(aux);
				getstr(aux,line,len,26,6);
				h = atof(aux);
				if (FPPP->map[ind].hgt1==0) { FPPP->map[ind].hgt1=FPPP->map[ind].hgt2=h; } //To avoid 0 values in case HGT1=HGT2=DHGT=0 in IONEX file
				nlon = numSteps(lon1,lon2,dlon);
				ilon = 0;
				readingCells = 1;
		*/
		/*	} else if (strncmp(&line[60],"END OF FILE",11)==0) {
								properlyRead = 1;
		*/	
			} else {  // readingCells

				getstr(aux,line,len,0,6); // LT
				lt = modulo(atof(aux)+360,360);
				getstr(aux,line,len,6,6); // LAT
				lat = atof(aux);
				getstr(aux,line,len,12,9); // PARTIAL TEC
				tec = atof(aux);
				getstr(aux,line,len,21,5); // SIGMA
				sigma = atof(aux);
				getstr(aux,line,len,27,3); // SIGMA EXPONENT
				exponent = atof(aux);
				sigma = sigma * E(exponent);
				getstr(aux,line,len,30,3); // MAP POSITION
				mapPosition = atoi(aux) -1;
			

				mapHeight = FPPP->map[ind].hgt1 + mapPosition*FPPP->map[ind].dhgt;
				//Set TEC value for current map
				mapType = 0;	
				setFPPPValue(&FPPP->map[ind],mapType,mapHeight,lat,lt,tec);
				//Set SIGMA values for current map
				mapType = 1;
				setFPPPValue(&FPPP->map[ind],mapType,mapHeight,lat,lt,sigma);
			
				properlyRead = 1;
				lastMapNotStarted = 0;
			}
		}
		
	} //end While

	FPPP->numMapsAlloc = ind+1;	//Save maps allocated for memory free later
	if (lastMapNotStarted) {ind--;} //Take into consideration the case in which the Header is given but not the data (due to the file is real time generated)
	FPPP->numMaps = ind +1;
	FPPP->endTime.MJDN = FPPP->map[ind].t.MJDN;
	FPPP->endTime.SoD = FPPP->map[ind].t.SoD;
	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readFPPPFile
 * Description : Read a IONEX FPPP file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TFPPP  *FPPP                    O  N/A  Structure to save the data
 * double *FPPPVersion             O  N/A  FPPP file version
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readFPPPFile (char *filename, TFPPPIONEX *FPPP, double *FPPPVersion, TOptions *options) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftFPPP) return 0;
	if ((fd = fopen(filename,"rb"))) {
		ret = readFPPP (fd, FPPP, FPPPVersion,options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}


/*****************************************************************************
 * Name        : readConstellation
 * Description : Read a constellation status file from a file descriptor
 *               File available at: 
 *                 http://gge.unb.ca/Resources/GPSConstellationStatus.txt
 *	             File compiled and maintaned by Richard B. Langley, Dept. of 
 *               Geodesy and Geomatics Engineering, University of New Brunswick.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TConstellation  *constellation  O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readConstellation (FILE *fd, TConstellation *constellation, TOptions *options) {
	char 					line[MAX_INPUT_LINE];
	char    				aux[100];
	int 					len = 0;
	int						properlyRead = 0;
	int						error = 0;
	struct tm				tm;
	int						readingInfo = 0;
	TConstellationElement	sat;
	int						i;
	
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;

	while(getL(line,&len,fd)!=-1) {
		getstr(aux,line,len,0,5);
		if (strcmp(aux,"Block")==0) {
			// Initialize
			initConstellationElement(&sat);
			sat.GNSS = GPS;		// Only prepared for GPS right now
						
			getstr(aux,line,len,6,10);
			if (strcmp(aux,"I")==0) {
				sat.block = GPS_BLOCK_I;
			} else if (strcmp(aux,"II")==0) {
				sat.block = GPS_BLOCK_II;
			} else if (strcmp(aux,"IIA")==0) {
				sat.block = GPS_BLOCK_IIA;
			} else if (strcmp(aux,"IIR")==0) {
				sat.block = GPS_BLOCK_IIR;
			} else if (strcmp(aux,"IIR-M")==0) {
				sat.block = GPS_BLOCK_IIRM;
			} else {
				sat.block = UNKNOWN_BLOCK;
			}
			if (sat.block == GPS_BLOCK_II || sat.block == GPS_BLOCK_IIA) {
				for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
					sat.PCO[i][0] = 0.279;
					sat.PCO[i][1] = 0;
					sat.PCO[i][2] = 1.023;
				}
			} else if (sat.block == GPS_BLOCK_I)  {
				for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
					sat.PCO[i][0] = 0.21;
					sat.PCO[i][1] = 0;
					sat.PCO[i][2] = 0.854;
				}
			} else {
				for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
					sat.PCO[i][0] = sat.PCO[i][1] = sat.PCO[i][2] = 0;
				}
			}
			properlyRead = 1;
			readingInfo = 1;
		} else {
			if (readingInfo) {
				if (strcmp(aux,"Notes")==0) {
					readingInfo = 0;
				} else { // Satellite Data
					getstr(aux,line,len,7,3);
					sat.SVN = atoi(aux);
					getstr(aux,line,len,57,14);
					if (sat.SVN!=0 && strcmp(aux,"Launch failure")!=0) { // Valid line
						getstr(aux,line,len,11,2);
						sat.PRN = atoi(aux);
						if (sat.PRN<=0||sat.PRN>=MAX_SATELLITES_PER_GNSS) {
							sprintf(messagestr,"Invalid PRN number '%s' in constellation file",aux);
							printError(messagestr,options);
						}
						
						getstr(aux,line,len,41,2);
						tm.tm_year = atoi(aux);
						if (tm.tm_year < 70) tm.tm_year+=100;
						getstr(aux,line,len,44,2);
						tm.tm_mon = atoi(aux)-1;
						getstr(aux,line,len,47,2);
						tm.tm_mday = atoi(aux);
						sat.tLaunch.MJDN = MJDN(&tm);
						sat.tLaunch.SoD = 0;
						
						if (line[68]==':') { // Satellite not decomissioned
							tm.tm_year = 130;
							tm.tm_mon = 0;
							tm.tm_mday = 1;
						} else { // Satellite decomissioned
							getstr(aux,line,len,70,2);
							tm.tm_year = atoi(aux);
							if (tm.tm_year < 70) tm.tm_year+=100;
							getstr(aux,line,len,73,2);
							tm.tm_mon = atoi(aux)-1;
							getstr(aux,line,len,76,2);
							tm.tm_mday = atoi(aux);
						} 
						sat.tDecommissioned.MJDN = MJDN(&tm);
						sat.tDecommissioned.SoD = 0;
						
						// Allocate memory
						constellation->numSatellites[sat.GNSS][sat.PRN]++;
						constellation->sat[sat.GNSS][sat.PRN] = realloc(constellation->sat[sat.GNSS][sat.PRN],sizeof(TConstellationElement)*constellation->numSatellites[sat.GNSS][sat.PRN]);
						
						// Store satellite
						memcpy(&constellation->sat[sat.GNSS][sat.PRN][constellation->numSatellites[sat.GNSS][sat.PRN]-1],&sat,sizeof(TConstellationElement));
					}
				}
			}
		}
	}

	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readConstellationFile
 * Description : Read a constellation status file from a filename
 *               File available at:
 *                 http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt
 *	             File compiled and maintaned by Richard B. Langley, Dept. of 
 *               Geodesy and Geomatics Engineering, University of New Brunswick.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TConstellation  *constellation  O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readConstellationFile (char *filename, TConstellation *constellation, TOptions *options) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftConstellation) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readConstellation (fd, constellation, options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readAntex
 * Description : Read an ANTEX file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TConstellation  *constellation  O  N/A  Structure to save the data of GNSS satellites
 * TAntennaList *antennaList       O  N/A  Structure to save the data of receiver 
 *                                         antennas
 * int type                        I  N/A  0 -> Reading ANTEX for satellite and receiver data
 *                                         1 -> Reading ANTEX for receiver data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readAntex (FILE *fd, TConstellation *constellation, TAntennaList *antennaList, int type, TOptions  *options) {
	char					line[MAX_INPUT_LINE];
	char					aux[100];
	char					*ca;
	int 					len = 0;
	struct tm				tm;
	int						properlyRead = 0;
	int						AddAntenna,strictradome;
	TConstellationElement	sat;
	TAntenna				ant;
	TAntenna 				*antSearch;
	int						i, j, k;
	int						freqInd;
	int						readingHeader = 1;
	int						error = 0;
	int						PRN;
	int						GNSS;
	int						readingWhat; // = 0 Satellite    = 1 Receiver antenna
	int						invalidDate=0;
	double					seconds;
	
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	
	while(getL(line,&len,fd)!=-1) {
		if (len<2) continue; //Skip blank lines
		if (readingHeader) {
			if (strncmp(&line[60],"ANTEX VERSION / SYST",20)==0) {
				properlyRead = 1;
			} else if (strncmp(&line[60],"PCV TYPE / REFANT",17)==0) {
				// Do nothing
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
			}
		} else { // readingHeader==0
			if (strncmp(&line[60],"TYPE / SERIAL NO",16)==0) {
				getstr(aux,line,len,20,20);
				PRN = atoi(&aux[1]);
				if (PRN!=0 && checkConstellationChar(aux[0])==1){
					// GNSS Satellite
					if(type==0) {
						initConstellationElement(&sat);
						sat.GNSS = gnsschar2gnsstype(aux[0]);
						sat.PRN = PRN;
						if (sat.PRN<=0 || sat.PRN>=MAX_SATELLITES_PER_GNSS) {
							sprintf(messagestr,"Invalid PRN number '%s' in ANTEX file",aux);
							printError(messagestr,options);
						}
						getstr(aux,line,len,40,10);
						sat.SVN = atoi(&aux[1]);
						getstr(aux,line,len,0,20);
						sat.block = satblockstr2satblock(aux,sat.GNSS);
					}
					readingWhat = 0;
				} else {
					// Receiver antenna
					initAntenna(&ant);
					getstr(aux,line,len,0,20);
					strcpy(ant.type,aux);
					// Separate the anntena.type into antenna and radome
					strcpy(ant.type_ant,ant.type);
					ca = strstr(ant.type_ant," ");
					if (ca != NULL) {
						*ca = '\0';
						strcpy(ant.type_radome,&ca[1]);
						trim(ant.type_radome,(int)strlen(ant.type_radome));
					}
					readingWhat = 1;
				}
			} else if (type==1 && readingWhat==0) {
				//If reading ANTEX for  receiver data, skip satellite data
				continue;
			} else if (strncmp(&line[60],"VALID",5)==0) {
				if (readingWhat==0) { // Satellite Antenna
					invalidDate=0;
					getstr(aux,line,len,2,4);
					tm.tm_year = atoi(aux);
					if (tm.tm_year<=1900) invalidDate=1;
					tm.tm_year -= 1900;
					getstr(aux,line,len,10,2);
					tm.tm_mon  = atoi(aux);
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,line,len,16,2);
					tm.tm_mday = atoi(aux);
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,line,len,22,2);
					tm.tm_hour = atoi(aux);
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,line,len,28,2);
					tm.tm_min  = atoi(aux);
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,line,len,33,10);
					tm.tm_sec  = atoi(aux);
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
					if(invalidDate==1) {
						sprintf(messagestr,"Invalid date '%.44s' in ANTEX file",line);
						printError(messagestr,options);
					}
					seconds = atof(aux);
					if (strncmp(&line[66],"FROM",4)==0) {
						sat.tLaunch.MJDN = MJDN(&tm);
						sat.tLaunch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					} else if (strncmp(&line[66],"UNTIL",5)==0) {
						sat.tDecommissioned.MJDN = MJDN(&tm);
						sat.tDecommissioned.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					}
				}
			} else if (strncmp(&line[60],"DAZI",4)==0) {
				getstr(aux,line,len,2,6);
				if (readingWhat==0) { // Satellite Antenna
					sat.dazi=atof(aux);
				} else if (readingWhat==1) { // Receiver Antenna
					ant.dazi=atof(aux);
				}
			} else if (strncmp(&line[60],"ZEN1 / ZEN2 / DZEN",18)==0) {
				getstr(aux,line,len,2,6);
				if (readingWhat==0) { // Satellite Antenna
					sat.zen1=sat.azi1=atof(aux);
					getstr(aux,line,len,8,6);
					sat.zen2=sat.azi2=atof(aux);
					getstr(aux,line,len,14,6);
					sat.dzen=atof(aux);
					sat.nzen=numSteps(sat.zen1,sat.zen2,sat.dzen);
					//Allocate memory for non azimuth corrections
					sat.noazi=malloc(sizeof(double*)*MAX_GNSS);
					for(i=0;i<MAX_GNSS;i++) {
						sat.noazi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
						for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
							sat.noazi[i][j]=calloc(sat.nzen,sizeof(double));//Use calloc to initialize all to 0, as there may be no data for some constellations/frequencies
						}
					}
					if(sat.dazi>0) {
						sat.numazi=numSteps(0.0,360.0,sat.dazi);
						//Allocate memory for azimuth corrections
						sat.azi=malloc(sizeof(double*)*MAX_GNSS);
						for(i=0;i<MAX_GNSS;i++) {
							sat.azi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
							for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
								sat.azi[i][j]=malloc(sizeof(double*)*sat.numazi);
								for(k=0;k<sat.numazi;k++) {
									sat.azi[i][j][k]=calloc(sat.nzen,sizeof(double)); //Use calloc to initialize all to 0, as there may be no data for some constellations/frequencies
								}
							}
						}
					}
				} else if (readingWhat==1) { // Receiver Antenna
					ant.zen1=ant.azi1=atof(aux);
					getstr(aux,line,len,8,6);
					ant.zen2=ant.azi2=atof(aux);
					getstr(aux,line,len,14,6);
					ant.dzen=atof(aux);
					ant.nzen=numSteps(ant.zen1,ant.zen2,ant.dzen);
					//Allocate memory for non azimuth corrections
					ant.noazi=malloc(sizeof(double*)*MAX_GNSS);
					for(i=0;i<MAX_GNSS;i++) {
						ant.noazi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
						for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
							ant.noazi[i][j]=calloc(ant.nzen,sizeof(double)); //Use calloc to initialize all to 0, as there may be no data for some constellations/frequencies
						}
					}
					if(ant.dazi>0) {
						ant.numazi=numSteps(0.0,360.0,ant.dazi);
						//Allocate memory for azimuth corrections
						ant.azi=malloc(sizeof(double*)*MAX_GNSS);
						for(i=0;i<MAX_GNSS;i++) {
							ant.azi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
							for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
								ant.azi[i][j]=malloc(sizeof(double*)*ant.numazi);
								for(k=0;k<ant.numazi;k++) {
									ant.azi[i][j][k]=calloc(ant.nzen,sizeof(double)); //Use calloc to initialize all to 0, as there may be no data for some constellations/frequencies
								}
							}
						}
					}
				}
			} else if (strncmp(&line[60],"START OF FREQUENCY",18)==0) {
				getstr(aux,line,len,4,2);
				freqInd = atoi(aux);
				getstr(aux,line,len,3,1);
				GNSS=gnsschar2gnsstype(aux[0]);
			} else if (strncmp(&line[60],"NORTH / EAST / UP",17)==0) {
				for (i=0;i<3;i++) {
					getstr(aux,line,len,i*10,10);
					if (readingWhat==0) { // Satellite Antenna
						sat.PCO[freqInd][i] = atof(aux)/1e3; // (ANTEX in mm)
					} else if (readingWhat==1) { // Receiver Antenna
						ant.PCO[GNSS][freqInd][i] = atof(aux)/1e3; // (ANTEX in mm)
					}
				}
				//Read non azimuth corrections
				if(getL(line,&len,fd)!=-1) {
					if (strncmp(&line[3],"NOAZI",5)==0) {
						if (readingWhat==0) { // Satellite Antenna
							for(i=0;i<sat.nzen;i++) {
								getstr(aux,line,len,8+8*i,8);
								sat.noazi[GNSS][freqInd][i]=atof(aux)/1e3;  // (ANTEX in mm)
							}
						} else if (readingWhat==1) { // Receiver Antenna
							for(i=0;i<ant.nzen;i++) {
								getstr(aux,line,len,8+8*i,8);
								ant.noazi[GNSS][freqInd][i]=atof(aux)/1e3;  // (ANTEX in mm)
							}
						}
					} else {
						//Non azimuth corrections missing
						properlyRead=0;
					}
				}
				//Read azimuth corrections if available
				if( (readingWhat==0 && sat.dazi>0) || (readingWhat==1 && ant.dazi>0) ) {
					if (readingWhat==0) { // Satellite Antenna
						for(i=0;i<sat.numazi;i++) {
							if(getL(line,&len,fd)!=-1) {
								for(j=0;j<sat.nzen;j++) {
									getstr(aux,line,len,8+8*j,8);
									sat.azi[GNSS][freqInd][i][j]=atof(aux)/1e3;  // (ANTEX in mm)
								}
							} else {
								properlyRead=0;
								break;
							}
						}
					} else if (readingWhat==1) { // Receiver Antenna
						for(i=0;i<ant.numazi;i++) {
							if(getL(line,&len,fd)!=-1) {
								for(j=0;j<ant.nzen;j++) {
									getstr(aux,line,len,8+8*j,8);
									ant.azi[GNSS][freqInd][i][j]=atof(aux)/1e3;  // (ANTEX in mm)
								}
							} else {
								properlyRead=0;
								break;
							}
						}

					}
				}
			} else if (strncmp(&line[60],"END OF ANTENNA",14)==0) {
				if (readingWhat==0) { // Satellite Antenna
					// Allocate memory
					constellation->numSatellites[sat.GNSS][sat.PRN]++;
					constellation->sat[sat.GNSS][sat.PRN] = realloc(constellation->sat[sat.GNSS][sat.PRN],sizeof(TConstellationElement)*constellation->numSatellites[sat.GNSS][sat.PRN]);
						
					// Store satellite
					memcpy(&constellation->sat[sat.GNSS][sat.PRN][constellation->numSatellites[sat.GNSS][sat.PRN]-1],&sat,sizeof(TConstellationElement));

				} else if (readingWhat==1) { // Receiver Antenna
					if (type==1) {
						//When reading an ANTEX file for receiver data, check if antenna is already saved
						//If it exists, replace the existing one
						//Temporary set strict radome to 1 so antenna and radome matches, and does not use radome "NONE" if not found
						strictradome=options->strictradome;
						options->strictradome=1;
						antSearch=getAntenna(ant.type,antennaList,options);
						if (antSearch!=NULL) {
							//Antenna found
							memcpy(antSearch,&ant,sizeof(TAntenna));
							AddAntenna=0;
						} else {
							AddAntenna=1;
						}
						options->strictradome=strictradome;
					} else {
						AddAntenna=1;
					}
					if (AddAntenna==1) {
						// Allocate memory
						antennaList->numAnt++;
						antennaList->ant = realloc(antennaList->ant,sizeof(TAntenna)*antennaList->numAnt);
					
						// Store antenna
						memcpy(&antennaList->ant[antennaList->numAnt-1],&ant,sizeof(TAntenna));
					}
				}
			}
		}
	}

	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readAntexFile
 * Description : Read an ANTEX file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TConstellation  *constellation  O  N/A  Structure to save the data of GNSS satellites
 * TAntennaList *antennaList       O  N/A  Structure to save the data of receiver 
 *                                         antennas
 * int type                        I  N/A  0 -> Reading ANTEX for satellite and receiver data
 *                                         1 -> Reading ANTEX for receiver data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readAntexFile (char *filename, TConstellation *constellation, TAntennaList *antennaList, int type, TOptions  *options) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftANTEX) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readAntex (fd, constellation, antennaList, type, options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readDCB
 * Description : Read a CODE DCB file from a file descriptor.
 *                These DCBs are for GPS only
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TTGDdata *tgdData               O  N/A  Structure to save the DCB data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => Properly read
 *                                          0 => Error
 *                                         -2 => First header line not recognized
 *****************************************************************************/
int readDCB (FILE *fd, TTGDdata *tgdData, TOptions *options) {
	char 					line[MAX_INPUT_LINE];
	char					*pt;
	char					*ptaux;
	char    				aux[100];
	enum MeasurementType	meas;
	enum GNSSystem			GNSS;
	double					value;
	double					rms;
	int 					len = 0;
	struct tm				tm;
	int						properlyRead = 0;
	int						readingHeader = 1;
	int						firstLineHeaderFound = 0;
	int						PRN;
	int						writtingAbs;
	int						year,doy;
	double					factor;
	TDCBdata 				*DCB;
	
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	tm.tm_mday = 1;

	if (tgdData->DCB==NULL) {
		tgdData->DCB = malloc(sizeof(TDCBdata));
		initDCB(tgdData->DCB);
	}
	DCB=tgdData->DCB;
	
	while(getL(line,&len,fd)!=-1) {
		if (readingHeader) {
			if ((pt=strstr(line,"YEAR-MONTH"))!=NULL) {
				// CODE'S MONTHLY GPS P1-C1 DCB SOLUTION, YEAR-MONTH 10-01          04-FEB-10 20:11
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 11; // Pointing to '10-01 [...]'
				getstr(aux,pt,(int)strlen(pt),0,2);
				tm.tm_year = atoi(aux);
				if (tm.tm_year <= 70) tm.tm_year += 100;
				getstr(aux,pt,(int)strlen(pt),3,2);
				tm.tm_mon = atoi(aux) - 1;
				DCB->block[DCB->n-1].startTime.MJDN = MJDN(&tm);
				tm.tm_mon ++;
				DCB->block[DCB->n-1].endTime.MJDN = MJDN(&tm);

			} else if ((pt=strstr(line,"YEAR "))!=NULL) { //From 1 January 2012 the date format has been changed in the DCB header
				// CODE'S MONTHLY GPS P1-C1 DCB SOLUTION, YEAR 2014, MONTH 05       04-JUN-14 07:46
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 5; // Pointing to year number
				getstr(aux,pt,(int)strlen(pt),0,4);
				tm.tm_year = atoi(aux) -1900;
				pt += 12; // Pointing to month number
				getstr(aux,pt,(int)strlen(pt),0,2);
				tm.tm_mon = atoi(aux) - 1;
				DCB->block[DCB->n-1].startTime.MJDN = MJDN(&tm);
				tm.tm_mon ++;
				DCB->block[DCB->n-1].endTime.MJDN = MJDN(&tm);

			} else if ((pt=strstr(line,"ENDING DAY"))!=NULL) { //From somewhere around 2017 the date format has been changed in the DCB header
				// CODE'S 30-DAY GPS P1-C1 DCB SOLUTION, ENDING DAY 306, 2017       06-NOV-17 06:45
				//or
				// CODE'S 30-DAY GNSS P1-C1 DCB SOLUTION, ENDING DAY 306, 2017      06-NOV-17 06:45
				//It does not matter wether is one or another, as the pointer returned by strstr(line,"ENDING DAY") will already have moved the extra character due to "GPS" or "GNSS" text difference
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 11; // Pointing to doy
				getstr(aux,pt,(int)strlen(pt),0,3);
				doy=atoi(aux);
				pt += 5; // Pointing to year
				getstr(aux,pt,(int)strlen(pt),0,4);
				year=atoi(aux);
				DCB->block[DCB->n-1].endTime.MJDN = (int)yeardoy2MJDN(year,doy,0);
				DCB->block[DCB->n-1].startTime.MJDN = DCB->block[DCB->n-1].endTime.MJDN-30;

			} else if (strstr(line,"CODE BIASES")!=NULL) {
				if (firstLineHeaderFound==0) return -2;
				// DIFFERENTIAL (P1-C1) CODE BIASES FOR SATELLITES AND RECEIVERS:
				pt = strstr(line,"(");
				if (pt==NULL) return 0;
				pt++;
				ptaux = strstr(pt,"-");
				if (ptaux==NULL) return 0;
				strncpy(aux,pt,ptaux-pt);
				aux[ptaux-pt]='\0';
				meas = measstr2meastype(aux);
				DCB->block[DCB->n-1].measTo = meas;
				pt=ptaux+1;
				ptaux = strstr(pt,")");
				if (ptaux==NULL) return 0;
				strncpy(aux,pt,ptaux-pt);
				aux[ptaux-pt]='\0';
				meas = measstr2meastype(aux);
				DCB->block[DCB->n-1].measFrom = meas;
				// Check to create the absolute measurement (from P1 to NA)
				if ((DCB->block[DCB->n-1].measFrom==C2P && DCB->block[DCB->n-1].measTo==C1P) || (DCB->block[DCB->n-1].measFrom==C1P && DCB->block[DCB->n-1].measTo==C2P)) {
					DCB->block[DCB->n].measFrom = C1P;
					DCB->block[DCB->n].measTo = NA;
					memcpy(&DCB->block[DCB->n].startTime,&DCB->block[DCB->n-1].startTime,sizeof(TTime));
					memcpy(&DCB->block[DCB->n].endTime,&DCB->block[DCB->n-1].endTime,sizeof(TTime));
					//factor = 1.0/(1.0-(GPSf1*GPSf1)/(GPSf2*GPSf2)); // 1/(1-f1^2/f2^2) ->Factor is applied when retrieving the DCB
					if (DCB->block[DCB->n-1].measFrom==C2P) factor = -1.0;
					else  factor = 1.0;
					writtingAbs = 1;
				} else {
					writtingAbs = 0;
				}
			} else if (strncmp(line,"PRN / STATION NAME",18)==0) {
				// PRN / STATION NAME        VALUE (NS)  RMS (NS)
				// ***   ****************    *****.***   *****.***
				if (firstLineHeaderFound==0) return -2;
				if (getL(line,&len,fd)==-1) {
					return 0;
				}
				readingHeader = 0;
			}
		} else { //readingHeader == 0
			GNSS = gnsschar2gnsstype(line[0]);
			getstr(aux,line,len,1,2);
			PRN = atoi(aux);
			if (PRN != 0) { // Satellite unidentified or blank line
				if (PRN<=0 || PRN>=MAX_SATELLITES_PER_GNSS) {
					sprintf(messagestr,"Invalid PRN number '%s' in DCB file",aux);
					printError(messagestr,options);
				}
				properlyRead = 1;
				getstr(aux,line,len,26,9);
				value = atof(aux);
				getstr(aux,line,len,38,9);
				rms = atof(aux);
				// From ns to metres
				value *= 1e-9*c0;
				rms *= 1e-9*c0;
				DCB->block[DCB->n-1].dcb[GNSS][PRN] = value;
				DCB->block[DCB->n-1].available[GNSS][PRN] = 1;
				if (writtingAbs) {
					DCB->block[DCB->n].dcb[GNSS][PRN] = value*factor;
					DCB->block[DCB->n].available[GNSS][PRN] = 1;
				}
			}
		}
	}
	if (writtingAbs) DCB->n++;
	
	return properlyRead;
}

/*****************************************************************************
 * Name        : readDCBFile
 * Description : Read a CODE DCB file from a filename.
 *                These DCBs are for GPS only
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TTGDdata *tgdData               O  N/A  Structure to save the DCB data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => File open and properly read
 *                                          0 => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => First header line not recognized
 *****************************************************************************/
int readDCBFile (char *filename,  TTGDdata *tgdData, TOptions *options) {
	FILE			*fd;
	int 			ret;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readDCB (fd, tgdData, options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readSINEXBIAS
 * Description : Read a SINEX BIAS DCB file. These are multiconstellation DCBs
 *               NOTE: The following assumptions are made:
 *                - No data gaps for all DCB provided
 *                - Time interval between is equal for all measurements
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * enum fileType ft                I  N/A  SINEX BIAS file type (with DSB or OSB)
 * TSINEXBiasData *SINEXBias       O  N/A  Structure to save the DCB data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => File open and properly read
 *                                          0 => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => No data lines
 *****************************************************************************/
int readSINEXBIAS (FILE  *fd, enum fileType ft, TSINEXBiasData *SINEXBias, TOptions *options) {

	int						i,j,k;
	int						len = 0;
	int						res;
	int						properlyRead=-2;
	int						readingHeader=1;
	int						numDigitsYear;
	int						posGNSS,posPRN,posOBS1,posOBS2,posSTART,posEND,posVALUE,posDEV;
	int						PRN,numMeas,numTimeBlocks,indexPos;
	int						yearStart,doyStart,yearEnd,doyEnd;
	int						maxMeas[MAX_GNSS];
	double					DCBVal,DCBSigma,secondsStart,secondsEnd;
	char					aux[100];
	char					line[MAX_INPUT_LINE];
	char					*p;
	enum GNSSystem			GNSS;
	enum MeasurementType	measFrom,measTo;

	for(i=0;i<MAX_GNSS;i++) {
		maxMeas[i]=0;
	}

	//Allocate memory if necessary (function may be called more than once)
	if (ft==ftSINEXBIASOSB && SINEXBias->OSBindex==NULL) {
		SINEXBias->OSBindex=malloc(MAX_GNSS*sizeof(int *));
		SINEXBias->SNXBiasBlockOSB=malloc(MAX_GNSS*sizeof(TSINEXBiasBlock *));
	
		for(i=0;i<MAX_GNSS;i++) {
			SINEXBias->OSBindex[i]=malloc(MAX_MEASUREMENTS_NO_COMBINATIONS*sizeof(int));
			SINEXBias->SNXBiasBlockOSB[i]=malloc(MAX_SATELLITES_PER_GNSS*sizeof(TSINEXBiasBlock *));
			for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
				SINEXBias->SNXBiasBlockOSB[i][j]=NULL;
			}
			for(j=0;j<MAX_MEASUREMENTS_NO_COMBINATIONS;j++) {
				SINEXBias->OSBindex[i][j]=-1;
			}
		}
	} else if (ft==ftSINEXBIASDSB && SINEXBias->DSBindex==NULL ) {
		SINEXBias->DSBindex=malloc(MAX_GNSS*sizeof(int *));
		SINEXBias->SNXBiasBlockDSB=malloc(MAX_GNSS*sizeof(TSINEXBiasBlock *));
	
		for(i=0;i<MAX_GNSS;i++) {
			SINEXBias->DSBindex[i]=malloc(MAX_MEASUREMENTS_NO_COMBINATIONS*sizeof(int *));
			SINEXBias->SNXBiasBlockDSB[i]=malloc(MAX_SATELLITES_PER_GNSS*sizeof(TSINEXBiasBlock *));
			for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
				SINEXBias->SNXBiasBlockDSB[i][j]=NULL;
			}
			for(j=0;j<MAX_MEASUREMENTS_NO_COMBINATIONS;j++) {
				SINEXBias->DSBindex[i][j]=malloc(MAX_MEASUREMENTS_NO_COMBINATIONS*sizeof(int));
				for(k=0;k<MAX_MEASUREMENTS_NO_COMBINATIONS;k++) {
					SINEXBias->DSBindex[i][j][k]=-1;
				}
			}
		}
	}



	while(getL(line,&len,fd)!=-1) {
		if(len<2) continue; //Skip blank lines
		if(readingHeader) {
			if(strncmp(line,"+BIAS/SOLUTION",14)==0) {
				//Read next header line. This will be the last line before data starts
				res = getL(line,&len,fd);
				if (res==-1) break;
				//In this header line we need to find the initial character of each field
			   	//(the position may change depending on the file author)
				//Look for PRN column
				p=strstr(line,"PRN");
				if (p==NULL) return 0; //PRN column not found
				posGNSS=p-line;
				posPRN=posGNSS+1;
				//Look for OBS1 column
				p=strstr(line,"OBS1");
				if (p==NULL) return 0; //OBS1 column not found
				posOBS1=p-line;
				//Look for OBS2 column
				p=strstr(line,"OBS2");
				if (p==NULL) return 0; //OBS2 column not found
				posOBS2=p-line;
				//Look for BIAS_START____ column
				p=strstr(line,"BIAS_START____");
				if (p==NULL) {
					//BIAS_START____ not found. It may due to Year is given with 2 digits	
					p=strstr(line,"BIAS_START__");
					if (p==NULL) return 0; //BIAS_START column not found
					numDigitsYear=2;
				} else {
					numDigitsYear=4;
				}
				posSTART=p-line;
				//Look for BIAS_END__ column
				p=strstr(line,"BIAS_END__");
				if (p==NULL) return 0; //BIAS_END_ column not found
				posEND=p-line;
				//Look for __ESTIMATED_VALUE__ column
				p=strstr(line,"__ESTIMATED_VALUE____");
				if (p==NULL) return 0; //__ESTIMATED_VALUE____ column not found
				posVALUE=p-line;
				//Look for _STD_DEV_ column
				p=strstr(line,"_STD_DEV___");
				if (p==NULL) return 0; //_STD_DEV___ column not found
				posDEV=p-line;

				readingHeader=0;
			}
		} else {
			if(strncmp(line,"-BIAS/SOLUTION",14)==0) break; //End of data
			if (ft==ftSINEXBIASOSB) {
				//
				if (strncmp(&line[1],"OSB",3)!=0) continue; //Not a data line for absolute biases
			} else {	// if (ft==ftSINEXBIASDSB)
				if (strncmp(&line[1],"DSB",3)!=0 && strncmp(&line[1],"DCB",3)!=0) continue; //Not a data line for differential biases
			}
			//Reading data
			properlyRead=1;
			//Get Constellation
			GNSS=gnsschar2gnsstype(line[posGNSS]);
			//Get PRN
			getstr(aux,line,len,posPRN,2);
			PRN=atoi(aux);
			if (PRN<=0) continue;
			if (PRN>=MAX_SATELLITES_PER_GNSS) {
				sprintf(messagestr,"Invalid PRN number '%s' in SINEX BIAS file",aux);
				printError(messagestr,options);
			}

			//Get Start Epoch
			getstr(aux,line,len,posSTART,numDigitsYear);
			yearStart=atoi(aux);
			getstr(aux,line,len,posSTART+numDigitsYear+1,3);
			doyStart=atoi(aux);
			getstr(aux,line,len,posSTART+numDigitsYear+5,5);
			secondsStart=atof(aux);
			//Get End Epoch
			getstr(aux,line,len,posEND,numDigitsYear);
			yearEnd=atoi(aux);
			getstr(aux,line,len,posEND+numDigitsYear+1,3);
			doyEnd=atoi(aux);
			getstr(aux,line,len,posEND+numDigitsYear+5,5);
			secondsEnd=atof(aux);
			if (numDigitsYear==2) {
				yearStart+=2000;
				yearEnd+=2000;
			}
			//Get DCB value
			getstr(aux,line,len,posVALUE,21);
			DCBVal=atof(aux);
			//Get DCB Sigma
			getstr(aux,line,len,posDEV,11);
			DCBSigma=atof(aux);
			//Get MeasTo
			getstr(aux,line,len,posOBS1,3);
			measFrom=measstr2meastype(aux);
			if (ft==ftSINEXBIASDSB) {
				///////DSB data
				//Get MeasTo
				getstr(aux,line,len,posOBS2,3);
				measTo=measstr2meastype(aux);
				indexPos=SINEXBias->DSBindex[GNSS][measFrom][measTo];
				numMeas=SINEXBias->numMeasBlocksDSB[GNSS];
				if (indexPos==-1) {
					//DSB or OSB measType not read before. Allocate memory for new DSB type for all satellites in the constellation
					if (numMeas<maxMeas[GNSS]) {
						indexPos=maxMeas[GNSS];
						numMeas=maxMeas[GNSS];
					} else {
						indexPos=numMeas;
					}
					SINEXBias->DSBindex[GNSS][measFrom][measTo]=indexPos;
					numTimeBlocks=0;
					numMeas++;
					for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
						SINEXBias->SNXBiasBlockDSB[GNSS][i]=realloc(SINEXBias->SNXBiasBlockDSB[GNSS][i],(numMeas)*sizeof(TSINEXBiasBlock));
						SINEXBias->SNXBiasBlockDSB[GNSS][i][indexPos].numTimeBlocks=0;
						SINEXBias->SNXBiasBlockDSB[GNSS][i][indexPos].EpochStart=NULL;
						SINEXBias->SNXBiasBlockDSB[GNSS][i][indexPos].EpochEnd=NULL;
						SINEXBias->SNXBiasBlockDSB[GNSS][i][indexPos].DCBVal=NULL;
						SINEXBias->SNXBiasBlockDSB[GNSS][i][indexPos].DCBSigma=NULL;
					}

					SINEXBias->numMeasBlocksDSB[GNSS]=numMeas;
				} else {
					//DSB read for current satellite
					numTimeBlocks=SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].numTimeBlocks;
				}
				if (numMeas>maxMeas[GNSS]) {
					maxMeas[GNSS]=numMeas;
				}
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].numTimeBlocks++;

				//Allocate memory for new epoch of a DSB type
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochStart=realloc(SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochStart,(numTimeBlocks+1)*sizeof(TTime));
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochEnd=realloc(SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochEnd,(numTimeBlocks+1)*sizeof(TTime));
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBVal=realloc(SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBVal,(numTimeBlocks+1)*sizeof(double));
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBSigma=realloc(SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBSigma,(numTimeBlocks+1)*sizeof(double));

				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochStart[numTimeBlocks].MJDN=(int)yeardoy2MJDN (yearStart,doyStart,(int)secondsStart);
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochStart[numTimeBlocks].SoD=secondsStart;
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochEnd[numTimeBlocks].MJDN=(int)yeardoy2MJDN (yearEnd,doyEnd,(int)secondsEnd);
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].EpochEnd[numTimeBlocks].SoD=secondsEnd;
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBVal[numTimeBlocks]=DCBVal;
				SINEXBias->SNXBiasBlockDSB[GNSS][PRN][indexPos].DCBSigma[numTimeBlocks]=DCBSigma;

			} else {
				///////OSB data
				measTo=NA;
				indexPos=SINEXBias->OSBindex[GNSS][measFrom];
				numMeas=SINEXBias->numMeasBlocksOSB[GNSS];
				if (indexPos==-1) {
					//OSB or OSB measType not read before. Allocate memory for new OSB type for all satellites in the constellation
					if (numMeas<maxMeas[GNSS]) {
						indexPos=maxMeas[GNSS];
						numMeas=maxMeas[GNSS];
					} else {
						indexPos=numMeas;
					}
					SINEXBias->OSBindex[GNSS][measFrom]=indexPos;
					numTimeBlocks=0;
					numMeas++;
					for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
						SINEXBias->SNXBiasBlockOSB[GNSS][i]=realloc(SINEXBias->SNXBiasBlockOSB[GNSS][i],(numMeas)*sizeof(TSINEXBiasBlock));
						SINEXBias->SNXBiasBlockOSB[GNSS][i][indexPos].numTimeBlocks=0;
						SINEXBias->SNXBiasBlockOSB[GNSS][i][indexPos].EpochStart=NULL;
						SINEXBias->SNXBiasBlockOSB[GNSS][i][indexPos].EpochEnd=NULL;
						SINEXBias->SNXBiasBlockOSB[GNSS][i][indexPos].DCBVal=NULL;
						SINEXBias->SNXBiasBlockOSB[GNSS][i][indexPos].DCBSigma=NULL;
					}

					SINEXBias->numMeasBlocksOSB[GNSS]=numMeas;
				} else {
					//OSB read for current satellite
					numTimeBlocks=SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].numTimeBlocks;
				}
				if (numMeas>maxMeas[GNSS]) {
					maxMeas[GNSS]=numMeas;
				}
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].numTimeBlocks++;

				//Allocate memory for new epoch of a OSB type
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochStart=realloc(SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochStart,(numTimeBlocks+1)*sizeof(TTime));
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochEnd=realloc(SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochEnd,(numTimeBlocks+1)*sizeof(TTime));
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBVal=realloc(SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBVal,(numTimeBlocks+1)*sizeof(double));
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBSigma=realloc(SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBSigma,(numTimeBlocks+1)*sizeof(double));

				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochStart[numTimeBlocks].MJDN=(int)yeardoy2MJDN (yearStart,doyStart,(int)secondsStart);
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochStart[numTimeBlocks].SoD=secondsStart;
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochEnd[numTimeBlocks].MJDN=(int)yeardoy2MJDN (yearEnd,doyEnd,(int)secondsEnd);
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].EpochEnd[numTimeBlocks].SoD=secondsEnd;
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBVal[numTimeBlocks]=DCBVal;
				SINEXBias->SNXBiasBlockOSB[GNSS][PRN][indexPos].DCBSigma[numTimeBlocks]=DCBSigma;
			}
		}
	}

	return (properlyRead);


}

/*****************************************************************************
 * Name        : readSINEXBIASFile
 * Description : Read a SINEX BIAS DCB file. These are multiconstellation DCBs
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * enum fileType ft                I  N/A  SINEX BIAS file type (with DSB or OSB)
 * TSINEXBiasData *SINEXBias       O  N/A  Structure to save the DCB data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => File open and properly read
 *                                          0 => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => First header line not recognized
 *****************************************************************************/
int readSINEXBIASFile (char *filename, enum fileType ft, TSINEXBiasData *SINEXBias, TOptions *options) {

	FILE       		*fd;
	int       	  	ret;

	if ((fd = fopen(filename,"rb"))) {
		ret = readSINEXBIAS (fd, ft, SINEXBias, options);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}


/*****************************************************************************
 * Name        : readRecType
 * Description : Read a GPS Receiver type file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TReceiverList  *recList         O  N/A  Structure to save the Receiver data
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readRecType (FILE *fd, TReceiverList *recList) {
	char 		line[MAX_INPUT_LINE];
	char		cr;
	char   		aux[100];
	int 		len = 0;
	
	while(getL(line,&len,fd)!=-1) {
		if (line[0]!='#') { // Line is not a comment
			getstr(aux,line,len,0,20);
			if (aux[0]!='\0' && aux[0]!='\n') {
				recList->n++;
				recList->rec = realloc(recList->rec,sizeof(TReceiverData)*recList->n);
				strcpy(recList->rec[recList->n-1].name,aux);
				cr = line[21];
				switch (cr) {
					case '0':
						recList->rec[recList->n-1].type = rtUNKNOWN;
						break;
					case '1':
						recList->rec[recList->n-1].type = rtCROSS;
						break;
					case '2':
						recList->rec[recList->n-1].type = rtNOP1;
						break;
					case '3':
						recList->rec[recList->n-1].type = rtNOMINAL;
						break;
					default:
						recList->rec[recList->n-1].type = rtUNKNOWN;
				}
			}
		}
	}
	
	return 1;
}

/*****************************************************************************
 * Name        : readRecTypeFile
 * Description : Read a GPS Receiver type file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TReceiverList  *recList         O  N/A  Structure to save the Receiver data
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readRecTypeFile (char *filename, TReceiverList *recList) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftRECEIVERTYPE) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readRecType (fd, recList);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readSINEX
 * Description : Read a SINEX station positions file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TStationList  *stationList      O  N/A  Structure to save the station data
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readSINEX (FILE *fd, TStationList *stationList) {
	char 	line[MAX_INPUT_LINE];
	char	aux[100];
	int 	len = 0;
	int		section;	// =0 => Unimportant stuff
						// =1 => SITE/ID section
						// =2 => SOLUTION/ESTIMATE section
	int 	properlyRead = 0;
	int		auxN;
	int		error = 0;
	int		i=0;
	char	prevName[5] = "";
	
	section = 0;
	while(getL(line,&len,fd)!=-1) {
		if (len<2) continue;
		if (line[0]=='+') { // Change of section
			if (strncmp(line,"+SITE/ID",8)==0) section = 1;
			else if (strncmp(line,"+SOLUTION/ESTIMATE",18)==0) {
				section = 2;
				auxN = 0;
				// Reserve memory for detected stations
				stationList->station = malloc(sizeof(TStation)*stationList->n);
			} else section = 0;
		} else if (line[0]!='*' && line[0]!='-') {
			if (section==1) {
				stationList->n++;
			} else if (section==2) {
				getstr(aux,line,len,7,3);
				if (strcmp(aux,"STA")==0) { // It is a station
					properlyRead = 1; // Any station has been found
					getstr(aux,line,len,14,4);
					if (strcmp(prevName,aux)!=0) { // New station
						auxN++;
						strcpy(stationList->station[auxN-1].name,aux);
						strcpy(prevName,aux);
					}
					getstr(aux,line,len,46,23);
					if (line[10]=='X') i=0;
					else if (line[10]=='Y') i=1;
					else if (line[10]=='Z') i=2;
					else error = 1;
					stationList->station[auxN-1].pos[i] = atof(aux);
				}
			}
		}
	}
	
	if (auxN!=stationList->n) error = 1; // Stations number not properly parsed
	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readSINEXFile
 * Description : Read a SINEX station positions file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TStationList  *stationList      O  N/A  Structure to save the station data
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readSINEXFile (char *filename, TStationList *stationList) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftSINEX) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readSINEX (fd, stationList);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readSBASFile
 * Description : Read a SBAS file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TSBASdatabox *SBASdatabox       O  N/A  Structure to save SBAS data
 * double *rinexVersion            O  N/A  Rinex file version
 * TTime *currentepoch             I  N/A  Current epoch
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => File open but reached end of
 *                                               file before getting to current
 *                                               epoch
 *****************************************************************************/
int readSBASFile (char *filename, TSBASdatabox *SBASdatabox, double *rinexVersion, TTime *currentepoch, TOptions  *options) {
	static FILE 			*fd;
	static FILE				*fdlist[18];
	static enum fileType 	sbasfile;
	int						i;
	int 					ret;
	static int				prevday=0;
	static int				initialized=0;
	static int				filesclosed=0;
	static char				*filelist[18];
	
	if(initialized==0) {
		sbasfile=whatFileTypeIs(filename);
		if (sbasfile!=ftRINEXB && sbasfile!=ftSBASEMSMESSAGE) return 0;

		//Check if any SBAS data file has to be written
		if (sbasfile==ftRINEXB) {
			ret=openSBASwritefiles(fdlist,filelist,filename,0,options);
		} else {
			ret=openSBASwritefiles(fdlist,filelist,filename,1,options);
		}

		//If any output file failed to open, exit with errors
		if(ret!=1) return ret;

		//Open SBAS file to be read
		fd = fopen(filename,"rb");
		if(fd==NULL) {
			// File do not exist
			return -1;
		}
		//Allocate memory for sbasblock
		SBASdatabox->sbasblock=malloc(sizeof(TSBASblock));

		initialized=1;
	} else if (SBASdatabox==NULL) {
		//Special call to close all files in case we have reached the end of observation file
		//but we have not closed the SBAS file
		if(fd!=NULL && filesclosed==0) {
			filesclosed=1;
			fclose(fd);
			fd=NULL;
			closefiles(fdlist,18);	//Close all other files
			for(i=0;i<18;i++) {
				if (filelist[i]!=NULL) {
					free(filelist[i]);
					filelist[i]=NULL;
				}
			}
		}
	}

	if(sbasfile==ftRINEXB && fd!=NULL) {
		ret=readRINEXB(fd,fdlist,filelist,SBASdatabox,rinexVersion,&prevday,currentepoch,options);

	} else if(sbasfile==ftSBASEMSMESSAGE && fd!=NULL){
		//If we are going to process data, the first call to this function will be just for opening files and reading header
		if(currentepoch->MJDN==-1 && options->onlyconvertSBAS==0) {
			if (options->workMode != wmSBASPLOTS) return 1;
		}

		//SBAS EMS message file
		*rinexVersion=0; //There is no RINEX version here, we set the value to 0
		ret=readEMS(fd,fdlist,filelist,SBASdatabox,&prevday,currentepoch,options);
	}

	if(fd!=NULL && filesclosed==0) {
		if (feof_function(fd)>0) {
			//Reached end of file
			filesclosed=1;
			fclose(fd);
			fd=NULL;
			closefiles(fdlist,18);	//Close all other files
			if(prevday==0 && options->writePegasusfile==1) {
				//No data was written in the RINEX H file for the previous day
				//But we have generated one with the header. We need to erase it.
				remove(filelist[fdEPHEMERISPREVDAY]);
			}
			for(i=0;i<18;i++) {
				free(filelist[i]);
				filelist[i]=NULL;
			}
		}
	} else if (fd==NULL) {
		//Reached end of file and files are already closed.
		return -2;
	}

	return ret;
}

/*****************************************************************************
 * Name        : readRINEXB
 * Description : Read a RINEX B file from a file descriptor
 *                and convert it to another SBAS data file (if necessary)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * char **filelist                 I  N/A  List of filenames for writing data
 * TSBASdatabox *SBASdatabox       O  N/A  Structure to save SBAS data
 * double *rinexVersion            O  N/A  Rinex file version
 * int *prevday                    O  N/A  Indicates if a RINEX H file from the
 *                                         previous day has been written
 * TTime *currentepoch             I  N/A  Current epoch
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => Properly read
 *                                         0  => Error
 *                                         -2 => Reached end of file before
 *                                               getting to current epoch
 *****************************************************************************/
int readRINEXB (FILE *fd, FILE **fdlist, char **filelist, TSBASdatabox *SBASdatabox, double *rinexVersion, int *prevday, TTime *currentepoch, TOptions  *options) {
	char           	line[MAX_INPUT_LINE];
	char           	aux[100];
	char			hexstring[300];
	char			binarystring[2400];
	unsigned char  	binarymessage[33];
	unsigned char	preamble;
	int            	len = 0;
	int            	error = 0;
	static int     	properlyRead = 0;
	static int     	readingHeader = 1;
	static int		writingHeader = 1;
	static int		bufferlen=0;
	int				GEOpos;
	int				GEOPRN;
	int				freeblock=1;
	int				numberofdatalines;
	int				numberofcolumns;
	int				numberofbadmessages=0;
	int            	i,j,m;
	int				decoderesult = 1;
	int				convergencetime;
	double			timediff;
	double			seconds;
	int				numMsgLost;
	int            	row=0;
	int				endmessage=0;
	int 			decodedmessagetype=0;
	int				messagesmissing=0;
	int				validpreamble;
	//int			reachedcurrentepoch=-1;
	int				MessageAheadCurrentEpoch=0;
	int				invalidDate=0;
	static int		firstdatalineMJDN=-1;
	static int		totalmsgmissing=0;
	static int		nummsgmissingdetected=0;
	static int		numfilelines=0;
	static int		writefiles=0;
	static int		prevnumMsgMissing[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	struct tm    	tm;
	static int		MsgMissingCleared[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static TTime	msgtime[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static TTime	prevmsgtime[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static int		initialized=0;
	static char		bufferstring[MAX_INPUT_LINE];
	TSBASblock  	*sbasblock;
	double			CurrentPos;
	struct stat 	filestat;	//This is to get the file size
	double			filesize;
	double			CurrentPercentage;
	double			PreviousPercentage=-1;

	sbasblock=SBASdatabox->sbasblock;

	if(initialized==0) {
		initialized=1;
		bufferstring[0]='\0';
		for(i=0;i<NUMPOSFREQSBASMSG;i++) {
			for(j=0;j<MAX_SBAS_PRN;j++) {
				prevmsgtime[i][j].MJDN=msgtime[i][j].MJDN=-1;
				prevmsgtime[i][j].SoD=msgtime[i][j].SoD=-1.;
				MsgMissingCleared[i][j]=0;
				prevnumMsgMissing[i][j]=0;
			}
		}
		//If writefiles is greater than 0, means that one file type has to be written
		writefiles=options->writeRinexBfile+options->writeEMSfile+options->writePegasusfile;

		if (printProgressConvert==1) {
			CurrentPos=0;
			fstat(fileno(fd), &filestat);
			filesize = (double)filestat.st_size;
			//Print position 0 as the percentage will be update every 3 lines read
			if (options->ProgressEndCharac=='\r') {
				//Printing to a terminal
				fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",0.0,"",options->ProgressEndCharac);
				#if defined (__WIN32__)
					//In Windows, cursor is not disabled
					fflush_function(options->terminalStream);
				#endif
			}
		}
	}

	//Initialize SBASdatabox->bufferlines
	for(i=0;i<MAX_LINES_BUFFERED_SBAS_MESSAGES;i++) {
		SBASdatabox->bufferlines[i][0]='\0';
		SBASdatabox->bufferlineslen[i]=0;
	}

	//Check for buffered line
	if (bufferstring[0]!='\0') {
		//There is a buffered line
		strcpy(line,bufferstring);
		bufferstring[0]='\0';
		len=bufferlen;
		bufferlen=0;
		numfilelines--;
		CurrentPos -= (double)len;
		if (len<60) line[60]='\0';	//This is to make len initialized in position 60 when checking if new header, as data lines are smaller than 60 and therefore it would compare with unitialized data
	} else {
		if (getL(line,&len,fd)==-1) return -1;
		if (len<60) line[60]='\0';	//This is to make len initialized in position 60 when checking if new header, as data lines are smaller than 60 and therefore it would compare with unitialized data
	} 

	do {
		numfilelines++;
		CurrentPos += (double)len;
		if (len<2) continue; //Skip blank lines

		//Alloc memory only when TSBASblock has been freed (once every time a message has been read)
		if(freeblock==1) {
			initSBASblock (sbasblock);
		}

		if (readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,len,0,9);
				*rinexVersion = atof(aux);
				if ((int)*rinexVersion>2) {return 0;} 		//Version check
			} else if (strncmp(&line[60],"REC INDEX/TYPE/VERS",19)==0) {
				SBASdatabox->SBASdata[0].numreceivers=SBASdatabox->SBASdata[0].numreceivers+1;	//Number of receivers
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
				properlyRead = 1;
				//If we are going to process data, the first call to this function will be just for opening files and reading header
				if(currentepoch->MJDN==-1 && options->onlyconvertSBAS==0 && options->SBAScorrections<SBASMaps1freqUsed) {
					return 1;
				}
			}
		} else {
			//Check first if there is another header line. Skip new header lines
			//If a RINEXB, EMS or Pegasus file is being written, header will just be written once
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,len,0,9);
				*rinexVersion = atof(aux);
				if ((int)*rinexVersion>2) {return 0;} 		//Version check
				row=0;
				while(strncmp(&line[60],"END OF HEADER",13)!=0) {
					if(getL(line,&len,fd)==-1) {
						return -2;
					} else if (strncmp(&line[60],"REC INDEX/TYPE/VERS",19)==0) {
						SBASdatabox->SBASdata[0].numreceivers=SBASdatabox->SBASdata[0].numreceivers+1;	//Number of receivers
					}
				}
				continue;
			//Data lines
			} else if ((int)*rinexVersion==2) {
				if (row==0) {

					getstr(aux,line,len,0,3);
					sbasblock->PRN = atoi(aux);		//PRN
					if (sbasblock->PRN<=0||sbasblock->PRN>=MAX_SBAS_PRN) {
						sprintf(messagestr,"Invalid PRN number '%s' in line number %d in RINEX-B file",aux,numfilelines);
						printError(messagestr,options);
					}
					invalidDate=0;
					getstr(aux,line,len,4,2);
					tm.tm_year = atoi(aux);			//Year
					if (tm.tm_year<=0) invalidDate=1;
					else if (tm.tm_year <= 70) tm.tm_year += 100;					
					getstr(aux,line,len,7,2);
					tm.tm_mon  = atoi(aux);			//Month
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,line,len,10,2);
					tm.tm_mday = atoi(aux);			//Day
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,line,len,13,2);
					tm.tm_hour = atoi(aux);			//Hour
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,line,len,16,2);
					tm.tm_min  = atoi(aux);			//Minute
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,line,len,18,5);
					tm.tm_sec  = atoi(aux);       		//Seconds,in time of reception of first bit 
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
					if (invalidDate==1) {
						sprintf(messagestr,"Invalid date '%.23s' in line number %d in RINEX-B file",line,numfilelines);
						printError(messagestr,options);
					}


					sbasblock->t.MJDN = MJDN(&tm);
					sbasblock->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + (double)(tm.tm_sec) + options->SBASmsgFlightTime + SBASMSGDURATION;	//Seconds in time of applicability (1 second later)

					if(sbasblock->t.SoD>=86400.) {
						//After adding 1 one second, we have gone to the next day
						sbasblock->t.MJDN=sbasblock->t.MJDN+1;
						sbasblock->t.SoD=sbasblock->t.SoD-86400.;
					}

					//Some RINEX-B files do not provide the frequency, datalength, receiverindex and source identifier,
					//even though the RINEX-B standard states it
					if (len>=45) {
						sbasblock->bandflag=line[25];				//Band flag
						getstr(aux,line,len,26,1);
						sbasblock->frequency=atoi(aux);				//Frequency number

						switch(sbasblock->frequency) {
							case 1:
								sbasblock->frequencyPos=SBAS1FFREQPOS;
								break;
							case 5:
								sbasblock->frequencyPos=SBASDFMCFREQPOS;
								break;
							default:
								sbasblock->frequencyPos=UNKNOWNFREQPOS;
								break;
						}
						getstr(aux,line,len,30,3);
						sbasblock->halfdatalength=atoi(aux);
						sbasblock->datalength=sbasblock->halfdatalength*2;	//Data message length  (in RINEX-B is number of pair of bytes)
						getstr(aux,line,len,36,3);
						sbasblock->receiverindex=atoi(aux);			//Receiver index
						getstr(aux,line,len,42,3);
						strcpy(sbasblock->sourceidentifier,aux); 	//Source identifier
					}

					if(firstdatalineMJDN==-1) {
						//Save the MJDN of the first line of data
						firstdatalineMJDN=sbasblock->t.MJDN;

						//If we are in SBAS plots mode, we need to gather the current day from the SBAS input data (only the first time we enter here)
						//SBAS plots will be computed for the current day from second 0 to second 86399 (all the day), but in order to have SBAS corrections
						//in memory at the start of the day, the file should have messages from the final part from the previous day (typically one hour)
						//gLAB will check the first line of data, if it is greater than hour 22 (this is an arbitrary threshold), we will assume that the file
						//is from the next day and set the current time to the next day and second. Otherwise, if it is at the beginning of the day, time will be set
						//at the same time as the one given in the message read.
						if (options->SBAScorrections>=SBASMaps1freqUsed) {
							if(sbasblock->t.SoD>=79200.) { //79200 seconds is hour 22, minute 0, second 0
								currentepoch->MJDN=sbasblock->t.MJDN+1;
								currentepoch->SoD=0.;
								convergencetime=86400-(int)(sbasblock->t.SoD-1.); //The -1. is to take out the second added to convert to time of applicability
								if (convergencetime%3600==0) {
									sprintf(messagestr,"Detected %d hour%s of convergence time in SBAS data file",convergencetime/3600,convergencetime/3600==1?"":"s");
								} else if (convergencetime>3600) {
									if (convergencetime%60==0) {
										sprintf(messagestr,"Detected 1 hour and %d minute%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s");
									} else {									
										sprintf(messagestr,"Detected 1 hour %d minute%s and %d second%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s",convergencetime%60,convergencetime%60==1?"":"s");
									}
								} else {
									if (convergencetime%60==0) {
										sprintf(messagestr,"Detected %d minute%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s");
									} else {									
										sprintf(messagestr,"Detected %d minute%s and %d second%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s",convergencetime%60,convergencetime%60==1?"":"s");
									}
								}
								printInfo(messagestr,options);
								if (convergencetime<900) {
									sprintf(messagestr,"WARNING Convergence time in SBAS data file may not be long enough. It is recommended to have at least 15 minutes of convergence time in SBAS data file");
									printInfo(messagestr,options);
								}
							} else {
								currentepoch->MJDN=sbasblock->t.MJDN;
								currentepoch->SoD=sbasblock->t.SoD;
								sprintf(messagestr,"WARNING No convergence time detected in SBAS data file. There should be at least 15 minutes of data from the previous day in the SBAS data file");
								printInfo(messagestr,options);
							}
						}
					}

					if (sbasblock->t.MJDN>currentepoch->MJDN || (currentepoch->MJDN==sbasblock->t.MJDN && (sbasblock->t.SoD-currentepoch->SoD)>DIFFEQTHRESHOLD)) {
						//The time of applicability of the current message is ahead of the current epoch.
						MessageAheadCurrentEpoch=1;
					}

					//Save current and previous message time of messages to check time between them (only if the GEO is not unselected)
					if(options->GEOPRNunsel[sbasblock->PRN]==0) {

						if(currentepoch->MJDN>=0) {
							//Only check missed messages if we are not only converting SBAS files and the message corresponds to the frequency we are using
							if (MessageAheadCurrentEpoch==0 /*&& sbasblock->frequencyPos==options->SBASFreqPosToProcess*/) {
								//Only update previous message epoch if current message read is usable
								if (prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN].MJDN==-1) {
									//On first message read, copy to previous message time the current epoch
									if (prevmsgtime[sbasblock->frequencyPos][0].MJDN==-1) {
										memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&sbasblock->t,sizeof(TTime));
									} else {
										memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&msgtime[sbasblock->frequencyPos][0],sizeof(TTime));
									}
									memcpy(&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN],&sbasblock->t,sizeof(TTime));
								} else {
									memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&msgtime[sbasblock->frequencyPos][0],sizeof(TTime));
									memcpy(&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN],&msgtime[sbasblock->frequencyPos][sbasblock->PRN],sizeof(TTime));
								}

								memcpy(&msgtime[sbasblock->frequencyPos][0],&sbasblock->t,sizeof(TTime));
								memcpy(&msgtime[sbasblock->frequencyPos][sbasblock->PRN],&sbasblock->t,sizeof(TTime));
							
								//Check time between current epoch and last message received for all GEO
								numMsgLost=(int)(tdiff(&msgtime[sbasblock->frequencyPos][0],&prevmsgtime[sbasblock->frequencyPos][0])+.00005)-1;

								if(numMsgLost>=1) {
									//SBAS messages are sent every second. If there is no data to send, we will receive type 62 or 63 messages to provide continuity of signal
									SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]+=numMsgLost;
									if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]>=4 && MsgMissingCleared[sbasblock->frequencyPos][0]==0) {
										//More than 4 messages missed and we have not cleared data
										SBASMissingMessageClearData(0,sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
										MsgMissingCleared[sbasblock->frequencyPos][0]=1;
									}
								} else {
									//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
									SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]=0;
									MsgMissingCleared[sbasblock->frequencyPos][0]=0;
								}

								//Check time between current epoch and last message received for current GEO
								numMsgLost=(int)(tdiff(&msgtime[sbasblock->frequencyPos][sbasblock->PRN],&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN])+.00005)-1;
								if(numMsgLost>=1) {
									if ( (tdiff(currentepoch,&msgtime[sbasblock->frequencyPos][sbasblock->PRN])-options->SBASmsg1MinusFlightTime)>DIFFEQTHRESHOLD) {
										SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]+=numMsgLost-prevnumMsgMissing[sbasblock->frequencyPos][sbasblock->PRN];
										//Print Info message when a SBAS message is missing, except when last message received is
										//the last one we have to read for the current epoch, due to this message will be shown
										//in the missing message check at the end of this function.
										//It has to be considered that this check of missing messages is for the case when for example, the observation file
										//has a data rate of 30 seconds, and there has been a data gap in between this 30 seconds
										if (options->workMode == wmDOPROCESSING) {
											if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]==1) {
												sprintf(messagestr,"SBAS message missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (1 missing message)",sbasblock->PRN,sbasblock->frequency,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime + SBASMSGDURATION);
											} else if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>1) {
												sprintf(messagestr,"SBAS messages missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",sbasblock->PRN,sbasblock->frequency,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime + SBASMSGDURATION,SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]);
											}
											printInfo(messagestr,options);
										}
										//The prevnumMsgMissing is just for the case when there are several messages missing between epochs (typically for 30s second rate files)
										//In this case, when computing the number of messages missed, after reaching the previous epoch and entering this function again, the first
										//message read vs the last one will be the hole gap (for example 21 messages missing), but the first 20 were alredy counted on the previous call
										//to this function, so they will be counted twice. prevnumMsgMissing variable stores the last number of messages missing 
										prevnumMsgMissing[sbasblock->frequencyPos][sbasblock->PRN]=0;
									}
									if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>=4 && MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]==0) {
										//More than 4 messages missed and we have not cleared data
										if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) { //This is for the case that all received messages were wrong, so no data was saved
											SBASMissingMessageClearData(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
										}
										MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]=1;
									}
								}
								//If we had a gap greater than 4 messages, set first message received to current message epoch minus 1 minute. 
								//This is to set the GEO in acqusition time (except for the current GEO, so the condition of acquisition does not block switching GEO)
								if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>=4) {
									GEOpos=SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN];
									if (options->GEOindex>=0 && options->GEOindex!=GEOpos) {
										memcpy(&SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos],&sbasblock->t,sizeof(TTime));
										SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos]=tdadd(&SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos],-60.);
									}
								}
								//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
								SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]=0;
								MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]=0;
								
							} //End if (MessageAheadCurrentEpoch==0)
						}//End if(currentepoch->MJDN>=0) 
					} //End if(options->GEOPRNunsel[sbasblock->PRN]==0)


					if(currentepoch->MJDN>=0) {
						//If it is not -1, means that we read until we reach the current epoch
						if(MessageAheadCurrentEpoch==1) {
							//The time of applicability of the current message is ahead of the current epoch.
							//Stop reading, save the current line (if we have not reached end of file) and exit function
							if(feof_function(fd)==0) {
								//Copy line to buffer, so it is read in the next function call
								strcpy(bufferstring,line);
								bufferlen=len;
							}
							break;
						}
					}

					//Compute the number of data lines (there are 18 bytes of message per line)
					numberofdatalines=(int)sbasblock->halfdatalength/18;
					if(sbasblock->halfdatalength%18!=0) numberofdatalines++;

					row++;
					endmessage=0;
					freeblock=0;
				} else {
					if (row==1) {
						getstr(aux,line,len,1,2);
						sbasblock->messagetype=atoi(aux);	//Message type
					}

					//Compute the number of records (columns) in the current line (normally the last one is not full)
					if(row==numberofdatalines) {
						numberofcolumns=(sbasblock->halfdatalength)%18;
					} else {
						numberofcolumns=18;
					}

					//Read data
					for(i=0;i<numberofcolumns;i++) {
						getstr(&hexstring[18*2*(row-1)+2*i],line,len,7+3*i,2);
					}
					row++;
			
					//All data has been read for a given message
					if(row==numberofdatalines+1) {
						if (printProgressConvert==1) {
							CurrentPercentage=100.*CurrentPos/filesize;
							if ((CurrentPercentage-PreviousPercentage)>=0.1) { //This is to avoid to many prints when percentages changed less than 0.1
								if (options->ProgressEndCharac=='\r') {
									//Printing to a terminal
									fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
									fflush_function(options->terminalStream);
								} else {
									//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
									if ((int)CurrentPercentage!=(int)PreviousPercentage) {
										fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
										fflush_function(options->terminalStream);
									}
								}
								PreviousPercentage=CurrentPercentage;
							}
						}
						//Convert the hexadecimal string to a binary string (1 bit per byte)
						strhextostrbin(hexstring,sbasblock->datalength,binarystring);

						//Convert the binary string (one bit per byte) to one string where each bit is one value of the message
						strbintobinstr(binarystring,sbasblock->datalength*4,binarymessage,sizeof(binarymessage));	

						//Read preable to uniquely identify message frequency
						preamble=binarymessage[0];
						validpreamble=readSBASmessagePreamble(&preamble,sbasblock);

						//Decode message
						decoderesult=readSBASmessage(binarystring,binarymessage,preamble,validpreamble,&decodedmessagetype,sbasblock,&messagesmissing,options);
						if(messagesmissing!=0) {
							//Increase counter for missing messages
							totalmsgmissing+=messagesmissing;
							nummsgmissingdetected++;
							//Increase size of vectors for logging missed messages
							SBASdatabox->numlinesmissing=realloc(SBASdatabox->numlinesmissing,sizeof(int)*nummsgmissingdetected);
							SBASdatabox->missingmessagesvector=realloc(SBASdatabox->missingmessagesvector,sizeof(int)*nummsgmissingdetected);
							//Save the line where missing message has been detected and what number has been lost
							SBASdatabox->numlinesmissing[nummsgmissingdetected-1]=numfilelines-2;
							SBASdatabox->missingmessagesvector[nummsgmissingdetected-1]=messagesmissing;
						}

						if(decoderesult<0) {
							//Error decoding message. Update failed messages only if GEO is not unselected
							numberofbadmessages++;	
							if(options->GEOPRNunsel[sbasblock->PRN]==0) {
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]+=1;
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]+=1;
							}
							//Print Info message when a SBAS message is missing only for GEO in use
							if (currentepoch->MJDN>=0) {
								if (options->workMode == wmDOPROCESSING) {
									if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]==1) {
										sprintf(messagestr,"Invalid SBAS message for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f  (1 invalid message)",sbasblock->PRN,sbasblock->frequency,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime + SBASMSGDURATION);
									} else {
										sprintf(messagestr,"Invalid SBAS messages for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive invalid messages)",sbasblock->PRN,sbasblock->frequency,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime + SBASMSGDURATION,SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]);
									}								
									printInfo(messagestr,options);
								}
								//When 4 consecutive invalid messages arrive, the GEO has to be disabled for ranging and all fast corrections must timeout
								if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]==4) {
									SBASErrorMessageTimeoutFastCorr(0,sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
								}
								if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]==4) {
									if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
										SBASErrorMessageTimeoutFastCorr(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
									}
								}
							}
						} else if(currentepoch->MJDN>=0){
							//Message decoded correctly. Update SBAS data only if we are processing data and the GEO is not unselected
							if(options->GEOPRNunsel[sbasblock->PRN]==0) {
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]=0;
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]=0;
								//Message decoded correctly. Update SBAS data only if we are processing data
								if(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]==-1) {
									//Current PRN not found before. 
									//Add 1 to the number of satellites
									SBASdatabox->SBASdata[0].numSBASsatellites=SBASdatabox->SBASdata[0].numSBASsatellites+1;
									//Add a slot in SBASdata structure for this PRN
									SBASdatabox->SBASdata=realloc(SBASdatabox->SBASdata,sizeof(TSBASdata)*(SBASdatabox->SBASdata[0].numSBASsatellites+1));
									//Initialise the new slot
									initSBASdata(SBASdatabox->SBASdata,SBASdatabox->SBASdata[0].numSBASsatellites);
									//Save the position of the new satellite
									SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]=SBASdatabox->SBASdata[0].numSBASsatellites;
									//Save the PRN of the new satellite
									SBASdatabox->SBASdata[SBASdatabox->SBASdata[0].numSBASsatellites].PRN=sbasblock->PRN;
								}

								updateSBASdata(SBASdatabox,SBASdatabox->SBASdata,sbasblock,options);
							}
						}
						row=0;
						endmessage=1;
						freeblock=1;
					}
				} //End else row==0
			} //End if rinexversion==2
		} //End else if readingheader

		//Print SBAS data file if necessary
		if(writefiles) {
			//Copy current line to buffer
			if(writingHeader==1) {
				strcpy(SBASdatabox->bufferlines[row],line);
				SBASdatabox->bufferlineslen[row]=len;
			} else if (endmessage==1) {
				strcpy(SBASdatabox->bufferlines[numberofdatalines],line); //We cannot use row here because when finishing a message row value is set back to 0
				SBASdatabox->bufferlineslen[numberofdatalines]=len;
			} else {
				strcpy(SBASdatabox->bufferlines[row-1],line);
				SBASdatabox->bufferlineslen[row-1]=len;
			}

			//Call function to write to files. It must be called only when we are writing header lines or when we have read a full message
			if(writingHeader==1) {
				writeSBASfiles(fdlist, fd, filelist, SBASdatabox->bufferlines, SBASdatabox->bufferlineslen, 1, writingHeader, 0, decoderesult, decodedmessagetype, prevday, sbasblock, options);
			} else if (endmessage==1) {
				writeSBASfiles(fdlist, fd, filelist, SBASdatabox->bufferlines, SBASdatabox->bufferlineslen, numberofdatalines+1, writingHeader, 0, decoderesult, decodedmessagetype, prevday, sbasblock, options);

			}

			if(readingHeader==0) writingHeader=0;	

		}

		if(freeblock==1) {	//Free sbasblock only when necessary
			//Handle special events if it is not the current epoch of the RINEX observation file
			if(currentepoch->MJDN>=0 && tdiff(currentepoch,&sbasblock->t)>SBASMSGDURATION) {
				SBAShandlespecialevents(currentepoch,SBASdatabox->SBASdata,options);
			}
		}
	} while(getL(line,&len,fd)!=-1);

    //Check for missing messages or error messages in all GEOs 
    //It can occur the case that we have not received any message for a tracked  PRN in the current interval read,
    //therefore it is necessary to check if there has been a data gap
    for(m=1;m<=SBASdatabox->SBASdata[0].numSBASsatellites;m++) {
		GEOPRN=SBASdatabox->SBASdata[m].PRN;
		for(i=0;i<(NUMPOSFREQSBASMSG-1);i++) { //Skip last frequency which is for not known frequencies
			//Only check satellites that have not been cleared
			if (msgtime[i][GEOPRN].MJDN==-1) {
				numMsgLost=0;
			} else {
				timediff=tdiff(currentepoch,&msgtime[i][GEOPRN]);
				numMsgLost=0;
				if (timediff>=1.) {
				numMsgLost=(int)(timediff);
				}
			}
			//The numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN] is to avoid printing the missing message due when we read the first message after a gap,
			//the prevmsgtime has not still been updated until the next message read
			if (prevmsgtime[i][GEOPRN].MJDN!=-1 && numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN]) {
				SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN]=numMsgLost;
				if(numMsgLost>=4) {
					//Print Info message when a SBAS message is missing only for GEO in use
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS messages missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds,numMsgLost);
						printInfo(messagestr,options);
					}
					if (MsgMissingCleared[i][GEOPRN]==0) {
						SBASMissingMessageClearData(m,i,currentepoch,SBASdatabox->SBASdata,options);
						MsgMissingCleared[i][GEOPRN]=1;
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else if(numMsgLost>=2) {
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS messages missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds,numMsgLost);
						printInfo(messagestr,options);
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else if(numMsgLost==1) {
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS message missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (1 missing message)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds);
						printInfo(messagestr,options);
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else {
					prevnumMsgMissing[i][GEOPRN]=0;
				}
			}
		}
    }

	if(feof_function(fd)>0) {
		//Print message decoding summary
		if(writefiles) {
			writeSBASdecodesummary(fdlist, fd, filelist[fdLOGFILE], numberofbadmessages, totalmsgmissing, nummsgmissingdetected, SBASdatabox->numlinesmissing, SBASdatabox->missingmessagesvector, options);
		}
	} 

	return (properlyRead && !error); // properly read AND no error
}

/*****************************************************************************
 * Name        : readEMS
 * Description : Read a EMS file from a file descriptor
 *               and convert it to another SBAS data file (if necessary)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * FILE  **fdlist                  I  N/A  Vector of file descriptors for writing data
 * char **filelist                 I  N/A  List of filenames for writing data
 * TSBASdatabox  *SBASdatabox      O  N/A  Structure to save SBAS data
 * int *prevday					   O  N/A  Indicates if a RINEX H file from the
 *                                         previous day has been written
 * TTime *currentepoch			   I  N/A  Current epoch
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => Properly read
 *                                          0 => Error
 *                                         -2 => Reached end of file before
 *                                               getting to current epoch
 *****************************************************************************/
int readEMS (FILE *fd, FILE **fdlist, char **filelist, TSBASdatabox *SBASdatabox, int *prevday, TTime *currentepoch, TOptions  *options) {
	char            	line[MAX_INPUT_LINE];
	char            	aux[100];
	char            	hexstring[300];
	char            	binarystring[2400];
	char				freqText[100];
	unsigned char  		binarymessage[33];
	unsigned char		preamble;
	int             	len = 0;
	int             	i,j,m;
	int					GEOpos;
	int					GEOPRN;
	int             	decoderesult = 1;
	double				timediff;
	double				seconds;
	int					numMsgLost;
	int 				decodedmessagetype=0;
	int             	messagesmissing=0;
	int					MessageAheadCurrentEpoch=0;
	int					convergencetime;
	int					validpreamble;
	int					invalidDate=0;
	static int			firstdatalineMJDN=-1;
	static int			totalmsgmissing=0;
	static int      	numberofbadmessages=0;
	static int			numfilelines=0;
	static int			nummsgmissingdetected=0;
	static int         	writefiles=0;
	static int			bufferlen=0;
	static int			prevnumMsgMissing[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	struct tm       	tm;
	static int			MsgMissingCleared[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static TTime		msgtime[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static TTime		prevmsgtime[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];
	static int			initialized=0;
	static char			bufferstring[MAX_INPUT_LINE];
	TSBASblock  	   	*sbasblock;
	double				CurrentPos;
	struct stat	 		filestat;	//This is to get the file size
	double				filesize;
	double				CurrentPercentage;
	double				PreviousPercentage=-1;

	sbasblock=SBASdatabox->sbasblock;

	if(initialized==0) {
		initialized=1;
		bufferstring[0]='\0';		
		for(i=0;i<NUMPOSFREQSBASMSG;i++) {
			for(j=0;j<MAX_SBAS_PRN;j++) {
				prevmsgtime[i][j].MJDN=msgtime[i][j].MJDN=-1;
				prevmsgtime[i][j].SoD=msgtime[i][j].SoD=-1.;
				MsgMissingCleared[i][j]=0;
				prevnumMsgMissing[i][j]=0;
			}
		}
		//If writefiles is greater than 0, means that one file type has to be written
		writefiles=options->writeRinexBfile+options->writeEMSfile+options->writePegasusfile;

		if (printProgressConvert==1) {
			CurrentPos=0;
			fstat(fileno(fd), &filestat);
			filesize = (double)filestat.st_size;
			//Print position 0 
			if (options->ProgressEndCharac=='\r') {
				//Printing to a terminal
				fprintf(options->terminalStream,"Percentage converted: %5.1f%%%60s%c",0.0,"",options->ProgressEndCharac);
				#if defined (__WIN32__)
					//In Windows, cursor is not disabled
					fflush_function(options->terminalStream);
				#endif
			}
		}
	}

	//Initialize SBASdatabox->bufferlines
	for(i=0;i<1;i++) {
		SBASdatabox->bufferlines[i][0]='\0';
		SBASdatabox->bufferlineslen[i]=0;
	}

	//Check for buffered line
	if (bufferstring[0]!='\0') {
		//There is a buffered line
		strcpy(line,bufferstring);
		len=bufferlen;
		bufferlen=0;
		numfilelines--;
		CurrentPos -= (double)len;
	} else {
		if (getL(line,&len,fd)==-1) return -1;
	} 


	do {
		numfilelines++;
		CurrentPos += (double)len;

		if (len<2) continue; //Skip blank lines

		initSBASblock(sbasblock);

		getstr(aux,line,len,0,3);
		sbasblock->PRN = atoi(aux);		//PRN
		if (sbasblock->PRN<=0||sbasblock->PRN>=MAX_SBAS_PRN) {
			sprintf(messagestr,"Invalid PRN number '%s' in line %d in EMS file",aux,numfilelines);
			printError(messagestr,options);
		}
		invalidDate=0;
		getstr(aux,line,len,4,2);
		tm.tm_year = atoi(aux);			//Year
		if (tm.tm_year<=0) invalidDate=1;
		else if (tm.tm_year <= 70) tm.tm_year += 100;
		getstr(aux,line,len,7,2);
		tm.tm_mon  = atoi(aux);			//Month
		if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
		tm.tm_mon  -= 1;
		getstr(aux,line,len,10,2);
		tm.tm_mday = atoi(aux);			//Day
		if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
		getstr(aux,line,len,13,2);
		tm.tm_hour = atoi(aux);			//Hour
		if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
		getstr(aux,line,len,16,2);
		tm.tm_min  = atoi(aux);			//Minute
		if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
		getstr(aux,line,len,19,2);
		tm.tm_sec  = atoi(aux);       	//Seconds,in time of applicability 
		if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1; //Seconds can have value 60 when a leap second is inserted
		if (invalidDate==1) {
			sprintf(messagestr,"Invalid date '%.23s' in line %d in EMS file",line,numfilelines);
			printError(messagestr,options);
		}
		getstr(aux,line,len,30,2);



		sbasblock->t.MJDN = MJDN(&tm);
		sbasblock->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + (double)(tm.tm_sec) + options->SBASmsgFlightTime;	//Seconds in time of applicability (0.1 seconds corresponds to travel time)

		//QZSS extension: EMS files with GPS,GLONASS,Galileo,BeiDou,QZSS navigation messages
		if (sbasblock->PRN<100) {
			//GPS,GLONASS,Galileo,BeiDou navigation messages. Skip line
			continue;
		} else if (sbasblock->PRN>=MINQZSSOBSPRN && sbasblock->PRN<=MAXQZSSOBSPRN) {
			//QZSS navigation messages. Skip line
			continue;
		} else {
			if(len<88 && line[0]!='\n') return 0;	//Data line too short (and are not blank lines)
		}

		if (line[21]=='.') {
			//New EMS format, seconds with 6 decimal places (plus the decimal dot), plus the band flag, frequency and message length
			//Band flag
			sbasblock->bandflag=line[29];

			//Frequency number
			getstr(aux,line,len,30,1);
			sbasblock->frequency=atoi(aux);

			getstr(aux,line,len,37,2);
			sbasblock->messagetype=atoi(aux);	//Message type

			//Message length (with padding), computed using characters read until end of line
			sbasblock->datalength=len-40;

			getstr(hexstring,line,len,40,sbasblock->datalength);
		} else {
			getstr(aux,line,len,22,2);
			sbasblock->messagetype=atoi(aux);	//Message type

			//Set a default invalid frequency number. If frequency cannot be determined by the preambled, it will be unchanged. If successfully detect, it will be changed to the right value
			sbasblock->frequency=2;

			if(sbasblock->messagetype<10) {	
				if (line[24]==' ') {
					//QZSS extension: message type always has two characters instead of just one (formatted with a extra blank space)

					//Message length (with padding), computed using characters read until end of line
					sbasblock->datalength=len-25;

					getstr(hexstring,line,len,25,sbasblock->datalength);
				} else {
					//Message length (with padding), computed using characters read until end of line
					sbasblock->datalength=len-24;

					getstr(hexstring,line,len,24,sbasblock->datalength);
				}
			} else {
				//Message length (with padding), computed using characters read until end of line
				sbasblock->datalength=len-25;

				getstr(hexstring,line,len,25,sbasblock->datalength);
			}
		}

		//Convert the hexadecimal string to a binary string (1 bit per byte)
		strhextostrbin(hexstring,sbasblock->datalength, binarystring);

		//Convert the binary string (one bit per byte) to one string where each bit is one value of the message
		strbintobinstr(binarystring,sbasblock->datalength*4,binarymessage,sizeof(binarymessage));	


		//Read preable to uniquely identify message frequency
		preamble=binarymessage[0];
		validpreamble=readSBASmessagePreamble(&preamble,sbasblock);


		if(sbasblock->t.SoD>=86400.) {
			//After adding 0.1 seconds, we have gone to the next day
			sbasblock->t.MJDN=sbasblock->t.MJDN+1;
			sbasblock->t.SoD=sbasblock->t.SoD-86400.;
		}
					

		if(firstdatalineMJDN==-1) {
			//Save the MJDN of the first line of data
			firstdatalineMJDN=sbasblock->t.MJDN;

			//If we are in SBAS plots mode, we need to gather the current day from the SBAS input data (only the first time we enter here)
			//SBAS plots will be computed for the current day from second 0 to second 86399 (all the day), but in order to have SBAS corrections
			//in memory at the start of the day, the file should have messages from the final part from the previous day (typically one hour)
			//gLAB will check the first line of data, if it is greater than hour 22 (this is an arbitrary threshold), we will assume that the file
			//is from the next day and set the current time to the next day and second. Otherwise, if it is at the beginning of the day, time will be set
			//at the same time as the one given in the message read.
			if (options->SBAScorrections>=SBASMaps1freqUsed) {
				if(sbasblock->t.SoD>=79200.) { //79200 seconds is hour 22, minute 0, second 0
					currentepoch->MJDN=sbasblock->t.MJDN+1;
					currentepoch->SoD=0;
					convergencetime=86400-(int)(sbasblock->t.SoD);
					if (convergencetime%3600==0) {
						sprintf(messagestr,"Detected %d hour%s of convergence time in SBAS data file",convergencetime/3600,convergencetime/3600==1?"":"s");
					} else if (convergencetime>3600) {
						if (convergencetime%60==0) {
							sprintf(messagestr,"Detected 1 hour and %d minute%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s");
						} else {									
							sprintf(messagestr,"Detected 1 hour %d minute%s and %d second%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s",convergencetime%60,convergencetime%60==1?"":"s");
						}
					} else {
						if (convergencetime%60==0) {
							sprintf(messagestr,"Detected %d minute%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s");
						} else {									
							sprintf(messagestr,"Detected %d minute%s and %d second%s of convergence time in SBAS data file",convergencetime/60,convergencetime/60==1?"":"s",convergencetime%60,convergencetime%60==1?"":"s");
						}
					}
					printInfo(messagestr,options);
					if (convergencetime<900) {
						sprintf(messagestr,"WARNING Convergence time in SBAS data file may not be long enough. It is recommended to have at least 15 minutes of convergence time in SBAS data file");
						printInfo(messagestr,options);
					}
				} else {
					currentepoch->MJDN=sbasblock->t.MJDN;
					currentepoch->SoD=sbasblock->t.SoD;
					sprintf(messagestr,"WARNING No convergence time detected in SBAS data file. There should be at least 15 minutes of data from the previous day in the SBAS data file");
					printInfo(messagestr,options);
				}
			}
		}

		if (sbasblock->t.MJDN>currentepoch->MJDN || (currentepoch->MJDN==sbasblock->t.MJDN && sbasblock->t.SoD>currentepoch->SoD)) {
			//The time of applicability of the current message is ahead of the current epoch.
			MessageAheadCurrentEpoch=1;
		}

		//Save current and previous message time of messages to check time between them (only if the GEO is not unselected)
		if(options->GEOPRNunsel[sbasblock->PRN]==0) {

			if(currentepoch->MJDN>=0) {
				//Only check missed messages if we are not only converting SBAS files and the message corresponds to the frequency we are using
				if (MessageAheadCurrentEpoch==0 /*&& sbasblock->frequencyPos==options->SBASFreqPosToProcess*/) {
					//Only update previous message epoch if current message read is usable
					if (msgtime[sbasblock->frequencyPos][sbasblock->PRN].MJDN==-1) {
						//On first message read, copy to previous message time the current epoch
						if (msgtime[sbasblock->frequencyPos][0].MJDN==-1) {
							memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&sbasblock->t,sizeof(TTime));
						} else {
							memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&msgtime[sbasblock->frequencyPos][0],sizeof(TTime));
						}
						memcpy(&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN],&sbasblock->t,sizeof(TTime));
					} else {
						memcpy(&prevmsgtime[sbasblock->frequencyPos][0],&msgtime[sbasblock->frequencyPos][0],sizeof(TTime));
						memcpy(&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN],&msgtime[sbasblock->frequencyPos][sbasblock->PRN],sizeof(TTime));
					}

					memcpy(&msgtime[sbasblock->frequencyPos][0],&sbasblock->t,sizeof(TTime));
					memcpy(&msgtime[sbasblock->frequencyPos][sbasblock->PRN],&sbasblock->t,sizeof(TTime));
					
					//Check time between current epoch and last message received for all GEO
					numMsgLost=(int)(tdiff(&msgtime[sbasblock->frequencyPos][0],&prevmsgtime[sbasblock->frequencyPos][0])+.00005)-1;
					if(numMsgLost>=1) {
						//SBAS messages are sent every second. If there is no data to send, we will receive type 62 or 63 messages to provide continuity of signal
						SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]+=numMsgLost;
						if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]>=4 && MsgMissingCleared[sbasblock->frequencyPos][0]==0) {
							//More than 4 messages missed and we have not cleared data
							SBASMissingMessageClearData(0,sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
							MsgMissingCleared[sbasblock->frequencyPos][0]=1;
						}
					} else {
						//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
						SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][0]=0;
						MsgMissingCleared[sbasblock->frequencyPos][0]=0;
					}

					//Check time between current epoch and last message received for current GEO
					numMsgLost=(int)(tdiff(&msgtime[sbasblock->frequencyPos][sbasblock->PRN],&prevmsgtime[sbasblock->frequencyPos][sbasblock->PRN])+.00005)-1;
					if(numMsgLost>=1) {
						if ( (tdiff(currentepoch,&msgtime[sbasblock->frequencyPos][sbasblock->PRN])-options->SBASmsg1MinusFlightTime)>DIFFEQTHRESHOLD) {
							SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]+=numMsgLost-prevnumMsgMissing[sbasblock->frequencyPos][sbasblock->PRN];
							//Print Info message when a SBAS message is missing, except when last message received is
							//the last one we have to read for the current epoch, due to this message will be shown
							//in the missing message check at the end of this function.
							//It has to be considered that this check of missing messages is for the case when for example, the observation file
							//has a data rate of 30 seconds, and there has been a data gap in between this 30 seconds
							if (options->workMode == wmDOPROCESSING) {
								if (sbasblock->frequencyPos==UNKNOWNFREQPOS && line[21]!='.') {
									//Unknown frequency and it is not new EMS format, which provides frequency number
									strcpy(freqText,"in unknown frequency");
								} else {
									sprintf(freqText,"and frequency %d",sbasblock->frequency);
								}
								if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]==1) {
									sprintf(messagestr,"SBAS message missing for GEO PRN %3d %s at epoch %17s / %02d:%02d:%05.2f (1 missing message)",sbasblock->PRN,freqText,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime);
								} else if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>1) {
									sprintf(messagestr,"SBAS messages missing for GEO PRN %3d %s at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",sbasblock->PRN,freqText,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime,SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]);
								}
								printInfo(messagestr,options);
							}
							//The prevnumMsgMissing is just for the case when there are several messages missing between epochs (typically for 30s second rate files)
							//In this case, when computing the number of messages missed, after reaching the previous epoch and entering this function again, the first
							//message read vs the last one will be the hole gap (for example 21 messages missing), but the first 20 were alredy counted on the previous call
							//to this function, so they will be counted twice. prevnumMsgMissing variable stores the last number of messages missing 
							prevnumMsgMissing[sbasblock->frequencyPos][sbasblock->PRN]=0;
						}
						if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>=4 && MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]==0) {
							//More than 4 messages missed and we have not cleared data
							if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
								SBASMissingMessageClearData(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
							}
							MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]=1;
						}
					}
					//If we had a gap greater than 4 messages, set first message received to current message epoch minus 1 minute. 
					//This is to set the GEO in acqusition time (except for the current GEO, so the condition of acquisition does not block switching GEO)
					if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]>=4) {
						GEOpos=SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN];
						if (options->GEOindex>=0 && options->GEOindex!=GEOpos) {
							memcpy(&SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos],&sbasblock->t,sizeof(TTime));
							SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos]=tdadd(&SBASdatabox->SBASdata[GEOpos].firstmessage[sbasblock->frequencyPos],-60.);
						}
					}
					//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
					SBASdatabox->SBASdata[0].missed4msg[sbasblock->frequencyPos][sbasblock->PRN]=0;
					MsgMissingCleared[sbasblock->frequencyPos][sbasblock->PRN]=0;
					prevnumMsgMissing[sbasblock->frequencyPos][sbasblock->PRN]=0;

				} //End if (MessageAheadCurrentEpoch==0)
			}//End if(currentepoch->MJDN>=0) 
		} //End if(options->GEOPRNunsel[sbasblock->PRN]==0)

		if(currentepoch->MJDN>=0) {
			//If it is not -1, means that we have to read until we reach the current epoch
			if(MessageAheadCurrentEpoch==1) {
				//The time of applicability of the current message is ahead of the current epoch.
				//Stop reading, save the current line (if we have not reached end of file) and exit function
				if(feof_function(fd)==0) {
					//Copy line to buffer, so it is read in the next function call
					strcpy(bufferstring,line);
					bufferlen=len;
				}
				break;
			}
		}

		if (printProgressConvert==1) {
			CurrentPercentage=100.*CurrentPos/filesize;
			if ((CurrentPercentage-PreviousPercentage)>=0.1) { //This is to avoid to many prints when percentages changed less than 0.1
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Percentage converted: %5.1f%%%60s%c",CurrentPercentage,"",options->ProgressEndCharac);
					//In Windows, cursor is not disabled
					fflush_function(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Percentage converted: %5.1f%%%60s%c",CurrentPercentage,"",options->ProgressEndCharac);
						fflush_function(options->terminalStream);
					}
				}
				PreviousPercentage=CurrentPercentage;
			}
		}

		//Decode message
		decoderesult=readSBASmessage(binarystring,binarymessage,preamble,validpreamble,&decodedmessagetype,sbasblock,&messagesmissing,options);
		if(messagesmissing!=0) {
			//Increase counter for missing messages
			totalmsgmissing+=messagesmissing;
			nummsgmissingdetected++;
			//Increase size of vectors for logging missed messages
			SBASdatabox->numlinesmissing=realloc(SBASdatabox->numlinesmissing,sizeof(int)*nummsgmissingdetected);
			SBASdatabox->missingmessagesvector=realloc(SBASdatabox->missingmessagesvector,sizeof(int)*nummsgmissingdetected);
			//Save the line where missing message has been detected and what number has been lost
			SBASdatabox->numlinesmissing[nummsgmissingdetected-1]=numfilelines;
			SBASdatabox->missingmessagesvector[nummsgmissingdetected-1]=messagesmissing;
		}					

		if(decoderesult<0) {
			//Error decoding message. Update failed messages only if GEO is not unselected
			numberofbadmessages++;
			if(options->GEOPRNunsel[sbasblock->PRN]==0) {
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]+=1; //failed messages for all GEO
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]+=1; //failed messages for a single GEO
			}
			//Print Info message when a SBAS message is missing only for GEO in use
			if (currentepoch->MJDN>=0) {
				if (options->workMode == wmDOPROCESSING) {
					if (sbasblock->frequencyPos==UNKNOWNFREQPOS && line[21]!='.') {
						//Unknown frequency and it is not new EMS format, which provides frequency number
						strcpy(freqText,"in unknown frequency");
					} else {
						sprintf(freqText,"and frequency %d",sbasblock->frequency);
					}
					if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]==1) {
						sprintf(messagestr,"Invalid SBAS message for GEO PRN %3d %s at epoch %17s / %02d:%02d:%05.2f (1 invalid message)",sbasblock->PRN,freqText,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime);
					} else {
						sprintf(messagestr,"Invalid SBAS messages for GEO PRN %3d %s at epoch %17s / %02d:%02d:%05.2f (%d consecutive invalid messages)",sbasblock->PRN,freqText,t2doystr(&msgtime[sbasblock->frequencyPos][sbasblock->PRN]),tm.tm_hour,tm.tm_min,(double)(tm.tm_sec) + options->SBASmsgFlightTime,SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]);
					}
					printInfo(messagestr,options);
				}
				//When 4 consecutive invalid messages arrive, the GEO has to be disabled for ranging and all fast corrections must timeout
				if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]==4) {
					SBASErrorMessageTimeoutFastCorr(0,sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
				}
				if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]==4) {
					if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
						SBASErrorMessageTimeoutFastCorr(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],sbasblock->frequencyPos,currentepoch,SBASdatabox->SBASdata,options);
					}
				}
			}
		} else if(currentepoch->MJDN>=0){
			//Message decoded correctly. Update SBAS data only if we are processing data and the GEO is not unselected
			if(options->GEOPRNunsel[sbasblock->PRN]==0) {
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][0]=0;
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->frequencyPos][sbasblock->PRN]=0;
				if(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]==-1) {
					//Current PRN not found before. 
					//Add 1 to the number of satellites
					SBASdatabox->SBASdata[0].numSBASsatellites=SBASdatabox->SBASdata[0].numSBASsatellites+1;
					//Add a slot in SBASdata structure for this PRN
					SBASdatabox->SBASdata=realloc(SBASdatabox->SBASdata,sizeof(TSBASdata)*(SBASdatabox->SBASdata[0].numSBASsatellites+1));
					//Initialise the new slot
					initSBASdata(SBASdatabox->SBASdata,SBASdatabox->SBASdata[0].numSBASsatellites);
					//Save the position of the new satellite
					SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]=SBASdatabox->SBASdata[0].numSBASsatellites;
					//Save the PRN of the new satellite
					SBASdatabox->SBASdata[SBASdatabox->SBASdata[0].numSBASsatellites].PRN=sbasblock->PRN;
				}
				
				updateSBASdata(SBASdatabox,SBASdatabox->SBASdata,sbasblock,options);
			}
		}


		if(writefiles) {
			//Copy current line to buffer
			strcpy(SBASdatabox->bufferlines[0],line);
			SBASdatabox->bufferlineslen[0]=len;
			//Write message to file
			writeSBASfiles(fdlist, fd, filelist, SBASdatabox->bufferlines, SBASdatabox->bufferlineslen, 1, 0, 1, decoderesult, decodedmessagetype, prevday, sbasblock, options);
		}

		//Handle special events if it is not the current epoch of the RINEX observation file	
		if(currentepoch->MJDN>=0 && tdiff(currentepoch,&sbasblock->t)>SBASMSGDURATION) {
			SBAShandlespecialevents(currentepoch,SBASdatabox->SBASdata,options);
		}
	} while(getL(line,&len,fd)!=-1);

	//Check for missing messages or error messages in all GEOs 
	//It can occur the case that we have not received any message for a tracked  PRN in the current interval read,
	//therefore it is necessary to check if there has been a data gap
    for(m=1;m<=SBASdatabox->SBASdata[0].numSBASsatellites;m++) {
		GEOPRN=SBASdatabox->SBASdata[m].PRN;
		for(i=0;i<(NUMPOSFREQSBASMSG-1);i++) { //Skip last frequency which is for not known frequencies
			//Only check satellites that have not been cleared
			if (msgtime[i][GEOPRN].MJDN==-1) {
				numMsgLost=0;
			} else {
				timediff=tdiff(currentepoch,&msgtime[i][GEOPRN]);
				numMsgLost=0;
				if (timediff>=1.) {
					numMsgLost=(int)(timediff);
				}
			}
			//The numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN] is to avoid printing the missing message due when we read the first message after a gap,
			//the prevmsgtime has not still been updated until the next message read
			if (prevmsgtime[i][GEOPRN].MJDN!=-1 && numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN]) {
				SBASdatabox->SBASdata[0].missed4msg[i][GEOPRN]=numMsgLost;
				if(numMsgLost>=4) {
					//Print Info message when a SBAS message is missing only for GEO in use
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS messages missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds,numMsgLost);
						printInfo(messagestr,options);
					}
					if (MsgMissingCleared[i][GEOPRN]==0) {
						SBASMissingMessageClearData(m,i,currentepoch,SBASdatabox->SBASdata,options);
						MsgMissingCleared[i][GEOPRN]=1;
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else if(numMsgLost>=2) {
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS messages missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (%d consecutive missing messages)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds,numMsgLost);
						printInfo(messagestr,options);
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else if(numMsgLost==1) {
					if (options->workMode == wmDOPROCESSING) {
						t2tmnolocal(currentepoch,&tm,&seconds);
						sprintf(messagestr,"SBAS message missing for GEO PRN %3d and frequency %d at epoch %17s / %02d:%02d:%05.2f (1 missing message)",GEOPRN,SBASfreqPos2freqNum[i],t2doystr(currentepoch),tm.tm_hour,tm.tm_min,seconds);
						printInfo(messagestr,options);
					}
					prevnumMsgMissing[i][GEOPRN]=numMsgLost;
				} else {
					prevnumMsgMissing[i][GEOPRN]=0;
				}
			}
		}
	}
		
	//Print message decoding summary
	if(feof_function(fd)>0) {
		//Print message decoding summary
		if(writefiles) {
			writeSBASdecodesummary(fdlist, fd, filelist[fdLOGFILE], numberofbadmessages, totalmsgmissing, nummsgmissingdetected, SBASdatabox->numlinesmissing, SBASdatabox->missingmessagesvector, options);
		}
	} 

	return 1;
}

/*****************************************************************************
 * Name        : readSBASmessagePreamble
 * Description : Check if there is a valid SBAS message preamble.
 *                It is necessary to read preamble before decoding the message, and
 *                 as the preamble uniquely identifies from what where the message
 *                 was sent from (the preambles are different for L1 and L5)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * unsigned char *preamble         I  N/A  Preamble (first 8 bits of message)
 * TSBASblock  *sbasblock          O  N/A  TSBASblock structure
 * Returned value (int)            O  N/A  Status of function
 *                                          0 => Invalid preamble
 *                                          1 => Valid preamble
 *****************************************************************************/
int readSBASmessagePreamble (unsigned char *preamble, TSBASblock *sbasblock) {

	////Check preamble. Valid preambles are 
	//For SBAS 1F
	//01010011 (0x53) 10011010 (0x9A) 11000110 (0xC6)
	//For SBAS DFMC
	//0101 (0x5) 1100 (0xC) 0110 (0x6) 1001 (0x9) 0011 (0x3) 1010 (0xA)
	//Note that in SBAS 1F there are three preambles with eight bits each (two bytes), in SBAS DFMC there are six preambles with 4 bits each (1 byte)

	switch(sbasblock->messagetype) {
		case SATMASKASIGNMENTS: case CLOCKEPHEMERISCOVARIANCEMATRIXDFMC:
		case OBADDFREIPARAMETERS: case SBASEPHEMERISDFMC: case SBASEPHEMERISCOVARIANCEDFMC:
		case SBASNETWORKTIMEPARAMETERSDFMC: case SBASALMANACSDFMC:
		case SERVICEAREADFMC: case SERVICEAREADFMCTESTBED:
			//All SBAS DFMC messages only. Preamble is only 4 bits, so set last 4 bits to 0
			*preamble&=0xF0;
			break;
		case INTEGRITYINFODFMC34:
			//Integrity SBAS DFMC messages only. Preamble is only 4 bits, so set last 4 bits to 0
			*preamble&=0xF0;
			sbasblock->msg0type=1;
			break;
		case INTEGRITYINFODFMC35:
			//Integrity SBAS DFMC messages only. Preamble is only 4 bits, so set last 4 bits to 0
			*preamble&=0xF0;
			sbasblock->msg0type=2;
			break;
		case INTEGRITYINFODFMC36:
			//Integrity SBAS DFMC messages only. Preamble is only 4 bits, so set last 4 bits to 0
			*preamble&=0xF0;
			sbasblock->msg0type=3;
			break;
		default:
			//For SBAS 1F messages or for both (types 0, 62, and 63), use the 8 bits. For the cases
			//of messages 0, 62 and 63, the possible preamble values in SBAS 1F and SBAS DFMC will
			//never match, so it is safe to check the preamble for both types
			break;
	}
	switch(*preamble) {
		//"01010011","10011010", "11000110"
		case 0x53: case 0x9A: case 0xC6:
			//SBAS 1F preambles.
			sbasblock->frequencyPos=SBAS1FFREQPOS;
			sbasblock->frequency=1;
			return 1;
			break;
		case 0x50: case 0x5F: case 0xC0: case 0xCF: case 0x60: case 0x6F:
		case 0x90: case 0x9F: case 0x30: case 0x3F: case 0xA0: case 0xAF:
		//"0101 0000", "0101 1111", "1100 0000", "1100 1111", "0110 0000", "0110 1111" 
		//"1001 0000", "1001 1111", "0011 0000", "0011 1111", "1010 0000", "1010 1111" 
		//Each preamble has to be tested twice in SBAS DFMC due to the second four bits will
		//correspond to the first four bits of message number, which will be 0 for message 0 and
		// 1111 for messages 62 and 63
			//SBAS DFMC preambles
			sbasblock->frequencyPos=SBASDFMCFREQPOS;
			sbasblock->frequency=5;
			return 1;
			break;
		default:
			//Incorrect preamble or unknown message type
			sbasblock->frequencyPos=UNKNOWNFREQPOS;
			//The frequency will be left to the default value or the one provided in the file
			return 0;
			break;
	}

	return 0;
}


/*****************************************************************************
 * Name        : readSBASmessage
 * Description : Decode SBAS message from a binary string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *binarystring              I  N/A  String with the binary message (1 bit per byte)
 * unsigned char *binarymessage    I  N/A  String with the binary message (8 bit per byte)
 * unsigned char preamble          I  N/A  Preamble (first 8 bits of message). For SBAS DFMC
 *                                           messages, the last 4 bits are zeroed as preamble
 *                                           only has 4 bits  
 * int  validpreamble              I  N/A  Flag to indicate if a valid preamble was found
 *                                             1 => Valid preamble found
 *                                             0 => No valid preamble found
 * int *decodedmessagetype         O  N/A  Message type decoded from hexadecimal message
 * TSBASblock  *sbasblock          O  N/A  TSBASblock structure
 * int *messagesmissing            O  N/A  Indicates the number of messages missing due to the 
 *                                          preamble does not follow the cycle (can be 0,1,2
 *                                          for SBAS 1F and 0,1,2,3,4,5 for SBAS DFMC)
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of function
 *                                        -14 => PRN in almanac slot in MT47 with broadcast indicator enabled
 *                                                does not match with GEO broadcasting the message [DFMC only]
 *                                        -13 => PRN in MT39 does not match with GEO broadcasting the message [DFMC only]
 *                                        -12 => Satellite slot delta is greater than 39 [DFMC only]
 *                                        -11 => Satellite slot delta is 0 [DFMC only]
 *                                        -10 => Satellite slot number is greater than 214 [DFMC only]
 *                                         -9 => Too many satellites with corrections
 *                                                (only for message type 31, if there
 *                                                are more than 92 satellites with
 *                                                corrections) [DFMC only]
 *                                         -8 => Unknown message type
 *                                         -7 => PRN Mask number is greater than 51 [SBAS 1F only]
 *                                         -6 => Time of Week is greater than maximum value
 *                                               (only for messages 12 [SBAS 1F] and 42 [DFMC])
 *                                         -5 => Time of Day is greater than maximum value 
 *                                               (only for messages 24,25,9,17 [SBAS 1F] 32,40,47 [DFMC])
 *                                         -4 => Too many satellites with corrections
 *                                                (only for message type 1, if there
 *                                                are more than 51 satellites with
 *                                                corrections) [SBAS 1F only]
 *                                         -3 => Message identifier does not match
 *                                               (decoded binary value does not
 *                                               match the value given in file)
 *                                         -2 => Preamble not valid
 *                                         -1 => Invalid parity check
 *                                          0 => Message type with no data
 *                                          1 => Message correctly decoded
 *****************************************************************************/
int readSBASmessage (char *binarystring, unsigned char *binarymessage, unsigned char preamble, int validpreamble, int *decodedmessagetype, TSBASblock *sbasblock, int *messagesmissing, TOptions  *options) {

	char				   *endptr;                //This is just for strtol function
	char 					aux[300];
	int						i,j;
	int						lengthmessage;
	int 					checksum;
	int						ret;
	int						start;
	double					scalefactor;
	static unsigned char	previouspreamble[3][MAX_SBAS_PRN]; //Pos 0 is for frequency 1, pos 1 is for frequency 5, pos 2 is for other messages
	static int      	    initialized=0;

	if (initialized==0) {
		for(i=0;i<MAX_SBAS_PRN;i++) {
			previouspreamble[0][i]=0;
			previouspreamble[1][i]=0;
		}
		initialized=1;
	}

	//Table values for messages 2,3,4,5 and 24
	const double	udreimeterslist[16]={0.75,1.0,1.25,1.75,2.25,3.0,3.75,4.5,5.25,6.0,7.5,15.0,50.0,150.0,-1,-2}; //UDRE (metres)
	const double	udreivariancelist[16]={0.0520,0.0924,0.1444,0.2830,0.4678,0.8315,1.2992,1.8709,2.5465,3.3260,5.1968,20.7870,230.9661,2078.695,-1,-2}; //variance (sigma^2) UDRE (metres^2)

	//Table values for message 7
	const double	fastcorrdegfactorlist[16]={0.00000,0.00005,0.00009,0.00012,0.00015,0.00020,0.00030,0.00045,0.00060,0.00090,0.00150,0.00210,0.00270,0.00330,0.00460,0.00580}; //Fast Correction degradation factor (metres/seconds^2)
	const int 		timeoutintervalnonpreciselist[16]={180,180,153,135,135,117,99,81,63,45,45,27,27,27,18,18};//User Time-Out Interval for fast corrections (seconds). En Route through Nonprecision approach
	const int		timeoutintervalpreciselist[16]={120,120,102,90,90,78,66,54,42,30,30,18,18,18,12,12}; //User Time-Out Interval for fast corrections (seconds). Precision approach mode
	const int 	 	maxfastcorrupdateintervallist[16]={60,60,51,45,45,39,33,27,21,15,15,9,9,9,6,6}; //Maximum fast correction update interval (seconds)

	//Table values for URA index in message 9
	const double	minurarangelist[16]={0.00,2.40,3.40,4.85,6.85,9.65,13.65,24.00,48.00,96.00,192.00,384.00,768.00,1536.00,3072.00,6144.00}; //Minimun URA range (metres)
	const double	maxurarangelist[16]={2.40,3.40,4.85,6.85,9.65,13.65,24.00,48.00,96.00,192.00,384.00,768.00,1536.00,3072.00,6144.00,-1};	  //Maximum URA range (metres). -1 means no limit (no accuracy)
	const double	uranominalvaluelist[16]={2,2.8,4,5.7,8,11.3,16,32,64,128,256,512,1024,2048,4096,-1}; //URA nominal values. -1 means no accuracy value

	//Table values for Delta UDRE Indicators in message 27
	const double	deltaudrevaluelist[16]={1,1.1,1.25,1.5,2,3,4,5,6,8,10,20,30,40,50,100};	//Delta UDRE values which multiply the UDRE standard deviation in type 2,3,4,5,6 and 24 messages

	//Table values for GIVE in message 26
	const double	givemeterslist[16]={0.3,0.6,0.9,1.20,1.5,1.8,2.1,2.4,2.7,3.0,3.6,4.5,6.0,15.0,45.0,-1}; //GIVE (metres)
	const double	givevariancelist[16]={0.0084,0.0333,0.0749,0.1331,0.2079,0.2994,0.4075,0.5322,0.6735,0.8315,1.1974,1.8709,3.3260,20.7870,187.0826,-1}; //variance (sigma^2) GIVE (metres^2)

	//Constellation order for SBAS DFMC MT37 OBAD parameters
	const enum GNSSystem 	constOBADorder[5]={GPS,GLONASS,Galileo,BDS,GEO};
	const double			DFREIminvalues[15]={0.125,0.25,0.375,0.5,0.625,0.75,1,1.25,1.5,1.75,2.,2.5,3.,4.,10.};	//DFREI minimum values (in metres)

	////Checksum for SBAS messages
	

	lengthmessage=sbasblock->datalength*4;		//Compute message length
	//Computechecksum from the binary message
	ret=checksumSBAS(binarymessage);

	//Extract the checksum from the message
	getstr(aux,binarystring,lengthmessage,226,24); 		//Parity bits are from bit 227 to 250
	checksum=strtol(aux,&endptr,2);						//Convert parity bits to a decimal number to obtain the message checksum

	*messagesmissing=0;

	//Message types which occur in both SBAS 1F and SBAS DFMC
	//Preambles are different length in each SBAS mode, so it is needed to check both to
	//find out from which frequency was found
	//Check first with SBAS 1F preambles, as they are longer
	if (validpreamble==1) {
		//We can only check for lost messages if preamble is valid
		switch(preamble) {
			case 0x53:
				//SBAS 1F
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,8,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x9A:
						*messagesmissing=1;
						break;
					case 0x53:
						*messagesmissing=2;
						break;
					default:
						break;
				}
				break;
			case 0x9A:
				//SBAS 1F
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,8,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0xC6:
						*messagesmissing=1;
						break;
					case 0x9A:
						*messagesmissing=2;
						break;
					default:
						break;
				}
				break;
			case 0xC6:
				//SBAS 1F
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,8,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x53:
						*messagesmissing=1;
						break;
					case 0xC6:
						*messagesmissing=2;
						break;
					default:
						break;
				}
				break;
			case 0x50: case 0x5F:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x30: case 0x3F:
						*messagesmissing=1;
						break;
					case 0x90: case 0x9F:
						*messagesmissing=2;
						break;
					case 0x60: case 0x6F:
						*messagesmissing=3;
						break;
					case 0xC0: case 0xCF:
						*messagesmissing=4;
						break;
					case 0x50: case 0x5F:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			case 0xC0: case 0xCF:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0xA0: case 0xAF:
						*messagesmissing=1;
						break;
					case 0x30: case 0x3F:
						*messagesmissing=2;
						break;
					case 0x90: case 0x9F:
						*messagesmissing=3;
						break;
					case 0x60: case 0x6F:
						*messagesmissing=4;
						break;
					case 0xC0: case 0xCF:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			case 0x60: case 0x6F:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x50: case 0x5F:
						*messagesmissing=1;
						break;
					case 0xA0: case 0xAF:
						*messagesmissing=2;
						break;
					case 0x30: case 0x3F:
						*messagesmissing=3;
						break;
					case 0x90: case 0x9F:
						*messagesmissing=4;
						break;
					case 0x60: case 0x6F:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			case 0x90: case 0x9F:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0xC0: case 0xCF:
						*messagesmissing=1;
						break;
					case 0x50: case 0x5F:
						*messagesmissing=2;
						break;
					case 0xA0: case 0xAF:
						*messagesmissing=3;
						break;
					case 0x30: case 0x3F:
						*messagesmissing=4;
						break;
					case 0x90: case 0x9F:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			case 0x30: case 0x3F:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x60: case 0x6F:
						*messagesmissing=1;
						break;
					case 0xC0: case 0xCF:
						*messagesmissing=2;
						break;
					case 0x50: case 0x5F:
						*messagesmissing=3;
						break;
					case 0xA0: case 0xAF:
						*messagesmissing=4;
						break;
					case 0x30: case 0x3F:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			case 0xA0: case 0xAF:
				//SBAS DFMC
				////Check that message type given in file matches the one decoded from the binary string
				getstr(aux,binarystring,lengthmessage,4,6);		//Extract message type identifier bits
				*decodedmessagetype=strtol(aux,&endptr,2);		//Convert the binary string to decimal	
				switch(previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]) {
					case 0:
						//This is the first message read in the file, set previouspreamble and continue
						previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble;
						break;
					case 0x90: case 0x9F:
						*messagesmissing=1;
						break;
					case 0x60: case 0x6F:
						*messagesmissing=2;
						break;
					case 0xC0: case 0xCF:
						*messagesmissing=3;
						break;
					case 0x50: case 0x5F:
						*messagesmissing=4;
						break;
					case 0xA0: case 0xAF:
						*messagesmissing=5;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		previouspreamble[sbasblock->frequencyPos][sbasblock->PRN]=preamble; //Copy preamble to previouspreamble variable
	}

	//Skip read function if CRC, preamble or message type have errors
	if(checksum!=ret) return -1;								//CRC Invalid
	if(validpreamble==0) return -2;								//Preamble invalid
	if(*decodedmessagetype!=sbasblock->messagetype) return -3;	//Message type read does not match the one decoded from the hexadecimal message

	////Read messages
	switch(sbasblock->messagetype) {
		case PRNMASKASSIGNMENTS: /*MT 1*/
			//Initialize blocks
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SBAS_PRN;j++) {
					sbasblock->PRNactive[i][j]=0;		//0 means satellite not active
					sbasblock->PRN2pos[i][j]=-1;		//-1 means satellite not in mask
				}
			}

			for(i=0;i<51;i++) {
				sbasblock->pos2PRN[i]=-1;			//-1 means position not set
				sbasblock->pos2GNSS[i]=-1;			//-1 means position not set
			}

			//Reading data

			j=0;							//Set the active PRN position indicator to 0
			//Now there are 210 bits of PRN mask
			//GPS slots PRN Maks
			for(i=14;i<51;i++) {
				if(binarystring[i]=='1') {			//The current PRN has corrections	
					sbasblock->PRNactive[GPS][i-13]=1;	//Set the current satellite active
					sbasblock->pos2PRN[j]=i-13;		//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GPS;		//Save the GNSS type in the list
					sbasblock->PRN2pos[GPS][i-13]=j;	//Save the position of this PRN
					sbasblock->constMonitored[GPS]=1;
					j++;
				}
			}

			
			//GLONASS slots PRN Maks
			for(i=51;i<75;i++) {
				if(binarystring[i]=='1') {			//The current PRN has corrections	
					if(j==51) return -4;			//Too many satellites corrected
					sbasblock->PRNactive[GLONASS][i-50]=1;	//Set the current satellite active
					sbasblock->pos2PRN[j]=i-50;		//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GLONASS;	//Save the GNSS type in the list
					sbasblock->PRN2pos[GLONASS][i-50]=j;	//Save the position of this PRN
					sbasblock->constMonitored[GLONASS]=1;
					j++;
				}
			}

			//Bits 62 to 119 are reserved for future GNSS systems. Skip them.

			//SBAS satellites WAAS, SBAS, MSAAS, GAGAN, SDCM
			for(i=133;i<224;i++) {
				if(binarystring[i]=='1') {			//The current PRN has corrections
					if(j==51) return -4;			//Too many satellites corrected
					sbasblock->PRNactive[GEO][i-13]=1;	//Set the current satellite active
					sbasblock->pos2PRN[j]=i-13;		//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GEO;		//Save the GNSS type in the list
					sbasblock->PRN2pos[GEO][i-13]=j;	//Save the position of this PRN
					sbasblock->constMonitored[GEO]=1;
					j++;
				}
			}

			getstr(aux,binarystring,lengthmessage,224,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);
			sbasblock->numsatellites=j-1;				//Save number of satellites monitored
			break;				
		case DONTUSE: /*MT 0*/ //SBAS 1F and SBAS DFMC
			sbasblock->dontuse=1;
			//Check if the whole message is 0
			getstr(aux,binarystring,lengthmessage,8,218);
			if(strtol(aux,&endptr,2)==0) {				//The message is filled with 0 (except for the preamble and the checksum)
				sbasblock->problems=1;					//In that case set the flag to indicate there are problems with SBAS
				break;
			}
			//If the message is not filled with 0, then it will contain a type 2 message for SBAS 1F and type 34,35,36 for SBAS DFMC
			//A break is not inserted here so it will execute the code of a type 2 message (only if option useAlarmmessageForCorrections is not zero)
			if(options->useAlarmmessageForCorrections==0) break;
			if (sbasblock->frequency==5) {
				//Get message type for SBAS DFMC
				getstr(aux,binarystring,lengthmessage,222,2);
				sbasblock->msg0type=strtol(aux,&endptr,2);
				if (sbasblock->msg0type==0) break; //If value is 0, no MT34, 35 or 36 is provided in MT0 message
			}
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case FASTCORRECTIONS2: /*MT 2*/ case FASTCORRECTIONS3: /*MT 3*/ case FASTCORRECTIONS4: /*MT 4*/ case FASTCORRECTIONS5: /*MT 5*/
			if (sbasblock->frequency==1) {
				//Reading data
				getstr(aux,binarystring,lengthmessage,14,2);				//Extract IODF
				sbasblock->IODF[0]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,16,2);				//Extract IODP
				sbasblock->IODP=strtol(aux,&endptr,2);

				
				for(i=0;i<13;i++) {					//Extract PRC Fast corrections (PRC has sign bit)
					getstr(aux,binarystring,lengthmessage,18+i*12,12);
					sbasblock->PRC[i]=0.125*(double)twocomplementstrbintointeger(aux,12); //PRC has a resolution of 0.125 metres
				}
				
				for(i=0;i<13;i++) {					//Extract UDREIs
					getstr(aux,binarystring,lengthmessage,174+i*4,4);
					sbasblock->UDREI[i]=strtol(aux,&endptr,2);	
					sbasblock->UDRE[i]=udreimeterslist[sbasblock->UDREI[i]];	//Get the UDRE meter value from the UDREI
					sbasblock->UDREsigma[i]=udreivariancelist[sbasblock->UDREI[i]];	//Get the UDRE variance value from the UDREI
				}

				break;
			}
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case INTEGRITYINFODFMC34: /*MT 34*/
			if (sbasblock->msg0type==1) {
				for(i=0;i<92;i++) {
					getstr(aux,binarystring,lengthmessage,10+i*2,2);	//Extract DFRECI
					sbasblock->DFRECI[i]=strtol(aux,&endptr,2);
				}

				for(i=0;i<7;i++) {
					getstr(aux,binarystring,lengthmessage,194+i*4,4);	//Extract DFREI
					sbasblock->DFREI[i]=strtol(aux,&endptr,2);
				}

				getstr(aux,binarystring,lengthmessage,224,2);            //Extract IODM
				sbasblock->IODM=strtol(aux,&endptr,2);
				break;
			}
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case INTEGRITYINFODFMC35: /*MT 35*/
			if (sbasblock->msg0type==2) {

				for(i=0;i<53;i++) {
					getstr(aux,binarystring,lengthmessage,10+i*4,4);	//Extract DFREI
					sbasblock->DFREI[i]=strtol(aux,&endptr,2);
				}

				getstr(aux,binarystring,lengthmessage,224,2);            //Extract IODM
				sbasblock->IODM=strtol(aux,&endptr,2);
				break;
			}
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case INTEGRITYINFODFMC36: /*MT 36*/
			for(i=0;i<38;i++) {
				getstr(aux,binarystring,lengthmessage,10+i*4,4);	//Extract DFREI
				sbasblock->DFREI[i]=strtol(aux,&endptr,2);
			}

			getstr(aux,binarystring,lengthmessage,224,2);            //Extract IODM
			sbasblock->IODM=strtol(aux,&endptr,2);
			break;
		case INTEGRITYINFO: /*MT 6*/
			//Reading data
			for(i=0;i<4;i++) {
				getstr(aux,binarystring,lengthmessage,14+2*i,2);		//Extract IODFs
				sbasblock->IODF[i]=strtol(aux,&endptr,2);
			}

			for(i=0;i<51;i++) {					//Extract UDREIs
				getstr(aux,binarystring,lengthmessage,22+4*i,4);		
				sbasblock->UDREIacu[i]=strtol(aux,&endptr,2);
				sbasblock->UDREacu[i]=udreimeterslist[sbasblock->UDREIacu[i]];	//Get the UDRE meter value from the UDREI
				sbasblock->UDREacusigma[i]=udreivariancelist[sbasblock->UDREIacu[i]];	//Get the UDRE variance value from the UDREI (metres^2)
			}
			break;
		case FASTCORRECTIONSDEGRADATIONFACTOR: /*MT 7*/
			//Reading data
			getstr(aux,binarystring,lengthmessage,14,4);				//Extract tlat
			sbasblock->tlat=strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,18,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);


			for(i=0;i<51;i++) {					//Extract ai indicators
				getstr(aux,binarystring,lengthmessage,22+4*i,4);		
				sbasblock->aiind[i]=strtol(aux,&endptr,2);
				sbasblock->aifactor[i]=fastcorrdegfactorlist[sbasblock->aiind[i]];				//Get the fast correction degradation factor
				sbasblock->timeoutintervalnonprecise[i]=timeoutintervalnonpreciselist[sbasblock->aiind[i]];	//Get the the user timeout interval for non precise approach (seconds)
				sbasblock->timeoutintervalprecise[i]=timeoutintervalpreciselist[sbasblock->aiind[i]];		//Get the the user timeout interval non precise approach (seconds)
				sbasblock->fastcorrupdateinterval[i]=maxfastcorrupdateintervallist[sbasblock->aiind[i]];	//Get the maximum fast correction update interval (seconds)
			}
			break;
		case DEGRADATIONPARAMETERS: /*MT 10*/

			//Reading data
			getstr(aux,binarystring,lengthmessage,14,10);                         //Extract Brrc (in metres)
			sbasblock->degradationfactors[BRRC]=0.002*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,24,10);                         //Extract Cltc_lsb (in metres)
			sbasblock->degradationfactors[CLTCLSB]=0.002*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,34,10);                         //Extract Cltc_v1 (in metres/second)
			sbasblock->degradationfactors[CLTCV1]=0.00005*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,44,9);				//Extract Iltc_v1 (in seconds)
			sbasblock->degradationfactors[ILTCV1]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,53,10);                         //Extract Cltc_v0 (in metres)
			sbasblock->degradationfactors[CLTCV0]=0.002*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,63,9);                          //Extract Iltc_v0 (in seconds)
			sbasblock->degradationfactors[ILTCV0]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,72,10);                         //Extract Cgeo_lsb (in metres)
			sbasblock->degradationfactors[CGEOLSB]=0.0005*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,82,10);                         //Extract Cgeo_v (in metres/second)
			sbasblock->degradationfactors[CGEOV]=0.00005*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,92,9);	                        //Extract Igeo (in seconds)
			sbasblock->degradationfactors[IGEO]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,101,6);                         //Extract Cer (in metres)
			sbasblock->degradationfactors[CER]=0.5*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,107,10);                         //Extract Ciono_step (in metres)
			sbasblock->degradationfactors[CIONOSTEP]=0.001*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,117,9);	                         //Extract Iiono (in seconds)
			sbasblock->degradationfactors[IIONO]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,126,10);                         //Extract Ciono ramp (in metres/second)
			sbasblock->degradationfactors[CIONORAMP]=0.000005*(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,136,1);                         //Extract RSSudre (unitless)
			sbasblock->degradationfactors[RSSUDRE]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,137,1);                         //Extract RSSiono (unitless)
			sbasblock->degradationfactors[RSSIONO]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,138,7);                         //Extract Ccovariance (unitless)
			sbasblock->degradationfactors[CCOVARIANCE]=0.1*(double)strtol(aux,&endptr,2);

			break;

		case LONGTERMSATELLITECORRECTIONS: /*MT 25*/
			//First we need to check the value of the two velocity code bits in the message, in order to know how many satellites are needed
			//Initially, we will have, at least, data for two satellites, but we can have data for three of four satellites depending on the velocity code
			//If velocity code is 0, then each half of the message contains clock offset and position error components estimates for two satellites
			//If velocity code is 1, then each half of the message contains clock drift and velocity error components estimates for one satellite
			ret=2;					//Initially there will be at least two satellites
			if(binarystring[14]=='0') ret+=1;	//Check if there are two satellites in the first half of the message
			if(binarystring[120]=='0') ret+=1;	//Check if there are two satellites in the second half of the message
			sbasblock->numlongtermsaterrcorrections=ret;				//Save the number of satellites in the block			
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				for(j=0;j<15;j++) {
					sbasblock->longtermsaterrcorrections[i][j]=9999;		//9999 means value not set. If velocity code is 0, some slots will not be set
				}
			}

			//Reading first half of message

			getstr(aux,binarystring,lengthmessage,14,1);
			if(strtol(aux,&endptr,2)==0) {		//Check if velocity code equal to 0
				for(i=0;i<2;i++) {							//Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,lengthmessage,14,1);							//Velocity code
					sbasblock->longtermsaterrcorrections[i][VELOCITYCODE]=(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,15+i*51,6);						//PRN Mask Number
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);	
					if(sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,lengthmessage,21+i*51,8);						//Issue of Data
					sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,29+i*51,9);						//Delta X
					sbasblock->longtermsaterrcorrections[i][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 metres	
				
					getstr(aux,binarystring,lengthmessage,38+i*51,9);						//Delta Y
					sbasblock->longtermsaterrcorrections[i][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 metres

					getstr(aux,binarystring,lengthmessage,47+i*51,9);						//Delta Z
					sbasblock->longtermsaterrcorrections[i][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 metres	

					getstr(aux,binarystring,lengthmessage,56+i*51,10);						//Delta A f0
					sbasblock->longtermsaterrcorrections[i][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,lengthmessage,117,2);							//IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i][IODPPOSITION]=(double)strtol(aux,&endptr,2); 	

					//GLONASS SDCM terms
					getstr(aux,binarystring,lengthmessage,21+i*51,3);							//Delay time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,24+i*51,5);							//Operation time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
				}
			} else {			//Velocity code equal to 1
				getstr(aux,binarystring,lengthmessage,14,1);							//Velocity code
				sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]=(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,15,6);							//PRN Mask Number
				sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);	
				if(sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,lengthmessage,21,8);							//Issue of Data
				sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,29,11);							//Delta X
				sbasblock->longtermsaterrcorrections[0][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 metres	
			
				getstr(aux,binarystring,lengthmessage,40,11);							//Delta Y
				sbasblock->longtermsaterrcorrections[0][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 metres

				getstr(aux,binarystring,lengthmessage,51,11);							//Delta Z
				sbasblock->longtermsaterrcorrections[0][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 metres	

				getstr(aux,binarystring,lengthmessage,62,11);							//Delta A f0
				sbasblock->longtermsaterrcorrections[0][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,lengthmessage,73,8);							//Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 metres/second
				
				getstr(aux,binarystring,lengthmessage,81,8);							//Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 metres/second
				
				getstr(aux,binarystring,lengthmessage,89,8);							//Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,97,8);							//Delta A f1
				sbasblock->longtermsaterrcorrections[0][DELTAAF1]=pow(2,-39)*(double)twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 metres/second

				getstr(aux,binarystring,lengthmessage,105,13);						//Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]=16.*(double)strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]>86384) return -5;
				
				getstr(aux,binarystring,lengthmessage,118,2);							//IODP
				sbasblock->longtermsaterrcorrections[0][IODPPOSITION]=(double)strtol(aux,&endptr,2); 

				//GLONASS SDCM terms
				getstr(aux,binarystring,lengthmessage,21,3);							//Delay time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[0][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,24,5);							//Operation time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[0][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
			}

			//Reading second half of message
			ret=(int)sbasblock->longtermsaterrcorrections[0][VELOCITYCODE];	//Save previous velocity code value, to know how many satellites we have read
			if(ret==0) ret=2;		//Two satellites read
			//else if(ret==1)  ret=1;	//One satellite read (the line commented because the action of the else if is useless, due to ret will have the right value
			getstr(aux,binarystring,lengthmessage,120,1);
			if(strtol(aux,&endptr,2)==0) {          //Check if velocity code equal to 0
				for(i=0;i<2;i++) {                                                      //Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,lengthmessage,120,1);                                                  //Velocity code
					sbasblock->longtermsaterrcorrections[i+ret][VELOCITYCODE]=(double)strtol(aux,&endptr,2);

					getstr(aux,binarystring,lengthmessage,121+i*51,6);                                             //PRN Mask Number
					sbasblock->longtermsaterrcorrections[i+ret][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);
					if((int)sbasblock->longtermsaterrcorrections[i+ret][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,lengthmessage,127+i*51,8);                                             //Issue of Data
					sbasblock->longtermsaterrcorrections[i+ret][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);

					getstr(aux,binarystring,lengthmessage,135+i*51,9);                                             //Delta X
					sbasblock->longtermsaterrcorrections[i+ret][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 metres  

					getstr(aux,binarystring,lengthmessage,144+i*51,9);                                             //Delta Y
					sbasblock->longtermsaterrcorrections[i+ret][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 metres

					getstr(aux,binarystring,lengthmessage,153+i*51,9);                                             //Delta Z
					sbasblock->longtermsaterrcorrections[i+ret][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 metres  

					getstr(aux,binarystring,lengthmessage,162+i*51,10);                                            //Delta A f0
					sbasblock->longtermsaterrcorrections[i+ret][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,lengthmessage,223,2);                                                 //IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i+ret][IODPPOSITION]=(double)strtol(aux,&endptr,2);

					//GLONASS SDCM terms
					getstr(aux,binarystring,lengthmessage,127+i*51,3);							//Delay time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i+ret][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,130+i*51,5);							//Operation time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i+ret][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
				}
			} else {                        //Velocity code equal to 1
				getstr(aux,binarystring,lengthmessage,120,1);                                                  //Velocity code
				sbasblock->longtermsaterrcorrections[ret][VELOCITYCODE]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,121,6);                                                  //PRN Mask Number
				sbasblock->longtermsaterrcorrections[ret][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);
				if(sbasblock->longtermsaterrcorrections[ret][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,lengthmessage,127,8);                                                  //Issue of Data
				sbasblock->longtermsaterrcorrections[ret][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,135,11);                                        	 //Delta X
				sbasblock->longtermsaterrcorrections[ret][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 metres 

				getstr(aux,binarystring,lengthmessage,146,11);                                      		 //Delta Y
				sbasblock->longtermsaterrcorrections[ret][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 metres

				getstr(aux,binarystring,lengthmessage,157,11);                                        	 //Delta Z
				sbasblock->longtermsaterrcorrections[ret][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 metres 

				getstr(aux,binarystring,lengthmessage,168,11);                                      		 //Delta A f0
				sbasblock->longtermsaterrcorrections[ret][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,lengthmessage,179,8);                                          	 //Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAXRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,187,8);                                          	 //Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAYRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,195,8);                                          	 //Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAZRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,203,8);                                          	 //Delta A f1
				sbasblock->longtermsaterrcorrections[ret][DELTAAF1]=pow(2,-39)*(double)twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 metres/second

				getstr(aux,binarystring,lengthmessage,211,13);                                        	 //Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[ret][TIMEOFDAYAPPLICABILITY]=16.*(double)strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[ret][TIMEOFDAYAPPLICABILITY]>86384) return -5;

				getstr(aux,binarystring,lengthmessage,224,2);                                         	 //IODP
				sbasblock->longtermsaterrcorrections[ret][IODPPOSITION]=(double)strtol(aux,&endptr,2);

				//GLONASS SDCM terms
				getstr(aux,binarystring,lengthmessage,127,3);							//Delay time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[ret][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,130,5);							//Operation time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[ret][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
			}
			break;

		case MIXEDFASTLONGTERMCORRECTIONS: /*MT 24*/
			ret=1;					//Initially there will be at least two satellites
			if(binarystring[120]=='0') ret+=1;	//Check if there are two satellites in the half of the message
			sbasblock->numlongtermsaterrcorrections=ret;				//Save the number of satellites in the block			
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				for(j=0;j<15;j++) {
					sbasblock->longtermsaterrcorrections[i][j]=9999;		//9999 means value not set. If velocity code is 0, some slots will not be set
				}
			}

			//Read fast corrections
			for(i=0;i<6;i++) {					//Extract PRC Fast corrections (PRC has sign bit)
				getstr(aux,binarystring,lengthmessage,14+i*12,12);
				sbasblock->PRC[i]=0.125*(double)twocomplementstrbintointeger(aux,12); //PRC has a resolution of 0.125 metres
			}
			
			for(i=0;i<6;i++) {					//Extract UDREIs
				getstr(aux,binarystring,lengthmessage,86+i*4,4);
				sbasblock->UDREI[i]=strtol(aux,&endptr,2);	
				sbasblock->UDRE[i]=udreimeterslist[sbasblock->UDREI[i]];	//Get the UDRE meter value from the UDREI
				sbasblock->UDREsigma[i]=udreivariancelist[sbasblock->UDREI[i]];	//Get the UDRE variance value from the UDREI
			}

			getstr(aux,binarystring,lengthmessage,110,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,112,2);				//Extract Block ID
			sbasblock->BlockID=strtol(aux,&endptr,2)+2;		//Block ID need to be added two because with 2 bits we have the range 0-3, but messages type are in range 2-5

			getstr(aux,binarystring,lengthmessage,114,2);				//Extract IODF
			sbasblock->IODF[0]=strtol(aux,&endptr,2);


			//Read long term satellite error corrections
			getstr(aux,binarystring,lengthmessage,120,1);
			if(strtol(aux,&endptr,2)==0) {          //Check if velocity code equal to 0
				for(i=0;i<2;i++) {                                                      //Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,lengthmessage,120,1);                                                  //Velocity code
					sbasblock->longtermsaterrcorrections[i][VELOCITYCODE]=(double)strtol(aux,&endptr,2);

					getstr(aux,binarystring,lengthmessage,121+i*51,6);                                             //PRN Mask Number
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);
					if((int)sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,lengthmessage,127+i*51,8);                                             //Issue of Data
					sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);

					getstr(aux,binarystring,lengthmessage,135+i*51,9);                                             //Delta X
					sbasblock->longtermsaterrcorrections[i][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 metres  

					getstr(aux,binarystring,lengthmessage,144+i*51,9);                                             //Delta Y
					sbasblock->longtermsaterrcorrections[i][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 metres

					getstr(aux,binarystring,lengthmessage,153+i*51,9);                                             //Delta Z
					sbasblock->longtermsaterrcorrections[i][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 metres  

					getstr(aux,binarystring,lengthmessage,162+i*51,10);                                            //Delta A f0
					sbasblock->longtermsaterrcorrections[i][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,lengthmessage,223,2);                                                 //IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i][IODPPOSITION]=(double)strtol(aux,&endptr,2);

					//GLONASS SDCM terms
					getstr(aux,binarystring,lengthmessage,127+i*51,3);							//Delay time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i+ret][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,130+i*51,5);							//Operation time (for GLONASS satellites only in SDCM)
					sbasblock->longtermsaterrcorrections[i+ret][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
				}
			} else {                        //Velocity code equal to 1
				getstr(aux,binarystring,lengthmessage,120,1);                                                  //Velocity code
				sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,121,6);                                                  //PRN Mask Number
				sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);
				if(sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,lengthmessage,127,8);                                                  //Issue of Data
				sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,135,11);                                        	 //Delta X
				sbasblock->longtermsaterrcorrections[0][DELTAX]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 metres 

				getstr(aux,binarystring,lengthmessage,146,11);                                      		 //Delta Y
				sbasblock->longtermsaterrcorrections[0][DELTAY]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 metres

				getstr(aux,binarystring,lengthmessage,157,11);                                        	 //Delta Z
				sbasblock->longtermsaterrcorrections[0][DELTAZ]=0.125*(double)twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 metres 

				getstr(aux,binarystring,lengthmessage,168,11);                                      		 //Delta A f0
				sbasblock->longtermsaterrcorrections[0][DELTAAF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,lengthmessage,179,8);                                          	 //Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,187,8);                                          	 //Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,195,8);                                          	 //Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE]=pow(2,-11)*(double)twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 metres/second

				getstr(aux,binarystring,lengthmessage,203,8);                                          	 //Delta A f1
				sbasblock->longtermsaterrcorrections[0][DELTAAF1]=pow(2,-39)*(double)twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 metres/second

				getstr(aux,binarystring,lengthmessage,211,13);                                        	 //Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]=16.*(double)strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]>86384) return -5;

				getstr(aux,binarystring,lengthmessage,224,2);                                         	 //IODP
				sbasblock->longtermsaterrcorrections[0][IODPPOSITION]=(double)strtol(aux,&endptr,2);

				//GLONASS SDCM terms
				getstr(aux,binarystring,lengthmessage,127,3);							//Delay time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[0][GLODELAYTIME]=30.*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,130,5);							//Operation time (for GLONASS satellites only in SDCM)
				sbasblock->longtermsaterrcorrections[0][GLOOPERATIONTIME]=30.*(double)strtol(aux,&endptr,2);	
			}
			break;
		case GEONAVIGATIONMESSAGE: /*MT 9*/
			//Read message
			getstr(aux,binarystring,lengthmessage,14,8);				//Extract IODN (In MOPS this bits are set as spare). According to RINEX v2.11, this spare bits are the IODN
			sbasblock->geonavigationmessage[IODNPOS]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,22,13);				//Extract t0 (seconds)
			sbasblock->geonavigationmessage[T0NAV]=16.*(double)strtol(aux,&endptr,2);
			if((int)sbasblock->geonavigationmessage[T0NAV]>86384) return -5;

			getstr(aux,binarystring,lengthmessage,35,4);				//Extract URA index
			sbasblock->geonavigationmessage[URAINDEX]=(double)strtol(aux,&endptr,2);
			sbasblock->geonavigationmessage[URAMINRANGE]=minurarangelist[(int)sbasblock->geonavigationmessage[URAINDEX]];
			sbasblock->geonavigationmessage[URAMAXRANGE]=maxurarangelist[(int)sbasblock->geonavigationmessage[URAINDEX]];
			sbasblock->geonavigationmessage[URANOMINALVALUE]=uranominalvaluelist[(int)sbasblock->geonavigationmessage[URAINDEX]];

			getstr(aux,binarystring,lengthmessage,39,30);				//Extract Xg 
			sbasblock->geonavigationmessage[XG]=0.08*(double)twocomplementstrbintointeger(aux,30);	//Xg has a resolution of 0.08 metres

			getstr(aux,binarystring,lengthmessage,69,30);				//Extract Yg
			sbasblock->geonavigationmessage[YG]=0.08*(double)twocomplementstrbintointeger(aux,30);	//Yg has a resolution of 0.08 metres

			getstr(aux,binarystring,lengthmessage,99,25);				//Extract Zg
			sbasblock->geonavigationmessage[ZG]=0.4*(double)twocomplementstrbintointeger(aux,25);	//Zg has a resolution of 0.4 metres

			getstr(aux,binarystring,lengthmessage,124,17);			//Extract Xg Rate of Change
			sbasblock->geonavigationmessage[XGRATEOFCHANGE]=0.000625*(double)twocomplementstrbintointeger(aux,17);	//Xg Rate of Change has a resolution of 0.000625 metres/second

			getstr(aux,binarystring,lengthmessage,141,17);			//Extract Yg Rate of Change
			sbasblock->geonavigationmessage[YGRATEOFCHANGE]=0.000625*(double)twocomplementstrbintointeger(aux,17);	//Yg Rate of Change has a resolution of 0.000625 metres/second

			getstr(aux,binarystring,lengthmessage,158,18);			//Extract Zg Rate of Change
			sbasblock->geonavigationmessage[ZGRATEOFCHANGE]=0.004*(double)twocomplementstrbintointeger(aux,18);	//Zg Rate of Change has a resolution of 0.004 metres/second

			getstr(aux,binarystring,lengthmessage,176,10);			//Extract Xg acceleration
			sbasblock->geonavigationmessage[XGACCELERATION]=0.0000125*(double)twocomplementstrbintointeger(aux,10);//Xg acceleration has a resolution of 0.0000125 metres/second^2

			getstr(aux,binarystring,lengthmessage,186,10);			//Extract Yg acceleration
			sbasblock->geonavigationmessage[YGACCELERATION]=0.0000125*(double)twocomplementstrbintointeger(aux,10);//Yg acceleration has a resolution of 0.0000125 metres/second^2

			getstr(aux,binarystring,lengthmessage,196,10);			//Extract Zg acceleration
			sbasblock->geonavigationmessage[ZGACCELERATION]=0.0000625*(double)twocomplementstrbintointeger(aux,10);//Zg acceleration has a resolution of 0.0000625 metres/second^2

			getstr(aux,binarystring,lengthmessage,206,12);			//Extract aGf0
			sbasblock->geonavigationmessage[AGF0]=pow(2,-31)*(double)twocomplementstrbintointeger(aux,12);	//aGf0 has a resolution of 2^-31 seconds

			getstr(aux,binarystring,lengthmessage,218,8);				//Extract aGf1
			sbasblock->geonavigationmessage[AGF1]=pow(2,-40)*(double)twocomplementstrbintointeger(aux,8);	//aGf1 has a resolution of 2^-40 seconds/second

			break;

		case GEOSATELLITEALMANACS: /*MT 17*/
			//First we need to check how many almanacs are given
			ret=0;
			getstr(aux,binarystring,lengthmessage,150,8);
			if(strtol(aux,&endptr,2)!=0) ret=3;
			else {
				getstr(aux,binarystring,lengthmessage,83,8);
				if(strtol(aux,&endptr,2)!=0) ret=2;
				else {
					getstr(aux,binarystring,lengthmessage,16,8);
					if(strtol(aux,&endptr,2)!=0) ret=1;
				}
			}
			sbasblock->numgeoalmanacs=ret;
			if(ret==0) ret=1;	//If there are no satellites we put one slot to avoid memory problems

			for(i=0;i<ret;i++) {
				for(j=0;j<12;j++) {
					sbasblock->geoalmanacsmessage[i][j]=-1.;
				}
			}

			//Read message
			for(i=0;i<sbasblock->numgeoalmanacs;i++) {
				getstr(aux,binarystring,lengthmessage,14+i*67,2);				//Extract Data ID
				sbasblock->geoalmanacsmessage[i][DATAID]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,16+i*67,8);				//Extract PRN Number
				sbasblock->geoalmanacsmessage[i][PRNNUMBER]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,24+i*67,8);				//Extract Health and Service provider (the eight bits of Health and status)
				sbasblock->geoalmanacsmessage[i][HEALTHPROVIDER]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,24+i*67,4);				//Extract Service provider (only the first four bits)
				sbasblock->geoalmanacsmessage[i][SERVICEPROVIDER]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,28+i*67,4);				//Extract Health status (only the last four bits)
				sbasblock->geoalmanacsmessage[i][HEALTHSTATUS]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,32+i*67,15);				//Extract Xg
				sbasblock->geoalmanacsmessage[i][XGALMANAC]=2600.*(double)twocomplementstrbintointeger(aux,15);	//Xg has a resolution of 2,600 metres

				getstr(aux,binarystring,lengthmessage,47+i*67,15);				//Extract Yg
				sbasblock->geoalmanacsmessage[i][YGALMANAC]=2600.*(double)twocomplementstrbintointeger(aux,15);	//Yg has a resolution of 2,600 metres

				getstr(aux,binarystring,lengthmessage,62+i*67,9);				//Extract Zg
				sbasblock->geoalmanacsmessage[i][ZGALMANAC]=26000.*(double)twocomplementstrbintointeger(aux,9);	//Zg has a resolution of 26,000 metres

				getstr(aux,binarystring,lengthmessage,71+i*67,3);				//Extract Xg Rate of Change
				sbasblock->geoalmanacsmessage[i][XGALMANACRATEOFCHANGE]=10.*(double)twocomplementstrbintointeger(aux,3);	//Xg Rate of Change has a resolution of 10 metres/second

				getstr(aux,binarystring,lengthmessage,74+i*67,3);				//Extract Yg Rate of Change
				sbasblock->geoalmanacsmessage[i][YGALMANACRATEOFCHANGE]=10.*(double)twocomplementstrbintointeger(aux,3);	//Yg Rate of Change has a resolution of 10 metres/second

				getstr(aux,binarystring,lengthmessage,77+i*67,4);				//Extract Zg Rate of Change
				sbasblock->geoalmanacsmessage[i][ZGALMANACRATEOFCHANGE]=60.*(double)twocomplementstrbintointeger(aux,4);	//Zg Rate of Change has a resolution of 60 metres/second

				getstr(aux,binarystring,lengthmessage,215,11);				//Extract t0 or Time of Day (seconds)
				sbasblock->geoalmanacsmessage[i][T0ALMANAC]=64.*(double)strtol(aux,&endptr,2);
				if((int)sbasblock->geoalmanacsmessage[i][T0ALMANAC]>86336) return -5;
			}
			break;
		case SBASSERVICEMESSAGE: /*MT 27*/
			//Read number of regions given
			getstr(aux,binarystring,lengthmessage,23,3);	
			ret=strtol(aux,&endptr,2);

			sbasblock->numregioncoordinates=ret;
			if(ret==0) ret=1;						//If the number of regions is 0, set the size to 1 to avoid possible memory issues	
			for(i=0;i<ret;i++) {
				for(j=0;j<12;j++) {
					sbasblock->regioncoordinates[i][j]=9999;		//9999 means value not set
				}
			}
	
			//Read message
			getstr(aux,binarystring,lengthmessage,14,3);				//Extract Issue of Data Service (IODS)
			sbasblock->servicemessage[IODSPOS]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,17,3);				//Extract Number of Service Messages
			sbasblock->servicemessage[NUMBERSERVICEMESSAGES]=(double)strtol(aux,&endptr,2)+1;	//This value has an offset of 1

			getstr(aux,binarystring,lengthmessage,20,3);				//Extract Service Message Number
			sbasblock->servicemessage[SERVICEMESSAGENUMBER]=(double)strtol(aux,&endptr,2)+1;	//This value has an offset of 1
			
			getstr(aux,binarystring,lengthmessage,23,3);				//Extract Number of Regions
			sbasblock->servicemessage[NUMBEROFREGIONS]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,26,2);				//Extract Priority Code
			sbasblock->servicemessage[PRIORITYCODE]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,28,4);				//Extract Delta UDRE Indicator Inside
			sbasblock->servicemessage[UDREINSIDEIND]=(double)strtol(aux,&endptr,2);
			sbasblock->servicemessage[UDREINSIDEVALUE]=deltaudrevaluelist[(int)sbasblock->servicemessage[UDREINSIDEIND]];	//Get Delta UDRE Indicator Inside value

			getstr(aux,binarystring,lengthmessage,32,4);				//Extract Delta UDRE Indicator Outside
			sbasblock->servicemessage[UDREOUTSIDEIND]=(double)strtol(aux,&endptr,2);
			sbasblock->servicemessage[UDREOUTSIDEVALUE]=deltaudrevaluelist[(int)sbasblock->servicemessage[UDREOUTSIDEIND]]; //Get Delta UDRE Indicator Outside value

			for(i=0;i<(int)sbasblock->servicemessage[NUMBEROFREGIONS];i++) {
				//Read all the regions given in the message
				//Positive values denote North latitude or East longitude
				getstr(aux,binarystring,lengthmessage,36+i*35,8);				//Extract Coordinate 1 Latitude (degrees)
				sbasblock->regioncoordinates[i][COORD1LAT]=twocomplementstrbintointeger(aux,8);

				getstr(aux,binarystring,lengthmessage,44+i*35,9);				//Extract Coordinate 1 Longitude (degrees)
				sbasblock->regioncoordinates[i][COORD1LON]=twocomplementstrbintointeger(aux,9);

				getstr(aux,binarystring,lengthmessage,53+i*35,8);				//Extract Coordinate 2 Latitude (degrees)
				sbasblock->regioncoordinates[i][COORD2LAT]=twocomplementstrbintointeger(aux,8);

				getstr(aux,binarystring,lengthmessage,61+i*35,9);				//Extract Coordinate 2 Longitude (degrees)
				sbasblock->regioncoordinates[i][COORD2LON]=twocomplementstrbintointeger(aux,9);

				getstr(aux,binarystring,lengthmessage,70+i*35,1);				//Extract Region Shape (0=> Tringular 1=>Square)
				sbasblock->regioncoordinates[i][REGIONSHAPE]=strtol(aux,&endptr,2);

				//Coordinate 3 takes Coordinate 1 latitude and Coordinate 2 longitude
				sbasblock->regioncoordinates[i][COORD3LAT]=sbasblock->regioncoordinates[i][COORD1LAT];
				sbasblock->regioncoordinates[i][COORD3LON]=sbasblock->regioncoordinates[i][COORD2LON];

				//Check the region shape. If it is a square, we will have to set the value for the fourth coordinate. If it a triangle, values are already set to 9999
				if(sbasblock->regioncoordinates[i][REGIONSHAPE]==1) {
					sbasblock->regioncoordinates[i][COORD4LAT]=sbasblock->regioncoordinates[i][COORD2LAT];
					sbasblock->regioncoordinates[i][COORD4LON]=sbasblock->regioncoordinates[i][COORD1LON];
				}

				//Copy UDRE values to region coordinates block
				sbasblock->regioncoordinates[i][UDREINSIDEVALUE]=(int)sbasblock->servicemessage[UDREINSIDEVALUE];
				sbasblock->regioncoordinates[i][UDREOUTSIDEVALUE]=(int)sbasblock->servicemessage[UDREOUTSIDEVALUE];
				//Copy number of service messages
				sbasblock->regioncoordinates[i][NUMBERSERVICEMESSAGES]=(int)sbasblock->servicemessage[NUMBERSERVICEMESSAGES];

			}
			break;
		case SBASNETWORKTIMEPARAMETERS: /*MT 12*/
			//Read message
			getstr(aux,binarystring,lengthmessage,14,24);				//Extract A1snt
			sbasblock->networktimemessage[A1SNT]=pow(2,-50)*(double)twocomplementstrbintointeger(aux,24);	//A1wnt has a resolution of 2^-50 seconds/second

			getstr(aux,binarystring,lengthmessage,38,32);				//Extract A0snt
			sbasblock->networktimemessage[A0SNT]=pow(2,-30)*(double)twocomplementstrbintolonglonginteger(aux,32);	//A0wnt has a resolution of 2^-30 seconds

			getstr(aux,binarystring,lengthmessage,70,8);				//Extract t0t
			sbasblock->networktimemessage[T0T]=pow(2,12)*(double)strtol(aux,&endptr,2);			//t0t has a resolution of 2^12 seconds

			getstr(aux,binarystring,lengthmessage,78,8);				//Extract WNt
			sbasblock->networktimemessage[WNT]=(double)strtol(aux,&endptr,2);				//In weeks
			
			getstr(aux,binarystring,lengthmessage,86,8);				//Extract Delta tLS
			sbasblock->networktimemessage[DELTATLS]=(double)twocomplementstrbintointeger(aux,8);		//Delta tLS has a resolution of 1 second

			getstr(aux,binarystring,lengthmessage,94,8);				//Extract WNlsf
			sbasblock->networktimemessage[WNLSF]=(double)strtol(aux,&endptr,2);				//In weeks

			getstr(aux,binarystring,lengthmessage,102,8);				//Extract DN
			sbasblock->networktimemessage[DNDAY]=(double)strtol(aux,&endptr,2);				//In days
			
			getstr(aux,binarystring,lengthmessage,110,8);				//Extract Delta tLSF 
			sbasblock->networktimemessage[DELTATLSF]=(double)twocomplementstrbintointeger(aux,8);		//Delta tLSF has a resolution of 1 second

			getstr(aux,binarystring,lengthmessage,118,3);				//Extract UTC Standard Identifier
			sbasblock->networktimemessage[UTCIDENTIFIER]=(double)strtol(aux,&endptr,2);
			
			getstr(aux,binarystring,lengthmessage,121,20);			//Extract GPS Time of Week
			sbasblock->networktimemessage[GPSTOW]=(double)strtol(aux,&endptr,2);				//In seconds
			if((int)sbasblock->networktimemessage[GPSTOW]>604799) return -6;
			
			getstr(aux,binarystring,lengthmessage,141,10);			//Extract GPS Week Number
			sbasblock->networktimemessage[GPSWEEKNUMBER]=(double)strtol(aux,&endptr,2);			//In weeks
			
			getstr(aux,binarystring,lengthmessage,151,1);				//Extract GLONASS Indicator
			sbasblock->networktimemessage[GLONASSINDICATOR]=(double)strtol(aux,&endptr,2);			

			getstr(aux,binarystring,lengthmessage,152,32);				//Extract GLONASS ai clock offset (in SDCM only)
			sbasblock->networktimemessage[GLONASSAIOFFSSET]=pow(2,-30)*(double)strtoll(aux,&endptr,2);			
			break;
		case CLOCKEPHEMERISCOVARIANCEMATRIX: /*MT 28*/
			//Read number of satellites
			ret=0;
			start=0;	//This is for the case we only have data in the second satellite
			//Check PRN Number first satellite
			getstr(aux,binarystring,lengthmessage,16,6);
			if(strtol(aux,&endptr,2)!=0) {
				ret++;
				start=0;
			}
			//Check PRN Number second satellite
			getstr(aux,binarystring,lengthmessage,121,6);
			if(strtol(aux,&endptr,2)!=0) {
				ret++;
				if(ret==1) start=1;
			}

			sbasblock->numclockephemeriscovariance=ret;    //Save number of satellites
			if(ret==0) ret=1;       //If there are no satellites, put ret equal to 1 to give size to numclockephemeriscovariance in order to avoid memory problems

			for(i=0;i<ret;i++) {
				for(j=0;j<14;j++) {
					sbasblock->clockephemeriscovariance[i][j]=-1;		//-1 means value not set
				}
			}

			//Read message
			for(i=start;i<sbasblock->numclockephemeriscovariance+start;i++) {
				getstr(aux,binarystring,lengthmessage,14,2);				//Extract IODP
				sbasblock->clockephemeriscovariance[i-start][IODPPOSITION]=(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,16+i*105,6);			//Extract PRN Mask Number
				sbasblock->clockephemeriscovariance[i-start][PRNMASKNUMBER]=(double)strtol(aux,&endptr,2);	
				if(sbasblock->clockephemeriscovariance[i-start][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,lengthmessage,22+i*105,3);			//Extract Scale Exponent
				sbasblock->clockephemeriscovariance[i-start][SCALEEXPONENT]=(double)strtol(aux,&endptr,2);	

				scalefactor=pow(2,sbasblock->clockephemeriscovariance[i-start][SCALEEXPONENT]-5.);

				sbasblock->clockephemeriscovariance[i-start][SCALEFACTOR]=scalefactor;

				getstr(aux,binarystring,lengthmessage,25+i*105,9);			//Extract E1,1
				sbasblock->clockephemeriscovariance[i-start][E11]=scalefactor*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,34+i*105,9);			//Extract E2,2
				sbasblock->clockephemeriscovariance[i-start][E22]=scalefactor*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,43+i*105,9);			//Extract E3,3
				sbasblock->clockephemeriscovariance[i-start][E33]=scalefactor*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,52+i*105,9);			//Extract E4,4
				sbasblock->clockephemeriscovariance[i-start][E44]=scalefactor*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,61+i*105,10);			//Extract E1,2
				sbasblock->clockephemeriscovariance[i-start][E12]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,lengthmessage,71+i*105,10);			//Extract E1,3
				sbasblock->clockephemeriscovariance[i-start][E13]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,lengthmessage,81+i*105,10);			//Extract E1,4
				sbasblock->clockephemeriscovariance[i-start][E14]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,lengthmessage,91+i*105,10);			//Extract E2,3
				sbasblock->clockephemeriscovariance[i-start][E23]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,lengthmessage,101+i*105,10);			//Extract E2,4
				sbasblock->clockephemeriscovariance[i-start][E24]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,lengthmessage,111+i*105,10);			//Extract E3,4
				sbasblock->clockephemeriscovariance[i-start][E34]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			}
			break;
		case IONOSPHERICGRIDPOINTSMASKS: /*MT 18*/
			//Read message
			getstr(aux,binarystring,lengthmessage,14,4);				//Extract Number of bands being broadcast
			sbasblock->igpmaskmessage[NUMBEROFBANDS]=strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,18,4);				//Extract Band Number
			sbasblock->igpmaskmessage[BANDNUMBER]=strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,22,2);				//Extract IODI (Issue of Data Ionosphere)
			sbasblock->igpmaskmessage[IODIPOS]=strtol(aux,&endptr,2);	

			for(i=0;i<201;i++) {
				getstr(aux,binarystring,lengthmessage,24+i,1);		//Extract IGP (Ionospheric Grid Point) Mask bit
				sbasblock->igpmaskmessage[i+3]=strtol(aux,&endptr,2);	
			}
			break;
		case IONOSPHERICDELAYCORRECTIONS: /*MT 26*/
			for(i=0;i<15;i++) {
				for(j=0;j<7;j++) {
					sbasblock->ionodelayparameters[i][j]=-1.;		//-1 means value not set
				}
			}

			//Read message
			for(i=0;i<15;i++) {
				getstr(aux,binarystring,lengthmessage,14,4);				//Extract Band Number
				sbasblock->ionodelayparameters[i][BANDNUMBER]=strtol(aux,&endptr,2);	
				
				getstr(aux,binarystring,lengthmessage,18,4);				//Extract Block ID
				sbasblock->ionodelayparameters[i][BLOCKID]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,22+i*13,9);			//Extract IGP Vertical Delay
				sbasblock->ionodelayparameters[i][IGPVERTICALDELAY]=0.125*strtol(aux,&endptr,2);	//IGP Vertical Delay has a resolution of 0.125 metres

				getstr(aux,binarystring,lengthmessage,31+i*13,4);			//Extract GIVEI (Grid Ionospheric Vertical Error Indicator)
				sbasblock->ionodelayparameters[i][GIVEI]=strtol(aux,&endptr,2);	
				sbasblock->ionodelayparameters[i][GIVEVALUE]=givemeterslist[(int)sbasblock->ionodelayparameters[i][GIVEI]];	//Get the GIVE value (metres) for the given indicator
				sbasblock->ionodelayparameters[i][GIVEVARIANCE]=givevariancelist[(int)sbasblock->ionodelayparameters[i][GIVEI]]; //Get the GIVE variance (metres^2) for the given indicator

				getstr(aux,binarystring,lengthmessage,217,2);				//Extract IODI (Ionospheric Mask Issue of Data)
				sbasblock->ionodelayparameters[i][IODIPOS]=strtol(aux,&endptr,2);	
			}
			break;
		case SATMASKASIGNMENTS: /*MT 31*/
			//Initialize blocks
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SBAS_PRN;j++) {
					sbasblock->PRNactive[i][j]=0;		//0 means satellite not active
					sbasblock->PRN2pos[i][j]=-1;		//-1 means satellite not in mask
				}
			}

			for(i=0;i<92;i++) {
				sbasblock->pos2PRN[i]=-1;			//-1 means position not set
				sbasblock->pos2GNSS[i]=-1;			//-1 means position not set
			}
			for(i=0;i<215;i++) {
				sbasblock->Slot2pos[i]=-1;			//-1 means position not set
			}

			//Reading data

			j=0;							//Set the active PRN position indicator to 0
			//Now there are 214 bits of PRN mask
			//GPS slots PRN Maks
			for(i=10;i<47;i++) {
				if(binarystring[i]=='1') {						//The current PRN has corrections	
					sbasblock->PRNactive[GPS][i-9]=1;			//Set the current satellite active
					sbasblock->pos2PRN[j]=i-9;					//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GPS;					//Save the GNSS type in the list
					sbasblock->PRN2pos[GPS][i-9]=j;				//Save the position of this PRN
					sbasblock->Slot2pos[i-10+1]=j;				//Save conversion from satellite slot to position in mask
					sbasblock->constMonitored[GPS]=1;
					j++;
				}

			}

			//GLONASS slots PRN Maks
			for(i=47;i<84;i++) {
				if(binarystring[i]=='1') {							//The current PRN has corrections	
					if(j==92) return -9;							//Too many satellites corrected
					sbasblock->PRNactive[GLONASS][i-46]=1;			//Set the current satellite active
					sbasblock->pos2PRN[j]=i-46;						//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GLONASS;					//Save the GNSS type in the list
					sbasblock->PRN2pos[GLONASS][i-46]=j;			//Save the position of this PRN
					sbasblock->Slot2pos[i-47+38]=j;					//Save conversion from satellite slot to position in mask
					sbasblock->constMonitored[GLONASS]=1;
					j++;
				}
			}

			//Galileo slots PRN Maks
			for(i=84;i<121;i++) {
				if(binarystring[i]=='1') {							//The current PRN has corrections	
					if(j==92) return -9;							//Too many satellites corrected
					sbasblock->PRNactive[Galileo][i-83]=1;			//Set the current satellite active
					sbasblock->pos2PRN[j]=i-83;						//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=Galileo;					//Save the GNSS type in the list
					sbasblock->PRN2pos[Galileo][i-83]=j;			//Save the position of this PRN
					sbasblock->Slot2pos[i-84+75]=j;					//Save conversion from satellite slot to position in mask
					sbasblock->constMonitored[Galileo]=1;
					j++;
				}
			}

			//Bits 121 to 128 are spare bits

			//GEO slots PRN Maks
			for(i=129;i<168;i++) {
				if(binarystring[i]=='1') {						//The current PRN has corrections	
					if(j==92) return -9;						//Too many satellites corrected
					sbasblock->PRNactive[GEO][i-9]=1;			//Set the current satellite active
					sbasblock->pos2PRN[j]=i-9;					//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=GEO;					//Save the GNSS type in the list
					sbasblock->PRN2pos[GEO][i-9]=j;				//Save the position of this PRN
					sbasblock->Slot2pos[i-129+120]=j;			//Save conversion from satellite slot to position in mask
					sbasblock->constMonitored[GEO]=1;
					j++;
				}
			}


			//BeiDou slots PRN Maks
			for(i=168;i<205;i++) {
				if(binarystring[i]=='1') {						//The current PRN has corrections	
					if(j==92) return -9;						//Too many satellites corrected
					sbasblock->PRNactive[BDS][i-167]=1;			//Set the current satellite active
					sbasblock->pos2PRN[j]=i-167;				//Save the PRN number in the list
					sbasblock->pos2GNSS[j]=BDS;					//Save the GNSS type in the list
					sbasblock->PRN2pos[BDS][i-167]=j;			//Save the position of this PRN
					sbasblock->Slot2pos[i-168+159]=j;			//Save conversion from satellite slot to position in mask
					sbasblock->constMonitored[BDS]=1;
					j++;
				}
			}

			//Bits 205 to 223 are reserved bits


			sbasblock->numsatellites=j-1;					//Save number of satellites monitored

			getstr(aux,binarystring,lengthmessage,224,2);	//Extract IODM
			sbasblock->IODM=strtol(aux,&endptr,2); 
			break;
		case CLOCKEPHEMERISCOVARIANCEMATRIXDFMC: /*MT 32*/
			//Get orbit parameters
			getstr(aux,binarystring,lengthmessage,10,8);                                                  //Satellite slot number
			sbasblock->orbitclockcorrection[SATSLOTNUMBER]=(double)strtol(aux,&endptr,2);
			sbasblock->covariancematrixdata[SATSLOTNUMBER]=(double)strtol(aux,&endptr,2);
			if(sbasblock->covariancematrixdata[SATSLOTNUMBER]>214) return -10;

			getstr(aux,binarystring,lengthmessage,18,10);                                                  //Issue of Data Navigation
			sbasblock->orbitclockcorrection[IODNPOSITION]=(double)strtol(aux,&endptr,2);
			sbasblock->covariancematrixdata[IODNPOSITION]=(double)strtol(aux,&endptr,2);

			getstr(aux,binarystring,lengthmessage,28,11);                                        	 //Delta X
			sbasblock->orbitclockcorrection[DELTAX]=0.0625*twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.0625 metres 

			getstr(aux,binarystring,lengthmessage,39,11);                                      		 //Delta Y
			sbasblock->orbitclockcorrection[DELTAY]=0.0625*twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.0625 metres

			getstr(aux,binarystring,lengthmessage,50,11);                                        	 //Delta Z
			sbasblock->orbitclockcorrection[DELTAZ]=0.0625*twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.0625 metres 

			getstr(aux,binarystring,lengthmessage,61,12);                                      		 //Delta A f0
			sbasblock->orbitclockcorrection[DELTAB]=0.03125*twocomplementstrbintointeger(aux,12); //Delta B has a resolution of 0.03125 metres

			getstr(aux,binarystring,lengthmessage,73,8);                                          	 //Delta X Rate of Change
			sbasblock->orbitclockcorrection[DELTAXRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 metres/second

			getstr(aux,binarystring,lengthmessage,81,8);                                          	 //Delta Y Rate of Change
			sbasblock->orbitclockcorrection[DELTAYRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 metres/second

			getstr(aux,binarystring,lengthmessage,89,8);                                          	 //Delta Z Rate of Change
			sbasblock->orbitclockcorrection[DELTAZRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 metres/second

			getstr(aux,binarystring,lengthmessage,97,9);                                          	 //Delta A f1
			sbasblock->orbitclockcorrection[DELTABRATEOFCHANGE]=pow(2,-12)*twocomplementstrbintointeger(aux,8); //Delta B Rate has a resolution of 2^-12 metres/second

			getstr(aux,binarystring,lengthmessage,106,13);											//Time of Day Applicability 
			sbasblock->orbitclockcorrection[TIMEOFDAYAPPLICABILITY]=16.*(double)strtol(aux,&endptr,2);		//Time of Day Applicability to has a resolution of 16 seconds
			//if((int)sbasblock->orbitclockcorrection[TIMEOFDAYAPPLICABILITY]>86384) return -5;

			getstr(aux,binarystring,lengthmessage,218,4);                                        	 //DFREI
			sbasblock->orbitclockcorrection[DFREIPOS]=(double)strtol(aux,&endptr,2); 

			getstr(aux,binarystring,lengthmessage,222,4);                                        	 //RCORR
			sbasblock->orbitclockcorrection[RCORRMULT]=1./15.*(double)strtol(aux,&endptr,2); 

			//Get covariance parameters
			getstr(aux,binarystring,lengthmessage,119,3);			//Extract Scale Exponent
			sbasblock->covariancematrixdata[SCALEEXPONENT]=(double)strtol(aux,&endptr,2);	

			scalefactor=pow(2,sbasblock->covariancematrixdata[SCALEEXPONENT]-5.);

			sbasblock->covariancematrixdata[SCALEFACTOR]=scalefactor;

			getstr(aux,binarystring,lengthmessage,122,9);			//Extract E1,1
			sbasblock->covariancematrixdata[E11]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,131,9);			//Extract E2,2
			sbasblock->covariancematrixdata[E22]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,140,9);			//Extract E3,3
			sbasblock->covariancematrixdata[E33]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,149,9);			//Extract E4,4
			sbasblock->covariancematrixdata[E44]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,158,10);			//Extract E1,2
			sbasblock->covariancematrixdata[E12]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,168,10);			//Extract E1,3
			sbasblock->covariancematrixdata[E13]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,178,10);			//Extract E1,4
			sbasblock->covariancematrixdata[E14]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,188,10);			//Extract E2,3
			sbasblock->covariancematrixdata[E23]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,198,10);			//Extract E2,4
			sbasblock->covariancematrixdata[E24]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,208,10);			//Extract E3,4
			sbasblock->covariancematrixdata[E34]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			break;
		case OBADDFREIPARAMETERS: /*MT 37*/
			//Decode common OBAD parameters
			getstr(aux,binarystring,lengthmessage,10,6);			//Extract IvalidMT32
			sbasblock->commonOBAD[IVALIDMT32]=30.+6.*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,16,6);			//Extract IvalidMT39/40
			sbasblock->commonOBAD[IVALIDMT3940]=30.+6.*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,22,6);			//Extract CER
			sbasblock->commonOBAD[CERMT37]=0.5*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,28,7);			//Extract Ccovariance
			sbasblock->commonOBAD[CCOVARIANCEMT37]=0.1*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,221,3);			//Extract Time reference identifier
			sbasblock->commonOBAD[TIMEREFID]=(double)strtol(aux,&endptr,2);	

			//Decode OBAD parameters for each constellation
			for(i=0;i<5;i++) {
				j=constOBADorder[i];

				getstr(aux,binarystring,lengthmessage,35+i*21,5);			//Extract ICORR
				sbasblock->OBAD[j][ICORR]=30.+6.*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,35+i*21+5,8);			//Extract CCORR
				sbasblock->OBAD[j][CCORR]=0.01*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,35+i*21+13,8);			//Extract RCORR and transform from mm/s to m/s
				sbasblock->OBAD[j][RCORR]=(0.2/1000.)*(double)strtol(aux,&endptr,2);	
			}

			//Decode DREI table parameters
			getstr(aux,binarystring,lengthmessage,161,4);			//Extract DFREI0
			sbasblock->DFREITable[DFREI0]=DFREIminvalues[DFREI0]+0.0625*(double)strtol(aux,&endptr,2);	

			for(i=0;i<4;i++) {
				getstr(aux,binarystring,lengthmessage,165+i*4,4);			//Extract DFREI 1 to 4
				sbasblock->DFREITable[i+1]=DFREIminvalues[i+1]+0.125*(double)strtol(aux,&endptr,2);	
			}

			for(i=0;i<5;i++) {
				getstr(aux,binarystring,lengthmessage,181+i*4,4);			//Extract DFREI 5 to 9
				sbasblock->DFREITable[i+5]=DFREIminvalues[i+5]+0.25*(double)strtol(aux,&endptr,2);	
			}

			for(i=0;i<2;i++) {
				getstr(aux,binarystring,lengthmessage,201+i*4,4);			//Extract DFREI 10 to 11
				sbasblock->DFREITable[i+10]=DFREIminvalues[i+10]+0.5*(double)strtol(aux,&endptr,2);	
			}

			getstr(aux,binarystring,lengthmessage,209,4);			//Extract DFREI12
			sbasblock->DFREITable[DFREI12]=DFREIminvalues[DFREI12]+(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,213,4);			//Extract DFREI13
			sbasblock->DFREITable[DFREI13]=DFREIminvalues[DFREI13]+3.*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,217,4);			//Extract DFREI14
			if (options->SBASDFMCMT37version==MT37V1) {
				sbasblock->DFREITable[DFREI14]=DFREIminvalues[DFREI14]+6.*(double)strtol(aux,&endptr,2);	
			} else {
				sbasblock->DFREITable[DFREI14]=DFREIminvalues[DFREI14]+30.*(double)strtol(aux,&endptr,2);	
			}

			break;
		case SBASEPHEMERISDFMC: /*MT 39*/
			if (options->SBASDFMCMT3940version==MT3940V1) {
				getstr(aux,binarystring,lengthmessage,10,6);			//Extract satellite slot delta (converted to satellite slot number)
				sbasblock->sbasepehemeris1[SATSLOTNUMBER]=119.+(double)strtol(aux,&endptr,2);	
				if ((int)sbasblock->sbasepehemeris1[SATSLOTNUMBER]<120) return -11;
				else if ((int)sbasblock->sbasepehemeris1[SATSLOTNUMBER]>158) return -12;
				if ((int)sbasblock->sbasepehemeris1[SATSLOTNUMBER]!=sbasblock->PRN) return -13;

				getstr(aux,binarystring,lengthmessage,16,2);                                                //Extract Issue of Data G
				sbasblock->sbasepehemeris1[IODGNAVSBAS]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,18,5);                                                //Extract SBAS provider ID
				sbasblock->sbasepehemeris1[SBASPROVIDERID]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,23,19);                                                //Extract Cuc
				sbasblock->sbasepehemeris1[CUCNAVSBAS]=pow(2,-19)*Pi*1e-4*(double)twocomplementstrbintointeger(aux,19);

				getstr(aux,binarystring,lengthmessage,42,19);                                                //Extract Cus
				sbasblock->sbasepehemeris1[CUSNAVSBAS]=pow(2,-19)*Pi*1e-4*(double)twocomplementstrbintointeger(aux,19);

				getstr(aux,binarystring,lengthmessage,61,22);                                                //Extract Idot
				sbasblock->sbasepehemeris1[IDOTNAVSBAS]=pow(2,-21)*7./6.*Pi*1e-6*(double)twocomplementstrbintointeger(aux,22);

				getstr(aux,binarystring,lengthmessage,83,34);                                                //Extract argument of perigree
				sbasblock->sbasepehemeris1[PERIGREENAVSBAS]=pow(2,-33)*Pi*(double)twocomplementstrbintolonglonginteger(aux,34);

				getstr(aux,binarystring,lengthmessage,117,34);                                                //Extract longitude of ascending node
				sbasblock->sbasepehemeris1[ASCENDINGNAVSBAS]=pow(2,-33)*Pi*(double)twocomplementstrbintolonglonginteger(aux,34);

				getstr(aux,binarystring,lengthmessage,151,34);                                                //Extract mean anomaly
				sbasblock->sbasepehemeris1[ANOMALYNAVSBAS]=pow(2,-33)*Pi*(double)twocomplementstrbintolonglonginteger(aux,34);

				getstr(aux,binarystring,lengthmessage,185,25);                                                //Extract agf0
				sbasblock->sbasepehemeris1[AGF0NAVSBAS]=0.02*(double)twocomplementstrbintointeger(aux,25);

				getstr(aux,binarystring,lengthmessage,210,16);                                                //Extract agf1
				sbasblock->sbasepehemeris1[AGF1NAVSBAS]=4.*1e-5*(double)twocomplementstrbintointeger(aux,16);
			} else { //MT3940V044
				getstr(aux,binarystring,lengthmessage,10,6);			//Extract satellite slot delta (converted to satellite slot number)
				sbasblock->sbasepehemeris1[SATSLOTNUMBER]=119.+(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,16,2);                                                //Extract Issue of Data G
				sbasblock->sbasepehemeris1[IODGNAVSBAS]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,18,5);                                                //Extract SBAS provider ID
				sbasblock->sbasepehemeris1[SBASPROVIDERID]=(double)strtol(aux,&endptr,2);

				getstr(aux,binarystring,lengthmessage,23,22);                                                //Extract Cuc
				sbasblock->sbasepehemeris1[CUCNAVSBAS]=pow(2,-22)*Pi*1e-4*(double)twocomplementstrbintointeger(aux,22);

				getstr(aux,binarystring,lengthmessage,45,22);                                                //Extract Cus
				sbasblock->sbasepehemeris1[CUSNAVSBAS]=pow(2,-22)*Pi*1e-4*(double)twocomplementstrbintointeger(aux,22);

				getstr(aux,binarystring,lengthmessage,67,22);                                                //Extract Idot
				sbasblock->sbasepehemeris1[IDOTNAVSBAS]=pow(2,-21)*7./6.*Pi*1e-6*(double)twocomplementstrbintointeger(aux,22);

				getstr(aux,binarystring,lengthmessage,89,32);			//Extract eccentricity
				sbasblock->sbasepehemeris1[AXISNAVSBASV044]=6370000.+0.01*(double)strtoll(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,121,35);                                                //Extract argument of perigree
				sbasblock->sbasepehemeris1[PERIGREENAVSBAS]=pow(2,-34)*Pi*(double)twocomplementstrbintolonglonginteger(aux,35);

				getstr(aux,binarystring,lengthmessage,156,35);                                                //Extract longitude of ascending node
				sbasblock->sbasepehemeris1[ASCENDINGNAVSBAS]=pow(2,-34)*Pi*(double)twocomplementstrbintolonglonginteger(aux,35);

				getstr(aux,binarystring,lengthmessage,191,35);                                                //Extract mean anomaly
				sbasblock->sbasepehemeris1[ANOMALYNAVSBAS]=pow(2,-34)*Pi*(double)twocomplementstrbintolonglonginteger(aux,35);

			}

			break;
		case SBASEPHEMERISCOVARIANCEDFMC: /*MT 40*/
			getstr(aux,binarystring,lengthmessage,10,2);                                                  //Issue of Data G
			sbasblock->sbasepehemeris2[IODGNAVSBAS]=(double)strtol(aux,&endptr,2);
			sbasblock->covariancematrixdata[IODGPOSITIONNAVSBAS]=(double)strtol(aux,&endptr,2);

			if (options->SBASDFMCMT3940version==MT3940V1) {
				j=0;
				getstr(aux,binarystring,lengthmessage,12,33);			//Extract inclination of angle at te
				sbasblock->sbasepehemeris2[INCNAVSBAS]=pow(2,-33)*Pi*(double)strtoll(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,45,30);			//Extract eccentricity
				sbasblock->sbasepehemeris2[ECCNAVSBAS]=pow(2,-30)*(double)strtoll(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,75,31);			//Extract semi-major axis
				sbasblock->sbasepehemeris2[AXISNAVSBAS]=6370000.+0.02*(double)strtoll(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,106,13);			//Extract SBAS ephemeris time
				sbasblock->sbasepehemeris2[EPHTIMENAVSBAS]=16.*(double)strtol(aux,&endptr,2);	
				//if((int)sbasblock->sbasepehemeris2[EPHTIMENAVSBAS]>86384) return -5;

				getstr(aux,binarystring,lengthmessage,218,4);                                        	 //DFREI
				sbasblock->sbasepehemeris2[DFREINAVSBAS]=(double)strtol(aux,&endptr,2); 

				getstr(aux,binarystring,lengthmessage,222,4);                                        	 //RCORR
				sbasblock->sbasepehemeris2[RCORRMULTNAVSBAS]=1./15.*(double)strtol(aux,&endptr,2); 
			} else { //MT3940V044
				j=-3;
				getstr(aux,binarystring,lengthmessage,12,34);			//Extract inclination of angle at te
				sbasblock->sbasepehemeris2[INCNAVSBAS]=pow(2,-34)*Pi*(double)strtoll(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,46,31);			//Extract eccentricity
				sbasblock->sbasepehemeris2[ECCNAVSBAS]=pow(2,-31)*(double)strtoll(aux,&endptr,2);	

				sbasblock->sbasepehemeris2[AXISNAVSBAS]=0.;	//No Semi-major axis provided in V0.4.4

				getstr(aux,binarystring,lengthmessage,77,13);			//Extract eccentricity
				sbasblock->sbasepehemeris2[EPHTIMENAVSBAS]=16.*(double)strtol(aux,&endptr,2);	
				//if((int)sbasblock->sbasepehemeris2[EPHTIMENAVSBAS]>86384) return -5;

				getstr(aux,binarystring,lengthmessage,90,15);                                                //Extract agf0
				sbasblock->sbasepehemeris2[AGF0NAVSBASV044]=0.02*(double)twocomplementstrbintointeger(aux,15);

				getstr(aux,binarystring,lengthmessage,105,11);                                                //Extract agf1
				sbasblock->sbasepehemeris2[AGF1NAVSBASV044]=4.*1e-5*(double)twocomplementstrbintointeger(aux,11);

				getstr(aux,binarystring,lengthmessage,215,4);                                        	 //DFREI
				sbasblock->sbasepehemeris2[DFREINAVSBAS]=(double)strtol(aux,&endptr,2); 

				getstr(aux,binarystring,lengthmessage,219,4);                                        	 //RCORR
				sbasblock->sbasepehemeris2[RCORRMULTNAVSBAS]=1./15.*(double)strtol(aux,&endptr,2); 
			}
			getstr(aux,binarystring,lengthmessage,119+j,3);			//Extract Scale Exponent
			sbasblock->covariancematrixdata[SCALEEXPONENT]=strtol(aux,&endptr,2);	

			scalefactor=pow(2,sbasblock->covariancematrixdata[SCALEEXPONENT]-5.);

			sbasblock->covariancematrixdata[SCALEFACTOR]=scalefactor;

			getstr(aux,binarystring,lengthmessage,122+j,9);			//Extract E1,1
			sbasblock->covariancematrixdata[E11]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,131+j,9);			//Extract E2,2
			sbasblock->covariancematrixdata[E22]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,140+j,9);			//Extract E3,3
			sbasblock->covariancematrixdata[E33]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,149+j,9);			//Extract E4,4
			sbasblock->covariancematrixdata[E44]=scalefactor*(double)strtol(aux,&endptr,2);	

			getstr(aux,binarystring,lengthmessage,158+j,10);			//Extract E1,2
			sbasblock->covariancematrixdata[E12]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,168+j,10);			//Extract E1,3
			sbasblock->covariancematrixdata[E13]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,178+j,10);			//Extract E1,4
			sbasblock->covariancematrixdata[E14]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,188+j,10);			//Extract E2,3
			sbasblock->covariancematrixdata[E23]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,198+j,10);			//Extract E2,4
			sbasblock->covariancematrixdata[E24]=scalefactor*(double)twocomplementstrbintointeger(aux,10);

			getstr(aux,binarystring,lengthmessage,208+j,10);			//Extract E3,4
			sbasblock->covariancematrixdata[E34]=scalefactor*(double)twocomplementstrbintointeger(aux,10);
			break;
		case SBASNETWORKTIMEPARAMETERSDFMC: /*MT 42*/
			if (options->SBASDFMCMT42version==MT42V1) {
				//To be implement when new MT42 is in standard
			} else { //MT42V071
				//Decoding old version, which was removed in version MOPS DFMC v0.8 and will be reworked in future versions
				//This message was sent in the Australian testbed
				getstr(aux,binarystring,lengthmessage,10,24);				//Extract A1snt
				sbasblock->GNSSTimeOffsetsCommon[A1SNT]=pow(2,-50)*(double)twocomplementstrbintointeger(aux,24);	//A1wnt has a resolution of 2^-50 seconds/second

				getstr(aux,binarystring,lengthmessage,34,35);				//Extract A0snt
				sbasblock->GNSSTimeOffsetsCommon[A0SNT]=pow(2,-33)*(double)twocomplementstrbintolonglonginteger(aux,35);	//A0wnt has a resolution of 2^-33 seconds

				getstr(aux,binarystring,lengthmessage,69,8);				//Extract t0t
				sbasblock->GNSSTimeOffsetsCommon[T0T]=4096.*(double)strtol(aux,&endptr,2);			//t0t has a resolution of 4096 seconds
				if((int)sbasblock->GNSSTimeOffsetsCommon[T0T]>604799) return -6;

				getstr(aux,binarystring,lengthmessage,77,8);				//Extract WNt
				sbasblock->GNSSTimeOffsetsCommon[WNT]=(double)strtol(aux,&endptr,2);				//In weeks
				
				getstr(aux,binarystring,lengthmessage,85,8);				//Extract Delta tLS
				sbasblock->GNSSTimeOffsetsCommon[DELTATLS]=(double)twocomplementstrbintointeger(aux,8);		//Delta tLS has a resolution of 1 second

				getstr(aux,binarystring,lengthmessage,93,8);				//Extract WNlsf
				sbasblock->GNSSTimeOffsetsCommon[WNLSF]=(double)strtol(aux,&endptr,2);				//In weeks

				getstr(aux,binarystring,lengthmessage,101,3);				//Extract DN
				sbasblock->GNSSTimeOffsetsCommon[DNDAY]=(double)strtol(aux,&endptr,2);				//In days
				
				getstr(aux,binarystring,lengthmessage,104,8);				//Extract Delta tLSF 
				sbasblock->GNSSTimeOffsetsCommon[DELTATLSF]=(double)twocomplementstrbintointeger(aux,8);		//Delta tLSF has a resolution of 1 second

				getstr(aux,binarystring,lengthmessage,112,3);				//Extract UTC Standard Identifier
				sbasblock->GNSSTimeOffsetsCommon[UTCIDENTIFIER]=(double)strtol(aux,&endptr,2);

				for(i=0;i<4;i++) {
					j=constOBADorder[i];

					getstr(aux,binarystring,lengthmessage,115+i*21,1);			//Extract Validity indicator
					sbasblock->GNSSTimeOffsetsConst[j][VALIDITYIND]=(double)strtol(aux,&endptr,2);	

					getstr(aux,binarystring,lengthmessage,116+i*21,17);			//Extract Time offset with respect to SBAS Network time
					sbasblock->GNSSTimeOffsetsConst[j][TIMEOFFSETWRTSBAS]=pow(2,-33)*(double)strtol(aux,&endptr,2);	
				}
			}
			break;
		case SBASALMANACSDFMC: /*MT 47*/
			sbasblock->numgeoalmanacsDFMC=0;
			
			
			//Decode parameters
			for(i=0;i<2;i++) {
				if (i==0) {
					j=0;
				} else {
					if (options->SBASDFMCMT47version==MT47V1) {
						j=0;
					} else {
						//In version <=0.4.4, there was no WNRO and there were 2 spare bits between each satellite
						j=2;
					}
				}
				getstr(aux,binarystring,lengthmessage,10+i*106+j,6);			//Extract satellite slot delta (converted to satellite slot number)
				sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]=(double)strtol(aux,&endptr,2);	
				if ((int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]==0) continue;	//No almanac data
				sbasblock->numgeoalmanacsDFMC++;
				sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]+=119.; //Convert to satellite slot number
				if ((int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]>158) return -12;

				getstr(aux,binarystring,lengthmessage,16+i*106+j,5);			//Extract SBAS provider ID
				sbasblock->geoalmanacsDFMC[i][SBASPROVIDERID]=(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,21+i*106+j,1);			//Extract broadcast indicator
				sbasblock->geoalmanacsDFMC[i][BROADCASTIND]=(double)strtol(aux,&endptr,2);	
				if ((int)sbasblock->geoalmanacsDFMC[i][BROADCASTIND]==1) {
					// Broadcast indicator will only be 1 for the GEO PRN data matching the GEO broadcasting the message
					if (sbasblock->PRN!=(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]) return -14;
				}

				getstr(aux,binarystring,lengthmessage,22+i*106+j,16);			//Extract semi-major axis
				sbasblock->geoalmanacsDFMC[i][AXISALMANAC]=6370000.+650.*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,38+i*106+j,8);			//Extract eccentricity
				sbasblock->geoalmanacsDFMC[i][ECCALMANAC]=pow(2,-8)*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,46+i*106+j,13);			//Extract inclination
				sbasblock->geoalmanacsDFMC[i][INCALMANAC]=pow(2,-13)*Pi*(double)strtol(aux,&endptr,2);	

				getstr(aux,binarystring,lengthmessage,59+i*106+j,14);			//Extract argument of perigree
				sbasblock->geoalmanacsDFMC[i][PERIGREEALMANAC]=pow(2,-13)*Pi*(double)twocomplementstrbintointeger(aux,14);	

				getstr(aux,binarystring,lengthmessage,73+i*106+j,14);			//Extract longitude of ascending node
				sbasblock->geoalmanacsDFMC[i][ASCENDINGAALMANAC]=pow(2,-13)*Pi*(double)twocomplementstrbintointeger(aux,14);	

				getstr(aux,binarystring,lengthmessage,87+i*106+j,8);			//Extract rate of right ascension
				sbasblock->geoalmanacsDFMC[i][ASCENSIONAALMANAC]=-1e-9*(double)twocomplementstrbintointeger(aux,8);	

				getstr(aux,binarystring,lengthmessage,95+i*106+j,15);			//Extract mean anomaly at ta
				sbasblock->geoalmanacsDFMC[i][ANOMALYAALMANAC]=pow(2,-14)*Pi*(double)twocomplementstrbintointeger(aux,15);	

				getstr(aux,binarystring,lengthmessage,110+i*106+j,6);			//Extract almanac reference epoch ta
				sbasblock->geoalmanacsDFMC[i][REFEPOCHALMANAC]=1800.*(double)strtol(aux,&endptr,2);	
				//if((int)sbasblock->geoalmanacsDFMC[i][REFEPOCHALMANAC]>86384) return -5;

				if (options->SBASDFMCMT47version==MT47V1) {
					getstr(aux,binarystring,lengthmessage,222,4);			//Week number roll over count
					sbasblock->geoalmanacsDFMC[i][WNR0COUNTALMANAC]=(double)strtol(aux,&endptr,2);	
				} else {
					//No WNR0COUNTALMANAC in version <= 0.4.4
					sbasblock->geoalmanacsDFMC[i][WNR0COUNTALMANAC]=15.;	
				}
			}
			break;
		case INTERNALTESTMESSAGE: /*MT 62*/
			if(sbasblock->frequency==5) {
				//For Australia SBAS DFMC test bed, there is a flag indicating if it is using GPS L1/L5 or L1/L2C
				getstr(aux,binarystring,lengthmessage,27,4);                //Extract flag
				sbasblock->GPSfrequenciesUsed=strtol(aux,&endptr,2);		//Flag = 0 => not set (using default L1/L5)
																			//Flag = 1 => using L1/L2
																			//Flag = 2 => using L1/L5
			}
			break;
		case SERVICEAREADFMC: /*MT 48*/ case SERVICEAREADFMCTESTBED: /*MT 50*/
			//DFMC messages not in standard
			break;
		case RESERVED8: case RESERVED11: case RESERVED13: case RESERVED14: case RESERVED15: case RESERVED16: case RESERVED19: case RESERVED20: case RESERVED21: case RESERVED22: case RESERVED23: case NULLMESSAGE:
			//Messages with no data that do not have any effect 
			return 0;
			break;
		default:
			//Unknown message type
			return -8;
			break;

	}
	//Message valid and correctly read
	return 1;
}

/*****************************************************************************
 * Name        : updateSBASdata
 * Description : Update the SBAS data with the next message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBASdatabox *SBASdatabox       IO N/A  Structure to save SBAS data
 * TSBASdata  *SBASdata            IO N/A  Structure to save SBAS data
 * TSBASblock  *sbasblock          I  N/A  TSBASblock structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void updateSBASdata (TSBASdatabox *SBASdatabox, TSBASdata  *SBASdata, TSBASblock  *sbasblock, TOptions  *options) {

	int 				i,j,k,l,m,n;
	int 				pos,GEObuffer;
	int					currentbandnumber,currentblockID,currentIODI;
	int					posFC;
	int					iodpposition;
	int					msgtimeout;
	int					dataDestMode;
	int					checkforIonobuffered,IODImaskVal;
	int					*BlockIDPlace2GridPtr;
	int					effectiveMessageType;
	static int			initpos;
	static int			posIndex[2];
	static int			initialized=0;
	static int			ionobuffered[MAX_SBAS_PRN][11][14]; //One for each band number and Block ID
	static int			MT39buffered[MAX_SBAS_PRN],MT40buffered[MAX_SBAS_PRN];
	static int			anyIonoCorrBuffered[MAX_SBAS_PRN];
	static double		sbasepehemeris1Buffer[MAX_SBAS_PRN][11];
	static double		sbasepehemeris2Buffer[MAX_SBAS_PRN][9];
	static double		covariancematrixdataBuffer[MAX_SBAS_PRN][14];
	static TTime		MT39bufferedtime[MAX_SBAS_PRN],MT40bufferedtime[MAX_SBAS_PRN];

	if(initialized==0) {
		//Check if mixed GEO is allowed
		if (options->GEOPRN==0 || (options->mixedGEOdata==1 && options->switchGEO==1)) {
			initpos=0;
		} else {
			initpos=1;
		}
		posIndex[0]=0;
				
		SBASdatabox->ionobuffer=malloc(sizeof(TSBASblockIono*)*MAX_SBAS_PRN);
		for(m=0;m<MAX_SBAS_PRN;m++) {
			MT39buffered[m]=0;
			MT40buffered[m]=0;
			anyIonoCorrBuffered[m]=0;
			SBASdatabox->ionobuffer[m]=malloc(sizeof(TSBASblockIono*)*11);
			for(i=0;i<11;i++) {
				SBASdatabox->ionobuffer[m][i]=malloc(sizeof(TSBASblockIono)*14);
				for(j=0;j<14;j++) {
					//initSBASblock(&SBASdatabox->ionobuffer[m][i][j]);
					//Allocate memory for Ionospheric Delay Corrections
					//SBASdatabox->ionobuffer[m][i][j].ionodelayparameters=malloc(sizeof(double*)*15); 		//Message 26 has 15 Grid Points
					for(k=0;k<15;k++) {
					//	SBASdatabox->ionobuffer[m][i][j].ionodelayparameters[k]=malloc(sizeof(double)*7);	//Each block will have 5 parameters + 2 for the GIVE value and variance
						for(l=0;l<7;l++) {
							SBASdatabox->ionobuffer[m][i][j].ionodelayparameters[k][l]=-1.;			//-1 means value not set
						}
					}
					ionobuffered[m][i][j]=0;
				}
			}
		}
		initialized=1;
	}

	//If we have one satellite in alarm (which lasts one minute), ignore its messages
	if(SBASdata[0].alarmGEOPRN[sbasblock->frequencyPos][sbasblock->PRN]==sbasblock->PRN && sbasblock->messagetype!=DONTUSE) return;

	posIndex[1]=SBASdata[0].GEOPRN2pos[sbasblock->PRN];

	//Select PRN slots to be updated (the slot with mixed PRN data and the slot with only 1 satellite)
	for(n=initpos;n<2;n++) {
		pos=posIndex[n];

		//New message. Update data only if the current slot is the mixed one (position 0 or the one of the current PRN) 

		if(SBASdata[pos].firstmessage[sbasblock->frequencyPos].MJDN==-1) {
			SBASdata[pos].firstmessage[sbasblock->frequencyPos].MJDN=sbasblock->t.MJDN;
			SBASdata[pos].firstmessage[sbasblock->frequencyPos].SoD=sbasblock->t.SoD;
		}

		switch(sbasblock->messagetype) {
			case PRNMASKASSIGNMENTS: /*MT 1*/
				//Check if we have a PRN Mask
				if(sbasblock->IODP!=SBASdata[pos].IODPmask) {
					//New Mask. Save the old mask, so we can still use messages 
					memcpy(SBASdata[pos].pos2PRN[sbasblock->frequencyPos][sbasblock->IODP],sbasblock->pos2PRN,sizeof(int)*51);
					memcpy(SBASdata[pos].pos2GNSS[sbasblock->frequencyPos][sbasblock->IODP],sbasblock->pos2GNSS,sizeof(enum GNSSystem)*51);
					/*for(i=0;i<51;i++) {
						SBASdata[pos].pos2PRN[sbasblock->frequencyPos][sbasblock->IODP][i]=sbasblock->pos2PRN[i];
						SBASdata[pos].pos2GNSS[sbasblock->frequencyPos][sbasblock->IODP][i]=sbasblock->pos2GNSS[i];
					}*/
					memcpy(SBASdata[pos].PRNactive[sbasblock->frequencyPos][sbasblock->IODP],sbasblock->PRNactive,sizeof(int)*MAX_GNSS*MAX_SBAS_PRN);
					memcpy(SBASdata[pos].PRN2pos[sbasblock->frequencyPos][sbasblock->IODP],sbasblock->PRN2pos,sizeof(int)*MAX_GNSS*MAX_SBAS_PRN);
					/*for(i=0;i<MAX_GNSS;i++) {
						for(j=0;j<MAX_SBAS_PRN;j++) {
							SBASdata[pos].PRNactive[sbasblock->frequencyPos][sbasblock->IODP][i][j]=sbasblock->PRNactive[i][j];
							SBASdata[pos].PRN2pos[sbasblock->frequencyPos][sbasblock->IODP][i][j]=sbasblock->PRN2pos[i][j];
						}
					}*/
					SBASdata[pos].oldIODPmask=SBASdata[pos].IODPmask;

					SBASdata[pos].IODPmask=sbasblock->IODP;
					SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODP]=sbasblock->numsatellites;
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;

					SBASdata[pos].oldmaskdiscarded[sbasblock->frequencyPos][sbasblock->messagetype]=0;

					//Set all other masks to -1
					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].oldIODPmask && i!=SBASdata[pos].IODPmask) {
							SBASdata[pos].numsatellites[sbasblock->frequencyPos][i]=0;
							for(j=0;j<MAX_GNSS;j++) {
								for(k=0;k<MAX_SBAS_PRN;k++) {
									SBASdata[pos].PRNactive[sbasblock->frequencyPos][i][j][k]=-1;
									SBASdata[pos].PRN2pos[sbasblock->frequencyPos][i][j][k]=-1;
								}
							}
						}
					}

					//Update constellations monitored
					//Only need to update once (when it is not mixed GEO), as constellation monitored is saved in Toptions structure
					//Reset constellation list
					options->numSBASConstList[pos][SBAS1FMODEPOS]=0;
					for(i=0;i<MAX_GNSS;i++) {
						options->SBASConstUsed[pos][SBAS1FMODEPOS][i]=sbasblock->constMonitored[i];
						if (sbasblock->constMonitored[i]==1 && options->ConstellationUsed[i]==1) {
							options->SBASConstList[pos][SBAS1FMODEPOS][options->numSBASConstList[pos][SBAS1FMODEPOS]]=i;
							options->numSBASConstList[pos][SBAS1FMODEPOS]++;
						} else {
							options->SBASConstList[pos][SBAS1FMODEPOS][i]=-1;
						}
					}
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case DONTUSE: /*MT 0*/
				if(options->usetype0messages==0) {
					//Alarm messages are ignored
					break;
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				SBASdata[pos].problems[sbasblock->frequencyPos]=sbasblock->problems;
				if(sbasblock->problems==1) {
					//This means that the message is all 0. There is no type 2 message data
					SBASdata[pos].dontuse[sbasblock->frequencyPos]=sbasblock->dontuse;
					if(pos!=0) {
						//If mixed GEO is not enabled, we set alarm also to the mixed GEO, as the alarm condition is checked with the mixed GEO
						SBASdata[0].dontuse[sbasblock->frequencyPos]=sbasblock->dontuse;
						//Save the PRN of the GEO that received the alarm
						if (SBASdata[0].alarmGEOPRN[sbasblock->frequencyPos][sbasblock->PRN]==-1) {
							//Alarm not already received from current GEO
							SBASdata[0].alarmGEOPRN[sbasblock->frequencyPos][sbasblock->PRN]=sbasblock->PRN;
							//Save the index position of the GEO with alarm
							SBASdata[0].alarmGEOindex[sbasblock->frequencyPos][SBASdata[0].numAlarmGEO[sbasblock->frequencyPos]]=pos;
							//Increase by one the number of GEOs with alarm
							SBASdata[0].numAlarmGEO[sbasblock->frequencyPos]++;
						}
						//Set the remaining alarm time to 60 seconds
						SBASdata[pos].alarmTimeRemaining[sbasblock->frequencyPos]=60;
						SBASdata[0].alarmTimeRemaining[sbasblock->frequencyPos]=60;
					}
					break;
				}
				if(options->useAlarmmessageForCorrections==0) {
					//Decode message type 0 as it is
					SBASdata[pos].dontuse[sbasblock->frequencyPos]=sbasblock->dontuse;
					if(pos!=0) {
						//If mixed GEO is not enabled, we set alarm also to the mixed GEO, as the alarm condition is checked with the mixed GEO
						SBASdata[0].dontuse[sbasblock->frequencyPos]=sbasblock->dontuse;
						if (SBASdata[0].alarmGEOPRN[sbasblock->frequencyPos][sbasblock->PRN]==-1) {
							//Save the PRN of the GEO that received the alarm
							SBASdata[0].alarmGEOPRN[sbasblock->frequencyPos][sbasblock->PRN]=sbasblock->PRN;
							//Save the index position of the GEO with alarm
							SBASdata[0].alarmGEOindex[sbasblock->frequencyPos][SBASdata[0].numAlarmGEO[sbasblock->frequencyPos]]=pos;
							//Increase by one the number of GEOs with alarm
							SBASdata[0].numAlarmGEO[sbasblock->frequencyPos]++;
							//Set the remaining alarm time to 60 seconds
							SBASdata[pos].alarmTimeRemaining[sbasblock->frequencyPos]=60;
							SBASdata[0].alarmTimeRemaining[sbasblock->frequencyPos]=60;
						}
					}
					break;
				}
				//If in SBAS DFMC message type is 0 and the spare bits are set to 0,
				//it means that no message type 34, 35 or 36 is embedded in message type 0
				if (sbasblock->frequency==5 && sbasblock->msg0type==0) break;
				//No break here because message will be decoded as type 2 for SBAS 1F
				// or type 34, 35 or 36 for SBAS DFMC
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case FASTCORRECTIONS2: /*MT 2*/ case FASTCORRECTIONS3: /*MT 3*/ case FASTCORRECTIONS4: /*MT 4*/ case FASTCORRECTIONS5: /*MT 5*/
				
				if (sbasblock->frequency==1) {
					if(SBASdata[pos].IODPfastcorr!=sbasblock->IODP) {
						SBASdata[pos].oldIODPfastcorr=SBASdata[pos].IODPfastcorr;
						SBASdata[pos].IODPfastcorr=sbasblock->IODP;

						for(i=0;i<5;i++) {
							if(i!=SBASdata[pos].IODPfastcorr && i!=SBASdata[pos].oldIODPfastcorr) {
								for(j=0;j<MAXSBASFASTCORR;j++) {
									for(k=0;k<51;k++) {
										SBASdata[pos].poslastFC[i][k] = -1;
										SBASdata[pos].numFC[i][k] = 0;
										SBASdata[pos].PRC[i][j][k] = 9999;
										SBASdata[pos].RRC[i][j][k] = 9999;
										SBASdata[pos].UDREI[i][j][k] = -1;
										SBASdata[pos].UDRE[i][j][k] = -1;
										SBASdata[pos].UDREsigma[i][j][k] = -1;
										SBASdata[pos].IODF[i][j][k] = -1;
										SBASdata[pos].lastfastcorrections[i][j][k].MJDN = -1;
										SBASdata[pos].lastfastcorrections[i][j][k].SoD = -1;
									}
								}
							}
						}
					}

					if(sbasblock->messagetype==DONTUSE) {
						i=0;
						effectiveMessageType=FASTCORRECTIONS2;
					} else {
						i=(sbasblock->messagetype-2)*13;
						effectiveMessageType=sbasblock->messagetype;
					}

					for(j=i,k=0;j<(effectiveMessageType-1)*13;j++,k++) {

						SBASdata[pos].poslastFC[sbasblock->IODP][j]=mod(SBASdata[pos].poslastFC[sbasblock->IODP][j]+1,MAXSBASFASTCORR);
						posFC=SBASdata[pos].poslastFC[sbasblock->IODP][j];

						SBASdata[pos].numFC[sbasblock->IODP][j]=SBASdata[pos].numFC[sbasblock->IODP][j]+1;
						if(SBASdata[pos].numFC[sbasblock->IODP][j]>MAXSBASFASTCORR) SBASdata[pos].numFC[sbasblock->IODP][j]=MAXSBASFASTCORR;

						SBASdata[pos].PRC[sbasblock->IODP][posFC][j]=sbasblock->PRC[k];
						SBASdata[pos].UDREI[sbasblock->IODP][posFC][j]=sbasblock->UDREI[k];
						SBASdata[pos].UDRE[sbasblock->IODP][posFC][j]=sbasblock->UDRE[k];
						SBASdata[pos].UDREsigma[sbasblock->IODP][posFC][j]=sbasblock->UDREsigma[k];
						SBASdata[pos].IODF[sbasblock->IODP][posFC][j]=sbasblock->IODF[0];

						SBASdata[pos].lastfastcorrections[sbasblock->IODP][posFC][j].MJDN=sbasblock->t.MJDN;
						SBASdata[pos].lastfastcorrections[sbasblock->IODP][posFC][j].SoD=sbasblock->t.SoD;

						//Save last fast message for satellites in current message
						SBASdata[pos].lastfastmessage[j]=effectiveMessageType;
					}

					//Update last received message
					SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][effectiveMessageType].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][effectiveMessageType].SoD=sbasblock->t.SoD;
					break;	
				}
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case INTEGRITYINFODFMC34: /*MT 34*/
				if (sbasblock->msg0type==1) {
					j=0;
					if (sbasblock->IODM!=SBASdata[pos].IODMmask && sbasblock->IODM!=SBASdata[pos].oldIODMmask) continue; //No mask received for current data
					for(i=0;i<SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODM];i++) {
						switch(sbasblock->DFRECI[i]) {
							case 0:
								//DFRECI is 0, which means that DFREI doesn't change, so timeout is refreshed
								//If previous DFREI has timed out, do not refresh timeout
								//In the case no DFREI was received before, lastDFREIreceived will be -1 (therefore the tdiff will be over the threshold)
								if (tdiff(&sbasblock->t,&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i])<=SBASdata[pos].timeoutmessages[sbasblock->frequencyPos][options->precisionapproach][INTEGRITYINFODFMC34]) {
									//DFREI not timeout, therefore we can refresh timeout
									memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
								}
								break;
							case 1:
								//DFRECI=1 means that DFREI has changed and therefore its value is transmitted in MT34
								//In MT34 there are only 7 slots for transmitting new DFREIs, so the first 7 satellites
								//with DFRECI=1 will have their DFREI updated in this message
								if (j<7) {
									SBASdata[pos].DFREI[sbasblock->IODM][i]=sbasblock->DFREI[j];
									SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]=0;	//Set no bump applied to DFREI
									memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
									j++;
								} else {
									//Set DFREI to 16. Value 16 is not in MOPS, but this is to indicate that the satellite
									//cannot be used due to the DFREI has changed but we don't have the new value.
									//Do not update time-out as we don't know the new value of the DFREI
									//According to SBAS SARPS, this case should never occur, but if it occurs, it will
									//be visible to the user in the unselection message
									SBASdata[pos].DFREI[sbasblock->IODM][i]=16;
								}
								break;
							case 2:
								//DFRECI is 2 which means that DFREI is increased by 1, so timeout is refreshed
								//If we don't have a previous DFREI or current DFREI has timeout, don't refresh timeout
								//and don't save the DFRECI value, as we can only apply the bump to a valid DFREI
								//In the case no DFREI was received before, lastDFREIreceived will be -1 (therefore the tdiff will be over the threshold)
								if (tdiff(&sbasblock->t,&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i])<=SBASdata[pos].timeoutmessages[sbasblock->frequencyPos][options->precisionapproach][INTEGRITYINFODFMC34]) {
									//If DFREI is 16, means that DFREI value changed but we don't have the new value, so we can't
									//add a bump to the current DFREI if we don't know the current value
									if (SBASdata[pos].DFREI[sbasblock->IODM][i]!=16) {
										if (SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]==0) {
											//DFRECI not bumped. Add 1 to DFREI (only if DFREI is not 15)
											if (SBASdata[pos].DFREI[sbasblock->IODM][i]<15) {
												SBASdata[pos].DFREI[sbasblock->IODM][i]++;
											}
											SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]=1;
										}
										memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
									}
								}
								break;
							default: //case 3:
								//DFRECI is 3, which means that satellite is unselected.
								//Timeout is updated although is not really necessary, as satellite will not be used
								//Also set DFRECI bump indicator to 0 as we have a new DFREI (don't use)
								SBASdata[pos].DFREI[sbasblock->IODM][i]=15;
								SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]=0;
								memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
								break;
						}
					}
					//Update last received message (the message type is manually set as it me be received inside a MT0 message)
					memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][INTEGRITYINFODFMC34],&sbasblock->t,sizeof(TTime));
					break;
				}
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case INTEGRITYINFODFMC35: /*MT 35*/
				if (sbasblock->msg0type==2) {
					if (sbasblock->IODM!=SBASdata[pos].IODMmask && sbasblock->IODM!=SBASdata[pos].oldIODMmask) continue; //No mask received for current data
					//If number of monitored satellites is less than 53, loop only on the number of monitored satellites
					if (SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODM]<53) {
						j=SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODM];
					} else {
						j=53;
					}
					for(i=0;i<j;i++) {
						SBASdata[pos].DFREI[sbasblock->IODM][i]=sbasblock->DFREI[i];
						SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]=0;	//Set no bump applied to DFREI
						memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
					}
					//Update last received message (the message type is manually set as it me be received inside a MT0 message)
					memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][INTEGRITYINFODFMC35],&sbasblock->t,sizeof(TTime));
					break;
				}
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case INTEGRITYINFODFMC36: /*MT 36*/
				if (sbasblock->IODM!=SBASdata[pos].IODMmask && sbasblock->IODM!=SBASdata[pos].oldIODMmask) continue; //No mask received for current data
				for(i=53;i<SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODM];i++) {
					SBASdata[pos].DFREI[sbasblock->IODM][i]=sbasblock->DFREI[i-53];
					SBASdata[pos].DFRECI2bumped[sbasblock->IODM][i]=0;	//Set no bump applied to DFREI
					memcpy(&SBASdata[pos].lastDFREIreceived[sbasblock->IODM][i],&sbasblock->t,sizeof(TTime));
				}
				//Update last received message (the message type is manually set as it me be received inside a MT0 message)
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][INTEGRITYINFODFMC36],&sbasblock->t,sizeof(TTime));
				break;
			case INTEGRITYINFO: /*MT 6*/

				if(SBASdata[pos].IODPfastcorr==4) {
					//No message type 2-5 or 24 received, so we don't have any IODP for the fast corrections.
					//This message has no IODP, it uses the last one received in messages 2-5 or 24.
					//There is the case that when IODP changes and we miss fast corrections messages with the
					//new IODP, and then this message type (6), we will decode with the wrong mask.
					//There is no reference to this case in MOPS, but it can be avoided if after changing
					//the IODP, message type 6 is not sent during some time to make sure any receiver gets
					//a type 2-5 or 24 message with the new IODP.
					break;
				}

				for(i=0;i<51;i++) {
					//Save old values only if the IODF from previous message type 6 differs
					//This is because previous type 6 messages are useless except when IODF differs from the last IODF received, and
					//the last IODF received does not match the last IODF received in message type 2-5,24
					if(SBASdata[pos].IODFintegrity[i]!=sbasblock->IODF[(int)(i/13)]) {
						SBASdata[pos].oldUDREI6[i]=SBASdata[pos].UDREI6[i];
						SBASdata[pos].oldUDRE6[i]=SBASdata[pos].UDRE6[i];
						SBASdata[pos].oldUDREsigma6[i]=SBASdata[pos].UDREsigma6[i];
						SBASdata[pos].oldIODFintegrity[i]=SBASdata[pos].IODFintegrity[i];
						SBASdata[pos].oldlastintegrityinfo[i].MJDN=SBASdata[pos].lastintegrityinfo[i].MJDN;
						SBASdata[pos].oldlastintegrityinfo[i].SoD=SBASdata[pos].lastintegrityinfo[i].SoD;
					}
					//Save new values
					SBASdata[pos].UDREI6[i]=sbasblock->UDREIacu[i];
					SBASdata[pos].UDRE6[i]=sbasblock->UDREacu[i];
					SBASdata[pos].UDREsigma6[i]=sbasblock->UDREacusigma[i];
					SBASdata[pos].IODFintegrity[i]=sbasblock->IODF[(int)(i/13)];

					SBASdata[pos].lastintegrityinfo[i].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastintegrityinfo[i].SoD=sbasblock->t.SoD;

					//Save last fast message for all satellites
					SBASdata[pos].lastfastmessage[i]=sbasblock->messagetype;
				}

				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;	
			case FASTCORRECTIONSDEGRADATIONFACTOR: /*MT 7*/

				if(SBASdata[pos].IODPdegcorr!=sbasblock->IODP) {
					SBASdata[pos].oldIODPdegcorr=SBASdata[pos].IODPdegcorr;
					SBASdata[pos].IODPdegcorr=sbasblock->IODP;
					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].IODPdegcorr && i!=SBASdata[pos].oldIODPdegcorr) {
							SBASdata[pos].tlat[i]=0;
							for(j=0;j<51;j++) {
								SBASdata[pos].aifactor[i][j]=-1;
								SBASdata[pos].fastcorrtimeout[0][i][j]=-1;
								SBASdata[pos].fastcorrtimeout[1][i][j]=-1;
								SBASdata[pos].fastcorrupdateinterval[i][j]=-1;
								SBASdata[pos].lastfastdegfactor[i][j].MJDN=-1;
								SBASdata[pos].lastfastdegfactor[i][j].SoD=-1;
							}
						}
					}
				}

				memcpy(SBASdata[pos].aifactor[sbasblock->IODP],sbasblock->aifactor,sizeof(double)*51);
				memcpy(SBASdata[pos].fastcorrtimeout[0][sbasblock->IODP],sbasblock->timeoutintervalnonprecise,sizeof(int)*51);
				memcpy(SBASdata[pos].fastcorrtimeout[1][sbasblock->IODP],sbasblock->timeoutintervalprecise,sizeof(int)*51);
				memcpy(SBASdata[pos].fastcorrupdateinterval[sbasblock->IODP],sbasblock->fastcorrupdateinterval,sizeof(int)*51);
				for(i=0;i<51;i++) {
				/*	SBASdata[pos].aifactor[sbasblock->IODP][i]=sbasblock->aifactor[i];	
					SBASdata[pos].fastcorrtimeout[0][sbasblock->IODP][i]=sbasblock->timeoutintervalnonprecise[i];	
					SBASdata[pos].fastcorrtimeout[1][sbasblock->IODP][i]=sbasblock->timeoutintervalprecise[i];	
					SBASdata[pos].fastcorrupdateinterval[sbasblock->IODP][i]=sbasblock->fastcorrupdateinterval[i];	*/
					SBASdata[pos].lastfastdegfactor[sbasblock->IODP][i].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastfastdegfactor[sbasblock->IODP][i].SoD=sbasblock->t.SoD;
				}

				SBASdata[pos].tlat[sbasblock->IODP]=sbasblock->tlat;
				SBASdata[pos].IODPdegcorr=sbasblock->IODP;

				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case DEGRADATIONPARAMETERS: /*MT 10*/

				memcpy(SBASdata[pos].olddegradationfactors,SBASdata[pos].degradationfactors,sizeof(double)*16);
				memcpy(SBASdata[pos].degradationfactors,sbasblock->degradationfactors,sizeof(double)*16);
			/*	for(i=0;i<16;i++) {
					//Save old values
					SBASdata[pos].olddegradationfactors[i]=SBASdata[pos].degradationfactors[i];	

					//Save new values
					SBASdata[pos].degradationfactors[i]=sbasblock->degradationfactors[i];
				}*/	

				//Update last received message 
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case LONGTERMSATELLITECORRECTIONS: /*MT 25*/
				//Check if IODP has changed
				if(SBASdata[pos].IODPlongterm!=sbasblock->longtermsaterrcorrections[0][IODPPOSITION]) {
					//IODP has changed. Save the old values and initialize the current one
					SBASdata[pos].oldIODPlongterm=SBASdata[pos].IODPlongterm;
					SBASdata[pos].IODPlongterm=(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION];
					for(i=0;i<51;i++) {
						for(j=0;j<15;j++) {
							for(k=0;k<4;k++) {
								if(k!=SBASdata[pos].oldIODPlongterm && k!=SBASdata[pos].IODPlongterm) {
									//Initialize the other IODP blocks
									SBASdata[pos].longtermsaterrcorrections[k][i][j]=9999;
									SBASdata[pos].lastlongtermdata[k][i].MJDN=-1;
									SBASdata[pos].lastlongtermdata[k][i].SoD=-1;
									SBASdata[pos].prevlongtermsaterrcorrections[k][i][j]=9999;
									SBASdata[pos].prevlastlongtermdata[k][i].MJDN=-1;
									SBASdata[pos].prevlastlongtermdata[k][i].SoD=-1;
								}
							}
						}
					}
				}
				//Save new values
				for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
					if(sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]==0) continue; //PRNMASKNUMBER=0 means that there is no valid data
					//Substract one because our PRN Mask number goes from 0 to 50
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]-1;
					j=(int)sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER];
					//Check if IODE has changed. Save the previous message if it has changed
					if(SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][ISSUEOFDATA]!=sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]) {
						//IODE has changed
						memcpy(SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],sizeof(double)*15);
						/*for(k=0;k<15;k++) {
							SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k];
						}*/
						//Update last received message for the given PRNs
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN;
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD;
					}

					memcpy(SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],sbasblock->longtermsaterrcorrections[i],sizeof(double)*15);
					/*for(k=0;k<15;k++) {
						SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=sbasblock->longtermsaterrcorrections[i][k];
					}*/
					//Update last received message for the given PRNs
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=sbasblock->t.SoD;

					//Leave sbasblock as it was
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]+1;

				}
				break;
			case MIXEDFASTLONGTERMCORRECTIONS: /*MT 24*/
				//FASTCORRECTIONS
				if(SBASdata[pos].IODPfastcorr!=sbasblock->IODP) {
					SBASdata[pos].oldIODPfastcorr=SBASdata[pos].IODPfastcorr;
					SBASdata[pos].IODPfastcorr=sbasblock->IODP;

					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].IODPfastcorr && i!=SBASdata[pos].oldIODPfastcorr) {
							for(j=0;j<MAXSBASFASTCORR;j++) {
								for(k=0;k<51;k++) {
									SBASdata[pos].poslastFC[i][k] = -1;
									SBASdata[pos].numFC[i][k] = 0;
									SBASdata[pos].PRC[i][j][k] = 9999;
									SBASdata[pos].RRC[i][j][k] = 9999;
									SBASdata[pos].UDREI[i][j][k] = -1;
									SBASdata[pos].UDRE[i][j][k] = -1;
									SBASdata[pos].UDREsigma[i][j][k] = -1;
									SBASdata[pos].IODF[i][j][k] = -1;
									SBASdata[pos].lastfastcorrections[i][j][k].MJDN = -1;
									SBASdata[pos].lastfastcorrections[i][j][k].SoD = -1;
								}
							}
						}
					}
				}

				i=(sbasblock->BlockID-2)*13;

				for(j=i,k=0;j<((sbasblock->BlockID-2)*13)+6;j++,k++) {

					SBASdata[pos].poslastFC[sbasblock->IODP][j]=mod(SBASdata[pos].poslastFC[sbasblock->IODP][j]+1,MAXSBASFASTCORR);
					posFC=SBASdata[pos].poslastFC[sbasblock->IODP][j];

					SBASdata[pos].numFC[sbasblock->IODP][j]=SBASdata[pos].numFC[sbasblock->IODP][j]+1;
					if(SBASdata[pos].numFC[sbasblock->IODP][j]>MAXSBASFASTCORR) SBASdata[pos].numFC[sbasblock->IODP][j]=MAXSBASFASTCORR;

					SBASdata[pos].PRC[sbasblock->IODP][posFC][j]=sbasblock->PRC[k];
					SBASdata[pos].UDREI[sbasblock->IODP][posFC][j]=sbasblock->UDREI[k];
					SBASdata[pos].UDRE[sbasblock->IODP][posFC][j]=sbasblock->UDRE[k];
					SBASdata[pos].UDREsigma[sbasblock->IODP][posFC][j]=sbasblock->UDREsigma[k];
					SBASdata[pos].IODF[sbasblock->IODP][posFC][j]=sbasblock->IODF[0];

					SBASdata[pos].lastfastcorrections[sbasblock->IODP][posFC][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastfastcorrections[sbasblock->IODP][posFC][j].SoD=sbasblock->t.SoD;

					//Save last fast message for satellites in current message
					SBASdata[pos].lastfastmessage[j]=sbasblock->messagetype;
				}

				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				//LONGTERMSATELLITECORRECTIONS
				//Check if IODP has changed
				if(SBASdata[pos].IODPlongterm!=sbasblock->longtermsaterrcorrections[0][IODPPOSITION]) {
					//IODP has changed. Save the old values and initialize the current one
					SBASdata[pos].oldIODPlongterm=SBASdata[pos].IODPlongterm;
					SBASdata[pos].IODPlongterm=(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION];
					for(i=0;i<51;i++) {
						for(j=0;j<15;j++) {
							for(k=0;k<4;k++) {
								if(k!=SBASdata[pos].oldIODPlongterm && k!=SBASdata[pos].IODPlongterm) {
									//Initialize the other IODP blocks
									SBASdata[pos].longtermsaterrcorrections[k][i][j]=9999;
									SBASdata[pos].lastlongtermdata[k][i].MJDN=-1;
									SBASdata[pos].lastlongtermdata[k][i].SoD=-1;
									SBASdata[pos].prevlongtermsaterrcorrections[k][i][j]=9999;
									SBASdata[pos].prevlastlongtermdata[k][i].MJDN=-1;
									SBASdata[pos].prevlastlongtermdata[k][i].SoD=-1;
								}
							}
						}
					}
				}
				//Save new values
				for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
					if(sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]==0) continue; //PRNMASKNUMBER=0 means that there is no valid data
					//Substract one because our PRN Mask number goes from 0 to 50
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]-1;
					j=(int)sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER];
					//Check if IODE has changed. Save the previous message if it has changed
					if(SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][ISSUEOFDATA]!=sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]) {
						//IODE has changed
						memcpy(SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],sizeof(double)*15);
						/*for(k=0;k<15;k++) {
							SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k];
						}*/
						//Update last received message for the given PRNs
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN;
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD;
					}
					memcpy(SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j],sbasblock->longtermsaterrcorrections[i],sizeof(double)*15);
					/*for(k=0;k<15;k++) {
						SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=sbasblock->longtermsaterrcorrections[i][k];	
					}*/
					//Update last received message for the given PRNs
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=sbasblock->t.SoD;


					//Leave sbasblock as it was
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]+1;
				}
				
				break;

			case GEONAVIGATIONMESSAGE: /*MT 9*/
				memcpy(SBASdata[pos].oldgeonavigationmessage,SBASdata[pos].geonavigationmessage,sizeof(double)*17);
				memcpy(SBASdata[pos].geonavigationmessage,sbasblock->geonavigationmessage,sizeof(double)*17);
				/*for(i=0;i<17;i++) {
					//Save old values
					SBASdata[pos].oldgeonavigationmessage[i]=SBASdata[pos].geonavigationmessage[i];	

					//Save new values
					SBASdata[pos].geonavigationmessage[i]=sbasblock->geonavigationmessage[i];	
				}*/
				//Update last received message
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case GEOSATELLITEALMANACS: /*MT 17*/
				memcpy(SBASdata[pos].oldgeoalmanacsmessage,SBASdata[pos].geoalmanacsmessage,sizeof(double)*3*12);
				//Save old values
				SBASdata[pos].oldnumgeoalmanacs=SBASdata[pos].numgeoalmanacs;
				/*for(i=0;i<3;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].oldgeoalmanacsmessage[i][j]=SBASdata[pos].geoalmanacsmessage[i][j];
					}
				}*/

				memcpy(SBASdata[pos].geoalmanacsmessage,sbasblock->geoalmanacsmessage,sizeof(double)*sbasblock->numgeoalmanacs*12);
				//Save new values
				SBASdata[pos].numgeoalmanacs=sbasblock->numgeoalmanacs;
				/*for(i=0;i<sbasblock->numgeoalmanacs;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].geoalmanacsmessage[i][j]=sbasblock->geoalmanacsmessage[i][j];	
					}
				}*/

				//If there are empty slots, initialize them so there are no remanents from previous messages
				for(;i<3;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].geoalmanacsmessage[i][j]=-1;
					}
				}
				//Update last received message
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case SBASSERVICEMESSAGE: /*MT 27*/
				if(SBASdata[pos].IODS!=(int)sbasblock->servicemessage[IODSPOS]) {
					//New IODS, we need to save old values and initialize the values of the current block
					SBASdata[pos].oldIODS=SBASdata[pos].IODS;

					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;

					SBASdata[pos].IODS=sbasblock->servicemessage[IODSPOS];
					//Initialize the values of the not used blocks 
					for(l=0;l<9;l++) {
						if(l!=SBASdata[pos].IODS && l!=SBASdata[pos].oldIODS) {
							for(i=0;i<4;i++) {
								SBASdata[pos].numberofregions[l][i]=0;
								SBASdata[pos].servicemessagesreceived[l][i]=-1;
								for(j=0;j<40;j++) {
									for(k=0;k<12;k++) {
										SBASdata[pos].regioncoordinates[l][i][j][k]=9999;
									}
								}
							}
							for(i=0;i<8;i++) {
								SBASdata[pos].servicemessagesreceived[l][i]=-1;
							}
							SBASdata[pos].maxprioritycode[l]=0;
							SBASdata[pos].totalservicemessagesreceived[l]=0;
						}
					}
				}

				//Check if the current service message has been received
				if(SBASdata[pos].servicemessagesreceived[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[SERVICEMESSAGENUMBER]-1]==-1) {
					//This service message has not been received, we need to save the data
					for(i=0;i<(int)sbasblock->servicemessage[NUMBEROFREGIONS];i++) {
						//memcpy(SBASdata[pos].regioncoordinates[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]][SBASdata[pos].numberofregions[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]]+i],sbasblock->regioncoordinates[i],sizeof(int)*12);
						for(j=0;j<12;j++) {
							SBASdata[pos].regioncoordinates[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]][SBASdata[pos].numberofregions[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]]+i][j]=sbasblock->regioncoordinates[i][j];
						}
					}
					SBASdata[pos].servicemessagesreceived[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[SERVICEMESSAGENUMBER]-1]=1;
					SBASdata[pos].totalservicemessagesreceived[(int)sbasblock->servicemessage[IODSPOS]]=SBASdata[pos].totalservicemessagesreceived[(int)sbasblock->servicemessage[IODSPOS]]+1;
					SBASdata[pos].numberofregions[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]]=SBASdata[pos].numberofregions[(int)sbasblock->servicemessage[IODSPOS]][(int)sbasblock->servicemessage[PRIORITYCODE]]+(int)sbasblock->servicemessage[NUMBEROFREGIONS];
					//Check for highest priority coded received
					if((int)sbasblock->servicemessage[PRIORITYCODE]>SBASdata[pos].maxprioritycode[(int)sbasblock->servicemessage[IODSPOS]]) {
						SBASdata[pos].maxprioritycode[(int)sbasblock->servicemessage[IODSPOS]]=(int)sbasblock->servicemessage[PRIORITYCODE];
					}
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case SBASNETWORKTIMEPARAMETERS: /*MT 12*/
				memcpy(SBASdata[pos].networktimemessage,sbasblock->networktimemessage,sizeof(double)*13);
				//for(i=0;i<13;i++) {
				//	SBASdata[pos].networktimemessage[i]=sbasblock->networktimemessage[i];
				//}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case CLOCKEPHEMERISCOVARIANCEMATRIX: /*MT 28*/
				//Check if the Message mask matches with the latest message received
				iodpposition=(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION];
				if(SBASdata[pos].IODPcovariance!=iodpposition) {
					//New mask. We need to save all the old values and initialize the current one
					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].IODPcovariance && i!=iodpposition) {
							for(j=0;j<51;j++) {
								SBASdata[pos].lastcovmatrix[i][j].MJDN=-1;
								SBASdata[pos].lastcovmatrix[i][j].SoD=-1;
							}

						}
					}
					SBASdata[pos].oldIODPcovariance=SBASdata[pos].IODPcovariance;

					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;
				}


				for(i=0;i<sbasblock->numclockephemeriscovariance;i++) {
					if((int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]==0) continue; //PRNMASKNUMBER=0 means that there is no valid data
					//Substract one because our PRN Mask number goes from 0 to 50
					sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]=sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]-1;
					j=(int)sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER];
					//Save new values
					memcpy(SBASdata[pos].clockephemeriscovariance[iodpposition][j],sbasblock->clockephemeriscovariance[i],sizeof(double)*14);

					//Update last received message for the given PRNs 
					SBASdata[pos].lastcovmatrix[iodpposition][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastcovmatrix[iodpposition][j].SoD=sbasblock->t.SoD;

					//Leave sbasblock as it was
					sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]=sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]+1;
				}
				
				SBASdata[pos].IODPcovariance=iodpposition;

				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case IONOSPHERICGRIDPOINTSMASKS: /*MT 18*/
				//Check if the mask has changed 
				if(SBASdata[pos].IODImask==(int)sbasblock->igpmaskmessage[IODIPOS]) {
					//The mask has NOT changed. Check if we have received this mask
					if(SBASdata[pos].IGPbandreceived[sbasblock->igpmaskmessage[BANDNUMBER]]!=1) {
						//Band not received. Continue filling the mask
						SBASdata[pos].numIGPbandreceived=SBASdata[pos].numIGPbandreceived+1;
						SBASdata[pos].IODImask=sbasblock->igpmaskmessage[IODIPOS];
						SBASdata[pos].IGPbandreceived[sbasblock->igpmaskmessage[BANDNUMBER]]=1;
						SBASdata[pos].numIGPbandbroadcast=sbasblock->igpmaskmessage[NUMBEROFBANDS];
						j=0;
						//memcpy(&SBASdata[pos].IGPinMask[SBASdata[pos].IODImask][sbasblock->igpmaskmessage[BANDNUMBER]][1],&sbasblock->igpmaskmessage[3],sizeof(int)*201);
						for(i=1;i<202;i++) {
							SBASdata[pos].IGPinMask[SBASdata[pos].IODImask][sbasblock->igpmaskmessage[BANDNUMBER]][i]=sbasblock->igpmaskmessage[i+2];

							//Create the dictionary in BlockIDPlace2Grid for current band
							if(SBASdata[pos].IGPinMask[SBASdata[pos].IODImask][sbasblock->igpmaskmessage[BANDNUMBER]][i]==1) {
								k=(int)(j/15);
								l=j%15;
								j++;
								SBASdata[pos].BlockIDPlace2Grid[sbasblock->igpmaskmessage[BANDNUMBER]][k][l]=i;
							}
						}
					}
				} else {
					//The mask has changed.
					//Save the old mask and initialize the new one
					SBASdata[pos].oldIODImask=SBASdata[pos].IODImask;
					SBASdata[pos].oldnumIGPbandbroadcast=SBASdata[pos].numIGPbandbroadcast;
					SBASdata[pos].oldnumIGPbandreceived=SBASdata[pos].numIGPbandreceived;
					SBASdata[pos].numIGPbandreceived=0;

					//memcpy(SBASdata[pos].oldIGPbandreceived,SBASdata[pos].IGPbandreceived,sizeof(int)*11);
					//memset(SBASdata[pos].IGPinMask[(int)sbasblock->igpmaskmessage[IODIPOS]],0,sizeof(int)*5*202);
					//memcpy(SBASdata[pos].oldBlockIDPlace2Grid,SBASdata[pos].BlockIDPlace2Grid,sizeof(int)*11*14*15);

					for(i=0;i<11;i++) {
						SBASdata[pos].oldIGPbandreceived[i]=SBASdata[pos].IGPbandreceived[i];

						SBASdata[pos].IGPbandreceived[i]=-1;
						for(j=0;j<202;j++) {
							SBASdata[pos].IGPinMask[(int)sbasblock->igpmaskmessage[IODIPOS]][i][j]=0;
						}
						for(j=0;j<14;j++) {
							for(k=0;k<15;k++) {
								SBASdata[pos].oldBlockIDPlace2Grid[i][j][k]=SBASdata[pos].BlockIDPlace2Grid[i][j][k];

								SBASdata[pos].BlockIDPlace2Grid[i][j][k]=-1;
							}
						}
					}
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD;

					
					//Check the values of IGP2Mask 
					for(i=0;i<11;i++) {
						for(j=0;j<202;j++) {
							if (SBASdata[pos].IGP2Mask[i][j]!=(int)sbasblock->igpmaskmessage[IODIPOS]) {
								if(SBASdata[pos].IGP2Mask[i][j]!=SBASdata[pos].oldIODImask) {
									//Check all IGP2Mask values. If any of them have an IODI which does not match the old or current IODI mask
									//set its IODI to 4 (In this position all the values of IGP2Mask will be 0)

									SBASdata[pos].IGP2Mask[i][j]=4;
								}
							}
						}
					}

					//Save new mask
					SBASdata[pos].IODImask=(int)sbasblock->igpmaskmessage[IODIPOS];
					SBASdata[pos].numIGPbandreceived=SBASdata[pos].numIGPbandreceived+1;
					SBASdata[pos].IGPbandreceived[sbasblock->igpmaskmessage[BANDNUMBER]]=1;
					SBASdata[pos].numIGPbandbroadcast=sbasblock->igpmaskmessage[NUMBEROFBANDS];
					j=0;
					for(i=1;i<202;i++) {
						SBASdata[pos].IGPinMask[SBASdata[pos].IODImask][sbasblock->igpmaskmessage[BANDNUMBER]][i]=sbasblock->igpmaskmessage[i+2];

						//Create the dictionary in BlockIDPlace2Grid for current band
						if(SBASdata[pos].IGPinMask[SBASdata[pos].IODImask][sbasblock->igpmaskmessage[BANDNUMBER]][i]==1) {
							k=(int)(j/15);
							l=j%15;
							j++;
							SBASdata[pos].BlockIDPlace2Grid[sbasblock->igpmaskmessage[BANDNUMBER]][k][l]=i;
						}
					}
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype].SoD=sbasblock->t.SoD;

				//No break here, so it will continue to process ionospheric delay corrections.
				//The reason for this is that when a new mask arrives, try to process all the data buffered fron the new mask
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case IONOSPHERICDELAYCORRECTIONS: /*MT 26*/

				//First we save the data in the buffer "ionobuffered". Then, if we have the mask, the data is saved in the SBAS structure
				//This allows to save data received before having the iono mask, and when the iono band mask is available decode the data,
				//In this way, we don't need to wait first for the mask and then for the data for that iono band, decreasing the initialization time

				//Select the position for the buffer according to the PRN
				if(pos==0) {
					GEObuffer=0;
				} else {
					GEObuffer=sbasblock->PRN;
				}

				//We can come here also when we receive a mask message. We only have to buffer if the message received are iono delay corrections and we don't have the mask
				if(sbasblock->messagetype==IONOSPHERICDELAYCORRECTIONS) {
					if (SBASdata[pos].IGPbandreceived[(int)sbasblock->ionodelayparameters[0][BANDNUMBER]]==-1) {
						currentbandnumber=(int)sbasblock->ionodelayparameters[0][BANDNUMBER];
						currentblockID=(int)sbasblock->ionodelayparameters[0][BLOCKID];
						//Copy values to the buffer
						memcpy(SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].ionodelayparameters,sbasblock->ionodelayparameters,sizeof(double)*15*7);
						/*for(i=0;i<15;i++) {
							for(j=0;j<7;j++) {
								SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].ionodelayparameters[i][j]=sbasblock->ionodelayparameters[i][j];
							}
						}*/
						SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.MJDN=sbasblock->t.MJDN;
						SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.SoD=sbasblock->t.SoD;

						ionobuffered[GEObuffer][currentbandnumber][currentblockID]=1;
						anyIonoCorrBuffered[GEObuffer]=1;
					} else {
						//Save data read in current message
						currentbandnumber=(int)sbasblock->ionodelayparameters[0][BANDNUMBER];
						currentblockID=(int)sbasblock->ionodelayparameters[0][BLOCKID];
						currentIODI=(int)sbasblock->ionodelayparameters[0][IODIPOS];
						if(SBASdata[pos].IODImask==currentIODI) {
							//Data is from the current mask
							dataDestMode=0;
							BlockIDPlace2GridPtr=SBASdata[pos].BlockIDPlace2Grid[currentbandnumber][currentblockID];
							IODImaskVal=SBASdata[pos].IODImask;
						} else if (SBASdata[pos].oldIODImask==currentIODI) {
							//Data is from the old mask
							dataDestMode=1;
							BlockIDPlace2GridPtr=SBASdata[pos].oldBlockIDPlace2Grid[currentbandnumber][currentblockID];
							IODImaskVal=SBASdata[pos].oldIODImask;
						} else {
							//The IODI does not match the current band or we have not received any mask
							dataDestMode=2;
						}
						if (dataDestMode<2) {
							//Save data
							for(i=0;i<15;i++) {
								/*switch(dataDestMode) {
									case 0:
										//Data is from the current mask
										l=SBASdata[pos].BlockIDPlace2Grid[currentbandnumber][currentblockID][i];
										if(l==-1) continue;
										SBASdata[pos].IGP2Mask[currentbandnumber][l]=SBASdata[pos].IODImask;
										break;
									case 1:
										//Data is from the old mask
										l=SBASdata[pos].oldBlockIDPlace2Grid[currentbandnumber][currentblockID][i];
										if(l==-1) continue;
										SBASdata[pos].IGP2Mask[currentbandnumber][l]=SBASdata[pos].oldIODImask;
										break;
									default:
										//The IODI does not match the current band or we have not received any mask
										continue;
										break;
								}*/

								l=BlockIDPlace2GridPtr[i];
								if(l==-1) continue;
								SBASdata[pos].IGP2Mask[currentbandnumber][l]=IODImaskVal;


								SBASdata[pos].Ionodelay[currentbandnumber][l]=sbasblock->ionodelayparameters[i][IGPVERTICALDELAY];
								SBASdata[pos].IonoGIVE[currentbandnumber][l]=sbasblock->ionodelayparameters[i][GIVEVALUE];
								SBASdata[pos].Ionosigma[currentbandnumber][l]=sbasblock->ionodelayparameters[i][GIVEVARIANCE];
								SBASdata[pos].lastiono[currentbandnumber][l].MJDN=sbasblock->t.MJDN;
								SBASdata[pos].lastiono[currentbandnumber][l].SoD=sbasblock->t.SoD;
							}
						} else {
							//No matching mask, buffer message instead
							currentbandnumber=(int)sbasblock->ionodelayparameters[0][BANDNUMBER];
							currentblockID=(int)sbasblock->ionodelayparameters[0][BLOCKID];
							//Copy values to the buffer
							memcpy(SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].ionodelayparameters,sbasblock->ionodelayparameters,sizeof(double)*15*7);
							/*for(i=0;i<15;i++) {
								for(j=0;j<7;j++) {
									SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].ionodelayparameters[i][j]=sbasblock->ionodelayparameters[i][j];
								}
							}*/
							SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.MJDN=sbasblock->t.MJDN;
							SBASdatabox->ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.SoD=sbasblock->t.SoD;

							ionobuffered[GEObuffer][currentbandnumber][currentblockID]=1;
							anyIonoCorrBuffered[GEObuffer]=1;
						}
					}
				}

				if (anyIonoCorrBuffered[GEObuffer]==1) {
					checkforIonobuffered=0;
					for(i=0;i<11;i++) {
						for(m=0;m<14;m++) {
							//Check if we have data for the current band in any BlockID
							if(ionobuffered[GEObuffer][i][m]==1) {
								//Check if we have received the iono mask for this band number. Otherwise leave it in the buffer 
								if(SBASdata[pos].IGPbandreceived[i]==1) {
									//We have the iono mask for this band number. 
									j=(int)SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[0][BLOCKID];
									if(SBASdata[pos].IODImask==(int)SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
										//Data is from the current mask
										dataDestMode=0;
										BlockIDPlace2GridPtr=SBASdata[pos].BlockIDPlace2Grid[i][j];
										IODImaskVal=SBASdata[pos].IODImask;
									} else if (SBASdata[pos].oldIODImask==(int)SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
										//Data is from the old mask
										dataDestMode=1;
										BlockIDPlace2GridPtr=SBASdata[pos].oldBlockIDPlace2Grid[i][j];
										IODImaskVal=SBASdata[pos].oldIODImask;
									} else {
										//The IODI does not match the current band or we have not received any mask
										dataDestMode=2;
									}
									if (dataDestMode<2) {
										for(k=0;k<15;k++) {
											/*switch(dataDestMode) {
												case 0:
													//Data is from the current mask
													l=SBASdata[pos].BlockIDPlace2Grid[i][j][k];
													if(l==-1) continue;
													SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].IODImask;
													break;
												case 1:
													//Data is from the old mask
													l=SBASdata[pos].oldBlockIDPlace2Grid[i][j][k];
													if(l==-1) continue;
													SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].oldIODImask;
													break;
												default:
													//The IODI does not match the current band or we have not received any mask
													continue;
													break;
											}*/

											/*if(SBASdata[pos].IODImask==(int)SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
												//Data is from the current mask
												l=SBASdata[pos].BlockIDPlace2Grid[i][j][k];
												if(l==-1) continue;
												SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].IODImask;
											} else if (SBASdata[pos].oldIODImask==(int)SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
												//Data is from the old mask
												l=SBASdata[pos].oldBlockIDPlace2Grid[i][j][k];
												if(l==-1) continue;
												SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].oldIODImask;
											} else {
												//The IODI does not match the current band or we have not received any mask
												break;
											}*/
											l=BlockIDPlace2GridPtr[k];
											if(l==-1) continue;
											SBASdata[pos].IGP2Mask[i][l]=IODImaskVal;

											SBASdata[pos].Ionodelay[i][l]=SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[k][IGPVERTICALDELAY];
											SBASdata[pos].IonoGIVE[i][l]=SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[k][GIVEVALUE];
											SBASdata[pos].Ionosigma[i][l]=SBASdatabox->ionobuffer[GEObuffer][i][m].ionodelayparameters[k][GIVEVARIANCE];
											SBASdata[pos].lastiono[i][l].MJDN=SBASdatabox->ionobuffer[GEObuffer][i][m].t.MJDN;
											SBASdata[pos].lastiono[i][l].SoD=SBASdatabox->ionobuffer[GEObuffer][i][m].t.SoD;

										}
										ionobuffered[GEObuffer][i][m]=0;
									} else {
										//The stored data has not been read, set the flag that we still have remaining data
										checkforIonobuffered=1;
									}
								} else {
									//We do not have the mask, so we cannot read any data for this band
									//The stored data has not been read, set the flag that we still have remaining data
									checkforIonobuffered=1;
									break;
								}
							} else {
								//No data for this bandnumber and BlockID
								continue;
							}
						}
					}
					//Update the flag to check if there is data buffered
					anyIonoCorrBuffered[GEObuffer]=checkforIonobuffered;
				}
				break;
			case SATMASKASIGNMENTS: /*MT 31*/
				//Check if we have a new PRN Mask
				if(sbasblock->IODM!=SBASdata[pos].IODMmask) {
					//New Mask. Save the old mask, so we can still use messages 
					memcpy(SBASdata[pos].pos2PRN[sbasblock->frequencyPos][sbasblock->IODM],sbasblock->pos2PRN,sizeof(int)*92);
					memcpy(SBASdata[pos].pos2GNSS[sbasblock->frequencyPos][sbasblock->IODM],sbasblock->pos2GNSS,sizeof(enum GNSSystem)*92);
					memcpy(SBASdata[pos].Slot2pos[sbasblock->frequencyPos][sbasblock->IODM],sbasblock->Slot2pos,sizeof(int)*215);
					memcpy(SBASdata[pos].PRNactive[sbasblock->frequencyPos][sbasblock->IODM],sbasblock->PRNactive,sizeof(int)*MAX_GNSS*MAX_SBAS_PRN);
					memcpy(SBASdata[pos].PRN2pos[sbasblock->frequencyPos][sbasblock->IODM],sbasblock->PRN2pos,sizeof(int)*MAX_GNSS*MAX_SBAS_PRN);
					/*for(i=0;i<MAX_GNSS;i++) {
						memcpy(SBASdata[pos].PRNactive[sbasblock->frequencyPos][sbasblock->IODM][i],sbasblock->PRNactive[i],sizeof(int)*MAX_SBAS_PRN);
						memcpy(SBASdata[pos].PRN2pos[sbasblock->frequencyPos][sbasblock->IODM][i],sbasblock->PRN2pos[i],sizeof(int)*MAX_SBAS_PRN);
					}*/

					//Set the old IODmask to -1 before changing the current IODM to the old one
					SBASdata[pos].numsatellites[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask]=0;
					for(j=0;j<MAX_GNSS;j++) {
						for(k=0;k<MAX_SBAS_PRN;k++) {
							SBASdata[pos].PRNactive[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][j][k]=-1;
							SBASdata[pos].PRN2pos[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][j][k]=-1;
						}
					}
					for(j=0;j<215;j++) {
						SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][j]=-1;
					}

					SBASdata[pos].oldIODMmask=SBASdata[pos].IODMmask;

					SBASdata[pos].IODMmask=sbasblock->IODM;
					SBASdata[pos].numsatellites[sbasblock->frequencyPos][sbasblock->IODM]=sbasblock->numsatellites;

					SBASdata[pos].oldmaskdiscarded[sbasblock->frequencyPos][sbasblock->messagetype]=0;

					memcpy(&SBASdata[pos].oldlastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],sizeof(TTime));

					//Update constellations monitored
					//Only need to update once (when it is not mixed GEO), as constellation monitored is saved in Toptions structure
					//Reset constellation list
					options->numSBASConstList[pos][SBASDFMCMODEPOS]=0;
					for(i=0;i<MAX_GNSS;i++) {
						options->SBASConstUsed[pos][SBASDFMCMODEPOS][i]=sbasblock->constMonitored[i];
						if (sbasblock->constMonitored[i]==1 && options->ConstellationUsed[i]==1) {
							options->SBASConstList[pos][SBASDFMCMODEPOS][options->numSBASConstList[pos][SBASDFMCMODEPOS]]=i;
							options->numSBASConstList[pos][SBASDFMCMODEPOS]++;
						} else {
							options->SBASConstList[pos][SBASDFMCMODEPOS][i]=-1;
						}
					}
				}

				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));

				break;
			case CLOCKEPHEMERISCOVARIANCEMATRIXDFMC: /*MT 32*/
				
				memcpy(SBASdata[pos].covarianceMatrixDFMC[(int)sbasblock->covariancematrixdata[SATSLOTNUMBER]],sbasblock->covariancematrixdata,sizeof(double)*14);
				memcpy(SBASdata[pos].clockephemerisDFMC[(int)sbasblock->covariancematrixdata[SATSLOTNUMBER]],sbasblock->orbitclockcorrection,sizeof(double)*15);

				//Check if mask is available
				if (SBASdata[pos].IODMmask!=-1) {
					//Mask available, update DFREI data
					j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].IODMmask][(int)sbasblock->covariancematrixdata[SATSLOTNUMBER]];
					if (j!=-1) {
						SBASdata[pos].DFREI[SBASdata[pos].IODMmask][j]=(int)sbasblock->orbitclockcorrection[DFREIPOS];
						SBASdata[pos].DFRECI2bumped[SBASdata[pos].IODMmask][j]=0;	//Set no bump applied to DFREI
						memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].IODMmask][j],&sbasblock->t,sizeof(TTime));
					}
				}
				
				//Check also if previous IODMmask is available
				if (SBASdata[pos].oldIODMmask!=-1) {
					//Mask available, update DFREI data
					j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][(int)sbasblock->covariancematrixdata[SATSLOTNUMBER]];
					if (j!=-1) {
						SBASdata[pos].DFREI[SBASdata[pos].oldIODMmask][j]=(int)sbasblock->orbitclockcorrection[DFREIPOS];
						SBASdata[pos].DFRECI2bumped[SBASdata[pos].oldIODMmask][j]=0;	//Set no bump applied to DFREI
						memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].oldIODMmask][j],&sbasblock->t,sizeof(TTime));
					}
				}
				memcpy(&SBASdata[pos].clockephemerisDFMCTime[(int)sbasblock->covariancematrixdata[SATSLOTNUMBER]],&sbasblock->t,sizeof(TTime));
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case OBADDFREIPARAMETERS: /*MT 37*/
				for(i=0;i<MAX_GNSS;i++) {
					memcpy(SBASdata[pos].OBAD[i],sbasblock->OBAD[i],sizeof(double)*3);
				}
				memcpy(SBASdata[pos].commonOBAD,sbasblock->commonOBAD,sizeof(double)*5);
				memcpy(SBASdata[pos].DFREITable,sbasblock->DFREITable,sizeof(double)*15);


				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case SBASEPHEMERISDFMC: /*MT 39*/
				if ((int)sbasblock->sbasepehemeris1[IODGNAVSBAS]==SBASdata[pos].navSBASmessage.IODG) {
					//IODG sent is the same. so data has not changed. Just update timeout
					memcpy(&SBASdata[pos].lastMT3940received,&sbasblock->t,sizeof(TTime));
				} else if (MT40buffered[sbasblock->PRN]==1) {
					//We have received a MT40 message first with different IODG, check it has the same IODG as the MT40
					if ((int)sbasblock->sbasepehemeris1[IODGNAVSBAS]==(int)sbasepehemeris2Buffer[sbasblock->PRN][IODGNAVSBAS]) {
						//New MT39 has the new IODG as in the MT40
						//Check that the MT40 buffered message has not timed-out
						if (SBASdata[pos].lastmsgreceived[SBASDFMCFREQPOS][OBADDFREIPARAMETERS].MJDN!=-1) {
							if (tdiff(&sbasblock->t,&MT40bufferedtime[sbasblock->PRN])>(SBASdata[pos].commonOBAD[IVALIDMT3940]*SBASdata[pos].tmoutFactor[options->precisionapproach]) ) {
								msgtimeout=1;
							} else {
								msgtimeout=0;
							}
						} else {
							//408 (seconds) is the highest value for IvalidMT39/40. As we don't have any IvalidMT39/40 value, we use
							//the highest value. As MT39/40 is for SBAS orbits, and Keplearian orbits usually lasts up to 2 hours (like GPS),
							//it is not critical to use the highest timeout value
							if (tdiff(&sbasblock->t,&MT40bufferedtime[sbasblock->PRN])>408) { 
								msgtimeout=1;
							} else {
								msgtimeout=0;
							}
						}
						if (msgtimeout==1) {
							//Buffered MT40 message has timed out. Save MT39 and remove MT40
							memcpy(sbasepehemeris1Buffer[sbasblock->PRN],sbasblock->sbasepehemeris1,sizeof(double)*11);
							memcpy(&MT39bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
							MT40buffered[sbasblock->PRN]=0;
						} else {
							//There is a buffered MT40 (and not timed-out) with same IOD as the current MT39.
							//Save data from both messages
							SBASdata[pos].SBASproviderID=(int)sbasblock->sbasepehemeris1[SBASPROVIDERID];
							SBASdata[pos].DFREISBASMT3940=(int)sbasepehemeris1Buffer[sbasblock->PRN][DFREINAVSBAS];
							SBASdata[pos].RCORRSBASMT3940=sbasepehemeris2Buffer[sbasblock->PRN][RCORRMULTNAVSBAS];
							SBASdata[pos].navSBASmessage.SBASDFMCdatatype=SBASDFMCGEONAVIGATIONDATA;

							SBASdata[pos].navSBASmessage.GNSS=GEO;
							SBASdata[pos].navSBASmessage.PRN=sbasblock->PRN;
							SBASdata[pos].navSBASmessage.BRDCtype=GEOCNAV;
							SBASdata[pos].navSBASmessage.IODNGEO=(int)sbasblock->sbasepehemeris1[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.IODG=(int)sbasblock->sbasepehemeris1[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.IODE=(int)sbasblock->sbasepehemeris1[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.cuc=sbasblock->sbasepehemeris1[CUCNAVSBAS];
							SBASdata[pos].navSBASmessage.cus=sbasblock->sbasepehemeris1[CUSNAVSBAS];
							SBASdata[pos].navSBASmessage.IDOT=sbasblock->sbasepehemeris1[IDOTNAVSBAS];
							SBASdata[pos].navSBASmessage.omega=sbasblock->sbasepehemeris1[PERIGREENAVSBAS];
							SBASdata[pos].navSBASmessage.OMEGA=sbasblock->sbasepehemeris1[ASCENDINGNAVSBAS];
							SBASdata[pos].navSBASmessage.M0=sbasblock->sbasepehemeris1[ANOMALYNAVSBAS];
							SBASdata[pos].navSBASmessage.i0=sbasepehemeris2Buffer[sbasblock->PRN][INCNAVSBAS];
							SBASdata[pos].navSBASmessage.e=sbasepehemeris2Buffer[sbasblock->PRN][ECCNAVSBAS];
							SBASdata[pos].navSBASmessage.toe=sbasepehemeris2Buffer[sbasblock->PRN][EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.transTime=sbasblock->t.SoD;

							SBASdata[pos].navSBASmessage.Ttoc.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.Ttoe.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.TtransTime.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.Ttoc.SoD=sbasepehemeris2Buffer[sbasblock->PRN][EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.Ttoe.SoD=sbasepehemeris2Buffer[sbasblock->PRN][EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.TtransTime.SoD=sbasblock->t.SoD;

							if (options->SBASDFMCMT3940version==MT3940V1) {
								SBASdata[pos].navSBASmessage.sqrta=sqrt(sbasepehemeris2Buffer[sbasblock->PRN][AXISNAVSBAS]);
								SBASdata[pos].navSBASmessage.clockbias=sbasblock->sbasepehemeris1[AGF0NAVSBAS];
								SBASdata[pos].navSBASmessage.clockdrift=sbasblock->sbasepehemeris1[AGF1NAVSBAS];
								SBASdata[pos].navSBASmessage.clockdriftrate=0.;
							} else {
								SBASdata[pos].navSBASmessage.sqrta=sqrt(sbasblock->sbasepehemeris1[AXISNAVSBASV044]);
								SBASdata[pos].navSBASmessage.clockbias=sbasepehemeris2Buffer[sbasblock->PRN][AGF0NAVSBASV044];
								SBASdata[pos].navSBASmessage.clockdrift=sbasepehemeris2Buffer[sbasblock->PRN][AGF1NAVSBASV044];
								SBASdata[pos].navSBASmessage.clockdriftrate=0.;
							}
							//Save covariance matrix data
							memcpy(SBASdata[pos].covarianceMatrixSBASDFMC,covariancematrixdataBuffer[sbasblock->PRN],sizeof(double)*14);

							//Save epoch of the last MT39 received (after decoding MT39 and MT40 act as single message and
							//the timeout will be accounted from then last one received
							memcpy(&SBASdata[pos].lastMT3940received,&sbasblock->t,sizeof(TTime));

							//Check if mask is available
							if (SBASdata[pos].IODMmask!=-1) {
								//Mask available, update DFREI data
								j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].IODMmask][(int)sbasblock->sbasepehemeris1[SATSLOTNUMBER]];
								if (j!=-1) {
									SBASdata[pos].DFREI[SBASdata[pos].IODMmask][j]=(int)sbasepehemeris2Buffer[sbasblock->PRN][DFREINAVSBAS];
									SBASdata[pos].DFRECI2bumped[SBASdata[pos].IODMmask][j]=0;	//Set no bump applied to DFREI
									memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].IODMmask][j],&sbasblock->t,sizeof(TTime));
								}
							}
							
							//Check also if previous IODMmask is available
							if (SBASdata[pos].oldIODMmask!=-1) {
								//Mask available, update DFREI data
								j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][(int)sbasblock->sbasepehemeris1[SATSLOTNUMBER]];
								if (j!=-1) {
									SBASdata[pos].DFREI[SBASdata[pos].oldIODMmask][j]=(int)sbasepehemeris2Buffer[sbasblock->PRN][DFREINAVSBAS];
									SBASdata[pos].DFRECI2bumped[SBASdata[pos].oldIODMmask][j]=0;	//Set no bump applied to DFREI
									memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].oldIODMmask][j],&sbasblock->t,sizeof(TTime));
								}
							}

							//Unbuffer MT39 and MT40 messages
							MT39buffered[sbasblock->PRN]=0;
							MT40buffered[sbasblock->PRN]=0;
						}
					} else {
						//New IODG from MT39 does not match the MT40. This case should not occur (MT39 and MT40 having different IODG and these
						//IODG are not the current one used. In these case, save MT39 data and remove the buffered MT40
						memcpy(sbasepehemeris1Buffer[sbasblock->PRN],sbasblock->sbasepehemeris1,sizeof(double)*11);
						memcpy(&MT39bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
						MT39buffered[sbasblock->PRN]=1;
						MT40buffered[sbasblock->PRN]=0;
					}
				} else {
					//New MT39 has a different IODG and no MT40 saved. Buffer MT39 until a matching MT40 arrives
					memcpy(sbasepehemeris1Buffer[sbasblock->PRN],sbasblock->sbasepehemeris1,sizeof(double)*11);
					memcpy(&MT39bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
					MT39buffered[sbasblock->PRN]=1;
				}
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case SBASEPHEMERISCOVARIANCEDFMC: /*MT 40*/
				if ((int)sbasblock->sbasepehemeris2[IODGNAVSBAS]==SBASdata[pos].navSBASmessage.IODG) {
					//IODG sent is the same. so data has not changed. Just update timeout
					memcpy(&SBASdata[pos].lastMT3940received,&sbasblock->t,sizeof(TTime));
				} else if (MT39buffered[sbasblock->PRN]==1) {
					//We have received a MT40 message first with different IODG, check it has the same IODG as the MT40
					if ((int)sbasblock->sbasepehemeris2[IODGNAVSBAS]==(int)sbasepehemeris1Buffer[sbasblock->PRN][IODGNAVSBAS]) {
						//New MT40 has the new IODG as in the MT39
						//Check that the MT39 buffered message has not timed-out
						if (SBASdata[pos].lastmsgreceived[SBASDFMCFREQPOS][OBADDFREIPARAMETERS].MJDN!=-1) {
							if (tdiff(&sbasblock->t,&MT39bufferedtime[sbasblock->PRN])>(SBASdata[pos].commonOBAD[IVALIDMT3940]*SBASdata[pos].tmoutFactor[options->precisionapproach]) ) {
								msgtimeout=1;
							} else {
								msgtimeout=0;
							}
						} else {
							//408 (seconds) is the highest value for IvalidMT39/40. As we don't have any IvalidMT39/40 value, we use
							//the highest value. As MT39/40 is for SBAS orbits, and Keplearian orbits usually lasts up to 2 hours (like GPS),
							//it is not critical to use the highest timeout value
							if (tdiff(&sbasblock->t,&MT39bufferedtime[sbasblock->PRN])>408) { 
								msgtimeout=1;
							} else {
								msgtimeout=0;
							}
						}
						if (msgtimeout==1) {
							//Buffered MT39 message has timed out. Save MT40 and remove MT39
							memcpy(sbasepehemeris2Buffer[sbasblock->PRN],sbasblock->sbasepehemeris2,sizeof(double)*9);
							memcpy(covariancematrixdataBuffer[sbasblock->PRN],sbasblock->covariancematrixdata,sizeof(double)*14);
							memcpy(&MT40bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
							MT39buffered[sbasblock->PRN]=0;
						} else {
							//There is a buffered MT40 (and not timed-out) with same IOD as the current MT39.
							//Save data from both messages
							SBASdata[pos].SBASproviderID=(int)sbasepehemeris1Buffer[sbasblock->PRN][SBASPROVIDERID];
							SBASdata[pos].DFREISBASMT3940=(int)sbasblock->sbasepehemeris2[DFREINAVSBAS];
							SBASdata[pos].RCORRSBASMT3940=sbasblock->sbasepehemeris2[RCORRMULTNAVSBAS];
							SBASdata[pos].navSBASmessage.SBASDFMCdatatype=SBASDFMCGEONAVIGATIONDATA;

							SBASdata[pos].navSBASmessage.GNSS=GEO;
							SBASdata[pos].navSBASmessage.PRN=sbasblock->PRN;
							SBASdata[pos].navSBASmessage.BRDCtype=GEOCNAV;
							SBASdata[pos].navSBASmessage.IODNGEO=(int)sbasblock->sbasepehemeris2[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.IODG=(int)sbasblock->sbasepehemeris2[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.IODE=(int)sbasblock->sbasepehemeris2[IODGNAVSBAS];
							SBASdata[pos].navSBASmessage.cuc=sbasepehemeris1Buffer[sbasblock->PRN][CUCNAVSBAS];
							SBASdata[pos].navSBASmessage.cus=sbasepehemeris1Buffer[sbasblock->PRN][CUSNAVSBAS];
							SBASdata[pos].navSBASmessage.IDOT=sbasepehemeris1Buffer[sbasblock->PRN][IDOTNAVSBAS];
							SBASdata[pos].navSBASmessage.omega=sbasepehemeris1Buffer[sbasblock->PRN][PERIGREENAVSBAS];
							SBASdata[pos].navSBASmessage.OMEGA=sbasepehemeris1Buffer[sbasblock->PRN][ASCENDINGNAVSBAS];
							SBASdata[pos].navSBASmessage.M0=sbasepehemeris1Buffer[sbasblock->PRN][ANOMALYNAVSBAS];
							SBASdata[pos].navSBASmessage.i0=sbasblock->sbasepehemeris2[INCNAVSBAS];
							SBASdata[pos].navSBASmessage.e=sbasblock->sbasepehemeris2[ECCNAVSBAS];
							SBASdata[pos].navSBASmessage.toe=sbasblock->sbasepehemeris2[EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.transTime=sbasblock->t.SoD;

							SBASdata[pos].navSBASmessage.Ttoc.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.Ttoe.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.TtransTime.MJDN=sbasblock->t.MJDN;
							SBASdata[pos].navSBASmessage.Ttoc.SoD=sbasblock->sbasepehemeris2[EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.Ttoe.SoD=sbasblock->sbasepehemeris2[EPHTIMENAVSBAS];
							SBASdata[pos].navSBASmessage.TtransTime.SoD=sbasblock->t.SoD;

							if (options->SBASDFMCMT3940version==MT3940V1) {
								SBASdata[pos].navSBASmessage.sqrta=sqrt(sbasblock->sbasepehemeris2[AXISNAVSBAS]);
								SBASdata[pos].navSBASmessage.clockbias=sbasepehemeris1Buffer[sbasblock->PRN][AGF0NAVSBAS];
								SBASdata[pos].navSBASmessage.clockdrift=sbasepehemeris1Buffer[sbasblock->PRN][AGF1NAVSBAS];
								SBASdata[pos].navSBASmessage.clockdriftrate=0.;
							} else {
								SBASdata[pos].navSBASmessage.sqrta=sqrt(sbasepehemeris1Buffer[sbasblock->PRN][AXISNAVSBASV044]);
								SBASdata[pos].navSBASmessage.clockbias=sbasblock->sbasepehemeris2[AGF0NAVSBASV044];
								SBASdata[pos].navSBASmessage.clockdrift=sbasblock->sbasepehemeris2[AGF1NAVSBASV044];
								SBASdata[pos].navSBASmessage.clockdriftrate=0.;
							}

							//Save covariance matrix data
							memcpy(SBASdata[pos].covarianceMatrixSBASDFMC,sbasblock->covariancematrixdata,sizeof(double)*14);

							//Save epoch of the last MT39 received (after decoding MT39 and MT40 act as single message and
							//the timeout will be accounted from then last one received
							memcpy(&SBASdata[pos].lastMT3940received,&sbasblock->t,sizeof(TTime));

							//Check if mask is available
							if (SBASdata[pos].IODMmask!=-1) {
								//Mask available, update DFREI data
								j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].IODMmask][(int)sbasepehemeris1Buffer[sbasblock->PRN][SATSLOTNUMBER]];
								if (j!=-1) {
									SBASdata[pos].DFREI[SBASdata[pos].IODMmask][j]=(int)sbasblock->sbasepehemeris2[DFREINAVSBAS];
									SBASdata[pos].DFRECI2bumped[SBASdata[pos].IODMmask][j]=0;	//Set no bump applied to DFREI
									memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].IODMmask][j],&sbasblock->t,sizeof(TTime));
								}
							}
							
							//Check also if previous IODMmask is available
							if (SBASdata[pos].oldIODMmask!=-1) {
								//Mask available, update DFREI data
								j=SBASdata[pos].Slot2pos[sbasblock->frequencyPos][SBASdata[pos].oldIODMmask][(int)sbasepehemeris1Buffer[sbasblock->PRN][SATSLOTNUMBER]];
								if (j!=-1) {
									SBASdata[pos].DFREI[SBASdata[pos].oldIODMmask][j]=(int)sbasblock->sbasepehemeris2[DFREINAVSBAS];
									SBASdata[pos].DFRECI2bumped[SBASdata[pos].oldIODMmask][j]=0;	//Set no bump applied to DFREI
									memcpy(&SBASdata[pos].lastDFREIreceived[SBASdata[pos].oldIODMmask][j],&sbasblock->t,sizeof(TTime));
								}
							}

							//Unbuffer MT39 and MT40 messages
							MT39buffered[sbasblock->PRN]=0;
							MT40buffered[sbasblock->PRN]=0;
						}
					} else {
						//New IODG from MT40 does not match the MT39. This case should not occur (MT39 and MT40 having different IODG and these
						//IODG are not the current one used. In these case, save MT40 data and remove the buffered MT39
						memcpy(sbasepehemeris2Buffer[sbasblock->PRN],sbasblock->sbasepehemeris2,sizeof(double)*9);
						memcpy(covariancematrixdataBuffer[sbasblock->PRN],sbasblock->covariancematrixdata,sizeof(double)*14);
						memcpy(&MT40bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
						MT39buffered[sbasblock->PRN]=0;
						MT40buffered[sbasblock->PRN]=1;
					}
				} else {
					//New MT40 has a different IODG and no MT39 saved. Buffer MT40 until a matching MT39 arrives
					memcpy(sbasepehemeris2Buffer[sbasblock->PRN],sbasblock->sbasepehemeris2,sizeof(double)*9);
					memcpy(covariancematrixdataBuffer[sbasblock->PRN],sbasblock->covariancematrixdata,sizeof(double)*14);
					memcpy(&MT40bufferedtime[sbasblock->PRN],&sbasblock->t,sizeof(TTime));
					MT40buffered[sbasblock->PRN]=1;
				}
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case SBASNETWORKTIMEPARAMETERSDFMC: /*MT 42*/
				for(i=0;i<MAX_GNSS;i++) {
					memcpy(SBASdata[pos].GNSSTimeOffsetsConst[i],sbasblock->GNSSTimeOffsetsConst[i],sizeof(double)*2);
				}
				memcpy(SBASdata[pos].GNSSTimeOffsetsCommon,sbasblock->GNSSTimeOffsetsCommon,sizeof(double)*9);
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case SBASALMANACSDFMC: /*MT 47*/
				for(i=0;i<2;i++) {
					if ((int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]==0) continue;  //No almanac data for current slot
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].GNSS=GEO;
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].PRN=(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].SBASDFMCdatatype=SBASDFMCGEOALMANACDATA;
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].sqrta=sqrt(sbasblock->geoalmanacsDFMC[i][AXISALMANAC]);
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].e=sbasblock->geoalmanacsDFMC[i][ECCALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].i0=sbasblock->geoalmanacsDFMC[i][INCALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].omega=sbasblock->geoalmanacsDFMC[i][PERIGREEALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].OMEGA=sbasblock->geoalmanacsDFMC[i][ASCENDINGAALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].OMEGADOT=sbasblock->geoalmanacsDFMC[i][ASCENSIONAALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].M0=sbasblock->geoalmanacsDFMC[i][ANOMALYAALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].toe=sbasblock->geoalmanacsDFMC[i][REFEPOCHALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].Ttoe.MJDN=sbasblock->t.MJDN;
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].TtransTime.MJDN=sbasblock->t.MJDN;
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].Ttoe.SoD=sbasblock->geoalmanacsDFMC[i][REFEPOCHALMANAC];
					SBASdata[pos].DFMCalmanac[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].TtransTime.SoD=sbasblock->t.SoD;
					SBASdata[pos].WNROcount=(int)sbasblock->geoalmanacsDFMC[i][WNR0COUNTALMANAC];
					
					//If almanac for current GEO had not been received, add one to the number of almanacs
					if (SBASdata[pos].DFMCalmanacTime[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120].MJDN==-1) {
						SBASdata[pos].posWithDataDFMCalmanac[SBASdata[pos].numDFMCalmanac]=(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120;
						SBASdata[pos].numDFMCalmanac++;
					}

					SBASdata[pos].DFMCSBASProvider[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120]=(int)sbasblock->geoalmanacsDFMC[i][SBASPROVIDERID];
					memcpy(&SBASdata[pos].DFMCalmanacTime[(int)sbasblock->geoalmanacsDFMC[i][SATSLOTNUMBER]-120],&sbasblock->t,sizeof(TTime));
				}
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case INTERNALTESTMESSAGE: /*MT 62*/
				if (sbasblock->frequency==5) {
					SBASdata[pos].GPSfrequenciesUsed=sbasblock->GPSfrequenciesUsed;
				}
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case SERVICEAREADFMC: /*MT 48*/ case SERVICEAREADFMCTESTBED: /*MT 50*/
				//Messages not in SBAS DFMC standard
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			case RESERVED8: case RESERVED11: case RESERVED13: case RESERVED14: case RESERVED15: case RESERVED16: case RESERVED19: case RESERVED20: case RESERVED21: case RESERVED22: case RESERVED23: case NULLMESSAGE:
				//Messages with no data that do not have any effect
				//Update last received message
				memcpy(&SBASdata[pos].lastmsgreceived[sbasblock->frequencyPos][sbasblock->messagetype],&sbasblock->t,sizeof(TTime));
				break;
			default:
				//Unknown message
				break;
		}//End case

	}//End for PRN slot update
}

/*****************************************************************************
 * Name        : readsigmamultipathFile
 * Description : Read sigma multipath file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TSBASdata  *SBASdata            IO N/A  Structure to save SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readsigmamultipathFile (char *filename,  TSBASdata  *SBASdata, TOptions  *options) {
	int		ret;
	FILE 	*fd;

	fd = fopen(filename,"rb");
	if ( fd == NULL ) {
		return -1;
	} else {
		ret = readsigmamultipath(fd,filename,SBASdata,options);
		fclose(fd);
		return ret;
	}
}

/*****************************************************************************
 * Name        : readsigmamultipath
 * Description : Read a sigma multipath file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * char  *filename                 I  N/A  Name of the file
 * TSBASdata  *SBASdata            IO N/A  Structure to save SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readsigmamultipath (FILE *fd, char  *filename, TSBASdata  *SBASdata, TOptions  *options) {
	char		line[MAX_INPUT_LINE];
	int			len = 0;
	int			numCharRead,numCharReadTotal;
	int			ret = 0;
	int			wordindex = 1;
	int			i;
	int			numwordsperline;
	int			numline = 0;
	
	while (getLNoComments(line,&len,fd)!=-1) {
		//Take out commas ',' and semicolon ';'
		for(i=0;i<len;i++) {
			if (line[i]==','||line[i]==';') {
				line[i]=' ';
			}
		}

		numwordsperline=0;
		numCharReadTotal=0;
		wordlst[wordindex][0]='#';
		wordlst[wordindex][1]='\0';
		ret = sscanf(line,"%s%n",wordlst[wordindex],&numCharRead);
		if ( ret ) {
			if ( wordlst[wordindex][0] != '#' ) { // It is not a comment
				numline++;
				numwordsperline++;
				wordindex++;
				numCharReadTotal+=numCharRead;
				while(sscanf(&line[numCharReadTotal],"%s%n",wordlst[wordindex],&numCharRead)==1) {
					numwordsperline++;
					wordindex++;
					numCharReadTotal+=numCharRead;
				}
				if(numline>1) {
						if(numwordsperline<2) {
						fclose(fd);
						sprintf(messagestr,"Too few columns in [%s] file",filename);
						printError(messagestr,options);
					} else if (numwordsperline>2) {
						fclose(fd);
						sprintf(messagestr,"Too many columns in [%s] file",filename);
						printError(messagestr,options);
					}
				}
				if(numline==1 && numwordsperline >1) {
					fclose(fd);
					sprintf(messagestr,"Too many columns in first data line in [%s] file",filename);
					printError(messagestr,options);
				}
			}
		}
	}
	
	SBASdata[0].numsigmamultipath=numline-1;

	//Allocate memory
	SBASdata[0].sigmamultipathdata=malloc(sizeof(double *)*2);
	SBASdata[0].sigmamultipathdata[0]=malloc(sizeof(double)*SBASdata[0].numsigmamultipath);
	SBASdata[0].sigmamultipathdata[1]=malloc(sizeof(double)*SBASdata[0].numsigmamultipath);

	//Save data
	if(strcasecmp(wordlst[1],"Elevation")==0) {
		SBASdata[0].sigmamultipathtype=0;
	} else if(strcasecmp(wordlst[1],"SNR")==0){
		SBASdata[0].sigmamultipathtype=1;
	} else {
		//Unknown model dependency
		fclose(fd);
		sprintf(messagestr,"'%s' model not supported in [%s] file",wordlst[1],filename);
		printError(messagestr,options);
		return 0;
	}

	for(i=1;i<=SBASdata[0].numsigmamultipath;i++) {
		SBASdata[0].sigmamultipathdata[0][i-1]=atof(wordlst[2*i]);
		SBASdata[0].sigmamultipathdata[1][i-1]=atof(wordlst[(2*i)+1]);
	}

	for(i=0;i<SBASdata[0].numsigmamultipath-1;i++) {
		//Check that current range and following range have not the same value.
		if(SBASdata[0].sigmamultipathdata[0][i]==SBASdata[0].sigmamultipathdata[0][i+1]) {
			//They are equal, this will cause a division by zero when computing the unitary distance between consecutive ranges. Show an error and exit
			fclose(fd);
			sprintf(messagestr,"Two consecutive range values are the same in [%s] file",filename);
			printError(messagestr,options);
		//Check ranges are not sorted
		} else if (SBASdata[0].sigmamultipathdata[0][i]>SBASdata[0].sigmamultipathdata[0][i+1]) {
			//Ranges are not sorted. User must give them sorted
			fclose(fd);
			sprintf(messagestr,"Ranges are not sorted from lowest to highest in [%s] file",filename);
			printError(messagestr,options);
		//Check that if elevation ranges are given, none of them is over 90º
		} else if (SBASdata[0].sigmamultipathtype==0 && (SBASdata[0].sigmamultipathdata[0][i]>90 || SBASdata[0].sigmamultipathdata[0][i+1]>90)) {
			//One of the ranges is over 90º
			fclose(fd);
			sprintf(messagestr,"One of the ranges given is above 90º of elevation in [%s] file",filename);
			printError(messagestr,options);
		}
	}
				
	return 1;
}

/*****************************************************************************
 * Name        : addUserError
 * Description : Read user added error from file descriptor, check active errors 
 *                and add the error to measurements
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * char  *filename                 I  N/A  Name of the file
 * TEpoch  *epoch                  IO N/A  Structure to save the data
 * TUserError *UserError           O  N/A  TUserError structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void addUserError (FILE  *fd, char  *filename, TEpoch  *epoch, TUserError *UserError, TOptions  *options) {
	static int				endfile=0;
	static int				numline=0;
	static int				GLOprintNoBias[MAX_SATELLITES_PER_GNSS];
	static int				initialized=0;
	char 					line[MAX_INPUT_LINE];
	int						len = 0;
	int						numCharRead,numCharReadTotal;
	int						ret = 0;
	int						wordindex = 1;
	int 					i,j,k,l;
	int						numwordsperline;
	int						currenterrortype,numwords;
	int						check=0;
	int						pos,numpos=0,measpos;
	int						start,end;
	int						Error2pos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS];
	int						seed;
	enum MeasurementType	measType; 
	double					meas,sample;
	double					**SatMeasError;
	TTime					StartTime;
	TTime					EndTime;

	if (initialized==0) {
		for(i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
			GLOprintNoBias[i]=0;
		}
		initialized=1;
	}
	
	SatMeasError=NULL;
	if(endfile==0) { 

		//If file has not finished, read new lines and check previous active user defined errors		
		while(getLNoComments(line,&len,fd)!=-1) {
			//Take out commas ',' and semicolon ';'
			for(i=0;i<len;i++) {
				if (line[i]==','||line[i]==';') {
					line[i]=' ';
				}
			}
			wordindex=1;
			numwordsperline=0;
			numCharReadTotal=0;
			wordlst[wordindex][0]='#';
			wordlst[wordindex][1]='\0';
			ret = sscanf(line,"%s%n",wordlst[wordindex],&numCharRead);
			if (ret) {
				if (wordlst[wordindex][0]!='#') { // It is not a comment
					numline++;
					numwordsperline++;
					wordindex++;
					numCharReadTotal+=numCharRead;
					while(sscanf(&line[numCharReadTotal],"%s%n",wordlst[wordindex],&numCharRead)==1) {
						numwordsperline++;
						wordindex++;
						numCharReadTotal+=numCharRead;
					}
					if(numline==1) {
						if(numwordsperline!=2) {
							fclose(fd);
							sprintf(messagestr,"Wrong number of columns in the line with time options in [%s] file",filename);
							printError(messagestr,options);
						} else {
							if(strcasecmp(wordlst[1],"ToW")==0) {
								UserError->numcolumnstime=2;
								UserError->timetype=1;
							} else if(strcasecmp(wordlst[1],"SoD")==0) {
								UserError->numcolumnstime=3;
								UserError->timetype=0;
							} else {
								fclose(fd);
								sprintf(messagestr,"'%s' time model not supported in [%s] file",wordlst[1],filename);
								printError(messagestr,options);
							}
							if(strcasecmp(wordlst[2],"Length")==0) {
								UserError->numcolumnstime+=1;
								UserError->lengthtype=0;
							} else if(strcasecmp(wordlst[2],"Time")==0) {
								UserError->numcolumnstime+=3-UserError->timetype;
								UserError->lengthtype=1;
							} else {
								fclose(fd);
								sprintf(messagestr,"'%s' time length not supported in [%s] file",wordlst[2],filename);
								printError(messagestr,options);
							}




						}
					} else if(numline==2) {
						if(numwordsperline!=2) {
							fclose(fd);
							sprintf(messagestr,"Wrong number of columns in line with seed value in [%s] file",filename);
							printError(messagestr,options);
						} else if (strcasecmp(wordlst[1],"Seed")!=0) {
							fclose(fd);
							sprintf(messagestr,"'Seed' must be the first word in second data line in [%s] file",filename);
							printError(messagestr,options);
						} else if (strcasecmp(wordlst[2],"Time")==0) {
							UserError->seed=(unsigned int)time(NULL);	
						} else {
							//Seed is a number
							seed=(int)atoi(wordlst[2]);
							if(seed<0) {
								sprintf(messagestr,"Seed value must be a positive integer number in [%s] file",filename);
								printError(messagestr,options);
							}
							UserError->seed=(unsigned int)seed;
						}

						#if defined (__WIN32__)
							srand(UserError->seed);
						#else
							srandom(UserError->seed);
						#endif	
					} else {
						//We need to check if user defined error active on previous epochs have ended (only once each time we enter this function)
						if(check==0) {
							check=1;
							for(i=0;i<NUMERRORFUNCTIONS;i++) {
								for(j=0;j<UserError->numactiveErrors[i];j++) {
									if(tdiff(&epoch->t,&UserError->activeErrorsEnd[i][j])>0) {
										//An user defined error has finished. Take out the data
										for(k=j;k<UserError->numactiveErrors[i]-1;k++) {
											memcpy(&UserError->activeErrorsStart[i][k],&UserError->activeErrorsStart[i][k+1],sizeof(TTime));
											memcpy(&UserError->activeErrorsEnd[i][k],&UserError->activeErrorsEnd[i][k+1],sizeof(TTime));
											UserError->measType[i][k]=UserError->measType[i][k+1];
											UserError->measFreq[i][k]=UserError->measFreq[i][k+1];
											UserError->System[i][k]=UserError->System[i][k+1];
											UserError->PRN[i][k]=UserError->PRN[i][k+1];
											for(l=0;l<NUMPARAMERRORS;l++) {
												UserError->ErrorParam[i][k][l]=UserError->ErrorParam[i][k+1][l];
											}
										}

										UserError->numactiveErrors[i]=UserError->numactiveErrors[i]-1;
										UserError->totalactiveErrors=UserError->totalactiveErrors-1;
										//Free memory
										free(UserError->ErrorParam[i][k]);
										UserError->activeErrorsStart[i]=realloc(UserError->activeErrorsStart[i],UserError->numactiveErrors[i]*sizeof(TTime));
										UserError->activeErrorsEnd[i]=realloc(UserError->activeErrorsEnd[i],UserError->numactiveErrors[i]*sizeof(TTime));
										UserError->measType[i]=realloc(UserError->measType[i],UserError->numactiveErrors[i]*sizeof(enum MeasurementType));
										UserError->measFreq[i]=realloc(UserError->measFreq[i],UserError->numactiveErrors[i]*sizeof(int));
										UserError->System[i]=realloc(UserError->System[i],UserError->numactiveErrors[i]*sizeof(enum GNSSystem));
										UserError->PRN[i]=realloc(UserError->PRN[i],UserError->numactiveErrors[i]*sizeof(int));
										UserError->ErrorParam[i]=realloc(UserError->ErrorParam[i],(UserError->numactiveErrors[i])*sizeof(double *));
										if(j==UserError->numactiveErrors[i]) break;
										j--;
									}
								}
							}	
						}

						//Check that we have a valid user added error model and the right number of columns
						if(strcasecmp(wordlst[1],"Step")==0) {
							currenterrortype=STEP;
							numwords=NUMWORDSSTEP;
							if(numwordsperline!=numwords+UserError->numcolumnstime) continue;
						} else if(strcasecmp(wordlst[1],"Ramp")==0) {
							currenterrortype=RAMP;
							numwords=NUMWORDSRAMP;
							if(numwordsperline!=numwords+UserError->numcolumnstime) continue;
						} else if (strcasecmp(wordlst[1],"Sinu")==0) {
							currenterrortype=SINUSOIDAL;
							numwords=NUMWORDSSINUSOIDAL;
							if(numwordsperline!=numwords+UserError->numcolumnstime) continue;
						} else if(strcasecmp(wordlst[1],"AWGN")==0) {
							currenterrortype=AWGN;
							numwords=NUMWORDSAWGN;
							if(numwordsperline!=numwords+UserError->numcolumnstime) continue;
						} else { 
							//Not supported model error. Ignore line
							continue;
						}

						//Transform date to MDJN,SoD
						if(UserError->timetype==0) {
							//Using YY/DoY/SoD
							StartTime.MJDN=(int)yeardoy2MJDN(atoi(wordlst[numwords+1]),atoi(wordlst[numwords+2]),atoi(wordlst[numwords+3]));
							StartTime.SoD=atof(wordlst[numwords+3]);
							if (StartTime.MJDN<FIRSTMJDNGPS || StartTime.SoD<0 || StartTime.SoD>=86400) {
								sprintf(messagestr,"Invalid start date in line '%s' in user error file [%s]",line,filename);
								printError(messagestr,options);
							}
							if(UserError->lengthtype==1) {
								EndTime.MJDN=(int)yeardoy2MJDN(atoi(wordlst[numwords+4]),atoi(wordlst[numwords+5]),atoi(wordlst[numwords+6]));
								EndTime.SoD=atof(wordlst[numwords+6]);
								if (EndTime.MJDN<FIRSTMJDNGPS || EndTime.SoD<0 || EndTime.SoD>=86400) {
									sprintf(messagestr,"Invalid end date in line '%s' in user error file [%s]",line,filename);
									printError(messagestr,options);
								}
							} else {
								EndTime.MJDN=StartTime.MJDN;
								EndTime.SoD=StartTime.SoD+atof(wordlst[numwords+4]);
								if(EndTime.SoD>=86400.) {
									EndTime.SoD-=86400.;
									EndTime.MJDN++;
								}
							}
						} else {
							// Using GPSWeek/ToW
							StartTime=gpsws2ttime(atoi(wordlst[numwords+1]),atof(wordlst[numwords+2]));
							if (StartTime.MJDN<FIRSTMJDNGPS || StartTime.SoD<0 || StartTime.SoD>=86400) {
								sprintf(messagestr,"Invalid start date in line '%s' in user error file [%s]",line,filename);
								printError(messagestr,options);
							}
							if(UserError->lengthtype==1) {
								EndTime=gpsws2ttime(atoi(wordlst[numwords+3]),atof(wordlst[numwords+4]));
								if (EndTime.MJDN<FIRSTMJDNGPS || EndTime.SoD<0 || EndTime.SoD>=86400) {
									sprintf(messagestr,"Invalid end date in line '%s' in user error file [%s]",line,filename);
									printError(messagestr,options);
								}
							} else {
								EndTime.MJDN=StartTime.MJDN;
								EndTime.SoD=StartTime.SoD+atof(wordlst[numwords+3]);
								if(EndTime.SoD>=86400.) {
									EndTime.SoD-=86400.;
									EndTime.MJDN++;
								}
							}
						}

						// Check that user defined error starts in this epoch or it started before (due to wrong sorting) but it is still active
						if(tdiff(&epoch->t,&StartTime)<0) {
							// User model error starts ahead of current time. Stop reading, go one line back and exit function
							getLback(line,&len,fd);
							numline--;
							break;
						} else if(tdiff(&epoch->t,&EndTime)>=0) {
							// User model error has already finished. Skip the line
							continue;
						}

						//Check that we have a valid measurement
						measType=measstr2meastype(wordlst[3]);
						if (measType==NA || measType>=ENDMEAS) {
							// Invalid measurement or it is a combination. Skip the line
							continue;
						}

						// Allocate memory for new user-defined error
						UserError->activeErrorsStart[currenterrortype]=realloc(UserError->activeErrorsStart[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(TTime));
						UserError->activeErrorsEnd[currenterrortype]=realloc(UserError->activeErrorsEnd[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(TTime));
						UserError->measType[currenterrortype]=realloc(UserError->measType[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(enum MeasurementType));
						UserError->measFreq[currenterrortype]=realloc(UserError->measFreq[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(int));
						UserError->System[currenterrortype]=realloc(UserError->System[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(enum GNSSystem));
						UserError->PRN[currenterrortype]=realloc(UserError->PRN[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(int));
						UserError->ErrorParam[currenterrortype]=realloc(UserError->ErrorParam[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(double *));
						UserError->ErrorParam[currenterrortype][UserError->numactiveErrors[currenterrortype]]=malloc(sizeof(double)*NUMPARAMERRORS);

						//Copy user-defined error parameters to UserError structure
						memcpy(&UserError->activeErrorsStart[currenterrortype][UserError->numactiveErrors[currenterrortype]],&StartTime,sizeof(TTime));
						memcpy(&UserError->activeErrorsEnd[currenterrortype][UserError->numactiveErrors[currenterrortype]],&EndTime,sizeof(TTime));
						UserError->measType[currenterrortype][UserError->numactiveErrors[currenterrortype]]=measType;
						UserError->measFreq[currenterrortype][UserError->numactiveErrors[currenterrortype]]=getFrequencyInt(measType);
						UserError->System[currenterrortype][UserError->numactiveErrors[currenterrortype]]=gnsschar2gnsstype(wordlst[2][0]);
						UserError->PRN[currenterrortype][UserError->numactiveErrors[currenterrortype]]=atoi(&wordlst[2][1]);
						if (UserError->PRN[currenterrortype][UserError->numactiveErrors[currenterrortype]]<0||UserError->PRN[currenterrortype][UserError->numactiveErrors[currenterrortype]]>=MAX_SATELLITES_PER_GNSS) {
							sprintf(messagestr,"Invalid PRN number '%s' in user defined error file [%s]",&wordlst[2][1],filename);
							printError(messagestr,options);
						}

						for(i=0;i<NUMPARAMERRORS;i++) {
							if(currenterrortype!=SINUSOIDAL && i>0) break;
							UserError->ErrorParam[currenterrortype][UserError->numactiveErrors[currenterrortype]][i]=atof(wordlst[4+i]);
						}

						//Increment counter
						UserError->numactiveErrors[currenterrortype]=UserError->numactiveErrors[currenterrortype]+1;
						UserError->totalactiveErrors=UserError->totalactiveErrors+1;


					} //End if(numline==1)
				} //End if(word[0]=='#')
			} //End if(ret)
		} //End while
	} else {
		//File has finished. Check if active user defined error have ended
		for(i=0;i<NUMERRORFUNCTIONS;i++) {
			for(j=0;j<UserError->numactiveErrors[i];j++) {
				if(tdiff(&epoch->t,&UserError->activeErrorsEnd[i][j])>0) {
					//An user defined error has finished. Take out the data
					for(k=j;k<UserError->numactiveErrors[i]-1;k++) {
						memcpy(&UserError->activeErrorsStart[i][k],&UserError->activeErrorsStart[i][k+1],sizeof(TTime));
						memcpy(&UserError->activeErrorsEnd[i][k],&UserError->activeErrorsEnd[i][k+1],sizeof(TTime));
						UserError->measType[i][k]=UserError->measType[i][k+1];
						UserError->measFreq[i][k]=UserError->measFreq[i][k+1];
						UserError->System[i][k]=UserError->System[i][k+1];
						UserError->PRN[i][k]=UserError->PRN[i][k+1];
						for(l=0;l<NUMPARAMERRORS;l++) {
							UserError->ErrorParam[i][k][l]=UserError->ErrorParam[i][k+1][l];
						}
					}

					UserError->numactiveErrors[i]=UserError->numactiveErrors[i]-1;
					UserError->totalactiveErrors=UserError->totalactiveErrors-1;
					//Free memory
					free(UserError->ErrorParam[i][k]);
					UserError->activeErrorsStart[i]=realloc(UserError->activeErrorsStart[i],UserError->numactiveErrors[i]*sizeof(TTime));
					UserError->activeErrorsEnd[i]=realloc(UserError->activeErrorsEnd[i],UserError->numactiveErrors[i]*sizeof(TTime));
					UserError->measType[i]=realloc(UserError->measType[i],UserError->numactiveErrors[i]*sizeof(enum MeasurementType));
					UserError->measFreq[i]=realloc(UserError->measFreq[i],UserError->numactiveErrors[i]*sizeof(int));
					UserError->System[i]=realloc(UserError->System[i],UserError->numactiveErrors[i]*sizeof(enum GNSSystem));
					UserError->PRN[i]=realloc(UserError->PRN[i],UserError->numactiveErrors[i]*sizeof(int));
					UserError->ErrorParam[i]=realloc(UserError->ErrorParam[i],(UserError->numactiveErrors[i])*sizeof(double *));
					if(j==UserError->numactiveErrors[i]-1) break;
					j--;
				}
			}
		}
	}



	//Add user defined error
	if(UserError->totalactiveErrors>0) {
		//There are active errors
		//Initialize Error2pos vector
		for(i=0;i<MAX_GNSS;i++) {
			for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
				for(k=0;k<MAX_MEASUREMENTS_NO_COMBINATIONS;k++) {
					Error2pos[i][j][k]=-1;
				}
			}
		}
		for(i=0;i<NUMERRORFUNCTIONS;i++) {
			for(j=0;j<UserError->numactiveErrors[i];j++) {
				if(UserError->PRN[i][j]==0) {
					//This user defined error applies to all satellites in the constellation
					start=1;
					end=MAX_SATELLITES_PER_GNSS;
				} else {
					start=UserError->PRN[i][j];
					end=UserError->PRN[i][j]+1;
				}
				for(k=start;k<end;k++) {
					//Check that we have data from the satellite 
					meas=getMeasurementValue(epoch,UserError->System[i][j],k,&UserError->measType[i][j],&UserError->measFreq[i][j]);
					if (options->includeSatellite[UserError->System[i][j]][k]==0) continue; //Skip unselected satellites 
					if(meas==-1) continue; //No data for this PRN and measurement
					pos=Error2pos[UserError->System[i][j]][k][UserError->measType[i][j]];
					if(pos==-1) {
						// This satellite and measurement has not appeared before
						pos=numpos;
						numpos++;
						Error2pos[UserError->System[i][j]][k][UserError->measType[i][j]]=pos;
						SatMeasError=realloc(SatMeasError,numpos*sizeof(double *));
						SatMeasError[pos]=(double *)calloc(USRNUMPOS,sizeof(double)); //Allocated memory is initialized to 0 inside calloc function
						SatMeasError[pos][USRGNSSPOS]=UserError->System[i][j];
						SatMeasError[pos][USRPRNPOS]=k;
						SatMeasError[pos][USRMEASPOS]=UserError->measType[i][j];
						SatMeasError[pos][USRFREQPOS]=(double)UserError->measFreq[i][j];
						SatMeasError[pos][USRMEASRAWPOS]=meas;
						SatMeasError[pos][USRMEASTOTPOS]=meas;
					}

					// Seek satellite position in epoch structure
					for (l=0;l<epoch->numSatellites;l++) {
						if (epoch->sat[l].GNSS == UserError->System[i][j] && epoch->sat[l].PRN == k) {
							SatMeasError[pos][USREPOCHPOS]=l;
							break;
						}
					}
						

					switch(i) {
						case(STEP):
							SatMeasError[pos][USRNUMSTEPPOS]++;
							sample=UserError->ErrorParam[i][j][AMPLITUDE];
							SatMeasError[pos][USRSTEPERRPOS]+=sample;

							break;
						case(RAMP):
							SatMeasError[pos][USRNUMRAMPPOS]++;
							sample=UserError->ErrorParam[i][j][AMPLITUDE]*tdiff(&epoch->t,&UserError->activeErrorsStart[i][j]);
							SatMeasError[pos][USRRAMPERRPOS]+=sample;
							break;
						case(SINUSOIDAL):
							SatMeasError[pos][USRNUMSINUPOS]++;
							sample=UserError->ErrorParam[i][j][AMPLITUDE]*sin((2*Pi*epoch->t.SoD/UserError->ErrorParam[i][j][PERIOD])+UserError->ErrorParam[i][j][OFFSET]*d2r);
							SatMeasError[pos][USRSINUERRPOS]+=sample;
							break;
						case(AWGN):
							SatMeasError[pos][USRNUMAWGNPOS]++;
							sample=AWGN_generator(UserError->ErrorParam[i][j][STDAWGN]);
							SatMeasError[pos][USRAWGNERRPOS]+=sample;
							break;
						default:
							break;
					} //End switch(i)

					//Increment total number of user defined errors added
					SatMeasError[pos][USRNUMTOTERRPOS]++;

					//Sum user added error to total 
					SatMeasError[pos][USRTOTERRPOS]+=sample;
					SatMeasError[pos][USRMEASTOTPOS]+=sample;

					//Add sample in epoch structure 
					measpos=epoch->measOrder[UserError->System[i][j]].meas2Ind[UserError->measType[i][j]];
					if(measpos!=-1) {
						if (whatIs(UserError->measType[i][j])==CarrierPhase) {
							if(epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].GNSS==GLONASS) {
								//Check if we have a valid conversion factor
								if (epoch->measOrder[epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].GNSS].lambdaMeas[(int)SatMeasError[i][USRFREQPOS]][(int)SatMeasError[pos][USRPRNPOS]]!=1.) {
									//Conversion factor available
									epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].meas[measpos].value+=sample/epoch->measOrder[epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].GNSS].lambdaMeas[(int)SatMeasError[i][USRFREQPOS]][(int)SatMeasError[pos][USRPRNPOS]];
								} else {
									if(GLOprintNoBias[(int)SatMeasError[pos][USRPRNPOS]]==0) {
										//Only print message first time
										GLOprintNoBias[(int)SatMeasError[pos][USRPRNPOS]]=1;
										sprintf(messagestr,"WARNING Frequency offset for GLONASS PRN %2d not available. User added error in phase measurements for this satellite will not be applied",(int)SatMeasError[pos][USRPRNPOS]);
										printInfo(messagestr,options);
									}
								}
							} else {
								epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].meas[measpos].value+=sample/epoch->measOrder[epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].GNSS].conversionFactor[UserError->measType[i][j]];
							}
						} else {
							epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].meas[measpos].value+=sample;
						}
					} else {
						sprintf(messagestr,"WARNING Measurement %3s is not in observation file. User added error for this measurement will not be applied",meastype2measstr(UserError->measType[i][j]));
						printInfo(messagestr,options);
					}
				} //End for(k=start;k<end;k++) 
			} //End for(j=0;j<UserError->numactiveErrors[i];j++)
		} //End for(i=0;i<NUMERRORFUNCTIONS;i++)

		if(options->printUserError==1) {
			printUserError(epoch,SatMeasError,numpos,options);
		}


		//Free memory
		for(i=0;i<numpos;i++) {
			free(SatMeasError[i]);
		}
		free(SatMeasError);

	} //End if(UserError->totalactiveErrors>0)

	if(options->printUserError==1) {
		//Empty UserError print buffers
		for (i=0;i<epoch->numPrintGNSS;i++) {
			for(j=0;j<epoch->numSatellitesGNSS[i];j++) {
				for (k=0;k<linesstoredUserError[i][j];k++) {
					fprintf(options->outFileStream,"%s",printbufferUserError[i][j][k]);
					free(printbufferUserError[i][j][k]);
				}
				linesstoredUserError[i][j]=0;
				free(printbufferUserError[i][j]);
				printbufferUserError[i][j]=NULL;
			}
		}
	}

	if(feof_function(fd)>0) endfile=1;
}

/*****************************************************************************
 * Name        : readReferenceFile
 * Description : Open reference position file, check if it is a SP3 or 
 *                columnar text file and read it
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TEpoch  *epoch                  IO N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => File type not valid
 *                                         -3 => SP3 File has incorrect number of entries in header (deprecated)
 *                                         -4 => SP3 File can not be concatenated more than three times
 *                                         -5 => SP3 File cannot have more than one satellite in the file
 *                                         -6 => Error reading SP3 file
 *****************************************************************************/
int readReferenceFile (char  *filename, TGNSSproducts *RefPosition, TOptions  *options) {

	FILE  					*fd;
	int 					ret;
	static enum fileType    Posfile;
	TGNSSproducts			nextSP3Prod;
	TGNSSproducts			pastSP3Prod;
	

	initGNSSproducts(&nextSP3Prod);
	initGNSSproducts(&pastSP3Prod);

	fd=fopen(filename,"rb");
	if (fd==NULL) {
		return -1;
	}
	Posfile=whatFileTypeIs(filename);
	if (Posfile!=ftSP3 && Posfile!=ftSBASEMSMESSAGE && Posfile!=ftUNKNOWN) {
		//File can be a SP3 or columnar text file. Columnar text file
		//may be detected as a EMS file or unknown type)
		return -2;
	}
	if (Posfile==ftSP3) {
		ret=readSP3 (fd, &pastSP3Prod, 1, 0, 1, options);	
		if (ret==-2) {
			return -3;
		} else if (ret==-3) {
			return -5;
		} else if (ret<=0) {
			return -6;
		} else if (ret==2) {
			ret=readSP3 (fd, RefPosition, 1, 0, 1, options);
			if (ret==-2) {
				return -3;
			} else if (ret==-3) {
				return -5;
			} else if (ret<=0) {
				return -6;
			} else if (ret==2) {
				ret=readSP3 (fd, &nextSP3Prod, 1, 0, 1, options);
				if (ret==-2) {
					return -3;
				} else if (ret==-3) {
					return -5;
				} else if (ret<=0) {
					return -6;
				} else if (ret==2) {
					return -4;
				}
			} else	{
				memcpy(&nextSP3Prod,RefPosition,sizeof(TGNSSproducts));
			}
		} else {
			memcpy(RefPosition,&pastSP3Prod,sizeof(TGNSSproducts));
			memcpy(&nextSP3Prod,RefPosition,sizeof(TGNSSproducts));
		}
		fclose(fd);
		RefPosition->SP3->orbits.index[0][0] = 0; //There only be one position for the index (the reference position, which will be stored at 0,0)
		nextSP3Prod.SP3->orbits.index[0][0] = 0; //There only be one position for the index (the reference position, which will be stored at 0,0)
		pastSP3Prod.SP3->orbits.index[0][0] = 0; //There only be one position for the index (the reference position, which will be stored at 0,0)
		ConcatenateSP3(1,RefPosition,&pastSP3Prod,&nextSP3Prod,options);
		freeSP3data(&pastSP3Prod);
		freeSP3data(&nextSP3Prod);
	} else {
		readPosFile (fd, filename, RefPosition, options);	
		fclose(fd);
	}
	return 1;
}

/*****************************************************************************
 * Name        : readPosFile
 * Description : Read columnar text file with reference position and save data
 *                in SP3 blocks (for later interpolation, if necessary)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * char  *filename                 I  N/A  Name of the file
 * TGNSSproducts *RefPosition      IO N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void readPosFile (FILE  *fd, char  *filename, TGNSSproducts *RefPosition, TOptions  *options) {

    static int      numfileline=0,numvalidline=-1;
    char            line[MAX_INPUT_LINE];
	char			aux[100];
	double			r;
	double			PositionNEU[3],PositionXYZ[3];
	double			seconds;
	double			Interval;
    int             len = 0;
    int             ret = 0;
    int             wordindex = 1;
    int             i;
	int				lenDate,lenTime;
	int				invalidDate=0;
	int				numCharRead,numCharReadTotal;
	int				rtkgeodeticheight=0; //Check if RTK is using height from the ellipsoid
    int             numwordsperline;
    int             numcolumns=0;
	int				usedRecords=0;
	int				lastcolumn=0;
	int				rtkformat=0;
	int				YearAvail=0,DoYAvail=0,SoDAvail=0,GPSWeekAvail=0,SoWAvail=0,DateAvail=0,TimeAvail=0;
	int				XAvail=0,YAvail=0,ZAvail=0,LonAvail=0,LatAvail=0,HeightAvail=0;
	int				YearPos,DoYPos,SoDPos,GPSWeekPos,SoWPos,DatePos,TimePos,XPos,YPos,ZPos,LatPos,LonPos,HeightPos;
	int				DataFormat; //0->Year/DoY/SoD XYZ 1->Year/DoY/SoD Lon Lat Height 2->GPSWeek SoW XYZ 3->GPSWeek SoW Lon Lat Height
	                            //4->Date Time XYZ 5->Date Time Lon Lat Height
	struct tm		tm;

	//Set space for SP3 orbits and initialize
	RefPosition->SP3=malloc(sizeof(TSP3products));
	initSP3products(RefPosition->SP3);
	RefPosition->SP3->orbits.numSatellites = 1;
	RefPosition->SP3->orbits.numSatellitesRead = 1;

	RefPosition->SP3->orbits.block = malloc(sizeof(TSP3orbitblock*)*RefPosition->SP3->orbits.numSatellites);
	RefPosition->SP3->orbits.block[0]=NULL;
	RefPosition->SP3->orbits.index[0][0] = 0; //There only be one position for the index (the reference position, which will be stored at 0,0)

	//High initial value, as the interval between samples used will be the smallest found in file. In a reference file, it is very likely
	//that there will be data gaps of several sizes (for the cases that solution cannot be computed), so interval must be computed each epoch
	RefPosition->SP3->orbits.interval = 999999; 

	while(getLNoComments(line,&len,fd)!=-1) {
		//Take out commas ',' and semicolon ';'
		for(i=0;i<len;i++) {
			if (line[i]==','||line[i]==';') {
				line[i]=' ';
			}
		}
		numfileline++;
		wordindex=1;
		numwordsperline=0;
		numCharReadTotal=0;
		wordlst[wordindex][0]='#';
		wordlst[wordindex][1]='\0';
		ret = sscanf(line,"%s%n",wordlst[wordindex],&numCharRead);
		if (ret) {
			if (wordlst[wordindex][0]!='#') { // It is not a comment
				numvalidline++;
				numwordsperline++;
				wordindex++;
				numCharReadTotal+=numCharRead;
				while(sscanf(&line[numCharReadTotal],"%s%n",wordlst[wordindex],&numCharRead)==1) {
					numwordsperline++;
					wordindex++;
					numCharReadTotal+=numCharRead;
				}
				if (wordlst[1][0]=='%') {
					if (wordindex>2) {
						if (strcasecmp(wordlst[2],"GPST")==0) { 
							rtkformat=1; //RTK line format
						} else if (strstr(wordlst[2],"lat/lon/height=WGS84/geodetic")!=NULL) {
							rtkgeodeticheight=1;
						}

					}
					if (rtkformat==0) {
						continue; //Comment line with %
					}
				}

				if(numwordsperline!=numcolumns) { 
					if (numcolumns==0) {
						//First data line read
						if (numwordsperline<5) { 
							sprintf(messagestr,"Number of columns in file must be at least 5 (GPSWeek SoW X Y Z) or 6 (Year DoY SoD X Y Z) in [%s] file",filename);
							printError(messagestr,options);
						} else {
							numcolumns=numwordsperline;
							for(i=1;i<=numwordsperline;i++) {
								if (strcasecmp(wordlst[i],"Year")==0) {
									YearAvail=1;
									YearPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"DoY")==0) {
									DoYAvail=1;
									DoYPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"SoD")==0) {
									SoDAvail=1;
									SoDPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"GPSWeek")==0) {
									GPSWeekAvail=1;
									GPSWeekPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"SoW")==0) {
									SoWAvail=1;
									SoWPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"X")==0) {
									XAvail=1;
									XPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Y")==0) {
									YAvail=1;
									YPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Z")==0) {
									ZAvail=1;
									ZPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Lon")==0||strcasecmp(wordlst[i],"Longitude")==0) {
									LonAvail=1;
									LonPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Lat")==0|| strcasecmp(wordlst[i],"Latitude")==0) {
									LatAvail=1;
									LatPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Height")==0) {
									HeightAvail=1;
									HeightPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Date")==0) {
									DateAvail=1;
									DatePos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"Time")==0) {
									TimeAvail=1;
									TimePos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"GPST")==0 && rtkformat==1 )  {
									DateAvail=1;
									DatePos=i-1;
									TimeAvail=1;
									TimePos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"x-ecef(m)")==0 && rtkformat==1 )  {
									XAvail=1;
									XPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"y-ecef(m)")==0 && rtkformat==1 )  {
									YAvail=1;
									YPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"z-ecef(m)")==0 && rtkformat==1 )  {
									ZAvail=1;
									ZPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"latitude(deg)")==0 && rtkformat==1 )  {
									LatAvail=1;
									LatPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"longitude(deg)")==0 && rtkformat==1 ) {
									LonAvail=1;
									LonPos=i;
									if (i>lastcolumn) lastcolumn=i;
								} else if (strcasecmp(wordlst[i],"height(m)")==0 && rtkformat==1 ) {
									HeightAvail=1;
									HeightPos=i;
									if (i>lastcolumn) lastcolumn=i;
								}
							}
							//Year, DoY, SoD is looked first, as it is preferred if both appear
							if (YearAvail==1 && DoYAvail==1 && SoDAvail==1 && XAvail==1 && YAvail==1 && ZAvail==1 ) {
								DataFormat=0;
							} else if (YearAvail==1 && DoYAvail==1 && SoDAvail==1 && LonAvail==1 && LatAvail==1 && HeightAvail==1 ) {
								DataFormat=1;
							} else if (GPSWeekAvail==1 && SoWAvail==1 && XAvail==1 && YAvail==1 && ZAvail==1 ) {
								DataFormat=2;
							} else if (GPSWeekAvail==1 && SoWAvail==1 && LonAvail==1 && LatAvail==1 && HeightAvail==1 ) {
								DataFormat=3;
							} else  if (DateAvail==1 && TimeAvail==1 && XAvail==1 && YAvail==1 && ZAvail==1 ) {
								DataFormat=4;
							} else  if (DateAvail==1 && TimeAvail==1 && LonAvail==1 && LatAvail==1 && HeightAvail==1 ) {
								DataFormat=5;
							} else {
								 printError("First line of data must have the column identifiers with at least the following fields: 'Year DoY SoD X Y Z' or 'Year DoY SoD Lon Lat Height' 'GPSWeek SoW X Y Z' or 'GPSWeek SoW Lon Lat Height' or 'Date Time X Y Z' or 'Date Time Lon Lat Height' or '%% GPST x-ecef(m) y-ecef(m) z-ecef(m)' (rtklib format) in order to indicate the date and position fields (order is not important)",options);
							}
						}
						continue;
					} else if (numwordsperline<lastcolumn) {
						sprintf(messagestr,"All lines must have at least %d columns as stated in the first line in [%s] file. Line number %d has %d columns instead of %d",lastcolumn,filename,numfileline,numwordsperline,lastcolumn);
						printError(messagestr,options);
					}
				}
				//Save data in SP3 orbit clock, so it can be interpolated if necessary
				RefPosition->SP3->orbits.block[0] = realloc(RefPosition->SP3->orbits.block[0],sizeof(TSP3orbitblock)*(usedRecords+1)); //Every orbit position will be for each position read
				initSP3orbitblock(&RefPosition->SP3->orbits.block[0][usedRecords]);

				//Read epoch
				if (DataFormat==0) {
					//Year DoY SoD X Y Z format
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN=(int)yeardoy2MJDN(atoi(wordlst[YearPos]),atoi(wordlst[DoYPos]),atoi(wordlst[SoDPos]));
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD=atof(wordlst[SoDPos]);
					if (RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN<FIRSTMJDNGPS || RefPosition->SP3->orbits.block[0][usedRecords].t.SoD<0
							|| RefPosition->SP3->orbits.block[0][usedRecords].t.SoD>=86400) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else if (DataFormat==1) {
					//Year DoY SoD Lon Lat Height format
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN=(int)yeardoy2MJDN(atoi(wordlst[YearPos]),atoi(wordlst[DoYPos]),atoi(wordlst[SoDPos]));
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD=atof(wordlst[SoDPos]);
					if (RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN<FIRSTMJDNGPS || RefPosition->SP3->orbits.block[0][usedRecords].t.SoD<0
							|| RefPosition->SP3->orbits.block[0][usedRecords].t.SoD>=86400) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					PositionNEU[0]=atof(wordlst[LatPos]);
					PositionNEU[1]=atof(wordlst[LonPos]);
					PositionNEU[2]=atof(wordlst[HeightPos]);
					//Check coordinates are in [-90..90] and [-180..180]
					if (PositionNEU[0]>90.||PositionNEU[0]<-90.) {
						sprintf(messagestr,"Latitude must be in the range [-90..90] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if ( PositionNEU[1]>180.||PositionNEU[1]<-180.) {
						sprintf(messagestr,"Longitude must be in the range [-180..180] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else {
						//Correct geoid height if necessary
						if (rtkgeodeticheight==1) {
							PositionNEU[2]+=getEGM96Height(PositionNEU);
						}
						PositionNEU[0]*=d2r;
						PositionNEU[1]*=d2r;
					}
					NEU2XYZ(PositionNEU,PositionXYZ);
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=PositionXYZ[0];
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=PositionXYZ[1];
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=PositionXYZ[2];
				} else if (DataFormat==2) {
					//GPSWeek SoW X Y Z format
					RefPosition->SP3->orbits.block[0][usedRecords].t=gpsws2ttime(atoi(wordlst[GPSWeekPos]),atof(wordlst[SoWPos]));
					if (RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN<FIRSTMJDNGPS || RefPosition->SP3->orbits.block[0][usedRecords].t.SoD<0
							|| RefPosition->SP3->orbits.block[0][usedRecords].t.SoD>=86400) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else if (DataFormat==3) {
					//GPSWeek SoW Lat Lon Height format
					RefPosition->SP3->orbits.block[0][usedRecords].t=gpsws2ttime(atoi(wordlst[GPSWeekPos]),atof(wordlst[SoWPos]));
					if (RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN<FIRSTMJDNGPS || RefPosition->SP3->orbits.block[0][usedRecords].t.SoD<0
							|| RefPosition->SP3->orbits.block[0][usedRecords].t.SoD>=86400) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					PositionNEU[0]=atof(wordlst[LatPos]);
					PositionNEU[1]=atof(wordlst[LonPos]);
					PositionNEU[2]=atof(wordlst[HeightPos]);
					//Check coordinates are in [-90..90] and [-180..180]
					if (PositionNEU[0]>90.||PositionNEU[0]<-90.) {
						sprintf(messagestr,"Latitude must be in the range [-90..90] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if ( PositionNEU[1]>180.||PositionNEU[1]<-180.) {
						sprintf(messagestr,"Longitude must be in the range [-180..180] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else {
						//Correct geoid height if necessary
						if (rtkgeodeticheight==1) {
							PositionNEU[2]+=getEGM96Height(PositionNEU);
						}
						PositionNEU[0]*=d2r;
						PositionNEU[1]*=d2r;
					}
					NEU2XYZ(PositionNEU,PositionXYZ);
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=PositionXYZ[0];
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=PositionXYZ[1];
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=PositionXYZ[2];
				} else if (DataFormat==4) {
					//Date Time X Y Z format (or rtklib '% GPST X Y Z')
					lenDate=(int)strlen(wordlst[DatePos]);
					lenTime=(int)strlen(wordlst[TimePos]);
					if(lenDate!=10) {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[DatePos][4]!='/'||wordlst[DatePos][7]!='/') {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (lenTime!=12) {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[TimePos][2]!=':'||wordlst[TimePos][5]!=':'||wordlst[TimePos][8]!='.') {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					invalidDate=0;
					getstr(aux,wordlst[DatePos],lenDate,0,4);
					tm.tm_year = atoi(aux);
					if (tm.tm_year<=1900) invalidDate=1;
					tm.tm_year -= 1900;
					getstr(aux,wordlst[DatePos],lenDate,5,2);
					tm.tm_mon  = atoi(aux);
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,wordlst[DatePos],lenDate,8,2);
					tm.tm_mday = atoi(aux);
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,0,2);
					tm.tm_hour = atoi(aux);
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,3,2);
					tm.tm_min  = atoi(aux);
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,6,6);
					tm.tm_sec  = atoi(aux);
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
					if (invalidDate==1) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					seconds = atof(aux);
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN = MJDN(&tm);
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else {
					//Date Time Lat Lon Height format
					lenDate=(int)strlen(wordlst[DatePos]);
					lenTime=(int)strlen(wordlst[TimePos]);
					if(lenDate!=10) {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[DatePos][4]!='/'||wordlst[DatePos][7]!='/') {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (lenTime!=12) {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[TimePos][2]!=':'||wordlst[TimePos][5]!=':'||wordlst[TimePos][8]!='.') {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					invalidDate=0;
					getstr(aux,wordlst[DatePos],lenDate,0,4);
					tm.tm_year = atoi(aux);
					if (tm.tm_year<=1900) invalidDate=1;
					tm.tm_year -= 1900;
					getstr(aux,wordlst[DatePos],lenDate,5,2);
					tm.tm_mon  = atoi(aux);
					if (tm.tm_mon<=0||tm.tm_mon>12) invalidDate=1;
					tm.tm_mon  -= 1;
					getstr(aux,wordlst[DatePos],lenDate,8,2);
					tm.tm_mday = atoi(aux);
					if (tm.tm_mday<=0||tm.tm_mday>31) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,0,2);
					tm.tm_hour = atoi(aux);
					if (tm.tm_hour<0 || tm.tm_hour>23) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,3,2);
					tm.tm_min  = atoi(aux);
					if (tm.tm_min<0 || tm.tm_min>59) invalidDate=1;
					getstr(aux,wordlst[TimePos],lenTime,6,6);
					tm.tm_sec  = atoi(aux);
					if (tm.tm_sec<0 || tm.tm_sec>60) invalidDate=1;	//Seconds can have value 60 when a leap second is inserted
					seconds = atof(aux);
					if (invalidDate==1) {
						sprintf(messagestr,"Invalid date in line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN = MJDN(&tm);
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					PositionNEU[0]=atof(wordlst[LatPos]);
					PositionNEU[1]=atof(wordlst[LonPos]);
					PositionNEU[2]=atof(wordlst[HeightPos]);
					//Check coordinates are in [-90..90] and [-180..180]
					if (PositionNEU[0]>90.||PositionNEU[0]<-90.) {
						sprintf(messagestr,"Latitude must be in the range [-90..90] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if ( PositionNEU[1]>180.||PositionNEU[1]<-180.) {
						sprintf(messagestr,"Longitude must be in the range [-180..180] degrees. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else {
						//Correct geoid height if necessary
						if (rtkgeodeticheight==1) {
							PositionNEU[2]+=getEGM96Height(PositionNEU);
						}
						PositionNEU[0]*=d2r;
						PositionNEU[1]*=d2r;
					}
					NEU2XYZ(PositionNEU,PositionXYZ);
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=PositionXYZ[0];
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=PositionXYZ[1];
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=PositionXYZ[2];
				}
				r = sqrt(RefPosition->SP3->orbits.block[0][usedRecords].x[0]*RefPosition->SP3->orbits.block[0][usedRecords].x[0] + 
						 RefPosition->SP3->orbits.block[0][usedRecords].x[1]*RefPosition->SP3->orbits.block[0][usedRecords].x[1] + 
						 RefPosition->SP3->orbits.block[0][usedRecords].x[2]*RefPosition->SP3->orbits.block[0][usedRecords].x[2]);
				if ( r < (MIN_EARTH_RADIUS-1000.) ) {
					sprintf(messagestr,"Receiver a priori position must be above Earth surface (%.2f vs %.2f). Check line number %d in file [%s]",r,MIN_EARTH_RADIUS-1000.0,numfileline,filename);
					printError(messagestr,options);
				} 

				if (numvalidline==1) {
					//First line read, save first epoch read
					memcpy(&RefPosition->SP3->orbits.startTime,&RefPosition->SP3->orbits.block[0][usedRecords].t,sizeof(TTime));
				} else {
					//Check that current is epoch is ahead of previous one
					Interval=tdiff(&RefPosition->SP3->orbits.block[0][usedRecords].t,&RefPosition->SP3->orbits.block[0][usedRecords-1].t);
					if (Interval<=0.) {
						//Current epoch is before or equal previous one. Show an error and exit
						sprintf(messagestr,"All data lines must be sort in chronological order in [%s] file. Check line %d of file",filename,numfileline);
						printError(messagestr,options);
					}
					RefPosition->SP3->orbits.interval=min(RefPosition->SP3->orbits.interval,Interval);
				}

				usedRecords++;

			} //If word[0]!='#'
		}//End if(ret)
	}//End while(getL)

	if (numvalidline==0) {
		sprintf(messagestr,"Reference position file [%s] has no data lines",filename);
		printError(messagestr,options);
	} else {
		//Save last epoch read
		memcpy(&RefPosition->SP3->orbits.endTime,&RefPosition->SP3->orbits.block[0][usedRecords-1].t,sizeof(TTime));
		RefPosition->SP3->orbits.numRecords=usedRecords;
		//Check number of data lines are enough for the selected interpolation
		if(usedRecords<=options->RefDegInterp) {
			sprintf(messagestr,"There are %d data lines, but for a interpolation degree of %d, the minimum data lines required are %d",usedRecords,options->RefDegInterp,options->RefDegInterp+1);
			printError(messagestr,options);
		}
		ConcatenateSP3(1,RefPosition,RefPosition,RefPosition,options);
	}


	return;
}

