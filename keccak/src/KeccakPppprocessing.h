/*
 * KeccakOptimized.h
 *
 *  Created on: 28.07.2014
 *      Author: beac0n
 */

#ifndef KECCAKOPTIMIZED_H_
#define KECCAKOPTIMIZED_H_

#include "Keccak.h"

class KeccakPppprocessing: public Keccak {
public:
	KeccakPppprocessing();
	virtual ~KeccakPppprocessing();
protected:

	const int newIndizies[25] =
	{
			0, 6, 12, 18, 24, 3, 9, 10, 16, 22, 1, 7, 13,
			19, 20, 4, 5, 11, 17, 23, 2, 8, 14, 15, 21
	};

	const int newIndiziesX[25] =
	{
			0, 1, 2, 3, 4, 3, 4, 0, 1, 2, 1, 2, 3, 4, 0,
			4, 0, 1, 2, 3, 2, 3, 4, 0, 1
	};

	virtual void keccakf();

};

#endif /* KECCAKOPTIMIZED_H_ */
