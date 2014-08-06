/*
 * KeccakPpppEficcientInplaceEarlyParity.h
 *
 *  Created on: 28.07.2014
 *      Author: Maximilian Schempp
 */

#ifndef KECCAKPPPPEFICCIENTINPLACEEARLYPARITY_H
#define	KECCAKPPPPEFICCIENTINPLACEEARLYPARITY_H

#include "KeccakPppprocessingEfficientInplace.h"

class KeccakPpppEficcientInplaceEarlyParity : public KeccakPppprocessingEfficientInplace {
public:
    KeccakPpppEficcientInplaceEarlyParity();
    virtual ~KeccakPpppEficcientInplaceEarlyParity();
protected:
    void keccakf();

};

#endif	/* KECCAKPPPPEFICCIENTINPLACEEARLYPARITY_H */

