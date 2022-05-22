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
 * File: input.c
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
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
 *       END_RELEASE_HISTORY
 *****************************/

/* External classes */
#include "input.h"
#include "output.h"
#include <limits.h>
#include <unistd.h>

//Import global variable printProgress
extern int 	printProgress;
extern int 	printProgressConvert;

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
	unsigned long int remainder = 0;
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
		remainder += ( b<<(16-j*8) );
	}

	data = remainder;
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
			remainder = data^key;
			data = remainder;
		}
		else if( shift == BYTEBITS*(len+3) ) remainder = data;
	}

	if ( remainder == parity ) check = 1;

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
	char sid[7];
	char l1_code;
	char l1_pseudo[25];
	char l1_partPhase[21];
	char l1_lock[8];
	char l1_N[9];
	char l1_cnr[9];
	char l2_code[3];
	char differ[15];
	char l2_partPhase[21];
	char l2_lock[8];
	char l2_cnr[9];
	char *endptr;
	int i;
	unsigned long long int a;

	for ( i = 0; i < ns; i++ ) {
		getstr(sid,body_str, 125 * i, 6);
		l1_code=body_str[6 + 125 * i];
		getstr(l1_pseudo, body_str, 7 + 125 * i, 24);
		getstr(l1_partPhase, body_str, 31 + 125 * i, 20);
		getstr(l1_lock, body_str, 51 + 125 * i, 7);
		getstr(l1_N, body_str, 58 + 125 * i, 8);
		getstr(l1_cnr, body_str, 66 + 125 * i, 8);
		getstr(l2_code, body_str, 74 + 125 * i, 2);
		getstr(differ, body_str, 76 + 125 * i, 14);
		getstr(l2_partPhase, body_str, 90 + 125 * i, 20);
		getstr(l2_lock, body_str, 110 + 125 * i, 7);
		getstr(l2_cnr, body_str, 117 + 125 * i, 8);

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
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void readRTCM3header (TEpoch *epoch, TEpoch *epochDGNSS, TRTCM3 *rtcm3, TOptions *options) {
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
		trim(epochDGNSS->receiver.antenna.type_radome);
	}

	// ARP
	epochDGNSS->receiver.ARP[2] = rtcm3->msg1006.antenna_height; // H
	epochDGNSS->receiver.ARP[1] = 0.0; // E
	epochDGNSS->receiver.ARP[0] = 0.0; // N

	// Types of Observations
	// "C1","L1","S1","P2","L2","S2"
	epochDGNSS->measOrder[GPS].nDiffMeasurements = 6;
	epochDGNSS->measOrder[GPS].GNSS = GPS;
	epochDGNSS->numGNSS = 1;
	meas = measstr2meastype("C1");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 0;
	epochDGNSS->measOrder[GPS].ind2Meas[0] = meas;
	meas = measstr2meastype("L1");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = GPSl1;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 1;
	epochDGNSS->measOrder[GPS].ind2Meas[1] = meas;
	meas = measstr2meastype("S1");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 2;
	epochDGNSS->measOrder[GPS].ind2Meas[2] = meas;
	meas = measstr2meastype("P2");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 3;
	epochDGNSS->measOrder[GPS].ind2Meas[3] = meas;
	meas = measstr2meastype("L2");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = GPSl2;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
	epochDGNSS->measOrder[GPS].meas2Ind[meas] = 4;
	epochDGNSS->measOrder[GPS].ind2Meas[4] = meas;
	meas = measstr2meastype("S2");
	epochDGNSS->measOrder[GPS].conversionFactor[meas] = 1.0;
	epochDGNSS->measOrder[GPS].usable[meas] = 1;
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
	*rtcm3->hour = (int)(floor(hour_d));
	intHour = (int)(floor(hour_d));
	doubleHour = floor(hour_d);
	// Minutes
	mins_d = (hour_d-doubleHour) * 60.0;
	mins = (int)(floor(mins_d));
	// Seconds
	sec = (mins_d-(double)(mins)) * 60.0;

	// Check if a day has passed
	if ( rtcm3->doWeHaveHeader > 2 && intHour < (int)*rtcm3->previousHour ) {
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

	// Loop for every satellite
	epochDGNSS->numSatellites = rtcm3->header.gps_no;
	for ( i = 0; i < rtcm3->header.gps_no; i++ ) {
		lli1 = 0; lli2 = 0;

		epochDGNSS->sat[i].PRN = rtcm3->msg1004[i].satellite_id;
		ind = rtcm3->msg1004[i].satellite_id;
		epochDGNSS->sat[i].GNSS = GPS;
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

		// C1P
		ind = 0;
		epochDGNSS->sat[i].meas[ind].value = C1;
		epochDGNSS->sat[i].meas[ind].rawvalue = C1;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].SNR = (int)snr1;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = S1;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// L1P
		ind = 1;
		epochDGNSS->sat[i].meas[ind].value = L1;
		epochDGNSS->sat[i].meas[ind].rawvalue = L1;
		epochDGNSS->sat[i].meas[ind].LLI = lli1;
		epochDGNSS->sat[i].meas[ind].SNR = (int)snr1;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = S1;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// S1
		ind = 2;
		epochDGNSS->sat[i].meas[ind].value = S1;
		epochDGNSS->sat[i].meas[ind].rawvalue = S1;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].SNR = 0;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = 0;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// C2P
		ind = 3;
		epochDGNSS->sat[i].meas[ind].value = C2;
		epochDGNSS->sat[i].meas[ind].rawvalue = C2;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].SNR = (int)snr2;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = S2;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// L2
		ind = 4;
		epochDGNSS->sat[i].meas[ind].value = L2;
		epochDGNSS->sat[i].meas[ind].rawvalue = L2;
		epochDGNSS->sat[i].meas[ind].LLI = lli2;
		epochDGNSS->sat[i].meas[ind].SNR = (int)snr2;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = S2;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// S2
		ind = 5;
		epochDGNSS->sat[i].meas[ind].value = S2;
		epochDGNSS->sat[i].meas[ind].rawvalue = S2;
		epochDGNSS->sat[i].meas[ind].LLI = 0;
		epochDGNSS->sat[i].meas[ind].SNR = 0;
		epochDGNSS->sat[i].meas[ind].SNRdBHz = 0;
		epochDGNSS->sat[i].meas[ind].dataFlag = 0;

		// Update satellites' dictionary
		if (epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]==-1) {
			epochDGNSS->satCSIndex[epochDGNSS->sat[i].GNSS][epochDGNSS->sat[i].PRN]=lastCSindex;
			lastCSindex++;
		}
	}

	// Update the previous hour to control if a day has passed
	*rtcm3->previousHour = intHour;

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
	FILE			*frin;
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
		fflush(options->terminalStream);
	}

	if ( options->RTCMmode == ConvertRTCM3 ) {
		frin = fopen(fileRINEXpointer, "wa");
	}
	
	while ( !feof(fd) && out == 0 ) {

		ch = fgetc(fd);
		CurrentPos++;
		if ( feof(fd) != 0 ) return 2;
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
							fflush(options->terminalStream);
						} else {
							//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
							if ((int)CurrentPercentage!=(int)PreviousPercentage) {
								fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
								fflush(options->terminalStream);
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
					readRTCM3header(epoch, epochDGNSS, rtcm3, options);
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
	else if ( feof(fd) != 0 ) return 2;

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
			ch = fgetc(fp);
			if ( feof(fp) ) {
				*checkControl = 1;
				data->indicator_end = 1;
				break;
			}
			i++;
			if ( ferror(fp) != 0 ) {
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
	int i, j;
	char indicator_word = '1';
	
	for ( j = 0; j < n; j++ ) {
		if ( (bitChar(in_arr[j], 6) == '1' ) && (bitChar(in_arr[j], 7) == '0') )
			for ( i = 0; i < BYTEFORMATBIT; i++ ) out_arr[BYTEFORMATBIT*j+i] = bitChar(in_arr[j], i);
		else indicator_word = '0';
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
	const int a = 2;
	int i;
	char check = '0';
	int old_d29 = last2bits[1];
	int old_d30 = last2bits[0];
	char ch[31];
	int aux[30];
	char originalParity[PARITYBIT+1];
	char computedParity[PARITYBIT+1];

	for ( i = 0; i < 24; i++ ) {
		switch ( msg[i] ) {
			case '0': 
				 aux[i] = old_d30 - 0;
				 break;
			case '1':
				 aux[i] = 1 - old_d30;
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
	getstr(computedParity,  ch, 24, PARITYBIT);
	getstr(originalParity, msg, 24, PARITYBIT);
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
	char type[MSGTYPEBIT+1];
	char sid[STATIONIDBIT+1];
	char zcount[ZCOUNTBIT+1];
	char sequence[SEQUENCENOBIT+1];
	char dataword[DATAWORDNOBIT+1];
	char *endptr;

	getstr(type,header_str,8,MSGTYPEBIT);
	head->message_type = strtol(type,&endptr,2);
	if ( head->message_type == 0 ) head->message_type = 64;
	getstr(sid,header_str,14,STATIONIDBIT);
	head->station_id = strtol(sid,&endptr,2);
	getstr(zcount,header_str,24,ZCOUNTBIT);
	head->modi_zcount = 0.6 * strtol(zcount,&endptr,2);
	getstr(sequence,header_str,37,SEQUENCENOBIT);
	head->sequence_no = strtol(sequence,&endptr,2);
	getstr(dataword,header_str,40,DATAWORDNOBIT);
	head->dataword_no = strtol(dataword,&endptr,2);
	getstr(head->station_health,header_str,45,STATIONHEALTHBIT);

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
	char scale;
	char udre[3];
	int  number_udre;
	char sid[6];
	char prc[17];
	char rrc[9];
	char iod[9];
	char *endptr;
	int i;
	unsigned long long int a;

	for (i=0;i<ns;i++){
		scale = body_str[0+SATELLITEBIT*i];
		getstr(udre,body_str,1+SATELLITEBIT*i,2);
		getstr(sid,body_str,3+SATELLITEBIT*i,5);
		getstr(prc,body_str,8+SATELLITEBIT*i,16);
		getstr(rrc,body_str,24+SATELLITEBIT*i,8);
		getstr(iod,body_str,32+SATELLITEBIT*i,8);
		
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
	char scale;
	char udre[3];
	int  number_udre;
	char sid[6];
	char dprc[17];
	char drrc[9];
	char iod[9];
	char *endptr;
	int i;
	unsigned long long int a;

	for (i=0;i<ns;i++) {
		scale = body_str[0+SATELLITEBIT*i];
		getstr(udre,body_str,1+SATELLITEBIT*i,2);
		getstr(sid,body_str,3+SATELLITEBIT*i,5);
		getstr(dprc,body_str,8+SATELLITEBIT*i,16);
		getstr(drrc,body_str,24+SATELLITEBIT*i,8);
		getstr(iod,body_str,32+SATELLITEBIT*i,8);
		
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
	char x[33];
	char y[33];
	char z[33];
	char *endptr;
	unsigned long long int a;

	getstr(x,body_str,0,32);
	getstr(y,body_str,32,32);
	getstr(z,body_str,64,32);
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
	char x[39];
	char y[39];
	char z[39];
	char ah[19];
	char *endptr;
	unsigned long long int a;

	getstr(x,body_str,0,38);
	getstr(y,body_str,40,38);
	getstr(z,body_str,80,38);
	a = strtol(x,&endptr,2);
	sc->x_coord = twoComplement(a,38) * 0.0001;
	a = strtol(y,&endptr,2);
	sc->y_coord = twoComplement(a,38) * 0.0001;
	a = strtol(z,&endptr,2);   
	sc->z_coord = twoComplement(a,38) * 0.0001; 
	sc->system_indicator = body_str[118];
	sc->AH_indicator = body_str[119];
	if ( sc->AH_indicator == '1' ) {
		getstr(ah,body_str,120,18);
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
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * TEpoch  *epochDGNSS             O  N/A  Structure to save the data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Return the status of the corrections
 *                                        -1 => Error reading file
 *                                         1 => Corrections read / End of file
 *                                         2 => RTCM version 2 detected succesfully
 *                                         3 => RTCM version 2 not detected
 *****************************************************************************/
int converterRTCM2 (FILE *fd, TRTCM2 *rtcm2, char *fileASCIIcorrections, char *fileASCIIantenna, TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options) {

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
		fflush(options->terminalStream);
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
					fflush(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
						fflush(options->terminalStream);
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
								getstr(rtcm2->preamble, rtcm2->correctedWord, 0, PREAMBLEBIT); 
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
				ret = writeRTCM2ascii(fout, fnew, rtcm2, epoch, epochDGNSS, options);
				if ( options->RTCMmode == ProcessRTCM2 && ret == bdrCORRECTIONSmsg1 ) out = 1;
				if ( ((unsigned int)rtcm2->i + LEFTLIMIT) > rtcm2->l ) rtcm2->my_state = EndOfString;
				else rtcm2->my_state = Initial;
				break;
			case EndOfString:
				if ( rtcm2->dataRead.indicator_end == 1 ) rtcm2->my_state = EndOfFile;
				else {
					getstr(rtcm2->leftwords_str, rtcm2->allwords_str, rtcm2->i, rtcm2->l - rtcm2->i);
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
			if(feof(fd)){
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
 *               windows and linux files.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *lineptr                  O  N/A  Buffer to write to
 * int  *n                         O  N/A  Length of buffer
 * FILE  *stream                   I  N/A  Input stream file
 * Returned value (int)            O  N/A  Return the number of characters read
 *                                         -1 on failure to read
 *****************************************************************************/
int getL (char *lineptr, int *n, FILE *stream) {
	int	rd;
	
	*n = 0;
	while ((rd=fgetc(stream))!=EOF) {
		if (rd==13 || rd=='\0' || rd=='\n') { // Character 13 is ^M (for Windows)
			if(rd=='\r') {
				lineptr[*n] = '\n';
				(*n)++;
				lineptr[*n]='\0';
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
	
	if (rd==13) fgetc(stream);
	if (rd==EOF && (*n)==0) return -1;
	else return (*n); 
}

/*****************************************************************************
 * Name        : getLNoComments
 * Description : Standard multipurpose input reader from files. Valid for
 *               windows and linux files. When a hash ('#') is found in the line,
 *               from this character from the end of line the data read will be
 *               ommited in the data buffwr
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *lineptr                  O  N/A  Buffer to write to
 * int  *n                         O  N/A  Length of buffer
 * FILE  *stream                   I  N/A  Input stream file
 * Returned value (int)            O  N/A  Return the number of characters read
 *                                         -1 on failure to read
 *****************************************************************************/
int getLNoComments (char *lineptr, int *n, FILE *stream) {
    int rd,HashFound=0;

    *n = 0;
    while ((rd=fgetc(stream))!=EOF) {
        if (rd==13 || rd=='\0' || rd=='\n') { // Character 13 is ^M (for Windows)
            if(rd=='\r') {
                lineptr[*n] = '\n';
                (*n)++;
                lineptr[*n]='\0';
            } else {
                lineptr[*n]=rd;
                if (rd!='\0') {
                    (*n)++;
                    lineptr[*n]='\0';
                }
            }
            break;
		} else if (HashFound==0) {
			if (rd=='#') {
				HashFound=1;
                lineptr[*n] = '\n';
                (*n)++;
                lineptr[*n]='\0';
			} else {
            	lineptr[*n] = rd;
	            (*n)++;
    	        if(*n>=MAX_INPUT_LINE-3) return -1; //Line too long, quit reading to avoid buffer overflow
			}
        }
    }

    if (rd==13) fgetc(stream);
    if (rd==EOF && (*n)==0) return -1;
    else return (*n);
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
		rd = fgetc(stream);
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
	FILE			*fd = NULL;
	char			line[MAX_INPUT_LINE];
	char			line2[MAX_INPUT_LINE];
	int				len = 0;
	int				res;
	char			aux[100];
	char			aux2[100];
	enum fileType	ft;

	ft = ftUNKNOWN;	// Default value

	fd = fopen(filename,"rb");
	
	if (fd==NULL) return ft;
	
	res = getL(line,&len,fd); 
	
	if (res!=-1) {
		getstr(aux,line,60,13);
		getstr(aux2,line,60,12);
		// RINEX check
		if (strcmp(aux,"RINEX VERSION")==0) {
			getstr(aux,line,20,11);
			if (strncmp(aux,"O",1)==0) ft = ftRINEXobservation;
			else if (strncmp(aux,"N",1)==0) ft = ftRINEXbroadcast;
			else if (strncmp(aux,"H",1)==0) ft = ftRINEXbroadcast; // Rinex v2 GEO nav data
			else if (strncmp(aux,"G",1)==0) ft = ftRINEXbroadcast; // Rinex v2 GLONASS nav data
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
		} else {
			strcpy(line2,line);	//This is to save the first line, it might be needed for checking EMS message
			res = getL(line,&len,fd); 
			if (res!=-1) {
				if (strstr(line,"Navstar GPS Constellation Status")!=NULL) ft = ftConstellation;
			}

			// SBAS EMS message
			if(strlen(line2)>85 && line2[0]!='#') ft = ftSBASEMSMESSAGE;
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
	char					line[MAX_INPUT_LINE];
	char					aux[100];
	char					*ca;
	char					**headerlines=NULL;
	int						numheaderlines=0;
	int						prevSysObs = 0, actSysObs = 1;
	int						len = 0;
	double					rinexVersion;
	int						properlyRead = 0;
	int						error = 0;
	int						readingHeader = 1;
	int						numLinesTypesofObsr = 0;
	int						obs,i,j,k;
	int						auxN;
	int						cleanedIndex=0;
	int						ErrorReadingEpochs;
	int						epochflag;
	enum MeasurementType	meas;
	long					posEndHeader;
	struct stat 			filestat;	//This is to get the file size
	off_t					filesize;
	struct tm   			tm;
	TTime					firstEpoch;
	TTime					secondEpoch;
	TTime					lastEpoch;
	double					seconds;
	double					interval;
	double					auxinterval;
	int						yy=-1,mm=-1,dd=-1,hour=-1,min=-1;
	static int				firstProgressCheck=1,firstProgressCheckDGNSS=1;

	while (getL(line,&len,fd)!=-1 && readingHeader) {
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
		if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
			getstr(aux,line,0,9);
			rinexVersion = atof(aux);
			if ((int)(rinexVersion)==2) epoch->source = RINEX2;
			else if ((int)(rinexVersion)==3) epoch->source = RINEX3;
			else {
				epoch->source = UNKNOWN_SOURCE;
				sprintf(aux,"Rinex observation file version %1.2f not supported. Supported versions are 2 and 3",rinexVersion);
				printError(aux,options);
			}
		} else if (strncmp(&line[60],"MARKER NAME",11)==0) {
			getstr(aux,line,0,60);
			//Do not copy empty marker name
			if (aux[0]!='\0') {
				strcpy(epoch->receiver.name,aux);
			}
		} else if (strncmp(&line[60],"ANT # / TYPE",12)==0) {
			getstr(aux,line,20,20);
			strcpy(epoch->receiver.antenna.type,aux);
			// Separate the anntena.type into antenna and radome
			strcpy(epoch->receiver.antenna.type_ant,epoch->receiver.antenna.type);
			ca = strstr(epoch->receiver.antenna.type_ant," ");
			if (ca != NULL) {
				*ca = '\0';
				strcpy(epoch->receiver.antenna.type_radome,&ca[1]);
				trim(epoch->receiver.antenna.type_radome);
			}
		} else if (strncmp(&line[60],"REC # / TYPE / VERS",19)==0) {
			getstr(aux,line,20,20);
			strcpy(epoch->receiver.type,aux);
		} else if (strncmp(&line[60],"ANTENNA: DELTA H/E/N",20)==0) {
			if (options->ARPData == arpRINEX) {
				getstr(aux,line,0,14);
				epoch->receiver.ARP[2] = atof(aux);
				getstr(aux,line,14,14);
				epoch->receiver.ARP[1] = atof(aux);
				getstr(aux,line,28,14);
				epoch->receiver.ARP[0] = atof(aux);
			}

		} else if (strncmp(&line[60],"TIME OF FIRST OBS",17)==0) {
			getstr(aux,line,22,2);
			epoch->initialhour=atoi(aux);
		} else if (strncmp(&line[60],"# / TYPES OF OBSERV",19)==0) {  // Only for RINEX v2.11
			//      5    L1    L2    P1    P2    C1                        # / TYPES OF OBSERV
			numLinesTypesofObsr++;
			getstr(aux,line,0,6);
			if (numLinesTypesofObsr==1) { // if this is the first line of observations
				auxN = atoi(aux);
				epoch->measOrder[GPS].nDiffMeasurements = auxN;
				epoch->measOrder[GPS].GNSS = GPS;
				epoch->measOrder[Galileo].nDiffMeasurements = auxN;
				epoch->measOrder[Galileo].GNSS = Galileo;
				epoch->measOrder[GEO].nDiffMeasurements = auxN;
				epoch->measOrder[GEO].GNSS = GEO;
				epoch->measOrder[GLONASS].nDiffMeasurements = auxN;
				epoch->measOrder[GLONASS].GNSS = GLONASS;
				epoch->numGNSS = 4;
				obs = 0;
			} 

			//Initialize meas2Ind factor, so previous index are not maintained when reading concatenated files
			if(cleanedIndex==0) {
				cleanedIndex=1;
				for (j=0;j<MAX_GNSS;j++) {
					for (i=0;i<MAX_MEASUREMENTS;i++) {
						epoch->measOrder[j].meas2Ind[i] = -1;
						epoch->measOrder[j].conversionFactor[i] = 0;
						epoch->measOrder[j].usable[i] = 1;
					}
				}
			}

			obs = 0;
			for (i=0,j=0;i<auxN;i++,j++) {
				getstr(aux,line,10+j*6,2);
				meas = measstr2meastype(aux);
				if (meas != NA) {
					// Carrier-phase are stored in cycles instead of metres, as
					// they are on RINEX files.
					//    aux[0]=='L'   => Measurement is carrier phase
					for (k=0;k<epoch->numGNSS;k++) {
						if (aux[0]=='L') {
							if (epoch->measOrder[k].GNSS==GPS) {
								if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = GPSl1;
								else if (aux[1]=='2') epoch->measOrder[k].conversionFactor[meas] = GPSl2;
								else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = GPSl5;
								else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
							} else if (epoch->measOrder[k].GNSS==Galileo) {
								if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = GALl1;
								else if (aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = GALl5a;
								else if (aux[1]=='7') epoch->measOrder[k].conversionFactor[meas] = GALl5b;
								else if (aux[1]=='8') epoch->measOrder[k].conversionFactor[meas] = GALl5;
								else if (aux[1]=='6') epoch->measOrder[k].conversionFactor[meas] = GALl6;
								else epoch->measOrder[k].conversionFactor[meas] = 1.0;
							} else if (epoch->measOrder[k].GNSS==GEO) {
								if (aux[1]=='1') epoch->measOrder[k].conversionFactor[meas] = SBASl1;
								else if(aux[1]=='5') epoch->measOrder[k].conversionFactor[meas] = SBASl5;
								else epoch->measOrder[k].conversionFactor[meas] = 1.0; //For the case of frequencies that are not in this constellation
							} else if (epoch->measOrder[k].GNSS==GLONASS) {
								//Conversion factor not implented for GLONASS
								epoch->measOrder[k].conversionFactor[meas] = 1.0; 
							}
						} else { // If measurement is not carrier-phase, conversionFactor is 1
							epoch->measOrder[k].conversionFactor[meas] = 1.0;
						}
						// Update dictionaries (if usableFreq is disabled for a specific frequency, the dictionary meas2Ind is avoided)
						if (options->usableFreq[k][getFrequencyInt(meas)]) {
							epoch->measOrder[k].usable[meas] = 1;
						} else {
							epoch->measOrder[k].usable[meas] = 0;
						}
						epoch->measOrder[k].meas2Ind[meas] = obs;
						epoch->measOrder[k].ind2Meas[obs] = meas;
					}
				} else {
					sprintf(messagestr,"Reading RINEX %4.2f file: Unrecognized measurement type: '%s'",rinexVersion,aux);
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
			prevSysObs = actSysObs;
			actSysObs = gnsschar2gnsstype(line[0]); 
			getstr(aux,line,1,5);
			if ( actSysObs==BDS || actSysObs==QZSS || actSysObs==IRNSS || ((prevSysObs==BDS || prevSysObs==QZSS || prevSysObs==IRNSS ) && aux[0]=='\0') ) {continue;} //BeiDou, QZSS, IRNSS are not supported
			//numLinesTypesofObsr++;
			//if (aux[0]!='\0') { // if this is the first line of a SYS
			//if (numLinesTypesofObsr==1 || actSysObs!=prevSysObs) { // if this is the first line of a SYS
			//if (numLinesTypesofObsr==1  ) { // if this is the first line of a SYS
				//epoch->measOrder[epoch->numGNSS].nDiffMeasurements = atoi(aux);
				//epoch->measOrder[actSysObs].nDiffMeasurements = atoi(aux);
				//epoch->measOrder[epoch->numGNSS].GNSS = gnsschar2gnsstype(line[0]);
				//epoch->measOrder[epoch->numGNSS].GNSS = actSysObs;
				//epoch->measOrder[actSysObs].GNSS = actSysObs;
				//epoch->numGNSS++;
				//obs = 0;
			//}}}
			epoch->measOrder[actSysObs].nDiffMeasurements = atoi(aux);
			epoch->measOrder[actSysObs].GNSS = actSysObs;
			//epoch->numGNSS++;
			obs = 0;

		
			//Initialize meas2Ind factor, so previous index are not maintained when reading concatenated files
			if(cleanedIndex==0) {
				cleanedIndex=1;
				for (j=0;j<MAX_GNSS;j++) {
					for (i=0;i<MAX_MEASUREMENTS;i++) {
						epoch->measOrder[j].meas2Ind[i] = -1;
						epoch->measOrder[j].conversionFactor[i] = 0;
						epoch->measOrder[j].usable[i] = 1;
					}
				}
			}

			for (i=0,j=0;i<epoch->measOrder[actSysObs].nDiffMeasurements;j++,i++) {
				getstr(aux,line,7+4*j,3);
				meas = measstr2meastype(aux);
				if (meas != NA) {
					// Carrier-phase are stored in cycles instead of metres, as
					// they are on RINEX files.
					//    aux[0]=='L'   => Measurement is carrier phase
					if (aux[0]=='L') {
						if (epoch->measOrder[actSysObs].GNSS==GPS) {
							if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl1;
							else if (aux[1]=='2') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl2;
							else if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = GPSl5;
							else epoch->measOrder[k].conversionFactor[meas] = 1.0;
						} else if (epoch->measOrder[actSysObs].GNSS==Galileo) {
							if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl1;
							else if (aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5a;
							else if (aux[1]=='7') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5b;
							else if (aux[1]=='8') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl5;
							else if (aux[1]=='6') epoch->measOrder[actSysObs].conversionFactor[meas] = GALl6;
							else epoch->measOrder[k].conversionFactor[meas] = 1.0;
						} else if (epoch->measOrder[actSysObs].GNSS==GEO) {
							if (aux[1]=='1') epoch->measOrder[actSysObs].conversionFactor[meas] = SBASl1;
							else if(aux[1]=='5') epoch->measOrder[actSysObs].conversionFactor[meas] = SBASl5;
							else epoch->measOrder[k].conversionFactor[meas] = 1.0;
						} else {
							//Other constellations (GLONASS, BeiDou).
							//To be done. Now we apply conversion factor of 1
							epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
						}
					} else { // If measurement in not carrier-phase, conversionFactor is 1
						epoch->measOrder[actSysObs].conversionFactor[meas] = 1.0;
					}
					// Update dictionaries (if usableFreq is disabled for a specific frequency, the dictionary meas2Ind is avoided)
					if (options->usableFreq[actSysObs][getFrequencyInt(meas)]) {
					//if (epoch->measOrder[actSysObs].usableFreq[getFrequencyInt(epoch->measOrder[actSysObs].GNSS,meas)]) {
						epoch->measOrder[actSysObs].meas2Ind[meas] = obs;
					}
					epoch->measOrder[actSysObs].ind2Meas[obs] = meas;
				} else {
					sprintf(messagestr,"Reading RINEX %4.2f file: Unrecognized measurement type: '%s'",rinexVersion,aux);
					printError(messagestr,options);
					error = 1;
				}				
				obs++;
				if ((j+1)%13==0 && epoch->measOrder[actSysObs].nDiffMeasurements>(j+1)) { // Following observables are in the next lines (max 13 per line)
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
			getstr(aux,line,0,10);
			trim(aux);
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
				getstr(aux,line,1,14);
				epoch->receiver.aproxPosition[0] = atof(aux);
				getstr(aux,line,14,14);
				epoch->receiver.aproxPosition[1] = atof(aux);
				getstr(aux,line,28,14);
				epoch->receiver.aproxPosition[2] = atof(aux);
				if (options->receiverPositionSource==rpRINEX) {
					epoch->receiver.aproxPositionError = 1e4; // 10 Km
				} else {
					epoch->receiver.aproxPositionError = 1e6;
				}
				epoch->numAproxPosRead++;
			} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
				getstr(aux,line,1,14);
				epoch->receiver.aproxPosition[0] = atof(aux);
				getstr(aux,line,14,14);
				epoch->receiver.aproxPosition[1] = atof(aux);
				getstr(aux,line,28,14);
				epoch->receiver.aproxPosition[2] = atof(aux);
				epoch->receiver.aproxPositionError = 0.1; // 10 cm
				epoch->numAproxPosRead++;
			}
			if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
				getstr(aux,line,1,14);
				epoch->receiver.aproxPositionRover[0] = atof(aux);
				getstr(aux,line,14,14);
				epoch->receiver.aproxPositionRover[1] = atof(aux);
				getstr(aux,line,28,14);
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
	}
	
	//Write header lines for RINEX observation file with user added error
	if (fdout!=NULL && epoch->DGNSSstruct==0) {
		writeRinexObsHeaderUserAddedError(fdout,headerlines,numheaderlines);
		for(i=0;i<numheaderlines;i++) {
			free(headerlines[i]);
		}
		free(headerlines);
	}

	//Check for non quantizied SNR measurements
	if (options->solutionMode==PPPMode) {
		//Get SNR for both frequencies
		i=epoch->measOrder[GPS].meas2Ind[S1P];
		if (i==-1) {
			i=epoch->measOrder[GPS].meas2Ind[S1C];
		}
		if (i==-1) {
			i=epoch->measOrder[GPS].meas2Ind[S1W];
		}
		j=epoch->measOrder[GPS].meas2Ind[S2P];
		if (j==-1) {
			j=epoch->measOrder[GPS].meas2Ind[S2C];
		} 
		if (j==-1) {
			j=epoch->measOrder[GPS].meas2Ind[S2W];
		}
		if (i!=-1 && j!=-1) {
			//GPS has non quantizied SNR measurements for both frequencies. Save positions
			epoch->measOrder[GPS].hasSNRmeas=1;
			epoch->measOrder[GPS].SNRmeaspos[1]=i;
			epoch->measOrder[GPS].SNRmeaspos[2]=j;
		}
	} else {
		//Get SNR for frequencies one
		i=epoch->measOrder[GPS].meas2Ind[S1C];
		if (i==-1) {
			i=epoch->measOrder[GPS].meas2Ind[S1P];
		}
		if (i==-1) {
			i=epoch->measOrder[GPS].meas2Ind[S1W];
		}
		if (i!=-1) {
			//GPS has non quantizied SNR measurements for both frequencies. Save positions
			epoch->measOrder[GPS].hasSNRmeas=1;
			epoch->measOrder[GPS].SNRmeaspos[1]=i;
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
							//Maybe some observation files have a data gap for all satellite in second, but that is extemely rare
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
							getstr(aux,line,0,4);
							yy = tm.tm_year = atoi(aux);
							if (tm.tm_year <= 70) tm.tm_year += 100;
							getstr(aux,line,3,4);
							mm = atoi(aux);
							tm.tm_mon  = mm - 1;
							getstr(aux,line,6,4);
							dd = tm.tm_mday = atoi(aux);
							getstr(aux,line,9,4);
							if(aux[1]=='.'||aux[2]=='.') {
								hour= tm.tm_hour = -1;
							} else {
								hour = tm.tm_hour = atoi(aux);
							}
							getstr(aux,line,12,4);
							min = tm.tm_min  = atoi(aux);
							getstr(aux,line,16,10);
							tm.tm_sec  = atoi(aux);
							seconds = atof(aux);
						} else {
							//RINEX v3
							if (line[0]=='>' && len<60) {
								//Line with valid epoch
								getstr(aux,line,2,4);
								yy =  atoi(aux);
								if (yy>=2000) yy-=2000;
								else yy-=1900;
								tm.tm_year = atoi(aux)-1900;
								getstr(aux,line,7,2);
								mm = atoi(aux);
								tm.tm_mon = mm-1;
								getstr(aux,line,10,2);
								dd = tm.tm_mday = atoi(aux);
								getstr(aux,line,13,2);
								hour = tm.tm_hour = atoi(aux);
								getstr(aux,line,16,2);
								min = tm.tm_min  = atoi(aux);
								getstr(aux,line,19,10);
								tm.tm_sec  = atoi(aux);
								seconds = atof(aux);
							} else {
								hour=-1;
							}
						}
						if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && min>=0 &&min<=59) {
							//Epoch timestamp found
							break;
                        } else if (i==2 && epoch->source == RINEX3) {
                            //Check if last epoch is an event epoch without date
                            getstr(aux,line,30,2);
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
					} else if (i==1) {
						secondEpoch.MJDN = MJDN(&tm);
						secondEpoch.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
						interval=tdiff(&secondEpoch,&firstEpoch);
						if (interval<1E-4) {
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
								epoch->numEpochsfile=tdiff(&lastEpoch,&firstEpoch)/interval;
							} else {
								//Last epoch of file is after user last epoch. Use user last epoch to compute number of epochs
								epoch->numEpochsfile=tdiff(&options->EndEpoch,&firstEpoch)/interval;
							}
						} else {
							epoch->numEpochsfile=tdiff(&lastEpoch,&firstEpoch)/interval;
						}
					}
				}
				//Set the file position back to the first epoch
				fseek(fd,posEndHeader,SEEK_SET);
				//If backward filtering is enabled, double the number of epochs in file
				if (options->filterIterations==2) {
					epoch->numEpochsfile*=2;
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
						getstr(aux,line,0,4);
						yy = tm.tm_year = atoi(aux);
						if (tm.tm_year <= 70) tm.tm_year += 100;
						getstr(aux,line,3,4);
						mm = atoi(aux);
						tm.tm_mon  = mm - 1;
						getstr(aux,line,6,4);
						dd = tm.tm_mday = atoi(aux);
						getstr(aux,line,9,4);
						if(aux[1]=='.'||aux[2]=='.') {
							hour= tm.tm_hour = -1;
						} else {
							hour = tm.tm_hour = atoi(aux);
						}
						getstr(aux,line,12,4);
						min = tm.tm_min  = atoi(aux);
						getstr(aux,line,16,10);
						tm.tm_sec  = atoi(aux);
						seconds = atof(aux);
					} else {
						//RINEX v3
						if (line[0]=='>' && len<60) {
							//Line with valid epoch
							getstr(aux,line,2,4);
							yy =  atoi(aux);
							if (yy>=2000) yy-=2000;
							else yy-=1900;
							tm.tm_year = atoi(aux)-1900;
							getstr(aux,line,7,2);
							mm = atoi(aux);
							tm.tm_mon = mm-1;
							getstr(aux,line,10,2);
							dd = tm.tm_mday = atoi(aux);
							getstr(aux,line,13,2);
							hour = tm.tm_hour = atoi(aux);
							getstr(aux,line,16,2);
							min = tm.tm_min  = atoi(aux);
							getstr(aux,line,19,10);
							tm.tm_sec  = atoi(aux);
							seconds = atof(aux);
						} else {
							hour=-1;
						}
					}
					if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && min>=0 &&min<=59) {
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
					if (interval<1E-4) {
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
 * TConstellation  *constellation  I  N/A  TConstellation structure
 * enum ProcessingDirection        I  N/A  Direction of the read
 *                                         pFORWARD  => Forward
 *                                         pBACKWARD => Backward
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error or EOF (no more epochs)
 *****************************************************************************/
int readRinexObsEpoch (FILE *fd, TEpoch *epoch, TConstellation *constellation, enum ProcessingDirection direction, char *Epochstr, TOptions *options) {
	char		line[MAX_INPUT_LINE];
	char		aux[100];
	char		cons;
	int			len = 0;
	int			properlyRead = 0;
	int			error = 0;
	int			i, j, k;
	int			n;
	int			notSupportedSatellites = 0;
	int			numEpochsMissing;
	struct tm	tm;
	double		seconds;
	double		value;
	int			nextRead;
	int			ret;

	// For converting from SNR flag in RINEX to dBHz. 60 means don't care (0 in RINEX) or very high (9 in RINEX)
	// There is no fixed value for very high SNR (9 in RINEX). A value is 60 is set in order to give a higher enough
	// value when computing the satellite weight using the SNR
	static int	SNRtable[10] = { 60, 11, 17, 23, 29, 35, 41, 47, 53, 60 };

	static int	twoepochs=1;	//Variable to read only the first two epochs to compute data rate file
	static int	lastCSindex[2]={0,0};	//Variable holding the first free index of all satellites viewed

	// Rewind for backward processing
	if ( direction == pBACKWARD ) {
		ret = rewindEpochRinexObs(fd,epoch->source);
		if ( ret == 0 ) return 0;
		ret = rewindEpochRinexObs(fd,epoch->source);
		if ( ret == 0 ) return 0;
	}

	//Remove index values from previous epoch
	for (i=0;i<epoch->numSatellites;i++) {
		epoch->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=-1;
	}

	
	if (getL(line,&len,fd)!=-1) {
		properlyRead = 1;
		// Block to detect new RINEX header, it only affects when large RINEX are used
		if (getLback(line,&len,fd)!=-1) {
			getL(line,&len,fd);
			getstr(aux,line,60,80);
			if (strncmp(aux,"RINEX VERSION / TYPE",20)==0) {
				getLback(line,&len,fd);
				return 2;
			}
		}
		if (epoch->source == RINEX2) {
			// RINEX 2.11				
			getstr(aux,line,27,2);
			epoch->flag = atoi(aux);
			
			if (epoch->flag>1) { // Unusable epoch
				if ( direction == pBACKWARD ) {
					//Save previous epoch
					memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));
					//When going backwards, skip epoch events and look for previous epoch in RINEX observation file
					//If next valid epoch was read, it would make an infinite loop as we want back one epoch, but read two,
					//and the next time we enter this function, we would go back two epochs, which results in always reading 
					//the same epoch
					ret = rewindEpochRinexObs(fd,epoch->source);
					if ( ret == 0 ) return 0;
				} else {
					getstr(aux,line,1,2);
					tm.tm_year = atoi(aux);
					if (tm.tm_year <= 70) tm.tm_year += 100;
					getstr(aux,line,4,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,line,7,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,line,10,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,line,13,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,line,16,10);
					tm.tm_sec  = atoi(aux);
					seconds = atof(aux);
					getstr(aux,line,30,2);
					n = atoi(aux);
					for (i=0;i<=n;i++) {
						if (getL(line,&len,fd)==-1) {
							return 0;
						}
						if (strncmp(&line[60],"APPROX POSITION XYZ",19)==0) {
							if (options->receiverPositionSource==rpRINEX || ( ( (options->receiverPositionSource == rpCALCULATERINEX) || (options->receiverPositionSource == rpCALCULATERINEXREF)  ) && epoch->numAproxPosRead==0)) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPosition[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPosition[1] = atof(aux);
								getstr(aux,line,28,14);
								epoch->receiver.aproxPosition[2] = atof(aux);
								epoch->receiver.aproxPositionError = 1e4; // 10 Km
								epoch->numAproxPosRead++;
							} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPosition[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPosition[1] = atof(aux);
								getstr(aux,line,28,14);
								epoch->receiver.aproxPosition[2] = atof(aux);
								epoch->receiver.aproxPositionError = 0.1; // 10 cm
								epoch->numAproxPosRead++;
							} 
							if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPositionRover[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPositionRover[1] = atof(aux);
								getstr(aux,line,28,14);
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
			}
			
			//Save previous epoch
			memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));

			getstr(aux,line,1,2);
			tm.tm_year = atoi(aux);
			if (tm.tm_year <= 70) tm.tm_year += 100;
			getstr(aux,line,4,2);
			tm.tm_mon  = atoi(aux)-1;
			getstr(aux,line,7,2);
			tm.tm_mday = atoi(aux);
			getstr(aux,line,10,2);
			tm.tm_hour = atoi(aux);
			getstr(aux,line,13,2);
			tm.tm_min  = atoi(aux);
			getstr(aux,line,16,10);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
			epoch->t.MJDN = MJDN(&tm);
			epoch->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;

			//Look for data gaps
			numEpochsMissing=abs((int)(tdiff(&epoch->t,&epoch->PreviousEpoch)/epoch->receiver.interval))-1;
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
								sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
								epoch->NewPercentage=1;
							}
						}
					} else {
						epoch->numEpochsprocessed++;
						epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
						if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
							sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
							epoch->NewPercentage=1;
						}
					}
				}
			}


			if (twoepochs) {
				if(epoch->firstepoch.SoD==-1.) {
					memcpy(&epoch->firstepoch,&epoch->t,sizeof(TTime));
				} else {
					if (tdiff(&epoch->t,&epoch->firstepoch)>1E-4) {
						//This is for the case we read the first epoch two times.
						//This occurs if we need to read the first epoch in order to look for Glonass k factors in the navigation file
						twoepochs=0;
						memcpy(&epoch->secondepoch,&epoch->t,sizeof(TTime));
					}
				}
			}
				
			getstr(aux,line,30,2);
			epoch->numSatellites = atoi(aux);
			for (i=0,j=0;i<epoch->numSatellites;i++,j++) { // Get satellite PRNs
				if ((i%12)==0 && i!=0) {
					if (getL(line,&len,fd)==-1) error = 1; // The next satellites are in the following line
					j = 0;
				}
				cons = line[32+3*j];
				getstr(aux,line,33+3*j,2);
				epoch->sat[i].PRN = atoi(aux);
				if (cons=='G' || cons==' ')
					epoch->sat[i].GNSS = GPS;
				else if (cons=='S')
					epoch->sat[i].GNSS = GEO;
				else if (cons=='R')
					epoch->sat[i].GNSS = GLONASS;
				else if (cons=='E')
					epoch->sat[i].GNSS = Galileo;
			}
			for (i=0;i<epoch->numSatellites;i++) { // Get satellite measurements
				if (getL(line,&len,fd)==-1) error = 1;
				nextRead = 0;
				for (j=0,k=0;j<epoch->measOrder[epoch->sat[i].GNSS].nDiffMeasurements;j++,k++) {
					if (nextRead) {
						if (getL(line,&len,fd)==-1) error = 1;
						nextRead = 0;
					}
					getstr(aux,line,16*k,14);
					value = atof(aux);
					if (value==0) value = -1;
					epoch->sat[i].meas[j].value = value;
					epoch->sat[i].meas[j].rawvalue = value;
					getstr(aux,line,14+16*k,1);
					epoch->sat[i].meas[j].LLI = atoi(aux);
					getstr(aux,line,15+16*k,1);
					if (line[15+16*k]==' ') {
						epoch->sat[i].meas[j].hasSNRflag=0;
					} else {
						epoch->sat[i].meas[j].hasSNRflag=1;
					}
					epoch->sat[i].meas[j].SNR = atoi(aux);
					epoch->sat[i].meas[j].SNRdBHz = SNRtable[epoch->sat[i].meas[j].SNR];
					epoch->sat[i].meas[j].dataFlag = 0;
					if ((k+1)%5==0) { // Following observables are in the next lines (max 5 per line)
						nextRead = 1;
						k=-1; // k will be increased in the for loop
					}
				}
				if (epoch->sat[i].GNSS==GPS) epoch->lastSBASindex=i; //When gLAB is multiconstellation and SBAS monitors also other constellations, this has to include other constellations
				epoch->satIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=i;

				if (epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]==-1) {
					epoch->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN]=lastCSindex[epoch->DGNSSstruct];
					lastCSindex[epoch->DGNSSstruct]++;
				}
			}
		} else if (epoch->source==RINEX3) {
			// RINEX 3.00
			getstr(aux,line,30,2);
			epoch->flag = atoi(aux);
			
			if (epoch->flag>1) { // Unusable epoch
				if ( direction == pBACKWARD ) {
					//Save previous epoch
					memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));
					//When going backwards, skip epoch events and look for previous epoch in RINEX observation file
					//If next valid epoch was read, it would make an infinite loop as we want back one epoch, but read two,
					//and the next time we enter this function, we would go back two epochs, which results in always reading 
					//the same epoch
					ret = rewindEpochRinexObs(fd,epoch->source);
					if ( ret == 0 ) return 0;
				} else {
					getstr(aux,line,2,4);
					tm.tm_year = atoi(aux)-1900;
					getstr(aux,line,7,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,line,10,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,line,13,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,line,16,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,line,19,10);
					tm.tm_sec  = atoi(aux);
					seconds = atof(aux);

					getstr(aux,line,33,2);
					n = atoi(aux);
					for (i=0;i<=n;i++) {
						if (getL(line,&len,fd)==-1) {
							return 0;
						}
						if (strncmp(&line[60],"APPROX POSITION XYZ",19)==0) {
							if (options->receiverPositionSource==rpRINEX || ( ( (options->receiverPositionSource == rpCALCULATERINEX) || (options->receiverPositionSource == rpCALCULATERINEXREF)  ) && epoch->numAproxPosRead==0)) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPosition[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPosition[1] = atof(aux);
								getstr(aux,line,28,14);
								epoch->receiver.aproxPosition[2] = atof(aux);
								epoch->receiver.aproxPositionError = 1e4; // 10 Km
								epoch->numAproxPosRead++;
							} else if ( options->receiverPositionSource >= rpRTCMbaseline && options->receiverPositionSource <= rpRTCMRoverUSERREF  ) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPosition[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPosition[1] = atof(aux);
								getstr(aux,line,28,14);
								epoch->receiver.aproxPosition[2] = atof(aux);
								epoch->receiver.aproxPositionError = 0.1; // 10 cm
								epoch->numAproxPosRead++;
							}
							if ( ( options->receiverPositionSource == rpRTCMRINEXROVER || options->receiverPositionSource == rpRTCMUserRINEXROVER ) && epoch->DGNSSstruct==0 ) {
								getstr(aux,line,1,14);
								epoch->receiver.aproxPositionRover[0] = atof(aux);
								getstr(aux,line,14,14);
								epoch->receiver.aproxPositionRover[1] = atof(aux);
								getstr(aux,line,28,14);
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
			}
			
			// Save previous epoch
			memcpy(&epoch->PreviousEpoch,&epoch->t,sizeof(TTime));

			getstr(aux,line,2,4);
			tm.tm_year = atoi(aux)-1900;
			getstr(aux,line,7,2);
			tm.tm_mon  = atoi(aux)-1;
			getstr(aux,line,10,2);
			tm.tm_mday = atoi(aux);
			getstr(aux,line,13,2);
			tm.tm_hour = atoi(aux);
			getstr(aux,line,16,2);
			tm.tm_min  = atoi(aux);
			getstr(aux,line,19,10);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
			epoch->t.MJDN = MJDN(&tm);
			epoch->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			
			if (printProgress==1) {
				//Only save current epoch if it we are reading Rover file, not reference file
				if (epoch->DGNSSstruct==0) {
					if (options->StartEpoch.MJDN!=-1) {
						if(tdiff(&epoch->t,&options->StartEpoch)>=0.) {
							epoch->numEpochsprocessed++;
							epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
							if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
								sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
								epoch->NewPercentage=1;
							}
						}
					} else {
						epoch->numEpochsprocessed++;
						epoch->CurrentPercentage=100*epoch->numEpochsprocessed/epoch->numEpochsfile;
						if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
							sprintf(Epochstr,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        ",t2doystr(&epoch->t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,epoch->CurrentPercentage);
							epoch->NewPercentage=1;
						}
					}
				}
			}

			if (twoepochs) {
				if(epoch->firstepoch.SoD==-1.) {
					memcpy(&epoch->firstepoch,&epoch->t,sizeof(TTime));
				} else {
					twoepochs=0;
					memcpy(&epoch->secondepoch,&epoch->t,sizeof(TTime));
				}
			}
				
			getstr(aux,line,33,2);
			epoch->numSatellites = atoi(aux);
			for (i=0;i<epoch->numSatellites;i++) { // Get satellite measurements and PRNs
				if (getL(line,&len,fd)==-1) error = 1;
				epoch->sat[i-notSupportedSatellites].GNSS = gnsschar2gnsstype(line[0]);
				if ( epoch->sat[i-notSupportedSatellites].GNSS==BDS || epoch->sat[i-notSupportedSatellites].GNSS==QZSS || epoch->sat[i-notSupportedSatellites].GNSS==IRNSS ) { //BeiDou, QZSS, IRNSS are not supported
					notSupportedSatellites++;
					continue; 
				}	
				getstr(aux,line,1,2);
				epoch->sat[i-notSupportedSatellites].PRN = atoi(aux);
				for (j=0;j<epoch->measOrder[epoch->sat[i-notSupportedSatellites].GNSS].nDiffMeasurements;j++) {
					getstr(aux,line,3+16*j,14);
					value = atof(aux);
					if (value==0) value = -1;
					epoch->sat[i-notSupportedSatellites].meas[j].value = value;
					epoch->sat[i-notSupportedSatellites].meas[j].rawvalue = value;
					getstr(aux,line,17+16*j,1);
					epoch->sat[i-notSupportedSatellites].meas[j].LLI = atoi(aux);
					getstr(aux,line,18+16*j,1);
					if (line[18+16*j]==' ') {
						epoch->sat[i-notSupportedSatellites].meas[j].hasSNRflag=0;
					} else {
						epoch->sat[i-notSupportedSatellites].meas[j].hasSNRflag=1;
					}
					epoch->sat[i-notSupportedSatellites].meas[j].SNR = atoi(aux);
					epoch->sat[i-notSupportedSatellites].meas[j].SNRdBHz = SNRtable[epoch->sat[i-notSupportedSatellites].meas[j].SNR];
					epoch->sat[i-notSupportedSatellites].meas[j].dataFlag = 0;
				}
				if(epoch->sat[i-notSupportedSatellites].GNSS==GPS) epoch->lastSBASindex=i-notSupportedSatellites; //When gLAB is multiconstellation and SBAS monitors also other constellations, this has to include other constellations
				epoch->satIndex[epoch->sat[i-notSupportedSatellites].GNSS][epoch->sat[i-notSupportedSatellites].PRN]=i-notSupportedSatellites;

				if (epoch->satCSIndex[epoch->sat[i-notSupportedSatellites].GNSS][epoch->sat[i-notSupportedSatellites].PRN]==-1) {
					epoch->satCSIndex[epoch->sat[i-notSupportedSatellites].GNSS][epoch->sat[i-notSupportedSatellites].PRN]=lastCSindex[epoch->DGNSSstruct];
					lastCSindex[epoch->DGNSSstruct]++;
				}
			}
			epoch->numSatellites-=notSupportedSatellites;
		} // (epoch->source==RINEX3)

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
	int			yy=-1,mm=-1,dd=-1,hour=-1,min=-1;
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
				getstr(aux,line,0,4);
				yy = atoi(aux);
				getstr(aux,line,3,4);
				mm = atoi(aux);
				getstr(aux,line,6,4);
				dd = atoi(aux);
				getstr(aux,line,9,4);
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
				getstr(aux,line,12,4);
				min = atoi(aux);
				if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && min>=0 &&min<=59) {
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
	int			ret;
	int			yy=-1,mm=-1,dd=-1,hour=-1,min=-1;
	int 		len = 0;
	char 		line[MAX_INPUT_LINE];
	char    	aux[100];
	double		seconds;
	struct tm   tm;

	ret = getL(line,&len,fd);

	if (ret==-1) {
		getLback(line,&len,fd);
		return 0;
	} else if (src == RINEX2) {
		getstr(aux,line,0,4);
		yy = tm.tm_year = atoi(aux);
		if (tm.tm_year <= 70) tm.tm_year += 100;
		getstr(aux,line,3,4);
		mm = atoi(aux);
		tm.tm_mon  = mm - 1;
		getstr(aux,line,6,4);
		dd = tm.tm_mday = atoi(aux);
		getstr(aux,line,9,4);
		if(aux[1]=='.'||aux[2]=='.') {
			hour= tm.tm_hour = -1;
		} else {
			hour = tm.tm_hour = atoi(aux);
		}
		getstr(aux,line,12,4);
		min = tm.tm_min  = atoi(aux);
		getstr(aux,line,16,10);
		tm.tm_sec  = atoi(aux);
		seconds = atof(aux);
	} else {
		//RINEX v3
		if (line[0]=='>' && len<60) {
			//Line with valid epoch
			getstr(aux,line,2,4);
			yy =  atoi(aux);
			if (yy>=2000) yy-=2000;
			else yy-=1900;
			tm.tm_year = atoi(aux)-1900;
			getstr(aux,line,7,2);
			mm = atoi(aux);
			tm.tm_mon = mm-1;
			getstr(aux,line,10,2);
			dd = tm.tm_mday = atoi(aux);
			getstr(aux,line,13,2);
			hour = tm.tm_hour = atoi(aux);
			getstr(aux,line,16,2);
			min = tm.tm_min  = atoi(aux);
			getstr(aux,line,19,10);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
		} else {
			hour=-1;
		}
	}
	if (yy>=0 && yy<=99 && mm>=1 && mm<=12 && dd>=1 && dd<=31 && hour>=0 && hour<=23 && min>=0 &&min<=59) {
		//Epoch timestamp found
		t->MJDN = MJDN(&tm);
		t->SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
		getLback(line,&len,fd);
		return 1;
	}
	getLback(line,&len,fd);
	return 0;
}

/*****************************************************************************
 * Name        : readRinexNav
 * Description : Read a RINEX navigation file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TGNSSproducts  *products        O  N/A  Structure to save the data
 * double *rinexNavVersion         O  N/A  Rinex Navigation version number
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error
 *****************************************************************************/
int readRinexNav (FILE *fd, TGNSSproducts *products, double *rinexNavVersion) {
	char						line[MAX_INPUT_LINE];
	char						aux[100], a0[100], a1[100], a2[100], a3[100];
	char						ConstellationType[2];
	int 						len = 0;
	int							properlyRead = 0;
	int							readingHeader = 1;
	int							i,j;
	unsigned int				k;  //to avoid warning: comparison between signed and unsigned integer expressions
	TBRDCblock					block;
	struct tm					tm;
	double						seconds;
	int							row;
	int							indSat, indBlock;
	enum TimeSystemCorrection	timecorr;	
	enum GNSSystem				satSystem;
	int							GPSweek;
	double						SoW;
	int							DoW;	//Day of Week

	products->type = BRDC;
	// If to avoid overwritten products structure when RINEX navigation are concatennated
	if ( products->BRDC == NULL ) {
		products->BRDC = malloc(sizeof(TBRDCproducts));
		initBRDCproducts(products->BRDC);
	} else {
		if ( products->BRDC->numblocksPast!=NULL) {
			//This is the third or more day we are reading. We need to free memory
			for(i=0;i<products->BRDC->numsatsPast;i++) {
				free(products->BRDC->blockPast[i]);
			}
			free(products->BRDC->numblocksPast);
			free(products->BRDC->blockPast);
			products->BRDC->numblocksPast=NULL;
			products->BRDC->blockPast=NULL;
		}
		memcpy(&products->BRDC->indexPast,&products->BRDC->index,sizeof(int)*MAX_GNSS*MAX_SATELLITES_PER_GNSS);
		products->BRDC->blockPast=products->BRDC->block;
		products->BRDC->numblocksPast=products->BRDC->numblocks;
		products->BRDC->numsatsPast=products->BRDC->numsatsPast;
		products->BRDC->numsats = 0;
		products->BRDC->block = NULL;
		products->BRDC->numblocks = NULL;
		for (i=0;i<MAX_GNSS;i++) {
			for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
				products->BRDC->index[i][j] = -1;
			}
		}
	}


	initBRDCblock(&block);
	ConstellationType[0] = '\0';
	
	while(getL(line,&len,fd)!=-1) {
		if (strncmp(&line[60],"COMMENT",7)==0) continue; //Comment can also be in the middle of the file
		if (readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,0,9);
				*rinexNavVersion = atof(aux);
				if ((int)(*rinexNavVersion)>3) {return 0;} //Version check
				if((int)*(rinexNavVersion)==2 && line[20]=='G') {
					// GLONASS Rinex v2 navigation file
					satSystem=GLONASS;
				} else if ((int)(*rinexNavVersion)==2 && line[20]=='H') {
					// GEO Rinex v2 navigation file
					satSystem=GEO;
				} else if ((int)(*rinexNavVersion)==2) {
					satSystem=GPS;
				}
			} else if (strncmp(&line[60],"ION ALPHA",9)==0) {  // Rinex v2
				for (i=0;i<4;i++) {
					getstr(aux,line,2+12*i,12);
					for (k=0;k<strlen(aux);k++) {
						if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
					}
					products->BRDC->ionA[i] = atof(aux);
				}
			} else if (strncmp(&line[60],"ION BETA",8)==0) {  // Rinex v2
				for (i=0;i<4;i++) {
					getstr(aux,line,2+12*i,12);
					for (k=0;k<strlen(aux);k++) {
						if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
					}
					products->BRDC->ionB[i] = atof(aux);
				}
			} else if (strncmp(&line[60],"IONOSPHERIC CORR",16)==0) {  // Rinex v3
				if (strncmp(&line[0],"GPSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ionA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"GPSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ionB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"GAL",3)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->ai[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"BDSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->bdsA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"BDSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->bdsB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"QZSA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->qzsA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"QZSB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->qzsB[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"IRNA",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->irnA[i] = atof(aux);
					}
				} else if (strncmp(&line[0],"IRNB",4)==0) {
					for (i=0;i<4;i++) {
						getstr(aux,line,5+12*i,12);
						for (k=0;k<strlen(aux);k++) {
							if (aux[k]=='D' || aux[k]=='e') aux[k]='E';
						}
						products->BRDC->irnB[i] = atof(aux);
					}
				}
			} else if (strncmp(&line[60],"TIME SYSTEM CORR",16)==0) {  //Rinex v3
				getstr(aux,line,0,4);
				timecorr = timecorrstr2timecorrtype(aux); 
				if ( timecorr != UNKNOWN_TIME_CORR){
					getstr(aux,line,5,17);
					products->BRDC->timeSysCorr[timecorr].acoff[0] = atof(aux);
					getstr(aux,line,22,16);
					products->BRDC->timeSysCorr[timecorr].acoff[1] = atof(aux);
					getstr(aux,line,38,7);
					products->BRDC->timeSysCorr[timecorr].timeref = atoi(aux);
					getstr(aux,line,45,5);
					products->BRDC->timeSysCorr[timecorr].weekref = atoi(aux);
				}
			} else if (strncmp(&line[60],"LEAP SECONDS",12)==0) {  
				getstr(aux,line,0,6);
				products->BRDC->AT_LS = atoi(aux);
				getstr(aux,line,6,6);
				if(aux[0] != '\0') { // No number given
					products->BRDC->AT_LSF = atoi(aux);
					if(products->BRDC->AT_LSF>0) {
						products->BRDC->LeapSecondsAvail=1;
					}
				}
				getstr(aux,line,12,6);
				if(aux[0] != '\0') { // No number given
					products->BRDC->WN_LSF = atoi(aux);
				}
				getstr(aux,line,18,6);
				if(aux[0] != '\0') { // No number given
					products->BRDC->DN = atoi(aux);
				}
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
				row = 0;
				properlyRead = 1;
			}
		} else {  // Reading body
			// Block to detect new RINEX header, it only affects when large RINEX are used
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getLback(line,&len,fd);
				//properlyRead = 1;
				//break;
				return 2;
			}
			if ((int)(*rinexNavVersion)==2) {
				if ( row == 0 ) {
					getstr(aux,line,0,2);
					block.PRN = atoi(aux);
					getstr(aux,line,3,2);
					tm.tm_year = atoi(aux);
					if (tm.tm_year <= 70) tm.tm_year += 100;
					getstr(aux,line,6,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,line,9,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,line,12,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,line,15,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,line,18,4);
					tm.tm_sec  = atoi(aux);
					seconds = atof(aux);
					block.Ttoc.MJDN = MJDN(&tm);
					block.Ttoc.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				}
				getstr(a0,line,3,19);
				if (a0[13]=='D' || a0[13]=='e') a0[13]='E';
				if (a0[14]=='D' || a0[14]=='e') a0[14]='E';
				if (a0[15]=='D' || a0[15]=='e') a0[15]='E';      // '-' sign can appear or not
				getstr(a1,line,22,19);
				if (a1[13]=='D' || a1[13]=='e') a1[13]='E';
				if (a1[14]=='D' || a1[14]=='e') a1[14]='E';
				if (a1[15]=='D' || a1[15]=='e') a1[15]='E';      // '-' sign can appear or not
				getstr(a2,line,41,19);
				if (a2[13]=='D' || a2[13]=='e') a2[13]='E';
				if (a2[14]=='D' || a2[14]=='e') a2[14]='E';
				if (a2[15]=='D' || a2[15]=='e') a2[15]='E';      // '-' sign can appear or not
				getstr(a3,line,60,19);
				if (a3[13]=='D' || a3[13]=='e') a3[13]='E';
				if (a3[14]=='D' || a3[14]=='e') a3[14]='E';
				if (a3[15]=='D' || a3[15]=='e') a3[15]='E';      // '-' sign can appear or not


				switch (satSystem) {
					case GPS:
						switch (row) {
							case 0:		
								block.clockbias			= atof(a1);
								block.clockdrift		= atof(a2);
								block.clockdriftrate	= atof(a3);
								break;
							case 1:
								block.IODE				= (int)atof(a0);
								block.crs				= atof(a1);
								block.deltan			= atof(a2);
								block.M0				= atof(a3);
								break;
							case 2:
								block.cuc				= atof(a0);
								block.e					= atof(a1);
								block.cus				= atof(a2);
								block.sqrta				= atof(a3);
								break;
							case 3:
								block.toe				= atof(a0);
								block.cic				= atof(a1);
								block.OMEGA				= atof(a2);
								block.cis				= atof(a3);
								break;
							case 4:
								block.i0				= atof(a0);
								block.crc				= atof(a1);
								block.omega				= atof(a2);
								block.OMEGADOT			= atof(a3);
								break;
							case 5:
								block.IDOT				= atof(a0);
								block.codesOnL2			= (int)atof(a1);
								block.GPSweek			= (int)atof(a2);
								block.L2Pdataflag		= (int)atof(a3);
								break;
							case 6:
								block.SVaccuracy		= atof(a0);
								block.SVhealth			= (int)atof(a1);
								block.TGD				= atof(a2);
								block.IODC				= (int)atof(a3);
								break;
							case 7:
								block.transTime			= atof(a0);
								block.fitInterval		= (int)atof(a1);
								if ( block.fitInterval == 0 ) block.fitInterval = 4;
								break;
						}
						break;
					case GLONASS: case GEO:
						switch(row){
							case 0:
								block.clockbias     		        = atof(a1);
								if (satSystem == GLONASS) {
									block.clockdrift           	= atof(a2);
									block.transTime			= atof(a3);
								} else {
									block.clockdrift                = atof(a2);
									block.transTime			= atof(a3);
								}
								block.clockdriftrate			= 0.0;
								//No IODE provided. Set it to -1
								block.IODE						= -1;
								block.SVaccuracy				= 0.;
								break;
							case 1:
								block.satposX                           = atof(a0)*1000;
								block.satvelX                           = atof(a1)*1000;
								block.sataccX                           = atof(a2)*1000;
								block.SVhealth                          = (int)atof(a3);
								break;
							case 2:
								block.satposY                           = atof(a0)*1000;
								block.satvelY                           = atof(a1)*1000;
								block.sataccY                           = atof(a2)*1000;
								if (satSystem == GLONASS) {
									block.freqnumber                = (int)atof(a3);
								} else {
									block.URAGEO			= (int)atof(a3);
								}
								break;
							case 3:
								block.satposZ                           = atof(a0)*1000;
								block.satvelZ                           = atof(a1)*1000;
								block.sataccZ                           = atof(a2)*1000;
								if (satSystem == GLONASS) {
									block.ageofoperation            = (int)atof(a3);
									block.fitInterval = 2; //For GLONASS, we will interpolate one hour back and one ahead
								} else {
									block.IODNGEO			= (int)atof(a3);
									block.fitInterval = 4;
								}
								break;
						}
						break;
					default:
						break;
				}
				row++;
				if ( row == 8 || (row==4 && (satSystem == GLONASS || satSystem == GEO ))) {
					row = 0;
					if (satSystem == GLONASS ) {
						//Toc and Toe of GLONASS will be left in UTC because orbits will be computed in UTC time
						block.Ttoe = block.Ttoc;
						ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
						//In Rinex v2, GLONASS transmission time is in UTC seconds of day!! We need to change to seconds of GPS Week
						DoW=(int)(SoW/86400); //Get Day of Week from Toe
						if(block.transTime<0) {
							block.transTime+=86400;
							DoW--;
							if(DoW<0) {
								DoW=6;
								GPSweek--;
							}
						}
						//Transform transmission time from UTC to GPS time
						block.transTime+=products->BRDC->AT_LS;
						if(block.transTime>=86400) {
							block.transTime-=86400;
							DoW++;
							if(DoW>6) {
								DoW=0;
								GPSweek++;
							}

						}
						block.transTime+=DoW*86400;//Convert to seconds of week
						block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
					} else if (satSystem == GEO ) {
						block.Ttoe = block.Ttoc;
						ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
						block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
					} else {
						block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
						block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
					}
					indSat = products->BRDC->index[satSystem][block.PRN];
					if (indSat == -1) {
						products->BRDC->index[satSystem][block.PRN] = products->BRDC->numsats;
						indSat = products->BRDC->index[satSystem][block.PRN];
						products->BRDC->block = realloc(products->BRDC->block,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
						products->BRDC->numblocks = realloc(products->BRDC->numblocks,sizeof(int)*(products->BRDC->numsats+1));
						products->BRDC->block[indSat] = NULL;
						products->BRDC->numblocks[indSat] = 0;
						products->BRDC->numsats++;
					}
					indBlock = products->BRDC->numblocks[indSat];
					products->BRDC->block[indSat] = realloc(products->BRDC->block[indSat],sizeof(TBRDCblock)*(indBlock+1));
					memcpy(&products->BRDC->block[indSat][indBlock], &block,sizeof(TBRDCblock));
					products->BRDC->numblocks[indSat]++;
				}
			}// End Nav Rinex v2
			 // Start Nav Rinex v3
			else if ((int)(*rinexNavVersion)==3) {
				if (row==0) {
					getstr(ConstellationType,line,0,1);	//GNSS type letter
					satSystem = gnsschar2gnsstype(ConstellationType[0]);
					if ( satSystem==QZSS || satSystem==IRNSS)  {row++;continue;} // QZSS and IRNSS are unsupported
						getstr(aux,line,1,2);	//PRN
						block.PRN = atoi(aux);
						getstr(aux,line,4,4);	//Year
						tm.tm_year = atoi(aux) -1900;
						getstr(aux,line,9,2);	//Month
						tm.tm_mon  = atoi(aux)-1;
						getstr(aux,line,12,2);	//Day
						tm.tm_mday = atoi(aux);
						getstr(aux,line,15,2);	//Hour
						tm.tm_hour = atoi(aux);
						getstr(aux,line,18,2);	//Minute
						tm.tm_min  = atoi(aux);
						getstr(aux,line,21,2);	//Second
						tm.tm_sec  = atoi(aux);
						seconds = atof(aux);
						block.Ttoc.MJDN = MJDN(&tm);
						block.Ttoc.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				}
				if ( satSystem==QZSS || satSystem==IRNSS ) { //QZSS and IRNSS are unsupported
					row++;
					if(row==8) { row=0;}	
					continue;
				} 
				getstr(a0,line,4,19);
				if (a0[13]=='D' || a0[13]=='e') a0[13]='E';
				if (a0[14]=='D' || a0[14]=='e') a0[14]='E';
				if (a0[15]=='D' || a0[15]=='e') a0[15]='E';	// '-' sign can appear or not
				getstr(a1,line,23,19);
				if (a1[13]=='D' || a1[13]=='e') a1[13]='E';
				if (a1[14]=='D' || a1[14]=='e') a1[14]='E';
				if (a1[15]=='D' || a1[15]=='e') a1[15]='E';	// '-' sign can appear or not
				getstr(a2,line,42,19);
				if (a2[13]=='D' || a2[13]=='e') a2[13]='E';
				if (a2[14]=='D' || a2[14]=='e') a2[14]='E';
				if (a2[15]=='D' || a2[15]=='e') a2[15]='E';	// '-' sign can appear or not
				getstr(a3,line,61,19);
				if (a3[13]=='D' || a3[13]=='e') a3[13]='E';
				if (a3[14]=='D' || a3[14]=='e') a3[14]='E';
				if (a3[15]=='D' || a3[15]=='e') a3[15]='E';	// '-' sign can appear or not

				

				switch (satSystem) {
					case GPS: case Galileo: case BDS:
						switch (row) {
							case 0:
								block.clockbias							= atof(a1);
								block.clockdrift						= atof(a2);
								block.clockdriftrate					= atof(a3);
								break;
							case 1:
								block.IODE								= (int)atof(a0);
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
								block.toe								= atof(a0);
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
								block.IDOT								= atof(a0);
								if (satSystem == GPS) {
									block.codesOnL2						= (int)atof(a1);
									block.GPSweek						= (int)atof(a2);
									block.L2Pdataflag					= (int)atof(a3);
								} else if (satSystem == Galileo) {
									block.dataSources		= (int)atof(a1);
									block.GALweek			= (int)atof(a2);
									block.GPSweek			= block.GALweek;
								} else if (satSystem == BDS) {
									block.BDSweek			= (int)atof(a2);
									block.GPSweek			= block.BDSweek+1356;
								}
								break;
							case 6:
								block.SVaccuracy = block.SISASignal		= atof(a0);
								block.SVhealth							= (int)atof(a1);
								if (satSystem == GPS) {
									block.TGD							= atof(a2);
									block.IODC							= (int)atof(a3);
								} else if (satSystem == Galileo) {
									block.BGDE5a			= atof(a2);
									block.BGDE5b			= atof(a3);
								} else if (satSystem == BDS) {
									block.TGD                       = atof(a2);
									block.TGD2                      = atof(a3);
								}
								break;
							case 7:
								block.transTime							= atof(a0);
								if (satSystem == GPS) {								
									block.fitInterval					= (int)atof(a1);
									if ( block.fitInterval == 0 ) block.fitInterval = 4;
								} else if (satSystem == BDS) {
									//block.transTime-=14;//Adjust 14 seconds to GPS time
									block.IODC                      = (int)atof(a1);
									if ( block.IODC>=0 && block.IODC<=1023 ) block.fitInterval=4;
								} else  if (satSystem == Galileo) {
									block.fitInterval		= 4;
								}
								break;
						}
						break;
					case GLONASS: case GEO:
						switch(row){
							case 0:
								block.clockbias     		        = atof(a1);
								if (satSystem == GLONASS) {
									block.clockdrift          	= atof(a2);
									block.transTime			= atof(a3);
								} else {
									block.clockdrift                = atof(a2);
									block.transTime			= atof(a3);
								}
								block.clockdriftrate					= 0.0;
								//No IODE and IODC provided. Set it to -1
								block.IODE								= -1;
								block.IODC         			           	= -1; 
								block.SVaccuracy						= 0.;
								break;
							case 1:
								block.satposX                           = atof(a0)*1000;
								block.satvelX                           = atof(a1)*1000;
								block.sataccX                           = atof(a2)*1000;
								block.SVhealth                          = (int)atof(a3);
								break;
							case 2:
								block.satposY                           = atof(a0)*1000;
								block.satvelY                           = atof(a1)*1000;
								block.sataccY                           = atof(a2)*1000;
								if (satSystem == GLONASS) {
									block.freqnumber                = (int)atof(a3);
								} else {
									block.URAGEO			= (int)atof(a3);
								}
								break;
							case 3:
								block.satposZ                           = atof(a0)*1000;
								block.satvelZ                           = atof(a1)*1000;
								block.sataccZ                           = atof(a2)*1000;
								if (satSystem == GLONASS) {
									block.ageofoperation            = (int)atof(a3);
									block.fitInterval = 2; //For GLONASS, we will interpolate one hour back and one ahead
								} else {
									block.IODNGEO			= (int)atof(a3);
									block.fitInterval = 4;
								}
								break;
						}
						break;
					default:
						break;
				}
				row++;
				if (row==8 || (row==4 && (satSystem == GLONASS || satSystem == GEO ))) {
					row = 0;
					if (satSystem == GLONASS ) {
						//Toc and Toe of GLONASS will be left in UTC because orbits will be computed in UTC time
						block.Ttoe = block.Ttoc;
						ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
						//In Rinex v3, GLONASS transmission time is in UTC seconds of week!
						//Transform transmission time from UTC to GPS time
						block.transTime+=products->BRDC->AT_LS;
						block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
					} else if (satSystem == GEO ) {
						block.Ttoe = block.Ttoc;
						ttime2gpswsnoroll(&block.Ttoc,&GPSweek,&SoW);
						block.TtransTime = gpsws2ttime(GPSweek,block.transTime);
					} else if (satSystem == BDS ) {
						//Convert from BeiDou time to GPS time
						//block.toe (toe in in seconds of BDS week) must be left untouched for computing satellite coordinates correctly
						block.Ttoc = tdadd(&block.Ttoc,14.);
						block.Ttoe = gpsws2ttime(block.GPSweek,block.toe+14.);
						block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime+14.);
					} else {
						block.Ttoe = gpsws2ttime(block.GPSweek,block.toe);
						block.TtransTime = gpsws2ttime(block.GPSweek,block.transTime);
					}
					indSat = products->BRDC->index[satSystem][block.PRN];
					if (indSat == -1) {
						products->BRDC->index[satSystem][block.PRN] = products->BRDC->numsats;
						indSat = products->BRDC->index[satSystem][block.PRN];
						products->BRDC->block = realloc(products->BRDC->block,sizeof(TBRDCblock*)*(products->BRDC->numsats+1));
						products->BRDC->numblocks = realloc(products->BRDC->numblocks,sizeof(int)*(products->BRDC->numsats+1));
						products->BRDC->block[indSat] = NULL;
						products->BRDC->numblocks[indSat] = 0;
						products->BRDC->numsats++;
					}
					indBlock = products->BRDC->numblocks[indSat];
					products->BRDC->block[indSat] = realloc(products->BRDC->block[indSat],sizeof(TBRDCblock)*(indBlock+1));
					memcpy(&products->BRDC->block[indSat][indBlock], &block,sizeof(TBRDCblock));
					products->BRDC->numblocks[indSat]++;
				}
			}// End Nav Rinex v3
		}
	}

	return (properlyRead); // properly read 
}

/*****************************************************************************
 * Name        : readRinexNavLastEpoch
 * Description : Find last epoch of RINEX navigation file. It will read the last
 *                day of data, as it can't assume that data is ordered 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TTime *lastEpoch                O  N/A  Last Epoch in SP3 file
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Last Epoch read
 *                                         0 => Error
 *****************************************************************************/
int readRinexNavLastEpoch (FILE *fd, TTime *lastEpoch) {

    struct stat             filestat;   //This is to get the file size
    off_t                   filesize;
    long                    CurrentPos;
    int                     len = 0;
	int						i;
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
	if (readRinexNav(fd, &products, &rinexNavVersion)<1) {
		free(products.BRDC->block);
		fseek(fd,CurrentPos,SEEK_SET);
		return 0;
	}
	fseek(fd,CurrentPos,SEEK_SET);
	*lastEpoch=getProductsLastEpochBRDC(&products);
	//Free memory
	for(i=0;i<products.BRDC->numsats;i++) {
		free(products.BRDC->block[i]);
	}
	free(products.BRDC->numblocks);
	free(products.BRDC->block);
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
	TTime			t,lastT;
	int				ind;
	struct tm		tm;
	double			seconds;
	double			interval;
	int				readedLine = 0;
	int				readedSatellites;
	//char			versionId;
	enum GNSSystem	system;
	int				usedRecords;
	int				CurrentInd;
	int				auxN;
	double			BaseSigmaOrbit;
	double			BaseSigmaClock;

	if (!readOrbits && !readClocks) return 0;

	products->type = SP3;
	products->SP3 = malloc(sizeof(TSP3products));
	initSP3products(products->SP3);
	lastT.MJDN = 0;
	lastT.SoD = 0;

	while(getL(line,&len,fd)!=-1) {
		readedLine++;
		if (readingHeader) {
			if (readedLine==1) {
				// #bP2008  8 27 00 00 00.00000000      96   d   ITR91 FIT  JPL
				if (line[0]!='#') error = 1;
				if (line[2]=='V') products->SP3->orbits.velocityAvailable = 1;
				else products->SP3->orbits.velocityAvailable = 0;
				getstr(aux,line,32,7);
				HeaderNumRecords=atoi(aux);
				if (readOrbits) products->SP3->orbits.numRecords = atoi(aux);
				if (readClocks) products->SP3->clocks.numRecords = atoi(aux);
			} else if (readedLine==2) {
				// ## 1494 259200.00000000   900.00000000 54705 0.0000000000000
				//getstr(aux,line,24,14);
				//if (readOrbits) products->SP3->orbits.interval = atof(aux);
				//if (readClocks) products->SP3->clocks.interval = atof(aux);
				getstr(aux,line,39,5);
				if (readOrbits) products->SP3->orbits.startTime.MJDN = atoi(aux);
				if (readClocks) products->SP3->clocks.startTime.MJDN = atoi(aux);
				getstr(aux,line,45,15);
				if (readOrbits) products->SP3->orbits.startTime.SoD = atof(aux)*86400.0;
				if (readClocks) products->SP3->clocks.startTime.SoD = atof(aux)*86400.0;
			} else if (strncmp(line,"+ ",2)==0) {
				// +   31   G02G03G04G05G06G07G08G09G10G11G12G13G14G15G16G17G18
				if (readedLine==3) {
					getstr(aux,line,3,3);
					auxN = atoi(aux);
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
				}
				for (i=0;i<17 && readedSatellites<auxN;i++,readedSatellites++) { //auxN = products->SP3->XXXX.numSatellites;
					system = gnsschar2gnsstype(line[9+3*i]);
					getstr(aux,line,10+3*i,2);
					if (readOrbits) products->SP3->orbits.index[system][atoi(aux)] = readedSatellites;
					if (readClocks) products->SP3->clocks.index[system][atoi(aux)] = readedSatellites;
				}
			} else if (strncmp(line,"++",2)==0) {
				if (readedSatellites==auxN) readedSatellites=0; //This is the first line with "++" read
				for (i=0;i<17 && readedSatellites<auxN;i++,readedSatellites++) { //auxN = products->SP3->XXXX.numSatellites;
					// Accuracy is 2^val mm.
					getstr(aux,line,10+3*i,2);
					if (readOrbits) products->SP3->orbits.accuracy[readedSatellites] = pow(2,atoi(aux))*1e-3;
				}
			} else if (strncmp(line,"%f",2)==0) {
				if (FirstHeaderfline==1) {
					FirstHeaderfline=0;
					if (readOrbits) {
						getstr(aux,line,3,10);
						BaseSigmaOrbit=atof(aux);
						if (BaseSigmaOrbit==0.) {
							BaseSigmaOrbit=2.;
						}
					}
					if (readClocks) {
						getstr(aux,line,14,10);
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
				getstr(aux,line,3,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,8,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,11,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,14,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,17,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,20,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				t.MJDN = MJDN(&tm);
				t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				//Compute interval (do not trust header)
				if (products->SP3->orbits.interval == 0. && lastT.MJDN!=0) { // If interval is still not known (and it is not the first epoch)
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
					system=0;
					PRN=0;
					ind=0;
				} else {
					system = gnsschar2gnsstype(line[1]);
					getstr(aux,line,2,2);
					PRN = atoi(aux);
					if (readOrbits) ind = products->SP3->orbits.index[system][PRN];
					else ind = products->SP3->clocks.index[system][PRN];
				}
				if (readOrbits) {
					if (CurrentInd==0) {
						//Check if sigmas per epoch are provided
						getstr(aux,line,46,14);
						products->SP3->orbits.hasSigmaPerEpoch=0;
						if (atof(aux)!=INVALID_CLOCK) {
							if (strncmp(&line[61],"  ",2)!=0) {
								products->SP3->orbits.hasSigmaPerEpoch=1;
							}
						}
					}
					getstr(aux,line,4,14);
					products->SP3->orbits.block[ind][CurrentInd].x[0] = atof(aux)*1e3;
					getstr(aux,line,18,14);
					products->SP3->orbits.block[ind][CurrentInd].x[1] = atof(aux)*1e3;
					getstr(aux,line,32,14);
					products->SP3->orbits.block[ind][CurrentInd].x[2] = atof(aux)*1e3;
					memcpy(&products->SP3->orbits.block[ind][usedRecords-1].t,&t,sizeof(TTime));

					getstr(aux,line,46,14);
					if (products->SP3->orbits.hasSigmaPerEpoch==1) {
						getstr(aux,line,46,14);
						if (atof(aux)!=INVALID_CLOCK) {
							getstr(aux,line,61,2);
							products->SP3->orbits.block[ind][CurrentInd].xsigma[0] = pow(BaseSigmaOrbit,atof(aux))*1e-3;
							getstr(aux,line,64,2);
							products->SP3->orbits.block[ind][CurrentInd].xsigma[1] = pow(BaseSigmaOrbit,atof(aux))*1e-3;
							getstr(aux,line,67,2);
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
					if(strlen(line)>=80 && strncmp(&line[78],"  ",2)!=0) {
						strncpy(products->SP3->orbits.block[ind][CurrentInd].orbitflags,&line[78],2);
						products->SP3->orbits.block[ind][CurrentInd].orbitflags[2]='\0';
					} else {
						products->SP3->orbits.block[ind][CurrentInd].orbitflags[0]='\0';
					}
				}
				if (readClocks) {
					getstr(aux,line,46,14);
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
							getstr(aux,line,70,3);
							products->SP3->clocks.block[ind][CurrentInd].clocksigma=pow(BaseSigmaClock,atof(aux))*1e-12*c0;
						}
					}
					memcpy(&products->SP3->clocks.block[ind][CurrentInd].t,&t,sizeof(TTime));

					//Read clock flags
					if(strlen(line)>=76 && strncmp(&line[74],"  ",2)!=0) {
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
					system=0;
					PRN=0;
					ind=0;
				} else {					
					system = gnsschar2gnsstype(line[1]);
					getstr(aux,line,2,2);
					PRN = atoi(aux);
					if (readOrbits) ind = products->SP3->orbits.index[system][PRN];
					else ind = products->SP3->clocks.index[system][PRN];
				}
				if (readOrbits) {
					getstr(aux,line,4,14);
					products->SP3->orbits.block[ind][CurrentInd].v[0] = atof(aux)*1e-1;
					getstr(aux,line,18,14);
					products->SP3->orbits.block[ind][CurrentInd].v[1] = atof(aux)*1e-1;
					getstr(aux,line,32,14);
					products->SP3->orbits.block[ind][CurrentInd].v[2] = atof(aux)*1e-1;
					memcpy(&products->SP3->orbits.block[ind][CurrentInd].t,&t,sizeof(TTime));
				}
				if (readClocks) {
					getstr(aux,line,46,14);
					products->SP3->clocks.block[ind][CurrentInd].clockrate = atof(aux)*(c0/1e7);
					memcpy(&products->SP3->clocks.block[ind][CurrentInd].t,&t,sizeof(TTime));
				}
			} else if (strncmp(line,"EOF",3)==0) { // End of File
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
					sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d)",HeaderNumRecords,usedRecords);
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
				if(usedRecords!=HeaderNumRecords) {
					//Header had incorrect number of entries
					sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d)",HeaderNumRecords,usedRecords);
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
		sprintf(messagestr,"WARNING Number of entries in header (%d) does not match with number of entries read (%d)",HeaderNumRecords,usedRecords);
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
			getstr(aux,line,3,4);
			tm.tm_year = atoi(aux)-1900;
			getstr(aux,line,8,2);
			tm.tm_mon  = atoi(aux)-1;
			getstr(aux,line,11,2);
			tm.tm_mday = atoi(aux);
			getstr(aux,line,14,2);
			tm.tm_hour = atoi(aux);
			getstr(aux,line,17,2);
			tm.tm_min  = atoi(aux);
			getstr(aux,line,20,11);
			tm.tm_sec  = atoi(aux);
			seconds = atof(aux);
			lastEpoch->MJDN = MJDN(&tm);
			lastEpoch->SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			fseek(fd,CurrentPos,SEEK_SET);
			return 1;
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         2 => Another file concatenated
 *                                         0 => Error
 *****************************************************************************/
int readRinexClocks (FILE *fd, TGNSSproducts *products) {
	char 			line[MAX_INPUT_LINE];
	char	 	   	aux[100];
	char	 	   	aux2[100];
	char	 	   	aux3[100];
	int 			len = 0;
	//double			rinexVersion;
	int				properlyRead = 0;
	int				error = 0;
	int				readingHeader = 1;
	enum GNSSystem	system;
	int				PRN;
	struct tm		tm;
	int				i,j;
	int				ind;
	double			seconds;
	double			interval;
	TTime			t, lastT;
	int				readedSatellites;
	const int		ini_vsize = 64;
	int 			found_prn_list = 0;
	
	lastT.MJDN = 0;
	lastT.SoD = 0;
	
	while(getL(line,&len,fd)!=-1) {
		if (!readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
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
				getstr(aux,line,0,9);
				//rinexVersion = atof(aux); //Commented to avoid not used variable warning
			} else if (strncmp(&line[60],"# OF SOLN SATS",14)==0) {
				getstr(aux,line,4,2);
				products->SP3->clocks.numSatellites = products->SP3->clocks.numSatellitesRead = atoi(aux);
				// Reserve memory for satellites
				products->SP3->clocks.block = malloc(sizeof(TSP3clockblock*)*products->SP3->clocks.numSatellites);
				// RINEX clock standard does not provide any apriori information on the number of records that will 
				// appear on the file. A dynamic readjustment becomes necessary to overcome this issue.
				products->SP3->clocks.vsizeblock = ini_vsize;
				// Reserve initial memory for blocks
				for (i=0;i<products->SP3->clocks.numSatellites;i++) {
					products->SP3->clocks.block[i] = malloc(sizeof(TSP3clockblock)*products->SP3->clocks.vsizeblock);
					for (j=0;j<products->SP3->clocks.vsizeblock;j++) 
						initSP3clockblock(&products->SP3->clocks.block[i][j]);
				}
				readedSatellites = 0;
			} else if (strncmp(&line[60],"PRN LIST",8)==0) {
				found_prn_list = 1;
				for (i=0;i<15 && readedSatellites<products->SP3->clocks.numSatellites;i++,readedSatellites++) {
					system = gnsschar2gnsstype(line[4*i]);
					getstr(aux,line,1+4*i,2);
					products->SP3->clocks.index[system][atoi(aux)] = readedSatellites;
				}
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
				properlyRead = 1;
				products->SP3->clocks.numRecords = 0;
				// The standard forces that the field 'PRN LIST' is present in the header, so the next section would
				// never be executed...
				if (!found_prn_list) {
					readedSatellites = 0;
					for (i=0;i<MAX_GNSS;i++) {
						for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
							products->SP3->clocks.index[i][j] = readedSatellites;
							readedSatellites++;
						}
					}
					products->SP3->clocks.numSatellites = readedSatellites;
					// Reserve memory for satellites
					products->SP3->clocks.block = malloc(sizeof(TSP3clockblock*)*products->SP3->clocks.numSatellites);
					products->SP3->clocks.vsizeblock = ini_vsize;
					for (i=0;i<products->SP3->clocks.numSatellites;i++) {
						products->SP3->clocks.block[i] = malloc(sizeof(TSP3clockblock)*products->SP3->clocks.vsizeblock);
						for (j=0;j<products->SP3->clocks.vsizeblock;j++) 
							initSP3clockblock(&products->SP3->clocks.block[i][j]);
					}
				}
			}
		} else { // !readingHeader
			getstr(aux,line,3,4);
			getstr(aux2,line,0,2);
			getstr(aux3,line,4,2);
			PRN = atoi(aux3);
			if ( (aux[0]=='G' || aux[0]=='R' || aux[0]=='E' || aux[0]=='S' || aux[0]=='C' || aux[0]=='J' || aux[0]=='I' ) && PRN>0 && strncmp(aux2,"AS",2)==0 )  {
				// AS G02  2008 10 10 00 00  0.000000  2    1.813604156067e-04  3.113411106060e-11
				system = gnsschar2gnsstype(aux[0]);
				ind = products->SP3->clocks.index[system][PRN];

				getstr(aux,line,8,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,13,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,19,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,22,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,25,9);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				t.MJDN = MJDN(&tm);
				t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				
				if (lastT.MJDN != t.MJDN || lastT.SoD != t.SoD) { // New Epoch
					if (products->SP3->clocks.interval == 0. && lastT.MJDN!=0) { // If interval is still not known (and it is not the first epoch)
						interval = tdiff(&t,&lastT);
						if (interval>=1.) {
							//Take out decimals if interval is greater than 1
							products->SP3->clocks.interval = (double)((int)(interval));
						} else {
							products->SP3->clocks.interval = interval;
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
					if (products->SP3->clocks.numRecords == products->SP3->clocks.vsizeblock) {
						products->SP3->clocks.vsizeblock *= 2;
						// Reserve memory for blocks
						for (i=0;i<products->SP3->clocks.numSatellites;i++) {
							products->SP3->clocks.block[i] = realloc(products->SP3->clocks.block[i],sizeof(TSP3clockblock)*products->SP3->clocks.vsizeblock);
							for (j=products->SP3->clocks.vsizeblock/2;j<products->SP3->clocks.vsizeblock;j++)  {
								initSP3clockblock(&products->SP3->clocks.block[i][j]);
							}
						}
					}
				}
			
				getstr(aux,line,37,22);
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clock = atof(aux)*c0;
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockrate = 0.0;
				products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockdriftrate = 0.0;

				//Read clock flags if available (NOTE: This is not in RINEX standard, but appear in MGEX clock files
				if(len>=83) {
				   if (	strncmp(&line[81],"  ",2)!=0) {
						strncpy(products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags,&line[81],2);
						products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags[2]='\0';
				   }
				} else {
					products->SP3->clocks.block[ind][products->SP3->clocks.numRecords-1].clockflags[0]='\0';
				}
			
				//getstr(aux,line,59,22);
			
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readRinexClocksFile (char *filename, TGNSSproducts *products) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftRINEXclocks) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readRinexClocks (fd, products);
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         4 => File is concatenated but no END OF FILE found
 *                                         3 => File is concatenated
 *                                         2 => properly read but no END OF FILE found
 *                                         1 => Properly read
 *                                         0 => Error
 *                                        -2 => Number of records read do not match the number given in the header
 *                                        -3 => Something wrong or missing in Header
 *****************************************************************************/
int readIONEX (FILE *fd, TIONEX *IONEX, double *ionexVersion) {
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
				getstr(aux,line,0,9);
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
				getstr(aux,line,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->startTime.MJDN = MJDN(&tm);
				IONEX->startTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"EPOCH OF LAST MAP",17)==0) {
				getstr(aux,line,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->endTime.MJDN = MJDN(&tm);
				IONEX->endTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"INTERVAL",8)==0) {
				getstr(aux,line,0,6);
				IONEX->interval = atoi(aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"# OF MAPS IN FILE",17)==0) {
				getstr(aux,line,0,6);
				IONEX->numMaps = atoi(aux); 
				// Reserve memory for maps
				IONEX->map = malloc(sizeof(TIonoMap)*IONEX->numMaps);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"MAPPING FUNCTION",16)==0) {
				getstr(aux,line,2,4);
				strcpy(IONEX->mappingFunction,aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"ELEVATION CUTOFF",16)==0) {
				getstr(aux,line,0,8);
				IONEX->elevationCutoff = atof(aux);
			} else if (strncmp(&line[60],"OBSERVABLES USED",16)==0) {
				getstr(aux,line,0,60);
				strcpy(IONEX->observablesUsed,aux);
			} else if (strncmp(&line[60],"# OF STATIONS",13)==0) {
				getstr(aux,line,0,6);
				IONEX->stationNumber = atoi(aux);
			} else if (strncmp(&line[60],"# OF SATELLITES",15)==0) {
				getstr(aux,line,0,6);
				IONEX->satNumber = atoi(aux);
			} else if (strncmp(&line[60],"BASE RADIUS",11)==0) {
				getstr(aux,line,0,8);
				IONEX->baseRadius = atof(aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"MAP DIMENSION",13)==0) {
				getstr(aux,line,0,6);
				IONEX->mapDimension = atoi(aux);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"EXPONENT",8)==0) {
				getstr(aux,line,0,6);
				IONEX->exponent = atoi(aux);
				IONEX->conversionFactor = E(IONEX->exponent);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"HGT1 / HGT2 / DHGT",18)==0) {
				getstr(aux,line,2,6);			// HGT1
				ionoMap.hgt1 = atof(aux);
				getstr(aux,line,8,6);			// HGT2
				ionoMap.hgt2 = atof(aux);
				getstr(aux,line,14,6);			// DHGT
				ionoMap.dhgt = atof(aux);
				ionoMap.nhgt = numSteps(ionoMap.hgt1,ionoMap.hgt2,ionoMap.dhgt);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"LAT1 / LAT2 / DLAT",18)==0) {
				getstr(aux,line,2,6);			// LAT1
				ionoMap.lat1 = atof(aux);
				getstr(aux,line,8,6);			// LAT2
				ionoMap.lat2 = atof(aux);
				getstr(aux,line,14,6);			// DLAT
				ionoMap.dlat = atof(aux);
				ionoMap.nlat = numSteps(ionoMap.lat1,ionoMap.lat2,ionoMap.dlat);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"LON1 / LON2 / DLON",18)==0) {
				getstr(aux,line,2,6);			// LON1
				ionoMap.lon1 = atof(aux);
				getstr(aux,line,8,6);			// LON2
				ionoMap.lon2 = atof(aux);
				getstr(aux,line,14,6);			// DLON
				ionoMap.dlon = atof(aux);
				ionoMap.nlon = numSteps(ionoMap.lon1,ionoMap.lon2,ionoMap.dlon);
				HeaderLinesNecessary++;
			} else if (strncmp(&line[60],"START OF TEC MAP",16)==0) {
				if(HeaderLinesNecessary!=0) break;
				getstr(aux,line,0,6);
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
				getstr(aux,line,0,6);
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
				getstr(aux,line,0,6);
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
				getstr(aux,line,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				IONEX->map[ind].t.MJDN = MJDN(&tm);
				IONEX->map[ind].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			} else if (strncmp(&line[60],"LAT/LON1/LON2/DLON/H",20)==0) {
				if(HeaderLinesNecessary!=0) break;
				getstr(aux,line,2,6);
				lat = atof(aux);
				getstr(aux,line,8,6);
				lon1 = atof(aux);
				getstr(aux,line,14,6);
				lon2 = atof(aux);
				getstr(aux,line,20,6);
				dlon = atof(aux);
				getstr(aux,line,26,6);
				h = atof(aux);
				if (IONEX->map[ind].hgt1==0) { IONEX->map[ind].hgt1=IONEX->map[ind].hgt2=h; } //To avoid 0 values in case HGT1=HGT2=DHGT=0 in IONEX file
				nlon = numSteps(lon1,lon2,dlon);
				ilon = 0;
				readingCells = 1;
			} else if (strncmp(&line[60],"PRN / BIAS / RMS",16)==0) {
				getstr(ConstellationType,line,3,1);     //GNSS type letter
				satSystem = gnsschar2gnsstype(ConstellationType[0]);
				getstr(aux,line,4,2);
				PRN = atoi(aux);
				getstr(aux,line,6,10);
				IONEX->ionexDCB.DCB[satSystem][PRN] = atof(aux);
				getstr(aux,line,16,10);
				IONEX->ionexDCB.DCBRMS[satSystem][PRN] = atof(aux);
				IONEX->ionexDCB.DCBavailable = 1;
			} else if (strncmp(&line[60],"STATION / BIAS / RMS",20)==0) {
				IONEX->numStationData++;
				IONEX->ionexStation = malloc(sizeof(TIonexStation)*IONEX->numStationData);
				getstr(aux,line,6,4);
				strcpy(IONEX->ionexStation[IONEX->numStationData -1].stationInitials,aux);
				getstr(aux,line,11,10);
				strcpy(IONEX->ionexStation[IONEX->numStationData -1].stationcode,aux);
				getstr(aux,line,26,10);
				IONEX->ionexStation[IONEX->numStationData -1].stationBias = atof(aux);
				getstr(aux,line,36,10);
				IONEX->ionexStation[IONEX->numStationData -1].stationRMS = atof(aux);
			} else if (strncmp(&line[60],"END OF FILE",11)==0) {
				properlyRead = 1;
				firstTimeRead=0;
				EndofFileFound=1;
			}
		} else {  // readingCells
			if(HeaderLinesNecessary!=0) break;
			for (i=0;i<16 && ilon<nlon;i++,ilon++) {
				getstr(aux,line,i*5,5);
				lon = ilon*dlon + lon1;
				ionoValue = atof(aux);
				if (ionoValue==9999) { setIonoValue(&IONEX->map[ind],mapType,h,lat,lon,ionoValue);}
				else {
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readFPPP (FILE *fd, TFPPPIONEX *FPPP, double *FPPPVersion) {
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
				getstr(aux,line,0,9);
				*FPPPVersion = atof(aux);
				if (*FPPPVersion != 1.0 ) return 0;
			} else if (strncmp(&line[60],"EPOCH OF FIRST MAP",18)==0) {
				getstr(aux,line,2,4);
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,10,2);
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);
				tm.tm_mday = atoi(aux);
				getstr(aux,line,22,2);
				tm.tm_hour = atoi(aux);
				getstr(aux,line,28,2);
				tm.tm_min  = atoi(aux);
				getstr(aux,line,34,11);
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				FPPP->startTime.MJDN = MJDN(&tm);
				FPPP->startTime.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
			} else if (strncmp(&line[60],"INTERVAL",8)==0) {
				getstr(aux,line,0,6);
				FPPP->interval = atoi(aux);
			} else if (strncmp(&line[60],"BASE RADIUS",11)==0) {
				getstr(aux,line,0,8);
				FPPP->baseRadius = atof(aux);
			} else if (strncmp(&line[60],"HGT1 / HGT2",11)==0) {
				getstr(aux,line,0,8);			// HGT1
				FPPPMap.hgt1 = atof(aux);
				getstr(aux,line,8,8);			// HGT2
				FPPPMap.hgt2 = atof(aux);
				FPPPMap.dhgt = FPPPMap.hgt2 - FPPPMap.hgt1;
		/*	} else if (strncmp(&line[60],"LAT1 / LAT2 / DLAT",18)==0) {
				getstr(aux,line,2,6);			// LAT1
				ionoMap.lat1 = atof(aux);
				getstr(aux,line,8,6);			// LAT2
				ionoMap.lat2 = atof(aux);
				getstr(aux,line,14,6);			// DLAT
				ionoMap.dlat = atof(aux);
				ionoMap.nlat = numSteps(ionoMap.lat1,ionoMap.lat2,ionoMap.dlat);*/
			} else if (strncmp(&line[60],"DLT / DLAT",10)==0) {
				getstr(aux,line,0,8);			// DLT
				FPPPMap.dlt = atof(aux);
				FPPPMap.lt2 = FPPPMap.lt2 - FPPPMap.dlt;
				getstr(aux,line,8,8);			// DLAT
				FPPPMap.dlat = atof(aux);
			} else if (strncmp(&line[60],"MIN/MAX  LAT",12)==0) {
				getstr(aux,line,0,8);                   // LAT1
								FPPPMap.lat1 = atof(aux);
				getstr(aux,line,8,8);			// LAT2
				FPPPMap.lat2 = atof(aux);
				FPPPMap.nlt = numSteps(FPPPMap.lt1,FPPPMap.lt2,FPPPMap.dlt);
				FPPPMap.nlat = numSteps(FPPPMap.lat1,FPPPMap.lat2,FPPPMap.dlat);
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
			}
		
		} else {
			if (strncmp(&line[60],"START OF TEC MAP",16)==0 && strlen(line)>60) {
				getstr(aux,line,0,7);
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
			} else if (strncmp(&line[60],"EPOCH OF CURRENT MAP",20)==0 && strlen(line)>60) {
				getstr(aux,line,2,4);		// Year
				tm.tm_year = atoi(aux)-1900;
				getstr(aux,line,10,2);		// Month
				tm.tm_mon  = atoi(aux)-1;
				getstr(aux,line,16,2);		// Day
				tm.tm_mday = atoi(aux);
				getstr(aux,line,22,2);		// Hour
				tm.tm_hour = atoi(aux);
				getstr(aux,line,28,2);		// Minute
				tm.tm_min  = atoi(aux);
				getstr(aux,line,34,2);		// Second
				tm.tm_sec  = atoi(aux);
				seconds = atof(aux);
				FPPP->map[ind].t.MJDN = MJDN(&tm);
				FPPP->map[ind].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
								//DCB data ended
								readingDCB = 0;
			} else if (readingDCB){
								getstr(ConstellationType,line,0,1);     //GNSS type letter
								satSystem = gnsschar2gnsstype(ConstellationType[0]);
				getstr(aux,line,1,2); // PRN 
				PRN = atoi(aux);	
				getstr(aux,line,4,9); // frac1 	
				FPPP->fpppDCB.frac1[satSystem][PRN] = atof(aux);
				getstr(aux,line,14,9); // frac2
				FPPP->fpppDCB.fracw[satSystem][PRN] = atof(aux);
				getstr(aux,line,24,9); // IFB
				FPPP->fpppDCB.IFB[satSystem][PRN] = atof(aux);
				FPPP->fpppDCB.DCBavailable = 1;
		/*	} else if (strncmp(&line[60],"LAT/LON1/LON2/DLON/H",20)==0) {
				getstr(aux,line,2,6);
				lat = atof(aux);
				getstr(aux,line,8,6);
				lon1 = atof(aux);
				getstr(aux,line,14,6);
				lon2 = atof(aux);
				getstr(aux,line,20,6);
				dlon = atof(aux);
				getstr(aux,line,26,6);
				h = atof(aux);
				if (FPPP->map[ind].hgt1==0) { FPPP->map[ind].hgt1=FPPP->map[ind].hgt2=h; } //To avoid 0 values in case HGT1=HGT2=DHGT=0 in IONEX file
				nlon = numSteps(lon1,lon2,dlon);
				ilon = 0;
				readingCells = 1;
		*/
		/*	} else if (strncmp(&line[60],"END OF FILE",11)==0) {
								properlyRead = 1;
		*/	
			}else {  // readingCells

				getstr(aux,line,0,6); // LT
				lt = modulo(atof(aux)+360,360);
				getstr(aux,line,6,6); // LAT
				lat = atof(aux);
				getstr(aux,line,12,9); // PARTIAL TEC
				tec = atof(aux);
				getstr(aux,line,21,5); // SIGMA
				sigma = atof(aux);
				getstr(aux,line,27,3); // SIGMA EXPONENT
				exponent = atof(aux);
				sigma = sigma * E(exponent);
				getstr(aux,line,30,3); // MAP POSITION
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readFPPPFile (char *filename, TFPPPIONEX *FPPP, double *FPPPVersion) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftFPPP) return 0;
	if ((fd = fopen(filename,"rb"))) {
		ret = readFPPP (fd, FPPP, FPPPVersion);
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readConstellation (FILE *fd, TConstellation *constellation) {
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
		if (line[strlen(line)-1]==13) line[strlen(line)-1] = '\n';
		getstr(aux,line,0,5);
		if (strcmp(aux,"Block")==0) {
			// Initialize
			initConstellationElement(&sat);
			sat.GNSS = GPS;		// Only prepared for GPS right now
						
			getstr(aux,line,6,10);
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
					getstr(aux,line,7,3);
					sat.SVN = atoi(aux);
					getstr(aux,line,57,14);
					if (sat.SVN!=0 && strcmp(aux,"Launch failure")!=0) { // Valid line
						getstr(aux,line,11,2);
						sat.PRN = atoi(aux);
						
						getstr(aux,line,41,2);
						tm.tm_year = atoi(aux);
						if (tm.tm_year < 70) tm.tm_year+=100;
						getstr(aux,line,44,2);
						tm.tm_mon = atoi(aux)-1;
						getstr(aux,line,47,2);
						tm.tm_mday = atoi(aux);
						sat.tLaunch.MJDN = MJDN(&tm);
						sat.tLaunch.SoD = 0;
						
						if (line[68]==':') { // Satellite not decomissioned
							tm.tm_year = 130;
							tm.tm_mon = 0;
							tm.tm_mday = 1;
						} else { // Satellite decomissioned
							getstr(aux,line,70,2);
							tm.tm_year = atoi(aux);
							if (tm.tm_year < 70) tm.tm_year+=100;
							getstr(aux,line,73,2);
							tm.tm_mon = atoi(aux)-1;
							getstr(aux,line,76,2);
							tm.tm_mday = atoi(aux);
						} 
						sat.tDecommissioned.MJDN = MJDN(&tm);
						sat.tDecommissioned.SoD = 0;
						
						// Allocate memory
						constellation->numSatellites ++;
						constellation->sat = realloc(constellation->sat,sizeof(TConstellationElement)*constellation->numSatellites);
						
						// Store satellite
						memcpy(&constellation->sat[constellation->numSatellites-1],&sat,sizeof(TConstellationElement));
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readConstellationFile (char *filename, TConstellation *constellation) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftConstellation) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readConstellation (fd, constellation);
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly read
 *                                         0 => Error
 *****************************************************************************/
int readAntex (FILE *fd, TConstellation *constellation, TAntennaList *antennaList) {
	char			line[MAX_INPUT_LINE];
	char			aux[100];
	char			*ca;
	int 			len = 0;
	struct tm		tm;
	int				properlyRead = 0;
	TConstellationElement	sat;
	TAntenna		ant;
	int				i, j, k;
	int				freqInd;
	int				readingHeader = 1;
	int				error = 0;
	int				PRN;
	int				system;
	int				readingWhat; // = 0 Satellite    = 1 Receiver antenna
	double			seconds;
	
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	
	while(getL(line,&len,fd)!=-1) {
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
				getstr(aux,line,20,20);
				PRN = atoi(&aux[1]);
				if (PRN!=0 && (aux[0]=='G' || aux[0]=='R' || aux[0]=='E' || aux[0]=='S' || aux[0]=='C' || aux[0]=='J' || aux[0]=='I')) {
					// GNSS Satellite
					initConstellationElement(&sat);
					sat.GNSS = gnsschar2gnsstype(aux[0]);
					sat.PRN = PRN;
					getstr(aux,line,40,10);
					sat.SVN = atoi(&aux[1]);
					getstr(aux,line,0,20);
					sat.block = satblockstr2satblock(aux);
					readingWhat = 0;
				} else {
					// Receiver antenna
					initAntenna(&ant);
					getstr(aux,line,0,20);
					strcpy(ant.type,aux);
					// Separate the anntena.type into antenna and radome
					strcpy(ant.type_ant,ant.type);
					ca = strstr(ant.type_ant," ");
					if (ca != NULL) {
						*ca = '\0';
						strcpy(ant.type_radome,&ca[1]);
						trim(ant.type_radome);
					}
					readingWhat = 1;
				}
			} else if (strncmp(&line[60],"VALID",5)==0) {
				if (readingWhat==0) { // Satellite Antenna
					getstr(aux,line,2,4);
					tm.tm_year = atoi(aux)-1900;
					getstr(aux,line,10,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,line,16,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,line,22,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,line,28,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,line,33,10);
					tm.tm_sec  = atoi(aux);
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
				getstr(aux,line,2,6);
				if (readingWhat==0) { // Satellite Antenna
					sat.dazi=atof(aux);
				} else if (readingWhat==1) { // Receiver Antenna
					ant.dazi=atof(aux);
				}
			} else if (strncmp(&line[60],"ZEN1 / ZEN2 / DZEN",18)==0) {
				getstr(aux,line,2,6);
				if (readingWhat==0) { // Satellite Antenna
					sat.zen1=sat.azi1=atof(aux);
					getstr(aux,line,8,6);
					sat.zen2=sat.azi2=atof(aux);
					getstr(aux,line,14,6);
					sat.dzen=atof(aux);
					sat.nzen=numSteps(sat.zen1,sat.zen2,sat.dzen);
					//Allocate memory for non azimuth corrections
					sat.noazi=malloc(sizeof(double*)*MAX_GNSS);
					for(i=0;i<MAX_GNSS;i++) {
						sat.noazi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
						for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
							sat.noazi[i][j]=malloc(sizeof(double)*sat.nzen);
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
									sat.azi[i][j][k]=malloc(sizeof(double)*sat.nzen);
								}
							}
						}
					}
				} else if (readingWhat==1) { // Receiver Antenna
					ant.zen1=ant.azi1=atof(aux);
					getstr(aux,line,8,6);
					ant.zen2=ant.azi2=atof(aux);
					getstr(aux,line,14,6);
					ant.dzen=atof(aux);
					ant.nzen=numSteps(ant.zen1,ant.zen2,ant.dzen);
					//Allocate memory for non azimuth corrections
					ant.noazi=malloc(sizeof(double*)*MAX_GNSS);
					for(i=0;i<MAX_GNSS;i++) {
						ant.noazi[i]=malloc(sizeof(double*)*MAX_FREQUENCIES_PER_GNSS);
						for(j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
							ant.noazi[i][j]=malloc(sizeof(double)*ant.nzen);
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
									ant.azi[i][j][k]=malloc(sizeof(double)*ant.nzen);
								}
							}
						}
					}
				}
			} else if (strncmp(&line[60],"START OF FREQUENCY",18)==0) {
				getstr(aux,line,4,2);
				freqInd = atoi(aux);
				getstr(aux,line,3,1);
				system=gnsschar2gnsstype(aux[0]);
			} else if (strncmp(&line[60],"NORTH / EAST / UP",17)==0) {
				/*if(system!=GPS) {
					//NORTH / EAST / UP is stored in single constellations, so data different from GPS has to be skipped!!!!!
					getL(line,&len,fd); //Skip NOAZI data
					if( (readingWhat==0 && sat.dazi>0) || (readingWhat==1 && ant.dazi>0) ) {
						for(i=0;i<sat.numazi;i++) {
							getL(line,&len,fd); //Skip AZI data if available
						}
					}
					continue;
				}*/
				for (i=0;i<3;i++) {
					getstr(aux,line,i*10,10);
					if (readingWhat==0) { // Satellite Antenna
						sat.PCO[freqInd][i] = atof(aux)/1e3; // (ANTEX in mm)
					} else if (readingWhat==1) { // Receiver Antenna
						ant.PCO[system][freqInd][i] = atof(aux)/1e3; // (ANTEX in mm)
					}
				}
				//Read non azimuth corrections
				if(getL(line,&len,fd)!=-1) {
					if (strncmp(&line[3],"NOAZI",5)==0) {
						if (readingWhat==0) { // Satellite Antenna
							for(i=0;i<sat.nzen;i++) {
								getstr(aux,line,8+8*i,8);
								sat.noazi[system][freqInd][i]=atof(aux)/1e3;  // (ANTEX in mm)
							}
						} else if (readingWhat==1) { // Receiver Antenna
							for(i=0;i<ant.nzen;i++) {
								getstr(aux,line,8+8*i,8);
								ant.noazi[system][freqInd][i]=atof(aux)/1e3;  // (ANTEX in mm)
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
									getstr(aux,line,8+8*j,8);
									sat.azi[system][freqInd][i][j]=atof(aux)/1e3;  // (ANTEX in mm)
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
									getstr(aux,line,8+8*j,8);
									ant.azi[system][freqInd][i][j]=atof(aux)/1e3;  // (ANTEX in mm)
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
					constellation->numSatellites ++;
					constellation->sat = realloc(constellation->sat,sizeof(TConstellationElement)*constellation->numSatellites);
						
					// Store satellite
					memcpy(&constellation->sat[constellation->numSatellites-1],&sat,sizeof(TConstellationElement));

				} else if (readingWhat==1) { // Receiver Antenna
					// Allocate memory
					antennaList->numAnt ++;
					antennaList->ant = realloc(antennaList->ant,sizeof(TAntenna)*antennaList->numAnt);
					
					// Store antenna
					memcpy(&antennaList->ant[antennaList->numAnt-1],&ant,sizeof(TAntenna));
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
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => File open and properly read
 *                                         0  => File open and failed to read
 *                                         -1 => File not open
 *****************************************************************************/
int readAntexFile (char *filename, TConstellation *constellation, TAntennaList *antennaList) {
	FILE	*fd;
	int		ret;
	
	if (whatFileTypeIs(filename)!=ftANTEX) return 0;
	
	if ((fd = fopen(filename,"rb"))) {
		ret = readAntex (fd, constellation, antennaList);
		fclose(fd);
		return ret;
	} else {
		// File do not exist
		return -1;
	}
}

/*****************************************************************************
 * Name        : readDCB
 * Description : Read a DCB file from a file descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  File descriptor
 * TDCBdata  *DCB                  O  N/A  Structure to save the DCB data
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => Properly read
 *                                          0 => Error
 *                                         -2 => First header line not recognized
 *****************************************************************************/
int readDCB (FILE *fd, TDCBdata *DCB) {
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
	
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	tm.tm_mday = 1;
	
	while(getL(line,&len,fd)!=-1) {
		if (readingHeader) {
			if ((pt=strstr(line,"YEAR-MONTH"))!=NULL) {
				// CODE'S MONTHLY GPS P1-C1 DCB SOLUTION, YEAR-MONTH 10-01          04-FEB-10 20:11
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 11; // Pointing to '10-01 [...]'
				getstr(aux,pt,0,2);
				tm.tm_year = atoi(aux);
				if (tm.tm_year <= 70) tm.tm_year += 100;
				getstr(aux,pt,3,2);
				tm.tm_mon = atoi(aux) - 1;
				DCB->block[DCB->n-1].startTime.MJDN = MJDN(&tm);
				tm.tm_mon ++;
				DCB->block[DCB->n-1].endTime.MJDN = MJDN(&tm);

			} else if ((pt=strstr(line,"YEAR "))!=NULL) { //From 1 January 2012 the date format has been changed in the DCB header
				// CODE'S MONTHLY GPS P1-C1 DCB SOLUTION, YEAR 2014, MONTH 05       04-JUN-14 07:46
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 5; // Pointing to year number
				getstr(aux,pt,0,4);
				tm.tm_year = atoi(aux) -1900;
				pt += 12; // Pointing to month number
				getstr(aux,pt,0,2);
				tm.tm_mon = atoi(aux) - 1;
				DCB->block[DCB->n-1].startTime.MJDN = MJDN(&tm);
				tm.tm_mon ++;
				DCB->block[DCB->n-1].endTime.MJDN = MJDN(&tm);

			} else if ((pt=strstr(line,"ENDING DAY"))!=NULL) { //From somewhere around 2017 the date format has been changed in the DCB header
				// CODE'S 30-DAY GPS P1-C1 DCB SOLUTION, ENDING DAY 306, 2017       06-NOV-17 06:45
				firstLineHeaderFound=1;
				DCB->n++;
				pt += 11; // Pointing to doy
				getstr(aux,pt,0,3);
				doy=atoi(aux);
				pt += 5; // Pointing to year
				getstr(aux,pt,0,4);
				year=atoi(aux);
				DCB->block[DCB->n-1].endTime.MJDN = yeardoy2MJDN(year,doy,0);
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
					factor = 1.0/(1.0-(GPSf1*GPSf1)/(GPSf2*GPSf2)); // 1/(1-f1^2/f2^2)
					if (DCB->block[DCB->n-1].measFrom==C2P) factor*= -1.0;
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
			getstr(aux,line,1,2);
			PRN = atoi(aux);
			if (PRN != 0) { // Satellite unidentified or blank line
				properlyRead = 1;
				getstr(aux,line,26,9);
				value = atof(aux);
				getstr(aux,line,38,9);
				rms = atof(aux);
				// From ns to meters
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
 * Description : Read a DCB file from a filename
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *filename                 I  N/A  Name of the file
 * TDCBdata  *DCB                  O  N/A  Structure to save the DCB data
 * Returned value (int)            O  N/A  Status of the function
 *                                          1 => File open and properly read
 *                                          0 => File open and failed to read
 *                                         -1 => File not open
 *                                         -2 => First header line not recognized
 *****************************************************************************/
int readDCBFile (char *filename, TDCBdata *DCB) {
	FILE		*fd;
	int 		ret;
	enum fileType	ft;
	
  ft = whatFileTypeIs(filename);

	if (ft!=ftP1C1DCB && ft!=ftP1P2DCB) return 0;

	if ((fd = fopen(filename,"rb"))) {
		ret = readDCB (fd, DCB);
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
			getstr(aux,line,0,20);
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
				getstr(aux,line,7,3);
				if (strcmp(aux,"STA")==0) { // It is a station
					properlyRead = 1; // Any station has been found
					getstr(aux,line,14,4);
					if (strcmp(prevName,aux)!=0) { // New station
						auxN++;
						strcpy(stationList->station[auxN-1].name,aux);
						strcpy(prevName,aux);
					}
					getstr(aux,line,46,23);
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

		initialized=1;
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
		if (feof(fd)>0) {
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
	char           	*lineaux[10];	//String to save previous line until a full message has been read
	char           	aux[100];
	char			hexstring[300];
	char			binarystring[2400];
	int            	len = 0;
	int            	error = 0;
	static int     	properlyRead = 0;
	static int     	readingHeader = 1;
	static int		writingHeader = 1;
	int				GEOpos;
	int				GEOPRN;
	int				freeblock=1;
	int				numberofdatalines;
	int				numberofcolumns;
	int				numberofbadmessages=0;
	int            	i,m;
	int				decoderesult = 1;
	int				convergencetime;
	double			timediff;
	double         	seconds;
	int				numMsgLost;
	int            	row=0;
	int				endmessage=0;
	int 			decodedmessagetype=0;
	int				messagesmissing=0;
	//int			reachedcurrentepoch=-1;
	int				MessageAheadCurrentEpoch=0;
	static int		firstdatalineMJDN=-1;
	static int		totalmsgmissing=0;
	static int		nummsgmissingdetected=0;
	static int		numfilelines=0;
	static int		*numlinesmissing=NULL;
	static int		*missingmessagesvector=NULL;
	static int		writefiles=0;
	static int		prevnumMsgMissing[MAX_SBAS_PRN];
	struct tm    	tm;
	static int		prevmsgtimeMJDN[MAX_SBAS_PRN];
	static int		MsgMissingCleared[MAX_SBAS_PRN];
	static int		msgtimeMJDN[MAX_SBAS_PRN];
	static double	prevmsgtimeSoD[MAX_SBAS_PRN];
	static double	msgtimeSoD[MAX_SBAS_PRN];
	static int		initialized=0;
	TTime			msgtime,prevmsgtime;
	TSBASblock  	*sbasblock;
	double			CurrentPos;
	struct stat 	filestat;	//This is to get the file size
	double			filesize;
	double			CurrentPercentage;
	double			PreviousPercentage=-1;

	if(initialized==0) {
		initialized=1;
		for(i=0;i<MAX_SBAS_PRN;i++) {
			prevmsgtimeMJDN[i]=msgtimeMJDN[i]=-1;
			prevmsgtimeSoD[i]=msgtimeSoD[i]=-1;
			MsgMissingCleared[i]=0;
			prevnumMsgMissing[i]=0;
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
					fflush(options->terminalStream);
				#endif
			}
		}
	}

	sbasblock=NULL;

	//Initialize lineaux
	for(i=0;i<10;i++) {
		lineaux[i]=malloc(sizeof(char)*MAX_INPUT_LINE);
		lineaux[i][0]='\0';
	}


	while(getL(line,&len,fd)!=-1) {
		numfilelines++;
		CurrentPos += (double)len;
		if(line[0]=='\n' || line[0]=='\r') continue;	//Skip blank lines

		//Alloc memory only when TSBASblock has been freed (once every time a message has been read)
		if(freeblock==1) {
			sbasblock=malloc(sizeof(TSBASblock));	//sbasblock is declared as pointer, so at each loop sbasblock structure is freed and allocated again,
													//so each sbasblock for each message will only occupy the necessary memory
			initSBASblock (sbasblock);
		}

		if (readingHeader) {
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,0,9);
				*rinexVersion = atof(aux);
				if ((int)*rinexVersion>2) {return 0;} 		//Version check
			} else if (strncmp(&line[60],"REC INDEX/TYPE/VERS",19)==0) {
				SBASdatabox->SBASdata[0].numreceivers=SBASdatabox->SBASdata[0].numreceivers+1;	//Number of receivers
			} else if (strncmp(&line[60],"END OF HEADER",13)==0) {
				readingHeader = 0;
				properlyRead = 1;
				//If we are going to process data, the first call to this function will be just for opening files and reading header
				if(currentepoch->MJDN==-1 && options->onlyconvertSBAS==0 && options->onlySBASplots==0) {
					for(i=0;i<10;i++) {
						free(lineaux[i]);
						lineaux[i]=NULL;
					}
					free(sbasblock);
					sbasblock=NULL;
					return 1;
				}
			}
		} else {
			//Check first if there is another header line. Skip new header lines
			//If a RINEXB, EMS or Pegasus file is being written, header will just be written once
			if (strncmp(&line[60],"RINEX VERSION / TYPE",20)==0) {
				getstr(aux,line,0,9);
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

					//Check if message is from L1. If not, ignore it (to be changed when updating to SBAS v3)
					//If no frequency given, assume its from L1
					if (len>=45) {
						getstr(aux,line,26,1);
						if(atoi(aux)!=1) {
							//Skip the two following lines of the current message
							if (getL(line,&len,fd)==-1) return -1;
							if (getL(line,&len,fd)==-1) return -1;
							continue;	
						}
					}

					getstr(aux,line,0,3);
					sbasblock->PRN = atoi(aux);		//PRN
					getstr(aux,line,4,2);
					tm.tm_year = atoi(aux);			//Year
					if (tm.tm_year <= 70) tm.tm_year += 100;
					getstr(aux,line,7,2);
					tm.tm_mon  = atoi(aux)-1;		//Month
					getstr(aux,line,10,2);
					tm.tm_mday = atoi(aux);			//Day
					getstr(aux,line,13,2);
					tm.tm_hour = atoi(aux);			//Hour
					getstr(aux,line,16,2);
					tm.tm_min  = atoi(aux);			//Minute
					getstr(aux,line,18,5);
					tm.tm_sec  = atoi(aux);       		//Seconds,in time of reception of first bit 
					seconds=atof(aux);

					sbasblock->t.MJDN = MJDN(&tm);
					sbasblock->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds +1.;	//Seconds in time of applicability (1 second later)

					//Check if RINEXB has the 0.1 second due to flight time. If it isn't, add it
					if ((double)((int)(sbasblock->t.SoD))==sbasblock->t.SoD) {
						sbasblock->t.SoD+=.1;
					}

					if(sbasblock->t.SoD>=86400.) {
						//After adding 1 one second, we have gone to the next day
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
						if (options->onlySBASplots==1) {
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

					if (sbasblock->t.MJDN>currentepoch->MJDN || (currentepoch->MJDN==sbasblock->t.MJDN && (sbasblock->t.SoD-currentepoch->SoD)>1E-4)) {
						//The time of applicability of the current message is ahead of the current epoch.
						MessageAheadCurrentEpoch=1;
					}

					//Save current and previous message time of messages to check time between them (only if the GEO is not unselected)
					if(options->GEOPRNunsel[sbasblock->PRN]==0) {

						if(currentepoch->MJDN>=0) {
							//Only check missed messages if we are not only converting SBAS files
							if (MessageAheadCurrentEpoch==0) {
								//Only update previous message epoch if current message read is usable
								prevmsgtimeMJDN[0]=msgtimeMJDN[0];
								prevmsgtimeSoD[0]=msgtimeSoD[0];
								prevmsgtimeMJDN[sbasblock->PRN]=msgtimeMJDN[sbasblock->PRN];
								prevmsgtimeSoD[sbasblock->PRN]=msgtimeSoD[sbasblock->PRN];
							

								msgtimeMJDN[0]=sbasblock->t.MJDN;
								msgtimeSoD[0]=sbasblock->t.SoD;
								msgtimeMJDN[sbasblock->PRN]=sbasblock->t.MJDN;
								msgtimeSoD[sbasblock->PRN]=sbasblock->t.SoD;
							
								//Check time between current epoch and last message received for all GEO
								msgtime.MJDN=msgtimeMJDN[0];
								msgtime.SoD=msgtimeSoD[0];
								prevmsgtime.MJDN=prevmsgtimeMJDN[0];
								prevmsgtime.SoD=prevmsgtimeSoD[0];

								numMsgLost=(int)(tdiff(&msgtime,&prevmsgtime)+.00005)-1;

								if(numMsgLost>=1 && prevmsgtime.MJDN!=-1) {
									//SBAS messages are sent every second. If there is no data to send, we will receive type 62 or 63 messages to provide continuity of signal
									SBASdatabox->SBASdata[0].missed4msg[0]=SBASdatabox->SBASdata[0].missed4msg[0]+numMsgLost;
									if (SBASdatabox->SBASdata[0].missed4msg[0]>=4 && MsgMissingCleared[0]==0) {
										//More than 4 messages missed and we have not cleared data
										SBASMissingMessageClearData(0,SBASdatabox->SBASdata);
										MsgMissingCleared[0]=1;
									}
								} else {
									//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
									SBASdatabox->SBASdata[0].missed4msg[0]=0;
									MsgMissingCleared[0]=0;
								}

								//Check time between current epoch and last message received for current GEO
								msgtime.MJDN=msgtimeMJDN[sbasblock->PRN];
								msgtime.SoD=msgtimeSoD[sbasblock->PRN];
								prevmsgtime.MJDN=prevmsgtimeMJDN[sbasblock->PRN];
								prevmsgtime.SoD=prevmsgtimeSoD[sbasblock->PRN];
								numMsgLost=(int)(tdiff(&msgtime,&prevmsgtime)+.00005)-1;
								if(numMsgLost>=1 && prevmsgtime.MJDN!=-1) {
									if ( (tdiff(currentepoch,&msgtime)-.9)>1E-4) {
										SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]=SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]+numMsgLost-prevnumMsgMissing[sbasblock->PRN];
										//Print Info message when a SBAS message is missing, except when last message received is
										//the last one we have to read for the current epoch, due to this message will be shown
										//in the missing message check at the end of this function.
										//It has to be considered that this check of missing messages is for the case when for example, the observation file
										//has a data rate of 30 seconds, and there has been a data gap in between this 30 seconds
										if (options->workMode == wmDOPROCESSING) {
											if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]==1) {
												sprintf(messagestr,"SBAS message missing for GEO PRN %3d at epoch %17s (1 missing message)",sbasblock->PRN,t2doystr(&msgtime));
											} else if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>1) {
												sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",sbasblock->PRN,t2doystr(&msgtime),SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]);
											}
											printInfo(messagestr,options);
										}
										//The prevnumMsgMissing is just for the case when there are several messages missing between epochs (typically for 30s second rate files)
										//In this case, when computing the number of messages missed, after reaching the previous epoch and entering this function again, the first
										//message read vs the last one will be the hole gap (for example 21 messages missing), but the first 20 were alredy counted on the previous call
										//to this function, so they will be counted twice. prevnumMsgMissing variable stores the last number of messages missing 
										prevnumMsgMissing[sbasblock->PRN]=0;
									}
									if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>=4 && MsgMissingCleared[sbasblock->PRN]==0) {
										//More than 4 messages missed and we have not cleared data
										if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) { //This is for the case that all received messages were wrong, so no data was saved
											SBASMissingMessageClearData(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],SBASdatabox->SBASdata);
										}
										MsgMissingCleared[sbasblock->PRN]=1;
									}
								}
								//If we had a gap greater than 4 messages, set first message received to current message epoch minus 1 minute. 
								//This is to set the GEO in acqusition time (except for the current GEO, so the condition of acquisition does not block switching GEO)
								if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>=4) {
									GEOpos=SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN];
									if (options->GEOindex>=0 && options->GEOindex!=GEOpos) {
										memcpy(&SBASdatabox->SBASdata[GEOpos].firstmessage,&sbasblock->t,sizeof(TTime));
										tdadd(&SBASdatabox->SBASdata[GEOpos].firstmessage,-60.);
									}
								}
								//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
								SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]=0;
								MsgMissingCleared[sbasblock->PRN]=0;
								
							} //End if (MessageAheadCurrentEpoch==0)
						}//End if(currentepoch->MJDN>=0) 
					} //End if(options->GEOPRNunsel[sbasblock->PRN]==0)


					if(currentepoch->MJDN>=0) {
						//If it is not -1, means that we read until we reach the current epoch
						if(MessageAheadCurrentEpoch==1) {
							//The time of applicability of the current message is ahead of the current epoch.
							//The following commented lines were to check if file was from previous day or next day, but this check is not used
							/*if(firstdatalineMJDN>currentepoch->MJDN) {
								//The first line of the file is from days ahead of the observation one. We have no data for the current day
								reachedcurrentepoch=0;
							} else if(tdiff(&sbasblock->t,currentepoch)>=86400.0) {
								//The message read is more than one day ahead, so we have no data for the current day
								reachedcurrentepoch=0;
							} else {
								reachedcurrentepoch=1;
							}*/
							//Stop reading, go one line back (if we have not reached end of file) and exit function
							if(feof(fd)==0) {
								getLback(line,&len,fd);
							}
							free(sbasblock);
							sbasblock=NULL;
							break;
						}
					}

					//Some RINEX-B files do not provide the frequency, datalength, receiverindex and source identifier,
					//even though the RINEX-B standard states it
					if (len>=45) {
						getstr(aux,line,26,1);
						sbasblock->frequency=atoi(aux);				//Frequency number
						getstr(aux,line,30,3);
						sbasblock->datalength=atoi(aux);			//Data message length 
						getstr(aux,line,36,3);
						sbasblock->receiverindex=atoi(aux);			//Receiver index
						getstr(aux,line,42,3);
						strcpy(sbasblock->sourceidentifier,aux); 	//Source identifier
					}

					//Compute the number of data lines (there are 18 bytes of message per line)
					numberofdatalines=(int)sbasblock->datalength/18;
					if(sbasblock->datalength%18!=0) numberofdatalines++;

					row++;
					endmessage=0;
					freeblock=0;
				} else {
					if (row==1) {
						getstr(aux,line,1,2);
						sbasblock->messagetype=atoi(aux);	//Message type
					}

					//Compute the number of records (columns) in the current line (normally the last one is not full)
					if(row==numberofdatalines) {
						numberofcolumns=sbasblock->datalength%18;
					} else {
						numberofcolumns=18;
					}

					//Read data
					for(i=0;i<numberofcolumns;i++) {
						getstr(&hexstring[18*2*(row-1)+2*i],line,7+3*i,2);
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
									fflush(options->terminalStream);
								} else {
									//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
									if ((int)CurrentPercentage!=(int)PreviousPercentage) {
										fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
										fflush(options->terminalStream);
									}
								}
								PreviousPercentage=CurrentPercentage;
							}
						}
						//Convert the hexadecimal string to a binary string (1 bit per byte)
						strhextostrbin(hexstring,binarystring);

						//Decode message
						decoderesult=readSBASmessage(binarystring,sbasblock->messagetype,&decodedmessagetype,sbasblock,&messagesmissing,options);
						if(messagesmissing!=0) {
							//Increase counter for missing messages
							totalmsgmissing+=messagesmissing;
							nummsgmissingdetected++;
							//Increase size of vectors for logging missed messages
							numlinesmissing=realloc(numlinesmissing,sizeof(int)*nummsgmissingdetected);
							missingmessagesvector=realloc(missingmessagesvector,sizeof(int)*nummsgmissingdetected);
							//Save the line where missing message has been detected and what number has been lost
							numlinesmissing[nummsgmissingdetected-1]=numfilelines-2;
							missingmessagesvector[nummsgmissingdetected-1]=messagesmissing;
						}

						if(decoderesult<0) {
							//Error decoding message. Update failed messages only if GEO is not unselected
							numberofbadmessages++;	
							if(options->GEOPRNunsel[sbasblock->PRN]==0) {
								SBASdatabox->SBASdata[0].failedmessages[0]=SBASdatabox->SBASdata[0].failedmessages[0]+1;
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]=SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]+1;
							}
							//Print Info message when a SBAS message is missing only for GEO in use
							if (currentepoch->MJDN>=0) {
								if (options->workMode == wmDOPROCESSING) {
									if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]==1) {
										sprintf(messagestr,"Invalid SBAS message for GEO PRN %3d at epoch %17s (1 invalid message)",sbasblock->PRN,t2doystr(&msgtime));
									} else {
										sprintf(messagestr,"Invalid SBAS messages for GEO PRN %3d at epoch %17s (%d consecutive invalid messages)",sbasblock->PRN,t2doystr(&msgtime),SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]);
									}								
									printInfo(messagestr,options);
								}
								//When 4 consecutive invalid messages arrive, the GEO has to be disabled for ranging and all fast corrections must timeout
								if (SBASdatabox->SBASdata[0].failedmessages[0]==4) {
									SBASErrorMessageTimeoutFastCorr(0,currentepoch,SBASdatabox->SBASdata,options);
								}
								if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]==4) {
									if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
										SBASErrorMessageTimeoutFastCorr(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],currentepoch,SBASdatabox->SBASdata,options);
									}
								}
							}
						} else if(currentepoch->MJDN>=0){
							//Message decoded correctly. Update SBAS data only if we are processing data and the GEO is not unselected
							if(options->GEOPRNunsel[sbasblock->PRN]==0) {
								SBASdatabox->SBASdata[0].failedmessages[0]=0;
								SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]=0;
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

								updateSBASdata(SBASdatabox->SBASdata,sbasblock,*currentepoch,messagesmissing,options);
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
			if(writingHeader==1) strcpy(lineaux[row],line);
			else if (endmessage==1) strcpy(lineaux[numberofdatalines],line); //We cannot use row here because when finishing a message row value is set back to 0
			else strcpy(lineaux[row-1],line);

			//Call function to write to files. It must be called only when we are writing header lines or when we have read a full message
			if(writingHeader==1) {
				writeSBASfiles(fdlist, fd, filelist, lineaux, 1, writingHeader, 0, decoderesult, decodedmessagetype, prevday, sbasblock, options);
			} else if (endmessage==1) {
				writeSBASfiles(fdlist, fd, filelist, lineaux, numberofdatalines+1, writingHeader, 0, decoderesult, decodedmessagetype, prevday, sbasblock, options);

			}

			if(readingHeader==0) writingHeader=0;	

		}

		if(freeblock==1) {	//Free sbasblock only when necessary
			if (decoderesult>0 || decoderesult<-3) {
				//Only free sbasblock messagetype memory if we have allocated memory
				freeSBASblock(sbasblock->messagetype,sbasblock,options);
			}

			//Handle special events if it is not the current epoch of the RINEX observation file
			if(currentepoch->MJDN>=0 && tdiff(currentepoch,&sbasblock->t)>1.) {
				SBAShandlespecialevents(*currentepoch,SBASdatabox->SBASdata,options);
			}

			free(sbasblock);
			sbasblock=NULL;

		}
	} //End while getLine

    //Check for missing messages or error messages in all GEOs 
    //It can occur the case that we have not received any message for a tracked  PRN in the current interval read,
    //therefore it is necessary to check if there has been a data gap
    for(m=1;m<=SBASdatabox->SBASdata[0].numSBASsatellites;m++) {
        //Only check satellites that have not been cleared
        GEOPRN=SBASdatabox->SBASdata[m].PRN;
		msgtime.MJDN=msgtimeMJDN[GEOPRN];
		msgtime.SoD=msgtimeSoD[GEOPRN];
		timediff=tdiff(currentepoch,&msgtime);
		numMsgLost=0;
		if (timediff>=1.) {
			numMsgLost=(int)(timediff);
		}
		//The numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[GEOPRN] is to avoid printing the missing message due when we read the first message after a gap,
		//the prevmsgtime has not still been updated until the next message read
        if (prevmsgtime.MJDN!=-1 && numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[GEOPRN]) {
            SBASdatabox->SBASdata[0].missed4msg[GEOPRN]=numMsgLost;
            if(numMsgLost>=4) {
                //Print Info message when a SBAS message is missing only for GEO in use
				if (options->workMode == wmDOPROCESSING) {
               		sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",GEOPRN,t2doystr(currentepoch),numMsgLost);
            	    printInfo(messagestr,options);
				}
                if (MsgMissingCleared[GEOPRN]==0) {
                    SBASMissingMessageClearData(m,SBASdatabox->SBASdata);
                    MsgMissingCleared[GEOPRN]=1;
                }
				prevnumMsgMissing[GEOPRN]=numMsgLost;
            } else if(numMsgLost>=2) {
				if (options->workMode == wmDOPROCESSING) {
                	sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",GEOPRN,t2doystr(currentepoch),numMsgLost);
	                printInfo(messagestr,options);
				}
				prevnumMsgMissing[GEOPRN]=numMsgLost;
            } else if(numMsgLost==1) {
				if (options->workMode == wmDOPROCESSING) {
                	sprintf(messagestr,"SBAS message missing for GEO PRN %3d at epoch %17s (1 missing message)",GEOPRN,t2doystr(currentepoch));
	                printInfo(messagestr,options);
				}
				prevnumMsgMissing[GEOPRN]=numMsgLost;
			} else {
				prevnumMsgMissing[GEOPRN]=0;
            }
        }
    }

	if(feof(fd)>0) {
		//Print message decoding summary
		if(writefiles) {
			writeSBASdecodesummary(fdlist, fd, filelist[fdLOGFILE], numberofbadmessages, totalmsgmissing, nummsgmissingdetected, numlinesmissing, missingmessagesvector, options);
		}
	} 

	//Free memory
	for(i=0;i<10;i++) {
		free(lineaux[i]);
		lineaux[i]=NULL;
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
 *                                         1  => Properly read
 *                                         0  => Error
 *                                         -2 => Reached end of file before
 *                                               getting to current epoch
 *****************************************************************************/
int readEMS (FILE *fd, FILE **fdlist, char **filelist, TSBASdatabox *SBASdatabox, int *prevday, TTime *currentepoch, TOptions  *options) {
	char            	line[MAX_INPUT_LINE];
	char            	*lineaux[1];   //String to save previous line until a full message has been read
	char            	aux[100];
	char            	hexstring[300];
	char            	binarystring[2400];
	int             	len = 0;
	int             	i,m;
	int					GEOpos;
	int					GEOPRN;
	int             	decoderesult = 1;
	double          	seconds;
	double				timediff;
	int					numMsgLost;
	int 				decodedmessagetype=0;
	int             	messagesmissing=0;
	//int					reachedcurrentepoch=-1;
	int					MessageAheadCurrentEpoch=0;
	int					convergencetime;
	static int			firstdatalineMJDN=-1;
	static int			totalmsgmissing=0;
	static int      	numberofbadmessages=0;
	static int			numfilelines=0;
	static int			nummsgmissingdetected=0;
	static int			*numlinesmissing=NULL;
	static int			*missingmessagesvector=NULL;
	static int         	writefiles=0;
	static int			prevnumMsgMissing[MAX_SBAS_PRN];
	struct tm       	tm;
	static int			MsgMissingCleared[MAX_SBAS_PRN];
	static int			prevmsgtimeMJDN[MAX_SBAS_PRN];
	static int			msgtimeMJDN[MAX_SBAS_PRN];
	static double		prevmsgtimeSoD[MAX_SBAS_PRN];
	static double		msgtimeSoD[MAX_SBAS_PRN];
	static int			initialized=0;
	TTime				msgtime,prevmsgtime;
	TSBASblock  	   	*sbasblock;
	double				CurrentPos;
	struct stat	 		filestat;	//This is to get the file size
	double				filesize;
	double				CurrentPercentage;
	double				PreviousPercentage=-1;


	if(initialized==0) {
		initialized=1;
		for(i=0;i<MAX_SBAS_PRN;i++) {
			prevmsgtimeMJDN[i]=msgtimeMJDN[i]=-1;
			prevmsgtimeSoD[i]=msgtimeSoD[i]=-1;
			MsgMissingCleared[i]=0;
			prevnumMsgMissing[i]=0;
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
				fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",0.0,"",options->ProgressEndCharac);
				#if defined (__WIN32__)
					//In Windows, cursor is not disabled
					fflush(options->terminalStream);
				#endif
			}
		}
	}

	sbasblock=NULL;

	//Initialize lineaux
	for(i=0;i<1;i++) {
			lineaux[i]=malloc(sizeof(char)*MAX_INPUT_LINE);
			lineaux[i][0]='\0';
	}


	while(getL(line,&len,fd)!=-1) {

		numfilelines++;
		CurrentPos += (double)len;

		if(len<88 && line[0]!='\n') return 0;	//Data line too short (and are not blank lines)
		else if (line[0]=='\n') continue;	//Skip blank lines

		sbasblock=malloc(sizeof(TSBASblock));	//sbasblock is declared as pointer, so at each loop sbasblock structure is freed and allocated again,
							//so each sbasblock for each message will only occupy the necessary memory
		initSBASblock (sbasblock);

		getstr(aux,line,0,3);
		sbasblock->PRN = atoi(aux);		//PRN
		getstr(aux,line,4,2);
		tm.tm_year = atoi(aux);			//Year
		if (tm.tm_year <= 70) tm.tm_year += 100;
		getstr(aux,line,7,2);
		tm.tm_mon  = atoi(aux)-1;		//Month
		getstr(aux,line,10,2);
		tm.tm_mday = atoi(aux);			//Day
		getstr(aux,line,13,2);
		tm.tm_hour = atoi(aux);			//Hour
		getstr(aux,line,16,2);
		tm.tm_min  = atoi(aux);			//Minute
		getstr(aux,line,19,2);
		tm.tm_sec  = atoi(aux);       	//Seconds,in time of applicability 
		seconds=atof(aux);

		sbasblock->t.MJDN = MJDN(&tm);
		sbasblock->t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds + 0.1;	//Seconds in time of applicability (0.1 seconds corresponds to travel time)

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
			if (options->onlySBASplots==1) {
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
				//Only check missed messages if we are not only converting SBAS files
				if (MessageAheadCurrentEpoch==0) {
					//Only update previous message epoch if current message read is usable
					prevmsgtimeMJDN[0]=msgtimeMJDN[0];
					prevmsgtimeSoD[0]=msgtimeSoD[0];
					prevmsgtimeMJDN[sbasblock->PRN]=msgtimeMJDN[sbasblock->PRN];
					prevmsgtimeSoD[sbasblock->PRN]=msgtimeSoD[sbasblock->PRN];

					msgtimeMJDN[0]=sbasblock->t.MJDN;
					msgtimeSoD[0]=sbasblock->t.SoD;
					msgtimeMJDN[sbasblock->PRN]=sbasblock->t.MJDN;
					msgtimeSoD[sbasblock->PRN]=sbasblock->t.SoD;
					
					//Check time between current epoch and last message received for all GEO
					msgtime.MJDN=msgtimeMJDN[0];
					msgtime.SoD=msgtimeSoD[0];
					prevmsgtime.MJDN=prevmsgtimeMJDN[0];
					prevmsgtime.SoD=prevmsgtimeSoD[0];

					numMsgLost=(int)(tdiff(&msgtime,&prevmsgtime)+.00005)-1;
					if(numMsgLost>=1 && prevmsgtime.MJDN!=-1) {
						//SBAS messages are sent every second. If there is no data to send, we will receive type 62 or 63 messages to provide continuity of signal
						SBASdatabox->SBASdata[0].missed4msg[0]=SBASdatabox->SBASdata[0].missed4msg[0]+numMsgLost;
						if (SBASdatabox->SBASdata[0].missed4msg[0]>=4 && MsgMissingCleared[0]==0) {
							//More than 4 messages missed and we have not cleared data
							SBASMissingMessageClearData(0,SBASdatabox->SBASdata);
							MsgMissingCleared[0]=1;
						}
					} else {
						//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
						SBASdatabox->SBASdata[0].missed4msg[0]=0;
						MsgMissingCleared[0]=0;
					}

					//Check time between current epoch and last message received for current GEO
					msgtime.MJDN=msgtimeMJDN[sbasblock->PRN];
					msgtime.SoD=msgtimeSoD[sbasblock->PRN];
					prevmsgtime.MJDN=prevmsgtimeMJDN[sbasblock->PRN];
					prevmsgtime.SoD=prevmsgtimeSoD[sbasblock->PRN];
					numMsgLost=(int)(tdiff(&msgtime,&prevmsgtime)+.00005)-1;
					if(numMsgLost>=1 && prevmsgtime.MJDN!=-1) {
						if ( (tdiff(currentepoch,&msgtime)-.9)>1E-4) {
							SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]=SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]+numMsgLost-prevnumMsgMissing[sbasblock->PRN];
							//Print Info message when a SBAS message is missing, except when last message received is
							//the last one we have to read for the current epoch, due to this message will be shown
							//in the missing message check at the end of this function.
							//It has to be considered that this check of missing messages is for the case when for example, the observation file
							//has a data rate of 30 seconds, and there has been a data gap in between this 30 seconds
							if (options->workMode == wmDOPROCESSING) {
								if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]==1) {
									sprintf(messagestr,"SBAS message missing for GEO PRN %3d at epoch %17s (1 missing message)",sbasblock->PRN,t2doystr(&msgtime));
								} else if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>1) {
									sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",sbasblock->PRN,t2doystr(&msgtime),SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]);
								}
								printInfo(messagestr,options);
							}
							//The prevnumMsgMissing is just for the case when there are several messages missing between epochs (typically for 30s second rate files)
							//In this case, when computing the number of messages missed, after reaching the previous epoch and entering this function again, the first
							//message read vs the last one will be the hole gap (for example 21 messages missing), but the first 20 were alredy counted on the previous call
							//to this function, so they will be counted twice. prevnumMsgMissing variable stores the last number of messages missing 
							prevnumMsgMissing[sbasblock->PRN]=0;
						}
						if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>=4 && MsgMissingCleared[sbasblock->PRN]==0) {
							//More than 4 messages missed and we have not cleared data
							if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
								SBASMissingMessageClearData(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],SBASdatabox->SBASdata);
							}
							MsgMissingCleared[sbasblock->PRN]=1;
						}
					}
					//If we had a gap greater than 4 messages, set first message received to current message epoch minus 1 minute. 
					//This is to set the GEO in acqusition time (except for the current GEO, so the condition of acquisition does not block switching GEO)
					if (SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]>=4) {
						GEOpos=SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN];
						if (options->GEOindex>=0 && options->GEOindex!=GEOpos) {
							memcpy(&SBASdatabox->SBASdata[GEOpos].firstmessage,&sbasblock->t,sizeof(TTime));
							tdadd(&SBASdatabox->SBASdata[GEOpos].firstmessage,-60.);
						}
					}
					//A new message has been received. Reset the and missed4msg counter and MsgMissingCleared flag
					SBASdatabox->SBASdata[0].missed4msg[sbasblock->PRN]=0;
					MsgMissingCleared[sbasblock->PRN]=0;
					prevnumMsgMissing[sbasblock->PRN]=0;

				} //End if (MessageAheadCurrentEpoch==0)
			}//End if(currentepoch->MJDN>=0) 
		} //End if(options->GEOPRNunsel[sbasblock->PRN]==0)

		if(currentepoch->MJDN>=0) {
			//If it is not -1, means that we have to read until we reach the current epoch
			//if(sbasblock->t.MJDN>currentepoch->MJDN || (currentepoch->MJDN==sbasblock->t.MJDN && sbasblock->t.SoD>currentepoch->SoD)  ) {
			if(MessageAheadCurrentEpoch==1) {
				//The time of applicability of the current message is ahead of the current epoch.
				//The following commented lines were to check if file was from previous day or next day, but this check is not used
				/*if(firstdatalineMJDN>currentepoch->MJDN) {
					//The first line of the file is from days ahead of the observation one. We have no data for the current day
					reachedcurrentepoch=0;
				} else if(tdiff(&sbasblock->t,currentepoch)>=86400.0) {
					//The message read is more than one day ahead, so we have no data for the current day
					reachedcurrentepoch=0;
				} else {
					reachedcurrentepoch=1;
				}*/
				//Stop reading, go one line back (if we have not reached end of file) and exit function
				if(feof(fd)==0) {
					getLback(line,&len,fd);
				}
				free(sbasblock);
				sbasblock=NULL;
				break;
			}
		}

		if (printProgressConvert==1) {
			CurrentPercentage=100.*CurrentPos/filesize;
			if ((CurrentPercentage-PreviousPercentage)>=0.1) { //This is to avoid to many prints when percentages changed less than 0.1
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
					//In Windows, cursor is not disabled
					fflush(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Percentage converted: %5.1f%%%10s%c",CurrentPercentage,"",options->ProgressEndCharac);
						fflush(options->terminalStream);
					}
				}
				PreviousPercentage=CurrentPercentage;
			}
		}

		getstr(aux,line,22,2);
		sbasblock->messagetype=atoi(aux);	//Message type

		//Hexadecimal message
		if(sbasblock->messagetype<10) {	
			getstr(hexstring,line,24,64);	
		} else {
			getstr(hexstring,line,25,64);
		}

		//Convert the hexadecimal string to a binary string (1 bit per byte)
		strhextostrbin(hexstring,binarystring);

		//Decode message
		decoderesult=readSBASmessage(binarystring,sbasblock->messagetype,&decodedmessagetype,sbasblock,&messagesmissing,options);
		if(messagesmissing!=0) {
			//Increase counter for missing messages
			totalmsgmissing+=messagesmissing;
			nummsgmissingdetected++;
			//Increase size of vectors for logging missed messages
			numlinesmissing=realloc(numlinesmissing,sizeof(int)*nummsgmissingdetected);
			missingmessagesvector=realloc(missingmessagesvector,sizeof(int)*nummsgmissingdetected);
			//Save the line where missing message has been detected and what number has been lost
			numlinesmissing[nummsgmissingdetected-1]=numfilelines;
			missingmessagesvector[nummsgmissingdetected-1]=messagesmissing;
		}					

		if(decoderesult<0) {
			//Error decoding message. Update failed messages only if GEO is not unselected
			numberofbadmessages++;
			if(options->GEOPRNunsel[sbasblock->PRN]==0) {
				SBASdatabox->SBASdata[0].failedmessages[0]=SBASdatabox->SBASdata[0].failedmessages[0]+1; //failed messages for all GEO
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]=SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]+1; //failed messages for a single GEO
			}
			//Print Info message when a SBAS message is missing only for GEO in use
			if (currentepoch->MJDN>=0) {
				if (options->workMode == wmDOPROCESSING) {
					if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]==1) {
						sprintf(messagestr,"Invalid SBAS message for GEO PRN %3d at epoch %17s (1 invalid message)",sbasblock->PRN,t2doystr(&msgtime));
					} else {
						sprintf(messagestr,"Invalid SBAS messages for GEO PRN %3d at epoch %17s (%d consecutive invalid messages)",sbasblock->PRN,t2doystr(&msgtime),SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]);
					}
					printInfo(messagestr,options);
				}
				//When 4 consecutive invalid messages arrive, the GEO has to be disabled for ranging and all fast corrections must timeout
				if (SBASdatabox->SBASdata[0].failedmessages[0]==4) {
					SBASErrorMessageTimeoutFastCorr(0,currentepoch,SBASdatabox->SBASdata,options);
				}
				if (SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]==4) {
					if (SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN]!=-1) {//This is for the case that all received messages were wrong, so no data was saved
						SBASErrorMessageTimeoutFastCorr(SBASdatabox->SBASdata[0].GEOPRN2pos[sbasblock->PRN],currentepoch,SBASdatabox->SBASdata,options);
					}
				}
			}
		} else if(currentepoch->MJDN>=0){
			//Message decoded correctly. Update SBAS data only if we are processing data and the GEO is not unselected
			if(options->GEOPRNunsel[sbasblock->PRN]==0) {
				SBASdatabox->SBASdata[0].failedmessages[0]=0;
				SBASdatabox->SBASdata[0].failedmessages[sbasblock->PRN]=0;
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
				
				updateSBASdata(SBASdatabox->SBASdata,sbasblock,*currentepoch,messagesmissing,options);
			}
		}


		if(writefiles) {
			//Copy current line to buffer
			strcpy(lineaux[0],line);
			//Write message to file
			writeSBASfiles(fdlist, fd, filelist, lineaux, 1, 0, 1, decoderesult, decodedmessagetype, prevday, sbasblock, options);
		}

		if (decoderesult>0 || decoderesult<-3) {
			//Only free sbasblock messagetype memory if we have allocated memory
			freeSBASblock(sbasblock->messagetype,sbasblock,options);
		}

		//Handle special events if it is not the current epoch of the RINEX observation file
		if(currentepoch->MJDN>=0 && tdiff(currentepoch,&sbasblock->t)>1.) {
			SBAShandlespecialevents(*currentepoch,SBASdatabox->SBASdata,options);
		}

		free(sbasblock);
		sbasblock=NULL;
	} //End while(getL(line,&len,fd)!=-1) {

	//Check for missing messages or error messages in all GEOs 
	//It can occur the case that we have not received any message for a tracked  PRN in the current interval read,
	//therefore it is necessary to check if there has been a data gap
    for(m=1;m<=SBASdatabox->SBASdata[0].numSBASsatellites;m++) {
		//Only check satellites that have not been cleared
		GEOPRN=SBASdatabox->SBASdata[m].PRN;
		msgtime.MJDN=msgtimeMJDN[GEOPRN];
		msgtime.SoD=msgtimeSoD[GEOPRN];
		timediff=tdiff(currentepoch,&msgtime);
		numMsgLost=0;
		if (timediff>=1.) {
			numMsgLost=(int)(timediff);
		}
		//The numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[GEOPRN] is to avoid printing the missing message due when we read the first message after a gap,
		//the prevmsgtime has not still been updated until the next message read
		if (prevmsgtime.MJDN!=-1 && numMsgLost!= SBASdatabox->SBASdata[0].missed4msg[GEOPRN]) {
			SBASdatabox->SBASdata[0].missed4msg[GEOPRN]=numMsgLost;
			if(numMsgLost>=4) {
				//Print Info message when a SBAS message is missing only for GEO in use
				if (options->workMode == wmDOPROCESSING) {
					sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",GEOPRN,t2doystr(currentepoch),numMsgLost);
					printInfo(messagestr,options);
				}
				if (MsgMissingCleared[GEOPRN]==0) {
					SBASMissingMessageClearData(m,SBASdatabox->SBASdata);
					MsgMissingCleared[GEOPRN]=1;
				}
				prevnumMsgMissing[GEOPRN]=numMsgLost;
			} else if(numMsgLost>=2) {
				if (options->workMode == wmDOPROCESSING) {
					sprintf(messagestr,"SBAS messages missing for GEO PRN %3d at epoch %17s (%d consecutive missing messages)",GEOPRN,t2doystr(currentepoch),numMsgLost);
					printInfo(messagestr,options);
				}
				prevnumMsgMissing[GEOPRN]=numMsgLost;
			} else if(numMsgLost==1) {
				if (options->workMode == wmDOPROCESSING) {
					sprintf(messagestr,"SBAS message missing for GEO PRN %3d at epoch %17s (1 missing message)",GEOPRN,t2doystr(currentepoch));
					printInfo(messagestr,options);
				}
				prevnumMsgMissing[GEOPRN]=numMsgLost;
			} else {
				prevnumMsgMissing[GEOPRN]=0;
			}
		}
	}
		
	//Print message decoding summary
	if(feof(fd)>0) {
		//Print message decoding summary
		if(writefiles) {
			writeSBASdecodesummary(fdlist, fd, filelist[fdLOGFILE], numberofbadmessages, totalmsgmissing, nummsgmissingdetected, numlinesmissing, missingmessagesvector, options);
		}

	} 


	//Free memory
	free(lineaux[0]);
	lineaux[0]=NULL;

	return 1;
}

