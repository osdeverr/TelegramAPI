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
#include "CXFramework/Reflection.h"
#include "Internal.h"

namespace tg
{
    class Chat;
    namespace Methods
    {
        cxclass(GetChat)
        {
        public:
            TGAPI_METHOD("getChat", tg::Chat);
            GetChat() {}
            GetChat(const cxstring& chatUsername)
            {
                if(chatUsername[0] != '@')
                    ChatID = "@" + chatUsername;
                else
                    ChatID = chatUsername;
            }
            GetChat(const IDType numID)
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
