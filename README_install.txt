Complete the following steps to compile the software 


a) PREVIOUS: 

   The following packages are required: Python, gcc 

   These packages can be installed in UBUNTU as follows:

   - Installing Python (this is necessary for gLAB GUI and for graph.py):

     sudo apt-get install python python-matplotlib python-tk python-mpltoolkits.basemap python-mpltoolkits.basemap-data python-numpy

   - Additional packages for Python3 (in case user wants to execute graph.py in Python3):

     sudo apt-get install python3-matplotlib python3-tk python3-mpltoolkits.basemap python-mpltoolkits.basemap-data python3-numpy

   - Installing C compiler (gcc)

     sudo apt-get install gcc

   - (Optional) For running 32-bit gLAB's GUI in a 64 bit Linux, the following packages are necessary:

     sudo dpkg --add-architecture i386
     sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386 libgl1-mesa-glx:i386 libgl1-mesa-dri:i386 libxi6:i386 libfontconfig:i386 libxrender1:i386


b) Compile the program by executing:
     
      make

c) Executing gLAB

   - Graphic user Interface

     ./gLAB_GUI


   - Command line mode

     ./gLAB_linux


   - Plotting module

     ./graph.py
