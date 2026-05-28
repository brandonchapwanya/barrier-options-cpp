//
//  TreePricerWithObserver.h
//  Part5_ObserverPattern
//

#ifndef TreePricerWithObserver_h
#define TreePricerWithObserver_h

#include <boost/shared_ptr.hpp>
#include <string>
#include "Parameters.h"
#include "TreeProducts.h"

class TreeObservable;

typedef boost::shared_ptr<TreeObservable> pTreeObservable;

class TreePricerWithObserver
{
public:
    TreePricerWithObserver(const pTreeObservable& observable,
                           double Spot,
                           const Parameters& r,
                           const Parameters& d,
                           double Vol,
                           unsigned long Steps,
                           double Time);
    
    double price(const TreeProducts& product, const std::string& productName);

private:
    pTreeObservable observable;
    double Spot;
    Parameters r;
    Parameters d;
    double Vol;
    unsigned long Steps;
    double Time;
};

#endif /* TreePricerWithObserver_h */