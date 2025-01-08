/****************************************************************************
 * Copyright & License:
 * ====================
 *
 *  Copyright 2009 - 2024 gAGE/UPC & ESA
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
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2018/01/12
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
 *          gLAB v6.0.0
 * Release: 2024/11/22
 * Change Log: Added multi-constellation, multi-frequency and multi-navigation message support for SPP and PPP. SBAS 1F supports
 *               using GEO an potentially GLONASS (although it is not testes as there are no messages). DGNSS (and RTCM decoding) is still GPS only,
 *               but all the internal logic have been upgraded to multi-constellation.
 *             Added SBAS DFMC mode.
 *             Added splash screen during the loading process.
 *             Added "Set multi-threading options" menu for setting the number of theads to use by the gLAB core.
 *             Added "Print messages in gLAB v5 format" option to make the gLAB core use the v5 output messages format (enabling
 *              this option will make templates in Analysis mode not work, as they are for v6).
 *             Added "Start Time" and "End Time" options in Show Orbits & clocks and Compare Orbits & clocks modes.
 *             Added "Maximum satellite combinations" option in Stanford-ESA options.
 *             Added option to change clock unit to nanoseconds in output messages in Positioning, Show Orbits & clocks and Compare Orbits & clocks modes.
 *             Added thresholds for computing convergence time in PPP modes.
 *             Added new output messages SFCSDATA, MWCSDATA, LICSDATA, IGFCSDATA containing data on cycle-slip computation.
 *             Added new windows for cycle-slip manual measurement selection (one per cycle-slip detector).
 *             Added new windows for SNR threshold selection per constellation and per frequency.
 *             Added new window for measurement selection per constellation for MEAS message.
 *             Added new window for managing the measurement priority list per constellation.
 *             Added random walk mode in filter coordinates, clocks and inter-system clock biases.
 *             Added "GLONASS RINEX navigation file" option in Add User Error to RINEX mode.
 *             Added link "https://epncb.oma.be/ftp/RINEX/" in RINEX Observation Files Version 2 menu.
 *             Added link "https://igs.bkg.bund.de/root_ftp/IGLOS/obs/" in RINEX Observation Files Version 2 menu.
 *             Added link "https://cddis.nasa.gov/archive/gnss/data/daily/" in RINEX Observation Files Version 3 menu.
 *             Added link "https://cddis.nasa.gov/archive/gnss/data/highrate/" in RINEX Observation Files Version 3 menu.
 *             Added link "https://gage-data.earthscope.org/archive/gnss/rinex/nav/" in RINEX Navigation Files Version 2 menu.
 *             Added link "http://garner.ucsd.edu/pub/nav/" in RINEX Navigation Files Version 2 menu.
 *             Added link "https://gage-data.earthscope.org/archive/gnss/products/sinex/" in Precise Files menu.
 *             Added link "http://ftp.aiub.unibe.ch/CODE/" in Precise Files and Other Files menus.
 *             Added link "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-products.dat" in Lists of NTRIP station menu.
 *             Added "Geoscience Australia" in "RINEX files from institutions" menu, containing link
 *               "https://www.unavco.org/data/gps-gnss/data-access-methods/gnss-data-access-notebooks/gnss-permanent-station-data-access-notebook-embed.html".
 *             Added link "https://www.unavco.org/data/gps-gnss/data-access-methods/gnss-data-access-notebooks/gnss-permanent-station-data-access-notebook-embed.html"
 *               in UNAVCO's Database RINEX Searcher.
 *             Added link "https://data.gnss.ga.gov.au/docs/home/gnss-data.html"
 *             Changed link from "http://gage.upc.es/glab-release-notes" to
 *               "https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-release-notes" in Release notes menu.
 *             Changed link from "http://gage.upc.es/gFD" to "https://gage.upc.edu/en/learning-materials/library/gnss-format-descriptions"
 *               in File formats description menu.
 *             Changed link from "http://www.gnsscalendar.com" to "https://www.gnsscalendar.com" in GNSS calendar menu.
 *             Changed link from "http://www.gnu.org/licenses/gpl.txt" to "https://www.gnu.org/licenses/gpl.txt" in License menu.
 *             Changed link from "http://www.gnu.org/licenses/lgpl.txt" to "https://www.gnu.org/licenses/lgpl.txt"  in License menu.
 *             Changed link from "http://www.apache.org/licenses/LICENSE-2.0" to "https://www.apache.org/licenses/LICENSE-2.0" in License menu.
 *             Changed link from "http://terras.gsi.go.jp/ja/crx2rnx.html" to "https://terras.gsi.go.jp/ja/crx2rnx.html" in Hatanaka compressor menu.
 *             Changed link from "http://semisys.gfz-potsdam.de/semisys/scripts/download/#software" to "https://gnss.gfz-potsdam.de/services/gfzrnx"
 *               in GFZRNX RINEX manipulator menu.
 *             Changed link from "http://gage.upc.es/gnss_book" to "https://gage.upc.edu/en/learning-materials/library/gnss-books/gnss-data-processing-book"
 *               in GNSS Data Processing Book menu.
 *             Changed link from "http://gage.upc.es/tutorials" to
 *               "https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-tutorials/gnss-tutorials"
 *               in GNSS Master Course menu.
 *             Changed link from "ftp://garner.ucsd.edu/rinex/" to "http://garner.ucsd.edu/pub/rinex/" in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://ftp.epncb.oma.be/pub/obs/" to "https://epncb.oma.be/ftp/RINEX/" in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://www.ngs.noaa.gov/cors/rinex/" to "https://geodesy.noaa.gov/corsdata/rinex/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://data-out.unavco.org/pub/rinex/obs/" to "https://gage-data.earthscope.org/archive/gnss/rinex/obs"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/IGS/obs/" to "https://igs.bkg.bund.de/root_ftp/IGS/obs/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/GREF/obs/" to "https://igs.bkg.bund.de/root_ftp/GREF/obs/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MISC/obs/" to "https://igs.bkg.bund.de/root_ftp/MISC/obs/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MGEX/obs/" to "https://igs.bkg.bund.de/root_ftp/MGEX/obs/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/EUREF/obs/" to "https://igs.bkg.bund.de/root_ftp/EUREF/obs/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://garner.ucsd.edu/rinex_highrate/" to "http://garner.ucsd.edu/pub/rinex_highrate/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/IGS/highrate/" to "https://igs.bkg.bund.de/root_ftp/IGS/highrate/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/GREF/highrate/" to "https://igs.bkg.bund.de/root_ftp/GREF/highrate/"
 *                in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MISC/highrate/" to "https://igs.bkg.bund.de/root_ftp/MISC/highrate/
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MGEX/highrate/" to "https://igs.bkg.bund.de/root_ftp/MGEX/highrate/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/EUREF/highrate/" to "https://igs.bkg.bund.de/root_ftp/EUREF/highrate/"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://data-out.unavco.org/pub/highrate/" to "https://gage-data.earthscope.org/archive/gnss/highrate"
 *               in RINEX Observation Files Version 2 menu.
 *             Changed link from "ftp://data-out.unavco.org/pub/rinex3/obs/" to "https://gage-data.earthscope.org/archive/gnss/rinex3"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/IGS/obs_v3/" to "https://igs.bkg.bund.de/root_ftp/IGS/obs_v3/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MISC/obs_v3/" to "https://igs.bkg.bund.de/root_ftp/MISC/obs_v3/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MGEX/obs_v3/" to "https://igs.bkg.bund.de/root_ftp/MGEX/obs_v3/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/EUREF/obs_v3/" to "https://igs.bkg.bund.de/root_ftp/EUREF/obs_v3/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/EUREF/highrate/" to "https://igs.bkg.bund.de/root_ftp/EUREF/highrate/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/IGS/BRDC/" to "https://igs.bkg.bund.de/root_ftp/IGS/BRDC/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/GREF/BRDC/" to "https://igs.bkg.bund.de/root_ftp/GREF/BRDC/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://igs.bkg.bund.de/MGEX/BRDC_v3/" to "https://igs.bkg.bund.de/root_ftp/MGEX/BRDC_v3/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2013/brdm/" to
 *               "https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/" in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://data-out.unavco.org/pub/rinex3/nav/" to "https://gage-data.earthscope.org/archive/gnss/rinex3/nav/"
 *               in RINEX Observation Files Version 3 menu.
 *             Changed link from "ftp://garner.ucsd.edu/products/" to "http://garner.ucsd.edu/pub/products/" in Precise Files menu.
 *             Changed link from "https://cddis.gsfc.nasa.gov/archive/gps/products" to "https://cddis.gsfc.nasa.gov/archive/gnss/products"
 *               in Precise Files menu.
 *             Changed link from "https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/" to "https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/"
 *               in Precise Files menu.
 *             Changed link from "ftp://ftp.igs.org/pub/station/general/pcv_archive/" to "https://files.igs.org/pub/station/general/pcv_archive/"
 *               in Other Files menu.
 *             Changed link from "ftp://ftp.aiub.unibe.ch/CODE" to "http://ftp.aiub.unibe.ch/CODE/" in Other Files menu.
 *             Changed link from "https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/GPS_Receiver_Types.gz" to
 *               "https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/etc/GPS_Receiver_Types.gz" in Other Files menu.
 *             Changed link from "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_euref-ip" to
 *               "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-euref.dat" in Lists of NTRIP station menu.
 *             Changed link from "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_igs-ip.htm" to
 *                "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-igs.dat" in Lists of NTRIP station menu.
 *             Changed link from "ftp://data-out.unavco.org/pub/" to "https://gage-data.earthscope.org/archive/gnss" in UNAVCO's Database RINEX Searcher.
 *             Changed link from "http://www.icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex" to
 *               "https://icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex" in Reference Station Files from Spain menu.
 *             Changed link from "ftp://icvficheros.icv.gva.es/Datos/" to "ftps://ftps.gva.es/Datos" in Reference Station Files from Spain menu.
 *             Changed link from "ftp://ftp.geodesia.ign.es/ERGNSS/" to "https://datos-geodesia.ign.es/ERGNSS/" in Reference Station Files from Spain menu.
 *             Changed gLAB paper citation from:
 *                 Ibáñez D., Rovira-García A., Sanz J., Juan JM., Gonzalez-Casado G., Jimenez-Baños D., López-Echazarreta C., Lapin I.
 *                 The GNSS Laboratory Tool Suite (gLAB) updates: SBAS, DGNSS and Global Monitoring System.
 *                 9th ESA Workshop on Satellite Navigation Technologies (NAVITEC2018), Noordwijk, The Netherlands.
 *                 December 5 - 7, 2018. DOI: 10.1109/NAVITEC.2018.8642707.
 *               To the following one:
 *                 Ibáñez D. (2023) Contributions to multi-purpose GNSS positioning to support multi-frequency and multi-constellation
 *                 with high accuracy and integrity. PhD thesis, URL https://server.gage.upc.edu/PhD/Ibanez_Deimos/PhD_Ibanez_Deimos.pdf.
 *               The previous citation has been left as additional one.
 *             Changed "GFZRNX RINEX version converter" menu name to "GFZRNX RINEX".
 *             Changed tooltip behaviour. For large tooltips, now they will open in a medium size but with scrollbars.
 *             Changed default for Prefit Outlier Detector Option. Now it is on by default in all modes (before it was off in all modes).
 *             Removed links "ftp://lox.ucsd.edu/rinex/" and "ftp://lox.ucsd.edu/rinex_highrate/" from RINEX Observation Files Version 2 and
 *               RINEX Navigation Files Version 2 as they point to same URL as "http://garner.ucsd.edu/pub/rinex/" and
 *               "http://garner.ucsd.edu/pub/rinex_highrate/" respectively.
 *             Removed link "ftp://ftp.nga.mil/pub2/gps/" from Precise orbits and clocks (SP3, CLK and SINEX files) menu.
 *             Removed link "https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/" from Precise orbits and clocks (SP3, CLK and
 *              SINEX files) menu.
 *             Removed link "ftp://ems.estec.esa.int/pub/" from SBAS Files menu.
 *             Removed link "https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/" in Other Files menu (SINEX BIAS OSB files).
 *             Removed link "https://igs.bkg.bund.de/dataandproducts/streams" from Lists of NTRIP station menu.
 *             Removed link "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_mgex.htm" from Lists of NTRIP station menu.
 *             Removed link "https://igs.bkg.bund.de/root_ftp/NTRIP/streams/streamlist_gref-ip.htm" from Lists of NTRIP station menu.
 *             Removed link "https://www.unavco.org/data/dai/" in UNAVCO's Database RINEX Searcher.
 *             Removed link "https://www.unavco.org/data/gps-gnss/data-access-methods/dai2/app/dai2.html" in UNAVCO's Database RINEX Searcher.
 *             Removed warning that triggered when dual frequency measurements were used but only single frequency cycle-slip detector,
 *               as the single frequency cycle-slip detectors will run on all carrier phases.
 *             Removed "SBAS Manual" and "DGNSS Manual" menus, as these manuals have been merged in the main gLAB manual.
 *             In Linux, library "libtiff" is now statically linked, as this library is only available with version 6 (libtiff6) since Ubuntu 23,
 *               while the GUI is compiled with version 5 (libtiff5). Note that the libtiff library used has been recompiled without support
 *               for "jBig" library, so the latter is not a new library dependency in the executable.
 *             Warnings and error messages generated by gLAB (when loading or saving configuration or executing gLAB) can now be selected with the mouse and copied.
 *             Fixed command line generation warnings not being shown when using "Show command line instruction".
 *             Fixed incorrect error message shown (instead of the real one printed by the gLAB core) in all modes (except Analysis mode) when gLAB core run t
 *               ended with error but did no create an output file, or the output file was empty or created from a previous run.
 *             Fixed GUI crash when when gLAB core run ended with a crash and the output file had been created but it was empty.
 *             Fixed "User Adder Error Mode" checking for gLAB errors in the output file set for orbit show mode instead of the one set for its own mode.
 *             Dropped support for 32-bit in Windows and Linux (except for ARMv7). The GUI can still be compiled in 32-bit by the user.
 *             Dropped support for Windows XP, Windows Vista and Ubuntu versions below 14.04. The GUI can still be compiled in these
 *               Windows versions (with Qt 5.7.1) by the users. For Ubuntu versions below 14, it can only we compiled if with GCC version
 *               4.8.1 (due to C++11 is required for compiling).
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#include "glab_gui.h"
#include "ui_glab_gui.h"
#include "math.h"



int DateConverterWindow=0;

////Definition of free functions (functions which does not belong to a class and can be called by any class)

int checkConstellationQChar(QChar charac) {
    switch (charac.unicode()) {
        case 'G': case 'g': case 'E': case 'e':
        case 'R': case 'r': case 'S': case 's':
        case 'C': case 'c': case 'J': case 'j':
        case 'I': case 'i':
            return 1;
        default:
            return 0;
    }
}

enum GNSSystem gnssQchar2gnsstype(QChar GNSS) {
    switch(GNSS.unicode()) {
        case 'G': case 'g':
            return GPS;
        case 'E': case 'e':
            return Galileo;
        case 'R': case 'r':
            return GLONASS;
        case 'S': case 's':
            return GEO;
        case 'C': case 'c':
            return BDS;
        case 'J': case 'j':
            return QZSS;
        case 'I': case 'i':
            return IRNSS;
        default:
            return GPS; //Default value
    }
}

// GUI constructor
gLAB_GUI::gLAB_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gLAB_GUI) {

    ui->setupUi(this);

    openP1P2=1;

    v5Message=0;

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
        ui->pageGPSPRN->setMinimumHeight(130); //124
        ui->pageGalileoPRN->setMinimumHeight(130); //155
        ui->pageGLONASSPRN->setMinimumHeight(130); //124
        ui->pageGEOPRN->setMinimumHeight(161); //155
        ui->pageQZSSPRN->setMinimumHeight(74); //62
        ui->pageIRNSSPRN->setMinimumHeight(74); //62
    #endif

    //Set global variables
    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 0;
    WriteAllParameters=0;
    TitleColor = "#d3d7cf";
    ISCBTrickColor = "#d3d6cf";

    gnssUnSelected.setStyle(Qt::SolidPattern); gnssUnSelected.setColor(QColor(RedColor));
    gnssSelected.setStyle(Qt::SolidPattern); gnssSelected.setColor(QColor(GreenColor));
    ISCBTitleSelected.setStyle(Qt::SolidPattern); ISCBTitleSelected.setColor(QColor(TitleColor));
    ISCBTitleTrick.setStyle(Qt::SolidPattern); ISCBTitleTrick.setColor(QColor(ISCBTrickColor));
    ISCBGNSSSelected.setStyle(Qt::NoBrush);

    // Set Navigation Message Type Table
    connect(ui->tableWidgetNavMessageTypeGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetNavMessageTypeIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetNavMessageTypeIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");

    connect(ui->tableWidgetCompareNavMessageTypeGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGPS_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGPS_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGalileo_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGLONASS_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeBDS_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeBDS_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeGEO_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeGEO_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeQZSS_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetCompareNavMessageTypeIRNSS_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");

    connect(ui->tableWidgetShowNavMessageTypeGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(ui->tableWidgetShowNavMessageTypeIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(navMessageTypesItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetShowNavMessageTypeIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");

    // Set overlook for tableWidgetRefGNSSClock
    connect(ui->tableWidgetRefGNSSClock,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(refClockItem_doubleClicked(QTableWidgetItem *)));
    ui->tableWidgetRefGNSSClock->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    ui->tableWidgetRefGNSSClock->setColumnWidth(0,95);
    ui->tableWidgetRefGNSSClock->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // Set overlook for tableWidgetISCB
    connect(ui->tableWidgetISCB,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(ISCBItem_textChanged(QTableWidgetItem *)));
    ui->tableWidgetISCB->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    ui->tableWidgetISCB->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    abort=0;
    SBASmaritime=0;

    // Set the text size depending on the Operating System
    this->setCorrectSizes();

    // Current version and revision
    version = 6.0;
    revision = 0;

    // Set the window title
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
    //ui->tabInput->setStyleSheet("#tabInput{background-color: rgb(239, 235, 231);}#tabInput:tab:selected{background: rgb(239, 235, 231);}");
    //ui->tabPreprocess->setStyleSheet("#tabPreprocess{background-color: rgb(239, 235, 231);}");
    //ui->tabModelling->setStyleSheet("#tabModelling{background-color: rgb(239, 235, 231);}");
    //ui->tabFilter->setStyleSheet("#tabFilter{background-color: rgb(239, 235, 231);}");
    //ui->tabOutput->setStyleSheet("#tabOutput{background-color: rgb(239, 235, 231);}");

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
    myGroupTemplate->addAction(ui->actionSBAS_1F);
    myGroupTemplate->addAction(ui->actionSBAS_DFMC);
    myGroupTemplate->addAction(ui->actionDGNSS);

    // Expand the tabs to the window width
    ui->tabWidget->installEventFilter(new ResizeFilter(ui->tabWidget));

    // Define Scroll bar for Input, Modelling, Filter and Output, and fix colors on Scroll Area tab
    ui->scrollAreaInput->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaWidgetContentsInput->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");
    ui->scrollAreaModelling->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar:horizontal{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaModellingOptions->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar:horizontal{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaWidgetContentsModelling1->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");
    ui->scrollAreaWidgetContentsModelling2->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");
    ui->scrollAreaFilter->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaWidgetContentsFilter->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");
    ui->scrollAreaOutput->setStyleSheet(QString::fromUtf8("QScrollBar:vertical{border: 1px solid #999999; color: white; width: 10px; margin: 0px 0px 0px 0px; border-radius: 4px;}QScrollBar::handle:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); min-height: 0px; border-radius: 4px;}QScrollBar::add-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: px; subcontrol-position: bottom; subcontrol-origin: margin; border-radius: 4px;}QScrollBar::sub-line:vertical{background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130)); height: 0px; subcontrol-position: top; subcontrol-origin: margin; border-radius: 4px;}QScrollArea{background-color:transparent;}"));
    ui->scrollAreaWidgetContentsOutput->setStyleSheet("#scrollAreaWidgetContentsModelling{background-color:transparent;}");

    // Callback instance to control all tooltips (active/inactive and color)
    qApp->installEventFilter(this);

    // Set StyleSheet
    #if (defined Q_OS_WIN32)
        QFile qss(":/data/WinStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #elif (defined Q_OS_MAC)
        QFile qss(":/data/MacStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #else
        QFile qss(":/data/LinuxStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #endif

    //Set Analysis conditons comboBox tooltips for each item and each plot
    this->set_conditionsComboBoxPlot1_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot2_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot3_OutputMessagesTooltips();
    this->set_conditionsComboBoxPlot4_OutputMessagesTooltips();

    ///INPUT TAB CONTEXT MENUS
    //Set right click menu for Input RINEX observation file label
    ui->labelInputObservationFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputObservationFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexObsFileMenu);
    //Set right click menu for Input Sat. ANTEX file checkbox
    ui->checkBoxSatAntex->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxSatAntex,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxInputSatANTEXFileMenu);
    //Set right click menu for Input Rec. ANTEX file checkbox
    ui->checkBoxRecAntex->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxRecAntex,&QCheckBox::customContextMenuRequested,this,&gLAB_GUI::checkBoxInputRecANTEXFileMenu);
    //Set right click menu for Input RINEX navigation file 1 label
    ui->labelInputRinexNavFile1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile1Menu);
    //Set right click menu for Input RINEX navigation file 2 label
    ui->labelInputRinexNavFile2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile2Menu);
    //Set right click menu for Input RINEX navigation file 3 label
    ui->labelInputRinexNavFile3->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile3,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile3Menu);
    //Set right click menu for Input RINEX navigation file 4 label
    ui->labelInputRinexNavFile4->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile4,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile4Menu);
    //Set right click menu for Input RINEX navigation file 5 label
    ui->labelInputRinexNavFile5->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile5,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile5Menu);
    //Set right click menu for Input RINEX navigation file 6 label
    ui->labelInputRinexNavFile6->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile6,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile6Menu);
    //Set right click menu for Input RINEX navigation file 7 label
    ui->labelInputRinexNavFile7->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputRinexNavFile7,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputRinexNavFile7Menu);
    //Set right click menu for Input SP3 Orbits & clocks file label
    ui->labelInputSP3OrbitsClocksFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSP3OrbitsClocksFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSP3OrbitsClocksFileMenu);
    //Set right click menu for Input SP3 Orbits file label
    ui->labelInputSP3OrbitsFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSP3OrbitsFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSP3OrbitsFileMenu);
    //Set right click menu for Input clocks file label
    ui->labelInputClkFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputClkFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputClocksFileMenu);
    //Set right click menu for Input RINEX GLONASS navigation file checkbox (SP3 only tab)
    ui->checkBoxRinexNavFileGLO1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxRinexNavFileGLO1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::checkBoxRinexNavFileGLO1Menu);
    //Set right click menu for Input RINEX navigation file for health flags checkbox (SP3 only tab)
    ui->checkBoxRinexNavFileHealth1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxRinexNavFileHealth1,&QLabel::customContextMenuRequested,this,&gLAB_GUI::checkBoxRinexNavFileHealth1Menu);
    //Set right click menu for Input RINEX GLONASS navigation file checkbox (SP3 and CLK tab)
    ui->checkBoxRinexNavFileGLO2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxRinexNavFileGLO2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::checkBoxRinexNavFileGLO2Menu);
    //Set right click menu for Input RINEX navigation file for health flags checkbox (SP3 and CLK tab)
    ui->checkBoxRinexNavFileHealth2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->checkBoxRinexNavFileHealth2,&QLabel::customContextMenuRequested,this,&gLAB_GUI::checkBoxRinexNavFileHealth2Menu);
    //Set right click menu for Input SINEX file label
    ui->labelInputSinexFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelInputSinexFile,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSINEXFileMenu);
    //Set right click menu for Input SBAS file label
    ui->comboBoxSbasInput->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->comboBoxSbasInput,&QLabel::customContextMenuRequested,this,&gLAB_GUI::labelInputSBASFileMenu);
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
    //Init variable with pointers to CheckBoxs GNSS widget pointers
    this->InitCheckBoxGNSSPointers();
    //Init variable with pointers to CheckBoxs function pointers
    this->InitCheckBoxGNSSFuncPointers();
    //Init variable with pointers to pushButton GNSS Measurements _clicked() functions
    this->InitPushButtonGNSSMeasurementFuncPointers();
    //Init GNSS freq & meas pointers
    this->InitGNSSFreqMeasComboBoxPointers();
    //Init Smooth pointers
    this->InitSmoothComboBoxPointers();
    //Init stdDev pointers
    this->InitGNSSStdDevPointers();
    //Init code and phase pointers
    this->InitGNSSFreqLabels();


    //initialize pop-windows
    gLABToolTipWin = new gLAB_ToolTip(this);

    SnrAdvancedMinWin = new GNSS_SNR_Advanced(this,0);
    // Remove question mark, minimize and maximize buttons from the title bar
    SnrAdvancedMinWin->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    SnrAdvancedMaxWin = new GNSS_SNR_Advanced(this,1);
    // Remove question mark, minimize and maximize buttons from the title bar
    SnrAdvancedMaxWin->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    CSAdvancedSF = new GNSS_CS_SF_Advanced(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    CSAdvancedSF->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    CSAdvancedMW = new GNSS_CS_MW_Advanced(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    CSAdvancedMW->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    CSAdvancedLI = new GNSS_CS_LI_Advanced(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    CSAdvancedLI->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    CSAdvancedIGF = new GNSS_CS_IGF_Advanced(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    CSAdvancedIGF->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    APCAdvanced = new GNSS_Antenna_Advanced(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    APCAdvanced->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    SBASOBADSet = new GNSS_SBAS_OBAD_Set(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    SBASOBADSet->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    FreqMeasGNSS = new GNSS_FreqMeas_Order(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    FreqMeasGNSS->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    MeasSelectGNSS = new GNSS_Meas_Select(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    MeasSelectGNSS->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

    MultiThread = new GNSS_Multi_Threading(this);
    // Remove question mark, minimize and maximize buttons from the title bar
    MultiThread->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint  & ~Qt::WindowContextHelpButtonHint);

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
    auto lSBASDFREIN = new QIntValidator(0, 14, this);
    lSBASDFREIN->setLocale(qlocale); // lineEdit validation for orbit and clock interpolation
    auto lsignalflighttime = new QDoubleValidator(0, 0.3,10, this);
    ldouble->setLocale(qlocale); // lineEdit validation for coordinates XYZ

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
    ui->lineEditSFiniStd->setValidator(ldoublePositive);
    ui->lineEditSFwindow->setValidator(lseconds);
    ui->lineEditSFkFactor->setValidator(ldoublePositive);
    ui->lineEditSFnSample->setValidator(lintPositive);
    ui->lineEditSFConsCheckValue->setValidator(ldoublePositive);
    this->on_radioButtonSFAutoSelection_clicked();
    ui->lineEditIntialStdDevMW->setValidator(ldoublePositive);
    ui->lineEditMWminStd->setValidator(ldoublePositive);
    ui->lineEditMWwindow->setValidator(lseconds);
    ui->lineEditMWkFactor->setValidator(ldoublePositive);
    ui->lineEditMWnSample->setValidator(lintPositive);
    this->on_radioButtonMWAutoSelection_clicked();
    ui->lineEditLImaxJumpThreshold->setValidator(ldoublePositive);
    ui->lineEditLImaxThreshold->setValidator(ldoublePositive);
    ui->lineEditLItimeConstant->setValidator(ldoublePositive);
    ui->lineEditLInSamples->setValidator(lintPositive);
    this->on_radioButtonLIAutoSelection_clicked();
    ui->lineEditIGFmaxJumpThreshold->setValidator(ldoublePositive);
    ui->lineEditIGFmaxThreshold->setValidator(ldoublePositive);
    ui->lineEditIGFtimeConstant->setValidator(ldoublePositive);
    ui->lineEditIGFnSamples->setValidator(lintPositive);
    this->on_radioButtonIGFAutoSelection_clicked();
    ui->lineEditUserDefinedSNRMin->setValidator(lSNR);
    ui->lineEditUserDefinedSNRMax->setValidator(lSNR);

    // MODELLING defaults
    ui->lineEditNavFreshTime->setValidator(lintInfinity);
    ui->lineEditOrbitInterpolationDegree->setValidator(linterpolation);
    ui->lineEditClockInterpolationDegree->setValidator(linterpolation);
    ui->lineEditOrbitConsecutiveGaps->setValidator(lseconds);
    ui->lineEditClockConsecutiveGaps->setValidator(lseconds);
    ui->lineEditOrbitMaxGaps->setValidator(lseconds);
    ui->lineEditClockMaxGaps->setValidator(lseconds);
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
    ui->lineEditSBASSignalFlightTime->setValidator(lsignalflighttime);
    ui->lineEditDoNotUseForSafetyAppPA_DFMC->setValidator(lintInfinity);
    ui->lineEditDoNotUseForSafetyAppNPA_DFMC->setValidator(lintInfinity);
    ui->lineEditSatMaskPA_DFMC->setValidator(lseconds);
    ui->lineEditSatMaskNPA_DFMC->setValidator(lseconds);
    ui->lineEditClkCovarianceMatrixPA_DFMC->setValidator(lseconds);
    ui->lineEditClkCovarianceMatrixNPA_DFMC->setValidator(lseconds);
    ui->lineEditIntegrityPA_DFMC->setValidator(lseconds);
    ui->lineEditIntegrityNPA_DFMC->setValidator(lseconds);
    ui->lineEditOBADParDFREITablePA_DFMC->setValidator(lseconds);
    ui->lineEditOBADParDFREITableNPA_DFMC->setValidator(lseconds);
    ui->lineEditSatCovarianceMatrixPA_DFMC->setValidator(lseconds);
    ui->lineEditSatCovarianceMatrixNPA_DFMC->setValidator(lseconds);
    ui->lineEditTimeOffsetsPA_DFMC->setValidator(lseconds);
    ui->lineEditTimeOffsetsNPA_DFMC->setValidator(lseconds);
    ui->lineEditSBASSatAlmanacsPA_DFMC->setValidator(lseconds);
    ui->lineEditSBASSatAlmanacsNPA_DFMC->setValidator(lseconds);
    ui->lineEditCerOBADParameterMT37->setValidator(ldouble);
    ui->lineEditCcovarianceOBADParameterMT37->setValidator(ldouble);
    ui->lineEditSetIcorrOBADParameterMT37->setValidator(ldouble);
    ui->lineEditSetCcorrOBADParameterMT37->setValidator(ldouble);
    ui->lineEditSetRcorrOBADParameterMT37->setValidator(ldouble);
    ui->lineEditSetDFREIValue->setValidator(ldouble);
    ui->lineEditSetValueDFREI0->setValidator(ldouble);
    ui->lineEditSetValueDFREI1->setValidator(ldouble);
    ui->lineEditSetValueDFREI2->setValidator(ldouble);
    ui->lineEditSetValueDFREI3->setValidator(ldouble);
    ui->lineEditSetValueDFREI4->setValidator(ldouble);
    ui->lineEditSetValueDFREI5->setValidator(ldouble);
    ui->lineEditSetValueDFREI6->setValidator(ldouble);
    ui->lineEditSetValueDFREI7->setValidator(ldouble);
    ui->lineEditSetValueDFREI8->setValidator(ldouble);
    ui->lineEditSetValueDFREI9->setValidator(ldouble);
    ui->lineEditSetValueDFREI10->setValidator(ldouble);
    ui->lineEditSetValueDFREI11->setValidator(ldouble);
    ui->lineEditSetValueDFREI12->setValidator(ldouble);
    ui->lineEditSetValueDFREI13->setValidator(ldouble);
    ui->lineEditSetValueDFREI14->setValidator(ldouble);
    ui->lineEditSetDeltaRcorrParameter->setValidator(ldouble);
    ui->lineEditSetDeltaDFREFactor->setValidator(ldouble);
    ui->lineEditSetUIRESigmaValue->setValidator(ldouble);
    ui->lineEditSetTroposphericSigma->setValidator(ldouble);
    ui->lineEditSigmaMultiPathFactor->setValidator(ldouble);
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
    ui->lineEditStdDevCodeAGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeABDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBBDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCBDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeABDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBBDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCBDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeABDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBBDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCBDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeAIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeBIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevCodeCIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGPS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGPS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGPS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGalileo_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGalileo_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGalileo_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGLONASS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGLONASS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGLONASS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGEO_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGEO_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCGEO_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseABDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBBDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCBDS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseABDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBBDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCBDS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseABDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBBDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCBDS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCQZSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCQZSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCQZSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCIRNSS_1->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCIRNSS_2->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseAIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseBIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditStdDevPhaseCIRNSS_3->setValidator(ldoublePositive);
    ui->lineEditPhiCoordinates->setValidator(ldoublePositive);
    ui->lineEditPhiClock->setValidator(ldoublePositive);
    ui->lineEditPhiISCB->setValidator(ldoublePositive);
    ui->lineEditPhiTropo->setValidator(ldoublePositive);
    ui->lineEditPhiPhaseAmbiguities->setValidator(ldoublePositive);
    ui->lineEditQcoordinates->setValidator(ldoublePositive);
    ui->lineEditQclock->setValidator(ldoublePositive);
    ui->lineEditQISCB->setValidator(ldoublePositive);
    ui->lineEditQtropo->setValidator(ldoublePositive);
    ui->lineEditQphaseAmbiguities->setValidator(ldoublePositive);
    ui->lineEditPoCoordinates->setValidator(ldoublePositive);
    ui->lineEditPoClock->setValidator(ldoublePositive);
    ui->lineEditPoISCB->setValidator(ldoublePositive);
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
    ui->lineEditStfdESAMaxSatCombinations->setValidator(lintInfinity);
    ui->lineEditHorizontalIntegrityRatio->setValidator(ldoublePositive);
    ui->lineEditVerticalIntegrityRatio->setValidator(ldoublePositive);
    ui->lineEditHorizontalAlarmLimitSBAS->setValidator(ldoublePositive);
    ui->lineEditVerticalAlarmLimitSBAS->setValidator(ldoublePositive);
    ui->lineEditPercentileValue->setValidator(lintPercentile);
    ui->lineEditSlidingWindowSBAS->setValidator(lintPositive);
    ui->lineEditMaritimeWindowSBAS->setValidator(lintPositive);
    ui->lineEditSummaryConvergenceFormalThresHor->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergenceFormalThresVer->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergenceFormalThres3D->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergenceFormalTimeThresHor->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergenceFormalTimeThresVer->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergenceFormalTimeThres3D->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionThresHor->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionThresVer->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionThres3D->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionTimeThresHor->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionTimeThresVer->setValidator(ldoublePositive);
    ui->lineEditSummaryConvergencePositionTimeThres3D->setValidator(ldoublePositive);

    // ANALYSIS defaults
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotXmin->setValidator(ldouble);
    ui->lineEditPlotXmax->setValidator(ldouble);
    ui->lineEditPlotYmin->setValidator(ldouble);
    ui->lineEditPlotYmax->setValidator(ldouble);
    //Column number has no validator due to mathematical formulas can be given
    //ui->lineEditPlot1Xcolumn->setValidator(lseconds);
    //ui->lineEditPlot1Ycolumn->setValidator(lseconds);
    //ui->lineEditPlot2Xcolumn->setValidator(lseconds);
    //ui->lineEditPlot2Ycolumn->setValidator(lseconds);
    //ui->lineEditPlot3Xcolumn->setValidator(lseconds);
    //ui->lineEditPlot3Ycolumn->setValidator(lseconds);
    //ui->lineEditPlot4Xcolumn->setValidator(lseconds);
    //ui->lineEditPlot4Ycolumn->setValidator(lseconds);
    ui->lineEditXTickNum->setValidator(ldoublePositive);
    ui->lineEditYTickNum->setValidator(ldoublePositive);

    // CONVERTER Defaults
    setInitialConverterValues();

    //Compare Orbits Defaults
    ui->lineEditCompareNavFreshTime->setValidator(lintInfinity);
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
    ui->lineEditShowNavFreshTime->setValidator(lintInfinity);
    ui->lineEditDecimationShowOrbit->setValidator(ldoublePositiveDec);
    ui->lineEditOrbitInterpolationDegreeShowOrbit->setValidator(linterpolation);
    ui->lineEditClockInterpolationDegreeShowOrbit->setValidator(linterpolation);
    ui->lineEditOrbitConsecutiveGapsShowOrbit->setValidator(lseconds);
    ui->lineEditClockConsecutiveGapsShowOrbit->setValidator(lseconds);
    ui->lineEditOrbitMaxGapsShowOrbit->setValidator(lseconds);
    ui->lineEditClockMaxGapsShowOrbit->setValidator(lseconds);
    ui->checkBoxPrintSatpvtShowOrbit->setToolTip(ui->checkBoxPrintSatpvt->toolTip());
    ui->lineEditEleAziSpecifyX->setValidator(ldouble);
    ui->lineEditEleAziSpecifyY->setValidator(ldouble);
    ui->lineEditEleAziSpecifyZ->setValidator(ldouble);
    ui->lineEditEleAziSpecifyLon->setValidator(lLongitude);
    ui->lineEditEleAziSpecifyLat->setValidator(lLatitude);
    ui->lineEditEleAziSpecifyHeight->setValidator(ldouble);
    setInitialShowOrbitValues();



    //Add User Error defaults
    setInitialAddUserErrorValues();
    ui->checkBoxPrintUserErrorAddError->setToolTip(ui->checkBoxPrintUsererror->toolTip());

    //DCB ISC
    setInitialDCBISC();

    //Set OS specific sizes
    this->setOSspecificObjectSizes();
}


void gLAB_GUI::setInitialPositioningValues() {

    QString OutputPath;

    v5Message=0;

    //Hide progress bar
    ui->stackedWidgetMainButtons->setCurrentIndex(0);
    // Set first SBAS modelling terms
    this->setSBASmodellingDefaults();
    // Set as default the SPP template
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
    ui->lineEditSatAntex->setText("");
    ui->lineEditRecAntex->setText("");
    ui->pushButtonAddRinexNav->setEnabled(true);
    ui->pushButtonDelRinexNav->setEnabled(false);
    ui->lineEditRinexNav1->setText("");
    ui->frameInputRinexNavFile2->setHidden(true);
    ui->lineEditRinexNav2->setText("");
    ui->frameInputRinexNavFile3->setHidden(true);
    ui->lineEditRinexNav3->setText("");
    ui->frameInputRinexNavFile4->setHidden(true);
    ui->lineEditRinexNav4->setText("");
    ui->frameInputRinexNavFile5->setHidden(true);
    ui->lineEditRinexNav5->setText("");
    ui->frameInputRinexNavFile6->setHidden(true);
    ui->lineEditRinexNav6->setText("");
    ui->frameInputRinexNavFile7->setHidden(true);
    ui->lineEditRinexNav7->setText("");
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
    this->on_radioButtonRtcmRinexRover_clicked();
    this->on_radioButtonRtcm_clicked();
    this->on_radioButtonCalculateSpecifyCartesian_clicked();
    this->on_radioButtonCalculateEarthCentre_clicked();
    this->on_checkBoxReferencePositionFileCalculate_clicked(false);
    this->on_radioButtonSpecifyUserCartesian_clicked();
    this->on_radioButtonSpecifyUserDefined_clicked();
    this->on_radioButtonRinex_clicked();

    // PREPROCESS defaults
    this->on_radioButtonIGFTwoIonoFree_clicked();

    this->on_checkBoxSNRMinAdvancedMode_clicked(false);
    this->on_checkBoxSNRMaxAdvancedMode_clicked(false);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();

    this->on_checkBoxGalileo_clicked(true);// Enable all Galileo satellites
    this->on_checkBoxGLONASS_clicked(true);// Enable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxBDS_clicked(true);// Enable all BDS satellites
    this->on_checkBoxQZSS_clicked(true);// Enable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(true);// Enable all IRNSS satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    ui->lineEditUserDefinedSNRMin->setText("");
    ui->lineEditUserDefinedSNRMax->setText("");


    this->CSAdvancedIGF->changePushButtonGEO(false); //GEO does not have triple frequency, it cannot use IGF
    this->CSAdvancedIGF->changePushButtonIRNSS(false); //IRNSS does not have triple frequency, it cannot use IGF

    // MODELLING defaults
    ui->dateTimeEditStartTimeSummary->setDate(date);

    // FILTER defaults
    this->initGNSSMeasAll();
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    this->on_groupBoxRefGNSSClock_clicked(false);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);

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
    ui->radioButtonNanosecondsUnitOutputClock->setChecked(false);
    ui->radioButtonMetresUnitOutputClock->setChecked(true);
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

    v5Message=0;

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

    v5Message=0;
    QDate date = QDate(1979, 12, 31);
    ui->StartTimeCompareOrbits->setDate(date);
    ui->EndTimeCompareOrbits->setDate(date);
    this->on_checkBoxStartTimeCompareOrbits_clicked(false);
    this->on_checkBoxEndTimeCompareOrbits_clicked(false);
    this->on_checkBoxAntexCompareOrbitsFile2_clicked(false);
    this->on_radioButtonOrbitNavCompareFile1_clicked();
    this->on_radioButtonOrbitNavCompareFile2_clicked();
    ui->radioButtonOrbitNextDayCompare->setChecked(true);
    ui->radioButtonClockNextDayCompare->setChecked(true);
    this->on_groupBoxConcatenedPreciseFilesCompare_clicked(false);
    ui->lineEditDecimationCompareOrbit->setText("300");
    ui->lineEditCompareNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
    ui->lineEditOrbitInterpolationDegreeCompare->setText("10");
    ui->lineEditClockInterpolationDegreeCompare->setText("1");
    ui->lineEditOrbitConsecutiveGapsCompare->setText("8");
    ui->lineEditClockConsecutiveGapsCompare->setText("2");
    ui->lineEditOrbitMaxGapsCompare->setText("16");
    ui->lineEditClockMaxGapsCompare->setText("4");
    ui->checkBoxSatClockOffsetCompare->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(true);
    ui->checkBoxDiscardEclipseCompare->setChecked(false);
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
    this->on_pushButtonOrbitsCompareMessagesAll_clicked();
    ui->radioButtonNanosecondsUnitOutputClockSATDIFF->setChecked(false);
    ui->radioButtonMetresUnitOutputClockSATDIFF->setChecked(true);
}

void gLAB_GUI::setInitialShowOrbitValues() {

    v5Message=0;
    QDate date = QDate(1979, 12, 31);
    ui->StartTimeShowOrbits->setDate(date);
    ui->EndTimeShowOrbits->setDate(date);
    this->on_checkBoxStartTimeShowOrbits_clicked(false);
    this->on_checkBoxEndTimeShowOrbits_clicked(false);
    this->on_checkBoxAntexShowOrbitFile_clicked(false);
    this->on_radioButtonOrbitNavShowOrbitFile_clicked();
    ui->radioButtonOrbitNextDayShowOrbit->setChecked(true);
    ui->radioButtonClockNextDayShowOrbit->setChecked(true);
    this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(false);
    ui->lineEditDecimationShowOrbit->setText("300");
    ui->lineEditShowNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
    ui->lineEditOrbitInterpolationDegreeShowOrbit->setText("10");
    ui->lineEditClockInterpolationDegreeShowOrbit->setText("1");
    ui->lineEditOrbitConsecutiveGapsShowOrbit->setText("8");
    ui->lineEditClockConsecutiveGapsShowOrbit->setText("2");
    ui->lineEditOrbitMaxGapsShowOrbit->setText("16");
    ui->lineEditClockMaxGapsShowOrbit->setText("4");
    ui->checkBoxSatClockOffsetShowOrbit->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(true);
    ui->lineEditNavShowOrbitFile->setText("");
    ui->lineEditPreciseFilesShowOrbitSP3File->setText("");
    ui->lineEditPreciseFilesShowOrbitOrbFile->setText("");
    ui->lineEditPreciseFilesShowOrbitClkFile->setText("");
    ui->lineEditAntexShowOrbitFile->setText("");
    ui->lineEditOutputFileShowOrbit->setText("");
    ui->radioButtonSatVelECEFShowOrbit->setChecked(true);
    this->on_groupBoxEleAziSpecify_clicked(false);
    this->on_radioButtonEleAziSpecifyUserCartesian_clicked();
    ui->lineEditEleAziSpecifyX->setText("");
    ui->lineEditEleAziSpecifyY->setText("");
    ui->lineEditEleAziSpecifyZ->setText("");
    ui->lineEditEleAziSpecifyLon->setText("");
    ui->lineEditEleAziSpecifyLat->setText("");
    ui->lineEditEleAziSpecifyHeight->setText("");
    this->on_pushButtonShowOrbitMessagesAll_clicked();
    ui->radioButtonNanosecondsUnitOutputClockSATPVT->setChecked(false);
    ui->radioButtonMetresUnitOutputClockSATPVT->setChecked(true);

}

void gLAB_GUI::setInitialAddUserErrorValues() {

    v5Message=0;
    this->on_groupBoxRinexNavFileGLOAddError_clicked(false);
    ui->lineEditRinexObsAddError->setText("");
    ui->lineEditUserAddedErrorAddError->setText("");
    ui->lineEditRinexNavFileGLOAddError->setText("");
    ui->lineEditRinexOutputFileAddError->setText("");
    ui->lineEditOutputFileAddError->setText("");
    ui->checkBoxPrintInfoAddError->setChecked(true);
    ui->checkBoxPrintUserErrorAddError->setChecked(true);
}

//Set OS specific object sizes for alignments. This function is meant to put all global specific changes so is easy to track them
void gLAB_GUI::setOSspecificObjectSizes() {

    //Check also function "setWeightTypeValues" in filter.c, where more OS sizes are also set (not set here due to it requires parameters)

    #ifdef Q_OS_WIN32
        //Manually set size of label labelStfdESAPlotFile (so it is aligned with label labelStfdESADataFile) in Windows
        ui->labelStfdESAPlotFile->setMinimumWidth(114);

        //Manually set size of labels in User added error mode so all lineEdits are aligned (in Windows text is smaller)
        ui->labelAddErrorObservationFile->setMinimumWidth(115);
        ui->labelAddErrorUserAddedErrorFile->setMinimumWidth(115);
        ui->labelAddErrorRinexOutputFile->setMinimumWidth(115);
        ui->labelAddErrorOutputFile->setMinimumWidth(115);

        //Manually set the maximum size of the frame containing output meas, clock unit and MEAS measurements (smaller in Windows)
        ui->frameOuputMessagesMeasClockUnits->setMinimumWidth(272);
        ui->frameOuputMessagesMeasClockUnits->setMaximumWidth(272);
    #endif

    #ifdef Q_OS_LINUX
        //Set size for groupBoxMeasurementConfigurationAndNoise in Linux
        ui->groupBoxMeasurementConfigurationAndNoise->setMinimumWidth(830);
        //Set size for groupBox for elevation and azimuth
        ui->groupBoxEleAziSpecify->setMinimumWidth(280);

        //Manually set size for code labels in Windows labels
        for(int iGNSS=0;iGNSS<MAX_GNSS;iGNSS++) {
            for(int icomb=0;icomb<MAXMEASTOFILTER;icomb++) {
                LabelCodePhaseFreq[iGNSS][icomb][CODEARRAYPOS]->setMinimumWidth(71);
            }
        }
    #endif

    #if defined(Q_OS_MAC)
        //Manually set size for code labels in filter tab
        for(int iGNSS=0;iGNSS<MAX_GNSS;iGNSS++) {
            for(int icomb=0;icomb<MAXMEASTOFILTER;icomb++) {
                LabelCodePhaseFreq[iGNSS][icomb][CODEARRAYPOS]->setMinimumWidth(72);
            }
        }
        //Manually set size for "constant" and "Static" radiobuttons in filter tab
        ui->radioButtonStatic->setMinimumWidth(80);
        ui->radioButtonStatic->setMaximumWidth(80);
        ui->radioButtonConstantClock->setMinimumWidth(80);
        ui->radioButtonConstantClock->setMaximumWidth(80);
        ui->radioButtonConstantISCB->setMinimumWidth(80);
        ui->radioButtonConstantISCB->setMaximumWidth(80);
    #endif        

}

// Destructor of the GUI
gLAB_GUI::~gLAB_GUI() {
    delete ui;
}

// Destructor of Resizefilter
ResizeFilter::~ResizeFilter() {
    //Defined empty to avoid warning "'ResizeFilter' out-of-line virtual method definitions: its vtable will be emitted in every translation unit" in glab_gui.h
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
        if (lastLine->size()>2) {
            //If first or second character is "\n", take it out
            if (lastLine->at(0)==newline) {
                lastLine->remove(0, 1);
            } else if (lastLine->at(1)==newline) {
                 lastLine->remove(0, 2);
            }
        } else {
            //Empty file
            *lastLine = "---";
        }
        //Close file
        outputfile.close();
    } else {
        //Error opening output file
        *lastLine = "---";
    }

    return;
}

//Function to put all unnecessary arguments in warning string
void gLAB_GUI::extraArgumentsToWarningStr(int startPos, QString *warningString, QString option, QStringList ParametersList) {
    int i;
    if (ParametersList.count()>startPos) {
        *warningString += "Parameter '" + option + "' has the following extra arguments (which have been omitted):";
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
        *errorString += FileDescription + " file path '" + userInput + "' is not valid.\n";
    } else {
        #ifdef Q_OS_WIN32
            if (userInput.contains(QRegularExpression("^:[a-zA-Z0-9]{0,}"))==true ||   userInput.contains(QRegularExpression("^[A-Z]{1}:[a-zA-Z0-9]{1,}"))==true || userInput.contains(QRegularExpression("^\\\\"))==true || userInput.contains(QRegularExpression("^[a-z]:"))==true ) {
                 *errorString += FileDescription + " file path '" + userInput + "' is not valid.\n";
                return;
            }
            if ( userInput.contains(QRegularExpression("^[\"']{0,1}[A-Z]{1}:\\\\"))==false ) {
        #else
            if (userInput.startsWith("/")==false) {
        #endif
                *warningString += FileDescription + " file path '" + userInput + "' is not absolute.\n";
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
    //non-ascii characters, gLAB will also handle them and vicerversa)
    (void)str;//To avoid unsed parameter warning
    return 0; //remove this return to enable again this function and uncomment following code
    /*Uncomment following code and comment previous return to re-enable this function
    int i;
    for(i=0; i<str.size(); i++) {
        if(str.at(i).unicode() > 127) return 1;
    }
    return 0;
    */
}


