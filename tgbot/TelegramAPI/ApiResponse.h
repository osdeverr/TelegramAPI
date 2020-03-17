//
//  APIResponse.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef APIResponse_h
#define APIResponse_h
#include "CXFramework/Object.h"
#include "CXFramework/Properties.h"

namespace tg
{
    cxclass_templated(ApiResponse, template<class T>)
    {
    public:
        bool IsOkay;
        T Result;
        
        int ErrorCode = 200;
        cxstring ErrorDesc = "OK";
        
        const bool ok() const { return IsOkay; }
        const T& get() const { return Result; }
        
        const int errcode() const { return ErrorCode; }
        const cxstring& errdesc() const { return ErrorDesc; }
        
        cxprops(ApiResponse) (
                              property(IsOkay, "ok"),
                              property(Result, "result"),
                              property(ErrorCode, "error_code"),
                              property(ErrorDesc, "description")
        );
    };
}

#endif /* APIResponse_h */
