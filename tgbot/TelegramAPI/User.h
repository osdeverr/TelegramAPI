//
//  User.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef User_h
#define User_h
#include <cstdint>
#include "CXFramework/Object.h"
#include "CXFramework/Properties.h"

namespace tg
{
    cxclass(User)
    {
    public:
        uint64_t ID;
        bool IsBot;
        cxstring FirstName;
        
        cxstring LastName = "";
        cxstring Username = "Unknown";
        cxstring Language = "";
        bool CanJoinGroups = true;
        bool CanReadAllMessages = true;
        bool SupportsInlineQueries = false;
        
        cxprops(User) (
                       property(ID, "id"),
                       property(IsBot, "is_bot"),
                       property(FirstName, "first_name"),
                       property(LastName, "last_name"),
                       property(Username, "username"),
                       property(Language, "language_code"),
                       property(CanJoinGroups, "can_join_groups"),
                       property(CanReadAllMessages, "can_read_all_group_messages"),
                       property(SupportsInlineQueries, "supports_inline_queries")
        );
    };
}

#endif /* User_h */
