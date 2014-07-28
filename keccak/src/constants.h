/*
 * constants.h
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#ifndef width
#define width 200
#endif

#ifndef capacity
#define capacity 64
#endif

#ifndef bitrate
#define bitrate (width-capacity)
#endif

#ifndef outputLength
#define outputLength (capacity/2)
#endif

#ifndef laneLength
#define laneLength 8
#endif

#ifndef blockLength
#define blockLength (bitrate/laneLength)
#endif

#ifndef rounds
#define rounds 24
#endif

#ifndef sizeOfState
#define sizeOfState 25
#endif

#endif /* CONSTANTS_H_ */
