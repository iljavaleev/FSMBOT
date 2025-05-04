#ifndef USER_STORAGE_HPP
#define USER_STORAGE_HPP

#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "DB.hpp"

template<typename K, typename V>
struct Storage
{
    std::unordered_map<K, std::shared_ptr<V>> storage;
    std::shared_ptr<V> get(K key);
    bool exist(K key);
    void set(K key, V value);
    void destroy(K key);
};


template<typename K, typename V> 
std::shared_ptr<V> Storage<K, V>::get(K key)
{
    if (auto res = storage.find(key); res != storage.end())
        return storage.at(key);
    return NULL;
}

template<typename K, typename V> 
bool Storage<K, V>::exist(K key)
{   
    return storage.contains(key);
}

template<typename K, typename V> 
void Storage<K, V>::destroy(K key)
{   
    if (storage.contains(key))
        storage.erase(key);
}

template<typename K, typename V> 
void Storage<K, V>::set(K key, V value)
{
    if (auto res = storage.find(key); res != storage.end())
    {
        return;
    }
        
    if (storage.size() > 10)
        storage.clear();

    storage.insert({key, std::make_shared<V>(std::move(value))});
}

template<typename K>
struct IdStorage
{
    std::unordered_set<K> storage;
    bool exist(K key);
    void add(K key);
};

template<typename K> 
bool IdStorage<K>::exist(K key)
{
    if (auto res = storage.find(key); res != storage.end())
        return 1;
    if (DBConnection::getInstance().get(key))
    {
        add(key);
        return 1;
    }
        
    return 0;
}


template<typename K> 
void IdStorage<K>::add(K key)
{
    if (auto res = storage.find(key); res != storage.end())
    {
        return;
    }
        
    if (storage.size() > 100)
        storage.clear();

    storage.insert(key);
}

#endif