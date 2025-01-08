Complete the following steps to compile the software 


PREVIOUS: 

a) For x86_64, all programs are precompiled, no package installation necessary.

   For ARMv7, ARMv8 or for compiling the core and running the plotting tool directly with python:

   - Install "make" and "gcc" to compile the core

     sudo apt-get install make gcc

   - Install Python 3 packages to run the plotting tool with python:

     sudo apt-get install python3-matplotlib python3-tk python3-numpy

   - For SBAS maps and WIR maps, the following packages are also needed:

     sudo apt-get install python3-mpltoolkits.basemap python-mpltoolkits.basemap-data


     NOTE: for Python 2 (not supported anymore), the packages are the following

     sudo apt-get install python python-matplotlib python-tk python-mpltoolkits.basemap python-mpltoolkits.basemap-data python-numpy
b) For ARMv7 and ARMv8 (for x86_64 already compiled): compile the program by executing:
     
      make -j2
      make -f Makefile_multithread -j2

c) Executing gLAB

   - Graphic user Interface

     ./gLAB_GUI (x86_64)

     ./gLAB_GUI_ARMv7 (ARMv7)

     ./gLAB_GUI_ARM64 (ARMv8 or aarch64)


   - Command line mode

     ./gLAB_linux


   - Plotting module

     ./graph/graph (x86_64)

     ./graph.py (ARMv7 and ARMv8)

