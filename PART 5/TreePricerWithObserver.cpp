//
//  TreePricerWithObserver.cpp
//  Part5_ObserverPattern
//

#include "TreePricerWithObserver.h"
#include "TreeObservable.h"
#include "CRRBinomialTree.h"
#include "TrinomialTree.h"
#include <sstream>

TreePricerWithObserver::TreePricerWithObserver(const pTreeObservable& obs,
                                               double Spot_,
                                               const Parameters& r_,
                                               const Parameters& d_,
                                               double Vol_,
                                               unsigned long Steps_,
                                               double Time_)
    : observable(obs), Spot(Spot_), r(r_), d(d_),
      Vol(Vol_), Steps(Steps_), Time(Time_)
{
}

double TreePricerWithObserver::price(const TreeProducts& product, const std::string& productName)
{
    CRRBinomialTree crrTree(Spot, r, d, Vol, Steps, Time);
    BoyleTrinomialTree triTree(Spot, r, d, Vol, Steps, Time);
    
    double crrPrice = crrTree.GetThePrice(product);
    double triPrice = triTree.GetThePrice(product);
    
    // send message with pricing results
    std::ostringstream message;
    message << productName << " - CRR: " << crrPrice << ", Trinomial: " << triPrice;
    observable->sendMessage(message.str());
    
    return crrPrice;
}