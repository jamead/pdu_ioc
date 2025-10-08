#!../../bin/linux-x86_64/PDU

#- SPDX-FileCopyrightText: 2005 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change PDU to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase "../../dbd/PDU.dbd"
PDU_registerRecordDeviceDriver(pdbbase) 

## Load record instances
#dbLoadRecords("../../db/PDU.db","user=Diag")
dbLoadRecords("../../db/Channel.db","P=PDU:","user=diag")
dbLoadRecords("../../db/Status.db","P=PDU:","user=diag")

iocInit()

## Start any sequence programs
#seq sncPDU,"user=Diag"

dbpf PDU:IP:Settings-SP 10.4.24.105:5000

