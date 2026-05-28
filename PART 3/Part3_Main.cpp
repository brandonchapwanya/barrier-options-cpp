//
//  Part3_Main.cpp
//  Part3_ConvergenceAnalysis
//


#include "CRRBinomialTree.h"
#include "TrinomialTree.h"
#include "TreeAmerican.h"
#include "TreeEuropeanBarrier.h"
#include "BlackScholesFormulas.h"
#include <iostream>
#include <vector>
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

    // Exercise times to test
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

    cout << "Comparing American Call and European Knock-Out Barrier Call\n";
    cout << "across different numbers of time steps:\n\n";

    // Create PayOff object for Call Option
    PayOffCall thePayOffCall(Strike);

    // Create ParametersConstant for risk-free rate and dividend yield
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    // Build Tabular Output
    TextTable t('-', '|', '+');

    t.add("Steps (N)");
    t.add("American Call (CRR)");
    t.add("Barrier Call (CRR)");
    t.add("American Call (Tri)");
    t.add("Barrier Call (Tri)");
    t.endOfRow();

    for (unsigned long idx = 0; idx < StepsList.size(); idx++)
    {
        unsigned long Steps = StepsList[idx];

        // Create TreeAmerican for standard American call
        TreeAmerican TreeAmerCall(Expiry, thePayOffCall);

        // Create TreeEuropeanBarrier for knock-out barrier call
        TreeEuropeanBarrier TreeBarrierCall(Expiry, thePayOffCall, Barrier);

        // Create CRRBinomialTree object
        CRRBinomialTree CRRTree(Spot, rParam, dParam, Vol, Steps, Expiry);

        // Create BoyleTrinomialTree object for comparison
        BoyleTrinomialTree TrinomTree(Spot, rParam, dParam, Vol, Steps, Expiry);

        // Calculate prices
        double amerCallCRR = CRRTree.GetThePrice(TreeAmerCall);
        double barrierCallCRR = CRRTree.GetThePrice(TreeBarrierCall);
        double amerCallTri = TrinomTree.GetThePrice(TreeAmerCall);
        double barrierCallTri = TrinomTree.GetThePrice(TreeBarrierCall);

        t.add(to_string(Steps));
        t.add(to_string(amerCallCRR));
        t.add(to_string(barrierCallCRR));
        t.add(to_string(amerCallTri));
        t.add(to_string(barrierCallTri));
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    t.setAlignment(3, TextTable::Alignment::RIGHT);
    t.setAlignment(4, TextTable::Alignment::RIGHT);
    t.setAlignment(5, TextTable::Alignment::RIGHT);
    std::cout << t;

    cout << "\n";
    cout << "Analysis:\n";
    cout << "---------\n";
    cout << "(a) The knock-out barrier call is worth less than the American call\n";
    cout << "    because the barrier feature adds a condition that makes the option\n";
    cout << "    worthless if the stock price ever reaches or exceeds B=70 during\n";
    cout << "    its life. Many paths that would produce a positive payoff for the\n";
    cout << "    American call get knocked out and pay zero instead. The American\n";
    cout << "    call has no such restriction and also benefits from early exercise.\n\n";
    cout << "(b) As the number of time steps increases from 50 to 400, the option\n";
    cout << "    prices converge toward stable values. With more steps, the tree\n";
    cout << "    approximates the continuous-time model more accurately, reducing\n";
    cout << "    discretization error. The barrier condition also becomes more\n";
    cout << "    precise because the tree checks the barrier more frequently,\n";
    cout << "    making knock-out detection more accurate along each path.\n";

    double tmp;
    cin >> tmp;

    return 0;
}