//
//  OptionPricingReportWriter.cpp
//  Part5_ObserverPattern
//

#include "OptionPricingReportWriter.h"
#include "TreeObservable.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

OptionPricingReportWriter::OptionPricingReportWriter(const pTreeObservable& obs,
                                                     const std::string& reportName)
    : observable(obs), reportName(reportName)
{
    this->registerWith(observable);
}

void OptionPricingReportWriter::update()
{
    std::string sourceId = observable->getSourceId();
    std::string message = observable->getLastMessage();
    
    write(message);
}

void OptionPricingReportWriter::write(const std::string& message)
{
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);
    
    std::ostringstream timeStream;
    timeStream << std::setfill('0')
               << std::setw(4) << (localTime->tm_year + 1900) << "-"
               << std::setw(2) << (localTime->tm_mon + 1) << "-"
               << std::setw(2) << localTime->tm_mday;
    std::string timestamp = timeStream.str();
    
    std::string sourceId = observable->getSourceId();
    
    std::ostringstream sourceFormatted;
    sourceFormatted << std::left << std::setw(10) << sourceId.substr(0, 10);
    
    std::ostringstream timeFormatted;
    timeFormatted << std::left << std::setw(10) << timestamp;
    
    std::cout << sourceFormatted.str() << " - "
              << timeFormatted.str() << ": "
              << message << std::endl;
}