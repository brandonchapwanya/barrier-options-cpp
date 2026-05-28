//
//  CRRBinomialTree.cpp
//  Part1_CRRBinomialTree

#include "CRRBinomialTree.h"
#include "Arrays.h"
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

CRRBinomialTree::CRRBinomialTree(double Spot_,
                                 const Parameters& r_,
                                 const Parameters& d_,
                                 double Volatility_,
                                 unsigned long Steps_,
                                 double Time_)
                                 : Spot(Spot_),
                                   r(r_),
                                   d(d_),
                                   Volatility(Volatility_),
                                   Steps(Steps_),
                                   Time(Time_),
                                   Discounts(Steps_)
{
    TreeBuilt = false;
}

void CRRBinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps + 1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(i + 1);

        double thisTime = (i * Time) / Steps;

        double movedLogSpot = InitialLogSpot 
                            + r.Integral(0.0, thisTime)
                            - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5 * Volatility * Volatility * thisTime;

        double sd = Volatility * sqrt(Time / Steps);

        for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j + 2, k++)
        {
            TheTree[i][k].first = exp(movedLogSpot + j * sd);
        }
    }
   
    for (unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l * Time / Steps, (l + 1) * Time / Steps));
    }
}

double CRRBinomialTree::GetThePrice(const TreeProducts& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in CRRBinomialTree");

    for (long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j + 2, k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

    double delta_t = Time / Steps;
    double u = exp(Volatility * sqrt(delta_t));
    double d_val = 1.0 / u;
    double p = (exp((r.Integral(0.0, delta_t) - d.Integral(0.0, delta_t))) - d_val) / (u - d_val);

    for (unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps - i;
        double ThisTime = index * Time / Steps;
   
        for (long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j + 2, k++)
        {
            double Spot_val = TheTree[index][k].first;
            double futureDiscountedValue = Discounts[index] 
                            * (p * TheTree[index + 1][k + 1].second 
                             + (1.0 - p) * TheTree[index + 1][k].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot_val, ThisTime, futureDiscountedValue);
        }
    }
    return TheTree[0][0].second;
}