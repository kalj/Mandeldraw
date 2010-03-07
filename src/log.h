/*
 * @(#)log.h
 * @author Karl Ljungkvist
 * Last changed: <2010-03-07 22:21:55 CET>
 *
 *   
 */

#ifndef _LOG_H
#define _LOG_H

#ifdef DEBUG
#include <cstdio>
#define LOG(FORMAT, ARGS...) fprintf(stderr,FORMAT,ARGS)

#else
#define LOG(FORMAT, ARGS...)

#endif

#endif /* _LOG_H */

