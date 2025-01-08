#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T13:49:49
#
#-------------------------------------------------
#This file is part of gLAB's GUI.
#
#    gLAB's GUI is free software: you can redistribute it and/or modify
#    it under the terms of the Lesser GNU General Public License as published by
#    the Free Software Foundation, either version 3.
#
#    gLAB's GUI is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    Lesser GNU General Public License for more details.
#
#    You should have received a copy of the Lesser GNU General Public License
#    along with gLAB's GUI.  If not, see <http://www.gnu.org/licenses/>.
#

QT       += core gui network
CONFIG   += g++11
CONFIG   += c++11
CONFIG   += resources_big #This flag is to avoid memory allocation error in 32-bit g++ compiler when compiling myresources.qrc

#QMAKE_CXXFLAGS_RELEASE += -O3       # Release -O3 (no use)

win32 {
 QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread
}
macx: ICON = gLAB.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

linux-arm-gnueabihf-g++ {
    TARGET = gLAB_GUI_ARMv7
} else:contains(QT_ARCH, arm64) {
    TARGET = gLAB_GUI_ARM64
#} else:linux-g++{
#    contains(QT_ARCH, x86_64){
#        TARGET = gLAB_GUI_64
#    } else {
#        TARGET = gLAB_GUI
#    }
} else {
    TARGET = gLAB_GUI
}
TEMPLATE = app

win32: RC_FILE = gLAB.rc

SOURCES += main.cpp \
    antenna_advanced.cpp \
    cs_igf_advanced.cpp \
    cs_li_advanced.cpp \
    cs_mw_advanced.cpp \
    cs_sf_advanced.cpp \
    freqmeas_order.cpp \
    glab_gui.cpp \
    glab_tooltip.cpp \
    input.cpp \
    meas_select.cpp \
    multi_threading.cpp \
    preprocess.cpp \
    modelling.cpp \
    filter.cpp \
    output.cpp \
    analysis.cpp \
    converter.cpp \
    compareOrbits.cpp \
    sbas_obad_set.cpp \
    showOrbits.cpp \
    coord_converter.cpp \
    date_converter.cpp \
    adderror_rinex.cpp \
    snr_advanced.cpp \
    load_positioning.cpp

HEADERS  += \
    antenna_advanced.h \
    cs_igf_advanced.h \
    cs_li_advanced.h \
    cs_mw_advanced.h \
    cs_sf_advanced.h \
    freqmeas_order.h \
    glab_const.h \
    glab_gui.h \
    coord_converter.h \
    date_converter.h \
    glab_tooltip.h \
    meas_select.h \
    multi_threading.h \
    sbas_obad_set.h \
    snr_advanced.h \

FORMS    += \
    antenna_advanced.ui \
    cs_igf_advanced.ui \
    cs_li_advanced.ui \
    cs_mw_advanced.ui \
    cs_sf_advanced.ui \
    freqmeas_order.ui \
    glab_gui.ui \
    coord_converter.ui \
    date_converter.ui \
    glab_tooltip.ui \
    meas_select.ui \
    multi_threading.ui \
    sbas_obad_set.ui \
    snr_advanced.ui \

RESOURCES += \
    myresources.qrc