// Modelling Defaults
void gLAB_GUI::setModellingDefaults() {
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->lineEditNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
    ui->lineEditOrbitInterpolationDegree->setText("10");
    ui->lineEditClockInterpolationDegree->setText("1");
    ui->lineEditOrbitConsecutiveGaps->setText("8");
    ui->lineEditClockConsecutiveGaps->setText("2");
    ui->lineEditOrbitMaxGaps->setText("16");
    ui->lineEditClockMaxGaps->setText("4");
    ui->lineEditARPnorth->setText("0");
    ui->lineEditARPeast->setText("0");
    ui->lineEditARPup->setText("0");
    this->on_groupBoxConcatenedPreciseFiles_clicked(false);
    ui->tableWidgetNavMessageTypeGPS->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeGalileo->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeGLONASS->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeGEO->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeBDS->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeQZSS->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->tableWidgetNavMessageTypeIRNSS->setDisabled(false); //Reenable the navigation table widget in case it was disabled by SBAS or DGNSS
    ui->radioButtonOrbitCurrentDay->setChecked(false);
    ui->radioButtonOrbitNextDay->setChecked(true);
    ui->radioButtonClockCurrentDay->setChecked(false);
    ui->radioButtonClockNextDay->setChecked(true);
    ui->checkBoxStrictRadome->setChecked(false);
    APCAdvanced->setAPCdefaults();
}

