//
//  BiTEuroBarrierPut.h
//  Part5_ObserverPattern
//

#ifndef BiTEuroBarrierPut_h
#define BiTEuroBarrierPut_h

#include "ArgList.h"
#include "TreeObservable.h"
#include "CRRBinomialTree.h"
#include "TreeEuropeanBarrier.h"
#include "PayOff3.h"
#include "PayOffBridge.h"
#include "Parameters.h"

class BiTEuroBarrierPut : public TreeObservable
{
public:
    BiTEuroBarrierPut(ArgumentList& args);
    
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

#endif /* BiTEuroBarrierPut_h */