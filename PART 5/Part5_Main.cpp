//
//  Part5_Main.cpp
//  Part5_ObserverPattern
//

/*
requires
    Arrays.cpp
    CRRBinomialTree.cpp
    TrinomialTree.cpp
    BlackScholesFormulas.cpp
    Normals.cpp
    Parameters.cpp
    PayOff3.cpp
    PayOffBridge.cpp
    TreeAmerican.cpp
    TreeEuropeanBarrier.cpp
    TreeProducts.cpp
    TreeObservable.cpp
    OptionPricingReportWriter.cpp
    TreePricerWithObserver.cpp
*/

#include "TreeObservable.h"
#include "OptionPricingReportWriter.h"
#include "TreePricerWithObserver.h"
#include "TreeAmerican.h"
#include "TreeEuropeanBarrier.h"
#include "Parameters.h"
#include "PayOff3.h"
#include "PayOffBridge.h"
#include <iostream>

using namespace std;

int main()
{
    double Expiry = 1.0;
    double Strike = 50.0;
    double Spot = 50.0;
    double Vol = 0.30;
    double r = 0.05;
    double d = 0.08;
    double Barrier = 70.0;
    unsigned long Steps;

    cout << "\nNumber of steps\n";
    cin >> Steps;

    cout << "\nParameters Used:\n";
    cout << "Spot: " << Spot << "\n";
    cout << "Strike: " << Strike << "\n";
    cout << "Barrier: " << Barrier << "\n";
    cout << "Volatility: " << Vol << "\n";
    cout << "Risk-free rate: " << r << "\n";
    cout << "Dividend yield: " << d << "\n";
    cout << "Expiry: " << Expiry << "\n";
    cout << "Number of steps: " << Steps << "\n\n";

    // create the observable subjects
    pTreeObservable crrObservable(new TreeObservable("CRRBiTree"));
    pTreeObservable triObservable(new TreeObservable("TriTree"));
    
    // create report writers (observers) and register them with observables
    OptionPricingReportWriter reportWriterCRR(crrObservable, "CRR Report");
    OptionPricingReportWriter reportWriterTri(triObservable, "Trinomial Report");
    
    // create pricers with observables attached
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    
    TreePricerWithObserver crrPricer(crrObservable, Spot, rParam, dParam, Vol, Steps, Expiry);
    TreePricerWithObserver triPricer(triObservable, Spot, rParam, dParam, Vol, Steps, Expiry);
    
    // build the option products
    PayOffCall callPayOff(Strike);
    PayOffPut putPayOff(Strike);
    
    TreeAmerican amerCall(Expiry, callPayOff);
    TreeAmerican amerPut(Expiry, putPayOff);
    TreeEuropeanBarrier barrierCall(Expiry, callPayOff, Barrier);
    TreeEuropeanBarrier barrierPut(Expiry, putPayOff, Barrier);
    
    cout << "Pricing Options with Observer Notifications:\n\n";
    
    // price each option - each pricing triggers observer update
    crrPricer.price(amerCall, "American Call");
    crrPricer.price(amerPut, "American Put");
    crrPricer.price(barrierCall, "Barrier Call");
    crrPricer.price(barrierPut, "Barrier Put");
    
    triPricer.price(amerCall, "American Call");
    triPricer.price(amerPut, "American Put");
    triPricer.price(barrierCall, "Barrier Call");
    triPricer.price(barrierPut, "Barrier Put");
    
    double tmp;
    cin >> tmp;

    return 0;
}