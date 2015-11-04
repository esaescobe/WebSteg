//
//  Compressor.cpp
//  Project 4
//
//  Created by Ronaq Virdi on 3/8/15.
//  Copyright (c) 2015 Ronaq Virdi. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include "HashTable.h" // mine
#include <iostream>
#include "provided.h"
using namespace std;

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
    unsigned long cap = (s.size()/2) + 512;  // set the capactity
    if(cap > 16384)
    {
        cap = 16384;
    }
    unsigned long buckets = cap / (.5);  // use the load formula to set the bucket number

    HashTable<string, unsigned short> H(buckets,cap); // create the table
    for(int j = 0; j < 256 ; j++)
    {
        string st(1, static_cast<char>(j));  // create a one character string
        H.set(st, j,true);  //set all 256 values in the hash table
    }
    
    unsigned short nextFreeID = 256;
    string runSoFar = "";
    vector<unsigned short> V;  // create a vector for the compressed result
    for(int c = 0; c < s.size(); c++)  // loop thru the input string
    {
        string expandedRun = runSoFar + s[c];
        unsigned short value;
        if(H.get(expandedRun, value) == true)
        {
            runSoFar = expandedRun;
            continue;
        }
        else
        {
            unsigned short x;
            H.get(runSoFar,x); // the short value is placed in x
            V.push_back(x);
            H.touch(runSoFar);
            runSoFar = "";
            unsigned short cv;
            string nw(1, static_cast<char>(s[c])); // create a 1 character string
            H.get(nw,cv);  // get the value at the string
            V.push_back(cv); // push the value
            if(H.isFull() == false)
            {
                H.set(expandedRun,nextFreeID);
                nextFreeID++;
            }
            else  // if the table is full, you need to discard the least recently added item
            {
                unsigned short valueOfDiscard;
                string stringofDiscard;
                H.discard(stringofDiscard, valueOfDiscard);
                H.set(expandedRun,valueOfDiscard);
            }
        }
    }
    if(runSoFar.size() != 0)  // push the value of the remaining string
    {
        unsigned short x;
        H.get(runSoFar, x);
        V.push_back(x);
    }
    V.push_back(cap);  // add the capacity of the hashtable
    
    numbers = V;  // set the numbers vector to V

}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
    unsigned long m_cap = numbers[numbers.size() - 1]; // capacity is equal to the last value in the input vector
    unsigned long m_buckets = m_cap / (.5);  // use load factor to calculate the number buckets
    
    HashTable<unsigned short, string> H(m_buckets,m_cap);  // create the hashtable
    for(int j = 0; j < 256 ; j++)
    {
        string st(1, static_cast<char>(j));
        H.set(j, st ,true);
    }
    unsigned short nextFreeID = 256;
    string runSoFar= "";  // ititialize the strings
    string output = "";
    for(int i = 0; i < numbers.size()-1; i++)  // loop thru the vector
    {
        unsigned short us = numbers[i];
        if(us <= 255)
        {
            string x;
            H.get(us,x);  // get the value in x
            output += x;  // append the value onto the output string
            if(runSoFar.size()== 0)  // if the runSoFar is empty
            {
                // if the string is empty simply append the value to the string
                runSoFar+= x;
                continue;
            }
            else
            {
            // if the size of runSoFar is not 0
                string expandedRun = runSoFar + x;
                if(H.isFull() == false)
                {
                    // if the hashtable is not full, set the next association in the table
                    string p;
                    H.set(nextFreeID, expandedRun);
                    nextFreeID++;
                }
                else
                {
                    // if the hashtable is full, u need to discard the least recently added item
                    unsigned short discardshortval;
                    string discardstr;
                    H.discard(discardshortval, discardstr);
                    // set the new associaton into the hashtable
                    H.set(discardshortval, expandedRun);
                    
                }
                runSoFar = "";
                continue;
            }
        }
        else  // if the value of us is greater than 255
        {
            string y;
            if(H.get(us, y) ==false)
            {
                return false;
            }
            else
            {
                // otherwise bring the value of us to the top of the hashtable
                H.touch(us);
                output += y;
                runSoFar = y;
                continue;
            }
        }
    }
    s = output;   // place the output string into s 
    return true;
}

unsigned int computeHash(string s){
    int hash = 0;
    for( size_t i = 0; i < s.size(); i++)
    {
        hash = hash * 139 + s[i];  // use a prime number for the hash
    }
    
    return hash;
}

unsigned int computeHash(unsigned short s){
    return s;
}
