//
//  BiTEuroBarrierCall.cpp
//  Part5_ObserverPattern
//

#include "BiTEuroBarrierCall.h"
#include <sstream>

BiTEuroBarrierCall::BiTEuroBarrierCall(ArgumentList& args)
    : TreeObservable("BiTEuroBaC")
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

double BiTEuroBarrierCall::Price() const
{
    PayOffCall thePayOff(Strike);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    TreeEuropeanBarrier TreeBarrierCall(Expiry, thePayOff, Barrier);
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);
    
    double price = CRRTree.GetThePrice(TreeBarrierCall);
    
    // notify observers with the price
    std::ostringstream message;
    message << "Barrier Call priced at " << price;
    const_cast<BiTEuroBarrierCall*>(this)->sendMessage(message.str());
    
    return price;
}