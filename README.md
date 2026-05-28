# Barrier Options Pricer & Design Patterns — C++/QuantLib

**Course:** FE545 Design Patterns for Derivative Pricing | Stevens Institute of Technology | Spring 2026  
**Author:** Brandon Tanaka Chapwanya (Individual Project)

> Academic project completed at Stevens Institute of Technology. All work is original. Do not submit as your own.

---

## Overview

This project implements a C++ options pricing library for American and European knock-out 
barrier options using the Cox-Ross-Rubinstein (CRR) binomial tree model, following 
production software design patterns — Factory (Singleton), Observer/Observable — 
integrated with QuantLib and boost::shared_ptr memory management.

**Core finding:** European knock-out barrier options are always worth less than equivalent 
American options. The barrier condition eliminates value at nodes where S(i,j) ≥ B, 
reducing the option's expected payoff under the risk-neutral measure.

**Correct output (N=100):**
- American Call: 4.004509
- American Put: 8.078126
- European Knock-out Barrier Call: < American Call
- European Knock-out Barrier Put: < American Put

---

## Model

### CRR Binomial Tree
- Up factor: u = exp(σ√Δt)
- Down factor: d = exp(−σ√Δt)
- Risk-neutral probability: p = (exp((r−q)Δt) − d) / (u − d)

### American Options
Early exercise at every node:

V(i,j) = max(intrinsic value, e^(−rΔt)[p·V(i+1,j+1) + (1−p)·V(i+1,j)])

### European Knock-out Barrier Options
Knocked out immediately if S(i,j) ≥ B:

V(i,j) = 0                                           if S(i,j) ≥ B
V(i,j) = e^(−rΔt)[p·V(i+1,j+1) + (1−p)·V(i+1,j)]   otherwise
---

## Parameters

| Parameter | Value |
|---|---|
| Initial Stock Price S₀ | 50 |
| Strike Price K | 50 |
| Barrier Level B | 70 |
| Volatility σ | 0.30 |
| Risk-Free Rate r | 0.05 |
| Dividend Yield q | 0.08 |
| Steps N | 50, 100, 200, 400 |

---

## Project Structure

### Part 1 — CRR Binomial Tree
Implements `CRRBinomialTree` class following the same design pattern as the provided 
`BoyleTrinomialTree` class. Prices American call and put options via backward induction 
with early exercise comparison at every node.

### Part 2 — European Knock-out Barrier Options
Implements `TreeEuropeanBarrier` class derived from `TreeProducts` base class — same 
pattern as `TreeAmerican`. Incorporates barrier knock-out condition at every node 
during backward induction.

### Part 3 — Convergence Analysis
Prices American call and European knock-out barrier call across N = 50, 100, 200, 400 
steps. Demonstrates:
- Both option types converge as N increases
- Barrier option prices below American option at every step count
- Knock-out premium erosion quantified across step sizes

### Part 4 — Factory Pattern (Singleton)
`PayOffFactory` class registers four product IDs:
- `BiTAmeriCall` — CRR Binomial Tree American Call
- `BiTAmeriPut` — CRR Binomial Tree American Put
- `BiTEuroBarrierCall` — European Knock-out Barrier Call
- `BiTEuroBarrierPut` — European Knock-out Barrier Put

Uses `ArgumentList` class for parameter passing and `PayOffConstructible` for 
class registration and object creation.

### Part 5 — Observer/Observable Pattern
- `TreeObservable` — extends QuantLib `Observable` base class
- `OptionPricingReportWriter` — implements QuantLib `Observer` abstract class
- Report format: `Source(10chars) - Timestamp(10chars): Message`

### Part 6 — Full Pricing Report
Integrates all components. Creates `OptionPricingReportWriter` instance, registers 
all four option pricing objects, prices across N = 50, 100, 200, 400 steps, 
reports through observer with pricer class ID, timestamp, and option value.
Uses `boost::shared_ptr` throughout.

---

## Contents

| File/Folder | Description |
|---|---|
| `Part1/` | CRRBinomialTree class — American options |
| `Part2/` | TreeEuropeanBarrier class — knock-out barrier options |
| `Part3/` | Convergence analysis across N = 50, 100, 200, 400 |
| `Part4/` | Factory pattern — PayOffFactory singleton |
| `Part5/` | Observer/Observable pattern — pricing report writer |
| `Part6/` | Full integration — all four pricers + report writer |
| `FE545_Project_Report_Chapwanya.pdf` | Full project report with results |
| `Output_Screenshots.pdf` | Program output and code screenshots |

---

## How to Build

```bash
# Requires: C++ compiler (C++14), QuantLib, Boost

# Example for Part 1
g++ -std=c++14 -o pricer main.cpp BinomialTree.cpp CRRBinomialTree.cpp \
    -lQuantLib -lboost_system

./pricer
```

---

## Sample Output (Part 6, N=100)
BiTAmeriCall  - 2026-05-28: American Call Price  (N=100): 4.004509
BiTAmeriPut   - 2026-05-28: American Put Price   (N=100): 8.078126
BiTEuroBarrierCall - 2026-05-28: Barrier Call    (N=100): 2.891243
BiTEuroBarrierPut  - 2026-05-28: Barrier Put     (N=100): 4.762198
---

## Concepts Demonstrated

- CRR binomial tree construction and backward induction
- American option early exercise premium
- European knock-out barrier option pricing and path dependence
- Factory design pattern with Singleton registration
- Observer/Observable pattern for event-driven pricing reports
- QuantLib Observable and Observer base class integration
- boost::shared_ptr memory management
- Convergence analysis across N = 50, 100, 200, 400 steps
