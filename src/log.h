/*
 * @(#)log.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-07 12:39:16 CET>
 *
 *   
 */

#ifndef _LOG_H
#define _LOG_H

#ifdef NDEBUG
#define LOG(FORMAT, ARGS...)
#else
#include <cstdio>
#define LOG(FORMAT, ARGS...) fprintf(stderr,FORMAT,ARGS)
#endif

#endif /* _LOG_H */

