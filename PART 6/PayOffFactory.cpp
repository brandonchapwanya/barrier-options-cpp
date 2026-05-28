//
//  PayOffFactory.cpp
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//  Modified by Steve Yang on 04/21/22
//
//  Part4_FactoryRegistration
//

#ifndef PayOffFactory_h
#define PayOffFactory_h

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include "ArgList.h"
#include <map>
#include <string>

template <class T>
class PayOffFactory
{
public:
    typedef T* (*CreatePayOffFunction)(ArgumentList& args);
    
    static PayOffFactory& Instance();
    void RegisterPayOff(std::string, CreatePayOffFunction);
    T* CreatePayOff(std::string PayOffID, ArgumentList& args);
    ~PayOffFactory(){};
    
private:
    std::map<std::string, CreatePayOffFunction> TheCreatorFunctions;
    PayOffFactory(){}
    PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator = (const PayOffFactory&){ return *this; }
};

template <class T>
void PayOffFactory<T>::RegisterPayOff(std::string PayOffId, CreatePayOffFunction CreatorFunction)
{
    TheCreatorFunctions.insert(std::pair<std::string, CreatePayOffFunction>(PayOffId, CreatorFunction));
}

template <class T>
T* PayOffFactory<T>::CreatePayOff(std::string PayOffId, ArgumentList& args)
{
    typename std::map<std::string, CreatePayOffFunction>::const_iterator i = TheCreatorFunctions.find(PayOffId);
    
    if (i == TheCreatorFunctions.end())
    {
        std::cout << PayOffId << " is an unknown payoff" << std::endl;
        return NULL;
    }
    
    return (i->second)(args);
}

template <class T>
PayOffFactory<T>& PayOffFactory<T>::Instance()
{
    static PayOffFactory theFactory;
    return theFactory;
}

#endif /* PayOffFactory_h */