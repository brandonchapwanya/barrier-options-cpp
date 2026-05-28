//
//  Part6_Main.cpp
//  Part6_FactoryObserver
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
    ArgList.cpp
    TreeObservable.cpp
    OptionPricingReportWriter.cpp
    BiTAmeriCall.cpp
    BiTAmeriPut.cpp
    BiTEuroBarrierCall.cpp
    BiTEuroBarrierPut.cpp
    PayOffConstructible.cpp
*/

#include "BiTAmeriCall.h"
#include "BiTAmeriPut.h"
#include "BiTEuroBarrierCall.h"
#include "BiTEuroBarrierPut.h"
#include "OptionPricingReportWriter.h"
#include "ArgList.h"
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

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

    vector<unsigned long> StepsList;
    StepsList.push_back(50);
    StepsList.push_back(100);
    StepsList.push_back(200);
    StepsList.push_back(400);

    cout << "\nParameters Used:\n";
    cout << "Spot: " << Spot << "\n";
    cout << "Strike: " << Strike << "\n";
    cout << "Barrier: " << Barrier << "\n";
    cout << "Volatility: " << Vol << "\n";
    cout << "Risk-free rate: " << r << "\n";
    cout << "Dividend yield: " << d << "\n";
    cout << "Expiry: " << Expiry << "\n\n";

    cout << "Option Pricing Report via Observer Pattern\n";
    cout << "==========================================\n\n";

    for (unsigned long idx = 0; idx < StepsList.size(); idx++)
    {
        unsigned long Steps = StepsList[idx];

        cout << "--- N = " << Steps << " ---\n";

        ArgumentList args("OptionParameters");
        args.add("spot", Spot);
        args.add("strike", Strike);
        args.add("barrier", Barrier);
        args.add("vol", Vol);
        args.add("r", r);
        args.add("d", d);
        args.add("expiry", Expiry);
        args.add("steps", static_cast<double>(Steps));

        // create option pricers stored in boost::shared_ptr (they are TreeObservables)
        pTreeObservable ameriCall(new BiTAmeriCall(args));
        pTreeObservable ameriPut(new BiTAmeriPut(args));
        pTreeObservable barrierCall(new BiTEuroBarrierCall(args));
        pTreeObservable barrierPut(new BiTEuroBarrierPut(args));

        // create one report writer per pricer and register it
        // using boost::shared_ptr as required
        boost::shared_ptr<OptionPricingReportWriter> writerCall(
            new OptionPricingReportWriter(ameriCall, "Report"));
        boost::shared_ptr<OptionPricingReportWriter> writerPut(
            new OptionPricingReportWriter(ameriPut, "Report"));
        boost::shared_ptr<OptionPricingReportWriter> writerBarrierCall(
            new OptionPricingReportWriter(barrierCall, "Report"));
        boost::shared_ptr<OptionPricingReportWriter> writerBarrierPut(
            new OptionPricingReportWriter(barrierPut, "Report"));

        // price each option - triggers update() on its registered observer
        // cast to derived type to call Price()
        boost::static_pointer_cast<BiTAmeriCall>(ameriCall)->Price();
        boost::static_pointer_cast<BiTAmeriPut>(ameriPut)->Price();
        boost::static_pointer_cast<BiTEuroBarrierCall>(barrierCall)->Price();
        boost::static_pointer_cast<BiTEuroBarrierPut>(barrierPut)->Price();

        cout << "\n";
    }

    double tmp;
    cin >> tmp;

    return 0;
}