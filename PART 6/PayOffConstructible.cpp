//
//  PayOffConstructible.cpp
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//
//  Part4_FactoryRegistration
//


#include "PayOffConstructible.h"
#include "BiTAmeriCall.h"
#include "BiTAmeriPut.h"
#include "BiTEuroBarrierCall.h"
#include "BiTEuroBarrierPut.h"

namespace {
    PayOffHelper<BiTAmeriCall> RegisterBiTAmeriCall("BiTAmeriCall");
    PayOffHelper<BiTAmeriPut> RegisterBiTAmeriPut("BiTAmeriPut");
    PayOffHelper<BiTEuroBarrierCall> RegisterBiTEuroBarrierCall("BiTEuroBarrierCall");
    PayOffHelper<BiTEuroBarrierPut> RegisterBiTEuroBarrierPut("BiTEuroBarrierPut");
}