// Filter Defaults
void gLAB_GUI::setFilterDefaults() {

    this->InitFilterWeights();
    ui->lineEditPhiCoordinates->setText("1");
    ui->lineEditPhiClock->setText("0");
    ui->lineEditPhiISCB->setText("0");
    ui->lineEditPhiTropo->setText("1");
    ui->lineEditPhiPhaseAmbiguities->setText("1");
    ui->lineEditQcoordinates->setText("0");
    ui->lineEditQclock->setText("9e10");
    ui->lineEditQISCB->setText("9e10");
    ui->lineEditQtropo->setText("1e-4");
    ui->lineEditQphaseAmbiguities->setText("0");
    ui->lineEditPoCoordinates->setText("1e8");
    ui->lineEditPoClock->setText("9e10");
    ui->lineEditPoISCB->setText("9e10");
    ui->lineEditPoTropo->setText("0.25");
    ui->lineEditPoPhaseAmbiguities->setText("400");
    this->on_radioButtonWhiteNoiseClock_clicked();
    this->on_radioButtonWhiteNoiseISCB_clicked();
    ui->comboBoxPoClockUnit->setCurrentIndex(0);
    ui->comboBoxPoISCBUnit->setCurrentIndex(0);
    ui->comboBoxQClockUnitNormal->setCurrentIndex(0);
    ui->comboBoxQISCBUnitNormal->setCurrentIndex(0);
    ui->lineEditMaxHDOP->setText("4");
    ui->lineEditMaxPDOP->setText("6");
    ui->lineEditMaxGDOP->setText("30");
    ui->lineEditPrefitOutliers->setText("40");
    this->on_groupBoxRefGNSSClock_clicked(false);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);
    this->initGNSSMeasAll();
    this->InitRefGNSSClock();
}

// SBAS Defaults
void gLAB_GUI::setSBASmodellingDefaults() {
    ui->frameOptionButtonNavTypes->setHidden(true); //Hide buttons for moving navigation message types and default button
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
    ui->lineEditSigmaMultiPathFactor->setText("2.59");
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
    ui->lineEditSBASSignalFlightTime->setText("0.12");
    ui->lineEditDoNotUseForSafetyAppPA_DFMC->setText("9999999");
    ui->lineEditDoNotUseForSafetyAppNPA_DFMC->setText("9999999");
    ui->lineEditSatMaskPA_DFMC->setText("600");
    ui->lineEditSatMaskNPA_DFMC->setText("600");
    ui->lineEditClkCovarianceMatrixPA_DFMC->setText("");
    ui->lineEditClkCovarianceMatrixNPA_DFMC->setText("");
    ui->lineEditIntegrityPA_DFMC->setText("12");
    ui->lineEditIntegrityNPA_DFMC->setText("18");
    ui->lineEditOBADParDFREITablePA_DFMC->setText("240");
    ui->lineEditOBADParDFREITableNPA_DFMC->setText("360");
    ui->lineEditSatCovarianceMatrixPA_DFMC->setText("");
    ui->lineEditSatCovarianceMatrixNPA_DFMC->setText("");
    ui->lineEditTimeOffsetsPA_DFMC->setText("86400");
    ui->lineEditTimeOffsetsNPA_DFMC->setText("86400");
    ui->lineEditSBASSatAlmanacsPA_DFMC->setText("240");
    ui->lineEditSBASSatAlmanacsNPA_DFMC->setText("360");
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
    this->on_checkBoxSigmaMultiPathFactor_clicked(false);
    ui->checkBoxParseAlarmSBAS1F->setChecked(false);
    ui->checkBoxParseAlarmSBASDFMC->setChecked(false);
    ui->checkBoxIgnoreAllAlarm->setChecked(false);
    ui->checkBoxAllowMixedGEOdata->setChecked(false);
    ui->checkBoxAllowUseNoneMOPSMeas->setChecked(false);
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
    ui->checkBoxDisableFastDegradationSigma->setChecked(false);
    ui->checkBoxDisableRRCsigma->setChecked(false);
    ui->checkBoxDisableSlowCorrectionsSigma->setChecked(false);
    ui->checkBoxDisableIonosphereSigma->setChecked(false);
    ui->checkBoxDisableTroposphereSigma->setChecked(false);
    this->on_groupBoxShowOldMessages_clicked(false);
    ui->checkBoxDecodeMT37->setChecked(false);
    ui->checkBoxDecodeMT3940->setChecked(false);
    ui->checkBoxDecodeMT42->setChecked(false);
    ui->checkBoxDecodeMT47->setChecked(false);
    ui->lineEditSetValueDFREI0->setText("0.625");
    ui->lineEditSetValueDFREI1->setText("1.25");
    ui->lineEditSetValueDFREI2->setText("1.375");
    ui->lineEditSetValueDFREI3->setText("1.5");
    ui->lineEditSetValueDFREI4->setText("1.625");
    ui->lineEditSetValueDFREI5->setText("2.75");
    ui->lineEditSetValueDFREI6->setText("3");
    ui->lineEditSetValueDFREI7->setText("3.25");
    ui->lineEditSetValueDFREI8->setText("3.5");
    ui->lineEditSetValueDFREI9->setText("3.75");
    ui->lineEditSetValueDFREI10->setText("6");
    ui->lineEditSetValueDFREI11->setText("6.5");
    ui->lineEditSetValueDFREI12->setText("11");
    ui->lineEditSetValueDFREI13->setText("28");
    ui->lineEditSetValueDFREI14->setText("58");
    this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
    this->on_groupBoxSetOBADParameters_clicked(false);
    this->on_checkBoxSetCerOBADParameterMT37_clicked(false);
    this->on_checkBoxSetCcovarianceOBADParameterMT37_clicked(false);
    this->on_checkBoxSetIcorrOBADParameterMT37_clicked(false);
    this->on_checkBoxSetCcorrOBADParameterMT37_clicked(false);
    this->on_checkBoxSetRcorrOBADParameterMT37_clicked(false);
    this->on_checkBoxSetIcorrOBADParameterMT37Advanced_clicked(false);
    this->on_checkBoxSetCcorrOBADParameterMT37Advanced_clicked(false);
    this->on_checkBoxSetRcorrOBADParameterMT37Advanced_clicked(false);
    this->on_groupBoxSetDFREICorrections_clicked(false);
    this->on_checkBoxSetOneDFREISigmaConversionValue_clicked(false);
    this->on_checkBoxSetAllDFREIConversionValues_clicked(false);
    this->on_groupBoxSetSepcificSigmas_clicked(false);
    this->on_checkBoxSetDeltaRcorrParameter_clicked(false);
    this->on_checkBoxSetDeltaDFREFactor_clicked(false);
    this->on_checkBoxSetUIRESigmaValue_clicked(false);
    this->on_checkBoxSetTroposphericSigma_clicked(false);
    this->on_groupBoxStanfordESA_clicked(false);
    this->on_checkBoxStanfordESAallGeometries_clicked(true);
    ui->lineEditSmoothMinSbas->setText("360");
    ui->lineEditStanfordEsaXmax->setText("50");
    ui->lineEditStanfordEsaYmax->setText("50");
    ui->lineEditStanfordEsaXres->setText("0.1");
    ui->lineEditStanfordEsaYres->setText("0.1");
    ui->lineEditHorizontalIntegrityRatio->setText("0.7");
    ui->lineEditVerticalIntegrityRatio->setText("0.7");
    SBASOBADSet->setOBADDefaults();
}

// Output defaults
void gLAB_GUI::setOutputDefaults() {

    ui->lineEditKML_Dec->setText("30");
    ui->lineEditKML_From->setText("-");
    ui->lineEditKML_To->setText("-");
    ui->lineEditSP3Letter->setText("L");
    ui->lineEditSP3PRN->setText("9");
    ui->lineEditStfdESAMaxSatCombinations->setText("999999");
    ui->KMLTimeStampsRangeFrame->setHidden(false);


    this->on_checkBoxPrintMeas_clicked(false);
    ui->radioButtonMetresUnitOutputClock->setChecked(true);
    MeasSelectGNSS->setMeasdefaults();
}

