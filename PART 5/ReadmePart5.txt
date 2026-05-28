
Part 5 - Observer Pattern with QuantLib

AUTHOR
------
Brandon Tanaka Chapwanya

BUILD INSTRUCTIONS
------------------
This program uses the QuantLib Observable/Observer pattern to create a
pricing report system. TreeObservable extends QuantLib::Observable and
OptionPricingReportWriter extends QuantLib::Observer. Each time an option
is priced, the pricer sends a message through the TreeObservable, which
notifies all registered observers.

REQUIRES QUANTLIB
-----------------
  Install QuantLib:
    brew install quantlib

  Compile:
    g++ -std=c++11 -o Part5 Part5_Main.cpp TreeObservable.cpp 
        OptionPricingReportWriter.cpp TreePricerWithObserver.cpp 
        CRRBinomialTree.cpp TrinomialTree.cpp TreeAmerican.cpp 
        TreeEuropeanBarrier.cpp Arrays.cpp Parameters.cpp PayOff3.cpp 
        PayOffBridge.cpp TreeProducts.cpp BlackScholesFormulas.cpp 
        Normals.cpp -I/opt/homebrew/include -L/opt/homebrew/lib 
        -lQuantLib && ./Part5

  For Intel Macs, replace /opt/homebrew with /usr/local.

RUNNING THE PROGRAM
-------------------
  ./Part5

  The program will prompt:
    Number of steps
  Enter a value (e.g. 50) and press Enter.

FILES INCLUDED
--------------
  TreeObservable.h/.cpp              - Observable subject class
  OptionPricingReportWriter.h/.cpp   - Observer class with write() method
  TreePricerWithObserver.h/.cpp      - Pricer that sends messages to
                                       observable when pricing completes
  Part5_Main.cpp                     - Main program

  CRRBinomialTree.h/.cpp             - CRR Binomial Tree (from Part 1)
  TrinomialTree.h/.cpp               - Boyle Trinomial Tree
  TreeAmerican.h/.cpp                - American option strategy
  TreeEuropeanBarrier.h/.cpp         - Barrier option strategy

  Helper files (from course materials):
  TreeProducts.h/.cpp, Parameters.h/.cpp, PayOff3.h/.cpp,
  PayOffBridge.h/.cpp, Arrays.h/.cpp, BlackScholesFormulas.h/.cpp,
  Normals.h/.cpp

OBSERVER PATTERN FLOW
---------------------
  TreeObservable (subject) --> OptionPricingReportWriter (observer)
  
  1. TreePricerWithObserver::price() computes both CRR and Trinomial prices
  2. Sends message string to TreeObservable::sendMessage()
  3. TreeObservable stores the message and calls notifyObservers()
  4. QuantLib notifies all registered OptionPricingReportWriter observers
  5. Each observer's update() calls write() to format and print the message

WRITE METHOD FORMAT
-------------------
  Source field:  fixed 10 characters, left-aligned (class ID of observable)
  Timestamp:     fixed 10 characters, left-aligned (YYYY-MM-DD format)
  Message:       unlimited length (option name and both prices)

  Example output:
    CRRBiTree  - 2026-05-10: American Call - CRR: 4.00451, Trinomial: 3.99863

PARAMETERS USED
---------------
  Spot Price (S0)     = 50
  Strike Price (K)    = 50
  Barrier Level (B)   = 70
  Volatility (sigma)  = 0.30
  Risk-free rate (r)  = 0.05
  Dividend yield (d)  = 0.08
  Expiry (T)          = 1.0
  Number of Steps (N) = user prompted

NOTES
-----
  - IntelliSense squiggles in VS Code are expected for QuantLib includes;
    they do not affect compilation as long as -I/opt/homebrew/include is
    passed to g++
  - The warning about nested namespace definition is from QuantLib's
    shared_ptr.hpp and is harmless
