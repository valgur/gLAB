/****************************************************************************
 * Copyright & License:
 * ====================
 *
 *  Copyright 2009 - 2020 gAGE/UPC & ESA
 *     This file is part of gLAB's GUI.
 *
 *     gLAB's GUI is free software: you can redistribute it and/or modify
 *     it under the terms of the Lesser GNU General Public License as published by
 *     the Free Software Foundation, either version 3.
 *
 *     gLAB's GUI is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     Lesser GNU General Public License for more details.
 *
 *     You should have received a copy of the Lesser GNU General Public License
 *     along with gLAB's GUI.  If not, see <http://www.gnu.org/licenses/>.
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
 * Files: gLAB.pro coord_converter.h date_converter.h glab_gui.h adderror_rinex.cpp analysis.cpp
 *        compareOrbits.cpp converter.cpp coord_converter.cpp date_converter.cpp filter.cpp
 *        glab_gui.cpp input.cpp main.cpp modelling.cpp output.cpp preprocess.cpp showOrbits.cpp
 *        coord_converter.ui date_converter.ui glab_gui.ui
 *        gAGE.ico gage_logo.png gLAB.icns Header.png igp_grid.jpg Mainlogo.gif warning.png
 *
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
 ***************************************************************************/

 /***************************
 *       RELEASE_HISTORY
 * -------------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log: First version with Qt based GUI
 * -------------
 *          gLAB v5.1.0
 * Release: 2017/11/17
 * Change Log: Added Mac compatibility.
 *             Added links "ftp://lox.ucsd.edu/pub/rinex/" and "ftp://ftp.gfz-potsdam.de/GNSS".
 *             Added "UNAVCO'S Database RINEX Searcher" in the "Download data files" menu.
 *             Added "GFZRNX RINEX version converter" in the "File conversion tools" menu.
 *             Added progress bar when gLAB processing is launched (for all modes except Analysis).
 *             Added abort button when gLAB processing is launched (in all modes).
 *             Added "Start Time" and "End Time" options in the INPUT section.
 *             Added "Set start time of SBAS summary" option in the "SBAS Summary Options" groupbox.
 *             Added used MOPS in the SBAS options.
 *             Added options for allowing the user to enter user defined coordinates in Geodetic system.
 *             Added a new input for reference position file in "A Priori Receiver Position From".
 *             Added output reference file in the "Output" tab.
 *             Added contextual menu to all input files for opening them with a text editor. In Windows,
 *               input files are opened with WordPad due to this program supports Linux end of file format.
 *             Added Date and coordinate converter in the Help menu.
 *             Added "File Standards" in the Help menu with links to several GNSS file standards.
 *             Added "Reference Position File Manual" in the "User manuals" section.
 *             Added option 'Write only DGNSS solutions' in output SP3 files in DGNSS mode.
 *             In the "Condition" combo box with the output message list (in the Analysis mode), now
 *               each item has the tooltip of its correspondent message.
 *             Tooltip for OUTPUT message has been adjusted to fit in typical laptop screen (without
 *               modifying the content).
 *             All date boxes in the GUI now have a button to display a calendar for date selection.
 *             SNR deselection is now named "SNR Mask", and allows to set a user defined threshold.
 *             Changed SBAS and DGNSS defaults for Data Gap, SNR and N-consecutive. In both modes,
 *               SNR mask is set to 33 dbHz, Data Gap to 10 seconds and N-consecutive is disabled.
 *             Changed default standard deviation from 1 to 5 metres for single frequency code, from
 *               1 to 3 metres for PC and from 0.01 to 0.03 metres for LC.
 *             Changed option name from 'Calculate - Specify' to 'Calculate - User defined'.
 *             Option "Estimate wet troposhere residual" in filter will automatically disable if
 *               troposphere model is disabled.
 *             In RTCM conversion mode, gLAB will automatically replace output files instead of asking.
 *             When opening a user manual, gLAB will overwrite any previous manual instead of using
 *               the old version (if it existed).
 *             Size of "A Priori Receiver Position From" has been fixed in order to avoid resizing
 *               when changing between options.
 *             The template "Orbit and Clock Comparison" will now set the "Source File" path to the
 *               processing mode output file path (plus "diff.out" filename) instead of the
 *               application directory when the comparison mode output file is empty.
 *             Fixed bug that showed an error of "GPS Receiver Type file" not found when user had
 *               selected "GPS Receiver Manual Selection".
 *             Fixed bug that showed a wrong error regarding to P1-P2 DCB correction selection.
 *             Fixed bug showing an error message twice when gLAB ended with an error and no data
 *               was written to the output file.
 *             Fixed bug passing wrong parameters to gLAB core when receiver antenna phase center
 *               correction was set to "Specify Offset".
 *             Fixed bug when loading cycle-slip detectors options from configuration file.
 *             Fixed bug reading configuration files when options had more than one space
 *               between them or line started with a space.
 *             Updated/corrected several tooltips.
 * -------------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: Added link to GPS Constellation Status file
 *               "http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt"
 *             Added "Add User to RINEX" mode. In this mode, gLAB reads an observation
 *               file, an user added error file and writes the a RINEX observation file
 *               with the same data but with the user added error in the measurements.
 *             Analysis page now allows to do plots without selecting any condition.
 *             ARP correction is now enabled by default in SBAS and DGNSS modes.
 *             "Satellite Options" groupbox in Preprocess tab will now keep all elements
 *               aligned to top (instead of centering them in height) when the "Discard
 *               Unhealthy Satellites (Brodcast only)" option is hidden.
 *             Updated/corrected several tooltips.
 * -------------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: Added extension type ".YYi" in the "RINEX file extension types" help menu.
 *             Changed ANTEX ftp link from "ftp://igscb.jpl.nasa.gov/igscb/station/general/pcv_archive/"
 *               to "ftp://ftp.igs.org/pub/station/general/pcv_archive/" (the URL of the link had changed).
 *             Changed DCB ftp link from "ftp://ftp.unibe.ch/aiub/CODE" to
 *               "ftp://ftp.aiub.unibe.ch/CODE/ (the URL of the link had changed).
 *             If P1-C1 correction is disabled or set to flexible in the MODELLING, it will now
 *               allow to leave the P1-C1 DCB file blank (previously it was only allowed to be
 *               empty if GPS Receiver Type was manually set to type 2).
 *             Fixed parameter '-pre:setrectype' appearing in the INPUT section instead of the
 *               preprocess section when creating a configuration file.
 *             Fixed parameter '-pre:setrectype' not appearing in configuration file when the
 *               GUI option "Generate minimum configuration" was disabled and this option had
 *               the default value (therefore it did not affect the processing).
 *             Updated/corrected several tooltips.
 * -------------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log: Removed link "ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMF/" in
 *               RINEX navigation and SBAS files links list. The new links are with
 *               "ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/", which were
 *               already in gLAB.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log: Added link "ftp://cddis.gsfc.nasa.gov/pub/gps/products/mgex/" in the
 *               "Other files" download data menu referred as "SINEX BIAS OSB files
 *               (multiconstellation absolute DCBs):".
 *             Added link "https://www.enri.go.jp/cnspub/sat/data/geonav/" in the
 *               "RINEX Navigation version 2" download data menu for QZSS GEO navigation files.
 *             Added link "https://www.enri.go.jp/cnspub/sat/data/rinex/" in the
 *               "RINEX Observation version 2" download data menu for QZSS 1Hz observation
 *               files (it is an unofficial RINEX 2 version).
 *             Added link "ftp://cddis.gsfc.nasa.gov/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/"
 *               in "RINEX Navigation files version 3" download data menu for navigation files
 *               with CNAV and LNAV messages.
 *             Added links "ftp://igs.bkg.bund.de/IGS/BRDC/" and "ftp://igs.bkg.bund.de/EUREF/BRDC/" in the
 *               "RINEX Navigation version 3" download data menu in "All or Mixed constellation RINEX
 *               Navigation files:" section.
 *             Added link "ftp://igs.bkg.bund.de/MGEX/BRDC/" in the "RINEX Navigation version 3" download
 *                data menu in "Mixed constellation RINEX Navigation files:" section.
 *             Added ".YYx" extension to "RINEX file extension types" help menu.
 *             Added "*n.rnx" and ".??p" extensions when selecting RINEX navigation files in the file explorer.
 *             Added "*o.rnx"extension when selecting RINEX observation files in the file explorer.
 *             Added option "Discard Satellites with a given UDREI" in SBAS advanced option.
 *             Added option "Sigma offset if MT10 is not used:" in SBAS advanced option.
 *             Added Summary option in "OUTPUT" tab.
 *             Changed link from "ftp://cddis.gsfc.nasa.gov/gnss/data/campaign/mgex/daily/rinex3/2014/brdm/" to
 *               "ftp://cddis.gsfc.nasa.gov/gnss/data/campaign/mgex/daily/rinex3/2013/brdm/". The link points to
 *               the same URL, except for the year, which is 2013 instead of 2014. This is done in order to point
 *               to the oldest data available, which is from year 2013.            
 *             Changed ".*GPS_Receiver_Types" to ""*GPS_Receiver_Types*" regular expression in file explorer
 *               in order to show files named as "GPS_Receiver_Types" (with no extension).
 *             Changed link name in the "Other files" download data menu from "Multiconstellation DCB files:"
 *               to "SINEX BIAS DSB files (multiconstellation DCBs for converting measurements):" in order to
 *               show an accurate description of the file content.
 *             Changed description of ".YYq" extension in "RINEX file extension types" help menu in order to
 *               reflect that there are also QZSS navigation file in an unofficial 2.12 RINEX format.
 *             Changed "All files (*.*)" extensions in all file explorers to "All files (*)" in order to
 *               be able to select files without extension.
 *             User can now introduce decimal number in the user defined SNR threshold.
 *             When opening a file explorer for selecting a reference position file, text and SP3 file types
 *               are now grouped into one single file type instead of different file types.
 *             If gLAB core is executed in any mode in the GUI, and it exits with an ERROR message before
 *                creating the output file (that is, the ERROR is written to standard output, the GUI
 *                will now be able to read the ERROR message and show it to the user.
 *             Removed units of GDOP option in "Filter" tab and in the Analysis mode (Dilution of Precision
 *               template). The previous unit was meters, when this measurement is adimensional.
 *             Removed SBAS summary groupbox in SBAS option in the "MODELLING" tab.
 *             Start gLAB image now covers the full extent of the "INPUT" tab instead of leaving some white
 *               space on the bottom.
 *             Fixed groupboxes in the right column not being aligned to the top in Windows and Linux.
 *             Fixed bad layout of satellite selection button in Mac.
 *             Fixed labels and textboxes in the "Ionosphere Source" in the "Input" tab sometimes showing
 *               with a smaller size than the rest of the elements or not being correctly centered.
 *             Fixed incorrect unchecking of radioButtons "StdDev from SBAS messages" and StdDev from
 *               DGNSS "Filter" tab after being clicked. This radioButtons have to be always checked
 *               (is the only option for the standard deviaton in SBAS and DGNSS modes).
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/03/09
 * Change Log: Added links "ftp://icvficheros.icv.gva.es/Datos/", "ftp://rgapa.cartografia.asturias.es/RINEX/" and
 *             "ftp://ftp.geodesia.ign.es/ERGNSS/" in the menu "RINEX files from Institutions->Spain"
 *             Added menu "Coastal Services" inside the "RINEX files from Institutions" menu.
 *             Added link "ftp://ftp.sonel.org/gps/data/" in the "Coastal Services" menu.
 *             Added a second text box in the "Window Size" line in the "Print Summary" groupbox in the OUTPUT section.
 *               This second text box is for setting the window size for maritime continuity risk computation.
 *             Added button "Geoid Height" in the KML options for applying EGM96 geoid model when writing the coordinates
 *               to the KML file.
 *             Added new groupbox "DOP Filters" in the FILTER tab in order to put all DOP filter options.
 *             Added buttons "Max. HDOP", "Max.PDOP" and "HDOP OR PDOP" in the "DOP Filters" groupbox.
 *             Added new text box for the window size in the "Summary" options. This box is for setting the value of the
 *               fixed window.
 *             Changed "Max. GDOP" options from the "Other Options" groupbox to the "DOP Filters" groupbox.
 *             Changed "Sliding Window Size" label to "Window Size (Sliding/Fixed)" in order to the account for the new
 *               method for computing the continuity risk.
 *             Changed link from "ftp://geofons.icc.cat/rinex/horari_1s/" to "ftp://geofons.icc.cat/rinex/" in the menu
 *               "RINEX files from Institutions->Spain"
 *             Changed label name from "Sliding Window Size" to "Window Size" in the "Print Summary" groupbox in the
 *               OUTPUT section. This is due there are two text boxes, one for each mode of computing the continuity
 *               risk. The new mode, the maritime mode, does not use a sliding window.
 *             Reduced size of "SBAS messages" and "DGNSS messages" groupbox in the OUTPUT tab in order to leave more
 *               space to the "Summary" groupbox.
 *             Changed SBAS maritime default options. Now, in addition to disabling MT10, MT 28 and MT28, it will also enable
 *               GEO switching, HDOP filter, PDOP filter, "HDOP OR PDOP" option and also set both alarm limits to 100Km and the
 *               window sizes to 900.
 *             Disabled check for non-ASCII characters in filenames. If your system terminal can handle the non-ASCII characters,
 *               gLAB will also handle them, and viceversa.
 *             In Windows, the option "Expand figure to Margin" in the Analysis page has been hidden, as the python version used
 *               in Windows does not support this option.
 *             In Linux and Mac, if Stanford-ESA, KML output, "TimeStamp" and "Range" options are all enabled, the checkbox
 *               "Geoid Height" and the label "Decimation" will change to "Geoid H" and "Dec" respectively for fitting
 *               in the screen.
 *             Fixed bug that made not to set KML timestamp options when running gLAB, showing the command line
 *               instruction or creating the configuration file.
 *             Fixed bug that made not check the "Range" button inside the KML timestamps when loading a configuration
 *               file.
 *             Fixed bug that made not to unhide the text box with the number of epochs to reach steady state in the FILTER tab
 *               when the DGNSS template was set.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/10/23
 * Change Log: First gLAB version where the GUI is also compiled for ARMv7(hf) and aarch64(ARMv8 64bit) in Linux platforms.
 *             Added link "ftp://cddis.gsfc.nasa.gov/pub/gps/products/mgex/" in the menu "Download Data: Precise Files".
 *             Added links "https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs14.atx" and
 *               "https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs08.atx" in the menu "Download Data: Other Files".
 *             Added manual "gLAB command line SBAS maps description" in the menu "User manuals".
 *             Added option "Select Best GEO" in SBAS options.
 *             Changed "Runge-Kutta" effect to "Runge effect" in all the tooltips.
 *             Changed error message when generating equivalent command line instructions. Instead of "configuration file again"
 *               the text is "command line instruction again".
 *             In Linux, system library "libjasper" is now statically linked, as this library is no longer provided in Ubuntu 18.
 *             Fixed compilation of gLAB GUI in Qt5.10 or greater (in these Qt versions it was necessary to add the
 *               preprocessor statement "#include <QDoubleValidator>" in header files glab_gui.h and coord_converter.h)
 *             Fixed incorrect tab order in several elements in the GUI.
 *             When compiling in Linux, the output filename will change according to the platform being built (x86,x86_64, ARMv7hf, ARM64)
 *             Updated tooltips to indicate that all time tags are in GPS time.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log: Added link to ANTEX standard description file in menu "Help->File Standards".
 *             Added link "ftp://cddis.gsfc.nasa.gov/pub/gps/products/" for SINEX files in the menu "Download Data: Precise Files".
 *             Added missing tooltips for "Constellation Letter" and "PRN Number" in the "SP3 File" options of the OUTPUT tab.
 *             In 64 bit Windows, the GUI is now built under Qt 5.12.1 (64 bit). 32 bit Windows remain in Qt 5.7.1. The upgrade
 *               of Qt version fixes the startup crash that ocurred sometimes.
 *             Changed default SBAS GEO selection to "Highest Elevation" (previous value was "First Read").
 *             Changed default SBAS switching cooltime to 0 (previous value was 20 seconds).
 *             Fixed bug which did not allow the user to select "Class 1" Airborne Receiver Type in SBAS mode.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.4.2
 * Release: 2019/03/08
 * Change Log: Added "Show K factor values" groupbox under the SBAS Advanced options for setting the K factor values
 *               used for computing the protection levels.
 *             Added third term for user defined "Fixed Sigma Multipath" for SBAS receiver. This additional term allows
 *               to set the factor dividing the elevation inside the exponential.
 *             Changed displayed units for elevation based weights in the FILTER tab. Previously the unit was "metres"
 *               for all terms, but the correct units are "metres" for the first two terms and "degrees" for the last term.
 *             Changed gLAB paper citation from:
 *                 Sanz, J.; Rovira-Garcia, Adria.; Hernandez, M.; Juan, J.; Ventura-Traveset, J.; Lopez, C.; Hein, G.
 *                 The ESA/UPC GNSS-Lab Tool (gLAB): An advanced educational and professional package for GNSS data processing and analysis.
 *                 6th ESA Workshop on Satellite Navigation Technologies Multi-GNSS Navigation Technologies.
 *                 Proceedings ISBN: 978-1-4673-2010-8, DOI: 10.1109/NAVITEC.2012.6423100. Noordwijk, the Netherlands. December 2012.
 *               To the following one:
 *                 Ibáñez D., Rovira-García A., Sanz J., Juan JM., Gonzalez-Casado G., Jimenez-Baños D., López-Echazarreta C., Lapin I.
 *                 The GNSS Laboratory Tool Suite (gLAB) updates: SBAS, DGNSS and Global Monitoring System.
 *                 9th ESA Workshop on Satellite Navigation Technologies (NAVITEC2018), Noordwijk, The Netherlands.
 *                 December 5 - 7, 2018. DOI: 10.1109/NAVITEC.2018.8642707.
 *             Fixed parameter for Sigma noise for user defined receiver being set when it was disabled and viceversa.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.4.3
 * Release: 2019/03/20
 * Change Log: Added "IGS Website with RINEX standards" with a link to an IGS website with links to RINEX standards in
 *               the "File Standards" help menu.
 * -----------
 *          gLAB v5.4.4
 * Release: 2019/03/20
 * Change Log: Added missing check for minimum value for "N-sample" field in L1-C1 cycle-slip detector.
 *             The gLAB GUI in Linux x86_64, ARMv7 and ARM64 is now built with libmng2 library linked statically.
 *               Therefore, the gLAB GUI can now be run in Linux operative systems that do not have libmng2 available, such as
 *               some versions of Debian.
 *             Changed gAGE URLs from "www.gage.es" to "gage.upc.es".
 *             Fixed incorrect error message when gLAB was unable to connect to gAGE servers when checking for new gLAB versions.
 *             Fixed incorrect error message for "N-sample" field in Melbourne-Wubbenna cycle-slip detector. The text had
 *               "N-sample cannot be equal or greater than 2" when it has to be "N-sample cannot be less than 2".
 *             Fixed incorrect check of "N-sample" field in Geometry-free cycle-slip detector. This made to accept any value
 *               greater than 0, when the minimum acceptable value is 2.
 * -----------
 *          gLAB v5.5.0
 * Release: 2020/11/13
 * Change Log: Added NeQuick ionosphere model.
 *             Added menu "Contact Us" inside Help menu.
 *             Added link "ftp://gssc.esa.int/gnss/data/daily/" in menus "Download Data: RINEX Observation Files Version 2", 
 *               "Download Data: RINEX Observation Files Version 3", "Download Data: RINEX Navigation Files Version 2" and 
 *               "Download Data: RINEX Navigation Files Version 3".
 *             Added link "ftp://gssc.esa.int/gnss/data/highrate/" in menus "Download Data: RINEX Observation Files Version 2" 
 *               and "Download Data: RINEX Observation Files Version 3".
 *             Added link "ftp://gssc.esa.int/gnss/products/" in menu "Download Data: Precise Files".
 *             Added link "ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/" in "Download Data: RINEX Observation Files Version 2",
 *               "Download Data: RINEX Observation Files Version 3" and "Download Data: RINEX Navigation Files Version 2".
 *             Added link "ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/highrate/" in menu "Download Data: RINEX Observation Files Version 2".
 *             Added link "ftp://gssc.esa.int/gnss/products/ionex/" in menu "Download Data: Other Files".
 *             Changed "GPS Receiver Types" link in "Other files" from "https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/GPS_Receiver_Types.gz"
 *               to "https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/GPS_Receiver_Types.gz".
 *             Changed "Valencian Cartographic Institute" credentials page from "http://icverva.icv.gva.es:8080/es/rinex" to
 *               "http://www.icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex".
 *             Changed the button text from "OK" to "Close" in "GNSS Date Converted" and "GNSS Coordinate Converter".
 *             Changed default date in "GNSS Date Converter" from 06/01/1980 to 01/01/2000. This is to be able to set a date between the 1st and th 5th
 *               month without having to change the month or year first, as in these cases changing first the day was blocked at it would result in a
 *               data prior to 06/01/1980, which is not allowed.
 *             Removed links "ftp://igs.bkg.bund.de/IGS/highrate_v3/" and "ftp://igs.bkg.bund.de/MGEX/highrate_v3/" from RINEX observation files version 3.
 *             Removed "EGNOS NTRIP servers" ("https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_egnos-ip.htm"), "FAMOS NTRIP servers"
 *               ("https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_famos.htm") and "World-Wide NTRIP servers"
 *               ("https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_world-wide.htm") from "List of NTRIP servers" menu.
 *             Fixed generation of wrong parameter "-input:klb" instead of "-input:bds" when BeiDou ionosphere model was selected and its
 *               model parameters were read from a separate RINEX navigation file.
 *             Fixed ionosphere model not set to "Klobuchar (Beidou)" when loading a configuration file with parameter "-input:bds".
 *             Fixed incorrect error message "MODEL: Klobuchar iono selected in PPP mode, but no external navigation file given" shown when processing
 *               in with precise products and using Klobuchar ionosphere model when it should have not shown any error.
 *             Fixed missing tooltip in "Interpolation Degree" label in "A Priori Receiver Form" when DGNSS mode was enabled.
 *             Updated/corrected several tooltips.
 * -----------
 *          gLAB v5.5.1
 * Release: 2020/12/11
 * Change Log: Added link "ftp://ftp.sirgas.org/pub/gps/SIRGAS/" in menu "Download Data: Precise Files".
 *             Added link "ftp://gssc.esa.int/gnss/products/1962/mgex/" in menu "Download Data: Other Files".
 *             Changed CDDIS link in "Download Data: RINEX Observation Files Version 2" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/" to
 *               "https://cddis.nasa.gov/archive/gnss/data/daily/".
 *             Changed CDDIS link in "Download Data: RINEX Observation Files Version 2" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/highrate/" to
 *               "https://cddis.nasa.gov/archive/gnss/data/highrate/".
 *             Changed CDDIS link in "Download Data: RINEX Observation Files Version 3" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/campaign/mgex/daily/rinex3/"
 *               to "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/".
 *             Changed CDDIS link in "Download Data: RINEX Navigation Files Version 2" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/" to
 *               "https://cddis.nasa.gov/archive/gnss/data/daily/".
 *             Changed CDDIS link in "Download Data: RINEX Navigation Files Version 3" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/" to
 *               "https://cddis.nasa.gov/archive/gnss/data/daily/".
 *             Changed CDDIS link in "Download Data: RINEX Navigation Files Version 3" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/campaign/mgex/daily/rinex3/"
 *               to "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/".
 *             Changed CDDIS link in "Download Data: RINEX Navigation Files Version 3" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/campaign/mgex/daily/rinex3/2013/brdm/"
 *               to "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2013/brdm/".
 *             Changed CDDIS link in "Download Data: RINEX Navigation Files Version 3" from "ftp://cddis.gsfc.nasa.gov/pub/gps/data/daily/campaign/mgex/daily/rinex3/2014/cnav/"
 *               to "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/".
 *             Changed CDDIS link in "Download Data: Precise Files" from "ftp://cddis.gsfc.nasa.gov/pub/gnss/products/" to "https://cddis.nasa.gov/archive/gnss/products/".
 *             Changed CDDIS link in "Download Data: Precise Files" from "ftp://cddis.gsfc.nasa.gov/pub/glonass/products/" to
 *               "https://cddis.nasa.gov/archive/glonass/products/".
 *             Changed CDDIS link in "Download Data: Precise Files" from "ftp://cddis.gsfc.nasa.gov/pub/gps/products/mgex/" to
 *               "https://cddis.nasa.gov/archive/gnss/products/mgex/".
 *             Changed CDDIS link in "Download Data: Other Files" from "ftp://cddis.gsfc.nasa.gov/pub/gps/products/ionex/" to
 *               "https://cddis.nasa.gov/archive/gnss/products/ionex/".
 *             Changed CDDIS link in "Download Data: Other Files" from "ftp://cddis.gsfc.nasa.gov/pub/gps/products/troposphere/new/" to
 *               "https://cddis.nasa.gov/archive/gnss/products/troposphere/new/".
 *             Changed CDDIS link in "Download Data: Other Files" from "ftp://cddis.gsfc.nasa.gov/pub/gps/products/mgex/dcb/" to
 *               "https://cddis.nasa.gov/archive/gnss/products/mgex/dcb/".
 *             Changed CDDIS link in "Download Data: Other Files" from "ftp://cddis.gsfc.nasa.gov/pub/gps/products/mgex/" to
 *               "https://cddis.nasa.gov/archive/gnss/products/mgex/".
 *             Changed incorrect link from "ftp://gssc.esa.int/gnss/products/ionex/" to "ftp://gssc.esa.int/gnss/products/troposphere_zpd/" in "Download Data: Other Files" menu.
 *             Removed blank line between "ZTD (troposphere)" links in "Download Data: Other Files" menu.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#include "glab_gui.h"
#include "ui_glab_gui.h"
#include "math.h"

int DateConverterWindow=0;

// GUI constructor
gLAB_GUI::gLAB_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gLAB_GUI) {

    ui->setupUi(this);

    //Set specific options for Menu bar in Mac so it looks line a native Mac program (and in Qt>=5.9.0 maskes key shortcuts work again)
    #ifdef Q_OS_MAC
        this->setWindowModality(Qt::NonModal);
    #elif !defined Q_OS_MAC
        ui->menuBar->setNativeMenuBar(false);
    #endif

    #ifdef Q_OS_MAC
        //Set working directory for Mac (so it does not start in "/"). It is also useful for Summer school data
        if (this->directoryExists("/Applications/gLAB_GUI.app/Contents/MacOS/WORK_FILES")==true) {
            QDir::setCurrent(QStringLiteral("/Applications/gLAB_GUI.app/Contents/MacOS/WORK_FILES"));
        } else {
            QDir::setCurrent(QDir::homePath());
        }
        //Force size of groupbox groupBoxSatSel to fit the buttons of each PRN
        //IMPORTANT: Buttons height and width need to be fixed, otherwise they will expand
        //making the buttons stay on top of each other (bug only on Mac)
        ui->groupBoxSatSel->setMinimumWidth(448);
        ui->groupBoxSatSel->setMinimumHeight(303);
        ui->stackedWidgetPRNButtons->setMinimumWidth(424);
        ui->stackedWidgetPRNButtons->setMinimumHeight(210);
        ui->page_11->setMinimumWidth(424);
        ui->page_11->setMinimumHeight(210);
    #endif

    //Set global variables
    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 0;
    WriteAllParameters=0;    
    GreenColor = "#00ff00";
    RedColor = "#ff0000";
    abort=0;
    SBASmaritime=0;

    // Set the text size depending on the Operating System
    this->setCorrectSizes();

    //Manually set size of label labelStfdESAPlotFile (so it is aligned with label labelStfdESADataFile) in Windows
    #ifdef Q_OS_WIN32
        ui->labelStfdESAPlotFile->setMinimumWidth(114);
    #endif

    //Manually set size of labels in User added error mode so all lineEdits are aligned (in Windows text is smaller)
    #ifdef Q_OS_WIN32
        ui->labelAddErrorObservationFile->setMinimumWidth(115);
        ui->labelAddErrorUserAddedErrorFile->setMinimumWidth(115);
        ui->labelAddErrorRinexOutputFile->setMinimumWidth(115);
        ui->labelAddErrorOutputFile->setMinimumWidth(115);
    #endif

    //Hide "Expand Figure to Margin" button in 32-bit Windows as it has never worked in Windows (as it uses python 2.6, and this option is supported in 2.7+)
    //64 bit windows now use py
    #ifdef Q_OS_WIN32
        if(this->fileExists(QString(QDir::toNativeSeparators(qApp->applicationDirPath() + "\\graph\\graph.exe")))==false) {
            ui->checkBoxExpandFigureToMargin->setChecked(false);
            ui->checkBoxExpandFigureToMargin->setHidden(true);
        }
    #endif

    // Current version and revision
    version = 5.5;
    revision = 1;

    // Set the window title
    //this->setWindowTitle(QString("gLAB v%1.%2 BETA (DO NOT DISTRIBUTE)").arg(version, 3, 'f', 1, '0').arg(revision));
    this->setWindowTitle(QString("gLAB v%1.%2").arg(version, 3, 'f', 1, '0').arg(revision));

    // Set the header image
    QPixmap pix(":/data/Header.png");
    ui->labelHeader->setScaledContents(true);
    ui->labelHeader->setPixmap(pix);

    // Set the Main logo image
    QPixmap pixMainLogo(":/data/MainLogo.gif");
    ui->labelMainLogo->setScaledContents(true);
    ui->labelMainLogo->setPixmap(pixMainLogo);

    //Add function for the event of a tab being clicked
    connect(ui->tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(tabClicked()));

    //This is to force the QStringList configFileName set space for six positions (each one for a different mode)
    configFileName << "" << "" << "" << "" << "" << "";

    // Set the Positioning mode
    this->on_actionPositioning_triggered();

    //Hide Output Satellite velocity in Positioning and Show Orbit modes (maybe in future versions it is used)
    ui->frameOutputSatVel->setHidden(true);
    ui->groupBoxSatVelShowOrbit->setHidden(true);


    // Set the background colour to both Analysis and Converter
    //White colour
    //ui->pagePositioning->setStyleSheet("#pagePositioning{background-color: rgb(252, 249, 246);}");/
    //ui->pageAnalysis->setStyleSheet("#pageAnalysis{background-color: rgb(252, 249, 246);}");/
    //ui->pageConverter->setStyleSheet("#pageConverter{background-color: rgb(252, 249, 246);}");
    //ui->pageCompareOrbits->setStyleSheet("#pageCompareOrbits{background-color: rgb(252, 249, 246);}");
    //ui->pageShowOrbits->setStyleSheet("#pageShowOrbits{background-color: rgb(252, 249, 246);}");
    //ui->pageAddError->setStyleSheet("#pageAddError{background-color: rgb(252, 249, 246);}");
    //Grey-background colour
    ui->pagePositioning->setStyleSheet("#pagePositioning{background-color: rgb(239, 235, 231);}");
    ui->pageAnalysis->setStyleSheet("#pageAnalysis{background-color: rgb(239, 235, 231);}");
    ui->pageConverter->setStyleSheet("#pageConverter{background-color: rgb(239, 235, 231);}");
    ui->pageCompareOrbits->setStyleSheet("#pageCompareOrbits{background-color: rgb(239, 235, 231);}");
    ui->pageShowOrbits->setStyleSheet("#pageShowOrbits{background-color: rgb(239, 235, 231);}");
    ui->pageAddError->setStyleSheet("#pageAddError{background-color: rgb(239, 235, 231);}");

    //ui->tabWidget->setStyleSheet("QTabBar::tab#tabWidget{background: rgb(239, 235, 231)QTabBar::tab#tabWidget:selected,QTabBar::tab#tabWidget:hover{background: rgb(239, 235, 231)");
    /*ui->tabInput->setStyleSheet("#tabInput{background-color: rgb(239, 235, 231);}#tabInput:tab:selected{background: rgb(239, 235, 231);}");
    ui->tabPreprocess->setStyleSheet("#tabPreprocess{background-color: rgb(239, 235, 231);}");
    ui->tabModelling->setStyleSheet("#tabModelling{background-color: rgb(239, 235, 231);}");
    ui->tabFilter->setStyleSheet("#tabFilter{background-color: rgb(239, 235, 231);}");
    ui->tabOutput->setStyleSheet("#tabOutput{background-color: rgb(239, 235, 231);}");*/

    // Radiobutton behaviour with modes
    QActionGroup *myGroupMode = new QActionGroup(this);
    myGroupMode->addAction(ui->actionAnalysis);
    myGroupMode->addAction(ui->actionPositioning);
    myGroupMode->addAction(ui->actionConverter);
    myGroupMode->addAction(ui->actionCompare_Orbits);
    myGroupMode->addAction(ui->actionShow_Orbits);
    myGroupMode->addAction(ui->actionAdd_User_Error_to_RINEX);

    // Radiobutton behaviour with templates
    QActionGroup *myGroupTemplate = new QActionGroup(this);
    myGroupTemplate->addAction(ui->actionSPP);
    myGroupTemplate->addAction(ui->actionPPP);
    myGroupTemplate->addAction(ui->actionSBAS);
    myGroupTemplate->addAction(ui->actionDGNSS);

    // Expand the tabs to the window width
    ui->tabWidget->installEventFilter(new ResizeFilter(ui->tabWidget));

    // Define Scroll bar for modelling and fix colors on Scroll Area within Modelling tab
    ui->scrollAreaModelling->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaWidgetContentsModelling->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");

    //Make Message Box text selectable
    qApp->setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    // Callback instance to control all tooltips (active/inactive and color)
    qApp->installEventFilter(this);
    //qApp->setStyleSheet("QToolTip{color: black; background-color: #2a82da; border: 1px solid black;}");

    //Set Analysis conditons comboBox tooltips for each item and each plot
    this->set_conditionsComboBoxPlot1_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot2_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot3_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot4_OutputMessagesTooltips();

    ///INPUT TAB CONTEXT MENUS
    //Set right click menu for Input RINEX observation file label
    ui->labelInputObservationFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputObservationFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexObsFileMenu);
    //Set right click menu for Input ANTEX file checkbox
    ui->checkBoxAntex->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxAntex,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxInputANTEXFileMenu);
    //Set right click menu for Input RINEX navigation file label
    ui->labelInputRinexNavFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFileMenu);
    //Set right click menu for Input SP3 Orbits & clocks file label
    ui->labelInputSP3OrbitsClocksFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSP3OrbitsClocksFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSP3OrbitsClocksFileMenu);
    //Set right click menu for Input SP3 Orbits file label
    ui->labelInputSP3OrbitsFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSP3OrbitsFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSP3OrbitsFileMenu);
    //Set right click menu for Input clocks file label
    ui->labelInputClkFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputClkFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputClocksFileMenu);
    //Set right click menu for Input SINEX file label
    ui->labelInputSinexFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSinexFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSINEXFileMenu);
    //Set right click menu for Input SBAS file label
    ui->labelInputSBASFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSBASFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSBASFileMenu);
    //Set right click menu for Input DGNSS file ComboBox
    ui->comboBoxRefStation->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->comboBoxRefStation,&QComboBox::customContextMenuRequested,this,&gLAB_GUI::comboBoxRefStationFileMenu);
    //Set right click menu for Input Iono RINEX navigation file label
    ui->labelInputRinexNavIonoFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavIonoFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavIonoFileMenu);
    //Set right click menu for Input IONEX file label
    ui->labelInputIonexIonoFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputIonexIonoFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputIonexIonoFileMenu);
    //Set right click menu for Input Iono SBAS file label
    ui->labelInputSbasIonoFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSbasIonoFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSbasIonoFileMenu);
    //Set right click menu for Input DCB P1-C1 file label
    ui->labelInputDCBP1C1File->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputDCBP1C1File,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputDCBP1C1FileMenu);
    //Set right click menu for Input GPS Receiver Type file label
    ui->labelInputGPSRecFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputGPSRecFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputGPSRecFileMenu);
    //Set right click menu for Input DCB P1-P2 RINEX navigation file label
    ui->labelInputRinexNavDCBFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavDCBFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavDCBFileMenu);
    //Set right click menu for Input DCB P1-P2 file label
    ui->labelInputDCBP1P2File->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputDCBP1P2File,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputDCBP1P2FileMenu);
    //Set right click menu for Input IONEX DCB file label
    ui->labelInputIonexDCBFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputIonexDCBFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputIonexDCBFileMenu);
    //Set right click menu for Input User Added Error file label
    ui->labelInputUserAddedErrorFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputUserAddedErrorFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputUserAddedErrorFileMenu);
    //Set right click menu for Input Sigma Multipath file label
    ui->labelInputSigmaMultipathFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSigmaMultipathFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSigmaMultipathFileMenu);
    //Set right click menu for Input Reference Position file for Rtcm label
    ui->labelReferenceFileRtcm->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelReferenceFileRtcm,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelReferenceFileRtcmFileMenu);
    //Set right click menu for Input Reference Position file for Specify label
    ui->labelReferenceFileSpecify->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelReferenceFileSpecify,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelReferenceFileSpecifyFileMenu);
    //Set right click menu for Reference Position file for Calculate checkbox
    ui->checkBoxReferencePositionFileCalculate->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxReferencePositionFileCalculate,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxReferencePositionFileCalculateFileMenu);

    ///OUTPUT TAB CONTEXT MENUS
    //Set right click menu for Output file label
    ui->labelOutputFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelOutputFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelOutputFileMenu);
    //Set right click menu for KML checkbox and KML edit line
    ui->checkBoxKML->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxKML,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxKMLMenu);
    //Set right click menu for KML0 checkbox
    ui->checkBoxKML0->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxKML0,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxKML0Menu);
    //Set right click menu for SP3 checkbox
    ui->checkBoxOutputSP3->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxOutputSP3,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxOutputSP3Menu);
    //Set right click menu for Ref file checkbox
    ui->checkBoxOutRefFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxOutRefFile,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxOutRefFileMenu);
    //Set right click menu for Stanford-ESA Plot File label
    ui->labelStfdESAPlotFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelStfdESAPlotFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelStfdESAPlotFileMenu);
    //Set right click menu for Stanford-ESA Data File label
    ui->labelStfdESADataFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelStfdESADataFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelStfdESADataFileMenu);

    ///ANALYSIS PAGE CONTEXT MENUS
    //Set right click menu for Plot 1 Source File label
    ui->labelPlot1SourceFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelPlot1SourceFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelPlot1SourceFileMenu);
    //Set right click menu for Plot 2 Source File label
    ui->labelPlot2SourceFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelPlot2SourceFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelPlot2SourceFileMenu);
    //Set right click menu for Plot 3 Source File label
    ui->labelPlot3SourceFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelPlot3SourceFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelPlot3SourceFileMenu);
    //Set right click menu for Plot 4 Source File label
    ui->labelPlot4SourceFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelPlot4SourceFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelPlot4SourceFileMenu);

    ///CONVERTER PAGE CONTEXT MENUS
    //Set right click menu for Converter SBAS Source File label
    ui->labelConvSbasFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelConvSbasFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelConvSbasFileMenu);
    //Set right click menu for Converter Output SBAS Directory label
    ui->labelConvOutputPath->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelConvOutputPath,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelConvOutputPathMenu);
    //Set right click menu for Converter DGNSS source file ComboBox
    ui->comboBoxConverterDgnssInput->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->comboBoxConverterDgnssInput,&QComboBox::customContextMenuRequested,this,&gLAB_GUI::comboBoxConverterDgnssInputMenu);
    //Set right click menu for Converter DGNSS Output RINEX file ComboBox
    ui->comboBoxConverterDgnssOutputRinex->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->comboBoxConverterDgnssOutputRinex,&QComboBox::customContextMenuRequested,this,&gLAB_GUI::comboBoxConverterDgnssOutputRinexMenu);
    //Set right click menu for Converter DGNSS Corrections File label
    ui->labelConvCorrectionsFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelConvCorrectionsFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelConvCorrectionsFileMenu);
    //Set right click menu for Converter DGNSS Antenna File label
    ui->labelConvAntennaFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelConvAntennaFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelConvAntennaFileMenu);

    ///COMPARISON PAGE CONTEXT MENUS
    //Set right click menu for Comparison RINEX navigation file 1 label
    ui->labelCompareRinexNavFile1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareRinexNavFile1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareRinexNavFile1Menu);
    //Set right click menu for Comparison SP3 Orbits & clocks file 1 label
    ui->labelCompareSP3OrbitsClocksFile1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareSP3OrbitsClocksFile1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareSP3OrbitsClocksFile1Menu);
    //Set right click menu for Comparison SP3 Orbits file 1 label
    ui->labelCompareSP3OrbitsFile1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareSP3OrbitsFile1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareSP3OrbitsFile1Menu);
    //Set right click menu for Comparison clocks file 1 label
    ui->labelCompareClockFile1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareClockFile1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareClockFile1Menu);
    //Set right click menu for Comparison RINEX navigation file 2 label
    ui->labelCompareRinexNavFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareRinexNavFile2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareRinexNavFile2Menu);
    //Set right click menu for Comparison SP3 Orbits & clocks file 2 label
    ui->labelCompareSP3OrbitsClocksFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareSP3OrbitsClocksFile2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareSP3OrbitsClocksFile2Menu);
    //Set right click menu for Comparison SP3 Orbits file 2 label
    ui->labelCompareSP3OrbitsFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareSP3OrbitsFile2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareSP3OrbitsFile2Menu);
    //Set right click menu for Comparison clocks file 2 label
    ui->labelCompareClockFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareClockFile2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareClockFile2Menu);
    //Set right click menu for Comparison ANTEX file checkbox
    ui->checkBoxAntexCompareOrbitsFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxAntexCompareOrbitsFile2,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxAntexCompareOrbitsFile2Menu);
    //Set right click menu for Comparison Output file label
    ui->labelCompareOutputFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelCompareOutputFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelCompareOutputFileMenu);

    //SHOW ORBITS PAGE CONTEXT MENUS
    //Set right click menu for Show Orbit RINEX navigation file label
    ui->labelShowOrbitRinexNavFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelShowOrbitRinexNavFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelShowOrbitRinexNavFileMenu);
    //Set right click menu for Show Orbit SP3 Orbits & clocks file label
    ui->labelShowOrbitSP3OrbitsClocksFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelShowOrbitSP3OrbitsClocksFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelShowOrbitSP3OrbitsClocksFileMenu);
    //Set right click menu for Show Orbit SP3 Orbits file label
    ui->labelShowOrbitSP3OrbitsFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelShowOrbitSP3OrbitsFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelShowOrbitSP3OrbitsFileMenu);
    //Set right click menu for Show Orbit clocks file label
    ui->labelShowOrbitClocksFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelShowOrbitClocksFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelShowOrbitClocksFileMenu);
    //Set right click menu for Show Orbit ANTEX file checkbox
    ui->checkBoxAntexShowOrbitFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxAntexShowOrbitFile,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxAntexShowOrbitFileMenu);
    //Set right click menu for Show Orbit Output file label
    ui->labelShowOrbitOutputFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelShowOrbitOutputFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelShowOrbitOutputFileMenu);

    //Add User Error to RINEX PAGE CONTEXT MENUS
    //Set right click menu for Add User Error RINEX observation file label
    ui->labelAddErrorObservationFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelAddErrorObservationFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelAddErrorObservationFileMenu);
    //Set right click menu for Add User Error User error file label
    ui->labelAddErrorUserAddedErrorFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelAddErrorUserAddedErrorFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelAddErrorUserAddedErrorFileMenu);
    //Set right click menu for Add User Error output Rinex file label
    ui->labelAddErrorRinexOutputFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelAddErrorRinexOutputFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelAddErrorRinexOutputFileMenu);
    //Set right click menu for Add User Error output file label
    ui->labelAddErrorOutputFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelAddErrorOutputFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelAddErrorOutputFileMenu);

    //Init variable with pointers to pushButtons function pointers
    this->InitPushButtonsFuncPointers();
    //Init variable with pointers to pushButtons widget pointers
    this->InitPushButtonsWidgetPointers();

    // Positioning defaults
    ui->tabWidget->setCurrentIndex(0);
    this->setInitialPositioningValues();


    // Show Main Logo on top of Input tab by hiding all the groupboxes in this tab
    ui->tabInput->setContentsMargins(0,0,0,0);
    ui->frametabInputGroupboxes->setHidden(true);
    ui->labelMainLogo->setHidden(false);

    // Set the locale to avoid comma as decimator and reject the group separator
    QLocale qlocale(QLocale::C);
    QRegularExpression rxPRNletter("[A-Z]\\d{1}");
    QRegularExpression rxPRNnumber("(^[1-9][0-9]\\d{0,1}$)|(^0[1-9]\\d{1}$)");
    QRegularExpression KMLRanges("(^-$)|(^[0-9]\\d{0,}$)|(^[0-9]\\d{0,}\\.[0-9]\\d{0,3}$)|(^\\.[0-9]\\d{1,3}$)"); //Allows only a "-", or positive values with 4 decimals
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto ldouble = new QDoubleValidator(-100000000, 100000000,6, this);
    ldouble->setLocale(qlocale); // lineEdit validation for coordinates XYZ
    auto ldoublePositive = new QDoubleValidator(0, 100000000,6, this);
    ldoublePositive->setLocale(qlocale); // lineEdit validation
    auto ldoublePositiveDec = new QDoubleValidator(0, 86400,4, this);
    ldoublePositiveDec->setLocale(qlocale); // lineEdit validation for decimation and datagap
    auto lseconds = new QIntValidator(0, 86400, this);
    lseconds->setLocale(qlocale); // lineEdit validation for seconds
    auto lsecondsPositive = new QIntValidator(1, 86400, this);
    lsecondsPositive->setLocale(qlocale); // lineEdit validation for seconds strictly greater than 0
    auto lSNR = new QDoubleValidator(1, 99, 1,this);
    lSNR->setLocale(qlocale); // lineEdit validation for SNR
    auto lelevMask = new QDoubleValidator(0, 90,4, this);
    lelevMask->setLocale(qlocale); // lineEdit Validation for elevation mask
    auto lintPositive = new QIntValidator(0, 86400, this);
    lintPositive->setLocale(qlocale); // lineEdit validation for positive int
    auto linterpolation = new QIntValidator(0, 19, this);
    linterpolation->setLocale(qlocale); // lineEdit validation for orbit and clock interpolation
    auto lGEOselection = new QIntValidator(120, 210, this);
    lGEOselection->setLocale(qlocale); // lineEdit validation for GEO selection
    auto lintInfinity = new QIntValidator(0, 9999999, this);
    lintInfinity->setLocale(qlocale); // lineEdit validation for int infinity
    auto lint = new QIntValidator(-9999999, 9999999, this);
    lint->setLocale(qlocale); // lineEdit validation for any int (positive or negative)
    auto lPRNnumberValidator = new QRegularExpressionValidator(rxPRNnumber, this);
    lPRNnumberValidator->setLocale(qlocale);  // lineEdit validation for PRN number
    auto lPRNletterValidator = new QRegularExpressionValidator(rxPRNletter, this);
    lPRNletterValidator->setLocale(qlocale);  // lineEdit validation for PRN letter (only A-Z)
    auto lintPercentile = new QIntValidator(1, 100, this);
    lintPercentile->setLocale(qlocale); // lineEdit validation for SBAS percentile value
    auto lKMLRanges = new QRegularExpressionValidator(KMLRanges, this);
    lKMLRanges->setLocale(qlocale); // lineEdit validation for KML Timestamp regions
    auto lLongitude = new QDoubleValidator(-180, 180,14, this);
    lLongitude->setLocale(qlocale); // lineEdit validation for longitude
    auto lLatitude = new QDoubleValidator(-90, 90,14, this);
    lLatitude->setLocale(qlocale); // lineEdit validation for longitude

    // INPUT defaults
    ui->lineEditCalculateSpecifyX->setValidator(ldouble);
    ui->lineEditCalculateSpecifyY->setValidator(ldouble);
    ui->lineEditCalculateSpecifyZ->setValidator(ldouble);
    ui->lineEditCalculateSpecifyLon->setValidator(lLongitude);
    ui->lineEditCalculateSpecifyLat->setValidator(lLatitude);
    ui->lineEditCalculateSpecifyHeight->setValidator(ldouble);
    ui->lineEditAprioriRecPosRtcmSpecifyX->setValidator(ldouble);
    ui->lineEditAprioriRecPosRtcmSpecifyY->setValidator(ldouble);
    ui->lineEditAprioriRecPosRtcmSpecifyZ->setValidator(ldouble);
    ui->lineEditAprioriRecPosRtcmSpecifyLon->setValidator(lLongitude);
    ui->lineEditAprioriRecPosRtcmSpecifyLat->setValidator(lLatitude);
    ui->lineEditAprioriRecPosRtcmSpecifyHeight->setValidator(ldouble);
    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setValidator(ldouble);
    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setValidator(ldouble);
    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setValidator(ldouble);
    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setValidator(lLongitude);
    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setValidator(lLatitude);
    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setValidator(ldouble);
    ui->lineEditSpecifyX->setValidator(ldouble);
    ui->lineEditSpecifyY->setValidator(ldouble);
    ui->lineEditSpecifyZ->setValidator(ldouble);
    ui->lineEditSpecifyLon->setValidator(lLongitude);
    ui->lineEditSpecifyLat->setValidator(lLatitude);
    ui->lineEditSpecifyHeight->setValidator(ldouble);
    ui->lineEditInterpolationDegreeRefFileCalculate->setValidator(linterpolation);
    ui->lineEditInterpolationDegreeRefFileSpecify->setValidator(linterpolation);
    ui->lineEditInterpolationDegreeRefFileRtcm->setValidator(linterpolation);

    // PREPROCESS defaults
    ui->lineEditDataDecimator->setValidator(ldoublePositiveDec);
    ui->lineEditDataGap->setValidator(ldoublePositiveDec);
    ui->lineEditNcon->setValidator(lseconds);
    ui->lineEditElevMask->setValidator(lelevMask);
    ui->lineEditUserDefinedSNR->setValidator(lSNR);
    ui->lineEditL1C1iniStd->setValidator(ldoublePositive);
    ui->lineEditL1C1window->setValidator(lseconds);
    ui->lineEditL1C1kFactor->setValidator(ldoublePositive);
    ui->lineEditL1C1nSample->setValidator(lintPositive);
    ui->lineEditL1C1ConsCheckValue->setValidator(ldoublePositive);
    ui->lineEditIntialStdDevBW->setValidator(ldoublePositive);
    ui->lineEditMWminStd->setValidator(ldoublePositive);
    ui->lineEditMWwindow->setValidator(lseconds);
    ui->lineEditMWkFactor->setValidator(ldoublePositive);
    ui->lineEditMWnSample->setValidator(lintPositive);
    ui->lineEditLImaxJumpThreshold->setValidator(ldoublePositive);
    ui->lineEditLImaxThreshold->setValidator(ldoublePositive);
    ui->lineEditLItimeConstant->setValidator(ldoublePositive);
    ui->lineEditLInSamples->setValidator(lintPositive);

    // MODELLING defaults
    ui->lineEditOrbitInterpolationDegree->setValidator(linterpolation);
    ui->lineEditClockInterpolationDegree->setValidator(linterpolation);
    ui->lineEditOrbitConsecutiveGaps->setValidator(lseconds);
    ui->lineEditClockConsecutiveGaps->setValidator(lseconds);
    ui->lineEditOrbitMaxGaps->setValidator(lseconds);
    ui->lineEditClockMaxGaps->setValidator(lseconds);
    ui->lineEditAPCf1north->setValidator(ldouble);
    ui->lineEditAPCf1east->setValidator(ldouble);
    ui->lineEditAPCf1up->setValidator(ldouble);
    ui->lineEditAPCf2north->setValidator(ldouble);
    ui->lineEditAPCf2east->setValidator(ldouble);
    ui->lineEditAPCf2up->setValidator(ldouble);
    ui->lineEditARPnorth->setValidator(ldouble);
    ui->lineEditARPeast->setValidator(ldouble);
    ui->lineEditARPup->setValidator(ldouble);
    ui->lineEditGEOselection->setValidator(lGEOselection);
    ui->lineEditGEOexclusion1->setValidator(lGEOselection);
    ui->lineEditGEOexclusion2->setValidator(lGEOselection);
    ui->lineEditGEOexclusion3->setValidator(lGEOselection);
    ui->lineEditSbasSigmaMultipathA->setValidator(ldoublePositive);
    ui->lineEditSbasSigmaMultipathB->setValidator(ldoublePositive);
    ui->lineEditSbasSigmaMultipathC->setValidator(ldoublePositive);
    ui->lineEditSbasSigmaDivergence->setValidator(ldoublePositive);
    ui->lineEditSbasSigmaNoise->setValidator(ldoublePositive);
    ui->lineEditPRNmaskPA->setValidator(lseconds);
    ui->lineEditPRNmaskNPA->setValidator(lseconds);
    ui->lineEditFastCorrectionsPA->setValidator(lseconds);
    ui->lineEditFastCorrectionsNPA->setValidator(lseconds);
    ui->lineEditRRCcorrectionsPA->setValidator(lseconds);
    ui->lineEditRRCcorrectionsNPA->setValidator(lseconds);
    ui->lineEditIntegrityInfoPA->setValidator(lseconds);
    ui->lineEditIntegrityInfoNPA->setValidator(lseconds);
    ui->lineEditFastCorrectionDegradationFactorPA->setValidator(lseconds);
    ui->lineEditFastCorrectionDegradationFactorNPA->setValidator(lseconds);
    ui->lineEditDegradationParametersPA->setValidator(lseconds);
    ui->lineEditDegradationParametersNPA->setValidator(lseconds);
    ui->lineEditLongTermSatelliteCorrectionsPA->setValidator(lseconds);
    ui->lineEditLongTermSatelliteCorrectionsNPA->setValidator(lseconds);
    ui->lineEditIonosphericGridPointsMaskPA->setValidator(lseconds);
    ui->lineEditIonosphericGridPointsMaskNPA->setValidator(lseconds);
    ui->lineEditIonosphericDelayCorrectionsPA->setValidator(lseconds);
    ui->lineEditIonosphericDelayCorrectionsNPA->setValidator(lseconds);
    ui->lineEditServiceMessagePA->setValidator(lseconds);
    ui->lineEditServiceMessageNPA->setValidator(lseconds);
    ui->lineEditClockEphemerisCovarianceMatrixPA->setValidator(lseconds);
    ui->lineEditClockEphemerisCovarianceMatrixNPA->setValidator(lseconds);
    ui->lineEditGeoNavigationMessagePA->setValidator(lseconds);
    ui->lineEditGeoNavigationMessageNPA->setValidator(lseconds);
    ui->lineEditGeoSatelliteAlmanacsPA->setValidator(lintInfinity);
    ui->lineEditGeoSatelliteAlmanacsNPA->setValidator(lintInfinity);
    ui->lineEditNetworkTimeParametersPA->setValidator(lseconds);
    ui->lineEditNetworkTimeParametersNPA->setValidator(lseconds);
    ui->lineEditDoNotUseForSafetyAppPA->setValidator(lintInfinity);
    ui->lineEditDoNotUseForSafetyAppNPA->setValidator(lintInfinity);
    ui->lineEditOffsetFastCorrNoMT10->setValidator(ldoublePositive);
    ui->lineEditGEOadquisitionTime->setValidator(lseconds);
    ui->lineEditSwitchinCooltime->setValidator(lseconds);
    ui->lineEditkhpa->setValidator(ldoublePositive);
    ui->lineEditkvpa->setValidator(ldoublePositive);
    ui->lineEditkhnpa->setValidator(ldoublePositive);
    ui->lineEditkvnpa->setValidator(ldoublePositive);
    ui->lineEditMaxAgeDgnss->setValidator(ldoublePositiveDec);
    ui->lineEditMaxValueDGNSS->setValidator(ldoublePositiveDec);

    // FILTER defaults
    ui->lineEditSmoothing->setValidator(lintPositive);
    ui->lineEditSmoothMinSbas->setValidator(lintPositive);
    ui->lineEditSmoothMinDgnss->setValidator(lintPositive);
    ui->lineEditFixedStdDevSingleCode->setValidator(ldoublePositive);
    ui->lineEditFixedStdDevSingleCarrier->setValidator(ldoublePositive);
    ui->lineEditFixedStdDevDualCode->setValidator(ldoublePositive);
    ui->lineEditFixedStdDevDualCarrier->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCodeA->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCodeB->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCodeC->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCarrierA->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCarrierB->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevSingleCarrierC->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCodeA->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCodeB->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCodeC->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCarrierA->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCarrierB->setValidator(ldoublePositive);
    ui->lineEditElevationStdDevDualCarrierC->setValidator(ldoublePositive);
    ui->lineEditPhiCoordinates->setValidator(ldoublePositive);
    ui->lineEditPhiClock->setValidator(ldoublePositive);
    ui->lineEditPhiTropo->setValidator(ldoublePositive);
    ui->lineEditPhiPhaseAmbiguities->setValidator(ldoublePositive);
    ui->lineEditQcoordinates->setValidator(ldoublePositive);
    ui->lineEditQclock->setValidator(ldoublePositive);
    ui->lineEditQtropo->setValidator(ldoublePositive);
    ui->lineEditQphaseAmbiguities->setValidator(ldoublePositive);
    ui->lineEditPoCoordinates->setValidator(ldoublePositive);
    ui->lineEditPoClock->setValidator(ldoublePositive);
    ui->lineEditPoTropo->setValidator(ldoublePositive);
    ui->lineEditPoPhaseAmbiguities->setValidator(ldoublePositive);
    ui->lineEditMaxHDOP->setValidator(ldoublePositive);
    ui->lineEditMaxPDOP->setValidator(ldoublePositive);
    ui->lineEditMaxGDOP->setValidator(ldoublePositive);
    ui->lineEditPrefitOutliers->setValidator(ldoublePositive);

    // OUTPUT defaults
    ui->lineEditKML_Dec->setValidator(ldoublePositiveDec);
    ui->lineEditKML_From->setValidator(lKMLRanges);
    ui->lineEditKML_To->setValidator(lKMLRanges);
    ui->lineEditSP3Letter->setValidator(lPRNletterValidator);
    ui->lineEditSP3PRN->setValidator(lPRNnumberValidator);
    ui->lineEditStanfordEsaXmax->setValidator(ldoublePositive);
    ui->lineEditStanfordEsaYmax->setValidator(ldoublePositive);
    ui->lineEditStanfordEsaXres->setValidator(ldoublePositive);
    ui->lineEditStanfordEsaYres->setValidator(ldoublePositive);
    ui->lineEditHorizontalIntegrityRatio->setValidator(ldoublePositive);
    ui->lineEditVerticalIntegrityRatio->setValidator(ldoublePositive);
    ui->lineEditHorizontalAlarmLimitSBAS->setValidator(ldoublePositive);
    ui->lineEditVerticalAlarmLimitSBAS->setValidator(ldoublePositive);
    ui->lineEditPercentileValue->setValidator(lintPercentile);
    ui->lineEditSlidingWindowSBAS->setValidator(lintPositive);
    ui->lineEditMaritimeWindowSBAS->setValidator(lintPositive);

    // ANALYSIS defaults
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotXmin->setValidator(ldouble);
    ui->lineEditPlotXmax->setValidator(ldouble);
    ui->lineEditPlotYmin->setValidator(ldouble);
    ui->lineEditPlotYmax->setValidator(ldouble);
    //Column number has no validator due to mathematical formulas can be given
    /*ui->lineEditPlot1Xcolumn->setValidator(lseconds);
    ui->lineEditPlot1Ycolumn->setValidator(lseconds);
    ui->lineEditPlot2Xcolumn->setValidator(lseconds);
    ui->lineEditPlot2Ycolumn->setValidator(lseconds);
    ui->lineEditPlot3Xcolumn->setValidator(lseconds);
    ui->lineEditPlot3Ycolumn->setValidator(lseconds);
    ui->lineEditPlot4Xcolumn->setValidator(lseconds);
    ui->lineEditPlot4Ycolumn->setValidator(lseconds);*/
    ui->lineEditXTickNum->setValidator(ldoublePositive);
    ui->lineEditYTickNum->setValidator(ldoublePositive);

    // CONVERTER Defaults
    setInitialConverterValues();

    //Compare Orbits Defaults
    ui->lineEditDecimationCompareOrbit->setValidator(ldoublePositiveDec);
    ui->lineEditOrbitInterpolationDegreeCompare->setValidator(linterpolation);
    ui->lineEditClockInterpolationDegreeCompare->setValidator(linterpolation);
    ui->lineEditOrbitConsecutiveGapsCompare->setValidator(lseconds);
    ui->lineEditClockConsecutiveGapsCompare->setValidator(lseconds);
    ui->lineEditOrbitMaxGapsCompare->setValidator(lseconds);
    ui->lineEditClockMaxGapsCompare->setValidator(lseconds);
    ui->checkBoxPrintSatdiffCompare->setToolTip(ui->checkBoxPrintSatdiff->toolTip());
    ui->checkBoxPrintSatstatCompare->setToolTip(ui->checkBoxPrintSatstat->toolTip());
    ui->checkBoxPrintSatstattotCompare->setToolTip(ui->checkBoxPrintSatstattot->toolTip());
    setInitialCompareOrbitValues();


    //Show Orbits defaults
    ui->lineEditDecimationShowOrbit->setValidator(ldoublePositiveDec);
    ui->lineEditOrbitInterpolationDegreeShowOrbit->setValidator(linterpolation);
    ui->lineEditClockInterpolationDegreeShowOrbit->setValidator(linterpolation);
    ui->lineEditOrbitConsecutiveGapsShowOrbit->setValidator(lseconds);
    ui->lineEditClockConsecutiveGapsShowOrbit->setValidator(lseconds);
    ui->lineEditOrbitMaxGapsShowOrbit->setValidator(lseconds);
    ui->lineEditClockMaxGapsShowOrbit->setValidator(lseconds);
    ui->checkBoxPrintSatpvtShowOrbit->setToolTip(ui->checkBoxPrintSatpvt->toolTip());
    setInitialShowOrbitValues();

    //Add User Error defaults
    setInitialAddUserErrorValues();
    ui->checkBoxPrintUserErrorAddError->setToolTip(ui->checkBoxPrintUsererror->toolTip());
}

