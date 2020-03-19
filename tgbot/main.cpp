//
//  main.cpp
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <thread>

#include "TelegramAPI/CXFramework/Query.h"
#include "TelegramAPI/User.h"
#include "TelegramAPI/Chat.h"
#include "TelegramAPI/Session.h"
#include "TelegramAPI/GetChat.h"
#include "TelegramAPI/GetUpdates.h"
#include "TelegramAPI/SendMessage.h"

constexpr char gkBotToken[] = "752829295:AAE2xJz7kTXdde4dbyPdfqW0mDaUWEvh4v8";
int main(int argc, const char * argv[]) {
    std::cout << "TGBot running" << std::endl;
    
    try
    {
        tg::Session& sess = tg::Session::Instance();
        sess.Authorize(gkBotToken);
        auto chat = sess.Query(tg::Methods::GetChat("@pubgrouptgcx"));
        std::cout << chat.CXToJSON() << std::endl;
        std::cout << "TG JSON access: " << std::endl;
        if(chat.PinnedMessage.Exists())
        {
            tg::Message msg = chat.PinnedMessage();
            tg::User user = msg.Sender();
            std::cout << "Pinned message by " << user.FirstName() << " " << user.LastName() << ": " << msg.Text() << std::endl;
        }
        else
            std::cout << "No Pinned Message" << std::endl;
        
        // lp worker
        std::thread t([]() {
            tg::Session& sess = tg::Session::Instance();            
            int64_t lastId = 0;
            while(true)
            {
                auto updates = sess.Query(tg::Methods::GetUpdates(lastId + 1));
                for(auto upd : updates)
                {
                    if(upd.ID() > lastId)
                        lastId = upd.ID();
                    
                    if(upd.MessageUpdate.Exists())
                    {
                        auto mesg = upd.MessageUpdate();
                        if(mesg.Text() == "/help")
                            mesg.Owner().Send("No commands yet -.-");
                    }
                }
            }
        });
        
        while(true)
        {
            cxstring text;
            std::cout << "@" << chat.Username() << ": ";
            std::getline(std::cin, text);
            chat.Send(text);
        }
    } catch(tg::ApiException& e)
    {
        std::cerr << "Caught TGAPI exception - " << e.what() << std::endl; 
    }
    
    return 0;
}
