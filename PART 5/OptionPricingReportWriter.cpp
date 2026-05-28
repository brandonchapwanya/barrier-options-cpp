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
    
    // Build the full message string and pass to write()
    write(message);
}

void OptionPricingReportWriter::write(const std::string& message)
{
    // get current time
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);
    
    // format timestamp as YYYY-MM-DD
    std::ostringstream timeStream;
    timeStream << std::setfill('0')
               << std::setw(4) << (localTime->tm_year + 1900) << "-"
               << std::setw(2) << (localTime->tm_mon + 1) << "-"
               << std::setw(2) << localTime->tm_mday;
    std::string timestamp = timeStream.str();
    
    // get source ID from the observable
    std::string sourceId = observable->getSourceId();
    
    // format source and timestamp to exactly 10 characters each
    std::ostringstream sourceFormatted;
    sourceFormatted << std::left << std::setw(10) << sourceId.substr(0, 10);
    
    std::ostringstream timeFormatted;
    timeFormatted << std::left << std::setw(10) << timestamp;
    
    // print formatted output
    std::cout << sourceFormatted.str() << " - "
              << timeFormatted.str() << ": "
              << message << std::endl;
}