void gLAB_GUI::setInitialPositioningValues() {

    QString OutputPath;

    //Hide progress bar
    ui->stackedWidgetMainButtons->setCurrentIndex(0);
    // Set as default the SPP template
    this->on_actionSBAS_triggered();
    this->on_actionDGNSS_triggered();
    this->on_actionSPP_triggered();

    // INPUT defaults
    this->on_checkBoxStartTime_clicked(false);
    this->on_checkBoxEndTime_clicked(false);
    QDate date = QDate(1979, 12, 31);
    ui->dateTimeEditStartTime->setDate(date);
    ui->dateTimeEditEndTime->setDate(date);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxReferenceStation_clicked(false);
    ui->stackedWidgetIonoSource->setCurrentIndex(3);
    this->on_comboBoxRefStation_currentIndexChanged(0);
    this->on_comboBoxDcbSourcePPP_currentIndexChanged(0);
    this->on_comboBoxDcbSource_currentIndexChanged(0);
    ui->checkBoxUserAddedErrorAfterPrepocessing->setChecked(false);
    ui->lineEditRinexObs->setText("");
    ui->lineEditAntex->setText("");
    ui->lineEditRinexNav->setText("");
    ui->lineEditPrecise1File->setText("");
    ui->lineEditPrecise2Files->setText("");
    ui->lineEditPreciseClk->setText("");
    ui->lineEditSbas->setText("");
    ui->lineEditRefStaRinex->setText("");
    ui->lineEditRefStaRtcmAuto->setText("");
    ui->lineEditRefStaRtcm2->setText("");
    ui->lineEditRefStaRtcm3->setText("");
    ui->lineEditIonoSourceRinexNav->setText("");
    ui->lineEditIonoSourceIonex->setText("");
    ui->lineEditIonoSourceSbasSpecify->setText("");
    ui->lineEditDcbFile->setText("");
    ui->lineEditGPSRecType->setText("");
    ui->lineEditUserAddedError->setText("");
    ui->lineEditDcbSourceRinexNav->setText("");
    ui->lineEditDcbSourceDcb->setText("");
    ui->lineEditDcbSourceIonex->setText("");
    ui->lineEditSigmaMultipath->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyX->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyY->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyZ->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyLon->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyLat->setText("");
    ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText("");
    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText("");
    ui->lineEditSinex->setText("");
    ui->lineEditSpecifyX->setText("");
    ui->lineEditSpecifyY->setText("");
    ui->lineEditSpecifyZ->setText("");
    ui->lineEditSpecifyLon->setText("");
    ui->lineEditSpecifyLat->setText("");
    ui->lineEditSpecifyHeight->setText("");
    ui->lineEditCalculateSpecifyX->setText("");
    ui->lineEditCalculateSpecifyY->setText("");
    ui->lineEditCalculateSpecifyZ->setText("");
    ui->lineEditCalculateSpecifyLon->setText("");
    ui->lineEditCalculateSpecifyLat->setText("");
    ui->lineEditCalculateSpecifyHeight->setText("");
    ui->lineEditReferenceFileSpecify->setText("");
    ui->lineEditReferencePositionFileCalculate->setText("");
    ui->lineEditReferenceFileRtcm->setText("");
    ui->lineEditInterpolationDegreeRefFileCalculate->setText("0");
    ui->lineEditInterpolationDegreeRefFileSpecify->setText("0");
    ui->lineEditInterpolationDegreeRefFileRtcm->setText("0");

    this->on_radioButtonRtcmRecCartesian_clicked();
    this->on_radioButtonRtcmRefCartesian_clicked();
    this->on_radioButtonRtcmUserDefined_clicked();
    this->on_radioButtonRtcmBaseline_clicked();
    this->on_radioButtonRtcm_clicked();
    this->on_radioButtonCalculateSpecifyCartesian_clicked();
    this->on_radioButtonCalculateEarthCentre_clicked();
    this->on_checkBoxReferencePositionFileCalculate_clicked(false);
    this->on_radioButtonSpecifyUserCartesian_clicked();
    this->on_radioButtonSpecifyUserDefined_clicked();
    this->on_radioButtonRinex_clicked();

    // PREPROCESS defaults
    this->on_pushButtonGPSSatSelAll_clicked(); // Enable all GPS satellites
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    ui->lineEditUserDefinedSNR->setText("");

    // MODELLING defaults
    this->setSBASmodellingDefaults();
    ui->dateTimeEditStartTimeSummary->setDate(date);


    // FILTER defaults


    // OUTPUT defaults
    this->on_checkBoxKML_clicked(false);
    this->on_checkBoxKML0_clicked(false);
    this->on_checkBox_KML_TimeStamps_clicked(false);
    this->on_checkBox_KML_Range_clicked(false);
    ui->checkBoxKMLRefStations->setChecked(true);
    ui->checkBoxKMLGeoid->setChecked(true);
    this->on_checkBoxOutputSP3_clicked(false);
    ui->checkBoxSP3OutFileWriteSPPSolutions->setChecked(true);
    this->on_checkBoxOutRefFile_clicked(false);
    ui->radioButtonOutRefFileYearDoYSoD->setChecked(true);
    ui->radioButtonOutRefFileCartesian->setChecked(true);
    ui->checkBoxRefOutFileWriteSPPSolutions->setChecked(true);
    this->on_groupBoxStanfordESA_clicked(false);
    this->on_checkBoxStanfordESAallGeometries_clicked(false);
    ui->stackedWidgetOtherMessages->setCurrentIndex(0);
    #ifdef Q_OS_MAC
        if (this->directoryExists("/Applications/gLAB_GUI.app/Contents/MacOS/WORK_FILES")==true) {
            OutputPath="/Applications/gLAB_GUI.app/Contents/MacOS/WORK_FILES";
        } else {
            OutputPath=QDir::homePath();
        }
    #else
        OutputPath=QDir::currentPath();
    #endif

    ui->lineEditOutputDestination->setText(QDir::toNativeSeparators(OutputPath + "/gLAB.out"));
    ui->lineEditKML->setText(QDir::toNativeSeparators(OutputPath + "/gLAB.kml"));
    ui->lineEditKML0->setText(QDir::toNativeSeparators(OutputPath + "/gLAB0.kml"));
    ui->lineEditOutputSP3->setText(QDir::toNativeSeparators(OutputPath + "/gLAB.sp3"));
    ui->lineEditOutRefFile->setText(QDir::toNativeSeparators(OutputPath + "/gLAB_Ref.txt"));
    ui->lineEditOutputStanfordEsaPlot->setText(QDir::toNativeSeparators(OutputPath + "/gLAB_stfd-ESA_plot.txt"));
    ui->lineEditOutputframeStanfordESAallGeometries->setText(QDir::toNativeSeparators(OutputPath + "/gLAB_stfd-ESA_data.txt"));
}

void gLAB_GUI::setInitialConverterValues() {
    QDate date = QDate(1979, 12, 31);
    ui->dateEdit1->setDate(date);
    ui->dateEdit2->setDate(date);
    ui->dateEdit3->setDate(date);
    ui->dateEdit4->setDate(date);
    this->on_groupBoxConverterSBAS_clicked(false);
    this->on_groupBoxConverterDgnss_clicked(false);
    ui->comboBoxConverterDgnssOutputRinex->setCurrentIndex(1);
    ui->frameConverterSBAS->setHidden(true);
    ui->checkBox_pegasus->setChecked(false);
    ui->checkBox_ems->setChecked(false);
    ui->checkBox_rinexb->setChecked(false);
    ui->Pegasus_frame->setHidden(true);
    ui->frame_holdingPegasusOptions->setHidden(false);
    ui->frame_holdingPegasusOptions->setFrameShape(QFrame::NoFrame);
    ui->lineEdit_convert_sbas->setText("");
    ui->lineEdit_outputpath_sbas->setText("");
    ui->lineEditConverterDgnssInput->setText("");
    ui->lineEditConverterDgnssOutputRinex->setText("");
    ui->lineEditConverterDgnssOutputAsciiCorrections->setText("");
    ui->lineEditConverterDgnssOutputAsciiAntenna->setText("");
}

void gLAB_GUI::setInitialCompareOrbitValues() {
    this->on_checkBoxAntexCompareOrbitsFile2_clicked(false);
    this->on_radioButtonOrbitNavCompareFile1_clicked();
    this->on_radioButtonOrbitNavCompareFile2_clicked();
    ui->radioButtonOrbitNextDayCompare->setChecked(true);
    ui->radioButtonClockNextDayCompare->setChecked(true);
    this->on_groupBoxConcatenedPreciseFilesCompare_clicked(false);
    ui->lineEditDecimationCompareOrbit->setText("300");
    ui->lineEditOrbitInterpolationDegreeCompare->setText("10");
    ui->lineEditClockInterpolationDegreeCompare->setText("0");
    ui->lineEditOrbitConsecutiveGapsCompare->setText("8");
    ui->lineEditClockConsecutiveGapsCompare->setText("2");
    ui->lineEditOrbitMaxGapsCompare->setText("16");
    ui->lineEditClockMaxGapsCompare->setText("4");
    ui->checkBoxSatClockOffsetCompare->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(true);
    ui->checkBoxDiscardEclipseCompare->setChecked(false);
    ui->checkBoxDiscardUnhealthyCompare->setChecked(true);
    ui->lineEditNavCompareFile1->setText("");
    ui->lineEditPreciseFilesCompareSP3File1->setText("");
    ui->lineEditPreciseFilesCompareOrbFile1->setText("");
    ui->lineEditPreciseFilesCompareClkFile1->setText("");
    ui->lineEditNavCompareFile2->setText("");
    ui->lineEditPreciseFilesCompareSP3File2->setText("");
    ui->lineEditPreciseFilesCompareOrbFile2->setText("");
    ui->lineEditPreciseFilesCompareClkFile2->setText("");
    ui->lineEditAntexCompareOrbitsFile2->setText("");
    ui->lineEditOutputFileCompare->setText("");
}

void gLAB_GUI::setInitialShowOrbitValues() {
    this->on_checkBoxAntexShowOrbitFile_clicked(false);
    this->on_radioButtonOrbitNavShowOrbitFile_clicked();
    ui->radioButtonOrbitNextDayShowOrbit->setChecked(true);
    ui->radioButtonClockNextDayShowOrbit->setChecked(true);
    this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(false);
    ui->lineEditDecimationShowOrbit->setText("300");
    ui->lineEditOrbitInterpolationDegreeShowOrbit->setText("10");
    ui->lineEditClockInterpolationDegreeShowOrbit->setText("0");
    ui->lineEditOrbitConsecutiveGapsShowOrbit->setText("8");
    ui->lineEditClockConsecutiveGapsShowOrbit->setText("2");
    ui->lineEditOrbitMaxGapsShowOrbit->setText("16");
    ui->lineEditClockMaxGapsShowOrbit->setText("4");
    ui->checkBoxSatClockOffsetShowOrbit->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(true);
    ui->checkBoxDiscardUnhealthyShowOrbit->setChecked(true);
    ui->lineEditNavShowOrbitFile->setText("");
    ui->lineEditPreciseFilesShowOrbitSP3File->setText("");
    ui->lineEditPreciseFilesShowOrbitOrbFile->setText("");
    ui->lineEditPreciseFilesShowOrbitClkFile->setText("");
    ui->lineEditAntexShowOrbitFile->setText("");
    ui->lineEditOutputFileShowOrbit->setText("");
    ui->radioButtonSatVelECEFShowOrbit->setChecked(true);
}

