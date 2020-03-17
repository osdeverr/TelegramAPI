//
//  GetChat.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef GetChat_h
#define GetChat_h
#include "CXFramework/Object.h"
#include "CXFramework/Properties.h"
#include "Chats.h"

namespace tg
{
    namespace Actions
    {
        cxclass(GetChat)
        {
        public:
            static constexpr char _ApiFunction[] = "getChat";
            typedef tg::Chat _ReturnClass;
            GetChat() {}
            GetChat(const cxstring& chatUsername)
            {
                if(chatUsername[0] != '@')
                    ChatID = "@" + chatUsername;
                else
                    ChatID = chatUsername;
            }
            GetChat(const int64_t numID)
            {
                ChatID = std::to_string(numID);
            }
            cxstring ChatID;
            
            cxprops(GetChat) (
                property(ChatID, "chat_id")
            );
        };
    }
}

#endif /* GetChat_h */
