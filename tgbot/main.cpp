//
//  main.cpp
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "TelegramAPI/User.h"
#include "TelegramAPI/Chats.h"
#include "TelegramAPI/Session.h"
#include "TelegramAPI/GetChat.h"
#include "TelegramAPI/SendMessage.h"

int main(int argc, const char * argv[]) {
    std::cout << "TGBot running" << std::endl;
    tg::Session sess("752829295:AAE2xJz7kTXdde4dbyPdfqW0mDaUWEvh4v8");
    
    try {
        auto chat = sess.Query(tg::Methods::GetChat("@pubgrouptgcx"));
        std::cout << chat.CXToJSON() << std::endl;
        
        while(true)
        {
            cxstring mesg;
            std::getline(std::cin, mesg);
            chat.Send(mesg);
        }
    } catch(tg::ApiException& e)
    {
        std::cerr << "tg::ApiException: " << e.what() << std::endl;
    }
    
    return 0;
}
