//
//  Part1_Main.cpp
//  Part1_CRRBinomialTree

#include "CRRBinomialTree.h"
#include "TrinomialTree.h"
#include "TreeAmerican.h"
#include "TreeEuropean.h"
#include "BlackScholesFormulas.h"
#include <iostream>
#include "TextTable.h"

using namespace std;
#include <cmath>

int main()
{
    // Parameters from Table 1
    double Expiry = 1.0;          // T = 1 year
    double Strike = 50.0;         // K = 50
    double Spot = 50.0;           // S0 = 50
    double Vol = 0.30;            // sigma = 0.30
    double r = 0.05;              // r = 0.05
    double d = 0.08;              // dividend yield = 0.08
    unsigned long Steps = 50;     // N = 50
    

    cout << "\nNumber of steps\n";
    cin >> Steps;

        cout << "\nNumber of steps: " << Steps << "\n";
    cout << "\nParameters Used:\n";
    cout << "Spot: " << Spot << "\n";
    cout << "Strike: " << Strike << "\n";
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

    // Create TreeAmerican objects
    TreeAmerican TreeAmerCall(Expiry, thePayOffCall);
    TreeAmerican TreeAmerPut(Expiry, thePayOffPut);

    // Create CRRBinomialTree object
    CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);

    // Create BoyleTrinomialTree object for comparison
    BoyleTrinomialTree TrinomTree(Spot, rParam, dParam, Vol, Steps, Expiry);

    double americanCallPriceCRR = 0.0;
    double americanPutPriceCRR = 0.0;
    double americanCallPriceTri = 0.0;
    double americanPutPriceTri = 0.0;

    // Calculate American Option prices using CRR Binomial Tree
    americanCallPriceCRR = CRRTree.GetThePrice(TreeAmerCall);
    americanPutPriceCRR = CRRTree.GetThePrice(TreeAmerPut);

    // Calculate American Option prices using Trinomial Tree
    americanCallPriceTri = TrinomTree.GetThePrice(TreeAmerCall);
    americanPutPriceTri = TrinomTree.GetThePrice(TreeAmerPut);

    // Build Tabular Output
    TextTable t('-', '|', '+');

    t.add("");
    t.add("American Call");
    t.add("American Put");
    t.endOfRow();

    t.add("CRR Binomial Tree");
    t.add(to_string(americanCallPriceCRR));
    t.add(to_string(americanPutPriceCRR));
    t.endOfRow();

    t.add("Boyle Trinomial Tree");
    t.add(to_string(americanCallPriceTri));
    t.add(to_string(americanPutPriceTri));
    t.endOfRow();

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t;

    double tmp;
    cin >> tmp;

    return 0;
}