/*****************************************************************************
 * Name        : readSBASmessage
 * Description : Decode SBAS message from a binary string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *binarystring              I  N/A  String with the binary message
 * int  messagetype                I  N/A  Message type identifier number
 * int *decodedmessagetype         O  N/A  Message type decoded from hexadecimal message
 * TSBASblock  *sbasblock          O  N/A  TSBASblock structure
 * int *messagesmissing            O  N/A  Indicates the number of messages missing due to the 
 *                                          preamble does not follow the cycle (can be 0,1,2)
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of function
 *                                         -8 => Unknown message type
 *                                         -7 => PRN Mask number is greater than 51
 *                                         -6 => Time of Week is greater than maximum value
 *                                               (only for message 12)
 *                                         -5 => Time of Day is greater than maximum value 
 *                                               (only for messages 24,25,9,17)
 *                                         -4 => Too many satellites with corrections
 *                                                (only for message type 1, if there
 *                                                are more than 51 satellites with
 *                                                corrections)
 *                                         -3 => Message identifier does not match
 *                                               (decoded binary value does not
 *                                               match the value given in file)
 *                                         -2 => Preamble not valid
 *                                         -1 => Invalid parity check
 *                                          0 => Message type with no data
 *                                          1 => Message correctly decoded
 *****************************************************************************/
