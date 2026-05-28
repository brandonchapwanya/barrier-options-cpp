//
//  Part2_Main.cpp
//  Part2_TreeEuropeanBarrier
//


#include "CRRBinomialTree.h"
#include "TrinomialTree.h"
#include "TreeEuropeanBarrier.h"
#include "BlackScholesFormulas.h"
#include <iostream>
#include "TextTable.h"

using namespace std;
#include <cmath>

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
    cout << "Number of steps: " << Steps << "\n";

    // Create PayOff objects for Call and Put Options
    PayOffCall thePayOffCall(Strike);
    PayOffPut thePayOffPut(Strike);

    // Create ParametersConstant for risk-free rate and dividend yield
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    // Create TreeEuropeanBarrier objects for barrier call and put
    TreeEuropeanBarrier TreeBarrierCall(Expiry, thePayOffCall, Barrier);
    TreeEuropeanBarrier TreeBarrierPut(Expiry, thePayOffPut, Barrier);

    // Create CRRBinomialTree object
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);

    // Create BoyleTrinomialTree object for comparison
    BoyleTrinomialTree TrinomTree(Spot, rParam, dParam, Vol, Steps, Expiry);

    double barrierCallPriceCRR = 0.0;
    double barrierPutPriceCRR = 0.0;
    double barrierCallPriceTri = 0.0;
    double barrierPutPriceTri = 0.0;

    // Calculate European Barrier Option prices using CRR Binomial Tree
    barrierCallPriceCRR = CRRTree.GetThePrice(TreeBarrierCall);
    barrierPutPriceCRR = CRRTree.GetThePrice(TreeBarrierPut);

    // Calculate European Barrier Option prices using Trinomial Tree
    barrierCallPriceTri = TrinomTree.GetThePrice(TreeBarrierCall);
    barrierPutPriceTri = TrinomTree.GetThePrice(TreeBarrierPut);

    cout << "\nEuropean Knock-Out Barrier Option Prices:\n";

    // Build Tabular Output
    TextTable t('-', '|', '+');

    t.add("");
    t.add("Barrier Call");
    t.add("Barrier Put");
    t.endOfRow();

    t.add("CRR Binomial Tree");
    t.add(to_string(barrierCallPriceCRR));
    t.add(to_string(barrierPutPriceCRR));
    t.endOfRow();

    t.add("Boyle Trinomial Tree");
    t.add(to_string(barrierCallPriceTri));
    t.add(to_string(barrierPutPriceTri));
    t.endOfRow();

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t;

    double tmp;
    cin >> tmp;

    return 0;
}