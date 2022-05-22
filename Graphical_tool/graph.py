#!/usr/bin/python
# -*- coding: UTF-8 -*- 

#############################################################################
#  Copyright & License:
#  ====================
#   
#  Copyright 2009-2020 gAGE/UPC & ESA 
#   
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#   
#  http://www.apache.org/licenses/LICENSE-2.0
#   
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#############################################################################

#############################################################################
# Copyright: gAGE/UPC & ESA
# Project: EDUNAV GNSS Lab Tool
# Supervisor: Jaume Sanz Subirana (group of Astronomy and GEomatics - gAGE/UPC)
# Authors: Adria Rovira-Garcia (group of Astronomy and GEomatics - gAGE/UPC)
#          Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
# Curator: Adria Rovira-Garcia ( gAGE/UPC )
# Developer: Deimos Ibanez Segura ( gAGE/UPC )
#            Yixie Shao ( gAGE/UPC )
#          glab.gage @ upc.edu           
# File: graph.py
# Code Management Tool File Version: 5.5  Revision: 1
# Date: 2020/12/11
#############################################################################

#############################################################################
# MODULE DESCRIPTION
#
# Name: graph
# Language: python
#
# Purpose:
#  The purpose of this module is to generate a plot for a set of specified
#  input data.
#
# Function:
#  This program creates a window which will show a plot for the specified 
#  columns in a file. It allows to include conditions to select which files
#  to plot.
# 
# Dependencies:
#  None
#
# Files modified:
#  .plot.lock
#
# Files read:
#  None
#
# Resources usage:
#  See Design Document
#############################################################################

#############################################################################
#       RELEASE_HISTORY
# -------------
#          gLAB v1.3.0
# Release: 2009/12/10
# Change Log: First public version.
# -------------
#          gLAB v1.4.0
# Release: 2010/06/21
# Change Log: Save figure function added.
# -------------
#          gLAB v1.4.1
# Release: 2010/07/09
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.2
# Release: 2010/07/31
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.3
# Release: 2010/08/31
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.4
# Release: 2010/09/22
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.5
# Release: 2010/10/31
# Change Log: Minor Changes in help 
# -------------
#          gLAB v2.0.0
# Release: 2012/12/31
# Change Log: gLAB version released together with the Educational Book:
#             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
#             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
#             ISBN: 978-92-9221-885-0 (two volumes)
#             ISSN: 1013-7076
#             December 2012.
# -------------
#          gLAB v2.2.0
# Release: 2014/09/22
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.1
# Release: 2014/12/23
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.2
# Release: 2015/03/02
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.3
# Release: 2015/05/28
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.4
# Release: 2015/07/01
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.5
# Release: 2015/10/20
# Change Log: When plot fails due to non-decimal values, the file .plot.lock is erased,
#               so gLAB_GUI.py "Plot" button doesn't get locked during 60 seconds. Also,
#               the error message has been clarified
#             In the Windows version (.exe binary), stdout has been redirected to stderr
#               so the help message is not lost
# -------------
#          gLAB v3.0.0
# Release: 2016/09/05
# Change Log: Added stanford plots and stanford-ESA plots
#             Added worst integrity ratio plots
#             Display environment in linux is not necessary when plot is saved to a file
#             It is now compatible with python 3
#             NOTE: The new plots (stanford and worst integrity ratio) need additional 
#                   python libraries (numpy and basemap), but they are not mandatory 
#                   if these plots are not used (for compatibility with previous versions)
# -------------
#          gLAB v3.1.0
# Release: 2016/09/26
# Change Log: Fixed a bug with input parameters due to bad space indentation 
# -----------
#          gLAB v3.1.1
# Release: 2016/10/21
# Change Log: Changed title name in Stanford-ESA plots from '# epochs' to '# samples'.
#             Fixed Stanford-ESA plots, which was horizontal protection levels from vertical plots and viceversa.
#             Added quantization check in Stanford plots generation for points greater than the
#                maximum X and Y. For example, (60,100) and (100,60) with a max X and Y of 50, 
#                would both result in the plot in the point (50,50) or (Xmax,Ymax), which made
#                it impossible to distinguish the MI from the non-MI. Now, MI points will result
#                in (Xmax,Ymax) while non MI will result in (Xmax-1,Ymax)
# -----------
#          gLAB v4.0.0
# Release: 2017/03/03
# Change Log: Added SBAS plots.
#             Added option to make a map with the station names in WIR maps mode.
#             Added many checks to prevent errors from user input.
#             Added check of X Display in Linux when not saving picture to file.
#             Added option to change the number of points shown in the label.
#             Added option to change the label position.
#             Added option to show number of MIs in worst integrity plot with coloured rings, 
#               using parameters '--mih' and --miv'.
#             Added new plot: World maps. Worst Integrity Plots are now a special case for world maps.
#             Added option for plotting user defined watermark in all plots.
#             Changed Worst Integrity Ratio colourbar and scale to a fixed one.
#             Parameter '-z' from worst integrity ratio plot has changes to '--rh' and '--rv', so
#               in one call to the program both horizontal and vertical ratio plots can be shown.
#             Changed default alarm limit in Stanford plots from 35 to 40 metres.
#             Changed default both X and Y axis maximum to 60 metres in Stanford plots
#             Changed default horizontal label in Stanford-ESA plots from "HPE","VPE" to 
#               "Horizontal Positioning Error (metres)","Vertical Positioning Error (metres)" respectively.
#             Changed default vertical label in Stanford-ESA plots from "HPL","VPL" to 
#               "Horizontal Protection Level (metres)","Vertical Protection Level (metres)" respectively.
#             Changed default title in Stanford-ESA plots from "StanfordESA" to "Stanford-ESA".
#             Changed reading of Stanford-ESA files in order to skip comment headers.
#             Fixed Stanford plots bug that always set maximum values to 50 metres.
#             Updated help messages.
# -----------
#          gLAB v4.1.0
# Release: 2017/04/07
# Change Log: Added option to set user defined ticks (for both X and Y) in standard plots.
#             Added option to adjust figure to margin, so there is the minimum white space margin left. 
#               This option applies to all modes except for world maps or integrity ratio maps.
#             Fixed all errors when executing graph.py with python3.
# -----------
#          gLAB v4.2.0
# Release: 2017/05/22
# Change Log: Changed default title of SBAS iono map from 'SBAS Iono Correction Map' to 
#                 'SBAS Iono Correction Availability Map'.
#             Added unicode text transformation in WaterMark text input when running under Python 2.
# -----------
#          gLAB v5.0.0
# Release: 2017/06/30
# Change Log:   Added two new modes for setting ticks in the plots: 
#                 With parameters '--XticksStep' and '--YticksStep', the ticks are set at the rate given by the user.
#                 With parameters '--XticksList' and '--YticksList', the user set the ticks by giving a list of ticks.
#               Added options '--percentileX' and '--percentileY' in Stanford Plots mode for setting ticks when the
#                 68%, 95% and 99.9% of the values are reached in each axe.
#               Added option '--CbarLabel' in SBAS Availability map plots for setting a label next to the colourbar.
#               Added option '--NoCbarPercent' n SBAS Availability map plots for not printing the '%' on top of the colourbar.
#               Setting ticks manually now work in all plot modes.
#               Vertical and horizontal label can now be set in World maps, Worst Integrity Ratio maps and SBAS maps.
#               Colorbar in SBAS Availability plots now has the same height as the plot.
# -----------
#          gLAB v5.1.0
# Release: 2017/11/24
# Change Log:   In Mac and Linux, if the ".plot.lock" cannot be created in the current directory,
#                 then this file will be created in the home directory. This is to make graph
#                 work in Mac when gLAB is opened by double clicking in the gLAB logo after
#                 opening the ".dmg" file (i.e. without installing gLAB). In this case, gLAB
#                 files were mounted on a read-only filesystem.
#               Changed title name in Stanford-ESA plots from '# samples' to '# geometries'.
#               Disabled warning deprecated messages in windows and Mac.
#               Removed the "Qt: Untested Windows version 6.2 detected!" warning message
#                 in Windows 10 from the Qt4 library used by python.
#               Fixed watermark being printed over the colourbarlabels in SBAS plots mode.
#               Fixed error in Stanford plots mode which made the image title get erased 
#                 when the user provided a title which had a newline in the middle of the text.
# -----------
#          gLAB v5.1.1
# Release: 2017/12/22
# Change Log: No changes in this file.
# -----------
#          gLAB v5.1.2
# Release: 2018/01/12
# Change Log: No changes in this file.
# -----------
#          gLAB v5.1.3
# Release: 2018/01/19
# Change Log: Removed text "PRN 0" in default ionosphere availability maps title when GEO PRN was 0
#               (PRN 0 means data was read from several GEOs).
# -----------
#          gLAB v5.2.0
# Release: 2018/03/09
# Change Log: The "os.remove(LockFile)" instruction is now inside a try/catch. This is to avoid a
#               rare race condition that occurs when multiple instances of "graph.py" are executed 
#               in parallel and one of them erases the "LockFile" (.plot.lock) after the check that
#               the "LockFile" exists but before the "os.remove(LockFile)" instruction is executed.
#               When this race condition ocurred, the program crashed before creating the plot.
#             Added option '--no-lock-file' for not creating the ".plot.lock" file.
#             Added option '--SBASSystemname' (or '--sbassystemname') for changing the "SBAS" word
#               in the SBAS maps default title for any user defined SBAS system name.
#             Added option '--PRNtext' (or '--prntext') for changing the text "PRN #" in the 
#               SBAS maps default title. This is useful when multiple GEO were used and the PRN in
#               the file header is 0.
#             Added option '--PRNtextnewline' (or '--prntextnewline') for moving the the text "PRN #"
#               in the SBAS maps default title to the line below. Useful when many GEO were used.
#             Added option '--wmc' (or '--watermarkcolor') for changing the colour of the watermark.
#             Added option '--wms' (or '--watermarksize') for changing the size of the watermark.
#             Added option '--wmp' (or '--watermarkposition') for changing the position of the watermark.
#             Changed default position of the watermark in SBAS maps. Now it will situated in the
#               top right side of the image (outside the plot and over the colourbar) instead of the bottom
#               right side of the plot.
#             Changed default size of the watermark in SBAS maps. The size has been changed from 8 to 15.
# -----------
#          gLAB v5.3.0
# Release: 2018/06/08
# Change Log:   Added option '--stanetwithnames' to enable showing station names in the station map (in previous
#                 version, station map only showed station names. Now it can show the station name, a marker or both)
#               Added options '--stanetdefaultnamesize', '--stanetdefaultnamecolor' and '--stanetdefaultnamealign' for
#                 setting the station name default size, colour and alignment respectively.
#               Added option '--stanetwithmarkers' for adding a marker in the station map.
#               Added options '--stanetdefaultmarkertype', '--stanetdefaultmarkersize' and '--stanetdefaultmarkercolor'
#                 for setting the station marker default type, size and colour respectively.
#               Added option '--stanet' for setting the input file column number for reading the station network name.
#               Added option '--stanetautolabel' for enabling a label for each station network in the station map.
#               Added option '--stanetdefaultlabel' for setting the default label for the station network.
#               Added option '--stanetlabel' for setting a label on a specific station network in the station map.
#               Added options '--stanetmarkertype', '--stanetmarkercolor', '--stanetmarkersize' for setting a marker type,
#                 marker colour or marker size (respectively) on a specific station network in the station map.
#               Added options '--stanetnamecolor', '--stanetnamesize', '--stanetnamealign' for setting a name colour,
#                 name size or name alignment (respectively) on a specific station network in the station map.
#               Added new plots for SBAS plots: Maritime Continuity Risk, HDOP, PDOP and GDOP.
#               Added option '--bineqcond' for setting the bin threshold to be "greater equal" or "less equal" instead of
#                 "greater" or "less" in SBAS plots.
#               Added options '--availmapbins', '--contriskmapbins', '--contriskmarmapbins', '--ionoavailmapbins',
#                 '--hdopmapbins', '--pdopmapbins', '--gdopmapbins' for manually setting the number of bins and its
#                 thresholds values for SBAS Availability, Continuity Risk, Maritime Continuity Risk, Iono Availability,
#                 HDOP, PDOP and GDOP maps respectively.
#               Added options '--availcontourlevels', '--contriskcontourlevels', '--contriskmarcontourlevels' for setting
#                 the contour levels for SBAS Availability, Continuity Risk and Maritime Continuity Risk respectively.
#               Added options '--availbincolors', '--contriskbincolors', '--contriskmarbincolors', '--ionoavailbincolors',
#                 '--hdopbincolors', '--pdopbincolors' and --gdopbincolors' for changing the colourbar bin colours for SBAS
#                 Availability, Continuity Risk, Maritime Continuity Risk, Iono Availability, HDOP, PDOP and GDOP maps respectively.
#                 Maritime Continuity Risk, Iono Availability, HDOP, PDOP and GDOP maps respectively.
#               Added option '--doppercentileplot' for making the percentile HDOP, PDOP and GDOP plots (in addition to the
#                 HDOP, PDOP and GDOP median plots).
#               Added option '--fireu' in order to draw the European FIR area in World Maps/Station Maps/SBAS plots.
#               Added option '--firuser' in order to draw a user defined FIR area (though a text file with the coordinates) in
#                 World Maps/Station Maps/SBAS plots.
#               Added options '--firlinetype', '--firlinewidth', '--firlinecolor' and '--firmarkersize' for setting the line
#                 type, line width, line colour and marker size of the FIR line delimeter.
#               Added option '--firdegradation' for computing and showing the availability degradation inside the FIR area.
#               Added option '--firdegtext', '--firdegtextsize', '--firdegtextcolor' and '--firdegtextposition' for setting
#                 the text to be written, the text size, the text colour and the text position for the FIR degradation.
# -----------
#          gLAB v5.4.0
# Release: 2018/11/16
# Change Log:   Added option '--stanetlabelnumsta' for automatically adding the number of stations read
#                 for each network in the label.
#               Added option '--sbasplotsize' for manually setting the plotting size
#                 (in centimetres) of the SBAS plot.
#               Added options '--sbastopfiguremargin', '--sbasbottomfiguremargin', 
#                 '--sbasleftfiguremargin', '--sbasrightfiguremargin' for manually setting the SBAS plot
#                 top, bottom, left and  right margins respectively.
#               Added "NA" (Not Available) bin in all SBAS plots. Points in this bin will the ones with
#                 0 epochs (column NUMEPOCHS with value equal to zero), or values that go outside the
#                 maximum or minimum (for example, for continuity risk maps, values below 0 or above 1).
#               Added option '--disablenotavailbin' for disabling the "NA" (Not Available) bin in the
#                 SBAS plots.
#               Added option '--notavailbincolor' for changing the colour of the "NA" (Not Available) bin.
#               Added option '--notavailbintext' for changing the text of the "NA" (Not Available) bin.
#               Added options '--availmapbinstext', '--contriskmapbinstext', '--contriskmarmapbinstext',
#                 '--ionoavailmapbinstext', '--hdopmapbinstext', '--pdopmapbinstext' and '--gdopmapbinstext'
#                 for setting the text to be shown in the colourbar bins for SBAS Availability, Continuity 
#                 Risk, Maritime Continuity Risk, Iono Availability, HDOP, PDOP and GDOP maps respectively.
#               Added options '--availcbartitle', '--contriskcbartitle', '--contriskmarcbartitle',
#                 '--ionoavailcbartitle', '--hdopcbartitle', '--pdopcbartitle' and '--gdopcbartitle' for
#                 setting a user defined title on the top of the colourbar for SBAS Availability, Continuity
#                 Risk, Maritime Continuity Risk, Iono Availability, HDOP, PDOP and GDOP maps respectively.
#               Added option '--firconus' for plotting the CONUS FIR area in SBAS and world maps.
#               Added option '--firalaska' for plotting the Alaska FIR area in SBAS and world maps.
#               Added option '--fircanada' for plotting the Canada FIR area in SBAS and world maps.
#               Added option '--firmexico' for plotting the Mexico FIR area in SBAS and world maps.
#               Added options '--firlinetypeeu', '--firlinetypeconus', '--firlinetypealaska',
#                 '--firlinetypecanada' and '--firlinetypemexico', for changing the line type for the European
#                 FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added options '--firlinewidtheu', '--firlinewidthconus', '--firlinewidthalaska',
#                 '--firlinewidthcanada' and '--firlinewidthmexico' for changing the line width for the
#                 European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added options '--firlinecoloreu', '--firlinecolorconus', '--firlinecoloralaska',
#                 '--firlinecolorcanada' and '--firlinecolormexico' for changing the line colour for the
#                 European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added options '--firmarkersizeeu', '--firmarkersizeconus', '--firmarkersizealaska',
#                 '--firmarkersizecanada' and '--firmarkersizemexico' for changing the marker size for the
#                 European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added option '--firdegtextheader' to add a header to the FIR degradation text for the user
#                 defined FIR areas. This option has to be set for each user defined FIR area.
#               Added options '--firdegtextheadereu', '--firdegtextheaderconus', '--firdegtextheaderalaska',
#                 '--firdegtextheadercanada' and '--firdegtextheadercanada' for adding a header to the
#                 FIR degradation text for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and 
#                 Mexico FIR respectively.
#               Added option '--nofirborder' for not plotting the user defined FIR area borders in the plot.
#                 This option is useful for the case that the user only wants the degradation percentage, but
#                 the FIR itself.
#               Added options '--nofirbordereu', '--nofirborderconus', --nofirborderalaska', '--nofirbordercanada',
#                 '--nofirbordermexico' for not plotting borders of the European FIR, CONUS FIR, Alaska FIR,
#                 Canada FIR and Mexico FIR respectively in the map.
#               Added option '--firdegtextfooter' to add a footer to the FIR degradation text for the user
#                 defined FIR areas. This option has to be set for each user defined FIR area.
#               Added options '--firdegtextfootereu', '--firdegtextfooterconus', '--firdegtextfooteralaska',
#                 '--firdegtextfootercanada' and '--firdegtextfootermexico' for adding a footer to the
#                 FIR degradation text for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and 
#                 Mexico FIR respectively.
#               Added options '--firdegtexteu', '--firdegtextconus', '--firdegtextalaska',
#                 '--firdegtextcanada' and '--firdegtextmexico' for changing the degradation FIR text of the
#                 European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added option '--firdegtextbins' for setting the list of bins for which the availability shall be
#                 computed. For each bin in the list, a line with the values will be printed.
#                 defined FIR areas. This option has to be set for each user defined FIR area.
#               Added options '--firdegtextbinseu', '--firdegtextbinsconus', '--firdegtextbinsalaska',
#                 '--firdegtextbinscanada' and '--firdegtextbinsmexico' for setting the list of bins for which 
#                 the availability shall be computed for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and 
#                 Mexico FIR respectively.
#               Added options '--firdegtextsizeeu', '--firdegtextsizeconus', '--firdegtextsizealaska',
#                 '--firdegtextsizecanada' and '--firdegtextsizemexico' for changing the FIR degradation text 
#                 size for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added options '--firdegtextcoloreu', '--firdegtextcolorconus', '--firdegtextcoloralaska',
#                 '--firdegtextcolorcanada' and '--firdegtextcolormexico' for changing the FIR degradation text 
#                 colour for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added options '--firdegtextpositioneu', '--firdegtextpositionconus', '--firdegtextpositionalaska',
#                 '--firdegtextpositioncanada' and '--firdegtextpositionmexico' for changing the FIR degradation
#                 text position for the European FIR, CONUS FIR, Alaska FIR, Canada FIR and Mexico FIR respectively.
#               Added option '--nofirdegtext' for not printing the user defined FIR degradation text in the plot.
#               Added options '--nofirdegtexteu', '--nofirdegtextconus', --nofirdegtextalaska', '--nofirdegtextcanada',
#                 '--nofirdegtextmexico' for not printing the European FIR, CONUS FIR, Alaska FIR,
#                 Canada FIR and Mexico FIR degradation text respectively in the map.
#               Added option '--firdegtexttable' for printing the FIR degradation text values in a table. This is
#                 useful when multiple FIR areas are shown.
#               Added option '--printfirdegtext' for printing to standard output the FIR degradation text. If
#                 option '--firdegtexttable' is set, the whole table will be printed.
#               Added option '--writetofilefirdegtext' for writing to a file the FIR degradation text. If
#                 option '--firdegtexttable' is set, the whole table will be written to the file.
#               Added option '--onlyprintfirdegtext' for making the program to exit after printing the FIR degradation
#                text but without showing the SBAS availability maps (useful for batch processing). 
#               Added option '--sbasserviceformat' for automatically setting an alternative format for SBAS maps.
#               Added option '--sbasservicemaritimeformat' for automatically setting an alternative format for SBAS
#                 maritime maps.
#               Added option '--sbasservicebinaryformat' for automatically setting an alternative format for SBAS maps
#                 which has only one two bins (plus the 'Not Avail' bin).
#               Added option '--sbasservicemaritimebinaryformat' for automatically setting an alternative format for 
#                 SBAS maritime maps which has only one two bins (plus the 'Not Avail' bin).
#               Added option '--disablebineqcond' for disabling the condition in "greater equal" or "less equal"
#                 (option '--bineqcond') which is enabled by default when using options '--sbasserviceformat',
#                 '--sbasservicemaritimeformat', '--sbasservicebinaryformat' or '--sbasservicemaritimebinaryformat'.
#               Added option '--contriskaspercentage' for showing the bin values in the continuity risk and
#                 maritime continuity risk as percentages instead of unitary values.
#               Added option '--countries' for drawing the country borders in SBAS availability maps and
#                 world maps/integrity maps/station maps.
#               Added option '--usastates' for drawing the USA state borders in SBAS availability maps and
#                 world maps/integrity maps/station maps.
#               Added option '--textmark' for adding a text mark in the plot. Multiple text marks can be set
#                 by providing this option as many times as necessary.
#               Added option '--textmarkcolor' for setting the colour of the text mark. Set this option for
#                 each text mark.
#               Added option '--textmarksize' for setting the size of the text mark. Set this option for
#                 each text mark.
#               Added option '--textmarkposition' for setting the position of the text mark. Set this option for
#                 each text mark.
#               Added check for empty input files. If input file is empty, it will show an error message
#                 and exit, instead of showing empty plots or crashing.
#               Added check for values for the colourbar bins. Now values outside the nominal ranges will not
#                 be accepted ([0-100] for availability and ionosphere availability maps, [0-1] for continuity
#                 risk and maritime continuity risk and [0-infinite] for DOP maps).
#               Added missing check for assuring that the number of colours provided for the SBAS ionosphere
#                 availability map matches the number of bins in the colourbar.
#               Added checks for the contour lines to be computed. Now it will not let you set the value of the
#                 smallest bin (as this makes the python function to crash). Furthermore, if one of the defined
#                 bins does not appear in any of the positions in the map, the contour line for this bin will
#                 be skipped, as this case made the python function to show incorrect contour lines.
#               Added check for Python versions >=2.7.15 and >=3.6 in SBAS availability maps. In these versions
#                 it is necessary to set greater margins in order to fit the horizontal legend or the colourbar
#                 bin texts.
#               In 64 bit Windows, python is now distributed with Python 3.6.6 64bit, instead of Python 2.6 32 bit
#                  (in Windows 32-bit still remains Python 2.6 32 bit).
#               Help message now shows explicitly the values that must be provided to the parameters (if required),
#                 by showing next to the parameter '<text>' (a text is required), '#' (a numerical value is required), 
#                 '#,#,...' (a list of numerical values is required), etc. 
#               Option '--bineqcond' is now also accepted as '--BinEqCond'.
#               Option '--fireu' is now also accepted as '--FIREu'.
#               It is possible to define as many user defined FIR areas as needed, instead of just one, by 
#                 using the parameter '--firuser' as many times as necessary. Each user defined FIR area
#                 properties can be defined independently, by providing the parameters for setting the user 
#                 defined FIR area properties as many times as necessary (in the same order as given in
#                 option '--firuser').
#               User defined FIRs are now also plotted in worst integrity maps.
#               European FIR area or used defined FIR area can now be set both at the same time. Moreover,
#                 any hard-coded FIR area can be set independently from any other FIR area set (including
#                 its drawing properties).
#               Option '--firdegtext' now can also print the number of points over the bin value inside the 
#                 FIR area, the number of points below below the bin value inside the FIR area, the total
#                 number of points inside the FIR area and the total number of points in the whole plot.
#               If the bin with value '100' in SBAS availability or ionosphere availability map is set and
#                 the option '--bineqcond' is set, this bin will appear with the default of text '=100'
#                 instead of '≥100'.
#               If the bin with value '0' in SBAS continuity risk, maritime continuity risk or DOP maps is set
#                 and the option '--bineqcond' is set, this bin will appear with the default of text '=0'
#                 instead of '≤0'.
#               In standard 2D plots, space for a title with up to three lines will be left even if option
#                 '--atm' is disabled (before the space was left only if '--atm' option was enabled).
#               If option '--firdegtext' is provided, FIR degradation computation will be automatically
#                 enabled (so it matches the behaviour of options '--firdegtextsize', '--firdegtextcolor'
#                 and '--firdegtextposition', which automatically enabled the FIR degradation computation).
#               Error messages due to invalid values in parameters or in input files will now always show
#                 the invalid value in the error message (except for user defined column numbers).
#               Errors due to incorrect colour or line type are now captured and show in an error message,
#                 instead of printing the Python's full traceback (except in Windows).
#               Parameter '--availcontourlevels' now can also be called as '--availcontourlines'. Both options
#                 are equally valid.
#               Parameter '--contriskcontourlevels' now can also be called as '--contriskcontourlines'. Both
#                 options are equally valid.
#               Parameter '--contriskmarcontourlevels' now can also be called as '--contriskmarcontourlines'. 
#                 Both options are equally valid.
#               Parameter '--nocontourlines' now can also be called as '--nocontourlevels'. Both options are 
#                 equally valid.
#               Changed behaviour when an invalid parameter is given. Now, instead of printing the help and
#                 the error message, it will just print the error message.
#               If user sends SIGINT signal (Ctrl+c in Unix terminal), the program will terminate without
#                 printing the traceback (except on Windows).
#               Changed option name from '--FIRDegrafation' to '--FIRDegradation' due to it was a typo in the
#                 name, as the lower case option is '-firdegradation'. The previous name '--FIRDegrafation'
#                 will still be accepted for backwards compatibility.
#               Changed slightly the input of parameter '--contriskmarbincolors', as now the colour of the
#                 "NA" (Not Available) bin must not be provided, where as before it had to be provided.
#                 The colour of the "NA" bin is now changed with parameter '--notavailbincolor'.
#               Changed value formatting in error message when checking user defined contour values for
#                 continuity risk and maritime continuity risk maps. The offending value will be printed
#                 with exponential format instead of decimal format, in order to prevent that values
#                 smaller than 0.1 (such as 1e-3) is not shown as '0.0'.
#               String formatting in all the graph.py code now uses the new python formatting style
#                 ("{0:s}".format(val)) instead of the old formatting style ("%s" %val).
#               Changed the reference coordinate system to 'axes fraction' (that is, coordenate origin is at 
#                 the bottom left of the figure) for all user defined positions for watermark, textmark and
#                 SBAS maps degradation text. 
#               If user sets bins over 99.9 (99.99, 99.999,...) the plot margins will auto adjust to fit
#                 the number in the colourbar text.
#               Fixed bin "100.0" text in colourbar going out of the borders when user manually selected 
#                 the "100.0" bin in SBAS availability and ionosphere availability maps.
#               Fixed user defined FIR text (option '--firdegtext') not working when using Python3.
#               Fixed world maps/integrity maps/station maps not working with old Linux distributions
#                 using Python 2.6 (e.g. Ubuntu 10.04).
#               Fixed division by zero when computing the degradation values when there were no points 
#                 inside the European FIR or user defined FIR area.
#               Fixed legend not appearing in station maps when only the station name was printed.
#               Fixed the string "DOP" being replaced for the DOP map type when the title has been defined
#                 the user (it had to occur only when the title was automatically set).
#               Fixed error in Python 2 when station names was a number. Now the number will read as the
#                 name, instead of crashing.
#               In SBAS DOP plots, if the number of epochs were 0, then the mean and percentile DOP was
#                 also 0, therefore this points were plotted to be under the minimum DOP threshold set
#                 (by default, shown in red colour), which was incorrect. Now, when the number of epochs
#                 is 0, this points will be internally set as "999", so they are shown in the greatest bin.
#               SBAS plots with an aspect ratio of 1.4 or below (defined as (MaxLon-MinLon)/(MaxLat-MinLon) 
#                 or the relation with the width and height) were plotted incorrectly (labels, title or 
#                 even the image was out of bounds) due to an incorrect size handling inside Python libraries.
#                 It has been fixed by forcing to leave margins in the plots.
#               For default SBAS plots (EGNOS default coverage area), if option '--prntextnewline' was
#                 enabled, the title would go out of bounds. Now the margin will increase in order to
#                 leave space for the extra line.
#               Fixed bug that made European FIR in station maps use the properties from the user defined
#                 FIRs, instead of the European FIR properties.
#               Fixed bug that made to apply maritime continuity risk contour levels to non maritime Continuity
#                 risk.
#               Some parameters which were expected to be provided only once (in concrete '--availbincolors',
#                 '--contriskbincolors', '--contriskmarbincolors', '--ionoavailbincolors', '--hdopbincolors',
#                 '--pdopbincolors', '--gdopbincolors', '--firdegtextbinseu', '--xtickslist' and '--ytickslist')
#                 would mess up the results or crash the program if they were provided more than once, as it
#                 mixed all the data provided each time the parameter was provided. Now it will only use the
#                 data given the last time the parameter is read.
#               Fixed "IOError: [Errno 32] Broken pipe" exception when the help was shown ('-h' parameter) and
#                 the output was redirected to a pipe (for instance, a pipe to the 'less' command), and the pipe
#                 was closed before reaching the end of the help.
# -----------
#          gLAB v5.4.1
# Release: 2019/02/15
# Change Log:   Added option '--firsumdeg' for computing the total degradation percentage
#                 in all or some of the FIRs enabled in the SBAS plots. By default it
#                 selects all of them, but if user selects one or more FIRs, only the
#                 selected FIRs will be used for the total degradation computation.
#               Added options '--firsumdegeu', '--firsumdegconus', '--firsumdegalaska',
#                 '--firsumdegcanada', '--firsumdegmexico' and '--firsumdeguserfir' for
#                 controlling which FIRs want to be used for the total degradation computation.
#               Added options '--firdegtextheaderfirsum', '--firdegtextfooterfirsum',
#                 '--firdegtextfirsum', '--firdegtextsizefirsum', '--firdegtextcolorfirsum'
#                 and '--firdegtextpositionfirsum' for controlling the output text and its
#                 properties for the total degradation computation.
#               Parameter '--nofirdegtext' now accepts a comma separated list of FIR numbers.
#               Fixed an error when printing the number of points below the bin value 
#                 inside the FIR area for user defined FIR areas.
#               
# -----------
#          gLAB v5.4.2
# Release: 2019/03/08
# Change Log:   Fixed bug in Stanford plots mode that made to appear false MIs when
#                 the difference between the error and the protection level was smaller
#                 than the resolution step for quantization and both values were not
#                 greater than the maximum value in their axis.
# -----------
#          gLAB v5.4.3
# Release: 2019/03/20
# Change Log:   Added options '--nogeometriesintitle', '--NoGeometriesInTitle',
#                 '--noepochsintitle' and '--NoEpochsInTitle'. All of them have the
#                 same effect: not to add the number of epochs or geometries in the
#                 title in Stanford or Stanford-ESA modes.
#               Added option '--sfesawithregions' in Stanford-ESA mode to plot the
#                 five regions (available, MI, HMI, Unavailable, Unavailable and MI)
#                 as in Stanford plot mode. With this option, the user can now create
#                 a Stanford Plot from a quantized file already created by the user
#                 (e.g. a file created from epochs of several years).
#               Added option '--sfesawithepochs' to write 'Epochs' instead of geometries
#                 in the Stanford-ESA plot.
#               Added capability to set the number of epochs/geometries, number of
#                 points that are not MI, the number of points that are MI and the
#                 number of points of each of the five regions (available, MI,
#                 HMI, Unavailable, Unavailable and MI).
#               Added options '--hal' and '--val' for setting the alarm limits in the
#                 horizontal and vertical axis respectively in Stanford-ESA plots.
#               Added options '--availepochpos', '--unavailepochpos', '--hmiepochpos',
#                 '--miavailepochpos' and '--miunavailepochpos' in Stanford and
#                 Stanford-ESA modes for setting the position for the text printed
#                 in each of the regions (available, MI, HMI, Unavailable, 
#                 Unavailable and MI) respectively.
#               Options '--percentilex', '--percentiley', '--percentilexlist' and
#                 '--percentileylist' from Stanford mode now also work in
#                 Stanford-ESA mode.
#               Fixed some geometries not counted as MIs in Stanford-ESA mode when
#                 the quantized protection level value was 0.
#               Fixed crash in Stanford-ESA mode when the total number of geometries
#                 in any of the axis was 0 or 1.
#               Fixed incorrect plotting size in Stanford mode when user set a title
#                 with two newlines and option 'adjust to margin' was not set.
#               Fixed "System unavailable" number of epochs in Stanford plots, which
#                 was also counting the epochs with MIs and over the alarm limit,
#                 when it should only count the number of epochs over the alarm but
#                 not MI.
# -----------
#          gLAB v5.4.4
# Release: 2019/05/10
# Change Log: Changed error message from "ERROR: One of the column number provided does 
#               not exist in line number {0:d} of SBAS maps data file" to
#               "ERROR: One of the column number provided does not exist in line number
#               {0:d} of data file". That is, the "SBAS map" words have been removed,
#               as the error could also occur with non SBAS map data files.
# -----------
#          gLAB v5.5.0
# Release: 2020/10/30
# Change Log:   Fixed exception when the INFO lines contained filepaths with non-ascii characters.
#                 These encoding errors will be ignored as these INFO lines are the only one that
#                 may contain non ASCII characters and are not used by the plotting tool.
# -----------
#          gLAB v5.5.1
# Release: 2020/12/11
# Change Log: No changes in this file.
# -----------
#       END_RELEASE_HISTORY
#############################################################################

import sys,os,matplotlib,math,optparse,re,warnings,errno
import traceback
import signal

#Ignore all deprecated warnings
warnings.filterwarnings("ignore");

from matplotlib.ticker import MultipleLocator, FormatStrFormatter
from optparse import OptionParser
if (sys.platform[:3].lower() == "win"):
    sys.stdout=sys.stderr

global PythonVersion
global PythonVersionDecimal
global legend
global LockFile
global CreateLockFile

legend=False
PythonVersion=sys.version_info[0]
PythonVersionDecimal=float(str(sys.version_info[0])+"."+str(sys.version_info[1]))
LockFile=".plot.lock"
CreateLockFile=True

if (sys.platform[:3].lower() != "win"):
    #Tkinter when has an error shows an exception, but is not caught by the try/except
    #A function in needed to be called when tkinter has an error
    #In Windows, when compiled into a self-executable, this code makes the program
    #instantaneously close without giving an error
    def tkinter_show_error(self,*args):
        err = str(traceback.format_exception(*args))
        if "rgb" in err:
            err = err.split("\\n")
            err = err[len(err)-3].split('"')
            #Color is  the only exception possible, as all other user input has been checked before
            print ("ERROR: User defined colour '{0:s}' is not a valid colour".format(err[1]))
        else:
            #Unknown error
            print (err.replace("\\n","\n"))
        removeLockFile()
        sys.exit()

    if PythonVersion == 2:
        import Tkinter
        #With this command, when Tkinter has an error it will call this function
        Tkinter.Tk.report_callback_exception = tkinter_show_error
    else:
        import tkinter
        #With this command, when Tkinter has an error it will call this function
        tkinter.Tk.report_callback_exception = tkinter_show_error


if (sys.platform[:3].lower() != "win"):
    #Function to capture SIGINT signal (Ctr+C)
    #In Windows, when compiled into a self-executable, the process automatically goes into background, 
    #so we cannot send the signal through the terminal
    def signal_SIGINT_handler(sig, frame):
        removeLockFile()
        sys.exit(1)

    #Capture SIGINT signal (Ctr+C), so it exits without printing the python trace
    signal.signal(signal.SIGINT, signal_SIGINT_handler)

class Plot:
    def __init__(self):
        self.FileName = ""
        self.ColX = "var[0]"
        self.ColY = "var[1]"
        self.Cond = ""
        self.Label = ""
        self.Xvar = []
        self.Yvar = []
        self.Style = "."
        self.MarkerSize = 5
        self.LineWidth = 0
        self.PlotColor = ""
        self.PlotColorAuto = True
        
        
class Graphic:
    def __init__(self):
        self.PlotList=[]
        self.PlotCounter = 0
        self.Title = ""
        self.Xlabel = ""
        self.Ylabel = ""
        self.FractionalTitle = ""
        self.WaterMark = ""
        self.WaterMarkColour = 'k'
        self.WaterMarkSize = 8
        self.WaterMarkSizeSetbyUser = 0
        self.WaterMarkPositionX = -999
        self.WaterMarkPositionY = -999
        self.WaterMarkPositionSetbyUser = 0
        self.TextMark = []
        self.TextMarkColour = []
        self.TextMarkSize = []
        self.TextMarkPositionX = []
        self.TextMarkPositionY = []
        self.NumTextMark = 0
        self.NumTextMarkColour = 0
        self.NumTextMarkSize = 0
        self.NumTextMarkPosition = 0
        self.TextMarkColourDefault = 'k'
        self.TextMarkSizeDefault = 15
        self.TextMarkPositionXDefault = 0.5
        self.TextMarkPositionYDefault = 0.5
        self.Cbarlabel = ""

        self.SupportedStylesCharactersList=['.','-','--','-.','.-',':',',','o','s','p','+','x','^','>','<','v','*','h','H','D','d','|','_','1','2','3','4']

        self.ColXUser = False
        self.ColYUser = False

        self.Xmin = 0.0
        self.Xmax = 0.0
        self.Ymin = 0.0
        self.Ymax = 0.0
        
        self.XminAuto = True
        self.XmaxAuto = True
        self.YminAuto = True
        self.YmaxAuto = True
        
        self.XTicsUser = False
        self.YTicsUser = False
        self.XTicsStepUser = False
        self.YTicsStepUser = False
        self.XTicsListUser = False
        self.YTicsListUser = False

        self.XTicsMax = 0.0
        self.XTicsMin = 0.0
        self.XTicsNum = 0
        self.YTicsMax = 0.0
        self.YTicsMin = 0.0
        self.YTicsNum = 0
        self.XTicsStep = 0.0
        self.YTicsStep = 0.0
        self.XTicksList = []
        self.YTicksList = []

        self.AdjustToMargin = False

        self.SaveFigure = False
        self.SaveFigurePath = []
        
        self.grid = True
        
        self.NumPointsLabelUser = False
        self.NumPointsLabel = 2
        self.LabelPosition = 1
        self.LabelPositionX = ""
        self.LabelPositionY = ""

        self.stanford = False
        self.ALAuto = True 
        self.NoEpochsInTitle = False
        self.StfdPercentileX = False
        self.StfdPercentileY = False
        self.StfdPercentileDefaultX = [0.68,0.95,0.999] 
        self.StfdPercentileDefaultY = [0.68,0.95,0.999]
        self.StfdPercentileListX = []
        self.StfdPercentileListY = []
        self.AvailEpochPosX = 999.
        self.AvailEpochPosY = 999.
        self.UnAvailEpochPosX = 999.
        self.UnAvailEpochPosY = 999.
        self.MIAvailEpochPosX = 999.
        self.MIAvailEpochPosY = 999.
        self.HMIAvailEpochPosX = 999.
        self.HMIAvailEpochPosY = 999.
        self.MIUnAvailEpochPosX = 999.
        self.MIUnAvailEpochPosY = 999.
        
        self.stanfordESA = False
        self.sfESAwithRegions = False
        self.resolution_x_auto = True
        self.resolution_y_auto = True
        self.sfESAHAL = 40
        self.sfESAVAL = 50
        self.textGeometriesLarge = "Geometries"
        self.textGeometriesShort = "Geom"
        
        self.maxpoints_auto = True
        self.worstIntegrityRatio = False
        self.worstIntegrityRatioColorbar = False
        self.SBASmaps = False
        self.ColName = ""
        self.ColLabelName = ""
        self.ColRatioV = ""
        self.ColRatioH = ""
        self.ColMIsV = ""
        self.ColMIsH = ""
        self.projection = "cyl"
        self.cbarAutoMin = True
        self.cbarAutoMax = True
        self.cbarAutoN = True
        self.StaNetAddLabel = False
        self.StaNetAddNumStations = False
        self.StaNetWorkWithNames = False
        self.StaNetWorkWithMarkers = False
        self.StaNetWorkDefName = 'Other'
        self.StaNetWorkDefNameSize = 9
        self.StaNetWorkDefNameColor = 'blue'
        self.StaNetWorkDefNameHorAlign = 'center'
        self.StaNetWorkDefNameVerAlign = 'bottom' #Note: Vertical alignment is inverted when applied by annotate function, so this is 'top' alignment
        self.StaNetWorkDefMarkerType = 'o'
        self.StaNetWorkDefMarkerSize = 5
        self.StaNetWorkDefMarkerColor = 'blue'
        self.StaLabelListName = []
        self.StaLabelListValue = []
        self.StaMarkerTypeListName = []
        self.StaMarkerTypeListValue = []
        self.StaMarkerColorListName = []
        self.StaMarkerColorListValue = []
        self.StaMarkerSizeListName = []
        self.StaMarkerSizeListValue = []
        self.StaLetterSizeListName = []
        self.StaLetterSizeListValue = []
        self.StaLetterColorListName = []
        self.StaLetterColorListValue = []
        self.StaLetterHorAlignListName = []
        self.StaLetterHorAlignListValue = []
        self.StaLetterVerAlignListName = []
        self.StaLetterVerAlignListValue = []

        self.Countries = False
        self.USAStates = False
        self.continentColor = ""
        self.lakeColor = ""
        self.boundaryColor = ""
        self.MapResolution = "l"
        self.ColorMap = ""

        self.BinsEqualCondition = False
        self.DisableBinsEqualCondition = False
        self.ContRiskAsPercentage = False
        self.ServiceFormat = False
        self.ServiceBinaryFormat = False
        self.ServiceFormatMaritime = False
        self.ServiceBinaryFormatMaritime = False
        self.NotAvailBin = True
        self.NotAvailColour = "#000000"
        self.NotAvailText = "NA"
        self.contourlines = True
        self.CbarPercentage = True
        self.AvailCbarTitle = ""
        self.ContRiskCbarTitle = ""
        self.ContRiskMarCbarTitle = ""
        self.IonoAvailCbarTitle = ""
        self.HDOPCbarTitle = ""
        self.PDOPCbarTitle = ""
        self.GDOPCbarTitle = ""
        self.DOPPercentilePlot = False
        self.SBASsystemName = ""
        self.PRNtext = ""
        self.PRNtextNewline = False
        self.UserSetAvailBins = False
        self.UserSetIonoBins = False
        self.UserSetRiskBins = False
        self.UserSetRiskMarBins = False
        self.UserSetHDOPBins = False
        self.UserSetPDOPBins = False
        self.UserSetGDOPBins = False
        self.AvailBins = [19.9,20.0,50.0,75.0,90.0,95.0,97.5,99.0,99.5,99.9]
        self.IonoAvailBins = [19.9,20.0,50.0,75.0,90.0,95.0,97.5,99.0,99.5,99.9]
        self.RiskBins = [7.6e-3,7.5e-3,5e-3,2.5e-3,1e-3,7.5e-4,5e-4,2.5e-4,1e-4,1e-5]
        self.RiskMarBins = [7.6e-3,7.5e-3,5e-3,2.5e-3,1e-3,7.5e-4,5e-4,2.5e-4,1e-4,1e-5]
        self.HDOPBins = [4.1,4,2]
        self.PDOPBins = [6.1,6,3.5]
        self.GDOPBins = [7.1,7,5]
        self.AvailBinsText = []
        self.IonoAvailBinsText = []
        self.RiskBinsText = []
        self.RiskMarBinsText = []
        self.HDOPBinsText = []
        self.PDOPBinsText = []
        self.GDOPBinsText = []
        self.AvailContourLevels = [95.0,97.5,99.9]
        self.RiskContourLevels = [1e-3,1e-5]
        self.RiskMarContourLevels = [1e-3,1e-5]
        self.AvailColorList = []
        self.ContRiskColorList = []
        self.ContRiskMarColorList = []
        self.IonoAvailColorList = []
        self.HDOPColorList = []
        self.PDOPColorList = []
        self.GDOPColorList = []
        self.TopMargin = -1
        self.BottomMargin = -1
        self.LeftMargin = -1
        self.RightMargin = -1
        self.SBASplotUserSetSize = False
        self.FigHorSize = -1
        self.FigVerSize = -1

        self.UserDefinedBinsOrContours = False
        self.UserDefinedAvailContourlevels = False
        self.UserDefinedRiskContourlevels = False
        self.UserDefinedRiskMarContourlevels = False

        self.FIREurope = False
        self.FIRCONUS = False
        self.FIRAlaska = False
        self.FIRCanada = False
        self.FIRMexico = False
        self.FIRDegradation = False
        self.FIRNumUserFile = 0
        self.FIRUserFile = []
        self.latFIR = [[]]
        self.lonFIR = [[]]
        self.latFIREur = []
        self.lonFIREur = []
        self.latFIRCONUS = []
        self.lonFIRCONUS = []
        self.latFIRAlaska = []
        self.lonFIRAlaska = []
        self.latFIRCanada = []
        self.lonFIRCanada = []
        self.latFIRMexico = []
        self.lonFIRMexico = []
        self.FIRUserSelLineColorEur = False
        self.FIRUserSelLineColorCONUS = False
        self.FIRUserSelLineColorAlaska = False
        self.FIRUserSelLineColorCanada = False
        self.FIRUserSelLineColorMexico = False
        self.FIRShowBorder = [1]
        self.FIRShowBorderEur = True
        self.FIRShowBorderCONUS = True
        self.FIRShowBorderAlaska = True
        self.FIRShowBorderCanada = True
        self.FIRShowBorderMexico = True
        self.FIRNumLineColor = 0
        self.FIRLineColorDefault = 'w'
        self.FIRLineColor = []
        self.FIRLineColorEur = self.FIRLineColorDefault
        self.FIRLineColorCONUS = self.FIRLineColorDefault
        self.FIRLineColorAlaska = self.FIRLineColorDefault
        self.FIRLineColorCanada = self.FIRLineColorDefault
        self.FIRLineColorMexico = self.FIRLineColorDefault
        self.FIRNumMarkerSize = 0
        self.FIRMarkerSizeDefault = 5
        self.FIRMarkerSize = []
        self.FIRMarkerSizeEur = self.FIRMarkerSizeDefault
        self.FIRMarkerSizeCONUS = self.FIRMarkerSizeDefault
        self.FIRMarkerSizeAlaska = self.FIRMarkerSizeDefault
        self.FIRMarkerSizeCanada = self.FIRMarkerSizeDefault
        self.FIRMarkerSizeMexico = self.FIRMarkerSizeDefault
        self.FIRNumLineStyle = 0
        self.FIRLineStyleDefault = '--'
        self.FIRLineStyle = []
        self.FIRLineStyleEur = self.FIRLineStyleDefault
        self.FIRLineStyleCONUS = self.FIRLineStyleDefault
        self.FIRLineStyleAlaska = self.FIRLineStyleDefault
        self.FIRLineStyleCanada = self.FIRLineStyleDefault
        self.FIRLineStyleMexico = self.FIRLineStyleDefault
        self.FIRNumLineWidth = 0
        self.FIRLineWidthDefault = 2
        self.FIRLineWidth = []
        self.FIRLineWidthEur = self.FIRLineWidthDefault
        self.FIRLineWidthCONUS = self.FIRLineWidthDefault
        self.FIRLineWidthAlaska = self.FIRLineWidthDefault
        self.FIRLineWidthCanada = self.FIRLineWidthDefault
        self.FIRLineWidthMexico = self.FIRLineWidthDefault
        self.FIRShowDegText = [1]
        self.FIRShowDegTextEur = True
        self.FIRShowDegTextCONUS = True
        self.FIRShowDegTextAlaska = True
        self.FIRShowDegTextCanada = True
        self.FIRShowDegTextMexico = True
        self.FIRNumDegText = 0
        self.FIRDegTextTable = False
        self.FIRDegTextHeader = []
        self.FIRNumDegTextHeader = 0
        self.FIRDegTextHeaderEur = "]]]]]]]]][[[[[[[[[[[" #Random text to check that user did not set any header or empty header
        self.FIRDegTextHeaderCONUS = "]]]]]]]]][[[[[[[[[[["
        self.FIRDegTextHeaderAlaska = "]]]]]]]]][[[[[[[[[[["
        self.FIRDegTextHeaderCanada = "]]]]]]]]][[[[[[[[[[["
        self.FIRDegTextHeaderMexico = "]]]]]]]]][[[[[[[[[[["
        self.FIRDegTextHeaderFIRSum = "]]]]]]]]][[[[[[[[[[["
        self.FIRDegTextFooter = []
        self.FIRNumDegTextFooter = 0
        self.FIRDegTextFooterEur = ""
        self.FIRDegTextFooterCONUS = ""
        self.FIRDegTextFooterAlaska = ""
        self.FIRDegTextFooterCanada = ""
        self.FIRDegTextFooterMexico = ""
        self.FIRDegTextFooterFIRSum = ""
        self.FIRDegText = []
        self.FIRDegTextEur = ""
        self.FIRDegTextCONUS = ""
        self.FIRDegTextAlaska = ""
        self.FIRDegTextCanada = ""
        self.FIRDegTextMexico = ""
        self.FIRDegTextFIRSum = ""
        self.FIRSum = False
        self.FIRSumWithSelection = False
        self.FIRSumDegEur = False
        self.FIRSumDegCONUS = False
        self.FIRSumDegAlaska = False
        self.FIRSumDegCanada = False
        self.FIRSumDegMexico = False
        self.FIRSumDegUserFIR = []

        self.FIRNumDegTextBins = 0
        self.FIRNumDegTextBinsEur = 0
        self.FIRNumDegTextBinsCONUS = 0
        self.FIRNumDegTextBinsAlaska = 0
        self.FIRNumDegTextBinsCanada = 0
        self.FIRNumDegTextBinsMexico = 0
        self.FIRNumDegTextBinsFIRSum = 0
        self.FIRNumDegTextBinsPos = []
        self.FIRNumDegTextBinsPosEur = 0
        self.FIRNumDegTextBinsPosCONUS = 0
        self.FIRNumDegTextBinsPosAlaska = 0
        self.FIRNumDegTextBinsPosCanada = 0
        self.FIRNumDegTextBinsPosMexico = 0
        self.FIRDegTextBins = [[]]
        self.FIRDegTextBinsEur = []
        self.FIRDegTextBinsCONUS = []
        self.FIRDegTextBinsAlaska = []
        self.FIRDegTextBinsCanada = []
        self.FIRDegTextBinsMexico = []
        self.FIRDegTextBinsFIRSum = []
        self.FIRNumDegTextColor = 0
        self.FIRDegTextColorDefault = 'w'
        self.FIRDegTextColor = []
        self.FIRDegTextColorEur = self.FIRDegTextColorDefault
        self.FIRDegTextColorCONUS = self.FIRDegTextColorDefault
        self.FIRDegTextColorAlaska = self.FIRDegTextColorDefault
        self.FIRDegTextColorCanada = self.FIRDegTextColorDefault
        self.FIRDegTextColorMexico = self.FIRDegTextColorDefault
        self.FIRDegTextColorFIRSum = self.FIRDegTextColorDefault
        self.FIRNumDegTextSize = 0
        self.FIRDegTextSizeDefault = 15
        self.FIRDegTextSizeDefaultForTable = 9
        self.FIRDegTextSize = []
        self.FIRDegTextSizeEur = self.FIRDegTextSizeDefault
        self.FIRDegTextSizeCONUS = self.FIRDegTextSizeDefault
        self.FIRDegTextSizeAlaska = self.FIRDegTextSizeDefault
        self.FIRDegTextSizeCanada = self.FIRDegTextSizeDefault
        self.FIRDegTextSizeMexico = self.FIRDegTextSizeDefault
        self.FIRDegTextSizeFIRSum = self.FIRDegTextSizeDefault
        self.FIRNumDegTextPositionX = 0
        self.FIRDegTextPositionXDefault = 0.20
        self.FIRDegTextPositionXDefaultForTable = 0.05
        self.FIRDegTextPositionX = []
        self.FIRDegTextPositionXEur = self.FIRDegTextPositionXDefault
        self.FIRDegTextPositionXCONUS = self.FIRDegTextPositionXDefault
        self.FIRDegTextPositionXAlaska = self.FIRDegTextPositionXDefault
        self.FIRDegTextPositionXCanada = self.FIRDegTextPositionXDefault
        self.FIRDegTextPositionXMexico = self.FIRDegTextPositionXDefault
        self.FIRDegTextPositionXFIRSum = self.FIRDegTextPositionXDefault
        self.FIRNumDegTextPositionY = 0
        self.FIRDegTextPositionYDefault = 0.80
        self.FIRDegTextPositionYDefaultForTable = 0.05
        self.FIRDegTextPositionY = []
        self.FIRDegTextPositionYEur = self.FIRDegTextPositionYDefault
        self.FIRDegTextPositionYCONUS = self.FIRDegTextPositionYDefault -2*0.27
        self.FIRDegTextPositionYAlaska = self.FIRDegTextPositionYDefault
        self.FIRDegTextPositionYCanada = self.FIRDegTextPositionYDefault -0.27
        self.FIRDegTextPositionYMexico = self.FIRDegTextPositionYDefault -3*0.27
        self.FIRDegTextPositionYFIRSum = self.FIRDegTextPositionYDefault -4*0.27
        self.FIRDegTextFontFamily = 'sans-serif'
        self.FIRPrintDegText = False
        self.FIROutputFileNameDegText = ""
        self.FIROnlyPrintDegText = False

    def readDataUserFir(self):
        j=-1
        for filename in Graph.FIRUserFile:
            try:
                 if PythonVersion == 2: 
                     f = open(filename,'rb')
                 else:
                     f = open(filename,'r',errors='replace')
            except:
                Errmsg=str(sys.exc_info()[1]).split(":")
                Errmsg=Errmsg[0].split("] ")
                print ("ERROR Opening file '{0:s}': '{1:s}'".format(filename,Errmsg[1]))
                removeLockFile()
                sys.exit()
            j += 1
            i = 0
            Graph.lonFIR.append([])
            Graph.latFIR.append([])
            for line in f:
                var = line.split()
                i = i + 1
                if var != []: 
                    match_result = re.match(r'^#',var[0])
                    if (match_result == None):
                        if len(var)<2:
                            continue
                        try:
                            lon = float(var[0])
                            lat = float(var[1])
                        except:
                            ErrMsg=str(sys.exc_info()[1]).split()
                            print ("ERROR: Invalid value '{0:s}' in line number {1:d} in FIR data file '{2:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),i,filename))
                            removeLockFile()
                            sys.exit()

                        if lon < -180. or lon > 180.:
                            print ("ERROR: Longitude must be between [-180..180] (check value '{0:s}' in line number {1:d}) in FIR data file '{2:s}'".format(var[0],i,filename))
                            removeLockFile()
                            sys.exit()
                        if lat < -90. or lat > 90.:
                            print ("ERROR: Latitude must be between [-90..90] (check value '{0:s}' in line number {1:d}) in FIR data file '{2:s}'".format(var[1],i,filename))
                            removeLockFile()
                            sys.exit()

                        Graph.lonFIR[j].append(lon)
                        Graph.latFIR[j].append(lat)

        if i<4:
            print ("ERROR: File '{0:s}' has no data".format(filename))
            removeLockFile()
            sys.exit()

        return self
            

###########################################################################
# This part makes the Stanford Plot
# It is inspired by the code from http://kom.aau.dk/~borre/easy2/easy14/
#    Copyright c 1998 The board of trustees of the Leland Stanford     
#    Junior University. All rights reserved. 
#    This script file may be distributed and used freely, provided     
#     this copyright notice is always kept with it.                     
#                                                                       
#     Questions and comments should be directed to Todd Walter at:      
#     walter@relgyro.stanford.edu                                                   
###########################################################################
class stanford:
    def __init__(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        if Graph.AdjustToMargin == True:
            self.fig.tight_layout()
            self.fig.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
        self.AL = 40
        self.PL = []
        self.PE = []
        self.zMax = 0
        self.myPointPatch = []
        self.myPointColors = []
        self.n_fail = 0
        self.n_fail1 = 0
        self.n_fail2 = 0
        self.n_fail3 = 0
        self.n_alarm = 0
        self.n_avail = 0
        self.n_total = 0
        self.Xmin = 0.0
        self.Xmax = 60.0
        self.Ymin = 0.0
        self.Ymax = 60.0
        self.resolution_x = 0.5
        self.resolution_y = 0.5
        self.Xlabel = 'Positioning Error (metres)'
        self.Ylabel = 'Protection Level (metres)'
        self.Title = 'Stanford Plot' 
        self.fColor=['r','pink','m','y']
        self.grid = True
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'

    def dealData(self):
        self.n_total=len(self.PL)
        newPE = []
        newPL = []
        self.intervalNo_x = self.Xmax/self.resolution_x
        self.intervalNo_y = self.Ymax/self.resolution_y
        self.data = np.zeros((int(self.intervalNo_x),int(self.intervalNo_y)))
        self.err_bin = np.linspace(self.resolution_x/2, (self.Xmax-self.resolution_x/2), self.intervalNo_x)
        self.sig_bin = np.linspace(self.resolution_y/2, (self.Ymax-self.resolution_y/2), self.intervalNo_y)
        for idx in range(self.n_total):
            j = self.PE[idx]
            k = self.PL[idx]
            diff = abs(k)-abs(j)
            j = int(abs(j)/self.resolution_x)
            k = int(abs(k)/self.resolution_y)
            if j >=(self.intervalNo_x-1):
                #When values are over maximum plot area, we need to check if they are MI.
                #This is because a value of (100,60) will have the same position in grid that (60,100),
                #making both values counted as MI epochs when there is only one.
                #Therefore, values over maximum over plot area which are not MI will be set in position self.intervalNo_x-2
                if diff>0:
                    j = self.intervalNo_x-2
                else:
                    j = self.intervalNo_x-1
            elif j>=k:
                if diff>0:
                    #This is the case where the PE is over the PL by an amount less than the resolution step. In this case,
                    #the quantization makes index j and k or either be the same (which in that case is an MI) or to j be
                    #larger than k (which is also an MI), but the values without quantization are not an MI.
                    #In this case, to avoid fake MIs, we will set k a value greater than j
                    k=j+1

            newPE.append(j)
            if k >(self.intervalNo_y-1):
                k = self.intervalNo_y-1
            newPL.append(k)     
        for idx in range(self.n_total):
            self.data[int(newPE[idx]),int(newPL[idx])] = self.data[int(newPE[idx]),int(newPL[idx])] + 1
        
        return self
    
    def getPoints(self):
        self.zMax = math.ceil(math.log10(np.max(self.data)))
        aa,bb = np.nonzero(self.data)
        self.x = self.err_bin[aa]
        self.y = self.sig_bin[bb]
        
        delta_x = 0.5 * np.ones(len(aa)) * self.resolution_x
        delta_y = 0.5 * np.ones(len(bb)) * self.resolution_y
        x = self.x - delta_x
        y = self.y - delta_y
        wx = 2 * delta_x
        wy = 2 * delta_y
        mypatch = []
        mycolors = []
        for x1,y1,w,l in zip(x, y, wx, wy):
            rectangle = Rectangle((x1,y1), w, l, linewidth=0)
            mypatch.append(rectangle)
        for idx in range(len(aa)):
            z = math.log10(self.data[aa[idx],bb[idx]])
            c_idx = math.ceil(255*z/self.zMax)
            mycolors.append(c_idx)
        self.myPointPatch = mypatch
        self.myPointColors = np.array(mycolors)
        i_fails = np.where(self.x>=self.y)[0]
        for idx in i_fails:
            self.n_fail = self.n_fail + self.data[aa[idx],bb[idx]] 
            if self.x[idx] < self.AL:
                self.n_fail2 = self.n_fail2 + self.data[aa[idx],bb[idx]]
            elif self.y[idx] >= self.AL:
                self.n_fail3 = self.n_fail3 + self.data[aa[idx],bb[idx]]
            else:
                self.n_fail1 = self.n_fail1 + self.data[aa[idx],bb[idx]]
                
        self.n_nofail = self.n_total - self.n_fail
        i_alarm = np.where(np.logical_and(np.less(x,y),np.greater_equal(y,self.AL)))[0]
        self.n_alarm = sum(self.data[aa[i_alarm],bb[i_alarm]])
        self.n_avail = self.n_total - self.n_alarm - self.n_fail1 - self.n_fail2 - self.n_fail3
        return self
    
    def getPercentileCount(self):  
        text_style1 = dict(horizontalalignment='right', verticalalignment='top',
                  fontsize=12, fontdict={'family': 'monospace'})
        text_style2 = dict(horizontalalignment='center', verticalalignment='center',
                  fontsize=12, fontdict={'family': 'monospace'}, rotation=90)
        if Graph.StfdPercentileListX != []:
            percentPointX = Graph.StfdPercentileListX
        else:
            percentPointX = Graph.StfdPercentileDefaultX

        numPointsX = len(percentPointX)
        lenPE=len(self.PE)
        percentIndexX = []
        for i in range(numPointsX):
            percentIndexX.append(percentPointX[i]*lenPE)

        if Graph.StfdPercentileListY != []:
            percentPointY = Graph.StfdPercentileListY
        else:
            percentPointY = Graph.StfdPercentileDefaultY

        numPointsY = len(percentPointY)
        lenPL=len(self.PL)
        percentIndexY = []
        for i in range(numPointsY):
            percentIndexY.append(percentPointY[i]*lenPL)

        x=sorted(self.PE)
        y=sorted(self.PL)
        self.xPoint = []
        XMaxList = []
        for i in range(numPointsX):
            self.xPoint.append(round(x[int(round(percentIndexX[i]))],2))
            XMaxList.append(self.Xmax)

        self.yPoint = []
        YMaxList = []
        for i in range(numPointsY):
            self.yPoint.append(round(y[int(round(percentIndexY[i]))],2))
            YMaxList.append(self.Ymax)

        if Graph.StfdPercentileX:
            self.ax.plot(self.xPoint,XMaxList,'v',markersize=10)
            for per, xp in zip(percentPointX,self.xPoint):
                self.ax.text(xp+.07,(0.9*self.Ymax+0.1*self.Ymin),'{0:.1f}%'.format(100.*per),**text_style2)     
        if Graph.StfdPercentileY:
            self.ax.plot(YMaxList,self.yPoint,'<',markersize=10)
            for per, yp in zip(percentPointY,self.yPoint):
                self.ax.text((0.97*self.Xmax+0.03*self.Xmin),yp,'{0:.1f}%'.format(100.*per),**text_style1) 
        return self    
        
    def plotPoints(self):     
        p = PatchCollection(self.myPointPatch, cmap=plt.get_cmap(self.cm), linewidth=0)       
        p.set_array(self.myPointColors)
        self.ax.add_collection(p)
        m = self.zMax + 1
        cbarTicks = np.linspace(0, 255, m)
        cbarLabel = np.linspace(0, m-1, m)
        
       
        if Graph.StfdPercentileY:
            NumNewlines=self.Title.count('\n')
            if NumNewlines>=2 and Graph.AdjustToMargin == False:
                pCbar = plt.colorbar(mappable=p, ticks=cbarTicks,pad=0.16)
            else:
                pCbar = plt.colorbar(mappable=p, ticks=cbarTicks,pad=0.1)
        else:
            pCbar = plt.colorbar(mappable=p, ticks=cbarTicks)
        pCbar.ax.set_yticklabels(cbarLabel) 
        pCbar.ax.set_ylabel('Number of Points per Pixel (logarithmic)')
        if Graph.AvailEpochPosX != 999.:
            self.ax.text(Graph.AvailEpochPosX,Graph.AvailEpochPosY, 'Normal Operation \nEpochs: {0:.0f}\n{1:.3f}%'.format(self.n_avail,100.*self.n_avail/float(self.n_total)), style='italic',transform=self.ax.transAxes)
        else:
            self.ax.text(self.AL/5, 6*self.AL/7, 'Normal Operation \nEpochs: {0:.0f}'.format(self.n_avail), style='italic')
            self.ax.text(self.AL/5, 5.5*self.AL/7, '{0:.3f}%'.format(100.*self.n_avail/float(self.n_total)), style='italic')
        return self
    
    def plotPatch(self):        
        
        fail1=Rectangle((self.AL, self.Ymin), (self.Xmax - self.AL), self.AL, lw=1, facecolor=self.fColor[0], alpha=0.2 )
        self.ax.add_patch(fail1)
        if Graph.HMIAvailEpochPosX != 999.:
            self.ax.text(Graph.HMIAvailEpochPosX,Graph.HMIAvailEpochPosY, 'HMI \nEpochs: {0:.0f}'.format(self.n_fail1) , style='italic',transform=self.ax.transAxes)
        elif self.AL<=45:
            self.ax.text(8*self.AL/7, 1*self.AL/7, 'HMI \nEpochs: {0:.0f}'.format(self.n_fail1) , style='italic')
        else:
            self.ax.text(7*self.AL/7, 1*self.AL/7, 'HMI \nEpochs: {0:.0f}'.format(self.n_fail1) , style='italic')
        
        vert2 = [(self.Xmin, self.Ymin), (self.AL, self.AL),(self.AL, self.Ymin), (self.Xmin,self.Ymin),]
        code2 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path2 = Path(vert2, code2)
        fail2=PathPatch(path2, facecolor=self.fColor[1], lw=1, alpha=0.2)
        self.ax.add_patch(fail2)
        if Graph.MIAvailEpochPosX != 999.:
            self.ax.text(Graph.MIAvailEpochPosX, Graph.MIAvailEpochPosY, 'MI \nEpochs: {0:.0f}'.format(self.n_fail2) , style='italic',transform=self.ax.transAxes)
        else:
            self.ax.text(2*self.AL/5, 1*self.AL/7, 'MI \nEpochs: {0:.0f}'.format(self.n_fail2) , style='italic')
        
        vert3 = [(self.AL, self.AL), (self.Xmax, self.Ymax), (self.Xmax, self.AL), (self.AL, self.AL),]
        code3 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path3 = Path(vert3, code3)
        fail3=PathPatch(path3, facecolor=self.fColor[2], lw=1, alpha=0.2)
        self.ax.add_patch(fail3)
        MItext="MI"
        if Graph.MIUnAvailEpochPosX != 999.:
            self.ax.text(Graph.MIUnAvailEpochPosX, Graph.MIUnAvailEpochPosY, '{0:>6s} \nEpochs: {1:.0f}'.format(MItext,self.n_fail3) , style='italic',transform=self.ax.transAxes)
        elif self.AL<=45:
            self.ax.text(8*self.AL/7, 17*self.AL/16, '{0:>6s} \nEpochs: {1:.0f}'.format(MItext,self.n_fail3) , style='italic')
        else:
            self.ax.text(7*self.AL/7, 16.2*self.AL/16, '{0:8s} \nEpochs: {1:.0f}'.format(MItext,self.n_fail3) , style='italic')
        
        vert1 = [(self.Xmin, self.AL), (self.Xmin, self.Ymax), (self.Xmax, self.Ymax), (self.AL, self.AL), (self.Xmin, self.AL),]
        code1 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path1 = Path(vert1, code1)
        alarm=PathPatch(path1, facecolor=self.fColor[3], lw=1, alpha=0.2)
        self.ax.add_patch(alarm)
        if Graph.UnAvailEpochPosX != 999.:
            self.ax.text(Graph.UnAvailEpochPosX,Graph.UnAvailEpochPosY, 'System Unavailable \nAlarm Epochs: {0:.0f}'.format(self.n_alarm) , style='italic',transform=self.ax.transAxes)
        elif self.AL<=45:
            self.ax.text(2*self.AL/5, 8*self.AL/7, 'System Unavailable \nAlarm Epochs: {0:.0f}'.format(self.n_alarm) , style='italic')
        else:
            self.ax.text(2*self.AL/5, 7.5*self.AL/7, 'System Unavailable \nAlarm Epochs: {0:.0f}'.format(self.n_alarm) , style='italic')
        return self
    
    def plotShow(self):
        plt.axis([self.Xmin, self.Xmax, self.Ymin, self.Ymax])
        #There is a bug in Python 2 and 3 that makes only showing one axe ticks when ticks are set in right or top sides (twinx() or twiny() functions)
        #To get around it, the extra ticks for sigma will be made with horizontal and vertical lines and text annotations for the labels
        bias=0
        if Graph.StfdPercentileY:
            bias=0.1
            #To set the labels in the correct position, we use the function matplotlib.transforms.blended_transform_factory to get the coordinate
            #system in the bottom right corner. Coordinates are from(0,0) to (1,1). The (self.ax.transAxes,self.ax.transData) means that the first
            #item is a coordinate in normalized X (0,1), and the second is a coordinate according to data max and min values
            trans = matplotlib.transforms.blended_transform_factory(self.ax.transAxes,self.ax.transData)
            for elem in self.yPoint:
                plt.axhline(elem, linestyle='dotted',color='black',linewidth=.9)
                #self.ax.annotate(elem, xy=(1.01, elem), xycoords=trans, clip_on=False, va='center') #Previous command. For unknown reasons, sometimes made python crash
                self.ax.text(1.01,elem,"{0:.2f}".format(elem),transform=trans, clip_on=False, va='center')
        if Graph.StfdPercentileX:
            bias=0
            if PythonVersionDecimal>=2.7:
                xBias=.05
                UpPos=1.06
            else:
                xBias=.07
                UpPos=1.01
            #The transform is the same as before,but now X is data and Y is normalized
            #The annotation in Y axis does not get perfect, we have to hardcode some correction 
            trans = matplotlib.transforms.blended_transform_factory(self.ax.transData,self.ax.transAxes)
            for elem in self.xPoint:
                plt.axvline(elem, linestyle='dotted',color='black',linewidth=.9)
                #self.ax.annotate(elem-.07,1.07,elem, xycoords=trans, clip_on=False,rotation=90) #Previous command. For unknown reasons, sometimes made python crash
                self.ax.text(elem-xBias,UpPos,"{0:.2f}".format(elem),transform=trans,clip_on=False,rotation=90)

        #Set sigma ticks. Set user defined ticks if user has set any
        if Graph.XTicsUser == True:
            self.ax.set_xticks(np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            self.ax.set_xticks(np.linspace(self.Xmin,self.Xmax,abs(int((self.Xmax-self.Xmin)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            self.ax.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            self.ax.set_yticks(np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            self.ax.set_yticks(np.linspace(self.Ymin,self.Ymax,abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            self.ax.set_yticks(Graph.YTicksList)

        self.ax.set_xlabel(self.Xlabel)
        self.ax.set_ylabel(self.Ylabel)

        NumNewlines=self.Title.count('\n')
        if Graph.AdjustToMargin == True:
            #Add space to fit multiline title
            if NumNewlines == 1:
                self.fig.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                self.fig.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                self.fig.subplots_adjust(top=.83)
            elif Graph.StfdPercentileX:
                self.fig.subplots_adjust(top=(1-bias))
        else:
            if NumNewlines >0 and PythonVersionDecimal<2.7:
                self.fig.subplots_adjust(right=.74)

        #Check if Newline are at the end. In that case, we need to add the number of epochs before the newlines
        if NumNewlines>0:
            NumNewlinesEnd = 0
            for i in range(NumNewlines):
                if (self.Title[len(self.Title)-1-i]=='\n'):
                    NumNewlinesEnd = NumNewlinesEnd + 1
                    if Graph.AdjustToMargin == False:
                        #Add space to fit multiline title if option to adjust to margin is not enabled
                        if Graph.StfdPercentileX:
                            bias = bias + .06
                else:
                    break
            if Graph.AdjustToMargin == False and Graph.StfdPercentileX:
                if NumNewlines==1:
                    self.fig.subplots_adjust(top=(1-bias-.1*(NumNewlines-NumNewlinesEnd)))
                else:
                    self.fig.subplots_adjust(top=(1-bias-.062*(NumNewlines-NumNewlinesEnd)))
            try:
                if NumNewlinesEnd>0:
                    Titlebuffer=self.Title[:-NumNewlinesEnd].format(int(self.n_total),int(self.n_nofail),int(self.n_fail),int(self.n_avail),int(self.n_alarm),int(self.n_fail2),int(self.n_fail1),int(self.n_fail3))
                    if Graph.NoEpochsInTitle == False:
                        self.Title = Titlebuffer + ' ({0:d} epochs)'.format(self.n_total)
                    else:
                        self.Title = Titlebuffer
                else:
                    Titlebuffer=self.Title.format(int(self.n_total),int(self.n_nofail),int(self.n_fail),int(self.n_avail),int(self.n_alarm),int(self.n_fail2),int(self.n_fail1),int(self.n_fail3))
                    if Graph.NoEpochsInTitle == False:
                        self.Title = Titlebuffer + ' ({0:d} epochs)'.format(self.n_total)
                    else:
                        self.Title = Titlebuffer
            except:
                Errmsg=str(sys.exc_info()[1])
                print ("ERROR: Stanford title '{0:s}' contains the following invalid format: '{1:s}'").format(self.Title,Errmsg.replace("u'","").replace("'",""))
                removeLockFile()
                sys.exit()
                
            for i in range(NumNewlinesEnd):
                self.Title = self.Title +'\n'
            self.ax.set_title(self.Title)
        else:
            try:
                Titlebuffer=self.Title.format(int(self.n_total),int(self.n_nofail),int(self.n_fail),int(self.n_avail),int(self.n_alarm),int(self.n_fail2),int(self.n_fail1),int(self.n_fail3))
                if Graph.NoEpochsInTitle == False:
                    self.ax.set_title(Titlebuffer + ' ({0:d} epochs)'.format(self.n_total) )
                else:
                    self.ax.set_title(Titlebuffer)
            except:
                Errmsg=str(sys.exc_info()[1])
                print ("ERROR: Stanford title '{0:s}' contains the following invalid format: '{1:s}'").format(self.Title,Errmsg.replace("u'","").replace("'",""))
                removeLockFile()
                sys.exit()

        if Graph.WaterMark != "":
            if Graph.WaterMarkPositionSetbyUser == 1:
                #self.ax.text(Graph.WaterMarkPositionX, Graph.WaterMarkPositionY, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                self.ax.annotate(Graph.WaterMark,xy=(Graph.WaterMarkPositionX, Graph.WaterMarkPositionY),style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour, xycoords='axes fraction')
            else:
                self.ax.text(17*self.Xmax/20, self.Ymax/40, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
        if Graph.NumTextMark > 0:
            for i in range(Graph.NumTextMark):
                self.ax.annotate(Graph.TextMark[i], xy=(Graph.TextMarkPositionX[i],Graph.TextMarkPositionY[i]), xycoords='axes fraction', clip_on=False, fontsize=Graph.TextMarkSize[i], color=Graph.TextMarkColour[i])

        if self.grid:                 
            plt.grid(True)
        if self.SaveFigure:
            try:
                plt.savefig(self.SaveFigurePath)
            except:
                print ("ERROR: {0:s}".format(sys.exc_info()[1]))
        else:
            plt.show()
        
###########################################################################
# This part makes the Stanford-ESA Plot
###########################################################################
class stanfordESA:
    def __init__(self):
        self.zMax = 0
        self.f = ""
        self.myPointPatch = []
        self.myPointColors = []
        self.Xmin = 0.0
        self.Xmax = 60.0
        self.Ymin = 0.0
        self.Ymax = 60.0
        self.resolution_x = 0.1
        self.resolution_y = 0.1
        self.Xlabel = "" 
        self.Ylabel = ""
        self.Title = 'Stanford-ESA Plot' 
        self.grid = True
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'
        self.maxpoints=500000
        self.fColor=['r','pink','m','y']
    def readData(self):
        try:
            if PythonVersion == 2: 
                f = open(self.f,'rb')
            else:
                f = open(self.f,'r',errors='replace')
        except:
            Errmsg=str(sys.exc_info()[1]).split(":")
            Errmsg=Errmsg[0].split("] ")
            print ("ERROR Opening file '{0:s}': '{1:s}'".format(self.f,Errmsg[1]))
            removeLockFile()
            sys.exit()
        self.x = []
        self.y = []
        self.verticalNo = []
        self.horizontalNo = []
        i = 0
        for line in f:
            var=line.split()
            i = i + 1
            if var != []: 
                match_result = re.match(r'^#',var[0])
                if match_result == None:
                    if i == 2:
                        if len(var)<4:
                            print ("ERROR: Second line of header must have at least 4 columns in Stanford-ESA data file '{0:s}'".format(self.f))
                            removeLockFile()
                            sys.exit()
                        try:
                            self.resolution_x = float(var[0])
                            self.resolution_y = float(var[1])
                            self.Xmax = float(var[2])
                            self.Ymax = float(var[3])
                            number_pixel=(self.Xmax*self.Ymax)/(self.resolution_x*self.resolution_y)
                            #if number_pixel> self.maxpoints:
                            #    print ("ERROR: Number of pixels in plot ({0:d}) is over limit ({1:d}).\nReduce the pixel resolution, or reduce x&y range or increase the maximum number of pixels.".format(number_pixel, self.maxpoints))
                            #    print ("To increase the maximum number of pixels, use the parameter '--maxpoints <value>'.\nWarning: If maximum number of pixels is too large, the system may run out of memory.")
                            #    removeLockFile()
                            #    sys.exit()
                        except:
                            ErrMsg=str(sys.exc_info()[1]).split()
                            print ("ERROR: Invalid value '{0:s}' in header of Stanford-ESA data file '{1:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),self.f))
                            removeLockFile()
                            sys.exit()
                    elif i>3:
                        if len(var)<4:
                            print ("ERROR: Line number {0:d} must have at least 4 columns in Stanford-ESA data file '{1:s}'".format(i,self.f))
                            removeLockFile()
                            sys.exit()
                        try:
                            self.x.append(float(var[0]))
                            self.y.append(float(var[1]))
                            self.horizontalNo.append(float(var[2]))
                            self.verticalNo.append(float(var[3]))
                        except:
                            ErrMsg=str(sys.exc_info()[1]).split()
                            print ("ERROR: Invalid value '{0:s}' in line number {1:d} of Stanford-ESA data file '{2:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),i,self.f))
                            removeLockFile()
                            sys.exit()
        f.close()
        if i<4:
            print ("ERROR: Stanford-ESA file '{0:s}' has no data".format(self.f))
            removeLockFile()
            sys.exit()

        return self
        
    
    def getPoints(self,ax,x,y,z):
        self.n_total = sum(z)
        self.n_fail = 0
        self.n_avail = 0
        self.n_alarm = 0
        self.n_fail1 = 0
        self.n_fail2 = 0
        self.n_fail3 = 0
        x = np.array(x)
        y = np.array(y)
        z = np.array(z)
        idx_nonzero = np.nonzero(z)
        x=x[idx_nonzero]
        y=y[idx_nonzero]
        z=z[idx_nonzero]

        if len(z)==0 or np.max(z)==1:
            self.zMax = 1
        else:
            self.zMax = math.ceil(math.log10(np.max(z)))

        mypatch = []
        mycolors = []
        for x1,y1 in zip(x, y):
            rectangle = Rectangle((x1,y1), self.resolution_x, self.resolution_y, linewidth=0)
            mypatch.append(rectangle)
        for number in z:
            c_idx = math.ceil(255*math.log10(number)/self.zMax)
            mycolors.append(c_idx)

        self.myPointPatch = mypatch
        self.myPointColors = np.array(mycolors)
        i_fails = np.where(x>=y)[0]
        for idx in i_fails:
            self.n_fail = self.n_fail + z[idx] 
            if self.x[idx] < self.AL:
                self.n_fail2 = self.n_fail2 + z[idx]
            elif self.y[idx] >= self.AL:
                self.n_fail3 = self.n_fail3 + z[idx]
            else:
                self.n_fail1 = self.n_fail1 + z[idx]

        self.n_nofail = self.n_total - self.n_fail
        
        i_alarm = np.where(np.logical_and(np.less(x,y),np.greater_equal(y,self.AL)))[0]
        for idx in i_alarm:
            self.n_alarm = self.n_alarm + z[idx] 
        self.n_avail = self.n_total - self.n_alarm - self.n_fail1 - self.n_fail2 - self.n_fail3 


        if Graph.StfdPercentileX or Graph.StfdPercentileY:
            text_style1 = dict(horizontalalignment='right', verticalalignment='top',
                      fontsize=12, fontdict={'family': 'monospace'})
            text_style2 = dict(horizontalalignment='center', verticalalignment='center',
                      fontsize=12, fontdict={'family': 'monospace'}, rotation=90)
            if Graph.StfdPercentileListX != []:
                percentPointX = Graph.StfdPercentileListX
            else:
                percentPointX = Graph.StfdPercentileDefaultX

            numPointsX = len(percentPointX)
            lenPE = int(self.n_total)
            SamplesPercentX = []
            for i in range(numPointsX):
                SamplesPercentX.append(percentPointX[i]*lenPE)

            if Graph.StfdPercentileListY != []:
                percentPointY = Graph.StfdPercentileListY
            else:
                percentPointY = Graph.StfdPercentileDefaultY

            numPointsY = len(percentPointY)
            lenPL = int(self.n_total)
            SamplesPercentY = []
            for i in range(numPointsY):
                SamplesPercentY.append(percentPointY[i]*lenPL)

            PointList=zip(x, y, z)
            if Graph.StfdPercentileX:
                sortPoints=sorted(PointList, key=lambda k: [k[0], k[1]])
                Sum=numPercentComputed=0
                self.xPoint = []
                XMaxList = []
                for xpos,ypos,zval in sortPoints:
                    Sum+=zval
                    if Sum>=SamplesPercentX[numPercentComputed]:
                        if xpos>=self.Xmax:
                            self.xPoint.append(self.Xmax)
                        else:
                            self.xPoint.append(xpos)
                        XMaxList.append(self.Ymax)
                        numPercentComputed+=1
                        if numPercentComputed==numPointsX:
                            break

            if Graph.StfdPercentileY:
                sortPoints=sorted(PointList, key=lambda k: [k[1], k[0]])
                Sum=numPercentComputed=0
                self.yPoint = []
                YMaxList = []
                for xpos,ypos,zval in sortPoints:
                    Sum+=zval
                    if Sum>=SamplesPercentY[numPercentComputed]:
                        if ypos>=self.Ymax:
                            self.yPoint.append(self.Ymax)
                        else:
                            self.yPoint.append(ypos)
                        YMaxList.append(self.Xmax)
                        numPercentComputed+=1
                        if numPercentComputed==numPointsY:
                            break

            if Graph.StfdPercentileX:
                ax.plot(self.xPoint,XMaxList,'v',markersize=10)
                for per, xp in zip(percentPointX,self.xPoint):
                    ax.text(xp+.07,(0.9*self.Ymax+0.1*self.Ymin),'{0:.1f}%'.format(100.*per),**text_style2)     

            if Graph.StfdPercentileY:
                ax.plot(YMaxList,self.yPoint,'<',markersize=10)
                for per, yp in zip(percentPointY,self.yPoint):
                    ax.text((0.97*self.Xmax+0.03*self.Xmin),yp,'{0:.1f}%'.format(100.*per),**text_style1) 

        return self
       
    def plotPoints(self, ax):     
        p = PatchCollection(self.myPointPatch, cmap=plt.get_cmap(self.cm), linewidth=0)       
        p.set_array(self.myPointColors)
        ax.add_collection(p)
        m = self.zMax + 1
        cbarTicks = np.linspace(0, 255, m)
        cbarLabel = np.linspace(0, m-1, m)
        if Graph.StfdPercentileY:
            pCbar = plt.colorbar(mappable=p, ticks=cbarTicks,pad=0.1)
        else:
            pCbar = plt.colorbar(mappable=p, ticks=cbarTicks)
        pCbar.ax.set_yticklabels(cbarLabel) 
        pCbar.ax.set_ylabel('Number of Points per Pixel (logarithmic)')
        x = [self.Xmin, self.Xmax]
        y = x
        plt.plot(x,y,'black')
        if Graph.WaterMark != "":
            if Graph.WaterMarkPositionSetbyUser == 1:
                ax.annotate(Graph.WaterMark,xy=(Graph.WaterMarkPositionX, Graph.WaterMarkPositionY),style='italic',fontsize=Graph.WaterMarkSize,color=Graph.WaterMarkColour,xycoords='axes fraction')
            else:
                ax.text(17*self.Xmax/20, self.Ymax/40, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
        if Graph.NumTextMark > 0:
            for i in range(Graph.NumTextMark):
                ax.annotate(Graph.TextMark[i], xy=(Graph.TextMarkPositionX[i],Graph.TextMarkPositionY[i]), xycoords='axes fraction', clip_on=False, fontsize=Graph.TextMarkSize[i], color=Graph.TextMarkColour[i])
        if Graph.sfESAwithRegions:
            if Graph.AvailEpochPosX != 999.:
                ax.text(Graph.AvailEpochPosX,Graph.AvailEpochPosY, 'Normal Operation \n{1:s}: {0:.0f}\n{2:.3f}%'.format(self.n_avail,Graph.textGeometriesShort,100.*self.n_avail/float(self.n_total),Graph.textGeometriesShort), style='italic',transform=ax.transAxes)
            else:
                ax.text(self.AL/5, 6*self.AL/7, 'Normal Operation \n{1:s}: {0:.0f}'.format(self.n_avail,Graph.textGeometriesShort), style='italic')
                ax.text(self.AL/5, 5.5*self.AL/7, '{0:.3f}%'.format(100.*self.n_avail/float(self.n_total),Graph.textGeometriesShort), style='italic')

            fail1=Rectangle((self.AL, self.Ymin), (self.Xmax - self.AL), self.AL, lw=1, facecolor=self.fColor[0], alpha=0.2 )
            ax.add_patch(fail1)
            if Graph.HMIAvailEpochPosX != 999.:
                ax.text(Graph.HMIAvailEpochPosX,Graph.HMIAvailEpochPosY, 'HMI \n{1:s}: {0:.0f}'.format(self.n_fail1,Graph.textGeometriesShort) , style='italic',transform=ax.transAxes)
            elif self.AL<=45:
                ax.text(8*self.AL/7, 1*self.AL/7, 'HMI \n{1:s}: {0:.0f}'.format(self.n_fail1,Graph.textGeometriesShort) , style='italic')
            else:
                ax.text(7*self.AL/7, 1*self.AL/7, 'HMI \n{1:s}: {0:.0f}'.format(self.n_fail1,Graph.textGeometriesShort) , style='italic')

            vert2 = [(self.Xmin, self.Ymin), (self.AL, self.AL),(self.AL, self.Ymin), (self.Xmin,self.Ymin),]
            code2 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
            path2 = Path(vert2, code2)
            fail2=PathPatch(path2, facecolor=self.fColor[1], lw=1, alpha=0.2)
            ax.add_patch(fail2)
            if Graph.MIAvailEpochPosX != 999.:
                ax.text(Graph.MIAvailEpochPosX, Graph.MIAvailEpochPosY, 'MI \n{1:s}: {0:.0f}'.format(self.n_fail2,Graph.textGeometriesShort) , style='italic',transform=ax.transAxes)
            else:
                ax.text(2*self.AL/5, 1*self.AL/7, 'MI \n{1:s}: {0:.0f}'.format(self.n_fail2,Graph.textGeometriesShort) , style='italic')

            vert3 = [(self.AL, self.AL), (self.Xmax, self.Ymax), (self.Xmax, self.AL), (self.AL, self.AL),]
            code3 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
            path3 = Path(vert3, code3)
            fail3=PathPatch(path3, facecolor=self.fColor[2], lw=1, alpha=0.2)
            ax.add_patch(fail3)
            MItext="MI"
            if Graph.MIUnAvailEpochPosX != 999.:
                ax.text(Graph.MIUnAvailEpochPosX, Graph.MIUnAvailEpochPosY, '{0:>6s} \n{2:s}: {1:.0f}'.format(MItext,self.n_fail3,Graph.textGeometriesShort) , style='italic',transform=ax.transAxes)
            elif self.AL<=45:
                ax.text(8*self.AL/7, 17*self.AL/16, '{0:>6s} \n{2:s}: {1:.0f}'.format(MItext,self.n_fail3,Graph.textGeometriesShort) , style='italic')
            else:
                ax.text(7*self.AL/7, 16.2*self.AL/16, '{0:8s} \n{2:s}: {1:.0f}'.format(MItext,self.n_fail3,Graph.textGeometriesShort) , style='italic')

            vert1 = [(self.Xmin, self.AL), (self.Xmin, self.Ymax), (self.Xmax, self.Ymax), (self.AL, self.AL), (self.Xmin, self.AL),]
            code1 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
            path1 = Path(vert1, code1)
            alarm=PathPatch(path1, facecolor=self.fColor[3], lw=1, alpha=0.2)
            ax.add_patch(alarm)
            if Graph.UnAvailEpochPosX != 999.:
                ax.text(Graph.UnAvailEpochPosX,Graph.UnAvailEpochPosY, 'System Unavailable \nAlarm {1:s}: {0:.0f}'.format(self.n_alarm,Graph.textGeometriesShort) , style='italic',transform=ax.transAxes)
            elif self.AL<=20:
                ax.text(3*self.AL/5, 12*self.AL/7, 'System Unavailable \nAlarm {1:s}: {0:.0f}'.format(self.n_alarm,Graph.textGeometriesShort) , style='italic')
            elif self.AL<=45:
                ax.text(2*self.AL/5, 8*self.AL/7, 'System Unavailable \nAlarm {1:s}: {0:.0f}'.format(self.n_alarm,Graph.textGeometriesShort) , style='italic')
            else:
                ax.text(2*self.AL/5, 7.5*self.AL/7, 'System Unavailable \nAlarm {1:s}: {0:.0f}'.format(self.n_alarm,Graph.textGeometriesShort) , style='italic')


        plt.axis([self.Xmin, self.Xmax, self.Ymin, self.Ymax])
        #There is a bug in Python 2 and 3 that makes only showing one axe ticks when ticks are set in right or top sides (twinx() or twiny() functions)
        #To get around it, the extra ticks for sigma will be made with horizontal and vertical lines and text annotations for the labels
        if Graph.StfdPercentileY:
            #To set the labels in the correct position, we use the function matplotlib.transforms.blended_transform_factory to get the coordinate
            #system in the bottom right corner. Coordinates are from(0,0) to (1,1). The (self.ax.transAxes,self.ax.transData) means that the first
            #item is a coordinate in normalized X (0,1), and the second is a coordinate according to data max and min values
            trans = matplotlib.transforms.blended_transform_factory(ax.transAxes,ax.transData)
            for elem in self.yPoint:
                plt.axhline(elem, linestyle='dotted',color='black',linewidth=.9)
                #ax.annotate(elem, xy=(1.01, elem), xycoords=trans, clip_on=False, va='center') #Previous command. For unknown reasons, sometimes made python crash
                ax.text(1.01,elem,"{0:.2f}".format(elem),transform=trans, clip_on=False, va='center')
        if Graph.StfdPercentileX:
            #The transform is the same as before,but now X is data and Y is normalized
            #The annotation in Y axis does not get perfect, we have to hardcode some correction 
            trans = matplotlib.transforms.blended_transform_factory(ax.transData,ax.transAxes)
            if PythonVersionDecimal>=2.7:
                xBias=.05
                UpPos=1.06
            else:
                xBias=.07
                UpPos=1.01
            for elem in self.xPoint:
                plt.axvline(elem, linestyle='dotted',color='black',linewidth=.9)
                #ax.annotate(elem-.07,1.07,elem, xycoords=trans, clip_on=False,rotation=90) #Previous command. For unknown reasons, sometimes made python crash
                ax.text(elem-xBias,UpPos,"{0:.2f}".format(elem),transform=trans,clip_on=False,rotation=90)

        #Set user defined ticks if user has set any
        if Graph.XTicsUser == True:
            ax.set_xticks(np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            ax.set_xticks(np.linspace(self.Xmin,self.Xmax,abs(int((self.Xmax-self.Xmin)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            ax.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            ax.set_yticks(np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            ax.set_yticks(np.linspace(self.Ymin,self.Ymax,abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            ax.set_yticks(Graph.YTicksList)

        ax.set_xlabel(self.Xlabel)
        ax.set_ylabel(self.Ylabel)
        try:
            Titlebuffer=self.Title.format(int(self.n_total),int(self.n_nofail),int(self.n_fail),int(self.n_avail),int(self.n_alarm),int(self.n_fail2),int(self.n_fail1),int(self.n_fail3))
            if Graph.NoEpochsInTitle == False:
                ax.set_title(Titlebuffer + ' ({0:.0f} {1:s})'.format(self.n_total,Graph.textGeometriesLarge) )
            else:
                ax.set_title(Titlebuffer)
        except:
           Errmsg=str(sys.exc_info()[1])
           print ("ERROR: Stanford-ESA title '{0:s}' contains the following invalid format: '{1:s}'").format(self.Title,Errmsg.replace("u'","").replace("'",""))
           removeLockFile()
           sys.exit()

        if self.grid:                 
            plt.grid(True)
        return 
    

##########################################################################
# This part makes the worst integrity ratio plot
##########################################################################
class WIRmap:
    def __init__(self):
        self.grid = True
        self.projection = 'cyl'
        self.Xmin = -180
        self.Xmax = 180
        self.Ymin = -90
        self.Ymax = 90
        self.continentColor = 'y'
        self.lakeColor = 'w'
        self.boundaryColor = 'w'
        self.f = ""
        self.myColorMap = 'jet'
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.Title = "Default title"
        self.Xlabel = "" 
        self.Ylabel = ""
        self.cbarMin = 0.0
        self.cbarMax = 2.0
        self.cbarMaxDef = 2.0
        self.cbarInterval = 8.0
        self.colName = ""
        self.colX = ""
        self.colY = ""
        self.colRatioV = ""
        self.colRatioH = ""
        self.colMIsV = ""
        self.colMIsH = ""
        self.ColLabelName = ""
        self.txt_show = False
        self.ms = 150
        self.NumStations = []
        self.StationNames = []
    def readData(self):
        try:
            if PythonVersion == 2: 
                f = open(self.f,'rb')
            else:
                f = open(self.f,'r',errors='replace')
        except:
            Errmsg=str(sys.exc_info()[1]).split(":")
            Errmsg=Errmsg[0].split("] ")
            print ("ERROR Opening file '{0:s}': '{1:s}'".format(self.f,Errmsg[1]))
            removeLockFile()
            sys.exit()
        self.StaName = []
        self.longitude = []
        self.latitude = []
        self.ratioV = []
        self.ratioH = []
        self.MIsV = []
        self.MIsH = []
        self.StaNetwork = []
        if Graph.StaNetAddNumStations == True and self.ColLabelName == "":
            self.StationNames.append(Graph.StaNetWorkDefName)
            self.NumStations.append(0)

        i = 0
        for line in f:
            i+=1
            var = line.split()
            if var != []: 
                match_result = re.match(r'^#',var[0])
                if match_result == None:
                    j = 0
                    for ele in var:
                        try:
                            auxEle = float(ele)
                            var[j] = auxEle
                            j += 1
                        except:
                            j += 1
                    try:
                        self.longitude.append(float(eval(self.colX)))
                        self.latitude.append(float(eval(self.colY)))
                        if self.colRatioV != "": self.ratioV.append(float(eval(self.colRatioV)))
                        if self.colRatioH != "": self.ratioH.append(float(eval(self.colRatioH)))
                        if self.colMIsV != "": self.MIsV.append(float(eval(self.colMIsV)))
                        if self.colMIsH != "": self.MIsH.append(float(eval(self.colMIsH)))
                        if PythonVersion == 2:
                            if self.colName != "": self.StaName.append(unicode(str(eval(self.colName)), "utf-8", errors="ignore"))
                            if self.ColLabelName != "": 
                                staNetworkName = unicode(str(eval(self.ColLabelName)), "utf-8", errors="ignore")
                                self.StaNetwork.append(staNetworkName)
                        else:
                            if self.colName != "": self.StaName.append(str(eval(self.colName)))
                            if self.ColLabelName != "": 
                                staNetworkName = str(eval(self.ColLabelName))
                                self.StaNetwork.append(staNetworkName)
                    except:
                        ErrMsg=str(sys.exc_info()[1]).split()
                        if "is not defined" in str(sys.exc_info()[1]):
                            print ("ERROR: User defined column '{0:s}' is not a valid column".format(ErrMsg[1].replace("'","")))
                        elif "list index out of range" in str(sys.exc_info()[1]):
                            print ("ERROR: One of the column number provided does not exist in line number {0:d} of worst integrity ratio data file '{1:s}'".format(i,self.f))
                        else:
                            print ("ERROR: Invalid value '{0:s}' in line number {1:d} of worst integrity ratio data file '{2:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),i,self.f))
                        removeLockFile()
                        sys.exit()

                    if Graph.StaNetAddNumStations == True:
                        #Count the number of stations for each network
                        if self.ColLabelName == "":
                            #For the case no column for station network provided, count the total number of station read
                            self.NumStations[0]+=1
                        else:
                            try:
                                pos=self.StationNames.index(staNetworkName)
                                self.NumStations[pos]+=1
                            except:
                                self.StationNames.append(staNetworkName)
                                self.NumStations.append(1)

        f.close()
        if i<1:
            print ("ERROR: File '{0:s}' has no data".format(self.f))
            removeLockFile()
            sys.exit()
        
        self.ratios = [self.ratioV,self.ratioH]
        self.mis = [self.MIsV,self.MIsH]
        return self
    def drawMap(self):
        idx_sv = 0
        if self.cbarMax != "":
            self.cbarMaxDef = "User"
        for i in range(2):
            ratio = self.ratios[i]
            MIs = self.mis[i]
            if ratio != []:
                fig = plt.figure() 
                if (Graph.cbarAutoMax == True):
                    self.cbarMax = int(max(ratio)) + 1
                ax1 = fig.add_axes([0.1,0.2,0.8,0.7])
                if self.Title == "Default title":
                    if MIs != []:
                        title = "Worst Integrity Ratio" + ' / Number of MIs'
                    else:
                        title = "Worst Integrity Ratio"
                else:
                    title = self.Title
                if (i == 0 and self.ratios[0] != [] and self.ratios[1] != []): title = 'Vertical ' + title
                elif (i == 1 and self.ratios[0] != [] and self.ratios[1] != []): title = 'Horizontal ' + title
                ax1.set_title(title) 
                if Graph.WaterMark != "":
                    if Graph.WaterMarkPositionSetbyUser == 1:
                        plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                    else:
                        plt.annotate(Graph.WaterMark, xy=(.87,.03), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                if Graph.NumTextMark > 0:
                    for j in range(Graph.NumTextMark):
                        plt.annotate(Graph.TextMark[j], xy=(Graph.TextMarkPositionX[j],Graph.TextMarkPositionY[j]), xycoords='axes fraction', fontsize=Graph.TextMarkSize[j], color=Graph.TextMarkColour[j])
                if self.projection == 'cyl':
                    baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,\
                            llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution=Graph.MapResolution,fix_aspect=True)
                    if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                        parallel = np.arange(self.Ymin,self.Ymax+1.,5.)
                        meridian = np.arange(self.Xmin,self.Xmax+1.,5.)  
                    else:
                        parallel = np.arange(self.Ymin,self.Ymax+1.,20.)
                        meridian = np.arange(self.Xmin,self.Xmax+1.,40.)  

                elif self.projection == 'lcc':
                    baseM = Basemap(width=12000000,height=9000000,projection='lcc',\
                                resolution=Graph.MapResolution,lat_1=45.,lat_0=50,lon_0=10.)
                    self.Title = "Lambert Conformal Projection"
                    parallel = np.arange(0.,81.,10.)
                    meridian = np.arange(10,351.,20.)  

                #Add European FIR
                if Graph.FIREurope:
                    if Graph.FIRUserSelLineColorEur == False:
                        #Set default color of FIRLineColor to black instead of white
                        Graph.FIRLineColorEur = 'k'
                    lonfir,latfir=baseM(Graph.lonFIREur,Graph.latFIREur)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleEur, markersize=Graph.FIRMarkerSizeEur, linewidth=Graph.FIRLineWidthEur,color=Graph.FIRLineColorEur) 
                #Add CONUS FIR
                if Graph.FIRCONUS:
                    if Graph.FIRUserSelLineColorCONUS == False:
                        #Set default color of FIRLineColor to black instead of white
                        Graph.FIRLineColorCONUS = 'k'
                    lonfir,latfir=baseM(Graph.lonFIRCONUS,Graph.latFIRCONUS)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleCONUS, markersize=Graph.FIRMarkerSizeCONUS, linewidth=Graph.FIRLineWidthCONUS,color=Graph.FIRLineColorCONUS) 
                #Add Alaska FIR
                if Graph.FIRAlaska:
                    if Graph.FIRUserSelLineColorAlaska == False:
                        #Set default color of FIRLineColor to black instead of white
                        Graph.FIRLineColorAlaska = 'k'
                    lonfir,latfir=baseM(Graph.lonFIRAlaska,Graph.latFIRAlaska)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleAlaska, markersize=Graph.FIRMarkerSizeAlaska, linewidth=Graph.FIRLineWidthAlaska,color=Graph.FIRLineColorAlaska) 
                #Add Canada FIR
                if Graph.FIRCanada:
                    if Graph.FIRUserSelLineColorCanada == False:
                        #Set default color of FIRLineColor to black instead of white
                        Graph.FIRLineColorCanada = 'k'
                    lonfir,latfir=baseM(Graph.lonFIRCanada,Graph.latFIRCanada)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleCanada, markersize=Graph.FIRMarkerSizeCanada, linewidth=Graph.FIRLineWidthCanada,color=Graph.FIRLineColorCanada) 
                #Add Mexico FIR
                if Graph.FIRMexico:
                    if Graph.FIRUserSelLineColorMexico == False:
                        #Set default color of FIRLineColor to black instead of white
                        Graph.FIRLineColorMexico = 'k'
                    lonfir,latfir=baseM(Graph.lonFIRMexico,Graph.latFIRMexico)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleMexico, markersize=Graph.FIRMarkerSizeMexico, linewidth=Graph.FIRLineWidthMexico,color=Graph.FIRLineColorMexico) 
                #Add User Defined FIRs
                if Graph.FIRNumUserFile >0:
                    for i in range(Graph.FIRNumUserFile):
                        if i>(Graph.FIRNumLineColor-1):
                            #No Line color provided for current FIR, set default to black color
                            Graph.FIRLineColor[i] = 'k'
                        lonfir,latfir=baseM(Graph.lonFIR[i],Graph.latFIR[i])
                        baseM.plot(lonfir,latfir,Graph.FIRLineStyle[i], markersize=Graph.FIRMarkerSize[i], linewidth=Graph.FIRLineWidth[i],color=Graph.FIRLineColor[i]) 
                

                if (Graph.XTicsStepUser == True):
                    meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
                elif Graph.XTicsUser == True:
                    meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
                elif Graph.XTicsListUser == True:
                    meridian = Graph.XTicksList

                if (Graph.YTicsStepUser == True):
                    parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
                elif Graph.YTicsUser == True:
                    parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
                elif Graph.YTicsListUser == True:
                    parallel = Graph.YTicksList

                baseM.drawcoastlines()
                if Graph.Countries:
                    baseM.drawcountries()
                if Graph.USAStates:
                    baseM.drawstates()
                baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
                if self.grid:
                    w_line = 1.0
                else: 
                    w_line = 0.0
                baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
                baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
                baseM.drawmapboundary(fill_color=self.boundaryColor)
                if MIs != []:
                    w_border = 3.0
                    c_border = []
                    for j in range(len(MIs)):
                        if MIs[j] == 0: c_border.append('white')
                        if MIs[j] == 1: c_border.append('silver')
                        if MIs[j] >= 2: c_border.append('black')
                else:
                    w_border = 0 
                    c_border = 'none'
                if Graph.worstIntegrityRatioColorbar == True:
                    self.cbarMax = 2.0
                    self.cbarMin = 0.0
                    self.cbarInterval = 8
                bin_size = (self.cbarMax-self.cbarMin)/self.cbarInterval
                c_ratio = np.array(ratio)/bin_size
                c_ratio = c_ratio.astype(int)*bin_size
                bounds = np.linspace(self.cbarMin, self.cbarMax, self.cbarInterval+1)
                xpt,ypt = baseM(self.longitude,self.latitude)
                if Graph.worstIntegrityRatioColorbar == True:
                    #cm = matplotlib.colors.ListedColormap(['#0080FF', '#40E0FF', '#00FF00', '#FFFF00', '#FF0000', '#FF00C8','#FF64FF','#FFA0FF'])
                    cm = matplotlib.colors.ListedColormap(['#0080FF', '#40E0FF', '#00FF00', '#FFFF00', '#FF0000', '#B22222','#B30000','#800000']) 
                    norm_border = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=cm.N)
                    self.cs = baseM.scatter(xpt,ypt,c=c_ratio,norm=norm_border,s=self.ms,edgecolor =c_border,linewidth=w_border,cmap=cm)
                else:
                    norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=256)
                    self.cs = baseM.scatter(xpt,ypt,c=c_ratio,norm=norm,s=self.ms,edgecolor =c_border,linewidth=w_border,cmap=self.myColorMap)
                if self.txt_show == True:
                    for j in range(len(ratio)):
                        txt_ratio = str(round(ratio[j],1))
                        ax1.annotate(txt_ratio, (xpt[j], ypt[j]),ha='center', va='center', fontsize=7, color='w')

                #cbar1 = baseM.colorbar(self.cs,location='bottom',pad="10%")
                if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                    cbaxes1 = fig.add_axes([0.18,0.08,0.64,0.04])
                else:
                    cbaxes1 = fig.add_axes([0.18,0.11,0.64,0.04])
                if Graph.worstIntegrityRatioColorbar == True:
                    cbar1 =  matplotlib.colorbar.ColorbarBase(cbaxes1,cmap=cm,norm=norm_border, boundaries=bounds,spacing='proportional', orientation='horizontal')
                else:
                    cbar1 = plt.colorbar(self.cs,cax=cbaxes1,orientation='horizontal')
                cbar1.ax.xaxis.set_ticks_position('top')
                if w_border != 0:
                    if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                        cbaxes2 = fig.add_axes([0.18,0.04,0.64,0.04])
                    else:
                        cbaxes2 = fig.add_axes([0.18,0.07,0.64,0.04])
                    cmap_border = matplotlib.colors.ListedColormap(['white', 'silver', 'black'])
                    bounds_border = [1,2,3,4]
                    norm_border = matplotlib.colors.BoundaryNorm(boundaries=bounds_border, ncolors=cmap_border.N)
                    cbar2 = matplotlib.colorbar.ColorbarBase(cbaxes2, cmap=cmap_border, norm=norm_border, boundaries=bounds_border,spacing='proportional', orientation='horizontal')
                    cbar2.ax.set_xticklabels(['0','1','2','>2'])
                    #cbar2.set_label('Number of')
                    #cbar2.ax.set_ytickposition('right')
                    #if (idx_sv ==0):
                    #    cbar2.set_label('Number of vertical MIs')
                    #elif (idx_sv ==1):
                    #    cbar2.set_label('Number of horizontal MIs')

                if (self.Xlabel!= ""):
                    ax1.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
                if (self.Ylabel!= ""):
                    ax1.set_ylabel(self.Ylabel)
                    ax1.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks

                if (self.SaveFigure == True): 
                    try:
                        if(len(self.SaveFigurePath)>=idx_sv+1):
                            plt.savefig(self.SaveFigurePath[idx_sv])
                    except:
                        Errmsg=str(sys.exc_info()[1]).split('"')
                        if "rgba" in str(sys.exc_info()[1]):
                            print ("ERROR: User defined colour '{0:s}' is not a valid colour".format(Errmsg[1]))
                        else:
                            print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                        removeLockFile()
                        sys.exit()
                idx_sv = idx_sv + 1

        if self.StaName != []:
            #Plot with the station names and markers
            if Graph.StaNetWorkWithMarkers == False and Graph.StaNetWorkWithNames == False:
                #If no option is set, set by default the map with station names only
                Graph.StaNetWorkWithNames = True
            if Graph.NumPointsLabelUser == False:
                if Graph.NumPointsLabel != None:
                    Graph.NumPointsLabel = 1

            try:
                fig, ax1 = plt.subplots()
            except:
                #This is for python <=2.6, where the previous statement may fail
                fig = plt.figure()
                ax1 = fig.add_subplot(111)
            if Graph.AdjustToMargin == True:
                fig.tight_layout() #This is to adjust plot to margins
            if self.Title == "Default title":
                title = "Station Map Distribution"
            else:
                if Graph.AdjustToMargin == True:
                    #Add margin on top to fit title with multiple lines (if necessary)
                    NumNewlines=self.Title.count('\n')
                    if NumNewlines == 1:
                        plt.subplots_adjust(top=.9)
                    elif NumNewlines == 2:
                        plt.subplots_adjust(top=.87)
                    elif NumNewlines > 2:
                        plt.subplots_adjust(top=.83)
                title = self.Title
            ax1.set_title(title) 
            if (self.Xlabel!= ""):
                ax1.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
            if (self.Ylabel!= ""):
                ax1.set_ylabel(self.Ylabel)
                ax1.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks

            if Graph.WaterMark != "":
                if Graph.WaterMarkPositionSetbyUser == 1:
                    plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    plt.annotate(Graph.WaterMark, xy=(.87,.03), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            if Graph.NumTextMark > 0:
                for j in range(Graph.NumTextMark):
                    plt.annotate(Graph.TextMark[j], xy=(Graph.TextMarkPositionX[j],Graph.TextMarkPositionY[j]), xycoords='axes fraction', fontsize=Graph.TextMarkSize[j], color=Graph.TextMarkColour[j])
            if self.projection == 'cyl':
                baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,\
                        llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution=Graph.MapResolution,fix_aspect=True)
                if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                    parallel = np.arange(self.Ymin,self.Ymax+1.,5.)
                    meridian = np.arange(self.Xmin,self.Xmax+1.,5.)  
                else:
                    parallel = np.arange(self.Ymin,self.Ymax+1.,20.)
                    meridian = np.arange(self.Xmin,self.Xmax+1.,40.)  
            elif self.projection == 'lcc':
                baseM = Basemap(width=12000000,height=9000000,projection='lcc',\
                            resolution=Graph.MapResolution,lat_1=45.,lat_0=50,lon_0=10.)
                self.Title = "Lambert Conformal Projection"
                parallel = np.arange(0.,81.,10.)
                meridian = np.arange(10,351.,20.)  

            #Add FIR
            if Graph.FIREurope:
                if Graph.FIRUserSelLineColorEur == False:
                    #Set default color of FIRLineColor to black instead of white
                    Graph.FIRLineColorEur = 'k'
                lonfir,latfir=baseM(Graph.lonFIREur,Graph.latFIREur)
                baseM.plot(lonfir,latfir,Graph.FIRLineStyleEur, markersize=Graph.FIRMarkerSizeEur, linewidth=Graph.FIRLineWidthEur,color=Graph.FIRLineColorEur) 
            #Add CONUS FIR
            if Graph.FIRCONUS:
                if Graph.FIRUserSelLineColorCONUS == False:
                    #Set default color of FIRLineColor to black instead of white
                    Graph.FIRLineColorCONUS = 'k'
                lonfir,latfir=baseM(Graph.lonFIRCONUS,Graph.latFIRCONUS)
                baseM.plot(lonfir,latfir,Graph.FIRLineStyleCONUS, markersize=Graph.FIRMarkerSizeCONUS, linewidth=Graph.FIRLineWidthCONUS,color=Graph.FIRLineColorCONUS) 
            #Add Alaska FIR
            if Graph.FIRAlaska:
                if Graph.FIRUserSelLineColorAlaska == False:
                    #Set default color of FIRLineColor to black instead of white
                    Graph.FIRLineColorAlaska = 'k'
                lonfir,latfir=baseM(Graph.lonFIRAlaska,Graph.latFIRAlaska)
                baseM.plot(lonfir,latfir,Graph.FIRLineStyleAlaska, markersize=Graph.FIRMarkerSizeAlaska, linewidth=Graph.FIRLineWidthAlaska,color=Graph.FIRLineColorAlaska) 
            #Add Canada FIR
            if Graph.FIRCanada:
                if Graph.FIRUserSelLineColorCanada == False:
                    #Set default color of FIRLineColor to black instead of white
                    Graph.FIRLineColorCanada = 'k'
                lonfir,latfir=baseM(Graph.lonFIRCanada,Graph.latFIRCanada)
                baseM.plot(lonfir,latfir,Graph.FIRLineStyleCanada, markersize=Graph.FIRMarkerSizeCanada, linewidth=Graph.FIRLineWidthCanada,color=Graph.FIRLineColorCanada) 
            #Add Mexico FIR
            if Graph.FIRMexico:
                if Graph.FIRUserSelLineColorMexico == False:
                    #Set default color of FIRLineColor to black instead of white
                    Graph.FIRLineColorMexico = 'k'
                lonfir,latfir=baseM(Graph.lonFIRMexico,Graph.latFIRMexico)
                baseM.plot(lonfir,latfir,Graph.FIRLineStyleMexico, markersize=Graph.FIRMarkerSizeMexico, linewidth=Graph.FIRLineWidthMexico,color=Graph.FIRLineColorMexico) 
            if Graph.FIRNumUserFile >0:
                for i in range(Graph.FIRNumUserFile):
                    if i>(Graph.FIRNumLineColor-1):
                        #No Line color provided for current FIR, set default to black color
                        Graph.FIRLineColor[i] = 'k'
                    lonfir,latfir=baseM(Graph.lonFIR[i],Graph.latFIR[i])
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyle[i], markersize=Graph.FIRMarkerSize[i], linewidth=Graph.FIRLineWidth[i],color=Graph.FIRLineColor[i]) 

            if (Graph.XTicsStepUser == True):
                meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
            elif Graph.XTicsUser == True:
                meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
            elif Graph.XTicsListUser == True:
                meridian = Graph.XTicksList

            if (Graph.YTicsStepUser == True):
                parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
            elif Graph.YTicsUser == True:
                parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
            elif Graph.YTicsListUser == True:
                parallel = Graph.YTicksList

            baseM.drawcoastlines()
            if Graph.Countries:
                baseM.drawcountries()
            if Graph.USAStates:
                baseM.drawstates()
            baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
            xpt,ypt = baseM(self.longitude,self.latitude)
            if self.grid:
                w_line = 1.0
            else: 
                w_line = 0.0
            baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
            baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
            baseM.drawmapboundary(fill_color=self.boundaryColor)
            for j in range(len(self.StaName)):
                try:
                    pos=Graph.StaLabelListName.index(self.StaNetwork[j])
                    labelname=Graph.StaLabelListValue[pos]
                except:
                    try:
                        labelname=self.StaNetwork[j] #Default label is its own station network
                    except:
                        labelname=Graph.StaNetWorkDefName  #If no station network provided, use default name

                if Graph.StaNetAddNumStations == True:
                    try:
                        pos=self.StationNames.index(self.StaNetwork[j])
                        labelname = labelname + " (" + str(self.NumStations[pos]) + ")"
                    except:
                        labelname = labelname + " (" + str(self.NumStations[0]) + ")"

                try:
                    pos=Graph.StaMarkerTypeListName.index(self.StaNetwork[j])
                    markertype=Graph.StaMarkerTypeListValue[pos]
                except:
                    markertype=Graph.StaNetWorkDefMarkerType #Default marker type 
                try:
                    pos=Graph.StaMarkerColorListName.index(self.StaNetwork[j])
                    markercolor=Graph.StaMarkerColorListValue[pos]
                except:
                    markercolor=Graph.StaNetWorkDefMarkerColor #Default marker color 
                try:
                    pos=Graph.StaMarkerSizeListName.index(self.StaNetwork[j])
                    markersize=Graph.StaMarkerSizeListValue[pos]
                except:
                    markersize=Graph.StaNetWorkDefMarkerSize #Default marker size 

                if Graph.StaNetWorkWithMarkers == True:
                    ax1.plot(xpt[j],ypt[j], markertype, markersize=markersize,color=markercolor,label=labelname)

                if  Graph.StaNetWorkWithNames == True:
                    try:
                        pos=Graph.StaLetterSizeListName.index(self.StaNetwork[j])
                        lettersize=Graph.StaLetterSizeListValue[pos]
                    except:
                        lettersize=Graph.StaNetWorkDefNameSize #Default letter size
                    try:
                        pos=Graph.StaLetterColorListName.index(self.StaNetwork[j])
                        lettercolor=Graph.StaLetterColorListValue[pos]
                    except:
                        lettercolor=Graph.StaNetWorkDefNameColor #Default letter colour
                    try:
                        pos=Graph.StaLetterHorAlignListName.index(self.StaNetwork[j])
                        letterhoralign=Graph.StaLetterHorAlignListValue[pos]
                    except:
                        letterhoralign=Graph.StaNetWorkDefNameHorAlign #Default letter horizontal alignment
                    try:
                        pos=Graph.StaLetterVerAlignListName.index(self.StaNetwork[j])
                        letterveralign=Graph.StaLetterVerAlignListValue[pos]
                    except:
                        letterveralign=Graph.StaNetWorkDefNameVerAlign #Default letter vertical alignment
                    ax1.annotate(self.StaName[j], (xpt[j], ypt[j]),ha=letterhoralign, va=letterveralign, fontsize=lettersize, color=lettercolor)
                    if Graph.StaNetWorkWithMarkers == False:
                        #If markers are not enabled, no labels are added. We need to add them manually with an extra "empty" plot
                        ax1.plot([],[], ' ',label=labelname)


            if Graph.StaNetAddLabel == True:
                handles, labels = ax1.get_legend_handles_labels()
                by_label = OrderedDict(zip(labels, handles))

                if Graph.NumPointsLabel==None:
                    #In this case, we print the station names but set no marker,therefore in the label there is no marker to show
                    #We need to remove the blank space left by the "empty" marker
                    if (Graph.LabelPosition == 11):
                        leg = ax1.legend(by_label.values(), by_label.keys(),handlelength=0, handletextpad=.3,numpoints=Graph.NumPointsLabel,bbox_to_anchor=(Graph.LabelPositionX, Graph.LabelPositionY))
                    else:
                        leg = ax1.legend(by_label.values(), by_label.keys(),handlelength=0, handletextpad=.3,numpoints=Graph.NumPointsLabel,loc=Graph.LabelPosition)

                else:
                    if (Graph.LabelPosition == 11):
                        ax1.legend(by_label.values(), by_label.keys(),numpoints=Graph.NumPointsLabel,bbox_to_anchor=(Graph.LabelPositionX, Graph.LabelPositionY))
                    else:
                        ax1.legend(by_label.values(), by_label.keys(),numpoints=Graph.NumPointsLabel,loc=Graph.LabelPosition)

            if (self.SaveFigure == True): 
                try:
                    if(len(self.SaveFigurePath)>=idx_sv+1):
                        plt.savefig(self.SaveFigurePath[idx_sv])
                except:
                    Errmsg=str(sys.exc_info()[1]).split('"')
                    if "rgba" in str(sys.exc_info()[1]):
                        print ("ERROR: User defined colour '{0:s}' is not a valid colour".format(Errmsg[1]))
                    else:
                        print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                    removeLockFile()
                    sys.exit()
                idx_sv = idx_sv + 1

        if (self.SaveFigure == False): plt.show()
                
        return self

##########################################################################
# This part makes the SBAS Availability maps
##########################################################################
class SBASmaps:
    def __init__(self):
        self.grid = True
        self.contourlines = True
        self.projection = 'cyl'
        self.continentColor = 'y'
        self.lakeColor = 'w'
        self.boundaryColor = 'w'
        self.f = ""
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'
        self.Title = "Equidistant Cylindrical Projection"
        self.Xlabel = "" 
        self.Ylabel = ""
        self.Cbarlabel = ""
        self.cbarMin = 0.0
        self.cbarMax = 2.0
        self.cbarInterval = 8.0
        self.txt_show = False
        self.map_type = ''
        self.hour = -1
        self.SBASsystemName = ""
        self.PRNtext = ""
        self.PRNtextNewline = False
        self.percentilepercentage = ""

    def readData(self):
        try:
             if PythonVersion == 2: 
                 f = open(self.f,'rb')
             else:
                 f = open(self.f,'r',errors='replace')
        except:
            Errmsg=str(sys.exc_info()[1]).split(":")
            Errmsg=Errmsg[0].split("] ")
            print ("ERROR Opening file '{0:s}': '{1:s}'".format(self.f,Errmsg[1]))
            removeLockFile()
            sys.exit()

        self.longitude = []
        self.latitude = []
        self.percentile = []
        self.doppercent = []
        self.allpercentile = [[],[],[]]
        self.alldoppercent = [[],[],[]]
        i = 0
        hour=0
        riskplot=0
        ionoplot=0
        availdopplot=0
        PRNtextNewline = ""
        if ( self.SBASsystemName == "" ):
            self.SBASsystemName="SBAS"

        if Graph.NotAvailBin==True:
            DOPNoDataValue=-1.
        else:
            DOPNoDataValue=999.
        for line in f:
            var = line.split()
            i = i + 1
            if var != []: 
                NumColumnsLine=len(var)
                match_result = re.match(r'^#',var[0])
                if (match_result != None and i==1):
                    if(var[NumColumnsLine-1] == "HOUR"):
                        hour=1
                        if (var[NumColumnsLine-2] == "WINDOW_SIZE"):
                            riskplot=1
                        elif (var[NumColumnsLine-2] == "GEO-PRN"):
                            ionoplot=1
                        else:
                            availdopplot=1
                    elif (var[NumColumnsLine-1] == "WINDOW_SIZE"):
                        riskplot=1
                    elif (var[NumColumnsLine-1] == "GEO-PRN"):
                        ionoplot=1
                    else:
                        availdopplot=1
                if match_result == None:
                    if i == 2:
                        try:
                            self.Xmin = float(var[2])
                            self.Xmax = float(var[3])
                            self.Ymin = float(var[0])
                            self.Ymax = float(var[1])
                            self.resolution = float(var[4])
                            if availdopplot==1 and hour==0:
                                #Availability or DOP map without hour
                                self.hal = float(var[6])
                                self.val = float(var[7])
                                self.doy = int(var[8])
                                self.year = int(var[9])
                                self.epochs = int(var[10])
                                self.prn = int(var[11])
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                        PRNtext = ""
                                    else:
                                        PRNtext = "PRN " + str(self.prn)

                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                     PRNtext = PRNtext + " "

                            elif availdopplot==1 and hour==1:
                                if hour==1:
                                    #Availability or DOP map with hour
                                    self.hal = float(var[6])
                                    self.val = float(var[7])
                                    self.doy = int(var[8])
                                    self.year = int(var[9])
                                    self.epochs = int(var[10])
                                    self.prn = int(var[11])
                                    self.hour = int(var[13])
                                    if (self.PRNtext != "" ):
                                        PRNtext = self.PRNtext
                                    else:
                                        if (self.prn == 0):
                                            PRNtext = ""
                                        else:
                                            PRNtext = "PRN " + str(self.prn)

                                    if (self.PRNtextNewline == True):
                                        PRNtextNewline = "\n" + PRNtext
                                        PRNtext = ""
                                    elif (PRNtext  != ""):
                                         PRNtext = PRNtext + " "
                            elif riskplot==1 and hour==0:
                                #Cont-Risk Map with no hour
                                self.hal = float(var[6])
                                self.val = float(var[7])
                                self.doy = int(var[8])
                                self.year = int(var[9])
                                self.epochs = int(var[10])
                                self.prn = int(var[11])
                                self.winsize = int(var[13])
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                         PRNtext = ""
                                    else:
                                         PRNtext = "PRN " + str(self.prn)

                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                    PRNtext = PRNtext + " "

                            elif riskplot==1 and hour==1:
                                #Cont-Risk Map with hour
                                self.hal = float(var[6])
                                self.val = float(var[7])
                                self.doy = int(var[8])
                                self.year = int(var[9])
                                self.epochs = int(var[10])
                                self.prn = int(var[11])
                                self.winsize = int(var[13])
                                self.hour = int(var[14])
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                        PRNtext = ""
                                    else:
                                        PRNtext = "PRN " + str(self.prn)

                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                    PRNtext = PRNtext + " "

                            elif ionoplot==1:
                                #Iono map with or without hour
                                self.doy = int(var[5])
                                self.year = int(var[6])
                                self.epochs = int(var[7])
                                self.prn = int(var[8])
                                self.map_type = 'ionoCorrection'
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                        PRNtext = ""
                                    else:
                                        PRNtext = "PRN " + str(self.prn)
        
                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                    PRNtext = PRNtext + " "

                                if hour==1:
                                    self.hour = int(var[9])
                                    self.Title = self.SBASsystemName +" Iono Correction Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self.hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "(Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                                else:
                                    self.Title = self.SBASsystemName + " Iono Correction Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "(Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        except:
                            ErrMsg=str(sys.exc_info()[1]).split()
                            print ("ERROR: Invalid value '{0:s}' in header of SBAS map data file '{1:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),self.f))
                            removeLockFile()
                            sys.exit()
                    else:
                        try:
                            self.latitude.append(float(var[0]))
                            self.longitude.append(float(var[1]))
                            if self.map_type == "HDOP" or self.map_type == "PDOP" or self.map_type == "GDOP":
                                numepochs=int(var[4])
                                if numepochs==0:
                                    #No epochs with solution, so no DOP available. Set it to 999. so it is not printed as a point with lowest DOP 
                                    self.percentile.append(DOPNoDataValue)
                                    if Graph.DOPPercentilePlot == True:
                                        self.doppercent.append(DOPNoDataValue)                                    
                                else:
                                    self.percentile.append(float(var[2]))
                                    if Graph.DOPPercentilePlot == True:
                                        self.doppercent.append(float(var[5]))
                            elif self.map_type == "AllDOP":
                                numepochs=int(var[11])
                                if numepochs==0:
                                    #No epochs with solution, so no DOP available. Set it to 999. so it is not printed as a point with lowest DOP 
                                    self.allpercentile[0].append(DOPNoDataValue)
                                    self.allpercentile[1].append(DOPNoDataValue)
                                    self.allpercentile[2].append(DOPNoDataValue)
                                    if Graph.DOPPercentilePlot == True:
                                        self.alldoppercent[0].append(DOPNoDataValue)
                                        self.alldoppercent[1].append(DOPNoDataValue)
                                        self.alldoppercent[2].append(DOPNoDataValue)
                                else:
                                    self.allpercentile[0].append(float(var[2]))
                                    self.allpercentile[1].append(float(var[5]))
                                    self.allpercentile[2].append(float(var[8]))
                                    if Graph.DOPPercentilePlot == True:
                                        self.alldoppercent[0].append(float(var[4]))
                                        self.alldoppercent[1].append(float(var[7]))
                                        self.alldoppercent[2].append(float(var[10]))
                            else:
                                if NumColumnsLine>3: #This check is to make it compatible with old files that did not provide the number of epochs
                                    if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                        numepochs=int(var[4])
                                    else:
                                        numepochs=int(var[3])
                                    if(numepochs==0):
                                        if Graph.NotAvailBin==True:
                                            self.percentile.append(-1.)
                                        else:
                                            self.percentile.append(float(var[2]))
                                    else:
                                        self.percentile.append(float(var[2]))
                                else:
                                    self.percentile.append(float(var[2]))


                        except:
                            ErrMsg=str(sys.exc_info()[1]).split()
                            if "list index out of range" in str(sys.exc_info()[1]):
                                print ("ERROR: There are missing data columns in line number {0:d} of SBAS map data file '{1:s}'".format(i,self.f))
                            else:
                                print ("ERROR: Invalid value '{0:s}' in line number {1:d} of SBAS map data file '{2:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),i,self.f))
                            removeLockFile()
                            sys.exit()
                elif i == 3:
                    if len(var)<4:
                        print ("ERROR: There are missing data columns in line number {0:d} of SBAS map data file '{1:s}'".format(i,self.f))
                        removeLockFile()
                        sys.exit()
                    if self.map_type != 'ionoCorrection':
                        if var[3] == 'AVAIL%':
                            #self.map_type = re.split(r'\%',var[3])[0]
                            self.map_type = 'availability'
                            if (self.hour == -1):
                                self.Title = self.SBASsystemName + " Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        elif var[3] == 'CONT-RISK':
                            if NumColumnsLine<5:
                                #Old format without the columns with the values used to compute the continuity
                                #Append manually the NUMRISK column, as it will be a continuity risk map
                                var.append("NUMRISK")
                            if var[4] == 'NUMRISK':
                                self.map_type = 'continuity'
                                if (self.hour == -1):
                                    self.Title = self.SBASsystemName + " Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                                else:
                                    self.Title = self.SBASsystemName + " Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.map_type = 'continuityMar'
                                if (self.hour == -1):
                                    self.Title = self.SBASsystemName + " Maritime Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                                else:
                                    self.Title = self.SBASsystemName + " Maritime Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        elif var[3] == 'MEANHDOP':
                            if var[NumColumnsLine-1][0:7] != "PERCENT" and NumColumnsLine>10:
                                self.percentilepercentage = var[NumColumnsLine-2][7:9]
                                self.map_type = "AllDOP"
                                if (self.hour == -1):
                                    self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                                else:
                                    self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.percentilepercentage = var[NumColumnsLine-1][7:9]
                                self.map_type = "HDOP"
                                if (self.hour == -1):
                                    self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                                else:
                                    self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        elif var[3] == 'MEANPDOP':
                            self.percentilepercentage = var[NumColumnsLine-1][7:9]
                            self.map_type = "PDOP"
                            if (self.hour == -1):
                                self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        elif var[3] == 'MEANGDOP':
                            self.percentilepercentage = var[NumColumnsLine-1][7:9]
                            self.map_type = "GDOP"
                            if (self.hour == -1):
                                self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " DOP Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + " (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
        f.close()
        if i<4:
            print ("ERROR: File '{0:s}' has no data".format(self.f))
            removeLockFile()
            sys.exit()

        return self

    def drawMap(self):
        DOPplottypes=['Median','Percentile']
        idx_sv = 0

        if (Graph.FIROutputFileNameDegText != ""):
            try:
                FIROutputFileDescriptorDegText = io.open(Graph.FIROutputFileNameDegText, 'w', encoding="utf-8")
            except:
                Errmsg=str(sys.exc_info()[1]).split(":")
                Errmsg=Errmsg[0].split("] ")
                print ("ERROR: Cannot open file '{0:s}' for writing FIR degradation text: '{1:s}'".format(Graph.FIROutputFileNameDegText,Errmsg[1]))
                removeLockFile()
                sys.exit()

        #If percentilepercentage is 00, is due to it only reads two characters
        if self.percentilepercentage == "00":
            self.percentilepercentage = "100"

        if self.map_type == 'AllDOP':
            nummaps=3
        else:
            nummaps=1

        for numplot in range(0,nummaps):
            if nummaps==3:
                if numplot==0:
                    self.map_type = 'HDOP'
                elif numplot==1:
                    self.map_type = 'PDOP'
                else:
                    self.map_type = 'GDOP'

            for plottype in DOPplottypes:
                if plottype=='Percentile':
                    if self.map_type == 'availability' or self.map_type == 'continuity' or self.map_type == 'continuityMar' or self.map_type == 'ionoCorrection':
                        continue
                    elif Graph.DOPPercentilePlot == False:
                        continue
                    if nummaps==3:
                        if numplot==0:
                            self.percentile = self.alldoppercent[0]
                        elif numplot==1:
                            self.percentile = self.alldoppercent[1]
                        else:
                            self.percentile = self.alldoppercent[2]
                    else:
                        self.percentile = self.doppercent
                else:
                    if nummaps==3:
                        if numplot==0:
                            self.percentile = self.allpercentile[0]
                        elif numplot==1:
                            self.percentile = self.allpercentile[1]
                        else:
                            self.percentile = self.allpercentile[2]

                #If aspect ratios is below 1.4 (threshold set by trial and error), the plot will not be fitted in the screen
                #We will manually adjust the margins to fit the image
                #The user can manually set the margins if automatic margins are not good
                AspectRatio=(self.Xmax-self.Xmin)/(self.Ymax-self.Ymin)
                if AspectRatio<=1.4: 
                    if Graph.TopMargin!=-1.:
                        topmargin=Graph.TopMargin
                    else:
                        if Graph.PRNtextNewline==True:
                            topmargin=.83
                        else:
                            topmargin=.87

                    if Graph.BottomMargin!=-1.:
                        bottommargin=Graph.BottomMargin
                    else:
                        if self.Xlabel!="":
                            if (PythonVersionDecimal==2.7 and sys.version_info[2]>=15) or PythonVersionDecimal>=3.6:
                                #In this Python versions there is not enough space for the Xlabel (something changed in the Python library)
                                bottommargin=.1
                            else:
                                bottommargin=.08
                        else:
                            bottommargin=.05
                else:
                    if Graph.TopMargin!=-1.:
                        topmargin=Graph.TopMargin
                    else:
                        if Graph.PRNtextNewline==True:
                            topmargin=.97
                        else:
                            topmargin=1

                    if Graph.BottomMargin!=-1.:
                        bottommargin=Graph.BottomMargin
                    else:
                        bottommargin=0

                if Graph.SBASplotUserSetSize == True:
                    fig = plt.figure(figsize=(Graph.FigHorSize,Graph.FigVerSize)) #This is to change the initial figure size (values are in inches)
                else:
                    fig = plt.figure()
                ax = fig.add_subplot(111,aspect = 'equal')
                leftmargin=0.07
                if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                    if (PythonVersionDecimal==2.7 and sys.version_info[2]>=15) or PythonVersionDecimal>=3.6:
                        #In this Python versions there is not enough space for colourbar bins text (something changed in the Python library)
                        rightmargin=.88
                    else:
                        rightmargin=.89

                    if Graph.ContRiskAsPercentage == True:
                        NumDecimalsMargin=-1*int('{0:.1e}'.format(Graph.RiskBins[len(Graph.RiskBins)-1]).split("e")[1])
                        if NumDecimalsMargin>4:
                            rightmargin-=(NumDecimalsMargin-5)*0.013
                        elif (PythonVersionDecimal==2.7 and sys.version_info[2]>=15) or PythonVersionDecimal>=3.6:
                            rightmargin=.90
                        else:
                            rightmargin=.91
                else:
                    if (PythonVersionDecimal==2.7 and sys.version_info[2]>=15) or PythonVersionDecimal>=3.6:
                        #In this Python versions there is not enough space for the colourbar bins text (something changed in the Python library)
                        rightmargin=.91
                    else:
                        rightmargin=.92

                    if self.map_type == 'availability':
                        try:
                            NumDecimalsMargin=len(str(int('{0:.12g}'.format(Graph.AvailBins[len(Graph.AvailBins)-1]).split(".")[1])))
                        except:
                            #For the case there are no decimals
                            NumDecimalsMargin=0
                        if NumDecimalsMargin==2:
                            rightmargin-=(NumDecimalsMargin-1)*0.015
                        elif NumDecimalsMargin>2:
                            rightmargin-=(NumDecimalsMargin-2)*0.02

                    elif self.map_type == 'ionoCorrection':
                        try:
                            NumDecimalsMargin=len(str(int('{0:.12g}'.format(Graph.IonoAvailBins[len(Graph.IonoAvailBins)-1]).split(".")[1])))
                        except:
                            #For the case there are no decimals
                            NumDecimalsMargin=0

                        if NumDecimalsMargin==2:
                            rightmargin-=(NumDecimalsMargin-1)*0.015
                        elif NumDecimalsMargin>2:
                            rightmargin-=(NumDecimalsMargin-2)*0.02

                if (self.Xlabel!= ""):
                    ax.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
                    ax.xaxis.labelpad = 10 #This is an offset to vertical label so it does not overlap with the degrees ticks
                if (self.Ylabel!= ""):
                    ax.set_ylabel(self.Ylabel)
                    ax.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks
                    leftmargin=0.1
                if Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True:
                    if self.map_type == 'availability' and Graph.AvailBinsText[1] == "Compliant":
                        rightmargin=.87
                    elif self.map_type == 'continuity' and Graph.RiskBinsText[1] == "Compliant":
                        rightmargin=.87
                    elif self.map_type == 'continuityMar' and Graph.RiskMarBinsText[1] == "Compliant":
                        rightmargin=.87
                    elif self.map_type == 'ionoCorrection' and Graph.IonoAvailBinsText[1] == "Compliant": 
                        rightmargin=.87
                    elif self.map_type == 'HDOP' and Graph.HDOPBinsText[1] == "Compliant":
                        rightmargin=.87
                    elif self.map_type == 'PDOP' and Graph.PDOPBinsText[1] == "Compliant":
                        rightmargin=.87
                    elif self.map_type == 'GDOP' and Graph.GDOPBinsText[1] == "Compliant":
                        rightmargin=.87
                elif (self.Cbarlabel != ""):
                    if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                        rightmargin=.86
                    else:
                        rightmargin=.9


                if self.map_type == 'HDOP' or self.map_type == 'PDOP' or self.map_type == 'GDOP':
                    if Graph.Title == "":
                        #Only replace values in title if it is not set by the user
                        if plottype=='Percentile':
                            ax.set_title(self.Title.replace("Map",self.percentilepercentage + " " + plottype + " Map").replace("DOP",self.map_type))
                        else:
                            ax.set_title(self.Title.replace("Map",plottype + " Map").replace("DOP",self.map_type)) 
                    else:
                        ax.set_title(self.Title)
                else:
                    if Graph.ContRiskAsPercentage == True:
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            if Graph.Title == "":
                                self.Title = self.Title.replace("Continuity Risk","Continuity")

                    ax.set_title(self.Title)

                if Graph.LeftMargin!=-1.:
                    leftmargin=Graph.LeftMargin

                if Graph.RightMargin!=-1.:
                    rightmargin=Graph.RightMargin

                plt.subplots_adjust(left=leftmargin, right=rightmargin,  wspace=0, hspace=0,bottom=bottommargin,top=topmargin) #This is to adjust figure to margin with tight_layout function

                baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution=Graph.MapResolution)
                #Add European FIR
                if Graph.FIREurope and Graph.FIRShowBorderEur == True:
                    lonfir,latfir=baseM(Graph.lonFIREur,Graph.latFIREur)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleEur, markersize=Graph.FIRMarkerSizeEur, linewidth=Graph.FIRLineWidthEur,color=Graph.FIRLineColorEur) 
                #Add CONUS FIR
                if Graph.FIRCONUS and Graph.FIRShowBorderCONUS == True:
                    lonfir,latfir=baseM(Graph.lonFIRCONUS,Graph.latFIRCONUS)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleCONUS, markersize=Graph.FIRMarkerSizeCONUS, linewidth=Graph.FIRLineWidthCONUS,color=Graph.FIRLineColorCONUS) 
                #Add Alaska FIR
                if Graph.FIRAlaska and Graph.FIRShowBorderAlaska == True:
                    lonfir,latfir=baseM(Graph.lonFIRAlaska,Graph.latFIRAlaska)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleAlaska, markersize=Graph.FIRMarkerSizeAlaska, linewidth=Graph.FIRLineWidthAlaska,color=Graph.FIRLineColorAlaska) 
                #Add Canada FIR
                if Graph.FIRCanada and Graph.FIRShowBorderCanada == True:
                    lonfir,latfir=baseM(Graph.lonFIRCanada,Graph.latFIRCanada)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleCanada, markersize=Graph.FIRMarkerSizeCanada, linewidth=Graph.FIRLineWidthCanada,color=Graph.FIRLineColorCanada) 
                #Add Mexico FIR
                if Graph.FIRMexico and Graph.FIRShowBorderMexico == True:
                    lonfir,latfir=baseM(Graph.lonFIRMexico,Graph.latFIRMexico)
                    baseM.plot(lonfir,latfir,Graph.FIRLineStyleMexico, markersize=Graph.FIRMarkerSizeMexico, linewidth=Graph.FIRLineWidthMexico,color=Graph.FIRLineColorMexico) 
                #Add user FIR
                if Graph.FIRNumUserFile >0:
                    for i in range(Graph.FIRNumUserFile):
                        if Graph.FIRShowBorder[i] == True:
                            lonfir,latfir=baseM(Graph.lonFIR[i],Graph.latFIR[i])
                            baseM.plot(lonfir,latfir,Graph.FIRLineStyle[i], markersize=Graph.FIRMarkerSize[i], linewidth=Graph.FIRLineWidth[i],color=Graph.FIRLineColor[i]) 

                #Set ticks according to user to automatic
                if Graph.XTicsStepUser == True:
                    meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
                elif Graph.XTicsUser == True:
                    meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
                elif Graph.XTicsListUser == True:
                    meridian = Graph.XTicksList
                else:
                    meridian = np.linspace(self.Xmin,self.Xmax,15.)

                if (Graph.YTicsStepUser == True):
                    parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
                elif Graph.YTicsUser == True:
                    parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
                elif Graph.YTicsListUser == True:
                    parallel = Graph.YTicksList
                else:
                    parallel = np.linspace(self.Ymin,self.Ymax,10.)

                baseM.drawcoastlines()
                if Graph.Countries:
                    baseM.drawcountries()
                if Graph.USAStates:
                    baseM.drawstates()
                baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
                if self.grid:
                    w_line = 1.0
                else: 
                    w_line = 0.0
                baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
                baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
                baseM.drawmapboundary(fill_color=self.boundaryColor)
                mypatch = []
                mycolors = []

                ColorList = []
                ColorBarTitle = ""
                BinTextList = []
                if self.map_type == 'continuity':
                    percentile_bin = list(np.array(Graph.RiskBins))
                    if Graph.ContRiskColorList != []:
                        ColorList = Graph.ContRiskColorList
                    if Graph.RiskBinsText != []:
                        BinTextList = Graph.RiskBinsText
                    if Graph.ContRiskCbarTitle != "":
                        ColorBarTitle = Graph.ContRiskCbarTitle
                    if Graph.BinsEqualCondition == False:
                        if Graph.DisableBinsEqualCondition == False:
                            if Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True or Graph.ServiceFormat == True or Graph.ServiceFormatMaritime == True:
                                Graph.BinsEqualCondition = True
                elif self.map_type == 'continuityMar':
                    percentile_bin = list(np.array(Graph.RiskMarBins))
                    if Graph.ContRiskMarColorList != []:
                        ColorList = Graph.ContRiskMarColorList
                    if Graph.RiskMarBinsText != []:
                        BinTextList = Graph.RiskMarBinsText
                    if Graph.ContRiskMarCbarTitle != []:
                        ColorBarTitle = Graph.ContRiskMarCbarTitle
                    if Graph.BinsEqualCondition == False:
                        if Graph.DisableBinsEqualCondition == False:
                            if Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True or Graph.ServiceFormat == True or Graph.ServiceFormatMaritime == True:
                                Graph.BinsEqualCondition = True
                elif self.map_type == 'HDOP':
                    percentile_bin = list(np.array(Graph.HDOPBins))
                    if Graph.HDOPColorList != []:
                        ColorList = Graph.HDOPColorList
                    if Graph.HDOPBinsText != []:
                        BinTextList = Graph.HDOPBinsText
                    if Graph.HDOPCbarTitle != "":
                        ColorBarTitle = Graph.HDOPCbarTitle
                elif self.map_type == 'PDOP':
                    percentile_bin = list(np.array(Graph.PDOPBins))
                    if Graph.PDOPColorList != []:
                        ColorList = Graph.PDOPColorList
                    if Graph.PDOPBinsText != []:
                        BinTextList = Graph.PDOPBinsText 
                    if Graph.PDOPCbarTitle != []:
                        ColorBarTitle = Graph.PDOPCbarTitle
                elif self.map_type == 'GDOP':
                    percentile_bin = list(np.array(Graph.GDOPBins))
                    if Graph.GDOPColorList != []:
                        ColorList = Graph.GDOPColorList
                    if Graph.GDOPBinsText != []:
                        BinTextList = Graph.GDOPBinsText
                    if Graph.GDOPCbarTitle != "":
                        ColorBarTitle = Graph.GDOPCbarTitle
                elif self.map_type == 'ionoCorrection':
                    percentile_bin = list(np.array(Graph.IonoAvailBins))
                    if Graph.IonoAvailColorList != []:
                        ColorList = Graph.IonoAvailColorList
                    if Graph.IonoAvailBinsText != []:
                        BinTextList = Graph.IonoAvailBinsText
                    if Graph.IonoAvailCbarTitle != "":
                        ColorBarTitle = Graph.IonoAvailCbarTitle
                    if Graph.BinsEqualCondition == False:
                        if Graph.DisableBinsEqualCondition == False:
                            if Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True or Graph.ServiceFormat == True or Graph.ServiceFormatMaritime == True:
                                Graph.BinsEqualCondition = True
                else: #Availability
                    percentile_bin = list(np.array(Graph.AvailBins))
                    if Graph.AvailColorList != []:
                        ColorList = Graph.AvailColorList
                    if Graph.AvailBinsText != []:
                        BinTextList = Graph.AvailBinsText 
                    if Graph.AvailCbarTitle != "":
                        ColorBarTitle = Graph.AvailCbarTitle
                    if Graph.BinsEqualCondition == False:
                        if Graph.DisableBinsEqualCondition == False:
                            if Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True or Graph.ServiceFormat == True or Graph.ServiceFormatMaritime == True:
                                Graph.BinsEqualCondition = True

                if Graph.NotAvailBin == True:
                    percentile_bin.insert(0,-1)

                percentile_len = len(percentile_bin)
                BinLastValue=percentile_bin[percentile_len-1]


                if Graph.FIRDegradation == True:
                    #Initialize values for user FIR degradation values
                    #The user defined FIR has to go first for the case that that the degradation
                    #text is printed in table format, in which ht bins used will be the ones
                    #given with parameter '--firdegtextbins' (values from the first time given will be used)
                    if Graph.ContRiskAsPercentage == True:
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            percentile_bin_aux = []
                            for i in percentile_bin:
                                if i==-1:
                                    percentile_bin_aux.append(i)
                                else:
                                    percentile_bin_aux.append(100*(1-i))

                    if Graph.FIRNumUserFile >0:
                        PolygonPath = []
                        TotalPointsInsideRegion = [[]]
                        TotalPointsInsideAvail = [[]]
                        TotalPointsInsideNoAvail = [[]]                        
                        for i in range(Graph.FIRNumUserFile):
                            if i>0 and Graph.FIRDegTextTable == True:
                                Graph.FIRDegTextBins[i] = Graph.FIRDegTextBins[0]
                            else:
                                if Graph.FIRNumDegTextBins == 0:
                                    Graph.FIRDegTextBins[i] = [] #For the case of multi-DOP map, to ensure it removes data from previous iteration
                                    Graph.FIRDegTextBins[i].append(BinLastValue)
                                else:
                                    if Graph.FIRDegTextBins[i]==[]:
                                        Graph.FIRDegTextBins[i].append(BinLastValue)
                                    else:
                                        for j in Graph.FIRDegTextBins[i]:
                                            try:
                                                k=percentile_bin.index(j)
                                            except:
                                                Error=1
                                                if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                                    try:
                                                        k=percentile_bin_aux.index(j)
                                                        Error=0
                                                    except:
                                                        BinVal='{0:.2f}'.format(j)
                                                else:
                                                    if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                                        BinVal='{0:.1e}'.format(j)
                                                    else:
                                                        BinVal='{0:.1f}'.format(j)
                                                
                                                if Error==1:
                                                    FileName=os.path.basename(Graph.FIRUserFile[i])
                                                    FileName=os.path.splitext(FileName)[0]
                                                    print ("ERROR: Bin '{0:s}' in '{1:s}' FIR is not a bin in the {2:s} map type".format(BinVal,FileName,self.map_type))
                                                    removeLockFile()
                                                    sys.exit()
                                                else:
                                                    l=Graph.FIRDegTextBins[i].index(j)
                                                    Graph.FIRDegTextBins[i][l]=percentile_bin[k]
                                        
                                        if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                            #Sort bins in ascending order
                                            Graph.FIRDegTextBins[i] = sorted(Graph.FIRDegTextBins[i])
                                        else:
                                            #Sort bins in descending order
                                            Graph.FIRDegTextBins[i] = sorted(Graph.FIRDegTextBins[i],reverse=True)
    
                            if PythonVersion == 2:
                                polygon = zip(Graph.lonFIR[i],Graph.latFIR[i])
                            else:
                                #In python3, the zip function is not accepted for creating the list of points for the polygon
                                polygon = []
                                for pair in ((Graph.lonFIR[i][j], Graph.latFIR[i][j]) for j in range(len(Graph.lonFIR[i]))):
                                    polygon.append(pair)
                            PolygonPath.append(mpltPath.Path(polygon))

                            TotalPointsInsideRegion.append([])
                            TotalPointsInsideAvail.append([])
                            TotalPointsInsideNoAvail.append([])
                            for j in range(len(Graph.FIRDegTextBins[i])):
                                TotalPointsInsideRegion[i].append(0)
                                TotalPointsInsideAvail[i].append(0)
                                TotalPointsInsideNoAvail[i].append(0)

                    elif Graph.FIRDegTextTable == True:
                        #Add the default value of the bins, as there are no user defined FIR maps
                        if  Graph.FIRNumDegTextBins==0:
                            Graph.FIRDegTextBins.append([])
                            Graph.FIRDegTextBins[0] = [] #For the case of multi-DOP map, to ensure it removes that from previous iteration
                            Graph.FIRDegTextBins[0].append(BinLastValue)
                        elif self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                            #Sort bins in ascending order
                            Graph.FIRDegTextBins[0] = sorted(Graph.FIRDegTextBins[0])
                        else:
                            #Sort bins in descending order
                            Graph.FIRDegTextBins[0] = sorted(Graph.FIRDegTextBins[0],reverse=True)


                    if Graph.FIRDegTextTable == True:
                        #Set to the European, CONUS, Alaska, Canada and Mexico FIR the same bins
                        Graph.FIRDegTextBinsEur = Graph.FIRDegTextBins[0]
                        Graph.FIRDegTextBinsCONUS = Graph.FIRDegTextBins[0]
                        Graph.FIRDegTextBinsAlaska = Graph.FIRDegTextBins[0]
                        Graph.FIRDegTextBinsCanada = Graph.FIRDegTextBins[0]
                        Graph.FIRDegTextBinsMexico = Graph.FIRDegTextBins[0]
                        #Set the lenght values to indicate that bins have been manually set
                        Graph.FIRNumDegTextBinsEur=len(Graph.FIRDegTextBins[0])
                        Graph.FIRNumDegTextBinsCONUS=len(Graph.FIRDegTextBins[0])
                        Graph.FIRNumDegTextBinsAlaska=len(Graph.FIRDegTextBins[0])
                        Graph.FIRNumDegTextBinsCanada=len(Graph.FIRDegTextBins[0])
                        Graph.FIRNumDegTextBinsMexico=len(Graph.FIRDegTextBins[0])
                        
                    #Initialize values for European FIR degradation values
                    if Graph.FIREurope:
                        if Graph.FIRNumDegTextBinsEur == 0:
                            Graph.FIRNumDegTextBinsEur=1
                            Graph.FIRDegTextBinsEur.append(BinLastValue)
                        else:
                            for i in Graph.FIRDegTextBinsEur:
                                try:
                                    percentile_bin.index(i)
                                except:
                                    Error=1
                                    if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                        try:
                                            percentile_bin_aux.index(i)
                                            Error=0
                                        except:
                                            BinVal='{0:.2f}'.format(i)
                                    else:
                                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                            BinVal='{0:.1e}'.format(i)
                                        else:
                                            BinVal='{0:.1f}'.format(i)
                                    
                                    if Error==1:
                                        print ("ERROR: Bin '{0:s}' in Europe FIR is not a bin in the {1:s} map type".format(BinVal,self.map_type))
                                        removeLockFile()
                                        sys.exit()
                                
                            if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                #Sort bins in ascending order
                                Graph.FIRDegTextBinsEur = sorted(Graph.FIRDegTextBinsEur)
                            else:
                                #Sort bins in descending order
                                Graph.FIRDegTextBinsEur = sorted(Graph.FIRDegTextBinsEur,reverse=True)

                        TotalPointsInsideRegionEur = []
                        TotalPointsInsideAvailEur = []
                        TotalPointsInsideNoAvailEur = []
                        if PythonVersion == 2:
                            polygon = zip(Graph.lonFIREur,Graph.latFIREur)
                        else:
                            #In python3, the zip function is not accepted for creating the list of points for the polygon
                            polygon = []
                            for pair in ((Graph.lonFIREur[i], Graph.latFIREur[i]) for i in range(len(Graph.lonFIREur))):
                                polygon.append(pair)
                        PolygonPathEur = mpltPath.Path(polygon)
                        for i in range(Graph.FIRNumDegTextBinsEur):
                            TotalPointsInsideRegionEur.append(0)
                            TotalPointsInsideAvailEur.append(0)
                            TotalPointsInsideNoAvailEur.append(0)
                    #Initialize values for CONUS FIR degradation values
                    if Graph.FIRCONUS:
                        if Graph.FIRNumDegTextBinsCONUS == 0:
                            Graph.FIRNumDegTextBinsCONUS=1
                            Graph.FIRDegTextBinsCONUS.append(BinLastValue)
                        else:
                            for i in Graph.FIRDegTextBinsCONUS:
                                try:
                                    percentile_bin.index(i)
                                except:
                                    Error=1
                                    if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                        try:
                                            percentile_bin_aux.index(i)
                                            Error=0
                                        except:
                                            BinVal='{0:.2f}'.format(i)
                                    else:
                                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                            BinVal='{0:.1e}'.format(i)
                                        else:
                                            BinVal='{0:.1f}'.format(i)
                                    
                                    if Error==1:
                                        print ("ERROR: Bin '{0:s}' in CONUS FIR is not a bin in the {1:s} map type".format(BinVal,self.map_type))
                                        removeLockFile()
                                        sys.exit()
                                
                            if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                #Sort bins in ascending order
                                Graph.FIRDegTextBinsCONUS = sorted(Graph.FIRDegTextBinsCONUS)
                            else:
                                #Sort bins in descending order
                                Graph.FIRDegTextBinsCONUS = sorted(Graph.FIRDegTextBinsCONUS,reverse=True)

                        TotalPointsInsideRegionCONUS = []
                        TotalPointsInsideAvailCONUS = []
                        TotalPointsInsideNoAvailCONUS = []
                        if PythonVersion == 2:
                            polygon = zip(Graph.lonFIRCONUS,Graph.latFIRCONUS)
                        else:
                            #In python3, the zip function is not accepted for creating the list of points for the polygon
                            polygon = []
                            for pair in ((Graph.lonFIRCONUS[i], Graph.latFIRCONUS[i]) for i in range(len(Graph.lonFIRCONUS))):
                                polygon.append(pair)
                        PolygonPathCONUS = mpltPath.Path(polygon)
                        for i in range(Graph.FIRNumDegTextBinsCONUS):
                            TotalPointsInsideRegionCONUS.append(0)
                            TotalPointsInsideAvailCONUS.append(0)
                            TotalPointsInsideNoAvailCONUS.append(0)

                    #Initialize values for Alaska FIR degradation values
                    if Graph.FIRAlaska:
                        if Graph.FIRNumDegTextBinsAlaska == 0:
                            Graph.FIRNumDegTextBinsAlaska=1
                            Graph.FIRDegTextBinsAlaska.append(BinLastValue)
                        else:
                            for i in Graph.FIRDegTextBinsAlaska:
                                try:
                                    percentile_bin.index(i)
                                except:
                                    Error=1
                                    if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                        try:
                                            percentile_bin_aux.index(i)
                                            Error=0
                                        except:
                                            BinVal='{0:.2f}'.format(i)
                                    else:
                                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                            BinVal='{0:.1e}'.format(i)
                                        else:
                                            BinVal='{0:.1f}'.format(i)
                                    
                                    if Error==1:
                                        print ("ERROR: Bin '{0:s}' in Alaska FIR is not a bin in the {1:s} map type".format(BinVal,self.map_type))
                                        removeLockFile()
                                        sys.exit()
                                
                            if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                #Sort bins in ascending order
                                Graph.FIRDegTextBinsAlaska = sorted(Graph.FIRDegTextBinsAlaska)
                            else:
                                #Sort bins in descending order
                                Graph.FIRDegTextBinsAlaska = sorted(Graph.FIRDegTextBinsAlaska,reverse=True)

                        TotalPointsInsideRegionAlaska = []
                        TotalPointsInsideAvailAlaska = []
                        TotalPointsInsideNoAvailAlaska = []
                        if PythonVersion == 2:
                            polygon = zip(Graph.lonFIRAlaska,Graph.latFIRAlaska)
                        else:
                            #In python3, the zip function is not accepted for creating the list of points for the polygon
                            polygon = []
                            for pair in ((Graph.lonFIRAlaska[i], Graph.latFIRAlaska[i]) for i in range(len(Graph.lonFIRAlaska))):
                                polygon.append(pair)
                        PolygonPathAlaska = mpltPath.Path(polygon)
                        for i in range(Graph.FIRNumDegTextBinsAlaska):
                            TotalPointsInsideRegionAlaska.append(0)
                            TotalPointsInsideAvailAlaska.append(0)
                            TotalPointsInsideNoAvailAlaska.append(0)

                    #Initialize values for Canada FIR degradation values
                    if Graph.FIRCanada:
                        if Graph.FIRNumDegTextBinsCanada == 0:
                            Graph.FIRNumDegTextBinsCanada=1
                            Graph.FIRDegTextBinsCanada.append(BinLastValue)
                        else:
                            for i in Graph.FIRDegTextBinsCanada:
                                try:
                                    percentile_bin.index(i)
                                except:
                                    Error=1
                                    if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                        try:
                                            percentile_bin_aux.index(i)
                                            Error=0
                                        except:
                                            BinVal='{0:.2f}'.format(i)
                                    else:
                                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                            BinVal='{0:.1e}'.format(i)
                                        else:
                                            BinVal='{0:.1f}'.format(i)
                                    
                                    if Error==1:
                                        print ("ERROR: Bin '{0:s}' in Canada FIR is not a bin in the {1:s} map type".format(BinVal,self.map_type))
                                        removeLockFile()
                                        sys.exit()
                                
                            if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                #Sort bins in ascending order
                                Graph.FIRDegTextBinsCanada = sorted(Graph.FIRDegTextBinsCanada)
                            else:
                                #Sort bins in descending order
                                Graph.FIRDegTextBinsCanada = sorted(Graph.FIRDegTextBinsCanada,reverse=True)

                        TotalPointsInsideRegionCanada = []
                        TotalPointsInsideAvailCanada = []
                        TotalPointsInsideNoAvailCanada = []
                        if PythonVersion == 2:
                            polygon = zip(Graph.lonFIRCanada,Graph.latFIRCanada)
                        else:
                            #In python3, the zip function is not accepted for creating the list of points for the polygon
                            polygon = []
                            for pair in ((Graph.lonFIRCanada[i], Graph.latFIRCanada[i]) for i in range(len(Graph.lonFIRCanada))):
                                polygon.append(pair)
                        PolygonPathCanada = mpltPath.Path(polygon)
                        for i in range(Graph.FIRNumDegTextBinsCanada):
                            TotalPointsInsideRegionCanada.append(0)
                            TotalPointsInsideAvailCanada.append(0)
                            TotalPointsInsideNoAvailCanada.append(0)

                    #Initialize values for Mexico FIR degradation values
                    if Graph.FIRMexico:
                        if Graph.FIRNumDegTextBinsMexico == 0:
                            Graph.FIRNumDegTextBinsMexico=1
                            Graph.FIRDegTextBinsMexico.append(BinLastValue)
                        else:
                            for i in Graph.FIRDegTextBinsMexico:
                                try:
                                    percentile_bin.index(i)
                                except:
                                    Error=1
                                    if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                        try:
                                            percentile_bin_aux.index(i)
                                            Error=0
                                        except:
                                            BinVal='{0:.2f}'.format(i)
                                    else:
                                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                            BinVal='{0:.1e}'.format(i)
                                        else:
                                            BinVal='{0:.1f}'.format(i)
                                    
                                    if Error==1:
                                        print ("ERROR: Bin '{0:s}' in Mexico FIR is not a bin in the {1:s} map type".format(BinVal,self.map_type))
                                        removeLockFile()
                                        sys.exit()
                                
                            if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                #Sort bins in ascending order
                                Graph.FIRDegTextBinsMexico = sorted(Graph.FIRDegTextBinsMexico)
                            else:
                                #Sort bins in descending order
                                Graph.FIRDegTextBinsMexico = sorted(Graph.FIRDegTextBinsMexico,reverse=True)

                        TotalPointsInsideRegionMexico = []
                        TotalPointsInsideAvailMexico = []
                        TotalPointsInsideNoAvailMexico = []
                        if PythonVersion == 2:
                            polygon = zip(Graph.lonFIRMexico,Graph.latFIRMexico)
                        else:
                            #In python3, the zip function is not accepted for creating the list of points for the polygon
                            polygon = []
                            for pair in ((Graph.lonFIRMexico[i], Graph.latFIRMexico[i]) for i in range(len(Graph.lonFIRMexico))):
                                polygon.append(pair)
                        PolygonPathMexico = mpltPath.Path(polygon)
                        for i in range(Graph.FIRNumDegTextBinsMexico):
                            TotalPointsInsideRegionMexico.append(0)
                            TotalPointsInsideAvailMexico.append(0)
                            TotalPointsInsideNoAvailMexico.append(0)

                    #Initialize values for FIR sum degradation values
                    if Graph.FIRSum == True:
                        if Graph.FIRDegTextTable == True:
                            #Use bins from the table
                            Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBins[0]
                            Graph.FIRNumDegTextBinsFIRSum = len(Graph.FIRDegTextBins[0])
                        else:
                            #If FIR sum it is not printed in a table, check that bin values are all the same for all FIR select
                            Graph.FIRDegTextBinsFIRSum = []
                            if Graph.FIRSumDegEur == True:
                                Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBinsEur
                                Graph.FIRNumDegTextBinsFIRSum = Graph.FIRNumDegTextBinsEur

                            if Graph.FIRSumDegCONUS == True:
                                if Graph.FIRDegTextBinsFIRSum == []:
                                    Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBinsCONUS
                                    Graph.FIRNumDegTextBinsFIRSum = Graph.FIRNumDegTextBinsCONUS
                                else:
                                    if (Graph.FIRNumDegTextBinsFIRSum != Graph.FIRNumDegTextBinsCONUS or Graph.FIRDegTextBinsFIRSum != Graph.FIRDegTextBinsCONUS):
                                        print("ERROR: When option to compute the sum of several FIRs is set and values are not printed in a tabular format, then all the bin values in all the FIR used for the sum must be the same. Check CONUS FIR bin values.")
                                        removeLockFile()
                                        sys.exit()

                            if Graph.FIRSumDegAlaska == True:
                                if Graph.FIRDegTextBinsFIRSum == []:
                                    Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBinsAlaska
                                    Graph.FIRNumDegTextBinsFIRSum = Graph.FIRNumDegTextBinsAlaska
                                else:
                                    if (Graph.FIRNumDegTextBinsFIRSum != Graph.FIRNumDegTextBinsAlaska or Graph.FIRDegTextBinsFIRSum != Graph.FIRDegTextBinsAlaska):
                                        print("ERROR: When option to compute the sum of several FIRs is set and values are not printed in a tabular format, then all the bin values in all the FIR used for the sum must be the same. Check Alaska FIR bin values.")
                                        removeLockFile()
                                        sys.exit()

                            if Graph.FIRSumDegCanada == True:
                                if Graph.FIRDegTextBinsFIRSum == []:
                                    Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBinsCanada
                                    Graph.FIRNumDegTextBinsFIRSum = Graph.FIRNumDegTextBinsCanada
                                else:
                                    if (Graph.FIRNumDegTextBinsFIRSum != Graph.FIRNumDegTextBinsCanada or Graph.FIRDegTextBinsFIRSum != Graph.FIRDegTextBinsCanada):
                                        print("ERROR: When option to compute the sum of several FIRs is set and values are not printed in a tabular format, then all the bin values in all the FIR used for the sum must be the same. Check Canada FIR bin values.")
                                        removeLockFile()
                                        sys.exit()

                            if Graph.FIRSumDegMexico == True:
                                if Graph.FIRDegTextBinsFIRSum == []:
                                    Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBinsMexico
                                    Graph.FIRNumDegTextBinsFIRSum = Graph.FIRNumDegTextBinsMexico
                                else:
                                    if (Graph.FIRNumDegTextBinsFIRSum != Graph.FIRNumDegTextBinsMexico or Graph.FIRDegTextBinsFIRSum != Graph.FIRDegTextBinsMexico):
                                        print("ERROR: When option to compute the sum of several FIRs is set and values are not printed in a tabular format, then all the bin values in all the FIR used for the sum must be the same. Check Mexico FIR bin values.")
                                        removeLockFile()
                                        sys.exit()

                            if Graph.FIRNumUserFile >0:
                                for i in range(Graph.FIRNumUserFile):
                                    if Graph.FIRSumDegUserFIR[i] == True:
                                        if Graph.FIRDegTextBinsFIRSum == []:
                                            Graph.FIRDegTextBinsFIRSum = Graph.FIRDegTextBins[i]
                                            Graph.FIRNumDegTextBinsFIRSum = len(Graph.FIRDegTextBins[i])
                                        else:
                                            if (Graph.FIRNumDegTextBinsFIRSum != len(Graph.FIRDegTextBins[i]) or Graph.FIRDegTextBinsFIRSum != Graph.FIRDegTextBins[i]):
                                                print("ERROR: When option to compute the sum of several FIRs is set and values are not printed in a tabular format, then all the bin values in all the FIR used for the sum must be the same. Check bin values from user defined FIR number {0:d}.",format(i+1))
                                                removeLockFile()
                                                sys.exit()
                    else:
                        #If FIR sum not enabled, set the number of bins to the sum of all bin values 
                        #of all FIRs to avoid error "index out of list" (as all FIR sum is always written to
                        #regardless it is printed or not later)
                        Graph.FIRNumDegTextBinsFIRSum=Graph.FIRNumDegTextBinsEur+Graph.FIRNumDegTextBinsCONUS+Graph.FIRNumDegTextBinsAlaska
                        Graph.FIRNumDegTextBinsFIRSum+=Graph.FIRNumDegTextBinsCanada+Graph.FIRNumDegTextBinsMexico
                        if Graph.FIRNumUserFile >0:
                            for i in range(Graph.FIRNumUserFile):
                                Graph.FIRNumDegTextBinsFIRSum+=len(Graph.FIRDegTextBins[i])



                    #Initialize data for ALL FIRs percentage (independently if FIR Sum is enabled or not)
                    TotalPointsInsideRegionFIRSum = []
                    TotalPointsInsideAvailFIRSum = []
                    TotalPointsInsideNoAvailFIRSum = []
                    for j in range(Graph.FIRNumDegTextBinsFIRSum):
                        TotalPointsInsideRegionFIRSum.append(0)
                        TotalPointsInsideAvailFIRSum.append(0)
                        TotalPointsInsideNoAvailFIRSum.append(0)



                TotalNumPointsWholePlot=0
                for x,y,z in zip(self.longitude,self.latitude,self.percentile):
                    TotalNumPointsWholePlot+=1
                    rectangle = Rectangle((x,y), self.resolution, self.resolution, linewidth=0)
                    mypatch.append(rectangle)
                    if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                        #Continuity maps
                        if Graph.NotAvailBin == False:
                            i = 1
                            c_ratio = 1
                            if Graph.BinsEqualCondition == True:
                                if z>percentile_bin[1]:
                                    i = 0
                                    c_ratio = 0
                                else:
                                    while (i < percentile_len and ((z-percentile_bin[i]) <= 0)):
                                        c_ratio = i
                                        i = i + 1
                            else:
                                if z>=percentile_bin[1]:
                                    i = 0
                                    c_ratio = 0
                                else:
                                    while (i < percentile_len and ((z-percentile_bin[i]) < 0)):
                                        c_ratio = i
                                        i = i + 1
                        else:
                            i = 2
                            c_ratio = 2
                            if z>1 or z<0.:
                                c_ratio = 0
                            else:
                                if Graph.BinsEqualCondition == True:
                                    if z>percentile_bin[2]:
                                        c_ratio = 1
                                    else:
                                        while (i < percentile_len and ((z-percentile_bin[i]) <= 0)):
                                            c_ratio = i 
                                            i = i + 1
                                else:
                                    if z>=percentile_bin[2]:
                                        c_ratio = 1
                                    else:
                                        while (i < percentile_len and ((z-percentile_bin[i]) < 0)):
                                            c_ratio = i 
                                            i = i + 1
                    elif self.map_type == 'HDOP' or self.map_type == 'PDOP' or self.map_type == 'GDOP':
                        #DOP maps
                        if Graph.NotAvailBin == False:
                            i = 1
                            c_ratio = 1
                            if Graph.BinsEqualCondition == True:
                                if z>percentile_bin[1]:
                                    c_ratio = 0
                                else:
                                    while (i < percentile_len and ((z-percentile_bin[i]) <= 0)):
                                        c_ratio = i  
                                        i = i + 1
                            else:
                                if z>=percentile_bin[1]:
                                    c_ratio = 0
                                else:
                                    while (i < percentile_len and ((z-percentile_bin[i]) < 0)):
                                        c_ratio = i  
                                        i = i + 1
                        else:
                            i = 2
                            c_ratio = 2
                            if z<0:
                                c_ratio = 0
                            else:
                                if Graph.BinsEqualCondition == True:
                                    if z>percentile_bin[2]:
                                        c_ratio = 1
                                    else:
                                        while (i < percentile_len and ((z-percentile_bin[i]) <= 0)):
                                            c_ratio = i  
                                            i = i + 1
                                else:
                                    if z>=percentile_bin[2]:
                                        c_ratio = 1
                                    else:
                                        while (i < percentile_len and ((z-percentile_bin[i]) < 0)):
                                            c_ratio = i  
                                            i = i + 1
                    else:
                        #Avail or IonoAvail maps
                        if Graph.NotAvailBin == False:
                            i = percentile_len -1
                            c_ratio = percentile_len -1
                            if Graph.BinsEqualCondition == True:
                                while (((z-percentile_bin[i]) < 0) and i > 0):
                                    i = i - 1
                                    c_ratio = i 
                            else:
                                while (((z-percentile_bin[i]) <= 0) and i > 0):
                                    i = i - 1
                                    c_ratio = i
                        else:
                            if z<0. or z>100.:
                                c_ratio = 0
                            else:
                                i = percentile_len -1
                                c_ratio = percentile_len -1
                                if Graph.BinsEqualCondition == True:
                                    while (((z-percentile_bin[i]) < 0) and i > 1):
                                        i = i - 1
                                        c_ratio = i 
                                else:
                                    while (((z-percentile_bin[i]) <= 0) and i > 1):
                                        i = i - 1
                                        c_ratio = i
                        
                    mycolors.append(c_ratio)

                    if Graph.FIRDegradation == True:
                        point = (x+self.resolution/2,y+self.resolution/2) #Add half the resolution in order to center the coordinates in the middle of the square pixel
                        PointUsedInCurrentFIRSum=0
                        NotPositivelyCountedPoint=[]
                        for j in range(Graph.FIRNumDegTextBinsFIRSum):
                            NotPositivelyCountedPoint.append(1)
                        #Compute values for European FIR
                        if Graph.FIREurope:
                            insidePolygon = PolygonPathEur.contains_point(point)

                            if insidePolygon == True:
                                UsePoint=0
                                if Graph.FIRSumDegEur == True:
                                    PointUsedInCurrentFIRSum=1
                                    UsePoint=1

                                for j in range(Graph.FIRNumDegTextBinsEur):
                                     TotalPointsInsideRegionEur[j]+=1
                                     TotalPointsInsideRegionFIRSum[j]+=1*UsePoint
                                     ind=percentile_bin.index(Graph.FIRDegTextBinsEur[j])
                                     if c_ratio>=ind:
                                         TotalPointsInsideAvailEur[j]+=1
                                         TotalPointsInsideAvailFIRSum[j]+=1*UsePoint
                                         NotPositivelyCountedPoint[j]=0
                                     else:
                                         TotalPointsInsideNoAvailEur[j]+=1
                        #Compute values for CONUS FIR
                        if Graph.FIRCONUS:
                            insidePolygon = PolygonPathCONUS.contains_point(point)

                            if insidePolygon == True:
                                UsePointTotal=0
                                UsePoint=0
                                if Graph.FIRSumDegCONUS == True:
                                    UsePoint=1
                                    if PointUsedInCurrentFIRSum==0:
                                        UsePointTotal=1
                                        PointUsedInCurrentFIRSum=1

                                for j in range(Graph.FIRNumDegTextBinsCONUS):
                                     TotalPointsInsideRegionCONUS[j]+=1
                                     TotalPointsInsideRegionFIRSum[j]+=1*UsePointTotal
                                     ind=percentile_bin.index(Graph.FIRDegTextBinsCONUS[j])
                                     if c_ratio>=ind:
                                         TotalPointsInsideAvailCONUS[j]+=1
                                         TotalPointsInsideAvailFIRSum[j]+=1*UsePoint*(NotPositivelyCountedPoint[j])
                                         NotPositivelyCountedPoint[j]=0
                                     else:
                                         TotalPointsInsideNoAvailCONUS[j]+=1
                        #Compute values for Alaska FIR
                        if Graph.FIRAlaska:
                            insidePolygon = PolygonPathAlaska.contains_point(point)

                            if insidePolygon == True:
                                UsePointTotal=0
                                UsePoint=0
                                if Graph.FIRSumDegAlaska == True:
                                    UsePoint=1
                                    if PointUsedInCurrentFIRSum==0:
                                        UsePointTotal=1
                                        PointUsedInCurrentFIRSum=1

                                for j in range(Graph.FIRNumDegTextBinsAlaska):
                                     TotalPointsInsideRegionAlaska[j]+=1
                                     TotalPointsInsideRegionFIRSum[j]+=1*UsePointTotal
                                     ind=percentile_bin.index(Graph.FIRDegTextBinsAlaska[j])
                                     if c_ratio>=ind:
                                         TotalPointsInsideAvailAlaska[j]+=1
                                         TotalPointsInsideAvailFIRSum[j]+=1*UsePoint*(NotPositivelyCountedPoint[j])
                                         NotPositivelyCountedPoint[j]=0
                                     else:
                                         TotalPointsInsideNoAvailAlaska[j]+=1
                        #Compute values for Canada FIR
                        if Graph.FIRCanada:
                            insidePolygon = PolygonPathCanada.contains_point(point)

                            if insidePolygon == True:
                                UsePointTotal=0
                                UsePoint=0
                                if Graph.FIRSumDegCanada == True:
                                    UsePoint=1
                                    if PointUsedInCurrentFIRSum==0:
                                        UsePointTotal=1
                                        PointUsedInCurrentFIRSum=1

                                for j in range(Graph.FIRNumDegTextBinsCanada):
                                     TotalPointsInsideRegionCanada[j]+=1
                                     TotalPointsInsideRegionFIRSum[j]+=1*UsePointTotal
                                     ind=percentile_bin.index(Graph.FIRDegTextBinsCanada[j])
                                     if c_ratio>=ind:
                                         TotalPointsInsideAvailCanada[j]+=1
                                         TotalPointsInsideAvailFIRSum[j]+=1*UsePoint*(NotPositivelyCountedPoint[j])
                                         NotPositivelyCountedPoint[j]=0
                                     else:
                                         TotalPointsInsideNoAvailCanada[j]+=1
                        #Compute values for Mexico FIR
                        if Graph.FIRMexico:
                            insidePolygon = PolygonPathMexico.contains_point(point)

                            if insidePolygon == True:
                                UsePointTotal=0
                                UsePoint=0
                                if Graph.FIRSumDegMexico == True:
                                    UsePoint=1
                                    if PointUsedInCurrentFIRSum==0:
                                        UsePointTotal=1
                                        PointUsedInCurrentFIRSum=1

                                for j in range(Graph.FIRNumDegTextBinsMexico):
                                     TotalPointsInsideRegionMexico[j]+=1
                                     TotalPointsInsideRegionFIRSum[j]+=1*UsePointTotal
                                     ind=percentile_bin.index(Graph.FIRDegTextBinsMexico[j])
                                     if c_ratio>=ind:
                                         TotalPointsInsideAvailMexico[j]+=1
                                         TotalPointsInsideAvailFIRSum[j]+=1*UsePoint*(NotPositivelyCountedPoint[j])
                                         NotPositivelyCountedPoint[j]=0
                                     else:
                                         TotalPointsInsideNoAvailMexico[j]+=1
                        #Compute values for user FIR
                        if Graph.FIRNumUserFile >0:
                            for j in range(Graph.FIRNumUserFile):
                                insidePolygon = PolygonPath[j].contains_point(point)

                                if insidePolygon == True:
                                    UsePointTotal=0
                                    UsePoint=0
                                    if Graph.FIRSumDegUserFIR[j] == True:
                                        UsePoint=1
                                        if PointUsedInCurrentFIRSum==0:
                                            UsePointTotal=1
                                            PointUsedInCurrentFIRSum=1

                                    for k in range(len(Graph.FIRDegTextBins[j])):
                                         TotalPointsInsideRegion[j][k]+=1
                                         TotalPointsInsideRegionFIRSum[k]+=1*UsePointTotal
                                         ind=percentile_bin.index(Graph.FIRDegTextBins[j][k])
                                         if c_ratio>=ind:
                                             TotalPointsInsideAvail[j][k]+=1
                                             if Graph.FIRSumDegUserFIR[j] == True:
                                                 TotalPointsInsideAvailFIRSum[k]+=1*UsePoint*(NotPositivelyCountedPoint[k])
                                                 NotPositivelyCountedPoint[k]=0
                                         else:
                                             TotalPointsInsideNoAvail[j][k]+=1

                        #If point in FIR sum was used, check if it was positively counted (that is, any FIR had that point as available)
                        #If not, add one to the number of points not available 
                        if PointUsedInCurrentFIRSum==1:
                            for j in range(Graph.FIRNumDegTextBinsFIRSum):
                                if NotPositivelyCountedPoint[j]==1:
                                    TotalPointsInsideNoAvailFIRSum[j]+=1



                bounds = np.linspace(0, percentile_len,percentile_len+1)

                #The following command are to print the colours used in the colormap
                #mycmap = plt.get_cmap(self.cm,11)  
                #for i in range(mycmap.N):
                #    rgb = mycmap(i)[:3] # will return rgba, we take only first 3 so we get rgb
                #    print(matplotlib.colors.rgb2hex(rgb))

                if ColorList == []:
                    
                    #self.cm value is overwritten in each execution, so we need to reset it in each iteration
                    if Graph.ColorMap == "":
                        self.cm = 'jet'
                    else:
                        self.cm = Graph.ColorMap

                    if Graph.NotAvailBin == True:
                        #self.cm = matplotlib.colors.ListedColormap(['#000000','#000080','#0000F3','#004DFF','#00B3FF','#29FFCE','#7BFF7B','#CEFF29','#FFC600','#FF6800','#F30900'])
                        mycmap = plt.get_cmap(self.cm,percentile_len)
                        colorlist = []
                        colorlist.append(Graph.NotAvailColour) #Add colour for NA bin
                        if self.cm=='jet': #Default color map
                            for i in range(mycmap.N-1):
                                colorlist.append(mycmap(i)[:3]) # will return rgba, we take only first 3 so we get rgb
                            colorlist.append('#F30900') #Append the red color instead of garnet
                        else:
                            #User defined color map
                            for i in range(mycmap.N):
                                colorlist.append(mycmap(i)[:3]) # will return rgba, we take only first 3 so we get rgb
                        self.cm = matplotlib.colors.ListedColormap(colorlist)
                        norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=self.cm.N)
                    else:
                        norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=235)
                else:
                    if Graph.NotAvailBin == True:
                        #Add the colour for the NA bin
                        ColorList.insert(0,Graph.NotAvailColour) 
                    self.cm = matplotlib.colors.ListedColormap(ColorList)
                    norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=self.cm.N)

                self.myPointPatch = mypatch
                self.myPointColors = np.array(mycolors)
                p = PatchCollection(self.myPointPatch, norm=norm, cmap=plt.get_cmap(self.cm), linewidth=0)       
                p.set_array(self.myPointColors)
                p.set_alpha(0.8)

                if ((self.map_type == 'availability' or self.map_type == 'continuity' or self.map_type == 'continuityMar') and self.contourlines == True):
                    X = np.linspace(self.Xmin,self.Xmax,1+int((self.Xmax-self.Xmin)/self.resolution))
                    Y = np.linspace(self.Ymin,self.Ymax,1+int((self.Ymax-self.Ymin)/self.resolution))
                    Z = np.reshape(mycolors,(len(Y),len(X)))
                    levels = []
                    FilteredContourList = []
                    if (self.map_type == 'continuity'):
                        ContourList = Graph.RiskContourLevels
                    elif (self.map_type == 'continuityMar'):
                        ContourList = Graph.RiskMarContourLevels
                    else:
                        ContourList = Graph.AvailContourLevels

                    for contour in ContourList:
                        indexBin = percentile_bin.index(contour)
                        #With this try/except we filter any contour level whose value is not in any point in the map
                        try:
                            mycolors.index(indexBin)
                            levels.append(indexBin-1)
                            FilteredContourList.append(contour)
                        except:
                            pass                        
                    if levels != []:
                        CS = plt.contour(X, Y, Z, levels=levels,colors='k')
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            CS.levels = ["{0:.1e}".format(i) for i in FilteredContourList]
                        else:
                            CS.levels = ["{0:.1f}".format(i) for i in FilteredContourList]
                        try:
                            plt.clabel(CS,CS.levels,inline=1, fontsize=10,linewidths=3)
                        except:
                            if "got multiple values for" in str(sys.exc_info()[1]):
                                try:
                                    #Some python versions do not accept CS.levels passed as parameter
                                    plt.clabel(CS,inline=1, fontsize=10,linewidths=3)
                                except:
                                    #Some python versions (3.7.1 in Windows) :tbdo not support 'linewidth' parameter
                                    plt.clabel(CS,inline=1, fontsize=10)
                            else:
                                #Some python versions (3.7.1 in Windows) :tbdo not support 'linewidth' parameter
                                plt.clabel(CS,CS.levels,inline=1, fontsize=10)
                ax.add_collection(p)
                cbarTicks = np.linspace(0.5, percentile_len-0.5, percentile_len)
                cbarLabel = []

                #Check if user provided text for the colourbar bin
                if BinTextList == []:
                    if Graph.NotAvailBin == True:
                        InitialPos=1
                    else:
                        InitialPos=0

                    for percent in percentile_bin:
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            if percent == 0:
                                if Graph.BinsEqualCondition == True:
                                    if Graph.NotAvailBin == True:
                                        if Graph.ContRiskAsPercentage == True:
                                            cbarLabel.append('=100')
                                        else:
                                            cbarLabel.append('=0')
                                    else:
                                        if Graph.ContRiskAsPercentage == True:
                                            cbarLabel.append(u'≥100')
                                        else:
                                            cbarLabel.append(u'≤0')
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        cbarLabel.append('>100')
                                    else:
                                        cbarLabel.append('<0')
                            elif percent==-1:
                                cbarLabel.append(Graph.NotAvailText)
                            elif percent==percentile_bin[InitialPos]:
                                if percent >= 1:
                                    if Graph.BinsEqualCondition == True:
                                        if Graph.ContRiskAsPercentage == True:
                                            cbarLabel.append('<0')
                                        else:
                                            cbarLabel.append('>1')
                                    else:
                                        if Graph.NotAvailBin == True:
                                            if Graph.ContRiskAsPercentage == True:
                                                cbarLabel.append('=0')
                                            else:
                                                cbarLabel.append('=1')
                                        else:
                                            if Graph.ContRiskAsPercentage == True:
                                                cbarLabel.append(u'≤0')
                                            else:
                                                cbarLabel.append(u'≥1')
                                elif Graph.BinsEqualCondition == True:
                                    if Graph.ContRiskAsPercentage == True:
                                        if percentile_bin[InitialPos+1]<=1e-5:
                                            cbarLabel.append('<{0:.12g}'.format(100*(1.-percentile_bin[InitialPos+1])))
                                        else:
                                            cbarLabel.append('<{0:.2f}'.format(100*(1.-percentile_bin[InitialPos+1])))
                                    else:
                                        cbarLabel.append('>{0:.1e}'.format(percentile_bin[InitialPos+1]))
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        if percentile_bin[InitialPos+1]<=1e-5:
                                            cbarLabel.append(u'≤{0:.12g}'.format(100*(1.-percentile_bin[InitialPos+1])))
                                        else:
                                            cbarLabel.append(u'≤{0:.2f}'.format(100*(1.-percentile_bin[InitialPos+1])))
                                    else:
                                        cbarLabel.append(u'≥{0:.1e}'.format(percentile_bin[InitialPos+1]))
                            elif percent == 1:
                                if Graph.BinsEqualCondition == True:
                                    if Graph.ContRiskAsPercentage == True:
                                        cbarLabel.append(u'≥0')
                                    else:
                                        cbarLabel.append(u'≤1')
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        cbarLabel.append('>0')
                                    else:
                                        cbarLabel.append('<1')
                            else:
                                if Graph.BinsEqualCondition == True:
                                    if Graph.ContRiskAsPercentage == True:
                                        if percent<=1e-5:
                                            cbarLabel.append(u'≥{0:.12g}'.format(100*(1.-percent)))
                                        else:
                                            cbarLabel.append(u'≥{0:.2f}'.format(100*(1.-percent)))
                                    else:
                                        cbarLabel.append(u'≤{0:.1e}'.format(percent))
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        if percent<=1e-5:
                                            cbarLabel.append('>{0:.12g}'.format(100*(1.-percent)))
                                        else:
                                            cbarLabel.append('>{0:.2f}'.format(100*(1.-percent)))
                                    else:
                                        cbarLabel.append('<{0:.1e}'.format(percent))
                        elif self.map_type == 'HDOP' or self.map_type == 'PDOP' or self.map_type == 'GDOP':
                            if percent==-1:
                                cbarLabel.append(Graph.NotAvailText)
                            elif percent == 0:
                                if Graph.BinsEqualCondition == True:
                                    if Graph.NotAvailBin == True:
                                        cbarLabel.append('=0')
                                    else:
                                        cbarLabel.append(u'≤0')
                                else:
                                    cbarLabel.append('<0')
                            elif percent==percentile_bin[InitialPos]:
                                if Graph.BinsEqualCondition == True:
                                    if percentile_bin[InitialPos+1]>99.9:
                                        cbarLabel.append('>{0:.12g}'.format(percentile_bin[InitialPos+1]))
                                    else:
                                        cbarLabel.append('>{0:.1f}'.format(percentile_bin[InitialPos+1]))
                                else:
                                    cbarLabel.append(u'≥{0:.1f}'.format(percentile_bin[InitialPos+1]))
                            else:
                                if Graph.BinsEqualCondition == True:
                                    if percent>99.9:
                                        cbarLabel.append(u'≤{0:.12g}'.format(percent))
                                    else:
                                        cbarLabel.append(u'≤{0:.1f}'.format(percent))
                                else:
                                    cbarLabel.append('<{0:.1f}'.format(percent))
                        else:
                            if percent<=0:
                                Decimals = 0
                            else:
                                Decimals = 1
                            if percent==100:
                                if Graph.BinsEqualCondition == True:
                                    if Graph.NotAvailBin == True:
                                        cbarLabel.append('=100')
                                    else:
                                        cbarLabel.append(u'≥100')
                                else:
                                    cbarLabel.append('>100')
                            elif percent==-1:
                                cbarLabel.append(Graph.NotAvailText)
                            elif percent==percentile_bin[InitialPos]:
                                if percent == 0:
                                    if Graph.BinsEqualCondition == True:
                                        cbarLabel.append('<0')
                                    else:
                                        if Graph.NotAvailBin == True:
                                            cbarLabel.append('=0')
                                        else:
                                            cbarLabel.append(u'≤0')
                                elif Graph.BinsEqualCondition == True:
                                    if percentile_bin[InitialPos+1]>99.9:
                                        cbarLabel.append('<{0:.12g}'.format(percentile_bin[InitialPos+1]))
                                    else:
                                        cbarLabel.append('<{0:.{1}f}'.format(percentile_bin[InitialPos+1],Decimals))
                                else:
                                    if percentile_bin[InitialPos+1]>99.9:
                                        cbarLabel.append(u'≤{0:.12g}'.format(percentile_bin[InitialPos+1]))
                                    else:
                                        cbarLabel.append(u'≤{0:.{1}f}'.format(percentile_bin[InitialPos+1],Decimals))
                            else:
                                if Graph.BinsEqualCondition == True:
                                    if percent>99.9:
                                        cbarLabel.append(u'≥{0:.12g}'.format(percent))
                                    else:
                                        cbarLabel.append(u'≥{0:.{1}f}'.format(percent,Decimals))
                                else:
                                    if percent>99.9:
                                        cbarLabel.append('>{0:.12g}'.format(percent))
                                    else:
                                        cbarLabel.append('>{0:.{1}f}'.format(percent,Decimals))
                else:
                    cbarLabel = BinTextList
                    if Graph.NotAvailBin == True:
                        cbarLabel.insert(0,Graph.NotAvailText)

                if Graph.WaterMark != "":
                    if Graph.WaterMarkSizeSetbyUser == 0:
                        #For SBAS maps, the default size is 15 instead of 8
                        Graph.WaterMarkSize = 15
                    if Graph.WaterMarkPositionSetbyUser == 1:
                        plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                    else:
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            #Continuity maps need to move watermark a bit to the right to set the watermark in the same position as in other SBAS maps
                            plt.annotate(Graph.WaterMark, xy=(.985,1.1), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                        else:
                            plt.annotate(Graph.WaterMark, xy=(.95,1.1), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)

                if Graph.NumTextMark > 0:
                    for j in range(Graph.NumTextMark):
                        plt.annotate(Graph.TextMark[j], xy=(Graph.TextMarkPositionX[j],Graph.TextMarkPositionY[j]), xycoords='axes fraction', fontsize=Graph.TextMarkSize[j], color=Graph.TextMarkColour[j])
                if Graph.FIRDegradation == True:
                    FIRTitles = []
                    FIRTitlesSizes = []
                    FIRValues=[[]]
                    NumColumns=0

                    if self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                        if Graph.BinsEqualCondition == True:
                           DefaultSymbols = [u'≥',u'<']
                        else:
                           DefaultSymbols = [u'>',u'≤']
                    else:
                        
                        if Graph.BinsEqualCondition == True:
                            if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                               DefaultSymbols = [u'≥',u'<']
                            else:
                               DefaultSymbols = [u'≤',u'>']
                        else:
                            if Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                                DefaultSymbols = [u'>',u'≤']
                            else:
                                DefaultSymbols = [u'<',u'≥']

                    #Print European FIR values
                    if Graph.FIREurope and Graph.FIRShowDegTextEur == True:
                        if Graph.FIRDegTextHeaderEur == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = u"Europe\n"
                            FIRTitles.append(u"Europe")
                        elif Graph.FIRDegTextHeaderEur == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderEur + "\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderEur)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextEur == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(len(Graph.FIRDegTextBinsEur)):
                            if TotalPointsInsideRegionEur[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailEur[i])/float(TotalPointsInsideRegionEur[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailEur[i])/float(TotalPointsInsideRegionEur[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsEur[i]<=1e-5:
                                        BinValueText = u"{0:.12g}".format(100*(1.-Graph.FIRDegTextBinsEur[i]))
                                    else:
                                        BinValueText = u"{0:.2f}".format(100*(1.-Graph.FIRDegTextBinsEur[i]))
                                else:
                                    BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBinsEur[i])
                            else:
                                if Graph.FIRDegTextBinsEur[i]>99.9:
                                    BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBinsEur[i])
                                else:
                                    BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBinsEur[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u" ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextEur.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsEur[i],TotalPointsInsideAvailEur[i],TotalPointsInsideNoAvailEur[i],TotalPointsInsideRegionEur[i],TotalNumPointsWholePlot) 
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: European FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextEur,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + u" " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)
    
                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterEur != "":
                                FirDegText+=Graph.FIRDegTextFooterEur

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXEur,Graph.FIRDegTextPositionYEur),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeEur,color=Graph.FIRDegTextColorEur,family=Graph.FIRDegTextFontFamily)
                    #Print CONUS FIR values
                    if Graph.FIRCONUS and Graph.FIRShowDegTextCONUS == True:
                        if Graph.FIRDegTextHeaderCONUS == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = u"CONUS\n"
                            FIRTitles.append(u"CONUS")
                        elif Graph.FIRDegTextHeaderCONUS == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderCONUS + "\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderCONUS)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextCONUS == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(len(Graph.FIRDegTextBinsCONUS)):
                            if TotalPointsInsideRegionCONUS[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailCONUS[i])/float(TotalPointsInsideRegionCONUS[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailCONUS[i])/float(TotalPointsInsideRegionCONUS[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsCONUS[i]<=1e-5:
                                        BinValueText = u"{0:.12g}".format(100*(1.-Graph.FIRDegTextBinsCONUS[i]))
                                    else:
                                        BinValueText = u"{0:.2f}".format(100*(1.-Graph.FIRDegTextBinsCONUS[i]))
                                else:
                                    BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBinsCONUS[i])
                            else:
                                if Graph.FIRDegTextBinsCONUS[i]>99.9:
                                    BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBinsCONUS[i])
                                else:
                                    BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBinsCONUS[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u" ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextCONUS.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsCONUS[i],TotalPointsInsideAvailCONUS[i],TotalPointsInsideNoAvailCONUS[i],TotalPointsInsideRegionCONUS[i],TotalNumPointsWholePlot)
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: CONUS FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextCONUS,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + u" " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)

                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterCONUS != "":
                                FirDegText+=Graph.FIRDegTextFooterCONUS

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXCONUS,Graph.FIRDegTextPositionYCONUS),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeCONUS,color=Graph.FIRDegTextColorCONUS,family=Graph.FIRDegTextFontFamily)
                    #Print Alaska FIR values
                    if Graph.FIRAlaska and Graph.FIRShowDegTextAlaska == True:
                        if Graph.FIRDegTextHeaderAlaska == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = u"Alaska\n"
                            FIRTitles.append(u"Alaska")
                        elif Graph.FIRDegTextHeaderAlaska == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderAlaska + "\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderAlaska)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextAlaska == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(len(Graph.FIRDegTextBinsAlaska)):
                            if TotalPointsInsideRegionAlaska[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailAlaska[i])/float(TotalPointsInsideRegionAlaska[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailAlaska[i])/float(TotalPointsInsideRegionAlaska[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsAlaska[i]<=1e-5:
                                        BinValueText = u"{0:.12g}".format(100*(1.-Graph.FIRDegTextBinsAlaska[i]))
                                    else:
                                        BinValueText = u"{0:.2f}".format(100*(1.-Graph.FIRDegTextBinsAlaska[i]))
                                else:
                                    BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBinsAlaska[i])
                            else:
                                if Graph.FIRDegTextBinsAlaska[i]>99.9:
                                    BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBinsAlaska[i])
                                else:
                                    BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBinsAlaska[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u" ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextAlaska.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsAlaska[i],TotalPointsInsideAvailAlaska[i],TotalPointsInsideNoAvailAlaska[i],TotalPointsInsideRegionAlaska[i],TotalNumPointsWholePlot)
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: Alaska FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextAlaska,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + u" " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)

                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterAlaska != "":
                                FirDegText+=Graph.FIRDegTextFooterAlaska

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXAlaska,Graph.FIRDegTextPositionYAlaska),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeAlaska,color=Graph.FIRDegTextColorAlaska,family=Graph.FIRDegTextFontFamily)
                    #Print Canada FIR values
                    if Graph.FIRCanada and Graph.FIRShowDegTextCanada == True:
                        if Graph.FIRDegTextHeaderCanada == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = "Canada\n"
                            FIRTitles.append("Canada")
                        elif Graph.FIRDegTextHeaderCanada == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderCanada + "\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderCanada)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextCanada == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(len(Graph.FIRDegTextBinsCanada)):
                            if TotalPointsInsideRegionCanada[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailCanada[i])/float(TotalPointsInsideRegionCanada[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailCanada[i])/float(TotalPointsInsideRegionCanada[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsCanada[i]<=1e-5:
                                        BinValueText = "{0:.12g}".format(100*(1.-Graph.FIRDegTextBinsCanada[i]))
                                    else:
                                        BinValueText = "{0:.2f}".format(100*(1.-Graph.FIRDegTextBinsCanada[i]))
                                else:
                                    BinValueText = "{0:.1e}".format(Graph.FIRDegTextBinsCanada[i])
                            else:
                                if Graph.FIRDegTextBinsCanada[i]>99.9:
                                    BinValueText = "{0:.12g}".format(Graph.FIRDegTextBinsCanada[i])
                                else:
                                    BinValueText = "{0:.1f}".format(Graph.FIRDegTextBinsCanada[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + ": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + ": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + ": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + ": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + "\n"
                                    TmpText=TmpText.replace("\n"," ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextCanada.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsCanada[i],TotalPointsInsideAvailCanada[i],TotalPointsInsideNoAvailCanada[i],TotalPointsInsideRegionCanada[i],TotalNumPointsWholePlot)
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: Canada FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextCanada,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + "\n"
                                    TmpText=TmpText.replace("\n","\n" + FIRTitles[NumColumns] + " ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + " " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + " " + TmpText + "\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)

                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterCanada != "":
                                FirDegText+=Graph.FIRDegTextFooterCanada

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXCanada,Graph.FIRDegTextPositionYCanada),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeCanada,color=Graph.FIRDegTextColorCanada,family=Graph.FIRDegTextFontFamily)
                    #Print Mexico FIR values
                    if Graph.FIRMexico and Graph.FIRShowDegTextMexico == True:
                        if Graph.FIRDegTextHeaderMexico == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = u"Mexico\n"
                            FIRTitles.append(u"Mexico")
                        elif Graph.FIRDegTextHeaderMexico == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderMexico + u"\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderMexico)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextMexico == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(len(Graph.FIRDegTextBinsMexico)):
                            if TotalPointsInsideRegionMexico[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailMexico[i])/float(TotalPointsInsideRegionMexico[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailMexico[i])/float(TotalPointsInsideRegionMexico[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsMexico[i]<=1e-5:
                                        BinValueText = u"{0:.12g}".format(100*(1-Graph.FIRDegTextBinsMexico[i]))
                                    else:
                                        BinValueText = u"{0:.2f}".format(100*(1-Graph.FIRDegTextBinsMexico[i]))
                                else:
                                    BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBinsMexico[i])
                            else:
                                if Graph.FIRDegTextBinsMexico[i]>99.9:
                                    BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBinsMexico[i])
                                else:
                                    BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBinsMexico[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u" ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextMexico.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsMexico[i],TotalPointsInsideAvailMexico[i],TotalPointsInsideNoAvailMexico[i],TotalPointsInsideRegionMexico[i],TotalNumPointsWholePlot)
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: Mexico FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextMexico,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + u" " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)

                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterMexico != "":
                                FirDegText+=Graph.FIRDegTextFooterMexico

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXMexico,Graph.FIRDegTextPositionYMexico),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeMexico,color=Graph.FIRDegTextColorMexico,family=Graph.FIRDegTextFontFamily)
                    #Print user FIR values
                    if Graph.FIRNumUserFile >0:
                        for i in range(Graph.FIRNumUserFile):
                            if Graph.FIRShowDegText[i] == False:
                                continue

                            if Graph.FIRDegTextHeader[i] == "]]]]]]]]][[[[[[[[[[[":
                                FileName=os.path.basename(Graph.FIRUserFile[i])
                                FileName=os.path.splitext(FileName)[0]
                                FirDegText = FileName + u"\n"
                                FIRTitles.append(FileName)
                            elif Graph.FIRDegTextHeader[i] == "":
                                FirDegText = ""
                                FIRTitles.append("")
                            else:
                                FirDegText = Graph.FIRDegTextHeader[i] + u"\n"
                                FIRTitles.append(Graph.FIRDegTextHeader[i])

                            FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                            if Graph.FIRDegText[i] == "":
                                UserDegText = False
                            else:
                                UserDegText = True


                            for j in range(len(Graph.FIRDegTextBins[i])):
                                if TotalPointsInsideRegion[i][j]==0:
                                    PercentAvail=0.
                                    PercentNoAvail=100.
                                else:
                                    PercentAvail=100.*float(TotalPointsInsideAvail[i][j])/float(TotalPointsInsideRegion[i][j])
                                    PercentNoAvail=100.*float(TotalPointsInsideNoAvail[i][j])/float(TotalPointsInsideRegion[i][j])
                                if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                    if Graph.ContRiskAsPercentage == True:
                                        if Graph.FIRDegTextBins[i][j]<=1e-5:
                                            BinValueText = u"{0:.12g}".format(100*(1.-Graph.FIRDegTextBins[i][j]))
                                        else:
                                            BinValueText = u"{0:.2f}".format(100*(1.-Graph.FIRDegTextBins[i][j]))
                                    else:
                                        BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBins[i][j])
                                else:
                                    if Graph.FIRDegTextBins[i][j]>99.9:
                                        BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBins[i][j])
                                    else:
                                        BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBins[i][j])

                                if Graph.FIRDegTextTable == False:
                                    if UserDegText == False:
                                        #No text provided, set the default value
                                        if PercentAvail == 100. or PercentNoAvail == 100.:
                                            TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                        else:
                                            TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                        FirDegText+=TmpText + u"\n"
                                        TmpText=TmpText.replace(u"\n",u" ",1)
                                    else:
                                        try:
                                            TmpText=Graph.FIRDegText[i].format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBins[i][j],TotalPointsInsideAvail[i][j],TotalPointsInsideNoAvail[i][j],TotalPointsInsideRegion[i][j],TotalNumPointsWholePlot)
                                        except:
                                            Errmsg=str(sys.exc_info()[1])
                                            print ("ERROR: FIR Degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegText[i],Errmsg.replace("u'","").replace("'",""))
                                            removeLockFile()
                                            sys.exit()

                                        FirDegText+=TmpText + u"\n"
                                        TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                    if Graph.FIRPrintDegText == True:
                                        print(FIRTitles[NumColumns] + u" " + TmpText)

                                    if (Graph.FIROutputFileNameDegText != ""):
                                        FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                                else:
                                    FIRValues.append([])
                                    FIRValues[NumColumns].append(PercentAvail)
                                    
                            NumColumns+=1

                            if Graph.FIRDegTextTable == False:
                                if Graph.FIRDegTextFooter[i] != "":
                                    FirDegText+=Graph.FIRDegTextFooter[i]

                                plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionX[i],Graph.FIRDegTextPositionY[i]),xycoords='axes fraction',fontsize=Graph.FIRDegTextSize[i],color=Graph.FIRDegTextColor[i],family=Graph.FIRDegTextFontFamily)
                    #Print FIR sum values
                    if Graph.FIRSum == True:
                        if Graph.FIRDegTextHeaderFIRSum == "]]]]]]]]][[[[[[[[[[[":
                            FirDegText = u"All FIR\n"
                            FIRTitles.append(u"All FIR")
                        elif Graph.FIRDegTextHeaderFIRSum == "":
                            FirDegText = ""
                            FIRTitles.append("")
                        else:
                            FirDegText = Graph.FIRDegTextHeaderFIRSum + u"\n"
                            FIRTitles.append(Graph.FIRDegTextHeaderFIRSum)

                        FIRTitlesSizes.append(len(FIRTitles[NumColumns]))
                        if Graph.FIRDegTextFIRSum == "":
                            UserDegText = False
                        else:
                            UserDegText = True

                        for i in range(Graph.FIRNumDegTextBinsFIRSum):
                            if TotalPointsInsideRegionFIRSum[i]==0:
                                PercentAvail=0.
                                PercentNoAvail=100.
                            else:
                                PercentAvail=100.*float(TotalPointsInsideAvailFIRSum[i])/float(TotalPointsInsideRegionFIRSum[i])
                                PercentNoAvail=100.*float(TotalPointsInsideNoAvailFIRSum[i])/float(TotalPointsInsideRegionFIRSum[i])
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.ContRiskAsPercentage == True:
                                    if Graph.FIRDegTextBinsFIRSum[i]<=1e-5:
                                        BinValueText = u"{0:.12g}".format(100*(1-Graph.FIRDegTextBinsFIRSum[i]))
                                    else:
                                        BinValueText = u"{0:.2f}".format(100*(1-Graph.FIRDegTextBinsFIRSum[i]))
                                else:
                                    BinValueText = u"{0:.1e}".format(Graph.FIRDegTextBinsFIRSum[i])
                            else:
                                if Graph.FIRDegTextBinsFIRSum[i]>99.9:
                                    BinValueText = u"{0:.12g}".format(Graph.FIRDegTextBinsFIRSum[i])
                                else:
                                    BinValueText = u"{0:.1f}".format(Graph.FIRDegTextBinsFIRSum[i])

                            if Graph.FIRDegTextTable == False:
                                if UserDegText == False:
                                    if PercentAvail == 100. or PercentNoAvail == 100.:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.0f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.0f}%".format(PercentNoAvail)
                                    else:
                                        TmpText = DefaultSymbols[0] + BinValueText + u": {0:.2f}%\n".format(PercentAvail) + DefaultSymbols[1] + BinValueText + u": {0:.2f}%".format(PercentNoAvail)
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u" ",1)
                                else:
                                    try:
                                        TmpText=Graph.FIRDegTextFIRSum.format(PercentAvail,PercentNoAvail,Graph.FIRDegTextBinsFIRSum[i],TotalPointsInsideAvailFIRSum[i],TotalPointsInsideNoAvailFIRSum[i],TotalPointsInsideRegionFIRSum[i],TotalNumPointsWholePlot)
                                    except:
                                        Errmsg=str(sys.exc_info()[1])
                                        print ("ERROR: FIR sum degradation text '{0:s}' contains the following invalid format: '{1:s}'").format(Graph.FIRDegTextFIRSum,Errmsg.replace("u'","").replace("'",""))
                                        removeLockFile()
                                        sys.exit()
                                        
                                    FirDegText+=TmpText + u"\n"
                                    TmpText=TmpText.replace(u"\n",u"\n" + FIRTitles[NumColumns] + u" ")

                                if Graph.FIRPrintDegText == True:
                                    print(FIRTitles[NumColumns] + u" " + TmpText)

                                if (Graph.FIROutputFileNameDegText != ""):
                                    FIROutputFileDescriptorDegText.write(FIRTitles[NumColumns] + u" " + TmpText + u"\n")
                            else:
                                FIRValues.append([])
                                FIRValues[NumColumns].append(PercentAvail)

                        NumColumns+=1

                        if Graph.FIRDegTextTable == False:
                            if Graph.FIRDegTextFooterFIRSum != "":
                                FirDegText+=Graph.FIRDegTextFooterFIRSum

                            plt.annotate(FirDegText,xy=(Graph.FIRDegTextPositionXFIRSum,Graph.FIRDegTextPositionYFIRSum),xycoords='axes fraction',fontsize = Graph.FIRDegTextSizeFIRSum,color=Graph.FIRDegTextColorFIRSum,family=Graph.FIRDegTextFontFamily)

                    #Print values in table format
                    if Graph.FIRDegTextTable == True:
                        #NOTE: All strings must be in unicode so there is no problem when printing to file 
                        #(if there is no unicode character, the write to file fails)
                        TableData=u""
                        #Print first line of header
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            if Graph.ContRiskAsPercentage == True:
                                if NumDecimalsMargin>8:
                                    NumDigitsTable=NumDecimalsMargin+1 
                                else:
                                    NumDigitsTable=9
                            else:
                                NumDigitsTable=9

                            FirstItem=u"{0:<{1}s}".format("Continuity",NumDigitsTable+2) #The +2 is for the "<" symbol + the space at the end
                        elif self.map_type == 'HDOP':
                            FirstItem=u"{0:<10s}".format("HDOP")
                        elif self.map_type == 'PDOP':
                            FirstItem=u"{0:<10s}".format("PDOP")
                        elif self.map_type == 'GDOP':
                            FirstItem=u"{0:<10s}".format("GDOP")
                        else:
                            if NumDecimalsMargin>3:
                                NumDigitsTable=NumDecimalsMargin+3 #The +3 is for the first two digits plus the decimal point
                            else:
                                NumDigitsTable=6

                            if NumDigitsTable>=11:
                                FirstItem=u"{0:<{1}s}".format("Availability",NumDigitsTable+2) #The +2 is for the ">" symbol + the space at the end
                            else:
                                FirstItem=u"{0:<{1}s}".format("Avail.",NumDigitsTable+2) #The +2 is for the ">" symbol + the space at the end

                        TableData+=FirstItem

                        for i in range(NumColumns):
                            if FIRTitlesSizes[i]<8: #8 characters is the minumum size to fit "Coverage" word
                                FIRTitlesSizes[i]=8

                            if i==0:
                                TableData+=u"| "+ "{1:<{0}s}".format(FIRTitlesSizes[i],FIRTitles[i])
                            else:
                                TableData+=u" | "+ "{1:<{0}s}".format(FIRTitlesSizes[i],FIRTitles[i])

                        LengthFirstLine=len(TableData)
                        TableData+="\n"

                        #Print second line of header
                        if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                            if Graph.ContRiskAsPercentage == True:
                                TmpStr=u"{0:<{1}s}".format("Percentage",NumDigitsTable+2)
                            else:
                                TmpStr=u"{0:<{1}s}".format("Risk",NumDigitsTable+2)
                            TableData+=TmpStr
                            LengthSecondLine=len(TmpStr)
                        elif self.map_type == 'HDOP' or self.map_type == 'PDOP' or self.map_type == 'GDOP':
                            TmpStr=u"{0:<10s}".format("Threshold")
                            TableData+=TmpStr
                            LengthSecondLine=len(TmpStr)
                        else:
                            TmpStr=u"{0:<{1}s}".format("Percent",NumDigitsTable+2)
                            TableData+=TmpStr
                            LengthSecondLine=len(TmpStr)

                        ColLenghts = []
                        for i in range(NumColumns):
                            if i==0:
                                TmpStr=u"| "+ u"{1:<{0}s}".format(FIRTitlesSizes[i],"Coverage")
                            else:
                                TmpStr=u" | "+ u"{1:<{0}s}".format(FIRTitlesSizes[i],"Coverage")
                            TableData+=TmpStr
                            LengthSecondLine+=len(TmpStr)

                        TableData+=u"\n"


                        #Print dashed line to separate header
                        for i in range(max(LengthFirstLine,LengthSecondLine)):
                            TableData+=u"-"

                        TableData+=u"\n"

                        #Add rows with values
                        NumDegTextBins=len(Graph.FIRDegTextBins[0])
                        for i in range(NumDegTextBins):
                            UseEqual = 0
                            if self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.FIRDegTextBins[0][i] == 1:
                                    if Graph.ContRiskAsPercentage == True:
                                        BinValueText = u"{0:<{1}.0f}".format(100*(1-Graph.FIRDegTextBins[0][i]),NumDigitsTable+1)
                                    else:
                                        BinValueText = u"{0:<{1}.0f}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                elif Graph.FIRDegTextBins[0][i] == 0:
                                    if Graph.ContRiskAsPercentage == True:
                                        BinValueText = u"{0:<{1}.0f}".format(100*(1-Graph.FIRDegTextBins[0][i]),NumDigitsTable+1)
                                    else:
                                        BinValueText = u"{0:<{1}.0f}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                    if Graph.BinsEqualCondition == True and Graph.NotAvailBin == True:
                                        UseEqual = 1                                    
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        if Graph.FIRDegTextBins[0][i]<=1e-5:
                                            BinValueText = u"{0:<{1}.14g}".format(100*(1-Graph.FIRDegTextBins[0][i]),NumDigitsTable+1)
                                        else:
                                            BinValueText = u"{0:<{1}.2f}".format(100*(1-Graph.FIRDegTextBins[0][i]),NumDigitsTable+1)
                                    else:
                                        BinValueText = u"{0:<{1}.1e}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                    NumDecimals = 2
                            elif self.map_type == 'HDOP' or self.map_type == 'PDOP' or self.map_type == 'GDOP':
                                if Graph.FIRDegTextBins[0][i] == 0:
                                    BinValueText = u"{0:<9.0f}".format(Graph.FIRDegTextBins[0][i])
                                    if Graph.BinsEqualCondition == True and Graph.NotAvailBin == True:
                                        UseEqual = 1
                                else:
                                    BinValueText = u"{0:<9.1f}".format(Graph.FIRDegTextBins[0][i])
                            else:
                                if Graph.FIRDegTextBins[0][i] == 100:
                                    BinValueText = u"{0:<{1}.0f}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                    if Graph.BinsEqualCondition == True and Graph.NotAvailBin == True:
                                        UseEqual = 1                                    
                                elif  Graph.FIRDegTextBins[0][i] == 0:
                                    BinValueText = u"{0:<{1}.0f}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                else:
                                    if Graph.FIRDegTextBins[0][i]>99.9:
                                        BinValueText = u"{0:<{1}.14g}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)
                                    else:
                                        BinValueText = u"{0:<{1}.1f}".format(Graph.FIRDegTextBins[0][i],NumDigitsTable+1)

                            if UseEqual == 1:
                                TableData+=u'=' + BinValueText
                            elif self.map_type == 'availability' or self.map_type == 'ionoCorrection':
                                if Graph.BinsEqualCondition == True:
                                    TableData+=u'≥' + BinValueText
                                else:
                                    TableData+=u'>' + BinValueText
                            elif self.map_type == 'continuity' or self.map_type == 'continuityMar':
                                if Graph.BinsEqualCondition == True:
                                    if Graph.ContRiskAsPercentage == True:
                                        TableData+=u'≥' + BinValueText
                                    else:
                                        TableData+=u'≤' + BinValueText
                                else:
                                    if Graph.ContRiskAsPercentage == True:
                                        TableData+=u'>' + BinValueText
                                    else:
                                        TableData+=u'<' + BinValueText
                            else:
                                if Graph.BinsEqualCondition == True:
                                    TableData+=u'≤' + BinValueText
                                else:
                                    TableData+=u'<' + BinValueText

                            
                            for j in range(NumColumns):
                                if FIRValues[j][i]==100 or FIRValues[j][i] == 0:
                                    NumDecimals = 0
                                else:
                                    NumDecimals= 2
                                if j==0:
                                    TmpStr=u" {0:.{1}f}%".format(FIRValues[j][i],NumDecimals)
                                    TableData+=u"| {1:<{0}s}".format(FIRTitlesSizes[j],TmpStr)
                                else:
                                    TmpStr=u" {0:.{1}f}%".format(FIRValues[j][i],NumDecimals)
                                    TableData+=u" | {1:<{0}s}".format(FIRTitlesSizes[j],TmpStr)

                            if i!=(NumDegTextBins-1):
                                TableData+=u"\n"

                    
                        if NumColumns>0:
                            plt.annotate(TableData,xy=(Graph.FIRDegTextPositionX[0],Graph.FIRDegTextPositionY[0]),xycoords='axes fraction',fontsize=Graph.FIRDegTextSize[0],color=Graph.FIRDegTextColor[0],family='monospace')

                            if Graph.FIRPrintDegText == True:
                                print(TableData)

                            if (Graph.FIROutputFileNameDegText != ""):
                                FIROutputFileDescriptorDegText.write(TableData + u"\n")

                ax = plt.gca()
                #im = ax.imshow(np.arange(100).reshape((10,10)))

                divider = make_axes_locatable(ax)
                cax = divider.append_axes("right", size=0.2, pad=0.05)
                pCbar = plt.colorbar(mappable=p, cax=cax, ticks=cbarTicks)

                pCbar.ax.set_yticklabels(cbarLabel) 
                if (self.Cbarlabel != ""):
                    pCbar.ax.set_ylabel(self.Cbarlabel)

                if ColorBarTitle != "":
                    pCbar.ax.set_title(ColorBarTitle)
                elif Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True:
                    if (self.map_type == 'availability' or self.map_type == 'ionoCorrection'):
                        if Graph.BinsEqualCondition == True: 
                            if BinLastValue == 100.:
                                pCbar.ax.set_title(u"         ≥{0:3.0f}%".format(BinLastValue))
                            elif BinLastValue>99.9: 
                                pCbar.ax.set_title(u"             ≥{0:.12g}%".format(BinLastValue))
                            else:
                                pCbar.ax.set_title(u"          ≥{0:.1f}%".format(BinLastValue))
                        else:
                            if BinLastValue == 100.:
                                pCbar.ax.set_title(u"         ≥{0:3.0f}%".format(BinLastValue))
                            elif BinLastValue>99.9: 
                                pCbar.ax.set_title(u"             ≥{0:.12g}%".format(BinLastValue))
                            else:
                                pCbar.ax.set_title("          >{0:.1f}%".format(BinLastValue))
                    elif self.map_type == 'continuity' or self.map_type == 'continuityMar':
                        if Graph.ContRiskAsPercentage == True:
                            if Graph.BinsEqualCondition == True: 
                                if (100*(1-BinLastValue))>99.99:
                                    pCbar.ax.set_title(u"             ≥{0:.12g}%".format(100*(1-BinLastValue)))
                                else:
                                    pCbar.ax.set_title(u"           ≥{0:.2f}%".format(100*(1-BinLastValue)))
                            else:
                                if (100*(1-BinLastValue))>99.99:
                                    pCbar.ax.set_title("           >{0:.12g}%".format(100*(1-BinLastValue)))
                                else:
                                    pCbar.ax.set_title("           >{0:.2f}%".format(100*(1-BinLastValue)))
                        else:
                            if Graph.BinsEqualCondition == True:
                                pCbar.ax.set_title(u"           ≤{0:.1e}".format(BinLastValue))
                            else:
                                pCbar.ax.set_title("           <{0:.1e}".format(BinLastValue))

                    else:
                        if Graph.BinsEqualCondition == True:
                            pCbar.ax.set_title(u"  ≤{0:.0f}".format(BinLastValue))
                        else:
                            pCbar.ax.set_title("  <{0:.0f}".format(BinLastValue))
                elif Graph.ContRiskAsPercentage == True and (self.map_type == 'continuity' or self.map_type == 'continuityMar'):
                    if Graph.CbarPercentage == True:
                        pCbar.ax.set_title('%')
                else:
                    if (self.map_type == 'availability' or self.map_type == 'ionoCorrection'):
                        if (Graph.CbarPercentage == True):
                            pCbar.ax.set_title('%')

                if (self.SaveFigure == True): 
                    try:
                        if(len(self.SaveFigurePath)>=idx_sv+1):
                            plt.savefig(self.SaveFigurePath[idx_sv])
                    except:
                        Errmsg=str(sys.exc_info()[1]).split('"')
                        if "rgba" in str(sys.exc_info()[1]):
                            print ("ERROR: User defined colour '{0:s}' is not a valid colour".format(Errmsg[1]))
                        else:
                            print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                        removeLockFile()
                        sys.exit()

                    idx_sv+=1

        #As more than one plot is computed, the plt.show has to be done when all plots are done
        if (self.SaveFigure == False): 
            if Graph.FIROnlyPrintDegText == False:
                plt.show()

        return self
##########################################################################
# Name        : Parse
# Description : This function reads from the command line all the 
#               options, and assigns them into the variables.
##########################################################################  
def Parse(value):
    auxValue=""
    mode=0
    try:
        number = str(int(value)-1)
        auxValue = "var["+number+"]"
    except:
        for element in value:
            if (mode==1):
                try:
                    number = str(int(element))
                    #auxValue=auxValue+number
                    n=n+number
                except:
                    mode=0
                    auxValue=auxValue+str(int(n)-1)+"]"
                    #auxValue=auxValue+"]"
            if (mode==0):
                if (element=="$"):
                    auxValue=auxValue+"var["
                    mode=1
                    n=""
                else:
                    auxValue=auxValue+element
        if (mode==1):
            auxValue=auxValue+str(int(n)-1)+"]"
    return auxValue

##########################################################################
# Name        : ParseCallback
# Description : When a new option for the graphic is introduced, this 
#               callback is called for storing the new parameter
##########################################################################   
def ParseCallback(option, opt_str, value, parser, Graph):

    if (option.dest=="Title"):
        if PythonVersion == 2:
            Graph.Title = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Title = value

    elif (option.dest=="FractionalTitle"):
        if PythonVersion == 2:
            Graph.FractionalTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FractionalTitle = value

    elif (option.dest=="Xlabel"):
        if PythonVersion == 2:
            Graph.Xlabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Xlabel = value

    elif (option.dest=="Ylabel"):
        if PythonVersion == 2:
            Graph.Ylabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Ylabel = value

    elif (option.dest=="filename"):
        Graph.PlotCounter += 1
        Graph.PlotList.append(Plot())
        if PythonVersion == 2:
            Graph.PlotList[Graph.PlotCounter-1].FileName = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.PlotList[Graph.PlotCounter-1].FileName = value

    elif (option.dest=="ColX"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].ColX = value
        Graph.ColXUser = True

    elif (option.dest=="ColY"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].ColY = value
        Graph.ColYUser = True


    elif (option.dest=="Cond"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].Cond = value

    elif (option.dest=="PlotLabel"):
        global legend
        legend=True 
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        if PythonVersion == 2:
            Graph.PlotList[Graph.PlotCounter-1].Label = unicode(value, "utf-8", errors="ignore")        
        else:
            Graph.PlotList[Graph.PlotCounter-1].Label = value

    elif (option.dest=="Style"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()

        Graph.PlotList[Graph.PlotCounter-1].Style = value

        if (value.count('-')!= 0): 
            Graph.PlotList[Graph.PlotCounter-1].LineWidth = 1.0

    elif (option.dest=="MarkerSize"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        try:
            Graph.PlotList[Graph.PlotCounter-1].MarkerSize = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for line marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="LineWidth"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        try:
            Graph.PlotList[Graph.PlotCounter-1].LineWidth = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for line width".format(value))
            removeLockFile()
            sys.exit()


    elif (option.dest=="grid"):
        if (value == "off" or value == "no" ): Graph.grid = False   

    elif (option.dest=="Xmin"):
        if (str(value) == '*' or value == "auto" ): 
            Graph.XminAuto = True
        else:
            Graph.XminAuto = False
            try:
                Graph.Xmin = float(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for X min".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="Xmax"):
        if (str(value) == '*' or value == "auto" ): Graph.XmaxAuto = True
        else:
            Graph.XmaxAuto = False
            try:
                Graph.Xmax = float(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for X max".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="Ymin"):
        if (str(value) == '*' or value == "auto" ): Graph.YminAuto = True
        else:        
            Graph.YminAuto = False
            try:
                Graph.Ymin = float(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for Y min".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="Ymax"):
        if (str(value) == '*' or value == "auto" ): Graph.YmaxAuto = True
        else:
            Graph.YmaxAuto = False
            try:
                Graph.Ymax = float(value)
            except:
                print( "ERROR: Invalid value '{0:s}' for Y max".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="NumPointsLabel"):
        Graph.NumPointsLabelUser = True
        try:
            Graph.NumPointsLabel = int(value)
            if (Graph.NumPointsLabel<1 or Graph.NumPointsLabel > 10):
                print ("ERROR: Number of points in label should be between 1 and 10 (provided value is '{0:s}')".format(value))
                removeLockFile()
                sys.exit()
        except:
            print ("ERROR: Invalid value '{0:s}' for number of points in label".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="LabelPosition"):
        if (str(value) == "tl" ):
            Graph.LabelPosition = 2
        elif (str(value) == "tc" ):
            Graph.LabelPosition = 9
        elif (str(value) == "tr" ):
            Graph.LabelPosition = 1
        elif (str(value) == "bl" ):
            Graph.LabelPosition = 3
        elif (str(value) == "bc" ):
            Graph.LabelPosition = 8
        elif (str(value) == "br" ):
            Graph.LabelPosition = 4
        elif (str(value) == "cl" ):
            Graph.LabelPosition = 6
        elif (str(value) == "c" ):
            Graph.LabelPosition = 10
        elif (str(value) == "cr" ):
            Graph.LabelPosition = 7
        else:
            Graph.LabelPosition = 11
            values = value.split(",")
            if (len(values) != 2):
                print ("ERROR: '{0:s}' is not a valid label position. An example of valid label position is '0.5,0.5'".format(value))
                removeLockFile()
                sys.exit()
            try:
                Graph.LabelPositionX = float(values[0])
            except:
                Graph.LabelPositionX = -1
                print ("ERROR: Invalid value '{0:s}' for X label position".format(values[0]))
                removeLockFile()
                sys.exit()

            if (Graph.LabelPositionX < -0.05 or Graph.LabelPositionX > 1.3):
                print ("ERROR: Position X for label must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
                removeLockFile()
                sys.exit()
            try:
                Graph.LabelPositionY = float(values[1])
            except:
                Graph.LabelPositionY = -1
                print ("ERROR: Invalid value '{0:s}' for Y label position".format(values[1]))
                removeLockFile()
                sys.exit()

            if (Graph.LabelPositionY < -0.05 or Graph.LabelPositionY > 1.2):
                print ("ERROR: Position Y for label must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
                removeLockFile()
                sys.exit()

    elif (option.dest=="PlotColor"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        Graph.PlotList[Graph.PlotCounter-1].PlotColorAuto = False
        Graph.PlotList[Graph.PlotCounter-1].PlotColor = value

    elif (option.dest=="SaveFigure"):
        Graph.SaveFigure = True 
        if PythonVersion == 2:
            Graph.SaveFigurePath.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.SaveFigurePath.append(str(value))

    elif (option.dest=="AL"):
        if (str(value) == '*' or value == "auto" ): Graph.ALAuto = True
        else:
            Graph.ALAuto = False
            try:
                Graph.AL = float(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for Alarm Limit".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="resolution_x"):
        if (str(value) == '*' or value == "auto" ): Graph.intervalNo_x_auto = True
        else:
            Graph.intervalNo_x_auto = False
            try:
                Graph.intervalNo_x = int(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for X resolution".format(value))
                removeLockFile()
                sys.exit()
    elif (option.dest=="resolution_y"):
        if (str(value) == '*' or value == "auto" ): Graph.intervalNo_y_auto = True
        else:
            Graph.intervalNo_y_auto = False
            try:
                Graph.intervalNo_y = int(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for Y resolution".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="percentileXList"):
        Graph.StfdPercentileX = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: List of X percentiles must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                except:
                    print ("ERROR: Invalid value '{0:s}' for X percentiles list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0. or valf>100.:
                    print ("ERROR: X Percentile must be between 0 and 100 (value provided is '{0:s}')".format(val))
                    removeLockFile()
                    sys.exit()
                else:
                    valfloated.append(valf/100.)

            valfloated = sorted(valfloated) #Sorted in ascending order
            Graph.StfdPercentileListX = valfloated 

    elif (option.dest=="percentileYList"):
        Graph.StfdPercentileY = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: List of Y percentiles must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                except:
                    print ("ERROR: Invalid value '{0:s}' for Y percentiles list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0. or valf>100.:
                    print ("ERROR: Y Percentile must be between 0 and 100 (value provided is '{0:s}')".format(val))
                    removeLockFile()
                    sys.exit()
                else:
                    valfloated.append(valf/100.)

            valfloated = sorted(valfloated) #Sorted in ascending order
            Graph.StfdPercentileListY = valfloated 

    elif (option.dest=="AvailEpochPos"):
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: '{0:s}' is not a valid position. An example of valid position is '0.5,0.5'".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.AvailEpochPosX= float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X position for Available Epochs in Stanford/Stanford-ESA plot".format(values[0]))
            removeLockFile()
            sys.exit()

        if (Graph.AvailEpochPosX < -0.05 or Graph.AvailEpochPosX > 1.3):
            print ("ERROR: Position X for Available Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.AvailEpochPosY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y position for Available Epochs in Stanford/Stanford-ESA plot".format(values[1]))
            removeLockFile()
            sys.exit()

        if (Graph.AvailEpochPosY < -0.05 or Graph.AvailEpochPosY > 1.2):
            print ("ERROR: Position Y for Available Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="UnAvailEpochPos"):
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: '{0:s}' is not a valid position. An example of valid position is '0.5,0.5'".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.UnAvailEpochPosX= float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X position for UnAvailable Epochs in Stanford/Stanford-ESA plot".format(values[0]))
            removeLockFile()
            sys.exit()

        if (Graph.UnAvailEpochPosX < -0.05 or Graph.UnAvailEpochPosX > 1.3):
            print ("ERROR: Position X for UnAvailable Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.UnAvailEpochPosY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y position for UnAvailable Epochs in Stanford/Stanford-ESA plot".format(values[1]))
            removeLockFile()
            sys.exit()

        if (Graph.UnAvailEpochPosY < -0.05 or Graph.UnAvailEpochPosY > 1.2):
            print ("ERROR: Position Y for UnAvailable Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="HMIEpochPos"):
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: '{0:s}' is not a valid position. An example of valid position is '0.5,0.5'".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.HMIAvailEpochPosX= float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X position for HMI Epochs in Stanford/Stanford-ESA plot".format(values[0]))
            removeLockFile()
            sys.exit()

        if (Graph.HMIAvailEpochPosX < -0.05 or Graph.HMIAvailEpochPosX > 1.3):
            print ("ERROR: Position X for HMI Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.HMIAvailEpochPosY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y position for HMI Epochs in Stanford/Stanford-ESA plot".format(values[1]))
            removeLockFile()
            sys.exit()

        if (Graph.HMIAvailEpochPosY < -0.05 or Graph.HMIAvailEpochPosY > 1.2):
            print ("ERROR: Position Y for HMI Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="MIAvailEpochPos"):
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: '{0:s}' is not a valid position. An example of valid position is '0.5,0.5'".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.MIAvailEpochPosX= float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X position for MI Available Epochs in Stanford/Stanford-ESA plot".format(values[0]))
            removeLockFile()
            sys.exit()

        if (Graph.MIAvailEpochPosX < -0.05 or Graph.MIAvailEpochPosX > 1.3):
            print ("ERROR: Position X for MI Available Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.MIAvailEpochPosY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y position for MI Available Epochs in Stanford/Stanford-ESA plot".format(values[1]))
            removeLockFile()
            sys.exit()

        if (Graph.MIAvailEpochPosY < -0.05 or Graph.MIAvailEpochPosY > 1.2):
            print ("ERROR: Position Y for MI Available Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="MIUnAvailEpochPos"):
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: '{0:s}' is not a valid position. An example of valid position is '0.5,0.5'".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.MIUnAvailEpochPosX= float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X position for MI Unavailable Epochs in Stanford/Stanford-ESA plot".format(values[0]))
            removeLockFile()
            sys.exit()

        if (Graph.MIUnAvailEpochPosX < -0.05 or Graph.MIUnAvailEpochPosX > 1.3):
            print ("ERROR: Position X for MI Unavailable Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.3 (provided value is '{0:s}')".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.MIUnAvailEpochPosY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y position for MI Unavailable Epochs in Stanford/Stanford-ESA plot".format(values[1]))
            removeLockFile()
            sys.exit()

        if (Graph.MIUnAvailEpochPosY < -0.05 or Graph.MIUnAvailEpochPosY > 1.2):
            print ("ERROR: Position Y for MI Unavailable Epochs in Stanford/Stanford-ESA plot must have values between -0.05 and 1.2 (provided value is '{0:s}')".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="HAL"):
        try:
            Graph.sfESAHAL = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Horizontal Alarm Limit in stanford-ESA plot".format(value))
            removeLockFile()
            sys.exit()

        if Graph.sfESAHAL<=0.:
            print ("ERROR: Horizontal Alarm Limit in stanford-ESA plot must be greater than 0, but user provided '{0:s}'".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="VAL"):
        try:
            Graph.sfESAVAL = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Vertical Alarm Limit in stanford-ESA plot".format(value))
            removeLockFile()
            sys.exit()

        if Graph.sfESAVAL<=0.:
            print ("ERROR: Vertical Alarm Limit in stanford-ESA plot must be greater than 0, but user provided '{0:s}'".format(value))
            removeLockFile()
            sys.exit()


    elif (option.dest=="maxpoints"):
        if (str(value) == '*' or value == "auto" ): Graph.maxpoints_auto = True
        else:
            Graph.maxpoints_auto = False
            try:
                Graph.maxpoints = int(value)
            except:
                print ("ERROR: Invalid value '{0:s}' for maxpoints".format(value))
                removeLockFile()
                sys.exit()

    elif (option.dest=="ColName"):
        value = Parse(value)
        Graph.ColName = value

    elif (option.dest=="ColStaNetwork"):
        value = Parse(value)
        Graph.ColLabelName = value

    elif (option.dest=="ColRatioV"):
        value = Parse(value)
        Graph.ColRatioV = value

    elif (option.dest=="ColRatioH"):
        value = Parse(value)
        Graph.ColRatioH = value

    elif (option.dest=="ColMIsV"):
        value = Parse(value)
        Graph.ColMIsV = value

    elif (option.dest=="ColMIsH"):
        value = Parse(value)
        Graph.ColMIsH = value

    elif (option.dest=="projection"):
        if (value == "lcc" or value == 'lambert'): Graph.projection = "lcc"               

    elif (option.dest=="cbarMin"):
        Graph.cbarAutoMin = False
        try:
            Graph.cbarMin = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for cbarMin".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="cbarMax"):
        Graph.cbarAutoMax = False
        try:
            Graph.cbarMax = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for cbarMax".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="cbarInterval"):
        Graph.cbarAutoN = False
        try:
            Graph.cbarInterval = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for cbarInterval".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="continentColor"):
        Graph.continentColor = value

    elif (option.dest=="lakeColor"):
        Graph.lakeColor = value

    elif (option.dest=="boundaryColor"):
        Graph.boundaryColor = value

    elif (option.dest=="MapResolution"):
        if(value != "c" and value != "l" and value != "i" and value != "h" and value != "f"):
            print ("ERROR: Invalid Map Resolution value '{0:s}'. Valid resolutions are: 'c', 'l', 'i', 'h' or 'f'".format(value))
            removeLockFile()
            sys.exit()
        Graph.MapResolution = value

    elif (option.dest=="WaterMark"):
        if PythonVersion == 2:
            Graph.WaterMark = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.WaterMark = str(value)

    elif (option.dest=="WaterMarkColor"):
        Graph.WaterMarkColour = value

    elif (option.dest=="WaterMarkSize"):
        Graph.WaterMarkSizeSetbyUser = 1
        try:
            Graph.WaterMarkSize = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for watermark size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="WaterMarkPosition"):
        Graph.WaterMarkPositionSetbyUser=1
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: WaterMark position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.WaterMarkPositionX = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for WaterMark X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.WaterMarkPositionY = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for WaterMark Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="TextMarkLabel"):
        Graph.NumTextMark+=1
        if PythonVersion == 2:
            Graph.TextMark.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.TextMark.append(str(value))

    elif (option.dest=="TextMarkColor"):
        Graph.NumTextMarkColour+=1
        Graph.TextMarkColour.append(value)

    elif (option.dest=="TextMarkSize"):
        Graph.NumTextMarkSize+= 1
        try:
            Graph.TextMarkSize.append(float(value))
        except:
            print ("ERROR: Invalid value '{0:s}' for text mark size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="TextMarkPosition"):
        Graph.NumTextMarkPosition+=1
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: Text Mark position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.TextMarkPositionX.append(float(values[0]))
        except:
            print ("ERROR: Invalid value '{0:s}' for Text Mark X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.TextMarkPositionY.append(float(values[1]))
        except:
            print ("ERROR: Invalid value '{0:s}' for Text Mark Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="ColourBarLabel"):
        if PythonVersion == 2:
            Graph.Cbarlabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Cbarlabel = str(value)

    elif (option.dest=="SBASsystemname"):
        if PythonVersion == 2:
            Graph.SBASsystemName = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.SBASsystemName = str(value)

    elif (option.dest=="SBASPRNtext"):
        if PythonVersion == 2:
            Graph.PRNtext = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.PRNtext = str(value)

    elif (option.dest=="Xticks"):
        if (Graph.XTicsListUser == True and Graph.XTicsStep == True):
             print ("ERROR: ' --Xticks', '--XticksStep' and '--XticksList' cannot be all set")
             removeLockFile()
             sys.exit()

        if (Graph.XTicsListUser == True):
            print ("ERROR: '--Xticks' and '--XticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsStep == True):
            print ("ERROR: '--Xticks' and '--XticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.XTicsUser = True
        values = value.split(",")
        if (len(values) != 3):
            print ("ERROR: X tick parameter must be Xmin,Xmax,NumberOfTicks (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsMin = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for X ticks minimum".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsMax = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for X ticks maximum".format(values[1]))
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsNum = int(values[2])
        except:
            print ("ERROR: Invalid value '{0:s}' for X ticks number".format(values[2]))
            removeLockFile()
            sys.exit()
        if (Graph.XTicsMax <= Graph.XTicsMin):
            print ("ERROR: X ticks maximum must be greater than the X ticks minimum")
            removeLockFile()
            sys.exit()

    elif (option.dest=="Yticks"):
        if (Graph.YTicsListUser == True and Graph.YTicsStep == True):
            print ("ERROR: ' --Yticks', '--YticksStep' and '--YticksList' cannot be all set")
            removeLockFile()
            sys.exit()

        if (Graph.YTicsListUser == True):
            print ("ERROR: '--Yticks' and '--YticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.YTicsStep == True):
            print ("ERROR: '--Yticks' and '--YticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsUser = True
        values = value.split(",")
        if (len(values) != 3):
            print ("ERROR: Y tick parameter must be Ymin,Ymax,NumberOfTicks (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsMin = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y ticks minimum".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsMax = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y ticks maximum".format(values[1]))
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsNum = int(values[2])
        except:
            print ("ERROR: Invalid value '{0:s}' for Y ticks number".format(values[2]))
            removeLockFile()
            sys.exit()
        if (Graph.YTicsMax <= Graph.YTicsMin):
            print ("ERROR: Y ticks maximum must be greater than the Y ticks minimum")
            removeLockFile()
            sys.exit()

    elif (option.dest=="XticksStep"):
        if (Graph.XTicsListUser == True and Graph.XTicsUser == True):
            print ("ERROR: ' --XticksStep', '--Xticks' and '--XticksList' cannot be all set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsListUser == True):
            print ("ERROR: '--XticksStep' and '--XticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsUser == True):
            print ("ERROR: '--XticksStep' and '--Xticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.XTicsStepUser = True
        try:
            Graph.XTicsStep = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for X ticks step".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="YticksStep"):
        if (Graph.YTicsListUser == True and Graph.YTicsUser == True):
            print ("ERROR: ' --YticksStep', '--Yticks' and '--YticksList' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsListUser == True):
            print ("ERROR: '--YticksStep' and '--YticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsUser == True):
            print ("ERROR: '--YticksStep' and '--Yticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsStepUser = True
        try:
            Graph.YTicsStep = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Y ticks step".format(value))
            removeLockFile()
            sys.exit()


    elif (option.dest=="XticksList"):
        Graph.XTicksList = [] #For the case the parameter is given more than once
        if (Graph.XTicsStep == True and Graph.XTicsUser == True):
            print ("ERROR: ' --XticksList', '--Xticks' and '--XticksStep' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.XTicsUser == True):
            print ("ERROR: '--XticksList' and '--Xticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.XTicsStepUser == True):
            print ("ERROR: '--XticksList' and '--XticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.XTicsListUser = True
        values = value.split(",")
        if (len(values) <1):
            print ("ERROR: X tick list parameter must be a comma (',') separated list with at least one number (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            for elem in values:
                try:
                    Graph.XTicksList.append(float(elem))
                except:
                    print ("ERROR: Invalid value '{0:s}' for X ticks list".format(elem))
                    removeLockFile()
                    sys.exit()

            Graph.XTicksList = sorted (Graph.XTicksList)

    elif (option.dest=="YticksList"):
        Graph.YTicksList = [] #For the case the parameter is given more than once
        if (Graph.YTicsStep == True and Graph.YTicsUser == True):
            print ("ERROR: ' --YticksList', '--Yticks' and '--YticksStep' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsUser == True):
            print ("ERROR: '--YticksList' and '--Yticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsStepUser == True):
            print ("ERROR: '--YticksList' and '--YticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsListUser = True
        values = value.split(",")
        if (len(values) <1):
            print ("ERROR: Y tick list parameter must be a comma (',') separated list with at least one number (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            for elem in values:
                try:
                    Graph.YTicksList.append(float(elem))
                except:
                    print ("ERROR: Invalid value '{0:s}' for Y ticks list".format(elem))
                    removeLockFile()
                    sys.exit()
            Graph.YTicksList = sorted (Graph.YTicksList)

    elif (option.dest=="ColorMap"):
        Graph.ColorMap = value

    elif (option.dest=="StaNetworkDefaultNameSize"):
        Graph.StaNetWorkWithNames = True
        try:
            Graph.StaNetWorkDefNameSize= float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for station network default name size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="StaNetworkDefaultNameColor"):
        Graph.StaNetWorkWithNames = True
        Graph.StaNetWorkDefNameColor = value

    elif (option.dest=="StaNetworkDefaultNameAlign"):
        Graph.StaNetWorkWithNames = True
        #Alignment is referred where the first or last letter must be to be aligned
        #with the coordinates, not on which side is the text written. We are flipping
        #the values in order to the user decide in what side is the text positioned
        if value[0]=='left':
            Graph.StaNetWorkDefNameHorAlign = 'right'
        elif value[0]=='right':
            Graph.StaNetWorkDefNameHorAlign = 'left'
        else:
            Graph.StaNetWorkDefNameHorAlign = value[0]
        if value[1]== 'top':
            Graph.StaNetWorkDefNameVerAlign = 'bottom'
        elif value[1]== 'bottom':
            Graph.StaNetWorkDefNameVerAlign = 'top'
        else:
            Graph.StaNetWorkDefNameVerAlign = value[1]

    elif (option.dest=="StaNetworkDefaultMarkerType"):
        Graph.StaNetWorkWithMarkers = True
        Graph.StaNetWorkDefMarkerType = value
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Marker '{0:s}' is not supported. Supported markers are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()

    elif (option.dest=="StaNetworkDefaultMarkerSize"):
        Graph.StaNetWorkWithMarkers = True
        try:
            Graph.StaNetWorkDefMarkerSize= float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for station network default marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="StaNetworkDefaultMarkerColor"):
        Graph.StaNetWorkWithMarkers = True
        Graph.StaNetWorkDefMarkerColor = value

    elif (option.dest=="StaNetworkDefaultLabel"):
        Graph.StaNetAddLabel = True
        if PythonVersion == 2:
            Graph.StaNetWorkDefName = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.StaNetWorkDefName = str(value)

    elif (option.dest=="StaNetworkLabel"):
        Graph.StaNetAddLabel = True
        try:
            if PythonVersion == 2:
                pos=Graph.StaLabelListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLabelListValue[pos] = unicode(value[1], "utf-8", errors="ignore")
            else:
                pos=Graph.StaLabelListName.index(str(value[0]))
                Graph.StaLabelListValue[pos] = str(value[1])
        except:
            if PythonVersion == 2:
                Graph.StaLabelListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLabelListValue.append(unicode(value[1], "utf-8", errors="ignore"))
            else:
                Graph.StaLabelListName.append(str(value[0]))
                Graph.StaLabelListValue.append(str(value[1]))

    elif (option.dest=="StaNetworkMarkerType"):
        Graph.StaNetWorkWithMarkers = True
        try:
            if PythonVersion == 2:
                pos=Graph.StaMarkerTypeListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaMarkerTypeListValue[pos] = value[1]
            else:
                pos=Graph.StaMarkerTypeListName.index(str(value[0]))
                Graph.StaMarkerTypeListValue[pos] = value[1]
        except:
            if PythonVersion == 2:
                Graph.StaMarkerTypeListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaMarkerTypeListValue.append(value[1])
            else:
                Graph.StaMarkerTypeListName.append(str(value[0]))
                Graph.StaMarkerTypeListValue.append(value[1])
        try:
            Graph.SupportedStylesCharactersList.index(value[1])
        except:
            print ("ERROR: Marker '{0:s}' is not supported. Supported markers are {1:s}".format(value[1],Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()

    elif (option.dest=="StaNetworkMarkerColor"):
        Graph.StaNetWorkWithMarkers = True
        try:
            if PythonVersion == 2:
                pos=Graph.StaMarkerColorListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaMarkerColorListValue[pos] = value[1]
            else:
                pos=Graph.StaMarkerColorListName.index(str(value[0]))
                Graph.StaMarkerColorListValue[pos] = value[1]
        except:
            if PythonVersion == 2:
                Graph.StaMarkerColorListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaMarkerColorListValue.append(value[1])
            else:
                Graph.StaMarkerColorListName.append(str(value[0]))
                Graph.StaMarkerColorListValue.append(value[1])

    elif (option.dest=="StaNetworkMarkerSize"):
        Graph.StaNetWorkWithMarkers = True
        try:
            pos=-1
            if PythonVersion == 2:
                pos=Graph.StaMarkerSizeListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaMarkerSizeListValue[pos] = float(value[1])
            else:
                pos=Graph.StaMarkerSizeListName.index(str(value[0]))
                Graph.StaMarkerSizeListValue[pos] = float(value[1])
        except:
            if pos!=-1:
                #The exception comes from the float(value[1])
                print ("ERROR: Invalid value '{0:s}' for station network name size".format(value[1]))
                removeLockFile()
                sys.exit()
            if PythonVersion == 2:
                Graph.StaMarkerSizeListName.append(unicode(value[0], "utf-8", errors="ignore"))
                try:
                    Graph.StaMarkerSizeListValue.append(float(value[1]))
                except:
                    print ("ERROR: Invalid value '{0:s}' for station network marker size".format(value[1]))
                    removeLockFile()
                    sys.exit()
            else:
                Graph.StaMarkerSizeListName.append(str(value[0]))
                try:
                    Graph.StaMarkerSizeListValue.append(float(value[1]))
                except:
                    print ("ERROR: Invalid value '{0:s}' for station network marker size".format(value[1]))
                    removeLockFile()
                    sys.exit()

    elif (option.dest=="StaNetworkNameColor"):
        Graph.StaNetWorkWithNames = True
        try:
            if PythonVersion == 2:
                pos=Graph.StaLetterColorListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterColorListValue[pos] = value[1]
            else:
                pos=Graph.StaLetterColorListName.index(str(value[0]))
                Graph.StaLetterColorListValue[pos] = value[1]
        except:
            if PythonVersion == 2:
                Graph.StaLetterColorListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterColorListValue.append(value[1])
            else:
                Graph.StaLetterColorListName.append(str(value[0]))
                Graph.StaLetterColorListValue.append(value[1])

    elif (option.dest=="StaNetworkNameSize"):
        Graph.StaNetWorkWithNames = True
        try:
            pos=-1
            if PythonVersion == 2:
                pos=Graph.StaLetterSizeListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterSizeListValue[pos] = float(value[1])
            else:
                pos=Graph.StaLetterSizeListName.index(str(value[0]))
                Graph.StaLetterSizeListValue[pos] = float(value[1])
        except:
            if pos!=-1:
                #The exception comes from the float(value[1])
                print ("ERROR: Invalid value '{0:s}' for station network name size".format(value[1]))
                removeLockFile()
                sys.exit()
            elif PythonVersion == 2:
                Graph.StaLetterSizeListName.append(unicode(value[0], "utf-8", errors="ignore"))
                try:
                    Graph.StaLetterSizeListValue.append(float(value[1]))
                except:
                    print ("ERROR: Invalid value '{0:s}' for station network name size".format(value[1]))
                    removeLockFile()
                    sys.exit()
            else:
                Graph.StaLetterSizeListName.append(str(value[0]))
                try:
                    Graph.StaLetterSizeListValue.append(float(value[1]))
                except:
                    print ("ERROR: Invalid value '{0:s}' for station network name size".format(value[1]))
                    removeLockFile()
                    sys.exit()

    elif (option.dest=="StaNetworkNameAlign"):
        Graph.StaNetWorkWithNames = True
        if value[1]=='left':
            horalign='right'
        elif value[1]=='right':
            horalign='left'
        else:
            horalign=value[1]

        if value[2]=='top':
            veralign='bottom'
        elif value[2]=='bottom':
            veralign='top'
        else:
            veralign=value[2]

        try:
            if PythonVersion == 2:
                pos=Graph.StaLetterHorAlignListName.index(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterHorAlignListValue[pos] = horalign
                Graph.StaLetterVerAlignListValue[pos] = veralign
            else:
                pos=Graph.StaLetterHorAlignListName.index(str(value[0]))
                Graph.StaLetterHorAlignListValue[pos] = horalign
                Graph.StaLetterVerAlignListValue[pos] = veralign
        except:
            if PythonVersion == 2:
                Graph.StaLetterHorAlignListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterVerAlignListName.append(unicode(value[0], "utf-8", errors="ignore"))
                Graph.StaLetterHorAlignListValue.append(horalign)
                Graph.StaLetterVerAlignListValue.append(veralign)
            else:
                Graph.StaLetterHorAlignListName.append(str(value[0]))
                Graph.StaLetterVerAlignListName.append(str(value[0]))
                Graph.StaLetterHorAlignListValue.append(horalign)
                Graph.StaLetterVerAlignListValue.append(veralign)

    elif (option.dest=="NotAvailBinText"):
        if PythonVersion == 2:
            Graph.NotAvailText = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.NotAvailText = value

    elif (option.dest=="NotAvailBinColor"):
        Graph.NotAvailColour = value

    elif (option.dest=="AvailMapBins"):
        Graph.UserSetAvailBins = True
        Graph.UserDefinedBinsOrContours = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: Availability Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in availability bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in Availability bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()
                elif valf>100.:
                    print ("ERROR: Bin '{0:s}' in Availability bin list is above 100".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated) #Sorted in ascending order
            #Add twice the first value with an arbitrary offset of 0.1 to put all values
            #smaller or equal than the value of the smallest bin in this position
            valfloated.insert(0,valfloated[0]-0.1)
            Graph.AvailBins = valfloated

    elif (option.dest=="ContRiskMapBins"):
        Graph.UserSetRiskBins = True
        Graph.UserDefinedBinsOrContours = True
        values = value.split(",")
        Graph.RiskBinsUserText = values #For error printing later
        if (len(values) < 1):
            print ("ERROR: Continuity Risk Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                except:
                    print ("ERROR: Invalid value '{0:s}' in continuity risk bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in Continuity Risk bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()
                elif valf>100.:
                    print ("ERROR: Bin '{0:s}' in Continuity Risk bin list is above 100".format(val))
                    removeLockFile()
                    sys.exit()
                
                valfloated.append(valf)

            #Values will be sorted later
            Graph.RiskBins = valfloated

    elif (option.dest=="ContRiskMarMapBins"):
        Graph.UserSetRiskMarBins = True
        Graph.UserDefinedBinsOrContours = True
        values = value.split(",")
        Graph.RiskMarBinsUserText = values #For error printing later
        if (len(values) < 1):
            print ("ERROR: Maritime Continuity Risk Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                except:
                    print ("ERROR: Invalid value '{0:s}' in continuity risk bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in Maritime Continuity Risk bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()
                elif valf>100.:
                    print ("ERROR: Bin '{0:s}' in Maritime Continuity Risk bin list is above 100".format(val))
                    removeLockFile()
                    sys.exit()
                
                valfloated.append(valf)

            #Values will be sorted later
            Graph.RiskMarBins = valfloated

    elif (option.dest=="IonoAvailMapBins"):
        Graph.UserSetIonoBins = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: Ionosphere Availability Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in Ionosphere availability bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in Ionosphere availability bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()
                elif valf>100.:
                    print ("ERROR: Bin '{0:s}' in Ionosphere availability bin list is above 100".format(val))
                    removeLockFile()
                    sys.exit()


            valfloated = sorted(valfloated) #Sorted in ascending order
            #Add twice the first value with an arbitrary offset of 0.1 to put all values
            #smaller or equal than the value of the smallest bin in this position
            valfloated.insert(0,valfloated[0]-0.1)
            Graph.IonoAvailBins = valfloated

    elif (option.dest=="HDOPMapBins"):
        Graph.UserSetHDOPBins = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: HDOP Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in HDOP bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in HDOP bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            #Add twice the first value with an arbitrary offset of 0.1 to put all values
            #greater or equal than the value of the smallest bin in this position
            valfloated.insert(0,valfloated[0]+0.1)
            Graph.HDOPBins = valfloated

    elif (option.dest=="PDOPMapBins"):
        Graph.UserSetPDOPBins = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: PDOP Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in PDOP bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in PDOP bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            #Add twice the first value with an arbitrary offset of 0.1 to put all values
            #greater or equal than the value of the smallest bin in this position
            valfloated.insert(0,valfloated[0]+0.1)
            Graph.PDOPBins = valfloated

    elif (option.dest=="GDOPMapBins"):
        Graph.UserSetGDOPBins = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: GDOP Map bins must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in GDOP bin list".format(val))
                    removeLockFile()
                    sys.exit()

                if valf<0.:
                    print ("ERROR: Bin '{0:s}' in GDOP bin list is below 0".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            #Add twice the first value with an arbitrary offset of 0.1 to put all values
            #greater or equal than the value of the smallest bin in this position
            valfloated.insert(0,valfloated[0]+0.1)
            Graph.GDOPBins = valfloated

    elif (option.dest=="AvailMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: Availability Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.AvailBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.AvailBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.AvailBinsText.append(i)

    elif (option.dest=="ContRiskMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: Continuity Risk Map bins text must have at least one value")
            removeLockFile()
            sys.exit()
        else:
            Graph.RiskBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.RiskBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.RiskBinsText.append(i)

    elif (option.dest=="ContRiskMarMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: Maritime Continuity Risk Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.RiskMarBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.RiskMarBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.RiskMarBinsText.append(i)

    elif (option.dest=="IonoAvailMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: Ionosphere Availability Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.IonoAvailBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.IonoAvailBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.IonoAvailBinsText.append(i)

    elif (option.dest=="HDOPMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: HDOP Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.HDOPBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.HDOPBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.HDOPBinsText.append(i)

    elif (option.dest=="PDOPMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: PDOP Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.PDOPBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.PDOPBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.PDOPBinsText.append(i)

    elif (option.dest=="GDOPMapBinsText"):
        values = value.split(";")
        if (len(values) < 1):
            print ("ERROR: GDOP Map bins text must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            Graph.GDOPBinsText = [] #For the case the parameter is given more than once
            for i in values:
                if PythonVersion == 2:
                    Graph.GDOPBinsText.append(unicode(i, "utf-8", errors="ignore"))
                else:
                    Graph.GDOPBinsText.append(i)

    elif (option.dest=="AvailContourLevels"):
        Graph.UserDefinedBinsOrContours = True
        Graph.UserDefinedAvailContourlevels = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: Availability contour list must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in availability contour list".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated) #Sorted in ascending order
            Graph.AvailContourLevels = valfloated

    elif (option.dest=="ContRiskContourLevels"):
        Graph.UserDefinedBinsOrContours = True
        Graph.UserDefinedRiskContourlevels = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: Continuity Risk contour list must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in continuity risk contour list".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            Graph.RiskContourLevels = valfloated

    elif (option.dest=="ContRiskMarContourLevels"):
        Graph.UserDefinedBinsOrContours = True
        Graph.UserDefinedRiskMarContourlevels = True
        values = value.split(",")
        if (len(values) < 1):
            print ("ERROR: Maritime Continuity Risk contour list must have at least one value (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            valfloated = []
            for val in values:
                try:
                    valf=float(val)
                    valfloated.append(valf)
                except:
                    print ("ERROR: Invalid value '{0:s}' in maritime continuity risk contour list".format(val))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            Graph.RiskMarContourLevels = valfloated

    elif (option.dest=="AvailBinColors"):
        values = value.split(",")
        Graph.AvailColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.AvailColorList.append(values[i])
        
    elif (option.dest=="ContRiskBinColors"):
        values = value.split(",")
        Graph.ContRiskColorList= [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.ContRiskColorList.append(values[i])

    elif (option.dest=="ContRiskMarBinColors"):
        values = value.split(",")
        Graph.ContRiskMarColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.ContRiskMarColorList.append(values[i])

    elif (option.dest=="IonoAvailBinColors"):
        values = value.split(",")
        Graph.IonoAvailColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.IonoAvailColorList.append(values[i])

    elif (option.dest=="HDOPBinColors"):
        values = value.split(",")
        Graph.HDOPColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.HDOPColorList.append(values[i])

    elif (option.dest=="PDOPBinColors"):
        values = value.split(",")
        Graph.PDOPColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.PDOPColorList.append(values[i])

    elif (option.dest=="GDOPBinColors"):
        values = value.split(",")
        Graph.GDOPColorList = [] #For the case the parameter is given more than once
        for i in range(len(values)):
            Graph.GDOPColorList.append(values[i])

    elif (option.dest=="FIRUser"):
        Graph.FIRNumUserFile+=1
        if PythonVersion == 2:
            Graph.FIRUserFile.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.FIRUserFile.append(value)

    elif (option.dest=="NoFIRBorder"):
        try:
            val = int(value)
        except:
            print ("ERROR: Invalid FIR number '{0:s}' in parameter '--nofirborder'".format(value))
            removeLockFile()
            sys.exit()

        if val<0:
            print ("ERROR: FIR number in parameter '--nofirborder' must be a positive number or 0 (value given is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        elif val==0:
            Graph.FIRShowBorder[0] = 0
        else:
            Graph.FIRShowBorder.append(val)

    elif (option.dest=="FIRLineType"):
        Graph.FIRNumLineStyle+=1
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyle.append(value)

    elif (option.dest=="FIRLineTypeEu"):
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyleEur = value

    elif (option.dest=="FIRLineTypeCONUS"):
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyleCONUS = value

    elif (option.dest=="FIRLineTypeAlaska"):
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyleAlaska = value

    elif (option.dest=="FIRLineTypeCanada"):
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyleCanada = value

    elif (option.dest=="FIRLineTypeMexico"):
        try:
            Graph.SupportedStylesCharactersList.index(value)
        except:
            print ("ERROR: Style '{0:s}' is not supported. Supported styles are {1:s}".format(value,Graph.SupportedStylesCharactersList))
            removeLockFile()
            sys.exit()
        Graph.FIRLineStyleMexico = value

    elif (option.dest=="FIRLineWidth"):
        Graph.FIRNumLineWidth+=1
        Graph.FIRLineWidth.append(value)

    elif (option.dest=="FIRLineWidthEu"):
        Graph.FIRLineWidthEur = value

    elif (option.dest=="FIRLineWidthCONUS"):
        Graph.FIRLineWidthCONUS = value

    elif (option.dest=="FIRLineWidthAlaska"):
        Graph.FIRLineWidthAlaska = value

    elif (option.dest=="FIRLineWidthCanada"):
        Graph.FIRLineWidthCanada = value

    elif (option.dest=="FIRLineWidthMexico"):
        Graph.FIRLineWidthMexico = value

    elif (option.dest=="FIRMarkerSize"):
        Graph.FIRNumMarkerSize+=1
        try:
            Graph.FIRMarkerSize.append(float(value))
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRMarkerSizeEu"):
        try:
            Graph.FIRMarkerSizeEur = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for European FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRMarkerSizeCONUS"):
        try:
            Graph.FIRMarkerSizeCONUS = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for CONUS FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRMarkerSizeAlaska"):
        try:
            Graph.FIRMarkerSizeAlaska = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Alaska FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRMarkerSizeCanada"):
        try:
            Graph.FIRMarkerSizeCanada = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Canada FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRMarkerSizeMexico"):
        try:
            Graph.FIRMarkerSizeMexico = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Mexico FIR marker size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRLineColor"):
        Graph.FIRData = True
        Graph.FIRNumLineColor+=1 
        Graph.FIRLineColor.append(value)

    elif (option.dest=="FIRLineColorEu"):
        Graph.FIRData = True
        Graph.FIRUserSelLineColorEur = True
        Graph.FIRLineColorEur = value

    elif (option.dest=="FIRLineColorCONUS"):
        Graph.FIRData = True
        Graph.FIRUserSelLineColorCONUS = True
        Graph.FIRLineColorCONUS = value

    elif (option.dest=="FIRLineColorAlaska"):
        Graph.FIRData = True
        Graph.FIRUserSelLineColorAlaska = True
        Graph.FIRLineColorAlaska = value

    elif (option.dest=="FIRLineColorCanada"):
        Graph.FIRData = True
        Graph.FIRUserSelLineColorCanada = True
        Graph.FIRLineColorCanada = value

    elif (option.dest=="FIRLineColorMexico"):
        Graph.FIRData = True
        Graph.FIRUserSelLineColorMexico = True
        Graph.FIRLineColorMexico = value

    elif (option.dest=="FIRDegTextHeader"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeader.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.FIRDegTextHeader.append(value)
        Graph.FIRNumDegTextHeader+=1

    elif (option.dest=="FIRDegTextHeaderEu"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderEur = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderEur = value

    elif (option.dest=="FIRDegTextHeaderCONUS"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderCONUS = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderCONUS = value

    elif (option.dest=="FIRDegTextHeaderAlaska"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderAlaska = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderAlaska = value

    elif (option.dest=="FIRDegTextHeaderCanada"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderCanada = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderCanada = value

    elif (option.dest=="FIRDegTextHeaderMexico"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderMexico = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderMexico = value

    elif (option.dest=="FIRDegTextHeaderFIRSum"):
        if PythonVersion == 2:
            Graph.FIRDegTextHeaderFIRSum = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextHeaderFIRSum = value

    elif (option.dest=="FIRDegTextFooter"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooter.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.FIRDegTextFooter.append(value)
        Graph.FIRNumDegTextFooter+=1

    elif (option.dest=="FIRDegTextFooterEu"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterEur = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterEur = value

    elif (option.dest=="FIRDegTextFooterCONUS"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterCONUS = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterCONUS = value

    elif (option.dest=="FIRDegTextFooterAlaska"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterAlaska = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterAlaska = value

    elif (option.dest=="FIRDegTextFooterCanada"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterCanada = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterCanada = value

    elif (option.dest=="FIRDegTextFooterMexico"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterMexico = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterMexico = value

    elif (option.dest=="FIRDegTextFooterFIRSum"):
        if PythonVersion == 2:
            Graph.FIRDegTextFooterFIRSum = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFooterFIRSum = value

    elif (option.dest=="FIRDegText"):
        Graph.FIRDegradation = True
        Graph.FIRNumDegText+=1
        if PythonVersion == 2:
            Graph.FIRDegText.append(unicode(value, "utf-8", errors="ignore"))
        else:
            Graph.FIRDegText.append(value)

    elif (option.dest=="FIRDegTextEu"):
        Graph.FIRDegradation = True
        if PythonVersion == 2:
            Graph.FIRDegTextEur = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextEur = value

    elif (option.dest=="FIRDegTextCONUS"):
        Graph.FIRDegradation = True
        if PythonVersion == 2:
            Graph.FIRDegTextCONUS = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextCONUS = value

    elif (option.dest=="FIRDegTextAlaska"):
        Graph.FIRDegradation = True
        if PythonVersion == 2:
            Graph.FIRDegTextAlaska = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextAlaska = value

    elif (option.dest=="FIRDegTextCanada"):
        Graph.FIRDegradation = True
        if PythonVersion == 2:
            Graph.FIRDegTextCanada = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextCanada = value

    elif (option.dest=="FIRDegTextMexico"):
        Graph.FIRDegradation = True
        if PythonVersion == 2:
            Graph.FIRDegTextMexico = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextMexico = value

    elif (option.dest=="FIRDegTextFIRSum"):
        Graph.FIRSum = True
        if PythonVersion == 2:
            Graph.FIRDegTextFIRSum = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FIRDegTextFIRSum = value

    elif (option.dest=="FIRSumDegUserFIR"):
        Graph.FIRSum = True
        Graph.FIRSumWithSelection= True
        values = value.split(",")
        for i in values:
            try:
                val = int(i)
            except:
                print ("ERROR: Invalid value '{0:s}' for user defined FIR number".format(i))
                removeLockFile()
                sys.exit()

            if (val<0):
                print ("ERROR: Invalid value '{0:s}' for user defined FIR number".format(i))
                removeLockFile()
                sys.exit()

            Graph.FIRSumDegUserFIR.append(val)

    elif (option.dest=="FIRDegTextBins"):
        Graph.FIRDegradation = True
        values = value.split(",")
        #Note: Values are sorted later
        Graph.FIRDegTextBins.append([])
        for i in values:
            try:
                Graph.FIRDegTextBins[Graph.FIRNumDegTextBins].append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBins +=1 

    elif (option.dest=="FIRDegTextBinsEu"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextBinsEur = [] #For the case the parameter is given twice
        values = value.split(",")
        #Note: Values are sorted later
        for i in values:
            try:
                Graph.FIRDegTextBinsEur.append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for European FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBinsEur = len(values)

    elif (option.dest=="FIRDegTextBinsCONUS"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextBinsCONUS = [] #For the case the parameter is given twice
        values = value.split(",")
        #Note: Values are sorted later
        for i in values:
            try:
                Graph.FIRDegTextBinsCONUS.append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for CONUS FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBinsCONUS = len(values)

    elif (option.dest=="FIRDegTextBinsAlaska"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextBinsAlaska = [] #For the case the parameter is given twice
        values = value.split(",")
        #Note: Values are sorted later
        for i in values:
            try:
                Graph.FIRDegTextBinsAlaska.append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for Alaska FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBinsAlaska = len(values)

    elif (option.dest=="FIRDegTextBinsCanada"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextBinsCanada = [] #For the case the parameter is given twice
        values = value.split(",")
        #Note: Values are sorted later
        for i in values:
            try:
                Graph.FIRDegTextBinsCanada.append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for Canada FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBinsCanada = len(values)

    elif (option.dest=="FIRDegTextBinsMexico"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextBinsMexico = [] #For the case the parameter is given twice
        values = value.split(",")
        #Note: Values are sorted later
        for i in values:
            try:
                Graph.FIRDegTextBinsMexico.append(float(i))
            except:
                print ("ERROR: Invalid value '{0:s}' for Mexico FIR bin".format(i))
                removeLockFile()
                sys.exit()
        Graph.FIRNumDegTextBinsMexico = len(values)


    elif (option.dest=="FIRDegTextSize"):
        Graph.FIRDegradation = True
        Graph.FIRNumDegTextSize+=1
        try:
            Graph.FIRDegTextSize.append(float(value))
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeEu"):
        Graph.FIRDegradation = True
        try:
            Graph.FIRDegTextSizeEur = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for European FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeCONUS"):
        Graph.FIRDegradation = True
        try:
            Graph.FIRDegTextSizeCONUS = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for CONUS FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeAlaska"):
        Graph.FIRDegradation = True
        try:
            Graph.FIRDegTextSizeAlaska = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Alaska FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeCanada"):
        Graph.FIRDegradation = True
        try:
            Graph.FIRDegTextSizeCanada = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Canada FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeMexico"):
        Graph.FIRDegradation = True
        try:
            Graph.FIRDegTextSizeMexico = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for Mexico FIR degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextSizeFIRSum"):
        Graph.FIRSum = True
        try:
            Graph.FIRDegTextSizeFIRSum = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR sum degradation text size".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextColor"):
        Graph.FIRDegradation = True
        Graph.FIRNumDegTextColor+=1
        Graph.FIRDegTextColor.append(value)

    elif (option.dest=="FIRDegTextColorEu"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextColorEur = value

    elif (option.dest=="FIRDegTextColorCONUS"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextColorCONUS = value

    elif (option.dest=="FIRDegTextColorAlaska"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextColorAlaska = value

    elif (option.dest=="FIRDegTextColorCanada"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextColorCanada = value

    elif (option.dest=="FIRDegTextColorMexico"):
        Graph.FIRDegradation = True
        Graph.FIRDegTextColorMexico = value

    elif (option.dest=="FIRDegTextColorFIRSum"):
        Graph.FIRSum = True
        Graph.FIRDegTextColorFIRSum = value

    elif (option.dest=="FIRDegTextPosition"):
        Graph.FIRDegradation = True
        Graph.FIRNumDegTextPositionX+=1
        Graph.FIRNumDegTextPositionY+=1
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionX.append(float(values[0]))
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionY.append(float(values[1]))
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionEu"):
        Graph.FIRDegradation = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: European FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXEur = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for European FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYEur = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for European FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionCONUS"):
        Graph.FIRDegradation = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: CONUS FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXCONUS = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for CONUS FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYCONUS = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for CONUS FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionAlaska"):
        Graph.FIRDegradation = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: Alaska FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXAlaska = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for Alaska FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYAlaska = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Alaska FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionCanada"):
        Graph.FIRDegradation = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: Canada FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXCanada = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for Canada FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYCanada = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Canada FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionMexico"):
        Graph.FIRDegradation = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: Mexico FIR Degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXMexico = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for Mexico FIR Degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYMexico = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for Mexico FIR Degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="FIRDegTextPositionFIRSum"):
        Graph.FIRSum = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: FIR sum degradation position parameter must be X,Y (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionXFIRSum = float(values[0])
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR sum degradation X position".format(values[0]))
            removeLockFile()
            sys.exit()
        try:
            Graph.FIRDegTextPositionYFIRSum = float(values[1])
        except:
            print ("ERROR: Invalid value '{0:s}' for FIR sum degradation Y position".format(values[1]))
            removeLockFile()
            sys.exit()

    elif (option.dest=="NoFIRDegText"):
        values = value.split(",")
        for i in values:
            try:
                val = int(i)
            except:
                print ("ERROR: Invalid FIR number '{0:s}' in parameter '--nofirdegtext'".format(i))
                removeLockFile()
                sys.exit()

            if val<0:
                print ("ERROR: FIR number in parameter '--nofirdegtext' must be a positive number or 0 (value given is '{0:s}')".format(i))
                removeLockFile()
                sys.exit()
            elif val==0:
                Graph.FIRShowDegText[0] = 0
            else:
                Graph.FIRShowDegText.append(val)

    elif (option.dest=="WriteToFileFIRDegText"):
       Graph.FIRDegradation = True
       if PythonVersion == 2:
           Graph.FIROutputFileNameDegText = unicode(value, "utf-8", errors="ignore")
       else:
           Graph.FIROutputFileNameDegText = value

    elif (option.dest=="AvailCbarTitle"):
        if PythonVersion == 2:
            Graph.AvailCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.AvailCbarTitle = value

    elif (option.dest=="ContRiskCbarTitle"):
        if PythonVersion == 2:
            Graph.ContRiskCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.ContRiskCbarTitle = value

    elif (option.dest=="ContRiskMarCbarTitle"):
        if PythonVersion == 2:
            Graph.ContRiskMarCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.ContRiskMarCbarTitle = value

    elif (option.dest=="IonoAvailCbarTitle"):
        if PythonVersion == 2:
            Graph.IonoAvailCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.IonoAvailCbarTitle = value

    elif (option.dest=="HDOPCbarTitle"):
        if PythonVersion == 2:
            Graph.HDOPCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.HDOPCbarTitle = value

    elif (option.dest=="PDOPCbarTitle"):
        if PythonVersion == 2:
            Graph.PDOPCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.PDOPCbarTitle = value

    elif (option.dest=="GDOPCbarTitle"):
        if PythonVersion == 2:
            Graph.GDOPCbarTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.GDOPCbarTitle = value

    elif (option.dest=="SBASTopFigureMargin"):
        try:
            Graph.TopMargin = 1. - float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for top margin size".format(value))
            removeLockFile()
            sys.exit()

        if Graph.TopMargin<0. or Graph.TopMargin<0.5:
            print ("ERROR: Top margin values must be between 0 and 0.5 (provided value is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="SBASBottomFigureMargin"):
        try:
            Graph.BottomMargin = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for bottom margin size".format(value))
            removeLockFile()
            sys.exit()

        if Graph.BottomMargin<0. or Graph.BottomMargin>0.5:
            print ("ERROR: Bottom margin values must be between 0 and 0.5 (provided value is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="SBASLeftFigureMargin"):
        try:
            Graph.LeftMargin = float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for left margin size".format(value))
            removeLockFile()
            sys.exit()

        if Graph.LeftMargin<0. or Graph.LeftMargin>0.5:
            print ("ERROR: Left margin values must be between 0 and 0.5 (provided value is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="SBASRightFigureMargin"):
        try:
            Graph.RightMargin = 1. - float(value)
        except:
            print ("ERROR: Invalid value '{0:s}' for right margin size".format(value))
            removeLockFile()
            sys.exit()

        if Graph.RightMargin<0. or Graph.RightMargin<0.5:
            print ("ERROR: Right margin values must be between 0 and 0.5 (provided value is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()

    elif (option.dest=="SBASPlotSize"):
        Graph.SBASplotUserSetSize = True
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: Plot size must have two values, horizontal and vertical size (value provided is '{0:s}')".format(value))
            removeLockFile()
            sys.exit()
        else:
            try:
                Graph.FigHorSize =float(values[0])/2.54 #Convert to inches
                if Graph.FigHorSize<=0.:
                    print ("ERROR: Horizontal size must be greater than 0 (provided value is '{0:s}')".format(values[0]))
                    removeLockFile()
                    sys.exit()
            except:
                print ("ERROR: Invalid value '{0:s}' for horizontal plot size".format(values[0]))
                removeLockFile()
                sys.exit()

            try:
                Graph.FigVerSize =float(values[1])/2.54 #Convert to inches
                if Graph.FigVerSize<=0.:
                    print ("ERROR: Vertical size must be greater than 0 (provided value is '{0:s}')".format(values[1]))
                    removeLockFile()
                    sys.exit()
            except:
                print ("ERROR: Invalid value '{0:s}' for vertical plot size".format(values[1]))
                removeLockFile()
                sys.exit()
            

##########################################################################
# Name        : readFile
# Description : Read the input file, according to the plotting condition,  
#               assign the value to Xvar and Yvar
##########################################################################   
def readFile(fileN, cond, colX, colY):
    try:
        #The 'rb' is to avoid unicode exceptions. In python2 it will not try to encode into utf
        #In Python3, the "errors='replace'" will convert faulty characters to question marks
        #This faulty characters can be ignored as they may appear only in the filepath of the
        #gLAB info message, which are of no use for graph
        if PythonVersion == 2: 
            f = open(fileN,'rb')
        else:
            f = open(fileN,'r',errors='replace')
    except:
        Errmsg=str(sys.exc_info()[1]).split(":")
        Errmsg=Errmsg[0].split("] ")
        print ("ERROR Opening file '{0:s}': '{1:s}'".format(fileN,Errmsg[1]))
        removeLockFile()
        sys.exit()
    Xvar = []
    Yvar = []
    i=0
    for line in f:
        i+=1
        var=line.split()
        j=0
        for ele in var:
            try:
                auxEle = float(ele)
                var[j] = auxEle
                j += 1
            except:
                j += 1
        if (cond != ""):
            try:
                ret = eval(cond)
            except:
                ret = False
        else:
            ret = True
        if (ret==True):
            try:
                ret1 = float(eval(colX))
                ret2 = float(eval(colY))
            except:
                ErrMsg=str(sys.exc_info()[1]).split()
                if "is not defined" in str(sys.exc_info()[1]):
                    print ("ERROR: User defined column '{0:s}' is not a valid column".format(ErrMsg[1].replace("'","")))
                elif "list index out of range" in str(sys.exc_info()[1]):
                    print ("ERROR: One of the column number provided does not exist in line number {0:d} of data file '{1:s}'".format(i,fileN))
                else:
                    print ("ERROR: Invalid value '{0:s}' in line number {1:d} of data file '{2:s}'".format(ErrMsg[len(ErrMsg)-1].replace("'",""),i,fileN))
                removeLockFile()
                sys.exit()
                

            Xvar.append(ret1)
            Yvar.append(ret2)
    f.close()
    if i<1:
        print ("ERROR: File '{0:s}' has no data".format(fileN))
        removeLockFile()
        sys.exit()
    return Xvar, Yvar 

##########################################################################
# Name        : removeLockFile
# Description : Remove lockfile '.plot.lock' inside a try/catch in order
#                 to avoid race conditions
##########################################################################   
def removeLockFile():
    if (CreateLockFile==True):
        if (os.path.isfile(LockFile)==True): 
            try:
                os.remove(LockFile)
            except:
                #It will enter here if after checking that the LockFile exists,
                #this instance is stopped before removing the file and another
                #instance removes the file. As the file will be erased, we don't
                #need to do anything
                pass

    return

##########################################################################
# Name        : MakeGraph
# Description : This function makes the graphic, from the parameters
#               already parsed.
##########################################################################


def MakeGraph():
    i=0
    if Graph.stanford:
        sfp = stanford()
        sfp.PE, sfp.PL = readFile(Graph.PlotList[i].FileName, Graph.PlotList[i].Cond, Graph.PlotList[i].ColX, Graph.PlotList[i].ColY)
        if (Graph.ALAuto == False): sfp.AL = Graph.AL
        if (Graph.resolution_x_auto == False): sfp.resolution_x = Graph.resolution_x
        if (Graph.resolution_y_auto == False): sfp.resolution_y = Graph.resolution_y
        if (Graph.ColorMap != ""): sfp.cm = Graph.ColorMap
        sfp.dealData()
        sfp.getPoints()
        sfp.plotPoints()
        if (Graph.XmaxAuto == False): sfp.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): sfp.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): sfp.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): sfp.Ymin = Graph.Ymin 
        if Graph.clean:
            x = [sfp.Xmin,sfp.Xmax]
            y = x
            plt.plot(x, y,'black')
        else:
            sfp.plotPatch()
        if (Graph.Xlabel != ""): sfp.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sfp.Ylabel =Graph.Ylabel
        if (Graph.Title != ""): sfp.Title =Graph.Title
        if (Graph.StfdPercentileX == True or Graph.StfdPercentileY == True):
            sfp.getPercentileCount()
        sfp.grid = Graph.grid
        sfp.SaveFigure = Graph.SaveFigure
        if (sfp.SaveFigure == True):
            sfp.SaveFigurePath = Graph.SaveFigurePath[0]
        removeLockFile()
        sfp.plotShow()
    elif Graph.stanfordESA:
        sfESA = stanfordESA()
        sfESA.f = Graph.PlotList[i].FileName
        if (Graph.maxpoints_auto == False): sfESA.maxpoints = Graph.maxpoints
        sfESA.readData()
        if (Graph.resolution_x_auto == False): sfESA.resolution_x = Graph.resolution_x
        if (Graph.resolution_y_auto == False): sfESA.resolution_y = Graph.resolution_y
        if (Graph.XmaxAuto == False): sfESA.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): sfESA.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): sfESA.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): sfESA.Ymin = Graph.Ymin 
        if (Graph.Xlabel != ""): sfESA.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sfESA.Ylabel =Graph.Ylabel
        if (Graph.Title != ""): sfESA.Title =Graph.Title
        if (Graph.ColorMap != ""): sfESA.cm = Graph.ColorMap
        sfESA.grid = Graph.grid
        sfESA.SaveFigure = Graph.SaveFigure
        if (sfESA.SaveFigure == True):
            sfESA.SaveFigurePath1 = Graph.SaveFigurePath[0]
        x = sfESA.x
        y = sfESA.y
        vertical = sfESA.verticalNo
        horizontal = sfESA.horizontalNo

        fig1 = plt.figure()
        ax1 = fig1.add_subplot(111)
        sfESA.Component="Vertical"
        NumNewlines=sfESA.Title.count('\n')
        if Graph.AdjustToMargin == True:
            fig1.tight_layout() #This is to adjust plot to margins
            fig1.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
            #Add space to fit multiline title
            if NumNewlines == 1:
                fig1.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                fig1.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig1.subplots_adjust(top=.83)
        else:
            if NumNewlines == 2:
                fig1.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig1.subplots_adjust(top=.83)

        sfESA.AL = Graph.sfESAHAL
        sfESA.getPoints(ax1,x,y,vertical)
        if (Graph.Xlabel == ""): sfESA.Xlabel = "Vertical Positioning Error (metres)"
        if (Graph.Ylabel == ""): sfESA.Ylabel = "Vertical Protection Level (metres)"
        if Graph.sfESAwithRegions == False:
            ax1.text(2*sfESA.Xmax/5, sfESA.Ymax/5, u'N {1:s} VPE≥VPL: {0:.0f}'.format(sfESA.n_fail,Graph.textGeometriesShort) , style='italic')
        sfESA.plotPoints(ax1)
        if (sfESA.SaveFigure == True):
            try:
                plt.savefig(Graph.SaveFigurePath[0])
            except:
                print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                removeLockFile()
                sys.exit()

        fig2 = plt.figure()
        ax2 = fig2.add_subplot(111)
        sfESA.Component="Horizontal"
        NumNewlines=sfESA.Title.count('\n')
        if Graph.AdjustToMargin == True:
            fig2.tight_layout() #This is to adjust plot to margins
            fig2.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
            #Add space to fit multiline title
            if NumNewlines == 1:
                fig2.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                fig2.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig2.subplots_adjust(top=.83)
        else:
            if NumNewlines == 2:
                fig2.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig2.subplots_adjust(top=.83)

        sfESA.AL = Graph.sfESAVAL
        sfESA.getPoints(ax2,x,y,horizontal)
        if (Graph.Xlabel == ""): sfESA.Xlabel = "Horizontal Positioning Error (metres)"
        if (Graph.Ylabel == ""): sfESA.Ylabel = "Horizontal Protection Level (metres)"
        if Graph.sfESAwithRegions == False:
            ax2.text(2*sfESA.Xmax/5, sfESA.Ymax/5, u'N {1:s} HPE≥HPL: {0:.0f}'.format(sfESA.n_fail,Graph.textGeometriesShort) , style='italic')
        sfESA.plotPoints(ax2)

        removeLockFile()
        if (sfESA.SaveFigure ==True) and (len(Graph.SaveFigurePath) > 1):
            try:
                plt.savefig(Graph.SaveFigurePath[1])
            except:
                print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                removeLockFile()
                sys.exit()
        if (sfESA.SaveFigure == False):
            plt.show()
    elif Graph.worstIntegrityRatio:
        wir = WIRmap()
        wir.f = Graph.PlotList[i].FileName
        wir.colName = Graph.ColName
        wir.colX = Graph.PlotList[i].ColX
        wir.colY = Graph.PlotList[i].ColY
        wir.colRatioV = Graph.ColRatioV
        wir.colRatioH = Graph.ColRatioH
        wir.colMIsV = Graph.ColMIsV
        wir.colMIsH = Graph.ColMIsH
        wir.grid = Graph.grid
        wir.ColLabelName = Graph.ColLabelName
        wir.readData()
        wir.projection = Graph.projection
        wir.ms = 30*Graph.PlotList[i].MarkerSize
        if (Graph.XmaxAuto == False): wir.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): wir.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): wir.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): wir.Ymin = Graph.Ymin 
        if (Graph.Title != ""): wir.Title =Graph.Title
        if (Graph.Xlabel != ""): wir.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): wir.Ylabel =Graph.Ylabel
        if (Graph.cbarAutoMin == False): wir.cbarMin = Graph.cbarMin
        if (Graph.cbarAutoMax == False): wir.cbarMax = Graph.cbarMax
        if (Graph.cbarAutoN == False): wir.cbarInterval = Graph.cbarInterval
        if (Graph.continentColor != ""): wir.continentColor = Graph.continentColor
        if (Graph.lakeColor != ""): wir.lakeColor = Graph.lakeColor
        if (Graph.boundaryColor != ""): wir.boundaryColor = Graph.boundaryColor
        if (Graph.ColorMap != ""): wir.myColorMap = Graph.ColorMap
        if(Graph.FIRNumUserFile > 0):
            Graph.readDataUserFir()
        wir.SaveFigure = Graph.SaveFigure
        if(wir.SaveFigure==True):
            wir.SaveFigurePath = Graph.SaveFigurePath
        removeLockFile()
        wir.drawMap()
    elif Graph.SBASmaps:
        sbas = SBASmaps()
        sbas.f = Graph.PlotList[i].FileName
        sbas.grid = Graph.grid
        sbas.contourlines = Graph.contourlines
        if (Graph.SBASsystemName != ""): sbas.SBASsystemName = Graph.SBASsystemName
        if (Graph.PRNtext != ""): sbas.PRNtext = Graph.PRNtext
        if (Graph.PRNtextNewline == True ): sbas.PRNtextNewline = True
        sbas.readData()
        if(Graph.FIRNumUserFile > 0):
            Graph.readDataUserFir()
        if (Graph.Title != ""): sbas.Title =Graph.Title
        if (Graph.Xlabel != ""): sbas.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sbas.Ylabel =Graph.Ylabel
        if (Graph.Cbarlabel != ""): sbas.Cbarlabel =Graph.Cbarlabel
        if (Graph.continentColor != ""): sbas.continentColor = Graph.continentColor
        if (Graph.lakeColor != ""): sbas.lakeColor = Graph.lakeColor
        if (Graph.boundaryColor != ""): sbas.boundaryColor = Graph.boundaryColor
        sbas.SaveFigure = Graph.SaveFigure
        if(sbas.SaveFigure==True):
            sbas.SaveFigurePath = Graph.SaveFigurePath
        removeLockFile()
        sbas.drawMap()
    else:
        ax1 = pylab.subplot(111)
        while i<Graph.PlotCounter:
            Graph.PlotList[i].Xvar, Graph.PlotList[i].Yvar = readFile(Graph.PlotList[i].FileName, Graph.PlotList[i].Cond, Graph.PlotList[i].ColX, Graph.PlotList[i].ColY)
            try:
                if (Graph.PlotList[i].PlotColorAuto == False):
                    pylab.plot(Graph.PlotList[i].Xvar,Graph.PlotList[i].Yvar,Graph.PlotList[i].Style,label=Graph.PlotList[i].Label,color=Graph.PlotList[i].PlotColor,markersize=Graph.PlotList[i].MarkerSize,linewidth=Graph.PlotList[i].LineWidth)
                else:
                    pylab.plot(Graph.PlotList[i].Xvar,Graph.PlotList[i].Yvar,Graph.PlotList[i].Style,label=Graph.PlotList[i].Label,markersize=Graph.PlotList[i].MarkerSize,linewidth=Graph.PlotList[i].LineWidth)
            except:
                print (sys.exc_info()[1])
                removeLockFile()
                sys.exit()

            i+=1

        #Set Max and min values for plots, retrieving this values if they are automatically set
        if (Graph.XmaxAuto == False): 
            pylab.xlim( xmax=Graph.Xmax )
            MaxXtick = Graph.Xmax
        else:
            Tmptick = ax1.get_xlim()
            MaxXtick = Tmptick[1]

        if (Graph.XminAuto == False): 
            pylab.xlim( xmin=Graph.Xmin )
            MinXtick = Graph.Xmin
        else:
            Tmptick = ax1.get_xlim()
            MinXtick = Tmptick[0] 

        if (Graph.YmaxAuto == False): 
            pylab.ylim( ymax=Graph.Ymax )
            MaxYtick = Graph.Ymax
        else:
            Tmptick = ax1.get_ylim()
            MaxYtick = Tmptick[1]

        if (Graph.YminAuto == False): 
            pylab.ylim( ymin=Graph.Ymin )
            MinYtick = Graph.Ymin
        else:
            Tmptick = ax1.get_ylim()
            MinYtick = Tmptick[0] 

        #Set manual ticks if user set them
        if Graph.XTicsUser == True:
            ax1.set_xticks(pylab.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            ax1.set_xticks(pylab.linspace(MinXtick,MaxXtick,abs(int((MaxXtick-MinXtick)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            ax1.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            ax1.set_yticks(pylab.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            ax1.set_yticks(pylab.linspace(MinYtick,MaxYtick,abs(int((MaxYtick-MinYtick)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            ax1.set_yticks(Graph.YTicksList)

        pylab.xlabel(Graph.Xlabel)
        pylab.ylabel(Graph.Ylabel)
        pylab.title(Graph.Title)

        NumNewlines=Graph.Title.count('\n')
        if Graph.AdjustToMargin == True:
            pylab.tight_layout() #Adjust plot to margins
            #Add margin on top to fit title with multiple lines (if necessary)
            if NumNewlines == 1:
                pylab.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                pylab.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                pylab.subplots_adjust(top=.83)
        else:
            if NumNewlines == 2:
                pylab.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                pylab.subplots_adjust(top=.83)



        if Graph.WaterMark != "":
            if Graph.AdjustToMargin == True:
                if Graph.WaterMarkPositionSetbyUser == 1:
                    pylab.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    pylab.annotate(Graph.WaterMark, xy=(.96, .11), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            else:
                if Graph.WaterMarkPositionSetbyUser == 1:
                    pylab.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    pylab.annotate(Graph.WaterMark, xy=(.89, .11), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)

        if Graph.NumTextMark > 0:
            for j in range(Graph.NumTextMark):
                pylab.annotate(Graph.TextMark[j], xy=(Graph.TextMarkPositionX[j],Graph.TextMarkPositionY[j]), xycoords='axes fraction', fontsize=Graph.TextMarkSize[j], color=Graph.TextMarkColour[j])
        if (Graph.FractionalTitle != ""):
            if Graph.AdjustToMargin == True:
                #Add margin for fractional title if none set
                if NumNewlines == 0:
                    pylab.subplots_adjust(top=.9)
            pylab.annotate(Graph.FractionalTitle, xy=(.025, .975), xycoords='figure fraction', horizontalalignment='left', verticalalignment='top')

        if Graph.grid:
            pylab.grid(True)


        if (legend==True):
            if (Graph.LabelPosition == 11):
                pylab.legend(numpoints=Graph.NumPointsLabel,bbox_to_anchor=(Graph.LabelPositionX,Graph.LabelPositionY))
            else: 
                pylab.legend(numpoints=Graph.NumPointsLabel,loc=Graph.LabelPosition) 

        removeLockFile()

        if (Graph.SaveFigure==True):
            try:
                pylab.savefig(Graph.SaveFigurePath[0])
            except:
                Errmsg=str(sys.exc_info()[1]).split('"')
                if "rgba" in str(sys.exc_info()[1]):
                    print ("ERROR: User defined colour '{0:s}' is not a valid colour".format(Errmsg[1]))
                else:
                    print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                removeLockFile()
                sys.exit()
        else:   
            pylab.show()






##########################################################################
# Name        : 
# Description : Main execution thread
##########################################################################

Graph = Graphic()


HelpHeader = """
#############################################################################
# Copyright: gAGE/UPC & ESA
# Project: EDUNAV GNSS Lab Tool
# Authors: Adria Rovira-Garcia (group of Astronomy and GEomatics - gAGE/UPC)
#          Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
# Curator: Adria Rovira-Garcia ( gAGE/UPC )
# Developer: Deimos Ibanez Segura ( gAGE/UPC )
#            Yixie Shao ( gAGE/UPC )
#          glab.gage @ upc.edu           
# File: graph.py
# Code Management Tool File Version: 5.5  Revision: 1
# Date: 2020/12/11
#############################################################################


GRAPHIC GENERAL OPTIONS (default options):

  The General Options are the ones that can be specified once per graphic,
  and will affect the entire graphic window.

  A hash ('#') means that the parameter expects a numerical value.
  A comma (',') or semicolon (';') means that the parameter expects a list of values
    separated by comma or semicolon (the list may be of numerical values if it has
    hashes or strings if it has the symbols '<' and '>'. If the list has a
    variable number of items, the "..." are shown.
  A '<text>' or any word between '<' and '>' means that the parameter expects a string
    (without the '<' and '>' symbols).

  -h, --help                                  Show this help message and exit

  -t, --title, --tit          <text>          Set the title of the Graphic

  --Xlabel, --xlab, --xl      <text>          Set the x-axis label

  --Ylabel, --ylab, --yl      <text>          Set the y-axis label

  --Xmin, --xmin, --xn             #          The minimum value for the x axis to be plot, if 
                                                no value is provided, automatic limits are set.  

  --Xmax, --xmax, --xx             #          The maximum value for the x axis to be plot, if 
                                                no value is provided, automatic limits are set.

  --Ymin, --ymin, --yn             #          The minimum value for the y axis to be plot, if 
                                                no value is provided, automatic limits are set.

  --Ymax, --ymax, --yx             #          The maximum value for the y axis to be plot, if 
                                                no value is provided, automatic limits are set. 

  --Xticks, --xticks, --xt     #,#,#          Set the ticks for x axis. The values must be 
                                                given in this format: Xmin,Xmax,NumberOfTicks
                                                (this parameter is incompatible with --XticksStep
                                                and --XTicksList). See note below.

  --Yticks, --yticks, --yt     #,#,#          Set the ticks for y axis. The values must be 
                                                given in this format: Ymin,Ymax,NumberOfTicks
                                                (this parameter is incompatible with --YticksStep
                                                and --YTicksList). See note below


  --XticksStep, --xticksstep,      #          Set the ticks step for x axis (this parameter
  --xts                                         is incompatible with --Xticks and --XTicksList).

  --YticksStep, --yticksstep,      #          Set the ticks step for y axis (this parameter
  --yts                                         is incompatible with --Yticks and --YTicksList).

  --XTicksList, --xtickslist,  #,#,...        Set the list of ticks for x axis. The list does
  --xtl                                         not to be ordered and must be comma (',') separated. 
                                                (this parameter is incompatible --Xticks and --XticksStep).

  --YTicksList, --ytickslist,  #,#,...        Set the list of ticks for y axis. The list does
  --ytl                                         not to be ordered and must be comma (',') separated. 
                                                (this parameter is incompatible --Yticks and --YticksStep).

  --Ftitle, --ftitle, --ft    <text>          Add a fractional title to the upper left corner.

  --wm, --watermark           <text>          Add a watermark with the given text.

  --wmc, --watermarkcolor   <colour>          Sets the watermark colour [DEFAULT 'black'].
                                                See option '--color' for the full list of colours.

  --wms, --watermarksize           #          Set the size of the watermark text [DEFAULT 8]

  --wmp, --watermarkposition     #,#          Set the X and Y position of the watermark. The position
                                                must be given relative to the lower left corner of the plot,
                                                and  with the X and Y values given a comma (',') separated string.
                                                For example, to set the default position of the watermark in
                                                SBAS plots (lower right corner), the parameter values should be
                                                provided as ".87,.03"

  --textmark                  <text>          Add an text mark with the given text. For adding multiple
                                                text marks, set this option as many times as necessary

  --textmarkc,              <colour>          Sets the text mark colour [DEFAULT 'black']. Set this option
  --textmarkcolor                               for each text mark set with option '--textmark'.
                                                See option '--color' for the full list of colours.

  --textmarks, --textmarksize      #          Set the size of the text mark [DEFAULT 10]. Set this option
                                                for each annotation text set with option '--textmark'.

  --textmarkp,                   #,#          Set the X and Y position of the text mark.  Set this option
  --textmarkposition                            for each annotation text set with option '--textmark'. 
                                                The position must be given relative to the lower left corner of the 
                                                plot, and with the X and Y values given a comma (',') separated string.
                                                For example, to set the default position of the text mark
                                                in the center of the image, the parameter values should be
                                                provided as ".5,.5"

  --atm, --adjusttomargin                     Expand the figure to fit the image margin (works for python
  --AdjustToMargin                              versions greater or equal to 2.7).

  --no-lock-file                              Do not create the ".plot.lock" file. This file is necessary
                                                to synchronize graph.py with the GUI, but not in command line.
                                                This option is recommended when multiple instances of this tool
                                                are executed in parallel.

  --colormap,        <colourmapname>          Set the colour map used [DEFAULT: 'jet']
  --ColorMap                                    See full list of colormaps in the following link:
                                                https://matplotlib.org/users/colormaps.html

  NOTE:  In '--Xticks' or '--Yticks' options, the maximum and minimum can be different from
         the plot range (it is an independent range). The number of ticks (NumberOfTicks)
         shall be computed with the following formula:

         NumberOfTicks = 1 + ToInteger((MaxTick-MinTick)/TickResolution)



  Example:
       graph.py -t "Graphic title" --xl "time (s)" --yl "Altitude [m]" --xmin -3.0 --ymax 5.0 --xticks 0,24,7


PLOT DEPENDENT OPTIONS (default options):

  The Plot Dependent Options are specific to each plot.
  One new plot is considered from the point that a '-f' or '--file' is found. 
  All the options coming after this parameter belong to that specific plot.

  -f, --file                <filename>        Set the input file name for the specific plot.

  -x, -X, --Xcol                 <val>        Set the source of the x axis: 
                                                -x 4 or -x '$4' : will take as x axis the 4th
                                                column of the input file.

                                                Operations can be done in this parameter, such as:
                                                -x '($4-$5)': This will take the difference between
                                                the 4th and the 5th column 

                                                Mathematical functions and constants are supported:
                                                -x '(math.sin($12*math.pi/180)'

  -y, -Y, --Ycol                 <val>        Set the source of the y axis
                                                Identical properties as x column


  -c, --cond               <condition>        Specify the plotting condition:
                                               -c '($6>=10)' Include the 6th column if it is 
                                                equal or greater than 10

                                                -c '($1==\"OUTPUT\")' Include the 1st column by a specific
                                                string: surrounding the string by \"  

                                                Mathematical functions, booleans and constants are supported:
                                                -c '($1==\"POSTFIT\")&(math.e($12+$5)>5.0)'

                                                NOTE: Windows users have to exchange the ' for \" and the \" for '
                                                    when specifying a condition. For example, the following
                                                    condition: 
                                                          -c '($1==\"POSTFIT\")&(math.e($12+$5)>5.0)'
                                                    is valid in Linux, but in Windows it shall be written like this:
                                                          -c \"($1=='POSTFIT')&(math.e($12+$5)>5.0)\"


  -l, --label, --plotlabel      <text>        Enables the label for the current plot

  --npl, --numpointslabel            #        Set the number of points to be shown in the label.
                                                If no value is provided, it is set to 2, except for
                                                stations map, which the default is one

  --lp, --labelpos, --labelPos   <val>        Set the position of the label in the plot.
                                                The following values are supported:
                                                'tl'             top    left
                                                'tc'             top    center
                                                'tr'             top    right [DEFAULT]
                                                'bl'             bottom left
                                                'bc'             bottom center
                                                'br'             bottom right
                                                'cl'             center left
                                                'c'              center
                                                'cr'             center right
                                                'coordX,coordY'  user defined position 
                                                                  coordX values must be between [-0.05,1.3]
                                                                  coordY values must be between [-0.05,1.15]

  -s, --style                  <style>        Sets the style for the current plot  
                                                The following styles are supported:
                                                '.'     circle marker [DEFAULT]
                                                '-'     solid line style
                                                '--'    dashed line style
                                                '-.'    dash-dot line style
                                                '.-'    dots joined with lines
                                                ':'     dotted line style
                                                ','     pixel marker
                                                'o'     point marker
                                                's'     square marker
                                                'p'     pentagon marker
                                                '+'     plus marker
                                                'x'     x marker
                                                '^'     triangle up marker
                                                '>'     triangle right marker
                                                '<'     triangle left marker
                                                'v'     triangle down marker
                                                '*'     star marker
                                                'h'     hexagon1 marker (top part with edge)
                                                'H'     hexagon2 marker (top part straight)
                                                'D'     diamond marker
                                                'd'     thin diamond marker
                                                '|'     vertical line marker
                                                '_'     horizontal line marker
                                                '1'     tri_down marker
                                                '2'     tri_up marker
                                                '3'     tri_left marker
                                                '4'     tri_right marker


  --color, --cl                <color>        Sets the colour for the current plot
                                                Here is a provided a short list of the colours supported:
                                                'b'     blue [DEFAULT]
                                                'g'     green
                                                'r'     red
                                                'c'     cyan
                                                'm'     magenta
                                                'y'     yellow
                                                'k'     black
                                                'w'     white
                                                OR
                                                Any colour in HTML format. For a full list of colours, see the link:
                                                 http://matplotlib.org/api/pyplot_api.html#matplotlib.pyplot.plot

  --markersize, --ms                 #        Sets the plot maker size [DEFAULT 5]  

  --linewidth, --lw                  #        Sets the plot line width [DEFAULT 1]

  -g, --grid                     <val>        Set the plot grid [DEFAULT on]
                                                It could be turn off by 'off' or 'no'

  Example:
       graph.py -f /home/gLAB/Example -x '(math.sin($1*math.pi/180))' -y 2 
       -l "Plot Label" --style p --color cyan   



MULTIPLE PLOTS:

  Each graphic window can contain several plots. One new plot is considered 
  from the point that a '-f' or '--file' is found:
      Graphic General Options: will apply to all the plots present
      Plot Dependent options: parameters specific to each plot.

  Example:
       graph.py -f /home/gLAB/Example -x 1 -y 2 -f /home/gLAB/Example -x 2 -y 1


SAVE CURRENT GRAPHIC:

  User can save the entire graphic window into the path specified. If no path 
  is specified, it will be allocated in the current working directory.
  The graphic output format is deduced from the extension of the file name, if no
  extension is provided a 'png' extension type will be used: 


  --save, --sv              <filename>        Stores the graphic window given a file name. The graphic           
                                                output format is deduced from the extension of the file name.
                                                Supported formats are: 
                                                emf, eps, jpeg, jpg, pdf, png [DEFAULT], ps, raw, rgba, svg, svgz.

  Example:
       graph.py -f /home/gLAB/Example -x 1 -y 2 --save Figure_Example
       graph.py -f /home/gLAB/Example -x 1 -y 2 --sv /home/Desktop/Figure_Example.eps




STANFORD PLOT:

  In this mode: 

  For GRAPHIC GENERAL OPTIONS, all the options work the same way as in the default plots,
                               except the options "--Ftitle" (add a fractional title), "--xt" and "--yt" (for setting ticks) which are disabled. 

  For PLOT DEPENDENT OPTIONS, the options "-f", "-x", "-y", "-c", "-g" work the same way as in the default plots,
                              while the other options in this part are disabled in this mode.
                              "-x" and "-y" options can also be written as "--error" and "--pl" respectively.

  MULTIPLE PLOTS are disabled in this mode.

  For SAVE CURRENT GRAPHIC, it works the same way as for the other kind of plots.

  --stanford, --sf, --sp                      Make a stanford plot.

  --AL, --al                         #        Set the alarm limit for the protection level [DEFAULT 40] 


  --clean                                     Make a stanford Plot without failure patches.

  --xr,   --xresolution              #        Set the resolution in x-direction of the plot [DEFAULT 0.5] 

  --yr,   --yresolution              #        Set the resolution in y-direction of the plot [DEFAULT 0.5]

  --percentilex, --percentileX                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the horizontal axis.

  --percentiley, --percentileY                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the vertical axis.

  --percentilexlist,           #,#,...        Show ticks where the user provided percentiles of 
  --percentileXList                             the points are reached in the horizontal axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentilex', the latter will be ignored.

  --percentileylist,           #,#,...        Show ticks where the user provided percentiles of
  --percentileYList                             the points are reached in the vertical axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentiley', the latter will be ignored.

  --noepochsintitle,                     Do not add the number of epochs in the title. Alternatively, the user can
  --NoEpochsInTitle                        set the number of epochs by adding in the title (with option '-t')
                                           the following texts (without quotes) which will be substituted with
                                           the values shown:
                                            {0:d} -> Print the total number of epochs
                                            {1:d} -> Print the total number of epochs that are not MI
                                            {2:d} -> Print the total number of epochs that are MIs
                                            {3:d} -> Print the total number of epochs that are below the
                                                       alarm limit and are not MIs
                                            {4:d} -> Print the total number of epochs that are over the
                                                       alarm limit and are not MIs
                                            {5:d} -> Print the total number of epochs that are MI and
                                                       are below the alarm limit in both axis
                                            {6:d} -> Print the total number of epochs that are HMI
                                            {7:d} -> Print the total number of epochs that are MI and
                                                       are over the alarm limit

  --availepochpos,           #,#         Set the position (in X,Y components) in the plot of the text for the available
  --AvailEpochPos                          epochs or 'normal operation'

  --unavailepochpos,         #,#         Set the position (in X,Y components) in the plot of the text for the
  --UnAvailEpochPos                       unavailable epochs (over the alarm limit) and not MI 

  --hmiepochpos,             #,#         Set the position (in X,Y components) in the plot of the text for the HMI epochs
  --HMIEpochPos                           

  --miavailpochpos,          #,#         Set the position (in X,Y components) in the plot of the text for the MI
  --MIAvailEpochPos                        epochs under alarm limit and not HMI

  --miunavailpochpos,        #,#         Set the position (in X,Y components) in the plot of the text for the MI
  --MIUnAvailEpochPos                      epochs over alarm limit

  --percentilex, --percentileX                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the horizontal axis.

  --percentiley, --percentileY                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the vertical axis.

  --percentilexlist,           #,#,...        Show ticks where the user provided percentiles of 
  --percentileXList                             the points are reached in the horizontal axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentilex', the latter will be ignored.

  --percentileylist,           #,#,...        Show ticks where the user provided percentiles of
  --percentileYList                             the points are reached in the vertical axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentiley', the latter will be ignored.

 Example:
        graph.py -f /home/gLAB/Example -x 1 -y 2 --sf


STANFORD-ESA PLOT:

  In this mode: 

  The input file should have this fixed format (this is gLAB's output format):

  The first three lines have the header with this format (numerical values can vary according to the plot):

  #XSTEP  YSTEP  XMAX  YMAX
   0.100  0.100  50.0  50.0
  # XPOS   YPOS  NUM_HOR  NUM_VER

  Since the fourth row, each row should provide the values: positioning error (the horizontal axis), protection level (the vertical axis), 
    number of horizontal vertical occurences (at the given coordinate of positioning error and protection level).

  For GRAPHIC GENERAL OPTIONS, all the options work the same way as in the default plots
                               except the option "--Ftitle" (add a fractional title),  "--xt" and "--yt" (for setting ticks) which are disabled.

  For PLOT DEPENDENT OPTIONS, the options "-f" works the same way as in the default plots,
                              while the other options in this part are disabled in this mode.

  MULTIPLE PLOTS are disabled in this mode.

  For SAVE CURRENT GRAPHIC, since it has two plots, then two save paths should be provided. If only one path is provided,
                            only the vertical plot will be saved.

  --stanfordESA, --sfesa, --spesa        Make a stanford-ESA plot.

  --sfesawithepochs,                     In the title and texts, set the word 'Epochs' instead of 'Geometries'
  --sfESAWithEpochs

  --nogeometriesintitle,                 Do not add the number of geometries (or epochs) in the title. Alternatively, the
  --NoGeometriesInTitle,                   user can set the number of geometries (or epochs) by adding in the title
  --noepochsintitle,                       (with option '-t') the following texts (without quotes) which will be 
  --NoEpochsInTitle                        substituted with the values shown:
                                            {0:d} -> Print the total number of geometries or epochs
                                            {1:d} -> Print the total number of geometries or epochs that are not MI
                                            {2:d} -> Print the total number of geometries or epochs that are MIs
                                            {3:d} -> Print the total number of geometries or epochs that are below the
                                                       alarm limit and are not MIs
                                            {4:d} -> Print the total number of geometries or epochs that are over the
                                                       alarm limit and are not MIs
                                            {5:d} -> Print the total number of geometries or epochs that are MI and
                                                       are below the alarm limit in both axis
                                            {6:d} -> Print the total number of geometries or epochs that are HMI
                                            {7:d} -> Print the total number of geometries or epochs that are MI and
                                                       are over the alarm limit


  --sfesawithregions,                    Add the regions 'MI', 'HMI' and 'System Unavailable' as in the Stanford plots.
  --sfESAWithRegions                       The number of geometries/epochs in each area will be printed as in
                                           the Stanford Plots.

  --hal, --HAL                 #         Set the alarm limit for the horizontal plot. This option only has effect if
                                           option '--sfesawithregions' is set  [Default 40]

  --val, --VAL                 #         Set the alarm limit for the vertical plot. This option only has effect if
                                           option '--sfesawithregions' is set  [Default 50]

  --availepochpos,           #,#         Set the position (in X,Y components) in the plot of the text for the available
  --AvailEpochPos                          epochs or 'normal operation'

  --unavailepochpos,         #,#         Set the position (in X,Y components) in the plot of the text for the
  --UnAvailEpochPos                        unavailable epochs (over the alarm limit) and not MI

  --hmiepochpos,             #,#         Set the position (in X,Y components) in the plot of the text for the HMI epochs
  --HMIEpochPos                         

  --miavailepochpos,         #,#         Set the position (in X,Y components) in the plot of the text for the MI
  --MIAvailEpochPos                        epochs under alarm limit and not HMI

  --miunavailepochpos,       #,#         Set the position (in X,Y components) in the plot of the text for the MI
  --MIUnAvailEpochPos                      epochs over alarm limit

  --percentilex, --percentileX                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the horizontal axis.

  --percentiley, --percentileY                Show ticks where the percentiles 68, 95 and 99.9
                                                of the points are reached in the vertical axis.

  --percentilexlist,           #,#,...        Show ticks where the user provided percentiles of 
  --percentileXList                             the points are reached in the horizontal axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentilex', the latter will be ignored.

  --percentileylist,           #,#,...        Show ticks where the user provided percentiles of
  --percentileYList                             the points are reached in the vertical axis.
                                                The list of points must be a comma separated list.
                                                If this parameter is provided along with parameter
                                                '--percentiley', the latter will be ignored.


 Examples: 
       graph.py -f /home/gLAB/Example --sfesa --sv /home/Desktop/Figure_Vertical.eps --sv /home/Desktop/Figure_Horizontal.eps

       graph.py -f /home/gLAB/Example --sfesa


WORLD MAP / STATION NAME MAP / WORST INTEGRITY RATIO PLOTS:
  In this mode: One, two or three plots can be generated depending on the input.

  The input file should contain the following fields: station name, geodetic coordinates (in degrees) and the values to be plotted.
  Parameter "-x": longitude (degrees)
  Parameter "-y": latitude (degrees)

  For GRAPHIC GENERAL OPTIONS, all the options work as in the default plots
                               except:
                                     the setting of "--xmax","--xmin","--ymax","--ymin"  only works 
                                     properly with the 'Equidistant Cylindrical Projection'.

                                     the option "--Ftitle", add a fractional title, is disabled. 

                                     the options "--xt" and "--yt" (for setting ticks) which are disabled.

                                     the option "--AdjustToMargin" will only take effect on station maps.

  For PLOT DEPENDENT OPTIONS, the options "-f", "-x", "-y", "--ms" work as in the default plots,
                              while the other options in this part are blocked in this mode.

  For SAVE CURRENT GRAPHIC:
                               In the case of one plot, it works the same way as for default plots
                               In the case of two plots, two save paths should be provided. If only one path is provided,
                               only the vertical map will be saved.
                               In the case of three plots, three save paths should be provided. If only one path is provided,
                               only the vertical map will be saved. If only two path are provided, only the vertical and
                               horizontal maps will be saved.


  --map --Map                                 Make a world map plot with the given values.

  --wir, --WIR                                Make a worst integrity ratio plot. This is a world map, but
                                                sets a fixed scale (with a minimum of 0 and a maximum of 2 
                                                independently of user input), and a fixed set of colors
                                                for the colourbar.

  --rv, --ratioV, --RV           <val>        Set the source of the vertical values or worst integrity ratio.
                                                Identical properties as x,y column in the default plots.

  --rh, --ratioH, --RH           <val>        Set the source of the horizontal values or worst integrity ratio.
                                                Identical properties as x,y column in the default plots.

  --miv, --MIV                   <val>        Set the source of the vertical MIs.
                                                Identical properties as x,y column in the default plots.

  --mih, --MIH                   <val>        Set the source of the horizontal MIs.
                                                Identical properties as x,y column in the default plots.

  --projection, --pj      <projection>        Set the projection of the map. [DEFAULT 'Equidistant Cylindrical Projection']
                                                User can set the value of projection as 'lcc' or 'lambert' 
                                                to switch to "Lambert Conformal Projection".

  --cbarMin,--cbarmin,--cmin         #        The minimum value for the colourbar, if no value is provided,
                                                automatic limits are set.  

  --cbarMax,--cbarmax,--cmax         #        The maximum value for the colourbar, if no value is provided,
                                                automatic limits are set. 

  --cbarInterval,--cbarN,--cn        #        The value of interval for colourbar's tick[DEFAULT 8]

  --continentColor,--cc        <color>        The continent's colour [DEFAULT 'yellow']

  --lakeColor, --lc            <color>        The lake's colour [DEFAULT 'white']

  --boundaryColor,--bc         <color>        The continent's colour, if no value is provided, 'white' is 
                                                set as [DEFAULT]

  --mapres, --MapResolution      <val>        Sets the world map resolution. Valid values are 'c', 'l' [DEFAULT],
                                                'i', 'h' or 'f' (ordered from lower to higher resolution).

  --sn, --staName, --SN          <val>        Set the source for the station name. Setting this value will make a new
                                                plot with the stations positions. The plot may have the name or a marker
                                                (or both) in the station coordinates

  --stanetwithnames,                          Add the station name in the station map. This is the default behaviour
  --staNetWithNames                             if this option ('--stanetwithnames') and marker option ('--stanetwithmarkers') 
                                                are not set. Also, this option is automatically set if options 
                                                '--stanetdefaultnamesize', '--stanetdefaultnamecolor', 
                                                '--stanetdefaultnamealign', '--stanetnamesize', '--stanetnamecolor' or
                                                '--stanetnamealign' are provided.

  --stanetdefaultnamesize,           #        Change the default letter size for the station names [DEFAULT 9]
  --staNetDefaultNameSize

  --stanetdefaultnamecolor,    <color>        Change the default letter colour for the station names [DEFAULT blue]
  --staNetDefaultNameColor

  --stanetdefaultnamealign,  <val1>  <val2>   Change the default letter alignment for the station names. There are two alignments,
  --staNetDefaultNameAlign                      horizontal and vertical alignment. The two values must be provided, first the
                                                horizontal alignment and then the vertical alignment.
                                                The possible values for horizontal alignment are:
                                                   'left'
                                                   'right'
                                                   'center' [DEFAULT]

                                                The possible values for vertical alignment are:
                                                   'top' [DEFAULT]
                                                   'bottom'
                                                   'center' 
                                                   'baseline'

  --stanetwithmarkers,                        Add a marker for each station in the station map. The marker properties can
  --staNetWithMarkers                           be set with the following options: '--stanetdefaultmarkertype', 
                                                '--stanetdefaultmarkersize', '--stanetdefaultmarkercolor'
                                                and '--stanetmarkersize' shown below. This option is automatically set if any
                                                of the marker properties option are set. If this option is set but no marker
                                                properties are set, the default values for the markers are to be a circular
                                                shape, with blue color and size 5.

  --stanetdefaultmarkertype,     <val>        Change the default marker type [DEFAULT 'o']
  --staNetDefaultMarkerType                     See parameter '-s' or '--style' for the list of marker types

  --stanetdefaultmarkersize,         #        Change the default marker size [DEFAULT '5']
  --staNetDefaultMarkerSize

  --stanetdefaultmarkercolor,    <val>        Change the default marker color [DEFAULT 'blue']
  --staNetDefaultMarkerColor                    See parameter '--color' for the list of colours

  --stanet,--staNetwork,         <val>        Set the source for the station network name. This option is for allowing to add
  --staNetwork                                  labels in the plot with the station map, as gLAB will be able to read from this
                                                column to what network each station belongs to.

  --stanetautolabel,                          Add an automatic label for each station network, which will be read from the column 
  --stanetAutoLabel                            set in parameter '--stanet'

  --stanetlabelnumsta,                        Add to the label of each station network the number of stations read. The number
  --staNetLabelNumSta                           will added at the end of the label name, adding a space (' ') and the number
                                                of station between parenthesis. This options works even if user sets a custom
                                                label for any network.

  --stanetdefaultlabel,        <label>        Change the default label for the station network [DEFAULT 'Other']
  --staNetDefaultLabel

  --stanetlabel,      <stanetname>  <label>   Set the label for a station network. Two values must be provided:
  --staNetworkLabel                             the name read from the input data (in the column specified with parameter
                                                '--stanet') and the label to be applied. To set a label to each
                                                station network that appears on the file, set this parameter as
                                                many times as necessary

  --stanetmarkertype,   <stanetname>  <val>   Set the marker type for a station network. Two values must be provided:
  --staNetworkMarkerType                        the name read from the input data (in the column specified with parameter
                                                '--stanet') and the marker type to be applied (see parameter '-s' for marker options). 
                                                In order to set a marker type to each station network that appears on the file, 
                                                set this parameter as many times as necessary

  --stanetmarkercolor,  <stanetname>  <val>   Set the marker colour for a station network. Two values must be provided:
  --staNetworkMarkerColor                       the name read from the input data (in the column specified with parameter
                                                '--stanet') and the marker colour to be applied (see parameter '--cl' for colours). 
                                                In order to set a marker colour to each station network that appears on the file, 
                                                set this parameter as many times as necessary

  --stanetmarkersize,   <stanetname>      #   Set the marker size for a station network. Two values must be provided:
  --staNetworkMarkerSize                        the name read from the input data (in the column specified with parameter
                                                '--stanet') and the marker size to be applied. 
                                                In order to set a marker size to each station network that appears on the file, 
                                                set this parameter as many times as necessary

  --stanetnamecolor,    <stanetname>  <val>   Set the colour for the station name for a given network. All the station name from
  --staNetNameColor                             the same network will have the same letter colour. Two values must be provided:
                                                the name read from the input data (in the column specified with parameter
                                                '--stanet') and the letter colour to be applied. 
                                                In order to set a letter colour to each station network that appears on the file, 
                                                set this parameter as many times as necessary

  --stanetnamesize,     <stanetname>      #   Set the letter size for the station name for a given network. All the station name from
  --staNetNameSize                              the same network will have the same letter size. Two values must be provided:
                                                the name read from the input data (in the column specified with parameter
                                                '--stanet') and the letter size to be applied. 
                                                In order to set a letter size to each station network that appears on the file, 
                                                set this parameter as many times as necessary

  --stanetnamealign, <stanetname> <val1>  <val2>  Set the letter alignment for the station name for a given network. All the station name
  --staNetNameAlign                                 from the same network will have the same alignment. Three values must be provided:
                                                    the name read from the input data (in the column specified with parameter
                                                    '--stanet') the horizontal and vertical alignment -in this order- (see parameter 
                                                    '--stanetdefaultnamealign'). In order to set a letter alignment to each station network 
                                                    that appears on the file, set this parameter as many times as necessary


 NOTES on World Maps / Worst Integrity Ratio Maps: 
    If only one of the parameters '--rh' or '--rv' is given, only the horizontal or vertical plots will be shown. 
    If both parameters '--rh' or '--rv' are given, two plots will be shown.
    If any of '--mih' or '--miv' parameters are given. a coloured ring around the coloured circles will appear on the corresponding plot.
    If only '--sn' parameter is given, a single plot with the station map will be shown.
    It is recommended to save station name maps in pdf format, as station names will be searchable inside the file.
    An horizontal label will only fit if no MIs are plotted, as the second colourbar for the MIs will occupy the free space.
    The European FIR area can also be added to this plots. See option '--fireu' in "SBAS AVAILABILITY" plots below.

 Example:
       Generate one plot:      graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 139 
       Generate two plots:     graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 139 --rv 141 --mih 149 --grid off
       Generate three plots:   graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 139 --rv 141 --sn 3 --mih 149 --miv 151 

 Example for saving the plots: 
       graph.py -f /home/gLAB/Example --wir  -x 5 -y 7 --rv 141 --miv 151 --rh 139 --mih 149 --xmin -30 --xmax 40 --ymin 25 --ymax 75  --sv /home/Desktop/Figure_V.eps --sv /home/Desktop/Figure_H.eps --sv /home/Desktop/Figure_Station_Map.pdf

SBAS AVAILABILITY, CONTINUITY AND DOP PLOTS:

  In this mode: 

  The input file should have this fixed format (this is gLAB's output format):

  The first three lines have the header with this format (numerical values can vary according to the plot):
    For SBAS Availability map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 315 2016     86400     120      5.00
       #  LAT     LON AVAIL% NUMAVAIL NUMEPOCHS

    NOTE: Previous versions of gLAB (5.2.0 and below) only had 4 fields in the third header line of the availability
           map (e.g. '#  LAT     LON AVAIL%'). This old file format is also accepted.

    For SBAS Continuity Risk map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 315 2016     86400     120      5.00          15
       #  LAT     LON      CONT-RISK    NUMRISK NUMEPOCHS

    NOTE: Previous versions of gLAB (5.2.0 and below) only had 4 fields in the third header line of the continuity risk
           map (e.g. '#  LAT     LON      CONT-RISK'). This old file format is also accepted.

    For SBAS Maritime Continuity Risk map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE
         25.00  70.00  -30.00   40.00       1.00       0.00 100000 100000 315 2016     86400     120      5.00         900
       #  LAT     LON      CONT-RISK NUMDISCONT NUMEPOCHS

    For SBAS Ionosphere Availability map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION DoY YEAR NUMEPOCHS GEO-PRN
         65.00  73.00   30.00   40.00       0.10 255 2016       288     120
       #  LAT     LON AVAIL% NUMAVAIL NUMEPOCHS

    NOTE: Previous versions of gLAB (5.2.0 and below) only had 4 fields in the third header line of the ionosphere
           availability map (e.g. '#  LAT     LON AVAIL%'). This old file format is also accepted.

    For SBAS HDOP map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 026 2018     86400       0      5.00
       #  LAT     LON    MEANHDOP       TOTALHDOP NUMEPOCHS    PERCENT95

    For SBAS PDOP map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 026 2018     86400       0      5.00
       #  LAT     LON    MEANPDOP       TOTALPDOP NUMEPOCHS    PERCENT95

    For SBAS GDOP map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 026 2018     86400       0      5.00
       #  LAT     LON    MEANGDOP       TOTALGDOP NUMEPOCHS    PERCENT95

    For SBAS combined DOP map (file with HDOP, PDOP and GDOP):
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 026 2018     86400       0      5.00
       #  LAT     LON    MEANHDOP       TOTALHDOP    PERCENT95    MEANPDOP       TOTALPDOP    PERCENT95    MEANGDOP       TOTALGDOP    PERCENT95 NUMEPOCHS


  Graph program will automatically detect which type of input file is given using the header, 
  and will read the map size from the header.

  Since the fourth row, each row should provide the following values: latitude, longitude, value.

  For DOP files, the default option is to do only the mean DOP map. To do an additional map with the
  percentile values, set option '--doppercentileplot'.

  The combined DOP file will make a plot for HDOP, PDOP and GDOP in a single run.

  For GRAPHIC GENERAL OPTIONS, only the option to set the title "--title" is enabled. If non set,
                               a title will be set automatically. The plot region will be
                               automatically set from the header values.

  For PLOT DEPENDENT OPTIONS, the options "-f" works the same way as in the default plots,
                              while the other options in this part are disabled in this mode.

  MULTIPLE PLOTS are disabled in this mode.

  For SAVE CURRENT GRAPHIC,   it works the same way as for the default plots.

  --sbas, --SBAS                              Make a SBAS map

  --bineqcond,                                When assigning values to the bins, the condition thresholds
  --BinEqCond,                                  will be 'equal or greater than' (for availability and ionosphere
  --binequalcondition,                          plots) and 'equal or less than' (for continuity and DOP plots)
  --BinEqualCondition                           instead of 'greater than' or 'less than'

  --disablebineqcond,                         Option '--bineqcond' is by default disabled, but the options
  --DisableBinEqCond,                           '--sbasserviceformat', '--sbasservicemaritimeformat',
  --disablebinequalcondition,                   '--sbasservicebinaryformat' or '--sbasservicemaritimebinaryformat'
  --DisableBinEqualCondition                    will enable '--bineqcond' option. With this option you can force
                                                the program to keep it disabled.

  --disablenotavailbin,                       Disable the bin at the bottom of the colourbar with the text "NA" (Not Available)
  --DisableNotAvailBin                        The values in this bin were set according to this criteria:
                                                  - In availability and ionosphere availability maps, all values
                                                    larger than 100 or with the number of epochs equal to 0
                                                  - In continuity and continuity risk maps, all values larger
                                                    than 1 or with the number of epochs equal to 0
                                                  - In DOP maps, all values with the number of epochs equal to 0

  --notavailbincolor,          <color>        Set the colour for the "NA" (Not Available) bin. The colour must be
  --NotAvailBinColor                            using the rgb code with a hash ('#') at the beginning or with one
                                                values shown in the '--color' option.

  --notavailbintext,            <text>        Set the text for the "NA" (Not Available) bin to be shown in the colourbar.
  --NotAvailBinText

  --contriskaspercentage,                     In continuity risk and maritime continuity risk plots, show the bin values as the
  --ContRiskAsPercentage                        continuity percentage instead of the continuity risk. That is, the bin values
                                                shown will computed as: 100*(1-binvalue), converting also the symbols "<" and
                                                "<=" to ">" and ">=" respectively.

  --availmapbins,              #,#,...        Set a custom list of bins for the availability plot. The list
  --AvailMapBins                                must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values smaller or equal than the
                                                smallest bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 20.0,50.0,75.0,90.0,95.0,97.5,99.0,99.5,99.9

  --contriskmapbins,           #,#,...        Set a custom list of bins for the continuity risk plot. The list
  --ContRiskMapBins                             must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values equal or greater than the
                                                greater bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 1e-2,7.5e-3,5e-3,2.5e-3,1e-3,7.5e-4,5e-4,2.5e-4,1e-4,1e-5

  --contriskmarmapbins,        #,#,...        Set a custom list of bins for the maritime continuity risk plot. The
  --ContRiskMarMapBins                          list must be comma (',') separated. The program will automatically add two bins:
                                                one for all values greater than one ('1') and a bin with all values
                                                equal or greater than the greater bin value provided but smaller than 1.
                                                Values may be provided in any order, as they will be automatically sorted. 
                                                DEFAULT: 1e-2,7.5e-3,5e-3,2.5e-3,1e-3,7.5e-4,5e-4,2.5e-4,1e-4,1e-5

  --ionoavailmapbins,          #,#,...        Set a custom list of bins for the ionosphere availability plot. The list
  --IonoAvailMapBins                            must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values smaller or equal than the
                                                smallest bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 20.0,50.0,75.0,90.0,95.0,97.5,99.0,99.5,99.9

  --hdopmapbins,               #,#,...        Set a custom list of bins for the Horizontal DOP (HDOP) plot. The list
  --HDOPMapBins                                 must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values greater or equal than the
                                                greater bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 4,2

  --pdopmapbins,               #,#,...        Set a custom list of bins for the Position DOP (PDOP) plot. The list
  --PDOPMapBins                                 must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values greater or equal than the
                                                greater bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 6,3.5

  --gdopmapbins,               #,#,...        Set a custom list of bins for the Geometric DOP (GDOP) plot. The list
  --GDOPMapBins                                 must be comma (',') separated. The program will automatically add a
                                                bin in the beginning as all values greater or equal than the
                                                greater bin value provided. Values may be provided in any order, as
                                                they will be automatically sorted. 
                                                DEFAULT: 7,5

  --availmapbinstext,   <text1>;<text2>;...   Set a custom list with the text to be shown in the bins of the colourbar
  --AvailMapBinsText                            for the availability plot. The list must be semicolon (';') separated, 
                                                with the same number of items plus one as in the default colourbar or
                                                the same number plus one as set with parameter '--availmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                smaller than the minimum bin provided.

  --contriskmapbinstext, <text1>;<text2>;...  Set a custom list with the text to be shown in the bins of the colourbar
  --ContRiskMapBinsText                         for the continuity risk plot. The list must be semicolon (';') separated, 
                                                with the same number of items plus one as in the default colourbar or
                                                the same number plus one as set with parameter '--contriskmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                greater than the maximum bin provided.

  --contriskmarmapbinstext, <text1>;<text2>;... Set a custom list with the text to be shown in the bins of the colourbar
  --ContRiskMarMapBinsText                      for the maritime continuity risk plot. The list must be semicolon (';')
                                                separated,with the same number of items plus one as in the default colourbar
                                                or the same number plus one as set with parameter '--contriskmarmapbins'.
                                                The additional bin is to account for the bin that gLAB adds for all values
                                                greater than the maximum bin provided.

  --ionoavailmapbinstext, <text1>;<text2>;... Set a custom list with the text to be shown in the bins of the colourbar
  --IonoAvailMapBinsText                        for the ionosphere availability plot. The list must be semicolon (';')
                                                separated, with the same number of items plus one as in the default colourbar
                                                or the same number plus one as set with parameter '--ionoavailmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                smaller than the minimum bin provided.

  --hdopmapbinstext,    <text1>;<text2>;...   Set a custom list with the text to be shown in the bins of the colourbar
  --HDOPMapBinsText                             for Horizontal DOP (HDOP) plot. The list must be semicolon (';') separated, 
                                                with the same number of items plus one as in the default colourbar or
                                                the same number plus one as set with parameter '--hdopmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                greater than the maximum bin provided.

  --pdopmapbinstext,    <text1>;<text2>;...   Set a custom list with the text to be shown in the bins of the colourbar
  --PDOPMapBinsText                             for the Position DOP (PDOP) plot. The list must be semicolon (';') separated, 
                                                with the same number of items plus one as in the default colourbar or
                                                the same number plus one as set with parameter '--pdopmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                greater than the maximum bin provided.

  --gdopmapbinstext,    <text1>;<text2>;...   Set a custom list with the text to be shown in the bins of the colourbar
  --GDOPMapBinsText                             for the Geometric DOP (GDOP) plot. The list must be semicolon (';') separated, 
                                                with the same number of items plus one as in the default colourbar or
                                                the same number plus one as set with parameter '--gdopmapbins'. The 
                                                additional bin is to account for the bin that gLAB adds for all values
                                                greater than the maximum bin provided.

  --availcontourlevels,        #,#,...        Set the levels list for drawing the availability map contour lines.
  --AvailContourLevels,                         The list must be comma (',') separated, and the values provided must be
  --availcontourlines,                           in the list of bins provided with '--availmapbins' parameter (or the
  --AvailContourLines                           default bins if not provided. Values may be provided in any order,
                                                as they will be automatically sorted.
                                                DEFAULT: 95.0,97.5,99.9

  --contriskcontourlevels,     #,#,...        Set the levels list for drawing the continuity risk map contour lines.
  --ContRiskContourLevels,                      The list must be comma (',') separated, and the values provided must be
  --contriskcontourlines,                       in the list of bins provided with '--contriskmapbins' parameter (or the
  --ContRiskContourLines                        default bins if not provided. Values may be provided in any order,
                                                as they will be automatically sorted.
                                                DEFAULT: 1e-3,5e-4

  --contriskmarcontourlevels,  #,#,...        Set the levels list for drawing the continuity maritime risk map contour lines.
  --ContRiskMarContourLevels,                   The list must be comma (',') separated, and the values provided must be in the
  --contriskmarcontourlines,                    in the list of bins provided with '--contriskmarmapbins' parameter (or the
  --ContRiskMarContourLines                     default bins if not provided. Values may be provided in any order,
                                                as they will be automatically sorted.
                                                DEFAULT: 1e-3,5e-4

  --availbincolors,        <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',')  separated list for each
  --AvailBinColors                              bin in the availability map. The number of colours must be the number of bins
                                                plus 1 provided in the '--availmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values smaller than 
                                                the minimum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning
                                                or with one the values shown in the '--color' option.

  --contriskbincolors,     <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each
  --ContRiskBinColors                           bin in the continuity risk map. The number of colours must be the number of bins
                                                plus 1 provided in the '--contriskmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values greater than 
                                                the maximum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning 
                                                or with one the values shown in the '--color' option.

  --contriskmarbincolors,  <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each
  --ContRiskMarBinColors                        bin in the maritime continuity risk map. The number of colours must be the number of bins
                                                plus 2 provided in the '--contriskmarmapbins' parameter (by default 11 colours). 
                                                gLAB adds an extra bin for all values greater than the maximum bin provided.
                                                The list of colours MUST be ordered, starting with the colour of the smallest bin
                                                and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning
                                                or with one the values shown in the '--color' option.
                                                For example, the default colours used for the maritime continuity risk map are:
                                                "#000080,#0000F3,#004DFF,#00B3FF,#29FFCE,#7BFF7B,#CEFF29,#FFC600,#FF6800,#F30900"

  --ionoavailbincolors,    <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each bin
  --IonoAvailBinColors                          in the ionosphere availability map. The number of colours must be the number of bins
                                                plus 1 provided in the '--ionoavailmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values smaller than 
                                                the minimum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning 
                                                or with one the values shown in the '--color' option.

  --hdopbincolors,         <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each
  --HDOPBinColors                               bin in the Horizontal DOP (HDOP) map. The number of colours must be the number of bins
                                                plus 1 provided in the '--hdopmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values greater than 
                                                the maximum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning
                                                or with one the values shown in the '--color' option.

  --pdopbincolors,         <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each
  --PDOPBinColors                               bin in the Position DOP (PDOP) map. The number of colours must be the number of bins
                                                plus 1 provided in the '--pdopmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values greater than 
                                                the maximum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning 
                                                or with one the values shown in the '--color' option.

  --gdopbincolors,         <val1>,<val2>,...  Set the colours to be used in the colour bar in a comma (',') separated list for each
  --GDOPBinColors                               bin in the Geometric DOP (GDOP) map. The number of colours must be the number of bins
                                                plus 1 provided in the '--gdopmapbins' parameter (by default 10 colours). 
                                                The extra colour is due to gLAB adds an extra bin for all values greater than 
                                                the maximum bin provided. The list of colours MUST be ordered, starting with 
                                                the colour of the smallest bin and ending with the colour of the highest bin. 
                                                The colour must be set using the rgb code with a hash ('#') at the beginning 
                                                or with one the values shown in the '--color' option.

  --sbasserviceformat,                        Set the SBAS maps to an alternative format. In this format, contour lines
  --SBASServiceFormat                           are disabled by default, but can be enabled by manually setting the contour
                                                levels with any of these parameters: '--availcontourlevels',
                                                '--contriskcontourlevels' or '--contriskmarcontourlevels'.

                                                Availability Maps:
                                                  Bin values: >=99.9,>=99,>=98,>=95,>=90,>=80,>=70,<70
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Continuity Risk Maps:
                                                  Bin values: <=1e-4,<=5e-4,<=1e-3,<=5e-3,<=1e-2,<=2e-2,<=3e-2,>3e-2
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Maritime Continuity Risk Maps:
                                                  Bin values: <=1e-4,<=5e-4,<=1e-3,<=5e-3,<=1e-2,<=2e-2,<=3e-2,>3e-2
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Ionosphere Availability Maps:
                                                  Bin values: >=99.9,>=99,>=98,>=95,>=90,>=80,>=70,<70
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                HDOP Maps:
                                                  Bin values: <2,<4,>=4 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                PDOP Maps:
                                                  Bin values: <3.5,<6,>=6 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                GDOP Maps:
                                                  Bin values: <5,<7,>=7 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour

                                                NOTES:
                                                   - If user manually sets the bin values or bin colours, the user options
                                                     will prevail
                                                   - The user change the bin thresholds from ">=" or "<=" to ">" or "<" respectively by
                                                     setting the option '--disablebineqcond'

  --sbasservicemaritimeformat,                  Set the SBAS maps to an alternative format. In this format, contour lines
  --SBASServiceMaritimeFormat                     are disabled by default, but can be enabled by manually setting the contour
                                                levels with any of these parameters: '--availcontourlevels',
                                                '--contriskcontourlevels' or '--contriskmarcontourlevels'.

                                                Availability Maps:
                                                  Bin values: >=99.8,>=99.5,>=99,>=97.5,>=95,>=90,>=70,<70
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Continuity Risk Maps:
                                                  Bin values: <=3e-4,<=4e-4,<=5e-4,<=7e-4,<=1e-3,<=1e-2,>1e-1
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Maritime Continuity Risk Maps:
                                                  Bin values: <=3e-4,<=4e-4,<=5e-4,<=7e-4,<=1e-3,<=1e-2,>1e-1
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                Ionosphere Availability Maps:
                                                  Bin values: >=99.8,>=99.5,>=99,>=97.5,>=95,>=90,>=70,<70
                                                  Bin colours: #00008b,#0040ff,#00ffff,#00ff00,#ffff00,#ffa500,#ff0000,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                HDOP Maps:
                                                  Bin values: <2,<4,>=4 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                PDOP Maps:
                                                  Bin values: <3.5,<6,>=6 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour
                                                GDOP Maps:
                                                  Bin values: <5,<7,>=7 (same as the default ones)
                                                  Bin colours: #00008b,#ffa500,#8b0000
                                                  Not Avail bin is enabled and with default colour

                                                NOTES: 
                                                   - If user manually sets the bin values or bin colours, the user options
                                                     will prevail
                                                   - The user change the bin thresholds from ">=" or "<=" to ">" or "<" respectively by
                                                     setting the option '--disablebineqcond'

  --sbasservicebinaryformat,                  Set the SBAS maps to an alternative format that only has two bins (plus
  --SBASServiceBinaryFormat                     the 'Not Avail' bin). The bin texts are 'Not \\n Compliant' and 'Compliant'
                                                This format is useful for visually checking if a condition is met or not
                                                (e.g. availability >=99.8). The user may change the bin value to set the
                                                desired condition. Also, contour lines are disabled by default, but can be
                                                enabled by manually setting the contour levels with any of these parameters:
                                                '--availcontourlevels', '--contriskcontourlevels' or '--contriskmarcontourlevels'.
                                                The default values for this format are:

                                                Availability Maps:
                                                  Bin values: >=99.9,<99.9
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "          >=99.9%" (the spaces are for padding the text to the right)
                                                Continuity Risk Maps:
                                                  Bin values: <=1e-4,>1e-4
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "           <=1e-4" (the spaces are for padding the text to the right)
                                                Maritime Continuity Risk Maps:
                                                  Bin values: <=1e-4,>1e-4
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "           <=1e-4" (the spaces are for padding the text to the right)
                                                Ionosphere Availability Maps:
                                                  Bin values: >=99.9,<99.9
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "          >=99.9%" (the spaces are for padding the text to the right)
                                                HDOP Maps:
                                                  Bin values: <4,>=4 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <4" (the spaces are for padding the text to the right)
                                                PDOP Maps:
                                                  Bin values: <6,>=6 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <6" (the spaces are for padding the text to the right)
                                                GDOP Maps:
                                                  Bin values: <7,>=7 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <7" (the spaces are for padding the text to the right)

                                                NOTES: 
                                                   - If user manually sets the bin values, bin colours or bin texts, the user options will prevail
                                                   - If user changes the bin value, the colourbar title will show the user defined bin value
                                                   - The user change the bin thresholds from ">=" or "<=" to ">" or "<" respectively by
                                                     setting the option '--disablebineqcond'

  --sbasservicemaritimebinaryformat,          Set the SBAS maps to an alternative format that only has two bins (plus
  --SBASServiceMaritimeBinaryFormat             the 'Not Avail' bin). The bin texts are 'Not \\n Compliant' and 'Compliant'
                                                This format is useful for visually checking if a condition is met or not
                                                (e.g. availability >=99.8). The user may change the bin value to set the
                                                desired condition. Also, contour lines are disabled by default, but can be
                                                enabled by manually setting the contour levels with any of these parameters:
                                                '--availcontourlevels', '--contriskcontourlevels' or '--contriskmarcontourlevels'.
                                                The default values for this format are:

                                                Availability Maps:
                                                  Bin values: >=99.8,<99.8
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "          >=99.8%" (the spaces are for padding the text to the right)
                                                Continuity Risk Maps:
                                                  Bin values: <=3e-4,>3e-4
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "           <=3e-4" (the spaces are for padding the text to the right)
                                                Maritime Continuity Risk Maps:
                                                  Bin values: <=3e-4,>3e-4
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "           <=3e-4" (the spaces are for padding the text to the right)
                                                Ionosphere Availability Maps:
                                                  Bin values: >=99.8,<99.8
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "          >=99.8%" (the spaces are for padding the text to the right)
                                                HDOP Maps:
                                                  Bin values: <4,>=4 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <4" (the spaces are for padding the text to the right)
                                                PDOP Maps:
                                                  Bin values: <6,>=6 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <6" (the spaces are for padding the text to the right)
                                                GDOP Maps:
                                                  Bin values: <7,>=7 
                                                  Bin colours: #ffffff,#006400
                                                  Colourbar title: "  <7" (the spaces are for padding the text to the right)

                                                NOTES: 
                                                   - If user manually sets the bin values, bin colours or bin texts, the user options will prevail
                                                   - If user changes the bin value, the colourbar title will show the user defined bin value
                                                   - The user change the bin thresholds from ">=" or "<=" to ">" or "<" respectively by
                                                     setting the option '--disablebineqcond'

  --availcbartitle,             <text>        Set the title for the colourbar in the availability maps
  --AvailCbarTitle

  --contriskcbartitle,          <text>        Set the title for the colourbar in the continuity risk maps
  --ContRiskCbarTitle

  --contriskmarcbartitle,       <text>        Set the title for the colourbar in the maritime continuity risk maps
  --ContRiskMarCbarTitle

  --ionoavailcbartitle,         <text>        Set the title for the colourbar in the ionosphere availability maps
  --IonoAvailCbarTitle

  --hdopcbartitle,              <text>        Set the title for the colourbar in the Horizontal DOP (HDOP) maps
  --HDOPCbarTitle

  --pdopcbartitle,              <text>        Set the title for the colourbar in the Position DOP (PDOP) maps
  --PDOPCbarTitle

  --gdopcbartitle,              <text>        Set the title for the colourbar in the Geometric DOP (GDOP) maps
  --GDOPCbarTitle

  --nocontourlines,                           Do not show contour lines in Availability, Continuity Risk or 
  --NoContourLines,                             Maritime Continuity Risk Maps
  --nocontourlevels,                            
  --NoContourLevels

  --nocbarpercent, --NoCbarPercent            Do not put the '%' sign in top of the colourbar

  --doppercentileplot,                        In DOP maps, also do percentile DOP plots
  --DOPPercentilePlot

  --CbarLabel, --cbarlabel      <text>        Add a label next to the colourbar

  --SBASSystemname,             <text>        Set the name of the SBAS system in the title, replacing the default
  --sbassystemname                              "SBAS" text in the default title.

  --PRNtext, --prntext          <text>        Replace the "PRN <number>" text in the default title with the given
                                              text. This is useful when the plot is from multiple PRNs, where the
                                              default PRN is 0.

  --PRNtextnewline, --prntextnewline          Move the "PRN <number>" to a newline below (instead of being next to
                                                the alarm limits and the pixel resolution)

  --firuser, --FIRUser      <filename>        Add a user defined FIR area through a text file. The text file must contain
                                                no header and each line at least two columns (separated by any number of spaces):
                                                one with the longitude and another with the latitude (in degrees, in ellipsoidal
                                                coordinates). Additional columns will be ignored. Also, lines starting with a 
                                                hash ('#') will be ignored.
                                                In order to be able to compute the degradation percentage inside the area, the
                                                FIR area must be closed by repeating the initial point at the end of the file.

                                                For setting multiple FIR areas, set this parameter as many times as necessary

  --fireu, --FIREu, --FIREU                   Add the external borders of the European FIR (Flight Information Region)
                                                area in the map (the European FIR coordinates are hardcoded in the program)

  --firconus, --FIRCONUS                      Add the external borders of the CONUS FIR (Flight Information Region)
                                                area in the map (the CONUS FIR coordinates are hardcoded in the program)

  --firalaska, --FIRAlaska                    Add the external borders of the Alaska FIR (Flight Information Region)
                                                area in the map (the Alaska FIR coordinates are hardcoded in the program)

  --fircanada, --FIRCanada                    Add the external borders of the Canada FIR (Flight Information Region)
                                                area in the map (the Canada FIR coordinates are hardcoded in the program)

  --firmexico, --FIRMexico                    Add the external borders of the Mexico FIR (Flight Information Region)
                                                area in the map (the Mexico FIR coordinates are hardcoded in the program)

  --firlinetype,                 <val>        Set the linewidth for FIR area border (see option '-s') [DEFAULT '--']
  --FIRLineType                                 Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

  --firlinetypeeu,               <val>        Same as '--firlinetype', but only applies to the European FIR area defined in
  --FIRLineTypeEu                               option '--fireu'.

  --firlinetypeconus,            <val>        Same as '--firlinetype', but only applies to the CONUS FIR area defined in
  --FIRLineTypeCONUS                            option '--firconus'.

  --firlinetypealaska,           <val>        Same as '--firlinetype', but only applies to the Alaska FIR area defined in
  --FIRLineTypeAlaska                           option '--firalaska'.

  --firlinetypecanada,           <val>        Same as '--firlinetype', but only applies to the Canada FIR area defined in
  --FIRLineTypeCanada                           option '--fircanada'.

  --firlinetypemexico,           <val>        Same as '--firlinetype', but only applies to the Mexico FIR area defined in
  --FIRLineTypeMexico                           option '--firmexico'.

  --firlinewidth,                    #        Set the linewidth for FIR area border [DEFAULT 2]
  --FIRLineWidth                                Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

  --firlinewidtheu,                  #        Same as '--firlinewidth', but only applies to the European FIR area defined in
  --FIRLineWidthEu                              option '--fireu'.

  --firlinewidthconus,               #        Same as '--firlinewidth', but only applies to the CONUS FIR area defined in
  --FIRLineWidthCONUS                           option '--firconus'.

  --firlinewidthalaska,              #        Same as '--firlinewidth', but only applies to the Alaska FIR area defined in
  --FIRLineWidthAlaska                          option '--firalaska'.

  --firlinewidthcanada,              #        Same as '--firlinewidth', but only applies to the Canada FIR area defined in
  --FIRLineWidthCanada                          option '--fircanada'.

  --firlinewidthmexico,              #        Same as '--firlinewidth', but only applies to the Mexico FIR area defined in
  --FIRLineWidthMexico                          option '--firmexico'.

  --firlinecolor,              <color>        Set the colour for the FIR area border [DEFAULT 'white' for availability maps,
  --FIRLineColor                                                                              'black' for world maps]
                                                Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

  --firlinecoloreu,            <color>        Same as '--firlinecolor', but only applies to the European FIR area defined in
  --FIRLineColorEu                              option '--fireu'.

  --firlinecolorconus,         <color>        Same as '--firlinecolor', but only applies to the CONUS FIR area defined in
  --FIRLineColorCONUS                           option '--firconus'.

  --firlinecoloralaska,        <color>        Same as '--firlinecolor', but only applies to the Alaska FIR area defined in
  --FIRLineColorAlaska                          option '--firalaska'.

  --firlinecolorcanada,        <color>        Same as '--firlinecolor', but only applies to the Canada FIR area defined in
  --FIRLineColorCanada                          option '--fircanada'.

  --firlinecolormexico,        <color>        Same as '--firlinecolor', but only applies to the Mexico FIR area defined in
  --FIRLineColorMexico                          option '--firmexico'.

  --firmarkersize,                   #        Set the marker size for FIR area border [DEFAULT 5]
  --FIRMarkerSize                               Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

  --firmarkersizeeu,                 #        Same as '--firmarkersize', but only applies to the European FIR area defined in
  --FIRMarkerSizeEu                             option '--fireu'.

  --firmarkersizeconus,              #        Same as '--firmarkersize', but only applies to the CONUS FIR area defined in
  --FIRMarkerSizeCONUS                          option '--firconus'.

  --firmarkersizealaska,             #        Same as '--firmarkersize', but only applies to the Alaska FIR area defined in
  --FIRMarkerSizeAlaska                         option '--firalaska'.

  --firmarkersizecanada,             #        Same as '--firmarkersize', but only applies to the Canada FIR area defined in
  --FIRMarkerSizeCanada                         option '--fircanada'.

  --firmarkersizemexico,             #        Same as '--firmarkersize', but only applies to the Mexico FIR area defined in
  --FIRMarkerSizeMexico                         option '--firmexico'.

  --nofirborder,                     #        Do not show the user defined FIR in the map. This option is useful if the user
  --NoFIRBorder                                 is only interested in computing the degradation percentage inside the FIR
                                                area (and printing it in the plot), but not the FIR area border itself.
                                                The parameter must come with the number of the user defined FIR that shall
                                                not be plotted. For instance, if user defines two FIR areas, and the second
                                                FIR area does not have to be plotted, then the parameter should be
                                                '--nofirborder 2'. This parameter must be provided for each user defined FIR
                                                area that shall not be plotted.

                                                NOTE: If the number provided is 0, all user defined FIR areas will not be plotted

  --nofirbordereu,                            Same as '--nofirborder', but only applies to the European FIR area defined in
  --NoFIRBorderEu                               option '--fireu'.

  --nofirborderconus,                         Same as '--nofirborder', but only applies to the CONUS FIR area defined in
  --NoFIRBorderCONUS                            option '--firconus'.

  --nofirborderalaska,                        Same as '--nofirborder', but only applies to the Alaska FIR area defined in
  --NoFIRBorderAlaska                           option '--firalaska'.

  --nofirbordercanada,                        Same as '--nofirborder', but only applies to the Canada FIR area defined in
  --NoFIRBorderCanada                           option '--fircanada'.

  --nofirbordermexico,                        Same as '--nofirborder', but only applies to the Mexico FIR area defined in
  --NoFIRBorderMexico                           option '--firmexico'.

  --firdegradation,                           Compute the availability degradation inside the FIR area and plot
  --FIRDegradation                              it in the map

  --firdegtextheader,           <text>         Set the header for the FIR availability degradation. This text will be printed
  --FIRDegTextHeader                             once for each availability area defined by the user, on top of the degradation
                                                 text. Set this option for each user defined FIR area (option '--firuser').
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextheadereu,         <text>         Set the header for the European FIR availability degradation. This text will be
  --FIRDegTextHeaderEu                           printed on top of the European area degradation text.
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextheaderconus,      <text>         Set the header for the CONUS FIR availability degradation. This text will be
  --FIRDegTextHeaderCONUS                        printed on top of the CONUS area degradation text.
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextheaderalaska,     <text>         Set the header for the Alaska FIR availability degradation. This text will be
  --FIRDegTextHeaderAlaska                       printed on top of the Alaska area degradation text.
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextheadercanada,     <text>         Set the header for the Canada FIR availability degradation. This text will be
  --FIRDegTextHeaderCanada                       printed on top of the Canada area degradation text.
                                                If option '--firdegtexttable' is set, it will change the the header title for this FIR

  --firdegtextheadermexico,     <text>         Set the header for the Mexico FIR availability degradation. This text will be
  --FIRDegTextHeaderMexico                       printed on top of the Mexico area degradation text.
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextheaderfirsum,     <text>         Set the header for all FIR availability degradation. This text will be
  --FIRDegTextHeaderFIRSum                       printed on top of all FIR area degradation text.
                                                 This option also sets '--firsumdeg'. 
                                                If option '--firdegtexttable' is set, it will change the header title for this FIR

  --firdegtextfooter,           <text>         Set the footer for the FIR availability degradation. This text will be printed
  --FIRDegTextFooter                             once for each availability area defined by the user, below the last degradation
                                                text. Set this option for each user defined FIR area drawn (option '--firuser').

  --firdegtextfootereu,         <text>         Set the footer for the European FIR availability degradation. This text will be
  --FIRDegTextFooterEu                           printed below the European area degradation text.

  --firdegtextfooterconus,      <text>         Set the footer for the CONUS FIR availability degradation. This text will be
  --FIRDegTextFooterCONUS                        printed below the CONUS area degradation text.

  --firdegtextfooteralaska,     <text>         Set the footer for the Alaska FIR availability degradation. This text will be
  --FIRDegTextFooterAlaska                       printed below the Alaska area degradation text.

  --firdegtextfootercanada,     <text>         Set the footer for the Canada FIR availability degradation. This text will be
  --FIRDegTextFooterCanada                       printed below the Canada area degradation text.

  --firdegtextfootermexico,     <text>         Set the footer for the Mexico FIR availability degradation. This text will be
  --FIRDegTextFooterMexico                       printed below the Mexico area degradation text.

  --firdegtextfooterfirsum,     <text>         Set the footer for all FIR availability degradation. This text will be
  --FIRDegTextFooterFIRSum                       printed below the all FIR area degradation text.
                                                 This option also sets '--firsumdeg'. 

  --firdegtext,                 <text>        Set the text for the FIR availability degradation (only if option '--firdegtexttable'
  --FIRDegText                                  is not set).  This text will be printed for each bin defined with parameter
                                                '--firdegtextbins', or if none defined, using the bin at the top of the colourbar.  
                                                The default text is:
                                                  '>{2:.1f}: {0:.2f}%
                                                   <={2:.1f}: {1:.2f}%'
                                                Note that '{0:.2f} sets to write the availability percentage value with 
                                                two decimals, '{1:.2f}' sets to write the unavailability percentage
                                                with two decimals and {2:.1f} sets to write the current bin value with
                                                one decimal. If any of these are not set, the value missing will not
                                                be printed. For example, to print only the availability percentage with
                                                one decimal and no other text but a percentage, the string would be: 
                                                '{0:.1f}%'
                                                For example, to print the unavailability percentage with one decimal to get
                                                text such as "<99.9: 1.2%", the string would be: '<{2:.1f}: {1:.1f}%'

                                                NOTES: 
                                                 - To print a literal curly-brace ('{' or '}'), set double number of curly
                                                braces. For example, if the desired text is 'Avail {80%}', the string to be
                                                passed by parameter shall be 'Avail {{{0:.0f}%}}'.

                                                 - The total number of points inside the FIR area, the number of points over
                                                the bin value and below the bin value (inside the FIR area) can be also printed
                                                (the values used to compute the percentages). Use the following formats:
                                                  {0:.1f} -> Percentage of points over the bin value inside the FIR area
                                                  {1:.1f} -> Percentage of points below the bin value inside the FIR area
                                                  {2:.1f} -> Value of the current bin (for continuity risk bins, use
                                                               the exponential format, for instance: {2:.1e})
                                                  {3:d} -> Number of points over the bin value inside the FIR area
                                                  {4:d} -> Number of points below the bin value inside the FIR area
                                                  {5:d} -> Total number of points inside the FIR area
                                                  {6:d} -> Total number of points in the whole plot

                                                Set this option for each user defined FIR area drawn (option '--firuser').

  --firdegtexteu,               <text>        Same as '--firdegtext', but only applies to the European FIR area defined in
  --FIRDegTextEu                                option '--fireu'.

  --firdegtextconus,            <text>        Same as '--firdegtext', but only applies to the CONUS FIR area defined in
  --FIRDegTextCONUS                             option '--firconus'.

  --firdegtextalaska,           <text>        Same as '--firdegtext', but only applies to the Alaska FIR area defined in
  --FIRDegTextAlaska                            option '--firalaska'.

  --firdegtextcanada,           <text>        Same as '--firdegtext', but only applies to the Canada FIR area defined in
  --FIRDegTextCanada                            option '--fircanada'.

  --firdegtextmexico,           <text>        Same as '--firdegtext', but only applies to the Mexico FIR area defined in
  --FIRDegTextMexico                            option '--firmexico'.

  --firdegtextfirsum,           <text>        Same as '--firdegtext', but applies to the degradation which is the total sum
  --FIRDegTextFIRSum                            of all FIR areas defined and set to be added.
                                                When setting this option (computing the total degradation of all FIR areas),
                                                the bins used in each FIR area must be the same for all of them. 
                                                This option also sets '--firsumdeg'. 

  --firsumdeg,                                Compute the total degradation for all FIR areas defined and print the result.
  --FIRSumDeg                                   If any of the options '--firdegtextfirsum', '--firdegtextsizefirsum',
                                                '--firdegtextcolorfirsum' or '--firdegtextpositionfirsum' are set, default
                                                values will be set. 

                                                NOTES:
                                                 - If none of these options '--firsumdegeu', '--firsumdegconus',
                                                   '--firsumdegAlaska', '--firsumdegcanada', '--firsumdegmexico',
                                                   '--firsumdeguserfir' are provided, it will select all FIR areas enabled.
                                                   Otherwise, if any of these options are provided, only the selected FIR
                                                   areas will be used

                                                 - If several FIR areas overlap, each overlapped point will count only once,
                                                   and the value used will be the best of all FIRs (as it is enough for any
                                                   area in the map to be covered by one system or GEO).
                                                   
                                                 - If this option is set and the degradation text is not printed in a table,
                                                   all degradation bins must have the same values.

                                                 - If option '--firsumdegtexttitle' is not set. the default title is "All FIRs".

  --firsumdegeu,                              Select Eu FIR area to be added to the total degradation sum.
  --FIRSumDegEu

  --firsumdegconus,                           Select CONUS FIR area to be added to the total degradation sum.
  --FIRSumDegCONUS

  --firsumdegalaska,                          Select Alaska FIR area to be added to the total degradation sum.
  --FIRSumDegAlaska

  --firsumdegcanada,                          Select Canada FIR area to be added to the total degradation sum.
  --FIRSumDegCanada

  --firsumdegmexico,                          Select Mexico FIR area to be added to the total degradation sum.
  --FIRSumDegMexico

  --firsumdeguserfir,          #,#,...        Select user defined FIR areas (defined with parameter '--firuser') to be added to the
  --FIRSumDegUserFIR                            total degradation sum (in a comma separated list). 
                                              If value is 0, it will select all user defined FIR areas.

  --firdegtextbins,            #,#,...        Set the bins for which the degradation will be computed and written (using the
  --FIRDegTextBins                              text provided with '--firdegtext' or the default value). The bins values must
                                                be comma (',') separated, and must be any of the bins provided with parameters
                                                '--availmapbins', '--contriskmapbins', '--contriskmarmapbins','--ionoavailmapbins',
                                                '--hdopmapbins', '--pdopmapbins' or '--gdopmapbins'. The order is not important
                                                as they will be automatically sorted.

                                                NOTES: 
                                                 - If option '--contriskaspercentage' is set and it is a Continuity Risk or
                                                   Maritime Continuity Risk plot, the bins can also be set as a percentage.

                                                 - If option '--firdegtexttable' is set, this parameter will set the bin
                                                   values of the table


  --firdegtextbinseu,          #,#,...        Same as '--firdegtextbins', but only applies to the European FIR area defined in
  --FIRDegTextBinsEu                            option '--fireu'.

  --firdegtextbinsconus,       #,#,...        Same as '--firdegtextbins', but only applies to the CONUS FIR area defined in
  --FIRDegTextBinsCONUS                         option '--firconus'.

  --firdegtextbinsalaska,      #,#,...        Same as '--firdegtextbins', but only applies to the Alaska FIR area defined in
  --FIRDegTextBinsAlaska                        option '--firalaska'.

  --firdegtextbinscanada,      #,#,...        Same as '--firdegtextbins', but only applies to the Canada FIR area defined in
  --FIRDegTextBinsCanada                        option '--fircanada'.

  --firdegtextbinsmexico,      #,#,...        Same as '--firdegtextbins', but only applies to the Mexico FIR area defined in
  --FIRDegTextBinsMexico                        option '--firmexico'.

  --firdegtextsize,                  #        Set the text size for the FIR availability degradation [DEFAULT 5]
  --FIRDegTextSize                              Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

                                                NOTE: If option '--firdegtexttable' is set, this parameter will set the text
                                                size of the table

  --firdegtextsizeeu,                #        Same as '--firdegtextsize', but only applies to the European FIR area defined in
  --FIRDegTextSizeEu                            option '--fireu'.

  --firdegtextsizeconus,             #        Same as '--firdegtextsize', but only applies to the CONUS FIR area defined in
  --FIRDegTextSizeCONUS                         option '--firconus'.

  --firdegtextsizealaska,            #        Same as '--firdegtextsize', but only applies to the Alaska FIR area defined in
  --FIRDegTextSizeAlaska                        option '--firalaska'.

  --firdegtextsizecanada,            #        Same as '--firdegtextsize', but only applies to the Canada FIR area defined in
  --FIRDegTextSizeCanada                        option '--fircanada'.

  --firdegtextsizemexico,            #        Same as '--firdegtextsize', but only applies to the Mexico FIR area defined in
  --FIRDegTextSizeMexico                        option '--firmexico'.

  --firdegtextsizefirsum,            #        Same as '--firdegtextsize', but only applies to the text for the sum of the
  --FIRDegTextSizeFIRSum                        degradation for all of the FIR areas defined
                                                This option also sets '--firsumdeg'. 

  --firdegtextcolor,           <color>        Set the text colour for the FIR availability degradation [DEFAULT 'white']
  --FIRDegTextColor                             Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

                                                NOTE: If option '--firdegtexttable' is set, this parameter will set the text
                                                colour of the table

  --firdegtextcoloreu,         <color>         Same as '--firdegtextcolor', but only applies to the European FIR area defined in
  --FIRDegTextColorEu                            option '--fireu'.

  --firdegtextcolorconus,      <color>         Same as '--firdegtextcolor', but only applies to the CONUS FIR area defined in
  --FIRDegTextColorCONUS                         option '--firconus'.

  --firdegtextcoloralaska,     <color>         Same as '--firdegtextcolor', but only applies to the Alaska FIR area defined in
  --FIRDegTextColorAlaska                        option '--firalaska'.

  --firdegtextcolorcanada,     <color>         Same as '--firdegtextcolor', but only applies to the Canada FIR area defined in
  --FIRDegTextColorCanada                        option '--fircanada'.

  --firdegtextcolormexico,     <color>         Same as '--firdegtextcolor', but only applies to the Mexico FIR area defined in
  --FIRDegTextColorMexico                        option '--firmexico'.

  --firdegtextcolorfirsum,     <color>         Same as '--firdegtextcolor', but only applies to the text for the sum of the
  --FIRDegTextColorFIRSum                        degradation for all of the FIR areas defined.
                                                 This option also sets '--firsumdeg'. 

  --firdegtextposition,            #,#        Set the text position for the FIR availability degradation.
  --FIRDegTextPosition                          Position must be given in x and y coordinates, separated by a comma (',') 
                                                (for example "0.3,0.5"). The coordinate are respect to the lower
                                                left corner of the plot [DEFAULT 0.245,0.88]
                                                Set this option for each user defined FIR area drawn (option '--firuser').
                                                If only one FIR area is drawn (including the European FIR area), this option
                                                will be set for that area (so it keeps compatibility with previous versions).

                                                NOTE: If option '--firdegtexttable' is set, this parameter will set the position
                                                position of the table

  --firdegtextpositioneu,          #,#        Same as '--firdegtextposition', but only applies to the European FIR area defined in
  --FIRDegTextPositionEu                         option '--fireu'.

  --firdegtextpositionconus,       #,#        Same as '--firdegtextposition', but only applies to the CONUS FIR area defined in
  --FIRDegTextPositionCONUS                      option '--firconus'.

  --firdegtextpositionalaska,      #,#        Same as '--firdegtextposition', but only applies to the Alaska FIR area defined in
  --FIRDegTextPositionAlaska                     option '--firalaska'.

  --firdegtextpositioncanada,      #,#        Same as '--firdegtextposition', but only applies to the Canada FIR area defined in
  --FIRDegTextPositionCanada                     option '--fircanada'.

  --firdegtextpositionmexico,      #,#        Same as '--firdegtextposition', but only applies to the Mexico FIR area defined in
  --FIRDegTextPositionMexico                     option '--firmexico'.

  --firdegtextpositionfirsum,      #,#        Same as '--firdegtextposition', but only applies to the text for the sum of the
  --FIRDegTextPositionFIRSum                     degradation for all of the FIR areas defined.
                                                 This option also sets '--firsumdeg'. 

  --nofirdegtext,              #,#,...        Do not print the degradation text in the map. This option is useful if the user
  --NoFIRDegText                                is only interested in showing the FIR border but does not want any degradation
                                                text to be printed (this FIR will also be skipped in the degradation table if
                                                option '--firdegtexttable').
                                                The parameter must come with a comma separated list with the number of the user
                                                defined FIR that shall not have degradation text. For instance, if user defines
                                                two FIR areas, and the second FIR area does not have to be plotted, then the
                                                parameter should be '--nofirdegtext 2'.

                                                NOTE: If the number provided is 0, all user defined FIR areas will not have
                                                degradation text printed.

  --nofirdegtexteu,                           Same as '--nofirdegtext', but only applies to the European FIR area defined in
  --NoFIRDegTextEu                              option '--fireu'.

  --nofirdegtextconus,                        Same as '--nofirdegtext', but only applies to the CONUS FIR area defined in
  --NoFIRDegTextCONUS                           option '--firconus'.

  --nofirdegtextalaska,                       Same as '--nofirdegtext', but only applies to the Alaska FIR area defined in
  --NoFIRDegTextAlaska                          option '--firalaska'.

  --nofirdegtextcanada,                       Same as '--nofirdegtext', but only applies to the Canada FIR area defined in
  --NoFIRDegTextCanada                          option '--fircanada'.

  --nofirdegtextmexico,                       Same as '--nofirdegtext', but only applies to the Mexico FIR area defined in
  --NoFIRDegTextMexico                          option '--firmexico'.                                                                                       

  --firdegtextmonospacefont,                  Set the FIR degradation type (for all FIRs texts in the plots) font to monospace.
  --FIRDegTextMonospaceFont                     The monospace font preserves the alignment of text (default 'sans-serif' font has,
                                                for instance, different widths for '1' and '0' characters). The monospace font
                                                is always used when option '--firdegtexttable' is set.

  --firdegtexttable,                          Show all degradation text FIR values in a table.
  --FIRDegTextTable                             The names for the user defined areas will be the filename (without extension). 
                                                Each row of data will be for each bin defined with parameter '--firdegtextbins', 
                                                and each column will be a different FIR area. Use parameters '--firdegtextsize', 
                                                '--firdegtextcolor' and '--firdegtextposition' for setting its properties. If
                                                these parameters are set multiple times, the values provided the first time will
                                                prevail.

  --printfirdegtext,                          Print the degradation text to standard output (does not work on Windows).
  --PrintFIRDegText                             If the FIR values are shown in table format (parameter '--firdegtexttable' is set),
                                                the whole table will be printed. Otherwise, each line of data will have its name
                                                of the FIR region prepended to the line, so as it can be distinguished from which
                                                FIR regions the current line belongs to. This option is compatible with
                                                '--writetofilefirdegtext' option.
                                                NOTE: Output text is encoded with 'utf-8'.

  --writetofilefirdegtext,  <filename>        Same as '--printfirdegtext' option, but instead of printing the FIR values to 
  --WriteToFileFIRDegText                       standard output, it will be written to the file provided (the output file
                                                will be truncated). This option is compatible with '--printfirdegtext' option.
                                                NOTE: Output text is encoded with 'utf-8'.

  --onlyprintfirdegtext,                      Do not show the plots, just print the degradation text to standard output or to a file
  --OnlyPrintFIRDegText                         (as in options '--printfirdegtext' and '--writetofilefirdegtext'). If option '--sv'
                                                is set (save picture to file), then this option has no effect, as with '--sv' option 
                                                plots are not shown.

  --sbasplotsize,                  #,#        Set the plotting area size, by providing the horizontal and vertical
  --SBASPlotSize                                size (in centimetres). The two values must be comma (',') separated.
                                                [DEFAULT 20.32,15.24]

  --sbastopfiguremargin,             #        Set the top figure margin by providing the fraction of image size
  --SBASTopFigureMargin                         to be left as margin (starting from the top). The range values are
                                                [0-0.5], being 0 no top margin. Adding top margin makes the figure
                                                move downwards in the plot area (shrinking if necessary).

  --sbasbottomfiguremargin,          #        Set the bottom figure margin by providing the fraction of image size
  --SBASBottomFigureMargin                      to be left as margin (starting from the bottom). The range values are
                                                [0-0.5], being 0 no bottom margin. Adding bottom margin makes the figure
                                                move upwards in the plot area (shrinking if necessary).

  --sbasleftfiguremargin,            #        Set the left figure margin by providing the fraction of image size
  --SBASLeftFigureMargin                        to be left as margin (starting from the left). The range values are
                                                [0-0.5], being 0 no left margin. Adding left margin makes the figure
                                                move to the right in the plot area (shrinking if necessary).

  --sbasrightfiguremargin,           #        Set the right figure margin by providing the fraction of image size
  --SBASRightFigureMargin                       to be left as margin (starting from the right). The range values are
                                                [0-0.5], being 0 no right margin. Adding right margin makes the figure
                                               move to the left in the plot area (shrinking if necessary).

  --countries,                                Draw the country borders in the map
  --Countries

  --usastates,                                Draw the USA states borders in the map
  --USAStates

  NOTE: If user sets a vertical label, the '--atm' option (adjust to margin) will be disabled in order to
        fit the vertical label

 Examples: 
       graph.py -f /home/gLAB/Example --sbas --sv /home/Desktop/SBASAvailMap.eps

       graph.py -f /home/gLAB/Example --SBAS

"""

GraphicParser = OptionParser(usage=HelpHeader,version="%prog 5.5.1") #This is for the case the user runs graph with parameter "--version"

GraphicParser.add_option("--title","--tit","-t", type="string", dest="Title", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ftitle","--ftitle","--ft", type="string", dest="FractionalTitle", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xlabel","--xlab","--xl" ,type="string", dest="Xlabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ylabel","--ylab","--yl" ,type="string", dest="Ylabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--file","-f" ,type="string", dest="filename", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xcol","-x","-X", "--error",type="string", dest="ColX", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ycol","-y","-Y", "--pl", type="string",dest="ColY", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cond","-c", type="string",dest="Cond", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--label","--plotlabel","-l", type="string",dest="PlotLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--style","-s", type="string",dest="Style", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 
GraphicParser.add_option("--grid","-g", type="string",dest="grid", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wm","--watermark", type="string",dest="WaterMark", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wmc","--watermarkcolor", type="string",dest="WaterMarkColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wms","--watermarksize", type="string",dest="WaterMarkSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wmp","--watermarkposition", type="string",dest="WaterMarkPosition", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--textmark",type="string",dest="TextMarkLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--textmarkc","--textmarkcolor", type="string",dest="TextMarkColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--textmarks","--textmarksize", type="string",dest="TextMarkSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--textmarkp","--textmarkposition", type="string",dest="TextMarkPosition", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xticks","--xticks","--xt", type="string",dest="Xticks", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Yticks","--yticks","--yt", type="string",dest="Yticks", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--XticksStep","--xticksstep","--xts", type="string",dest="XticksStep", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--YticksStep","--yticksstep","--yts", type="string",dest="YticksStep", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--XticksList","--xtickslist","--xtl", type="string",dest="XticksList", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--YticksList","--ytickslist","--ytl", type="string",dest="YticksList", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--AdjustToMargin","--adjusttomargin","--atm",  dest="AdjustToMargin", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--no-lock-file", dest="NoLockFile", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--colormap","--ColorMap", type="string",dest="ColorMap", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--numpointslabel","--NumPointsLabel","--npl", type="string",dest="NumPointsLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--labelpos","--labelPos","--lp", type="string",dest="LabelPosition", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--ms","--MarkerSize","--markersize",type="string",dest="MarkerSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 
GraphicParser.add_option("--lw","--LineWidth","--linewidth", type="string",dest="LineWidth", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 

GraphicParser.add_option("--save","--sv", type="string",dest="SaveFigure", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--color","--cl", type="string",dest="PlotColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xmin","--xmin","--xn", type="string",dest="Xmin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xmax","--xmax","--xx", type="string",dest="Xmax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ymin","--ymin","--yn", type="string",dest="Ymin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ymax","--ymax","--yx", type="string",dest="Ymax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)




GraphicParser.add_option("--stanford","--sf","--sp", dest="stanford", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--clean",dest="clean", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--AL","--al",type="string",dest="AL", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--xr","--xresolution",type="string",dest="resolution_x", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--yr","--yresolution",type="string",dest="resolution_y", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileX", "--percentilex", dest="StfdPercentileX", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileY", "--percentiley", dest="StfdPercentileY", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileXList","--percentilexlist",type="string",dest="percentileXList",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileYList","--percentileylist",type="string",dest="percentileYList",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availepochpos","--AvailEpochPos",type="string",dest="AvailEpochPos",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--unavailepochpos","--UnAvailEpochPos",type="string",dest="UnAvailEpochPos",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hmiepochpos","--HMIEpochPos",type="string",dest="HMIEpochPos",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--miavailepochpos","--MIAvailEpochPos",type="string",dest="MIAvailEpochPos",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--miunavailepochpos","--MIUnAvailEpochPos",type="string",dest="MIUnAvailEpochPos",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--stanfordESA","--sfesa","--spesa", dest="stanfordESA", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sfesawithregions","--sfESAWithRegions", dest="sfESAwithRegions", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sfesawithepochs","--sfESAWithEpochs", dest="sfESAWithEpochs", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--noepochsintitle","--NoEpochsInTitle","--nogeometriesintitle","--NoGeometriesInTitle", dest="NoEpochsInTitle", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hal","--HAL",type="string",dest="HAL", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--val","--VAL",type="string",dest="VAL", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--maxpoints","--MaxPoints",type="string",dest="maxpoints", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--map","--Map", dest="wir", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wir","--WIR", dest="wircolorbar", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sn","--staName","--SN", type="string",dest="ColName", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--rv","--ratioV","--RV", type="string",dest="ColRatioV", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--rh","--ratioH","--RH", type="string",dest="ColRatioH", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--miv","--MIV", type="string",dest="ColMIsV", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--mih","--MIH", type="string",dest="ColMIsH", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--projection","--pj", type="string",dest="projection", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarMin","--cbarmin","--cmin", type="string",dest="cbarMin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarMax","--cbarmax","--cmax", type="string",dest="cbarMax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarInterval","--cbarN","--cn", type="string",dest="cbarInterval", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--continentColor","--cc", type="string",dest="continentColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--lakeColor","--lc", type="string",dest="lakeColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--boundaryColor","--bc", type="string",dest="boundaryColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--mapres","--MapRes","--MapResolution", type="string",dest="MapResolution", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanet","--staNetwork", type="string",dest="ColStaNetwork", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetautolabel","--stanetAutoLabel", dest="StaNetAutoLabel",default=False, action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetwithnames","--staNetWithNames", dest="StaNetworkWithNames", default=False, action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultnamesize","--staNetDefaultNameSize", type="string",dest="StaNetworkDefaultNameSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultnamecolor","--staNetDefaultNameColor", type="string",dest="StaNetworkDefaultNameColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultnamealign","--staNetDefaultNameAlign", type="string",dest="StaNetworkDefaultNameAlign",nargs=2, action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetwithmarkers","--staNetWithMarkers", dest="StaNetworkWithMarkers", default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultmarkertype","--staNetDefaultMarkerType", type="string",dest="StaNetworkDefaultMarkerType", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultmarkersize","--staNetDefaultMarkerSize", type="string",dest="StaNetworkDefaultMarkerSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultmarkercolor","--staNetDefaultMarkerColor", type="string",dest="StaNetworkDefaultMarkerColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetdefaultlabel","--staNetDefaultLabel", type="string",dest="StaNetworkDefaultLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetlabel","--staNetworkLabel", type="string",dest="StaNetworkLabel",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetmarkertype","--staNetworkMarkerType", type="string",dest="StaNetworkMarkerType",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetmarkercolor","--staNetworkMarkerColor", type="string",dest="StaNetworkMarkerColor",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetmarkersize","--staNetworkMarkerSize", type="string",dest="StaNetworkMarkerSize",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetnamecolor","--staNetNameColor", type="string",dest="StaNetworkNameColor",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetnamesize","--staNetNameSize", type="string",dest="StaNetworkNameSize",nargs=2,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetnamealign","--staNetNameAlign", type="string",dest="StaNetworkNameAlign",nargs=3,action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--stanetlabelnumsta","--staNetLabelNumSta", dest="staNetLabelNumSta",default=False, action='store_true',help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--sbas","--SBAS", dest="sbas", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--bineqcond","--BinEqCond","--binequalcondition","--BinEqualCondition", dest="BinsEqualCondition", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--disablebineqcond","--DisableBinEqCond","--disablebinequalcondition","--DisableBinEqualCondition", dest="DisableBinEqualCondition", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--disablenotavailbin","--DisableNotAvailBin",dest="DisableNotAvailBin", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--notavailbincolor","--NotAvailBinColor",type="string",dest="NotAvailBinColor",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--notavailbintext","--NotAvailBinText",type="string",dest="NotAvailBinText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskaspercentage","--ContRiskAsPercentage", dest="ContRiskAsPercentage", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availmapbins","--AvailMapBins",type="string",dest="AvailMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmapbins","--ContRiskMapBins",type="string",dest="ContRiskMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmarmapbins","--ContRiskMarMapBins",type="string",dest="ContRiskMarMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--ionoavailmapbins","--IonoAvailMapBins",type="string",dest="IonoAvailMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hdopmapbins","--HDOPMapBins",type="string",dest="HDOPMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--pdopmapbins","--PDOPMapBins",type="string",dest="PDOPMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--gdopmapbins","--GDOPMapBins",type="string",dest="GDOPMapBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availmapbinstext","--AvailMapBinsText",type="string",dest="AvailMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmapbinstext","--ContRiskMapBinsText",type="string",dest="ContRiskMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmarmapbinstext","--ContRiskMarMapBinsText",type="string",dest="ContRiskMarMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--ionoavailmapbinstext","--IonoAvailMapBinsText",type="string",dest="IonoAvailMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hdopmapbinstext","--HDOPMapBinsText",type="string",dest="HDOPMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--pdopmapbinstext","--PDOPMapBinsText",type="string",dest="PDOPMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--gdopmapbinstext","--GDOPMapBinsText",type="string",dest="GDOPMapBinsText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availcontourlevels","--AvailContourLevels","--availcontourlines","--AvailContourLines",type="string",dest="AvailContourLevels",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskcontourlevels","--ContRiskContourLevels","--contriskcontourlines","--ContRiskContourLines",type="string",dest="ContRiskContourLevels",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmarcontourlevels","--ContRiskMarContourLevels","--contriskmarcontourlines","--ContRiskMarContourLines",type="string",dest="ContRiskMarContourLevels",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availbincolors","--AvailBinColors",type="string",dest="AvailBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskbincolors","--ContRiskBinColors",type="string",dest="ContRiskBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmarbincolors","--ContRiskMarBinColors",type="string",dest="ContRiskMarBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--ionoavailbincolors","--IonoAvailBinColors",type="string",dest="IonoAvailBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hdopbincolors","--HDOPBinColors",type="string",dest="HDOPBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--pdopbincolors","--PDOPBinColors",type="string",dest="PDOPBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--gdopbincolors","--GDOPBinColors",type="string",dest="GDOPBinColors",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasserviceformat","--SBASServiceFormat", dest="SBASServiceFormat", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasservicemaritimeformat","--SBASServiceMaritimeFormat", dest="SBASServiceMaritimeFormat", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasservicebinaryformat","--SBASServiceBinaryFormat", dest="SBASServiceBinaryFormat", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasservicemaritimebinaryformat","--SBASServiceMaritimeBinaryFormat", dest="SBASServiceMaritimeBinaryFormat", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--availcbartitle","--AvailCbarTitle",type="string",dest="AvailCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskcbartitle","--ContRiskCbarTitle",type="string",dest="ContRiskCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--contriskmarcbartitle","--ContRiskMarCbarTitle",type="string",dest="ContRiskMarCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--ionoavailcbartitle","--IonoAvailCbarTitle",type="string",dest="IonoAvailCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--hdopcbartitle","--HDOPCbarTitle",type="string",dest="HDOPCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--pdopcbartitle","--PDOPCbarTitle",type="string",dest="PDOPCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--gdopcbartitle","--GDOPCbarTitle",type="string",dest="GDOPCbarTitle",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nocontourlines","--NoContourLines", dest="SBASNoContourLines", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nocbarpercent","--NoCbarPercent",dest="NoCbarPercentage",default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--doppercentileplot","--DOPPercentilePlot",dest="DOPPercentilePlot",default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--CbarLabel","--cbarlabel",type="string",dest="ColourBarLabel",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--SBASSystemname","--sbassystemname",type="string",dest="SBASsystemname",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--PRNtext","--prntext",type="string",dest="SBASPRNtext",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--PRNtextnewline","--prntextnewline", dest="SBASPRNtextNewline", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--countries","--Countries",dest="Countries",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--usastates","--USAStates",dest="USAStates",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--fireu","--FIREu","--FIREU",dest="FIREurope",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firconus","--FIRCONUS",dest="FIRCONUS",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firalaska","--FIRAlaska",dest="FIRAlaska",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--fircanada","--FIRCanada",dest="FIRCanada",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmexico","--FIRMexico",dest="FIRMexico",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firuser","--FIRUser",type="string",dest="FIRUser",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetype","--FIRLineType",type="string",dest="FIRLineType",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetypeeu","--FIRLineTypeEu",type="string",dest="FIRLineTypeEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetypeconus","--FIRLineTypeCONUS",type="string",dest="FIRLineTypeCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetypealaska","--FIRLineTypeAlaska",type="string",dest="FIRLineTypeAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetypecanada","--FIRLineTypeCanada",type="string",dest="FIRLineTypeCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinetypemexico","--FIRLineTypeMexico",type="string",dest="FIRLineTypeMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidth","--FIRLineWidth",type="string",dest="FIRLineWidth",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidtheu","--FIRLineWidthEu",type="string",dest="FIRLineWidthEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidthconus","--FIRLineWidthCONUS",type="string",dest="FIRLineWidthCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidthalaska","--FIRLineWidthAlaska",type="string",dest="FIRLineWidthAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidthcanada","--FIRLineWidthCanada",type="string",dest="FIRLineWidthCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinewidthmexico","--FIRLineWidthMexico",type="string",dest="FIRLineWidthMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecolor","--FIRLineColor",type="string",dest="FIRLineColor",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecoloreu","--FIRLineColorEu",type="string",dest="FIRLineColorEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecolorconus","--FIRLineColorCONUS",type="string",dest="FIRLineColorCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecoloralaska","--FIRLineColorAlaska",type="string",dest="FIRLineColorAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecolorcanada","--FIRLineColorCanada",type="string",dest="FIRLineColorCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firlinecolormexico","--FIRLineColorMexico",type="string",dest="FIRLineColorMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersize","--FIRMarkerSize",type="string",dest="FIRMarkerSize",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersizeeu","--FIRMarkerSizeEu",type="string",dest="FIRMarkerSizeEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersizeconus","--FIRMarkerSizeCONUS",type="string",dest="FIRMarkerSizeCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersizealaska","--FIRMarkerSizeAlaska",type="string",dest="FIRMarkerSizeAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersizecanada","--FIRMarkerSizeCanada",type="string",dest="FIRMarkerSizeCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firmarkersizemexico","--FIRMarkerSizeMexico",type="string",dest="FIRMarkerSizeMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirborder","--NoFIRBorder",type="string",dest="NoFIRBorder",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirbordereu","--NoFIRBorderEu",dest="NoFIRBorderEu",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirborderconus","--NoFIRBorderCONUS",dest="NoFIRBorderCONUS",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirborderalaska","--NoFIRBorderAlaska",dest="NoFIRBorderAlaska",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirbordercanada","--NoFIRBorderCanada",dest="NoFIRBorderCanada",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirbordermexico","--NoFIRBorderMexico",dest="NoFIRBorderMexico",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegradation","--FIRDegradation","--FIRDegrafation",dest="FIRDegradation",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheader","--FIRDegTextHeader",type="string",dest="FIRDegTextHeader",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheadereu","--FIRDegTextHeaderEu",type="string",dest="FIRDegTextHeaderEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheaderconus","--FIRDegTextHeaderCONUS",type="string",dest="FIRDegTextHeaderCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheaderalaska","--FIRDegTextHeaderAlaska",type="string",dest="FIRDegTextHeaderAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheadercanada","--FIRDegTextHeaderCanada",type="string",dest="FIRDegTextHeaderCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheadermexico","--FIRDegTextHeaderMexico",type="string",dest="FIRDegTextHeaderMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextheaderfirsum","--FIRDegTextHeaderFIRSum",type="string",dest="FIRDegTextHeaderFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfooter","--FIRDegTextFooter",type="string",dest="FIRDegTextFooter",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfootereu","--FIRDegTextFooterEu",type="string",dest="FIRDegTextFooterEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfooterconus","--FIRDegTextFooterCONUS",type="string",dest="FIRDegTextFooterCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfooteralaska","--FIRDegTextFooterAlaska",type="string",dest="FIRDegTextFooterAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfootercanada","--FIRDegTextFooterCanada",type="string",dest="FIRDegTextFooterCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfootermexico","--FIRDegTextFooterMexico",type="string",dest="FIRDegTextFooterMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfooterfirsum","--FIRDegTextFooterFIRSum",type="string",dest="FIRDegTextFooterFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtext","--FIRDegText",type="string",dest="FIRDegText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtexteu","--FIRDegTextEu",type="string",dest="FIRDegTextEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextconus","--FIRDegTextCONUS",type="string",dest="FIRDegTextCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextalaska","--FIRDegTextAlaska",type="string",dest="FIRDegTextAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcanada","--FIRDegTextCanada",type="string",dest="FIRDegTextCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextmexico","--FIRDegTextMexico",type="string",dest="FIRDegTextMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextfirsum","--FIRDegTextFIRSum",type="string",dest="FIRDegTextFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdeg","--FIRSumDeg",dest="FIRSumDeg",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdegeu","--FIRSumDegEu",dest="FIRSumDegEu",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdegconus","--FIRSumDegCONUS",dest="FIRSumDegCONUS",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdegalaska","--FIRSumDegAlaska",dest="FIRSumDegAlaska",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdegcanada","--FIRSumDegCanada",dest="FIRSumDegCanada",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdegmexico","--FIRSumDegMexico",dest="FIRSumDegMexico",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firsumdeguserfir","--FIRSumDegUserFIR",type="string",dest="FIRSumDegUserFIR",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbins","--FIRDegTextBins",type="string",dest="FIRDegTextBins",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbinseu","--FIRDegTextBinsEu",type="string",dest="FIRDegTextBinsEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbinsconus","--FIRDegTextBinsCONUS",type="string",dest="FIRDegTextBinsCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbinsalaska","--FIRDegTextBinsAlaska",type="string",dest="FIRDegTextBinsAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbinscanada","--FIRDegTextBinsCanada",type="string",dest="FIRDegTextBinsCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextbinsmexico","--FIRDegTextBinsMexico",type="string",dest="FIRDegTextBinsMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsize","--FIRDegTextSize",type="string",dest="FIRDegTextSize",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizeeu","--FIRDegTextSizeEu",type="string",dest="FIRDegTextSizeEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizeconus","--FIRDegTextSizeCONUS",type="string",dest="FIRDegTextSizeCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizealaska","--FIRDegTextSizeAlaska",type="string",dest="FIRDegTextSizeAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizecanada","--FIRDegTextSizeCanada",type="string",dest="FIRDegTextSizeCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizemexico","--FIRDegTextSizeMexico",type="string",dest="FIRDegTextSizeMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextsizefirsum","--FIRDegTextSizeFIRSum",type="string",dest="FIRDegTextSizeFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcolor","--FIRDegTextColor",type="string",dest="FIRDegTextColor",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcoloreu","--FIRDegTextColorEu",type="string",dest="FIRDegTextColorEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcolorconus","--FIRDegTextColorCONUS",type="string",dest="FIRDegTextColorCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcoloralaska","--FIRDegTextColorAlaska",type="string",dest="FIRDegTextColorAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcolorcanada","--FIRDegTextColorCanada",type="string",dest="FIRDegTextColorCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcolormexico","--FIRDegTextColorMexico",type="string",dest="FIRDegTextColorMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextcolorfirsum","--FIRDegTextColorFIRSum",type="string",dest="FIRDegTextColorFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextposition","--FIRDegTextPosition",type="string",dest="FIRDegTextPosition",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositioneu","--FIRDegTextPositionEu",type="string",dest="FIRDegTextPositionEu",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositionconus","--FIRDegTextPositionCONUS",type="string",dest="FIRDegTextPositionCONUS",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositionalaska","--FIRDegTextPositionAlaska",type="string",dest="FIRDegTextPositionAlaska",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositioncanada","--FIRDegTextPositionCanada",type="string",dest="FIRDegTextPositionCanada",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositionmexico","--FIRDegTextPositionMexico",type="string",dest="FIRDegTextPositionMexico",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextpositionfirsum","--FIRDegTextPositionFIRSum",type="string",dest="FIRDegTextPositionFIRSum",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtext","--NoFIRDegText",type="string",dest="NoFIRDegText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtexteu","--NoFIRDegTextEu",dest="NoFIRDegTextEu",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtextconus","--NoFIRDegTextCONUS",dest="NoFIRDegTextCONUS",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtextalaska","--NoFIRDegTextAlaska",dest="NoFIRDegTextAlaska",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtextcanada","--NoFIRDegTextCanada",dest="NoFIRDegTextCanada",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nofirdegtextmexico","--NoFIRDegTextMexico",dest="NoFIRDegTextMexico",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtextmonospacefont","--FIRDegTextMonospaceFont",dest="FIRDegTextMonospaceFont",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--firdegtexttable","--FIRDegTextTable",dest="FIRDegTextTable",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--printfirdegtext","--PrintFIRDegText",dest="PrintFIRDegText",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--writetofilefirdegtext","--WriteToFileFIRDegText",type="string",dest="WriteToFileFIRDegText",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--onlyprintfirdegtext","--OnlyPrintFIRDegText",dest="OnlyPrintFIRDegText",default=False,action="store_true",help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbastopfiguremargin","--SBASTopFigureMargin",type="string",dest="SBASTopFigureMargin",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasbottomfiguremargin","--SBASBottomFigureMargin",type="string",dest="SBASBottomFigureMargin",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasleftfiguremargin","--SBASLeftFigureMargin",type="string",dest="SBASLeftFigureMargin",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasrightfiguremargin","--SBASRightFigureMargin",type="string",dest="SBASRightFigureMargin",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sbasplotsize","--SBASPlotSize",type="string",dest="SBASPlotSize",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)


#This function is to override the default error function of OptionParser
#The goal is to not to print the help (because it is too long) and print only the error
def parser_error(self,error):
    print("ERROR: " + error)
    sys.exit()

#Intermidiate command for function overriding in a class
funcType = type(GraphicParser.error)
#Override error function of GraphicParser (class OptionParser)
if PythonVersion == 2:
    GraphicParser.error = funcType(parser_error, GraphicParser, OptionParser)
else:
    GraphicParser.error = funcType(parser_error, OptionParser)

try:
    (opts,args)=GraphicParser.parse_args()
except IOError as e:
    if e.errno == errno.EPIPE:
        #This is to avoid exception when help message is requested ('-h' options)
        #and the help is piped, and the pipe is closed before reaching the end of the help
        sys.exit()
    else:
        #Other unknown error
        print("ERROR: {0:s}".format(e))
        sys.exit()

if (opts.NoLockFile==True):
    CreateLockFile=False

if (CreateLockFile==True):
    if (os.path.isfile(LockFile) != True) :
        try:
            PlotLockFile = open(LockFile, "w")   
        except:
            #In Mac, sys name is "Darwin". If fails to open in Mac, it may be due to
            #gLAB is launched without installing (gLAB mounted on a read-only filesystem)
            #Try the home folder instead
            if (sys.platform[:3].lower() != "win"):
                if (sys.version_info >= (3,4)):
                    #Python 3.4+
                    from pathlib import Path
                    LockFile=str(Path.home()) + "/.plot.lock"
                else:
                    #Python version <= 3.3
                    from os.path import expanduser
                    LockFile=expanduser("~") + "/.plot.lock"

                try:
                    PlotLockFile = open(LockFile, "w")
                except:
                    print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                    sys.exit()
            else:
                print ("ERROR: {0:s}".format(sys.exc_info()[1]))
                sys.exit()

        PlotLockFile.close()

if (opts.wir):
    Graph.worstIntegrityRatio = True
if (opts.wircolorbar):
    opts.wir = True
    Graph.worstIntegrityRatio = True
    Graph.worstIntegrityRatioColorbar = True    

if(opts.stanford and opts.wir):
    print ("ERROR: stanford plots and worst integrity ratio plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA):
    print ("ERROR: stanford plots and stanford-ESA plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.wir and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots and worst integrity ratio plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.stanford):
    print ("ERROR: stanford plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.wir):
    print ("ERROR: Worst integrity ratio plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.wir):
    print ("ERROR: stanford plots, stanford-ESA plots and worst integrity ratio plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.sbas):
    print ("ERROR: stanford plots, stanford-ESA plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.wir and opts.stanfordESA and opts.sbas):
    print ("ERROR: stanford plots, worst integrity ratio plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.wir and opts.sbas):
    print ("ERROR: stanford plots, worst integrity ratio plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.wir and opts.sbas):
    print ("ERROR: stanford plots, stanford-ESA plots, worst integrity ratio plots or SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford or opts.wir or opts.stanfordESA or opts.sbas):
    if (Graph.PlotCounter>1):
        print ("ERROR: stanford plots or worst integrity ratio plots or stanford-ESA plots or SBAS plots only allow one plot per execution")
        removeLockFile()
        sys.exit()

if ((Graph.StaLabelListName != [] or Graph.StaMarkerTypeListName != [] or Graph.StaMarkerColorListName != [] or Graph.StaMarkerSizeListName != []) and Graph.ColLabelName == ""):
     print ("ERROR: If a list of labels or marker properties are provided, it is also necessary to provide the column number with the station network with parameter '--stanet <number>'")
     removeLockFile()
     sys.exit()


if opts.stanford:
    Graph.stanford = True 
    Graph.clean = False
if opts.stanfordESA:
    Graph.stanfordESA = True 
if opts.sfESAwithRegions:
    Graph.sfESAwithRegions = True
if opts.sfESAWithEpochs:
    Graph.textGeometriesLarge = "Epochs"
    Graph.textGeometriesShort = "Epochs"
if opts.NoEpochsInTitle:
    Graph.NoEpochsInTitle = True

   
if opts.sbas:
    Graph.SBASmaps = True
if opts.clean:
    Graph.clean = True
if opts.StfdPercentileX:
    Graph.StfdPercentileX = True
if opts.StfdPercentileY:
    Graph.StfdPercentileY = True
if opts.ContRiskAsPercentage:
    Graph.ContRiskAsPercentage = True
if opts.SBASNoContourLines:
    Graph.contourlines = False
if opts.NoCbarPercentage:
    Graph.CbarPercentage = False
if opts.SBASPRNtextNewline:
    Graph.PRNtextNewline = True
if opts.BinsEqualCondition:
    Graph.BinsEqualCondition = True
if opts.DisableBinEqualCondition:
    Graph.DisableBinsEqualCondition = True
if opts.DisableNotAvailBin:
    Graph.NotAvailBin = False
if opts.DOPPercentilePlot:
    Graph.DOPPercentilePlot = True
if opts.SBASServiceFormat:
    Graph.ServiceFormat = True
if opts.SBASServiceMaritimeFormat:
    Graph.ServiceFormatMaritime = True
if opts.SBASServiceBinaryFormat:
    Graph.ServiceBinaryFormat = True
if opts.SBASServiceMaritimeBinaryFormat:
    Graph.ServiceBinaryFormatMaritime = True

if (Graph.BinsEqualCondition == True and Graph.DisableBinsEqualCondition == True):
    print("ERROR: Options '--bineqcond' and '--disablebineqcond' cannot be both set")
    removeLockFile()
    sys.exit()

if (Graph.ServiceFormat == True and Graph.ServiceFormatMaritime == True):
    print("ERROR: Options '--sbasserviceformat' and '--sbasservicemaritimeformat' cannot be both set")
    removeLockFile()
    sys.exit()

if (Graph.ServiceBinaryFormat == True and Graph.ServiceBinaryFormatMaritime == True):
    print("ERROR: Options '--sbasservicebinaryformat' and '--sbasservicemaritimebinaryformat' cannot be both set")
    removeLockFile()
    sys.exit()

if (Graph.ServiceFormat == True and Graph.ServiceBinaryFormat == True):
    print("ERROR: Options '--sbasserviceformat' and '--sbasservicebinaryformat' cannot be both set")
    removeLockFile()

if (Graph.ServiceFormat == True and Graph.ServiceBinaryFormatMaritime == True):
    print("ERROR: Options '--sbasserviceformat' and '--sbasservicemaritimebinaryformat' cannot be both set")
    removeLockFile()

if (Graph.ServiceFormatMaritime == True and Graph.ServiceBinaryFormat == True):
    print("ERROR: Options '--sbasservicemaritimeformat' and '--sbasservicebinaryformat' cannot be both set")
    removeLockFile()
    sys.exit()
if (Graph.ServiceFormatMaritime == True and Graph.ServiceBinaryFormatMaritime == True):
    print("ERROR: Options '--sbasservicemaritimeformat' and '--sbasservicemaritimebinaryformat' cannot be both set")
    removeLockFile()
    sys.exit()

if opts.AdjustToMargin:
    if (PythonVersionDecimal<2.7):
        #tight_margin() does not work in for python version smaller than 2.7
        print("WARNING: Option 'Adjust to Margin' ('--atm', '--adjusttomargin' or '--AdjustToMargin') does not work in python versions < 2.7 (current version is {0:.1f}). Option ignored.".format(PythonVersionDecimal))
    else:  
        Graph.AdjustToMargin = True

if opts.FIREurope:
    Graph.FIREurope = True

if opts.FIRCONUS:
    Graph.FIRCONUS = True

if opts.FIRAlaska:
    Graph.FIRAlaska = True

if opts.FIRCanada:
    Graph.FIRCanada = True

if opts.FIRMexico:
    Graph.FIRMexico = True

if opts.FIRDegradation:
    Graph.FIRDegradation = True

if opts.FIRDegTextTable:
    Graph.FIRDegradation = True
    Graph.FIRDegTextTable = True

if opts.FIRDegTextMonospaceFont:
    Graph.FIRDegTextFontFamily = 'monospace'

if opts.FIRSumDeg:
    Graph.FIRSum = True

if opts.FIRSumDegEu and Graph.FIREurope == True:
    Graph.FIRSum = True
    Graph.FIRSumWithSelection = True
    Graph.FIRSumDegEur = True

if opts.FIRSumDegCONUS and Graph.FIRCONUS == True:
    Graph.FIRSum = True
    Graph.FIRSumWithSelection = True
    Graph.FIRSumDegCONUS = True

if opts.FIRSumDegAlaska and Graph.FIRAlaska == True:
    Graph.FIRSum = True
    Graph.FIRSumWithSelection = True
    Graph.FIRSumDegAlaska = True

if opts.FIRSumDegCanada and Graph.FIRCanada == True:
    Graph.FIRSum = True
    Graph.FIRSumWithSelection = True
    Graph.FIRSumDegCanada = True

if opts.FIRSumDegMexico and Graph.FIRMexico == True:
    Graph.FIRSum = True
    Graph.FIRSumWithSelection = True
    Graph.FIRSumDegMexico = True

if Graph.FIRSum == True:
    if Graph.FIRSumWithSelection == False:
        #No FIR selected for total FIR sum. Select all FIRs
        if Graph.FIREurope == True:
            Graph.FIRSumDegEur = True

        if Graph.FIRCONUS == True:
            Graph.FIRSumDegCONUS = True

        if Graph.FIRAlaska == True:
            Graph.FIRSumDegAlaska = True

        if Graph.FIRCanada == True:
            Graph.FIRSumDegCanada = True

        if Graph.FIRMexico == True:
            Graph.FIRSumDegMexico = True

        Graph.FIRSumDegUserFIR = []
        for i in range(Graph.FIRNumUserFile):
            Graph.FIRSumDegUserFIR.append(True)
    else:
        #User selected some FIR for the FIR sum
        if Graph.FIRSumDegUserFIR == []:
            #User defined FIR not selected. Unselect all of them
            for i in range(Graph.FIRNumUserFile):
                Graph.FIRSumDegUserFIR.append(False)
        else:
            #Some of the user defined FIR were selected
            TmpList = []
            for i in range(Graph.FIRNumUserFile):
                TmpList.append(False)

            for i in Graph.FIRSumDegUserFIR:
                if (i==0):
                    #If value is 0, select all
                    for j in range(Graph.FIRNumUserFile):
                        TmpList[j] = True
                else:
                    #Select the FIR given in the position value
                    if i>Graph.FIRNumUserFile:
                        print ("ERROR: FIR number {0:d} referenced in parameter '--firsumdeguserfir', but only {1:d} FIR defined".format(i,Graph.FIRNumUserFile))
                        removeLockFile()
                        sys.exit()
                    else:
                        TmpList[i-1] = True

            Graph.FIRSumDegUserFIR = []
            Graph.FIRSumDegUserFIR = TmpList
            TmpList = []

elif Graph.FIRNumUserFile>0:
    #If FIR sum is disabled, set FIRSumDegUserFIR to False to avoid potential problems with empty lists
    for i in range(Graph.FIRNumUserFile):
        Graph.FIRSumDegUserFIR.append(False)


if opts.PrintFIRDegText:
    if sys.platform[:3].lower() == "win":
        #In windows, stdout is redirected to the error file, but this error file cannot write non-ASCII characters like "≥"
        print("Option '--printfirdegtext' does not work in Windows. Use option '--writetofilefirdegtext' instead")
    else:
        Graph.FIRDegradation = True
        Graph.FIRPrintDegText = True

if opts.OnlyPrintFIRDegText:
    Graph.FIRDegradation = True
    Graph.FIRPrintDegText = True
    Graph.FIROnlyPrintDegText = True

if opts.NoFIRBorderEu:
    Graph.FIRShowBorderEur = False

if opts.NoFIRBorderCONUS:
    Graph.FIRShowBorderCONUS = False

if opts.NoFIRBorderAlaska:
    Graph.FIRShowBorderAlaska = False

if opts.NoFIRBorderCanada:
    Graph.FIRShowBorderCanada = False

if opts.NoFIRBorderMexico:
    Graph.FIRShowBorderMexico = False

if opts.NoFIRDegTextEu:
    Graph.FIRShowDegTextEur = False

if opts.NoFIRDegTextCONUS:
    Graph.FIRShowDegTextCONUS = False

if opts.NoFIRDegTextAlaska:
    Graph.FIRShowDegTextAlaska = False

if opts.NoFIRDegTextCanada:
    Graph.FIRShowDegTextCanada = False

if opts.NoFIRDegTextMexico:
    Graph.FIRShowDegTextMexico = False

if Graph.FIRNumUserFile > 0:

    TmpList = []
    if Graph.FIRShowBorder[0] == 0:
        #Do not print any user defined FIR area borders
        for i in range(Graph.FIRNumUserFile):
            TmpList.append(False)
    else:
        for i in range(Graph.FIRNumUserFile):
            TmpList.append(True)

        for i in range(len(Graph.FIRShowBorder)):
            if i==0:
                continue
            if Graph.FIRShowBorder[i]>Graph.FIRNumUserFile:
                print ("ERROR: FIR number {0:d} referenced in parameter '--nofirborder', but {1:d} user FIR areas defined".format(Graph.FIRShowBorder[i],Graph.FIRNumUserFile))
                removeLockFile()
                sys.exit()
            else:
                TmpList[Graph.FIRShowBorder[i]-1] = False

    Graph.FIRShowBorder = []
    Graph.FIRShowBorder = TmpList
    TmpList = []

    if Graph.FIRNumLineColor > Graph.FIRNumUserFile:
        print ("ERROR: {0:d} FIR line colors provided, but {1:d} user FIR areas defined".format(Graph.FIRNumLineColor,Graph.FIRNumUserFile))
        removeLockFile()
        sys.exit()
    elif Graph.FIRNumLineColor < Graph.FIRNumUserFile:
        #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
        for i in range(Graph.FIRNumUserFile-Graph.FIRNumLineColor):
            Graph.FIRLineColor.append(Graph.FIRDegTextColorDefault)

    if Graph.FIRNumLineStyle > Graph.FIRNumUserFile:
        print ("ERROR: {0:d} FIR line types provided, but {1:d} user FIR areas defined".format(Graph.FIRNumLineStyle,Graph.FIRNumUserFile))
        removeLockFile()
        sys.exit()
    elif Graph.FIRNumLineStyle < Graph.FIRNumUserFile:
        #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
        for i in range(Graph.FIRNumUserFile-Graph.FIRNumLineStyle):
            Graph.FIRLineStyle.append(Graph.FIRLineStyleDefault)

    if Graph.FIRNumLineWidth > Graph.FIRNumUserFile:
        print ("ERROR: {0:d} FIR line widths provided, but {1:d} user FIR areas defined".format(Graph.FIRNumLineWidth,Graph.FIRNumUserFile))
        removeLockFile()
        sys.exit()
    elif Graph.FIRNumLineWidth < Graph.FIRNumUserFile:
        #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
        for i in range(Graph.FIRNumUserFile-Graph.FIRNumLineWidth):
            Graph.FIRLineWidth.append(Graph.FIRLineWidthDefault)

    if Graph.FIRNumMarkerSize > Graph.FIRNumUserFile:
        print ("ERROR: {0:d} FIR marker size provided, but {1:d} user FIR areas defined".format(Graph.FIRNumMarkerSize,Graph.FIRNumUserFile))
        removeLockFile()
        sys.exit()
    elif Graph.FIRNumMarkerSize < Graph.FIRNumUserFile:
        #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
        for i in range(Graph.FIRNumUserFile-Graph.FIRNumMarkerSize):
            Graph.FIRMarkerSize.append(Graph.FIRMarkerSizeDefault)
            
    if Graph.FIRDegradation == True:

        TmpList = []
        if Graph.FIRShowDegText[0] == 0:
            #Do not print any user defined FIR degradation texts
            for i in range(Graph.FIRNumUserFile):
                TmpList.append(False)
        else:
            for i in range(Graph.FIRNumUserFile):
                TmpList.append(True)

            for i in range(len(Graph.FIRShowDegText)):
                if i==0:
                    continue
                if Graph.FIRShowDegText[i]>Graph.FIRNumUserFile:
                    print ("ERROR: FIR number {0:d} referenced in parameter '--nofirdegtext', but {1:d} user FIR areas defined".format(Graph.FIRShowDegText[i],Graph.FIRNumUserFile))
                    removeLockFile()
                    sys.exit()
                else:
                    TmpList[Graph.FIRShowDegText[i]-1] = False

        Graph.FIRShowDegText = []
        Graph.FIRShowDegText = TmpList
        TmpList = []

        if Graph.FIRNumDegText > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations texts provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegText,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegText < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegText):
                Graph.FIRDegText.append("") #Default defined later

        if Graph.FIRNumDegTextColor > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text colours provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextColor,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextColor < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextColor):
                Graph.FIRDegTextColor.append(Graph.FIRDegTextColorDefault)

        if Graph.FIRNumDegTextSize > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text sizes provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextSize,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextSize < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextSize):
                if i==0:
                    if Graph.FIRNumDegTextSize==0 and Graph.FIRDegTextTable == True:
                        Graph.FIRDegTextSize.append(Graph.FIRDegTextSizeDefaultForTable)
                    else:
                        Graph.FIRDegTextSize.append(Graph.FIRDegTextSizeDefault)
                else:
                    Graph.FIRDegTextSize.append(Graph.FIRDegTextSizeDefault)

        if Graph.FIRNumDegTextPositionX > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text positions provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextPositionX,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextPositionX < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextPositionX):
                if i==0:
                    if Graph.FIRNumDegTextPositionX==0 and Graph.FIRDegTextTable == True:
                        Graph.FIRDegTextPositionX.append(Graph.FIRDegTextPositionXDefaultForTable) #Set by default in the bottom left corner
                        Graph.FIRDegTextPositionY.append(Graph.FIRDegTextPositionYDefaultForTable) #Set by default in the bottom left corner
                    else:
                        Graph.FIRDegTextPositionX.append(Graph.FIRDegTextPositionXDefault)
                        Graph.FIRDegTextPositionY.append(Graph.FIRDegTextPositionYDefault-i*0.27) #Default separate each text by moving them downwards
                else:
                    Graph.FIRDegTextPositionX.append(Graph.FIRDegTextPositionXDefault)
                    Graph.FIRDegTextPositionY.append(Graph.FIRDegTextPositionYDefault-i*0.27) #Default separate each text by moving them downwards

        if Graph.FIRNumDegTextBins > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text bins provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextBins,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextBins < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextBins):
                Graph.FIRDegTextBins.append([]) #Default defined later

        if Graph.FIRNumDegTextHeader > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text headers provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextHeader,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextHeader < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextHeader):
                Graph.FIRDegTextHeader.append("]]]]]]]]][[[[[[[[[[[") #Default defined later

        if Graph.FIRNumDegTextFooter > Graph.FIRNumUserFile:
            print ("ERROR: {0:d} FIR degradations text footers provided, but {1:d} user FIR areas defined".format(Graph.FIRNumDegTextFooter,Graph.FIRNumUserFile))
            removeLockFile()
            sys.exit()
        elif Graph.FIRNumDegTextFooter < Graph.FIRNumUserFile:
            #Add the default values to the missing positions, so the list has the same size as the number of FIR areas
            for i in range(Graph.FIRNumUserFile-Graph.FIRNumDegTextFooter):
                Graph.FIRDegTextFooter.append("") #Default is empty

elif Graph.FIRDegTextTable == True:
    #Add default values to degradation text
    Graph.FIRDegTextSize.append(Graph.FIRDegTextSizeDefaultForTable)
    Graph.FIRDegTextColor.append(Graph.FIRDegTextColorDefault)
    Graph.FIRDegTextPositionX.append(Graph.FIRDegTextPositionXDefaultForTable) #Set by default in the bottom left corner
    Graph.FIRDegTextPositionY.append(Graph.FIRDegTextPositionYDefaultForTable) #Set by default in the bottom left corner

if opts.Countries:
    Graph.Countries = True

if opts.USAStates:
    Graph.USAStates= True

if opts.StaNetAutoLabel:
    Graph.StaNetAddLabel = True

if opts.StaNetworkWithNames:
    Graph.StaNetWorkWithNames = True

if opts.StaNetworkWithMarkers:
    Graph.StaNetWorkWithMarkers = True

if opts.staNetLabelNumSta:
    Graph.StaNetAddNumStations = True

if Graph.StaNetWorkWithNames == True and Graph.StaNetWorkWithMarkers == False:
    if Graph.StaNetAddLabel == True:
        Graph.NumPointsLabel=None
elif Graph.StaNetWorkWithNames == False and Graph.StaNetWorkWithMarkers == False:
    if Graph.StaNetAddLabel == True:
        Graph.NumPointsLabel=None

if (Graph.PlotCounter==0 and opts.stanford):
    print ("ERROR: stanford plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.wir):
    print ("ERROR: worst integrity ratio plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.sbas):
    print ("ERROR: SBAS plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()

if (Graph.Xmin >= Graph.Xmax and Graph.XmaxAuto == False):
    print ("ERROR: X max must be greater than X min")
    removeLockFile()
    sys.exit()

if (Graph.Ymin >= Graph.Ymax and Graph.YmaxAuto == False):
    print ("ERROR: Y max must be greater than Y min")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColXUser == False):
    print ("ERROR: Longitude column in file for worst integrity ratio plots must be set. Use '-x <col>'")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColYUser == False):
    print ("ERROR: Latitude column in file for worst integrity ratio plots must be set. Use '-y <col>'")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioH == "" and Graph.ColRatioV == "" and Graph.ColName == ""):
    print ("ERROR: Horizontal or Vertical integrity ratio column or Station Name column in file for worst integrity ratio plots must be set. Use '--rh <col>' for horizontal ratio column or '--rv <col>' for vertical ratio column or '--sn <col>' for station name column")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioV == "" and Graph.ColMIsV != ""):
    print ("ERROR: Vertical MI column given, but no Vertical integrity ratio column given. Use '--rv <col>' to input vertical integrity ratio column")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioH == "" and Graph.ColMIsH != ""):
    print ("ERROR: Horizontal MI column given, but no horizontal integrity ratio column given. Use '--rh <col>' to input horizontal ratio column")
    removeLockFile()
    sys.exit()

if (Graph.FIRDegradation == True and opts.sbas == False):
    print ("ERROR: FIR Degradation computation can only be enabled in SBAS Availability plots")
    removeLockFile()
    sys.exit()

if Graph.ServiceFormat == True:
    if Graph.UserSetAvailBins == False:
        Graph.AvailBins = [70.1,70.0,80.0,90.0,95.0,98.0,99.0,99.9]
        
    if Graph.UserSetRiskBins == False:
        Graph.RiskBins = [3.1e-2,3e-2,2e-2,1e-2,5e-3,1e-3,5e-4,1e-4]

    if Graph.UserSetRiskMarBins == False:
        Graph.RiskMarBins = [3.1e-2,3e-2,2e-2,1e-2,5e-3,1e-3,5e-4,1e-4]

    if Graph.UserSetIonoBins == False:
        Graph.IonoAvailBins = [70.1,70.0,80.0,90.0,95.0,98.0,99.0,99.9]

    if Graph.UserSetHDOPBins == False:
        Graph.HDOPBins = [4.1,4,2]

    if Graph.UserSetPDOPBins == False:
        Graph.PDOPBins = [6.1,6,3.5]

    if Graph.UserSetGDOPBins == False:
        Graph.GDOPBins = [7.1,7,5]

    if Graph.AvailColorList == []:
        Graph.AvailColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.ContRiskColorList == []:
        Graph.ContRiskColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.ContRiskMarColorList == []:
        Graph.ContRiskMarColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.IonoAvailColorList == []:
        Graph.IonoAvailColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.HDOPColorList == []:
        Graph.HDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.PDOPColorList == []:
        Graph.PDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.GDOPColorList == []:
        Graph.GDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.UserDefinedAvailContourlevels == False:        
        Graph.AvailContourLevels = []

    if Graph.UserDefinedRiskContourlevels == False:        
        Graph.RiskContourLevels = []

    if Graph.UserDefinedRiskMarContourlevels == False:        
        Graph.RiskMarContourLevels = []

    if Graph.UserDefinedAvailContourlevels == False and Graph.UserDefinedRiskContourlevels == False and Graph.UserDefinedRiskMarContourlevels == False:
        #If user didn't set any contour line, disable them
        Graph.contourlines = False


if Graph.ServiceFormatMaritime == True:
    if Graph.UserSetAvailBins == False:
        Graph.AvailBins = [70.1,70.0,90.0,95.0,97.5,99.0,99.5,99.8]

    if Graph.UserSetRiskBins == False:
        Graph.RiskBins = [1.1e-1,1e-1,1e-2,1e-3,7e-4,5e-4,4e-4,3e-4]

    if Graph.UserSetRiskMarBins == False:
        Graph.RiskMarBins = [1.1e-1,1e-1,1e-2,1e-3,7e-4,5e-4,4e-4,3e-4]

    if Graph.UserSetIonoBins == False:
        Graph.IonoAvailBins = [70.1,70.0,90.0,95.0,97.5,99.0,99.5,99.8]

    if Graph.UserSetHDOPBins == False:
        Graph.HDOPBins = [4.1,4,2]

    if Graph.UserSetPDOPBins == False:
        Graph.PDOPBins = [6.1,6,3.5]

    if Graph.UserSetGDOPBins == False:
        Graph.GDOPBins = [7.1,7,5]

    if Graph.AvailColorList == []:
        Graph.AvailColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.ContRiskColorList == []:
        Graph.ContRiskColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.ContRiskMarColorList == []:
        Graph.ContRiskMarColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.IonoAvailColorList == []:
        Graph.IonoAvailColorList = ["#00008b","#0040ff","#00ffff","#00ff00","#ffff00","#ffa500","#ff0000","#8b0000"]

    if Graph.HDOPColorList == []:
        Graph.HDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.PDOPColorList == []:
        Graph.PDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.GDOPColorList == []:
        Graph.GDOPColorList = ["#00008b","#ffa500","#8b0000"]

    if Graph.UserDefinedAvailContourlevels == False:        
        Graph.AvailContourLevels = []

    if Graph.UserDefinedRiskContourlevels == False:        
        Graph.RiskContourLevels = []

    if Graph.UserDefinedRiskMarContourlevels == False:        
        Graph.RiskMarContourLevels = []

    if Graph.UserDefinedAvailContourlevels == False and Graph.UserDefinedRiskContourlevels == False and Graph.UserDefinedRiskMarContourlevels == False:
        #If user didn't set any contour line, disable them
        Graph.contourlines = False

if Graph.ServiceBinaryFormat == True:
    if Graph.UserSetAvailBins == False:
        Graph.AvailBins = [99.8,99.9]

    if Graph.UserSetRiskBins == False:
        Graph.RiskBins = [1.1e-4,1e-4]

    if Graph.UserSetRiskMarBins == False:
        Graph.RiskMarBins = [1.1e-4,1e-4]

    if Graph.UserSetIonoBins == False:
        Graph.IonoAvailBins = [99.8,99.9]

    if Graph.UserSetHDOPBins == False:
        Graph.HDOPBins = [4.1,4]

    if Graph.UserSetPDOPBins == False:
        Graph.PDOPBins = [6.1,6]

    if Graph.UserSetGDOPBins == False:
        Graph.GDOPBins = [7.1,7]

    if Graph.AvailColorList == []:
        Graph.AvailColorList = ["#ffffff","#006400"]

    if Graph.ContRiskColorList == []:
        Graph.ContRiskColorList = ["#ffffff","#006400"]

    if Graph.ContRiskMarColorList == []:
        Graph.ContRiskMarColorList = ["#ffffff","#006400"]

    if Graph.IonoAvailColorList == []:
        Graph.IonoAvailColorList = ["#ffffff","#006400"]

    if Graph.HDOPColorList == []:
        Graph.HDOPColorList = ["#ffffff","#006400"]

    if Graph.PDOPColorList == []:
        Graph.PDOPColorList = ["#ffffff","#006400"]

    if Graph.GDOPColorList == []:
        Graph.GDOPColorList = ["#ffffff","#006400"]

    if Graph.AvailBinsText == []:
        Graph.AvailBinsText = ["Not\nCompliant","Compliant"]

    if Graph.RiskBinsText == []:
        Graph.RiskBinsText = ["Not\nCompliant","Compliant"]

    if Graph.RiskMarBinsText == []:
        Graph.RiskMarBinsText = ["Not\nCompliant","Compliant"]

    if Graph.IonoAvailBinsText == []:
        Graph.IonoAvailBinsText = ["Not\nCompliant","Compliant"]

    if Graph.HDOPBinsText == []:
        Graph.HDOPBinsText = ["Not\nCompliant","Compliant"]

    if Graph.PDOPBinsText == []:
        Graph.PDOPBinsText = ["Not\nCompliant","Compliant"]

    if Graph.GDOPBinsText == []:
        Graph.GDOPBinsText = ["Not\nCompliant","Compliant"]

    if Graph.UserDefinedAvailContourlevels == False:        
        Graph.AvailContourLevels = []

    if Graph.UserDefinedRiskContourlevels == False:        
        Graph.RiskContourLevels = []

    if Graph.UserDefinedRiskMarContourlevels == False:        
        Graph.RiskMarContourLevels = []

    if Graph.UserDefinedAvailContourlevels == False and Graph.UserDefinedRiskContourlevels == False and Graph.UserDefinedRiskMarContourlevels == False:
        #If user didn't set any contour line, disable them
        Graph.contourlines = False

if Graph.ServiceBinaryFormatMaritime == True:
    if Graph.UserSetAvailBins == False:
        Graph.AvailBins = [99.7,99.8]

    if Graph.UserSetRiskBins == False:
        Graph.RiskBins = [3.1e-4,3e-4]

    if Graph.UserSetRiskMarBins == False:
        Graph.RiskMarBins = [3.1e-4,3e-4]

    if Graph.UserSetIonoBins == False:
        Graph.IonoAvailBins = [99.7,99.8]

    if Graph.UserSetHDOPBins == False:
        Graph.HDOPBins = [4.1,4]

    if Graph.UserSetPDOPBins == False:
        Graph.PDOPBins = [6.1,6]

    if Graph.UserSetGDOPBins == False:
        Graph.GDOPBins = [7.1,7]

    if Graph.AvailColorList == []:
        Graph.AvailColorList = ["#ffffff","#006400"]

    if Graph.ContRiskColorList == []:
        Graph.ContRiskColorList = ["#ffffff","#006400"]

    if Graph.ContRiskMarColorList == []:
        Graph.ContRiskMarColorList = ["#ffffff","#006400"]

    if Graph.IonoAvailColorList == []:
        Graph.IonoAvailColorList = ["#ffffff","#006400"]

    if Graph.HDOPColorList == []:
        Graph.HDOPColorList = ["#ffffff","#006400"]

    if Graph.PDOPColorList == []:
        Graph.PDOPColorList = ["#ffffff","#006400"]

    if Graph.GDOPColorList == []:
        Graph.GDOPColorList = ["#ffffff","#006400"]

    if Graph.AvailBinsText == []:
        Graph.AvailBinsText = ["Not\nCompliant","Compliant"]

    if Graph.RiskBinsText == []:
        Graph.RiskBinsText = ["Not\nCompliant","Compliant"]

    if Graph.RiskMarBinsText == []:
        Graph.RiskMarBinsText = ["Not\nCompliant","Compliant"]

    if Graph.IonoAvailBinsText == []:
        Graph.IonoAvailBinsText = ["Not\nCompliant","Compliant"]

    if Graph.HDOPBinsText == []:
        Graph.HDOPBinsText = ["Not\nCompliant","Compliant"]

    if Graph.PDOPBinsText == []:
        Graph.PDOPBinsText = ["Not\nCompliant","Compliant"]
        
    if Graph.GDOPBinsText == []:
        Graph.GDOPBinsText = ["Not\nCompliant","Compliant"]

    if Graph.UserDefinedAvailContourlevels == False:        
        Graph.AvailContourLevels = []

    if Graph.UserDefinedRiskContourlevels == False:        
        Graph.RiskContourLevels = []

    if Graph.UserDefinedRiskMarContourlevels == False:        
        Graph.RiskMarContourLevels = []

    if Graph.UserDefinedAvailContourlevels == False and Graph.UserDefinedRiskContourlevels == False and Graph.UserDefinedRiskMarContourlevels == False:
        #If user didn't set any contour line, disable them
        Graph.contourlines = False

if Graph.UserSetRiskBins == True:
    if Graph.ContRiskAsPercentage == True:
        #It is necessary to check whether the user set the bins as risk values or as a percentage
        RiskPercentValues=0
        for elem in Graph.RiskBins:
            if elem>10.:
                RiskPercentValues=1
                break;
        if RiskPercentValues==1:
            #Values provided as percentages, it is necessary to invert them
            valfloated=[]
            for elem in Graph.RiskBins:
                valfloated.append(round((100.-elem)/100.,14)) #The round() is to avoid problems with decimals
            
            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            valfloated.insert(0,valfloated[0]+1e-3)
            Graph.RiskBins = valfloated
        else:
            for elem in Graph.RiskBins:
                if float(elem)>1.:
                    print ("ERROR: Bin '{0:s}' in Continuity Risk bin list is above 1".format(elem))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(Graph.RiskBins,reverse=True) #Sorted in descending order
            valfloated.insert(0,valfloated[0]+1e-3)
            Graph.RiskBins = valfloated
    else:
        for elem in Graph.RiskBinsUserText:
            if float(elem)>1.:
                print ("ERROR: Bin '{0:s}' in Continuity Risk bin list is above 1".format(elem))
                removeLockFile()
                sys.exit()

        valfloated = sorted(Graph.RiskBins,reverse=True) #Sorted in descending order
        valfloated.insert(0,valfloated[0]+1e-3)
        Graph.RiskBins = valfloated

    valfloated=[]

if Graph.UserSetRiskMarBins == True:
    if Graph.ContRiskAsPercentage == True:
        #It is necessary to check whether the user set the bins as risk values or as a percentage
        RiskPercentValues=0
        for elem in Graph.RiskMarBins:
            if elem>10.:
                RiskPercentValues=1
                break;
        if RiskPercentValues==1:
            #Values provided as percentages, it is necessary to invert them
            valfloated=[]
            for elem in Graph.RiskMarBins:
                valfloated.append(round((100.-elem)/100.,14)) #The round() is to avoid problems with decimals
            
            valfloated = sorted(valfloated,reverse=True) #Sorted in descending order
            valfloated.insert(0,valfloated[0]+1e-3)
            Graph.RiskMarBins = valfloated
        else:
            for elem in Graph.RiskMarBinsUserText:
                if float(elem)>1.:
                    print ("ERROR: Bin '{0:s}' in Maritime Continuity Risk bin list is above 1".format(elem))
                    removeLockFile()
                    sys.exit()

            valfloated = sorted(Graph.RiskMarBins,reverse=True) #Sorted in descending order
            valfloated.insert(0,valfloated[0]+1e-3)
            Graph.RiskMarBins = valfloated
    else:
        for elem in Graph.RiskMarBinsUserText:
            if float(elem)>1:
                print ("ERROR: Bin '{0:s}' in Maritime Continuity Risk bin list is above 1".format(elem))
                removeLockFile()
                sys.exit()

        valfloated = sorted(Graph.RiskMarBins,reverse=True) #Sorted in descending order
        valfloated.insert(0,valfloated[0]+1e-3)
        Graph.RiskMarBins = valfloated

    valfloated=[]


if Graph.AvailColorList != []:
    if len(Graph.AvailColorList)!=len(Graph.AvailBins):
        print ("ERROR: Number of colours provided for availability map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.AvailColorList),len(Graph.AvailBins)))
        removeLockFile()
        sys.exit()

if Graph.ContRiskColorList != []:
    if len(Graph.ContRiskColorList)!=len(Graph.RiskBins):
        print ("ERROR: Number of colours provided for continuity risk map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.ContRiskColorList),len(Graph.RiskBins)))
        removeLockFile()
        sys.exit()

if Graph.ContRiskMarColorList != []:
    if len(Graph.ContRiskMarColorList)!=len(Graph.RiskMarBins):
        print ("ERROR: Number of colours provided for maritime continuity risk map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.ContRiskMarColorList),len(Graph.RiskMarBins)))
        removeLockFile()
        sys.exit()

if Graph.IonoAvailColorList != []:
    if len(Graph.IonoAvailColorList)!=len(Graph.IonoAvailBins):
        print ("ERROR: Number of colours provided for ionosphere availability map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.IonoAvailColorList),len(Graph.IonoAvailBins)))
        removeLockFile()
        sys.exit()

if Graph.HDOPColorList != []:
    if len(Graph.HDOPColorList)!=len(Graph.HDOPBins):
        print ("ERROR: Number of colours provided for HDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.HDOPColorList),len(Graph.HDOPBins)))
        removeLockFile()
        sys.exit()

if Graph.PDOPColorList != []:
    if len(Graph.PDOPColorList)!=len(Graph.PDOPBins):
        print ("ERROR: Number of colours provided for PDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.PDOPColorList),len(Graph.PDOPBins)))
        removeLockFile()
        sys.exit()

if Graph.GDOPColorList != []:
    if len(Graph.GDOPColorList)!=len(Graph.GDOPBins):
        print ("ERROR: Number of colours provided for GDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.GDOPColorList),len(Graph.GDOPBins)))
        removeLockFile()
        sys.exit()

if Graph.AvailBinsText != []:
    if len(Graph.AvailBinsText)!=len(Graph.AvailBins):
        print ("ERROR: Number of texts provided for availability map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.AvailBinsText),len(Graph.AvailBins)))
        removeLockFile()
        sys.exit()

if Graph.RiskBinsText != []:
    if len(Graph.RiskBinsText)!=len(Graph.RiskBins):
        print ("ERROR: Number of texts provided for continuity risk map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.RiskBinsText),len(Graph.RiskBins)))
        removeLockFile()
        sys.exit()

if Graph.RiskMarBinsText != []:
    if len(Graph.RiskMarBinsText)!=len(Graph.RiskMarBins):
        print ("ERROR: Number of texts provided for maritime continuity risk map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.RiskMarBinsText),len(Graph.   RiskMarBins)))
        removeLockFile()
        sys.exit()

if Graph.IonoAvailBinsText != []:
    if len(Graph.IonoAvailBinsText)!=len(Graph.IonoAvailBins):
        print ("ERROR: Number of texts provided for ionosphere availability map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.IonoAvailBinsText),len(Graph.      IonoAvailBins)))
        removeLockFile()
        sys.exit()

if Graph.HDOPBinsText != []:
    if len(Graph.HDOPBinsText)!=len(Graph.HDOPBins):
        print ("ERROR: Number of texts provided for HDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.HDOPBinsText),len(Graph.HDOPBins)))
        removeLockFile()
        sys.exit()

if Graph.PDOPBinsText != []:
    if len(Graph.PDOPBinsText)!=len(Graph.PDOPBins):
        print ("ERROR: Number of texts provided for PDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.PDOPBinsText),len(Graph.PDOPBins)))
        removeLockFile()
        sys.exit()

if Graph.GDOPBinsText != []:
    if len(Graph.GDOPBinsText)!=len(Graph.GDOPBins):
        print ("ERROR: Number of texts provided for GDOP map ({0:d}) does not match the number of bins ({1:d})".format(len(Graph.GDOPBinsText),len(Graph.GDOPBins)))
        removeLockFile()
        sys.exit()


if Graph.TopMargin==.5 and Graph.BottomMargin==.5:
    print ("ERROR: Top margin and bottom margin can not be both 0.5")
    removeLockFile()
    sys.exit()

if Graph.LeftMargin==.5 and Graph.RightMargin==.5:
    print ("ERROR: Left margin and right margin can not be both 0.5")
    removeLockFile()
    sys.exit()

if Graph.NumTextMark > 0:
    if Graph.NumTextMarkColour > Graph.NumTextMark:
        print ("ERROR: {0:d} Text mark colors provided, but {1:d} text mark defined".format(Graph.NumTextMarkColour,Graph.NumTextMark))
        removeLockFile()
        sys.exit()
    elif Graph.NumTextMarkColour < Graph.NumTextMark:
        #Add the default values to the missing positions, so the list has the same size as the number text mark defined
        for i in range(Graph.NumTextMark-Graph.NumTextMarkColour):
            Graph.TextMarkColour.append(Graph.TextMarkColourDefault)

    if Graph.NumTextMarkSize > Graph.NumTextMark:
        print ("ERROR: {0:d} Text mark sizes provided, but {1:d} text mark defined".format(Graph.NumTextMarkSize,Graph.NumTextMark))
        removeLockFile()
        sys.exit()
    elif Graph.NumTextMarkSize < Graph.NumTextMark:
        #Add the default values to the missing positions, so the list has the same size as the number text mark defined
        for i in range(Graph.NumTextMark-Graph.NumTextMarkSize):
            Graph.TextMarkSize.append(Graph.TextMarkSizeDefault)

    if Graph.NumTextMarkPosition > Graph.NumTextMark:
        print ("ERROR: {0:d} Text mark positions provided, but {1:d} text mark defined".format(Graph.NumTextMarkPosition,Graph.NumTextMark))
        removeLockFile()
        sys.exit()
    elif Graph.NumTextMarkPosition < Graph.NumTextMark:
        #Add the default values to the missing positions, so the list has the same size as the number text mark defined
        for i in range(Graph.NumTextMark-Graph.NumTextMarkPosition):
            Graph.TextMarkPositionX.append(Graph.TextMarkPositionXDefault)
            Graph.TextMarkPositionY.append(Graph.TextMarkPositionYDefault-i*0.15) #Default separate each text by moving them downwards


#matplot lib Agg does not use XDisplay, so if we are saving plot in a file (or only plotting degradation text), we will not need XDisplay in Linux
if Graph.SaveFigure or (Graph.SBASmaps and Graph.FIROnlyPrintDegText):
    import matplotlib
    matplotlib.use('Agg')

#The imports are done after the parameters are read, so if no stanford or 
#worst integrity ratio plots are done, their libraries are not imported
if (Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
    import numpy as np
    import matplotlib.pyplot as plt
    import matplotlib.path as mpltPath
    import matplotlib.transforms as mtransforms
    from matplotlib.path import Path
    from matplotlib.patches import Rectangle,PathPatch,Polygon
    from matplotlib.collections import PatchCollection
    from mpl_toolkits.axes_grid1 import make_axes_locatable
else:
    import pylab

#Import OrderedDict only if necessary
if Graph.worstIntegrityRatio and Graph.StaNetAddLabel:
    try:
        from collections import OrderedDict
    except:
        if sys.platform[:3].lower() == "win":
            #Python 2.6 from Windows SciPy package has OrderedDict inside mdp.utils module
            from mdp.utils._ordered_dict import OrderedDict
        else:
            #Alternative import in Linux for OrderedDict if not found
            from sqlalchemy.util import OrderedDict
            
if Graph.worstIntegrityRatio or Graph.SBASmaps:
    from mpl_toolkits.basemap import Basemap
    
if Graph.SBASmaps and Graph.FIROutputFileNameDegText != "":
    #io module is for writing to files with unicode characters
    import io

#If we are not in Windows and we are not saving the plot in a file (or only plotting degradation text), check if we have a display available
if (sys.platform[:3].lower() != "win" and (Graph.SaveFigure==False or (Graph.SBASmaps and Graph.FIROnlyPrintDegText==False))):
        try:
            if(Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
                plt.figure()
                plt.close('all')
            else:
                pylab.xlabel("")
        except:
            print (sys.exc_info()[1])
            removeLockFile()
            sys.exit()

#This plt.close('all') is repeated due to sometimes a weird error of Tkinter appeared (can't invoke "event" command: application has been destroyed).
#Forcing again to close all plots is a workaround to the problem 
if(Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
    plt.close('all')
    plt.close('all')

#For Availability, Continuity Risk and Maritime Continuity Risk plots, if the bins or contour lines are changed,
#check that the list of contour values are also in the bin list
if (Graph.UserDefinedBinsOrContours == True or Graph.ServiceFormat == True or Graph.ServiceFormatMaritime == True or 
        Graph.ServiceBinaryFormat == True or Graph.ServiceBinaryFormatMaritime == True) and Graph.contourlines == True:
    for contour in Graph.AvailContourLevels:
        pos = -1
        try:
            pos = Graph.AvailBins.index(contour)
        except:
            pass
        if pos <= 0: #pos=-1 means that value is not found. pos=0 is the bin added internally for the last position, which is not visible to the user
            print ("ERROR: Contour value '{0:.1f}' not found in availability bin list. Change availability contour values with parameter '--availcontourlevels' or availability bins with parameter '--availmapbins'".format(contour))
            removeLockFile()
            sys.exit()
        elif pos == 1:
            if len(Graph.AvailBins)>2:
                print ("ERROR: Contour value '{0:.1f}' cannot be the smallest value in the availability bin list '{1:s}' (except if there is only one bin in the list). Use a higher value in the bin list or remove this value".format(contour,''.join(str(Graph.AvailBins[1:]))))
                removeLockFile()
                sys.exit()

    for contour in Graph.RiskContourLevels:
        pos=-1
        try:
            pos = Graph.RiskBins.index(contour)
        except:
            pass
        if pos <= 0: #pos=-1 means that value is not found. pos=0 is the bin added internally for the last position, which is not visible to the user
            print ("ERROR: Contour value '{0:.1e}' not found in continuity risk bin list. Change continuity risk contour values with parameter '--contriskcontourlevels' or continuity risk bins with parameter '--contriskmapbins'".format(contour))
            removeLockFile()
            sys.exit()
        elif pos == 1:
            if len(Graph.RiskBins)>2:
                print ("ERROR: Contour value '{0:.1e}' cannot be the smallest value in the continuity risk bin list '{1:s}' (except if there is only one bin in the list). Use a higher value in the bin list or remove this value".format(contour,''.join(str(Graph.RiskBins[1:]))))
                removeLockFile()
                sys.exit()

    for contour in Graph.RiskMarContourLevels:
        pos=-1
        try:
            pos = Graph.RiskMarBins.index(contour)
        except:
            pass
        if pos <= 0: #pos=-1 means that value is not found. pos=0 is the bin added internally for the last position, which is not visible to the user
            print ("ERROR: Contour value '{0:.1e}' not found in maritime continuity risk bin list. Change maritime continuity risk contour values with parameter '--contriskmarcontourlevels' or maritime continuity risk bins with parameter '--contriskmarmapbins'".format(contour))
            removeLockFile()
            sys.exit()
        elif pos == 1:
            if len(Graph.RiskMarBins)>2:
                print ("ERROR: Contour value '{0:.1e}' cannot be the smallest value in the maritime continuity risk bin list '{1:s}' (except if there is only one bin in the list). Use a higher value in the bin list or remove this value".format(contour,''.join(str(Graph.RiskMarBins[1:]))))
                removeLockFile()
                sys.exit()
if Graph.FIREurope:
    Graph.latFIREur=[69.77246666700,69.76929444400,69.76929722200,69.76631111100,69.76457777800,69.76102500000,69.76043888900,69.76295277800,69.75848611100,69.75624444400,69.75285833300,69.75243888900,69.75561111100,69.75617222200,69.75487500000,69.75327500000,69.75046111100,69.75120833300,69.74888333300,69.74615000000,69.74448333300,69.74155277800,69.74180000000,69.73788333300,69.73713888900,69.73531111100,69.73401111100,69.73216111100,69.73104444400,69.72921388900,69.72501388900,69.71985000000,69.71755833300,69.71849166700,69.71470000000,69.71269166700,69.70970000000,69.70683333300,69.70339444400,69.70297500000,69.70136111100,69.69955277800,69.70162500000,69.70047500000,69.69799722200,69.69435555600,69.69119444400,69.69085277800,69.68478055600,69.68697500000,69.68558611100,69.68308888900,69.68078333300,69.67778611100,69.67573611100,69.67436111100,69.67632500000,69.67409722200,69.67461944400,69.66865833300,69.66424722200,69.66228333300,69.65759722200,69.65372222200,69.64758888900,69.64656111100,69.64368888900,69.64112500000,69.63813888900,69.63476944400,69.63237777800,69.61815000000,69.61396944400,69.60848611100,69.60187222200,69.59651111100,69.59055833300,69.58148333300,69.57609166700,69.57225000000,69.56068055600,69.55357222200,69.54951111100,69.54619722200,69.53742777800,69.53502500000,69.52864166700,69.54056944400,69.54208611100,69.54026944400,69.54778333300,69.58979444400,69.62879166700,69.65303333300,69.66918333300,69.65805833300,69.64281944400,69.64341111100,69.62879166700,69.61535555600,69.61280833300,69.60878333300,69.60567500000,69.59918055600,69.59261666700,69.58509166700,69.57985000000,69.56639722200,69.56363333300,69.55751666700,69.55106388900,69.54495833300,69.53841666700,69.53270555600,69.53343888900,69.53038333300,69.52522222200,69.52322500000,69.51593611100,69.50788888900,69.49397500000,69.48006111100,69.47157777800,69.46912777800,69.45395000000,69.43102777800,69.42329722200,69.41137777800,69.40525000000,69.40696666700,69.41302777800,69.41861388900,69.41817777800,69.42383888900,69.42314166700,69.40618611100,69.39760833300,69.38921944400,69.38648055600,69.38367222200,69.37937500000,69.37152500000,69.36612500000,69.36332777800,69.34737777800,69.33867777800,69.31780833300,69.31720833300,69.32016388900,69.32296111100,69.32823055600,69.32893055600,69.32717777800,69.32868333300,69.32188333300,69.32141944400,69.31851111100,69.32248333300,69.31090000000,69.30765277800,69.30171944400,69.29861666700,69.29352222200,69.28160277800,69.27524722200,69.25603888900,69.24629444400,69.23798888900,69.22869444400,69.22186666700,69.21664722200,69.20981388900,69.20651666700,69.19749444400,69.19321388900,69.18694444400,69.17898055600,69.16498333300,69.16127777800,69.15561666700,69.15365555600,69.14676944400,69.13873888900,69.12857500000,69.12515277800,69.12451944400,69.12202777800,69.11296944400,69.06693888900,69.06303055600,69.03937500000,69.01501388900,69.01063055600,69.02509444400,69.05194444400,69.07722222200,69.05194444400,68.93000000000,68.91555555600,68.88555555600,68.88638888900,68.86916666700,68.73222222200,68.53972222200,68.19638888900,68.07444444400,67.80305555600,67.67361111100,67.52250000000,67.49055555600,67.47916666700,67.42500000000,67.39805555600,67.39638888900,67.39250000000,67.38083333300,67.37194444400,67.37027777800,67.36472222200,67.36027777800,67.35500000000,67.35250000000,67.35166666700,67.34944444400,67.34555555600,67.34194444400,67.34083333300,67.33666666700,67.33638888900,67.32972222200,67.32638888900,67.33083333300,67.32388888900,67.32250000000,67.31972222200,67.31944444400,67.31583333300,67.31194444400,67.31083333300,67.31194444400,67.30833333300,67.30888888900,67.31027777800,67.31000000000,67.29388888900,67.28527777800,67.28055555600,67.22527777800,66.99611111100,66.96138888900,66.94388888900,66.92611111100,66.85305555600,66.80138888900,66.79527777800,66.79055555600,66.78694444400,66.78444444400,66.77944444400,66.78055555600,66.69416666700,66.64138888900,66.63888888900,66.63611111100,66.63638888900,66.62722222200,66.62444444400,66.60750000000,66.60388888900,66.59833333300,66.59750000000,66.59222222200,66.59194444400,66.58305555600,66.57833333300,66.54388888900,66.49638888900,66.36638888900,66.31972222200,66.27722222200,66.27472222200,66.27250000000,66.27111111100,66.26833333300,66.26666666700,66.26833333300,66.12722222200,66.04611111100,66.04388888900,66.04083333300,66.02472222200,66.02250000000,66.01972222200,65.97888888900,65.96666666700,65.95861111100,65.89500000000,65.85055555600,65.75222222200,65.69972222200,65.66861111100,65.68722222200,65.69638888900,65.63722222200,65.60944444400,65.57694444400,65.56055555600,65.52638888900,65.49750000000,65.48250000000,65.47250000000,65.40027777800,65.37388888900,65.34750000000,65.28916666700,65.27583333300,65.26000000000,65.23166666700,65.23083333300,65.22583333300,65.22888888900,65.21527777800,65.20638888900,65.19305555600,65.14416666700,65.12861111100,65.13166666700,65.12722222200,65.10527777800,65.10388888900,65.09194444400,65.09138888900,65.06055555600,65.01277777800,64.99500000000,64.95972222200,64.92722222200,64.86638888900,64.84916666700,64.83722222200,64.81888888900,64.78972222200,64.78972222200,64.79361111100,64.79472222200,64.79138888900,64.79277777800,64.77388888900,64.76500000000,64.76444444400,64.74111111100,64.71305555600,64.64888888900,64.63472222200,64.62583333300,64.61527777800,64.58750000000,64.57722222200,64.53388888900,64.50444444400,64.50055555600,64.48305555600,64.47222222200,64.45083333300,64.44166666700,64.43416666700,64.40194444400,64.36500000000,64.35805555600,64.35055555600,64.32972222200,64.32000000000,64.29972222200,64.28138888900,64.26916666700,64.26222222200,64.22166666700,64.20444444400,64.15500000000,64.13222222200,64.10166666700,64.04888888900,64.01694444400,63.98277777800,63.93222222200,63.90944444400,63.82194444400,63.80111111100,63.75722222200,63.70805555600,63.70388888900,63.70194444400,63.69666666700,63.69444444400,63.68000000000,63.66777777800,63.60722222200,63.58416666700,63.54555555600,63.46666666700,63.42694444400,63.40527777800,63.37694444400,63.37333333300,63.37222222200,63.37083333300,63.36833333300,63.36444444400,63.36500000000,63.36250000000,63.35555555600,63.33666666700,63.30777777800,63.30722222200,63.30388888900,63.30333333300,63.28138888900,63.27083333300,63.26888888900,63.26305555600,63.26500000000,63.26166666700,63.24416666700,63.23555555600,63.22944444400,63.22416666700,63.21916666700,63.21361111100,63.19500000000,63.18194444400,63.17861111100,63.14194444400,63.11527777800,63.10750000000,63.09388888900,63.07083333300,63.06027777800,63.05472222200,63.05138888900,63.04916666700,63.04194444400,63.04333333300,63.02416666700,63.00611111100,62.99638888900,62.91833333300,62.91444444400,62.90861111100,62.79666666700,62.78388888900,62.78500000000,62.69000000000,62.68250000000,62.67500000000,62.67500000000,62.67194444400,62.67138888900,62.66000000000,62.64972222200,62.64500000000,62.64361111100,62.64055555600,62.64027777800,62.53333333300,62.52555555600,62.52305555600,62.49861111100,62.49361111100,62.48750000000,62.48194444400,62.45500000000,62.44611111100,62.44222222200,62.33333333300,62.32777777800,62.31222222200,62.30555555600,62.31027777800,62.27555555600,62.27055555600,62.26111111100,62.23500000000,62.22666666700,62.20888888900,62.21055555600,62.20888888900,62.19222222200,62.18944444400,62.18333333300,62.17361111100,62.14166666700,62.11861111100,62.06388888900,62.03666666700,62.03472222200,62.03250000000,62.03333333300,62.02277777800,61.99944444400,61.98000000000,61.97333333300,61.97305555600,61.96416666700,61.96277777800,61.94500000000,61.93500000000,61.93361111100,61.89277777800,61.89138888900,61.88222222200,61.85805555600,61.81888888900,61.81888888900,61.77333333300,61.76527777800,61.68194444400,61.67694444400,61.67055555600,61.67055555600,61.65527777800,61.63555555600,61.63500000000,61.62694444400,61.60305555600,61.58333333300,61.57583333300,61.56027777800,61.55222222200,61.52611111100,61.52027777800,61.50055555600,61.50027777800,61.49555555600,61.49583333300,61.49222222200,61.49194444400,61.46138888900,61.34944444400,61.34388888900,61.29166666700,61.27611111100,61.27333333300,61.27055555600,61.26444444400,61.25750000000,61.25638888900,61.24444444400,61.24138888900,61.24222222200,61.23666666700,61.18861111100,61.17388888900,61.15166666700,61.14333333300,61.14444444400,61.14222222200,61.13555555600,61.12166666700,61.09666666700,61.09333333300,61.04444444400,61.02694444400,60.97888888900,60.94944444400,60.94805555600,60.95527777800,60.95166666700,60.95638888900,60.95500000000,60.95722222200,60.93694444400,60.92916666700,60.92583333300,60.92333333300,60.88750000000,60.88555555600,60.88361111100,60.88472222200,60.85416666700,60.85777777800,60.84138888900,60.81000000000,60.78277777800,60.77861111100,60.74083333300,60.72055555600,60.68250000000,60.68111111100,60.67027777800,60.67111111100,60.60444444400,60.58194444400,60.57833333300,60.57500000000,60.56583333300,60.56138888900,60.55416666700,60.53361111100,60.50777777800,60.50388888900,60.49555555600,60.48916666700,60.47166666700,60.46916666700,60.45111111100,60.43750000000,60.43361111100,60.39166666700,60.22333333300,60.20027777800,60.13333333300,59.97500000000,59.88333333300,59.74029390500,59.61166666700,59.45888888900,59.43805555600,59.40083333300,59.39333333300,59.37944444400,59.36722222200,59.35055555600,59.29861111100,59.29416666700,59.29194444400,59.28666666700,59.27944444400,59.27472222200,59.26861111100,59.24388888900,59.23888888900,59.21916666700,59.20555555600,59.16500000000,59.14111111100,59.12972222200,59.10444444400,59.09388888900,59.03000000000,59.01194444400,58.98916666700,58.98611111100,58.95611111100,58.78722222200,58.63055555600,58.37722222200,58.30305555600,58.22472222200,58.22111111100,58.21000000000,58.11833333300,58.09722222200,58.05416666700,58.04500000000,58.03000000000,58.01444444400,58.00555555600,58.00000000000,58.00000000000,58.00722222200,58.00194444400,57.98388888900,57.97444444400,57.96388888900,57.95500000000,57.94111111100,57.93638888900,57.93027777800,57.92944444400,57.91527777800,57.91416666700,57.91611111100,57.91500000000,57.90972222200,57.90138888900,57.88305555600,57.85861111100,57.84500000000,57.83583333300,57.82944444400,57.83194444400,57.82777777800,57.83888888900,57.83944444400,57.83055555600,57.82027777800,57.80416666700,57.80055555600,57.79250000000,57.77888888900,57.75777777800,57.74500000000,57.73361111100,57.70861111100,57.70583333300,57.70750000000,57.71444444400,57.71166666700,57.71250000000,57.68083333300,57.65555555600,57.63416666700,57.62194444400,57.61138888900,57.59611111100,57.59222222200,57.58777777800,57.58166666700,57.57555555600,57.55916666700,57.51750000000,57.52833333300,57.52944444400,57.54111111100,57.53888888900,57.52222222200,57.51944444400,57.51444444400,57.50333333300,57.47583333300,57.46694444400,57.45666666700,57.44694444400,57.44083333300,57.42416666700,57.41000000000,57.40500000000,57.37805555600,57.35277777800,57.32777777800,57.31666666700,57.30500000000,57.28500000000,57.26694444400,57.24250000000,57.15972222200,57.15111111100,57.14000000000,57.13444444400,57.12750000000,57.11222222200,57.09972222200,57.09305555600,57.08777777800,57.08833333300,57.08222222200,57.04555555600,57.04138888900,57.03000000000,57.01250000000,57.00277777800,56.99472222200,56.98694444400,56.97694444400,56.96722222200,56.95611111100,56.94194444400,56.93055555600,56.91111111100,56.89638888900,56.86444444400,56.84472222200,56.83722222200,56.83750000000,56.85500000000,56.85722222200,56.85722222200,56.86500000000,56.86416666700,56.86805555600,56.87694444400,56.87500000000,56.87555555600,56.86388888900,56.83222222200,56.82666666700,56.82805555600,56.82388888900,56.81694444400,56.80805555600,56.80527777800,56.80000000000,56.77722222200,56.76472222200,56.75166666700,56.75027777800,56.74722222200,56.73611111100,56.72194444400,56.71527777800,56.70805555600,56.68694444400,56.66888888900,56.65694444400,56.63666666700,56.61000000000,56.59500000000,56.58888888900,56.58805555600,56.57722222200,56.56638888900,56.55694444400,56.54750000000,56.53972222200,56.53361111100,56.52250000000,56.51777777800,56.51583333300,56.50916666700,56.49833333300,56.49250000000,56.47861111100,56.44111111100,56.40638888900,56.39416666700,56.38000000000,56.34666666700,56.31805555600,56.28250000000,56.27555555600,56.23416666700,56.22305555600,56.21250000000,56.20777777800,56.19750000000,56.17222222200,56.15833333300,56.14611111100,56.13305555600,56.12777777800,56.12027777800,56.12694444400,56.11750000000,56.10055555600,56.08750000000,56.06472222200,56.05305555600,56.04888888900,56.04111111100,56.03916666700,56.03611111100,56.02833333300,56.02000000000,56.00666666700,56.00000000000,55.98694444400,55.97444444400,55.93527777800,55.91222222200,55.89027777800,55.83555555600,55.80055555600,55.78638888900,55.78361111100,55.79138888900,55.79583333300,55.80222222200,55.81361111100,55.81250000000,55.80472222200,55.79305555600,55.79111111100,55.79444444400,55.80583333300,55.82638888900,55.83277777800,55.84388888900,55.85333333300,55.85166666700,55.83388888900,55.82888888900,55.83416666700,55.83138888900,55.78166666700,55.76166666700,55.73333333300,55.71722222200,55.70611111100,55.70333333300,55.69638888900,55.68861111100,55.68555555600,55.68888888900,55.70138888900,55.70555555600,55.69666666700,55.67444444400,55.65777777800,55.61833333300,55.59694444400,55.58083333300,55.56972222200,55.55972222200,55.54750000000,55.53444444400,55.52944444400,55.52361111100,55.51638888900,55.51222222200,55.49000000000,55.39027777800,55.37416666700,55.35888888900,55.35277777800,55.34638888900,55.33805555600,55.33666666700,55.32750000000,55.33027777800,55.32333333300,55.33527777800,55.32916666700,55.33777777800,55.33916666700,55.34500000000,55.33694444400,55.32555555600,55.32944444400,55.32694444400,55.32000000000,55.32277777800,55.31166666700,55.30944444400,55.29916666700,55.29500000000,55.28472222200,55.28500000000,55.25638888900,55.23611111100,55.21277777800,55.20472222200,55.20388888900,55.19805555600,55.18888888900,55.17555555600,55.16444444400,55.15416666700,55.15333333300,55.14638888900,55.14250000000,55.14861111100,55.14694444400,55.16027777800,55.15416666700,55.12583333300,55.13416666700,55.14138888900,55.15277777800,55.14166666700,55.10944444400,55.10027777800,55.09111111100,55.07888888900,55.06583333300,55.03750000000,55.00250000000,54.97250000000,54.96583333300,54.95694444400,54.93777777800,54.93555555600,54.93777777800,54.94722222200,54.95555555600,54.95888888900,54.94972222200,54.93750000000,54.92277777800,54.91222222200,54.89166666700,54.85805555600,54.81527777800,54.80027777800,54.77444444400,54.76194444400,54.74694444400,54.72027777800,54.69805555600,54.67583333300,54.65111111100,54.63416666700,54.60388888900,54.59333333300,54.58583333300,54.57916666700,54.57361111100,54.56527777800,54.54638888900,54.53277777800,54.50972222200,54.48027777800,54.46527777800,54.44666666700,54.43694444400,54.42166666700,54.41472222200,54.41194444400,54.39055555600,54.37277777800,54.36027777800,54.34694444400,54.33694444400,54.33277777800,54.32666666700,54.31611111100,54.31611111100,54.32138888900,54.32055555600,54.31361111100,54.28944444400,54.27916666700,54.27055555600,54.26194444400,54.25388888900,54.24722222200,54.24166666700,54.23694444400,54.23416666700,54.22833333300,54.20444444400,54.18750000000,54.17666666700,54.16861111100,54.16805555600,54.17250000000,54.17027777800,54.14527777800,54.14055555600,54.14000000000,54.14916666700,54.15083333300,54.15694444400,54.15861111100,54.17555555600,54.18305555600,54.19083333300,54.19666666700,54.20527777800,54.21611111100,54.22638888900,54.23083333300,54.24111111100,54.24972222200,54.27750000000,54.29527777800,54.30638888900,54.31555555600,54.31833333300,54.31666666700,54.30138888900,54.30055555600,54.29611111100,54.28333333300,54.27611111100,54.27166666700,54.27444444400,54.26416666700,54.18861111100,54.14111111100,54.13500000000,54.13777777800,54.16277777800,54.16277777800,54.13777777800,54.13555555600,54.12916666700,54.12305555600,54.10138888900,54.07805555600,54.05972222200,54.04361111100,54.01972222200,53.99527777800,53.98000000000,53.96555555600,53.96111111100,53.95444444400,53.96222222200,53.96444444400,53.95222222200,53.95555555600,53.96666666700,53.98305555600,53.99750000000,54.01416666700,54.01694444400,54.01777777800,54.00611111100,53.97888888900,53.95916666700,53.92388888900,53.90916666700,53.90555555600,53.90972222200,53.91916666700,53.93000000000,53.95000000000,53.96166666700,53.96138888900,53.95611111100,53.95416666700,53.93972222200,53.96666666700,53.96638888900,53.95611111100,53.94972222200,53.95138888900,53.95694444400,53.93916666700,53.93277777800,53.91500000000,53.90555555600,53.90138888900,53.90500000000,53.92500000000,53.93277777800,53.93388888900,53.92527777800,53.91666666700,53.91722222200,53.93138888900,53.96666666700,53.93361111100,53.88222222200,53.85833333300,53.84583333300,53.77583333300,53.76527777800,53.75444444400,53.74250000000,53.72722222200,53.70333333300,53.65333333300,53.61444444400,53.60083333300,53.59333333300,53.58361111100,53.50805555600,53.48138888900,53.47444444400,53.30638888900,53.27111111100,53.24888888900,53.24111111100,53.22888888900,53.22305555600,53.21722222200,53.20805555600,53.19361111100,53.18722222200,53.17166666700,53.15833333300,53.15277777800,53.14750000000,53.14083333300,53.12944444400,53.11472222200,53.10277777800,53.09861111100,53.09111111100,53.08388888900,53.07138888900,53.06361111100,53.05861111100,53.05444444400,53.04777777800,53.04416666700,53.01888888900,52.96666666700,52.94777777800,52.93527777800,52.89166666700,52.82666666700,52.67000000000,52.60333333300,52.57361111100,52.54833333300,52.48611111100,52.44666666700,52.36055555600,52.32138888900,52.28250000000,52.27472222200,52.27194444400,52.26527777800,52.26194444400,52.25777777800,52.25388888900,52.24583333300,52.23750000000,52.22638888900,52.22138888900,52.22111111100,52.21388888900,52.21861111100,52.21555555600,52.20972222200,52.20638888900,52.20472222200,52.21166666700,52.20555555600,52.20333333300,52.20222222200,52.20472222200,52.19638888900,52.19361111100,52.19444444400,52.19861111100,52.19722222200,52.19388888900,52.19138888900,52.18888888900,52.18111111100,52.17722222200,52.17611111100,52.18055555600,52.17222222200,52.17111111100,52.18416666700,52.18250000000,52.17750000000,52.17361111100,52.17388888900,52.18000000000,52.17916666700,52.17555555600,52.17138888900,52.17194444400,52.16777777800,52.16444444400,52.15333333300,52.14888888900,52.14666666700,52.14861111100,52.14722222200,52.14333333300,52.13722222200,52.13694444400,52.13083333300,52.13166666700,52.12166666700,52.11666666700,52.11333333300,52.10611111100,52.09166666700,52.07722222200,52.05194444400,52.04750000000,52.04194444400,52.02333333300,52.02027777800,52.00500000000,52.00305555600,51.99916666700,51.99083333300,51.98500000000,51.98055555600,51.97277777800,51.96861111100,51.96611111100,51.96805555600,51.96750000000,51.95694444400,51.95611111100,51.94888888900,51.94111111100,51.93666666700,51.93583333300,51.92527777800,51.92666666700,51.92166666700,51.91416666700,51.90888888900,51.90500000000,51.90027777800,51.89750000000,51.89027777800,51.87805555600,51.88083333300,51.87888888900,51.87361111100,51.86416666700,51.85833333300,51.84972222200,51.84361111100,51.84166666700,51.83527777800,51.83416666700,51.83111111100,51.81611111100,51.80416666700,51.79472222200,51.78583333300,51.78611111100,51.77805555600,51.77611111100,51.77694444400,51.76583333300,51.76000000000,51.76250000000,51.75111111100,51.74888888900,51.74500000000,51.73277777800,51.73138888900,51.72694444400,51.72416666700,51.72277777800,51.72722222200,51.71777777800,51.71388888900,51.70972222200,51.70694444400,51.70333333300,51.70055555600,51.68888888900,51.68611111100,51.68361111100,51.68194444400,51.67555555600,51.66805555600,51.66527777800,51.66388888900,51.65944444400,51.65472222200,51.64944444400,51.64222222200,51.63472222200,51.62833333300,51.61972222200,51.60611111100,51.60111111100,51.59583333300,51.58583333300,51.58083333300,51.56833333300,51.55916666700,51.55027777800,51.53861111100,51.53222222200,51.53694444400,51.53111111100,51.53083333300,51.52750000000,51.52444444400,51.51583333300,51.50555555600,51.49888888900,51.48805555600,51.49111111100,51.48750000000,51.47416666700,51.46194444400,51.46138888900,51.45777777800,51.44861111100,51.44444444400,51.43638888900,51.43166666700,51.42666666700,51.42138888900,51.41888888900,51.41444444400,51.41250000000,51.40444444400,51.40083333300,51.39500000000,51.39222222200,51.38722222200,51.38388888900,51.38027777800,51.37694444400,51.37083333300,51.36861111100,51.36277777800,51.35638888900,51.34472222200,51.33972222200,51.33333333300,51.32194444400,51.31388888900,51.30555555600,51.28833333300,51.28888888900,51.27777777800,51.27444444400,51.26833333300,51.26972222200,51.25833333300,51.24750000000,51.23972222200,51.23388888900,51.23333333300,51.23027777800,51.22833333300,51.22388888900,51.22083333300,51.21694444400,51.21388888900,51.21166666700,51.20722222200,51.20166666700,51.20250000000,51.19944444400,51.19111111100,51.19027777800,51.18083333300,51.17277777800,51.16916666700,51.16500000000,51.16138888900,51.16194444400,51.15750000000,51.15666666700,51.15861111100,51.15472222200,51.15111111100,51.14666666700,51.13666666700,51.13222222200,51.13055555600,51.13277777800,51.12361111100,51.11194444400,51.10750000000,51.10305555600,51.09638888900,51.08083333300,51.08250000000,51.07666666700,51.07888888900,51.07500000000,51.07222222200,51.06638888900,51.05361111100,51.04611111100,51.04333333300,51.04111111100,51.04194444400,51.03777777800,51.03027777800,51.02638888900,51.02138888900,51.01750000000,51.01555555600,51.01250000000,51.00166666700,50.98666666700,50.97611111100,50.95583333300,50.94805555600,50.93222222200,50.90722222200,50.89666666700,50.89305555600,50.88277777800,50.87777777800,50.87388888900,50.87027777800,50.87111111100,50.86361111100,50.86027777800,50.84583333300,50.84027777800,50.83861111100,50.84333333300,50.84333333300,50.81194444400,50.80611111100,50.80083333300,50.79000000000,50.78527777800,50.77361111100,50.77388888900,50.77027777800,50.76527777800,50.75722222200,50.74944444400,50.74222222200,50.73750000000,50.72583333300,50.72638888900,50.72083333300,50.72222222200,50.71694444400,50.71361111100,50.70861111100,50.70138888900,50.69611111100,50.68888888900,50.67805555600,50.67250000000,50.67000000000,50.66527777800,50.66472222200,50.65833333300,50.65416666700,50.64888888900,50.64444444400,50.63888888900,50.63583333300,50.60638888900,50.57111111100,50.52583333300,50.46944444400,50.44638888900,50.43527777800,50.41222222200,50.41361111100,50.42027777800,50.41305555600,50.40611111100,50.39805555600,50.39333333300,50.38666666700,50.36972222200,50.34416666700,50.33750000000,50.30972222200,50.29333333300,50.27500000000,50.25444444400,50.20416666700,50.15583333300,50.13777777800,50.11527777800,50.10472222200,50.09555555600,50.08305555600,50.07194444400,50.05611111100,50.05222222200,50.04555555600,50.03166666700,50.02361111100,50.00000000000,49.86694444400,49.83361111100,49.82583333300,49.80888888900,49.79472222200,49.78138888900,49.77055555600,49.76527777800,49.75083333300,49.73611111100,49.72805555600,49.71694444400,49.69527777800,49.68500000000,49.63555555600,49.58388888900,49.56666666700,49.55083333300,49.54166666700,49.53611111100,49.52388888900,49.48833333300,49.45138888900,49.43638888900,49.41027777800,49.40555555600,49.37583333300,49.32722222200,49.31250000000,49.29083333300,49.28027777800,49.25972222200,49.23944444400,49.23194444400,49.22444444400,49.21916666700,49.21888888900,49.21583333300,49.20555555600,49.19694444400,49.19277777800,49.17722222200,49.17111111100,49.16833333300,49.18222222200,49.18472222200,49.18472222200,49.18222222200,49.17805555600,49.17194444400,49.17111111100,49.16527777800,49.15916666700,49.15333333300,49.15694444400,49.14638888900,49.14055555600,49.13388888900,49.11944444400,49.11416666700,49.11194444400,49.11500000000,49.11277777800,49.10972222200,49.10500000000,49.09888888900,49.09805555600,49.09500000000,49.08222222200,49.07861111100,49.07500000000,49.07027777800,49.06555555600,49.05638888900,49.05166666700,49.04361111100,49.04027777800,49.04055555600,49.03694444400,49.02944444400,49.02361111100,49.01777777800,49.00916666700,49.00638888900,49.02750000000,49.05388888900,49.05500000000,49.04444444400,49.05083333300,49.04972222200,49.04194444400,49.04444444400,49.05166666700,49.06361111100,49.07777777800,49.08194444400,49.09416666700,49.09611111100,49.09277777800,49.08799419400,49.08366086100,49.08103630600,49.07948305600,49.03016136100,49.02520094400,49.02132188900,49.00676505600,49.00288380600,48.99674558300,48.99951633300,48.99838747200,48.99410733300,48.99118294400,48.97627919400,48.97294305600,48.92932786100,48.92437008300,48.92188652800,48.91925175000,48.91257075000,48.90458350000,48.90348186100,48.90151191700,48.88460122200,48.87708725000,48.87328133300,48.86966183300,48.86503958300,48.86003916700,48.83887488900,48.83402550000,48.82450269400,48.80661400000,48.80004016700,48.79462577800,48.78244419400,48.77950588900,48.77301169400,48.77160044400,48.76614711100,48.75712413900,48.75067772200,48.74919605600,48.74322705600,48.73999955600,48.73854655600,48.73019963900,48.72614444400,48.72032008300,48.71783755600,48.70588955600,48.69858302800,48.68389222200,48.68227580600,48.67637497200,48.67319400000,48.66932263900,48.66154872200,48.64739833300,48.63946833300,48.62770769400,48.62054686100,48.62127297200,48.60939708300,48.60962288900,48.60311036100,48.60238661100,48.58753758300,48.56732802800,48.52704088900,48.51498783300,48.51282077800,48.50980313900,48.45267083300,48.43268519400,48.42851408300,48.41879400000,48.41458600000,48.41128477800,48.40384336100,48.40395952800,48.39972222200,48.41277777800,48.42361111100,48.42361111100,48.41888888900,48.41333333300,48.41027777800,48.40444444400,48.39944444400,48.39472222200,48.39027777800,48.38166666700,48.36611111100,48.36277777800,48.35805555600,48.36055555600,48.36416666700,48.36194444400,48.32583333300,48.32166666700,48.30472222200,48.28250000000,48.26527777800,48.25083333300,48.24388888900,48.24166666700,48.25166666700,48.25333333300,48.24972222200,48.25027777800,48.24638888900,48.25500000000,48.25555555600,48.25138888900,48.24527777800,48.24222222200,48.24027777800,48.22944444400,48.21638888900,48.21222222200,48.20333333300,48.19888888900,48.19972222200,48.19388888900,48.18611111100,48.16138888900,48.14916666700,48.14333333300,48.13083333300,48.12527777800,48.12000000000,48.10888888900,48.10861111100,48.09305555600,48.09500000000,48.10277777800,48.10444444400,48.09583333300,48.09194444400,48.09416666700,48.10111111100,48.10222222200,48.11111111100,48.11722222200,48.11583333300,48.11944444400,48.11138888900,48.11555555600,48.11944444400,48.12000000000,48.11555555600,48.10694444400,48.10472222200,48.11388888900,48.11666666700,48.11666666700,48.11277777800,48.09333333300,48.08444444400,48.08027777800,48.07750000000,48.05500000000,48.04361111100,48.03083333300,48.02527777800,48.01888888900,48.01194444400,48.00000000000,48.00000000000,47.99444444400,47.98833333300,47.98222222200,47.97750000000,47.97166666700,47.95916666700,47.95916666700,47.96416666700,47.96944444400,47.99861111100,48.00722222200,48.01250000000,48.01694444400,48.01555555600,48.00750000000,48.01083333300,47.99250000000,47.99083333300,47.99138888900,48.00000000000,48.00166666700,48.00750000000,48.00500000000,48.01055555600,48.01888888900,48.02694444400,48.03750000000,48.04111111100,48.05944444400,48.06666666700,48.07916666700,48.08194444400,48.08805555600,48.09944444400,48.10805555600,48.11444444400,48.11833333300,48.11388888900,48.10722222200,48.10055555600,48.09638888900,48.09555555600,48.09166666700,48.09222222200,48.10166666700,48.09638888900,48.08750000000,48.08083333300,48.07583333300,48.06666666700,48.06222222200,48.05500000000,48.04611111100,48.03916666700,48.03194444400,48.02472222200,48.01944444400,48.01972222200,48.00000000000,48.00000000000,47.98277777800,47.98027777800,47.98111111100,47.98666666700,48.00000000000,48.00000000000,47.98833333300,47.99722222200,47.99222222200,47.98222222200,47.96500000000,47.95194444400,47.94083333300,47.93638888900,47.93472222200,47.95527777800,47.96416666700,47.96527777800,47.95833333300,47.94722222200,47.92277777800,47.91500000000,47.91361111100,47.91972222200,47.92000000000,47.91805555600,47.90583333300,47.90611111100,47.91444444400,47.92138888900,47.93194444400,47.92916666700,47.93083333300,47.94166666700,47.95583333300,47.96555555600,47.96916666700,47.97000000000,47.95888888900,47.95694444400,47.96527777800,47.96416666700,47.95055555600,47.94666666700,47.93888888900,47.92694444400,47.91166666700,47.90500000000,47.88333333300,47.87194444400,47.85916666700,47.84555555600,47.84138888900,47.84055555600,47.83500000000,47.83166666700,47.82166666700,47.81833333300,47.81361111100,47.79944444400,47.77611111100,47.75805555600,47.74305555600,47.73777777800,47.73027777800,47.72472222200,47.72222222200,47.73055555600,47.73583333300,47.73916666700,47.75222222200,47.75777777800,47.78833333300,47.80555555600,47.84638888900,47.86805555600,47.88111111100,47.88305555600,47.88666666700,47.90833333300,47.91694444400,47.93555555600,47.94527777800,47.95055555600,47.95250000000,47.96083333300,47.96388888900,47.96638888900,47.97138888900,47.98388888900,47.98750000000,47.98555555600,47.99111111100,47.98611111100,47.99138888900,47.98833333300,48.00000000000,48.03277777800,48.04888888900,48.07527777800,48.08916666700,48.10333333300,48.11750000000,48.13444444400,48.15555555600,48.16777777800,48.17861111100,48.18805555600,48.18722222200,48.19305555600,48.19222222200,48.19944444400,48.19861111100,48.19472222200,48.19111111100,48.18972222200,48.19055555600,48.20055555600,48.20055555600,48.19638888900,48.19694444400,48.20305555600,48.20722222200,48.20750000000,48.21055555600,48.21527777800,48.21805555600,48.22277777800,48.21944444400,48.21638888900,48.21305555600,48.21777777800,48.22388888900,48.22500000000,48.22222222200,48.23138888900,48.23444444400,48.24638888900,48.24722222200,48.24111111100,48.23972222200,48.24111111100,48.24722222200,48.26194444400,48.26111111100,48.25750000000,48.25333333300,48.25277777800,48.25611111100,48.26416666700,48.26333333300,48.25861111100,48.25222222200,48.24888888900,48.24694444400,48.24944444400,48.25388888900,48.26222222200,48.26527777800,48.26388888900,48.25333333300,48.24666666700,48.24888888900,48.25583333300,48.25861111100,48.25500000000,48.24805555600,48.24555555600,48.24805555600,48.24305555600,48.24888888900,48.24944444400,48.25416666700,48.24611111100,48.24416666700,48.23333333300,48.22861111100,48.22611111100,48.22861111100,48.23416666700,48.23111111100,48.21722222200,48.20222222200,48.20166666700,48.19472222200,48.19222222200,48.18861111100,48.18027777800,48.18027777800,48.18222222200,48.19861111100,48.19972222200,48.19638888900,48.18638888900,48.17916666700,48.17027777800,48.16638888900,48.16138888900,48.16250000000,48.15972222200,48.15222222200,48.14888888900,48.14444444400,48.15250000000,48.14944444400,48.14416666700,48.13416666700,48.13027777800,48.12805555600,48.12138888900,48.12416666700,48.13500000000,48.13833333300,48.13666666700,48.13472222200,48.12805555600,48.12500000000,48.12388888900,48.12861111100,48.12944444400,48.11611111100,48.10777777800,48.10250000000,48.08972222200,48.08194444400,48.06916666700,48.05277777800,48.04861111100,48.03861111100,48.03500000000,48.03416666700,48.03166666700,48.02694444400,48.02277777800,48.01777777800,48.01138888900,48.00833333300,48.00750000000,48.01166666700,48.01500000000,48.01305555600,48.01055555600,48.00111111100,47.99444444400,47.99111111100,47.99472222200,47.98555555600,47.97138888900,47.96694444400,47.94694444400,47.92111111100,47.90194444400,47.84916666700,47.83777777800,47.83694444400,47.83361111100,47.83055555600,47.82527777800,47.83166666700,47.82694444400,47.82027777800,47.81472222200,47.81416666700,47.81694444400,47.81555555600,47.81250000000,47.80694444400,47.79916666700,47.79444444400,47.78777777800,47.78333333300,47.77861111100,47.78000000000,47.76805555600,47.76305555600,47.76000000000,47.76388888900,47.75666666700,47.74972222200,47.74861111100,47.75277777800,47.74888888900,47.74694444400,47.74500000000,47.73472222200,47.73000000000,47.72861111100,47.72638888900,47.72305555600,47.72305555600,47.72861111100,47.72611111100,47.73111111100,47.73222222200,47.72944444400,47.72055555600,47.71972222200,47.71250000000,47.70777777800,47.70416666700,47.70027777800,47.70222222200,47.70027777800,47.69333333300,47.68972222200,47.68388888900,47.68055555600,47.66194444400,47.66083333300,47.64916666700,47.64250000000,47.63861111100,47.62694444400,47.61972222200,47.60972222200,47.60250000000,47.59916666700,47.59527777800,47.58305555600,47.58305555600,47.58027777800,47.57138888900,47.56555555600,47.56333333300,47.56305555600,47.55361111100,47.54916666700,47.54666666700,47.54611111100,47.53583333300,47.53750000000,47.53333333300,47.53055555600,47.52555555600,47.52166666700,47.52666666700,47.51833333300,47.51361111100,47.50805555600,47.49944444400,47.49416666700,47.48583333300,47.48888888900,47.48666666700,47.48388888900,47.48083333300,47.47833333300,47.48055555600,47.48472222200,47.49000000000,47.48805555600,47.48250000000,47.47638888900,47.47444444400,47.48222222200,47.47833333300,47.48083333300,47.48444444400,47.48777777800,47.48833333300,47.48638888900,47.47722222200,47.47305555600,47.47027777800,47.46416666700,47.46277777800,47.46583333300,47.46444444400,47.45750000000,47.44944444400,47.44694444400,47.43916666700,47.43444444400,47.43055555600,47.42333333300,47.42416666700,47.41888888900,47.41250000000,47.40916666700,47.41055555600,47.40805555600,47.39972222200,47.39444444400,47.38722222200,47.38500000000,47.38305555600,47.37583333300,47.37388888900,47.37444444400,47.37805555600,47.37694444400,47.37416666700,47.37111111100,47.36805555600,47.36805555600,47.36500000000,47.37138888900,47.36833333300,47.34694444400,47.34972222200,47.34666666700,47.34027777800,47.33972222200,47.34194444400,47.34027777800,47.32916666700,47.33222222200,47.32861111100,47.32750000000,47.32527777800,47.32083333300,47.31722222200,47.31861111100,47.32222222200,47.32888888900,47.32583333300,47.31750000000,47.31972222200,47.32583333300,47.32055555600,47.31055555600,47.31305555600,47.31138888900,47.30333333300,47.29972222200,47.30166666700,47.30694444400,47.30805555600,47.30500000000,47.30805555600,47.30083333300,47.30027777800,47.30444444400,47.30888888900,47.30972222200,47.30000000000,47.29666666700,47.29111111100,47.28500000000,47.28583333300,47.29194444400,47.28972222200,47.29722222200,47.30000000000,47.29805555600,47.29388888900,47.29472222200,47.28388888900,47.27638888900,47.27611111100,47.26416666700,47.25750000000,47.25750000000,47.25277777800,47.25111111100,47.25444444400,47.25000000000,47.24722222200,47.24861111100,47.24694444400,47.24250000000,47.23833333300,47.23972222200,47.23416666700,47.23055555600,47.23111111100,47.22805555600,47.22166666700,47.21916666700,47.21444444400,47.20500000000,47.20361111100,47.20805555600,47.19694444400,47.19027777800,47.18805555600,47.19111111100,47.18972222200,47.17250000000,47.16638888900,47.16666666700,47.16305555600,47.15611111100,47.15194444400,47.15333333300,47.15055555600,47.14694444400,47.14777777800,47.14388888900,47.14194444400,47.14416666700,47.14055555600,47.13805555600,47.13527777800,47.13916666700,47.13444444400,47.13305555600,47.13583333300,47.13194444400,47.12777777800,47.12527777800,47.12277777800,47.12750000000,47.12888888900,47.12166666700,47.11583333300,47.11277777800,47.10833333300,47.10388888900,47.10361111100,47.10722222200,47.10722222200,47.10500000000,47.10250000000,47.10277777800,47.09861111100,47.09166666700,47.08777777800,47.08166666700,47.07333333300,47.07611111100,47.06666666700,47.06666666700,47.06138888900,47.06500000000,47.05972222200,47.05694444400,47.05527777800,47.05333333300,47.05250000000,47.05055555600,47.04666666700,47.04861111100,47.04472222200,47.04111111100,47.04361111100,47.03666666700,47.03388888900,47.03722222200,47.03583333300,47.02861111100,47.02305555600,47.02361111100,47.03000000000,47.03027777800,47.02083333300,47.02472222200,47.01972222200,47.01416666700,47.01916666700,47.01500000000,47.01083333300,47.01138888900,47.00944444400,47.00722222200,47.00111111100,47.00500000000,47.00555555600,47.00361111100,47.00027777800,46.99055555600,46.98583333300,46.97888888900,46.97611111100,46.97250000000,46.96638888900,46.96305555600,46.95750000000,46.95611111100,46.94805555600,46.94916666700,46.94222222200,46.93972222200,46.94194444400,46.93666666700,46.93555555600,46.93833333300,46.93666666700,46.93222222200,46.92944444400,46.92833333300,46.92222222200,46.90944444400,46.91055555600,46.90944444400,46.90500000000,46.90722222200,46.90305555600,46.90055555600,46.89583333300,46.89611111100,46.89222222200,46.89527777800,46.88944444400,46.89527777800,46.89305555600,46.88361111100,46.87750000000,46.87361111100,46.87305555600,46.87000000000,46.86972222200,46.86555555600,46.85694444400,46.85333333300,46.85277777800,46.84750000000,46.84944444400,46.84166666700,46.84416666700,46.84222222200,46.83694444400,46.82277777800,46.81888888900,46.82305555600,46.81444444400,46.81333333300,46.80888888900,46.80361111100,46.79972222200,46.79833333300,46.79444444400,46.79222222200,46.78444444400,46.78500000000,46.79083333300,46.79111111100,46.78388888900,46.77861111100,46.77722222200,46.77388888900,46.77555555600,46.77027777800,46.76833333300,46.77055555600,46.75972222200,46.75944444400,46.75527777800,46.75638888900,46.75083333300,46.75083333300,46.74805555600,46.74583333300,46.74305555600,46.74250000000,46.73388888900,46.73555555600,46.73333333300,46.73000000000,46.72861111100,46.72333333300,46.72305555600,46.72055555600,46.72111111100,46.71583333300,46.71166666700,46.70444444400,46.70083333300,46.69611111100,46.68777777800,46.68750000000,46.68583333300,46.68361111100,46.68861111100,46.69055555600,46.68000000000,46.67638888900,46.67333333300,46.67527777800,46.68166666700,46.67972222200,46.67500000000,46.66750000000,46.66722222200,46.65194444400,46.64555555600,46.64444444400,46.64027777800,46.63611111100,46.62972222200,46.62722222200,46.62111111100,46.61555555600,46.61250000000,46.60694444400,46.60388888900,46.60166666700,46.59722222200,46.59305555600,46.59027777800,46.58500000000,46.58111111100,46.57888888900,46.56833333300,46.56388888900,46.56333333300,46.55166666700,46.55361111100,46.54666666700,46.54361111100,46.53666666700,46.53361111100,46.53611111100,46.53583333300,46.53027777800,46.53027777800,46.52527777800,46.52027777800,46.52250000000,46.51861111100,46.51055555600,46.51222222200,46.50500000000,46.50222222200,46.49972222200,46.49888888900,46.49888888900,46.50250000000,46.49555555600,46.49500000000,46.48722222200,46.48444444400,46.47972222200,46.47611111100,46.48000000000,46.47833333300,46.47611111100,46.46972222200,46.46666666700,46.46444444400,46.46166666700,46.45833333300,46.45222222200,46.44750000000,46.44722222200,46.43722222200,46.43222222200,46.42472222200,46.42083333300,46.41527777800,46.41611111100,46.40833333300,46.40638888900,46.40361111100,46.40333333300,46.40000000000,46.39833333300,46.40083333300,46.39444444400,46.38972222200,46.39555555600,46.39194444400,46.38861111100,46.38305555600,46.38138888900,46.38138888900,46.37277777800,46.37388888900,46.37027777800,46.36944444400,46.36666666700,46.36444444400,46.36416666700,46.35944444400,46.35916666700,46.35638888900,46.35694444400,46.35944444400,46.35500000000,46.34972222200,46.35166666700,46.35361111100,46.35222222200,46.34555555600,46.34250000000,46.34694444400,46.34694444400,46.34277777800,46.33861111100,46.33388888900,46.33750000000,46.33305555600,46.33000000000,46.32666666700,46.32277777800,46.32805555600,46.32777777800,46.32055555600,46.32083333300,46.31500000000,46.30305555600,46.30027777800,46.29611111100,46.29388888900,46.29055555600,46.29055555600,46.28527777800,46.29055555600,46.29444444400,46.29777777800,46.29444444400,46.28277777800,46.28166666700,46.28611111100,46.28611111100,46.29166666700,46.29250000000,46.29111111100,46.28166666700,46.27833333300,46.27861111100,46.28500000000,46.28638888900,46.28472222200,46.28166666700,46.26833333300,46.26750000000,46.26388888900,46.26222222200,46.25583333300,46.25750000000,46.25222222200,46.24805555600,46.25083333300,46.24194444400,46.24333333300,46.23888888900,46.24583333300,46.24194444400,46.23055555600,46.22138888900,46.21972222200,46.21500000000,46.21138888900,46.20611111100,46.20194444400,46.20527777800,46.21194444400,46.21166666700,46.20694444400,46.20000000000,46.19583333300,46.19222222200,46.19527777800,46.19194444400,46.19222222200,46.18277777800,46.18583333300,46.18583333300,46.18388888900,46.18111111100,46.17972222200,46.17694444400,46.17583333300,46.17888888900,46.17694444400,46.16444444400,46.16166666700,46.15472222200,46.15555555600,46.15055555600,46.14777777800,46.14361111100,46.13833333300,46.13166666700,46.13027777800,46.12583333300,46.12611111100,46.11166666700,46.11277777800,46.11083333300,46.10777777800,46.10416666700,46.10194444400,46.10388888900,46.09888888900,46.09888888900,46.09611111100,46.09055555600,46.08666666700,46.08333333300,46.07833333300,46.08111111100,46.07833333300,46.07416666700,46.07166666700,46.06805555600,46.06388888900,46.06027777800,46.05944444400,46.05638888900,46.05277777800,46.05416666700,46.05250000000,46.04694444400,46.04333333300,46.04333333300,46.03500000000,46.02027777800,46.01472222200,46.00861111100,45.99972222200,45.99111111100,45.98833333300,45.97833333300,45.97833333300,45.97555555600,45.97277777800,45.96861111100,45.96194444400,45.95416666700,45.94500000000,45.93611111100,45.93138888900,45.92250000000,45.91833333300,45.91361111100,45.90972222200,45.90111111100,45.89916666700,45.88777777800,45.88500000000,45.88277777800,45.88250000000,45.88472222200,45.88166666700,45.87777777800,45.87638888900,45.87055555600,45.86305555600,45.85972222200,45.84972222200,45.84500000000,45.84388888900,45.83527777800,45.83083333300,45.82666666700,45.82333333300,45.82055555600,45.81611111100,45.81333333300,45.80750000000,45.80222222200,45.79861111100,45.79472222200,45.79611111100,45.79416666700,45.79083333300,45.79111111100,45.77833333300,45.78333333300,45.77861111100,45.77555555600,45.77361111100,45.76833333300,45.76416666700,45.76416666700,45.76083333300,45.75444444400,45.75166666700,45.74472222200,45.74472222200,45.74027777800,45.73694444400,45.73111111100,45.72527777800,45.72388888900,45.71777777800,45.70888888900,45.70444444400,45.69777777800,45.69333333300,45.68277777800,45.67944444400,45.66583333300,45.66000000000,45.65416666700,45.65166666700,45.64972222200,45.64888888900,45.64416666700,45.64083333300,45.63583333300,45.62166666700,45.62583333300,45.62361111100,45.61944444400,45.61888888900,45.62277777800,45.62694444400,45.62666666700,45.62166666700,45.61805555600,45.61027777800,45.60611111100,45.59805555600,45.59555555600,45.58833333300,45.58694444400,45.57944444400,45.57611111100,45.57250000000,45.57416666700,45.57138888900,45.57527777800,45.57222222200,45.57138888900,45.57694444400,45.57750000000,45.56777777800,45.56638888900,45.57555555600,45.56583333300,45.56250000000,45.56083333300,45.55472222200,45.54722222200,45.54583333300,45.53666666700,45.53388888900,45.52944444400,45.52472222200,45.52500000000,45.51972222200,45.51138888900,45.51000000000,45.50805555600,45.50055555600,45.50166666700,45.50000000000,45.48583333300,45.48222222200,45.47500000000,45.47138888900,45.47333333300,45.46722222200,45.46055555600,45.45416666700,45.44055555600,45.43027777800,45.40805555600,45.39250000000,45.33083333300,45.32361111100,45.30722222200,45.26611111100,45.25750000000,45.25527777800,45.25111111100,45.23583333300,45.22916666700,45.23000000000,45.24750000000,45.25388888900,45.27416666700,45.28333333300,45.28972222200,45.29833333300,45.30833333300,45.31388888900,45.32222222200,45.33388888900,45.33750000000,45.33638888900,45.30833333300,45.30277777800,45.28500000000,45.28555555600,45.29055555600,45.29638888900,45.31000000000,45.31916666700,45.33166666700,45.35611111100,45.36000000000,45.36555555600,45.37416666700,45.38694444400,45.38805555600,45.38361111100,45.38722222200,45.39750000000,45.39972222200,45.41083333300,45.42027777800,45.43000000000,45.43277777800,45.44194444400,45.44444444400,45.43972222200,45.43916666700,45.44416666700,45.42388888900,45.41083333300,45.40694444400,45.39000000000,45.34388888900,45.31166666700,45.27138888900,45.26250000000,45.25472222200,45.22666666700,45.21666666700,45.15000000000,44.50000000000,44.25000000000,43.68333333300,42.80000000000,42.46168333800,42.11666666700,41.98333333300,41.98333333300,41.98722222200,41.99472222200,41.99388888900,41.98944444400,41.98361111100,41.98916666700,41.98638888900,41.98944444400,41.98194444400,41.98472222200,41.98111111100,41.98166666700,41.98666666700,41.99472222200,41.99694444400,41.99833333300,42.00972222200,42.01000000000,42.00861111100,41.99972222200,41.99750000000,41.99750000000,42.00527777800,42.00527777800,41.99750000000,42.00055555600,41.99361111100,41.98472222200,41.97888888900,41.96888888900,41.96555555600,41.96833333300,41.96638888900,41.96027777800,41.95638888900,41.95500000000,41.95555555600,41.95972222200,41.95861111100,41.95083333300,41.94888888900,41.95027777800,41.95638888900,41.95861111100,41.95583333300,41.96027777800,41.95944444400,41.96055555600,41.96833333300,41.96972222200,41.97194444400,41.96833333300,41.97333333300,41.97333333300,41.97555555600,41.98055555600,41.98222222200,41.98527777800,41.97972222200,41.98333333300,41.98500000000,41.98277777800,41.97861111100,41.97888888900,41.97666666700,41.97027777800,41.96944444400,41.96472222200,41.96416666700,41.96944444400,41.96333333300,41.96388888900,41.96805555600,41.96694444400,41.96194444400,41.96583333300,41.96305555600,41.96527777800,41.96416666700,41.96194444400,41.95666666700,41.94888888900,41.94750000000,41.95361111100,41.95527777800,41.94194444400,41.94722222200,41.94222222200,41.93305555600,41.93138888900,41.92888888900,41.92472222200,41.92166666700,41.91777777800,41.91305555600,41.91111111100,41.92388888900,41.94666666700,41.96000000000,41.96222222200,41.96000000000,41.96111111100,41.97750000000,41.97750000000,41.98194444400,41.99361111100,41.99666666700,41.99666666700,42.00583333300,42.01861111100,42.02972222200,42.05361111100,42.06166666700,42.06527777800,42.07444444400,42.08666666700,42.09250000000,42.09833333300,42.10055555600,42.10750000000,42.10472222200,42.10750000000,42.10166666700,42.09000000000,42.08416666700,42.07444444400,42.06972222200,42.06500000000,42.06500000000,42.07444444400,42.07027777800,42.07250000000,42.07527777800,42.08750000000,42.09111111100,42.09111111100,42.09666666700,42.08666666700,42.08500000000,42.06694444400,42.05888888900,42.04638888900,42.04111111100,42.03888888900,42.03472222200,42.01916666700,42.01027777800,42.00444444400,42.00388888900,41.99611111100,41.99361111100,41.99250000000,41.98472222200,41.97583333300,41.97416666700,41.97972222200,41.98305555600,41.99000000000,41.97444444400,41.96305555600,41.96750000000,41.96583333300,41.97000000000,41.96916666700,41.97305555600,41.97222222200,41.97555555600,41.98222222200,41.98333333300,41.96611111100,41.95805555600,41.94416666700,41.92972222200,41.92277777800,41.90750000000,41.88833333300,41.87944444400,41.87083333300,41.85805555600,41.84472222200,41.84083333300,41.83638888900,41.83527777800,41.83611111100,41.83250000000,41.78277777800,41.75861111100,41.74777777800,41.71972222200,41.70250000000,41.69222222200,41.69500000000,41.67750000000,41.66916666700,41.66166666700,41.64972222200,41.63888888900,41.62694444400,41.62250000000,41.61944444400,41.61555555600,41.59722222200,41.58361111100,41.55250000000,41.53861111100,41.53111111100,41.52277777800,41.50472222200,41.49111111100,41.48027777800,41.47194444400,41.44972222200,41.43916666700,41.42833333300,41.39083333300,41.35611111100,41.34638888900,41.34138888900,41.32861111100,41.32888888900,41.33555555600,41.34583333300,41.34777777800,41.34472222200,41.34694444400,41.33833333300,41.33527777800,41.33083333300,41.31750000000,41.30472222200,41.29333333300,41.28666666700,41.27083333300,41.26361111100,41.26055555600,41.25916666700,41.26805555600,41.26111111100,41.25638888900,41.24333333300,41.23638888900,41.22500000000,41.21777777800,41.21111111100,41.19777777800,41.18972222200,41.18250000000,41.16500000000,41.15416666700,41.14972222200,41.14055555600,41.13472222200,41.12777777800,41.11916666700,41.11388888900,41.12055555600,41.12138888900,41.11416666700,41.10638888900,41.09194444400,41.08166666700,41.05638888900,41.05000000000,41.04722222200,41.04833333300,41.04000000000,41.03527777800,41.02611111100,41.00361111100,40.99888888900,41.00000000000,40.99583333300,40.99194444400,40.98722222200,40.96583333300,40.96083333300,40.95388888900,40.94972222200,40.94027777800,40.93861111100,40.94000000000,40.93777777800,40.92888888900,40.92222222200,40.91555555600,40.91416666700,40.91027777800,40.89972222200,40.89916666700,40.90638888900,40.92166666700,40.90861111100,40.89444444400,40.89138888900,40.89055555600,40.89805555600,40.89055555600,40.88222222200,40.87777777800,40.87472222200,40.87083333300,40.86555555600,40.85972222200,40.85583333300,40.85694444400,40.85472222200,40.84333333300,40.84388888900,40.83944444400,40.83527777800,40.81861111100,40.82222222200,40.82333333300,40.81666666700,40.80972222200,40.78166666700,40.76777777800,40.76194444400,40.75444444400,40.74333333300,40.73750000000,40.74277777800,40.74555555600,40.61666666700,40.38333333300,40.25000000000,40.10000000000,39.95000000000,39.50000000000,39.38333333300,39.46666666700,39.01666666700,38.66666666700,38.48333333300,38.30000000000,38.21666666700,38.18333333300,38.00000000000,38.00000000000,37.83333333300,37.71666666700,37.66666666700,37.56666666700,37.55000000000,37.26666666700,37.15000000000,36.96666666700,36.90000000000,36.81666666700,36.73333333300,36.56666666700,36.71666666700,36.70000000000,36.51666666700,36.56666666700,36.21666666700,36.10000000000,36.18333333300,36.18333333300,36.06666666700,36.08333333300,36.05265561100,36.02406605900,35.99168103000,35.95550806200,35.91555555600,35.91555555600,35.58333333300,35.41666666700,35.26666666700,34.91666666700,34.63333333300,34.55281944400,34.55777238300,34.55798273700,34.55344915500,34.54420079500,34.53029712500,34.51182750700,34.48891058200,34.46169344500,34.43336536600,34.40177732100,34.36709638600,34.32820491900,34.28781616400,34.24346603600,34.19824791600,34.14940228500,34.08698522800,34.02226120000,33.95577224100,33.88807389600,33.81973049500,33.75131040700,33.68338130600,33.61476488000,33.54954422300,33.48648091400,33.42609346900,33.36741886300,33.31394454400,33.26331854100,33.21854845300,33.17766388900,33.10000000000,33.10000000000,33.08833333300,32.77666666700,32.72631388900,32.70241769200,32.67345623900,32.64027386700,32.60308417800,32.56212628400,32.51766317800,32.46997994800,32.41938185400,32.35333692500,32.28229510300,32.20850614100,32.13271917200,32.05570174200,31.97823193100,31.90109044700,31.82505277800,32.26179841000,32.68252982500,33.09533004300,33.50000000000,33.63244375400,33.76076547600,33.88493308900,34.00000000000,34.00000000000,34.33333333300,34.33333333300,37.50000000000,37.88474606800,38.26309688200,38.63489964700,39.00000000000,39.00000000000,38.67101054600,38.33333333300,38.10426541500,37.87190851000,37.63630996100,37.37565173000,37.13342748400,36.86565305500,36.61700766300,36.34233906200,36.25000000000,35.83333333300,35.83333333300,35.96666666700,35.96666666700,35.52404521600,35.08050418200,34.63606743900,34.15361043200,33.70738147200,33.26032639900,32.73774647800,32.23905929000,32.18063043000,32.11779410200,32.05548403700,31.99534888200,31.93751366200,31.88209840800,31.82921793200,31.77898162100,31.73149323400,31.68184869100,31.63587756900,31.59369767900,31.55541697800,31.52113333000,31.49093429000,31.46488997900,31.44307366900,31.42554470800,31.41234776900,31.40351647000,31.39907330100,31.39898559400,31.40324984000,31.41190289500,31.42492272400,31.44227615900,31.46391897600,31.48979598800,31.51984116800,31.55397779100,31.59211860500,31.63416602300,31.67902049100,31.72847603500,31.78148887700,31.83792264700,31.89763193800,31.96046264300,32.02625230100,32.09483047400,32.16451065200,32.26467707100,32.36718849800,32.47475538500,32.58356738000,32.69649802100,32.80954329600,32.92389047400,33.03899838000,33.15432018400,33.26930593000,33.38340514000,33.49606944700,33.60675526800,33.71325834200,33.81844050300,33.91851867300,33.98309340400,34.04432293700,34.10506366200,34.16230058600,34.23698190400,34.47887930800,35.00032217900,35.49598847500,36.01083708700,36.50000000000,42.00000000000,42.26140464700,42.50976086200,42.75597105800,43.00000000000,45.00000000000,45.00000000000,51.00000000000,51.00000000000,54.00000000000,54.08532176400,54.16102782400,54.23971350200,54.30925386700,54.38121809600,54.44451669900,54.50968013900,54.56666666700,61.00000000000,61.00000000000,63.00000000000,63.00000000000,63.28073235400,63.55090805200,63.82054697600,64.08952260300,64.35770869700,64.61257913700,64.87960336000,65.13333333300,65.61833333300,65.75000000000,66.23520008200,66.49955786700,66.75081311900,67.00097242000,67.25000000000,67.51019810100,67.73677935600,67.99443943700,68.21872693800,68.47367881400,68.69551778600,68.91615767400,69.13556073100,69.35368782200,69.57049836900,69.78595030000,70.00000000000,70.19251303700,70.37159650400,70.53755632400,70.70581152100,70.86602524500,71.00741706200,71.15155195700,71.27767343900,71.33333333300,71.33333333300,71.00000000000,70.84318917600,70.68534681600,70.52649787700,70.36666666700,70.00000000000,69.79439722200,69.78590833300,69.77888333300,69.77246666700]
    Graph.lonFIREur=[30.84052500000,30.84689166700,30.85287500000,30.85038888900,30.85313888900,30.85080555600,30.85486388900,30.85904166700,30.86678333300,30.86225555600,30.86140833300,30.86594166700,30.86680833300,30.87033611100,30.87208611100,30.86978611100,30.87724722200,30.86798055600,30.87104444400,30.86992777800,30.87344444400,30.87268055600,30.87759166700,30.87937500000,30.89042222200,30.88832222200,30.89166666700,30.89069444400,30.88530277800,30.89298055600,30.88796111100,30.89064444400,30.88355555600,30.87796111100,30.87419444400,30.88103611100,30.88161111100,30.88611666700,30.89938888900,30.89116111100,30.89124722200,30.89637777800,30.89954166700,30.90885000000,30.90957500000,30.91981111100,30.91636388900,30.92389722200,30.92999166700,30.93649722200,30.93563888900,30.94509722200,30.94244166700,30.94585000000,30.94206111100,30.94640000000,30.93435277800,30.93665277800,30.92804444400,30.92289722200,30.92540277800,30.93101388900,30.92966388900,30.93435833300,30.93402222200,30.93939166700,30.93917222200,30.94328055600,30.95252500000,30.95139166700,30.95443333300,30.94914166700,30.95303611100,30.94813333300,30.94949166700,30.93883333300,30.94745277800,30.94308611100,30.94689166700,30.93907777800,30.93878611100,30.91595555600,30.89068611100,30.88728611100,30.86125000000,30.83922777800,30.81638333300,30.66421944400,30.56605277800,30.51553888900,30.50756944400,30.41776944400,30.30364444400,30.22377222200,30.15108333300,30.08526388900,30.09095000000,30.13731666700,30.14804166700,30.15036666700,30.15311111100,30.15165833300,30.15803611100,30.15988611100,30.16545833300,30.17993611100,30.17838888900,30.18811666700,30.18771111100,30.18065000000,30.18565555600,30.17990000000,30.17814722200,30.17086944400,30.16105555600,30.14983333300,30.14093611100,30.13115000000,30.12172222200,30.11793333300,30.11671944400,30.11251388900,30.11760555600,30.11531666700,30.07708888900,30.04692222200,30.03157500000,29.98928888900,29.94473333300,29.93486111100,29.93228333300,29.91521388900,29.90025277800,29.87132222200,29.85306388900,29.79690833300,29.78678333300,29.72267500000,29.72052777800,29.71165277800,29.71241388900,29.69791666700,29.69720833300,29.69435000000,29.64384722200,29.62756666700,29.57065000000,29.53846111100,29.53141388900,29.52828611100,29.52737777800,29.52338333300,29.51380555600,29.50555000000,29.48555000000,29.44110833300,29.41362500000,29.39573888900,29.35682500000,29.33582222200,29.31994722200,29.29685000000,29.28537500000,29.28231111100,29.27656111100,29.27804166700,29.28794722200,29.31242500000,29.31329444400,29.30358333300,29.30059722200,29.30557777800,29.29320833300,29.29630833300,29.29026111100,29.29489722200,29.28928055600,29.26913888900,29.24812222200,29.25718888900,29.25714444400,29.24626944400,29.23963333300,29.24384444400,29.23871111100,29.23241944400,29.23115000000,29.24229722200,29.15938333300,29.14205000000,29.09418333300,29.05664444400,29.04129722200,29.01971388900,28.92944444400,28.85833333300,28.92916666700,28.49583333300,28.41583333300,28.46805555600,28.66138888900,28.80083333300,28.70638888900,28.43388888900,28.64611111100,29.32722222200,29.65944444400,30.01694444400,29.93027777800,29.85916666700,29.84000000000,29.76250000000,29.71472222200,29.71694444400,29.71611111100,29.68611111100,29.67611111100,29.65777777800,29.65027777800,29.65138888900,29.64555555600,29.62388888900,29.62138888900,29.62277777800,29.61638888900,29.64194444400,29.64500000000,29.64222222200,29.64500000000,29.61666666700,29.61166666700,29.58416666700,29.57805555600,29.56583333300,29.56638888900,29.56416666700,29.58000000000,29.56972222200,29.57111111100,29.55027777800,29.53888888900,29.53611111100,29.53861111100,29.52250000000,29.51444444400,29.50444444400,29.51638888900,29.43444444400,29.07333333300,29.04083333300,29.03388888900,29.03333333300,29.06055555600,29.11888888900,29.10416666700,29.10583333300,29.13194444400,29.13222222200,29.14111111100,29.14944444400,29.27527777800,29.35444444400,29.36111111100,29.36083333300,29.35833333300,29.36305555600,29.36000000000,29.38611111100,29.37611111100,29.38250000000,29.40000000000,29.41000000000,29.41916666700,29.41055555600,29.42250000000,29.47194444400,29.51944444400,29.63138888900,29.66222222200,29.69694444400,29.70666666700,29.70472222200,29.69472222200,29.69666666700,29.70333333300,29.70944444400,29.92333333300,29.97083333300,29.98111111100,29.97361111100,29.98416666700,29.99250000000,29.98916666700,29.99722222200,30.02416666700,30.02444444400,30.06833333300,30.08722222200,30.11944444400,30.13416666700,30.13833333300,30.03972222200,30.01722222200,29.72194444400,29.75388888900,29.83083333300,29.86388888900,29.79833333300,29.75472222200,29.74888888900,29.73305555600,29.72750000000,29.73138888900,29.74666666700,29.64611111100,29.60916666700,29.60166666700,29.63388888900,29.70055555600,29.74416666700,29.76416666700,29.85944444400,29.88555555600,29.89361111100,29.81944444400,29.85027777800,29.86388888900,29.85277777800,29.89694444400,29.87194444400,29.83083333300,29.73277777800,29.62694444400,29.61444444400,29.59944444400,29.61916666700,29.61111111100,29.64500000000,29.68138888900,29.69972222200,29.68750000000,29.73972222200,29.86888888900,29.89750000000,29.99583333300,30.00722222200,30.04305555600,30.08638888900,30.09111111100,30.08555555600,30.04138888900,30.05361111100,30.13583333300,30.13000000000,30.11888888900,30.05444444400,29.98944444400,29.99750000000,29.98694444400,30.01472222200,30.02972222200,30.02444444400,30.04583333300,30.05833333300,30.05000000000,30.05722222200,30.04500000000,30.11000000000,30.13722222200,30.21027777800,30.28555555600,30.30222222200,30.36694444400,30.36083333300,30.38833333300,30.48250000000,30.50972222200,30.46638888900,30.51583333300,30.55333333300,30.55361111100,30.52805555600,30.49194444400,30.44694444400,30.35361111100,30.32083333300,30.26027777800,30.15027777800,29.97194444400,30.06472222200,30.06055555600,30.06722222200,30.07388888900,30.07277777800,30.10888888900,30.12388888900,30.24416666700,30.25805555600,30.38444444400,30.48388888900,30.66916666700,30.78777777800,30.84250000000,30.84361111100,30.84666666700,30.84500000000,30.85083333300,30.86666666700,30.87277777800,30.87722222200,30.93444444400,30.94416666700,30.97916666700,30.98638888900,30.99250000000,31.02055555600,31.08555555600,31.10194444400,31.12611111100,31.13138888900,31.13722222200,31.14666666700,31.16444444400,31.18444444400,31.21138888900,31.22000000000,31.23750000000,31.24083333300,31.23833333300,31.24555555600,31.25472222200,31.25555555600,31.26527777800,31.27222222200,31.29388888900,31.36361111100,31.38055555600,31.38138888900,31.38777777800,31.38750000000,31.41055555600,31.42500000000,31.46305555600,31.44888888900,31.50222222200,31.57166666700,31.58111111100,31.58666666700,31.45555555600,31.46666666700,31.43916666700,31.38027777800,31.38500000000,31.38527777800,31.38111111100,31.37944444400,31.37611111100,31.37722222200,31.37305555600,31.36222222200,31.34583333300,31.34944444400,31.34527777800,31.25416666700,31.24416666700,31.24527777800,31.22166666700,31.18472222200,31.18611111100,31.17333333300,31.16250000000,31.16250000000,31.13805555600,30.94277777800,30.96222222200,30.95500000000,30.94333333300,30.90416666700,30.83416666700,30.81083333300,30.80861111100,30.76500000000,30.74472222200,30.72027777800,30.68888888900,30.65694444400,30.63638888900,30.62916666700,30.62972222200,30.63555555600,30.60277777800,30.56416666700,30.48305555600,30.44361111100,30.44722222200,30.44388888900,30.43888888900,30.42333333300,30.37694444400,30.35166666700,30.33750000000,30.32777777800,30.30555555600,30.30444444400,30.31277777800,30.30083333300,30.27416666700,30.21138888900,30.19416666700,30.19611111100,30.15555555600,30.07500000000,30.07111111100,30.04722222200,30.03805555600,29.86805555600,29.86166666700,29.86166666700,29.84555555600,29.81861111100,29.81000000000,29.80305555600,29.79361111100,29.75472222200,29.74805555600,29.74055555600,29.71111111100,29.68861111100,29.64333333300,29.64527777800,29.60722222200,29.60055555600,29.59138888900,29.57888888900,29.55805555600,29.49611111100,29.50305555600,29.32472222200,29.32222222200,29.26555555600,29.24138888900,29.24555555600,29.24472222200,29.22166666700,29.20861111100,29.19972222200,29.17722222200,29.17527777800,29.17277777800,29.16194444400,29.02194444400,28.98555555600,28.95694444400,28.91500000000,28.90250000000,28.88361111100,28.87277777800,28.81916666700,28.80805555600,28.80416666700,28.71388888900,28.71027777800,28.68416666700,28.65500000000,28.64916666700,28.61472222200,28.57277777800,28.53722222200,28.52750000000,28.52472222200,28.49305555600,28.48361111100,28.48416666700,28.46527777800,28.39805555600,28.40000000000,28.39750000000,28.39277777800,28.33555555600,28.32416666700,28.31194444400,28.25583333300,28.22055555600,28.17416666700,28.13555555600,28.08888888900,28.01527777800,28.01777777800,27.99805555600,27.99527777800,27.87333333300,27.84777777800,27.83833333300,27.84472222200,27.84222222200,27.84722222200,27.81444444400,27.77444444400,27.77666666700,27.76833333300,27.76500000000,27.76805555600,27.75666666700,27.74833333300,27.74805555600,27.69444444400,27.68694444400,27.72583333300,27.45666666700,27.29305555600,26.55000000000,26.11166666700,25.86666666700,26.81877146800,27.63666666700,28.08222222200,28.13055555600,28.19583333300,28.20388888900,28.21000000000,28.20861111100,28.19777777800,28.12750000000,28.11722222200,28.10250000000,28.02944444400,28.01000000000,27.97083333300,27.95277777800,27.90416666700,27.90083333300,27.90444444400,27.90277777800,27.86555555600,27.82388888900,27.80833333300,27.79222222200,27.79250000000,27.74861111100,27.74638888900,27.73888888900,27.72555555600,27.69777777800,27.35694444400,27.42833333300,27.56055555600,27.48750000000,27.49138888900,27.48694444400,27.50638888900,27.58861111100,27.63305555600,27.60666666700,27.61222222200,27.60611111100,27.61527777800,27.62527777800,27.63833333300,27.65500000000,27.68250000000,27.69527777800,27.69833333300,27.69444444400,27.68305555600,27.68111111100,27.69555555600,27.69527777800,27.69861111100,27.71861111100,27.72750000000,27.73194444400,27.78555555600,27.79666666700,27.80638888900,27.81666666700,27.82611111100,27.82694444400,27.80166666700,27.79555555600,27.77888888900,27.74666666700,27.73638888900,27.71055555600,27.65888888900,27.55944444400,27.54250000000,27.52444444400,27.51083333300,27.50138888900,27.50583333300,27.51722222200,27.53472222200,27.54000000000,27.53111111100,27.52388888900,27.50722222200,27.48194444400,27.47472222200,27.44500000000,27.39388888900,27.38083333300,27.39861111100,27.40083333300,27.37861111100,27.37250000000,27.36666666700,27.34694444400,27.33361111100,27.32722222200,27.33583333300,27.35138888900,27.39861111100,27.44500000000,27.51277777800,27.55111111100,27.54750000000,27.54916666700,27.56722222200,27.56472222200,27.55305555600,27.51666666700,27.51194444400,27.51361111100,27.52111111100,27.57500000000,27.64027777800,27.64972222200,27.68027777800,27.76222222200,27.79333333300,27.83944444400,27.85111111100,27.86166666700,27.86694444400,27.86416666700,27.82138888900,27.81305555600,27.79027777800,27.77055555600,27.75888888900,27.74833333300,27.72694444400,27.72250000000,27.72666666700,27.74583333300,27.75222222200,27.74527777800,27.73194444400,27.72861111100,27.71750000000,27.71888888900,27.73527777800,27.74083333300,27.73916666700,27.73111111100,27.73305555600,27.73000000000,27.72333333300,27.67194444400,27.66777777800,27.67527777800,27.66666666700,27.66694444400,27.68805555600,27.70888888900,27.71805555600,27.75416666700,27.77000000000,27.79166666700,27.79750000000,27.80027777800,27.80916666700,27.84638888900,27.86861111100,27.90222222200,27.92333333300,27.94888888900,27.97194444400,27.97500000000,27.97222222200,27.95444444400,27.95000000000,27.95138888900,27.91805555600,27.90166666700,27.90916666700,27.90805555600,27.92055555600,27.95444444400,27.96194444400,27.98333333300,27.98222222200,28.00944444400,28.01555555600,28.01638888900,28.03444444400,28.03972222200,28.05666666700,28.07888888900,28.13361111100,28.13944444400,28.14083333300,28.13888888900,28.10944444400,28.09972222200,28.10250000000,28.11055555600,28.12055555600,28.12666666700,28.12000000000,28.12277777800,28.14250000000,28.18444444400,28.19166666700,28.18361111100,28.16500000000,28.19833333300,28.21277777800,28.24111111100,28.24111111100,28.19250000000,28.18888888900,28.20305555600,28.19111111100,28.18111111100,28.17555555600,28.11694444400,28.10722222200,28.08722222200,28.05027777800,28.04083333300,28.00638888900,27.96916666700,27.95500000000,27.95388888900,27.93638888900,27.90472222200,27.87722222200,27.86277777800,27.82250000000,27.80722222200,27.81277777800,27.82444444400,27.81083333300,27.82000000000,27.80472222200,27.75722222200,27.66527777800,27.65333333300,27.62527777800,27.63388888900,27.61500000000,27.60305555600,27.58666666700,27.46583333300,27.43361111100,27.41055555600,27.38833333300,27.37222222200,27.36111111100,27.32305555600,27.29972222200,27.28527777800,27.25694444400,27.22527777800,27.20388888900,27.19361111100,27.17583333300,27.13277777800,27.09805555600,27.08333333300,27.04416666700,27.00805555600,26.92222222200,26.90555555600,26.88694444400,26.87944444400,26.86111111100,26.83611111100,26.81444444400,26.80361111100,26.78000000000,26.74805555600,26.70166666700,26.66777777800,26.64611111100,26.61972222200,26.63166666700,26.62555555600,26.62527777800,26.62833333300,26.61750000000,26.59944444400,26.59388888900,26.57388888900,26.53805555600,26.51638888900,26.51638888900,26.53250000000,26.55000000000,26.55888888900,26.51861111100,26.49222222200,26.48500000000,26.48194444400,26.49638888900,26.54027777800,26.56500000000,26.58277777800,26.59333333300,26.62027777800,26.62916666700,26.64611111100,26.65972222200,26.66500000000,26.68083333300,26.72888888900,26.74833333300,26.78750000000,26.79805555600,26.81055555600,26.82444444400,26.84583333300,26.85277777800,26.86333333300,26.87194444400,26.85250000000,26.74333333300,26.73055555600,26.72638888900,26.71194444400,26.68555555600,26.67472222200,26.67638888900,26.69194444400,26.69361111100,26.67722222200,26.65777777800,26.63638888900,26.61500000000,26.60277777800,26.55472222200,26.52500000000,26.49833333300,26.46777777800,26.44666666700,26.43611111100,26.37250000000,26.32638888900,26.26222222200,26.26194444400,26.27611111100,26.27250000000,26.25472222200,26.24555555600,26.22194444400,26.13027777800,26.10194444400,26.09638888900,26.06833333300,26.05000000000,26.03583333300,26.01305555600,26.00277777800,25.98416666700,25.97000000000,25.91000000000,25.86777777800,25.85694444400,25.85388888900,25.80305555600,25.75416666700,25.74638888900,25.74333333300,25.75583333300,25.76027777800,25.76055555600,25.74222222200,25.73916666700,25.74222222200,25.75138888900,25.75777777800,25.76527777800,25.76111111100,25.73500000000,25.72305555600,25.71277777800,25.70194444400,25.68777777800,25.67083333300,25.64527777800,25.62694444400,25.62388888900,25.63944444400,25.63777777800,25.63194444400,25.61055555600,25.60611111100,25.59250000000,25.56972222200,25.55916666700,25.55916666700,25.55944444400,25.56388888900,25.59583333300,25.63527777800,25.66277777800,25.69305555600,25.70694444400,25.72055555600,25.72944444400,25.76472222200,25.76861111100,25.77638888900,25.80833333300,25.81027777800,25.80638888900,25.78611111100,25.77833333300,25.79694444400,25.79194444400,25.79583333300,25.79388888900,25.78138888900,25.76277777800,25.74361111100,25.67944444400,25.66500000000,25.65527777800,25.63583333300,25.60194444400,25.57000000000,25.54277777800,25.52805555600,25.52416666700,25.53083333300,25.55694444400,25.57722222200,25.58027777800,25.57916666700,25.57611111100,25.58777777800,25.58666666700,25.55638888900,25.52888888900,25.52305555600,25.52194444400,25.51527777800,25.50444444400,25.49277777800,25.45000000000,25.43166666700,25.40361111100,25.37611111100,25.33277777800,25.28972222200,25.24222222200,25.16000000000,25.07777777800,25.05527777800,25.02222222200,24.97138888900,24.95416666700,24.88694444400,24.85083333300,24.83166666700,24.82166666700,24.81000000000,24.80527777800,24.81611111100,24.83722222200,24.84194444400,24.82972222200,24.81222222200,24.78222222200,24.76777777800,24.75916666700,24.73583333300,24.71916666700,24.71166666700,24.69611111100,24.69500000000,24.70944444400,24.71694444400,24.71055555600,24.70611111100,24.68555555600,24.63222222200,24.56222222200,24.51777777800,24.46388888900,24.43333333300,24.38500000000,24.31583333300,24.24666666700,24.21166666700,24.18694444400,24.15527777800,24.13638888900,24.12722222200,24.11500000000,23.99750000000,23.93583333300,23.91861111100,23.92055555600,23.90527777800,23.87416666700,23.84638888900,23.82138888900,23.80083333300,23.82583333300,23.82305555600,23.80500000000,23.78666666700,23.76500000000,23.74222222200,23.68694444400,23.66666666700,23.63611111100,23.61361111100,23.60083333300,23.50583333300,23.52722222200,23.53972222200,23.55416666700,23.55916666700,23.56583333300,23.57750000000,23.59861111100,23.61083333300,23.61111111100,23.60777777800,23.60750000000,23.61388888900,23.61388888900,23.63250000000,23.63833333300,23.66194444400,23.68055555600,23.68833333300,23.77861111100,23.80277777800,23.81972222200,23.83166666700,23.86805555600,23.87055555600,23.86611111100,23.86472222200,23.87138888900,23.87805555600,23.90944444400,23.92027777800,23.92138888900,23.91666666700,23.91888888900,23.90277777800,23.89111111100,23.89444444400,23.88916666700,23.88694444400,23.87638888900,23.88833333300,23.89000000000,23.90833333300,23.91250000000,23.90972222200,23.91888888900,23.93861111100,23.94944444400,23.95611111100,23.94083333300,23.93277777800,23.92833333300,23.92444444400,23.54416666700,23.45444444400,23.40750000000,23.33388888900,23.29083333300,23.24305555600,23.20444444400,23.17694444400,23.20861111100,23.21083333300,23.20583333300,23.20583333300,23.21277777800,23.21250000000,23.20333333300,23.19944444400,23.20583333300,23.21388888900,23.22944444400,23.27333333300,23.31027777800,23.31416666700,23.30500000000,23.30583333300,23.34527777800,23.35333333300,23.36027777800,23.35888888900,23.36527777800,23.37388888900,23.37416666700,23.38055555600,23.38944444400,23.39722222200,23.39916666700,23.39777777800,23.40555555600,23.40638888900,23.40111111100,23.40416666700,23.41194444400,23.42222222200,23.42722222200,23.43500000000,23.45333333300,23.46694444400,23.46583333300,23.47194444400,23.48055555600,23.49000000000,23.49972222200,23.50888888900,23.50944444400,23.49722222200,23.49722222200,23.49027777800,23.49277777800,23.49805555600,23.50361111100,23.51555555600,23.51861111100,23.51972222200,23.51666666700,23.52444444400,23.52833333300,23.54472222200,23.55000000000,23.56666666700,23.59777777800,23.61000000000,23.62361111100,23.65444444400,23.65916666700,23.65805555600,23.66305555600,23.66638888900,23.66305555600,23.68166666700,23.69194444400,23.69611111100,23.69000000000,23.67388888900,23.66972222200,23.67444444400,23.67305555600,23.66888888900,23.66500000000,23.65611111100,23.64583333300,23.63166666700,23.64638888900,23.64972222200,23.64833333300,23.64027777800,23.63527777800,23.62194444400,23.61666666700,23.62611111100,23.62277777800,23.62666666700,23.64194444400,23.64194444400,23.63027777800,23.63750000000,23.62194444400,23.61333333300,23.61250000000,23.61583333300,23.62083333300,23.61805555600,23.60527777800,23.61472222200,23.60833333300,23.62555555600,23.63027777800,23.63861111100,23.64333333300,23.63583333300,23.63388888900,23.62750000000,23.62111111100,23.61555555600,23.60777777800,23.59722222200,23.58027777800,23.56500000000,23.55055555600,23.54138888900,23.53750000000,23.53583333300,23.53361111100,23.54000000000,23.53972222200,23.54444444400,23.54916666700,23.55666666700,23.55416666700,23.55777777800,23.55333333300,23.56111111100,23.56111111100,23.55194444400,23.55388888900,23.56388888900,23.55833333300,23.55694444400,23.55972222200,23.55722222200,23.54916666700,23.54444444400,23.54666666700,23.54027777800,23.55083333300,23.54583333300,23.54916666700,23.55000000000,23.54555555600,23.54750000000,23.55361111100,23.55666666700,23.56638888900,23.57027777800,23.57944444400,23.57083333300,23.57277777800,23.58861111100,23.59888888900,23.60555555600,23.61583333300,23.61916666700,23.61833333300,23.62638888900,23.62250000000,23.62750000000,23.64555555600,23.66416666700,23.67111111100,23.67916666700,23.66083333300,23.65388888900,23.65222222200,23.65861111100,23.68472222200,23.68833333300,23.68333333300,23.69111111100,23.69444444400,23.70416666700,23.69833333300,23.70250000000,23.70611111100,23.69083333300,23.68777777800,23.68305555600,23.69000000000,23.68472222200,23.68388888900,23.68694444400,23.68611111100,23.67194444400,23.66944444400,23.66083333300,23.65611111100,23.66111111100,23.64472222200,23.64083333300,23.64333333300,23.65194444400,23.65416666700,23.67083333300,23.68694444400,23.70166666700,23.71222222200,23.72000000000,23.72833333300,23.73055555600,23.72916666700,23.73361111100,23.74055555600,23.74444444400,23.74250000000,23.74805555600,23.74805555600,23.74361111100,23.74611111100,23.75888888900,23.76111111100,23.77500000000,23.78277777800,23.78750000000,23.79194444400,23.80250000000,23.81694444400,23.82222222200,23.82888888900,23.82944444400,23.83611111100,23.85083333300,23.85416666700,23.85833333300,23.86638888900,23.86777777800,23.87305555600,23.87194444400,23.87638888900,23.87388888900,23.86722222200,23.86305555600,23.85666666700,23.86638888900,23.86722222200,23.86472222200,23.87638888900,23.88638888900,23.89222222200,23.90777777800,23.91194444400,23.91805555600,23.91916666700,23.91666666700,23.92277777800,23.92000000000,23.92138888900,23.92722222200,23.93666666700,23.93555555600,23.92583333300,23.93111111100,23.93222222200,23.94027777800,23.92472222200,23.92250000000,23.95361111100,23.96833333300,23.97333333300,23.97666666700,23.99111111100,24.00388888900,24.04611111100,24.05888888900,24.08722222200,24.10361111100,24.11861111100,24.12361111100,24.13944444400,24.15055555600,24.15083333300,24.14861111100,24.12222222200,24.10555555600,24.05166666700,24.03777777800,23.99305555600,23.97055555600,23.97055555600,23.96472222200,23.97111111100,23.96861111100,23.98361111100,24.01166666700,24.02277777800,24.02611111100,24.01972222200,24.02305555600,24.01916666700,24.02277777800,24.02000000000,24.02916666700,24.04111111100,24.07138888900,24.07416666700,24.07277777800,24.06166666700,24.05611111100,24.05527777800,24.06444444400,24.07250000000,24.07361111100,24.08333333300,24.08527777800,24.08944444400,24.08944444400,24.09222222200,24.08500000000,24.09055555600,24.09166666700,24.10888888900,24.10250000000,24.08805555600,24.07805555600,24.06055555600,24.04277777800,24.02500000000,23.93694444400,23.89277777800,23.82111111100,23.77805555600,23.75500000000,23.75083333300,23.73194444400,23.72083333300,23.70472222200,23.69555555600,23.69027777800,23.62722222200,23.61000000000,23.60194444400,23.55305555600,23.45527777800,23.40055555600,23.37277777800,23.33055555600,23.31888888900,23.29222222200,23.28611111100,23.27666666700,23.24388888900,23.23055555600,23.22416666700,23.22055555600,23.21305555600,23.17861111100,23.02277777800,22.97416666700,22.95638888900,22.94000000000,22.90833333300,22.90416666700,22.90444444400,22.90055555600,22.89694444400,22.86444444400,22.86138888900,22.85000000000,22.80333333300,22.79388888900,22.76277777800,22.69833333300,22.68027777800,22.67583333300,22.66777777800,22.66694444400,22.67111111100,22.70000000000,22.69694444400,22.70472222200,22.72305555600,22.72916666700,22.72916666700,22.74055555600,22.74611111100,22.75861111100,22.75750000000,22.74888888900,22.74444444400,22.73388888900,22.73305555600,22.73805555600,22.74611111100,22.75111111100,22.73416666700,22.73250000000,22.72583333300,22.71361111100,22.71750000000,22.72472222200,22.73805555600,22.74555555600,22.75777777800,22.76111111100,22.75500000000,22.75388888900,22.74944444400,22.74583333300,22.74750000000,22.76305555600,22.79666666700,22.80055555600,22.79888888900,22.81527777800,22.83500000000,22.83611111100,22.85111111100,22.85694444400,22.86361111100,22.86638888900,22.86250000000,22.87250000000,22.89361111100,22.89611111100,22.88694444400,22.87333333300,22.87305555600,22.87638888900,22.87416666700,22.87638888900,22.88111111100,22.87472222200,22.87555555600,22.88583333300,22.88750000000,22.88222222200,22.88638888900,22.89805555600,22.89666666700,22.88750000000,22.82750000000,22.78388888900,22.77833333300,22.76250000000,22.72472222200,22.71500000000,22.69666666700,22.67888888900,22.65861111100,22.64472222200,22.63722222200,22.62472222200,22.60194444400,22.59083333300,22.57888888900,22.56570758300,22.56559619400,22.56259591700,22.55323669400,22.55107938900,22.54770075000,22.53799113900,22.54549611100,22.53112069400,22.52082213900,22.50050202800,22.49499911100,22.49033775000,22.47730980600,22.47560969400,22.46622777800,22.42492108300,22.42629447200,22.43117891700,22.43154791700,22.42480638900,22.42343144400,22.42073966700,22.42258055600,22.42112433300,22.39466283300,22.39442725000,22.38673144400,22.38353566700,22.38128172200,22.37994747200,22.37591294400,22.38369830600,22.38499969400,22.38764841700,22.37905613900,22.37336961100,22.36434958300,22.35793569400,22.35028566700,22.34569683300,22.34561975000,22.34266711100,22.35006000000,22.35390861100,22.36222683300,22.36045638900,22.36179511100,22.36013002800,22.35069277800,22.35370158300,22.34557027800,22.34569533300,22.33961169400,22.32152166700,22.30254569400,22.30138136100,22.29080547200,22.28227188900,22.25029477800,22.24966930600,22.24050455600,22.22998608300,22.21570280600,22.19838163900,22.18863819400,22.18702355600,22.18381925000,22.17137891700,22.16097955600,22.15828461100,22.15558258300,22.15315611100,22.15456100000,22.14152933300,22.13769052800,22.14024005600,22.13705841700,22.13828711100,22.14280216700,22.14397350000,22.15243200000,22.16305555600,22.17972222200,22.21333333300,22.22916666700,22.23805555600,22.27777777800,22.28055555600,22.27666666700,22.26944444400,22.25527777800,22.25000000000,22.26444444400,22.27472222200,22.27166666700,22.28250000000,22.30972222200,22.32194444400,22.32722222200,22.32305555600,22.32472222200,22.34583333300,22.34555555600,22.36916666700,22.37472222200,22.38444444400,22.39444444400,22.40361111100,22.41361111100,22.43833333300,22.45444444400,22.46750000000,22.49222222200,22.50222222200,22.50888888900,22.51027777800,22.50777777800,22.52333333300,22.52388888900,22.53388888900,22.55138888900,22.56277777800,22.57500000000,22.58472222200,22.58694444400,22.57222222200,22.58833333300,22.60444444400,22.60027777800,22.60222222200,22.60083333300,22.60555555600,22.60083333300,22.60388888900,22.61527777800,22.62333333300,22.62472222200,22.63138888900,22.65083333300,22.67972222200,22.68777777800,22.69777777800,22.70722222200,22.71777777800,22.73305555600,22.74138888900,22.75555555600,22.77527777800,22.78027777800,22.78111111100,22.81138888900,22.81277777800,22.81027777800,22.81750000000,22.81916666700,22.82222222200,22.83166666700,22.83777777800,22.84000000000,22.84694444400,22.85222222200,22.86305555600,22.87416666700,22.88944444400,22.88833333300,22.88527777800,22.87305555600,22.87222222200,22.89194444400,22.85638888900,22.85138888900,22.85194444400,22.85888888900,22.87250000000,22.88000000000,22.90611111100,22.93222222200,22.94666666700,22.95027777800,22.94138888900,22.93305555600,22.93194444400,22.93888888900,22.95083333300,22.97194444400,22.98250000000,23.01388888900,23.02972222200,23.03805555600,23.05333333300,23.06694444400,23.07916666700,23.09916666700,23.10333333300,23.10194444400,23.11333333300,23.11722222200,23.11333333300,23.12305555600,23.12083333300,23.13833333300,23.13166666700,23.12972222200,23.15777777800,23.16194444400,23.16972222200,23.18666666700,23.19694444400,23.20444444400,23.20111111100,23.20500000000,23.22055555600,23.23583333300,23.25027777800,23.27055555600,23.27722222200,23.27861111100,23.28611111100,23.30000000000,23.29611111100,23.28638888900,23.29027777800,23.30333333300,23.33361111100,23.34194444400,23.34138888900,23.34527777800,23.35694444400,23.40305555600,23.43555555600,23.47916666700,23.49805555600,23.51111111100,23.52111111100,23.53000000000,23.62027777800,23.66833333300,23.76638888900,23.79833333300,23.82361111100,23.84250000000,23.85055555600,23.86305555600,23.87250000000,23.89083333300,23.95416666700,23.97444444400,24.01166666700,24.04277777800,24.07750000000,24.11027777800,24.12722222200,24.14666666700,24.17500000000,24.20138888900,24.21111111100,24.23472222200,24.24250000000,24.27138888900,24.30888888900,24.33194444400,24.36861111100,24.38416666700,24.39805555600,24.40944444400,24.43111111100,24.44750000000,24.47666666700,24.51194444400,24.52833333300,24.57833333300,24.58500000000,24.60777777800,24.63361111100,24.64027777800,24.64361111100,24.67111111100,24.67416666700,24.67777777800,24.68277777800,24.70361111100,24.72000000000,24.72750000000,24.74694444400,24.75888888900,24.78333333300,24.80722222200,24.82305555600,24.83027777800,24.84333333300,24.85944444400,24.87583333300,24.89361111100,24.89638888900,24.89472222200,24.89694444400,24.91000000000,25.00194444400,25.03694444400,25.05583333300,25.09444444400,25.12055555600,25.15472222200,25.16666666700,25.20305555600,25.22888888900,25.23222222200,25.23555555600,25.28000000000,25.40388888900,25.42555555600,25.45694444400,25.48722222200,25.60722222200,25.61472222200,25.62472222200,25.63388888900,25.75138888900,25.78722222200,25.84444444400,25.91500000000,26.02416666700,26.07305555600,26.09222222200,26.11250000000,26.14416666700,26.19972222200,26.22361111100,26.23888888900,26.27250000000,26.28250000000,26.28444444400,26.29916666700,26.30444444400,26.32472222200,26.32750000000,26.32138888900,26.32194444400,26.35277777800,26.35805555600,26.36555555600,26.38416666700,26.38833333300,26.39027777800,26.38861111100,26.39111111100,26.39861111100,26.42527777800,26.43000000000,26.43750000000,26.44194444400,26.43833333300,26.44000000000,26.45527777800,26.46055555600,26.45861111100,26.46166666700,26.47888888900,26.48750000000,26.52027777800,26.52888888900,26.55500000000,26.55777777800,26.56194444400,26.57777777800,26.57388888900,26.57500000000,26.58888888900,26.59388888900,26.60083333300,26.60638888900,26.62305555600,26.62138888900,26.63333333300,26.63916666700,26.64388888900,26.64444444400,26.64750000000,26.65527777800,26.66055555600,26.66527777800,26.66666666700,26.66333333300,26.66388888900,26.66777777800,26.68361111100,26.69111111100,26.69527777800,26.69944444400,26.70444444400,26.70861111100,26.72111111100,26.73166666700,26.72694444400,26.72888888900,26.74277777800,26.73416666700,26.73527777800,26.76555555600,26.78388888900,26.78527777800,26.79750000000,26.80833333300,26.81750000000,26.82638888900,26.83333333300,26.82944444400,26.83222222200,26.84222222200,26.85027777800,26.85611111100,26.86138888900,26.88388888900,26.90861111100,26.90305555600,26.89222222200,26.89333333300,26.90333333300,26.91666666700,26.92055555600,26.91361111100,26.92888888900,26.94305555600,26.95000000000,26.94555555600,26.93277777800,26.93333333300,26.94472222200,26.97138888900,26.98166666700,26.99166666700,26.99166666700,26.98305555600,26.95555555600,26.95138888900,26.95194444400,26.96000000000,26.96833333300,26.98861111100,27.00083333300,27.00638888900,27.01472222200,27.02194444400,27.02833333300,27.02888888900,27.02277777800,27.02388888900,27.02861111100,27.03361111100,27.03888888900,27.03388888900,27.04055555600,27.04055555600,27.02638888900,27.04194444400,27.04666666700,27.07944444400,27.08277777800,27.08250000000,27.08555555600,27.10083333300,27.10611111100,27.10416666700,27.09416666700,27.09111111100,27.08972222200,27.09194444400,27.10194444400,27.10888888900,27.12250000000,27.12805555600,27.12833333300,27.12055555600,27.12333333300,27.13444444400,27.16638888900,27.15861111100,27.15333333300,27.14138888900,27.17833333300,27.15083333300,27.20027777800,27.20888888900,27.23000000000,27.24361111100,27.24750000000,27.24666666700,27.23500000000,27.22250000000,27.21694444400,27.21500000000,27.22277777800,27.23000000000,27.23527777800,27.24166666700,27.24138888900,27.23138888900,27.23166666700,27.24833333300,27.24888888900,27.25416666700,27.25305555600,27.26611111100,27.26805555600,27.26444444400,27.26583333300,27.27972222200,27.28555555600,27.27972222200,27.28750000000,27.29444444400,27.29833333300,27.29805555600,27.28694444400,27.28083333300,27.28500000000,27.29388888900,27.29527777800,27.29250000000,27.28611111100,27.27611111100,27.26777777800,27.26805555600,27.26527777800,27.25972222200,27.25444444400,27.25000000000,27.26638888900,27.26916666700,27.26777777800,27.27194444400,27.28083333300,27.28250000000,27.27888888900,27.27361111100,27.28111111100,27.29583333300,27.29527777800,27.30666666700,27.31527777800,27.31555555600,27.32250000000,27.33361111100,27.36055555600,27.36472222200,27.37361111100,27.37111111100,27.37638888900,27.40444444400,27.42750000000,27.42833333300,27.41777777800,27.41833333300,27.42083333300,27.43222222200,27.42388888900,27.43916666700,27.43694444400,27.43000000000,27.44472222200,27.45611111100,27.45500000000,27.44444444400,27.45083333300,27.45194444400,27.46694444400,27.45555555600,27.45694444400,27.45388888900,27.46777777800,27.46750000000,27.47416666700,27.49416666700,27.49611111100,27.49222222200,27.49305555600,27.50638888900,27.50861111100,27.50750000000,27.51333333300,27.51583333300,27.51250000000,27.51222222200,27.51583333300,27.52222222200,27.53611111100,27.53722222200,27.53166666700,27.53361111100,27.53777777800,27.54027777800,27.54277777800,27.54750000000,27.55638888900,27.55833333300,27.56361111100,27.56916666700,27.57194444400,27.57416666700,27.57000000000,27.55777777800,27.56194444400,27.55444444400,27.55388888900,27.56083333300,27.56777777800,27.57527777800,27.57416666700,27.57611111100,27.58222222200,27.58472222200,27.58305555600,27.56944444400,27.56888888900,27.57277777800,27.56833333300,27.56888888900,27.57194444400,27.57555555600,27.57805555600,27.58388888900,27.58277777800,27.57444444400,27.57583333300,27.58416666700,27.58916666700,27.59583333300,27.60083333300,27.59555555600,27.60555555600,27.60694444400,27.60444444400,27.61055555600,27.61166666700,27.61527777800,27.60138888900,27.58722222200,27.58083333300,27.59416666700,27.59583333300,27.59305555600,27.59833333300,27.60138888900,27.59916666700,27.60527777800,27.61083333300,27.60527777800,27.61666666700,27.62222222200,27.62638888900,27.62777777800,27.63500000000,27.63861111100,27.63333333300,27.64555555600,27.64861111100,27.64638888900,27.64972222200,27.65833333300,27.66416666700,27.66944444400,27.67361111100,27.67666666700,27.67444444400,27.67888888900,27.67944444400,27.68444444400,27.68277777800,27.68416666700,27.68805555600,27.69027777800,27.70555555600,27.70250000000,27.70500000000,27.71388888900,27.71777777800,27.72972222200,27.73805555600,27.73722222200,27.74777777800,27.74472222200,27.75833333300,27.74333333300,27.74250000000,27.74500000000,27.75222222200,27.75694444400,27.75611111100,27.75000000000,27.74611111100,27.74555555600,27.75083333300,27.75916666700,27.75472222200,27.75527777800,27.77444444400,27.77527777800,27.77000000000,27.78583333300,27.78611111100,27.77694444400,27.77888888900,27.79055555600,27.78638888900,27.78694444400,27.79222222200,27.80111111100,27.80388888900,27.79611111100,27.80388888900,27.80944444400,27.81138888900,27.80194444400,27.80194444400,27.79000000000,27.78472222200,27.78555555600,27.79638888900,27.80027777800,27.79944444400,27.78194444400,27.78361111100,27.81500000000,27.82361111100,27.82916666700,27.83000000000,27.83472222200,27.84166666700,27.84833333300,27.85194444400,27.85138888900,27.84555555600,27.84333333300,27.83916666700,27.82666666700,27.83444444400,27.85666666700,27.85500000000,27.85861111100,27.86138888900,27.86444444400,27.87500000000,27.87444444400,27.86750000000,27.87333333300,27.88416666700,27.88000000000,27.89250000000,27.89666666700,27.89805555600,27.90527777800,27.91555555600,27.92361111100,27.93305555600,27.94000000000,27.94583333300,27.95777777800,27.95944444400,27.95777777800,27.94666666700,27.94444444400,27.95083333300,27.96361111100,27.95833333300,27.95916666700,27.97305555600,27.97833333300,27.98388888900,27.98944444400,27.99472222200,27.99500000000,28.01777777800,28.02250000000,28.02666666700,28.03583333300,28.04166666700,28.04833333300,28.05250000000,28.05361111100,28.04250000000,28.03444444400,28.03305555600,28.04000000000,28.04305555600,28.04083333300,28.05138888900,28.05111111100,28.05388888900,28.05555555600,28.05416666700,28.08111111100,28.07805555600,28.09638888900,28.09583333300,28.08527777800,28.08611111100,28.07861111100,28.08305555600,28.09388888900,28.09000000000,28.09861111100,28.09722222200,28.09250000000,28.08888888900,28.09027777800,28.08833333300,28.08305555600,28.08222222200,28.10333333300,28.10583333300,28.09722222200,28.11277777800,28.10305555600,28.09611111100,28.09444444400,28.09555555600,28.08722222200,28.08305555600,28.08861111100,28.08555555600,28.09305555600,28.09694444400,28.10388888900,28.10861111100,28.10972222200,28.11361111100,28.11222222200,28.11805555600,28.10916666700,28.10111111100,28.09861111100,28.11138888900,28.10777777800,28.12250000000,28.11777777800,28.12611111100,28.12388888900,28.11805555600,28.11361111100,28.10972222200,28.10750000000,28.11500000000,28.11444444400,28.11944444400,28.12527777800,28.12361111100,28.13027777800,28.12833333300,28.13250000000,28.15166666700,28.15277777800,28.14916666700,28.15472222200,28.16111111100,28.16277777800,28.16138888900,28.16500000000,28.16611111100,28.17666666700,28.16111111100,28.16500000000,28.17277777800,28.16805555600,28.17111111100,28.17805555600,28.17777777800,28.18527777800,28.18222222200,28.17694444400,28.17333333300,28.17750000000,28.17722222200,28.18388888900,28.18361111100,28.17888888900,28.18416666700,28.19194444400,28.19527777800,28.19583333300,28.18972222200,28.18777777800,28.19361111100,28.19472222200,28.20277777800,28.20194444400,28.20972222200,28.21027777800,28.20277777800,28.21444444400,28.21277777800,28.20805555600,28.20861111100,28.21472222200,28.21611111100,28.22055555600,28.22472222200,28.22333333300,28.22888888900,28.23166666700,28.23027777800,28.23611111100,28.23527777800,28.24000000000,28.23527777800,28.23722222200,28.24583333300,28.23833333300,28.24361111100,28.24444444400,28.23916666700,28.24805555600,28.25138888900,28.24916666700,28.25222222200,28.24416666700,28.25027777800,28.24194444400,28.23833333300,28.24111111100,28.24000000000,28.23138888900,28.24138888900,28.22250000000,28.22750000000,28.22500000000,28.23250000000,28.23555555600,28.22666666700,28.22083333300,28.22250000000,28.21472222200,28.22277777800,28.22361111100,28.22638888900,28.22472222200,28.23000000000,28.22916666700,28.22361111100,28.21444444400,28.21888888900,28.22250000000,28.21500000000,28.20888888900,28.21472222200,28.21083333300,28.21222222200,28.21638888900,28.22138888900,28.22333333300,28.23055555600,28.22861111100,28.23194444400,28.22500000000,28.23416666700,28.24055555600,28.24388888900,28.24638888900,28.24500000000,28.25166666700,28.24527777800,28.25805555600,28.25527777800,28.24000000000,28.24277777800,28.25666666700,28.26111111100,28.25527777800,28.25833333300,28.25083333300,28.24944444400,28.23083333300,28.23000000000,28.23861111100,28.23472222200,28.22666666700,28.22444444400,28.22944444400,28.23750000000,28.24250000000,28.23472222200,28.21694444400,28.21583333300,28.22361111100,28.21750000000,28.22111111100,28.21388888900,28.20888888900,28.20027777800,28.19722222200,28.20666666700,28.20388888900,28.20555555600,28.19916666700,28.20055555600,28.20833333300,28.19805555600,28.19305555600,28.19250000000,28.19083333300,28.19611111100,28.18527777800,28.18805555600,28.18277777800,28.18722222200,28.19361111100,28.19361111100,28.19555555600,28.19944444400,28.19472222200,28.19611111100,28.18805555600,28.18361111100,28.19222222200,28.18666666700,28.19361111100,28.19638888900,28.19861111100,28.20138888900,28.20861111100,28.20555555600,28.19500000000,28.17833333300,28.17916666700,28.18666666700,28.18472222200,28.17916666700,28.18027777800,28.17250000000,28.17694444400,28.17250000000,28.16916666700,28.16972222200,28.16277777800,28.16472222200,28.15694444400,28.15388888900,28.15111111100,28.14916666700,28.15333333300,28.15166666700,28.14416666700,28.14750000000,28.14611111100,28.14000000000,28.13722222200,28.13638888900,28.13416666700,28.13611111100,28.12666666700,28.13055555600,28.14083333300,28.14666666700,28.14027777800,28.13361111100,28.12305555600,28.11916666700,28.11888888900,28.11444444400,28.10972222200,28.11166666700,28.10666666700,28.11222222200,28.10722222200,28.11472222200,28.10972222200,28.11361111100,28.11777777800,28.11777777800,28.12166666700,28.12611111100,28.12361111100,28.11750000000,28.11833333300,28.13333333300,28.13777777800,28.14111111100,28.14027777800,28.13472222200,28.13166666700,28.13111111100,28.13333333300,28.14305555600,28.14333333300,28.13861111100,28.13055555600,28.12833333300,28.14305555600,28.13638888900,28.13305555600,28.12694444400,28.12416666700,28.12388888900,28.12916666700,28.12555555600,28.12833333300,28.13472222200,28.13055555600,28.12527777800,28.12472222200,28.11888888900,28.11666666700,28.11638888900,28.12250000000,28.11666666700,28.11111111100,28.10777777800,28.10222222200,28.10694444400,28.10527777800,28.11166666700,28.10694444400,28.10861111100,28.10111111100,28.09222222200,28.09333333300,28.09027777800,28.09000000000,28.10083333300,28.09805555600,28.08888888900,28.09000000000,28.09361111100,28.10138888900,28.10527777800,28.10055555600,28.10388888900,28.09750000000,28.09055555600,28.08777777800,28.09555555600,28.08555555600,28.09527777800,28.09861111100,28.10527777800,28.09861111100,28.10722222200,28.10666666700,28.10194444400,28.10861111100,28.10555555600,28.11444444400,28.11833333300,28.11472222200,28.12083333300,28.12611111100,28.12083333300,28.12027777800,28.11638888900,28.12027777800,28.11250000000,28.11833333300,28.11305555600,28.11611111100,28.12388888900,28.12750000000,28.13055555600,28.12833333300,28.13277777800,28.12750000000,28.12722222200,28.10583333300,28.11361111100,28.11194444400,28.10583333300,28.11250000000,28.10861111100,28.11138888900,28.10944444400,28.11250000000,28.10750000000,28.11861111100,28.12055555600,28.11944444400,28.12194444400,28.11833333300,28.11444444400,28.11222222200,28.11361111100,28.11944444400,28.13500000000,28.15138888900,28.15555555600,28.15527777800,28.15027777800,28.14805555600,28.14944444400,28.14472222200,28.14333333300,28.15166666700,28.14972222200,28.15083333300,28.15472222200,28.15722222200,28.16638888900,28.16583333300,28.16055555600,28.16638888900,28.16388888900,28.17027777800,28.15944444400,28.16388888900,28.16194444400,28.16611111100,28.17055555600,28.16694444400,28.16250000000,28.16611111100,28.15805555600,28.15972222200,28.17166666700,28.17416666700,28.17194444400,28.15611111100,28.14527777800,28.13805555600,28.13027777800,28.13222222200,28.13055555600,28.12305555600,28.12111111100,28.11444444400,28.11027777800,28.10027777800,28.09027777800,28.08888888900,28.09277777800,28.10027777800,28.10611111100,28.11250000000,28.12111111100,28.11750000000,28.12166666700,28.12527777800,28.12694444400,28.13222222200,28.13222222200,28.13472222200,28.13500000000,28.13916666700,28.14388888900,28.14666666700,28.15666666700,28.15555555600,28.14888888900,28.15916666700,28.15527777800,28.16111111100,28.16527777800,28.16555555600,28.16194444400,28.16611111100,28.16555555600,28.15694444400,28.16666666700,28.16194444400,28.15444444400,28.16416666700,28.16277777800,28.17111111100,28.17361111100,28.17833333300,28.18277777800,28.18527777800,28.19638888900,28.20500000000,28.21055555600,28.25972222200,28.28138888900,28.28916666700,28.29027777800,28.28555555600,28.29305555600,28.34194444400,28.35444444400,28.40361111100,28.54527777800,28.56472222200,28.57333333300,28.63916666700,28.68527777800,28.71861111100,28.73666666700,28.79500000000,28.79527777800,28.77000000000,28.76750000000,28.77277777800,28.80000000000,28.80944444400,28.80833333300,28.79416666700,28.79444444400,28.81388888900,28.82694444400,28.90055555600,28.90472222200,28.93138888900,28.94666666700,28.95722222200,28.95972222200,28.95722222200,28.95833333300,28.96694444400,28.99666666700,29.00694444400,29.05000000000,29.06166666700,29.09055555600,29.11361111100,29.13111111100,29.14944444400,29.17166666700,29.18250000000,29.19750000000,29.22805555600,29.24916666700,29.31361111100,29.32750000000,29.33666666700,29.37138888900,29.39722222200,29.42972222200,29.48722222200,29.56194444400,29.57083333300,29.59861111100,29.65750000000,29.67361111100,29.68055555600,29.66583333300,29.66138888900,29.67500000000,29.66666666700,29.96666666700,30.26666666700,30.40000000000,30.53333333300,30.75000000000,29.87024275800,29.00000000000,28.31666666700,28.03333333300,27.99833333300,27.98694444400,27.98222222200,27.97861111100,27.96027777800,27.95805555600,27.95138888900,27.93861111100,27.93500000000,27.92833333300,27.92111111100,27.91472222200,27.90722222200,27.90861111100,27.90666666700,27.89361111100,27.87277777800,27.86833333300,27.86555555600,27.86611111100,27.86222222200,27.85888888900,27.85805555600,27.85361111100,27.85194444400,27.83611111100,27.82750000000,27.82500000000,27.83000000000,27.82861111100,27.83333333300,27.83861111100,27.84138888900,27.84194444400,27.83972222200,27.83583333300,27.83138888900,27.82833333300,27.82055555600,27.82111111100,27.81861111100,27.81500000000,27.81250000000,27.80861111100,27.79694444400,27.79111111100,27.78722222200,27.78583333300,27.79222222200,27.79000000000,27.78333333300,27.77666666700,27.76694444400,27.75027777800,27.74750000000,27.75305555600,27.75111111100,27.74138888900,27.73472222200,27.72611111100,27.70444444400,27.70361111100,27.70805555600,27.69305555600,27.68777777800,27.68555555600,27.68222222200,27.68027777800,27.67722222200,27.67472222200,27.66527777800,27.66277777800,27.66111111100,27.65416666700,27.64527777800,27.64361111100,27.63611111100,27.62750000000,27.62527777800,27.62583333300,27.63388888900,27.61944444400,27.61388888900,27.61333333300,27.60777777800,27.59194444400,27.57944444400,27.57972222200,27.57194444400,27.57972222200,27.58027777800,27.56888888900,27.57694444400,27.57916666700,27.57583333300,27.56305555600,27.54638888900,27.53166666700,27.51861111100,27.51472222200,27.49888888900,27.48972222200,27.46861111100,27.44916666700,27.44361111100,27.43916666700,27.43500000000,27.42277777800,27.41722222200,27.40000000000,27.39222222200,27.38138888900,27.36888888900,27.34305555600,27.34222222200,27.33305555600,27.31277777800,27.30166666700,27.28833333300,27.27444444400,27.26500000000,27.25027777800,27.23138888900,27.22277777800,27.20888888900,27.20972222200,27.21277777800,27.20972222200,27.20333333300,27.18694444400,27.17222222200,27.14944444400,27.14083333300,27.12611111100,27.11666666700,27.10583333300,27.08222222200,27.05583333300,27.03388888900,27.03416666700,27.02861111100,27.01611111100,27.00444444400,26.99055555600,26.98583333300,26.98583333300,26.97916666700,26.97138888900,26.94638888900,26.92222222200,26.90444444400,26.87083333300,26.85694444400,26.84916666700,26.84388888900,26.81527777800,26.80500000000,26.79444444400,26.77111111100,26.76000000000,26.74916666700,26.73277777800,26.72277777800,26.71000000000,26.68694444400,26.67111111100,26.65027777800,26.63333333300,26.61666666700,26.62083333300,26.60194444400,26.58083333300,26.57027777800,26.57194444400,26.58694444400,26.57305555600,26.58166666700,26.56805555600,26.55555555600,26.54861111100,26.54361111100,26.53500000000,26.52527777800,26.38138888900,26.37500000000,26.34527777800,26.33666666700,26.33833333300,26.36194444400,26.38500000000,26.41250000000,26.44388888900,26.47388888900,26.49694444400,26.49944444400,26.50861111100,26.51888888900,26.53638888900,26.55111111100,26.58611111100,26.59611111100,26.60250000000,26.59416666700,26.60527777800,26.59777777800,26.59944444400,26.60611111100,26.61000000000,26.60500000000,26.61583333300,26.62000000000,26.61722222200,26.61888888900,26.63388888900,26.64166666700,26.63694444400,26.62666666700,26.61333333300,26.59222222200,26.58277777800,26.57222222200,26.56416666700,26.55722222200,26.54000000000,26.52861111100,26.52166666700,26.50750000000,26.50250000000,26.49583333300,26.47250000000,26.46833333300,26.44500000000,26.42250000000,26.41583333300,26.40722222200,26.36277777800,26.34305555600,26.33250000000,26.32916666700,26.32583333300,26.32722222200,26.33694444400,26.32611111100,26.32361111100,26.32861111100,26.31500000000,26.31166666700,26.31888888900,26.33694444400,26.33750000000,26.32472222200,26.32694444400,26.31694444400,26.31083333300,26.31694444400,26.32694444400,26.33388888900,26.33805555600,26.33361111100,26.31805555600,26.31777777800,26.33250000000,26.33138888900,26.33305555600,26.34388888900,26.35055555600,26.36277777800,26.36833333300,26.35833333300,26.34638888900,26.33861111100,26.33000000000,26.32833333300,26.33083333300,26.35722222200,26.35972222200,26.35777777800,26.32666666700,26.31527777800,26.30972222200,26.29527777800,26.28972222200,26.29000000000,26.29583333300,26.29750000000,26.30138888900,26.30138888900,26.29027777800,26.28333333300,26.27361111100,26.26472222200,26.25583333300,26.25416666700,26.24972222200,26.24055555600,26.22833333300,26.22305555600,26.22833333300,26.22611111100,26.21472222200,26.20916666700,26.21638888900,26.20666666700,26.21083333300,26.21944444400,26.22305555600,26.21611111100,26.21166666700,26.20750000000,26.19444444400,26.16944444400,26.16555555600,26.15916666700,26.15888888900,26.15500000000,26.13555555600,26.13194444400,26.13277777800,26.12500000000,26.10027777800,26.06416666700,26.04444444400,26.04111111100,25.87500000000,25.90000000000,25.66666666700,25.60000000000,25.70000000000,25.70000000000,26.00000000000,26.41666666700,26.78333333300,26.31666666700,26.35000000000,26.18333333300,26.20000000000,26.23333333300,26.50000000000,26.93333333300,27.15000000000,27.10000000000,26.98333333300,26.98333333300,27.05000000000,27.18333333300,27.10000000000,27.25000000000,27.43333333300,27.43333333300,27.23333333300,27.45000000000,27.85000000000,27.93333333300,27.96666666700,28.30000000000,28.88333333300,29.25000000000,29.38333333300,29.58333333300,29.73333333300,30.00000000000,30.85316502400,31.52807790600,32.20247099600,32.87628081800,33.54944444400,35.66638888900,35.48333333300,35.60000000000,35.70000000000,35.63333333300,35.71666666700,35.59676666700,35.52516218800,35.45330611900,35.38166070800,35.31068673800,35.24084032900,35.17256977900,35.10631248100,35.04249192800,34.98693038300,34.93401073200,34.88400975200,34.83568473000,34.79240248700,34.75151694300,34.71587393500,34.68329147200,34.64949411900,34.62271181200,34.60315261200,34.59096290400,34.58622673500,34.58896569500,34.59913933000,34.61720445200,34.64206899900,34.67387963500,34.71236015100,34.75844325200,34.80937778200,34.86739314000,34.92903390900,34.99700555600,34.95000000000,34.71666666700,34.60833333300,34.54333333300,34.54950555600,34.48510223000,34.42126682200,34.36039312900,34.30286952900,34.24906150100,34.19930925100,34.15392554900,34.11319378700,34.06967349000,34.03329199400,34.00552891200,33.98664489200,33.97680894000,33.97609759900,33.98449510100,34.00189444400,33.00133967700,32.01016028200,31.00973121700,30.00000000000,29.28734130400,28.57253185300,27.85562352100,27.16666666700,24.16666666700,23.58333333300,11.50000000000,11.50000000000,10.63846347200,9.76799068700,8.88852032500,8.00000000000,4.66666666700,4.21093348700,3.75000000000,3.12724381900,2.50839205500,1.89344221100,1.22703239700,0.62022348500,-0.03732433400,-0.63603168000,-1.28477020000,-1.50000000000,-2.10000000000,-7.38333333300,-7.38333333300,-12.00000000000,-12.32889093400,-12.65418613700,-12.97597554900,-13.32072631200,-13.63549147900,-13.94701481700,-14.30646999700,-14.64498799000,-14.68694909700,-14.73649472700,-14.79055913300,-14.84788369400,-14.90834320900,-14.97180669300,-15.03813765000,-15.10719437100,-15.17883021400,-15.26165645100,-15.34729109700,-15.43551116900,-15.52608799400,-15.61878774800,-15.71337197900,-15.80962674700,-15.90729128900,-16.00610339600,-16.10581118500,-16.20616085000,-16.30689721100,-16.40566325700,-16.50640994000,-16.60678033400,-16.70651921400,-16.80537271000,-16.90308884900,-16.99941810300,-17.09411393400,-17.18693333700,-17.27763737700,-17.36599172900,-17.45001040800,-17.53304956000,-17.61307310300,-17.68987027300,-17.76323754000,-17.83297911700,-17.89890746300,-17.96084377900,-18.01745839800,-18.08890301000,-18.15115550000,-18.20583387300,-18.25097164400,-18.28772855300,-18.31476798500,-18.33256343900,-18.34099508000,-18.33998638100,-18.32950515900,-18.30956443500,-18.28022308500,-18.24158627900,-18.19462162800,-18.13803337400,-18.07382527100,-18.02646758300,-17.97682628000,-17.92257792400,-17.86640826200,-17.78475770500,-17.49807782900,-16.87148780100,-16.26468095100,-15.62229480400,-15.00000000000,-15.00000000000,-14.48995782200,-13.99721517500,-13.50057267700,-13.00000000000,-13.00000000000,-8.00000000000,-8.00000000000,-15.00000000000,-15.00000000000,-14.35806384800,-13.76321040400,-13.11638112000,-12.51716567400,-11.86578348500,-11.26252903400,-10.60695328800,-10.00000000000,-10.00000000000,0.00000000000,0.00000000000,4.00000000000,4.27702576800,4.54930144000,4.82677598700,5.10948552400,5.39746251300,5.67698407300,5.97616422700,6.26666666700,6.84055555600,7.00000000000,7.74560391700,8.16650002600,8.57665473900,8.99524134100,9.42250000000,9.88066884400,10.28986319900,10.76726825700,11.19376727300,11.69150509500,12.13629486700,12.58997293500,13.05277129300,13.52492745500,14.00668442500,14.49829066000,15.00000000000,16.15606007900,17.29513171300,18.41344647900,19.61826193500,20.84295390200,21.99752390200,23.25904437300,24.44672540500,25.00000000000,28.00000000000,30.00000000000,30.43937233700,30.87185834800,31.29758215900,31.71666666700,31.13333333300,30.81743611100,30.82386388900,30.84097500000,30.84052500000]

if Graph.FIRCONUS:
    Graph.latFIRCONUS=[46,47,48,46,46,44,47,50,50,40,33,32,31,31,29,29,26,25,28,29,29,25,25,31,35,37,40,41,43,44,46]
    Graph.lonFIRCONUS=[-67,-67,-69,-71,-75,-79,-83,-92,-125,-125,-120,-115,-111,-106,-104,-101,-99,-97,-96,-93,-84,-82,-79,-81,-75,-75,-73,-69,-70,-66,-67]
if Graph.FIRAlaska:
    Graph.latFIRAlaska=[56,60,60,61,70,72,69,68,67,66,64,64,62,61,60,59,60,59,58,58,57,54,52,55,57,56,59,59,60,59,55,54,54,56]
    Graph.lonFIRAlaska=[-130,-135,-138,-141,-141,-157,-167,-167,-165,-169,-167,-163,-167,-166,-168,-166,-165,-163,-161,-158,-159,-169,-169,-159,-156,-154,-150,-147,-146,-140,-134,-132,-130,-130]
if Graph.FIRCanada:
    Graph.latFIRCanada=[70,60,59,59,56,55,55,53,48,49,49,46,43,45,45,47,47,46,43,47,46,48,54,56,61,67,71,75,75,71,70]
    Graph.lonFIRCanada=[-142,-142,-137,-135,-131,-131,-134,-133,-125,-124,-92,-83,-79,-75,-71,-69,-68,-68,-66,-57,-53,-52,-56,-60,-64,-61,-68,-80,-125,-127,-142]
if Graph.FIRMexico:
    Graph.latFIRMexico=[32,32,30,30,27,26,21,19,19,20,22,22,17,17,17,16,15,14,15,16,15,16,26,33,33,32]
    Graph.lonFIRMexico=[-111,-106,-104,-101,-99,-97,-97,-95,-92,-91,-91,-86,-87,-88,-90,-90,-92,-92,-93,-95,-96,-100,-115,-118,-114,-111]


#Make plot
MakeGraph()