int readSBASmessage (char *binarystring, int messagetype, int *decodedmessagetype, TSBASblock *sbasblock, int *messagesmissing, TOptions  *options) {

	char			   *endptr;                //This is just for strtol function
	char 				aux[300];
	unsigned char  		binarymessage[33];
	int					i,j;
	int					lengthmessage;
	int 				checksum;
	int					ret;
	int					start;

	static char			previouspreamble[MAX_SBAS_PRN][9];
	static int			badpreamble=0;
	static int          initialized=0;

	if (initialized==0) {
		for(i=0;i<MAX_SBAS_PRN;i++) {
			strcpy(previouspreamble[i],"00000000");
		}
		initialized=1;
	}

	//Table values for messages 2,3,4,5 and 24
	const double 	udreimeterslist[16]={0.75,1.0,1.25,1.75,2.25,3.0,3.75,4.5,5.25,6.0,7.5,15.0,50.0,150.0,-1,-2}; //UDRE (meters)
	const double   udreivariancelist[16]={0.0520,0.0924,0.1444,0.2830,0.4678,0.8315,1.2992,1.8709,2.5465,3.3260,5.1968,20.7870,230.9661,2078.695,-1,-2}; //variance (sigma^2) UDRE (meters^2)

	//Table values for message 7
	const double	fastcorrdegfactorlist[16]={0.00000,0.00005,0.00009,0.00012,0.00015,0.00020,0.00030,0.00045,0.00060,0.00090,0.00150,0.00210,0.00270,0.00330,0.00460,0.00580}; //Fast Correction degradation factor (meters/seconds^2)
	const int 		timeoutintervalnonpreciselist[16]={180,180,153,135,135,117,99,81,63,45,45,27,27,27,18,18};//User Time-Out Interval for fast corrections (seconds). En Route through Nonprecision approach
	const int		timeoutintervalpreciselist[16]={120,120,102,90,90,78,66,54,42,30,30,18,18,18,12,12}; //User Time-Out Interval for fast corrections (seconds). Precision approach mode
	const int  	maxfastcorrupdateintervallist[16]={60,60,51,45,45,39,33,27,21,15,15,9,9,9,6,6}; //Maximum fast correction update interval (seconds)

	//Table values for URA index in message 9
	const double	minurarangelist[16]={0.00,2.40,3.40,4.85,6.85,9.65,13.65,24.00,48.00,96.00,192.00,384.00,768.00,1536.00,3072.00,6144.00}; //Minimun URA range (meters)
	const double	maxurarangelist[16]={2.40,3.40,4.85,6.85,9.65,13.65,24.00,48.00,96.00,192.00,384.00,768.00,1536.00,3072.00,6144.00,-1};	  //Maximum URA range (meters). -1 means no limit (no accuracy)
	const double   uranominalvaluelist[16]={2,2.8,4,5.7,8,11.3,16,32,64,128,256,512,1024,2048,4096,-1}; //URA nominal values. -1 means no accuracy value

	//Table values for Delta UDRE Indicators in message 27
	const double	deltaudrevaluelist[16]={1,1.1,1.25,1.5,2,3,4,5,6,8,10,20,30,40,50,100};	//Delta UDRE values which multiply the UDRE standard deviation in type 2,3,4,5,6 and 24 messages

	//Table values for GIVE in message 26
	const double	givemeterslist[16]={0.3,0.6,0.9,1.20,1.5,1.8,2.1,2.4,2.7,3.0,3.6,4.5,6.0,15.0,45.0,-1}; //GIVE (meters)
	const double	givevariancelist[16]={0.0084,0.0333,0.0749,0.1331,0.2079,0.2994,0.4075,0.5322,0.6735,0.8315,1.1974,1.8709,3.3260,20.7870,187.0826,-1}; //variance (sigma^2) GIVE (meters^2)

	////Checksum for SBAS messages
	
	//Convert the binary string (one bit per byte) to one string where each bit is one value of the message
	lengthmessage=strlen(binarystring);		//Compute message length
	strbintobinstr(binarystring,lengthmessage,binarymessage,sizeof(binarymessage));	
	//Compute checksum from the binary message
	ret=checksumSBAS((unsigned char *)binarymessage);

	//Extract the checksum from the message
	getstr(aux,binarystring,226,24); 		//Parity bits are from bit 227 to 250
	checksum=strtol(aux,&endptr,2);			//Convert parity bits to a decimal number to obtain the message checksum


	////Check preamble. Valid preambles are 
	//01010011 (0x53) 10011010 (0x9A) 11000110 (0xC6)
	getstr(aux,binarystring,0,8);			//Extract preamble bits
	*messagesmissing=0;
	if(strcmp(aux,"01010011")!=0 && strcmp(aux,"10011010")!=0 && strcmp(aux,"11000110")!=0) {
		badpreamble=1;
	}
	else {
		badpreamble=0;			
	}

	//Check if the preamble received is the next in the cycle, otherwise some messages will are missing in the data file
	if (badpreamble==1) {
		//If the previous message had a bad preamble, we cannot say if we have lost any messages
	} else if(strcmp(previouspreamble[sbasblock->PRN],"00000000")==0) {
		//This is the first message read in the file, set previouspreamble and continue
		strcpy(previouspreamble[sbasblock->PRN],aux);
	} else if (strcmp(aux,"01010011")==0) {
		//Check preamble
		if(strcmp(previouspreamble[sbasblock->PRN],"10011010")==0) *messagesmissing=1;
		else if(strcmp(previouspreamble[sbasblock->PRN],"01010011")==0) *messagesmissing=2;
	} else if (strcmp(aux,"10011010")==0) {
		if(strcmp(previouspreamble[sbasblock->PRN],"11000110")==0) *messagesmissing=1;
		else if(strcmp(previouspreamble[sbasblock->PRN],"10011010")==0) *messagesmissing=2;
	} else { //if (strcmp(aux,"11000110")==0) {
		if(strcmp(previouspreamble[sbasblock->PRN],"01010011")==0) *messagesmissing=1;
		else if(strcmp(previouspreamble[sbasblock->PRN],"11000110")==0) *messagesmissing=2;
	}

	if(badpreamble==0) strcpy(previouspreamble[sbasblock->PRN],aux); //Copy preamble to previouspreamble variable

	////Check that message type given in file matches the one decoded from the binary string
	getstr(aux,binarystring,8,6);			//Extract message type identifier bits
	*decodedmessagetype=strtol(aux,&endptr,2);	//Convert the binary string to decimal	


	//Skip read function if CRC, preamble or message type have errors
	if(checksum!=ret) return -1;						//CRC Invalid
	if(badpreamble==1) return -2;						//Preamble invalid
	if(*decodedmessagetype!=messagetype) return -3;		//Message type read does not match the one decoded from the hexadecimal message



	////Read messages
	switch(messagetype) {
		case(PRNMASKASSIGNMENTS):
			//Allocate memory for the current message type
			sbasblock->PRNactive=malloc(MAX_GNSS*sizeof(int*));	//Allocate size of each GNSS system
			sbasblock->pos2PRN=malloc(51*sizeof(int));          	//SBAS only gives corrections to 51 satellites at once
			sbasblock->pos2GNSS=malloc(51*sizeof(int)); 		//SBAS only gives corrections to 51 satellites at once
			sbasblock->PRN2pos=malloc(MAX_GNSS*sizeof(int*));   	//Allocate size of each GNSS system

			//Initialize blocks
			for(i=0;i<MAX_GNSS;i++) {
				sbasblock->PRNactive[i]=NULL;
				sbasblock->PRN2pos[i]=NULL;
				sbasblock->PRNactive[i]=malloc(MAX_SBAS_PRN*sizeof(int));
				sbasblock->PRN2pos[i]=malloc(MAX_SBAS_PRN*sizeof(int));
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
					j++;
				}
			}

			getstr(aux,binarystring,224,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);
			sbasblock->numsatellites=j-1;				//Save number of satellites monitored
			break;				
		case(DONTUSE):
			sbasblock->dontuse=1;
			//Check if the whole message is 0
			getstr(aux,binarystring,8,218);
			if(strtol(aux,&endptr,2)==0) {				//The message is filled with 0 (except for the preamble and the checksum)
				sbasblock->problems=1;				//In that case set the flag to indicate there are problems with SBAS
				break;
			}
			//If the message is not filled with 0, then it will contain a type 2 message
			//A break is not inserted here so it will execute the code of a type 2 message (only if option alarmmessageastype2 is not zero)
			if(options->alarmmessageastype2==0) break;
			/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
		case(FASTCORRECTIONS2):case(FASTCORRECTIONS3):case(FASTCORRECTIONS4):case(FASTCORRECTIONS5):
			//Allocate memory for the current message type
			sbasblock->IODF=malloc(sizeof(int));			//Messages 2,3,4,5 only have one IODF
			sbasblock->PRC=malloc(sizeof(double)*13);		//Messages 2,3,4,5 have corrections for 13 satellites (except 5, that has only 12)
			sbasblock->UDREI=malloc(sizeof(int)*13);		//Messages 2,3,4,5 have corrections for 13 satellites (except 5, that has only 12)
			sbasblock->UDRE=malloc(sizeof(double)*13);    		//Messages 2,3,4,5 have corrections for 13 satellites (except 5, that has only 12)
			sbasblock->UDREsigma=malloc(sizeof(double)*13); 	//Messages 2,3,4,5 have corrections for 13 satellites (except 5, that has only 12)

			//Reading data
			getstr(aux,binarystring,14,2);				//Extract IODF
			sbasblock->IODF[0]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,16,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);

			
			for(i=0;i<13;i++) {					//Extract PRC Fast corrections (PRC has sign bit)
				getstr(aux,binarystring,18+i*12,12);
				sbasblock->PRC[i]=0.125*twocomplementstrbintointeger(aux,12); //PRC has a resolution of 0.125 meters
			}
			
			for(i=0;i<13;i++) {					//Extract UDREIs
				getstr(aux,binarystring,174+i*4,4);
				sbasblock->UDREI[i]=strtol(aux,&endptr,2);	
				sbasblock->UDRE[i]=udreimeterslist[sbasblock->UDREI[i]];	//Get the UDRE meter value from the UDREI
				sbasblock->UDREsigma[i]=udreivariancelist[sbasblock->UDREI[i]];	//Get the UDRE variance value from the UDREI
			}

			break;
		case(INTEGRITYINFO):
			//Allocate memory for the current message type
			sbasblock->IODF=malloc(sizeof(int)*4);			//Message 6 has four IODF (one for each message typ2 2,3,4,5)
			sbasblock->UDREIacu=malloc(sizeof(int)*51);		//Message 6 has 51 UDREI
			sbasblock->UDREacu=malloc(sizeof(double)*51);		//Message 6 has 51 UDRE
			sbasblock->UDREacusigma=malloc(sizeof(double)*51);	//Message 6 has 51 UDRE


			//Reading data
			for(i=0;i<4;i++) {
				getstr(aux,binarystring,14+2*i,2);		//Extract IODFs
				sbasblock->IODF[i]=strtol(aux,&endptr,2);
			}

			for(i=0;i<51;i++) {					//Extract UDREIs
				getstr(aux,binarystring,22+4*i,4);		
				sbasblock->UDREIacu[i]=strtol(aux,&endptr,2);
				sbasblock->UDREacu[i]=udreimeterslist[sbasblock->UDREIacu[i]];	//Get the UDRE meter value from the UDREI
				sbasblock->UDREacusigma[i]=udreivariancelist[sbasblock->UDREIacu[i]];	//Get the UDRE variance value from the UDREI (meters^2)
			}
			break;
		case(FASTCORRECTIONSDEGRADATIONFACTOR):
			//Allocate memory for the current message type
			sbasblock->aiind=malloc(sizeof(int)*51);			//Message 7 has 51 ai indicators
			sbasblock->aifactor=malloc(sizeof(double)*51);			//Message 7 has 51 ai indicators
			sbasblock->timeoutintervalnonprecise=malloc(sizeof(int)*51);	//Message 7 has 51 ai indicators
			sbasblock->timeoutintervalprecise=malloc(sizeof(int)*51);	//Message 7 has 51 ai indicators
			sbasblock->fastcorrupdateinterval=malloc(sizeof(int)*51);	//Message 7 has 51 ai indicators
				
			//Reading data
			getstr(aux,binarystring,14,4);				//Extract tlat
			sbasblock->tlat=strtol(aux,&endptr,2);

			getstr(aux,binarystring,18,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);


			for(i=0;i<51;i++) {					//Extract ai indicators
				getstr(aux,binarystring,22+4*i,4);		
				sbasblock->aiind[i]=strtol(aux,&endptr,2);
				sbasblock->aifactor[i]=fastcorrdegfactorlist[sbasblock->aiind[i]];				//Get the fast correction degradation factor
				sbasblock->timeoutintervalnonprecise[i]=timeoutintervalnonpreciselist[sbasblock->aiind[i]];	//Get the the user timeout interval for non precise approach (seconds)
				sbasblock->timeoutintervalprecise[i]=timeoutintervalpreciselist[sbasblock->aiind[i]];		//Get the the user timeout interval non precise approach (seconds)
				sbasblock->fastcorrupdateinterval[i]=maxfastcorrupdateintervallist[sbasblock->aiind[i]];	//Get the maximum fast correction update interval (seconds)
			}
			break;
		case(DEGRADATIONPARAMETERS):
			//Allocate memory for the current message type		
			sbasblock->degradationfactors=malloc(sizeof(double)*16);               //Message 10 has 16 degradation factors


			//Reading data
			getstr(aux,binarystring,14,10);                         //Extract Brrc (in meters)
			sbasblock->degradationfactors[BRRC]=0.002*strtol(aux,&endptr,2);

			getstr(aux,binarystring,24,10);                         //Extract Cltc_lsb (in meters)
			sbasblock->degradationfactors[CLTCLSB]=0.002*strtol(aux,&endptr,2);

			getstr(aux,binarystring,34,10);                         //Extract Cltc_v1 (in meters/second)
			sbasblock->degradationfactors[CLTCV1]=0.00005*strtol(aux,&endptr,2);

			getstr(aux,binarystring,44,9);				//Extract Iltc_v1 (in seconds)
			sbasblock->degradationfactors[ILTCV1]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,53,10);                         //Extract Cltc_v0 (in meters)
			sbasblock->degradationfactors[CLTCV0]=0.002*strtol(aux,&endptr,2);

			getstr(aux,binarystring,63,9);                          //Extract Iltc_v0 (in seconds)
			sbasblock->degradationfactors[ILTCV0]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,72,10);                         //Extract Cgeo_lsb (in meters)
			sbasblock->degradationfactors[CGEOLSB]=0.0005*strtol(aux,&endptr,2);

			getstr(aux,binarystring,82,10);                         //Extract Cgeo_v (in meters/second)
			sbasblock->degradationfactors[CGEOV]=0.00005*strtol(aux,&endptr,2);

			getstr(aux,binarystring,92,9);	                        //Extract Igeo (in seconds)
			sbasblock->degradationfactors[IGEO]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,101,6);                         //Extract Cer (in meters)
			sbasblock->degradationfactors[CER]=0.5*strtol(aux,&endptr,2);

			getstr(aux,binarystring,107,10);                         //Extract Ciono_step (in meters)
			sbasblock->degradationfactors[CIONOSTEP]=0.001*strtol(aux,&endptr,2);

			getstr(aux,binarystring,117,9);	                         //Extract Iiono (in seconds)
			sbasblock->degradationfactors[IIONO]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,126,10);                         //Extract Ciono ramp (in meters/second)
			sbasblock->degradationfactors[CIONORAMP]=0.000005*strtol(aux,&endptr,2);

			getstr(aux,binarystring,136,1);                         //Extract RSSudre (unitless)
			sbasblock->degradationfactors[RSSUDRE]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,137,1);                         //Extract RSSiono (unitless)
			sbasblock->degradationfactors[RSSIONO]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,138,7);                         //Extract Ccovariance (unitless)
			sbasblock->degradationfactors[CCOVARIANCE]=0.1*strtol(aux,&endptr,2);

			break;

		case(LONGTERMSATELLITECORRECTIONS):
			//First we need to check the value of the two velocity code bits in the message, in order to know how many satellites are needed
			//Initially, we will have, at least, data for two satellites, but we can have data for three of four satellites depending on the velocity code
			//If velocity code is 0, then each half of the message contains clock offset and position error components estimates for two satellites
			//If velocity code is 1, then each half of the message contains clock drift and velocity error components estimates for one satellite
			ret=2;					//Initially there will be at least two satellites
			if(binarystring[14]=='0') ret+=1;	//Check if there are two satellites in the first half of the message
			if(binarystring[120]=='0') ret+=1;	//Check if there are two satellites in the second half of the message
			//Allocate memory for the current message type and initialize values to -1
			sbasblock->longtermsaterrcorrections=malloc(sizeof(double*)*ret);	//One block for each satellite
			sbasblock->numlongtermsaterrcorrections=ret;				//Save the number of satellites in the block			
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				sbasblock->longtermsaterrcorrections[i]=NULL;
				sbasblock->longtermsaterrcorrections[i]=malloc(sizeof(double)*13);	//With velocity code equal to 1, there are 13 values to save (8 with velocity code equal to 0)
				for(j=0;j<13;j++) {
					sbasblock->longtermsaterrcorrections[i][j]=9999;		//9999 means value not set. If velocity code is 0, some slots will not be set
				}
			}


			//Reading first half of message

			getstr(aux,binarystring,14,1);
			if(strtol(aux,&endptr,2)==0) {		//Check if velocity code equal to 0
				for(i=0;i<2;i++) {							//Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,14,1);							//Velocity code
					sbasblock->longtermsaterrcorrections[i][VELOCITYCODE]=strtol(aux,&endptr,2);	

					getstr(aux,binarystring,15+i*51,6);						//PRN Mask Number
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=strtol(aux,&endptr,2);	
					if(sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,21+i*51,8);						//Issue of Data
					sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]=strtol(aux,&endptr,2);	

					getstr(aux,binarystring,29+i*51,9);						//Delta X
					sbasblock->longtermsaterrcorrections[i][DELTAX]=0.125*twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 meters	
				
					getstr(aux,binarystring,38+i*51,9);						//Delta Y
					sbasblock->longtermsaterrcorrections[i][DELTAY]=0.125*twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 meters

					getstr(aux,binarystring,47+i*51,9);						//Delta Z
					sbasblock->longtermsaterrcorrections[i][DELTAZ]=0.125*twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 meters	

					getstr(aux,binarystring,56+i*51,10);						//Delta A f0
					sbasblock->longtermsaterrcorrections[i][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,117,2);							//IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i][IODPPOSITION]=strtol(aux,&endptr,2); 	
				}
			} else {			//Velocity code equal to 1
				getstr(aux,binarystring,14,1);							//Velocity code
				sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,15,6);							//PRN Mask Number
				sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]=strtol(aux,&endptr,2);	
				if(sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,21,8);							//Issue of Data
				sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,29,11);							//Delta X
				sbasblock->longtermsaterrcorrections[0][DELTAX]=0.125*twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 meters	
			
				getstr(aux,binarystring,40,11);							//Delta Y
				sbasblock->longtermsaterrcorrections[0][DELTAY]=0.125*twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 meters

				getstr(aux,binarystring,51,11);							//Delta Z
				sbasblock->longtermsaterrcorrections[0][DELTAZ]=0.125*twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 meters	

				getstr(aux,binarystring,62,11);							//Delta A f0
				sbasblock->longtermsaterrcorrections[0][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,73,8);							//Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 meters/second
				
				getstr(aux,binarystring,81,8);							//Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 meters/second
				
				getstr(aux,binarystring,89,8);							//Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,97,8);							//Delta A f1
				sbasblock->longtermsaterrcorrections[0][DELTAAF1]=pow(2,-39)*twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 meters/second

				getstr(aux,binarystring,105,13);						//Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]=16*strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]>86384) return -5;
				
				getstr(aux,binarystring,118,2);							//IODP
				sbasblock->longtermsaterrcorrections[0][IODPPOSITION]=strtol(aux,&endptr,2); 
			}

			//Reading second half of message
			ret=sbasblock->longtermsaterrcorrections[0][VELOCITYCODE];	//Save previous velocity code value, to know how many satellites we have read
			if(ret==0) ret=2;		//Two satellites read
			//else if(ret==1)  ret=1;	//One satellite read (the line commented because the action of the else if is useless, due to ret will have the right value
			getstr(aux,binarystring,120,1);
			if(strtol(aux,&endptr,2)==0) {          //Check if velocity code equal to 0
				for(i=0;i<2;i++) {                                                      //Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,120,1);                                                  //Velocity code
					sbasblock->longtermsaterrcorrections[i+ret][VELOCITYCODE]=strtol(aux,&endptr,2);

					getstr(aux,binarystring,121+i*51,6);                                             //PRN Mask Number
					sbasblock->longtermsaterrcorrections[i+ret][PRNMASKNUMBER]=strtol(aux,&endptr,2);
					if(sbasblock->longtermsaterrcorrections[i+ret][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,127+i*51,8);                                             //Issue of Data
					sbasblock->longtermsaterrcorrections[i+ret][ISSUEOFDATA]=strtol(aux,&endptr,2);

					getstr(aux,binarystring,135+i*51,9);                                             //Delta X
					sbasblock->longtermsaterrcorrections[i+ret][DELTAX]=0.125*twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 meters  

					getstr(aux,binarystring,144+i*51,9);                                             //Delta Y
					sbasblock->longtermsaterrcorrections[i+ret][DELTAY]=0.125*twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 meters

					getstr(aux,binarystring,153+i*51,9);                                             //Delta Z
					sbasblock->longtermsaterrcorrections[i+ret][DELTAZ]=0.125*twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 meters  

					getstr(aux,binarystring,162+i*51,10);                                            //Delta A f0
					sbasblock->longtermsaterrcorrections[i+ret][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,223,2);                                                 //IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i+ret][IODPPOSITION]=strtol(aux,&endptr,2);
				}
			} else {                        //Velocity code equal to 1
				getstr(aux,binarystring,120,1);                                                  //Velocity code
				sbasblock->longtermsaterrcorrections[ret][VELOCITYCODE]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,121,6);                                                  //PRN Mask Number
				sbasblock->longtermsaterrcorrections[ret][PRNMASKNUMBER]=strtol(aux,&endptr,2);
				if(sbasblock->longtermsaterrcorrections[ret][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,127,8);                                                  //Issue of Data
				sbasblock->longtermsaterrcorrections[ret][ISSUEOFDATA]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,135,11);                                        	 //Delta X
				sbasblock->longtermsaterrcorrections[ret][DELTAX]=0.125*twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 meters 

				getstr(aux,binarystring,146,11);                                      		 //Delta Y
				sbasblock->longtermsaterrcorrections[ret][DELTAY]=0.125*twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 meters

				getstr(aux,binarystring,157,11);                                        	 //Delta Z
				sbasblock->longtermsaterrcorrections[ret][DELTAZ]=0.125*twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 meters 

				getstr(aux,binarystring,168,11);                                      		 //Delta A f0
				sbasblock->longtermsaterrcorrections[ret][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,179,8);                                          	 //Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAXRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,187,8);                                          	 //Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAYRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,195,8);                                          	 //Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[ret][DELTAZRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,203,8);                                          	 //Delta A f1
				sbasblock->longtermsaterrcorrections[ret][DELTAAF1]=pow(2,-39)*twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 meters/second

				getstr(aux,binarystring,211,13);                                        	 //Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[ret][TIMEOFDAYAPPLICABILITY]=16*strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[ret][TIMEOFDAYAPPLICABILITY]>86384) return -5;

				getstr(aux,binarystring,224,2);                                         	 //IODP
				sbasblock->longtermsaterrcorrections[ret][IODPPOSITION]=strtol(aux,&endptr,2);
			}
			break;

		case(MIXEDFASTLONGTERMCORRECTIONS):
			//Allocate memory for fast corrections
			sbasblock->IODF=malloc(sizeof(int));			//Message 24 only have one IODF
			sbasblock->PRC=malloc(sizeof(double)*6);		//Message 24 has corrections for 6 satellites 
			sbasblock->UDREI=malloc(sizeof(int)*6);		//Message 24 hascorrections for 6 satellites
			sbasblock->UDRE=malloc(sizeof(double)*6);    		//Message 24 has corrections for 6 satellites
			sbasblock->UDREsigma=malloc(sizeof(double)*6); 		//Message 24 has corrections for 6 satellites
			
			//Allocate memory for long term satellite error corrections
			ret=1;					//Initially there will be at least two satellites
			if(binarystring[120]=='0') ret+=1;	//Check if there are two satellites in the half of the message
			sbasblock->longtermsaterrcorrections=malloc(sizeof(double*)*ret);	//One block for each satellite
			sbasblock->numlongtermsaterrcorrections=ret;				//Save the number of satellites in the block			
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				sbasblock->longtermsaterrcorrections[i]=NULL;
				sbasblock->longtermsaterrcorrections[i]=malloc(sizeof(double)*13);	//With velocity code equal to 1, there are 13 values to save (8 with velocity code equal to 0)
				for(j=0;j<13;j++) {
					sbasblock->longtermsaterrcorrections[i][j]=9999;		//9999 means value not set. If velocity code is 0, some slots will not be set
				}
			}

			//Read fast corrections
			for(i=0;i<6;i++) {					//Extract PRC Fast corrections (PRC has sign bit)
				getstr(aux,binarystring,14+i*12,12);
				sbasblock->PRC[i]=0.125*twocomplementstrbintointeger(aux,12); //PRC has a resolution of 0.125 meters
			}
			
			for(i=0;i<6;i++) {					//Extract UDREIs
				getstr(aux,binarystring,86+i*4,4);
				sbasblock->UDREI[i]=strtol(aux,&endptr,2);	
				sbasblock->UDRE[i]=udreimeterslist[sbasblock->UDREI[i]];	//Get the UDRE meter value from the UDREI
				sbasblock->UDREsigma[i]=udreivariancelist[sbasblock->UDREI[i]];	//Get the UDRE variance value from the UDREI
			}

			getstr(aux,binarystring,110,2);				//Extract IODP
			sbasblock->IODP=strtol(aux,&endptr,2);

			getstr(aux,binarystring,112,2);				//Extract Block ID
			sbasblock->BlockID=strtol(aux,&endptr,2)+2;		//Block ID need to be added two because with 2 bits we have the range 0-3, but messages type are in range 2-5

			getstr(aux,binarystring,114,2);				//Extract IODF
			sbasblock->IODF[0]=strtol(aux,&endptr,2);


			//Read long term satellite error corrections
			getstr(aux,binarystring,120,1);
			if(strtol(aux,&endptr,2)==0) {          //Check if velocity code equal to 0
				for(i=0;i<2;i++) {                                                      //Loop to read the first two satellites when velocity code equal to 0
					getstr(aux,binarystring,120,1);                                                  //Velocity code
					sbasblock->longtermsaterrcorrections[i][VELOCITYCODE]=strtol(aux,&endptr,2);

					getstr(aux,binarystring,121+i*51,6);                                             //PRN Mask Number
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=strtol(aux,&endptr,2);
					if(sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]>51) return -7;

					getstr(aux,binarystring,127+i*51,8);                                             //Issue of Data
					sbasblock->longtermsaterrcorrections[i][ISSUEOFDATA]=strtol(aux,&endptr,2);

					getstr(aux,binarystring,135+i*51,9);                                             //Delta X
					sbasblock->longtermsaterrcorrections[i][DELTAX]=0.125*twocomplementstrbintointeger(aux,9); //Delta X has a resolution of 0.125 meters  

					getstr(aux,binarystring,144+i*51,9);                                             //Delta Y
					sbasblock->longtermsaterrcorrections[i][DELTAY]=0.125*twocomplementstrbintointeger(aux,9); //Delta Y has a resolution of 0.125 meters

					getstr(aux,binarystring,153+i*51,9);                                             //Delta Z
					sbasblock->longtermsaterrcorrections[i][DELTAZ]=0.125*twocomplementstrbintointeger(aux,9); //Delta Z has a resolution of 0.125 meters  

					getstr(aux,binarystring,162+i*51,10);                                            //Delta A f0
					sbasblock->longtermsaterrcorrections[i][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,10); //Delta A f0 has a resolution of 2^-31 seconds

					getstr(aux,binarystring,223,2);                                                 //IODP (common for all satellites)
					sbasblock->longtermsaterrcorrections[i][IODPPOSITION]=strtol(aux,&endptr,2);
				}
			} else {                        //Velocity code equal to 1
				getstr(aux,binarystring,120,1);                                                  //Velocity code
				sbasblock->longtermsaterrcorrections[0][VELOCITYCODE]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,121,6);                                                  //PRN Mask Number
				sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]=strtol(aux,&endptr,2);
				if(sbasblock->longtermsaterrcorrections[0][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,127,8);                                                  //Issue of Data
				sbasblock->longtermsaterrcorrections[0][ISSUEOFDATA]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,135,11);                                        	 //Delta X
				sbasblock->longtermsaterrcorrections[0][DELTAX]=0.125*twocomplementstrbintointeger(aux,11); //Delta X has a resolution of 0.125 meters 

				getstr(aux,binarystring,146,11);                                      		 //Delta Y
				sbasblock->longtermsaterrcorrections[0][DELTAY]=0.125*twocomplementstrbintointeger(aux,11); //Delta Y has a resolution of 0.125 meters

				getstr(aux,binarystring,157,11);                                        	 //Delta Z
				sbasblock->longtermsaterrcorrections[0][DELTAZ]=0.125*twocomplementstrbintointeger(aux,11); //Delta Z has a resolution of 0.125 meters 

				getstr(aux,binarystring,168,11);                                      		 //Delta A f0
				sbasblock->longtermsaterrcorrections[0][DELTAAF0]=pow(2,-31)*twocomplementstrbintointeger(aux,11); //Delta A f0 has a resolution of 2^-31 seconds

				getstr(aux,binarystring,179,8);                                          	 //Delta X Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAXRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta X Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,187,8);                                          	 //Delta Y Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAYRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Y Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,195,8);                                          	 //Delta Z Rate of Change
				sbasblock->longtermsaterrcorrections[0][DELTAZRATEOFCHANGE]=pow(2,-11)*twocomplementstrbintointeger(aux,8); //Delta Z Rate has a resolution of 2^-11 meters/second

				getstr(aux,binarystring,203,8);                                          	 //Delta A f1
				sbasblock->longtermsaterrcorrections[0][DELTAAF1]=pow(2,-39)*twocomplementstrbintointeger(aux,8); //Delta A f1 has a resolution of 2^-39 meters/second

				getstr(aux,binarystring,211,13);                                        	 //Time of Day Applicability to
				sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]=16*strtol(aux,&endptr,2); //Time of Day Applicability to has a resolution of 16 seconds
				if((int)sbasblock->longtermsaterrcorrections[0][TIMEOFDAYAPPLICABILITY]>86384) return -5;

				getstr(aux,binarystring,224,2);                                         	 //IODP
				sbasblock->longtermsaterrcorrections[0][IODPPOSITION]=strtol(aux,&endptr,2);
			}
			break;
		case(GEONAVIGATIONMESSAGE):
			//Allocate memory for GEO Navigation message
			sbasblock->geonavigationmessage=malloc(sizeof(double)*17);	//Message 9 has 17 parameters
			//sbasblock->URAvalues=malloc(sizeof(double)*3);		//URA values will contain the minimum and maximum values for the range index and a nominal URA value for the given index

			//Read message
			getstr(aux,binarystring,14,8);				//Extract IODN (In MOPS this bits are set as spare). According to RINEX v2.11, this spare bits are the IODN
			sbasblock->geonavigationmessage[IODN]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,22,13);				//Extract t0 (seconds)
			sbasblock->geonavigationmessage[T0NAV]=16*strtol(aux,&endptr,2);
			if((int)sbasblock->geonavigationmessage[T0NAV]>86384) return -5;

			getstr(aux,binarystring,35,4);				//Extract URA index
			sbasblock->geonavigationmessage[URAINDEX]=strtol(aux,&endptr,2);
			sbasblock->geonavigationmessage[URAMINRANGE]=minurarangelist[(int)sbasblock->geonavigationmessage[URAINDEX]];
			sbasblock->geonavigationmessage[URAMAXRANGE]=maxurarangelist[(int)sbasblock->geonavigationmessage[URAINDEX]];
			sbasblock->geonavigationmessage[URANOMINALVALUE]=uranominalvaluelist[(int)sbasblock->geonavigationmessage[URAINDEX]];

			getstr(aux,binarystring,39,30);				//Extract Xg 
			sbasblock->geonavigationmessage[XG]=0.08*twocomplementstrbintointeger(aux,30);	//Xg has a resolution of 0.08 meters

			getstr(aux,binarystring,69,30);				//Extract Yg
			sbasblock->geonavigationmessage[YG]=0.08*twocomplementstrbintointeger(aux,30);	//Yg has a resolution of 0.08 meters

			getstr(aux,binarystring,99,25);				//Extract Zg
			sbasblock->geonavigationmessage[ZG]=0.4*twocomplementstrbintointeger(aux,25);	//Zg has a resolution of 0.4 meters

			getstr(aux,binarystring,124,17);			//Extract Xg Rate of Change
			sbasblock->geonavigationmessage[XGRATEOFCHANGE]=0.000625*twocomplementstrbintointeger(aux,17);	//Xg Rate of Change has a resolution of 0.000625 meters/second

			getstr(aux,binarystring,141,17);			//Extract Yg Rate of Change
			sbasblock->geonavigationmessage[YGRATEOFCHANGE]=0.000625*twocomplementstrbintointeger(aux,17);	//Yg Rate of Change has a resolution of 0.000625 meters/second

			getstr(aux,binarystring,158,18);			//Extract Zg Rate of Change
			sbasblock->geonavigationmessage[ZGRATEOFCHANGE]=0.004*twocomplementstrbintointeger(aux,18);	//Zg Rate of Change has a resolution of 0.004 meters/second

			getstr(aux,binarystring,176,10);			//Extract Xg acceleration
			sbasblock->geonavigationmessage[XGACCELERATION]=0.0000125*twocomplementstrbintointeger(aux,10);//Xg acceleration has a resolution of 0.0000125 meters/second^2

			getstr(aux,binarystring,186,10);			//Extract Yg acceleration
			sbasblock->geonavigationmessage[YGACCELERATION]=0.0000125*twocomplementstrbintointeger(aux,10);//Yg acceleration has a resolution of 0.0000125 meters/second^2

			getstr(aux,binarystring,196,10);			//Extract Zg acceleration
			sbasblock->geonavigationmessage[ZGACCELERATION]=0.0000625*twocomplementstrbintointeger(aux,10);//Zg acceleration has a resolution of 0.0000625 meters/second^2

			getstr(aux,binarystring,206,12);			//Extract aGf0
			sbasblock->geonavigationmessage[AGF0]=pow(2,-31)*twocomplementstrbintointeger(aux,12);	//aGf0 has a resolution of 2^-31 seconds

			getstr(aux,binarystring,218,8);				//Extract aGf1
			sbasblock->geonavigationmessage[AGF1]=pow(2,-40)*twocomplementstrbintointeger(aux,8);	//aGf1 has a resolution of 2^-40 seconds/second

			break;

		case(GEOSATELLITEALMANACS):
			//First we need to check how many almanacs are given
			ret=0;
			getstr(aux,binarystring,150,8);
			if(strtol(aux,&endptr,2)!=0) ret=3;
			else {
				getstr(aux,binarystring,83,8);
				if(strtol(aux,&endptr,2)!=0) ret=2;
				else {
					getstr(aux,binarystring,16,8);
					if(strtol(aux,&endptr,2)!=0) ret=1;
				}
			}
			sbasblock->numgeoalmanacs=ret;
			if(ret==0) ret=1;	//If there are no satellites we put one slot to avoid memory problems

			//Allocate memory for GEO Almanacs message
			sbasblock->geoalmanacsmessage=malloc(sizeof(double*)*ret);    		 //Message 17 has data for three satellites
			for(i=0;i<ret;i++) {
				sbasblock->geoalmanacsmessage[i]=NULL;
				sbasblock->geoalmanacsmessage[i]=malloc(sizeof(double)*12);     //Message 17 has 12 parameters for each satellite
				for(j=0;j<12;j++) {
					sbasblock->geoalmanacsmessage[i][j]=-1.;
				}
			}

			//Read message
			for(i=0;i<sbasblock->numgeoalmanacs;i++) {
				getstr(aux,binarystring,14+i*67,2);				//Extract Data ID
				sbasblock->geoalmanacsmessage[i][DATAID]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,16+i*67,8);				//Extract PRN Number
				sbasblock->geoalmanacsmessage[i][PRNNUMBER]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,24+i*67,8);				//Extract Health and Service provider (the eight bits of Health and status)
				sbasblock->geoalmanacsmessage[i][HEALTHPROVIDER]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,24+i*67,4);				//Extract Service provider (only the first four bits)
				sbasblock->geoalmanacsmessage[i][SERVICEPROVIDER]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,28+i*67,4);				//Extract Health status (only the last four bits)
				sbasblock->geoalmanacsmessage[i][HEALTHSTATUS]=strtol(aux,&endptr,2);

				getstr(aux,binarystring,32+i*67,15);				//Extract Xg
				sbasblock->geoalmanacsmessage[i][XGALMANAC]=2600*twocomplementstrbintointeger(aux,15);	//Xg has a resolution of 2,600 meters

				getstr(aux,binarystring,47+i*67,15);				//Extract Yg
				sbasblock->geoalmanacsmessage[i][YGALMANAC]=2600*twocomplementstrbintointeger(aux,15);	//Yg has a resolution of 2,600 meters

				getstr(aux,binarystring,62+i*67,9);				//Extract Zg
				sbasblock->geoalmanacsmessage[i][ZGALMANAC]=26000*twocomplementstrbintointeger(aux,9);	//Zg has a resolution of 26,000 meters

				getstr(aux,binarystring,71+i*67,3);				//Extract Xg Rate of Change
				sbasblock->geoalmanacsmessage[i][XGALMANACRATEOFCHANGE]=10*twocomplementstrbintointeger(aux,3);	//Xg Rate of Change has a resolution of 10 meters/second

				getstr(aux,binarystring,74+i*67,3);				//Extract Yg Rate of Change
				sbasblock->geoalmanacsmessage[i][YGALMANACRATEOFCHANGE]=10*twocomplementstrbintointeger(aux,3);	//Yg Rate of Change has a resolution of 10 meters/second

				getstr(aux,binarystring,77+i*67,4);				//Extract Zg Rate of Change
				sbasblock->geoalmanacsmessage[i][ZGALMANACRATEOFCHANGE]=60*twocomplementstrbintointeger(aux,4);	//Zg Rate of Change has a resolution of 60 meters/second

				getstr(aux,binarystring,215,11);				//Extract t0 or Time of Day (seconds)
				sbasblock->geoalmanacsmessage[i][T0ALMANAC]=64*strtol(aux,&endptr,2);
				if((int)sbasblock->geoalmanacsmessage[i][T0ALMANAC]>86336) return -5;
			}
			break;
		case(SBASSERVICEMESSAGE):
			//Read number of regions given
			getstr(aux,binarystring,23,3);	
			ret=strtol(aux,&endptr,2);

			//Allocate memory for SBAS service message
			sbasblock->servicemessage=malloc(sizeof(double)*9);   		//Message 27 has 7 parameters + 2 for the Delta UDRE values
			sbasblock->numregioncoordinates=ret;
			if(ret==0) ret=1;						//If the number of regions is 0, set the size to 1 to avoid possible memory issues	
			sbasblock->regioncoordinates=malloc(sizeof(int*)*ret);	
			for(i=0;i<ret;i++) {
				sbasblock->regioncoordinates[i]=NULL;
				sbasblock->regioncoordinates[i]=malloc(sizeof(int)*12);	//Each region will need 12 parameters
				for(j=0;j<12;j++) {
					sbasblock->regioncoordinates[i][j]=9999;		//9999 means value not set
				}
			}
	
			//Read message
			getstr(aux,binarystring,14,3);				//Extract Issue of Data Service (IODS)
			sbasblock->servicemessage[IODSPOS]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,17,3);				//Extract Number of Service Messages
			sbasblock->servicemessage[NUMBERSERVICEMESSAGES]=strtol(aux,&endptr,2)+1;	//This value has an offset of 1

			getstr(aux,binarystring,20,3);				//Extract Service Message Number
			sbasblock->servicemessage[SERVICEMESSAGENUMBER]=strtol(aux,&endptr,2)+1;	//This value has an offset of 1
			
			getstr(aux,binarystring,23,3);				//Extract Number of Regions
			sbasblock->servicemessage[NUMBEROFREGIONS]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,26,2);				//Extract Priority Code
			sbasblock->servicemessage[PRIORITYCODE]=strtol(aux,&endptr,2);

			getstr(aux,binarystring,28,4);				//Extract Delta UDRE Indicator Inside
			sbasblock->servicemessage[UDREINSIDEIND]=strtol(aux,&endptr,2);
			sbasblock->servicemessage[UDREINSIDEVALUE]=deltaudrevaluelist[(int)sbasblock->servicemessage[UDREINSIDEIND]];	//Get Delta UDRE Indicator Inside value

			getstr(aux,binarystring,32,4);				//Extract Delta UDRE Indicator Outside
			sbasblock->servicemessage[UDREOUTSIDEIND]=strtol(aux,&endptr,2);
			sbasblock->servicemessage[UDREOUTSIDEVALUE]=deltaudrevaluelist[(int)sbasblock->servicemessage[UDREOUTSIDEIND]]; //Get Delta UDRE Indicator Outside value

			for(i=0;i<(int)sbasblock->servicemessage[NUMBEROFREGIONS];i++) {
				//Read all the regions given in the message
				//Positive values denote North latitude or East longitude
				getstr(aux,binarystring,36+i*35,8);				//Extract Coordinate 1 Latitude (degrees)
				sbasblock->regioncoordinates[i][COORD1LAT]=twocomplementstrbintointeger(aux,8);

				getstr(aux,binarystring,44+i*35,9);				//Extract Coordinate 1 Longitude (degrees)
				sbasblock->regioncoordinates[i][COORD1LON]=twocomplementstrbintointeger(aux,9);

				getstr(aux,binarystring,53+i*35,8);				//Extract Coordinate 2 Latitude (degrees)
				sbasblock->regioncoordinates[i][COORD2LAT]=twocomplementstrbintointeger(aux,8);

				getstr(aux,binarystring,61+i*35,9);				//Extract Coordinate 2 Longitude (degrees)
				sbasblock->regioncoordinates[i][COORD2LON]=twocomplementstrbintointeger(aux,9);

				getstr(aux,binarystring,70+i*35,1);				//Extract Region Shape (0=> Tringular 1=>Square)
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
				sbasblock->regioncoordinates[i][UDREINSIDEVALUE]=sbasblock->servicemessage[UDREINSIDEVALUE];
				sbasblock->regioncoordinates[i][UDREOUTSIDEVALUE]=sbasblock->servicemessage[UDREOUTSIDEVALUE];
				//Copy number of service messages
				sbasblock->regioncoordinates[i][NUMBERSERVICEMESSAGES]=sbasblock->servicemessage[NUMBERSERVICEMESSAGES];

			}
			break;
		case(SBASNETWORKTIMEPARAMETERS):
			//Allocate memory for Network Time/UTC parameters
			sbasblock->networktimemessage=malloc(sizeof(double)*12);     		//Message 12 has 12 parameters

			//Read message
			getstr(aux,binarystring,14,24);				//Extract A1wnt
			sbasblock->networktimemessage[A1WNT]=pow(2,-50)*twocomplementstrbintointeger(aux,24);	//A1wnt has a resolution of 2^-50 seconds/second

			getstr(aux,binarystring,38,32);				//Extract A0wnt
			sbasblock->networktimemessage[A0WNT]=pow(2,-30)*twocomplementstrbintointeger(aux,32);	//A0wnt has a resolution of 2^-30 seconds

			getstr(aux,binarystring,70,8);				//Extract t0t
			sbasblock->networktimemessage[T0T]=pow(2,12)*strtol(aux,&endptr,2);			//t0t has a resolution of 2^12 seconds

			getstr(aux,binarystring,78,8);				//Extract WNt
			sbasblock->networktimemessage[WNT]=strtol(aux,&endptr,2);				//In weeks
			
			getstr(aux,binarystring,86,8);				//Extract Delta tLS
			sbasblock->networktimemessage[DELTATLS]=twocomplementstrbintointeger(aux,8);		//Delta tLS has a resolution of 1 second

			getstr(aux,binarystring,94,8);				//Extract WNlsf
			sbasblock->networktimemessage[WNLSF]=strtol(aux,&endptr,2);				//In weeks

			getstr(aux,binarystring,102,8);				//Extract DN
			sbasblock->networktimemessage[DNDAY]=strtol(aux,&endptr,2);				//In days
			
			getstr(aux,binarystring,110,8);				//Extract Delta tLSF 
			sbasblock->networktimemessage[DELTATLSF]=twocomplementstrbintointeger(aux,8);		//Delta tLSF has a resolution of 1 second

			getstr(aux,binarystring,118,3);				//Extract UTC Standard Identifier
			sbasblock->networktimemessage[UTCIDENTIFIER]=strtol(aux,&endptr,2);
			
			getstr(aux,binarystring,121,20);			//Extract GPS Time of Week
			sbasblock->networktimemessage[GPSTOW]=strtol(aux,&endptr,2);				//In seconds
			if((int)sbasblock->networktimemessage[GPSTOW]>604799) return -6;
			
			getstr(aux,binarystring,141,10);			//Extract GPS Week Number
			sbasblock->networktimemessage[GPSWEEKNUMBER]=strtol(aux,&endptr,2);			//In weeks
			
			getstr(aux,binarystring,151,1);				//Extract GLONASS Indicator
			sbasblock->networktimemessage[GLONASSINDICATOR]=strtol(aux,&endptr,2);			
			break;
		case(CLOCKEPHEMERISCOVARIANCEMATRIX):
			//Read number of satellites
			ret=0;
			start=0;	//This is for the case we only have data in the second satellite
			//Check PRN Number first satellite
			getstr(aux,binarystring,16,6);
			if(strtol(aux,&endptr,2)!=0) {
				ret++;
				start=0;
			}
			//Check PRN Number second satellite
			getstr(aux,binarystring,121,6);
			if(strtol(aux,&endptr,2)!=0) {
				ret++;
				if(ret==1) start=1;
			}

			sbasblock->numclockephemeriscovariance=ret;    //Save number of satellites
			if(ret==0) ret=1;       //If there are no satellites, put ret equal to 1 to give size to numclockephemeriscovariance in order to avoid memory problems

			//Allocate memory for Clock Ephemeris Covariance matrix parameters
			sbasblock->clockephemeriscovariance=malloc(sizeof(int*)*ret);		//Message 28 may have 1 or 2 satellites covariance matrix

			for(i=0;i<ret;i++) {
				sbasblock->clockephemeriscovariance[i]=NULL;
				sbasblock->clockephemeriscovariance[i]=malloc(sizeof(int)*13);	//Each satellite will have 13 parameters
				for(j=0;j<13;j++) {
					sbasblock->clockephemeriscovariance[i][j]=-1;		//-1 means value not set
				}
			}

			//Read message
			for(i=start;i<sbasblock->numclockephemeriscovariance+start;i++) {
				getstr(aux,binarystring,14,2);				//Extract IODP
				sbasblock->clockephemeriscovariance[i-start][IODPPOSITION]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,16+i*105,6);			//Extract PRN Mask Number
				sbasblock->clockephemeriscovariance[i-start][PRNMASKNUMBER]=strtol(aux,&endptr,2);	
				if(sbasblock->clockephemeriscovariance[i-start][PRNMASKNUMBER]>51) return -7;

				getstr(aux,binarystring,22+i*105,3);			//Extract Scale Exponent
				sbasblock->clockephemeriscovariance[i-start][SCALEEXPONENT]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,25+i*105,9);			//Extract E1,1
				sbasblock->clockephemeriscovariance[i-start][E11]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,34+i*105,9);			//Extract E2,2
				sbasblock->clockephemeriscovariance[i-start][E22]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,43+i*105,9);			//Extract E3,3
				sbasblock->clockephemeriscovariance[i-start][E33]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,52+i*105,9);			//Extract E4,4
				sbasblock->clockephemeriscovariance[i-start][E44]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,61+i*105,10);			//Extract E1,2
				sbasblock->clockephemeriscovariance[i-start][E12]=twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,71+i*105,10);			//Extract E1,3
				sbasblock->clockephemeriscovariance[i-start][E13]=twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,81+i*105,10);			//Extract E1,4
				sbasblock->clockephemeriscovariance[i-start][E14]=twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,91+i*105,10);			//Extract E2,3
				sbasblock->clockephemeriscovariance[i-start][E23]=twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,101+i*105,10);			//Extract E2,4
				sbasblock->clockephemeriscovariance[i-start][E24]=twocomplementstrbintointeger(aux,10);

				getstr(aux,binarystring,111+i*105,10);			//Extract E3,4
				sbasblock->clockephemeriscovariance[i-start][E34]=twocomplementstrbintointeger(aux,10);

			}
			break;
		case(IONOSPHERICGRIDPOINTSMASKS):
			//Allocate memory for Ionospheric Grid Points Mask
			sbasblock->igpmaskmessage=malloc(sizeof(int)*204);	//Message 18 may has 3 parameters and 201 Mask bits
			 
			//Read message
			getstr(aux,binarystring,14,4);				//Extract Number of bands being broadcast
			sbasblock->igpmaskmessage[NUMBEROFBANDS]=strtol(aux,&endptr,2);	

			getstr(aux,binarystring,18,4);				//Extract Band Number
			sbasblock->igpmaskmessage[BANDNUMBER]=strtol(aux,&endptr,2);	

			getstr(aux,binarystring,22,2);				//Extract IODI (Issue of Data Ionosphere)
			sbasblock->igpmaskmessage[IODIPOS]=strtol(aux,&endptr,2);	

			for(i=0;i<201;i++) {
				getstr(aux,binarystring,24+i,1);		//Extract IGP (Ionospheric Grid Point) Mask bit
				sbasblock->igpmaskmessage[i+3]=strtol(aux,&endptr,2);	
			}
			break;
		case(IONOSPHERICDELAYCORRECTIONS):
			//Allocate memory for Ionospheric Delay Corrections
			sbasblock->ionodelayparameters=malloc(sizeof(double*)*15); 		//Message 26 has 15 Grid Points
			for(i=0;i<15;i++) {
				sbasblock->ionodelayparameters[i]=NULL;
				sbasblock->ionodelayparameters[i]=malloc(sizeof(double)*7);	//Each block will have 5 parameters + 2 for the GIVE value and variance
				for(j=0;j<7;j++) {
					sbasblock->ionodelayparameters[i][j]=-1.;		//-1 means value not set
				}
			}

			//Read message
			for(i=0;i<15;i++) {
				getstr(aux,binarystring,14,4);				//Extract Band Number
				sbasblock->ionodelayparameters[i][BANDNUMBER]=strtol(aux,&endptr,2);	
				
				getstr(aux,binarystring,18,4);				//Extract Block ID
				sbasblock->ionodelayparameters[i][BLOCKID]=strtol(aux,&endptr,2);	

				getstr(aux,binarystring,22+i*13,9);			//Extract IGP Vertical Delay
				sbasblock->ionodelayparameters[i][IGPVERTICALDELAY]=0.125*strtol(aux,&endptr,2);	//IGP Vertical Delay has a resolution of 0.125 meters

				getstr(aux,binarystring,31+i*13,4);			//Extract GIVEI (Grid Ionospheric Vertical Error Indicator)
				sbasblock->ionodelayparameters[i][GIVEI]=strtol(aux,&endptr,2);	
				sbasblock->ionodelayparameters[i][GIVEVALUE]=givemeterslist[(int)sbasblock->ionodelayparameters[i][GIVEI]];	//Get the GIVE value (meters) for the given indicator
				sbasblock->ionodelayparameters[i][GIVEVARIANCE]=givevariancelist[(int)sbasblock->ionodelayparameters[i][GIVEI]]; //Get the GIVE variance (meters^2) for the given indicator

				getstr(aux,binarystring,217,2);				//Extract IODI (Ionospheric Mask Issue of Data)
				sbasblock->ionodelayparameters[i][IODIPOS]=strtol(aux,&endptr,2);	
			}
			break;
		case(RESERVED8):case(RESERVED11):case(RESERVED13):case(RESERVED14):case(RESERVED15):case(RESERVED16):case(RESERVED19):case(RESERVED20):case(RESERVED21):case(RESERVED22):case(RESERVED23):case(INTERNALTESTMESSAGE):case(NULLMESSAGE):
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
 * TSBASdata  *SBASdata            IO N/A  Structure to save SBAS data
 * TSBASblock  *sbasblock          I  N/A  TSBASblock structure
 * TTime currentepoch              I  N/A  Current epoch
 * int *messagesmissing            I  N/A  Indicates the number of messages missing due to the 
 *                                         preamble does not follow the cycle (can be 0,1,2)
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void updateSBASdata (TSBASdata  *SBASdata, TSBASblock  *sbasblock, TTime currentepoch, int messagesmissing, TOptions  *options) {

	int 				i,j,k,l,m,n;
	int 				pos,GEObuffer;
	int					currentbandnumber,currentblockID;
	int					posFC;
	static int			initpos;
	static int			posIndex[2];
	static int			initialized=0;
	static int			ionobuffered[MAX_SBAS_PRN][11][14];
	static TSBASblock 	ionobuffer[MAX_SBAS_PRN][11][14]; //One for each band number and Block ID
	

	if(initialized==0) {
		//Check if mixed GEO is allowed
		if (options->GEOPRN==0 || (options->mixedGEOdata==1 && options->switchGEO==1)) {
			initpos=0;
		} else {
			initpos=1;
		}
		posIndex[0]=0;
				
		for(m=0;m<MAX_SBAS_PRN;m++) {
			for(i=0;i<11;i++) {
				for(j=0;j<14;j++) {
					initSBASblock(&ionobuffer[m][i][j]);
					//Allocate memory for Ionospheric Delay Corrections
					ionobuffer[m][i][j].ionodelayparameters=malloc(sizeof(double*)*15); 		//Message 26 has 15 Grid Points
					for(k=0;k<15;k++) {
						ionobuffer[m][i][j].ionodelayparameters[k]=malloc(sizeof(double)*7);	//Each block will have 5 parameters + 2 for the GIVE value and variance
						for(l=0;l<7;l++) {
							ionobuffer[m][i][j].ionodelayparameters[k][l]=-1.;			//-1 means value not set
						}
					}
					ionobuffered[m][i][j]=0;
				}
			}
		}
		initialized=1;
	}

	//If we have one satellite in alarm (which lasts one minute), ignore its messages
	if(SBASdata[0].alarmGEOPRN[sbasblock->PRN]==sbasblock->PRN && sbasblock->messagetype!=DONTUSE) return;

	posIndex[1]=SBASdata[0].GEOPRN2pos[sbasblock->PRN];

	//Select PRN slots to be updated (the slot with mixed PRN data and the slot with only 1 satellite)
	for(n=initpos;n<2;n++) {
		pos=posIndex[n];

		//New message. Update data only if the current slot is the mixed one (position 0 or the one of the current PRN) 

		if(SBASdata[pos].firstmessage.MJDN==-1) {
			SBASdata[pos].firstmessage.MJDN=sbasblock->t.MJDN;
			SBASdata[pos].firstmessage.SoD=sbasblock->t.SoD;
		}

		switch(sbasblock->messagetype) {
			case(PRNMASKASSIGNMENTS):
				//Check if we have a PRN Mask
				if(sbasblock->IODP!=SBASdata[pos].IODPmask) {
					//New Mask. Save the old mask, so we can still use messages 
					for(i=0;i<51;i++) {

						SBASdata[pos].pos2PRN[sbasblock->IODP][i]=sbasblock->pos2PRN[i];
						SBASdata[pos].pos2GNSS[sbasblock->IODP][i]=sbasblock->pos2GNSS[i];
					}
					for(i=0;i<MAX_GNSS;i++) {
						for(j=0;j<MAX_SBAS_PRN;j++) {
							SBASdata[pos].PRNactive[sbasblock->IODP][i][j]=sbasblock->PRNactive[i][j];
							SBASdata[pos].PRN2pos[sbasblock->IODP][i][j]=sbasblock->PRN2pos[i][j];
						}
					}
					SBASdata[pos].oldIODPmask=SBASdata[pos].IODPmask;

					SBASdata[pos].IODPmask=sbasblock->IODP;
					SBASdata[pos].numsatellites[sbasblock->IODP]=sbasblock->numsatellites;
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;

					//Set all other masks to -1
					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].oldIODPmask && i!=SBASdata[pos].IODPmask) {
							SBASdata[pos].numsatellites[i]=0;
							for(j=0;j<MAX_GNSS;j++) {
								for(k=0;k<MAX_SBAS_PRN;k++) {
									SBASdata[pos].PRNactive[i][j][k]=-1;
									SBASdata[pos].PRN2pos[i][j][k]=-1;
								}
							}

						}
					}
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case(DONTUSE):
				if(options->usetype0messages==0) {
					//Alarm messages are ignored
					break;
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				SBASdata[pos].problems=sbasblock->problems;
				if(sbasblock->problems==1) {
					//This means that the message is all 0. There is no type 2 message data
					SBASdata[pos].dontuse=sbasblock->dontuse;
					if(pos!=0) {
						//If mixed GEO is not enabled, we set alarm also to the mixed GEO, as the alarm condition is checked with the mixed GEO
						SBASdata[0].dontuse=sbasblock->dontuse;
						//Save the PRN of the GEO that received the alarm
						if (SBASdata[0].alarmGEOPRN[sbasblock->PRN]==-1) {
							//Alarm not already received from current GEO
							SBASdata[0].alarmGEOPRN[sbasblock->PRN]=sbasblock->PRN;
							//Save the index position of the GEO with alarm
							SBASdata[0].alarmGEOindex[SBASdata[0].numAlarmGEO]=pos;
							//Increase by one the number of GEOs with alarm
							SBASdata[0].numAlarmGEO++;
						}
						//Set the remaining alarm time to 60 seconds
						SBASdata[pos].alarmTimeRemaining=60;
						SBASdata[0].alarmTimeRemaining=60;
					}
					break;
				}
				if(options->alarmmessageastype2==0) {
					//Decode message type 0 as it is
					SBASdata[pos].dontuse=sbasblock->dontuse;
					if(pos!=0) {
						//If mixed GEO is not enabled, we set alarm also to the mixed GEO, as the alarm condition is checked with the mixed GEO
						SBASdata[0].dontuse=sbasblock->dontuse;
						if (SBASdata[0].alarmGEOPRN[sbasblock->PRN]==-1) {
							//Save the PRN of the GEO that received the alarm
							SBASdata[0].alarmGEOPRN[sbasblock->PRN]=sbasblock->PRN;
							//Save the index position of the GEO with alarm
							SBASdata[0].alarmGEOindex[SBASdata[0].numAlarmGEO]=pos;
							//Increase by one the number of GEOs with alarm
							SBASdata[0].numAlarmGEO++;
							//Set the remaining alarm time to 60 seconds
							SBASdata[pos].alarmTimeRemaining=60;
							SBASdata[0].alarmTimeRemaining=60;
						}
					}
					break;
				}
				//No break here because message will be decoded as type 2
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case(FASTCORRECTIONS2):case(FASTCORRECTIONS3):case(FASTCORRECTIONS4):case(FASTCORRECTIONS5):

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

				if(sbasblock->messagetype==DONTUSE) i=0;
				else i=(sbasblock->messagetype-2)*13;


				for(j=i,k=0;j<(sbasblock->messagetype-1)*13;j++,k++) {

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

				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;


				break;	
			case(INTEGRITYINFO):

				if(SBASdata[pos].IODPfastcorr==-1) {
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

				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;	
			case(FASTCORRECTIONSDEGRADATIONFACTOR):

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

				for(i=0;i<51;i++) {
					SBASdata[pos].aifactor[sbasblock->IODP][i]=sbasblock->aifactor[i];	
					SBASdata[pos].fastcorrtimeout[0][sbasblock->IODP][i]=sbasblock->timeoutintervalnonprecise[i];	
					SBASdata[pos].fastcorrtimeout[1][sbasblock->IODP][i]=sbasblock->timeoutintervalprecise[i];	
					SBASdata[pos].fastcorrupdateinterval[sbasblock->IODP][i]=sbasblock->fastcorrupdateinterval[i];	
					SBASdata[pos].lastfastdegfactor[sbasblock->IODP][i].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastfastdegfactor[sbasblock->IODP][i].SoD=sbasblock->t.SoD;
				}

				SBASdata[pos].tlat[sbasblock->IODP]=sbasblock->tlat;
				SBASdata[pos].IODPdegcorr=sbasblock->IODP;

				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case(DEGRADATIONPARAMETERS):
				for(i=0;i<16;i++) {
					//Save old values
					SBASdata[pos].olddegradationfactors[i]=SBASdata[pos].degradationfactors[i];	

					//Save new values
					SBASdata[pos].degradationfactors[i]=sbasblock->degradationfactors[i];
				}	

				//Update last received message 
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case(LONGTERMSATELLITECORRECTIONS):
				//Check if IODP has changed
				if(SBASdata[pos].IODPlongterm!=sbasblock->longtermsaterrcorrections[0][IODPPOSITION]) {
					//IODP has changed. Save the old values and initialize the current one
					SBASdata[pos].oldIODPlongterm=SBASdata[pos].IODPlongterm;
					SBASdata[pos].IODPlongterm=(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION];
					for(i=0;i<51;i++) {
						for(j=0;j<13;j++) {
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
						for(k=0;k<13;k++) {
							SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k];
						}
						//Update last received message for the given PRNs
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN;
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD;
					}

					for(k=0;k<13;k++) {
						SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=sbasblock->longtermsaterrcorrections[i][k];
					}
					//Update last received message for the given PRNs
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=sbasblock->t.SoD;

					//Leave sbasblock as it was
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]+1;

				}
				break;
			case(MIXEDFASTLONGTERMCORRECTIONS):
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

				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				//LONGTERMSATELLITECORRECTIONS
				//Check if IODP has changed
				if(SBASdata[pos].IODPlongterm!=sbasblock->longtermsaterrcorrections[0][IODPPOSITION]) {
					//IODP has changed. Save the old values and initialize the current one
					SBASdata[pos].oldIODPlongterm=SBASdata[pos].IODPlongterm;
					SBASdata[pos].IODPlongterm=(int)sbasblock->longtermsaterrcorrections[0][IODPPOSITION];
					for(i=0;i<51;i++) {
						for(j=0;j<13;j++) {
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
						for(k=0;k<13;k++) {
							SBASdata[pos].prevlongtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k];
						}
						//Update last received message for the given PRNs
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN;
						SBASdata[pos].prevlastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD;
					}
					for(k=0;k<13;k++) {
						SBASdata[pos].longtermsaterrcorrections[SBASdata[pos].IODPlongterm][j][k]=sbasblock->longtermsaterrcorrections[i][k];	
					}
					//Update last received message for the given PRNs
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastlongtermdata[SBASdata[pos].IODPlongterm][j].SoD=sbasblock->t.SoD;


					//Leave sbasblock as it was
					sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]=sbasblock->longtermsaterrcorrections[i][PRNMASKNUMBER]+1;
				}
				
				break;
			case(GEONAVIGATIONMESSAGE):
				for(i=0;i<17;i++) {
					//Save old values
					SBASdata[pos].oldgeonavigationmessage[i]=SBASdata[pos].geonavigationmessage[i];	

					//Save new values
					SBASdata[pos].geonavigationmessage[i]=sbasblock->geonavigationmessage[i];	
				}
				//Update last received message
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case(GEOSATELLITEALMANACS):
				//Save old values
				SBASdata[pos].oldnumgeoalmanacs=SBASdata[pos].numgeoalmanacs;
				for(i=0;i<3;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].oldgeoalmanacsmessage[i][j]=SBASdata[pos].geoalmanacsmessage[i][j];
					}
				}

				//Save new values
				SBASdata[pos].numgeoalmanacs=sbasblock->numgeoalmanacs;
				for(i=0;i<sbasblock->numgeoalmanacs;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].geoalmanacsmessage[i][j]=sbasblock->geoalmanacsmessage[i][j];	
					}
				}

				//If there are empty slots, initialize them so there are no remanents from previous messages
				for(;i<3;i++) {
					for(j=0;j<12;j++) {
						SBASdata[pos].geoalmanacsmessage[i][j]=-1;
					}
				}
				//Update last received message
				//Save old values
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
				SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;
				//Save new values
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case(SBASSERVICEMESSAGE):
				if(SBASdata[pos].IODS!=(int)sbasblock->servicemessage[IODSPOS]) {
					//New IODS, we need to save old values and initialize the values of the current block
					SBASdata[pos].oldIODS=SBASdata[pos].IODS;

					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;

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
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case(SBASNETWORKTIMEPARAMETERS):
				for(i=0;i<12;i++) {
					SBASdata[pos].networktimemessage[i]=sbasblock->networktimemessage[i];
				}
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
				break;
			case(CLOCKEPHEMERISCOVARIANCEMATRIX):
				//Check if the Message mask matches with the latest message received
				if(SBASdata[pos].IODPcovariance!=(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]) {
					//New mask. We need to save all the old values and initialize the current one
					for(i=0;i<5;i++) {
						if(i!=SBASdata[pos].IODPcovariance && i!=(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]) {
							for(j=0;j<51;j++) {
								SBASdata[pos].lastcovmatrix[i][j].MJDN=-1;
								SBASdata[pos].lastcovmatrix[i][j].SoD=-1;
							}

						}
					}
					SBASdata[pos].oldIODPcovariance=SBASdata[pos].IODPcovariance;

					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;
				}


				for(i=0;i<sbasblock->numclockephemeriscovariance;i++) {
					if(sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]==0) continue; //PRNMASKNUMBER=0 means that there is no valid data
					//Substract one because our PRN Mask number goes from 0 to 50
					sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]=sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]-1;
					j=sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER];
					for(k=0;k<13;k++) {
						//Save new values
						SBASdata[pos].clockephemeriscovariance[(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]][j][k]=sbasblock->clockephemeriscovariance[i][k];
					}

					//Update last received message for the given PRNs 
					SBASdata[pos].lastcovmatrix[(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]][j].MJDN=sbasblock->t.MJDN;
					SBASdata[pos].lastcovmatrix[(int)sbasblock->clockephemeriscovariance[0][IODPPOSITION]][j].SoD=sbasblock->t.SoD;

					//Leave sbasblock as it was
					sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]=sbasblock->clockephemeriscovariance[i][PRNMASKNUMBER]+1;
				}
				
				SBASdata[pos].IODPcovariance=sbasblock->clockephemeriscovariance[0][IODPPOSITION];

				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				break;
			case(IONOSPHERICGRIDPOINTSMASKS):
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
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].MJDN=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN;
					SBASdata[pos].oldlastmsgreceived[sbasblock->messagetype].SoD=SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD;

					



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
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;

				//No break here, so it will continue to process ionospheric delay corrections.
				//The reason for this is that when a new mask arrives, try to process all the data buffered fron the new mask
				/* Falls through. */ //To avoid warning -Wimplicit-fallthrough=
			case(IONOSPHERICDELAYCORRECTIONS):

				//First we save the data in the buffer "ionobuffered". Then, if we have the mask, the data is saved in the SBAS structure
				//This allows to save data received before having the iono mask, and when the iono band mask is available decode the data,
				//In this way, we don't need to wait first for the mask and then for the data for that iono band, decreasing the initialization time

				//Select the position for the buffer according to the PRN
				if(pos==0) {
					GEObuffer=0;
				} else {
					GEObuffer=sbasblock->PRN;
				}

				//We can come here also when we receive a mask message. We only have to buffer if the message received are iono delay corrections
				if(sbasblock->messagetype==IONOSPHERICDELAYCORRECTIONS) {
					currentbandnumber=(int)sbasblock->ionodelayparameters[0][BANDNUMBER];
					currentblockID=(int)sbasblock->ionodelayparameters[0][BLOCKID];
					//Copy values to the buffer
					for(i=0;i<15;i++) {
						for(j=0;j<7;j++) {
							ionobuffer[GEObuffer][currentbandnumber][currentblockID].ionodelayparameters[i][j]=sbasblock->ionodelayparameters[i][j];
							ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.MJDN=sbasblock->t.MJDN;
							ionobuffer[GEObuffer][currentbandnumber][currentblockID].t.SoD=sbasblock->t.SoD;
						}
					}

					ionobuffered[GEObuffer][currentbandnumber][currentblockID]=1;
				}


				for(i=0;i<11;i++) {
					for(m=0;m<14;m++) {
						//Check if we have data for the current band in any BlockID
						if(ionobuffered[GEObuffer][i][m]==1) {
							//Check if we have received the iono mask for this band number. Otherwise leave it in the buffer 
							if(SBASdata[pos].IGPbandreceived[i]==1) {
								//We have the iono mask for this band number. 
								j=(int)ionobuffer[GEObuffer][i][m].ionodelayparameters[0][BLOCKID];
								for(k=0;k<15;k++) {
									if(SBASdata[pos].IODImask==(int)ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
										//Data is from the current mask
										l=SBASdata[pos].BlockIDPlace2Grid[i][j][k];
										if(l==-1) continue;
										SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].IODImask;
									} else if (SBASdata[pos].oldIODImask==(int)ionobuffer[GEObuffer][i][m].ionodelayparameters[0][IODIPOS]) {
										//Data is from the old mask
										l=SBASdata[pos].oldBlockIDPlace2Grid[i][j][k];
										if(l==-1) continue;
										SBASdata[pos].IGP2Mask[i][l]=SBASdata[pos].oldIODImask;
									} else {
										//The IODI does not match the current band or we have not received any mask
										break;
									}
									SBASdata[pos].Ionodelay[i][l]=ionobuffer[GEObuffer][i][m].ionodelayparameters[k][IGPVERTICALDELAY];
									SBASdata[pos].IonoGIVE[i][l]=ionobuffer[GEObuffer][i][m].ionodelayparameters[k][GIVEVALUE];
									SBASdata[pos].Ionosigma[i][l]=ionobuffer[GEObuffer][i][m].ionodelayparameters[k][GIVEVARIANCE];
									SBASdata[pos].lastiono[i][l].MJDN=ionobuffer[GEObuffer][i][m].t.MJDN;
									SBASdata[pos].lastiono[i][l].SoD=ionobuffer[GEObuffer][i][m].t.SoD;

								}
								ionobuffered[GEObuffer][i][m]=0;
							} else {
								//We do not have the mask, so we cannot read any data for this band
								break;
							}
						} else {
							//No data for this bandnumber and BLockID
							continue;
						}
					}
				}
				break;
			case(RESERVED8):case(RESERVED11):case(RESERVED13):case(RESERVED14):case(RESERVED15):case(RESERVED16):case(RESERVED19):case(RESERVED20):case(RESERVED21):case(RESERVED22):case(RESERVED23):case(INTERNALTESTMESSAGE):case(NULLMESSAGE):
				//Messages with no data that do not have any effect
				//Update last received message
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].MJDN=sbasblock->t.MJDN;
				SBASdata[pos].lastmsgreceived[sbasblock->messagetype].SoD=sbasblock->t.SoD;
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
	char		word[MAX_INPUT_LINE];
	char		*wordlst[MAX_WORDS];
	char		format[MAX_INPUT_LINE];
	char		format2[MAX_INPUT_LINE];
	char		formataux[MAX_INPUT_LINE];
	int			len = 0;
	int			ret = 0;
	int			wordindex = 1;
	int			i;
	int			numwordsperline;
	int			numline = 0;
	
	wordlst[0] = NULL;
	while (getLNoComments(line,&len,fd)!=-1) {
		//Take out commas ',' and semicolon ';'
		for(i=0;i<len;i++) {
			if (line[i]==','||line[i]==';') {
				line[i]=' ';
			}
		}

		numwordsperline=0;
		word[0]='#';
		word[1]='\0';
		ret = sscanf(line,"%s",word);
		if ( ret ) {
			if ( word[0] != '#' ) { // It is not a comment
				numline++;
				numwordsperline++;
				wordlst[wordindex] = malloc(sizeof(char)*(strlen(word)+2)); // +2 for the '\0' and the '-' char
				strcpy(wordlst[wordindex],word);
				wordindex++;
				strcpy(format,"%*s");
				sprintf(formataux,"%s %%s",format);
				while(sscanf(line,formataux,word)==1) {
					numwordsperline++;
					if(numwordsperline>2) {
					}
					wordlst[wordindex] = malloc(sizeof(char)*(strlen(word)+1)); // +1 for the '\0'
					strcpy(wordlst[wordindex],word);
					wordindex++;
					sprintf(format2,"%s %%*s",format);
					sprintf(format,"%s",format2);
					sprintf(formataux,"%s %%s",format);
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
	
	wordlst[wordindex] = NULL;
/*
*/
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
				
	// Free memory
	for (i=0;i<wordindex;i++) {
		free (wordlst[i]);
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
	char 					line[MAX_INPUT_LINE];
	char					word[MAX_INPUT_LINE];
	char					*wordlst[MAX_WORDS];
	char					format[MAX_INPUT_LINE];
	char					format2[MAX_INPUT_LINE];
	char					formataux[MAX_INPUT_LINE];
	int						len = 0;
	int						ret = 0;
	int						wordindex = 1;
	int 					i,j,k,l;
	int						numwordsperline;
	int						currenterrortype,numwords;
	int						check=0;
	int						pos,numpos=0,measpos;
	int						start,end;
	int						Error2pos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS];
	int						seed;
	enum MeasurementType	measType;
	double					meas,sample;
	double					**SatMeasError;
	TTime					StartTime;
	TTime					EndTime;
	
	SatMeasError=NULL;
	if(endfile==0) { 
		for(i=0;i<MAX_WORDS;i++) {
			wordlst[i] = NULL;
		}

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
			word[0]='#';
			word[1]='\0';
			ret = sscanf(line,"%s",word);
			if (ret) {
				if (word[0]!='#') { // It is not a comment
					numline++;
					numwordsperline++;
					wordlst[wordindex] = realloc(wordlst[wordindex],sizeof(char)*(strlen(word)+2)); // +2 for the '\0' and the '-' char
					strcpy(wordlst[wordindex],word);
					wordindex++;
					strcpy(format,"%*s");
					sprintf(formataux,"%s %%s",format);
					while(sscanf(line,formataux,word)==1) {
						numwordsperline++;
						wordlst[wordindex] = realloc(wordlst[wordindex],sizeof(char)*(strlen(word)+1)); // +1 for the '\0'
						strcpy(wordlst[wordindex],word);
						wordindex++;
						sprintf(format2,"%s %%*s",format);
						sprintf(format,"%s",format2);
						sprintf(formataux,"%s %%s",format);
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
										UserError->System[i]=realloc(UserError->System[i],UserError->numactiveErrors[i]*sizeof(enum MeasurementType));
										UserError->PRN[i]=realloc(UserError->PRN[i],UserError->numactiveErrors[i]*sizeof(int));
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
							if(numwordsperline!=numwords+UserError->numcolumnstime) {
								// Free memory
								for (i=1;i<=wordindex;i++) {
									free (wordlst[i]);
									wordlst[i]=NULL;
								}
								continue;
							}
						} else if(strcasecmp(wordlst[1],"Ramp")==0) {
							currenterrortype=RAMP;
							numwords=NUMWORDSRAMP;
							if(numwordsperline!=numwords+UserError->numcolumnstime) {
								// Free memory
								for (i=1;i<=wordindex;i++) {
									free (wordlst[i]);
									wordlst[i]=NULL;
								}
								continue;
							}
						} else if (strcasecmp(wordlst[1],"Sinu")==0) {
							currenterrortype=SINUSOIDAL;
							numwords=NUMWORDSSINUSOIDAL;
							if(numwordsperline!=numwords+UserError->numcolumnstime) {
								// Free memory
								for (i=1;i<=wordindex;i++) {
									free (wordlst[i]);
									wordlst[i]=NULL;
								}
								continue;
							}
						} else if(strcasecmp(wordlst[1],"AWGN")==0) {
							currenterrortype=AWGN;
							numwords=NUMWORDSAWGN;
							if(numwordsperline!=numwords+UserError->numcolumnstime) {
								// Free memory
								for (i=1;i<=wordindex;i++) {
									free (wordlst[i]);
									wordlst[i]=NULL;
								}
								continue;
							}
						} else { 
							//Not supported model error. Ignore line
							// Free memory
							for (i=1;i<=wordindex;i++) {
								free (wordlst[i]);
								wordlst[i]=NULL;
							}
							continue;
						}

						//Transform date to MDJN,SoD
						if(UserError->timetype==0) {
							//Using YY/DoY/SoD
							StartTime.MJDN=(int)yeardoy2MJDN(atoi(wordlst[numwords+1]),atoi(wordlst[numwords+2]),atoi(wordlst[numwords+3]));
							StartTime.SoD=atof(wordlst[numwords+3]);
							if(UserError->lengthtype==1) {
								EndTime.MJDN=(int)yeardoy2MJDN(atoi(wordlst[numwords+4]),atoi(wordlst[numwords+5]),atoi(wordlst[numwords+6]));
								EndTime.SoD=atof(wordlst[numwords+6]);
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
							if(UserError->lengthtype==1) {
								EndTime=gpsws2ttime(atoi(wordlst[numwords+3]),atof(wordlst[numwords+4]));
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
							// Free memory
							for (i=1;i<=wordindex;i++) {
								free (wordlst[i]);
								wordlst[i]=NULL;
							}
							break;
						} else if(tdiff(&epoch->t,&EndTime)>=0) {
							// User model error has already finished. Skip the line
							// Free memory
							for (i=1;i<=wordindex;i++) {
								free (wordlst[i]);
								wordlst[i]=NULL;
							}
							continue;
						}

						//Check that we have a valid measurement
						measType=measstr2meastype(wordlst[3]);
						if (measType==NA || measType>=ENDMEAS) {
							// Invalid measurement or it is a combination. Skip the line
							// Free memory
							for (i=1;i<=wordindex;i++) {
								free (wordlst[i]);
								wordlst[i]=NULL;
							}
							continue;
						}

						// Allocate memory for new user-defined error
						UserError->activeErrorsStart[currenterrortype]=realloc(UserError->activeErrorsStart[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(TTime));
						UserError->activeErrorsEnd[currenterrortype]=realloc(UserError->activeErrorsEnd[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(TTime));
						UserError->measType[currenterrortype]=realloc(UserError->measType[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(enum MeasurementType));
						UserError->System[currenterrortype]=realloc(UserError->System[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(enum MeasurementType));
						UserError->PRN[currenterrortype]=realloc(UserError->PRN[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(int));
						UserError->ErrorParam[currenterrortype]=realloc(UserError->ErrorParam[currenterrortype],(UserError->numactiveErrors[currenterrortype]+1)*sizeof(double *));
						UserError->ErrorParam[currenterrortype][UserError->numactiveErrors[currenterrortype]]=malloc(sizeof(double)*NUMPARAMERRORS);

						//Copy user-defined error parameters to UserError structure
						memcpy(&UserError->activeErrorsStart[currenterrortype][UserError->numactiveErrors[currenterrortype]],&StartTime,sizeof(TTime));
						memcpy(&UserError->activeErrorsEnd[currenterrortype][UserError->numactiveErrors[currenterrortype]],&EndTime,sizeof(TTime));
						UserError->measType[currenterrortype][UserError->numactiveErrors[currenterrortype]]=measType;
						UserError->System[currenterrortype][UserError->numactiveErrors[currenterrortype]]=gnsschar2gnsstype(wordlst[2][0]);
						UserError->PRN[currenterrortype][UserError->numactiveErrors[currenterrortype]]=atoi(&wordlst[2][1]);

						for(i=0;i<NUMPARAMERRORS;i++) {
							if(currenterrortype!=SINUSOIDAL && i>0) break;
							UserError->ErrorParam[currenterrortype][UserError->numactiveErrors[currenterrortype]][i]=atof(wordlst[4+i]);
						}

						//Increment counter
						UserError->numactiveErrors[currenterrortype]=UserError->numactiveErrors[currenterrortype]+1;
						UserError->totalactiveErrors=UserError->totalactiveErrors+1;


					} //End if(numline==1)

					// Free memory
					for (i=1;i<=wordindex;i++) {
						free (wordlst[i]);
						wordlst[i]=NULL;
					}


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
					UserError->System[i]=realloc(UserError->System[i],UserError->numactiveErrors[i]*sizeof(enum MeasurementType));
					UserError->PRN[i]=realloc(UserError->PRN[i],UserError->numactiveErrors[i]*sizeof(int));
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
				for(k=0;k<MAX_MEASUREMENTS;k++) {
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
					meas=getMeasurementValue(epoch,UserError->System[i][j],k,UserError->measType[i][j]);
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
							epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].meas[measpos].value+=sample/epoch->measOrder[epoch->sat[(int)SatMeasError[pos][USREPOCHPOS]].GNSS].conversionFactor[UserError->measType[i][j]];
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
	


	if(feof(fd)>0) endfile=1;
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
    char            word[MAX_INPUT_LINE];
    char            *wordlst[MAX_WORDS];
    char            format[MAX_INPUT_LINE];
    char            format2[MAX_INPUT_LINE];
    char            formataux[MAX_INPUT_LINE];
	char			aux[100];
	double			r;
	double			PositionNEU[3],PositionXYZ[3];
	double			seconds;
	double			Interval;
    int             len = 0;
    int             ret = 0;
    int             wordindex = 1;
    int             i;
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

	//Initialize wordlst
	for(i=0;i<MAX_WORDS;i++) {
		wordlst[i] = NULL;
	}

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
		word[0]='#';
		word[1]='\0';
		ret = sscanf(line,"%s",word);
		if (ret) {
			if (word[0]!='#') { // It is not a comment
				numvalidline++;
				numwordsperline++;
				wordlst[wordindex] = realloc(wordlst[wordindex],sizeof(char)*(strlen(word)+2)); // +2 for the '\0' and the '-' char
				strcpy(wordlst[wordindex],word);
				wordindex++;
				strcpy(format,"%*s");
				sprintf(formataux,"%s %%s",format);
				while(sscanf(line,formataux,word)==1) {
					numwordsperline++;
					wordlst[wordindex] = realloc(wordlst[wordindex],sizeof(char)*(strlen(word)+1)); // +1 for the '\0'
					strcpy(wordlst[wordindex],word);
					wordindex++;
					sprintf(format2,"%s %%*s",format);
					sprintf(format,"%s",format2);
					sprintf(formataux,"%s %%s",format);
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
						// Free memory
						for (i=1;i<=wordindex;i++) {
						free (wordlst[i]);
						wordlst[i]=NULL;
						}
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
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else if (DataFormat==1) {
					//Year DoY SoD Lon Lat Height format
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN=(int)yeardoy2MJDN(atoi(wordlst[YearPos]),atoi(wordlst[DoYPos]),atoi(wordlst[SoDPos]));
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD=atof(wordlst[SoDPos]);
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
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else if (DataFormat==3) {
					//GPSWeek SoW Lat Lon Height format
					RefPosition->SP3->orbits.block[0][usedRecords].t=gpsws2ttime(atoi(wordlst[GPSWeekPos]),atof(wordlst[SoWPos]));
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
					if(strlen(wordlst[DatePos])!=10) {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[DatePos][4]!='/'||wordlst[DatePos][7]!='/') {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (strlen(wordlst[TimePos])!=12) {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[TimePos][2]!=':'||wordlst[TimePos][5]!=':'||wordlst[TimePos][8]!='.') {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					getstr(aux,wordlst[DatePos],0,4);
					tm.tm_year = atoi(aux)-1900;
					getstr(aux,wordlst[DatePos],5,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,wordlst[DatePos],8,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,wordlst[TimePos],0,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,wordlst[TimePos],3,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,wordlst[TimePos],6,6);
					tm.tm_sec  = atoi(aux);
					seconds = atof(aux);
					RefPosition->SP3->orbits.block[0][usedRecords].t.MJDN = MJDN(&tm);
					RefPosition->SP3->orbits.block[0][usedRecords].t.SoD = (double)(tm.tm_hour*3600 + tm.tm_min*60) + seconds;
					RefPosition->SP3->orbits.block[0][usedRecords].x[0]=atof(wordlst[XPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[1]=atof(wordlst[YPos]);
					RefPosition->SP3->orbits.block[0][usedRecords].x[2]=atof(wordlst[ZPos]);
				} else {
					//Date Time Lat Lon Height format
					if(strlen(wordlst[DatePos])!=10) {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[DatePos][4]!='/'||wordlst[DatePos][7]!='/') {
						sprintf(messagestr,"Date format must be in format YYYY/MM/DD. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (strlen(wordlst[TimePos])!=12) {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					} else if (wordlst[TimePos][2]!=':'||wordlst[TimePos][5]!=':'||wordlst[TimePos][8]!='.') {
						sprintf(messagestr,"Time format must be in format HH:MM:SS.zzz. Check line number %d in reference file [%s]",numfileline,filename);
						printError(messagestr,options);
					}
					getstr(aux,wordlst[DatePos],0,4);
					tm.tm_year = atoi(aux)-1900;
					getstr(aux,wordlst[DatePos],5,2);
					tm.tm_mon  = atoi(aux)-1;
					getstr(aux,wordlst[DatePos],8,2);
					tm.tm_mday = atoi(aux);
					getstr(aux,wordlst[TimePos],0,2);
					tm.tm_hour = atoi(aux);
					getstr(aux,wordlst[TimePos],3,2);
					tm.tm_min  = atoi(aux);
					getstr(aux,wordlst[TimePos],6,6);
					tm.tm_sec  = atoi(aux);
					seconds = atof(aux);
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
						//Current epoch is before or equal previous one. Show an error exit
						sprintf(messagestr,"All data lines must be sort in chronological order in [%s] file. Check line %d of file",filename,numfileline);
						printError(messagestr,options);
					}
					RefPosition->SP3->orbits.interval=min(RefPosition->SP3->orbits.interval,Interval);
				}

				usedRecords++;

				// Free memory
				for (i=1;i<=wordindex;i++) {
					free (wordlst[i]);
					wordlst[i]=NULL;
				}
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
