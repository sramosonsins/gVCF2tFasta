#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=bin
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sources/CFai.o \
	${OBJECTDIR}/sources/CFasta.o \
	${OBJECTDIR}/sources/CStringTools.o \
	${OBJECTDIR}/sources/CTFasta.o \
	${OBJECTDIR}/sources/CVCF.o \
	${OBJECTDIR}/sources/File.o \
	${OBJECTDIR}/sources/main.o \
	${OBJECTDIR}/sources/zindex.o \
	${OBJECTDIR}/sources/zutil.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lz -I/usr/local/include
CXXFLAGS=-lz -I/usr/local/include

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/gVCF2tFasta

${CND_DISTDIR}/gVCF2tFasta: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}
	${LINK.cc} -o ${CND_DISTDIR}/gVCF2tFasta ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/sources/CFai.o: sources/CFai.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/CFai.o sources/CFai.cpp

${OBJECTDIR}/sources/CFasta.o: sources/CFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/CFasta.o sources/CFasta.cpp

${OBJECTDIR}/sources/CStringTools.o: sources/CStringTools.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/CStringTools.o sources/CStringTools.cpp

${OBJECTDIR}/sources/CTFasta.o: sources/CTFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/CTFasta.o sources/CTFasta.cpp

${OBJECTDIR}/sources/CVCF.o: sources/CVCF.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/CVCF.o sources/CVCF.cpp

${OBJECTDIR}/sources/File.o: sources/File.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/File.o sources/File.cpp

${OBJECTDIR}/sources/main.o: sources/main.cpp
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/main.o sources/main.cpp

${OBJECTDIR}/sources/zindex.o: sources/zindex.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/zindex.o sources/zindex.c

${OBJECTDIR}/sources/zutil.o: sources/zutil.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/zutil.o sources/zutil.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
