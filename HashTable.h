//
//  HashTable.h
//  Project 4
//
//  Created by Ronaq Virdi on 3/5/15.
//  Copyright (c) 2015 Ronaq Virdi. All rights reserved.
//

#ifndef Project_4_HashTable_h
#define Project_4_HashTable_h

#include <iostream>

template <typename KeyType, typename ValueType>
class HashTable
{
public:
    HashTable(unsigned int numBuckets, unsigned int capacity);
    ~HashTable();
    bool isFull() const;
    bool set(const KeyType& key, const ValueType& value, bool permanent = false);
    bool get(const KeyType& key, ValueType& value) const;
    bool touch(const KeyType& key);
    bool discard(KeyType& key, ValueType& value);
    
private:
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
    
    unsigned int getBucketForKey(const KeyType& key) const;
    
    struct Node
    {
        Node* next;
        Node* prev;
        Node* history_next;
        Node* history_prev;
        KeyType key;
        ValueType value;
        bool m_perm = false;
    };
    
    Node** head;
    Node** tail;
    Node* l_rec;
    Node* m_rec;
    unsigned int m_cap;
    unsigned int n_associations;
    unsigned int totalBuckets;
};


template <typename KeyType, typename ValueType>
inline
unsigned int computeHash(KeyType key);
//{
//
//}

