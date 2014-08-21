/*
 * KeccakOptimized.cpp
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#include "KeccakPppprocessing.h"
#include <stdint.h>

KeccakPppprocessing::KeccakPppprocessing() :
Keccak() {
}

KeccakPppprocessing::~KeccakPppprocessing() {
}

void KeccakPppprocessing::keccakf() {
    uint64_t A[sizeOfState];
    uint64_t B[5];
    uint64_t C[5];
    uint64_t D[5];

    for (int round = 0; round < rounds; ++round) {
        memcpy(A, state, sizeOfState * 8);

        for (int x = 0; x < 5; ++x) {
            C[x] = A[coordinate(x, 0)] ^
                    A[coordinate(x, 1)] ^
                    A[coordinate(x, 2)] ^
                    A[coordinate(x, 3)] ^
                    A[coordinate(x, 4)];
        }

        for (int x = 0; x < 5; ++x) {
            D[x] = C[(x + 4) % 5] ^ rotate(C[(x + 1) % 5], 1);
        }

        for (int y = 0; y < 5; ++y) {

            int curIndex;
            int curIndexX;

            for (int x = 0; x < 5; ++x) {
                curIndex = newIndizies[coordinate(x, y)];
                curIndexX = newIndiziesX[coordinate(x, y)];

                B[x] = rotate((A[curIndex] ^ D[curIndexX]), cyclicShiftOffsets[curIndex]);
            }

            for (int x = 0; x < 5; ++x) {
                curIndex = coordinate(x, y);
                state[curIndex] = B[x] ^ ((~B[(x + 1) % 5]) & B[(x + 2) % 5]);
            }
        }

        state[0] ^= roundConstants[round];
    }
}