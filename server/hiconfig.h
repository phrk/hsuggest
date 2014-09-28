/* 
 * File:   config.h
 * Author: phrk
 *
 * Created on February 18, 2014, 10:36 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <cstdio>

#ifdef __linux__

	#define __STDC_LIMIT_MACROS
	#include <stdint.h>
	#include <string.h>
	//#define NO_STD_TR1

#else

	#define NO_STD_TR1

#endif

//#define PUNKT_TARGETER_COOKIE_ONLY
#define PUNKT_TARGETER_HASHD

#define POOLSERVER_SOCKET_CONN_QUEUE_SIZE 2048

#endif	/* CONFIG_H */

