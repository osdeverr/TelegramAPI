//
//  main.cpp
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "TelegramAPI/User.h"
#include "TelegramAPI/Chat.h"
#include "TelegramAPI/Session.h"
#include "TelegramAPI/GetChat.h"
#include "TelegramAPI/SendMessage.h"

constexpr char gkBotToken[] = "752829295:AAE2xJz7kTXdde4dbyPdfqW0mDaUWEvh4v8";
int main(int argc, const char * argv[]) {
    std::cout << "TGBot running" << std::endl;
    
    try {
        tg::Session sess(gkBotToken);
        auto chat = sess.Query(tg::Methods::GetChat("@pubgrouptgcx"));
        std::cout << chat.CXToJSON() << std::endl;
        std::cout << "TG JSON access: " << std::endl;
        if(chat.PinnedMessage.Exists())
        {
            tg::Message msg = chat.PinnedMessage();
            std::cout << "Pinned message by " << msg.Sender().FirstName() << " " << msg.Sender().LastName() << ": " << msg.Text() << std::endl;
        }
        else
            std::cout << "No Pinned Message" << std::endl;
        
        while(true)
        {
            cxstring mesg;
            std::cout << "@" << (cxstring) chat.Username << " > ";
            std::getline(std::cin, mesg);
            std::cout << chat.Send(mesg).CXToJSON() << std::endl;
        }
    } catch(std::exception& e)
    {
        std::cerr << "Caught exception - " << e.what() << std::endl;
    }
    
    return 0;
}
