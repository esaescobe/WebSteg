//
//  main.cpp
//  Project 4
//
//  Created by Ronaq Virdi on 3/5/15.
//  Copyright (c) 2015 Ronaq Virdi. All rights reserved.
//
//

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "HashTable.h"  // mine
#include "provided.h"
#include "http.h"
using namespace std;


int main(){
    
//    string pageText =
//    "<html>\n"
//    "<head>\n"
//    " <title>My Pretend Web Page</title>\n"
//    "</head>\n"
//    "<body>\n"
//    "<h2>My Pretend Web Page<h1>\n"
//    "<p>\n"
//    "I wish I were creative enough to have something interesting \n"
//    "to say here.  I'm not, though, so this is a boring page.\n"
//    "</p>\n"
//    "<p>\n"
//    "Oh, well.\n"
//    "</p>\n"
//    "</body>\n"
//    "</html>\n"
//    ;
//    HTTP().set("http://boring.com", pageText);
//    string plan =
//    "Lefty and Mugsy enter the bank by the back door.\n"
//    "Shorty waits out front in the getaway car.\n"
//    "Don't let the teller trip the silent alarm.\n"
//    ;
//    if ( ! WebSteg::hideMessageInPage("http://boring.com", plan, pageText))
//    {
//        cout << "Error hiding!" << endl;
//        return 1;
//    }
//    HTTP().set("http://boring.com", pageText);
//    string msg;
//    if ( ! WebSteg::revealMessageInPage("http://boring.com", msg))
//    {
//        cout << "Error revealing!" << endl;
//        return 1;
//    }
//    if (msg != plan)
//    {
//        cout << "Message not recovered properly:\n" << msg;
//        return 1;
//    }
//    cout << "Recovered text is what was hidden:\n" << msg;
    
//    string text;
//    if ( ! WebSteg::hideMessageInPage("http://www.nba.com", "yuee", text))
//        cout << "Error hiding!" << endl;
//    string msg;
//    HTTP().set("http://cs.ucla.edu/classes/winter15/cs32/Projects/4/spec.html", text);
//    if ( ! WebSteg::revealMessageInPage("http://cs.ucla.edu/classes/winter15/cs32/Projects/4/spec.html", msg))
//        cout << "Error revealing!" << endl;
//    cout << msg << endl;
    
    string text;
    string message;
    for (int i = 0; i < 200000; i++)
        message.push_back(static_cast<char>(rand() % 256));
    //HTTP().get("reddit.com", site);
    if (!WebSteg::hideMessageInPage("http://www.reddit.com", message, text))
        cout << "Error hiding!" << endl;
    string msg;
    HTTP().set("http://www.reddit.com", text);
    if (!WebSteg::revealMessageInPage("http://www.reddit.com", msg))
        cout << "Error revealing!" << endl;
    if (msg == message)
        cout << "yeee boi" << endl;
    
//    HashTable<string, int> table(10,20);
//    table.set("rohan", 18);
//    table.set("rak", 10);
//    table.set("shiv",199);
//    int val;
//    table.set("rohan", 20);
//    table.get("rohan", val);
//    table.get("rohan", val);
//    //cout << val << endl;
//    string key;
//    table.discard(key, val);
//    table.touch("shiv");
//    cout << key << endl;
//    cout << val << endl;
//
//    
//    cout << "TESTING TABLE 1" << endl << endl;
//    
//    HashTable<string, int> table(5,6);
//    assert(table.set("rohan", 18)); // set should return true if it is inserted properly
//    assert(table.set("rak", 10));
//    int val = 12345;
//    assert(table.set("rohan", 20));
//    assert(table.get("rohan", val));
//    assert(val == 20); // val is reset to rohan's value
//    assert(table.get("rak", val));
//    assert(val == 10);
//
//    assert(table.set("elise", 22)); // i added this off of shivam's basic testing so i could check that elise and rohan could be put in the same bucket since they both have a size 5 (since the hash is determined by the length of the string)
//    assert(table.set("elise", 2));
//
//    assert(table.touch("rak"));
//    
//    table.output();
//    cout << endl;
//    
//    table.recencyorder();
//    cout << endl;
//    
//    cout << "****DISCARDING ****" << endl << endl;
//    string key = "";
//    assert(table.discard(key, val));
//    assert(key == "rohan" && val == 20);
//    assert(table.touch("elise"));
//    
//    table.recencyorder();
//    cout << endl;
//    
//    cout << "****DISCARDING ****" << endl << endl;
//    assert(table.discard(key, val));
//    
//    assert(key == "rak" && val == 10);
//    
//    table.recencyorder();
//    cout << endl;
//    
//    ///////////////////////////////////
//    
//    cout << "TESTING TABLE 2" << endl << endl;
//    
//    HashTable<string, int> t2(2,3);
//    assert(t2.set("hello", 1, true));
//    assert(!t2.touch("hello")); // can't touch because permanent
//    assert(!t2.isFull());
//    assert(!t2.get("hey", val)); // can't get a key that doesn't exist in the hashtable
//    assert(val == 10); // val should be unchanged
//    assert(!t2.discard(key, val)); // there are no non-permanent associations to delete
//    assert(key == "rak" && val == 10); // key and val should be unchanged
//    assert(t2.set("hi", 2));
//    assert(t2.set("hello", 3));
//    assert(t2.set("hey", 4, true));
//    assert(!t2.set("hola", 5)); // can't insert because max capacity hit
//    assert(t2.isFull());
//    
//    t2.recencyorder();
//    cout << endl;
//    
//    assert(t2.discard(key, val));
//    assert(key == "hi" && val == 2);
//    assert(!t2.discard(key, val)); // can't discard anymore because no non-permanent nodes
//    assert(key == "hi" && val == 2); // key and val should be unchanged
//    
//    t2.output();
//    cout << endl;

//    string in = "html\r\neee\rxxx\ntttttt\r\npppp";
//    string msg = "Thank you based God";
//    string out = "";
//    
//    Steg::hide(in, msg, out);
//    string r = out;
//    
//    string originalmsg = "";
//    
//    cout << "DONE WITH HIDE" << endl;
//    cout << "------------------------------------------------" << endl;
//    
//    Steg::reveal(r, originalmsg);
//    cout << originalmsg<< endl;


}


