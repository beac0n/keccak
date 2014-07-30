/*
 * KeccakPppprocessingEarlyParity.cpp
 *
 *  Created on: 30.07.2014
 *      Author: beac0n
 */

#include "KeccakPppprocessingEarlyParity.h"

KeccakPppprocessingEarlyParity::KeccakPppprocessingEarlyParity() {
	// TODO Auto-generated constructor stub

}

KeccakPppprocessingEarlyParity::~KeccakPppprocessingEarlyParity() {
	// TODO Auto-generated destructor stub
}

void KeccakPppprocessingEarlyParity::keccakf() {
	uint64_t A[sizeOfState];
	uint64_t E[sizeOfState];

	uint64_t B[5];
	uint64_t C[5];
	uint64_t D[5];

	memcpy(A, state, sizeOfState * 8);

	for (int x = 0; x < 5; ++x) {
		C[x] =	A[coordinate(x, 0)] ^
				A[coordinate(x, 1)] ^
				A[coordinate(x, 2)] ^
				A[coordinate(x, 3)] ^
				A[coordinate(x, 4)];
	}

	for (int round = 0; round < rounds; ++round) {

		for (int x = 0; x < 5; ++x) {
			D[x] = C[(x + 4) % 5] ^ rotate(C[(x + 1) % 5], 1);
		}

		memset(C, 0, 5*8);

		for (int y = 0; y < 5; ++y) {

			int curIndex;
			int curIndexX;

			for (int x = 0; x < 5; ++x) {
				curIndex = newIndizies[Keccak::coordinate(x, y)];
				curIndexX = newIndiziesX[Keccak::coordinate(x, y)];

				B[x] = Keccak::rotate((A[curIndex] ^ D[curIndexX]),
						cyclicShiftOffsets[curIndex]);
			}

			for (int x = 0; x < 5; ++x) {
				curIndex = Keccak::coordinate(x, y);
				E[curIndex] = B[x] ^ ((~B[(x + 1) % 5]) & B[(x + 2) % 5]);
				C[x] ^= E[curIndex];
			}
		}

		E[0] ^= roundConstants[round];

		memcpy(A, E, sizeOfState * 8);
	}

	memcpy(state, E, sizeOfState * 8);
}
