#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

static int StatusSub(aSubRecord *precord) {
    float *status;
    int i;

    status = (float *)precord->a;
    *(int *)precord->vala = (int)(status[0]);
    *(float *)precord->valb = status[1];
    *(float *)precord->valc = status[2];
    *(float *)precord->vald = status[3];
    *(int *)precord->vale = (int)(status[4]);
    *(int *)precord->valf = (int)(status[5]);
    *(int *)precord->valg = (int)(status[6]);
    *(int *)precord->valh = (int)(status[7]);
    *(float *)precord->vali = status[10];
    *(float *)precord->valj = status[11];
    *(int *)precord->valk = (int)(status[12]);
    *(int *)precord->vall = (int)(status[13]);
    *(int *)precord->valm = (int)(status[14]);
    *(int *)precord->valn = (int)(status[18]);
    *(int *)precord->valo = (int)(status[19]);

    return(0);
}
// Note the function must be registered at the end!
epicsRegisterFunction(StatusSub);
