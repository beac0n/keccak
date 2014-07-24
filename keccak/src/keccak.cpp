//============================================================================
// Name        : keccak.cpp
// Author      : Maximilian Schempp
//============================================================================

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

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


int coordinate(int x, int y) {
	return (x%5)+5*(y%5);
}

uint64_t rotate(uint64_t x, int y) {
	return ((x) << (y)) | ((x) >> ((64) - (y)));
}

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

void theta() {
	uint64_t C[5] = {0,0,0,0,0};
	uint64_t D[5] = {0,0,0,0,0};

	for(int i = 0; i < 5; ++i) {
		C[i] =	state[coordinate(i, 0)] ^ state[coordinate(i, 1)] ^
				state[coordinate(i, 2)] ^ state[coordinate(i, 3)] ^
				state[coordinate(i, 4)];
	}

	for(int i = 0; i < 5; ++i) {
		D[i] = C[(i+4)%5] ^ rotate(C[(i+1)%5], 1);
	}

	for(int i = 0; i < sizeOfState; ++i) {
		state[i] ^= D[i%5];
	}
}

uint64_t* rhoPi() {
	uint64_t* B = new uint64_t [sizeOfState];
	memset(B, 0, sizeOfState);

	for(int x = 0; x < 5; ++x) {
		for(int y = 0; y < 5; ++y) {
			B[coordinate(y,(2*x+3*y))] = rotate(state[coordinate(x,y)], cyclicShiftOffsets[coordinate(x,y)]);
		}
	}

	return B;
}

void chi(uint64_t* B) {
	for(int x = 0; x < 5; ++x) {
		for(int y = 0; y < 5; ++y) {
			state[coordinate(x,y)] = B[coordinate(x,y)] ^
					((~B[coordinate(x+1,y)]) & B[coordinate(x+2, y)]);
		}
	}
}

void iota(int round) {
	state[0] ^= roundConstants[round];
}

void keccakf() {
	for(int i = 0; i < rounds; ++i) {
		theta();
		uint64_t* B = rhoPi();
		chi(B);
		iota(i);
	}
}

void absorb(paddedInput paddedInput) {
	for(size_t i = 0; i < paddedInput.length; i += bitrate) {
		for(int j = 0; j < blockLength; ++j) {
			state[j] ^= *((uint64_t*) (paddedInput.paddedInput+i+(j*8)));
		}

		keccakf();

	}
}

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

uint8_t* squeez() {
	uint64_t* Z = new uint64_t [blockLength];

	for(int i = 0; i < blockLength; ++i) {
		Z[i] = state[i];
	}

	uint8_t* returnValue = new uint8_t [outputLength];
	memcpy(returnValue, Z, outputLength);

	delete(Z);

	return returnValue;
}

uint8_t* keccak(const uint8_t* input, int inputLength) {
	// padding
	paddedInput paddedInput = padd(input, inputLength);

	// initialization
	memset(state, 0, sizeOfState);

	//absorbing phase
	absorb(paddedInput);

	delete(paddedInput.paddedInput);

	// squeesing phase
	return squeez();
}

int main() {
	const char* test = "Keccak-256 Test Hash";
	int size = strlen(test);

	uint8_t* retVal = keccak((uint8_t *)test,size);

	size = strlen((char*)retVal);
	for(int i = 0; i < size; ++i) {
		std::cout << std::uppercase << std::hex << int(retVal[i]) << " ";
	}

	return 0;
}


