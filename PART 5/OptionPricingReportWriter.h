//
//  OptionPricingReportWriter.h
//  Part5_ObserverPattern
//

#ifndef OptionPricingReportWriter_h
#define OptionPricingReportWriter_h

#include <ql/patterns/observable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

class TreeObservable;

typedef boost::shared_ptr<TreeObservable> pTreeObservable;

class OptionPricingReportWriter : public QuantLib::Observer
{
public:
    OptionPricingReportWriter(const pTreeObservable& observable,
                              const std::string& reportName);
    
    void update() override;
    void write(const std::string& message);

private:
    pTreeObservable observable;
    std::string reportName;
};

#endif /* OptionPricingReportWriter_h */