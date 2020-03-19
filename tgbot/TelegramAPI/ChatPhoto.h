//
//  ChatPhoto.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/18/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef ChatPhoto_h
#define ChatPhoto_h
#include "Internal.h"

namespace tg
{
    cxclass(ChatPhoto)
    {
    public:
        cxopt<cxstring> Small, SmallUnique;
        cxopt<cxstring> Big, BigUnique;
        
        cxprops(ChatPhoto) (
                            property(Small, "small_file_id"),
                            property(SmallUnique, "small_file_unique_id"),
                            property(Big, "big_file_id"),
                            property(BigUnique, "big_file_unique_id")
                            );
    };
}

#endif /* ChatPhoto_h */
