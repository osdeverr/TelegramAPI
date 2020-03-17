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

const CX::String query = "https://api.telegram.org/bot752829295:AAH0Kn22eUYDPAegXsLc7YmsdUsKaMN6N6M/getChat?chat_id=359969336";
int main(int argc, const char * argv[]) {
    std::cout << "TGBot running" << std::endl;
    tg::Session sess("752829295:AAH0Kn22eUYDPAegXsLc7YmsdUsKaMN6N6M");
    auto chat = sess.Query(tg::Actions::GetChat(359969336));
    std::cout << chat.CXToJSON() << std::endl;
    
    return 0;
}
