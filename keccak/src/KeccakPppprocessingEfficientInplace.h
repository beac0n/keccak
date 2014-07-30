/*
 * KeccakPppprocessingEarlyParity.h
 *
 *  Created on: 28.07.2014
 *      Author: beac0n
 */

#ifndef KeccakPppprocessingEfficientInplace_H_
#define KeccakPppprocessingEfficientInplace_H_

#include "KeccakPppprocessing.h"

class KeccakPppprocessingEfficientInplace: public KeccakPppprocessing {
public:
	KeccakPppprocessingEfficientInplace();
	virtual ~KeccakPppprocessingEfficientInplace();
protected:
	void keccakf();

	int N[4][25] = {
			{ 0, 6, 12, 18, 24, 10, 16, 22, 3, 9, 20, 1, 7, 13, 19, 5, 11, 17, 23, 4, 15, 21, 2, 8, 14 },
			{ 0, 16, 7, 23, 14, 20, 11, 2, 18, 9, 15, 6, 22, 13, 4, 10, 1, 17, 8, 24, 5, 21, 12, 3, 19 },
			{ 0, 11, 22, 8, 19, 15, 1, 12, 23, 9, 5, 16, 2, 13, 24, 20, 6, 17, 3, 14, 10, 21, 7, 18, 4 },
			{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 }
	};

};

#endif /* KeccakPppprocessingEfficientInplace_H_ */
