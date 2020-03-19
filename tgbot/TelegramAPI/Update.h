//
//  Update.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/19/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Update_h
#define Update_h
#include "Internal.h"
#include "Message.h"

namespace tg
{
    cxclass(Update)
    {
    public:
        cxopt<int> ID;
        cxref<tg::Message> MessageUpdate;
        
        cxprops(Update) (
                         property(ID, "update_id"),
                         property(MessageUpdate, "message")
        );
    };
}

#endif /* Update_h */
