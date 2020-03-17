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
#include "TelegramAPI/ApiResponse.h"

const CX::String query = "https://api.telegram.org/bot742829295:AAH0Kn22eUYDPAegXsLc7YmsdUsKaMN6N6M/getMe";

int main(int argc, const char * argv[]) {
    std::cout << "TGBot running" << std::endl;
    cURLpp::initialize();
    cURLpp::Easy hEasy;
    std::stringstream result;
    hEasy.setOpt(cURLpp::Options::Url(query));
    hEasy.setOpt(cURLpp::Options::Proxy("http://143.0.111.138:3128"));
    hEasy.setOpt(cURLpp::Options::WriteStream(&result));
    std::cout << "TGBot performing" << std::endl;
    hEasy.perform();
    
    auto res = tg::ApiResponse<tg::User>::CXFromJSON(result.str());
    if(res.ok())
        std::cout << res.get().CXToJSON() << std::endl;
    else
        std::cout << "TGAPI request failed: " << res.errcode() << " " << res.errdesc() << std::endl;
    
    cURLpp::terminate();
    
    return 0;
}
