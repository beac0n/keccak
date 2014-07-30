/*
 * main.cpp
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#include <stdint.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Keccak.h"
#include "KeccakPppprocessing.h"
#include "KeccakPppprocessingEarlyParity.h"
#include "KeccakPppprocessingEfficientInplace.h"

/*
int coordinate(int x, int y, int i) {

        int N[4][4] = { { 1, 0, 1, 2 }, { 1, 0, 3, 4 }, { 1, 0, 2, 3 },
                        { 1, 0, 0, 1 } };

        int xt = (N[i][0] * x + N[i][1] * y) % 5;
        int yt = (N[i][2] * x + N[i][3] * y) % 5;

        return 5 * yt + xt;
}

        for (int i = 0; i < 4; ++i) {

                std::cout << "i=" << i << ": ";
                for (int y = 0; y < 5; ++y) {
                        for (int x = 0; x < 5; ++x) {
                                std::cout << coordinate(x, y, i) << ", ";
                        }
                }

                std::cout << std::endl;
        } 
 */

int main() {

    const char* testString = "Keccak-256 Test Hash";
    int size = strlen(testString);
    uint8_t expectedOutput[32] = {0xA8, 0xD7, 0x1B, 0x07, 0xF4, 0xAF, 0x26,
        0xA4, 0xFF, 0x21, 0x02, 0x7F, 0x62, 0xFF, 0x60, 0x26, 0x7F, 0xF9,
        0x55, 0xC9, 0x63, 0xF0, 0x42, 0xC4, 0x6D, 0xA5, 0x2E, 0xE3, 0xCF,
        0xAF, 0x3D, 0x3C};

    Keccak* keccak = new KeccakPppprocessingEarlyParity();
    uint8_t * actualOutput = keccak->keccak((uint8_t *) testString, size);
    bool fail = memcmp(expectedOutput, actualOutput, 32);

    if (!fail) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "fail" << std::endl;
    }

    for (int i = 0; i < 32; ++i) {
        std::cout << std::hex << (int) *(actualOutput + i) << " ";
    }
    std::cout << std::endl;
    delete[] (actualOutput);

    return 0;
}

