#include <stdexcept>

#include "bot/database/DB.hpp"
#include <format>


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


std::string DBConnection::get(const std::string& id)
{
    std::string query;
    pqxx::result res;
    
    if (!connection->is_open())
        reconnect();

    pqxx::nontransaction non_trans(*connection);
    res = non_trans.exec(query);


    if (res.empty())
        throw std::runtime_error("empty result: " + query);

    std::stringstream result;

        
    //    result << '\n';

    
    return result.str();
}

void DBConnection::create(const std::string& id, const User& user)
{
    std::string query;
            
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
        std::cerr << "ERROR: " << e.what() << '\n';
    }

}

void update(const std::string&, const User&){}

void destroy(const std::string&){}
