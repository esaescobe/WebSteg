//
//  BinaryConverter.cpp
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


const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string numberToBit = "";
    string bitToTabsAndSpaces = "";
    for(int i=0; i < numbers.size(); i++)   // loop thru the numbers vector
    {
        numberToBit = convertNumberToBitString(numbers[i]);  // store the bit string into numberToBit
        for(int k=0; k < numberToBit.size();k++)  // loop thru the numberToBit string
        {
            if(numberToBit[k] == '1')
            {
                bitToTabsAndSpaces += '\t';  // append a tab to the string
            }
            else if(numberToBit[k] == '0')
            {
                bitToTabsAndSpaces+= ' ';   // append a space to the string
            }
        }
    }
    
    return bitToTabsAndSpaces;  // return a string with all tabs and spaces
}

bool BinaryConverter::decode(const string& bitString,
                             vector<unsigned short>& numbers)
{
    if(bitString.size() % 16 != 0)  // if the bit string is not a multiple of 16
        return false;
    for(int k = 0; k < bitString.size(); k++)  // loop thru the entire bit string
    {
        if(bitString[k] == '\t' || bitString[k] == ' ')   // if there is a character other than a tab or space return false
            continue;
        else
            return false;
    }
    
    for(int j = 0; j < numbers.size() ; j++)  // loop thru the numbers vector
    {
        numbers.erase(numbers.begin()+ j);  // erase everything in the vector
        j--;
    }
    
    string tabsAndSpaces = "";
    string characToBin = "";
    for(int i =0 ; i < bitString.size() ; i++)  // loop thru the bit string
    {
        if(bitString[i] == ' ')
            characToBin += '0';  // append a 0 to represent a space
        else if(bitString[i] == '\t')
            characToBin += '1';  // append a 1 to represent a spcae
        if(characToBin.size() == 16)
        {
            unsigned short value;
            if(convertBitStringToNumber(characToBin, value)) // converts the 16 bit string to a number stored in num
            {
                numbers.push_back(value);  // push the converted number to the vector
            }
            characToBin = "";  // reset the string
        }
    }
    return true;  // This compiles, but may not be correct
}

string convertNumberToBitString(unsigned short number)
{
    string result(BITS_PER_UNSIGNED_SHORT, '0');
    for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
    {
        k--;
        if (number % 2 == 1)
            result[k] = '1';
    }
    return result;
    
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
    if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
        return false;
    number = 0;
    for (size_t k = 0; k < bitString.size(); k++)
    {
        number *= 2;
        if (bitString[k] == '1')
            number++;
        else if (bitString[k] != '0')
            return false;
    }
    return true;
}

