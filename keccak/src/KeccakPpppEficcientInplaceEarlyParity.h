/* 
 * File:   KeccakPpppEficcientInplaceEarlyParity.h
 * Author: beac0n
 *
 * Created on 31. Juli 2014, 14:59
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