void gLAB_GUI::setInitialAddUserErrorValues() {
    ui->lineEditRinexObsAddError->setText("");
    ui->lineEditUserAddedErrorAddError->setText("");
    ui->lineEditRinexOutputFileAddError->setText("");
    ui->lineEditOutputFileAddError->setText("");
    ui->checkBoxPrintInfoAddError->setChecked(true);
    ui->checkBoxPrintUserErrorAddError->setChecked(true);
}

// Destructor of the GUI
gLAB_GUI::~gLAB_GUI() {
    delete ui;
}

// Function to check if a file exists
bool gLAB_GUI::fileExists(QString path) {
    QFile file(path);
    QFileInfo check_file(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) return true;
    else return false;
}

// Function to check if a directory exists
bool gLAB_GUI::directoryExists(QString path) {
    QFile file(path);
    QFileInfo check_file(file);
    // check if file exists and if yes: Is it really a directory?
    if (check_file.exists() && !check_file.isFile()) return true;
    else return false;
}

//Funtion to read last line of a file
void  gLAB_GUI::getLastLineOfFile(QString path, QString *lastLine) {
    QFile outputfile(path);
    QMessageBox messageBox;
    QString newline ="\n";
    int count=0;
    int lines = 1; //Number of lines to read
    int charactersReadPerLine=0;
    if(outputfile.open(QIODevice::ReadOnly))  {
        outputfile.seek(outputfile.size());
        while ( (count < lines) && (outputfile.pos() > 0) ) {
                QString ch = outputfile.read(1);
                charactersReadPerLine++;
                outputfile.seek(outputfile.pos()-2);
                if (ch == "\n") {
                    if (charactersReadPerLine!=1) {
                        //Only count non blank lines
                        count++;
                    }
                    charactersReadPerLine=0;
                }

        }
        *lastLine = outputfile.readAll();
        //If first or second character is "\n", take it out
        if (lastLine->at(0)==newline) {
            lastLine->remove(0, 1);
        } else if (lastLine->at(1)==newline) {
             lastLine->remove(0, 2);
        }
        //Close file
        outputfile.close();
    } else {
        //Error opening output file
        *lastLine = "---";
    }

    return;
}

//Function to put all unnecessary parameters in warning string
void gLAB_GUI::extraParametersToWarningStr(int startPos, QString *warningString, QString option, QStringList ParametersList) {
    int i;
    if (ParametersList.count()>startPos) {
        *warningString += "Parameter '" + option + "' has the following extra values (which have been omitted):";
        for(i=startPos;i<ParametersList.count();i++) {
            *warningString += " '" + ParametersList.at(i) + "'";
        }
        *warningString += ".\n";
    }
}

//Function to check if paths are valid for the current system or if the paths are absolute
void gLAB_GUI::checkConfigurationFileInputFilePaths (QString FileDescription, QString *warningString, QString *errorString, QString userInput) {
    QString PlatformSlashType;
    QString OtherPlatformSlashType;
    #ifdef Q_OS_WIN32
        PlatformSlashType= "\\";
        OtherPlatformSlashType= "/";
    #else
        PlatformSlashType= "/";
        OtherPlatformSlashType="\\";
    #endif

    if (userInput.contains(OtherPlatformSlashType) ) {
        *errorString += FileDescription + " file path is not valid.\n";
    } else {
        #ifdef Q_OS_WIN32
            if (userInput.contains(QRegularExpression("^:[a-zA-Z0-9]{0,}"))==true ||   userInput.contains(QRegularExpression("^[A-Z]{1}:[a-zA-Z0-9]{1,}"))==true || userInput.contains(QRegularExpression("^\\\\"))==true || userInput.contains(QRegularExpression("^[a-z]:"))==true ) {
                 *errorString += FileDescription + " file path is not valid.\n";
                return;
            }
            if ( userInput.contains(QRegularExpression("^[A-Z]{1}:\\\\"))==false ) {
        #else
            if (userInput.startsWith("/")==false) {
        #endif
                *warningString += FileDescription + " file path is not absolute.\n";
            }
    }
}

//Get PRN range from input parameters
int gLAB_GUI::GetPRNRangeParam(QString *userInputSingleSpace, QString *option, enum GNSSystem *System, int *StartPRN, int *EndPRN, QString *warningString) {
    int HyphenPos;
    const int listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};

    HyphenPos=userInputSingleSpace->section(" ", 0,0).indexOf("-",1);
    *System=this->ConsString2ConsEnum(userInputSingleSpace->section(" ", 0,0).at(0));
    if (HyphenPos!=-1) {
        *StartPRN=userInputSingleSpace->section(" ", 0,0).mid(1, HyphenPos-1).toInt();
        *EndPRN=userInputSingleSpace->section(" ", 0,0).mid(HyphenPos+1).toInt();
        if (*StartPRN<0 || *StartPRN>listMaxSatGNSS[*System]) {
            *warningString += "Parameter '" + *option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[*System]) + ". It was skipped.\n";
        } else if (*EndPRN<*StartPRN || *EndPRN>listMaxSatGNSS[*System]) {
            *warningString += "PRN range in parameter '" + *option + "' must end in a number equal or greater than the starting satellite or up to " + QString("%1").arg(listMaxSatGNSS[*System]) + ". It was skipped.\n";
        } else {
            if (*StartPRN==0) {
                *StartPRN=1;
                *EndPRN=listMaxSatGNSS[*System];
            } else {
                *EndPRN=*StartPRN;
            }
            return 1;
        }
    } else {
        *StartPRN=userInputSingleSpace->section(" ", 0,0).mid(1).toInt();
        if (*StartPRN<0 || *StartPRN>listMaxSatGNSS[*System]) {
            *warningString += "Parameter '" + *option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[*System]) + ". It was skipped.\n";
        } else {
            if (*StartPRN==0) {
                *StartPRN=1;
                *EndPRN=listMaxSatGNSS[*System];
            } else {
                *EndPRN=*StartPRN;
            }
            return 1;
        }
    }
    return 0;
}

//Function to check what type of DCB file is
int gLAB_GUI::checkDCBFileType(QString filepath) {
    //0-> P1-C1 DCB 1-> P1-P2 DCB 2-> P2-C2 DCB 3-> Rinex Nav 4-> MGEX DCB 5-> IONEX
    QString line;
    QFile file(filepath);
    //QFileInfo does not query filesystem if it is not necessary. As the filename is in the string,
    // it will not query the system (therefore it doesn't matter if the file exists or not)
    QFileInfo fi = filepath;
    QString FileNoPath = fi.fileName();
    QTextStream InputFile(&file);
    InputFile.setAutoDetectUnicode(true);

    if ( file.open(QIODevice::ReadOnly) ) {
         //File opened
        line = QString(InputFile.readLine());
        file.close(); //Close file, as we only have to read the first line
        if ( line == "") { // Empty line, not a valid DCB file
            return -1;
        }
        if ( line.at(0) == '\n' || line.at(0) == '\r') { // Empty line, not a valid DCB file
            return -1;
        }
        //Search for 'P1-C1' text in line
        if (line.contains("P1-C1", Qt::CaseInsensitive)==true || line.contains("C1-P1", Qt::CaseInsensitive)==true ) {
            //File is P1-C1 type
            return 0;
        } else if (line.contains("P1-P2", Qt::CaseInsensitive)==true || line.contains("P2-P1", Qt::CaseInsensitive)==true ) {
            //File is P1-P2 type
            return 1;
        } else if (line.contains("P2-C2", Qt::CaseInsensitive)==true || line.contains("C2-P2", Qt::CaseInsensitive)==true ) {
            //File is P2-C2 type
            return 2;
        } else if (line.contains("RINEX VERSION / TYPE", Qt::CaseInsensitive)==true && line.contains("NAVIGATION", Qt::CaseInsensitive)==true ) {
            //File is a RINEX navigation file
            return 3;
        } else if (line.contains("%=BIA", Qt::CaseInsensitive)==true ) {
            //File is MGEX DCB
            return 4;
        } else if (line.contains("IONEX VERSION / TYPE", Qt::CaseInsensitive)==true ) {
            //File is IONEX
            return 5;
        } else {
            //Not a DCB file or unknown DCB file
            return -1;
        }
     } else {
        //Failed to open file. Try to guess type by filename
        if (FileNoPath.contains("P1C1", Qt::CaseInsensitive)==true || FileNoPath.contains("C1P1", Qt::CaseInsensitive)==true ) {
            //File is P1-C1 type
            return 0;
        } else if (FileNoPath.contains("P1P2", Qt::CaseInsensitive)==true || FileNoPath.contains("P2P1", Qt::CaseInsensitive)==true ) {
            //File is P1-P2 type
            return 1;
        } else if (FileNoPath.contains("P2C2", Qt::CaseInsensitive)==true || FileNoPath.contains("C2P2", Qt::CaseInsensitive)==true ) {
            //File is P2-C2 type
            return 2;
        } else if (FileNoPath.contains(QRegularExpression("\\.[0-9][0-9][nN]$"))==true) {
            //File is a RINEX navigation file
            return 3;
        } else if (FileNoPath.contains("DCB.BSX", Qt::CaseInsensitive)==true ) {
            //File is MGEX DCB
            return 4;
        } else if (FileNoPath.contains(QRegularExpression("\\.[0-9][0-9][iI]$"))==true) {
            //File is a IONEX
            return 5;
        } else {
            //Not a DCB file or unknown DCB file
            return -1;
        }
    }
}

//Check if string has non ASCII characters. Return 1 if it finds any, 0 if not
int gLAB_GUI::checknonASCIIcharacters(QString str) {
    //NOTE: This function has been disabled, as the support for non-ASCII characters
    //is depending on the local configuration (if the system terminal can handle the
    //non-ascii characters, gLAB will als handle them and vicerversa)
    return 0; //remove this return to enable again this function
    int i;
    for(i=0; i<str.size(); i++) {
        if(str.at(i).unicode() > 127) return 1;
    }
    return 0;
}


// Modelling Defaults
void gLAB_GUI::setModellingDefaults() {
    ui->lineEditOrbitInterpolationDegree->setText("10");
    ui->lineEditClockInterpolationDegree->setText("0");
    ui->lineEditOrbitConsecutiveGaps->setText("8");
    ui->lineEditClockConsecutiveGaps->setText("2");
    ui->lineEditOrbitMaxGaps->setText("16");
    ui->lineEditClockMaxGaps->setText("4");
    ui->lineEditAPCf1north->setText("0");
    ui->lineEditAPCf1east->setText("0");
    ui->lineEditAPCf1up->setText("0");
    ui->lineEditAPCf2north->setText("0");
    ui->lineEditAPCf2east->setText("0");
    ui->lineEditAPCf2up->setText("0");
    ui->lineEditARPnorth->setText("0");
    ui->lineEditARPeast->setText("0");
    ui->lineEditARPup->setText("0");
    this->on_groupBoxConcatenedPreciseFiles_clicked(false);
    ui->radioButtonOrbitCurrentDay->setChecked(false);
    ui->radioButtonOrbitNextDay->setChecked(true);
    ui->radioButtonClockCurrentDay->setChecked(false);
    ui->radioButtonClockNextDay->setChecked(true);
    ui->checkBoxStrictRadome->setChecked(false);
}

// Filter Defaults
void gLAB_GUI::setFilterDefaults() {
    if ( ui->labelCurrentTemplate->text() == "PPP" ) {
        ui->lineEditFixedStdDevSingleCode->setText("100");
        ui->lineEditFixedStdDevSingleCarrier->setText("0.5");
    } else {
        ui->lineEditFixedStdDevSingleCode->setText("1");
        ui->lineEditFixedStdDevSingleCarrier->setText("0.01");
    }
    ui->lineEditFixedStdDevDualCode->setText("3");
    ui->lineEditFixedStdDevDualCarrier->setText("0.03");
    ui->lineEditElevationStdDevSingleCodeA->setText("");
    ui->lineEditElevationStdDevSingleCodeB->setText("");
    ui->lineEditElevationStdDevSingleCodeC->setText("");
    ui->lineEditElevationStdDevSingleCarrierA->setText("");
    ui->lineEditElevationStdDevSingleCarrierB->setText("");
    ui->lineEditElevationStdDevSingleCarrierC->setText("");
    ui->lineEditElevationStdDevDualCodeA->setText("");
    ui->lineEditElevationStdDevDualCodeB->setText("");
    ui->lineEditElevationStdDevDualCodeC->setText("");
    ui->lineEditElevationStdDevDualCarrierA->setText("");
    ui->lineEditElevationStdDevDualCarrierB->setText("");
    ui->lineEditElevationStdDevDualCarrierC->setText("");
    //ui->lineEditPhiCoordinates->setText("1");
    ui->lineEditPhiClock->setText("0");
    ui->lineEditPhiTropo->setText("1");
    ui->lineEditPhiPhaseAmbiguities->setText("1");
    //ui->lineEditQcoordinates->setText("0");
    ui->lineEditQclock->setText("9e10");
    ui->lineEditQtropo->setText("1e-4");
    ui->lineEditQphaseAmbiguities->setText("0");
    ui->lineEditPoCoordinates->setText("1e8");
    ui->lineEditPoClock->setText("9e10");
    ui->lineEditPoTropo->setText("0.25");
    ui->lineEditPoPhaseAmbiguities->setText("400");
    ui->lineEditMaxHDOP->setText("4");
    ui->lineEditMaxPDOP->setText("6");
    ui->lineEditMaxGDOP->setText("30");
    ui->lineEditPrefitOutliers->setText("40");
}

// SBAS Defaults
void gLAB_GUI::setSBASmodellingDefaults() {
    this->on_comboBoxSBASApplication_currentIndexChanged(0);
    this->on_comboBoxSbasNavigationMode_currentIndexChanged(0);
    this->on_comboBoxGEOselection_currentIndexChanged(2);
    this->on_checkBoxGEOexclusion_clicked(false);
    this->on_checkBoxNavigationModeSwitching_clicked(false);
    this->on_comboBoxGEOexclusion_currentIndexChanged(0);
    this->on_checkBoxGEOswitching_clicked(false);
    this->on_checkBoxSelectBestGEO_clicked(false);
    ui->comboBoxAirboneReceiverType->setCurrentIndex(2);
    this->on_groupBoxUserDefinedReceiverSigma_clicked(false);
    this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(false);
    this->on_checkBoxUserDefinedReceiverSigmaDivergence_clicked(false);
    this->on_checkBoxUserDefinedReceiverSigmaNoise_clicked(false);
    this->on_groupBoxMessageTimeOuts_clicked(false);
    ui->lineEditGEOselection->setText("");
    ui->lineEditGEOexclusion1->setText("");
    ui->lineEditGEOexclusion2->setText("");
    ui->lineEditGEOexclusion3->setText("");
    ui->lineEditSbasSigmaMultipathA->setText("0.13");
    ui->lineEditSbasSigmaMultipathB->setText("0.53");
    ui->lineEditSbasSigmaMultipathC->setText("10");
    ui->lineEditSbasSigmaDivergence->setText("0");
    ui->lineEditSbasSigmaNoise->setText("0.36");
    ui->lineEditPRNmaskPA->setText("600");
    ui->lineEditPRNmaskNPA->setText("600");
    ui->lineEditFastCorrectionsPA->setText("");
    ui->lineEditFastCorrectionsNPA->setText("");
    ui->lineEditRRCcorrectionsPA->setText("");
    ui->lineEditRRCcorrectionsNPA->setText("");
    ui->lineEditIntegrityInfoPA->setText("12");
    ui->lineEditIntegrityInfoNPA->setText("18");
    ui->lineEditFastCorrectionDegradationFactorPA->setText("240");
    ui->lineEditFastCorrectionDegradationFactorNPA->setText("360");
    ui->lineEditDegradationParametersPA->setText("240");
    ui->lineEditDegradationParametersNPA->setText("360");
    ui->lineEditLongTermSatelliteCorrectionsPA->setText("240");
    ui->lineEditLongTermSatelliteCorrectionsNPA->setText("360");
    ui->lineEditIonosphericGridPointsMaskPA->setText("1200");
    ui->lineEditIonosphericGridPointsMaskNPA->setText("1200");
    ui->lineEditIonosphericDelayCorrectionsPA->setText("600");
    ui->lineEditIonosphericDelayCorrectionsNPA->setText("600");
    ui->lineEditServiceMessagePA->setText("86400");
    ui->lineEditServiceMessageNPA->setText("86400");
    ui->lineEditClockEphemerisCovarianceMatrixPA->setText("240");
    ui->lineEditClockEphemerisCovarianceMatrixNPA->setText("360");
    ui->lineEditGeoNavigationMessagePA->setText("240");
    ui->lineEditGeoNavigationMessageNPA->setText("360");
    ui->lineEditGeoSatelliteAlmanacsPA->setText("9999999");
    ui->lineEditGeoSatelliteAlmanacsNPA->setText("9999999");
    ui->lineEditNetworkTimeParametersPA->setText("86400");
    ui->lineEditNetworkTimeParametersNPA->setText("86400");
    ui->lineEditDoNotUseForSafetyAppPA->setText("9999999");
    ui->lineEditDoNotUseForSafetyAppNPA->setText("9999999");
    ui->lineEditOffsetFastCorrNoMT10->setText("8");
    ui->lineEditGEOadquisitionTime->setText("");
    ui->lineEditSwitchinCooltime->setText("");
    ui->lineEditkhpa->setText("6");
    ui->lineEditkvpa->setText("5.33");
    ui->lineEditkhnpa->setText("6.18");
    ui->lineEditkvnpa->setText("5.33");
    ui->lineEditHorizontalAlarmLimitSBAS->setText("40");
    ui->lineEditVerticalAlarmLimitSBAS->setText("50");
    ui->lineEditPercentileValue->setText("95");
    ui->lineEditSlidingWindowSBAS->setText("15");
    ui->lineEditMaritimeWindowSBAS->setText("15");
    ui->checkBoxWaitforDayStart->setChecked(true);
    this->on_checkBoxStartTimeSummary_clicked(false);
    this->on_groupBoxSbasAdvancedOptions_clicked(false);
    ui->checkBoxParseAlarm->setChecked(false);
    ui->checkBoxIgnoreAllAlarm->setChecked(false);
    ui->checkBoxAllowMixedGEOdata->setChecked(false);
    ui->checkBoxAllowKlobucharIono->setChecked(true);    
    ui->comboBoxUDREIThresholds->setCurrentIndex(10);
    this->on_checkBoxDiscardUDREIThreshold_clicked(false);
    this->on_checkBoxMaintainCurrentGEOafterGEOswitch_clicked(true);
    ui->lineEditGEOadquisitionTime->setText("300");
    ui->lineEditSwitchinCooltime->setText("0");
    this->on_groupBoxSBASKFactor_clicked(false);
    this->on_groupBoxDisableSpecificCorrections_clicked(false);
    ui->checkBoxDisableFastCorrections->setChecked(false);
    ui->checkBoxDisableRRCcorrections->setChecked(false);
    ui->checkBoxDisableSlowCorrections->setChecked(false);
    ui->checkBoxDisableIonosphereCorrections->setChecked(false);
    ui->checkBoxDisableEnRoute->setChecked(false);
    this->on_groupBoxDisableSpecificSigmas_clicked(false);
    ui->checkBoxDisableFastCorrectionsSigma->setChecked(false);
    ui->checkBoxDisableRRCsigma->setChecked(false);
    ui->checkBoxDisableSlowCorrectionsSigma->setChecked(false);
    ui->checkBoxDisableIonosphereSigma->setChecked(false);
    ui->checkBoxDisableTroposphereSigma->setChecked(false);
    this->on_groupBoxStanfordESA_clicked(false);
    this->on_checkBoxStanfordESAallGeometries_clicked(true);
    ui->lineEditSmoothMinSbas->setText("360");
    ui->lineEditStanfordEsaXmax->setText("50");
    ui->lineEditStanfordEsaYmax->setText("50");
    ui->lineEditStanfordEsaXres->setText("0.1");
    ui->lineEditStanfordEsaYres->setText("0.1");
    ui->lineEditHorizontalIntegrityRatio->setText("0.7");
    ui->lineEditVerticalIntegrityRatio->setText("0.7");
}

// Output defaults
void gLAB_GUI::setOutputDefaults() {

    ui->lineEditKML_Dec->setText("30");
    ui->lineEditKML_From->setText("-");
    ui->lineEditKML_To->setText("-");
    ui->lineEditSP3Letter->setText("L");
    ui->lineEditSP3PRN->setText("9");
    ui->KMLTimeStampsRangeFrame->setHidden(false);
}

///////////// Templates /////////////
// SPP Template
void gLAB_GUI::on_actionSPP_triggered() {
    ui->labelCurrentTemplate->setText("SPP");
    ui->actionSPP->setChecked(true);

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();    
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonIonoSourceBrdc_clicked();
    this->on_groupBoxReferenceStation_clicked(false);
    this->on_radioButtonRinex_clicked();
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);
    ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);
    //Manually set size of GroupBox groupBoxAPrioriPosition in Linux and Mac, so it does not reescale when changing a priori receiver options
    #if defined Q_OS_LINUX || defined Q_OS_MAC
        ui->groupBoxAPrioriPosition->setMinimumWidth(303);
    #endif

    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(true);
    ui->lineEditDataDecimator->setText("300");
    ui->checkBoxDiscardEclipse->setChecked(false);
    ui->checkBoxDiscardUnhealthy->setChecked(true);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(true);
    ui->checkBoxL1C1->setChecked(false);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("40");
    this->on_pushButtonGPSSatSelAll_clicked();
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_comboBoxSNRThresholds_currentIndexChanged(4);
    this->on_checkBoxDiscardSNRThreshold_clicked(false);


    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(true);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    ui->checkBoxAntennaPhase->setChecked(false);
    ui->checkBoxAntennaReference->setChecked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(false);
    ui->checkBoxRelativisticClock->setChecked(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(0);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    this->on_checkBoxP1P2correction_clicked(true);
    ui->comboBoxP1P2correction->setCurrentIndex(0);
    this->on_checkBoxP1C1correction_clicked(true);
    ui->comboBoxP1C1correction->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);


    // FILTER
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSelectionPseudorange_clicked();
    this->on_checkBoxSmoothing_clicked(false);
    this->on_radioButtonSingleFreq_clicked();
    this->on_radioButtonKinematic_clicked();
    this->on_checkBoxEstimateTroposphere_clicked(false);
    this->on_radioButtonFixedStdDevSingleCode_clicked();
    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
    this->on_radioButtonFixedStdDevDualCode_clicked();
    this->on_radioButtonFixedStdDevDualCarrier_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(false);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(false);
    setFilterDefaults();
    this->on_groupBoxStanfordESA_clicked(false);
    this->on_checkBoxPrefitOutliers_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(false);
    ui->lineEditElevationStdDevSingleCodeA->setText("0.13");
    ui->lineEditElevationStdDevSingleCodeB->setText("0.53");
    ui->lineEditElevationStdDevSingleCodeC->setText("10");
    ui->lineEditElevationStdDevSingleCarrierA->setText("0.13");
    ui->lineEditElevationStdDevSingleCarrierB->setText("0.53");
    ui->lineEditElevationStdDevSingleCarrierC->setText("10");
    ui->lineEditElevationStdDevDualCodeA->setText("0.13");
    ui->lineEditElevationStdDevDualCodeB->setText("0.53");
    ui->lineEditElevationStdDevDualCodeC->setText("10");
    ui->lineEditElevationStdDevDualCarrierA->setText("0.13");
    ui->lineEditElevationStdDevDualCarrierB->setText("0.53");
    ui->lineEditElevationStdDevDualCarrierC->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesAll_clicked();
    ui->checkBoxPrintMeas->setChecked(false);
    ui->checkBoxPrintSatsel->setChecked(false);
    ui->checkBoxPrintUsererror->setChecked(true);
    this->on_pushButtonOrbitsComparisonMessagesNone_clicked();
    this->on_pushButtonSbasMessagesNone_clicked();
    this->on_pushButtonDgnssMessagesNone_clicked();
    ui->groupBoxStanfordESA->setHidden(true);
    this->setOutputDefaults();
    ui->stackedWidgetOtherMessages->setCurrentIndex(0);
    ui->stackedWidgetOtherMessages->setHidden(true);
    ui->frameOutputSatVel->setContentsMargins(0,0,0,9);
    ui->radioButtonSatVelECEF->setChecked(true);
    this->on_checkBoxPrintSummary_clicked(true);
    ui->labelSummarySlidingWindow->setHidden(true);
    ui->lineEditSlidingWindowSBAS->setHidden(true);
    ui->labelSummarySlidingWindowUnit->setHidden(true);    

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(0);
}

// PPP Template
void gLAB_GUI::on_actionPPP_triggered() {
    ui->labelCurrentTemplate->setText("PPP");
    ui->actionPPP->setChecked(true);

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxAntex_clicked(true);
    this->on_radioButtonOrbitPrecise1file_clicked();    
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonIonoSourceBrdc_clicked();
    this->on_groupBoxReferenceStation_clicked(false);
    this->on_radioButtonRinex_clicked();
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);
    //Manually set size of GroupBox groupBoxAPrioriPosition in Linux, so it does not reescale when changing a priori receiver options
    #ifdef Q_OS_LINUX
        ui->groupBoxAPrioriPosition->setMinimumWidth(275);
    #endif


    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(true);
    ui->lineEditDataDecimator->setText("300");
    ui->checkBoxDiscardEclipse->setChecked(true);
    ui->checkBoxDiscardUnhealthy->setChecked(true);
    ui->checkBoxLLI->setChecked(true);
    this->on_checkBoxNcon_clicked(true);
    ui->checkBoxL1C1->setChecked(false);
    ui->checkBoxMW->setChecked(true);
    ui->checkBoxLI->setChecked(true);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("40");
    this->on_pushButtonGPSSatSelAll_clicked();
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_comboBoxSNRThresholds_currentIndexChanged(4);
    this->on_checkBoxDiscardSNRThreshold_clicked(false);

    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(true);
    ui->checkBoxAntennaPhase->setChecked(true);
    ui->checkBoxAntennaReference->setChecked(true);
    this->on_checkBoxAntennaPhase_clicked(true);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    this->on_checkBoxIonoCorrection_clicked(false);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(1);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(1);
    this->on_checkBoxP1P2correction_clicked(false);
    this->on_checkBoxP1C1correction_clicked(true);
    ui->comboBoxP1C1correction->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(true);
    ui->checkBoxTides->setChecked(true);
    ui->checkBoxRelativisticPath->setChecked(true);
    this->on_radioButtonAPCread_clicked();
    this->on_radioButtonARPread_clicked();
    ui->stackedWidgetAPCf1f2->setCurrentIndex(0);

    // FILTER
    setFilterDefaults();
    ui->lineEditSmoothing->setText("10");
    this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
    this->on_checkBoxSmoothing_clicked(false);
    this->on_radioButtonDualFreq_clicked();
    this->on_radioButtonStatic_clicked();
    this->on_checkBoxEstimateTroposphere_clicked(true);
    this->on_radioButtonFixedStdDevSingleCode_clicked();
    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
    this->on_radioButtonFixedStdDevDualCode_clicked();
    this->on_radioButtonFixedStdDevDualCarrier_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(true);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(false);

    this->on_groupBoxStanfordESA_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(false);
    ui->lineEditElevationStdDevSingleCodeA->setText("0.13");
    ui->lineEditElevationStdDevSingleCodeB->setText("0.53");
    ui->lineEditElevationStdDevSingleCodeC->setText("10");
    ui->lineEditElevationStdDevSingleCarrierA->setText("0.13");
    ui->lineEditElevationStdDevSingleCarrierB->setText("0.53");
    ui->lineEditElevationStdDevSingleCarrierC->setText("10");
    ui->lineEditElevationStdDevDualCodeA->setText("0.13");
    ui->lineEditElevationStdDevDualCodeB->setText("0.53");
    ui->lineEditElevationStdDevDualCodeC->setText("10");
    ui->lineEditElevationStdDevDualCarrierA->setText("0.13");
    ui->lineEditElevationStdDevDualCarrierB->setText("0.53");
    ui->lineEditElevationStdDevDualCarrierC->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesAll_clicked();
    ui->checkBoxPrintMeas->setChecked(false);
    ui->checkBoxPrintSatsel->setChecked(false);
    ui->checkBoxPrintUsererror->setChecked(true);;
    this->on_pushButtonOrbitsComparisonMessagesNone_clicked();
    this->on_pushButtonSbasMessagesNone_clicked();
    this->on_pushButtonDgnssMessagesNone_clicked();
    ui->groupBoxStanfordESA->setHidden(true);
    this->setOutputDefaults();
    ui->stackedWidgetOtherMessages->setCurrentIndex(0);
    ui->stackedWidgetOtherMessages->setHidden(true);
    ui->frameOutputSatVel->setContentsMargins(0,0,0,9);
    ui->radioButtonSatVelECEF->setChecked(true);
    this->on_checkBoxPrintSummary_clicked(true);
    ui->labelSummarySlidingWindow->setHidden(true);
    ui->lineEditSlidingWindowSBAS->setHidden(true);
    ui->labelSummarySlidingWindowUnit->setHidden(true);    

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(0);
}

// SBAS Template
void gLAB_GUI::on_actionSBAS_triggered() {
    ui->labelCurrentTemplate->setText("SBAS");
    ui->actionSBAS->setChecked(true);
    this->on_groupBoxConverterSBAS_clicked(true); // Converter
    this->on_groupBoxConverterDgnss_clicked(false); // Converter

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();    
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_groupBoxReferenceStation_clicked(false);    
    this->on_groupBoxSbas_clicked(true);
    this->on_radioButtonRinex_clicked();
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    this->on_radioButtonIonoSourceSbas_clicked();
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);
    //Manually set size of GroupBox groupBoxAPrioriPosition in Linux, so it does not reescale when changing a priori receiver options
    #ifdef Q_OS_LINUX
        ui->groupBoxAPrioriPosition->setMinimumWidth(275);
    #endif


    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(true);
    ui->lineEditDataDecimator->setText("1");
    ui->checkBoxDiscardEclipse->setChecked(false);
    ui->checkBoxDiscardUnhealthy->setChecked(true);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(false);
    ui->checkBoxL1C1->setChecked(true);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("10");
    this->on_pushButtonGPSSatSelAll_clicked();
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_checkBoxDiscardSNRThreshold_clicked(true);
    this->on_comboBoxSNRThresholds_currentIndexChanged(4);

    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    ui->checkBoxAntennaPhase->setChecked(false);
    ui->checkBoxAntennaReference->setChecked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(4);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    this->on_checkBoxP1P2correction_clicked(true);
    ui->comboBoxP1P2correction->setCurrentIndex(0);
    ui->comboBoxP1C1correction->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);
    this->setSBASmodellingDefaults();


    // FILTER
    setFilterDefaults();
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSelectionPseudorange_clicked();
    this->on_checkBoxSmoothing_clicked(true);
    this->on_radioButtonSingleFreq_clicked();
    this->on_radioButtonKinematic_clicked();
    this->on_checkBoxEstimateTroposphere_clicked(false);
    this->on_radioButtonFixedStdDevSingleCode_clicked();
    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
    this->on_radioButtonFixedStdDevDualCode_clicked();
    this->on_radioButtonFixedStdDevDualCarrier_clicked();
    this->on_radioButtonStdDevSBAS_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(false);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(true);
    ui->lineEditElevationStdDevSingleCodeA->setText("0.13");
    ui->lineEditElevationStdDevSingleCodeB->setText("0.53");
    ui->lineEditElevationStdDevSingleCodeC->setText("10");
    ui->lineEditElevationStdDevSingleCarrierA->setText("0.13");
    ui->lineEditElevationStdDevSingleCarrierB->setText("0.53");
    ui->lineEditElevationStdDevSingleCarrierC->setText("10");
    ui->lineEditElevationStdDevDualCodeA->setText("0.13");
    ui->lineEditElevationStdDevDualCodeB->setText("0.53");
    ui->lineEditElevationStdDevDualCodeC->setText("10");
    ui->lineEditElevationStdDevDualCarrierA->setText("0.13");
    ui->lineEditElevationStdDevDualCarrierB->setText("0.53");
    ui->lineEditElevationStdDevDualCarrierC->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintCS->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
    ui->checkBoxPrintSatsel->setChecked(true);
    this->on_pushButtonOrbitsComparisonMessagesNone_clicked();
    this->on_pushButtonSbasMessagesNone_clicked();
    ui->checkBoxPrintSbasout->setChecked(true);
    ui->checkBoxPrintUsererror->setChecked(true);
    this->on_pushButtonDgnssMessagesNone_clicked();
    ui->groupBoxStanfordESA->setHidden(false);
    this->setOutputDefaults();
    ui->stackedWidgetOtherMessages->setCurrentIndex(1);
    ui->stackedWidgetOtherMessages->setHidden(false);
    ui->radioButtonSatVelECEF->setChecked(true);
    ui->frameOutputSatVel->setContentsMargins(0,11,0,9);
    this->on_checkBoxPrintSummary_clicked(true);
    ui->labelSummarySlidingWindow->setHidden(false);
    ui->lineEditSlidingWindowSBAS->setHidden(false);
    ui->labelSummarySlidingWindowUnit->setHidden(false);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(false);
    ui->stackedWidgetTemplates->setCurrentIndex(1);
}

// DGNSS Template
void gLAB_GUI::on_actionDGNSS_triggered() {
    ui->labelCurrentTemplate->setText("DGNSS");
    ui->actionDGNSS->setChecked(true);
    this->on_groupBoxConverterSBAS_clicked(false); // Converter
    this->on_groupBoxConverterDgnss_clicked(true); // Converter

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxReferenceStation_clicked(true);
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    this->on_radioButtonIonoSourceBrdc_clicked();
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);
    this->on_groupBoxIonoSource_clicked(false);
    QDate date = QDate(1979, 12, 31);
    ui->dateEdit1->setDate(date);
    ui->dateEdit2->setDate(date);
    ui->dateEdit3->setDate(date);
    this->on_radioButtonRtcmBaseline_clicked();
    //Manually set size of GroupBox groupBoxAPrioriPosition in Linux, so it does not reescale when changing a priori receiver options
    #ifdef Q_OS_LINUX
        ui->groupBoxAPrioriPosition->setMinimumWidth(285);
    #endif

    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(false);
    ui->lineEditDataDecimator->setText("");
    ui->checkBoxNcon->setChecked(false);
    ui->checkBoxDiscardEclipse->setChecked(false);
    ui->checkBoxDiscardUnhealthy->setChecked(true);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(false);
    ui->checkBoxL1C1->setChecked(true);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("10");
    this->on_pushButtonGPSSatSelAll_clicked();
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_checkBoxDiscardSNRThreshold_clicked(true);
    this->on_comboBoxSNRThresholds_currentIndexChanged(4);

    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    ui->checkBoxAntennaPhase->setChecked(false);
    ui->checkBoxAntennaReference->setChecked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(0);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    this->on_checkBoxP1P2correction_clicked(true);
    ui->comboBoxP1P2correction->setCurrentIndex(0);
    this->on_checkBoxP1C1correction_clicked(true);
    ui->comboBoxP1C1correction->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);
    ui->lineEditMaxAgeDgnss->setText("31");
    ui->lineEditMaxValueDGNSS->setText("500");

    // FILTER
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSelectionPseudorange_clicked();
    this->on_checkBoxSmoothing_clicked(true);
    this->on_radioButtonSingleFreq_clicked();
    this->on_radioButtonKinematic_clicked();
    this->on_checkBoxEstimateTroposphere_clicked(false);
    this->on_radioButtonFixedStdDevSingleCode_clicked();
    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
    this->on_radioButtonFixedStdDevDualCode_clicked();
    this->on_radioButtonFixedStdDevDualCarrier_clicked();
    this->on_radioButtonStdDevDGNSS_clicked();
    this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(false);
    this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(true);
    ui->lineEditSmoothMinDgnss->setText("360");
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(true);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(false);
    setFilterDefaults();
    this->on_groupBoxStanfordESA_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(true);
    ui->lineEditElevationStdDevSingleCodeA->setText("0.13");
    ui->lineEditElevationStdDevSingleCodeB->setText("0.53");
    ui->lineEditElevationStdDevSingleCodeC->setText("10");
    ui->lineEditElevationStdDevSingleCarrierA->setText("0.13");
    ui->lineEditElevationStdDevSingleCarrierB->setText("0.53");
    ui->lineEditElevationStdDevSingleCarrierC->setText("10");
    ui->lineEditElevationStdDevDualCodeA->setText("0.13");
    ui->lineEditElevationStdDevDualCodeB->setText("0.53");
    ui->lineEditElevationStdDevDualCodeC->setText("10");
    ui->lineEditElevationStdDevDualCarrierA->setText("0.13");
    ui->lineEditElevationStdDevDualCarrierB->setText("0.53");
    ui->lineEditElevationStdDevDualCarrierC->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesAll_clicked();
    ui->checkBoxPrintMeas->setChecked(false);
    ui->checkBoxPrintSatsel->setChecked(false);
    this->on_pushButtonOrbitsComparisonMessagesNone_clicked();
    this->on_pushButtonSbasMessagesNone_clicked();
    this->on_pushButtonDgnssMessagesNone_clicked();
    ui->checkBoxPrintDgnss->setChecked(true);
    ui->groupBoxStanfordESA->setHidden(true);
    this->setOutputDefaults();
    ui->stackedWidgetOtherMessages->setCurrentIndex(2);
    ui->stackedWidgetOtherMessages->setHidden(false);
    ui->frameOutputSatVel->setContentsMargins(0,11,0,9);
    ui->radioButtonSatVelECEF->setChecked(true);
    ui->checkBoxKMLRefStations->setChecked(true);
    this->on_checkBoxPrintSummary_clicked(true);
    ui->labelSummarySlidingWindow->setHidden(true);
    ui->lineEditSlidingWindowSBAS->setHidden(true);
    ui->labelSummarySlidingWindowUnit->setHidden(true);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(2);

    // CONVERTER
    ui->dateEdit4->setDate(date);
    ui->comboBoxConverterDgnssOutputRinex->setCurrentIndex(1);

}
///////// End of Templates /////////


