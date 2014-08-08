/*
 * KeccakPppprocessingEarlyParity.cpp
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#include "KeccakPppprocessingEfficientInplace.h"

KeccakPppprocessingEfficientInplace::KeccakPppprocessingEfficientInplace() {
}

KeccakPppprocessingEfficientInplace::~KeccakPppprocessingEfficientInplace() {
}

/* Algorithmen zur berechnung der neuene Koordinaten

int coordinate(int x, int y, int i) {

    int N[4][4] = {
        { 1, 0, 0, 1},
        { 1, 0, 1, 2},
        { 1, 0, 3, 4},
        { 1, 0, 2, 3}
    };

    int xt = (N[i][0] * x + N[i][1] * y) % 5;
    int yt = (N[i][2] * x + N[i][3] * y) % 5;

    return 5 * yt + xt;
}

void printNewCoordinates() {
    for (int i = 0; i < 4; ++i) {

        std::cout << "i=" << i << ": ";
        for (int y = 0; y < 5; ++y) {
            for (int x = 0; x < 5; ++x) {
                std::cout << coordinate(x, y, i) << ", ";
            }
        }

        std::cout << std::endl;
    }
}  
*/

void KeccakPppprocessingEfficientInplace::keccakf() {
    uint64_t B[5];
    uint64_t C[5];
    uint64_t D[5];

    for (int round = 0; round < rounds; ++round) {

        for (int x = 0; x < 5; ++x) {
            C[x] = state[N[ROUNDS][coordinate(x, 0)]] ^
                    state[N[ROUNDS][coordinate(x, 1)]] ^
                    state[N[ROUNDS][coordinate(x, 2)]] ^
                    state[N[ROUNDS][coordinate(x, 3)]] ^
                    state[N[ROUNDS][coordinate(x, 4)]];
        }

        for (int x = 0; x < 5; ++x) {
            D[x] = C[(x + 4) % 5] ^ rotate(C[(x + 1) % 5], 1);
        }

        for (int y = 0; y < 5; ++y) {

            int curIndex;

            for (int x = 0; x < 5; ++x) {
                curIndex = coordinate(x, y);
                B[(x + 2 * y) % 5] = rotate(
                        (state[N[(round + 1) % 4][curIndex]] ^ D[x]),
                        cyclicShiftOffsets[N[1][curIndex]]
                        );
            }

            for (int x = 0; x < 5; ++x) {
                curIndex = coordinate(x, y);
                state[N[(round + 1) % 4][curIndex]] = B[x] ^ ((~B[(x + 1) % 5]) & B[(x + 2) % 5]);
            }
        }

        state[0] ^= roundConstants[round];
    }
}

