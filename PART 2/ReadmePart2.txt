
Part 2 - European Knock-Out Barrier Options


AUTHOR
------
Brandon Tanaka Chapwanya

BUILD INSTRUCTIONS
------------------
This project prices European knock-out barrier call and put options using 
both CRR Binomial Tree and Boyle Trinomial Tree methods.

All files are in a single directory. No external libraries are needed beyond 
standard C++.

Compile (example using g++ on macOS/Linux):

  g++ -std=c++11 -o Part2 Part2_Main.cpp CRRBinomialTree.cpp 
      TrinomialTree.cpp TreeEuropeanBarrier.cpp Arrays.cpp 
      Parameters.cpp PayOff3.cpp PayOffBridge.cpp TreeProducts.cpp 
      TreeAmerican.cpp TreeEuropean.cpp BlackScholesFormulas.cpp 
      Normals.cpp && ./Part2

Or open in VS Code / Xcode and add all .cpp and .h files to the project.

FILES INCLUDED
--------------
  TreeEuropeanBarrier.h    - European barrier option class header
  TreeEuropeanBarrier.cpp  - European barrier option class implementation
  Part2_Main.cpp           - Main program, prices barrier options and 
                             compares CRR Binomial with Trinomial tree
  CRRBinomialTree.h/.cpp   - CRR Binomial Tree (from Part 1)
  TrinomialTree.h/.cpp     - Boyle Trinomial Tree (from provided materials)

  Helper files (from course materials):
  TreeProducts.h/.cpp      - Abstract base class for tree-priced derivatives
  TreeAmerican.h/.cpp      - American option exercise strategy
  TreeEuropean.h/.cpp      - European option exercise strategy
  Parameters.h/.cpp        - Parameter classes (Bridge pattern)
  PayOff3.h/.cpp           - PayOff class hierarchy (Call, Put)
  PayOffBridge.h/.cpp      - PayOff Bridge wrapper
  Arrays.h/.cpp            - MJArray custom array class
  BlackScholesFormulas.h/.cpp - Black-Scholes closed-form formulas
  Normals.h/.cpp           - Normal distribution functions
  TextTable.h              - ASCII table formatting utility

DESIGN PATTERN
--------------
  TreeEuropeanBarrier derives from TreeProducts, following the same 
  design pattern as TreeAmerican:

  - Constructor takes FinalTime, PayOffBridge, and Barrier level
  - FinalPayOff() returns zero if Spot >= Barrier (knocked out at maturity),
    otherwise returns the standard payoff
  - PreFinalValue() checks the barrier at every node: if Spot >= Barrier,
    option value becomes zero and stays zero through backward induction
  - No early exercise (European style): PreFinalValue returns the 
    continuation value rather than max(intrinsic, continuation)

PARAMETERS USED
---------------
  Spot Price (S0)     = 50
  Strike Price (K)    = 50
  Barrier Level (B)   = 70
  Volatility (sigma)  = 0.30
  Risk-free rate (r)  = 0.05
  Dividend yield (d)  = 0.08
  Expiry (T)          = 1.0
  Number of Steps (N) = 50 (user prompted)

OUTPUT
------
  The program prompts for the number of steps, prints the parameters 
  used, then displays European knock-out barrier call and put option 
  prices from both the CRR Binomial Tree and Boyle Trinomial Tree 
  in a formatted table for comparison.

  Expected results at N=50:
    Barrier Call (CRR):  ~1.14
    Barrier Put (CRR):   ~8.03
    Barrier Call (Tri):  ~1.18
    Barrier Put (Tri):   ~8.05

NOTES
-----
  - The barrier check happens at every node during backward induction
  - Once a node reaches or exceeds the barrier, its value becomes zero
  - The barrier put price is close to the standard put because the 
    barrier (70) is far above the spot (50), so knock-out is unlikely
  - The barrier call is significantly reduced compared to a standard 
    call because upward paths that would make the call valuable also 
    risk hitting the barrier