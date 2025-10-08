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

static int ChanStatus(aSubRecord *precord) {
    int Ch1status,Ch2status,Ch3status,Ch4status;
    int i;

    Ch1status = *(int *)precord->a;
    Ch2status = *(int *)precord->b;
    Ch3status = *(int *)precord->c;
    Ch4status = *(int *)precord->d;

    *(int *)precord->vala = Ch1status&1;
    *(int *)precord->valb = (Ch1status&2)/2;
    *(int *)precord->valc = (Ch1status&4)/4;
    *(int *)precord->vald = (Ch1status&8)/8;
    *(int *)precord->vale = (Ch1status&16)/16;

    *(int *)precord->valf = Ch2status&1;
    *(int *)precord->valg = (Ch2status&2)/2;
    *(int *)precord->valh = (Ch2status&4)/4;
    *(int *)precord->vali = (Ch2status&8)/8;
    *(int *)precord->valj = (Ch2status&16)/16;

    *(int *)precord->valk = Ch3status&1;
    *(int *)precord->vall = (Ch3status&2)/2;
    *(int *)precord->valm = (Ch3status&4)/4;
    *(int *)precord->valn = (Ch3status&8)/8;
    *(int *)precord->valo = (Ch3status&16)/16;

    *(int *)precord->valp = Ch4status&1;
    *(int *)precord->valq = (Ch4status&2)/2;
    *(int *)precord->valr = (Ch4status&4)/4;
    *(int *)precord->vals = (Ch4status&8)/8;
    *(int *)precord->valt = (Ch4status&16)/16;

    return(0);
}
// Note the function must be registered at the end!
epicsRegisterFunction(ChanStatus);
