/*
 * KeccakPppprocessingEarlyParity.cpp
 *
 *  Created on: 28.07.2014
 *      Author: beac0n
 */

#include "KeccakPppprocessingEfficientInplace.h"

KeccakPppprocessingEfficientInplace::KeccakPppprocessingEfficientInplace() {
}

KeccakPppprocessingEfficientInplace::~KeccakPppprocessingEfficientInplace() {
}

void KeccakPppprocessingEfficientInplace::keccakf() {
	uint64_t B[5];
	uint64_t C[5];
	uint64_t D[5];

	for (int round = 0; round < rounds; ++round) {

		for (int x = 0; x < 5; ++x) {
			C[x] =	state[N[round % 4][coordinate(x, 0)]] ^
					state[N[round % 4][coordinate(x, 1)]] ^
					state[N[round % 4][coordinate(x, 2)]] ^
					state[N[round % 4][coordinate(x, 3)]] ^
					state[N[round % 4][coordinate(x, 4)]];
		}

		for (int x = 0; x < 5; ++x) {
			D[x] = C[(x + 4) % 5] ^ rotate(C[(x + 1) % 5], 1);
		}

		for (int y = 0; y < 5; ++y) {
			int curIndex;
			for (int x = 0; x < 5; ++x) {
				curIndex = Keccak::coordinate(x, y);

				B[(x+2*y)%5] =
						Keccak::rotate(
								(state[N[(round+1)%4][curIndex]] ^ D[x]),
								cyclicShiftOffsets[N[0][curIndex]]
								                   );
			}

			for (int x = 0; x < 5; ++x) {
				curIndex = Keccak::coordinate(x, y);
				state[N[(round+1)%4][curIndex]] = B[x] ^ ((~B[(x + 1) % 5]) & B[(x + 2) % 5]);
			}
		}

		state[0] ^= roundConstants[round];
	}
}