//SPP default configuration
void gLAB_GUI::setSPPDefault(){
    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxSatAntex_clicked(false);
    this->on_checkBoxRecAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();
    this->on_checkBoxRinexNavFileGLO1_clicked(false);
    this->on_checkBoxRinexNavFileHealth1_clicked(false);
    this->on_checkBoxRinexNavFileGLO2_clicked(false);
    this->on_checkBoxRinexNavFileHealth2_clicked(false);
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    ui->groupBoxIonoSource->setHidden(false);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonIonoSourceBrdc_clicked();
    this->on_radioButtonRinex_clicked();
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);
    ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);

    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(false);
    ui->lineEditDataDecimator->setText("1");
    ui->checkBoxDiscardEclipse->setChecked(false);
    this->on_checkBoxDiscardUnhealthy_clicked(true);
    ui->checkBoxDiscardMarginal->setChecked(true);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(true);
    ui->checkBoxSF->setChecked(false);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    ui->checkBoxIGF->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("40");
    this->on_checkBoxGalileo_clicked(true);// Enable all Galileo satellites
    this->on_checkBoxGLONASS_clicked(true);// Enable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxBDS_clicked(true);// Enable all BDS satellites
    this->on_checkBoxQZSS_clicked(true);// Enable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(true);// Enable all IRNSS satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    for (int i=0; i<MAX_GNSS; i++){
        CheckBoxGNSS[i]->setEnabled(true);
    }
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_comboBoxSNRThresholdsMin_currentIndexChanged(4);
    this->on_comboBoxSNRThresholdsMax_currentIndexChanged(8);
    this->on_checkBoxSNRThresholdMin_clicked(false);
    this->on_checkBoxSNRThresholdMax_clicked(false);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();


    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(true);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(false);
    ui->checkBoxRelativisticClock->setChecked(true);
    ui->checkBoxIonoCorrection->setEnabled(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(0);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);
    //DCB
    this->on_groupBoxShowDCBOptions_clicked(false);
    //GPS
    this->on_groupBoxShowDCBOptionsGPS_clicked(false);
    ui->comboBoxDCBdfGPS->setCurrentIndex(1);
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
    ui->comboBoxISCsfL1CAGPS->setCurrentIndex(1);
    ui->comboBoxISCsfL2CGPS->setCurrentIndex(1);
    ui->comboBoxISCsfL5I5GPS->setCurrentIndex(1);
    ui->comboBoxISCsfL5Q5GPS->setCurrentIndex(1);
    //Galileo
    this->on_groupBoxShowDCBOptionsGalileo_clicked(false);
    ui->comboBoxDCBsfE1E5aGalileo->setCurrentIndex(1);
    ui->comboBoxDCBsfE1E5bGalileo->setCurrentIndex(1);
    //GLONASS
    this->on_groupBoxShowDCBOptionsGLONASS_clicked(false);
    ui->comboBoxDCBsfP1P2GLONASS->setCurrentIndex(1);
    //BDS
    this->on_groupBoxShowDCBOptionsBDS_clicked(false);
    ui->comboBoxDCBdfBDS->setCurrentIndex(1);
    ui->comboBoxDCBsfB2B6BDS->setCurrentIndex(1);
    ui->comboBoxDCBsfB7B6BDS->setCurrentIndex(1);
    ui->comboBoxDCBsfSP3BDS->setCurrentIndex(0);
    //QZSS
    this->on_groupBoxShowDCBOptionsQZSS_clicked(false);
    ui->comboBoxDCBdfQZSS->setCurrentIndex(1);
    ui->comboBoxDCBsfC1CQZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL2CQZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL5I5QZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL5Q5QZSS->setCurrentIndex(1);
    //IRNSS
    this->on_groupBoxShowDCBOptionsIRNSS_clicked(false);
    ui->comboBoxDCBsfC9C5IRNSS->setCurrentIndex(1);

    // FILTER
    setFilterDefaults();
    ui->pushButtonMeasGNSSAdd->setEnabled(true);
    ui->pushButtonMeasGNSSDelete->setEnabled(true);
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSelectionPseudorange_clicked();
    ui->radioButtonDualFreq->setHidden(false);
    ui->radioButtonSingleFreq->setHidden(false);
    this->on_radioButtonSingleFreq_clicked();
    this->on_radioButtonKinematic_clicked();
    // measurement
    ui->checkBoxSetFreqMeasOrderGNSS->setEnabled(true);
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    //GPS
    ui->stackedWidgetStdDevCodeGPS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGPS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGPS_3->setCurrentIndex(0);
    //Galileo
    ui->stackedWidgetStdDevCodeGalileo_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGalileo_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGalileo_3->setCurrentIndex(0);
    //GLONASS
    ui->stackedWidgetStdDevCodeGLONASS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGLONASS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGLONASS_3->setCurrentIndex(0);
    //GEO
    ui->stackedWidgetStdDevCodeGEO_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGEO_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGEO_3->setCurrentIndex(0);
    //BDS
    ui->stackedWidgetStdDevCodeBDS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeBDS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeBDS_3->setCurrentIndex(0);
    //QZSS
    ui->stackedWidgetStdDevCodeQZSS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeQZSS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeQZSS_3->setCurrentIndex(0);
    //IRNSS
    ui->stackedWidgetStdDevCodeIRNSS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeIRNSS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeIRNSS_3->setCurrentIndex(0);
    //others
    this->on_checkBoxEstimateTroposphere_clicked(false);
    ui->groupBoxTroposphere->setHidden(false);
    ui->checkBoxUseSigmaIonosphere->setChecked(false);
    ui->groupBoxIonosphere->setHidden(false);
    this->on_radioButtonWhiteNoiseClock_clicked();
    this->on_radioButtonWhiteNoiseISCB_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(false);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(true);
    this->on_groupBoxStanfordESA_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(false);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    ui->groupBoxRefGNSSClock->setEnabled(true);
    this->on_groupBoxRefGNSSClock_clicked(false);
    ui->groupBoxISCB->setEnabled(true);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);

    //GPS
    ui->lineEditStdDevCodeAGPS_1->setText("1");
    ui->lineEditStdDevCodeBGPS_1->setText("0.53");
    ui->lineEditStdDevCodeCGPS_1->setText("10");
    ui->lineEditStdDevPhaseAGPS_1->setText("0.1");
    ui->lineEditStdDevPhaseBGPS_1->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_1->setText("10");
    ui->lineEditStdDevCodeAGPS_2->setText("1");
    ui->lineEditStdDevCodeBGPS_2->setText("0.53");
    ui->lineEditStdDevCodeCGPS_2->setText("10");
    ui->lineEditStdDevPhaseAGPS_2->setText("0.1");
    ui->lineEditStdDevPhaseBGPS_2->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_2->setText("10");
    ui->lineEditStdDevCodeAGPS_3->setText("1");
    ui->lineEditStdDevCodeBGPS_3->setText("0.53");
    ui->lineEditStdDevCodeCGPS_3->setText("10");
    ui->lineEditStdDevPhaseAGPS_3->setText("0.1");
    ui->lineEditStdDevPhaseBGPS_3->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_3->setText("10");
    //Galileo
    ui->lineEditStdDevCodeAGalileo_1->setText("1");
    ui->lineEditStdDevCodeBGalileo_1->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_1->setText("10");
    ui->lineEditStdDevPhaseAGalileo_1->setText("0.1");
    ui->lineEditStdDevPhaseBGalileo_1->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_1->setText("10");
    ui->lineEditStdDevCodeAGalileo_2->setText("1");
    ui->lineEditStdDevCodeBGalileo_2->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_2->setText("10");
    ui->lineEditStdDevPhaseAGalileo_2->setText("0.1");
    ui->lineEditStdDevPhaseBGalileo_2->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_2->setText("10");
    ui->lineEditStdDevCodeAGalileo_3->setText("1");
    ui->lineEditStdDevCodeBGalileo_3->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_3->setText("10");
    ui->lineEditStdDevPhaseAGalileo_3->setText("0.1");
    ui->lineEditStdDevPhaseBGalileo_3->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_3->setText("10");
    //GLONASS
    ui->lineEditStdDevCodeAGLONASS_1->setText("1");
    ui->lineEditStdDevCodeBGLONASS_1->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_1->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_1->setText("0.1");
    ui->lineEditStdDevPhaseBGLONASS_1->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_1->setText("10");
    ui->lineEditStdDevCodeAGLONASS_2->setText("1");
    ui->lineEditStdDevCodeBGLONASS_2->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_2->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_2->setText("0.1");
    ui->lineEditStdDevPhaseBGLONASS_2->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_2->setText("10");
    ui->lineEditStdDevCodeAGLONASS_3->setText("1");
    ui->lineEditStdDevCodeBGLONASS_3->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_3->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_3->setText("0.1");
    ui->lineEditStdDevPhaseBGLONASS_3->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_3->setText("10");
    //GEO
    ui->lineEditStdDevCodeAGEO_1->setText("1");
    ui->lineEditStdDevCodeBGEO_1->setText("0.53");
    ui->lineEditStdDevCodeCGEO_1->setText("10");
    ui->lineEditStdDevPhaseAGEO_1->setText("0.1");
    ui->lineEditStdDevPhaseBGEO_1->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_1->setText("10");
    ui->lineEditStdDevCodeAGEO_2->setText("1");
    ui->lineEditStdDevCodeBGEO_2->setText("0.53");
    ui->lineEditStdDevCodeCGEO_2->setText("10");
    ui->lineEditStdDevPhaseAGEO_2->setText("0.1");
    ui->lineEditStdDevPhaseBGEO_2->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_2->setText("10");
    ui->lineEditStdDevCodeAGEO_3->setText("1");
    ui->lineEditStdDevCodeBGEO_3->setText("0.53");
    ui->lineEditStdDevCodeCGEO_3->setText("10");
    ui->lineEditStdDevPhaseAGEO_3->setText("0.1");
    ui->lineEditStdDevPhaseBGEO_3->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_3->setText("10");
    //BDS
    ui->lineEditStdDevCodeABDS_1->setText("1");
    ui->lineEditStdDevCodeBBDS_1->setText("0.53");
    ui->lineEditStdDevCodeCBDS_1->setText("10");
    ui->lineEditStdDevPhaseABDS_1->setText("0.1");
    ui->lineEditStdDevPhaseBBDS_1->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_1->setText("10");
    ui->lineEditStdDevCodeABDS_2->setText("1");
    ui->lineEditStdDevCodeBBDS_2->setText("0.53");
    ui->lineEditStdDevCodeCBDS_2->setText("10");
    ui->lineEditStdDevPhaseABDS_2->setText("0.1");
    ui->lineEditStdDevPhaseBBDS_2->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_2->setText("10");
    ui->lineEditStdDevCodeABDS_3->setText("1");
    ui->lineEditStdDevCodeBBDS_3->setText("0.53");
    ui->lineEditStdDevCodeCBDS_3->setText("10");
    ui->lineEditStdDevPhaseABDS_3->setText("0.1");
    ui->lineEditStdDevPhaseBBDS_3->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_3->setText("10");
    //QZSS
    ui->lineEditStdDevCodeAQZSS_1->setText("1");
    ui->lineEditStdDevCodeBQZSS_1->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_1->setText("10");
    ui->lineEditStdDevPhaseAQZSS_1->setText("0.1");
    ui->lineEditStdDevPhaseBQZSS_1->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_1->setText("10");
    ui->lineEditStdDevCodeAQZSS_2->setText("1");
    ui->lineEditStdDevCodeBQZSS_2->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_2->setText("10");
    ui->lineEditStdDevPhaseAQZSS_2->setText("0.1");
    ui->lineEditStdDevPhaseBQZSS_2->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_2->setText("10");
    ui->lineEditStdDevCodeAQZSS_3->setText("1");
    ui->lineEditStdDevCodeBQZSS_3->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_3->setText("10");
    ui->lineEditStdDevPhaseAQZSS_3->setText("0.1");
    ui->lineEditStdDevPhaseBQZSS_3->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_3->setText("10");
    //IRNSS
    ui->lineEditStdDevCodeAIRNSS_1->setText("1");
    ui->lineEditStdDevCodeBIRNSS_1->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_1->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_1->setText("0.1");
    ui->lineEditStdDevPhaseBIRNSS_1->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_1->setText("10");
    ui->lineEditStdDevCodeAIRNSS_2->setText("1");
    ui->lineEditStdDevCodeBIRNSS_2->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_2->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_2->setText("0.1");
    ui->lineEditStdDevPhaseBIRNSS_2->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_2->setText("10");
    ui->lineEditStdDevCodeAIRNSS_3->setText("1");
    ui->lineEditStdDevCodeBIRNSS_3->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_3->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_3->setText("0.1");
    ui->lineEditStdDevPhaseBIRNSS_3->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_3->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
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
    ui->groupBoxSummaryConvergence->setHidden(true);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(0);
}
//PPP default configuration
void gLAB_GUI::setPPPDefault(){
    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxRinexNavFileGLO1_clicked(false);
    this->on_checkBoxRinexNavFileHealth1_clicked(false);
    this->on_checkBoxRinexNavFileGLO2_clicked(false);
    this->on_checkBoxRinexNavFileHealth2_clicked(false);
    this->on_checkBoxSatAntex_clicked(true);
    this->on_checkBoxRecAntex_clicked(false);
    this->on_radioButtonOrbitPrecise1file_clicked();
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    ui->groupBoxIonoSource->setHidden(false);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonIonoSourceBrdc_clicked();
    this->on_radioButtonRinex_clicked();
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);


    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(false);
    ui->lineEditDataDecimator->setText("1");
    ui->checkBoxDiscardEclipse->setChecked(true);
    this->on_checkBoxDiscardUnhealthy_clicked(false);
    this->on_checkBoxDiscardMarginal_clicked(false);
    ui->checkBoxLLI->setChecked(true);
    this->on_checkBoxNcon_clicked(true);
    ui->checkBoxSF->setChecked(false);
    ui->checkBoxMW->setChecked(true);
    ui->checkBoxLI->setChecked(true);
    ui->checkBoxIGF->setChecked(false);
    this->on_radioButtonIGFTwoIonoFree_clicked();
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("40");
    this->on_checkBoxGalileo_clicked(true);// Enable all Galileo satellites
    this->on_checkBoxGLONASS_clicked(true);// Enable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxBDS_clicked(true);// Enable all BDS satellites
    this->on_checkBoxQZSS_clicked(true);// Enable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(true);// Enable all IRNSS satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    for (int i=0; i<MAX_GNSS; i++){
        CheckBoxGNSS[i]->setEnabled(true);
    }
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_comboBoxSNRThresholdsMin_currentIndexChanged(4);
    this->on_comboBoxSNRThresholdsMax_currentIndexChanged(8);
    this->on_checkBoxSNRThresholdMin_clicked(false);
    this->on_checkBoxSNRThresholdMax_clicked(false);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();

    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(true);
    this->on_checkBoxAntennaPhase_clicked(true);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    ui->checkBoxIonoCorrection->setEnabled(true);
    this->on_checkBoxIonoCorrection_clicked(false);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(1);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(1);
    ui->checkBoxWindUp->setChecked(true);
    ui->checkBoxTides->setChecked(true);
    ui->checkBoxRelativisticPath->setChecked(true);
    this->on_radioButtonAPCread_clicked();
    this->on_radioButtonARPread_clicked();
    //DCB
    this->on_groupBoxShowDCBOptions_clicked(false);
    //GPS
    this->on_groupBoxShowDCBOptionsGPS_clicked(false);
    ui->comboBoxDCBdfGPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(0);
    ui->comboBoxISCsfL1CAGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5GPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5GPS->setCurrentIndex(0);
    //Galileo
    this->on_groupBoxShowDCBOptionsGalileo_clicked(false);
    ui->comboBoxDCBsfE1E5aGalileo->setCurrentIndex(0);
    ui->comboBoxDCBsfE1E5bGalileo->setCurrentIndex(0);
    //GLONASS
    this->on_groupBoxShowDCBOptionsGLONASS_clicked(false);
    ui->comboBoxDCBsfP1P2GLONASS->setCurrentIndex(0);
    //BDS
    this->on_groupBoxShowDCBOptionsBDS_clicked(false);
    ui->comboBoxDCBdfBDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB2B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB7B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfSP3BDS->setCurrentIndex(1);
    //QZSS
    this->on_groupBoxShowDCBOptionsQZSS_clicked(false);
    ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
    ui->comboBoxDCBsfC1CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5QZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5QZSS->setCurrentIndex(0);
    //IRNSS
    this->on_groupBoxShowDCBOptionsIRNSS_clicked(false);
    ui->comboBoxDCBsfC9C5IRNSS->setCurrentIndex(0);


    // FILTER
    setFilterDefaults();
    ui->pushButtonMeasGNSSAdd->setEnabled(true);
    ui->pushButtonMeasGNSSDelete->setEnabled(true);
    ui->lineEditSmoothing->setText("10");
    this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
    ui->radioButtonDualFreq->setHidden(false);
    ui->radioButtonSingleFreq->setHidden(false);
    this->on_radioButtonDualFreq_clicked();
    this->on_radioButtonStatic_clicked();
    // measurement
    ui->checkBoxSetFreqMeasOrderGNSS->setEnabled(true);
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    //GPS
    ui->stackedWidgetStdDevCodeGPS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGPS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGPS_3->setCurrentIndex(0);
    //Galileo
    ui->stackedWidgetStdDevCodeGalileo_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGalileo_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGalileo_3->setCurrentIndex(0);
    //GLONASS
    ui->stackedWidgetStdDevCodeGLONASS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGLONASS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGLONASS_3->setCurrentIndex(0);
    //GEO
    ui->stackedWidgetStdDevCodeGEO_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGEO_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeGEO_3->setCurrentIndex(0);
    //BDS
    ui->stackedWidgetStdDevCodeBDS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeBDS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeBDS_3->setCurrentIndex(0);
    //QZSS
    ui->stackedWidgetStdDevCodeQZSS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeQZSS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeQZSS_3->setCurrentIndex(0);
    //IRNSS
    ui->stackedWidgetStdDevCodeIRNSS_1->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeIRNSS_2->setCurrentIndex(0);
    ui->stackedWidgetStdDevCodeIRNSS_3->setCurrentIndex(0);
    //others
    this->on_checkBoxEstimateTroposphere_clicked(true);
    ui->groupBoxTroposphere->setHidden(false);
    ui->checkBoxUseSigmaIonosphere->setChecked(false);
    ui->groupBoxIonosphere->setHidden(false);
    this->on_radioButtonWhiteNoiseClock_clicked();
    this->on_radioButtonConstantISCB_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(true);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(true);

    this->on_groupBoxStanfordESA_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(false);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    ui->groupBoxRefGNSSClock->setEnabled(true);
    this->on_groupBoxRefGNSSClock_clicked(false);
    ui->groupBoxISCB->setEnabled(true);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);
    //GPS
    ui->lineEditStdDevCodeAGPS_1->setText("3");
    ui->lineEditStdDevCodeBGPS_1->setText("0.53");
    ui->lineEditStdDevCodeCGPS_1->setText("10");
    ui->lineEditStdDevPhaseAGPS_1->setText("0.03");
    ui->lineEditStdDevPhaseBGPS_1->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_1->setText("10");
    ui->lineEditStdDevCodeAGPS_2->setText("3");
    ui->lineEditStdDevCodeBGPS_2->setText("0.53");
    ui->lineEditStdDevCodeCGPS_2->setText("10");
    ui->lineEditStdDevPhaseAGPS_2->setText("0.03");
    ui->lineEditStdDevPhaseBGPS_2->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_2->setText("10");
    ui->lineEditStdDevCodeAGPS_3->setText("3");
    ui->lineEditStdDevCodeBGPS_3->setText("0.53");
    ui->lineEditStdDevCodeCGPS_3->setText("10");
    ui->lineEditStdDevPhaseAGPS_3->setText("0.03");
    ui->lineEditStdDevPhaseBGPS_3->setText("0.53");
    ui->lineEditStdDevPhaseCGPS_3->setText("10");
    //Galileo
    ui->lineEditStdDevCodeAGalileo_1->setText("3");
    ui->lineEditStdDevCodeBGalileo_1->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_1->setText("10");
    ui->lineEditStdDevPhaseAGalileo_1->setText("0.03");
    ui->lineEditStdDevPhaseBGalileo_1->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_1->setText("10");
    ui->lineEditStdDevCodeAGalileo_2->setText("3");
    ui->lineEditStdDevCodeBGalileo_2->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_2->setText("10");
    ui->lineEditStdDevPhaseAGalileo_2->setText("0.03");
    ui->lineEditStdDevPhaseBGalileo_2->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_2->setText("10");
    ui->lineEditStdDevCodeAGalileo_3->setText("3");
    ui->lineEditStdDevCodeBGalileo_3->setText("0.53");
    ui->lineEditStdDevCodeCGalileo_3->setText("10");
    ui->lineEditStdDevPhaseAGalileo_3->setText("0.03");
    ui->lineEditStdDevPhaseBGalileo_3->setText("0.53");
    ui->lineEditStdDevPhaseCGalileo_3->setText("10");
    //GLONASS
    ui->lineEditStdDevCodeAGLONASS_1->setText("3");
    ui->lineEditStdDevCodeBGLONASS_1->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_1->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_1->setText("0.03");
    ui->lineEditStdDevPhaseBGLONASS_1->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_1->setText("10");
    ui->lineEditStdDevCodeAGLONASS_2->setText("3");
    ui->lineEditStdDevCodeBGLONASS_2->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_2->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_2->setText("0.03");
    ui->lineEditStdDevPhaseBGLONASS_2->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_2->setText("10");
    ui->lineEditStdDevCodeAGLONASS_3->setText("3");
    ui->lineEditStdDevCodeBGLONASS_3->setText("0.53");
    ui->lineEditStdDevCodeCGLONASS_3->setText("10");
    ui->lineEditStdDevPhaseAGLONASS_3->setText("0.03");
    ui->lineEditStdDevPhaseBGLONASS_3->setText("0.53");
    ui->lineEditStdDevPhaseCGLONASS_3->setText("10");
    //GEO
    ui->lineEditStdDevCodeAGEO_1->setText("3");
    ui->lineEditStdDevCodeBGEO_1->setText("0.53");
    ui->lineEditStdDevCodeCGEO_1->setText("10");
    ui->lineEditStdDevPhaseAGEO_1->setText("0.03");
    ui->lineEditStdDevPhaseBGEO_1->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_1->setText("10");
    ui->lineEditStdDevCodeAGEO_2->setText("3");
    ui->lineEditStdDevCodeBGEO_2->setText("0.53");
    ui->lineEditStdDevCodeCGEO_2->setText("10");
    ui->lineEditStdDevPhaseAGEO_2->setText("0.03");
    ui->lineEditStdDevPhaseBGEO_2->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_2->setText("10");
    ui->lineEditStdDevCodeAGEO_3->setText("3");
    ui->lineEditStdDevCodeBGEO_3->setText("0.53");
    ui->lineEditStdDevCodeCGEO_3->setText("10");
    ui->lineEditStdDevPhaseAGEO_3->setText("0.03");
    ui->lineEditStdDevPhaseBGEO_3->setText("0.53");
    ui->lineEditStdDevPhaseCGEO_3->setText("10");
    //BDS
    ui->lineEditStdDevCodeABDS_1->setText("3");
    ui->lineEditStdDevCodeBBDS_1->setText("0.53");
    ui->lineEditStdDevCodeCBDS_1->setText("10");
    ui->lineEditStdDevPhaseABDS_1->setText("0.03");
    ui->lineEditStdDevPhaseBBDS_1->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_1->setText("10");
    ui->lineEditStdDevCodeABDS_2->setText("3");
    ui->lineEditStdDevCodeBBDS_2->setText("0.53");
    ui->lineEditStdDevCodeCBDS_2->setText("10");
    ui->lineEditStdDevPhaseABDS_2->setText("0.03");
    ui->lineEditStdDevPhaseBBDS_2->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_2->setText("10");
    ui->lineEditStdDevCodeABDS_3->setText("3");
    ui->lineEditStdDevCodeBBDS_3->setText("0.53");
    ui->lineEditStdDevCodeCBDS_3->setText("10");
    ui->lineEditStdDevPhaseABDS_3->setText("0.03");
    ui->lineEditStdDevPhaseBBDS_3->setText("0.53");
    ui->lineEditStdDevPhaseCBDS_3->setText("10");
    //QZSS
    ui->lineEditStdDevCodeAQZSS_1->setText("3");
    ui->lineEditStdDevCodeBQZSS_1->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_1->setText("10");
    ui->lineEditStdDevPhaseAQZSS_1->setText("0.03");
    ui->lineEditStdDevPhaseBQZSS_1->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_1->setText("10");
    ui->lineEditStdDevCodeAQZSS_2->setText("3");
    ui->lineEditStdDevCodeBQZSS_2->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_2->setText("10");
    ui->lineEditStdDevPhaseAQZSS_2->setText("0.03");
    ui->lineEditStdDevPhaseBQZSS_2->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_2->setText("10");
    ui->lineEditStdDevCodeAQZSS_3->setText("3");
    ui->lineEditStdDevCodeBQZSS_3->setText("0.53");
    ui->lineEditStdDevCodeCQZSS_3->setText("10");
    ui->lineEditStdDevPhaseAQZSS_3->setText("0.03");
    ui->lineEditStdDevPhaseBQZSS_3->setText("0.53");
    ui->lineEditStdDevPhaseCQZSS_3->setText("10");
    //IRNSS
    ui->lineEditStdDevCodeAIRNSS_1->setText("3");
    ui->lineEditStdDevCodeBIRNSS_1->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_1->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_1->setText("0.03");
    ui->lineEditStdDevPhaseBIRNSS_1->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_1->setText("10");
    ui->lineEditStdDevCodeAIRNSS_2->setText("3");
    ui->lineEditStdDevCodeBIRNSS_2->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_2->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_2->setText("0.03");
    ui->lineEditStdDevPhaseBIRNSS_2->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_2->setText("10");
    ui->lineEditStdDevCodeAIRNSS_3->setText("3");
    ui->lineEditStdDevCodeBIRNSS_3->setText("0.53");
    ui->lineEditStdDevCodeCIRNSS_3->setText("10");
    ui->lineEditStdDevPhaseAIRNSS_3->setText("0.03");
    ui->lineEditStdDevPhaseBIRNSS_3->setText("0.53");
    ui->lineEditStdDevPhaseCIRNSS_3->setText("10");

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
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
    ui->groupBoxSummaryConvergence->setHidden(false);
    ui->lineEditSummaryConvergenceFormalThresHor->setText("0.4");
    ui->lineEditSummaryConvergenceFormalThresVer->setText("0.4");
    ui->lineEditSummaryConvergenceFormalThres3D->setText("0.4");
    ui->lineEditSummaryConvergenceFormalTimeThresHor->setText("300");
    ui->lineEditSummaryConvergenceFormalTimeThresVer->setText("300");
    ui->lineEditSummaryConvergenceFormalTimeThres3D->setText("300");
    ui->lineEditSummaryConvergencePositionThresHor->setText("0.4");
    ui->lineEditSummaryConvergencePositionThresVer->setText("0.4");
    ui->lineEditSummaryConvergencePositionThres3D->setText("0.4");
    ui->lineEditSummaryConvergencePositionTimeThresHor->setText("300");
    ui->lineEditSummaryConvergencePositionTimeThresVer->setText("300");
    ui->lineEditSummaryConvergencePositionTimeThres3D->setText("300");

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(0);
}
//SBAS 1F default configuration
void gLAB_GUI::setSBAS1FDefault(){
    this->on_groupBoxConverterSBAS_clicked(true); // Converter
    this->on_groupBoxConverterDgnss_clicked(false); // Converter

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxSatAntex_clicked(false);
    this->on_checkBoxRecAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();
    ui->checkBoxRinexNavFileHealth1->setHidden(true);
    ui->lineEditRinexNavFileHealth1->setHidden(true);
    ui->pushButtonRinexNavFileHealth1->setHidden(true);
    ui->checkBoxRinexNavFileHealth2->setHidden(true);
    ui->lineEditRinexNavFileHealth2->setHidden(true);
    ui->pushButtonRinexNavFileHealth2->setHidden(true);
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_radioButtonRinex_clicked();
    ui->groupBoxIonoSource->setHidden(false);
    this->on_groupBoxIonoSource_clicked(false);
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    this->on_radioButtonIonoSourceSbas_clicked();
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);


    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(true);
    ui->lineEditDataDecimator->setText("1");
    ui->checkBoxDiscardEclipse->setChecked(false);
    this->on_checkBoxDiscardUnhealthy_clicked(false);
    ui->checkBoxDiscardMarginal->setChecked(false);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(false);
    ui->checkBoxSF->setChecked(true);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    ui->checkBoxIGF->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("10");
    this->on_checkBoxGalileo_clicked(false);// Disable all Galileo satellites
    this->on_checkBoxGLONASS_clicked(false);// Enable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxBDS_clicked(false);// Disable all BDS satellites
    this->on_checkBoxQZSS_clicked(false);// Disable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(false);// Disable all IRNSS satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    CheckBoxGNSS[GPS]->setEnabled(true);
    CheckBoxGNSS[Galileo]->setEnabled(false);
    CheckBoxGNSS[GLONASS]->setEnabled(true);
    CheckBoxGNSS[GEO]->setEnabled(true);
    CheckBoxGNSS[BDS]->setEnabled(false);
    CheckBoxGNSS[QZSS]->setEnabled(false);
    CheckBoxGNSS[IRNSS]->setEnabled(false);
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_checkBoxSNRThresholdMin_clicked(true);
    this->on_checkBoxSNRThresholdMax_clicked(true);
    this->on_comboBoxSNRThresholdsMin_currentIndexChanged(4);
    this->on_comboBoxSNRThresholdsMax_currentIndexChanged(8);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();

    // MODELLING
    ui->groupBoxSbasOptions->setTitle("SBAS Options (Using MOPS-D)");
    ui->groupBoxSbasAdvancedOptions->setTitle("Show SBAS 1F Advanced Options");
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    ui->checkBoxIonoCorrection->setEnabled(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(4);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);

    // MODELLING for SBAS
    this->setSBASmodellingDefaults();
    this->change_comboBoxSBASApplication(0);
    ui->groupBoxDisableSBASMessages->setHidden(false);
    ui->groupBoxDisableSpecificCorrections->setHidden(false);
    ui->groupBoxDisableSpecificSigmas->setHidden(false);
    ui->groupBoxShowOldMessages->setHidden(true);
    ui->groupBoxSetOBADParameters->setHidden(true);
    ui->groupBoxSetDFREICorrections->setHidden(true);
    ui->groupBoxSetSepcificSigmas->setHidden(true);
    ui->frameSigmaMultiPathFactor->setHidden(true);
    ui->checkBoxAllowUseNoneMOPSMeas->setHidden(true);
    ui->frameSBAS1FMessages->setHidden(false);
    ui->stackedWidgetSBASMessages->setCurrentIndex(0);
    ui->checkBoxParseAlarmSBAS1F->setHidden(false);
    ui->checkBoxParseAlarmSBASDFMC->setHidden(true);
    ui->checkBoxAllowKlobucharIono->setHidden(false);
    ui->frame_discardSatellitesUDREI->setHidden(false);

    //Set navigation message types
    QString option="-model:brdc:gps",type="LNAV",tmpString="";
    this->command_2_UserNavMessageTypes(&option,&type,&tmpString,0);
    ui->tableWidgetNavMessageTypeGPS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGalileo->setDisabled(true);
    ui->tableWidgetNavMessageTypeGLONASS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGEO->setDisabled(true);
    ui->tableWidgetNavMessageTypeBDS->setDisabled(true);
    ui->tableWidgetNavMessageTypeQZSS->setDisabled(true);
    ui->tableWidgetNavMessageTypeIRNSS->setDisabled(true);

    //DCB
    this->on_groupBoxShowDCBOptions_clicked(false);
    //GPS
    this->on_groupBoxShowDCBOptionsGPS_clicked(false);
    ui->comboBoxDCBdfGPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
    ui->comboBoxISCsfL1CAGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5GPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5GPS->setCurrentIndex(0);
    //Galileo
    this->on_groupBoxShowDCBOptionsGalileo_clicked(false);
    ui->comboBoxDCBsfE1E5aGalileo->setCurrentIndex(0);
    ui->comboBoxDCBsfE1E5bGalileo->setCurrentIndex(0);
    //GLONASS
    this->on_groupBoxShowDCBOptionsGLONASS_clicked(false);
    ui->comboBoxDCBsfP1P2GLONASS->setCurrentIndex(0);
    //BDS
    this->on_groupBoxShowDCBOptionsBDS_clicked(false);
    ui->comboBoxDCBdfBDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB2B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB7B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfSP3BDS->setCurrentIndex(0);
    //QZSS
    this->on_groupBoxShowDCBOptionsQZSS_clicked(false);
    ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
    ui->comboBoxDCBsfC1CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5QZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5QZSS->setCurrentIndex(0);
    //IRNSS
    this->on_groupBoxShowDCBOptionsIRNSS_clicked(false);
    ui->comboBoxDCBsfC9C5IRNSS->setCurrentIndex(0);

    // FILTER
    setFilterDefaults();
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSmoothing_clicked();
    this->on_radioButtonSingleFreq_clicked();
    ui->radioButtonDualFreq->setHidden(true);
    ui->radioButtonSingleFreq->setHidden(false);
    this->on_radioButtonKinematic_clicked();
    ui->radioButtonSelectionGraphic->setHidden(true);
    // measurement
    ui->checkBoxSetFreqMeasOrderGNSS->setEnabled(false);
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    ui->pushButtonMeasGNSSAdd->setEnabled(false);
    ui->pushButtonMeasGNSSDelete->setEnabled(false);
    //GPS
    this->on_comboBoxFreqCodeGPS_1_currentIndexChanged(0); //F1
    ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(3); //C1C
    ui->comboBoxFreqCodeGPS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GPS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGPS_1->setCurrentIndex(1);//SBAS Single StdDev
    this->on_comboBoxSmoothFreq1GPS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GPS_1_currentIndexChanged(1);//L1P
    ui->frameSmoothGPS_1->setEnabled(false);
    //GLONASS
    this->on_comboBoxFreqCodeGLONASS_1_currentIndexChanged(0); //F1
    ui->comboBoxMeasCodeFreq1GLONASS_1->setCurrentIndex(3); //C1C
    ui->comboBoxFreqCodeGLONASS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GLONASS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGLONASS_1->setCurrentIndex(1);//SBAS Single StdDev
    this->on_comboBoxSmoothFreq1GLONASS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GLONASS_1_currentIndexChanged(1);//L1P
    ui->frameSmoothGLONASS_1->setEnabled(false);
    //GEO
    this->on_comboBoxFreqCodeGEO_1_currentIndexChanged(0); //F1
    ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(3); //C1C
    ui->comboBoxFreqCodeGEO_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GEO_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGEO_1->setCurrentIndex(1);//SBAS Single StdDev
    this->on_comboBoxSmoothFreq1GEO_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GEO_1_currentIndexChanged(1);//L1P
    ui->frameSmoothGEO_1->setEnabled(false);
    //others
    this->on_checkBoxEstimateTroposphere_clicked(false);
    ui->groupBoxTroposphere->setHidden(true);
    ui->checkBoxUseSigmaIonosphere->setChecked(false);
    ui->groupBoxIonosphere->setHidden(true);
    this->on_radioButtonWhiteNoiseClock_clicked();
    this->on_radioButtonWhiteNoiseISCB_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(false);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(true);
    ui->checkBoxBackwardFiltering->setHidden(true);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    ui->groupBoxRefGNSSClock->setEnabled(false);
    this->on_groupBoxRefGNSSClock_clicked(false);
    ui->groupBoxISCB->setEnabled(false);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
    ui->checkBoxPrintUsererror->setChecked(true);
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
    ui->checkBoxPrintSbascor->setHidden(false);
    ui->checkBoxPrintSbasvar->setHidden(false);
    ui->checkBoxPrintSbasiono->setHidden(false);
    ui->checkBoxPrintSbasunsel->setHidden(false);
    ui->checkBoxPrintSbasDFMCCor->setHidden(true);
    ui->checkBoxPrintSbasDFMCVar->setHidden(true);
    ui->checkBoxPrintSbasDFMCUnsel->setHidden(true);
    ui->groupBoxSummaryConvergence->setHidden(true);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(false);
    ui->stackedWidgetTemplates->setCurrentIndex(1);
    ui->pushButtonTemplateSBASIonoComponents->setHidden(false);

    //Convertor
    this->on_checkBox_pegasus_clicked(false);
    ui->checkBox_pegasus->setHidden(false);
    ui->frame_holdingPegasusOptions->setHidden(false);
}
//SBAS DFMC default configuration
void gLAB_GUI::setSBASDFMCDefault(){
    this->on_groupBoxConverterDgnss_clicked(false); // Converter
    this->on_groupBoxConverterSBAS_clicked(true); // Converter

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxSatAntex_clicked(false);
    this->on_checkBoxRecAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();
    ui->checkBoxRinexNavFileHealth1->setHidden(true);
    ui->lineEditRinexNavFileHealth1->setHidden(true);
    ui->pushButtonRinexNavFileHealth1->setHidden(true);
    ui->checkBoxRinexNavFileHealth2->setHidden(true);
    ui->lineEditRinexNavFileHealth2->setHidden(true);
    ui->pushButtonRinexNavFileHealth2->setHidden(true);
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_radioButtonRinex_clicked();
    this->on_groupBoxIonoSource_clicked(false);
    ui->groupBoxIonoSource->setHidden(false);
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    this->on_radioButtonIonoSourceSbas_clicked();
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);


    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(true);
    ui->lineEditDataDecimator->setText("1");
    ui->checkBoxDiscardEclipse->setChecked(false);
    this->on_checkBoxDiscardUnhealthy_clicked(false);
    ui->checkBoxDiscardMarginal->setChecked(false);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(false);
    ui->checkBoxSF->setChecked(false);
    ui->checkBoxMW->setChecked(true);
    ui->checkBoxLI->setChecked(true);
    ui->checkBoxIGF->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("10");
    this->on_checkBoxGLONASS_clicked(false);// Disable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxQZSS_clicked(false);// Disable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(false);// Disable all IRNSS satellites
    this->on_checkBoxBDS_clicked(false);// Disable all BDS satellites
    this->on_checkBoxGalileo_clicked(true);// Enable all Galileo satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    CheckBoxGNSS[GPS]->setEnabled(true);
    CheckBoxGNSS[Galileo]->setEnabled(true);
    CheckBoxGNSS[GLONASS]->setEnabled(false);
    CheckBoxGNSS[GEO]->setEnabled(true);
    CheckBoxGNSS[BDS]->setEnabled(true);
    CheckBoxGNSS[QZSS]->setEnabled(true);
    CheckBoxGNSS[IRNSS]->setEnabled(false);
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_checkBoxSNRThresholdMin_clicked(true);
    this->on_checkBoxSNRThresholdMax_clicked(true);
    this->on_comboBoxSNRThresholdsMin_currentIndexChanged(4);
    this->on_comboBoxSNRThresholdsMax_currentIndexChanged(8);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();

    // MODELLING
    ui->groupBoxSbasOptions->setTitle("SBAS DFMC Options (using ED-259 v0.8)");
    ui->groupBoxSbasAdvancedOptions->setTitle("Show SBAS DFMC Advanced Options");
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    this->on_checkBoxIonoCorrection_clicked(false);
    ui->comboBoxIonoCorrection->setCurrentIndex(0);
    ui->checkBoxIonoCorrection->setEnabled(false);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);

    // MODELLING for SBAS
    this->setSBASmodellingDefaults();
    this->change_comboBoxSBASApplication(1);
    ui->groupBoxDisableSBASMessages->setHidden(true);
    ui->groupBoxDisableSpecificCorrections->setHidden(true);
    ui->groupBoxDisableSpecificSigmas->setHidden(true);
    ui->groupBoxShowOldMessages->setHidden(false);
    ui->groupBoxSetOBADParameters->setHidden(false);
    ui->groupBoxSetDFREICorrections->setHidden(false);
    ui->groupBoxSetSepcificSigmas->setHidden(false);
    ui->frameSigmaMultiPathFactor->setHidden(false);
    ui->checkBoxAllowUseNoneMOPSMeas->setHidden(false);
    ui->frameSBAS1FMessages->setHidden(true);
    ui->stackedWidgetSBASMessages->setCurrentIndex(1);
    ui->checkBoxParseAlarmSBAS1F->setHidden(true);
    ui->checkBoxParseAlarmSBASDFMC->setHidden(false);
    ui->checkBoxAllowKlobucharIono->setHidden(true);
    ui->frame_discardSatellitesUDREI->setHidden(true);

    //Set navigation message types
    QString option="-model:brdc:gps",type="LNAV",tmpString="";
    this->command_2_UserNavMessageTypes(&option,&type,&tmpString,0);
    option="-model:brdc:gal";
    type="FNAV";
    tmpString="";
    this->command_2_UserNavMessageTypes(&option,&type,&tmpString,0);
    ui->tableWidgetNavMessageTypeGPS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGalileo->setDisabled(true);
    ui->tableWidgetNavMessageTypeGLONASS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGEO->setDisabled(true);
    ui->tableWidgetNavMessageTypeBDS->setDisabled(true);
    ui->tableWidgetNavMessageTypeQZSS->setDisabled(true);
    ui->tableWidgetNavMessageTypeIRNSS->setDisabled(true);


    //DCB
    this->on_groupBoxShowDCBOptions_clicked(false);
    //GPS
    this->on_groupBoxShowDCBOptionsGPS_clicked(false);
    ui->comboBoxDCBdfGPS->setCurrentIndex(1);
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(0);
    ui->comboBoxISCsfL1CAGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CGPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5GPS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5GPS->setCurrentIndex(0);
    //Galileo
    this->on_groupBoxShowDCBOptionsGalileo_clicked(false);
    ui->comboBoxDCBsfE1E5aGalileo->setCurrentIndex(0);
    ui->comboBoxDCBsfE1E5bGalileo->setCurrentIndex(0);
    //GLONASS
    this->on_groupBoxShowDCBOptionsGLONASS_clicked(false);
    ui->comboBoxDCBsfP1P2GLONASS->setCurrentIndex(0);
    //BDS
    this->on_groupBoxShowDCBOptionsBDS_clicked(false);
    ui->comboBoxDCBdfBDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB2B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB7B6BDS->setCurrentIndex(0);
    ui->comboBoxDCBsfSP3BDS->setCurrentIndex(0);
    //QZSS
    this->on_groupBoxShowDCBOptionsQZSS_clicked(false);
    ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
    ui->comboBoxDCBsfC1CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL2CQZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5I5QZSS->setCurrentIndex(0);
    ui->comboBoxISCsfL5Q5QZSS->setCurrentIndex(0);
    //IRNSS
    this->on_groupBoxShowDCBOptionsIRNSS_clicked(false);
    ui->comboBoxDCBsfC9C5IRNSS->setCurrentIndex(0);

    // FILTER
    setFilterDefaults();
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSmoothing_clicked();
    this->on_radioButtonDualFreq_clicked();
    ui->radioButtonDualFreq->setHidden(false);
    ui->radioButtonSingleFreq->setHidden(true);
    this->on_radioButtonKinematic_clicked();
    // measurement
    ui->checkBoxSetFreqMeasOrderGNSS->setEnabled(false);
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    //GPS
    this->on_comboBoxFreqCodeGPS_1_currentIndexChanged(1); //PC15
    ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(3); //C1C
    ui->comboBoxMeasCodeFreq2GPS_1->setCurrentIndex(1); //C5Q
    ui->comboBoxFreqCodeGPS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GPS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq2GPS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGPS_1->setCurrentIndex(2);//SBAS Dual StdDev
    this->on_comboBoxSmoothFreq1GPS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GPS_1_currentIndexChanged(1);//L1P
    this->on_comboBoxSmoothFreq2GPS_1_currentIndexChanged(2);//F5
    this->on_comboBoxSmoothPhase2GPS_1_currentIndexChanged(1);//L5P
    ui->frameSmoothGPS_1->setEnabled(false);
    ui->pushButtonMeasGNSSAdd->setEnabled(false);
    ui->pushButtonMeasGNSSDelete->setEnabled(false);
    //Galileo
    this->on_comboBoxFreqCodeGalileo_1_currentIndexChanged(0); //PC15
    ui->comboBoxMeasCodeFreq1Galileo_1->setCurrentIndex(1); //C1C
    ui->comboBoxMeasCodeFreq2Galileo_1->setCurrentIndex(1); //C5Q
    ui->comboBoxFreqCodeGalileo_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1Galileo_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq2Galileo_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGalileo_1->setCurrentIndex(2);//SBAS Dual StdDev
    this->on_comboBoxSmoothFreq1Galileo_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1Galileo_1_currentIndexChanged(1);//L1C
    this->on_comboBoxSmoothFreq2Galileo_1_currentIndexChanged(1);//F5
    this->on_comboBoxSmoothPhase2Galileo_1_currentIndexChanged(1);//L5Q
    ui->frameSmoothGalileo_1->setEnabled(false);
    //GEO
    this->on_comboBoxFreqCodeGEO_1_currentIndexChanged(0); //PC15
    ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(1); //C1C
    ui->comboBoxMeasCodeFreq2GEO_1->setCurrentIndex(1); //C5Q
    ui->comboBoxFreqCodeGEO_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GEO_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq2GEO_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGEO_1->setCurrentIndex(2);//SBAS Dual StdDev
    this->on_comboBoxSmoothFreq1GEO_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GEO_1_currentIndexChanged(1);//L1C
    this->on_comboBoxSmoothFreq2GEO_1_currentIndexChanged(1);//F5
    this->on_comboBoxSmoothPhase2GEO_1_currentIndexChanged(1);//L5Q
    ui->frameSmoothGEO_1->setEnabled(false);
    //BDS
    this->on_comboBoxFreqCodeBDS_1_currentIndexChanged(1); //PC15
    ui->comboBoxMeasCodeFreq1BDS_1->setCurrentIndex(1); //C1P
    ui->comboBoxMeasCodeFreq2BDS_1->setCurrentIndex(1); //C5P
    ui->comboBoxFreqCodeBDS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1BDS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq2BDS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeBDS_1->setCurrentIndex(2);//SBAS Dual StdDev
    this->on_comboBoxSmoothFreq1BDS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1BDS_1_currentIndexChanged(1);//L1P
    this->on_comboBoxSmoothFreq2BDS_1_currentIndexChanged(2);//F5
    this->on_comboBoxSmoothPhase2BDS_1_currentIndexChanged(1);//L5P
    ui->frameSmoothBDS_1->setEnabled(false);
    //QZSS
    this->on_comboBoxFreqCodeQZSS_1_currentIndexChanged(1); //PC15
    ui->comboBoxMeasCodeFreq1QZSS_1->setCurrentIndex(3); //C1C
    ui->comboBoxMeasCodeFreq2QZSS_1->setCurrentIndex(1); //C5Q
    ui->comboBoxFreqCodeQZSS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1QZSS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq2QZSS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeQZSS_1->setCurrentIndex(2);//SBAS Dual StdDev
    this->on_comboBoxSmoothFreq1QZSS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1QZSS_1_currentIndexChanged(1);//L1P
    this->on_comboBoxSmoothFreq2QZSS_1_currentIndexChanged(2);//F5
    this->on_comboBoxSmoothPhase2QZSS_1_currentIndexChanged(1);//L5P
    ui->frameSmoothQZSS_1->setEnabled(false);
    //others
    this->on_checkBoxEstimateTroposphere_clicked(false);
    ui->groupBoxTroposphere->setHidden(true);
    ui->checkBoxUseSigmaIonosphere->setChecked(false);
    ui->groupBoxIonosphere->setHidden(true);
    this->on_radioButtonWhiteNoiseClock_clicked();
    this->on_radioButtonWhiteNoiseISCB_clicked();
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(false);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(true);
    ui->checkBoxBackwardFiltering->setHidden(true);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    ui->groupBoxRefGNSSClock->setEnabled(false);
    this->on_groupBoxRefGNSSClock_clicked(false);
    ui->groupBoxISCB->setEnabled(false);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
    ui->checkBoxPrintUsererror->setChecked(true);
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
    ui->checkBoxPrintSbascor->setHidden(true);
    ui->checkBoxPrintSbasvar->setHidden(true);
    ui->checkBoxPrintSbasiono->setHidden(true);
    ui->checkBoxPrintSbasunsel->setHidden(true);
    ui->checkBoxPrintSbasDFMCCor->setHidden(false);
    ui->checkBoxPrintSbasDFMCVar->setHidden(false);
    ui->checkBoxPrintSbasDFMCUnsel->setHidden(false);
    ui->groupBoxSummaryConvergence->setHidden(true);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(false);
    ui->stackedWidgetTemplates->setCurrentIndex(1);
    ui->pushButtonTemplateSBASIonoComponents->setHidden(true);

    //Convertor
    this->on_checkBox_pegasus_clicked(false);
    ui->checkBox_pegasus->setHidden(true);
    ui->frame_holdingPegasusOptions->setHidden(true);
}
//DGNSS default configuration
void gLAB_GUI::setDGNSSDefault(){
    this->on_groupBoxConverterSBAS_clicked(false); // Converter
    this->on_groupBoxConverterDgnss_clicked(true); // Converter

    //Hide Main Logo and show all groupboxes in Input tab
    if (ui->labelMainLogo->isHidden()==false) {
        ui->labelMainLogo->setHidden(true);
        ui->tabInput->setContentsMargins(9,9,9,9);
        ui->frametabInputGroupboxes->setHidden(false);
    }

    // INPUT
    this->on_checkBoxSatAntex_clicked(false);
    this->on_checkBoxRecAntex_clicked(false);
    this->on_radioButtonOrbitBrdc_clicked();
    ui->checkBoxRinexNavFileHealth1->setHidden(true);
    ui->lineEditRinexNavFileHealth1->setHidden(true);
    ui->pushButtonRinexNavFileHealth1->setHidden(true);
    ui->checkBoxRinexNavFileHealth2->setHidden(true);
    ui->lineEditRinexNavFileHealth2->setHidden(true);
    ui->pushButtonRinexNavFileHealth2->setHidden(true);
    this->on_groupBoxAuxFiles_clicked(false);
    this->on_groupBoxP1C1correction_clicked(false);
    this->on_groupBoxP1P2correction_clicked(false);
    this->on_groupBoxUserAddedError_clicked(false);
    this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
    this->on_radioButtonGPSReceiverTypeFile_clicked();
    ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
    this->on_radioButtonIonoSourceBrdc_clicked();
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(0);
    ui->groupBoxIonoSource->setHidden(false);
    this->on_groupBoxIonoSource_clicked(false);
    QDate date = QDate(1979, 12, 31);
    ui->dateEdit1->setDate(date);
    ui->dateEdit2->setDate(date);
    ui->dateEdit3->setDate(date);
    //this->on_radioButtonRtcmRinexRover_clicked();
    this->on_radioButtonRtcmBaseline_clicked();

    // PREPROCESS
    ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    this->on_checkBoxDataDecimator_clicked(false);
    ui->lineEditDataDecimator->setText("");
    ui->checkBoxNcon->setChecked(false);
    ui->checkBoxDiscardEclipse->setChecked(false);
    this->on_checkBoxDiscardUnhealthy_clicked(true);
    ui->checkBoxDiscardMarginal->setChecked(true);
    ui->checkBoxLLI->setChecked(false);
    this->on_checkBoxNcon_clicked(false);
    ui->checkBoxSF->setChecked(true);
    ui->checkBoxMW->setChecked(false);
    ui->checkBoxLI->setChecked(false);
    ui->checkBoxIGF->setChecked(false);
    this->setCSdefaults();
    ui->lineEditElevMask->setText("5");
    ui->lineEditDataGap->setText("10");
    this->on_checkBoxGalileo_clicked(false);// Disable all Galileo satellites
    this->on_checkBoxGLONASS_clicked(false);// Disable all GLONASS satellites
    this->on_checkBoxGEO_clicked(false);// Disable all GEO satellites
    this->on_checkBoxBDS_clicked(false);// Disable all BDS satellites
    this->on_checkBoxQZSS_clicked(false);// Disable all QZSS satellites
    this->on_checkBoxIRNSS_clicked(false);// Disable all IRNSS satellites
    this->on_checkBoxGPS_clicked(true); // Enable all GPS satellites
    for (int i=0; i<MAX_GNSS; i++){
        CheckBoxGNSS[i]->setEnabled(false);
    }
    ui->checkBoxReceiverCodeJumps->setChecked(true);
    ui->checkBoxPrealignPhase->setChecked(true);
    this->on_checkBoxSNRThresholdMin_clicked(true);
    this->on_checkBoxSNRThresholdMax_clicked(true);
    this->on_comboBoxSNRThresholdsMin_currentIndexChanged(4);
    this->on_comboBoxSNRThresholdsMax_currentIndexChanged(8);
    SnrAdvancedMinWin->setSNRdefaults();
    SnrAdvancedMaxWin->setSNRdefaults();

    // MODELLING
    setModellingDefaults();
    ui->checkBoxSatClockOffset->setChecked(true);
    ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
    ui->checkBoxSatMovement->setChecked(true);
    ui->checkBoxEarthRotation->setChecked(true);
    this->on_checkBoxSatMassCentre_clicked(false);
    this->on_checkBoxAntennaPhase_clicked(false);
    this->on_checkBoxAntennaReference_clicked(true);
    ui->checkBoxRelativisticClock->setChecked(true);
    ui->checkBoxIonoCorrection->setEnabled(true);
    this->on_checkBoxIonoCorrection_clicked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(0);
    this->on_checkBoxTropoCorrection_clicked(true);
    ui->comboBoxTropoCorrection->setCurrentIndex(0);
    ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
    ui->checkBoxWindUp->setChecked(false);
    ui->checkBoxTides->setChecked(false);
    ui->checkBoxRelativisticPath->setChecked(false);
    ui->lineEditMaxAgeDgnss->setText("31");
    ui->lineEditMaxValueDGNSS->setText("500");
    ui->frameOptionButtonNavTypes->setHidden(true); //Hide buttons for moving navigation message types and default button
    ui->frameNavFreshTime->setHidden(true);

    //Set navigation message types
    QString option="-model:brdc:gps",type="LNAV",tmpString="";
    this->command_2_UserNavMessageTypes(&option,&type,&tmpString,0);
    ui->tableWidgetNavMessageTypeGPS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGalileo->setDisabled(true);
    ui->tableWidgetNavMessageTypeGLONASS->setDisabled(true);
    ui->tableWidgetNavMessageTypeGEO->setDisabled(true);
    ui->tableWidgetNavMessageTypeBDS->setDisabled(true);
    ui->tableWidgetNavMessageTypeQZSS->setDisabled(true);
    ui->tableWidgetNavMessageTypeIRNSS->setDisabled(true);

    //DCB
    this->on_groupBoxShowDCBOptions_clicked(false);
    //GPS
    this->on_groupBoxShowDCBOptionsGPS_clicked(false);
    ui->comboBoxDCBdfGPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
    ui->comboBoxISCsfL1CAGPS->setCurrentIndex(1);
    ui->comboBoxISCsfL2CGPS->setCurrentIndex(1);
    ui->comboBoxISCsfL5I5GPS->setCurrentIndex(1);
    ui->comboBoxISCsfL5Q5GPS->setCurrentIndex(1);
    //Galileo
    this->on_groupBoxShowDCBOptionsGalileo_clicked(false);
    ui->comboBoxDCBsfE1E5aGalileo->setCurrentIndex(1);
    ui->comboBoxDCBsfE1E5bGalileo->setCurrentIndex(1);
    //GLONASS
    this->on_groupBoxShowDCBOptionsGLONASS_clicked(false);
    ui->comboBoxDCBsfP1P2GLONASS->setCurrentIndex(1);
    //BDS
    this->on_groupBoxShowDCBOptionsBDS_clicked(false);
    ui->comboBoxDCBdfBDS->setCurrentIndex(0);
    ui->comboBoxDCBsfB2B6BDS->setCurrentIndex(1);
    ui->comboBoxDCBsfB7B6BDS->setCurrentIndex(1);
    ui->comboBoxDCBsfSP3BDS->setCurrentIndex(0);
    //QZSS
    this->on_groupBoxShowDCBOptionsQZSS_clicked(false);
    ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
    ui->comboBoxDCBsfC1CQZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL2CQZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL5I5QZSS->setCurrentIndex(1);
    ui->comboBoxISCsfL5Q5QZSS->setCurrentIndex(1);
    //IRNSS
    this->on_groupBoxShowDCBOptionsIRNSS_clicked(false);
    ui->comboBoxDCBsfC9C5IRNSS->setCurrentIndex(1);

    // FILTER
    setFilterDefaults();
    ui->lineEditSmoothing->setText("100");
    this->on_radioButtonSmoothing_clicked();
    ui->radioButtonDualFreq->setHidden(true);
    ui->radioButtonSingleFreq->setHidden(false);
    this->on_radioButtonSingleFreq_clicked();
    this->on_radioButtonKinematic_clicked();
    ui->radioButtonSelectionGraphic->setHidden(true);
    // measurement
    ui->checkBoxSetFreqMeasOrderGNSS->setEnabled(false);
    this->on_checkBoxSetFreqMeasOrderGNSS_clicked(false);
    //GPS
    this->on_comboBoxFreqCodeGPS_1_currentIndexChanged(0); //F1
    ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(3); //C1C
    ui->comboBoxFreqCodeGPS_1->setEnabled(false);
    ui->comboBoxMeasCodeFreq1GPS_1->setEnabled(false);
    ui->stackedWidgetStdDevCodeGPS_1->setCurrentIndex(3);//DGNSS StdDev
    this->on_comboBoxSmoothFreq1GPS_1_currentIndexChanged(0);//F1
    this->on_comboBoxSmoothPhase1GPS_1_currentIndexChanged(1);//L1P
    ui->frameSmoothGPS_1->setEnabled(false);
    //others
    this->on_checkBoxEstimateTroposphere_clicked(false);
    ui->groupBoxTroposphere->setHidden(true);
    ui->checkBoxUseSigmaIonosphere->setChecked(false);
    ui->groupBoxIonosphere->setHidden(true);
    this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(false);
    this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(true);
    ui->lineEditSmoothMinDgnss->setText("360");
    this->on_checkBoxMaxHDOP_clicked(false);
    this->on_checkBoxMaxPDOP_clicked(false);
    this->on_checkBoxMaxGDOP_clicked(true);
    ui->checkBoxHDOPorPDOP->setChecked(false);
    this->on_checkBoxPrefitOutliers_clicked(true);
    this->on_groupBoxStanfordESA_clicked(false);
    ui->checkBoxBackwardFiltering->setHidden(true);
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    ui->groupBoxRefGNSSClock->setEnabled(false);
    this->on_groupBoxRefGNSSClock_clicked(false);
    ui->groupBoxISCB->setEnabled(false);
    this->on_groupBoxISCB_clicked(false);
    this->on_pushButtonISCBEstimateAll_clicked();
    ui->comboBoxISCBUnit->setCurrentIndex(0);
    ui->pushButtonMeasGNSSAdd->setEnabled(false);
    ui->pushButtonMeasGNSSDelete->setEnabled(false);

    // OUTPUT
    this->on_pushButtonCommonNavigationMessagesNone_clicked();
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
    ui->checkBoxPrintUsererror->setChecked(true);
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
    ui->groupBoxSummaryConvergence->setHidden(true);

    // ANALYSIS
    ui->framePlotTemplates4SBAS->setHidden(true);
    ui->stackedWidgetTemplates->setCurrentIndex(2);

    // CONVERTER
    ui->dateEdit4->setDate(date);
    ui->comboBoxConverterDgnssOutputRinex->setCurrentIndex(1);
}

