//
//  GetUpdates.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/19/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef GetUpdates_h
#define GetUpdates_h
#include "Internal.h"
#include "Update.h"

namespace tg
{
    namespace Methods
    {
        cxclass(GetUpdates)
        {
        public:
            TGAPI_METHOD("getUpdates", std::vector<tg::Update>);
            GetUpdates(cxopt<int64_t> lastUpdate = cxopt<int64_t>(),
                       cxopt<int> lptimeout = cxopt<int>(),
                       cxopt<int> maxupd = cxopt<int>()) :
                LastUpdateID(lastUpdate), MaxUpdates(maxupd),
                LongPollTimeout(lptimeout) {}
            
            cxopt<int64_t> LastUpdateID;
            cxopt<int> MaxUpdates;
            cxopt<int> LongPollTimeout;
            
            cxprops(GetUpdates) (
                                 property(LastUpdateID, "offset"),
                                 property(MaxUpdates, "limit"),
                                 property(LongPollTimeout, "timeout")
            );
        };
    };
}

#endif /* GetUpdates_h */
