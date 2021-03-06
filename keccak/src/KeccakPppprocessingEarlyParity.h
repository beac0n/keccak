/*
 * KeccakPppprocessingEarlyParity.h
 *
 *  Created on: 30.07.2014
 *      Author: Maximilian Schempp
 */

#ifndef KECCAKPPPPROCESSINGEARLYPARITY_H_
#define KECCAKPPPPROCESSINGEARLYPARITY_H_

#include "KeccakPppprocessing.h"

class KeccakPppprocessingEarlyParity : public KeccakPppprocessing  {
public:
	KeccakPppprocessingEarlyParity();
	virtual ~KeccakPppprocessingEarlyParity();
protected:
	void keccakf();

};

#endif /* KECCAKPPPPROCESSINGEARLYPARITY_H_ */
