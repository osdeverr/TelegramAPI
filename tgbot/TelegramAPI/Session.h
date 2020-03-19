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
        static Session& Instance()
        {
            static Session inst;
            return inst;
        }
        void Authorize(const cxstring& token)
        {
            mToken = token;
        }
        
        template<class QueryType>
        const typename QueryType::_ReturnClass Query(QueryType q)
        {
            cxstring params = q.CXToJSON();
            std::stringstream ssquery;
            ssquery << "https://api.telegram.org/bot";
            ssquery << mToken << "/" << QueryType::_ApiFunction;
            cxstring query = ssquery.str();
            cxstring result = TGApiCall(query, params);
            
            auto response = ApiResponse<typename QueryType::_ReturnClass>::CXFromJSON(result);
            if(response.ok())
                return response.get();
            else
                throw ApiException(response.errcode(), response.errdesc());
        }
    private:
        Session()
        {
            cURLpp::initialize();
        }
        ~Session()
        {
            cURLpp::terminate();
        }
        const cxstring TGApiCall(const cxstring& query, const cxstring& params)
        {
            cURLpp::Easy hEasy;
            std::stringstream result;
            
            hEasy.setOpt(new cURLpp::Options::Url(query));
            //hEasy.setOpt(new cURLpp::Options::Proxy("http://91.214.179.24:8080"));
            //hEasy.setOpt(new cURLpp::Options::ProxyType(CURLPROXY_SOCKS5));
            std::list<std::string> header;
            header.push_back("Content-Type: application/json");
            
            hEasy.setOpt(new curlpp::options::HttpHeader(header));
            hEasy.setOpt(new cURLpp::Options::Post(true));
            hEasy.setOpt(new cURLpp::Options::WriteStream(&result));
            hEasy.setOpt(new cURLpp::Options::PostFields(params));
            hEasy.setOpt(new cURLpp::Options::PostFieldSize(params.size()));
            hEasy.perform();
            
            return result.str();
        }
        cxstring mToken;
    };
}

#endif /* Auth_h */