//////////////// The modes of gLAB ////////////////
void gLAB_GUI::on_actionPositioning_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(0);
    ui->stackedWidgetMainButtons2->setCurrentIndex(0);
    ui->labelCurrentTemplateFixed->setHidden(false);
    ui->labelCurrentTemplate->setHidden(false);
    ui->actionSPP->setEnabled(true);
    ui->actionPPP->setEnabled(true);
    ui->actionSBAS->setEnabled(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[0]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionAnalysis_triggered() {
    if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
    ui->stackedWidgetMainWindow->setCurrentIndex(1);
    ui->stackedWidgetMainButtons2->setCurrentIndex(1);
    ui->labelCurrentTemplateFixed->setHidden(false);
    ui->labelCurrentTemplate->setHidden(false);
    ui->actionSPP->setEnabled(true);
    ui->actionPPP->setEnabled(true);
    ui->actionSBAS->setEnabled(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionConverter_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(2);
    ui->stackedWidgetMainButtons2->setCurrentIndex(2);
    ui->labelCurrentTemplateFixed->setHidden(false);
    ui->labelCurrentTemplate->setHidden(false);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS->setEnabled(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[2]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionCompare_Orbits_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(3);
    ui->stackedWidgetMainButtons2->setCurrentIndex(3);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS->setEnabled(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[3]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionShow_Orbits_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(4);
    ui->stackedWidgetMainButtons2->setCurrentIndex(4);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS->setEnabled(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[4]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionAdd_User_Error_to_RINEX_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(5);
    ui->stackedWidgetMainButtons2->setCurrentIndex(5);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS->setEnabled(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[5]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
}

void gLAB_GUI::on_actionExit_triggered() {
    qApp->closeAllWindows();
}
//////////// End of The modes of gLAB /////////////


// Function to set the correct size in the group boxes
void gLAB_GUI::setCorrectSizes() {
    QFont font;
    int   width;
    #ifdef Q_OS_LINUX
      font.setPointSize(9);
      width=73;
    #elif defined(Q_OS_WIN32)
      font.setPointSize(9);
      width=58;
    #elif defined(Q_OS_MAC)
      font.setPointSize(13);
      width=73;
    #endif
    font.setBold(false);
    ui->tabWidget->setFont(font);
    ui->labelDevelopedByGAGE->setFont(font);
    ui->labelCurrentTemplateFixed->setFont(font);
    font.setBold(true);
    // Input
    ui->groupBoxRoverFiles->setFont(font);
    ui->groupBoxAPrioriPosition->setFont(font);
    ui->groupBoxOrbitAndClock->setFont(font);
    ui->groupBoxSbas->setFont(font);
    ui->groupBoxReferenceStation->setFont(font);
    ui->groupBoxIonoSource->setFont(font);
    ui->groupBoxAuxFiles->setFont(font);
    ui->groupBoxP1C1correction->setFont(font);
    ui->groupBoxP1P2correction->setFont(font);
    ui->groupBoxUserAddedError->setFont(font);
    ui->groupBoxUserDefinedSbasSigmaMultipath->setFont(font);
    // Preprocess
    ui->groupBoxSatelliteOptions->setFont(font);
    ui->groupBoxCSdetection->setFont(font);
    ui->groupBoxStationData->setFont(font);
    ui->groupBoxSatSel->setFont(font);
    ui->groupBoxL1C1->setFont(font);
    ui->groupBoxMW->setFont(font);
    ui->groupBoxLI->setFont(font);
    // Model
    ui->groupBoxModellingOptions->setFont(font);
    ui->groupBoxInterpolationOptions->setFont(font);
    ui->groupBoxInterpolationOrbits->setFont(font);
    ui->groupBoxInterpolationClocks->setFont(font);
    ui->groupBoxPreciseProductsDataInterpolation->setFont(font);
    ui->groupBoxReceiverAntennaPhaseCentreCorrection->setFont(font);
    ui->groupBoxReceiverAntennaReferencePointCorrection->setFont(font);
    ui->groupBoxDgnssOptions->setFont(font);
    ui->groupBoxSbasOptions->setFont(font);
    ui->groupBoxUserDefinedReceiverSigma->setFont(font);
    ui->groupBoxMessageTimeOuts->setFont(font);
    ui->groupBoxSbasAdvancedOptions->setFont(font);
    ui->groupBoxGEOandSwitchOptions->setFont(font);
    ui->groupBoxDisableSpecificCorrections->setFont(font);
    ui->groupBoxDisableSpecificSigmas->setFont(font);
    // Filter
    ui->groupBoxMeasurements->setFont(font);
    ui->groupBoxSelection->setFont(font);
    ui->groupBoxSmoothing->setFont(font);
    ui->groupBoxMeasurementConfigurationAndNoise->setFont(font);
    ui->groupBoxParameters->setFont(font);
    ui->groupBoxDOPFilter->setFont(font);
    ui->groupBoxAvailableFrequencies->setFont(font);
    ui->groupBoxTroposphere->setFont(font);
    ui->groupBoxIonosphere->setFont(font);
    ui->groupBoxReceiverKinematics->setFont(font);
    ui->groupBoxOtherOptions->setFont(font);    
    // Output
    ui->groupBoxOutputDestination->setFont(font);
    ui->groupBoxCommonNavigationMessages->setFont(font);
    ui->groupBoxOrbitsComparisonMessages->setFont(font);
    ui->groupBoxSbasMessages->setFont(font);
    ui->groupBoxDgnssMessages->setFont(font);
    ui->groupBoxStanfordESA->setFont(font);
    ui->groupBoxPrintSummary->setFont(font);
    //Compare Orbits
    ui->groupBoxOutputMessagesCompare->setFont(font);
    //Show Orbits
    ui->groupBoxOutputMessagesShowOrbit->setFont(font);
    ui->groupBoxOptionsCompare->setFont(font);
    //User added error
    ui->groupBoxAddErrorInputRinexObservation->setFont(font);
    ui->groupBoxAddErrorUserAddedError->setFont(font);
    ui->groupBoxAddErrorRinexOutput->setFont(font);
    ui->groupBoxAddErrorOutput->setFont(font);
    ui->groupBoxOutputMessagesAddError->setFont(font);

    //Set width to XColumn in Analysis to adjust row
    ui->labelPlot1XColumn->setMinimumWidth(width);
    ui->labelPlot2XColumn->setMinimumWidth(width);
    ui->labelPlot3XColumn->setMinimumWidth(width);
    ui->labelPlot4XColumn->setMinimumWidth(width);
    ui->labelPlot1XColumn->setMaximumWidth(width);
    ui->labelPlot2XColumn->setMaximumWidth(width);
    ui->labelPlot3XColumn->setMaximumWidth(width);
    ui->labelPlot4XColumn->setMaximumWidth(width);
}

void gLAB_GUI::resizeEvent(QResizeEvent* event) {
   QMainWindow::resizeEvent(event);
    #ifndef Q_OS_WIN32
        if (ui->groupBoxStanfordESA->isChecked() == true && ui->checkBox_KML_TimeStamps->isChecked()==true && ui->checkBox_KML_Range->isChecked()==true ) {
            if (this->width()<KMLOPTIONSREDUCETHRESHOLD) {
                //Only reduce names if they don't fit in the screen
                ui->label_KML_Decimation->setText("Dec");
                ui->checkBoxKMLGeoid->setText("Geoid H");
            } else {
                //Names now fit in the screen. Put back them to normal
                ui->label_KML_Decimation->setText("Decimation");
                ui->checkBoxKMLGeoid->setText("Geoid Height");
            }
        }
    #endif
}

// Function to ask for confirmation before exiting gLAB
void gLAB_GUI::closeEvent(QCloseEvent *event) {
    event->ignore();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Close Confirmation",
                                  "You are about to close gLAB.\nAre you sure you want to continue?\n",
                                  QMessageBox::Yes|QMessageBox::No);
    if ( reply == QMessageBox::Yes ) QApplication::quit();
}

// Function that is called when a tab is clicked
void gLAB_GUI::tabClicked() {
    //Hide Main Logo if it is visible
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }
}

// Function to turn on or off all the tooltips and forbidden the wheel scroll in combo boxes
// NOTE: to avoid the mouse wheel efect over the combo boxes, set the its focus to strong focus
bool gLAB_GUI::eventFilter(QObject *obj, QEvent *event) {
    QComboBox* combo = qobject_cast<QComboBox*>(obj);
    QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
    QPoint position = helpEvent->pos();
    if ( event->type() == QEvent::ToolTip ) {
        // Set the tooltips only for the tabs
        if ( obj == ui->tabWidget->tabBar() ) {
            int index = ui->tabWidget->tabBar()->tabAt(position);
            if ( index == 0 && ui->actionTooltips->isChecked() == true ) {
                QToolTip::showText(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Input section</b><br><br>This section provides all the configuration options to select the input files for gLAB.<br>");
            } else if ( index == 1 && ui->actionTooltips->isChecked() == true ) {
                QToolTip::showText(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Preprocess section</b><br><br>This section provides all the configuration options to preprocess the input data. "
                    "In particular, it allows changing the decimation rate, the elevation mask, the cycle-slip detection, "
                    "and selecting individual satellites for the processing.<br>");
            } else if ( index == 2 && ui->actionTooltips->isChecked() == true ) {
                QToolTip::showText(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Modelling section</b><br><br>This section provides the configuration options to set/unset each individual model that is used by gLAB.<br>");
            } else if ( index == 3 && ui->actionTooltips->isChecked() == true ) {
                QToolTip::showText(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Filter section</b><br><br>This section provides all the configuration options to specify the behaviour of the Kalman Filter. "
                    "In particular, the selection of measurement and the parameters to be estimated can be chosen in this section.<br>");
            } else if ( index == 4 && ui->actionTooltips->isChecked() == true ) {
                QToolTip::showText(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Output section</b><br><br>This section provides all the configuration options to select which files and messages are output.<br>");
            }
            return true;
        } else if ( ui->actionTooltips->isChecked() == false ) {
            if ( event->type() == QEvent::ToolTip ) {
                return true;
            } else if ( event->type() == QEvent::Wheel ) {
                if ( combo && !combo->hasFocus() ) {
                    return true;
                }
            } else {
                return QMainWindow::eventFilter(obj, event);
            }
        }
    }
    // Disable mouse wheel in combo boxes
    if ( event->type() == QEvent::Wheel ) {
        if ( combo && !combo->hasFocus() ) {
            return true;
        }
    } else {
        return QMainWindow::eventFilter(obj, event);
    }
    // Obviously innecessary but written to avoid warning
    return QMainWindow::eventFilter(obj, event);
}

// Function to visit the gAGE webpage
void gLAB_GUI::on_actionVisit_gAGE_website_triggered() {
    QDesktopServices::openUrl(QUrl("http://gage.upc.es"));
}

// Function to visit the gLAB release notes
void gLAB_GUI::on_actionRelease_notes_triggered() {
    QDesktopServices::openUrl(QUrl("http://gage.upc.es/glab-release-notes"));
}

// Function to visit the gLAB explained formats
void gLAB_GUI::on_actionExplained_Formats_triggered() {
    QDesktopServices::openUrl(QUrl("http://gage.upc.es/gFD"));
}

// Function to visit the a web with GNSS Calendar formats
void gLAB_GUI::on_actionGNSS_Calendar_triggered() {
    QDesktopServices::openUrl(QUrl("http://www.gnsscalendar.com/"));
}

// Function to show the gLAB GNSS Date Converter
void gLAB_GUI::on_actionGNSS_Date_Converter_triggered() {
   // if(DateConverterWindow==0) {  //Uncomment this line to force only one window at a time can be opened
        DateConverterWindow=1; //This is to avoid opening more than one window of date converter
        DateConvWin = new GNSS_Date_Converter(this);
        //DateConvWin->setModal(true); //This to force the window to not allow the main window until it is closed
        DateConvWin->setAttribute(Qt::WA_DeleteOnClose);
        // Remove question mark, minimize and maximize buttons from the title bar
        DateConvWin->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);
        DateConvWin->show();
   // }
}

// Function to show the gLAB GNSS Coordinate Converter
void gLAB_GUI::on_actionGNSS_Coordinate_Converter_triggered() {
    CoordConvWin = new GNSS_Coord_converter(this);
    //CoordConvWin->setModal(true); //This to force the window to not allow the main window until it is closed
    CoordConvWin->setAttribute(Qt::WA_DeleteOnClose);
    // Remove question mark, minimize and maximize buttons from the title bar
    CoordConvWin->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);
    CoordConvWin->show();
}

// Function to show the gLAB user manual
void gLAB_GUI::on_actionManual_triggered() {
    #ifndef Q_OS_WIN32
        QProcess *processUserManual = new QProcess(this);
    #endif
        QString program;
        QFile HelpFile(":/data/gLAB_SUM.pdf");
        //Qt copy option does not overwrite files. We need to erase first the file if it exits
        if (QFile::exists(qApp->applicationDirPath().append("/gLAB_SUM.pdf"))) {
            QFile::remove(qApp->applicationDirPath().append("/gLAB_SUM.pdf"));
        }
        HelpFile.copy(qApp->applicationDirPath().append("/gLAB_SUM.pdf"));

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("evince " + qApp->applicationDirPath() + "/gLAB_SUM.pdf");
            // Execute the program
            processUserManual->start(program);
        #elif defined(Q_OS_WIN32)
            QString str = qApp->applicationDirPath().replace("\\","/").append("/gLAB_SUM.pdf");
            QDesktopServices::openUrl(QUrl::fromLocalFile(str));
        #elif defined(Q_OS_MAC)
            program = QString("open " + qApp->applicationDirPath() + "/gLAB_SUM.pdf");
            // Execute the program
            processUserManual->start(program);
        #endif
}

// Function to show the gLAB SBAS manual
void gLAB_GUI::on_actionSBAS_Manual_triggered() {
    #ifndef Q_OS_WIN32
        QProcess *processUserManual = new QProcess(this);
    #endif
    QString program;
    QFile HelpFile(":/data/gLAB_SBAS_SUM.pdf");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_SBAS_SUM.pdf"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_SBAS_SUM.pdf"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_SBAS_SUM.pdf"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("evince " + qApp->applicationDirPath() + "/gLAB_SBAS_SUM.pdf");
        // Execute the program
        processUserManual->start(program);
    #elif defined(Q_OS_WIN32)
        QString str = qApp->applicationDirPath().replace("\\","/").append("/gLAB_SBAS_SUM.pdf");
        QDesktopServices::openUrl(QUrl::fromLocalFile(str));
    #elif defined(Q_OS_MAC)
        program = QString("open " + qApp->applicationDirPath() + "/gLAB_SBAS_SUM.pdf");
        // Execute the program
        processUserManual->start(program);
    #endif
}

// Function to show the gLAB DGNSS manual
void gLAB_GUI::on_actionDGNSS_Manual_triggered() {
    #ifndef Q_OS_WIN32
        QProcess *processUserManual = new QProcess(this);
    #endif
    QString program;
    QFile HelpFile(":/data/gLAB_DGNSS_SUM.pdf");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_DGNSS_SUM.pdf"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_DGNSS_SUM.pdf"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_DGNSS_SUM.pdf"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("evince " + qApp->applicationDirPath() + "/gLAB_DGNSS_SUM.pdf");
        // Execute the program
        processUserManual->start(program);
    #elif defined(Q_OS_WIN32)
        QString str = qApp->applicationDirPath().replace("\\","/").append("/gLAB_DGNSS_SUM.pdf");
        QDesktopServices::openUrl(QUrl::fromLocalFile(str));
    #elif defined(Q_OS_MAC)
        program = QString("open " + qApp->applicationDirPath() + "/gLAB_DGNSS_SUM.pdf");
        // Execute the program
        processUserManual->start(program);
    #endif
}

// Function to show the gLAB User adder error error example file
void gLAB_GUI::on_actionUser_Added_Error_File_Manual_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_User_Error_File_Example.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the gLAB Sigma Multipath example file
void gLAB_GUI::on_actionUser_defined_Sigma_Multipath_File_Manual_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_Sigma_Multipath_File_Example.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the gLAB Reference Position example file
void gLAB_GUI::on_actionReference_Position_File_Manual_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_Reference_Position_File_Example.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}


// Function to show the gLAB command line help file
void gLAB_GUI::on_actiongLAB_command_line_help_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_command_line_help.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_help.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_command_line_help.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_command_line_help.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_help.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_help.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_command_line_help.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the gLAB command line messages file
void gLAB_GUI::on_actiongLAB_command_line_messages_description_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_command_line_messages.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_messages.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_command_line_messages.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_command_line_messages.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_messages.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_messages.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_command_line_messages.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the gLAB command line SBAS maps description file
void gLAB_GUI::on_actionGLAB_command_line_SBAS_maps_description_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_command_line_sbas_maps_description.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the graph command line help file
void gLAB_GUI::on_actionGraph_plot_tool_command_line_help_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/graph_command_line_help.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exits
    if (QFile::exists(qApp->applicationDirPath().append("/graph_command_line_help.txt"))) {
        QFile::remove(qApp->applicationDirPath().append("/graph_command_line_help.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/graph_command_line_help.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/graph_command_line_help.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/graph_command_line_help.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/graph_command_line_help.txt");
    #endif

    // Execute the program
    processShow->start(program, arguments);
}

// Function to show the About of gLAB
void gLAB_GUI::on_actionAboutgLAB_triggered() {
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox msgBox;
    msgBox.setWindowTitle("About gLAB");
    msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(QString("<p align='center'><b>gLAB v%1.%2</b></p></br>").arg(version, 3, 'f', 1, '0').arg(revision) +

                   "<span style='font-weight:normal'><p align='center'>gLAB is a complete GNSS analysis tool for both educational and professional purposes. "+
                   "gLAB is given as is for free (please see the license). gLAB allows a full customisation "+
                   "of its options and provides precise point positioning capabilities on the centimetre level.</p></br>"+

                   "<p align='center'>gLAB is divided in three different modules:<br>"+
                   "Data Processing Core (DPC) - For all the processing<br>"+
                   "Graphic User Interface (GUI) - To customise options<br>"+
                   "Data Analysis Tool (DAT) - Graphics</p></br>"+

                   "<p align='center'>Both the processing core and the plotting tool can be executed "+
                   "independently from the GUI</p></br>"+

                   "<p align='center'>The GUI has been built with <a href='https://www.qt.io/'>Qt</a> (v" + QT_VERSION_STR +").</p></br>"+

                   "<p align='center'>Please e-mail any bugs, comments or requests to: "+
                   QString("<b><font color='#0000FF'>%1@%2</font></b></p></br>").arg("glab.gage").arg("upc.edu") +

                   QString("<p align='center'>\u00a9 2009 - %1 gAGE/UPC & ESA</p></br>").arg(local.toString("yyyy")));
    msgBox.exec();
}

// Function to show the how to contact gAGE
void gLAB_GUI::on_actionContact_Us_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Contact Us");
    msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(QString("<span style='font-weight:normal'><p align='left'>") +
                   QString("Please e-mail any bugs, comments or requests to: <b><font color='#0000FF'>%1.%2@%3.%4</font></b>").arg("glab","gage","upc","edu"));
    msgBox.exec();
}

// Function to show the Credits of gLAB
void gLAB_GUI::on_actionCredits_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Credits");
    //msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Jaume Sanz [Supervisor]</br>"

                   "<p align='left'>Written by:</br>"

                   "<p align='left'>Pere Ramos-Bosch [DPC, GUI, DAT]</br>"

                   "<p align='left'>Adria Rovira-Garcia [GUI, DAT]</br>"

                   "<p align='left'>Deimos Ibáñez Segura [DPC, GUI, DAT]</br>"

                   "<p align='left'>Jesús Romero Sánchez [DPC, GUI]</br>"

                   "<p align='left'>Yixie Shao [DPC, DAT]</br>");
    msgBox.exec();
}

// Function to show the License of gLAB
void gLAB_GUI::on_actionLicense_triggered() {
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox msgBox;
    msgBox.setWindowTitle("License");
    msgBox.setTextFormat(Qt::RichText);
    //msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(QString("<span style='font-weight:normal'><p align='left'>Copyright 2009-%1 gAGE/UPC & ESA</br>").arg(local.toString("yyyy")) +

                   "<p align='left'>The <b>gLAB's GUI (Graphical User Interface)</b> is licensed under the Lesser GNU General Public License (LGPL) version 3.\nYou may obtain a copy of the GPL and LGPL Licenses at:</p></br>"

                   "<p align='left'><a href='http://www.gnu.org/licenses/gpl.txt'>GPL License</a><br>"
                   "<a href='http://www.gnu.org/licenses/lgpl.txt'>LGPL License</a></p></br>"

                   "<p align='left'>The <b>gLAB's GUI (Graphical User Interface)</b> is free software: you can redistribute it and/or modify "
                       "it under the terms of the Lesser GNU General Public License as published by "
                       "the Free Software Foundation, either version 3 of the License, or "
                       "(at your option) any later version.</br>"
                       "This program is distributed in the hope that it will be useful, "
                       "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                       "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                       "Lesser GNU General Public License for more details.</br></br></br></p>"

                   "<p align='left'>The <b>gLAB processing core and graphical tool</b> is licensed under the Apache License, Version 2.0 (the \"License\").\nYou may obtain a copy of the License at:</p></br>"

                   "<p align='left'><a href='http://www.apache.org/licenses/LICENSE-2.0'>http://www.apache.org/licenses/LICENSE-2.0</a></p></br>"

                   "<p align='left'>Unless required by applicable law or agreed to in writing, software "
                   "distributed under the License is distributed on an \"AS IS\" BASIS, "
                   "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. "
                   "See the License for the specific language governing permissions and "
                   "limitations under the License.</br></p>");
    msgBox.exec();
}

// Function to visit the teqc website
void gLAB_GUI::on_actionTeqc_triggered() {
    QDesktopServices::openUrl(QUrl("https://www.unavco.org/software/data-processing/teqc/teqc.html"));
}

// Function to visit the Hatanaka website
void gLAB_GUI::on_actionHatanaka_compressor_triggered() {
    QDesktopServices::openUrl(QUrl("http://terras.gsi.go.jp/ja/crx2rnx.html"));
}

// Function to visit the GFZ RINEX version converter
void gLAB_GUI::on_actionGFZ_RINEX_version_converter_triggered() {
   QDesktopServices::openUrl(QUrl("http://semisys.gfz-potsdam.de/semisys/scripts/download/#software"));
}

// Function to show RINEX file extension types
void gLAB_GUI::on_actionRINEX_file_extension_types_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(450, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("RINEX file extension types");
    msgBox.setMinimumWidth(700);
    //NOTE: The 'white-space:pre' is to avoid program from collapsing sequences of white space
    //The <pre> tahg is to make the font monospace (all letter occupy the same width), so text is aligned
    msgBox.setText("<span style='font-weight:normal;white-space:pre'><p align='left'>Content of RINEX files according to its extension ('YY' is the year with two digits):"
                   "<pre>.YYd ⇒ Hatanaka (CRINEX) Compressed Observation File<br>"
                   ".YYo ⇒ RINEX Observation File (versions 2 and 3)<br><br>"
                   ".YYe ⇒ Galileo  RINEX Navigation File (version 2.12, which is not official)<br>"
                   ".YYl ⇒ Galileo  RINEX Navigation File (version 3)<br>"
                   ".YYf ⇒ BeiDou   RINEX Navigation File (version 3)<br>"
                   ".YYg ⇒ Glonass  RINEX Navigation File (versions 2 and 3)<br>"
                   ".YYh ⇒ GEO      RINEX Navigation File (versions 2 and 3)<br>"
                   ".YYn ⇒ GPS      RINEX Navigation File (versions 2 and 3)<br>"
                   ".YYq ⇒ QZSS     RINEX Navigation File (versions 3 and 2.12, the latter is not official)<br>"
                   ".YYp ⇒ Mixed    RINEX Navigation File (All constellations) (version 3)<br>"
                   ".YYx ⇒ GPS/QZSS RINEX Navigation File (LNAV/CNAV messages) (version 4, which is not official)<br>"
                   ".YYm ⇒ Meteorological RINEX file<br>"
                   ".YYi ⇒ Ionosphere map in IONEX format<br>"
                   ".YYs ⇒ teqc quality check output file (from RINEX observation files)<br>"
                   ".YYb ⇒ SBAS messages in RINEX format (version 2)<br>"
                   ".ems ⇒ SBAS messages in EMS format</pre>");

    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}


// Function to see IGS website with Standards
void gLAB_GUI::on_actionIGS_Standards_Website_triggered() {
    QDesktopServices::openUrl(QUrl("https://kb.igs.org/hc/en-us/articles/201096516-IGS-Formats"));
}

// Function to see RINEX and SP3 standard list
void gLAB_GUI::on_actionRINEX_SP3_files_triggered() {
    QDesktopServices::openUrl(QUrl("ftp://igs.org/pub/data/format/"));
}

// Function to see SINEX standard web page explanation
void gLAB_GUI::on_actionSINEX_files_triggered() {
    QDesktopServices::openUrl(QUrl("https://www.iers.org/IERS/EN/Organization/AnalysisCoordinator/SinexFormat/sinex.html"));
}

// Function to see SINEX Bias standard web page explanation
void gLAB_GUI::on_actionSINEX_Bias_files_triggered() {
    QDesktopServices::openUrl(QUrl("https://cddis.nasa.gov/Data_and_Derived_Products/GNSS/gnss_differential_code_bias_product.html"));
}

// Function to see IONEX and troposhere standard
void gLAB_GUI::on_actionIonosphere_IONEX_and_Troposphere_files_triggered() {
    QDesktopServices::openUrl(QUrl("https://cddis.nasa.gov/Data_and_Derived_Products/GNSS/atmospheric_products.html"));
}

// Function to see ANTEX standard
void gLAB_GUI::on_actionANTEX_files_triggered() {
    QDesktopServices::openUrl(QUrl("ftp://igs.org/pub/station/general/antex14.txt"));
}

// Function to visit the GNSS Data Processing book website
void gLAB_GUI::on_actionGNSS_Tutorial_Book_triggered() {
    QDesktopServices::openUrl(QUrl("http://gage.upc.es/gnss_book"));
}

// Function to visit the GNSS Master Course website
void gLAB_GUI::on_actionMaster_triggered() {
    QDesktopServices::openUrl(QUrl("http://gage.upc.es/tutorials"));
}

// Function to get the latest released version
void gLAB_GUI::on_actionCheck_for_updates_triggered() {
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl("http://gage.upc.es/gLAB/version")));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll(); // Source should be stored here
    QString v1 = "<version>";
    QString v2 = "</version>";
    int iv1 = html.indexOf(v1) + 9;
    int iv2 = html.indexOf(v2);
    QString r1 = "<revision>";
    QString r2 = "</revision>";
    int ir1 = html.indexOf(r1) + 10;
    int ir2 = html.indexOf(r2);
    QString versionaux = html.mid(iv1,iv2-iv1);
    QString revisionaux = html.mid(ir1,ir2-ir1);

    double ver = versionaux.toDouble();
    int    rev = revisionaux.toInt();

    QMessageBox messageBox;
    if ( ver == 0 && rev == 0 ) {
        messageBox.critical(0, "Connection problem",
                            "Cannot connect to server.\nPlease, review your Internet connection and try it again.\n");
    } else if ( version> ver ||( version==ver && revision >= rev) ) {
        messageBox.setWindowTitle("Version check");
        messageBox.setText(QString("<p align='left'><br>The current gLAB v%1.%2 is the latest.</br><br></br>").arg(version, 3, 'f', 1, '0').arg(revision));
        messageBox.exec();
    } else if ( version < ver ||( version==ver && revision < rev) ) {
        messageBox.setWindowTitle("Version check");
        messageBox.setTextFormat(Qt::RichText);
        messageBox.setText(QString("<p align='left'><br>There is a new version available: gLAB v%1.%2.</br><br>Please check <a href='http://gage.upc.es/gLAB/'>http://gage.upc.es/gLAB/</a> to obtain it.</br><br></br>").arg(ver, 3, 'f', 1, '0').arg(rev));
        messageBox.exec();
    }
}

// Function to show or hide the gLAB GUI header
void gLAB_GUI::on_actionHeader_triggered() {
    if ( ui->actionHeader->isChecked() == false ) ui->labelHeader->setHidden(true);
    else ui->labelHeader->setHidden(false);
}

// Function to show the RINEX Files
void gLAB_GUI::on_actionRINEXObsVersion_2_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Observation Files Version 2");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX measurement files:<br>"
                   "<a href='ftp://garner.ucsd.edu/rinex/'>ftp://garner.ucsd.edu/rinex/</a><br>"
                   "<a href='ftp://ftp.epncb.oma.be/pub/obs/'>ftp://ftp.epncb.oma.be/pub/obs/</a><br>"
                   "<a href='ftp://www.ngs.noaa.gov/cors/rinex/'>ftp://www.ngs.noaa.gov/cors/rinex/</a><br>"
                   "<a href='ftp://data-out.unavco.org/pub/rinex/obs/'>ftp://data-out.unavco.org/pub/rinex/obs/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='ftp://lox.ucsd.edu/rinex/'>ftp://lox.ucsd.edu/rinex/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/IGS/obs/'>ftp://igs.bkg.bund.de/IGS/obs/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/GREF/obs/'>ftp://igs.bkg.bund.de/GREF/obs/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MISC/obs/'>ftp://igs.bkg.bund.de/MISC/obs/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MGEX/obs/'>ftp://igs.bkg.bund.de/MGEX/obs/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/obs/'>ftp://igs.bkg.bund.de/EUREF/obs/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz):<br>"
                   "<a href='ftp://garner.ucsd.edu/rinex_highrate/'>ftp://garner.ucsd.edu/rinex_highrate/</a><br>"
                   "<a href='ftp://lox.ucsd.edu/rinex_highrate/'>ftp://lox.ucsd.edu/rinex_highrate/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/highrate/'>ftp://gssc.esa.int/gnss/data/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/IGS/highrate/'>ftp://igs.bkg.bund.de/IGS/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/GREF/highrate/'>ftp://igs.bkg.bund.de/GREF/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MISC/highrate/'>ftp://igs.bkg.bund.de/MISC/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MGEX/highrate/'>ftp://igs.bkg.bund.de/MGEX/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/highrate/'>ftp://igs.bkg.bund.de/EUREF/highrate/</a><br>"
                   "<a href='ftp://data-out.unavco.org/pub/highrate/'>ftp://data-out.unavco.org/pub/highrate/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/highrate/'>https://cddis.nasa.gov/archive/gnss/data/highrate/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/highrate/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/highrate/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz) with QZSS (unofficial RINEX 2 version):<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/rinex/'>https://www.enri.go.jp/cnspub/sat/data/rinex/</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the RINEX Files
void gLAB_GUI::on_actionRINEXObsVersion_3_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Observation Files Version 3");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX measurement files:<br>"
                    "<a href='ftp://igs.ensg.ign.fr/pub/igs/data/rinex3/'>ftp://igs.ensg.ign.fr/pub/igs/data/rinex3/</a><br>"
                   "<a href='ftp://data-out.unavco.org/pub/rinex3/obs/'>ftp://data-out.unavco.org/pub/rinex3/obs/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/IGS/obs_v3/'>ftp://igs.bkg.bund.de/IGS/obs_v3/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MISC/obs_v3/'>ftp://igs.bkg.bund.de/MISC/obs_v3/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MGEX/obs_v3/'>ftp://igs.bkg.bund.de/MGEX/obs_v3/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/obs_v3/'>ftp://igs.bkg.bund.de/EUREF/obs_v3/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz):<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/highrate/'>ftp://gssc.esa.int/gnss/data/highrate/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/highrate_v3/'>ftp://igs.bkg.bund.de/EUREF/highrate_v3/</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

void gLAB_GUI::on_actionRINEXNavVersion_2_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Navigation Files Version 2");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>All or Mixed constellation RINEX Navigation files:<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>GPS RINEX Navigation files:<br>"
                   "<a href='ftp://lox.ucsd.edu/rinex/'>ftp://lox.ucsd.edu/rinex/</a></p>"

                   "<p align='left'>GPS and Galileo RINEX Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/</a></p>"

                   "<p align='left'>GPS and Glonass RINEX Navigation files:<br>"
                   "<a href='ftp://igs.bkg.bund.de/IGS/BRDC/'>ftp://igs.bkg.bund.de/IGS/BRDC/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/GREF/BRDC/'>ftp://igs.bkg.bund.de/GREF/BRDC/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/BRDC/'>ftp://igs.bkg.bund.de/EUREF/BRDC/</a></p>"

                   "<p align='left'>GEO Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/H/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/H/</a><br>"
                   "<a href='ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/H/'>ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/H/</a></p>"

                   "<p align='left'>QZSS GEO Navigation files:<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/geonav/'>https://www.enri.go.jp/cnspub/sat/data/geonav/</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

