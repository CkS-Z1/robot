#ifndef __diary_h__
#define __diary_h__

#include "global.h"


void finitialize_diary();
void fstart_diary(Incidentcode *incidentcode, struct tm *starttime);
void fend_diary(Incidentcode *incidentcode, struct tm *endtime);
void fget_time();
void fsave_time();


#endif