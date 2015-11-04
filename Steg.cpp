//
//  Steg.cpp
//  Project 4
//
//  Created by Ronaq Virdi on 3/8/15.
//  Copyright (c) 2015 Ronaq Virdi. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "provided.h"
using namespace std;


bool Steg::hide(const string& hostIn, const string& msg, string& hostOut)
{
    if(hostIn.size() == 0)  // host string is empty
        return false;
    
    vector<string> newLine;  // create a new vector to hold all the sublines
    string substr = "";
    for(int i = 0; i < hostIn.size(); i++)  // loop thru the enitre host in string
    {
        if(hostIn[i] == '\r' || hostIn[i] == '\t' || hostIn[i] == ' ')
            continue;
        else if(hostIn[i] != '\n')  // append the character to the substring
        {
            substr += hostIn[i];
        }
        else if(hostIn[i] == '\n')
        {
            newLine.push_back(substr);  // once you hit the endline, then the substr is full
            substr = "";  // reset substr
        }
    }
    if(substr.size() != 0)  // enables you to get the last substring if the string doesn't end in an endline
    {
        newLine.push_back(substr); // to get the last piece
    }
    
    vector<unsigned short> strToNum;
    Compressor::compress(msg, strToNum);  // returns a vector of numbers

    string y = BinaryConverter::encode(strToNum); // returns a string with tabs and spaces
    

    int L = y.size(); // gives the size of all the tabs and spaces
    int N = newLine.size();  // number of substrings
    int t = L % N;
    int substrCount = 0;
    string tabAndSpaceSubStr = "";
    vector<string>tabAndSpaces;
    for(int i =0; i < y.size(); i++) // loops thru the string of tabs and spaces
    {
        tabAndSpaceSubStr += y[i];  // add each char into a substring
        
        if(tabAndSpaceSubStr.size() == (L/N)+1 && substrCount < t)  // for the first L%N sub strings
        {
            substrCount++;
            tabAndSpaces.push_back(tabAndSpaceSubStr);
            tabAndSpaceSubStr = "";  // reset the substring
        }
        else if(tabAndSpaceSubStr.size() == (L/N) && substrCount >= t)
        {
            substrCount++;
            tabAndSpaces.push_back(tabAndSpaceSubStr);
            tabAndSpaceSubStr = "";  // reset the substring
        }
    }
    if(tabAndSpaceSubStr.size() != 0)  //enables you to get the last substring if the string doesn't end in an endline
    {
        tabAndSpaces.push_back(tabAndSpaceSubStr); // to get the last piece
    }

    string final = ""; // create an empty string
    for(int i = 0; i < tabAndSpaces.size() ; i++)  // loop thru the vector of tabs and spaces
    {
        final += newLine[i]+tabAndSpaces[i]+'\n';  // append the newline stirng, tab and space string, and a newline char
    }
    
    hostOut = final;  // place the final string into hostout
    return true;
}

bool Steg::reveal(const string& hostIn, string& msg)
{
    vector<string> newLine;
    string substr = "";
    for(int i = 0; i < hostIn.size(); i++) // loop thru the host in string
    {
        if(hostIn[i] == '\r')
            continue;
        else if(hostIn[i] != '\n')
        {
            substr += hostIn[i];
        }
        else if(hostIn[i] == '\n')
        {
            newLine.push_back(substr);  // once you hit a newline push that stirng into a vector
            substr = "";  // reset substr
        }
    }
    if(substr.size() != 0)//enables you to get the last substring if the string doesn't end in an endline
    {
        newLine.push_back(substr); // to get the last piece
    }
    
    vector<string> tabsAndSpacesOnly;
    string sub = "";
    for(int i =0; i < newLine.size() ; i++) // loop thru every string in the vector
    {
        string x = newLine[i];
        for(int j = 0; j < x.size(); j++) // loop thru every char is the string
        {
            if(x[j] == ' ' || x[j] == '\t')  // gather all the spaces and tabs
            {
                sub += x[j];  // increment the character onto the substring
            }
        }
        if(sub.size() != 0)
        {
            tabsAndSpacesOnly.push_back(sub);  // push the space and tab string into the vector
            sub = ""; // reset the sub
        }
    }
    
    string p = "";
    for(int i= 0; i < tabsAndSpacesOnly.size(); i++) // loop thru the tabs and spaces vector
    {
        p += tabsAndSpacesOnly[i];   // make a single string with tabs and spaces
    }
    if(p.size() == 0)
        return false;
    vector<unsigned short> nums;
    if(BinaryConverter::decode(p, nums) == false)  // if there are unneccessary tabs and spaces
        return false;
    string final = "";
    if(Compressor::decompress(nums, final) == false) // if there are unneccessary tabs and spaces
        return false;
    
    msg = final;  // store final into msg
    return true;
}

