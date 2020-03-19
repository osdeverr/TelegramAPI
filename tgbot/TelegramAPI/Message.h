//
//  Message.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/18/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Message_h
#define Message_h
#include "Internal.h"
#include <ctime>
#include <vector>

namespace tg
{
    class Chat; class User;
    cxclass(MessageEntity)
    {
    public:
        cxopt<cxstring> Type;
        cxopt<int> Offset;
        cxopt<int> Length;
        
        cxopt<cxstring> LinkURL;
        cxopt<User> MentionedUser;
        cxopt<cxstring> CodeLanguage;
        
        cxprops(MessageEntity) (
                                property(Type, "type"),
                                property(Offset, "offset"),
                                property(Length, "length"),
                                property(LinkURL, "url"),
                                property(MentionedUser, "user"),
                                property(CodeLanguage, "language")
        );
    };
    
    cxclass(Message)
    {
    public:
        cxopt<int> ID;
        cxopt<time_t> Date;
        cxref<Chat> Owner;
        
        cxopt<User> Sender;
        cxref<Chat> FwdOriginalChat;
        cxref<Message> FwdOriginalMessage;
        cxopt<User> FwdOriginalPoster;
        cxopt<int> FwdOriginalMessageID;
        cxopt<cxstring> FwdOriginalAuthorSig;
        cxopt<cxstring> FwdOriginalAuthorName;
        cxopt<time_t> FwdDate;
        
        cxopt<time_t> EditDate;
        cxopt<cxstring> MediaGroupID;
        cxopt<cxstring> AuthorSignature;
        
        cxopt<cxstring> Text;
        
        cxopt<std::vector<MessageEntity>> Entities;
        cxopt<std::vector<MessageEntity>> CaptionEntities;
        
        cxprops(Message) (
                          property(Text, "text"),
                          property(Sender, "from"),
                          property(Date, "date"),
                          property(Owner, "chat"),
                          property(FwdOriginalChat, "forward_from_chat"),
                          property(FwdOriginalMessage, "reply_to_message"),
                          property(FwdOriginalPoster, "forward_from"),
                          property(FwdOriginalMessageID, "forward_from_message_id"),
                          property(FwdOriginalAuthorSig, "forward_signature"),
                          property(FwdOriginalAuthorName, "forward_sender_name"),
                          property(FwdDate, "forward_date"),
                          property(EditDate, "edit_date"),
                          property(MediaGroupID, "media_group_id"),
                          property(AuthorSignature, "author_signature"),
                          property(Entities, "entities"),
                          property(CaptionEntities, "caption_entities")
        );
    };
}

#endif /* Message_h */
