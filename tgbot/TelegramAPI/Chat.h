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
#include "Internal.h"
#include "User.h"
#include "Session.h"
#include "SendMessage.h"
#include "ChatPhoto.h"
#include "ChatPermissions.h"
#include "Message.h"

namespace tg
{
    cxclass(Chat)
    {
    public:
        cxopt<IDType> ID;
        cxopt<cxstring> Type;
        cxopt<cxstring> Title;
        cxopt<cxstring> Username;
        cxopt<cxstring> FirstName;
        cxopt<cxstring> LastName;
        cxopt<ChatPhoto> Photo;
        cxopt<cxstring> Description;
        cxopt<cxstring> InviteLink;
        
        cxref<Message> PinnedMessage;
        cxopt<ChatPermissions> Permissions;
        cxopt<int> SlowModeDelay;
        cxopt<cxstring> StickerSetName;
        cxopt<bool> CanChangeStickerSet;
        
        const Message Send(const cxstring& message)
        {
            return Session::Instance().Query(Methods::SendMessage(ID, message));
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
