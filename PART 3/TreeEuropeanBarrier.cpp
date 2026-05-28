//
//  TreeEuropeanBarrier.cpp
//  Part2_TreeEuropeanBarrier
//

#include "TreeEuropeanBarrier.h"
#include <algorithm>

TreeEuropeanBarrier::TreeEuropeanBarrier(double FinalTime,
                                         const PayOffBridge& ThePayOff_,
                                         double Barrier_)
                 : TreeProducts(FinalTime),
                   ThePayOff(ThePayOff_),
                   Barrier(Barrier_)
{
}

TreeProducts* TreeEuropeanBarrier::clone() const
{
    return new TreeEuropeanBarrier(*this);
}

double TreeEuropeanBarrier::FinalPayOff(double Spot) const
{
    // Check barrier at maturity: if spot is at or above barrier, option is knocked out
    if (Spot >= Barrier)
        return 0.0;
    
    return ThePayOff(Spot);
}

double TreeEuropeanBarrier::PreFinalValue(double Spot,
                                          double, // Time argument not used, following TreeEuropean pattern
                                          double DiscountedFutureValue) const
{
    // Check barrier at this node: if breached, option is worthless
    if (Spot >= Barrier)
        return 0.0;
    
    // European style: no early exercise, just pass through the discounted future value
    return DiscountedFutureValue;
}