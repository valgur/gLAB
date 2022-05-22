CC = gcc
CXXFLAGS += -O3 -fno-stack-protector
#CXXFLAGS += -pedantic
#CXXFLAGS += -Wall
CXXFLAGS += -std=gnu99
#CXXFLAGS += -Wno-unknown-pragmas
#CXXFLAGS += -fopenmp

# gLAB installation directory:
ppwwdd = `pwd`

all: gLAB

gLAB: gLAB.c dataHandling.c filter.c input.c model.c preprocessing.c output.c
	 ${CC} ${CXXFLAGS} -o gLAB_linux gLAB.c dataHandling.c filter.c input.c model.c preprocessing.c output.c -lm

