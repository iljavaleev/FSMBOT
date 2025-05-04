#include <stdexcept>

#include "bot/database/DB.hpp"
#include <format>
#include <optional>


void DBConnection::reconnect()
{  
    try
    {
        connection = std::make_shared<pqxx::connection>(uri);
    }
    catch(const pqxx::broken_connection & e){}

    if (!connection->is_open())
        throw std::runtime_error("DB reconnection error");
};


std::optional<TgUser> DBConnection::get(long id)
{
    std::optional<TgUser> result;
    std::string query = std::format("select * from botuser where id={}", id);
    pqxx::result res;
    
    if (!connection->is_open())
        reconnect();

    pqxx::nontransaction non_trans(*connection);
    res = non_trans.exec(std::move(query));


    if (res.empty())
        return std::nullopt;
    pqxx::row record = res.begin(); 
    TgUser user;
   
    user.id = record.at(0).as<long>();
    user.name = record.at(1).as<std::string>();
    user.surname = record.at(2).as<std::string>();
    user.phone_number = record.at(3).as<std::string>();
    user.email = record.at(4).as<std::string>();
    
    return result.emplace(std::move(user));
}


void DBConnection::transaction(const std::string& query)
{
    try
    {
        if (!connection->is_open())
            reconnect();

        pqxx::work tx{*connection};
        tx.exec(query);
        tx.commit();
    }
    catch (std::exception const &e)
    {
        throw;
    }
}


bool DBConnection::create(const TgUser& user)
{
    std::string query = std::format("insert into botuser values \
        ({}, '{}', '{}', '{}', '{}')", user.id, user.name, user.surname, 
        user.phone_number, user.email);
    try
    {
        transaction(std::move(query));
    }
    catch(const std::exception& e)
    {
        printf("%s\n", e.what());
        return 0;
    }
    
    return 1;
}

bool DBConnection::update(const TgUser& user)
{
    std::string query = std::format("update botuser set name = '{}', \
    surname = '{}', phone_number = '{}', email = '{}' where id = {}", 
    user.name, user.surname, user.phone_number, user.email, user.id);
            
    try
    {
        transaction(std::move(query));
    }
    catch(const std::exception& e)
    {
        printf("%s\n", e.what());
        return 0;
    }
    
    return 1;
}

bool DBConnection::destroy(long id)
{
    std::string query = std::format(
        "delete from botuser where idid={}", 
        id
    );
    try
    {
        transaction(std::move(query));
    }
    catch(const std::exception& e)
    {
        printf("%s\n", e.what());
        return 0;
    }
    
    return 1;
}
