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
#include "KeccakPpppEficcientInplaceEarlyParity.h"

#ifndef outputSize
#define outputSize 32
#endif

bool testKeccakImplementation(Keccak* keccak, char* keccakAlgorithm, const char* testString, uint8_t expectedOutput[outputSize]) {
    int size = strlen(testString);
    uint8_t* actualOutputKeccak = keccak->keccak((uint8_t*) testString, size);

    std::cout << "Testing " << keccakAlgorithm << " - ";
    bool fail = memcmp(expectedOutput, actualOutputKeccak, outputSize);
    std::cout <<  (fail ? "Fail" : "Success") << std::endl;
    std::cout << "Output: ";
    for (int i = 0; i < 32; ++i) {
        if (!(i % 8)) std::cout << std::endl;
        std::cout << "0x" << std::uppercase << std::hex << (int) *(actualOutputKeccak + i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    delete[] (actualOutputKeccak);
    
    return fail;
}

void testAllKeccakImplementation(const char* testString, uint8_t expectedOutput[outputSize]) {
    int size = strlen(testString);
    Keccak* keccak = new Keccak();
    Keccak* keccakPppprocessing = new KeccakPppprocessing();
    Keccak* keccakPppprocessingEarlyParity = new KeccakPppprocessingEarlyParity();
    Keccak* keccakPppprocessingEfficientInplace = new KeccakPppprocessingEfficientInplace();
    Keccak* keccakPpppEficcientInplaceEarlyParity = new KeccakPpppEficcientInplaceEarlyParity();

    bool succK = !testKeccakImplementation(keccak,
            "Reference Implementation", testString, expectedOutput);
    bool succPppp = !testKeccakImplementation(keccakPppprocessing,
            "Plane-Per-Plane Processing", testString, expectedOutput);
    bool succPpppEp = !testKeccakImplementation(keccakPppprocessingEarlyParity,
            "Plane-Per-Plane Processing with early parity", testString, expectedOutput);
    bool succPpppEi = !testKeccakImplementation(keccakPppprocessingEfficientInplace,
            "Plane-Per-Plane Processing with efficient in-place implementation", testString, expectedOutput);
    bool succPpppEiEp = !testKeccakImplementation(keccakPpppEficcientInplaceEarlyParity,
            "Plane-Per-Plane Processing with efficient in-place implementation and early parity", testString, expectedOutput);
    
    std::cout <<  ((succK && succPppp && succPpppEp && succPpppEi && succPpppEiEp) ? "OVERALL SUCCESS" : "Fail") << std::endl;

    delete (keccak);
    delete (keccakPppprocessing);
    delete (keccakPppprocessingEarlyParity);
    delete (keccakPppprocessingEfficientInplace);
    delete (keccakPpppEficcientInplaceEarlyParity);
}

int main() {
    char* testString = "Keccak-256 Test Hash";
    uint8_t expectedOutput[32] = {
        0xA8, 0xD7, 0x1B, 0x07, 0xF4, 0xAF, 0x26, 0xA4,
        0xFF, 0x21, 0x02, 0x7F, 0x62, 0xFF, 0x60, 0x26,
        0x7F, 0xF9, 0x55, 0xC9, 0x63, 0xF0, 0x42, 0xC4,
        0x6D, 0xA5, 0x2E, 0xE3, 0xCF, 0xAF, 0x3D, 0x3C
    };

    testAllKeccakImplementation(testString, expectedOutput);

    return 0;
}