void gLAB_GUI::on_actionRINEXNavVersion_3_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(570, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Navigation Files Version 3");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>All or Mixed constellation RINEX Navigation files:<br>"
                   "<a href='ftp://igs.bkg.bund.de/IGS/BRDC/'>ftp://igs.bkg.bund.de/IGS/BRDC/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/EUREF/BRDC/'>ftp://igs.bkg.bund.de/EUREF/BRDC/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/</a></p>"

                   "<p align='left'>GPS and Galileo RINEX Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/</a></p>"

                   "<p align='left'>Mixed constellation RINEX Navigation files:<br>"
                   "<a href='ftp://igs.bkg.bund.de/MGEX/BRDC/'>ftp://igs.bkg.bund.de/MGEX/BRDC/</a><br>"
                   "<a href='ftp://igs.bkg.bund.de/MGEX/BRDC_v3/'>ftp://igs.bkg.bund.de/MGEX/BRDC_v3/</a><br>"
                   "<a href='ftp://data-out.unavco.org/pub/rinex3/nav/'>ftp://data-out.unavco.org/pub/rinex3/nav/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2013/brdm/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2013/brdm/</a></p>"

                    "<p align='left'>GPS and QZSS Navigation files with LNAV and CNAV messages (unofficial RINEX version):<br>"
                    "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download Precise Files
void gLAB_GUI::on_actionPrecise_Files_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(450, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Precise Files");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Precise orbits and clocks (SP3, CLK and SINEX files):<br>"
                   "<a href='ftp://ftp.nga.mil/pub2/gps/'>ftp://ftp.nga.mil/pub2/gps/</a><br>"
                   "<a href='ftp://garner.ucsd.edu/products/'>ftp://garner.ucsd.edu/products/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/'>https://cddis.nasa.gov/archive/gnss/products/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/glonass/products/'>https://cddis.nasa.gov/archive/glonass/products/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/'>ftp://gssc.esa.int/gnss/products/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/GNSS/products/'>ftp://ftp.gfz-potsdam.de/GNSS/products/</a></p>"

                   "<p align='left'>Mixed files (All constellations):<br>"
                   "<a href='ftp://igs.ign.fr/pub/igs/products/mgex/'>ftp://igs.ign.fr/pub/igs/products/mgex/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/'>ftp://gssc.esa.int/gnss/products/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/mgex/'>https://cddis.nasa.gov/archive/gnss/products/mgex/</a></p>"

                   "<p align='left'>SINEX files:<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/'>https://cddis.nasa.gov/archive/gnss/products/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/'>ftp://gssc.esa.int/gnss/products/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/GNSS/metadata/station/snx/'>ftp://ftp.gfz-potsdam.de/GNSS/metadata/station/snx/</a><br>"
                   "<a href='ftp://ftp.sirgas.org/pub/gps/SIRGAS/'>ftp://ftp.sirgas.org/pub/gps/SIRGAS/</a></p>");


    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download SBAS Files
void gLAB_GUI::on_actionSBAS_Files_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(450, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: SBAS Files");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX-B files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/MSG/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/MSG/</a><br>"
                   "<a href='ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/MSG/'>ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/MSG/</a></p>"

                   "<p align='left'>EMS files:<br>"
                   "<a href='ftp://ems.estec.esa.int/pub/'>ftp://ems.estec.esa.int/pub/</a></p>"

                   "<p align='left'>EMS files with QZSS (unofficial EMS version):<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/ems/'>https://www.enri.go.jp/cnspub/sat/data/ems/</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download Other Files
void gLAB_GUI::on_actionOther_Files_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(550, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Other Files");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>ANTEX files (antenna corrections):<br>"
                   "<a href='ftp://ftp.igs.org/pub/station/general/pcv_archive/'>ftp://ftp.igs.org/pub/station/general/pcv_archive/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/GNSS/metadata/satellite/ANTEX/'>ftp://ftp.gfz-potsdam.de/GNSS/metadata/satellite/ANTEX/</a><br>"
                   "<a href='https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs14.atx'>https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs14.atx</a><br>"
                   "<a href='https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs08.atx'>https://ftp.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs08.atx</a></p>"

                   "<p align='left'>IONEX files (ionosphere):<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/ionex/'>https://cddis.nasa.gov/archive/gnss/products/ionex/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/ionex/'>ftp://gssc.esa.int/gnss/products/ionex/</a></p>"

                   "<p align='left'>ZTD files (troposphere):<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/troposphere/new/'>https://cddis.nasa.gov/archive/gnss/products/troposphere/new/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/troposphere_zpd/'>ftp://gssc.esa.int/gnss/products/troposphere_zpd/</a></p>"

                   "<p align='left'>DCB files (P1-C1 and P1-P2):<br>"
                   "<a href='ftp://ftp.aiub.unibe.ch/CODE/'>ftp://ftp.aiub.unibe.ch/CODE/</a></p>"

                   "<p align='left'>SINEX BIAS DSB files (multiconstellation DCBs for converting measurements):<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/mgex/dcb/'>https://cddis.nasa.gov/archive/gnss/products/mgex/dcb/</a></p>"

                   "<p align='left'>SINEX BIAS OSB files (multiconstellation absolute DCBs):<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/products/mgex/'>https://cddis.nasa.gov/archive/gnss/products/mgex/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/1962/mgex/'>ftp://gssc.esa.int/gnss/products/1962/mgex/</a></p>"

                   "<p align='left'>GPS Receiver types:<br>"
                   "<a href='https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/GPS_Receiver_Types.gz'>https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/GPS_Receiver_Types.gz</a></p>"

                   "<p align='left'>GPS Constellation Status:<br>"
                   "<a href='http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt'>http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Reference Station Files from Spain
void gLAB_GUI::on_actionRefStations_Spain_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(550, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Reference Station Files from Spain");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Cartographic and Geologic Institute of Catalonia (1s / 30s):<br>"
                   "<a href='ftp://geofons.icc.cat/rinex/'>ftp://geofons.icc.cat/rinex/</a></p>"

                   "<p align='left'>Valencian Cartographic Institute (1s / 5s / 30s):<br>"
                   "[Public user and password is in <a href='http://www.icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex'>http://www.icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex</a>]<br>"
                   "<a href='ftp://icvficheros.icv.gva.es/Datos/'>ftp://icvficheros.icv.gva.es/Datos/</a></p>"

                   "<p align='left'>Principality of Asturias Active GNSS Network (1s / 5s / 30s):<br>"
                   "<a href='ftp://rgapa.cartografia.asturias.es/RINEX/'>ftp://rgapa.cartografia.asturias.es/RINEX/</a></p>"

                   "<p align='left'>National Geographic Institute (1s / 5s / 30s):<br>"
                   "<a href='ftp://ftp.geodesia.ign.es/ERGNSS/'>ftp://ftp.geodesia.ign.es/ERGNSS/</a></p>");

    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the reference station Files from coastal services
void gLAB_GUI::on_actionRefStaions_Coastal_Services_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Reference Station Files from coastal services");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>SONEL (30s):<br>"
                   "<a href='ftp://ftp.sonel.org/gps/data/'>ftp://ftp.sonel.org/gps/data/</a></p>");

    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show lists of NTRIP servers
void gLAB_GUI::on_actionLists_of_NTRIP_servers_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Lists of NTRIP station");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'>""<p align='left'>GDC (GNSS Data Center) server list:<br>"
                   "<a href='https://igs.bkg.bund.de/dataandproducts/streams'>https://igs.bkg.bund.de/dataandproducts/streams</a></p>"

                   "<p align='left'>Ntrip Working Group server list:<br>"
                   "<a href='http://www.rtcm-ntrip.org/home'>http://www.rtcm-ntrip.org/home</a></p>"

                   "<p align='left'>EUREF NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_euref-ip'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_euref-ip</a></p>"

                   "<p align='left'>IGS NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_igs-ip.htm'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_igs-ip.htm</a></p>"

                   "<p align='left'>MGEX NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_mgex.htm'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_mgex.htm</a></p>"

                   "<p align='left'>GREF NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_gref-ip.htm'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_gref-ip.htm</a></p>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show links to the UNAVCO's Database RINEX searcher
void gLAB_GUI::on_actionUNAVCO_Database_RINEX_Searcher_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(505, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("UNAVCO's Database RINEX Searcher");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'>""<p align='justify'>UNAVCO has got a public FTP server (<a href='ftp://data-out.unavco.org/pub/'>ftp://data-out.unavco.org/pub/</a>) with RINEX observation and navigation files from many stations and years.<br>"
                   "In order to make fast and precise data search in their FTP server, there is a special web interface available called Data Archive Interface (DAI) for this purpose.<br><br>"
                   "DAI v2 (newest version, but requires Flash):<br>"
                   "<a href='https://www.unavco.org/data/gps-gnss/data-access-methods/dai2/app/dai2.html'>https://www.unavco.org/data/gps-gnss/data-access-methods/dai2/app/dai2.html</a><br><br>"
                   "DAI v1 (older version, HTML based):<br>"
                   "<a href='https://www.unavco.org/data/gps-gnss/data-access-methods/dai1/dai1.html'>https://www.unavco.org/data/gps-gnss/data-access-methods/dai1/dai1.html</a><br>");
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show "Request for additional links" message
void gLAB_GUI::on_actionAdd_your_link_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Request for additional links");
    msgBox.setMinimumWidth(700);
    msgBox.setText(QString("<span style='font-weight:normal'>""<p align='left'>If you know more links for downloading GNSS data and want them to be added to gLAB, please send them to:</p>")+
                   QString("<p align='center'><b><font color='#0000FF'>%1@%2</font></b></p></br>").arg("glab.gage").arg("upc.edu") +
                   QString("<p align='left'>If the link is regarded to a institution, send also the institution name (in english), its country and region.</p>"));
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show "How to reference gLAB" message
void gLAB_GUI::on_actionReference_gLAB_triggered() {
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(630, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("How to reference gLAB");
    msgBox.setMinimumWidth(700);
    msgBox.setText(QString("<span style='font-weight:normal'><p align='left'>If you feel it is appropriate, you may consider paying us back by citing the following gLAB paper:<br><br>")+
                   QString("Ibáñez D., Rovira-García A., Sanz J., Juan JM., Gonzalez-Casado G., Jimenez-Baños D., López-Echazarreta C., Lapin I.") +
                   QString(" The GNSS Laboratory Tool Suite (gLAB) updates: SBAS, DGNSS and Global Monitoring System. ")+
                   QString("9th ESA Workshop on Satellite Navigation Technologies (NAVITEC 2018), Noordwijk, The Netherlands. December 5 - 7, 2018. DOI: <a href='https://doi.org/10.1109/NAVITEC.2018.8642707'>10.1109/NAVITEC.2018.8642707</a>.</p>"));
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

void gLAB_GUI::on_pushButtonAbort_clicked() {
    abort=1;
}

// Function to execute gLAB
void gLAB_GUI::on_pushButtonRunGlab_clicked() {
    // Disable both Run gLAB and Show Output buttons
    // Show Output button will remain disable in case of a gLAB error
    ui->pushButtonRunGlab->setEnabled(false);
    ui->pushButtonShowOutput->setEnabled(false);
    // Declare and initialize
    QProcess *processRun = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QString processReadline;
    QChar PercentageCharac = '%';
    int percentage;

    getInputOptions(errorString, warningString, saveString, runString);
    getPreprocessOptions(errorString, warningString, saveString, runString);
    getModellingOptions(errorString, warningString, saveString, runString);
    getFilterOptions(errorString, warningString, saveString, runString);
    getOutputOptions(errorString, warningString, saveString, runString);


    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing processing again:\n\n" + *errorString);
        ui->pushButtonRunGlab->setEnabled(true);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::warning(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            ui->pushButtonRunGlab->setEnabled(true);
            return;
        }
    }

    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processRun->setReadChannel(QProcess::StandardOutput);

    abort=0;

    // Execute the program
    processRun->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processRun->state() == 0 ) {
        messageBox.critical(0, "Errors found", "gLAB could not be executed.\n");
    } else {

        //Show Progress bar and set it to 0
        ui->progressBar->setValue(0);
        ui->stackedWidgetMainButtons->setCurrentIndex(1);

        // Change the cursor to wait mode
        this->setCursor(Qt::WaitCursor);

        while ( processRun->state() != 0 && abort == 0 ) {
            if ( processRun->canReadLine() ) {
                processReadline = processRun->readLine();
                //Get current percentage from line read
                if (processReadline[62]!=PercentageCharac) {
                    //It is not the 100% line
                    //Currently Qt progress bar cannot display decimals!!!
                    percentage=processReadline.mid(59,2).toInt();
                } else {
                    percentage=100;
                }
                //Update progress bar
                ui->progressBar->setValue(percentage);
            }
            sleep(1);
        }

        //If abort button is clicked, kill the process
        if (abort==1) {
            processRun->kill();
        }

        //Check the exit code
        if (processRun->exitCode()!=0 && abort==0) {
            //Check the last line of file for error messages
            getLastLineOfFile(ui->lineEditOutputDestination->text(),lastLine);
            if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                processReadline="";
                while ( processRun->canReadLine() ) {
                    processReadline = processRun->readLine();
                }
                if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during the processing:\n\n" + processReadline +"\n");
                } else {
                    messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                }
            } else if (*lastLine!="---") {
                messageBox.critical(0, "Errors found", "gLAB had the following error during the processing:\n\n" + *lastLine +"\n");
            } else {
                //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                processReadline="";
                while ( processRun->canReadLine() ) {
                    processReadline = processRun->readLine();
                }
                if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during the processing:\n\n" + processReadline +"\n");
                } else {
                    messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                }
            }
        }

    }
    // Enable the show output button
    ui->pushButtonShowOutput->setEnabled(true);

    //Hide Progress bar
    ui->stackedWidgetMainButtons->setCurrentIndex(0);
    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);

    // Even if errors were found, enable the button
    ui->pushButtonRunGlab->setEnabled(true);
}

// Function to show the output file
void gLAB_GUI::on_pushButtonShowOutput_clicked() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;
    QMessageBox messageBox;

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << ui->lineEditOutputDestination->text();
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << ui->lineEditOutputDestination->text();
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << ui->lineEditOutputDestination->text();
    #endif

    // Execute the program
    if (ui->lineEditOutputDestination->text() == "") {
        messageBox.warning(0, "Error","Output file is empty\n");
    } else if (this->fileExists(ui->lineEditOutputDestination->text())==false) {
        messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputDestination->text() + "' does not exist.\n");
    } else {
        processShow->start(program, arguments);
        sleep(100);
        if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
            if (processShow->exitCode()!=0) {
                messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputDestination->text() + "' could not be opened with default text editor.\n");
            }
        }
    }
}

// Function to generate the plot(s)
void gLAB_GUI::on_pushButtonPlot_clicked() {
    // Disable Plot button
    ui->pushButtonPlot->setEnabled(false);
    // Declare and initialize
    QProcess *processShow = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QFile fileLock;
    QString PlotLockWorkingDir;
    QString PlotLockHome;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QStringList *runString = new QStringList;
    int counter;

    // Delete the ".plot.lock" just if it remained from any crash
    fileLock.remove(".plot.lock");

    // Program is graph.py
    #ifdef Q_OS_LINUX
        program = QString("/graph.py");
    #elif defined(Q_OS_WIN32)
        if(this->fileExists(QString(QDir::toNativeSeparators(qApp->applicationDirPath() + "\\graph\\graph.exe")))==true) {
            program = QString("\\graph\\graph.exe");
        } else {
            program = QString("\\graph.exe");
        }
    #elif defined(Q_OS_MAC)
        program = QString("/graph");
    #endif

    getAnalysisOptions(errorString, warningString, saveString, runString);

    // Output the errors
    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing the plot command again:\n\n" + *errorString);
        // Enable the Plot button
        ui->pushButtonPlot->setEnabled(true);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            // Enable the Plot button
            ui->pushButtonPlot->setEnabled(true);
            return;
        }
    }

    // Delete the ".plot.lock" just if it remained from any crash
    PlotLockWorkingDir=QString(QDir::toNativeSeparators(qApp->applicationDirPath() + "/.plot.lock"));
    PlotLockHome=QDir::homePath();
    fileLock.remove(".plot.lock");
    fileLock.remove(PlotLockWorkingDir);
    fileLock.remove(PlotLockHome);

    //Show Abort button
    abort=0;
    ui->progressBar->setHidden(true);
    ui->stackedWidgetMainButtons->setCurrentIndex(1);

    // Execute the program
    #if defined(Q_OS_MAC)
        processShow->setWorkingDirectory(QDir::toNativeSeparators(qApp->applicationDirPath()));
    #endif
    processShow->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);

    if ( processShow->state() == 0 ) {
        messageBox.critical(0, "Errors found", "graph could not be executed.\n");
    } else {
        this->setCursor(Qt::WaitCursor);
    }
    ui->pushButtonPlot->setEnabled(false);
    sleep(1000);

    // To set a time limit of 60 seconds for the next loop
    counter = 0;
    while ( (this->fileExists(".plot.lock")==true ||this->fileExists(PlotLockWorkingDir)==true||this->fileExists(PlotLockHome)==true )
            && processShow->state() != 0 /*&& counter <= 600*/ && abort==0 ) {
        // Change the cursor to wait mode
        this->sleep(10);
        counter++;
    }
    if(abort==1) {
        processShow->kill();
    }
    // Enable the Plot button
    ui->pushButtonPlot->setEnabled(true);

    //Hide Abort Button
    ui->stackedWidgetMainButtons->setCurrentIndex(0);
    ui->progressBar->setHidden(false);

    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);
}


// Function to show the conversion output folder
void gLAB_GUI::on_pushButtonConvertShowOutput_clicked() {

    QMessageBox messageBox;

    //Open SBAS folder
    if ( ui->groupBoxConverterSBAS->isChecked()==true ) {
        if (ui->lineEdit_outputpath_sbas->text() == "") {
            messageBox.warning(0, "Error","SBAS Output path is empty\n");
        } else {
            if (this->directoryExists( ui->lineEdit_outputpath_sbas->text() ) == false ) {
                messageBox.critical(0, "Error","SBAS Output path '" + ui->lineEdit_outputpath_sbas->text() + "' does not exist.\n");
            } else {
                QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEdit_outputpath_sbas->text()));
            }
        }
    } else if ( ui->groupBoxConverterDgnss->isChecked()==true) {
        if (ui->lineEditConverterDgnssOutputRinex->text() == "") {
            messageBox.warning(0, "Error","DGNSS Output RINEX filename is empty\n");
        } else {
            #ifdef Q_OS_WIN32
                if (this->directoryExists( ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2) ) == false ) {
                    messageBox.critical(0, "Error","DGNSS Output path '" + ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2) + "' does not exist.\n");
                } else {
                    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2)));
                }
            #else
                if (this->directoryExists( ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2) ) == false ) {
                    messageBox.critical(0, "Error","DGNSS Output path '" + ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2) + "' does not exist.\n");
                } else {
                    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2)));
                }
            #endif
        }
    } else {
        messageBox.warning(0, "Error","Select the conversion mode before showing the output files.\n");
    }
}

// Function to execute the converter
void gLAB_GUI::on_pushButtonConvert_clicked() {
    // Disable both Convert and Show Output(s) buttons
    // Show Output(s) button will remain disable in case of a gLAB error
    ui->pushButtonConvert->setEnabled(false);
    ui->pushButtonConvertShowOutput->setEnabled(false);
    // Declare and initialize
    QProcess *processConvert = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QFile fileLock;

    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString *lastLine = new QString;
    QStringList *runString = new QStringList;
    QString processReadline;
    QChar PercentageCharac = '%';
    int percentage;
    int ret;

    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    ret=getConverterOptions(0,errorString, warningString, saveString, runString);

    if (ret==1) return; //For the case the user selects not to overwrite files

    // Output the errors
    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing the file conversion:\n\n" + *errorString);
        ui->pushButtonConvert->setEnabled(true);
        ui->pushButtonConvertShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            ui->pushButtonConvert->setEnabled(true);
            return;
        }
    }

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processConvert->setReadChannel(QProcess::StandardOutput);

    // Execute the program
    processConvert->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processConvert->state() == 0 ) {
        messageBox.critical(0, "Errors found", "gLAB could not be executed.\n");
    } else {
        //Show Abort button
        abort=0;
        ui->progressBar->setValue(0);
        ui->stackedWidgetMainButtons->setCurrentIndex(1);
        ui->pushButtonConvert->setEnabled(false);
        ui->pushButtonConvertShowOutput->setEnabled(false);
        // Change the cursor to wait mode
        this->setCursor(Qt::WaitCursor);
        while ( processConvert->state() != 0 && abort==0 ) {
            if ( processConvert->canReadLine() ) {
                processReadline = processConvert->readLine();
                //Get current percentage from line read
                if (processReadline[25]!=PercentageCharac) {
                    //It is not the 100% line
                    //Currently Qt progress bar cannot display decimals!!!
                    percentage=processReadline.mid(23,2).toInt();
                } else {
                    percentage=100;
                }
                //Update progress bar
                ui->progressBar->setValue(percentage);
            }
            sleep(1);
        }
        if(abort==1) {
            processConvert->kill();
        } else {
            //Check the exit code
            if (processConvert->exitCode()!=0) {
                //Check the last line of file for error messages
                getLastLineOfFile(QDir::toNativeSeparators("./gLAB_conversion.out"),lastLine);
                if ((*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processConvert->canReadLine() ) {
                        processReadline = processConvert->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the file conversion:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                } else if (*lastLine!="---") {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during the file conversion:\n\n" + *lastLine +"\n");
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processConvert->canReadLine() ) {
                        processReadline = processConvert->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the file conversion:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                }
            }
        }
        //Remove output file
        fileLock.remove(QDir::toNativeSeparators("./gLAB_conversion.out"));
    }

    //Hide Abort Button
    ui->stackedWidgetMainButtons->setCurrentIndex(0);

    // Enable both Convert and Show Output(s) buttons
    ui->pushButtonConvert->setEnabled(true);
    ui->pushButtonConvertShowOutput->setEnabled(true);
    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);
}

// Function to show the orbit comparison output file
void gLAB_GUI::on_pushButtonCompareShowOutput_clicked() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;
    QMessageBox messageBox;

    if (ui->lineEditOutputFileCompare->text() == "") {
        messageBox.warning(0, "Error","Output file is empty\n");
    } else {
        if (this->fileExists( ui->lineEditOutputFileCompare->text() ) == false ) {
            messageBox.critical(0, "Error","Output file '" + ui->lineEditOutputFileCompare->text() + "' does not exist.\n");
        } else {
            // Based on the OS open the text editor
            #ifdef Q_OS_LINUX
                program = QString("gedit");
                arguments << ui->lineEditOutputFileCompare->text();
            #elif defined(Q_OS_WIN32)
                program = QString("notepad");
                arguments << ui->lineEditOutputFileCompare->text();
            #elif defined(Q_OS_MAC)
                program = QString("open");
                arguments << "-t" << ui->lineEditOutputFileCompare->text();
            #endif

            // Execute the program
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileCompare->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

// Function to execute the orbit comparison
void gLAB_GUI::on_pushButtonCompare_clicked() {
    // Disable both Convert and Show Output(s) buttons
    // Show Output(s) button will remain disable in case of a gLAB error
    ui->pushButtonCompare->setEnabled(false);
    ui->pushButtonCompareShowOutput->setEnabled(false);
    // Declare and initialize
    QProcess *processCompare = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;


    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    getCompareOrbitOptions(errorString, warningString, saveString, runString);

    // Output the errors
    if (*errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing the orbit comparison:\n\n" + *errorString);
        ui->pushButtonCompare->setEnabled(true);
        ui->pushButtonCompareShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            ui->pushButtonCompare->setEnabled(true);
            return;
        }
    }

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processCompare->setReadChannel(QProcess::StandardOutput);

    // Execute the program
    processCompare->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processCompare->state() == 0 ) {
        messageBox.critical(0, "Errors found", "gLAB core could not be executed.\n");
    } else {
        //Show Abort button
        abort=0;
        ui->pushButtonCompare->setEnabled(false);
        ui->pushButtonCompareShowOutput->setEnabled(false);

        ui->progressBar->setValue(0);
        ui->stackedWidgetMainButtons->setCurrentIndex(1);
        // Change the cursor to wait mode
        this->setCursor(Qt::WaitCursor);

        while ( processCompare->state() != 0 && abort==0 ) {
            if ( processCompare->canReadLine() ) {
                processReadline = processCompare->readLine();
                //Get current percentage from line read
                percentage=processReadline.mid(58,3).toInt();
                ui->progressBar->setValue(percentage);
            }
            sleep(1);
        }
        if(abort==1) {
            processCompare->kill();
        } else {
            //Check the exit code
            if (processCompare->exitCode()!=0) {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileCompare->text(),lastLine);
                if ((*lastLine==""  || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processCompare->canReadLine() ) {
                        processReadline = processCompare->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit comparison:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                } else if (*lastLine!="---") {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit comparison:\n\n" + *lastLine +"\n");
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processCompare->canReadLine() ) {
                        processReadline = processCompare->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit comparison:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                }
            }
        }
    }
    //Hide Abort Button
    ui->stackedWidgetMainButtons->setCurrentIndex(0);

    // Enable both Convert and Show Output(s) buttons
    ui->pushButtonCompare->setEnabled(true);
    ui->pushButtonCompareShowOutput->setEnabled(true);

    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);


}

// Function to show the orbit show output file
void gLAB_GUI::on_pushButtonShowOrbitShowOutput_clicked() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;
    QMessageBox messageBox;

    if (ui->lineEditOutputFileShowOrbit->text() == "") {
        messageBox.warning(0, "Error","Output file is empty\n");
    } else {
        if (this->fileExists( ui->lineEditOutputFileShowOrbit->text() ) == false ) {
            messageBox.critical(0, "Error","Output file '" + ui->lineEditOutputFileShowOrbit->text() + "' does not exist.\n");
        } else {
            // Based on the OS open the text editor
            #ifdef Q_OS_LINUX
                program = QString("gedit");
                arguments << ui->lineEditOutputFileShowOrbit->text();
            #elif defined(Q_OS_WIN32)
                program = QString("notepad");
                arguments << ui->lineEditOutputFileShowOrbit->text();
            #elif defined(Q_OS_MAC)
                program = QString("open");
                arguments << "-t" << ui->lineEditOutputFileShowOrbit->text();
            #endif

            // Execute the program
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileShowOrbit->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

// Function to execute the orbit show
void gLAB_GUI::on_pushButtonShowOrbit_clicked() {
    // Disable both Convert and Show Output(s) buttons
    // Show Output(s) button will remain disable in case of a gLAB error
    ui->pushButtonShowOrbit->setEnabled(false);
    ui->pushButtonShowOrbitShowOutput->setEnabled(false);
    // Declare and initialize
    QProcess *processShowOrbit = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;


    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    getshowOrbitOptions(errorString, warningString, saveString, runString);


    // Output the errors
    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing the orbit computation:\n\n" + *errorString);
        ui->pushButtonShowOrbit->setEnabled(true);
        ui->pushButtonShowOrbitShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            ui->pushButtonShowOrbit->setEnabled(true);
            return;
        }
    }

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processShowOrbit->setReadChannel(QProcess::StandardOutput);

    // Execute the program
    processShowOrbit->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processShowOrbit->state() == 0 ) {
        messageBox.critical(0, "Errors found", "gLAB core could not be executed.\n");
    } else {
        //Show Abort button
        abort=0;
        ui->pushButtonShowOrbit->setEnabled(false);
        ui->pushButtonShowOrbitShowOutput->setEnabled(false);
        ui->progressBar->setValue(0);
        ui->stackedWidgetMainButtons->setCurrentIndex(1);
        // Change the cursor to wait mode
        this->setCursor(Qt::WaitCursor);

        while ( processShowOrbit->state() != 0 && abort==0 ) {
            if ( processShowOrbit->canReadLine() ) {
                processReadline = processShowOrbit->readLine();
                //Get current percentage from line read
                percentage=processReadline.mid(58,3).toInt();
                ui->progressBar->setValue(percentage);
            }
            sleep(1);
        }
        if(abort==1) {
            processShowOrbit->kill();
        } else {
            //Check the exit code
            if (processShowOrbit->exitCode()!=0) {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileShowOrbit->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---" ) {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processShowOrbit->canReadLine() ) {
                        processReadline = processShowOrbit->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit computation:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                } else if (*lastLine!="---") {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit computation:\n\n" + *lastLine +"\n");
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processShowOrbit->canReadLine() ) {
                        processReadline = processShowOrbit->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during the orbit computation:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                }
            }
        }
    }
    //Hide Abort Button
    ui->stackedWidgetMainButtons->setCurrentIndex(0);

    // Enable both Convert and Show Output(s) buttons
    ui->pushButtonShowOrbit->setEnabled(true);
    ui->pushButtonShowOrbitShowOutput->setEnabled(true);
    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);
}


// Function to show the output rinex observation with user added error file
void gLAB_GUI::on_pushButtonAddErrorShowOutput_clicked() {
    QProcess *processAddError = new QProcess(this);
    QString program;
    QStringList arguments;
    QMessageBox messageBox;

    if (ui->lineEditRinexOutputFileAddError->text() == "") {
        messageBox.warning(0, "Error","Output RINEX file is empty\n");
    } else {
        if (this->fileExists( ui->lineEditRinexOutputFileAddError->text() ) == false ) {
            messageBox.critical(0, "Error","Output RINEX file '" + ui->lineEditRinexOutputFileAddError->text() + "' does not exist.\n");
        } else {
            // Based on the OS open the text editor
            #ifdef Q_OS_LINUX
                program = QString("gedit");
                arguments << ui->lineEditRinexOutputFileAddError->text();
            #elif defined(Q_OS_WIN32)
                program = QString("notepad");
                arguments << ui->lineEditRinexOutputFileAddError->text();
            #elif defined(Q_OS_MAC)
                program = QString("open");
                arguments << "-t" << ui->lineEditRinexOutputFileAddError->text();
            #endif

            // Execute the program
            processAddError->start(program, arguments);
            sleep(100);
            if (processAddError->state()==QProcess::NotRunning||processAddError->atEnd()==true) {
                if (processAddError->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditRinexOutputFileAddError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

// Function to execute the add error to Rinex
void gLAB_GUI::on_pushButtonAddError2Rinex_clicked() {
    // Disable both Convert and Show Output(s) buttons
    // Show Output(s) button will remain disable in case of a gLAB error
    ui->pushButtonAddError2Rinex->setEnabled(false);
    ui->pushButtonAddErrorShowOutput->setEnabled(false);
    // Declare and initialize
    QProcess *processAddError = new QProcess(this);
    QString program;
    QMessageBox messageBox;
    QMessageBox::StandardButton reply;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;


    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    getAddErrorOptions(errorString, warningString, saveString, runString);


    // Output the errors
    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before executing the orbit computation:\n\n" + *errorString);
        ui->pushButtonAddError2Rinex->setEnabled(true);
        ui->pushButtonAddErrorShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            ui->pushButtonAddError2Rinex->setEnabled(true);
            return;
        }
    }

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processAddError->setReadChannel(QProcess::StandardOutput);

    // Execute the program
    processAddError->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processAddError->state() == 0 ) {
        messageBox.critical(0, "Errors found", "gLAB core could not be executed.\n");
    } else {
        //Show Abort button
        abort=0;
        ui->pushButtonAddError2Rinex->setEnabled(false);
        ui->pushButtonAddErrorShowOutput->setEnabled(false);
        ui->progressBar->setValue(0);
        ui->stackedWidgetMainButtons->setCurrentIndex(1);
        // Change the cursor to wait mode
        this->setCursor(Qt::WaitCursor);

        while ( processAddError->state() != 0 && abort==0 ) {
            if ( processAddError->canReadLine() ) {
                processReadline = processAddError->readLine();
                //Get current percentage from line read
                percentage=processReadline.mid(58,3).toInt();
                ui->progressBar->setValue(percentage);
            }
            sleep(1);
        }
        if(abort==1) {
            processAddError->kill();
        } else {
            //Check the exit code
            if (processAddError->exitCode()!=0) {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileShowOrbit->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---" ) {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processAddError->canReadLine() ) {
                        processReadline = processAddError->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during adding user error to RINEX:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                } else if (*lastLine!="---") {
                    messageBox.critical(0, "Errors found", "gLAB had the following error during adding user error to RINEX:\n\n" + *lastLine +"\n");
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processAddError->canReadLine() ) {
                        processReadline = processAddError->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.critical(0, "Errors found", "gLAB had the following error during adding user error to RINEX:\n\n" + processReadline +"\n");
                    } else {
                        messageBox.critical(0, "Errors found", "gLAB exited unexpectedly for unknown reason.\n");
                    }
                }
            }
        }
    }
    //Hide Abort Button
    ui->stackedWidgetMainButtons->setCurrentIndex(0);

    // Enable both Convert and Show Output(s) buttons
    ui->pushButtonAddError2Rinex->setEnabled(true);
    ui->pushButtonAddErrorShowOutput->setEnabled(true);
    // Restore the cursor
    this->setCursor(Qt::ArrowCursor);
}

// Function to show the configuration file
void gLAB_GUI::on_actionShow_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;
    QMessageBox messageBox;

    if (this->fileExists(configFileName[ui->stackedWidgetMainWindow->currentIndex()])==false) {
        QMessageBox messageBox;
        messageBox.critical(0, "Errors found",
                            "Configuration file " + configFileName[ui->stackedWidgetMainWindow->currentIndex()] + "does not exist.\n");
        return;
    }

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << configFileName[ui->stackedWidgetMainWindow->currentIndex()];
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << configFileName[ui->stackedWidgetMainWindow->currentIndex()];
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << configFileName[ui->stackedWidgetMainWindow->currentIndex()];
    #endif

    // Execute the program
    processShow->start(program, arguments);
    sleep(100);
    if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
        if (processShow->exitCode()!=0) {
            messageBox.critical(0, "Errors found", "File '" + configFileName[ui->stackedWidgetMainWindow->currentIndex()] + "' could not be opened with default text editor.\n");
        }
    }
}

// Function to show the command line instruction
void gLAB_GUI::on_actionShow_command_line_instruction_triggered() {

    QString program;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString auxstring;
    QString auxstring2;
    QString auxstringCygwin;
    QStringList *runString = new QStringList;
    int label=0;
    int condition=0;


    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("/gLAB_linux");
    #elif defined(Q_OS_WIN32)
        program = QString("\\gLAB.exe");
        QString programCygwin = QString("gLAB_linux");
    #elif defined(Q_OS_MAC)
        program = QString("/gLAB_mac");
    #endif

    //Compute parameters
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        getInputOptions(errorString, warningString, saveString, runString);
        getPreprocessOptions(errorString, warningString, saveString, runString);
        getModellingOptions(errorString, warningString, saveString, runString);
        getFilterOptions(errorString, warningString, saveString, runString);
        getOutputOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        getAnalysisOptions(errorString, warningString, saveString, runString);
        #ifdef Q_OS_WIN32
            if(this->fileExists(QString(QDir::toNativeSeparators(qApp->applicationDirPath() + "\\graph\\graph.exe")))==true) {
                program = QString("\\graph\\graph.exe");
            } else {
                program = QString("\\graph.exe");
            }
            programCygwin = QString("graph.py");
        #elif defined Q_OS_LINUX
            program = QString("/graph.py");
        #elif defined(Q_OS_MAC)
            program = QString("/graph");
        #endif
    } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
        getConverterOptions(1,errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
        getCompareOrbitOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
        getshowOrbitOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
        getAddErrorOptions(errorString, warningString, saveString, runString);
    } else {
        return;
    }

    if ( *errorString != "" ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before generating the command line instruction again:\n\n" + *errorString);
        return;
    }
    //Transform from QStringList to QString
    for (int i = 0; i < runString->size(); ++i) {
        if (ui->stackedWidgetMainWindow->currentIndex()==1) {
            //Analysis page
            if(label==1) {
                auxstring += "\"" + runString->at(i) + "\" ";
                auxstringCygwin += "\"" + runString->at(i) + "\" ";
                label=0;
                continue;
            } else if (condition==1) {
                auxstring2 = runString->at(i);
                    #ifdef Q_OS_WIN32
                        auxstring += "\"" + runString->at(i) + "\" ";
                        auxstring2 = runString->at(i);
                        auxstringCygwin += "'" + auxstring2.replace(QString("'"), QString("\"")) + "' ";
                    #else
                        auxstring += "'" + runString->at(i) + "' ";
                    #endif
                condition=0;
                continue;
            } else if (runString->at(i)=="-t" || runString->at(i)=="--xl" || runString->at(i)=="--yl" || runString->at(i)=="--ft" || runString->at(i)=="--wm" || runString->at(i)=="-f" || runString->at(i)=="-l") {
                label=1;
                auxstring += runString->at(i) + " ";
                auxstringCygwin  += runString->at(i) + " ";
                continue;
            } else if (runString->at(i)=="-c") {
                condition=1;
                auxstring += runString->at(i) + " ";
                auxstringCygwin += runString->at(i) + " ";
                continue;
            } else {
                auxstring += runString->at(i) + " ";
                auxstringCygwin += runString->at(i) + " ";
                continue;
            }

        } else {
            //Check if parameter contains a path and put it between quotes
            auxstring2 = runString->at(i);
            #ifdef Q_OS_WIN32
            if (auxstring2.contains("\\")==true) {
            #else
            if (auxstring2.contains("/")==true) {
            #endif
                auxstring += "\"" + runString->at(i) + "\" ";
                auxstringCygwin += "\"" + runString->at(i) + "\" ";
            } else {
                auxstring += runString->at(i) + " ";
                auxstringCygwin += runString->at(i) + " ";
            }
        }
    }

    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(550, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
     if (ui->stackedWidgetMainWindow->currentIndex()==1) {
            msgBox.setWindowTitle("Equivalent command line execution for graph");
     } else {
        msgBox.setWindowTitle("Equivalent command line execution for gLAB");
     }
    msgBox.setMinimumWidth(1000);
    #ifdef Q_OS_WIN32
        msgBox.setText("<span style='font-weight:normal'><p align='left'> <b>Cygwin command line:</b><br>" + programCygwin + " " + auxstringCygwin + "<br><br><b>Windows command line:</b><br>\"" + QDir::toNativeSeparators(QCoreApplication::applicationDirPath()) + program + "\" " + auxstring + "<br></p>");
    #else
        msgBox.setText("<span style='font-weight:normal'><p align='left'> \"" + QDir::toNativeSeparators(QCoreApplication::applicationDirPath()) + program + "\" " + auxstring + "<br></p>");
    #endif
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}


// Function to sleep the GUI thread during the milliseconds introduced
void gLAB_GUI::sleep(int millisecondsToWait) {
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//Function to set /unset to generate a configuration file with all parameters or not
void gLAB_GUI::on_actionGenerate_minimum_configuration_triggered(bool checked) {
    if (checked==false) {
        WriteAllParameters=1;
    } else {
        WriteAllParameters=0;
    }
}

// Function to save the gLAB configuration file
void gLAB_GUI::on_actionSave_triggered() {
    // Header
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox::StandardButton reply;
    QMessageBox messageBox;
    QString header = "###################################################\n";
    header += "#\n";
    header += QString("#     gLAB - Version: %1.%2\n").arg(version, 3, 'f', 1, '0').arg(revision);
    header += "#     This is a self-generated configuration file.\n";
    if (WriteAllParameters==0) {
        header += "#     It only contains the minimum options to change the defaults.\n";
    }
    header += "#     Created at: " + local.toString("hh:mm") + " on " + local.toString("dd/MM/yyyy") + "\n";
    header += "#\n";
    header += "###################################################\n\n\n";


    // INPUT data and checks
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QStringList *runString = new QStringList;
    //Compute parameters
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        getInputOptions(errorString, warningString, saveString, runString);
        getPreprocessOptions(errorString, warningString, saveString, runString);
        getModellingOptions(errorString, warningString, saveString, runString);
        getFilterOptions(errorString, warningString, saveString, runString);
        getOutputOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        return;
    } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
        getConverterOptions(1,errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
        getCompareOrbitOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
        getshowOrbitOptions(errorString, warningString, saveString, runString);
    } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
        getAddErrorOptions(errorString, warningString, saveString, runString);
    } else {
        return;
    }


    if ( *errorString != "" ) {
        messageBox.critical(0, "Errors found",
                            "gLAB has found the following errors, please correct them before generating the configuration file again:\n\n" + *errorString);
        return;
    }

    if ( *warningString != "" ) {
        reply = QMessageBox::question(this, "Problems found",
                                      QString("%1\nAre you sure you want to continue?\n").arg(*warningString),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            return;
        }
    }

    // Enable the show action
    ui->actionShow->setEnabled(true);

    // Open the dialog to select the filename and path to store the gLAB configuration

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("gLAB Configuration Files (*.cfg);;All Files (*.*)"));
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        return;
    } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_convert.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_compare.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_show.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_adderror.cfg");
        }
    } else {
        return;
    }

    if ( dialog.exec() ) configFileName[ui->stackedWidgetMainWindow->currentIndex()] = dialog.selectedFiles().at(0);
    if ( configFileName.isEmpty() ) return;
    else {
        QFile file(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]==NULL) {
            //User pressed cancel button
        } else if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
            messageBox.critical(0, "Errors found", "gLAB could not create the Configuration File.\n");
            return;
        } else {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << header << *saveString;
            file.close();
        }
    }
}

