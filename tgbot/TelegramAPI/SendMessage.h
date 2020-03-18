//
//  SendMessage.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/18/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef SendMessage_h
#define SendMessage_h
#include "CXFramework/Object.h"
#include "CXFramework/Reflection.h"
#include "Internal.h"

namespace tg
{
    class Message;
    namespace Methods
    {
        cxclass(SendMessage)
        {
        public:
            TGAPI_METHOD("sendMessage", tg::Message);
            
            SendMessage() {}
            SendMessage(const cxstring& dest, const cxstring& text) : mDestination(dest), mMessageText(text) {}
            SendMessage(const IDType dest, const cxstring& text) : mDestination(std::to_string(dest)), mMessageText(text) {}
            
            cxstring mDestination;
            cxstring mMessageText;
            
            cxprops(SendMessage) (
                                  property(mDestination, "chat_id"),
                                  property(mMessageText, "text")
            );
        };
    }
}

#endif /* SendMessage_h */
