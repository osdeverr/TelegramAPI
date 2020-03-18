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
#include "CXFramework/Reflection.h"

namespace tg
{
    cxclass(User)
    {
    public:
        cxopt<uint64_t> ID;
        cxopt<bool> IsBot;
        cxopt<cxstring> FirstName;
        
        cxopt<cxstring> LastName;
        cxopt<cxstring> Username;
        cxopt<cxstring> Language;
        cxopt<bool> CanJoinGroups;
        cxopt<bool> CanReadAllMessages;
        cxopt<bool> SupportsInlineQueries;
        
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