template <typename KeyType, typename ValueType>
inline
unsigned int HashTable<KeyType,ValueType>::getBucketForKey(const KeyType& key) const
{
    // The computeHash function must be defined // for each type of key that we use in some // hash table.
    unsigned int computeHash(KeyType); // prototype
    unsigned int determineBucketFromHash(KeyType); // prototype
    unsigned int bucketNum = computeHash(key) % totalBuckets;
    return bucketNum;
}
template <typename KeyType, typename ValueType>
HashTable<KeyType,ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity)
{
    m_cap = capacity;
    n_associations = 0;
    totalBuckets = numBuckets;
    
    head = new Node*[numBuckets];  // initialize all the pointers
    tail = nullptr;
    l_rec = nullptr;
    m_rec = nullptr;
    for(int i=0; i < numBuckets; i++)  // set every bucket to point to nullptr
    {
        head[i] = nullptr;
    }
}
template <typename KeyType, typename ValueType>
HashTable<KeyType,ValueType>::~HashTable()
{
    // Multiset destructor
    for(int i=0;i < totalBuckets; i++)  // loops thru every bucket in the array
    {
        Node* p = *(head + i);   // p points to the bucket
        while(p != nullptr)  // loops thru every list in the node
        {
            Node* n = p->next;
            delete p;   // delete the node
            p = n;
        }
    }
}
template <typename KeyType, typename ValueType>
bool HashTable<KeyType,ValueType>::isFull() const
{
    if(n_associations == m_cap)
        return true;
    return false;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType,ValueType>::set(const KeyType& key, const ValueType& value, bool permanent)
{
    if(isFull() == true)
        return false;
    int y = getBucketForKey(key);   // gets to the proper bucket in the array
    Node* p = *(head + y);  // p points to the correct bucket
    if(p == nullptr) // when youre adding the first node at the particular bucket
    {
        Node* r = new Node;  // otherwise add a new node
        *(head+y) = r;   // make the bucket point to the first node in the list
        r->key = key;
        r->value = value;
        r->m_perm = permanent;
        r->next = nullptr;
        r->prev = nullptr;
        
        if(r->m_perm == false)  // if the node is not permanent set up the history pointers
        {
            r->history_prev = nullptr;
            r->history_next = m_rec;
            if(m_rec) // mrec not equal to nullptr
            {
                m_rec->history_prev = r;
            }
            m_rec = r;
            if(!l_rec)  // lec rec is a nullptr
            {
                l_rec = r;  // NEW: WHen the first node in the list is added, least and most rec
            }
        }
        n_associations++; // increment associations
        return true;
    }
    
    while(p->next != nullptr) // loops thru all the nodes except the last node
    {
        if(p->key == key)
        {
            p->value = value;
            if(p->m_perm == false)  // if the node is not permanent, set up the history pointers
            {
                if(p != l_rec)   // if the node is not the least most recent in the history list
                {
                    if(p->history_next != nullptr)
                    {
                        p->history_next->history_prev = p->history_prev;
                        p->history_prev->history_next = p->history_next;
                    }
                    else if(p->history_next == nullptr)
                    {
                        p->history_prev->history_next = nullptr;
                    }
                    
                    p->history_next = m_rec;  // set up the pointers and both sides
                    (m_rec)->history_prev = p;
                    m_rec = p;  // p is now the most recent
                    p->history_prev = nullptr;
                    p->history_prev = l_rec;
                   
                }
                else   // when the node that you are setting is the least recent in the history list
                {
                    l_rec->history_next = nullptr;
                    p->history_next = m_rec;
                    m_rec->history_prev = p;
                    m_rec = p;  // p is the most recent
                    m_rec->history_prev = nullptr;
                }
            }
            return true;
        }
        p = p->next;
    }
    if(p->key == key) // if the last one has the desired key
    {
        p->value = value;
        if(p->m_perm == false)
        {
            if(p != l_rec) // if the node is not the least most recent in the history list
            {
                if(p->history_next == nullptr && p->history_prev != nullptr)
                {
                    p->history_prev->history_next = nullptr;
                }
                p->history_next = m_rec;
                (m_rec)->history_prev = p;
                m_rec = p;  // p is now the most recent
                p->history_prev = nullptr;
                
            }
            else  // if p is the last node in the history list
            {
                // set up the history pointers on both sides of the updated node
                l_rec = p->history_prev;
                l_rec->history_next = nullptr;
                l_rec->history_prev = p->history_prev;
                p->history_next = m_rec;
                m_rec->history_prev = p;
                m_rec = p;  // p is now the most recent
                m_rec->history_prev = nullptr;
            }
        }
        return true;
    }
    Node* r = new Node;  // otherwise add a new node if u cannot find a node to update
    r->key = key;  // set up the key and value
    r->value = value;
    r->m_perm = permanent;
    r->next = nullptr;
    r->prev = p;
    if(p != nullptr)
        p->next = r;
    
    if(r->m_perm == false)   // if the new node that is added is not permanent add it to the history list
    {
        r->history_prev = nullptr;
        r->history_next = m_rec;
        if(m_rec != nullptr)
            (m_rec)->history_prev = r;
        m_rec = r;  // the new node is the most recent
    }
    n_associations++; // increment associations
    return true;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType,ValueType>::get(const KeyType& key, ValueType& value) const
{
    int x = getBucketForKey(key);
    Node* p = *(head + x); // p points to the desired bucket
    while(p != nullptr)  // loop thru the entire linked list
    {
        if(p->key == key)
        {
            value = p->value;  // the value is set to the value of the found node
            return true;
        }
        p = p->next;
    }
    return false;  // if u could not find the proper value
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType,ValueType>::touch(const KeyType& key)
{
    int z = getBucketForKey(key);
    Node* p= *(head + z);  // p points to the desired bucket
    while(p != nullptr) // loop thru the entire linked list
    {
        if(p->m_perm == false && p->key == key)
        {
            if(p->history_next != nullptr && p->history_prev != nullptr)
            {
                // set up the histroy pointers
                p->history_next->history_prev = p->history_prev;
                p->history_prev->history_next = p->history_next;
            }
            else if(p->history_next == nullptr && p->history_prev != nullptr)
            {
                // set up pointers
                p->history_prev->history_next = nullptr;
                l_rec = p->history_prev;
            }
            
            p->history_next = m_rec;
            (m_rec)->history_prev = p;
            m_rec = p;   // mrec is now p
            p->history_prev = nullptr;
            return true;
        }
        p = p->next;
    }
    
    return false;
}
template <typename KeyType, typename ValueType>
bool HashTable<KeyType,ValueType>::discard(KeyType& key, ValueType& value)
{
    if(l_rec == nullptr)
        return false;
    key = l_rec->key;  // store the key and value of the desired node
    value = l_rec->value;
    
    Node* p = l_rec;  // point p to the least recent node in the histroy list
    if(p->prev == nullptr)  // if you are deleting the first node in the linked list
    {
        int z = getBucketForKey(p->key);
        *(head + z) = p->next;  // the bucket must now point to the SECOND list in the list
        if(*(head + z) != nullptr)
        {
            (*(head + z))->prev = nullptr;
        }
    }
    else if(p->next != nullptr) // if the node that you are deleteing is in the middle of the list
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    else  // the node that you are deleteing is the last node in the linked list for that bucket
    {
        p->prev->next = nullptr;
    }
    
    // set up the history pointers for the deleted node
    if(p->history_prev != nullptr)
    {
        p->history_prev->history_next = nullptr;
    }
    l_rec = p->history_prev;
    delete p;
    n_associations--;  // there is now one less association in the hash table
    return true;
    
}

#endif
