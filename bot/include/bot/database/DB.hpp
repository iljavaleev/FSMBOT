#ifndef DB_HPP
#define DB_HPP



#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <format>


struct TgUser
{
    long id;
    std::string name;
    std::string surname;
    std::string phone_number;
    std::string email;

    std::string toString()
    {
        return std::format(
            "User with name: {} {}\nPhone number: {}\nEmail: {}\n", 
            name, surname, phone_number, email);
    }
};


class DBConnection 
{
public:
    static DBConnection& getInstance()
    {
        if (!instance)
        {
           instance = new DBConnection();
        }
            
        return *instance;
    }
    std::optional<TgUser> get(long);
    
    void transaction(const std::string&);
    bool create(const ::TgUser&);
    bool update(const ::TgUser&);
    bool destroy(long);

    DBConnection(const DBConnection&) = delete;
    DBConnection& operator=(const DBConnection&) = delete;
    
private:
    DBConnection()
    {
        connection = std::make_shared<pqxx::connection>(uri);
        if (!connection->is_open())
            throw std::runtime_error("error open db"); 
    }

    void reconnect();
    ~DBConnection()
    { 
        delete instance;
    }
    
    static DBConnection* instance;
    std::shared_ptr<pqxx::connection> connection{nullptr};
    
    const static std::string uri; 
        
};

inline DBConnection* DBConnection::instance = nullptr;

inline const std::string DBConnection::uri =  
    std::string("dbname=") + (std::getenv("POSTGRES_DB") ? 
        std::getenv("POSTGRES_DB") : "postgres") +
    std::string(" user=") + (std::getenv("POSTGRES_USER") ? 
        std::getenv("POSTGRES_USER") : "postgres") +
    std::string(" password=") + (std::getenv("POSTGRES_PASSWORD") ? 
        std::getenv("POSTGRES_PASSWORD") : "postgres") + 
    std::string(" host=") + (std::getenv("POSTGRES_HOST") ? 
        std::getenv("POSTGRES_HOST") : "localhost") +
    std::string(" port=") +  (std::getenv("POSTGRES_PORT") ? 
        std::getenv("POSTGRES_PORT") : "5432");

#endif 
