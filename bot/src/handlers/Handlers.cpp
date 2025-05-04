#include "bot/handlers/Handlers.hpp" 
#include "bot/database/DB.hpp"  
#include "bot/keyboards/Keyboards.hpp"  
#include "bot/utils/Utils.hpp"
#include "bot/Vocabular.hpp"
#include "bot/coro.hpp"
                           
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
        InlineKeyboardMarkup::Ptr keyboard{nullptr};
        std::string msg = "";
        try
        {
            if (id_storage->exist(message->chat->id))
            {
                keyboard = Keyboards::register_menu();
                msg = "Menu";
            }
            else
            {
                keyboard = Keyboards::start_register();
                msg = "Register first";
            }
            return bot->getApi().sendMessage(
                message->chat->id, 
                std::move(msg),
                nullptr,
                nullptr,
                std::move(keyboard),
                "HTML");
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }  
        return Message::Ptr(nullptr);
    }


    Message::Ptr help_command::operator()(const Message::Ptr& message)
    {
        try
        {
            return bot->getApi().sendMessage(
                message->chat->id, 
                std::string(help_string),
                nullptr,
                nullptr,
                nullptr,
                "HTML");
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }
        return Message::Ptr(nullptr);
    }
};


namespace handlers
{
    Message::Ptr start_registration::operator()(const CallbackQuery::Ptr& query)
    {
        if (query->data != "reg")
        {
            return Message::Ptr(nullptr);
        }
        auto fsm = Register(query->message->chat->id, bot);
        auto msg = fsm.get_message();
        try
        {
            storage->set(query->message->chat->id, std::move(fsm));
            return msg;
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }  
        return Message::Ptr(nullptr);
    }

    Message::Ptr end_registration::operator()(const CallbackQuery::Ptr& query)
    {
        if (query->data.size() > 1 || !storage->exist(query->message->chat->id))
        {
            return Message::Ptr(nullptr);
        }
        auto fsm_ptr = storage->get(query->message->chat->id);
        if (!fsm_ptr)
            return Message::Ptr(nullptr); 
        
        try
        {
            fsm_ptr->send_message(query->data);
            storage->destroy(query->message->chat->id);
            Message::Ptr msg = fsm_ptr->get_message();
            if (StringTools::startsWith(msg->text, "Registration"))
                id_storage->add(query->message->chat->id);
            return fsm_ptr->get_message();
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }  
        return Message::Ptr(nullptr);
    }


    Message::Ptr registration::operator()(const Message::Ptr& message)
    {
        if (!storage->exist(message->chat->id))
            return Message::Ptr(nullptr);
        auto fsm_ptr = storage->get(message->chat->id);
        if (!fsm_ptr)
            return Message::Ptr(nullptr); 
        fsm_ptr->send_message(message->text);
        try
        {
            return fsm_ptr->get_message();
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }     
        return Message::Ptr(nullptr); 
    }
 
    Message::Ptr show_data::operator()(const CallbackQuery::Ptr& query)
    {
        if (query->data != "get" || !id_storage->exist(query->message->chat->id))
            return Message::Ptr(nullptr);
        auto maybe_user = DBConnection::getInstance().get(query->message->chat->id);
        if (!maybe_user) return Message::Ptr(nullptr);
        
        try
        {
            return bot->getApi().sendMessage(
                query->message->chat->id, 
                (*maybe_user).toString());
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }
        return Message::Ptr(nullptr);
    }


    Message::Ptr start_update_data::operator()(const CallbackQuery::Ptr& query)
    {
        
        if (query->data != "start_update" || 
            !id_storage->exist(query->message->chat->id))
            return Message::Ptr(nullptr);
        
        try
        {
            return bot->getApi().sendMessage(
                query->message->chat->id,
                "Choose field to update",
                nullptr,
                nullptr,
                Keyboards::update_kb(),
                "HTML"
            )
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }
        return Message::Ptr(nullptr);
    }

    Message::Ptr update_data::operator()(const CallbackQuery::Ptr& query)
    {
        
        if (!StringTools::startsWith(query->data, "update") || 
            !id_storage->exist(query->message->chat->id))
            return Message::Ptr(nullptr);
    
        auto part = StringTools::split(query->data, ' ').at(1);
        try
        {
            return bot->getApi().sendMessage(
                query->message->chat->id,
                "Choose field to update",
                nullptr,
                nullptr,
                Keyboards::update_kb(),
                "HTML"
            )
        }
        catch(const std::exception& e)
        {
            printf("%s\n", e.what());
        }
        return Message::Ptr(nullptr);
    }


    Message::Ptr delete_data::operator()(const CallbackQuery::Ptr& query)
    {
        
        return Message::Ptr(nullptr); 
    }

};
