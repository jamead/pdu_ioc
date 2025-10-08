# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS

TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = PDU
# PDU.dbd will be created and installed
DBD += PDU.dbd

# PDU.dbd will be made up from these files:
PDU_DBD += base.dbd

# Include dbd files from all support applications:
#PDU_DBD += xxx.dbd
PDU_DBD += PDUsubs.dbd

# Add all the support libraries needed by this IOC
#PDU_LIBS += xxx

# PDU_registerRecordDeviceDriver.cpp derives from PDU.dbd
PDU_SRCS += PDU_registerRecordDeviceDriver.cpp
PDU_SRCS += ChanSub.c
PDU_SRCS += StatusSub.c
PDU_SRCS += ChanStatus.c

# Build the main IOC entry point on workstation OSs.
PDU_SRCS_DEFAULT += PDUMain.cpp
PDU_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#PDU_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
PDU_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

