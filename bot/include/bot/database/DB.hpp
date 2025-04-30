#ifndef DB_HPP
#define DB_HPP



#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>
#include <memory>



struct User
{
    long id;
    std::string name;
    std::string surname;
    std::string phone_number;
    std::string email;
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
    std::string get(const std::string&);
    
    void create(const std::string&, const ::User&);
    void update(const std::string&, const ::User&);
    void destroy(const std::string&);

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
    static constexpr char end_query[] = "select exercise, reps,\
    work_id, week_id, superset from endurance where work_id=";
    static constexpr char str_query[] = "select exercise, reps,\
    work_id, week_id from strenght where work_id=";
    
    
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
