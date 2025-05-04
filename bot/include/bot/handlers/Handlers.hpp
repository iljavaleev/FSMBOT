#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "bot/database/UserStorage.hpp"
#include "bot/coro.hpp"

#include <string>

#include "tgbot/types/CallbackQuery.h" 
#include "tgbot/types/Message.h"
#include "tgbot/tgbot.h"


using namespace TgBot;


namespace command_handlers
{
    class start_command
    {
        const std::shared_ptr<TgBot::Bot> bot;
        std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        start_command(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<IdStorage<long>>& _s):
            bot(_bot),
            id_storage(_s)
            {}
        Message::Ptr operator()(const Message::Ptr&);
    };

    class help_command
    {
        const std::shared_ptr<TgBot::Bot> bot;
    public:
        help_command(std::shared_ptr<TgBot::Bot> _bot):
            bot(_bot)
            {}
        Message::Ptr operator()(const Message::Ptr&);
    };
   
};

namespace handlers
{   
    class start_registration
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
    public:
        start_registration(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<Storage<long, FSM>>& s):
            bot(_bot), 
            storage(s)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class end_registration
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
        const std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        end_registration(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<Storage<long, FSM>>& s, 
            std::shared_ptr<IdStorage<long>>& _id_storage):
            bot(_bot), 
            storage(s),
            id_storage(_id_storage)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class registration
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
    public:
        registration(std::shared_ptr<TgBot::Bot> _bot,
            std::shared_ptr<Storage<long, FSM>>& s):
            bot(_bot), 
            storage(s)
            {}
        Message::Ptr operator()(const Message::Ptr& message);
    };

    class show_data
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
        std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        show_data(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<Storage<long, FSM>>& s, 
            std::shared_ptr<IdStorage<long>>& _id_storage):
            bot(_bot), 
            storage(s),
            id_storage(_id_storage)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class start_update_data
    {
        const std::shared_ptr<TgBot::Bot> bot;
        std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        start_update_data(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<IdStorage<long>>& _id_storage):
            bot(_bot),
            id_storage(_id_storage)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class update_data
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
        std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        update_data(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<Storage<long, FSM>>& s, 
            std::shared_ptr<IdStorage<long>>& _id_storage):
            bot(_bot), 
            storage(s),
            id_storage(_id_storage)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class delete_data
    {
        const std::shared_ptr<TgBot::Bot> bot;
        const std::shared_ptr<Storage<long, FSM>>& storage;
        std::shared_ptr<IdStorage<long>>& id_storage;
    public:
        delete_data(std::shared_ptr<TgBot::Bot> _bot, 
            std::shared_ptr<Storage<long, FSM>>& s, 
            std::shared_ptr<IdStorage<long>>& _id_storage):
            bot(_bot), 
            storage(s),
            id_storage(_id_storage)
            {}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
};


#endif