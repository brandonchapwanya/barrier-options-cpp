//
//  PayOffConstructible.h
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.

//  Part4_FactoryRegistration
//


#ifndef PayOffConstructible_h
#define PayOffConstructible_h

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include <iostream>
#include "ArgList.h"
#include "BiTAmeriCall.h"
#include "BiTAmeriPut.h"
#include "BiTEuroBarrierCall.h"
#include "BiTEuroBarrierPut.h"
#include "PayOffFactory.h"
#include <string>

template <class T>
class PayOffHelper
{
public:
    PayOffHelper(std::string);
    static T* Create(ArgumentList& args);
};

template <class T>
T* PayOffHelper<T>::Create(ArgumentList& args)
{
    return new T(args);
}

template <class T>
PayOffHelper<T>::PayOffHelper(std::string id)
{
    PayOffFactory<T>& thePayOffFactory = PayOffFactory<T>::Instance();
    thePayOffFactory.RegisterPayOff(id, PayOffHelper<T>::Create);
}

#endif /* PayOffConstructible_h */