//
//  BiTAmeriPut.cpp
//  Part5_ObserverPattern
//

#include "BiTAmeriPut.h"
#include <sstream>

BiTAmeriPut::BiTAmeriPut(ArgumentList& args)
    : TreeObservable("BiTAmeriPu")
{
    Spot = args.GetDoubleArgumentValue("spot");
    Strike = args.GetDoubleArgumentValue("strike");
    Vol = args.GetDoubleArgumentValue("vol");
    r = args.GetDoubleArgumentValue("r");
    d = args.GetDoubleArgumentValue("d");
    Expiry = args.GetDoubleArgumentValue("expiry");
    Steps = args.GetULArgumentValue("steps");
}

double BiTAmeriPut::Price() const
{
    PayOffPut thePayOff(Strike);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    TreeAmerican TreeAmerPut(Expiry, thePayOff);
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);
    
    double price = CRRTree.GetThePrice(TreeAmerPut);
    
    // notify observers with the price
    std::ostringstream message;
    message << "American Put priced at " << price;
    const_cast<BiTAmeriPut*>(this)->sendMessage(message.str());
    
    return price;
}