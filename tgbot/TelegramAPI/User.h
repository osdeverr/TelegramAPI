//
//  User.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef User_h
#define User_h
#include "../CXFramework/Object.h"
#include "../CXFramework/Properties.h"
#include <stdint.h>

namespace tg
{
    cxclass(User)
    {
    public:
        uint64_t fID;
        bool fIsBot;
        CX::String fFirstName;
        
        CX::String fLastName = "";
        CX::String fUsername = "Unknown";
        CX::String fLanguage = "";
        bool fCanJoinGroups = true;
        bool fCanReadAllMessages = true;
        bool fSupportsInlineQueries = false;
        
        cxprops(User) (
                       property(fID, "id"),
                       property(fIsBot, "is_bot"),
                       property(fFirstName, "first_name"),
                       property(fLastName, "last_name"),
                       property(fUsername, "username"),
                       property(fLanguage, "language_code"),
                       property(fCanJoinGroups, "can_join_groups"),
                       property(fCanReadAllMessages, "can_read_all_group_messages"),
                       property(fSupportsInlineQueries, "supports_inline_queries")
        );
    };
}

#endif /* User_h */
