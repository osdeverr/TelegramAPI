//
//  MethodsInternal.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/18/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef MethodsInternal_h
#define MethodsInternal_h
#include "CXFramework/Object.h"
#include "CXFramework/Reflection.h"

namespace tg {
    class Session;
    typedef uint64_t IDType;
}
#define TGAPI_METHOD(funcname, returntype) static constexpr char _ApiFunction[] = funcname; typedef returntype _ReturnClass;

#endif /* MethodsInternal_h */
