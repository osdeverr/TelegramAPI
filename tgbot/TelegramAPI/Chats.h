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
#include "CXFramework/Object.h"
#include "CXFramework/Properties.h"

namespace tg
{
    cxclass(ChatPhoto)
    {
    public:
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
    
    // implement messages..
    
    cxclass(Chat)
    {
    public:
        int64_t ID;
        cxstring Type;
        cxstring Title;
        cxstring Username;
        cxstring FirstName;
        cxstring LastName;
        ChatPhoto Photo;
        cxstring Description;
        cxstring InviteLink;
        
        // TODO
        // Message Pinned;
        ChatPermissions Permissions;
        int SlowModeDelay = 0;
        cxstring StickerSetName = "";
        bool CanChangeStickerSet = false;
        
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
                       // message prop here
                       property(Permissions, "permissions"),
                       property(SlowModeDelay, "slow_mode_delay"),
                       property(StickerSetName, "sticker_set_name"),
                       property(CanChangeStickerSet, "can_set_sticker_set")
        );
    };
}

#endif /* Chat_h */
