//
//  WebSteg.cpp
//  Project 4
//
//  Created by Ronaq Virdi on 3/9/15.
//  Copyright (c) 2015 Ronaq Virdi. All rights reserved.
//

#include "provided.h"
#include "http.h"
#include <string>
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
    string text;
    if (HTTP().get(url, text) == false) // if the webpage cant be retreieved return false
        return false;
    if(Steg::hide(text, msg, host) == true)
        return true;
    else
        return false;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
    string text;
    if(HTTP().get(url, text) == false) // if the webpage cant be retreieved return false
        return false;
    if(Steg::reveal(text, msg) == true)
        return true;
    else
        return false;
}