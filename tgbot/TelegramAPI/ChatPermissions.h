//
//  ChatPermissions.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/18/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef ChatPermissions_h
#define ChatPermissions_h
#include "Internal.h"

namespace tg
{
    cxclass(ChatPermissions)
    {
    public:
        TGAPI_CLASS;
        cxopt<bool> CanSendMessages;
        cxopt<bool> CanSendMedia;
        cxopt<bool> CanSendPolls;
        cxopt<bool> CanSendOther;
        cxopt<bool> CanAddWebPreviews;
        cxopt<bool> CanEditChat;
        cxopt<bool> CanInviteUsers;
        cxopt<bool> CanPinMessages;
        
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
}

#endif /* ChatPermissions_h */
