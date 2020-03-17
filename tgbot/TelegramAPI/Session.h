//
//  Auth.h
//  tgbot
//
//  Created by Nikita Ivanov on 3/17/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Auth_h
#define Auth_h
#include <exception>
#include <string>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "CXFramework/Object.h"
#include "ApiResponse.h"

namespace tg
{
    cxclass(ApiException) extends(std::exception)
    {
    public:
        ApiException(const int errcode, const cxstring& errdesc)
        {
            std::stringstream s;
            s << "TGAPI Error " << errcode << ": " << errdesc;
            mError = s.str();
        }
        const char* what() { return mError.c_str(); }
    private:
        cxstring mError;
    };
    
    // ONE PER APP: make it CRYSTAL CLEAR
    cxclass(Session)
    {
    public:
        Session(const cxstring& token) : mToken(token)
        {
            cURLpp::initialize();
        }
        ~Session()
        {
            cURLpp::terminate();
        }
        
        template<class QueryType>
        const typename QueryType::_ReturnClass Query(QueryType q)
        {
            cURLpp::Easy hEasy;
            std::stringstream result;
            std::stringstream query;
            cxstring params = q.CXToJSON();
            query << "https://api.telegram.org/bot";
            query << mToken << "/" << QueryType::_ApiFunction;
            cxstring sQuery = query.str();
            
            hEasy.setOpt(new cURLpp::Options::Url(sQuery));
            hEasy.setOpt(new cURLpp::Options::Proxy("http://64.225.25.221:1080"));
            std::list<std::string> header;
            header.push_back("Content-Type: application/json");
            
            hEasy.setOpt(new curlpp::options::HttpHeader(header));
            hEasy.setOpt(new cURLpp::Options::Post(true));
            hEasy.setOpt(new cURLpp::Options::Verbose(true));
            hEasy.setOpt(new cURLpp::Options::WriteStream(&result));
            hEasy.setOpt(new cURLpp::Options::PostFields(params));
            hEasy.setOpt(new cURLpp::Options::PostFieldSize(params.size()));
            hEasy.perform();
            
            auto response = ApiResponse<typename QueryType::_ReturnClass>::CXFromJSON(result.str());
            if(response.ok())
                return response.get();
            else
                throw ApiException(response.errcode(), response.errdesc() + params);
        }
    private:
        cxstring mToken;
    };
}

#endif /* Auth_h */
