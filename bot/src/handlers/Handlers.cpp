#include "bot/handlers/Handlers.hpp" 
#include "bot/database/DB.hpp"  
#include "bot/keyboards/Keyboards.hpp"  
#include "bot/utils/Utils.hpp"
#include "bot/Vocabular.hpp"
                           
#include <memory>                                   
#include <string>                                                                     
#include <vector> 
#include <future> 
#include <exception>       
#include <string_view>
#include <regex>


using namespace TgBot;


namespace command_handlers
{
    Message::Ptr start_command::operator()(const Message::Ptr& message)
    {
        try
        {
            /*
                if ( message->chat->id in reg )
                    keyboard = меню для зарегистрированного
                keyboard = регистрация(начать рег)
            */
            return bot.getApi().sendMessage(
                message->chat->id, 
                std::string(choose_program_string),
                nullptr,
                nullptr,
                nullptr,
                "HTML");
        }
        catch(const std::exception& e)
        {
            
        }  
        return Message::Ptr(nullptr);
    }


    Message::Ptr help_command::operator()(const Message::Ptr& message)
    {
        try
        {
            return bot.getApi().sendMessage(
                message->chat->id, 
                std::string(help_string),
                nullptr,
                nullptr,
                nullptr,
                "HTML");
        }
        catch(const std::exception& e)
        {
   
        }
        return Message::Ptr(nullptr);
    }
};


namespace handlers
{
    Message::Ptr inform_handler::operator()(const CallbackQuery::Ptr& query)
    {
        if (!(query->data == "0" || query->data == "1"))
        {
            return Message::Ptr(nullptr);
        }
            
        try
        {
            storage->set(query->message->chat->id, *query->data.c_str());
            return bot.getApi().sendMessage(
                query->message->chat->id, 
                std::string(choose_work_string),
                nullptr,
                nullptr,
                nullptr,
                "HTML");
        }
        catch(const std::exception& e)
        {
            
        }  
        return Message::Ptr(nullptr);
    }


    Message::Ptr get_training::operator()(const Message::Ptr& message)
    {
        if ((message->text == "/start" || message->text == "/help"))
            return Message::Ptr(nullptr);
        if (!std::regex_search(message->text, 
            std::regex("^[0-9]+$", std::regex_constants::ECMAScript))) 
        {
            try
            {
                return bot.getApi().sendMessage(
                    message->chat->id, 
                    std::string(error_string),
                    nullptr,
                    nullptr,
                    nullptr,
                    "HTML");
            }
            catch(const std::exception& e)
            {
                return Message::Ptr(nullptr);
            }  
        }
        
        auto program = storage->get(message->chat->id);
        if (!program)
        {
            try
            {
                return bot.getApi().sendMessage(
                    message->chat->id, 
                    std::string(choose_program_string),
                    nullptr,
                    nullptr,
                    nullptr,
                    "HTML");
            }
            catch(const std::exception& e)
            {
                return Message::Ptr(nullptr);
            }
            
        }
        
        if (1)
        {
            try
            {
                return bot.getApi().sendMessage(
                    message->chat->id, 
                    std::string(error_string),
                    nullptr,
                    nullptr,
                    nullptr,
                    "HTML");
            }
            catch(const std::exception& e)
            {
                return Message::Ptr(nullptr);
            }  
        }
        
        std::string training;
        try
        {
            auto& pg_connection = DBConnection::getInstance();
            auto fut_training = std::async(std::launch::async, 
                &DBConnection::get, std::ref(pg_connection), 
                std::ref(message->text));
            training = fut_training.get();
        }
        catch(const std::exception& e)
        {
            try
            {
                return bot.getApi().sendMessage(
                    message->chat->id, 
                    std::string(problems_string),
                    nullptr,
                    nullptr,
                    nullptr,
                    "HTML"
                );
            }
            catch(const std::exception& e)
            {
            }  
            return Message::Ptr(nullptr);
        }  

        try
        {
            std::string mess;
            
            return bot.getApi().sendMessage(message->chat->id, 
                std::move(mess), 
                nullptr, 
                nullptr, 
                nullptr,
                "HTML"
            );
        }
        catch(const std::exception& e)
        {
        }

        return Message::Ptr(nullptr); 
    }
 
    Message::Ptr prev_next_training::operator()(const CallbackQuery::Ptr& query)
    {
        auto data = StringTools::split(query->data, ',');
        if (data.size() != 2)
        {
            return Message::Ptr(nullptr);
        }
        
        std::string training;
        try
        {
            auto& pg_connection = DBConnection::getInstance();
            auto fut_training = std::async(std::launch::async, 
                &DBConnection::get, std::ref(pg_connection), 
                data.at(0));
            training = fut_training.get();
        }
        catch(const std::exception& e)
        {
            try
            {
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    std::string(problems_string),
                    nullptr,
                    nullptr,
                    nullptr,
                    "HTML"
                );
            }
            catch(const std::exception& e)
            {
    
            }  
            return Message::Ptr(nullptr);
        }  
       

        try
        {
            std::string mess;
            
    
            return bot.getApi().sendMessage(query->message->chat->id, 
                std::move(mess), 
                nullptr, 
                nullptr, 
                nullptr,
                "HTML"
            );
        }
        catch(const std::exception& e)
        {
            
        }

        return Message::Ptr(nullptr); 
    }

};
