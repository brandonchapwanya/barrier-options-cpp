
Part 3 - Convergence Analysis


AUTHOR
------
Brandon Tanaka Chapwanya

BUILD INSTRUCTIONS
------------------
This program compares American call and European knock-out barrier call 
option prices across multiple time step values (N = 50, 100, 200, 400) 
using both CRR Binomial Tree and Boyle Trinomial Tree methods.

All files are in a single directory. No external libraries are needed 
beyond standard C++.

Compile (example using g++ on macOS/Linux):

  g++ -std=c++11 -o Part3 Part3_Main.cpp CRRBinomialTree.cpp 
      TrinomialTree.cpp TreeAmerican.cpp TreeEuropeanBarrier.cpp 
      Arrays.cpp Parameters.cpp PayOff3.cpp PayOffBridge.cpp 
      TreeProducts.cpp TreeEuropean.cpp BlackScholesFormulas.cpp 
      Normals.cpp && ./Part3

FILES INCLUDED
--------------
  Part3_Main.cpp           - Main program that loops over N=50,100,200,400
                             and tabulates American vs barrier call prices
  CRRBinomialTree.h/.cpp   - CRR Binomial Tree (from Part 1)
  TreeEuropeanBarrier.h/.cpp - European barrier option class (from Part 2)
  TrinomialTree.h/.cpp     - Boyle Trinomial Tree (from provided materials)

  Helper files (from course materials):
  TreeAmerican.h/.cpp      - American option exercise strategy
  TreeEuropean.h/.cpp      - European option exercise strategy
  TreeProducts.h/.cpp      - Abstract base class for tree-priced derivatives
  Parameters.h/.cpp        - Parameter classes (Bridge pattern)
  PayOff3.h/.cpp           - PayOff class hierarchy (Call, Put)
  PayOffBridge.h/.cpp      - PayOff Bridge wrapper
  Arrays.h/.cpp            - MJArray custom array class
  BlackScholesFormulas.h/.cpp - Black-Scholes closed-form formulas
  Normals.h/.cpp           - Normal distribution functions
  TextTable.h              - ASCII table formatting utility

PARAMETERS USED
---------------
  Spot Price (S0)     = 50
  Strike Price (K)    = 50
  Barrier Level (B)   = 70
  Volatility (sigma)  = 0.30
  Risk-free rate (r)  = 0.05
  Dividend yield (d)  = 0.08
  Expiry (T)          = 1.0

RESULTS SUMMARY
---------------
  N=50:  American Call = 4.004509  Barrier Call = 1.139640
  N=100: American Call = 4.003734  Barrier Call = 1.125936
  N=200: American Call = 4.006687  Barrier Call = 1.120027
  N=400: American Call = 4.006543  Barrier Call = 1.098615

ANSWERS TO QUESTIONS
--------------------
  (a) The knock-out barrier call is worth less because it becomes 
      worthless if the stock price ever reaches or exceeds B=70. 
      Upward stock movements that create profits for the American 
      call also trigger knock-out for the barrier call. The American 
      call also benefits from early exercise, which the barrier call 
      (European style) does not.

  (b) As N increases, the American call price stabilizes near 4.00 
      while the barrier call price gradually decreases from 1.14 to 
      1.10. This happens because finer time steps detect more barrier 
      breaches, giving a more accurate (and lower) price. Both prices 
      converge to their continuous-time limits as discretization 
      error shrinks.