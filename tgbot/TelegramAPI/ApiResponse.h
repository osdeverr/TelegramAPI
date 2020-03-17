//
//  APIResponse.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef APIResponse_h
#define APIResponse_h
#include "../CXFramework/Object.h"
#include "../CXFramework/Properties.h"

namespace tg
{
    cxclass_templated(ApiResponse, template<class T>)
    {
    public:
        bool fOkay;
        T fResult;
        
        int fErrorCode = 200;
        CX::String fErrorDesc = "OK";
        
        const bool ok() const { return fOkay; }
        const T& get() const { return fResult; }
        
        const int errcode() const { return fErrorCode; }
        const CX::String& errdesc() const { return fErrorDesc; }
        
        cxprops(ApiResponse) (
                              property(fOkay, "ok"),
                              property(fResult, "result"),
                              property(fErrorCode, "error_code"),
                              property(fErrorDesc, "description")
        );
    };
}

#endif /* APIResponse_h */