///////////// Templates /////////////
// SPP Template
void gLAB_GUI::on_actionSPP_triggered() {
    ui->labelCurrentTemplate->setText("SPP");
    ui->actionSPP->setChecked(true);

    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxReferenceStation_clicked(false);
    this->setSPPDefault();
}
// PPP Template
void gLAB_GUI::on_actionPPP_triggered() {
    ui->labelCurrentTemplate->setText("PPP");
    ui->actionPPP->setChecked(true);

    this->on_groupBoxSbas_clicked(false);
    this->on_groupBoxReferenceStation_clicked(false);
    this->setPPPDefault();
}
// SBAS 1F Template
void gLAB_GUI::on_actionSBAS_1F_triggered() {
    ui->labelCurrentTemplate->setText("SBAS 1F");
    ui->actionSBAS_1F->setChecked(true);

    this->on_comboBoxSbasInput_currentIndexChanged(0);
}
// SBAS DFMC
void gLAB_GUI::on_actionSBAS_DFMC_triggered(){
    ui->labelCurrentTemplate->setText("SBAS DFMC");
    ui->actionSBAS_DFMC->setChecked(true);

    this->on_comboBoxSbasInput_currentIndexChanged(1);
}
// DGNSS Template
void gLAB_GUI::on_actionDGNSS_triggered() {
    ui->labelCurrentTemplate->setText("DGNSS");
    ui->actionDGNSS->setChecked(true);

    this->on_groupBoxReferenceStation_clicked(true);
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
    ui->actionSBAS_1F->setEnabled(true);
    ui->actionSBAS_DFMC->setEnabled(true);
    ui->actionSBAS_DFMC->setCheckable(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[0]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
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
    ui->actionSBAS_1F->setEnabled(true);
    ui->actionSBAS_DFMC->setEnabled(true);
    ui->actionSBAS_DFMC->setCheckable(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void gLAB_GUI::on_actionConverter_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(2);
    ui->stackedWidgetMainButtons2->setCurrentIndex(2);
    ui->labelCurrentTemplateFixed->setHidden(false);
    ui->labelCurrentTemplate->setHidden(false);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS_1F->setEnabled(true);
    ui->actionSBAS_DFMC->setEnabled(true);
    ui->actionSBAS_DFMC->setCheckable(true);
    ui->actionDGNSS->setEnabled(true);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[2]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void gLAB_GUI::on_actionCompare_Orbits_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(3);
    ui->stackedWidgetMainButtons2->setCurrentIndex(3);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS_1F->setEnabled(false);
    ui->actionSBAS_DFMC->setEnabled(false);
    ui->actionSBAS_DFMC->setCheckable(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[3]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void gLAB_GUI::on_actionShow_Orbits_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(4);
    ui->stackedWidgetMainButtons2->setCurrentIndex(4);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS_1F->setEnabled(false);
    ui->actionSBAS_DFMC->setEnabled(false);
    ui->actionSBAS_DFMC->setCheckable(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[4]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void gLAB_GUI::on_actionAdd_User_Error_to_RINEX_triggered() {
    ui->stackedWidgetMainWindow->setCurrentIndex(5);
    ui->stackedWidgetMainButtons2->setCurrentIndex(5);
    ui->labelCurrentTemplateFixed->setHidden(true);
    ui->labelCurrentTemplate->setHidden(true);
    ui->actionSPP->setEnabled(false);
    ui->actionPPP->setEnabled(false);
    ui->actionSBAS_1F->setEnabled(false);
    ui->actionSBAS_DFMC->setEnabled(false);
    ui->actionSBAS_DFMC->setCheckable(false);
    ui->actionDGNSS->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(true);
    if ( configFileName[5]!="" ) ui->actionShow->setEnabled(true);
    else ui->actionShow->setEnabled(false);
    // set scroll bar to initial place
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void gLAB_GUI::on_actionExit_triggered() {
    qApp->closeAllWindows();
}
//////////// End of The modes of gLAB /////////////


// Function to set the correct size in the group boxes
void gLAB_GUI::setCorrectSizes() {
    QFont font;
    #ifdef Q_OS_LINUX
      font.setPointSize(9);
    #elif defined(Q_OS_WIN32)
      font.setPointSize(9);
    #elif defined(Q_OS_MAC)
      font.setPointSize(13);
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
    ui->groupBoxSF->setFont(font);
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
    ui->groupBoxShowOldMessages->setFont(font);
    ui->groupBoxSetOBADParameters->setFont(font);
    ui->groupBoxSetDFREICorrections->setFont(font);
    ui->groupBoxSetSepcificSigmas->setFont(font);
    // Filter
    ui->groupBoxMeasurements->setFont(font);
    ui->groupBoxSmoothing->setFont(font);
    ui->groupBoxMeasurementConfigurationAndNoise->setFont(font);
    ui->groupBoxParameters->setFont(font);
    ui->groupBoxDOPFilter->setFont(font);
    ui->groupBoxAvailableFrequencies->setFont(font);
    ui->groupBoxTroposphere->setFont(font);
    ui->groupBoxIonosphere->setFont(font);
    ui->groupBoxOtherOptions->setFont(font);
    ui->groupBoxRefGNSSClock->setFont(font);
    ui->groupBoxISCB->setFont(font);
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
    ui->groupBoxRinexNavFileGLOAddError->setFont(font);
    ui->groupBoxAddErrorRinexOutput->setFont(font);
    ui->groupBoxAddErrorOutput->setFont(font);
    ui->groupBoxOutputMessagesAddError->setFont(font);
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
// Function to show tooltip in a window with scroll bar
int gLAB_GUI::showToolTipinQLineEdit(const QPoint &pos, const QString strTT, int tabflag){
    if (strTT.size()>0){
        int fontsize=9;
        #ifdef Q_OS_LINUX
          fontsize=9;
        #elif defined(Q_OS_WIN32)
          fontsize=9;
        #elif defined(Q_OS_MAC)
          fontsize=3;
        #endif
        double nRow=strTT.size()*fontsize/gLABToolTipWin->maximumWidth();

        if (tabflag==1){ // Tab tooltip
            // set gLABToolTipWin position
            gLABToolTipWin->setModal(true);
            gLABToolTipWin->show();
            gLABToolTipWin->resize(gLABToolTipWin->maximumWidth()/2,200);
            gLABToolTipWin->setTooltip(strTT);
            gLABToolTipWin->resize(gLABToolTipWin->maximumWidth()/2,gLABToolTipWin->tHeight()+5);
            QPoint movePos(pos.x()-10,pos.y()-10);
            QRect screenRect = QGuiApplication::screens().at(0)->geometry(), TTRect = gLABToolTipWin->geometry();
            //if too right
            if (movePos.x()+TTRect.width()>screenRect.width()) movePos.setX(movePos.x()-TTRect.width()+25);
            //if too left
            if (movePos.x()<0) movePos.setX(0);
            //if too bottom
            if ( (movePos.y()+TTRect.height()>screenRect.height())) movePos.setY(movePos.y()-TTRect.height()+25);
            //if too top
            if (movePos.y()<0) movePos.setY(0);
            gLABToolTipWin->move(movePos);
        } else if (nRow<3){ // other (short) tooltip
            return 0;
        } else { // other (long) tooltip
            // set gLABToolTipWin position
            gLABToolTipWin->setModal(true);
            gLABToolTipWin->show();
            gLABToolTipWin->resize(gLABToolTipWin->maximumWidth(),200);
            gLABToolTipWin->setTooltip(strTT);
            gLABToolTipWin->resize(gLABToolTipWin->maximumWidth(),gLABToolTipWin->tHeight()+5);
            QPoint movePos(pos.x()-10,pos.y()-10);
            QRect screenRect = QGuiApplication::screens().at(0)->geometry(), TTRect = gLABToolTipWin->geometry();
            //if too right
            if (movePos.x()+TTRect.width()>screenRect.width()) movePos.setX(movePos.x()-TTRect.width()+25);
            //if too left
            if (movePos.x()<0) movePos.setX(0);
            //if too bottom
            if ( (movePos.y()+TTRect.height()>screenRect.height())) movePos.setY(movePos.y()-TTRect.height()+25);
            //if too top
            if (movePos.y()<0) movePos.setY(0);
            gLABToolTipWin->move(movePos);
            return 1;
        }
    }
    return 0;
}

// Function to clear tableWidget selection using mouse press event
void gLAB_GUI::mousePressEvent(QMouseEvent * event) {
    // positioning
    if ( ui->stackedWidgetMainWindow->currentIndex()==0 ){
        //modelling
        if ( ui->tabWidget->currentIndex()==2 ){
            ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
            ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
        }
        //filter
        else if ( ui->tabWidget->currentIndex()==3 ){
            ui->tableWidgetISCB->setCurrentItem(nullptr);
            ui->tableWidgetRefGNSSClock->setCurrentItem(nullptr);
        }
    }
    // compare orbit and clock
    else if ( ui->stackedWidgetMainWindow->currentIndex()==3 ){
        if ( ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0 ){
            ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
        } else if ( ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1 ){
            ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
        }
    }
    // show orbit and clock
    else if ( ui->stackedWidgetMainWindow->currentIndex()==4 ){
        ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
        ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
    }

    return QWidget::mousePressEvent(event);
}

// Function to turn on or off all the tooltips and forbidden the wheel scroll in combo boxes
// NOTE: to avoid the mouse wheel efect over the combo boxes, set the its focus to strong focus
bool gLAB_GUI::eventFilter(QObject *obj, QEvent *event) {
    QComboBox* combo = qobject_cast<QComboBox*>(obj);
    QWidget* widget4Tooltip = qobject_cast<QWidget*>(obj);
    QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
    QPoint position = helpEvent->pos();
    if ( event->type() == QEvent::ToolTip ) {
        // Set the tooltips only for the tabs
        if ( obj == ui->tabWidget->tabBar() ) {
            int index = ui->tabWidget->tabBar()->tabAt(position);
            if ( index == 0 && ui->actionTooltips->isChecked() == true ) {
                this->showToolTipinQLineEdit(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Input section</b><br><br>This section provides all the configuration options to select the input files for gLAB.<br>",1);
            } else if ( index == 1 && ui->actionTooltips->isChecked() == true ) {
                this->showToolTipinQLineEdit(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Preprocess section</b><br><br>This section provides all the configuration options to preprocess the input data. "
                    "In particular, it allows changing the decimation rate, the elevation mask, the cycle-slip detection, "
                    "and selecting individual satellites for the processing.<br>",1);
            } else if ( index == 2 && ui->actionTooltips->isChecked() == true ) {
                this->showToolTipinQLineEdit(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Modelling section</b><br><br>This section provides the configuration options to set/unset each individual model that is used by gLAB.<br>",1);
            } else if ( index == 3 && ui->actionTooltips->isChecked() == true ) {
                this->showToolTipinQLineEdit(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Filter section</b><br><br>This section provides all the configuration options to specify the behaviour of the Kalman Filter. "
                    "In particular, the selection of measurement and the parameters to be estimated can be chosen in this section.<br>",1);
            } else if ( index == 4 && ui->actionTooltips->isChecked() == true ) {
                this->showToolTipinQLineEdit(ui->tabWidget->tabBar()->mapToGlobal(position),
                    "<b>Output section</b><br><br>This section provides all the configuration options to select which files and messages are output.<br>",1);
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
        } else if (ui->actionTooltips->isChecked() == true){
            if (widget4Tooltip) {
                if (this->showToolTipinQLineEdit(helpEvent->globalPos(),qobject_cast<QWidget*>(obj)->toolTip(),0)) {
                    return true;
                } else {
                    return QMainWindow::eventFilter(obj, event);
                }
            }
            return true;
        }
    }
    // Disable mouse wheel in combo boxes
    else if ( event->type() == QEvent::Wheel ) {
        if ( combo && !combo->hasFocus() ) {
            return true;
        }
    }
    else if (event->type() == QEvent::FocusOut) {
        if (combo) {
            //To fix entire Qt losing focus (and switching to background program) when a combo box is open
            return true;
        }
    }
    else {
        return QMainWindow::eventFilter(obj, event);
    }
    // Obviously innecessary but written to avoid warning
    return QMainWindow::eventFilter(obj, event);
}

// Function to visit the gAGE webpage
void gLAB_GUI::on_actionVisit_gAGE_website_triggered() {
    QDesktopServices::openUrl(QUrl("https://gage.upc.edu"));
}

// Function to visit the gLAB release notes
void gLAB_GUI::on_actionRelease_notes_triggered() {
    QDesktopServices::openUrl(QUrl("https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-release-notes"));
}

// Function to visit the gLAB explained formats
void gLAB_GUI::on_actionExplained_Formats_triggered() {
    QDesktopServices::openUrl(QUrl("https://gage.upc.edu/en/learning-materials/library/gnss-format-descriptions"));
}

// Function to visit the a web with GNSS Calendar formats
void gLAB_GUI::on_actionGNSS_Calendar_triggered() {
    QDesktopServices::openUrl(QUrl("https://www.gnsscalendar.com/"));
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
        DateConvWin->setModal(true);
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
    CoordConvWin->setModal(true);
    CoordConvWin->show();
}

// Function to show the gLAB user manual
void gLAB_GUI::on_actionManual_triggered() {
    #ifndef Q_OS_WIN32
        QProcess *processUserManual = new QProcess(this);
    #endif
        QString program;
        QFile HelpFile(":/data/gLAB_SUM.pdf");
        //Qt copy option does not overwrite files. We need to erase first the file if it exists
        if (QFile::exists(qApp->applicationDirPath().append("/gLAB_SUM.pdf"))) {
            QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_SUM.pdf"),QFileDevice::WriteUser);
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

// Function to show the gLAB FAQ
void gLAB_GUI::on_actionFAQ_triggered() {
    QProcess *processFAQ = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_FAQ.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_FAQ.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_FAQ.txt"),QFileDevice::WriteUser);
        QFile::remove(qApp->applicationDirPath().append("/gLAB_FAQ.txt"));
    }
    HelpFile.copy(qApp->applicationDirPath().append("/gLAB_FAQ.txt"));

    // Based on the OS open the text editor
    #ifdef Q_OS_LINUX
        program = QString("gedit");
        arguments << qApp->applicationDirPath().append("/gLAB_FAQ.txt");
    #elif defined(Q_OS_WIN32)
        program = QString("notepad");
        arguments << qApp->applicationDirPath().append("/gLAB_FAQ.txt");
    #elif defined(Q_OS_MAC)
        program = QString("open");
        arguments << "-t" << qApp->applicationDirPath().append("/gLAB_FAQ.txt");
    #endif

    // Execute the program
    processFAQ->start(program, arguments);
}

// Function to show the gLAB User adder error error example file
void gLAB_GUI::on_actionUser_Added_Error_File_Manual_triggered() {
    QProcess *processShow = new QProcess(this);
    QString program;
    QStringList arguments;

    QFile HelpFile(":/data/gLAB_User_Error_File_Example.txt");
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_User_Error_File_Example.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_Sigma_Multipath_File_Example.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_Reference_Position_File_Example.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_help.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_command_line_help.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_messages.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_command_line_messages.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/gLAB_command_line_sbas_maps_description.txt"),QFileDevice::WriteUser);
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
    //Qt copy option does not overwrite files. We need to erase first the file if it exists
    if (QFile::exists(qApp->applicationDirPath().append("/graph_command_line_help.txt"))) {
        QFile::setPermissions(qApp->applicationDirPath().append("/graph_command_line_help.txt"),QFileDevice::WriteUser);
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

// Function to show Contact us
void gLAB_GUI::on_actionContactUs_triggered(){
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    msgBox.setWindowTitle("Contact us");
    msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(
                   "<p align='center'>Please e-mail any bugs, comments or requests to: "+
                   QString("<b><font color='#0000FF'>%1@%2</font></b></p></br>").arg("glab.gage").arg("upc.edu"));
    msgBox.exec();
}

// Function to show the About of gLAB
void gLAB_GUI::on_actionAboutgLAB_triggered() {
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    msgBox.setWindowTitle("About gLAB");
    msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(QString("<p align='center'><b>gLAB v%1.%2</b></p></br>").arg(version, 3, 'f', 1, '0').arg(revision) +

                   "<span style='font-weight:normal'><p align='center'>gLAB is a complete GNSS analysis tool for both educational and professional purposes. "+
                   "gLAB is given as is for free (please see the license). gLAB allows a full customisation "+
                   "of its options and provides precise point positioning capabilities on the centimetre level.</p></br>"+

                   "<p align='center'>gLAB is divided in three different modules:<br>"+
                   "Data Processing Core (DPC) - For all the processing.<br>"+
                   "Graphic User Interface (GUI) - User friendly graphical interface.<br>"+
                   "Data Analysis Tool (DAT) - For plotting the results.</p></br>"+

                   "<p align='center'>Both the processing core and the plotting tool can be executed "+
                   "independently from the GUI.</p></br>"+

                   "<p align='center'>The GUI has been built with <a href='https://www.qt.io/'>Qt</a> (v" + QT_VERSION_STR +").</p></br>"+

                   "<p align='center'>Please e-mail any bugs, comments or requests to: "+
                   QString("<b><font color='#0000FF'>%1@%2</font></b></p></br>").arg("glab.gage").arg("upc.edu") +

                   QString("<p align='center'>\u00a9 2009 - %1 gAGE/UPC & ESA</p></br>").arg(local.toString("yyyy")));
    msgBox.exec();
}

// Function to show the Credits of gLAB
void gLAB_GUI::on_actionCredits_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    msgBox.setWindowTitle("Credits");
    //msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Jaume Sanz [Supervisor]</br>"

                   "<p align='left'>Written by:</br>"

                   "<p align='left'>Pere Ramos-Bosch [DPC, GUI, DAT]</br>"

                   "<p align='left'>Adria Rovira-Garcia [GUI, DAT]</br>"

                   "<p align='left'>Deimos Ibáñez Segura [DPC, GUI, DAT]</br>"

                   "<p align='left'>Jesús Romero Sánchez [DPC, GUI]</br>"

                   "<p align='left'>Yixie Shao [DPC, DAT]</br>"

                   "<p align='left'>Mowen Li [GUI]</br>");
    msgBox.exec();
}

// Function to show the License of gLAB
void gLAB_GUI::on_actionLicense_triggered() {
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    msgBox.setWindowTitle("License");
    msgBox.setTextFormat(Qt::RichText);
    //msgBox.setIconPixmap(QPixmap(":/data/gage_logo.png"));
    msgBox.setText(QString("<span style='font-weight:normal'><p align='left'>Copyright 2009-%1 gAGE/UPC & ESA</br>").arg(local.toString("yyyy")) +

                   "<p align='left'>The <b>gLAB's GUI (Graphical User Interface)</b> is licensed under the Lesser GNU General Public License (LGPL) version 3.\nYou may obtain a copy of the GPL and LGPL Licenses at:</p></br>"

                   "<p align='left'><a href='https://www.gnu.org/licenses/gpl.txt'>GPL License</a><br>"
                   "<a href='https://www.gnu.org/licenses/lgpl.txt'>LGPL License</a></p></br>"

                   "<p align='left'>The <b>gLAB's GUI (Graphical User Interface)</b> is free software: you can redistribute it and/or modify "
                       "it under the terms of the Lesser GNU General Public License as published by "
                       "the Free Software Foundation, either version 3 of the License, or "
                       "(at your option) any later version.</br>"
                       "This program is distributed in the hope that it will be useful, "
                       "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                       "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                       "Lesser GNU General Public License for more details.</br></br></br></p>"

                   "<p align='left'>The <b>gLAB processing core and graphical tool</b> is licensed under the Apache License, Version 2.0 (the \"License\").\nYou may obtain a copy of the License at:</p></br>"

                   "<p align='left'><a href='https://www.apache.org/licenses/LICENSE-2.0'>https://www.apache.org/licenses/LICENSE-2.0</a></p></br>"

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
    QDesktopServices::openUrl(QUrl("https://terras.gsi.go.jp/ja/crx2rnx.html"));
}

// Function to visit the GFZ RINEX version converter
void gLAB_GUI::on_actionGFZ_RINEX_version_converter_triggered() {
   QDesktopServices::openUrl(QUrl("https://gnss.gfz-potsdam.de/services/gfzrnx"));
}

// Function to show RINEX file extension types
void gLAB_GUI::on_actionRINEX_file_extension_types_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
                   ".YYf ⇒ BDS      RINEX Navigation File (version 3)<br>"
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

    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}


// Function to see IGS website with Standards
void gLAB_GUI::on_actionIGS_Standards_Website_triggered() {
    QDesktopServices::openUrl(QUrl("https://igs.org/formats-and-standards/"));
}

// Function to see RINEX and SP3 standard list
void gLAB_GUI::on_actionRINEX_SP3_files_triggered() {
    QDesktopServices::openUrl(QUrl("https://files.igs.org/pub/data/format/"));
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
    QDesktopServices::openUrl(QUrl("https://files.igs.org/pub/data/format/antex14.txt"));
}

// Function to see EMS standards
void gLAB_GUI::on_actionEMS_files_triggered() {
    QDesktopServices::openUrl(QUrl("http://www.egnos-pro.esa.int/ems/new.html"));
}

// Function to visit the GNSS Data Processing book website
void gLAB_GUI::on_actionGNSS_Tutorial_Book_triggered() {
    QDesktopServices::openUrl(QUrl("https://gage.upc.edu/en/learning-materials/library/gnss-books/gnss-data-processing-book"));
}

// Function to visit the GNSS Master Course website
void gLAB_GUI::on_actionMaster_triggered() {
    QDesktopServices::openUrl(QUrl("https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-tutorials/gnss-tutorials"));
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

    int versionInt=static_cast<int>(version*10);
    int ver = static_cast<int>(versionaux.toDouble()*10);
    int rev = revisionaux.toInt();

    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    if ( ver == 0 && rev == 0 ) {
        messageBox.critical(nullptr, "Connection problem",
                            "Cannot connect to server.\nPlease, review your Internet connection and try it again.\n");
    } else if ( versionInt > ver ||( versionInt==ver && revision >= rev) ) {
        messageBox.setWindowTitle("Version check");
        messageBox.setText(QString("<p align='left'><br>The current gLAB version v%1.%2 is the latest.</br><br></br>").arg(version, 3, 'f', 1, '0').arg(revision));
        messageBox.exec();
    } else if ( versionInt < ver ||( versionInt==ver && revision < rev) ) {
        messageBox.setWindowTitle("Version check");
        messageBox.setTextFormat(Qt::RichText);
        messageBox.setText(QString("<p align='left'><br>There is a new version available: gLAB v%1.%2.</br><br>Please check <a href='http://gage.upc.es/gLAB'>http://gage.upc.es/gLAB</a> to obtain it.</br><br></br>").arg(static_cast<double>(ver)/10., 3, 'f', 1, '0').arg(rev));
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
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Observation Files Version 2");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX measurement files:<br>"
                   "<a href='http://garner.ucsd.edu/pub/rinex/'>http://garner.ucsd.edu/pub/rinex/</a><br>"
                   "<a href='https://epncb.oma.be/ftp/RINEX/'>https://epncb.oma.be/ftp/RINEX/</a><br>"
                   "<a href='https://geodesy.noaa.gov/corsdata/rinex/'>https://geodesy.noaa.gov/corsdata/rinex/</a><br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/rinex/obs'>https://gage-data.earthscope.org/archive/gnss/rinex/obs</a> (requires free registration)<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGS/obs/'>https://igs.bkg.bund.de/root_ftp/IGS/obs/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/GREF/obs/'>https://igs.bkg.bund.de/root_ftp/GREF/obs/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MISC/obs/'>https://igs.bkg.bund.de/root_ftp/MISC/obs/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MGEX/obs/'>https://igs.bkg.bund.de/root_ftp/MGEX/obs/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/obs/'>https://igs.bkg.bund.de/root_ftp/EUREF/obs/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGLOS/obs/'>https://igs.bkg.bund.de/root_ftp/IGLOS/obs/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz):<br>"
                   "<a href='http://garner.ucsd.edu/pub/rinex_highrate/'>http://garner.ucsd.edu/pub/rinex_highrate/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/highrate/'>ftp://gssc.esa.int/gnss/data/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGS/highrate/'>https://igs.bkg.bund.de/root_ftp/IGS/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/GREF/highrate/'>https://igs.bkg.bund.de/root_ftp/GREF/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MISC/highrate/'>https://igs.bkg.bund.de/root_ftp/MISC/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MGEX/highrate/'>https://igs.bkg.bund.de/root_ftp/MGEX/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/highrate/'>https://igs.bkg.bund.de/root_ftp/EUREF/highrate/</a><br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/highrate'>https://gage-data.earthscope.org/archive/gnss/highrate</a> (requires free registration)<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/highrate/'>https://cddis.nasa.gov/archive/gnss/data/highrate/</a> (requires free registration)<br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/highrate/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/highrate/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz) with QZSS (unofficial RINEX 2 version):<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/rinex/'>https://www.enri.go.jp/cnspub/sat/data/rinex/</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the RINEX Files
void gLAB_GUI::on_actionRINEXObsVersion_3_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(550, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Observation Files Version 3");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX measurement files:<br>"
                    "<a href='ftp://igs.ensg.ign.fr/pub/igs/data/rinex3/'>ftp://igs.ensg.ign.fr/pub/igs/data/rinex3/</a><br>"
                   "<a href='https://epncb.oma.be/ftp/RINEX/'>https://epncb.oma.be/ftp/RINEX/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a> (requires free registration)<br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/rinex3/'>https://gage-data.earthscope.org/archive/gnss/rinex3</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGS/obs_v3/'>https://igs.bkg.bund.de/root_ftp/IGS/obs_v3/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MISC/obs_v3/'>https://igs.bkg.bund.de/root_ftp/MISC/obs_v3/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MGEX/obs_v3/'>https://igs.bkg.bund.de/root_ftp/MGEX/obs_v3/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/obs_v3/'>https://igs.bkg.bund.de/root_ftp/EUREF/obs_v3/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/</a> (requires free registration)<br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>RINEX measurement files (1 Hz):<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/highrate/'>https://cddis.nasa.gov/archive/gnss/data/highrate/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/highrate/'>ftp://gssc.esa.int/gnss/data/highrate/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/highrate/'>https://igs.bkg.bund.de/root_ftp/EUREF/highrate/</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

void gLAB_GUI::on_actionRINEXNavVersion_2_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Navigation Files Version 2");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>All or Mixed constellation RINEX Navigation files:<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a> (requires free registration)<br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/rinex/nav/'>https://gage-data.earthscope.org/archive/gnss/rinex/nav/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/'>ftp://ftp.ga.gov.au/geodesy-outgoing/gnss/data/daily/</a></p>"

                   "<p align='left'>GPS RINEX Navigation files:<br>"
                   "<a href='http://garner.ucsd.edu/pub/nav/'>http://garner.ucsd.edu/pub/nav/</a></p>"

                   "<p align='left'>GPS and Galileo RINEX Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/</a></p>"

                   "<p align='left'>GPS and Glonass RINEX Navigation files:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGS/BRDC/'>https://igs.bkg.bund.de/root_ftp/IGS/BRDC/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/GREF/BRDC/'>https://igs.bkg.bund.de/root_ftp/GREF/BRDC/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/BRDC/'>https://igs.bkg.bund.de/root_ftp/EUREF/BRDC/</a></p>"

                   "<p align='left'>GEO Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/H/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/H/</a><br>"
                   "<a href='ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/H/'>ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/H/</a></p>"

                   "<p align='left'>QZSS GEO Navigation files:<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/geonav/'>https://www.enri.go.jp/cnspub/sat/data/geonav/</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

void gLAB_GUI::on_actionRINEXNavVersion_3_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(610, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: RINEX Navigation Files Version 3");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>All or Mixed constellation RINEX Navigation files:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/IGS/BRDC/'>https://igs.bkg.bund.de/root_ftp/IGS/BRDC/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/EUREF/BRDC/'>https://igs.bkg.bund.de/root_ftp/EUREF/BRDC/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/daily/'>https://cddis.nasa.gov/archive/gnss/data/daily/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/data/daily/'>ftp://gssc.esa.int/gnss/data/daily/</a><br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/</a> (requires free registration)</p>"

                   "<p align='left'>GPS and Galileo RINEX Navigation files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/NAV/</a></p>"

                   "<p align='left'>Mixed constellation RINEX Navigation files:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MGEX/BRDC/'>https://igs.bkg.bund.de/root_ftp/MGEX/BRDC/</a><br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/MGEX/BRDC_v3/'>https://igs.bkg.bund.de/root_ftp/MGEX/BRDC_v3/</a><br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/rinex3/nav/'>https://gage-data.earthscope.org/archive/gnss/rinex3/nav/</a> (requires free registration)<br>"
                   "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/</a> (requires free registration)</p>"

                    "<p align='left'>GPS and QZSS Navigation files with LNAV and CNAV messages (unofficial RINEX version):<br>"
                    "<a href='https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/'>https://cddis.nasa.gov/archive/gnss/data/campaign/mgex/daily/rinex3/2014/cnav/</a> (requires free registration)</p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download Precise Files
void gLAB_GUI::on_actionPrecise_Files_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Precise Files");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Precise orbits and clocks (SP3, CLK and SINEX files):<br>"
                   "<a href='http://garner.ucsd.edu/pub/products/'>http://garner.ucsd.edu/pub/products/</a><br>"
                   "<a href='http://ftp.aiub.unibe.ch/CODE/'>http://ftp.aiub.unibe.ch/CODE/</a><br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/glonass/products/'>https://cddis.gsfc.nasa.gov/archive/glonass/products/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/'>ftp://gssc.esa.int/gnss/products/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/pub/GNSS/products/'>ftp://ftp.gfz-potsdam.de/pub/GNSS/products/</a></p>"

                   "<p align='left'>Mixed files (All constellations):<br>"
                   "<a href='ftp://igs.ign.fr/pub/igs/products/mgex/'>ftp://igs.ign.fr/pub/igs/products/mgex/</a><br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/gnss/products/'>https://cddis.gsfc.nasa.gov/archive/gnss/products/</a> (requires free registration)</p>"


                   "<p align='left'>SINEX files:<br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/gnss/products/'>https://cddis.gsfc.nasa.gov/archive/gnss/products/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/'>ftp://gssc.esa.int/gnss/products/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/pub/GNSS/metadata/station/snx/'>ftp://ftp.gfz-potsdam.de/pub/GNSS/metadata/station/snx/</a><br>"
                   "<a href='https://gage-data.earthscope.org/archive/gnss/products/sinex/'>https://gage-data.earthscope.org/archive/gnss/products/sinex/</a> (requires free registration)<br>"
                   "<a href='ftp://ftp.sirgas.org/pub/gps/SIRGAS/'>ftp://ftp.sirgas.org/pub/gps/SIRGAS/</a></p>");

    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download SBAS Files
void gLAB_GUI::on_actionSBAS_Files_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(450, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: SBAS Files");
    msgBox.setMinimumWidth(1000);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>RINEX-B files:<br>"
                   "<a href='ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/MSG/'>ftp://serenad-public.cnes.fr/SERENAD0/FROM_NTMFV2/MSG/</a><br>"
                   "<a href='ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/MSG/'>ftp://serenad-public.essp-sas.eu/SERENAD0/FROM_ESSP/MSG/</a></p>"

                   "<p align='left'>EMS files with QZSS (unofficial EMS version):<br>"
                   "<a href='https://www.enri.go.jp/cnspub/sat/data/ems/'>https://www.enri.go.jp/cnspub/sat/data/ems/</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Download Other Files
void gLAB_GUI::on_actionOther_Files_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(560, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Other Files");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>ANTEX files (antenna corrections):<br>"
                   "<a href='https://files.igs.org/pub/station/general/pcv_archive/'>https://files.igs.org/pub/station/general/pcv_archive/</a><br>"
                   "<a href='ftp://ftp.gfz-potsdam.de/pub/GNSS/metadata/satellite/ANTEX/'>ftp://ftp.gfz-potsdam.de/pub/GNSS/metadata/satellite/ANTEX/</a><br>"
                   "<a href='https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs20.atx'>https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs20.atx</a><br>"
                   "<a href='https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs14.atx'>https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs14.atx</a><br>"
                   "<a href='https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs08.atx'>https://www.ngs.noaa.gov/ANTCAL/LoadFile?file=ngs08.atx</a></p>"

                   "<p align='left'>IONEX files (ionosphere):<br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/gps/products/ionex/'>https://cddis.gsfc.nasa.gov/archive/gps/products/ionex/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/ionex/'>ftp://gssc.esa.int/gnss/products/ionex/</a></p>"

                   "<p align='left'>ZTD files (troposphere):<br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/gps/products/troposphere/new/'>https://cddis.gsfc.nasa.gov/archive/gps/products/troposphere/new/</a> (requires free registration)<br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/troposphere_zpd/'>ftp://gssc.esa.int/gnss/products/troposphere_zpd/</a></p>"

                   "<p align='left'>DCB files (P1-C1 and P1-P2):<br>"
                   "<a href='http://ftp.aiub.unibe.ch/CODE/'>http://ftp.aiub.unibe.ch/CODE/</a></p>"

                   "<p align='left'>SINEX BIAS DSB files (multiconstellation DCBs for converting measurements):<br>"
                   "<a href='https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/dcb/'>https://cddis.gsfc.nasa.gov/archive/gps/products/mgex/dcb/</a> (requires free registration)</p>"

                   "<p align='left'>SINEX BIAS OSB files (multiconstellation absolute DCBs):<br>"
                   "<a href='http://ftp.aiub.unibe.ch/CODE/'>http://ftp.aiub.unibe.ch/CODE/</a><br>"
                   "<a href='ftp://gssc.esa.int/gnss/products/1962/mgex/'>ftp://gssc.esa.int/gnss/products/1962/mgex/</a></p>"

                   "<p align='left'>GPS Receiver types:<br>"
                   "<a href='https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/etc/GPS_Receiver_Types.gz'>https://sideshow.jpl.nasa.gov/pub/gipsy_products/gipsy_params/etc/GPS_Receiver_Types.gz</a></p>"

                   "<p align='left'>GPS Constellation Status:<br>"
                   "<a href='http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt'>http://www2.unb.ca/gge/Resources/GPSConstellationStatus.txt</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Reference Station Files from Spain
void gLAB_GUI::on_actionRefStations_Spain_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(530, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Reference Station Files from Spain");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Cartographic and Geologic Institute of Catalonia (1s / 30s):<br>"
                   "<a href='ftp://geofons.icc.cat/rinex/'>ftp://geofons.icc.cat/rinex/</a></p>"

                   "<p align='left'>Valencian Cartographic Institute (1s / 5s / 30s):<br>"
                   "[Public user and password is at <a href='https://icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex'>https://icv.gva.es/es/web/icv-erva/descarga-ficheros-rinex</a>]<br>"
                   "<a href='ftps://ftps.gva.es/Datos'>ftps://ftps.gva.es/Datos</a></p>"

                   "<p align='left'>Principality of Asturias Active GNSS Network (1s / 5s / 30s):<br>"
                   "<a href='ftp://rgapa.cartografia.asturias.es/RINEX/'>ftp://rgapa.cartografia.asturias.es/RINEX/</a></p>"

                   "<p align='left'>National Geographic Institute (1s / 5s / 30s):<br>"
                   "<a href='https://datos-geodesia.ign.es/ERGNSS/'>https://datos-geodesia.ign.es/ERGNSS/</a></p>");

    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the Reference Station Files from Geoscience Australia
void gLAB_GUI::on_actionGeoscience_Australia_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(530, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Reference Station Files from Geoscience Australia");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>Geoscience Australia home page (1s and 30s files, web and SFTP access):<br>"
                   "<a href='https://data.gnss.ga.gov.au/docs/home/gnss-data.html'>https://data.gnss.ga.gov.au/docs/home/gnss-data.html</a></p>");

    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show the reference station Files from coastal services
void gLAB_GUI::on_actionRefStaions_Coastal_Services_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Reference Station Files from coastal services");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'><p align='left'>SONEL (30s):<br>"
                   "<a href='ftp://ftp.sonel.org/gps/data/'>ftp://ftp.sonel.org/gps/data/</a></p>");

    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show lists of NTRIP servers
void gLAB_GUI::on_actionLists_of_NTRIP_servers_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Download Data: Lists of NTRIP station");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'>""<p align='left'>Ntrip Working Group server list:<br>"
                   "<a href='http://www.rtcm-ntrip.org/home'>http://www.rtcm-ntrip.org/home</a></p>"

                   "<p align='left'>EUREF NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-euref.dat'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-euref.dat</a></p>"

                   "<p align='left'>IGS NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-igs.dat'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-igs.dat</a></p>"

                   "<p align='left'>Products NTRIP servers:<br>"
                   "<a href='https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-products.dat'>https://igs.bkg.bund.de/root_ftp/NTRIP/streams/sourcetable-products.dat</a></p>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show links to the UNAVCO's Database RINEX searcher
void gLAB_GUI::on_actionUNAVCO_Database_RINEX_Searcher_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(505, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("UNAVCO's Database RINEX Searcher");
    msgBox.setMinimumWidth(700);
    msgBox.setText("<span style='font-weight:normal'>""<p align='justify'>UNAVCO has an accesible (free registation required) HTTPS server at <a href='https://gage-data.earthscope.org/archive/gnss'>https://gage-data.earthscope.org/archive/gnss</a>, with RINEX observation and navigation files from many stations and years.<br>"
                   "In order to make fast and precise data search in their HTTPS server, there two interfaces<br><br>"
                   "GNSS Data Access Notebook:<br>"
                   "<a href='https://www.unavco.org/data/gps-gnss/data-access-methods/gnss-data-access-notebooks/gnss-permanent-station-data-access-notebook-embed.html'>https://www.unavco.org/data/gps-gnss/data-access-methods/gnss-data-access-notebooks/gnss-permanent-station-data-access-notebook-embed.html</a><br><br>"
                   "DAI (Data Archive Interface) v1 (deprecated):<br>"
                   "<a href='https://www.unavco.org/data/gps-gnss/data-access-methods/dai1/dai1.html'>https://www.unavco.org/data/gps-gnss/data-access-methods/dai1/dai1.html</a><br>");
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show "Request for additional links" message
void gLAB_GUI::on_actionAdd_your_link_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("Request for additional links");
    msgBox.setMinimumWidth(700);
    msgBox.setText(QString("<span style='font-weight:normal'>""<p align='left'>If you know more links for downloading GNSS data and want them to be added to gLAB, please send them to:</p>")+
                   QString("<p align='center'><b><font color='#0000FF'>%1@%2</font></b></p></br>").arg("glab.gage").arg("upc.edu") +
                   QString("<p align='left'>If the link is regarded to a institution, send also the institution name (in english), its country and region.</p>"));
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

// Function to show "How to reference gLAB" message
void gLAB_GUI::on_actionReference_gLAB_triggered() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(630, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setWindowTitle("How to reference gLAB");
    msgBox.setMinimumWidth(700);
    msgBox.setText(QString("<span style='font-weight:normal'><p align='left'>If you feel it is appropriate, you may consider paying us back by citing the following PhD thesis:<br><br>")+
                   QString("Ibáñez D. (2023) Contributions to multi-purpose GNSS positioning to support multi-frequency and multi-constellation with high accuracy and integrity.")+
                   QString(" PhD thesis, URL <a href='https://server.gage.upc.edu/PhD/Ibanez_Deimos/PhD_Ibanez_Deimos.pdf'>https://server.gage.upc.edu/PhD/Ibanez_Deimos/PhD_Ibanez_Deimos.pdf</a><br><br>")+
                   QString("Moreover, the following gLAB paper may also be cited:<br><br>")+
                   QString("Ibáñez D., Rovira-García A., Sanz J., Juan JM., Gonzalez-Casado G., Jimenez-Baños D., López-Echazarreta C., Lapin I.") +
                   QString(" The GNSS Laboratory Tool Suite (gLAB) updates: SBAS, DGNSS and Global Monitoring System. ")+
                   QString("9th ESA Workshop on Satellite Navigation Technologies (NAVITEC 2018), Noordwijk, The Netherlands. December 5 - 7, 2018. DOI: <a href='https://doi.org/10.1109/NAVITEC.2018.8642707'>10.1109/NAVITEC.2018.8642707</a>.</p>"));
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
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
    QMessageBox messageBox,messageBoxWarn;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QString processReadline;
    QChar PercentageCharac = '%';
    int percentage;
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    //multi-threading mode
    if ( MultiThread->nThreads>1 && ui->stackedWidgetMainWindow->currentIndex()==0 ) {
        *saveString = "###################################################\n";
        *saveString += "#     Multi-Threading\n";
        *saveString += "###################################################\n\n";
        *saveString += "-numthreads " + QString::number(MultiThread->nThreads) + "\n\n";
        *runString << "-numthreads" << QString::number(MultiThread->nThreads);
    }

    getInputOptions(errorString, warningString, saveString, runString);
    getPreprocessOptions(errorString, warningString, saveString, runString);
    getModellingOptions(errorString, warningString, saveString, runString);
    getFilterOptions(errorString, warningString, saveString, runString);
    getOutputOptions(errorString, warningString, saveString, runString);


    if ( *errorString != "" ) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before executing processing again:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        ui->pushButtonRunGlab->setEnabled(true);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
        if ( reply == QMessageBox::No ) {
            ui->pushButtonRunGlab->setEnabled(true);
            return;
        }
    }

    if (MultiThread->nThreads<=1) {
        #ifdef Q_OS_LINUX
            program = QString("/gLAB_linux");
        #elif defined(Q_OS_WIN32)
            program = QString("\\gLAB.exe");
        #elif defined(Q_OS_MAC)
            program = QString("/gLAB_mac");
        #endif
    } else {
        #ifdef Q_OS_LINUX
            program = QString("/gLAB_linux_MultiThread");
        #elif defined(Q_OS_WIN32)
            program = QString("\\gLAB_MultiThread.exe");
        #elif defined(Q_OS_MAC)
            program = QString("/gLAB_mac_MultiThread");
        #endif
    }

    //Add hidden parameter to the core so its prints the right lines for the GUI
    *runString << "-print:guiprogress";

    processRun->setReadChannel(QProcess::StandardOutput);

    abort=0;

    // Execute the program
    QString testStr=QDir::toNativeSeparators(qApp->applicationDirPath()+program);
    processRun->start(QDir::toNativeSeparators(qApp->applicationDirPath()+program), *runString);
    sleep(10);
    if ( processRun->state() == 0 ) {
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB core could not be executed.\n");
        messageBox.exec();
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
            //Check first if in standard output there is an error message
            if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                messageBox.setWindowTitle("Error found");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("gLAB had the following error during the processing:\n\n" + processReadline +"\n");
                messageBox.exec();
            } else {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputDestination->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processRun->canReadLine() ) {
                        processReadline = processRun->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the processing:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
                } else if (*lastLine!="---") {
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("gLAB had the following error during the processing:\n\n" + *lastLine +"\n");
                    messageBox.exec();
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processRun->canReadLine() ) {
                        processReadline = processRun->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the processing:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

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
        messageBox.setWindowTitle("Problem found");
        messageBox.setText("Output file is empty\n");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    } else if (this->fileExists(ui->lineEditOutputDestination->text())==false) {
        messageBox.setWindowTitle("Error found");
        messageBox.setText("File '" + ui->lineEditOutputDestination->text() + "' does not exist.\n");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
    } else {
        processShow->start(program, arguments);
        sleep(100);
        if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
            if (processShow->exitCode()!=0) {
                messageBox.setWindowTitle("Error found");
                messageBox.setText("File '" + ui->lineEditOutputDestination->text() + "' could not be opened with default text editor.\n");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.exec();
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
    QMessageBox messageBox,messageBoxWarn;
    QFile fileLock;
    QString PlotLockWorkingDir;
    QString PlotLockHome;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QStringList *runString = new QStringList;
    int counter;
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    // Delete the ".plot.lock" just if it remained from any crash
    fileLock.remove(".plot.lock");

    // Program is graph.py
    #ifdef Q_OS_LINUX
        program = QString("/graph/graph");
    #elif defined(Q_OS_WIN32)
        program = QString("\\graph\\graph.exe");
    #elif defined(Q_OS_MAC)
        program = QString("/graph");
    #endif

    getAnalysisOptions(errorString, warningString, saveString, runString);

    // Output the errors
    if ( *errorString != "" ) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before executing the plot command again:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        // Enable the Plot button
        ui->pushButtonPlot->setEnabled(true);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
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
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("graph could not be executed.\n");
        messageBox.exec();
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    //Open SBAS folder
    if ( ui->groupBoxConverterSBAS->isChecked()==true ) {
        if (ui->lineEdit_outputpath_sbas->text() == "") {
            messageBox.setWindowTitle("Error");
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("SBAS Output path is empty\n");
            messageBox.exec();
        } else {
            if (this->directoryExists( ui->lineEdit_outputpath_sbas->text() ) == false ) {
                messageBox.setWindowTitle("Error");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("SBAS Output path '" + ui->lineEdit_outputpath_sbas->text() + "' does not exist.\n");
                messageBox.exec();
            } else {
                QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEdit_outputpath_sbas->text()));
            }
        }
    } else if ( ui->groupBoxConverterDgnss->isChecked()==true) {
        if (ui->lineEditConverterDgnssOutputRinex->text() == "") {
            messageBox.setWindowTitle("Error");
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("DGNSS Output RINEX filename is empty\n");
            messageBox.exec();
        } else {
            #ifdef Q_OS_WIN32
                if (this->directoryExists( ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2) ) == false ) {
                    messageBox.setWindowTitle("Error");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("DGNSS Output path '" + ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2) + "' does not exist.\n");
                    messageBox.exec();
                } else {
                    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditConverterDgnssOutputRinex->text().section("\\",0,-2)));
                }
            #else
                if (this->directoryExists( ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2) ) == false ) {
                    messageBox.setWindowTitle("Error");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("DGNSS Output path '" + ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2) + "' does not exist.\n");
                    messageBox.exec();
                } else {
                    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditConverterDgnssOutputRinex->text().section("/",0,-2)));
                }
            #endif
        }
    } else {
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Select the conversion mode before showing the output files.\n");
        messageBox.exec();
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
    QMessageBox messageBox,messageBoxWarn;
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
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

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
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before executing the file conversion:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        ui->pushButtonConvert->setEnabled(true);
        ui->pushButtonConvertShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
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
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB core could not be executed.\n");
        messageBox.exec();
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
        }

        //Check the exit code
        if (processConvert->exitCode()!=0 && abort==0) {
            //Check first if in standard output there is an error message
            if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                messageBox.setWindowTitle("Error found");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("gLAB had the following error during the file conversion:\n\n" + processReadline +"\n");
                messageBox.exec();
            } else {
                //Check the last line of file for error messages
                getLastLineOfFile(QDir::toNativeSeparators("./gLAB_conversion.out"),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processConvert->canReadLine() ) {
                        processReadline = processConvert->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the file conversion:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
                } else if (*lastLine!="---") {
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("gLAB had the following error during the file conversion:\n\n" + *lastLine +"\n");
                    messageBox.exec();
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processConvert->canReadLine() ) {
                        processReadline = processConvert->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the file conversion:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    if (ui->lineEditOutputFileCompare->text() == "") {
        messageBox.setWindowTitle("Problem found");
        messageBox.setText("Output file is empty.\n");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    } else {
        if (this->fileExists( ui->lineEditOutputFileCompare->text() ) == false ) {
            messageBox.setWindowTitle("Error");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Output file '" + ui->lineEditOutputFileCompare->text() + "' does not exist.\n");
            messageBox.exec();
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
                    messageBox.setWindowTitle("Error");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("File '" + ui->lineEditOutputFileCompare->text() + "' could not be opened with default text editor.\n");
                    messageBox.exec();
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
    QMessageBox messageBox,messageBoxWarn;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

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
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before executing the orbit comparison:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        ui->pushButtonCompare->setEnabled(true);
        ui->pushButtonCompareShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
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
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB core could not be executed.\n");
        messageBox.exec();
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
        }

        //Check the exit code
        if (processCompare->exitCode()!=0 && abort==0) {
            //Check first if in standard output there is an error message
            if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                messageBox.setWindowTitle("Error found");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("gLAB had the following error during the orbit comparison:\n\n" + processReadline +"\n");
                messageBox.exec();
            } else {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileCompare->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processCompare->canReadLine() ) {
                        processReadline = processCompare->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the orbit comparison:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
                } else if (*lastLine!="---") {
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("gLAB had the following error during the orbit comparison:\n\n" + *lastLine +"\n");
                    messageBox.exec();
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processCompare->canReadLine() ) {
                        processReadline = processCompare->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the orbit comparison:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    if (ui->lineEditOutputFileShowOrbit->text() == "") {
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Output file is empty\n");
        messageBox.exec();

    } else {
        if (this->fileExists( ui->lineEditOutputFileShowOrbit->text() ) == false ) {
            messageBox.setWindowTitle("Error found");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Output file '" + ui->lineEditOutputFileShowOrbit->text() + "' does not exist.\n");
            messageBox.exec();
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
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("File '" + ui->lineEditOutputFileShowOrbit->text() + "' could not be opened with default text editor.\n");
                    messageBox.exec();
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
    QMessageBox messageBox,messageBoxWarn;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

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
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before executing the orbit computation:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        ui->pushButtonShowOrbit->setEnabled(true);
        ui->pushButtonShowOrbitShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
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
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB core could not be executed.\n");
        messageBox.exec();
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
        }

        //Check the exit code
        if (processShowOrbit->exitCode()!=0 && abort==0) {
            //Check first if in standard output there is an error message
            if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                messageBox.setWindowTitle("Error found");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("gLAB had the following error during the orbit computation:\n\n" + processReadline +"\n");
                messageBox.exec();
            } else {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileShowOrbit->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processShowOrbit->canReadLine() ) {
                        processReadline = processShowOrbit->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the orbit computation:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
                } else if (*lastLine!="---") {
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("gLAB had the following error during the orbit computation:\n\n" + *lastLine +"\n");
                    messageBox.exec();
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processShowOrbit->canReadLine() ) {
                        processReadline = processShowOrbit->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during the orbit computation:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    if (ui->lineEditRinexOutputFileAddError->text() == "") {
        messageBox.setWindowTitle("Problem found");
        messageBox.setText("Output RINEX file is empty\n");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    } else {
        if (this->fileExists( ui->lineEditRinexOutputFileAddError->text() ) == false ) {
            messageBox.setWindowTitle("Error found");
            messageBox.setText("Output RINEX file '" + ui->lineEditRinexOutputFileAddError->text() + "' does not exist.\n");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.exec();
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
                    messageBox.setWindowTitle("Error found");
                    messageBox.setText("File '" + ui->lineEditRinexOutputFileAddError->text() + "' could not be opened with default text editor.\n");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.exec();
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
    QMessageBox messageBox,messageBoxWarn;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString*lastLine = new QString;
    QStringList *runString = new QStringList;
    QFile fileLock;
    QString processReadline;
    int percentage;
    int reply;

    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");


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
        messageBox.setWindowTitle("Errors found");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB has found the following errors, please correct them before adding user error to RINEX:\n\n" + *errorString);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        ui->pushButtonAddError2Rinex->setEnabled(true);
        ui->pushButtonAddErrorShowOutput->setEnabled(false);
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        reply = messageBoxWarn.exec();
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
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("gLAB core could not be executed.\n");
        messageBox.exec();
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
        }
        //Check the exit code
        if (processAddError->exitCode()!=0 && abort==0) {
            //Check first if in standard output there is an error message
            if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                messageBox.setWindowTitle("Error found");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("gLAB had the following error during adding user error to RINEX:\n\n" + processReadline +"\n");
                messageBox.exec();
            } else {
                //Check the last line of file for error messages
                getLastLineOfFile(ui->lineEditOutputFileAddError->text(),lastLine);
                if ( (*lastLine=="" || (!lastLine->contains("ERROR",Qt::CaseSensitive))) && *lastLine!="---") {
                    //Check if gLAB showed an ERROR in standard output (the output file existed from previous runs)
                    processReadline="";
                    while ( processAddError->canReadLine() ) {
                        processReadline = processAddError->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during adding user error to RINEX:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
                    }
                } else if (*lastLine!="---") {
                    messageBox.setWindowTitle("Error found");
                    messageBox.setIcon(QMessageBox::Critical);
                    messageBox.setText("gLAB had the following error during adding user error to RINEX:\n\n" + *lastLine +"\n");
                    messageBox.exec();
                } else {
                    //No output file created. Check if gLAB showed an ERROR in standard output before creating the output file
                    processReadline="";
                    while ( processAddError->canReadLine() ) {
                        processReadline = processAddError->readLine();
                    }
                    if (processReadline.contains("ERROR",Qt::CaseSensitive)) {
                        messageBox.setWindowTitle("Error found");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB had the following error during adding user error to RINEX:\n\n" + processReadline +"\n");
                        messageBox.exec();
                    } else {
                        messageBox.setWindowTitle("Error");
                        messageBox.setIcon(QMessageBox::Critical);
                        messageBox.setText("gLAB exited unexpectedly for unknown reason.\n");
                        messageBox.exec();
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
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    if (this->fileExists(configFileName[ui->stackedWidgetMainWindow->currentIndex()])==false) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("Configuration file " + configFileName[ui->stackedWidgetMainWindow->currentIndex()] + " does not exist.\n");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
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
            messageBox.setWindowTitle("Errors found");
            messageBox.setText("File '" + configFileName[ui->stackedWidgetMainWindow->currentIndex()] + "' could not be opened with default text editor.\n");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.exec();
        }
    }
}

// Function to show the command line instruction
void gLAB_GUI::on_actionShow_command_line_instruction_triggered() {

    QString program;
    QString programCygwin;
    QString *errorString = new QString;
    QString *warningString = new QString;
    QString *saveString = new QString;
    QString auxstring;
    QString auxstring2;
    QString auxstringCygwin;
    QStringList *runString = new QStringList;
    int reply;
    int label=0;
    int condition=0;


    // Based on the OS open the text editor
    if (MultiThread->nThreads<=1) {
        #ifdef Q_OS_LINUX
            program = QString("/gLAB_linux");
        #elif defined(Q_OS_WIN32)
            program = QString("\\gLAB.exe");
            programCygwin = QString("gLAB_linux");
        #elif defined(Q_OS_MAC)
            program = QString("/gLAB_mac");
        #endif
    } else if (ui->stackedWidgetMainWindow->currentIndex()==0) {
        #ifdef Q_OS_LINUX
            program = QString("/gLAB_linux_MultiThread");
        #elif defined(Q_OS_WIN32)
            program = QString("\\gLAB_MultiThread.exe");
            programCygwin = QString("gLAB_linux_MultiThread");
        #elif defined(Q_OS_MAC)
            program = QString("/gLAB_mac_MultiThread");
        #endif
    }

    //Compute parameters
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        getInputOptions(errorString, warningString, saveString, runString);
        getPreprocessOptions(errorString, warningString, saveString, runString);
        getModellingOptions(errorString, warningString, saveString, runString);
        getFilterOptions(errorString, warningString, saveString, runString);
        getOutputOptions(errorString, warningString, saveString, runString);
        //multi-threading mode
        if (MultiThread->nThreads>1) {
            *saveString += " -numthreads " + QString::number(MultiThread->nThreads);
            *runString << "-numthreads" << QString::number(MultiThread->nThreads);
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        getAnalysisOptions(errorString, warningString, saveString, runString);
        #ifdef Q_OS_WIN32
            program = QString("\\graph\\graph.exe");
            programCygwin = QString("graph");
        #elif defined Q_OS_LINUX
            program = QString("/graph/graph");
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
        messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB has found the following errors, please correct them before generating the configuration file again:\n\n" + *errorString);
        messageBox.setIcon(QMessageBox::Critical);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        return;
    }

    if ( *warningString != "" ) {
        QMessageBox messageBox;
        messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
        messageBox.setWindowTitle("Problems found");
        messageBox.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBox.setIcon(QMessageBox::Question);
        messageBox.addButton(QMessageBox::Yes);
        messageBox.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

        reply = messageBox.exec();
        if ( reply == QMessageBox::No ) {
            return;
        }
    }

    //Transform from QStringList to QString and add quotes in pathes
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
            if (auxstring2.contains("\\")==true && auxstring2[0]!='\"' && auxstring2[auxstring2.length()-1]!='\"') {
            #else
            if (auxstring2.contains("/")==true && auxstring2[0]!='\"' && auxstring2[auxstring2.length()-1]!='\"') {
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
    int widthCommandLinuxGroupBox=550;
    msgBox.setMinimumWidth(1100);
    #ifdef Q_OS_WIN32
        //Make the message wider in Windows due to commnd line is duplicated for Cygwin when all parameters are shown
        if (ui->actionGenerate_minimum_configuration->isChecked()==false) {
            widthCommandLinuxGroupBox=1000;
        }
       // msgBox.setMinimumWidth(1100);
    #endif
    msgBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QSpacerItem* horizontalSpacer = new QSpacerItem(widthCommandLinuxGroupBox, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
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
    QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
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
//Function to select multi-threading mode and set number of threads
void gLAB_GUI::on_actionSet_Multi_threading_options_triggered() {
    MultiThread->setModal(true);
    MultiThread->show();

}
//Function to print messages in V5 formate
void gLAB_GUI::on_actionPrint_messages_in_gLAB_v5_format_triggered(bool checked){
    if(checked==true) {
        this->v5Message=1;
    } else {
        this->v5Message=0;
    }
}

// Function to save the gLAB configuration file
void gLAB_GUI::on_actionSave_triggered() {
    // Header
    QDateTime local(QDateTime::currentDateTime());
    QMessageBox messageBox,messageBoxWarn;
    int reply;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    messageBoxWarn.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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

    //multi-threading mode
    if (MultiThread->nThreads>1) {
        *saveString += "\n###################################################\n";
        *saveString += "#     Multi-Threading\n";
        *saveString += "###################################################\n\n";
        *saveString += "-numthreads " + QString::number(MultiThread->nThreads) + "\n\n";
        *runString << "-numthreads" << QString::number(MultiThread->nThreads);
    }

    // Footer of the file
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     End of self-generated parameters\n";
    *saveString += "###################################################\n";


    if ( *errorString != "" ) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB has found the following errors, please correct them before generating the configuration file again:\n\n" + *errorString);
        messageBox.setIcon(QMessageBox::Critical);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        return;
    }

    if ( *warningString != "" ) {
        messageBoxWarn.setWindowTitle("Problems found");
        messageBoxWarn.setText("gLAB has found the following issues:\n\n" + *warningString + "\nAre you sure you want to continue?\n");
        messageBoxWarn.setIcon(QMessageBox::Question);
        messageBoxWarn.addButton(QMessageBox::Yes);
        messageBoxWarn.addButton(QMessageBox::No);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBoxWarn.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

        reply = messageBoxWarn.exec();
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

    if ( dialog.exec() ) {
        configFileName[ui->stackedWidgetMainWindow->currentIndex()] = dialog.selectedFiles().at(0);
    } else return;
    if ( configFileName.isEmpty() ) return;
    else {
        QFile file(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]==nullptr) {
            //User pressed cancel button
        } else if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
            messageBox.setWindowTitle("Errors found");
            messageBox.setText("gLAB could not create the Configuration File.\n");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.exec();
            return;
        } else {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << header << *saveString;
            file.close();
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
    hour=static_cast<int>(static_cast<double>(SoD)/3600.);
    minute=static_cast<int>(static_cast<double>(SoD)/60.)%60;
    second=SoD%60;

    *time=QTime(hour,minute,second,0);
}

//Convert from GPSWeek and SoW to QDate and QTime
void gLAB_GUI::GPSTime2DateTime(int GPSWeek, int SoW, QDate *date, QTime *time) {
    int DoW;
    int SoD;

    DoW=static_cast<int>(static_cast<double>(SoW)/86400.0);
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
    } else if ( QString::compare(Constellation, "C", Qt::CaseSensitive)==0 || QString::compare(Constellation, "BDS", Qt::CaseSensitive)==0 ) {
        return BDS;
    } else if ( QString::compare(Constellation, "C", Qt::CaseSensitive)==0 || QString::compare(Constellation, "BeiDou", Qt::CaseSensitive)==0 ) {
        return BDS;
    } else if ( QString::compare(Constellation, "J", Qt::CaseSensitive)==0 || QString::compare(Constellation, "QZSS", Qt::CaseSensitive)==0 ) {
        return QZSS;
    } else if ( QString::compare(Constellation, "I", Qt::CaseSensitive)==0 || QString::compare(Constellation, "IRNSS", Qt::CaseSensitive)==0 ) {
        return IRNSS;
    }

    return GNSSSystemUnknown;
}
