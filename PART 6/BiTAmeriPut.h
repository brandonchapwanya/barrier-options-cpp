//
//  BiTAmeriPut.h
//  Part5_ObserverPattern
//

#ifndef BiTAmeriPut_h
#define BiTAmeriPut_h

#include "ArgList.h"
#include "TreeObservable.h"
#include "CRRBinomialTree.h"
#include "TreeAmerican.h"
#include "PayOff3.h"
#include "PayOffBridge.h"
#include "Parameters.h"

class BiTAmeriPut : public TreeObservable
{
public:
    BiTAmeriPut(ArgumentList& args);
    
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

#endif /* BiTAmeriPut_h */