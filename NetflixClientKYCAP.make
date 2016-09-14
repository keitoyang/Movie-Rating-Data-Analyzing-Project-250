#  Makefile: Editing of Tim Budd's "Makefile" by Bina Ramamurthy and 
#  Ken Regan, Fall 1996, and again by KWR in Spring 2000.
#  Tailored for LinkMain.make by KWR for CSE250, Fall 2009.
#
#  USAGE---enter at command prompt in directory:  make -f LinkMain.make


# Unix Macros---choose which compiler and options here!

 CC     = g++      #optional change to: g++ -Wall
# CC     = g++ -fhandle-exceptions -frtti
# CC     = CC     # name of the Sun C++ compiler---NOT available on timberlake
                  # if you have a command-line installation at home (as
                  # opposed to an IDE like Eclipse), put your compiler here.
#CC = gfilt

LIBS   = -lm
OBJ    = .o
RM     = rm -fr


# SYNTAX: Dependencies must be on same line as ":".  Actions must
# follow on succeeding line(s), and have at least one TAB indent.
# Hence, be careful mouse-copying makefile text if tabs convert to spaces.

all:	NetflixClientKYCAP

# Invoke this via "make -f LinkMain.make clean".  No "-" before "clean"!
clean:
	$(RM) *$(OBJ)    # ISR/*$(OBJ)---etc. for any subdirectories

# Below I hard-coded ".o" in place of the variable "$(OBJ)" to save room.

movieBaseKY.o: movieBaseKY.cpp movieBaseKY.h  #lives in base directory
	$(CC) -c movieBaseKY.cpp

userBaseCAP.o: userBaseCAP.cpp userBaseCAP.h
	$(CC) -c userBaseCAP.cpp

# LinkTemplate.o: LinkTemplate.cpp LinkTemplate.h   ## NO! with g++

NetflixClientKYCAP.o: NetflixClientKYCAP.cpp movieBaseKY.h userBaseCAP.h
	$(CC) -c NetflixClientKYCAP.cpp

NetflixClientKYCAP: NetflixClientKYCAP.o movieBaseKY.o userBaseCAP.o
	$(CC) -o NetflixClientKYCAP NetflixClientKYCAP.o movieBaseKY.o userBaseCAP.o  $(LIBS)

# The .o file with main should come before all the other object files in the
# final linking stage.
