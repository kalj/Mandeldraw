/*
 * @(#)log.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-15 18:55:03 CET>
 *
 *   
 */

#ifndef _LOG_H
#define _LOG_H

#include <cstdio>

#ifdef DEBUG
#define DBGLOG(FORMAT, ARGS...) fprintf(stderr,FORMAT,ARGS)

#else
#define DBGLOG(FORMAT, ARGS...)

#endif

extern bool VERBOSE;
extern bool WARNINGS;

#define INFOLOG(FORMAT, ARGS...) if (VERBOSE) fprintf(stderr,FORMAT,ARGS)

#define WARNLOG(FORMAT, ARGS...)if (WARNINGS) fprintf(stderr,"Warning: "); \
    if (WARNINGS) fprintf(stderr, FORMAT, ARGS)



#endif /* _LOG_H */

