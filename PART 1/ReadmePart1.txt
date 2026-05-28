
 Part 1 - CRR Binomial Tree Option Pricer


AUTHOR
------
Brandon Tanaka Chapwanya

BUILD INSTRUCTIONS
------------------
This project prices American call and put options using the CRR Binomial Tree 
method and compares results with the Boyle Trinomial Tree.

All files are in a single directory. No external libraries are needed beyond 
standard C++.

Compile (example using g++ on macOS/Linux):

  g++ -o Part1 Part1_Main.cpp CRRBinomialTree.cpp TrinomialTree.cpp 
      Arrays.cpp Parameters.cpp PayOff3.cpp PayOffBridge.cpp 
      TreeProducts.cpp TreeAmerican.cpp TreeEuropean.cpp 
      BlackScholesFormulas.cpp Normals.cpp -std=c++11

Or using Xcode:
  1. Create a new Command Line Tool project
  2. Add all .cpp and .h files to the project
  3. Build and Run

RUNNING THE PROGRAM
-------------------
When you run the program, you will be prompted:

  Number of steps

Enter the number of time steps for the binomial tree (e.g., 50).
The program then prints the parameters used and a table comparing 
the CRR Binomial Tree and Boyle Trinomial Tree prices for American 
call and put options.

FILES INCLUDED
--------------
  CRRBinomialTree.h        - CRR Binomial Tree class header
  CRRBinomialTree.cpp      - CRR Binomial Tree class implementation
  Part1_Main.cpp           - Main program, prices American options and 
                             compares with Trinomial tree

  Helper files (from course materials):
  TreeProducts.h/.cpp      - Abstract base class for tree-priced derivatives
  TreeAmerican.h/.cpp      - American option exercise strategy
  TreeEuropean.h/.cpp      - European option exercise strategy  
  TrinomialTree.h/.cpp     - Boyle Trinomial Tree for comparison
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
  Volatility (sigma)  = 0.30
  Risk-free rate (r)  = 0.05
  Dividend yield (d)  = 0.08
  Expiry (T)          = 1.0
  Number of Steps (N) = entered by user at runtime

OUTPUT
------
  After entering the number of steps, the program displays the 
  parameters used and a formatted table with American call and 
  put prices from both trees.

NOTES
-----
  - The CRRBinomialTree class follows the same design pattern as 
    BoyleTrinomialTree (Strategy pattern with TreeProducts)
  - The CRR tree uses the standard Cox-Ross-Rubinstein up/down factors:
      u = exp(sigma * sqrt(dt))
      d = 1 / u
  - Risk-neutral probability is computed inline:
      p = (exp((r-q)*dt) - d) / (u - d)
