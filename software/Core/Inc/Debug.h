/*
 * Debug.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#define DEBUG 1
#if DEBUG
	#define Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define Debug(__info,...)
#endif


#endif /* INC_DEBUG_H_ */
