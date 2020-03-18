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
            SendMessage(
                        const cxstring& dest,
                        const cxstring& text,
                        const cxopt<cxstring> parseMode = cxopt<cxstring>(),
                        const cxopt<bool> noWebPreview = cxopt<bool>(),
                        const cxopt<bool> silent = cxopt<bool>(),
                        const cxopt<int> replyMessageID = cxopt<int>())
                          : Destination(dest), MessageText(text),
                            ParseMode(parseMode),DisableWebPreview(noWebPreview),
                            SilentMessage(silent), ReplyMsgID(replyMessageID) {}
            
            
            SendMessage(const IDType dest, const cxstring& text) : Destination(std::to_string(dest)), MessageText(text) {}
            
            cxstring Destination;
            cxstring MessageText;
            cxopt<cxstring> ParseMode;
            cxopt<bool> DisableWebPreview;
            cxopt<bool> SilentMessage;
            cxopt<int> ReplyMsgID;
            
            cxprops(SendMessage) (
                                  property(Destination, "chat_id"),
                                  property(MessageText, "text"),
                                  property(ParseMode, "parse_mode"),
                                  property(DisableWebPreview, "disable_web_page_preview"),
                                  property(SilentMessage, "disable_notification"),
                                  property(ReplyMsgID, "reply_to_message_id")
            );
        };
    }
}

#endif /* SendMessage_h */
