//
//  BiTAmeriCall.cpp
//  Part5_ObserverPattern
//

#include "BiTAmeriCall.h"
#include <sstream>

BiTAmeriCall::BiTAmeriCall(ArgumentList& args)
    : TreeObservable("BiTAmeriCa")
{
    Spot = args.GetDoubleArgumentValue("spot");
    Strike = args.GetDoubleArgumentValue("strike");
    Vol = args.GetDoubleArgumentValue("vol");
    r = args.GetDoubleArgumentValue("r");
    d = args.GetDoubleArgumentValue("d");
    Expiry = args.GetDoubleArgumentValue("expiry");
    Steps = args.GetULArgumentValue("steps");
}

double BiTAmeriCall::Price() const
{
    PayOffCall thePayOff(Strike);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    TreeAmerican TreeAmerCall(Expiry, thePayOff);
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);
    
    double price = CRRTree.GetThePrice(TreeAmerCall);
    
    // notify observers with the price
    std::ostringstream message;
    message << "American Call priced at " << price;
    const_cast<BiTAmeriCall*>(this)->sendMessage(message.str());
    
    return price;
}