// Function to load a gLAB configuration file
void gLAB_GUI::on_actionLoad_triggered() {
    // Open dialog to select the gLAB configuration file
    QString line;
    QFileDialog dialog(this);
    QString option;
    QString userInput;
    QString errorString = "";
    QString warningString = "";
    QString userInputSingleSpace;
    QStringList ParametersList;

    QDate date;
    QTime hour;
    QMessageBox messageBox;

    int i;
    int numNav=0,numSP3=0,numOrb=0,numClk=0, numAnt=0, numInputOrbFiles=0, noAntParameter=0, numRefPos=0;
    int numSBAS=0, numDGNSS=0, numRTCM=0, numRTCM2=0, numRTCM3=0, numOutput=0;
    int numSigmaMultipath=0, numUserError=0, numSinex=0, numDCB=0, numRecTypes=0;
    int numSBASiono=0, numKlob=0, numNeq=0, numBDS=0, numIONEX=0, numStfdESA=0, numStfdESALOI=0;
    int numKML=0, numKML0=0, numOutputSP3=0, numObs=0, numOutRefPos=0;
    int numDCBType[6]= {0,0,0,0,0,0}; //0-> P1-C1 DCB 1-> P1-P2 DCB 2-> P2-C2 DCB 3-> Rinex Nav 4-> MGEX DCB 5-> IONEX
    int CodeSingleFreq=0, PhaseDualFreq=0, CodeDualFreq=0, PhaseSingleFreq=0, DualFrequencyUsed=0;
    int year, month,day, doy, hour2, minute, second,sod,GPSWeek,sow;
    int mode=-1; //0 -> SPP 1-> 2->SBAS 3->DGNSS
    int L1Avail=1, L2Avail=1;
    int LICycleSlip=0, MWCycleSlip=0, L1C1CycleSlip=0;
    int SmoothFreq1=0, SmoothFreq2=0, SmoothDualFreq=0;
    int CodeFreq1Used=0, PhaseFreq1Used=0, CodeFreq2Used=0, PhaseFreq2Used=0;
    int DCBfiletype, BackwardFiltering=0, numKMLRanges=0;
    int SmoothNoL1P=0;
    int ValidDate, addDay, leapYear;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonthLeapYear[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int RefFileFirst=-1; //-1->Unknown 0->First '-pre:setrecpos' 1->First input file  2->Only input:ref file
    int RefFileInterpDegree=-1;
    int LetterPos,StartPRN,EndPRN,HyphenPos,HashPos;
    int PRN,ValidSNR,ValidRange;
    double radius, SNR;
    QString RefFilePath;
    QString ParameterName;
    QString GPSLetter="G", GLONASSLetter="R", GalileoLetter="E", BeiDouLetter="C", GEOLetter="S", QZSSLetter="J", IRNSSLetter="I";
    QString Sign;
    QStringList PRNlist;
    enum GNSSystem System;
    const int listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Configuration Files (*.cfg);;All Files (*.*)"));
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        return;
    } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_convert.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_compare.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_show.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_adderror.cfg");
        }
    } else {
        return;
    }
    if ( dialog.exec() ) {
        configFileName[ui->stackedWidgetMainWindow->currentIndex()] = dialog.selectedFiles().at(0);
        if ( !configFileName[ui->stackedWidgetMainWindow->currentIndex()].isEmpty() ) {
            QFile file(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
            if ( !file.open(QIODevice::ReadOnly) ) {
                 QMessageBox messageBox;
                 messageBox.critical(0, "Errors found", "gLAB could not open the Configuration File.\n");
                 return;
             } else {
                // Enable the show action
                ui->actionShow->setEnabled(true);

                if(ui->stackedWidgetMainWindow->currentIndex()==0) {
                    //Code below
                } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
                    converterLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
                    compareOrbitsLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
                    showOrbitsLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
                    AddErrorLoadParameters(&file);
                    file.close();
                    return;
                } else {
                    file.close();
                    return;
                }

                QTextStream InputFile(&file);
                InputFile.setAutoDetectUnicode(true);


                //First loop: Check for errors
                while ( !InputFile.atEnd() ) {
                    line = QString(InputFile.readLine());
                    if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
                    if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
                    line.remove(QRegularExpression("^\\s+"));
                    if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
                    if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
                    HashPos=line.indexOf("#");
                    if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
                    if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
                    option = line.section(" ", 0, 0);
                    option.remove(QRegularExpression("[\\n\\t\\r\"']"));                    
                    userInput = line.section(" ", 1);
                    userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
                    userInput.remove(QRegularExpression("^\\s+"));
                    userInput.remove(QRegularExpression("\\s+$"));
                    userInputSingleSpace = userInput;
                    userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
                    userInputSingleSpace.remove(QRegularExpression("\\s$"));
                    ParametersList.clear();
                    ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

                    if (QString::compare(option, "-help", Qt::CaseInsensitive)==0 || QString::compare(option, "--help", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show the parameter help message and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-messages", Qt::CaseInsensitive)==0 || QString::compare(option, "--messages", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show the fields of each output message and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-examples", Qt::CaseInsensitive)==0 || QString::compare(option, "--examples", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show examples for calling the program and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-config", Qt::CaseInsensitive)==0 || QString::compare(option, "--config", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show info of the configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-usererrorfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--usererrorfile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description and examples of the user-defined error configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-sigmamultipathfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--sigmamultipathfile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description and examples of the user multipath model configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-rtcmv2conversioninfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--rtcmv2conversioninfo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description of output files generated from RTCM v2.X conversion and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-referenceposfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--referenceposfile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description of the reference position file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-sbasplotsinfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--sbasplotsinfo", Qt::CaseInsensitive)==0 ||
                               QString::compare(option, "-sbasmapsinfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--sbasmapsinfo", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description about how to generate SBAS maps and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-onlyconvert", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for changing gLAB mode to SBAS conversion only. It is not valid for positioning mode.\n";                    
                    } else if (QString::compare(option, "-dateconv:calendar", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(6,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:doy", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:gpsweek", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:mjdn", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-coordconv:cartesian", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if (QString::compare(option, "-coordconv:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if ( QString::compare(option, "-coordconv:spherical", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
                        numObs++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Observation", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
                        numNav++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Navigation", &warningString,&errorString,userInput);
                        }
                        if(mode==-1)mode=0;
                    } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
                        numSP3++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
                        numOrb++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3 orbit", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
                        numClk++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Clock", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
                        numAnt++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("ANTEX", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
                        numSBAS++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS", &warningString,&errorString,userInput);
                        }
                        mode=2;
                    } else if ( QString::compare(option, "-input:dgnss", Qt::CaseInsensitive)==0  ) {
                        numDGNSS++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("DGNSS", &warningString,&errorString,userInput);
                        }
                        mode=3;
                    } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0  ) {
                        numRTCM++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM", &warningString,&errorString,userInput);
                        }
                        mode=3;
                    } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
                        numRTCM2++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM2", &warningString,&errorString,userInput);
                        }
                        mode=3;
                    } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
                        numRTCM3++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM3", &warningString,&errorString,userInput);
                        }
                        mode=3;
                    } else if ( QString::compare(option, "-input:snx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SINEX", &warningString,&errorString,userInput);
                        }
                        numSinex++;
                    } else if ( QString::compare(option, "-input:klb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Klobuchar Navigation", &warningString,&errorString,userInput);
                        }
                        numKlob++;
                    } else if ( QString::compare(option, "-input:neq", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("NeQuick Navigation", &warningString,&errorString,userInput);
                        }
                        numNeq++;
                    } else if ( QString::compare(option, "-input:bei", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:bds", Qt::CaseInsensitive)==0) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("BeiDou Navigation", &warningString,&errorString,userInput);
                        }
                        numBDS++;
                    } else if ( QString::compare(option, "-input:inx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("IONEX", &warningString,&errorString,userInput);
                        }
                        numIONEX++;
                    } else if ( QString::compare(option, "-input:sbasiono", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS iono", &warningString,&errorString,userInput);
                        }
                        numSBASiono++;
                    } else if ( QString::compare(option, "-input:dcb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("DCB", &warningString,&errorString,userInput);
                            DCBfiletype=checkDCBFileType(userInput);
                            if (DCBfiletype==-1) {
                                errorString += "Unknown DCB file type '" + userInput + "'.\n";
                            } else {
                                numDCBType[DCBfiletype]++;
                            }
                        }
                        numDCB++;
                    } else if ( QString::compare(option, "-input:rec", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("GPS Receiver Types", &warningString,&errorString,userInput);
                        }
                        numRecTypes++;
                    } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("User error", &warningString,&errorString,userInput);
                        }
                        numUserError++;
                    } else if ( QString::compare(option, "-input:sigmpath", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS Sigma multipath", &warningString,&errorString,userInput);
                        }
                        numSigmaMultipath++;
                    } else if ( QString::compare(option, "-input:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Reference position", &warningString,&errorString,userInput);
                            RefFilePath=userInput;
                        }
                        numRefPos++;
                        if(RefFileFirst==-1) {
                            RefFileFirst=2;
                        }
                    } else if ( QString::compare(option, "-pre:refpos:deg", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            //warning will be issued in the second reading loop
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                                //warning will be issued in the second reading loop
                            } else {
                                RefFileInterpDegree=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                            }
                        }
                    } else if ( QString::compare(option, "-pre:setrecpos", Qt::CaseInsensitive)==0 ) {
                        if(RefFileFirst==-1) {
                            RefFileFirst=0;
                        } else if (RefFileFirst==2) {
                            RefFileFirst=1;
                        }
                    } else if ( QString::compare(option, "-pre:availf", Qt::CaseInsensitive)==0 ) {
                        //Read this option to know which frequencies are available
                        if (ParametersList.count()<1) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length()==1) {
                              //warning will be issued in the second reading loop
                            } else {
                                L1Avail=L2Avail=0;
                                for(i=1;i<userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length();i++) {
                                    if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==1) {
                                        L1Avail=1;
                                    } else if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==2) {
                                        L2Avail=1;
                                    } else {
                                        //warning will be issued in the second reading loop
                                    }
                                }
                                if (L1Avail==0 && L2Avail==0) {
                                    errorString += "Frequencies 1 and 2 cannot be both disabled (in parameter '" + option + "').\n";
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        //To check if LI detector is enabled
                        LICycleSlip=1;
                    } else if ( QString::compare(option, "--pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        //To check if LI detector is enabled
                        LICycleSlip=0;
                    } else if ( QString::compare(option, "-pre:cs:bw", Qt::CaseInsensitive)==0 ) {
                        //To check if MW detector is enabled
                        MWCycleSlip=1;
                    } else if ( QString::compare(option, "--pre:cs:bw", Qt::CaseInsensitive)==0 ) {
                        //To check if MW detector is enabled
                        MWCycleSlip=0;
                    } else if ( QString::compare(option, "-pre:cs:l1c1", Qt::CaseInsensitive)==0 ) {
                        //To check if L1C1 detector is enabled
                        L1C1CycleSlip=1;
                    } else if ( QString::compare(option, "--pre:cs:l1c1", Qt::CaseInsensitive)==0 ) {
                        //To check if L1C1 detector is enabled
                        L1C1CycleSlip=0;
                    } else if ( QString::compare(option, "-pre:smoothMeas", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<2) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>1) {
                            //warning will be issued in the second reading loop
                        } else {
                            if ((QString::compare(ParametersList[1], "L1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[1], "L1", Qt::CaseInsensitive)==0) ) {
                                SmoothFreq1=1;
                            } else if ((QString::compare(ParametersList[1], "L2P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[1], "L2", Qt::CaseInsensitive)==0) ) {
                                SmoothFreq2=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "LC", Qt::CaseInsensitive)==0) {
                                SmoothDualFreq=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "DF", Qt::CaseInsensitive)==0) {
                                SmoothDualFreq=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "G1C", Qt::CaseInsensitive)==0) {
                                SmoothFreq1=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "G1P", Qt::CaseInsensitive)==0) {
                                SmoothFreq1=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "G2P", Qt::CaseInsensitive)==0) {
                                SmoothFreq2=1;
                                SmoothNoL1P=1;
                            } else if (QString::compare(ParametersList[1], "G2C", Qt::CaseInsensitive)==0) {
                                SmoothFreq2=1;
                                SmoothNoL1P=1;
                            } else {
                                //warning will be issued in the second reading loop
                            }
                        }
                    } else if ( QString::compare(option, "-filter:select", Qt::CaseInsensitive)==0 ) {
                        //We read this parameter to know if dual frequency is activated (necessary to set filter weight in the right position
                        if (ParametersList.count()<1) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                           //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            //warning will be issued in the second reading loop
                        } else {
                            for(i=1;i<=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();i++) {
                                //Phase measurements
                                if ((QString::compare(ParametersList[i], "C1C", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "C1", Qt::CaseInsensitive)==0) ) {
                                    if(i==2) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        CodeSingleFreq=1;
                                        CodeFreq1Used=1;
                                    }
                                } else if ((QString::compare(ParametersList[i], "C1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "P1", Qt::CaseInsensitive)==0) ) {
                                    if(i==2) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        CodeSingleFreq=1;
                                        CodeFreq1Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "C2P", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[i], "P2", Qt::CaseInsensitive)==0) {
                                    if(i==2) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        CodeSingleFreq=1;
                                        CodeFreq2Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "PC", Qt::CaseInsensitive)==0) {
                                    if(i==2) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                         CodeDualFreq=1;
                                    }
                                //Phase measurements
                                } else if ((QString::compare(ParametersList[i], "L1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "L1", Qt::CaseInsensitive)==0) ) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq1Used=1;
                                    }
                                } else if ((QString::compare(ParametersList[i], "L2P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "L2", Qt::CaseInsensitive)==0) ) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq2Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "LC", Qt::CaseInsensitive)==0) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseDualFreq=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "G1C", Qt::CaseInsensitive)==0) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq1Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "G1P", Qt::CaseInsensitive)==0) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq1Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "G2P", Qt::CaseInsensitive)==0) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq2Used=1;
                                    }
                                } else if (QString::compare(ParametersList[i], "G2C", Qt::CaseInsensitive)==0) {
                                    if(i==1) {
                                        //warning will be issued in the second reading loop
                                    } else {
                                        PhaseSingleFreq=1;
                                        PhaseFreq2Used=1;
                                    }
                                } else {
                                    //warning will be issued in the second reading loop
                                }
                            }
                            if ( (CodeSingleFreq==1 && PhaseDualFreq==1) || (CodeDualFreq==1 && PhaseSingleFreq==1 ) || (CodeSingleFreq==1 && CodeDualFreq==1) || (PhaseSingleFreq==1 && PhaseDualFreq==1) ) {
                                errorString += "Measurements from single and dual frequency (in parameter '" + option + "' cannot be mixed in the GUI.\n";
                            } else if (CodeDualFreq==1) {
                                DualFrequencyUsed=1;
                            }
                        }
                    } else if ( QString::compare(option, "-filter:backward", Qt::CaseInsensitive)==0 ) {
                        BackwardFiltering=1;
                    } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Output Corrections", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasavailplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS availability plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS continuity risk plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskmarplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS maritime continuity risk plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskdisc", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS discontinuity risk data", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasionoplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS iono availability plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbashdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS HDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbaspdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS PDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasgdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS GDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbascombdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS Combined DOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
                        numOutput++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml", Qt::CaseInsensitive)==0 ) {
                        numKML++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("KML", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml0", Qt::CaseInsensitive)==0 ) {
                        numKML0++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("KML0", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:sp3", Qt::CaseInsensitive)==0 ) {
                        numOutputSP3++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3 output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:refpos", Qt::CaseInsensitive)==0 ) {
                        numOutRefPos++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Reference Position output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:stfdesa", Qt::CaseInsensitive)==0 ) {
                        numStfdESA++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Stanford-ESA output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:stfdesaloi", Qt::CaseInsensitive)==0 ) {
                        numStfdESALOI++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Stanford-ESA all geometries", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        noAntParameter=1;
                    }
                }


                //Check for errors in number of files
                if (numInputOrbFiles>1) {
                    //More than one orbit file given
                    if (numNav>1) {
                        errorString += "More than one navigation file ('-input:nav' option) is provided.\n";
                    }
                    if (numSP3>1) {
                        errorString += "More than one SP3 file ('-input:sp3' option) is provided.\n";
                    }
                    if (numOrb>1) {
                        errorString += "More than one orbit SP3 file ('-input:orb' option) is provided.\n";
                    }
                    if (numNav>0 && numSP3>0 && numOrb>0) {
                        errorString += "Navigation file, SP3 file and orbit SP3 file were provided, but only one type can be given.\n";
                    } else if (numNav>0 && numSP3>0) {
                        errorString += "Navigation file and SP3 file were provided, but only one type can be given.\n";
                    } else if (numNav>0 && numOrb>0) {
                        errorString += "Navigation file and orbit SP3 file were provided, but only one type can be given.\n";
                    } else if (numSP3>0 && numOrb>0) {
                        errorString += "Orbit & clock SP3 file and orbit SP3 file were provided, but only one type can be given.\n";
                    }
                }
                //Check if a orbit SP3 was given but not a CLK file
                if (numOrb>0 && numClk==0) {
                    warningString += "Orbit SP3 file provided, but no clock file given.\n";
                }
                //Check if a CLK file is provided, but no orbit file is given
                if (numOrb==0 && numClk>0) {
                    warningString += "Clock file provided, but no orbit SP3 file given.\n";
                }
                //Check if more than ANTEX was given
                if (numAnt>1) {
                    errorString += "More than one ANTEX file ('-input:ant' option) is provided.\n";
                }
                //Check if ANTEX file provided, but option for no ANTEX provided
                if (numAnt>0 && noAntParameter==1) {
                    warningString += "ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
                }

                //More than one orbit file given
                if (numSBAS>1) {
                    errorString += "More than one SBAS file ('-input:sbas' option) is provided.\n";
                }
                if( (numRTCM + numRTCM2 + numRTCM3 + numDGNSS)>1) {
                     errorString += "More than one type of DGNSS/RTCM type file provided.\n";
                }
                if (numDGNSS>1) {
                     errorString += "More than one RINEX DGNSS file ('-input:dgnss' option) is provided.\n";
                }
                if (numRTCM>1) {
                     errorString += "More than one RTCM (auto detection) file ('-input:rtcm' option) is provided.\n";
                }
                if (numRTCM2>1) {
                     errorString += "More than one RTCM2 file ('-input:rtcm2' option) is provided.\n";
                }
                if (numRTCM3>1) {
                     errorString += "More than one RTCM3 file ('-input:rtcm3' option) is provided.\n";
                }
                if (numSinex>1) {
                     errorString += "More than one SINEX file ('-input:snx' option) is provided.\n";
                }
                if (numKlob>1) {
                     errorString += "More than one Klobuchar iono navigation file ('-input:klb' option) is provided.\n";
                }
                if (numNeq>1) {
                     errorString += "More than one NeQuick iono navigation file ('-input:neq' option) is provided.\n";
                }
                if (numBDS>1) {
                     errorString += "More than one BeiDou iono navigation file ('-input:bds' option) is provided.\n";
                }
                if (numIONEX>1) {
                     errorString += "More than one IONEX file ('-input:inx' option) is provided.\n";
                }
                if ((numKlob+numNeq+numBDS)>1) {
                     errorString += "Iono navigation files can only be entered for one iono model.\n";
                }
                if (numSBASiono>1) {
                     errorString += "More than one SBAS iono file ('-input:sbasiono' option) is provided.\n";
                }
                if (numDCB>2) {
                     errorString += "More than two DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[0]>1) {
                    errorString += "More than two P1-C1 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[1]>1) {
                    errorString += "More than two P1-P2 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[2]>1) {
                    errorString += "More than two P2-C2 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[3]>1) {
                    errorString += "More than two DCB RINEX Navigation files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[4]>1) {
                    errorString += "More than two MGEX DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[5]>1) {
                    errorString += "More than two IONEX DCB files ('-input:dcb' option) are provided.\n";
                }
                if (numRecTypes>1) {
                     errorString += "More than one GPS receiver types file ('-input:rec' option) is provided.\n";
                }
                if (numSigmaMultipath>1) {
                     errorString += "More than one SBAS sigma multipath file ('-input:sigmpath' option) is provided.\n";
                }
                if (numRefPos>1) {
                     errorString += "More than one Reference Position file ('-input:refpos' option) is provided.\n";
                }
                if (numUserError>1) {
                     errorString += "More than one User added error file ('-input:usererror' option) is provided.\n";
                }
                if ( (numSP3>0 || numOrb>0 || numClk>0) && numSBAS>0) {
                    errorString += "Cannot determine positioning mode (PPP or SBAS) due to precise product and SBAS files provided.\n";
                }
                if ( (numSP3>0 || numOrb>0 || numClk>0) && ( numRTCM>0 || numRTCM2>0 || numRTCM3>0 || numDGNSS>0)) {
                    errorString += "Cannot determine positioning mode (PPP or DGNSS) due to precise product and DGNSS files provided.\n";
                }
                if ( numSBAS>0  &&  (numRTCM>0 || numRTCM2>0 || numRTCM3>0 || numDGNSS>0)) {
                    errorString += "Cannot determine positioning mode (SBAS or DGNSS) due to SBAS and DGNSS files provided.\n";
                }
                if ( numNav>0 && (numSP3>0 || numOrb>0 || numClk>0) ) {
                    errorString += "Cannot determine positioning mode (SPP or PPP) due to navigation file and precise product files provided.\n";
                }

                //Check observation file
                if (numObs>1) {
                    errorString += "More than one observation file ('-input:obs' option) is provided.\n";
                }
                //Check number of output files
                if (numOutput>1) {
                    errorString += "More than one output file ('-output:file' option) is provided.\n";
                }
                if (numKML>1) {
                    errorString += "More than one output KML file ('-output:kml' option) is provided.\n";
                }
                if (numKML0>1) {
                    errorString += "More than one output KML0 file ('-output:kml0' option) is provided.\n";
                }
                if (numOutputSP3>1) {
                    errorString += "More than one output SP3 file ('-output:sp3' option) is provided.\n";
                }
                if (numOutRefPos>1) {
                    errorString += "More than one output Reference position file ('-output:refpos' option) is provided.\n";
                }
                if (numStfdESA>1) {
                    errorString += "More than one output Stanford-ESA file ('-output:stfdesa' option) is provided.\n";
                }
                if (numStfdESALOI>1) {
                    errorString += "More than one output Stanford-ESA (all geometries) file ('-output:stfdesaloi' option) is provided.\n";
                }

                //Check mode is set to any value
                if(mode==-1) {
                    errorString += "No navigation, SP3, SBAS or DGNSS file provided. Cannot determine positioning mode (SPP, PPP, SBAS, DGNSS).\n";
                }

                //Check that we are not using  measurements from disabled frequencies
                if (L1Avail==0 && L1C1CycleSlip==1) {
                    errorString += "L1C1 Cycle-slip detector enabled, but frequency 1 is disabled. This is an invalid configuration.\n";
                }
                if ( (L1Avail==0 || L2Avail==0) && MWCycleSlip==1) {
                    errorString += "Melbourne-Wübbena Cycle-slip detector enabled, but frequency 1 or 2 are disabled. This is an invalid configuration.\n";
                }
                if ( (L1Avail==0 || L2Avail==0) && LICycleSlip==1) {
                    errorString += "LI Cycle-slip detector enabled, but frequency 1 or 2 is disabled. This is an invalid configuration.\n";
                }
                if ( L1Avail==0 && SmoothFreq1==1) {
                    errorString += "Smoothing with measurement of frequency 1, but frequency 1 is disabled. This is an invalid configuration.\n";
                }
                if ( L2Avail==0 && SmoothFreq2==1) {
                    errorString += "Smoothing with measurement of frequency 2, but frequency 2 is disabled. This is an invalid configuration.\n";
                }
                if ( (L1Avail==0 || L2Avail==0)  && SmoothDualFreq==1) {
                    errorString += "Smoothing with measurement of dual frequency, but frequency 1 or 2 are are disabled. This is an invalid configuration.\n";
                }
                if (L1Avail==0 && (CodeFreq1Used==1 || PhaseFreq1Used==1)) {
                    errorString += "Selected measurement of frequency 1 for the filter, but frequency 1 is disabled. This is an invalid configuration.\n";
                }
                if (L2Avail==0 && (CodeFreq2Used==2 || PhaseFreq2Used==1)) {
                    errorString += "Selected measurement of frequency 2 for the filter, but frequency 2 is disabled. This is an invalid configuration.\n";
                }
                if(DualFrequencyUsed==1 && L2Avail==0) {
                    errorString += "Dual frequency measurement selected, but frequency 2 is disabled. This is an invalid configuration.\n";
                }
                if (mode>=2 && L1Avail==0) {
                    errorString += "Frequency 1 cannot be disabled in SBAS or DGNSS modes.\n";
                }
                if (mode>=2  && DualFrequencyUsed==1) {
                     errorString += "Dual frequency measurements cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                if (mode>=2 && (PhaseFreq1Used==1 ||  PhaseFreq2Used==1)) {
                    errorString += "Carrier phase measurements  cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                if (mode>=2 && (CodeFreq2Used==1 || PhaseFreq2Used==1)  )  {
                    errorString += "Frequency 2 code or carrier phase measurements cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                if (mode==2 && SmoothNoL1P==1) {
                    errorString += "Only L1P smoothing can be selected in SBAS mode.\n";
                }


                //Check that backward filtering is not enabled in SBAS or DGNSS modes
                if (mode>=2 && BackwardFiltering==1) {
                    errorString += "Backward filtering cannot be enabled in SBAS or DGNSS modes.\n";
                }

                //If errors ocurred, show them and return
                if (!errorString.isEmpty()) {
                    messageBox.critical(0, "Errors found",
                                        "gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
                    return;
                }



                //Second loop: Load parameters
                file.seek(0); //Go back to beginning of file
                setInitialPositioningValues(); //Set initial default values in Positioning page
                //Set defaults for selected mode
                if (mode==0) {
                    on_actionSPP_triggered();
                } else if (mode==1) {
                    on_actionPPP_triggered();
                } else if (mode==2) {
                    on_actionSBAS_triggered();
                } else { //mode==3
                    on_actionDGNSS_triggered();
                }

                while ( !InputFile.atEnd() ) {
                    line = QString(InputFile.readLine());
                    if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
                    if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
                    line.remove(QRegularExpression("^\\s+"));
                    if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the line only contained spaces and it has been emptied
                    if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
                    HashPos=line.indexOf("#");
                    if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
                    if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
                    option = line.section(" ", 0, 0);
                    option.remove(QRegularExpression("[\\n\\t\\r\"']"));
                    userInput = line.section(" ", 1);
                    userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
                    userInput.remove(QRegularExpression("^\\s+"));
                    userInput.remove(QRegularExpression("\\s+$"));
                    userInputSingleSpace = userInput;
                    userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
                    userInputSingleSpace.remove(QRegularExpression("\\s$"));
                    ParametersList.clear();
                    ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);


                    ////////////////////
                    // INPUT SECTION
                    // Rover
                    if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRinexObs->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_radioButtonOrbitBrdc_clicked();
                            ui->lineEditRinexNav->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxAntex_clicked(true);
                            ui->lineEditAntex->setText(userInput);
                        }
                    // Rover -> Orbit and Clock Source
                    } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise1file_clicked();
                            ui->lineEditPrecise1File->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise2files_clicked();
                            ui->lineEditPrecise2Files->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise2files_clicked();
                            ui->lineEditPreciseClk->setText(userInput);
                        }
                    // A priori Receiver Position From -> SINEX
                    } else if ( QString::compare(option, "-input:snx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_radioButtonSinex_clicked();
                            ui->lineEditSinex->setText(userInput);
                        }
                    // SBAS
                    } else if ( QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->radioButtonIonoSourceSbas->setChecked(true);
                            ui->lineEditSbas->setText(userInput);
                        }
                    // Reference Station (DGNSS)
                    } else if ( QString::compare(option, "-input:dgnss", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRinex->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(0);
                            ui->comboBoxRefStation->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcmAuto->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(1);
                            ui->comboBoxRefStation->setCurrentIndex(1);
                        }
                    } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcm2->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(2);
                            ui->comboBoxRefStation->setCurrentIndex(2);
                        }
                    } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcm3->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(3);
                            ui->comboBoxRefStation->setCurrentIndex(3);
                        }
                    } else if ( QString::compare(option, "-input:rtcm:initdate", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.length()<8 || userInputSingleSpace.length()>8) {
                                warningString += "RTCM input date format is incorrect. The correct format is YYYYMMDD. It was skipped.\n";
                            } else {
                                year = userInputSingleSpace.mid(0, 4).toInt();
                                month = userInputSingleSpace.mid(4, 2).toInt();
                                day = userInputSingleSpace.mid(6, 2).toInt();
                                if (year<1980) {
                                    warningString += "RTCM input date is below 1980. It was skipped.\n";
                                } else if (!(QDate::isValid(year, month, day))) {
                                    warningString += "RTCM input date is not valid. It was skipped.\n";
                                } else {
                                    date = QDate(year, month, day);
                                    ui->dateEdit1->setDate(date);
                                    ui->dateEdit2->setDate(date);
                                    ui->dateEdit3->setDate(date);
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-input:rtcm:inithour", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>24) {
                               warningString += "RTCM input hour is not valid. It was skipped.\n";
                            } else {
                                hour = QTime(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), 0);
                                ui->timeEdit1->setTime(hour);
                                ui->timeEdit2->setTime(hour);
                            }
                        }
                    } else if ( QString::compare(option, "-input:dcb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            //Check what type of DCB file is
                            DCBfiletype=checkDCBFileType(userInput);
                            //We have previously checked that we have a valid DCB file
                            if (DCBfiletype==0) {
                                //P1-C1 DCB
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1C1correction_clicked(true);
                                ui->lineEditDcbFile->setText(userInput);
                            } else if (DCBfiletype==1) {
                                //P1-P2 DCB
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(2);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(1);
                                ui->lineEditDcbSourceDcb->setText(userInput);
                            } else if (DCBfiletype==2) {
                                //P2-C2 DCB
                                warningString += "File '" + userInput + "' is a P2-C2 DCB file, which is not used in gLAB. File skipped.\n";
                            } else if (DCBfiletype==3) {
                                //RINEX Navigation
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(1);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(0);
                                ui->lineEditDcbSourceRinexNav->setText(userInput);
                            } else if (DCBfiletype==4) {
                                //MGEX DCB
                                warningString += "File '" + userInput + "' is a MGEX DCB file, which is not used in gLAB. File skipped.\n";
                            } else if (DCBfiletype==5) {
                                //IONEX file
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(4);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(3);
                                ui->lineEditDcbSourceIonex->setText(userInput);
                            }
                        }
                    } else if ( QString::compare(option, "-input:rec", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            ui->lineEditGPSRecType->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:klb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option, "-input:neq", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(1);
                        }
                    } else if ( QString::compare(option, "-input:bei", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:bds", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(3);
                        }
                    } else if ( QString::compare(option, "-input:inx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceIonex_clicked();
                            ui->lineEditIonoSourceIonex->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:sbasiono", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceSbas_clicked();
                            ui->lineEditSbas->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxUserAddedError_clicked(true);
                            ui->lineEditUserAddedError->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:sigmpath", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(true);
                            ui->lineEditSigmaMultipath->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if (RefFileFirst==2) {
                                //No '-pre:setrecpos' parameter set. Therefore the default mode will be calculateRef
                                this->on_radioButtonCalculate_clicked();
                                this->on_radioButtonCalculateEarthCentre_clicked();
                                this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                                if (RefFileInterpDegree!=-1) {
                                    ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-input:con", Qt::CaseInsensitive)==0 ) {
                        //As this parameter is not used, we do not check if file has a correct path
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-input:cfg", Qt::CaseInsensitive)==0 ) {
                        //As this parameter is not used, we do not check if file has a correct path
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        }


                    ////////////////////
                    // PREPROCESS SECTION

                    } else if ( QString::compare(option, "-pre:setrecpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRinex_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "SINEX", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonSinex_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculate", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateEarthCentre_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRINEX", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateRinex_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSER", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSER' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[2]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[3]).replace(",","").toDouble()==0.) {
                                    warningString += "Parameter '" + option + " calculateUSER' cannot have a initial position of (0,0,0). It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyCartesian_clicked();
                                    ui->lineEditCalculateSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERGeod", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERGeod' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyGeodetic_clicked();
                                    ui->lineEditCalculateSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRef", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateEarthCentre_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRINEXRef", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateRinex_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERRef", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERRef' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[2]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[3]).replace(",","").toDouble()==0.) {
                                    warningString += "Parameter '" + option + " calculateUSERRef' cannot have a initial position of (0,0,0). It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyCartesian_clicked();
                                    ui->lineEditCalculateSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERGeodRef", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERGeodRef' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyGeodetic_clicked();
                                    ui->lineEditCalculateSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSbaseline", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmBaseline_clicked();
                        } else if (QString::compare(ParametersList[0], "RTCMUserbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserbaseline", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "RTCMUserCarbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarbaseline", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMUserbaseline", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserbaseline";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarbaseline", Qt::CaseInsensitive)==0 ) {
                                 ParameterName="RTCMUserCarbaseline";
                            } else if (QString::compare(ParametersList[0], "DGNSSUserCarbaseline", Qt::CaseInsensitive)==0 ) {
                                 ParameterName="DGNSSUserCarbaseline";
                            } else {
                                ParameterName="DGNSSUserbaseline";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserBaseline_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodbaseline", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodbaseline", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodbaseline";
                            } else {
                                ParameterName="DGNSSUserGeodbaseline";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserBaseline_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRinexRover", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmRinexRover_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserRinexRover", Qt::CaseInsensitive)==0 ||
                                   QString::compare(ParametersList[0], "RTCMUserCarRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarRinexRover", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMUserRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserRinexRover";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarRinexRover", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="RTCMUserCarRinexRover";
                            } else  if (QString::compare(ParametersList[0], "DGNSSUserCarRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSUserCarRinexRover";
                            } else {
                                ParameterName="DGNSSUserRinexRover";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserRinexRover_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodRinexRover", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodRinexRover";
                            } else {
                                ParameterName="DGNSSUserGeodRinexRover";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserRinexRover_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSER", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSER", Qt::CaseInsensitive)==0 ||
                                 QString::compare(ParametersList[0], "RTCMRoverUSERCar", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERCar", Qt::CaseInsensitive)==0  ) {
                            if (QString::compare(ParametersList[0], "RTCMRoverUSER", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRoverUSER";
                            } else if (QString::compare(ParametersList[0], "RTCMRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="RTCMRoverUSERCar";
                            } else if (QString::compare(ParametersList[0], "DGNSSRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="DGNSSRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRoverUSER";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmSpecify_clicked();
                                    this->on_radioButtonRtcmUserDefined_clicked();
                                    this->on_radioButtonRtcmRecCartesian_clicked();
                                    ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSERGeod", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRoverUSERGeod";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmSpecify_clicked();
                                    this->on_radioButtonRtcmUserDefined_clicked();
                                    this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                    ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSERRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERRef", Qt::CaseInsensitive)==0 ) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmSpecify_clicked();
                            this->on_radioButtonRtcmReferenceFile_clicked();
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserRoverRef", Qt::CaseInsensitive)==0 ||
                                  QString::compare(ParametersList[0], "RTCMUserCarRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserRoverRef";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserCarRoverRef";
                            } else if (QString::compare(ParametersList[0], "DGNSSUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSUserCarRoverRef";
                            } else {
                                ParameterName="DGNSSUserRoverRef";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserSpecify_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    this->on_radioButtonRtcmReferenceFile_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodRoverRef", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodRoverRef";
                            } else {
                                ParameterName="DGNSSUserGeodRoverRef";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserSpecify_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    this->on_radioButtonRtcmReferenceFile_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefRoverUSER", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefRoverUSER", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "RTCMRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERCar", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefRoverUSER", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefRoverUSER";
                            } else if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefCarRoverUSERCar";
                            } else if (QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSRefCarRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRefRoverUSER";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(7,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    radius=sqrt(pow(QString("%1").arg(ParametersList[4]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[5]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[6]).replace(",","").toDouble(),2));
                                    if(radius<MIN_EARTH_RADIUS-1000.) {
                                        warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecCartesian_clicked();
                                        this->on_radioButtonRtcmRefCartesian_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefGeodRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRefGeodRoverUSERGeod";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(7,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    if (QString("%1").arg(ParametersList[4]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[4]).replace(",","").toDouble()>180) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover longitude range of [-180..180] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[5]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[5]).replace(",","").toDouble()>90) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover latitude range of [-90..90] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[6]).replace(",","").toDouble()<-10000) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover height value greater than -10 kilometres. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                        this->on_radioButtonRtcmRefGeodetic_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERGeod", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERGeod", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefCarRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRefCarRoverUSERGeod";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(7,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    if (QString("%1").arg(ParametersList[4]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[4]).replace(",","").toDouble()>180) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover longitude range of [-180..180] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[5]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[5]).replace(",","").toDouble()>90) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover latitude range of [-90..90] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[6]).replace(",","").toDouble()<-10000) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover height value greater than -10 kilometres. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                        this->on_radioButtonRtcmRefCartesian_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERCar", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefGeodRoverUSERCar", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefGeodRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRefGeodRoverUSERCar";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(7,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    radius=sqrt(pow(QString("%1").arg(ParametersList[4]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[5]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[6]).replace(",","").toDouble(),2));
                                    if(radius<MIN_EARTH_RADIUS-1000.) {
                                        warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecCartesian_clicked();
                                        this->on_radioButtonRtcmRefGeodetic_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "SetRef", Qt::CaseInsensitive)==0 ) {
                            //Specify Reference file
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonSpecify_clicked();
                            this->on_radioButtonSpecifyReferenceFile_clicked();
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileSpecify->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileSpecify->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "Set", Qt::CaseInsensitive)==0 ) {
                            //Specify User defined Cartesian
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + "' Set has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " Set' cannot have a reference position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserCartesian_clicked();
                                    ui->lineEditSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "SetGeod", Qt::CaseInsensitive)==0 ) {
                            //Specify User defined Geodetic
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " SetGeod' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " SetGeod' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " SetGeod' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " SetGeod' must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserGeodetic_clicked();
                                    ui->lineEditSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else {
                            //Specify User defined Cartesian
                            if (ParametersList.count()<3) {
                                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(3,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[0]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + "' cannot have a reference position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserCartesian_clicked();
                                    ui->lineEditSpecifyX->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                                    ui->lineEditSpecifyY->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyZ->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        }
                    } else if ( QString::compare(option, "-pre:refpos:deg", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                                warningString += "Parameter '" + option + "' has an invalid interpolation degree. It was skipped.\n";
                            }
                            //Value is saved in the first reading loop and applied with '-input:refpos' or '-pre:setrecpos' parameters
                        }
                    } else if ( QString::compare(option, "-pre:starttime", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            ValidDate=1;
                            addDay=0;
                            leapYear=0;
                            extraParametersToWarningStr(2,&warningString,option,ParametersList);
                            if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                                //Time has ":" symbol.
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Time is in YYYY/MM/DD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                         if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                             warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                             ValidDate=0;
                                         } else {
                                             year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                             month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                             day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                                         }
                                    }
                                } else {
                                    //Time is in YYYYMMDD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                            ValidDate=0;
                                        } else {
                                            year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                            month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                            day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                                        }
                                    }
                                }
                                if (ValidDate==1) {
                                    //Check date values and time length
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(month<1||month>12) {
                                        warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                                        warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                        warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                if (ValidDate==1) {
                                    //Read time in HH:MM:SS format and check values
                                    hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                                    minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                                    second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                                    if(hour2<0||hour2>24) {
                                        warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(minute<0||minute>60) {
                                        warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(second<0||second>60) {
                                        warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                 if (ValidDate==1) {
                                     if(second==60) {
                                         second-=60;
                                         minute++;
                                     }
                                     if(minute==60) {
                                         minute-=60;
                                         hour2++;
                                     }
                                     if(hour2==24) {
                                         hour2-=24;
                                         addDay=1;
                                     }
                                     date=QDate(year,month,day);
                                     if(addDay==1) {
                                        date=date.addDays(qint64(1));
                                     }
                                     hour=QTime(hour2,minute,second);
                                     ui->dateTimeEditStartTime->setDate(date);
                                     ui->dateTimeEditStartTime->setTime(hour);
                                     this->on_checkBoxStartTime_clicked(true);
                                 }
                            } else {
                                //Time can be in YYYY/DoY or GPSWeek
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Date is in YYYY/DoY SoD format
                                    year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                    doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                                    sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                        warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sod<0||sod>86400) {
                                        warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sod==86400) {
                                            sod-=86400;
                                            doy++;
                                        }
                                        if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                            doy=1;
                                            year++;
                                        }
                                        doy2date(year,doy,&date);
                                        SoD2time(sod,&hour);
                                        ui->dateTimeEditStartTime->setDate(date);
                                        ui->dateTimeEditStartTime->setTime(hour);
                                        this->on_checkBoxStartTime_clicked(true);
                                    }
                                } else {
                                    //Date is in GPSWeek SoW format
                                    GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                                    sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(GPSWeek<1) {
                                        warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sow<0||sow>604800) {
                                        warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sow==604800) {
                                            sow-=604800;
                                            GPSWeek++;
                                        }
                                        GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                                        ui->dateTimeEditStartTime->setDate(date);
                                        ui->dateTimeEditStartTime->setTime(hour);
                                        this->on_checkBoxStartTime_clicked(true);
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:endtime", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            ValidDate=1;
                            addDay=0;
                            leapYear=0;
                            extraParametersToWarningStr(2,&warningString,option,ParametersList);
                            if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                                //Time has ":" symbol.
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Time is in YYYY/MM/DD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                         if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                             warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                             ValidDate=0;
                                         } else {
                                             year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                             month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                             day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                                         }
                                    }
                                } else {
                                    //Time is in YYYYMMDD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                            ValidDate=0;
                                        } else {
                                            year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                            month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                            day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                                        }
                                    }
                                }
                                if (ValidDate==1) {
                                    //Check date values and time length
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(month<1||month>12) {
                                        warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                                        warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                        warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                if (ValidDate==1) {
                                    //Read time in HH:MM:SS format and check values
                                    hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                                    minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                                    second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                                    if(hour2<0||hour2>24) {
                                        warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(minute<0||minute>60) {
                                        warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(second<0||second>60) {
                                        warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                 if (ValidDate==1) {
                                     if(second==60) {
                                         second-=60;
                                         minute++;
                                     }
                                     if(minute==60) {
                                         minute-=60;
                                         hour2++;
                                     }
                                     if(hour2==24) {
                                         hour2-=24;
                                         addDay=1;
                                     }
                                     date=QDate(year,month,day);
                                     if(addDay==1) {
                                        date=date.addDays(qint64(1));
                                     }
                                     hour=QTime(hour2,minute,second);
                                     ui->dateTimeEditEndTime->setDate(date);
                                     ui->dateTimeEditEndTime->setTime(hour);
                                     this->on_checkBoxEndTime_clicked(true);
                                 }
                            } else {
                                //Time can be in YYYY/DoY or GPSWeek
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Date is in YYYY/DoY SoD format
                                    year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                    doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                                    sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                        warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sod<0||sod>86400) {
                                        warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sod==86400) {
                                            sod-=86400;
                                            doy++;
                                        }
                                        if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                            doy=1;
                                            year++;
                                        }
                                        doy2date(year,doy,&date);
                                        SoD2time(sod,&hour);
                                        ui->dateTimeEditEndTime->setDate(date);
                                        ui->dateTimeEditEndTime->setTime(hour);
                                        this->on_checkBoxEndTime_clicked(true);
                                    }
                                } else {
                                    //Date is in GPSWeek SoW format
                                    GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                                    sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(GPSWeek<1) {
                                        warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sow<0||sow>604800) {
                                        warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sow==604800) {
                                            sow-=604800;
                                            GPSWeek++;
                                        }
                                        GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                                        ui->dateTimeEditEndTime->setDate(date);
                                        ui->dateTimeEditEndTime->setTime(hour);
                                        this->on_checkBoxEndTime_clicked(true);
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:usererrorafter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxAuxFiles_clicked(true);
                        this->on_groupBoxUserAddedError_clicked(true);
                        ui->checkBoxUserAddedErrorAfterPrepocessing->setChecked(true);
                    } else if ( QString::compare(option, "--pre:usererrorafter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUserAddedErrorAfterPrepocessing->setChecked(false);
                    } else if ( QString::compare(option, "-pre:elevation", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90.) {
                            warningString += "Parameter '" + option + "' has to be smaller or equal than 90. It was skipped.\n";
                        } else {
                           ui->lineEditElevMask->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:eclipse", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardEclipse->setChecked(true);
                    } else if ( QString::compare(option, "--pre:eclipse", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardEclipse->setChecked(false);
                    } else if ( QString::compare(option, "-pre:dec", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>0. && userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4 ) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>86400.) {
                            warningString += "Parameter '" + option + "' has to be smaller or equal than 86400. It was skipped.\n";
                        } else {
                           this->on_checkBoxDataDecimator_clicked(true);
                           ui->lineEditDataDecimator->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:prealign", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrealignPhase->setChecked(true);
                    } else if ( QString::compare(option, "--pre:prealign", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrealignPhase->setChecked(false);
                    } else if ( QString::compare(option, "-pre:checkcodejumps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverCodeJumps->setChecked(true);
                    } else if ( QString::compare(option, "--pre:checkcodejumps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverCodeJumps->setChecked(false);
                    //} else if ( QString::compare(option, "-pre:flexibleC1P1", Qt::CaseInsensitive)==0 ) {  //It is also commented in gLAB
                    //} else if ( QString::compare(option, "--pre:flexibleC1P1", Qt::CaseInsensitive)==0 ) { //It is also commented in gLAB
                    } else if ( QString::compare(option, "-pre:cs:datagap", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>0. && userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
                        } else {
                            ui->lineEditDataGap->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:lli", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLLI->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:lli", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLLI->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:ncon", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNcon_clicked(true);
                    } else if ( QString::compare(option, "--pre:cs:ncon", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNcon_clicked(false);
                    } else if ( QString::compare(option, "-pre:cs:ncon:min", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxNcon_clicked(true);
                            ui->lineEditNcon->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:li:min", Qt::CaseInsensitive)==0 ) { //Deprecated parameter
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:li:maxjump", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditLImaxJumpThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:max", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditLImaxThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:t0", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditLItimeConstant->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:samples", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditLInSamples->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    /*} else if ( QString::compare(option, "-pre:cs:lc", Qt::CaseInsensitive)==0 ) { //LC parameters. To be added in a future update
                    } else if ( QString::compare(option, "--pre:cs:lc", Qt::CaseInsensitive)==0 ) {
                    } else if ( QString::compare(option, "-pre:cs:lc:maxjump", Qt::CaseInsensitive)==0 ) {
                    } else if ( QString::compare(option, "-pre:cs:lc:max", Qt::CaseInsensitive)==0 ) {
                    } else if ( QString::compare(option, "-pre:cs:lc:t0", Qt::CaseInsensitive)==0 ) {
                    } else if ( QString::compare(option, "-pre:cs:lc:samples", Qt::CaseInsensitive)==0 ) {*/
                    } else if ( QString::compare(option, "-pre:cs:bw", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:bw", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:bw:min", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:bw:max", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:bw:siginit", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditIntialStdDevBW->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:bw:sigmin", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMWminStd->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:bw:timewindow", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMWwindow->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:bw:kfactor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMWkFactor->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:bw:slope", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:bw:samples", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMWnSample->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:l1c1", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxL1C1->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:l1c1", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxL1C1->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:l1c1:unconcheck", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxL1C1ConsistencyCheck_clicked(true);
                    } else if ( QString::compare(option, "--pre:cs:l1c1:unconcheck", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxL1C1ConsistencyCheck_clicked(false);
                    } else if ( QString::compare(option, "-pre:cs:l1c1:unconcheck:th", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxL1C1ConsistencyCheck_clicked(true);
                            ui->lineEditL1C1ConsCheckValue->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:l1c1:kfactor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditL1C1kFactor->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:l1c1:slope", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:l1c1:window", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:l1c1:max", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:l1c1:timewindow", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditL1C1window->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:l1c1:init", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditL1C1iniStd->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:l1c1:samples", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditL1C1nSample->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:setrectype", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            //Unknown receiver.
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            //Cross correlated receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            //No P1 receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(2);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==3) {
                            //Nominal receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(3);
                        } else if (QString::compare(ParametersList[0], "gpsrt", Qt::CaseInsensitive)==0) {
                            //Use the same as the GPS receiver type file
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeFile_clicked();
                        } else {
                            warningString += "Parameter '" + option + "' does not admit value '" + userInputSingleSpace.section(" ", 0,0) +"'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-pre:sat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            LetterPos=0;
                            Sign=RedColor;
                            if (userInputSingleSpace.section(" ", 0,0).at(0)=='+') {
                                LetterPos=1;
                                Sign=GreenColor;
                            } else if (userInputSingleSpace.section(" ", 0,0).at(0)=='-' ) {
                                LetterPos=1;
                                Sign=RedColor;
                            }
                            System=this->ConsString2ConsEnum(userInputSingleSpace.section(" ", 0,0).at(LetterPos));
                            if (userInputSingleSpace.section(" ", 0,0).at(LetterPos)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(LetterPos)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(LetterPos)==BeiDouLetter
                                       ||userInputSingleSpace.section(" ", 0,0).at(LetterPos)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(LetterPos)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(LetterPos)==IRNSSLetter ) {
                                warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                            } else if (userInputSingleSpace.section(" ", 0,0).at(LetterPos)==GPSLetter) {
                                HyphenPos=userInputSingleSpace.section(" ", 0,0).indexOf("-",LetterPos+1);
                                if (HyphenPos!=-1) {
                                    StartPRN=userInputSingleSpace.section(" ", 0,0).mid(LetterPos+1, HyphenPos-1-LetterPos).toInt();
                                    EndPRN=userInputSingleSpace.section(" ", 0,0).mid(HyphenPos+1).toInt();
                                    if (StartPRN<0 || StartPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";
                                    } else if (EndPRN<=0 || EndPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' only admits PRN numbers from 1 to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";
                                    } else {
                                        if (StartPRN==0) {
                                            StartPRN=1;
                                            EndPRN=listMaxSatGNSS[System];
                                        }
                                        for(i=StartPRN;i<=EndPRN;i++) {
                                            callSatellitePushButtonFunction(System,i,Sign);
                                        }
                                    }
                                } else {
                                    StartPRN=userInputSingleSpace.section(" ", 0,0).mid(LetterPos+1).toInt();
                                    if (StartPRN<0 || StartPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";
                                    } else {
                                        if (StartPRN==0) {
                                            StartPRN=1;
                                            EndPRN=listMaxSatGNSS[System];
                                        } else {
                                            EndPRN=StartPRN;
                                        }
                                        for(i=StartPRN;i<=EndPRN;i++) {
                                            callSatellitePushButtonFunction(System,i,Sign);
                                        }
                                    }
                                }
                            } else {
                                warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-pre:GEOexclude", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            PRNlist=userInputSingleSpace.section(" ", 0,0).split(",");
                            for(i=0;i<PRNlist.size();i++) {
                                PRN=QString("%1").arg(PRNlist.at(i)).section(".",0,0).toInt();
                                if (PRN<120 || PRN>210) {
                                    if (PRNlist.size()==1) {
                                        warningString += "Parameter '" + option + "' has to be equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                                    } else {
                                        warningString += "PRN in position " + QString("%1").arg(i+1) + " for parameter '" + option + "' has to be equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                                    }
                                } else {
                                    if (ui->checkBoxGEOexclusion->isChecked()==false) {
                                        //GEO exclusion disabled. Put GEO excluded in first position
                                        this->on_checkBoxGEOexclusion_clicked(true);
                                        this->on_comboBoxGEOexclusion_currentIndexChanged(0);
                                        ui->lineEditGEOexclusion1->setText(QString("%1").arg(PRN));
                                    } else {
                                        //GEO exclusion enabled
                                        if ( (ui->lineEditGEOexclusion1->text()!="" && QString::compare(ui->lineEditGEOexclusion1->text(),QString("%1").arg(PRN))==0) ||
                                             (ui->lineEditGEOexclusion2->text()!="" && QString::compare(ui->lineEditGEOexclusion2->text(),QString("%1").arg(PRN))==0) ||
                                             (ui->lineEditGEOexclusion3->text()!="" && QString::compare(ui->lineEditGEOexclusion3->text(),QString("%1").arg(PRN))==0) ) {
                                            //PRN already saved. Don't do nothing
                                        } else if (ui->lineEditGEOexclusion1->text()=="") {
                                            //First GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(0);
                                            ui->lineEditGEOexclusion1->setText(QString("%1").arg(PRN));
                                        } else  if (ui->lineEditGEOexclusion2->text()=="") {
                                            //Second GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(1);
                                            ui->lineEditGEOexclusion2->setText(QString("%1").arg(PRN));
                                        } else  if (ui->lineEditGEOexclusion3->text()=="") {
                                            //Third GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(2);
                                            ui->lineEditGEOexclusion3->setText(QString("%1").arg(PRN));
                                        } else {
                                            //Maximum of three SBAS GEO excluded with the GUI. Skip them
                                            warningString += "A maximum of 3 SBAS GEO can be excluded in the GUI with parameter '-pre:GEOexclude' (but there is no limit through command line).\n";
                                        }
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:GEOsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if ( ( userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 && userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<120) ||userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>210 ) {
                            warningString += "Parameter '" + option + "' has to be with values 0, 1, 2 or equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            //Use mixed data from all GEO
                            this->on_comboBoxGEOselection_currentIndexChanged(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            //Select first GEO read in SBAS file
                            this->on_comboBoxGEOselection_currentIndexChanged(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            //Select GEO with maximum elevation
                            this->on_comboBoxGEOselection_currentIndexChanged(2);
                        } else {
                            //Use GEO with the given PRN
                            this->on_comboBoxGEOselection_currentIndexChanged(3);
                            ui->lineEditGEOselection->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:SmoothMin", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditSmoothMinSbas->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:dgnss:smoothMin", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditSmoothMinDgnss->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:SNR", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardSNRThreshold_clicked(true);
                    } else if ( QString::compare(option, "--pre:SNR", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardSNRThreshold_clicked(false);
                    } else if ( QString::compare(option, "-pre:SNRsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            ValidSNR=0;
                            System=this->ConsString2ConsEnum(userInputSingleSpace.section(" ", 0,0).at(0));
                            if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                                warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                            } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                                HyphenPos=userInputSingleSpace.section(" ", 0,0).indexOf("-",1);
                                if (HyphenPos!=-1) {
                                    StartPRN=userInputSingleSpace.section(" ", 0,0).mid(1, HyphenPos-1).toInt();
                                    EndPRN=userInputSingleSpace.section(" ", 0,0).mid(HyphenPos+1).toInt();
                                    if (StartPRN<0 || StartPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";                                    
                                    } else if (EndPRN<StartPRN || EndPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' PRN range must end in a number equal or greater than the starting satellite or up to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";
                                    } else if (StartPRN!=0) {
                                        warningString += "Parameter '" + option + "' in the GUI can only be used with PRN 0 (all satellites). It was skipped.\n";
                                    } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<=0) {
                                        warningString += "SNR ratio in parameter '" + option + "' must be greater than 0.\n";
                                    } else {
                                        SNR=userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble();
                                        ValidSNR=1;
                                    }
                                } else {
                                    StartPRN=userInputSingleSpace.section(" ", 0,0).mid(1).toInt();
                                    EndPRN=StartPRN;
                                    if (StartPRN<0 || StartPRN>listMaxSatGNSS[System]) {
                                        warningString += "Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[System]) + ". It was skipped.\n";
                                    } else if (StartPRN!=0) {
                                        warningString += "Parameter '" + option + "' in the GUI can only be used with PRN 0 (all satellites). It was skipped.\n";
                                    } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<=0) {
                                        warningString += "SNR ratio in parameter '" + option + "' must be greater than 0.\n";
                                    } else {
                                        SNR=userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble();
                                        ValidSNR=1;
                                    }
                                }
                                if (ValidSNR==1) {
                                    this->on_checkBoxDiscardSNRThreshold_clicked(true);
                                    if ( SNR==12) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(0);
                                    } else if (SNR==18) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(1);
                                    } else if (SNR==24) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(2);
                                    } else if (SNR==30) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(3);
                                    } else if (SNR==33) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(4);
                                    } else if (SNR==36) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(5);
                                    } else if (SNR==42) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(6);
                                    } else if (SNR==48) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(7);
                                    } else if (SNR==54) {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(8);
                                    } else {
                                        this->on_comboBoxSNRThresholds_currentIndexChanged(9);
                                        ui->lineEditUserDefinedSNR->setText(userInputSingleSpace.section(" ", 1,1).replace(",",""));
                                    }
                                }
                            } else {
                                warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-pre:availf", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length()==1) {
                              warningString += "Parameter '" + option + "' needs a constellation and a frequency number, but only a constellation was given. It was skipped.\n";
                            } else {
                                L1Avail=L2Avail=0;
                                for(i=1;i<userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length();i++) {
                                    if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==1) {
                                        L1Avail=1;
                                    } else if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==2) {
                                        L2Avail=1;
                                    } else {
                                        warningString += "Frequency '" + userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i) + "' (in parameter '" + option + "') is not available in the GUI.\n";
                                    }
                                }
                                if (L1Avail==0) {
                                    //Disable all cycle-slip detectors
                                    ui->checkBoxL1C1->setChecked(false);
                                    ui->checkBoxMW->setChecked(false);
                                    ui->checkBoxLI->setChecked(false);
                                    //Set single frequency positioning
                                    this->on_radioButtonSingleFreq_clicked();
                                    //Set filter measurements to C2P and L2P if they have frequency 1 measurements
                                    if (ui->comboBoxMeasConfSingleFqPseudorange->currentIndex()<2) {
                                        ui->comboBoxMeasConfSingleFqPseudorange->setCurrentIndex(2);
                                    }
                                    if (ui->comboBoxMeasConfSingleFqPhase->currentIndex()==0 || ui->comboBoxMeasConfSingleFqPhase->currentIndex()==2 || ui->comboBoxMeasConfSingleFqPhase->currentIndex()==3 ) {
                                        ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(1);
                                    }
                                    //Change smoothing to L2P if is using frequency 1 measurement
                                    if (ui->comboBoxSmoothWithSPP->currentIndex()==0 || (ui->comboBoxSmoothWithSPP->currentIndex()>=2 && ui->comboBoxSmoothWithSPP->currentIndex()<6) ) {
                                        ui->comboBoxSmoothWithSPP->setCurrentIndex(1);
                                    }
                                } else if (L2Avail==0) {
                                    //Disable dual frequency cycle-slip detectors
                                    ui->checkBoxMW->setChecked(false);
                                    ui->checkBoxLI->setChecked(false);
                                    //Set single frequency positioning
                                    this->on_radioButtonSingleFreq_clicked();
                                    //Set filter measurements to C1C and L1P if they have frequency 2 measurements
                                    if (ui->comboBoxMeasConfSingleFqPseudorange->currentIndex()==2) {
                                        ui->comboBoxMeasConfSingleFqPseudorange->setCurrentIndex(0);
                                    }
                                    if (ui->comboBoxMeasConfSingleFqPhase->currentIndex()==1 || ui->comboBoxMeasConfSingleFqPhase->currentIndex()>3 ) {
                                        ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(0);
                                    }
                                    //Change smoothing to L1P if is using frequency 2 measurement
                                    if (ui->comboBoxSmoothWithSPP->currentIndex()==1 || ui->comboBoxSmoothWithSPP->currentIndex()==2 || ui->comboBoxSmoothWithSPP->currentIndex()==3 || ui->comboBoxSmoothWithSPP->currentIndex()>5 ) {
                                        ui->comboBoxSmoothWithSPP->setCurrentIndex(0);
                                    }
                                }
                            }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:smooth", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                                ui->lineEditSmoothing->setText("0");
                                this->on_checkBoxSmoothing_clicked(false);
                            } else {
                                if(ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true) {
                                    this->on_checkBoxSmoothing_clicked(true);
                                    ui->lineEditSmoothing->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                                    //Put back option of Pseudorange and carrier phase (when smoothing is enabled it is unchecked)
                                    this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
                                } else {
                                    this->on_checkBoxSmoothing_clicked(true);
                                    ui->lineEditSmoothing->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:smoothMeas", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' first value has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4) {
                            warningString += "Parameter '" + option + "' first value cannot be greater than 4. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>1) {
                            warningString += "Parameter '" + option + "' first value cannot be greater than 1 in the GUI. It was skipped.\n";
                        } else {
                            if ((QString::compare(ParametersList[1], "L1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[1], "L1", Qt::CaseInsensitive)==0) ) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(0);
                                }
                            } else if ((QString::compare(ParametersList[1], "L2P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[1], "L2", Qt::CaseInsensitive)==0) ) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(1);
                                }
                            } else if (QString::compare(ParametersList[1], "LC", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(2);
                                    ui->comboBoxSmoothWithPPP->setCurrentIndex(0);
                                }
                            } else if (QString::compare(ParametersList[1], "DF", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(3);
                                    ui->comboBoxSmoothWithPPP->setCurrentIndex(1);
                                }
                            } else if (QString::compare(ParametersList[1], "G1C", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(4);
                                }
                            } else if (QString::compare(ParametersList[1], "G1P", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(5);
                                }
                            } else if (QString::compare(ParametersList[1], "G2P", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(6);
                                }
                            } else if (QString::compare(ParametersList[1], "G2C", Qt::CaseInsensitive)==0) {
                                if(mode!=2) {
                                    ui->comboBoxSmoothWithSPP->setCurrentIndex(7);
                                }
                            } else {
                                warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' has an invalid measurement for smoothing. It was skipped.\n";
                            }
                            if (mode==2 && (QString::compare(ParametersList[1], "L1P", Qt::CaseInsensitive)!=0) && (QString::compare(ParametersList[1], "L1", Qt::CaseInsensitive)!=0) ) {
                                warningString += "Parameter '" + option + "' has no effect in SBAS mode.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-pre:dgnss:excludeSmoothingConvergenceUser", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(true);
                    } else if ( QString::compare(option, "--pre:dgnss:excludeSmoothingConvergenceUser", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(false);
                    } else if ( QString::compare(option, "-pre:dgnss:excludeSmoothingConvergenceRef", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(true);
                    } else if ( QString::compare(option, "--pre:dgnss:excludeSmoothingConvergenceRef", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(false);


                    ////////////////////
                    // MODEL SECTION

                    } else if ( QString::compare(option, "-model:iono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(false);
                        } else if (QString::compare(ParametersList[0], "Klobuchar", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "NeQuick", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(1);
                        } else if (QString::compare(ParametersList[0], "BeiDou", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(2);
                        } else if (QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(3);
                        } else if (QString::compare(ParametersList[0], "SBAS", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(4);
                        } else if (userInputSingleSpace.section(" ", 0,0)=="FPPP") {
                            warningString += "'F-PPP' ionosphere model in parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--model:iono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxIonoCorrection_clicked(false);
                    } else if ( QString::compare(option, "-model:ionoRMS", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        //Only used in the core for F-PPP, but the option is not present in the help.
                        //Leave it here to avoid error message
                    } else if ( QString::compare(option, "-model:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:tropo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxTropoCorrection_clicked(true);
                    } else if ( QString::compare(option, "--model:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:tropo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxTropoCorrection_clicked(false);
                    } else if ( QString::compare(option, "-model:trop:nominal", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "Simple", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxTropoCorrection_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "UNB3", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxTropoCorrection_currentIndexChanged(1);
                        } else if (QString::compare(ParametersList[0], "TropoGal", Qt::CaseInsensitive)==0) {
                            warningString += "'TropoGal' troposphere model in parameter '" + option + "' is not available. It was skipped.\n";
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:trop:mapping", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "Simple", Qt::CaseInsensitive)==0) {
                            ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
                        } else if (QString::compare(ParametersList[0], "Niell", Qt::CaseInsensitive)==0) {
                            ui->comboBoxTropoCorrectionMapping->setCurrentIndex(1);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatClockOffset->setChecked(true);
                    } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatClockOffset->setChecked(false);
                    } else if ( QString::compare(option, "-model:relclock", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticClock->setChecked(true);
                    } else if ( QString::compare(option, "--model:relclock", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticClock->setChecked(false);
                    } else if ( QString::compare(option, "-model:satmovinflight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatMovement->setChecked(true);
                    } else if ( QString::compare(option, "--model:satmovinflight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatMovement->setChecked(false);
                    } else if ( QString::compare(option, "-model:earthrotinflight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEarthRotation->setChecked(true);
                    } else if ( QString::compare(option, "--model:earthrotinflight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEarthRotation->setChecked(false);
                    } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSatMassCentre_clicked(true);
                    } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSatMassCentre_clicked(false);
                    } else if ( QString::compare(option, "-model:satphasevar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(true);
                    } else if ( QString::compare(option, "--model:satphasevar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(false);
                    } else if ( QString::compare(option, "-model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaPhase_clicked(false);
                        } else if (QString::compare(ParametersList[0], "ANTEX", Qt::CaseInsensitive)==0) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaPhase_clicked(true);
                            this->on_radioButtonAPCread_clicked();
                        } else {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(4,&warningString,option,ParametersList);
                                if (ParametersList[0].replace(",","").section(".",0,0).toInt()<=0 && ParametersList[0].replace(",","").section(".",0,0).toInt()>9 ) {
                                    warningString += "Frequency number for parameter '" + option + "' has to be between 1 and 9. It was skipped.\n";
                                } else if (ParametersList[0].replace(",","").section(".",0,0).toInt()!=1 && ParametersList[0].replace(",","").section(".",0,0).toInt()!=2 ) {
                                    warningString += "The current GUI only accepts frquencies 1 and 2 in parameter '" + option + "'. It was skipped.\n";
                                } else if (ParametersList[0].replace(",","").section(".",0,0).toInt()==1) {
                                    this->on_checkBoxAntennaPhase_clicked(true);
                                    this->on_radioButtonAPCspecifyF1_clicked();
                                    ui->lineEditAPCf1north->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAPCf1east->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAPCf1up->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                } else if (ParametersList[0].replace(",","").section(".",0,0).toInt()==2) {
                                    this->on_checkBoxAntennaPhase_clicked(true);
                                    this->on_radioButtonAPCspecifyF2_clicked();
                                    ui->lineEditAPCf2north->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAPCf2east->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAPCf2up->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "--model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxAntennaPhase_clicked(false);
                    } else if ( QString::compare(option, "-model:recphasevar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(true);
                    } else if ( QString::compare(option, "--model:recphasevar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(false);
                    } else if ( QString::compare(option, "-model:strictradome", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:radomestrict", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStrictRadome->setChecked(true);
                    } else if ( QString::compare(option, "--model:strictradome", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:radomestrict", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStrictRadome->setChecked(false);
                    } else if ( QString::compare(option, "-model:arp", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaReference_clicked(false);
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            extraParametersToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaReference_clicked(true);
                            this->on_radioButtonARPread_clicked();
                        } else {
                            if (ParametersList.count()<3) {
                                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                            } else {
                                extraParametersToWarningStr(3,&warningString,option,ParametersList);
                                this->on_checkBoxAntennaReference_clicked(true);
                                this->on_radioButtonARPspecify_clicked();
                                ui->lineEditARPnorth->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                                ui->lineEditARPeast->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                ui->lineEditARPup->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                            }
                        }
                    } else if ( QString::compare(option, "--model:arp", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxAntennaReference_clicked(false);
                    } else if ( QString::compare(option, "-model:dcb:p1c1", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1C1correction_clicked(false);
                        } else if (QString::compare(ParametersList[0], "flexible", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1C1correction_clicked(true);
                            this->on_comboBoxP1C1correction_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "strict", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1C1correction_clicked(true);
                            this->on_comboBoxP1C1correction_currentIndexChanged(1);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--model:dcb:p1c1", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxP1C1correction_clicked(false);
                    } else if ( QString::compare(option, "-model:dcb:p1p2", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1P2correction_clicked(false);
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1P2correction_clicked(true);
                            this->on_comboBoxP1P2correction_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "DCB", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1P2correction_clicked(true);
                            this->on_comboBoxP1P2correction_currentIndexChanged(1);
                        } else if (QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxP1P2correction_clicked(true);
                            this->on_comboBoxP1P2correction_currentIndexChanged(2);
                        } else if (QString::compare(ParametersList[0], "FPPP", Qt::CaseInsensitive)==0) {
                            warningString += "'F-PPP' DCB source in parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--model:dcb:p1p2", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxP1P2correction_clicked(false);
                    } else if ( QString::compare(option, "-model:windup", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxWindUp->setChecked(true);
                    } else if ( QString::compare(option, "--model:windup", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxWindUp->setChecked(false);
                    } else if ( QString::compare(option, "-model:solidtides", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxTides->setChecked(true);
                    } else if ( QString::compare(option, "--model:solidtides", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxTides->setChecked(false);
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                    } else if ( QString::compare(option, "-model:relpath", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticPath->setChecked(true);
                    } else if ( QString::compare(option, "--model:relpath", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticPath->setChecked(false);
                    } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitInterpolationDegree->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockInterpolationDegree->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitConsecutiveGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditOrbitConsecutiveGaps->setText("0");
                    } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockConsecutiveGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
                         extraParametersToWarningStr(0,&warningString,option,ParametersList);
                         ui->lineEditClockConsecutiveGaps->setText("0");
                    } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitMaxGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditOrbitMaxGaps->setText("0");
                    } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockMaxGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditClockMaxGaps->setText("0");
                    } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxConcatenedPreciseFiles_clicked(true);
                        ui->radioButtonOrbitCurrentDay->setChecked(true);
                    } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOrbitNextDay->setChecked(true);
                    } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonClockCurrentDay->setChecked(true);
                    } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonClockNextDay->setChecked(true);
                    } else if ( QString::compare(option, "-model:satellitehealth", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:sathealth", Qt::CaseInsensitive)==0  ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardUnhealthy->setChecked(true);
                    } else if ( QString::compare(option, "--model:satellitehealth", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:sathealth", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardUnhealthy->setChecked(false);
                    } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxCheckBroadcastTransmissionTime->setChecked(true);
                    } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
                    } else if ( QString::compare(option, "-model:maxurabrdc", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                             warningString += "Value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--model:maxurabrdc", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-model:sbasmaritime", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_comboBoxSBASApplication_currentIndexChanged(1);
                    } else if ( QString::compare(option, "-model:alarmmsgtype2", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxParseAlarm->setChecked(true);
                    } else if ( QString::compare(option, "--model:alarmmsgtype2", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxParseAlarm->setChecked(false);
                    } else if ( QString::compare(option, "-model:ignoretype0", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxIgnoreAllAlarm->setChecked(true);
                    } else if ( QString::compare(option, "--model:ignoretype0", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIgnoreAllAlarm->setChecked(false);
                    } else if ( QString::compare(option, "-model:SBASmode", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "PA", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxSbasNavigationMode_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "NPA", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxSbasNavigationMode_currentIndexChanged(1);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:maintainGEO", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(true);
                    } else if ( QString::compare(option, "--model:maintainGEO", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(false);
                    } else if ( QString::compare(option, "-model:GEOswitch", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxGEOswitching_clicked(true);
                    } else if ( QString::compare(option, "--model:GEOswitch", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxGEOswitching_clicked(false);
                    } else if ( QString::compare(option, "-model:selectbestgeo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSelectBestGEO_clicked(true);
                    } else if ( QString::compare(option, "--model:selectbestgeo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSelectBestGEO_clicked(false);
                    } else if ( QString::compare(option, "-model:SBASmodeswitch", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNavigationModeSwitching_clicked(true);
                    } else if ( QString::compare(option, "--model:SBASmodeswitch", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNavigationModeSwitching_clicked(false);
                    } else if ( QString::compare(option, "-model:GEOfallback", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxReturnToInitialGEO->setChecked(true);
                    } else if ( QString::compare(option, "--model:GEOfallback", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReturnToInitialGEO->setChecked(false);
                    } else if ( QString::compare(option, "-model:GEOacqtime", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:GEOadqtime", Qt::CaseInsensitive)==0  ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            ui->lineEditGEOadquisitionTime->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:switchtime", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            ui->lineEditSwitchinCooltime->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 0,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutNPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 1,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmout", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 2,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFCPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFCNPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFC", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                            ui->lineEditFastCorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRCPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRCNPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRC", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                            ui->lineEditRRCcorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:mixedGEO", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowMixedGEOdata->setChecked(true);
                    } else if ( QString::compare(option, "--model:mixedGEO", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowMixedGEOdata->setChecked(false);
                    } else if ( QString::compare(option, "-model:initcoordNPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxAllowKlobucharIono->setChecked(true);
                    } else if ( QString::compare(option, "--model:initcoordNPA", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowKlobucharIono->setChecked(false);
                    } else if ( QString::compare(option, "-model:udreithreshold", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<1||userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>13) {
                             warningString += "Value for parameter '" + option + "' have to be between 1 and 13. It was skipped.\n";
                        } else {
                            this->on_checkBoxDiscardUDREIThreshold_clicked(true);
                            ui->comboBoxUDREIThresholds->setCurrentIndex(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()-1);
                        }
                    } else if ( QString::compare(option, "--model:udreithreshold", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardUDREIThreshold_clicked(false);
                    } else if ( QString::compare(option, "-model:sigfltnomt10offset", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0) {
                             warningString += "Value for parameter '" + option + "' have equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditOffsetFastCorrNoMT10->setText(userInputSingleSpace.section(" ", 0,0).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-model:SBASreceiver", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(2);
                        } else {
                            warningString += "SBAS receiver type '" + userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0) + "' in parameter '" + option + "' is not valid. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:sigmpath", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (ParametersList.count()==2) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.) {
                                warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                            } else {
                                this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                                this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(true);
                                ui->lineEditSbasSigmaMultipathA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditSbasSigmaMultipathB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                            }
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.) {
                                warningString += "First two values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                                warningString += "Third value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                            } else {
                                this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                                this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(true);
                                ui->lineEditSbasSigmaMultipathA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditSbasSigmaMultipathB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                ui->lineEditSbasSigmaMultipathC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                            }
                        }
                    } else if ( QString::compare(option, "-model:sigdiv", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                            this->on_checkBoxUserDefinedReceiverSigmaDivergence_clicked(true);
                            ui->lineEditSbasSigmaDivergence->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:signoise", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                            this->on_checkBoxUserDefinedReceiverSigmaNoise_clicked(true);
                            ui->lineEditSbasSigmaNoise->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:khpa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkhpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:kvpa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkvpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:khnpa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkhnpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:kvnpa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkvnpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:nofastcor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableFastCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastcor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:norrccor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableRRCcorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:norrccor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableRRCcorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:noslowcor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableSlowCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:noslowcor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableSlowCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:noionocor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableIonosphereCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:noionocor", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableIonosphereCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:nofastsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:nofastdeg", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastdeg", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:norrcsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableRRCsigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:norrcsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableRRCsigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noslowsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableSlowCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:noslowsigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableSlowCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noionosigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableIonosphereSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:noionosigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableIonosphereSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:notroposigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableTroposphereSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:notroposigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableTroposphereSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noenroutesigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableEnRoute->setChecked(true);
                    } else if ( QString::compare(option, "--model:noenroutesigma", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableEnRoute->setChecked(false);
                    } else if ( QString::compare(option, "-model:nomt10", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSBASMessages_clicked(true);
                        ui->checkBoxDisableMT10->setChecked(true);
                    } else if ( QString::compare(option, "--model:nomt10", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableMT10->setChecked(false);
                    } else if ( QString::compare(option, "-model:nomt2728", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:nodeltaudre", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSBASMessages_clicked(true);
                        ui->checkBoxDisableMT2728->setChecked(true);
                    } else if ( QString::compare(option, "--model:nomt2728", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:nodeltaudre", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableMT2728->setChecked(false);
                    } else if ( QString::compare(option, "-model:dgnss:sigmainflation", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDgnssInflateSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:dgnss:sigmainflation", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDgnssInflateSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:dgnss:maxage", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMaxAgeDgnss->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:dgnss:maxcorrval", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMaxValueDGNSS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }


                    ////////////////////
                    // FILTER SECTION

                    } else if ( QString::compare(option, "-filter:nav", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "static", Qt::CaseInsensitive)==0) {
                           this->on_radioButtonStatic_clicked();
                        } else if (QString::compare(ParametersList[0], "kinematic", Qt::CaseInsensitive)==0) {
                            this->on_radioButtonKinematic_clicked();
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:meas", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if(mode>=2) {
                            //In SBAS or DGNSS mode this has no effect
                            warningString += "Parameter '" + option + "' has no effect in SBAS or DGNSS modes. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "pseudorange", Qt::CaseInsensitive)==0) {
                           this->on_radioButtonSelectionPseudorange_clicked();
                        } else if (QString::compare(ParametersList[0], "carrierphase", Qt::CaseInsensitive)==0) {
                            this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:select", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";
                        } else {
                            extraParametersToWarningStr(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()+1,&warningString,option,ParametersList);
                            if(mode>=2) {
                                //In SBAS or DGNSS mode this has no effect
                                warningString += "Parameter '" + option + "' has no effect in SBAS or DGNSS modes. It was skipped.\n";
                            } else {
                                for(i=1;i<=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();i++) {
                                    //Phase measurements
                                    if ((QString::compare(ParametersList[i], "C1C", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "C1", Qt::CaseInsensitive)==0) ) {
                                        if(i==2) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a code measurement as a second measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPseudorange->setCurrentIndex(0);
                                        }
                                    } else if ((QString::compare(ParametersList[i], "C1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "P1", Qt::CaseInsensitive)==0) ) {
                                        if(i==2) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a codee measurement as a second measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPseudorange->setCurrentIndex(1);
                                        }
                                    } else if (QString::compare(ParametersList[i], "C2P", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[i], "P2", Qt::CaseInsensitive)==0) {
                                        if(i==2) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a code measurement as a second measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPseudorange->setCurrentIndex(2);
                                        }
                                    } else if (QString::compare(ParametersList[i], "PC", Qt::CaseInsensitive)==0) {
                                        if(i==2) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a code measurement as a second measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonDualFreq_clicked();
                                            ui->comboBoxMeasConfDualFqPseudorange->setCurrentIndex(0);
                                        }
                                    //Phase measurements
                                    } else if ((QString::compare(ParametersList[i], "L1P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "L1", Qt::CaseInsensitive)==0) ) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(0);
                                        }
                                    } else if ((QString::compare(ParametersList[i], "L2P", Qt::CaseInsensitive)==0) || (QString::compare(ParametersList[i], "L2", Qt::CaseInsensitive)==0) ) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(1);
                                        }
                                    } else if (QString::compare(ParametersList[i], "LC", Qt::CaseInsensitive)==0) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonDualFreq_clicked();
                                            ui->comboBoxMeasConfDualFqPhase->setCurrentIndex(0);
                                        }
                                    } else if (QString::compare(ParametersList[i], "G1C", Qt::CaseInsensitive)==0) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(2);
                                        }
                                    } else if (QString::compare(ParametersList[i], "G1P", Qt::CaseInsensitive)==0) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(3);
                                        }
                                    } else if (QString::compare(ParametersList[i], "G2P", Qt::CaseInsensitive)==0) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(4);
                                        }
                                    } else if (QString::compare(ParametersList[i], "G2C", Qt::CaseInsensitive)==0) {
                                        if(i==1) {
                                            warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' cannot have a carrier phase measurement as a first measurement for the filter. It was skipped.\n";
                                        } else {
                                            this->on_radioButtonSingleFreq_clicked();
                                            ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(5);
                                        }
                                    } else {
                                        warningString += "Parameter '" + option + " " + ParametersList[0] + " " + ParametersList[1] + "' has an invalid measurement for the filter. It was skipped.\n";
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-filter:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:tropo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEstimateTroposphere->setChecked(true);
                    } else if ( QString::compare(option, "--filter:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "--filter:tropo", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEstimateTroposphere->setChecked(false);
                    } else if ( QString::compare(option, "-filter:fixedweight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";                        
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)==0 ) {
                            warningString += "Use of URA for fixed weight in parameter '" + option + "' is only available in command line. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<=0. && QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Fixed weight in for parameter '" + option + "' have to be greater than 0. It was skipped.\n";
                        } else {
                            if(DualFrequencyUsed==1) {
                                if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1 ) {
                                    this->on_radioButtonFixedStdDevDualCode_clicked();
                                    ui->lineEditFixedStdDevDualCode->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2 ) {
                                    this->on_radioButtonFixedStdDevDualCarrier_clicked();
                                    ui->lineEditFixedStdDevDualCarrier->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                } else {
                                    //Measurement is 0 (weight applied to all measurements)
                                    this->on_radioButtonFixedStdDevDualCode_clicked();
                                    ui->lineEditFixedStdDevDualCode->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    this->on_radioButtonFixedStdDevDualCarrier_clicked();
                                    ui->lineEditFixedStdDevDualCarrier->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                }
                            } else {
                                if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1 ) {
                                    this->on_radioButtonFixedStdDevSingleCode_clicked();
                                    ui->lineEditFixedStdDevSingleCode->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2 ) {
                                    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
                                    ui->lineEditFixedStdDevSingleCarrier->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                } else {
                                    //Measurement is 0 (weight applied to all measurements)
                                    this->on_radioButtonFixedStdDevSingleCode_clicked();
                                    ui->lineEditFixedStdDevSingleCode->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    this->on_radioButtonFixedStdDevSingleCarrier_clicked();
                                    ui->lineEditFixedStdDevSingleCarrier->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-filter:fixedweightsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {                                
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/                                
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0 ) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<=0. && QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Fixed weight in parameter '" + option + "' must be greater than 0. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:elevweight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)==0 ) {
                            warningString += "Use of URA for constant in parameter '" + option + "' is only available in command line. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0. && QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                            warningString += "Exponential factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant value and exponential factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()<=0.) {
                            warningString += "Elevation factor in parameter '" + option + "' must be greater than 0. It was skipped.\n";
                        } else {
                            if(DualFrequencyUsed==1) {
                                if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1 ) {
                                    this->on_radioButtonElevationStdDevDualCode_clicked();
                                    ui->lineEditElevationStdDevDualCodeA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevDualCodeB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevDualCodeC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2 ) {
                                    this->on_radioButtonElevationStdDevDualCarrier_clicked();
                                    ui->lineEditElevationStdDevDualCarrierA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevDualCarrierB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevDualCarrierC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                } else {
                                    //Measurement is 0 (weight applied to all measurements)
                                    this->on_radioButtonElevationStdDevDualCode_clicked();
                                    ui->lineEditElevationStdDevDualCodeA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevDualCodeB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevDualCodeC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                    this->on_radioButtonElevationStdDevDualCarrier_clicked();
                                    ui->lineEditElevationStdDevDualCarrierA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevDualCarrierB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevDualCarrierC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                }
                            } else {
                                if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1 ) {
                                    this->on_radioButtonElevationStdDevSingleCode_clicked();
                                    ui->lineEditElevationStdDevSingleCodeA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCodeB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCodeC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2 ) {
                                    this->on_radioButtonElevationStdDevSingleCarrier_clicked();
                                    ui->lineEditElevationStdDevSingleCarrierA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCarrierB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCarrierC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                } else {
                                    //Measurement is 0 (weight applied to all measurements)
                                    this->on_radioButtonElevationStdDevSingleCode_clicked();
                                    ui->lineEditElevationStdDevSingleCodeA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCodeB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCodeC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                    this->on_radioButtonElevationStdDevSingleCarrier_clicked();
                                    ui->lineEditElevationStdDevSingleCarrierA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCarrierB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                                    ui->lineEditElevationStdDevSingleCarrierC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 3,3).replace(",","")));
                                }
                            }
                        }                    
                    } else if ( QString::compare(option, "-filter:elevweightsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(5,&warningString,option,ParametersList);
                        if (ParametersList.count()<5) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0. && QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()<0.) {
                                    warningString += "Exponential factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant value and exponential factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 4,4).replace(",","").toDouble()<=0.) {
                                    warningString += "Elevation factor in parameter '" + option + "' must be greater than 0. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sinelevweight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.&& QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                            warningString += "Sinusoidal factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant value and sinusoidal factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sinelevweightsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0. && QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()<0.) {
                                    warningString += "Sinusoidal factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant value and sinusoidal factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrweight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.&& QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                            warningString += "SNR factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant value and SNR factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrweightsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()<0.) {
                                    warningString += "SNR factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant value and SNR factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrelevweight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.&& QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                            warningString += "SNR factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 1,1),"URA", Qt::CaseInsensitive)!=0) {
                            warningString += "Constant value and SNR factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrelevweightsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()<0.) {
                                    warningString += "Multiplier factor in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()==0. && userInputSingleSpace.section(" ", 3,3).replace(",","").toDouble()==0.&& QString::compare(userInputSingleSpace.section(" ", 2,2),"URA", Qt::CaseInsensitive)!=0) {
                                    warningString += "Constant value and multiplier factor in parameter '" + option + "' cannot be both 0. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrweight:comb", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"SNRi", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"SNRj", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"MaxSNR", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"MinSNR", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"MeanSNR", Qt::CaseInsensitive)!=0) {
                            if (userInputSingleSpace.section(" ", 1,1).contains("[a-zA-Z]")==true || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0
                                                || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()>1) {
                                warningString += "Value '" + userInputSingleSpace.section(" ", 1,1) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                            }
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:snrweight:combsat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (QString::compare(userInputSingleSpace.section(" ", 2,2),"SNRi", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"SNRj", Qt::CaseInsensitive)!=0
                                           && QString::compare(userInputSingleSpace.section(" ", 2,2),"MaxSNR", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"MinSNR", Qt::CaseInsensitive)!=0
                                           && QString::compare(userInputSingleSpace.section(" ", 2,2),"MeanSNR", Qt::CaseInsensitive)!=0) {
                                    if (userInputSingleSpace.section(" ", 2,2).contains("[a-zA-Z]")==true || userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0
                                                        || userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()>1) {
                                        warningString += "Value '" + userInputSingleSpace.section(" ", 2,2) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                                    } else {
                                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                    }
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sbasdgnssweightmode", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"ComputedOnly", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"ComputedPlusUser", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"Computed+User", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"UserOnly", Qt::CaseInsensitive)!=0) {
                            warningString += "Value '" + userInputSingleSpace.section(" ", 1,1) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sbasdgnssweightmodesat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BeiDouLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (QString::compare(userInputSingleSpace.section(" ", 2,2),"ComputedOnly", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"ComputedPlusUser", Qt::CaseInsensitive)!=0
                                           && QString::compare(userInputSingleSpace.section(" ", 2,2),"Computed+User", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"UserOnly", Qt::CaseInsensitive)!=0) {
                                    warningString += "Value '" + userInputSingleSpace.section(" ", 2,2) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:phi:dr", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiCoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:phi:clk", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiClock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:phi:trop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiTropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:phi:amb", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiPhaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:q:dr", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQcoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:q:clk", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQclock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:q:trop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQtropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:q:amb", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQphaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:p0:dr", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoCoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:p0:clk", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoClock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:p0:trop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoTropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:p0:amb", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoPhaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:backward", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxBackwardFiltering->setChecked(true);
                    } else if ( QString::compare(option, "--filter:backward", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxBackwardFiltering->setChecked(false);
                    } else if ( QString::compare(option, "-filter:stfdesa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        if (mode==2) {
                            //Stanford-ESA is only for SBAS mode
                            this->on_groupBoxStanfordESA_clicked(true);
                            this->on_checkBoxStanfordESAallGeometries_clicked(true);
                        } else {
                            warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:stfdesa", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxStanfordESA_clicked(false);
                    } else if ( QString::compare(option, "-filter:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        if (mode==2) {
                            //Stanford-ESA is only for SBAS mode
                            this->on_groupBoxStanfordESA_clicked(true);
                            this->on_checkBoxStanfordESAallGeometries_clicked(true);
                        } else {
                            warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxStanfordESAallGeometries_clicked(false);
                    } else if ( QString::compare(option, "-filter:stfdesa:hwir", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditHorizontalIntegrityRatio->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:vwir", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditVerticalIntegrityRatio->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:xmax", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaXmax->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:ymax", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaYmax->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:xres", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaXres->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:yres", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaYres->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:maxhdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxHDOP_clicked(true);
                            ui->lineEditMaxHDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxhdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxHDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:maxpdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxPDOP_clicked(true);
                            ui->lineEditMaxPDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxpdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxHDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:maxgdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxGDOP_clicked(true);
                            ui->lineEditMaxGDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxgdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxGDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:hdoporpdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxHDOPorPDOP->setChecked(true);
                    } else if ( QString::compare(option, "--filter:hdoporpdop", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxHDOPorPDOP->setChecked(false);
                    } else if ( QString::compare(option, "-filter:SigmaIono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUseSigmaIonosphere->setChecked(true);
                    } else if ( QString::compare(option, "--filter:SigmaIono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUseSigmaIonosphere->setChecked(false);
                    } else if ( QString::compare(option, "-filter:StepDetector", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        if(mode==2) {
                            //Step detector is only used in SBAS mode
                            ui->checkBoxStepDetector->setChecked(true);
                        } else {
                            warningString += "Step detector (parameter '" + option + "' only takes effect in SBAS mode. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:StepDetector", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStepDetector->setChecked(false);
                    } else if ( QString::compare(option, "-filter:prefitOutliers:Abs", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:prefitOutliers:Abs", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:prefitOutliers:Median", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrefitOutliers_clicked(true);
                            ui->lineEditPrefitOutliers->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:prefitOutliers:Median", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrefitOutliers_clicked(false);

                    ////////////////////
                    // OUTPUT SECTION

                    } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditOutputDestination->setText(userInput);
                        }
                    } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
                    } else if ( QString::compare(option, "-output:kml", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxKML_clicked(true);
                            ui->lineEditKML->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml0", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxKML0_clicked(true);
                            ui->lineEditKML0->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml:refsta", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        if(mode!=3) {
                            //This option only has effect in DGNSS mode
                            warningString += "Parameter '" + option + "' only takes effect in DGNSS mode. It was skipped.\n";
                        } else {
                            ui->checkBoxKMLRefStations->setChecked(true);
                        }
                    } else if ( QString::compare(option, "--output:kml:refsta", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLRefStations->setChecked(false);
                    } else if ( QString::compare(option, "-output:kml:egm96geoid", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLGeoid->setChecked(true);
                    } else if ( QString::compare(option, "--output:kml:egm96geoid", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLGeoid->setChecked(false);
                    } else if ( QString::compare(option, "-output:kml:tstamp", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBox_KML_TimeStamps_clicked(true);
                    } else if ( QString::compare(option, "--output:kml:tstamp", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBox_KML_TimeStamps_clicked(false);
                    } else if ( QString::compare(option, "-output:kml:tstampdec", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBox_KML_TimeStamps_clicked(true);
                            ui->lineEditKML_Dec->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-output:kml:tstamprange", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if ( (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. && userInputSingleSpace.section(" ", 0,0)!="-") ||
                              (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0. && userInputSingleSpace.section(" ", 1,1)!="-") ) {
                            warningString += "Timestamp ranges in parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else {
                            numKMLRanges++;
                            if(numKMLRanges==1) {
                                this->on_checkBox_KML_TimeStamps_clicked(true);
                                this->on_checkBox_KML_Range_clicked(true);
                                ui->lineEditKML_From->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditKML_To->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                            } else {
                                warningString += "Only one timestamp range can be set in the GUI (in command line there is no limit). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-output:sp3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxOutputSP3_clicked(true);
                            ui->lineEditOutputSP3->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:sp3:letter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).length()>1) {
                            warningString += "Parameter '" + option + "' only admits one character for the satellite constellation. It was skipped.\n";
                        } else if (!userInputSingleSpace.section(" ", 0,0).contains("[A-Z]")) {
                            warningString += "Parameter '" + option + "' only admits capital letters for satellite constellation. It was skipped.\n";
                        } else {
                            ui->lineEditSP3Letter->setText(userInputSingleSpace.section(" ", 0,0));
                        }
                    } else if ( QString::compare(option, "-output:sp3:prn", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>99) {
                            warningString += "PRN number for parameter '" + option + "' has to be greater than 0 and less than 100. It was skipped.\n";
                        } else {
                            ui->lineEditSP3PRN->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()));
                        }
                    } else if ( QString::compare(option, "-output:sp3:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSP3OutFileWriteSPPSolutions->setChecked(true);
                    } else if ( QString::compare(option, "--output:sp3:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSP3OutFileWriteSPPSolutions->setChecked(false);
                    } else if ( QString::compare(option, "-output:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxOutRefFile_clicked(true);
                            ui->lineEditOutRefFile->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:refpos:doy", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileYearDoYSoD->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:gpsweek", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileGPSWeek->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:caltime", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileCalendar->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRefOutFileWriteSPPSolutions->setChecked(true);
                    } else if ( QString::compare(option, "--output:refpos:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRefOutFileWriteSPPSolutions->setChecked(false);
                    } else if ( QString::compare(option, "-output:refpos:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileGeod->setChecked(true);
                    } else if ( QString::compare(option, "--output:refpos:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileCartesian->setChecked(false);
                    } else if ( QString::compare(option, "-output:satvel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        //This parameter is hidden in the GUI, due to "Inertial" velocity is not the completely in inertial coordinates
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "inertial", Qt::CaseInsensitive)==0) {
                             if (ui->frameOutputSatVel->isHidden()==true) {
                                warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                             }
                             ui->radioButtonSatVelInertial->setChecked(true);
                        } else if (QString::compare(ParametersList[0], "ITRF", Qt::CaseInsensitive)==0) {
                            if (ui->frameOutputSatVel->isHidden()==true) {
                                warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                            }
                             ui->radioButtonSatVelECEF->setChecked(true);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-output:stfdesa", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditOutputStanfordEsaPlot->setText(userInput);
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-output:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if (mode==2) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditOutputframeStanfordESAallGeometries->setText(userInput);
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }



                    ////////////////////
                    // PRINT SECTION

                    } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(true);
                    } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(false);
                    } else if ( QString::compare(option, "-print:model", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintModel->setChecked(true);
                    } else if ( QString::compare(option, "--print:model", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintModel->setChecked(false);
                    } else if ( QString::compare(option, "-print:prefit", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPrefit->setChecked(true);
                    } else if ( QString::compare(option, "--print:prefit", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPrefit->setChecked(false);
                    } else if ( QString::compare(option, "-print:postfit", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPostfit->setChecked(true);
                    } else if ( QString::compare(option, "--print:postfit", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPostfit->setChecked(false);
                    } else if ( QString::compare(option, "-print:filter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintFilter->setChecked(true);
                    } else if ( QString::compare(option, "--print:filter", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintFilter->setChecked(false);
                    } else if ( QString::compare(option, "-print:cycleslips", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintCS->setChecked(true);
                    } else if ( QString::compare(option, "--print:cycleslips", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintCS->setChecked(false);
                    } else if ( QString::compare(option, "-print:satellites", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:epochsat", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:sat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintEpochsat->setChecked(true);
                    } else if ( QString::compare(option, "--print:satellites", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:epochsat", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:sat", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintEpochsat->setChecked(false);
                    } else if ( QString::compare(option, "-print:input", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInput->setChecked(true);
                    } else if ( QString::compare(option, "--print:input", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInput->setChecked(false);
                    } else if ( QString::compare(option, "-print:meas", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintMeas->setChecked(true);
                    } else if ( QString::compare(option, "--print:meas", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintMeas->setChecked(false);
                    } else if ( QString::compare(option, "-print:output", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintOutput->setChecked(true);
                    } else if ( QString::compare(option, "--print:output", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintOutput->setChecked(false);
                    } else if ( QString::compare(option, "-print:satsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSatsel->setChecked(true);
                    } else if ( QString::compare(option, "--print:satsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSatsel->setChecked(false);
                    } else if ( QString::compare(option, "-print:satdiff", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satdiff", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satstat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satstat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satstattot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satstattot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satpvt", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for show orbits mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satpvt", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for show orbits mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:sbasout", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasout->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasout", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasout->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbascor", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:sbascorr", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbascor->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbascor", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:sbascorr", Qt::CaseInsensitive)==0) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbascor->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasvar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasvar->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasvar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasvar->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasiono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasiono->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasiono", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasiono->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasunsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunsel->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasunsel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunsel->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasunused", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunused->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasunused", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunused->setChecked(false);
                    } else if ( QString::compare(option, "-print:usererror", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintUsererror->setChecked(true);
                    } else if ( QString::compare(option, "--print:usererror", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintUsererror->setChecked(false);
                    } else if ( QString::compare(option, "-print:dgnss", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnss->setChecked(true);
                    } else if ( QString::compare(option, "--print:dgnss", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnss->setChecked(false);
                    } else if ( QString::compare(option, "-print:dgnssunused", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnssunused->setChecked(true);
                    } else if ( QString::compare(option, "--print:dgnssunused", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnssunused->setChecked(false);
                    } else if ( QString::compare(option, "-print:summary", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(true);
                    } else if ( QString::compare(option, "--print:summary", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(false);
                    } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(true);
                        ui->checkBoxPrintModel->setChecked(true);
                        ui->checkBoxPrintPrefit->setChecked(true);
                        ui->checkBoxPrintPostfit->setChecked(true);
                        ui->checkBoxPrintFilter->setChecked(true);
                        ui->checkBoxPrintCS->setChecked(true);
                        ui->checkBoxPrintEpochsat->setChecked(true);
                        ui->checkBoxPrintInput->setChecked(true);
                        ui->checkBoxPrintMeas->setChecked(true);
                        ui->checkBoxPrintOutput->setChecked(true);
                        ui->checkBoxPrintSbasout->setChecked(true);
                        ui->checkBoxPrintSbascor->setChecked(true);
                        ui->checkBoxPrintSbasvar->setChecked(true);
                        ui->checkBoxPrintSbasiono->setChecked(true);
                        ui->checkBoxPrintSbasunsel->setChecked(true);
                        ui->checkBoxPrintSbasunused->setChecked(true);
                        ui->checkBoxPrintUsererror->setChecked(true);
                        ui->checkBoxPrintDgnss->setChecked(true);
                        ui->checkBoxPrintDgnssunused->setChecked(true);
                        this->on_checkBoxPrintSummary_clicked(true);
                    } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0|| QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(false);
                        ui->checkBoxPrintModel->setChecked(false);
                        ui->checkBoxPrintPrefit->setChecked(false);
                        ui->checkBoxPrintPostfit->setChecked(false);
                        ui->checkBoxPrintFilter->setChecked(false);
                        ui->checkBoxPrintCS->setChecked(false);
                        ui->checkBoxPrintEpochsat->setChecked(false);
                        ui->checkBoxPrintInput->setChecked(false);
                        ui->checkBoxPrintMeas->setChecked(false);
                        ui->checkBoxPrintOutput->setChecked(false);
                        ui->checkBoxPrintSbasout->setChecked(false);
                        ui->checkBoxPrintSbascor->setChecked(false);
                        ui->checkBoxPrintSbasvar->setChecked(false);
                        ui->checkBoxPrintSbasiono->setChecked(false);
                        ui->checkBoxPrintSbasunsel->setChecked(false);
                        ui->checkBoxPrintSbasunused->setChecked(false);
                        ui->checkBoxPrintUsererror->setChecked(false);
                        ui->checkBoxPrintDgnss->setChecked(false);
                        ui->checkBoxPrintDgnssunused->setChecked(false);
                        this->on_checkBoxPrintSummary_clicked(false);
                    } else if ( QString::compare(option, "-print:progress", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for showing progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--print:progress", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for not showing progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-print:progressalways", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for forcing to show the progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--print:progressalways", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for forcing to show the progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-print:guiprogress", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is an internal parameter for printing the progress in a format readable by the GUI. It was skipped.\n";


                    ////////////////////
                    // SUMMARY SECTION

                    } else if ( QString::compare(option, "-sbassummary:VAL", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:VAL", Qt::CaseInsensitive)==0  ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditHorizontalAlarmLimitSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-sbassummary:HAL", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:HAL", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditVerticalAlarmLimitSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-sbassummary:percentile", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:percentile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>100 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 and less or equal to 100. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditPercentileValue->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:windowsize", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:windowsize", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSlidingWindowSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:windowsizemar", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:windowsizemar", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditMaritimeWindowSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:waitfordaystart", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:waitfordaystart", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(true);
                        this->on_checkBoxWaitforDayStart_clicked(true);
                    } else if ( QString::compare(option, "--sbassummary:waitfordaystart", Qt::CaseInsensitive)==0 || QString::compare(option, "--summary:waitfordaystart", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxWaitforDayStart_clicked(false);
                    } else if ( QString::compare(option, "-sbassummary:stationnetworkname", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:stationnetworkname", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbassummary:starttime", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:starttime", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            ValidDate=1;
                            addDay=0;
                            leapYear=0;
                            extraParametersToWarningStr(2,&warningString,option,ParametersList);
                            if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                                //Time has ":" symbol.
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Time is in YYYY/MM/DD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                         if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                             warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                             ValidDate=0;
                                         } else {
                                             year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                             month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                             day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                                         }
                                    }
                                } else {
                                    //Time is in YYYYMMDD HH:MM:SS format
                                    if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                                        //Invalid date
                                        warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                            ValidDate=0;
                                        } else {
                                            year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                            month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                            day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                                        }
                                    }
                                }
                                if (ValidDate==1) {
                                    //Check date values and time length
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(month<1||month>12) {
                                        warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                                        warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                        warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                if (ValidDate==1) {
                                    //Read time in HH:MM:SS format and check values
                                    hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                                    minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                                    second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                                    if(hour2<0||hour2>24) {
                                        warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(minute<0||minute>60) {
                                        warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(second<0||second>60) {
                                        warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                }
                                 if (ValidDate==1) {
                                     if(second==60) {
                                         second-=60;
                                         minute++;
                                     }
                                     if(minute==60) {
                                         minute-=60;
                                         hour2++;
                                     }
                                     if(hour2==24) {
                                         hour2-=24;
                                         addDay=1;
                                     }
                                     date=QDate(year,month,day);
                                     if(addDay==1) {
                                        date=date.addDays(qint64(1));
                                     }
                                     hour=QTime(hour2,minute,second);
                                     ui->dateTimeEditStartTimeSummary->setDate(date);
                                     ui->dateTimeEditStartTimeSummary->setTime(hour);
                                     this->on_checkBoxPrintSummary_clicked(true);
                                     this->on_checkBoxStartTimeSummary_clicked(true);
                                 }
                            } else {
                                //Time can be in YYYY/DoY or GPSWeek
                                if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                                    //Date is in YYYY/DoY SoD format
                                    year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                    doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                                    sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(year<=1970) {
                                        warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                                        ValidDate=0;
                                    } else {
                                        //Check leap year
                                        if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                            leapYear=1;
                                        }
                                    }
                                    if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                        warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sod<0||sod>86400) {
                                        warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sod==86400) {
                                            sod-=86400;
                                            doy++;
                                        }
                                        if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                            doy=1;
                                            year++;
                                        }
                                        doy2date(year,doy,&date);
                                        SoD2time(sod,&hour);
                                        ui->dateTimeEditStartTimeSummary->setDate(date);
                                        ui->dateTimeEditStartTimeSummary->setTime(hour);
                                        this->on_checkBoxPrintSummary_clicked(true);
                                        this->on_checkBoxStartTimeSummary_clicked(true);
                                    }
                                } else {
                                    //Date is in GPSWeek SoW format
                                    GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                                    sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                                    if(GPSWeek<1) {
                                        warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if(sow<0||sow>604800) {
                                        warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                                        ValidDate=0;
                                    }
                                    if (ValidDate==1) {
                                        if(sow==604800) {
                                            sow-=604800;
                                            GPSWeek++;
                                        }
                                        GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                                        ui->dateTimeEditStartTimeSummary->setDate(date);
                                        ui->dateTimeEditStartTimeSummary->setTime(hour);
                                        this->on_checkBoxPrintSummary_clicked(true);
                                        this->on_checkBoxStartTimeSummary_clicked(true);
                                    }
                                }
                            }
                        }

                    ////////////////////
                    // FILE CONVERSION SECTION

                    } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:rinexb", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:ems", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegasus", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegspace", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegstrictrinex", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegfilealign", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:rinexversion", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                        }


                    ////////////////////
                    // SBAS PLOTS SECTION

                    } else if ( QString::compare(option, "-sbasplots:minlat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-90. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90. ) {
                            warningString += "Parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:maxlat", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-90. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90. ) {
                            warningString += "Parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:minlon", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-180. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>180. ) {
                            warningString += "Parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:maxlon", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-180. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>180. ) {
                            warningString += "Parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:recheight", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:VAL", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:HAL", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:AvailStep", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.01 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 with a minimum resolution of 0.01 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:IonoStep", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.01 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 with a minimum resolution of 0.01 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:ionotimestep", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:windowsize", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:plotarea", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:exclusionarea", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:inclusionarea", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:hourlymaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:hourlymaps", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noAvailPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noAvailPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noRiskPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noRiskPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noIonoPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noIonoPlot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noIonoModel", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:hdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:hdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:pdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:pdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:gdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:gdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:combdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:combdopplot", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:doppercentile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:doppercentile", Qt::CaseInsensitive)==0 ) {
                        extraParametersToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-output:sbasavailplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskmarplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskdisc", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasionoplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbashdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbaspdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasgdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbascombdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else {
                        warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                    }
                }
                file.close();

                if ( !warningString.isEmpty() ) {
                    messageBox.warning(0, "Errors found",
                                        "gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
                }
            }
        }
    }
}

////////////////////////////////////////////////////
// Date Conversion functions

//Convert Year/DoY to QDate
void gLAB_GUI::doy2date (int year, int doy, QDate *date) {
    int i = -1;
    int res, month, day;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ( doy > 366 ) return;

    if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 )
        daysmonth[2] += 1;

    res = doy;
    while ( res > 0 ) {
        i += 1;
        res -= daysmonth[i];
    }

    month = i;
    day = daysmonth[i] + res;
    *date=QDate(year,month,day);
}

//Convert SoD to QTime
void gLAB_GUI::SoD2time (int SoD,QTime *time) {
    int hour, minute,second;
    hour=(int)( (double)(SoD)/3600.);
    minute=(int)((double)(SoD)/60.)%60;
    second=SoD%60;

    *time=QTime(hour,minute,second,0);
}

//Convert from GPSWeek and SoW to QDate and QTime
void gLAB_GUI::GPSTime2DateTime(int GPSWeek, int SoW, QDate *date, QTime *time) {
    int DoW;
    int SoD;

    DoW=(int)((double)(SoW)/86400.0);
    SoD=SoW-DoW*86400;
    *date=QDate(1980,1,6); //Start of GPS time
    *date=date->addDays(qint64(GPSWeek*7+DoW));
    SoD2time(SoD,time);
}

//Convert from string or character to enum GNSStype
enum GNSSystem gLAB_GUI::ConsString2ConsEnum(QString Constellation) {
    if ( QString::compare(Constellation, "G", Qt::CaseSensitive)==0 || QString::compare(Constellation, "GPS", Qt::CaseSensitive)==0 ) {
        return GPS;
    } else if ( QString::compare(Constellation, "R", Qt::CaseSensitive)==0 || QString::compare(Constellation, "GLONASS", Qt::CaseSensitive)==0 ) {
        return GLONASS;
    } else if ( QString::compare(Constellation, "E", Qt::CaseSensitive)==0 || QString::compare(Constellation, "Galileo", Qt::CaseSensitive)==0 ) {
        return Galileo;
    } else if ( QString::compare(Constellation, "S", Qt::CaseSensitive)==0 || QString::compare(Constellation, "SBAS", Qt::CaseSensitive)==0 ) {
        return GEO;
    } else if ( QString::compare(Constellation, "C", Qt::CaseSensitive)==0 || QString::compare(Constellation, "BeiDou", Qt::CaseSensitive)==0 ) {
        return BDS;
    } else if ( QString::compare(Constellation, "J", Qt::CaseSensitive)==0 || QString::compare(Constellation, "QZSS", Qt::CaseSensitive)==0 ) {
        return QZSS;
    } else if ( QString::compare(Constellation, "I", Qt::CaseSensitive)==0 || QString::compare(Constellation, "IRNSS", Qt::CaseSensitive)==0 ) {
        return IRNSS;
    }

    return GNSSSystemUnknown;
}
