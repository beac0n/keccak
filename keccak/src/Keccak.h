/*
 * keccak.h
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#ifndef KECCAK_H_
#define KECCAK_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "constants.h"

struct paddedInput {
	uint8_t* paddedInput;
	size_t length;
};

class Keccak {
public:
	Keccak();
	virtual ~Keccak();

	uint8_t* keccak(const uint8_t* input, int inputLength);
protected:
	uint64_t state[sizeOfState];

	const uint64_t roundConstants[rounds] = {
			0x0000000000000001, 0x0000000000008082,	0x800000000000808a,
			0x8000000080008000, 0x000000000000808b,	0x0000000080000001,
			0x8000000080008081, 0x8000000000008009,	0x000000000000008a,
			0x0000000000000088, 0x0000000080008009,	0x000000008000000a,
			0x000000008000808b, 0x800000000000008b,	0x8000000000008089,
			0x8000000000008003, 0x8000000000008002,	0x8000000000000080,
			0x000000000000800a, 0x800000008000000a,	0x8000000080008081,
			0x8000000000008080, 0x0000000080000001,	0x8000000080008008
	};

	const int cyclicShiftOffsets[sizeOfState] = {
			0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43,
			25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14
	};

	int coordinate(int x, int y);
	uint64_t rotate(uint64_t x, int y);
	void theta();
	void rhoPiChi();
	void iota(int round);
	virtual void keccakf();
	void absorb(paddedInput paddedInput);
	paddedInput padd(const uint8_t* input, size_t inputLength);
	uint8_t* squeez();
};

#endif /* KECCAK_H_ */
