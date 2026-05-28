//
//  BiTEuroBarrierPut.cpp
//  Part5_ObserverPattern
//

#include "BiTEuroBarrierPut.h"
#include <sstream>

BiTEuroBarrierPut::BiTEuroBarrierPut(ArgumentList& args)
    : TreeObservable("BiTEuroBaP")
{
    Spot = args.GetDoubleArgumentValue("spot");
    Strike = args.GetDoubleArgumentValue("strike");
    Barrier = args.GetDoubleArgumentValue("barrier");
    Vol = args.GetDoubleArgumentValue("vol");
    r = args.GetDoubleArgumentValue("r");
    d = args.GetDoubleArgumentValue("d");
    Expiry = args.GetDoubleArgumentValue("expiry");
    Steps = args.GetULArgumentValue("steps");
}

double BiTEuroBarrierPut::Price() const
{
    PayOffPut thePayOff(Strike);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    TreeEuropeanBarrier TreeBarrierPut(Expiry, thePayOff, Barrier);
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);
    
    double price = CRRTree.GetThePrice(TreeBarrierPut);
    
    // notify observers with the price
    std::ostringstream message;
    message << "Barrier Put priced at " << price;
    const_cast<BiTEuroBarrierPut*>(this)->sendMessage(message.str());
    
    return price;
}