/*
 * Keccak.cpp
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */
#include "Keccak.h"

Keccak::Keccak() {
}

Keccak::~Keccak() {
}

int Keccak::coordinate(int x, int y) {
	return (x % 5) + 5 * (y % 5);
}

uint64_t Keccak::rotate(uint64_t x, int y) {
	return (x << y) | (x >> (laneLength * 8 - y));
}

void Keccak::theta() {
	uint64_t C[5];
	uint64_t D[5];

	for (int i = 0; i < 5; ++i) {
		C[i] = state[coordinate(i, 0)] ^ state[coordinate(i, 1)]
				^ state[coordinate(i, 2)] ^ state[coordinate(i, 3)]
				^ state[coordinate(i, 4)];
	}

	for (int i = 0; i < 5; ++i) {
		// originally it would be C[(i-1)%5], but since
		// (-1)%5 == -1 and not 4, we need to write C[(i+4)%5]
		D[i] = C[(i + 4) % 5] ^ rotate(C[(i + 1) % 5], 1);
	}

	for (int i = 0; i < sizeOfState; ++i) {
		state[i] ^= D[i % 5];
	}
}

void Keccak::rhoPiChi() {
	// rhoPi
	uint64_t B[sizeOfState];

	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			B[coordinate(y, (2 * x + 3 * y))] = rotate(state[coordinate(x, y)],
					cyclicShiftOffsets[coordinate(x, y)]);
		}
	}

	// chi
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			state[coordinate(x, y)] = B[coordinate(x, y)]
					^ ((~B[coordinate(x + 1, y)]) & B[coordinate(x + 2, y)]);
		}
	}
}

void Keccak::iota(int round) {
	state[0] ^= roundConstants[round];
}

void Keccak::keccakf() {
	for (int i = 0; i < rounds; ++i) {
		theta();
		rhoPiChi();
		iota(i);
	}
}

void Keccak::absorb(paddedInput paddedInput) {
	// iterate over the whole input with bitrate-block steps
	for (size_t i = 0; i < paddedInput.length; i += bitrate) {
		// iterate over each bitrate-block
		for (int j = 0; j < blockLength; ++j) {
			// since the paddedInput is in 8bit form and
			// the state is in 64 bit form, the steps need
			// to be multiplied with 8
			state[j] ^= *((uint64_t*) (paddedInput.paddedInput + i + (j * 8)));
		}

		keccakf();
	}
}

paddedInput Keccak::padd(const uint8_t* input, size_t inputLength) {
	// calculate how many blocks of bitrate length
	// fit in the input
	size_t blockCount = inputLength / bitrate;
	// since there must be at least one block => add 1
	size_t newSizeByte = (blockCount + 1) * bitrate;

	uint8_t* returnValue = new uint8_t[newSizeByte];
	memset(returnValue, 0, newSizeByte);
	memcpy(returnValue, input, inputLength);

	// set the first byte after the input
	*(returnValue + inputLength) = 0x01;
	// set the last byte of the padded input
	*(returnValue + (newSizeByte - 1)) = 0x80;

	struct paddedInput returnStruct;
	returnStruct.paddedInput = returnValue;
	returnStruct.length = newSizeByte;

	return returnStruct;
}

uint8_t* Keccak::squeez() {
	// since there is enough output after the first
	// loop cycle, there is no need for a loop
	uint8_t* returnValue = new uint8_t[outputLength];
	memcpy(returnValue, state, outputLength);
	return returnValue;
}

uint8_t* Keccak::keccak(const uint8_t* input, int inputLength) {
	// padding
	paddedInput paddedInput = padd(input, inputLength);

	// initialization
	memset(state, 0, sizeOfState*8);

	//absorbing phase
	absorb(paddedInput);

	// padded input is no longer needed
	delete[] (paddedInput.paddedInput);

	// squeezing phase
	return squeez();
}
