//============================================================================
// Name        : keccak.cpp
// Author      : Maximilian Schempp
//============================================================================

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#ifndef width
#define width 200
#endif

#ifndef rounds
#define rounds 24 // this could be calculated
#endif

#ifndef capacity
#define capacity 64
#endif

#ifndef bitrate
#define bitrate (width-capacity)
#endif

#ifndef outputLength
#define outputLength (capacity/2)
#endif

#ifndef laneLength
#define laneLength 8
#endif

#ifndef blockLength
#define blockLength (bitrate/laneLength)
#endif

#ifndef sizeOfState
#define sizeOfState 25
#endif

#ifndef rotate
#define rotate(x, y) (((x) << (y)) | ((x) >> (64 - (y))))
#endif

#ifndef coordinate
#define coordinate(x, y) (x+5*y)
#endif

uint64_t state[25];

const uint64_t roundConstants[24] =
{
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

const int cyclicShiftOffsets[25] =
{
	0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43,
	25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14
};

struct paddedInput {
	uint8_t* paddedInput;
	size_t length;
};

paddedInput padd(const uint8_t* input, size_t inputLength) {
	size_t blockCount = inputLength / bitrate;
	size_t newSizeByte = (blockCount + 1) * bitrate;

	uint8_t* returnValue = new uint8_t [newSizeByte];
	memset(returnValue, 0, newSizeByte);
	memcpy(returnValue, input, inputLength);

	*(returnValue+inputLength) = 0x01;
	*(returnValue+(newSizeByte-1)) = 0x80;

	struct paddedInput returnStruct;
	returnStruct.paddedInput = returnValue;
	returnStruct.length = newSizeByte;

	return returnStruct;
}

void keccakf() {

}

void absorb(paddedInput paddedInput) {
	for(int i = 0; i < paddedInput.length; i += bitrate) {
		for(int j = 0; j < blockLength; ++j) {
			state[j] ^= *((uint64_t*) (paddedInput.paddedInput+i+(j*8)));
		}
	}
}

uint8_t* squeez() {
	uint64_t* Z = new uint64_t [blockLength];

	for(int i = 0; i < blockLength; ++i) {
		Z[i] = state[i];
	}

	uint8_t* returnValue = new uint8_t [outputLength];
	memcpy(returnValue, Z, outputLength);

	return returnValue;
}

uint8_t* keccak(const uint8_t* input, int inputLength) {
	// padding
	paddedInput paddedInput = padd(input, inputLength);

	// initialization
	memset(state, 0, sizeOfState);

	//absorbing phase
	absorb(paddedInput);

	// squeesing phase
	return squeez();
}

int main() {
	const char* test = "this is a test";
	int size = 14;

	std::cout << rounds << std::endl;

	keccak((uint8_t *)test,size);

	return 0;
}


