/*
 * KeccakOptimized.cpp
 *
 *  Created on: 28.07.2014
 *      Author: beac0n
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
    uint64_t E[sizeOfState];    
    
    memcpy(E, state, sizeOfState * 8);
    
    uint64_t B[5];
    uint64_t C[5];
    uint64_t D[5];

    for (int round = 0; round < rounds; ++round) {        
        memcpy(A, E, sizeOfState * 8);
        
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
                E[curIndex] = B[x] ^ ((~B[(x + 1) % 5]) & B[(x + 2) % 5]);
            }
        }

        E[0] ^= roundConstants[round];        
    }

    memcpy(state, E, sizeOfState * 8);

    /* Alogithms used to calculate newIndizies and newIndiziesX:

     int calculate(int x, int y) { // newIndizies

             double xt = (double) x;
             double yt = (double) y;

             int temp = ((-1.5 * xt + 0.5 * yt) + 10) * 6;
             double newX = temp % 5;
             double newY = xt;

             return 5 * newY + newX;
     }

     int calculateX(int x, int y) { // newIndiziesX
             double xt = (double) x;
             double yt = (double) y;

             int temp = ((-1.5 * xt + 0.5 * yt) + 10) * 6;

             return temp % 5;
     }
     */
}

