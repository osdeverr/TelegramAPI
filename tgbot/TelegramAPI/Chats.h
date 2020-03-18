//
//  Chat.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Chat_h
#define Chat_h
#include <cstdint>
#include <ctime>
#include <vector>
#include "CXFramework/Object.h"
#include "CXFramework/Reflection.h"
#include "Internal.h"
#include "User.h"
#include "Session.h"
#include "SendMessage.h"

namespace tg
{
    cxclass(ChatPhoto)
    {
    public:
        TGAPI_CLASS;
        cxstring Small, SmallUnique;
        cxstring Big, BigUnique;
        
        cxprops(ChatPhoto) (
                            property(Small, "small_file_id"),
                            property(SmallUnique, "small_file_unique_id"),
                            property(Big, "big_file_id"),
                            property(BigUnique, "big_file_unique_id")
        );
    };
    cxclass(ChatPermissions)
    {
    public:
        TGAPI_CLASS;
        bool CanSendMessages = false;
        bool CanSendMedia = false;
        bool CanSendPolls = false;
        bool CanSendOther = false;
        bool CanAddWebPreviews = false;
        bool CanEditChat = false;
        bool CanInviteUsers = false;
        bool CanPinMessages = false;
        
        cxprops(ChatPermissions) (
                                  property(CanSendMessages, "can_send_messages"),
                                  property(CanSendMedia, "can_send_media_messages"),
                                  property(CanSendPolls, "can_send_polls"),
                                  property(CanSendOther, "can_send_other_messages"),
                                  property(CanAddWebPreviews, "can_add_web_page_previews"),
                                  property(CanEditChat, "can_change_info"),
                                  property(CanInviteUsers, "can_invite_users"),
                                  property(CanPinMessages, "can_pin_messages")
        );
    };
    
    cxclass(MessageEntity)
    {
    public:
        TGAPI_CLASS;
        cxstring Type;
        int Offset;
        int Length;
        
        cxstring LinkURL;
        User MentionedUser;
        cxstring CodeLanguage;
        
        cxprops(MessageEntity) (
                                property(Type, "type"),
                                property(Offset, "offset"),
                                property(Length, "length"),
                                property(LinkURL, "url"),
                                property(MentionedUser, "user"),
                                property(CodeLanguage, "language")
        );
    };
    
    class Chat;
    cxclass(Message)
    {
    public:
        TGAPI_CLASS;
        int ID;
        User Sender;
        time_t Date;
        cxref<Chat> Owner;
        
        cxref<Chat> FwdOriginalChat;
        cxref<Message> FwdOriginalMessage;
        User FwdOriginalPoster;
        int FwdOriginalMessageID;
        cxstring FwdOriginalAuthorSig;
        cxstring FwdOriginalAuthorName;
        time_t FwdDate;
        
        time_t EditDate;
        cxstring MediaGroupID;
        cxstring AuthorSignature;
        
        cxstring Text;
        
        std::vector<MessageEntity> Entities;
        std::vector<MessageEntity> CaptionEntities;
        
        cxprops(Message) (
                          property(Text, "text"),
                          property(Sender, "from")
        );
    };
    
    cxclass(Chat)
    {
    public:
        TGAPI_CLASS;        
        IDType ID;
        cxstring Type;
        cxstring Title;
        cxstring Username;
        cxstring FirstName;
        cxstring LastName;
        ChatPhoto Photo;
        cxstring Description;
        cxstring InviteLink;
        
        cxref<Message> PinnedMessage;
        ChatPermissions Permissions;
        int SlowModeDelay = 0;
        cxstring StickerSetName = "";
        bool CanChangeStickerSet = false;
        
        const Message Send(const cxstring& message)
        {
            return _pSession->Query(Methods::SendMessage(ID, message));
        }
        
        cxprops(Chat) (
                       property(ID, "id"),
                       property(Type, "type"),
                       property(Title, "title"),
                       property(Username, "username"),
                       property(FirstName, "first_name"),
                       property(LastName, "last_name"),
                       property(Photo, "photo"),
                       property(Description, "description"),
                       property(InviteLink, "invite_link"),
                       property(PinnedMessage, "pinned_message"),
                       property(Permissions, "permissions"),
                       property(SlowModeDelay, "slow_mode_delay"),
                       property(StickerSetName, "sticker_set_name"),
                       property(CanChangeStickerSet, "can_set_sticker_set")
        );
    };
}

#endif /* Chat_h */
