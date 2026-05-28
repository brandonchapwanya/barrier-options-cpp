//
//  TreeEuropeanBarrier.h
//  Part2_TreeEuropeanBarrier
//

#ifndef TreeEuropeanBarrier_h
#define TreeEuropeanBarrier_h

#include "TreeProducts.h"
#include "PayOffBridge.h"

class TreeEuropeanBarrier : public TreeProducts
{

public:

    TreeEuropeanBarrier(double FinalTime,
                        const PayOffBridge& ThePayOff_,
                        double Barrier_);

    virtual TreeProducts* clone() const;
    virtual double FinalPayOff(double Spot) const;
    virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const;
    virtual ~TreeEuropeanBarrier(){}

private:

    PayOffBridge ThePayOff;
    double Barrier;

};

#endif /* TreeEuropeanBarrier_h */