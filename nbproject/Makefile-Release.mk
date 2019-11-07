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
CND_SOURCES=sources

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CFai.o \
	${OBJECTDIR}/CFasta.o \
	${OBJECTDIR}/CStringTools.o \
	${OBJECTDIR}/CTFasta.o \
	${OBJECTDIR}/CVCF.o \
	${OBJECTDIR}/File.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/zindex.o \
	${OBJECTDIR}/zutil.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x -lz -I/usr/local/include
CXXFLAGS=-std=c++0x -lz -I/usr/local/include

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
	${LINK.cc} -o ${CND_DISTDIR}/gVCF2tFasta ${OBJECTFILES} ${LDLIBSOPTIONS} -lz

${OBJECTDIR}/CFai.o: ${CND_SOURCES}/CFai.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CFai.o ${CND_SOURCES}/CFai.cpp -I/usr/local/include

${OBJECTDIR}/CFasta.o: ${CND_SOURCES}/CFasta.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CFasta.o ${CND_SOURCES}/CFasta.cpp -I/usr/local/include

${OBJECTDIR}/CStringTools.o: ${CND_SOURCES}/CStringTools.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CStringTools.o ${CND_SOURCES}/CStringTools.cpp -I/usr/local/include

${OBJECTDIR}/CTFasta.o: ${CND_SOURCES}/CTFasta.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CTFasta.o ${CND_SOURCES}/CTFasta.cpp -I/usr/local/include

${OBJECTDIR}/CVCF.o: ${CND_SOURCES}/CVCF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CVCF.o ${CND_SOURCES}/CVCF.cpp -I/usr/local/include

${OBJECTDIR}/File.o: ${CND_SOURCES}/File.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/File.o ${CND_SOURCES}/File.cpp -I/usr/local/include

${OBJECTDIR}/main.o: ${CND_SOURCES}/main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o ${CND_SOURCES}/main.cpp -I/usr/local/include

${OBJECTDIR}/zindex.o: ${CND_SOURCES}/zindex.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/zindex.o ${CND_SOURCES}/zindex.c -I/usr/local/include

${OBJECTDIR}/zutil.o: ${CND_SOURCES}/zutil.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/zutil.o ${CND_SOURCES}/zutil.c -I/usr/local/include

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/gVCF2tFasta

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
