//
//  BinomialTree.cpp
//  ch8_trees
//
//  Created by Steve Yang on 10/25/21.
//

#include "TrinomialTree.h"
#include "Arrays.h"
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

BoyleTrinomialTree::BoyleTrinomialTree(double Spot_,
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
                                         Discounts(Steps)
{
    TreeBuilt=false;
}

void BoyleTrinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(2*i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot =
                            InitialLogSpot+ r.Integral(0.0, thisTime)
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(2*Time/Steps);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j++,k++)
        {
			TheTree[i][k].first = exp(movedLogSpot + j * sd);
		}
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double BoyleTrinomialTree::GetThePrice(const TreeProducts& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleTrinomialTree");

    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>(Steps); j++,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

	double delta_t = Time / Steps;
	// 2*sigma^2/(r - q)^2
	double check = 2 * pow(Volatility / (r.Integral(0.0, 1.0) - d.Integral(0.0, 1.0)), 2);
	if (delta_t >= check)
		throw("Condition on delta_t is not satisfied!");
	// Compute the probabilities p_u, p_d, p_m
	double x = exp(Volatility * sqrt(delta_t / 2));
	double y = exp(0.5 * (r.Integral(0.0, delta_t) - d.Integral(0.0, delta_t)));
	double p_u = pow((y - 1/x) / (x - 1/x), 2);
	double p_d = pow((x - y) / (x - 1/x), 2);
	double p_m = 1 - p_u - p_d;

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = index*Time/Steps;

        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j++,k++)
        {
            double Spot = TheTree[index][k].first;
			double futureDiscountedValue =
						Discounts[index]
						* (p_d * TheTree[index + 1][k].second
						+ p_m * TheTree[index + 1][k + 1].second
						+ p_u * TheTree[index + 1][k + 2].second);
			TheTree[index][k].second = TheProduct.PreFinalValue(Spot, ThisTime, futureDiscountedValue);
		}   
    }
    return TheTree[0][0].second;
}
