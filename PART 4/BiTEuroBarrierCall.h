//
//  BiTEuroBarrierCall.h
//  Part4_FactoryRegistration
//

#ifndef BiTEuroBarrierCall_h
#define BiTEuroBarrierCall_h

#include "ArgList.h"
#include "CRRBinomialTree.h"
#include "TreeEuropeanBarrier.h"
#include "PayOff3.h"
#include "PayOffBridge.h"
#include "Parameters.h"

class BiTEuroBarrierCall
{
public:
    BiTEuroBarrierCall(ArgumentList& args);
    
    double Price() const;

private:
    double Spot;
    double Strike;
    double Barrier;
    double Vol;
    double r;
    double d;
    double Expiry;
    unsigned long Steps;
};

#endif /* BiTEuroBarrierCall_h */