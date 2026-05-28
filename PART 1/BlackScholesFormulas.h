//
//  BlackScholesFormulas.hpp
//  ch8_trees
//
//  Created by Steve Yang on 10/12/21.
//

#ifndef BlackScholesFormulas_hpp
#define BlackScholesFormulas_hpp

double BlackScholesCall( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);


double BlackScholesPut( double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry);

double BlackScholesDigitalCall(double Spot,
                               double Strike,
                               double r,
                               double d,
                               double Vol,
                               double Expiry);


double BlackScholesCallVega( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);


#endif /* BlackScholesFormulas_hpp */
