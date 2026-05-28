//
//  BiTAmeriCall.h
//  Part5_ObserverPattern
//

#ifndef BiTAmeriCall_h
#define BiTAmeriCall_h

#include "ArgList.h"
#include "TreeObservable.h"
#include "CRRBinomialTree.h"
#include "TreeAmerican.h"
#include "PayOff3.h"
#include "PayOffBridge.h"
#include "Parameters.h"

class BiTAmeriCall : public TreeObservable
{
public:
    BiTAmeriCall(ArgumentList& args);
    
    double Price() const;

private:
    double Spot;
    double Strike;
    double Vol;
    double r;
    double d;
    double Expiry;
    unsigned long Steps;
};

#endif /* BiTAmeriCall_h */