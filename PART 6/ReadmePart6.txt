
Part 5 - Part 6 - Factory + Observer Integration

AUTHOR
------
Brandon Tanaka Chapwanya

BUILD INSTRUCTIONS
------------------
This program integrates the PayOffFactory (Part 4) with the Observer 
pattern (Part 5). Four option pricers are created via the factory and 
registered with OptionPricingReportWriter observers using boost::shared_ptr. 
Prices are reported for N = 50, 100, 200, 400.

REQUIRES QUANTLIB
-----------------
  Install: brew install quantlib

  Compile (from part 6 folder):
    g++ -std=c++11 -o Part6 Part6_Main.cpp BiTAmeriCall.cpp 
        BiTAmeriPut.cpp BiTEuroBarrierCall.cpp BiTEuroBarrierPut.cpp 
        PayOffConstructible.cpp TreeObservable.cpp 
        OptionPricingReportWriter.cpp CRRBinomialTree.cpp 
        TrinomialTree.cpp TreeAmerican.cpp TreeEuropeanBarrier.cpp 
        Arrays.cpp Parameters.cpp PayOff3.cpp PayOffBridge.cpp 
        TreeProducts.cpp ArgList.cpp BlackScholesFormulas.cpp 
        Normals.cpp -I/opt/homebrew/include -L/opt/homebrew/lib 
        -lQuantLib && ./Part6

RUNNING
-------
  ./Part6
  No user input required. Program loops through N=50,100,200,400 
  automatically.

FILES INCLUDED
--------------
  Part6_Main.cpp                     - Main program
  BiTAmeriCall.h/.cpp                - American Call pricer (TreeObservable)
  BiTAmeriPut.h/.cpp                 - American Put pricer (TreeObservable)
  BiTEuroBarrierCall.h/.cpp          - Barrier Call pricer (TreeObservable)
  BiTEuroBarrierPut.h/.cpp           - Barrier Put pricer (TreeObservable)
  TreeObservable.h/.cpp              - QuantLib Observable base
  OptionPricingReportWriter.h/.cpp   - QuantLib Observer with write()
  PayOffFactory.h                    - Template singleton factory
  PayOffConstructible.h/.cpp         - Auto-registration via PayOffHelper
  ArgList.h/.cpp                     - Parameter passing
  CRRBinomialTree.h/.cpp, TrinomialTree.h/.cpp,
  TreeAmerican.h/.cpp, TreeEuropeanBarrier.h/.cpp,
  TreeProducts.h/.cpp, Parameters.h/.cpp, PayOff3.h/.cpp,
  PayOffBridge.h/.cpp, Arrays.h/.cpp,
  BlackScholesFormulas.h/.cpp, Normals.h/.cpp

RESULTS (N=50)
--------------
  BiTAmeriCa - 2026-05-10: American Call priced at 4.00451
  BiTAmeriPu - 2026-05-10: American Put priced at 8.07813
  BiTEuroBaC - 2026-05-10: Barrier Call priced at 1.13964
  BiTEuroBaP - 2026-05-10: Barrier Put priced at 8.03444

RESULTS (N=100)
---------------
  BiTAmeriCa - 2026-05-10: American Call priced at 4.00373
  BiTAmeriPu - 2026-05-10: American Put priced at 8.08843
  BiTEuroBaC - 2026-05-10: Barrier Call priced at 1.12594
  BiTEuroBaP - 2026-05-10: Barrier Put priced at 8.03683

RESULTS (N=200)
---------------
  BiTAmeriCa - 2026-05-10: American Call priced at 4.00669
  BiTAmeriPu - 2026-05-10: American Put priced at 8.08526
  BiTEuroBaC - 2026-05-10: Barrier Call priced at 1.12003
  BiTEuroBaP - 2026-05-10: Barrier Put priced at 8.02913

RESULTS (N=400)
---------------
  BiTAmeriCa - 2026-05-10: American Call priced at 4.00654
  BiTAmeriPu - 2026-05-10: American Put priced at 8.08571
  BiTEuroBaC - 2026-05-10: Barrier Call priced at 1.09862
  BiTEuroBaP - 2026-05-10: Barrier Put priced at 8.02615

NOTES
-----
  - Each pricer inherits from TreeObservable (QuantLib::Observable)
  - OptionPricingReportWriter inherits from QuantLib::Observer
  - Factory creates pricers by string ID; observers registered via 
    boost::shared_ptr
  - Barrier call price decreases as N increases (finer grid detects 
    more barrier breaches)
  - American call/put prices stable across N (rapid convergence)