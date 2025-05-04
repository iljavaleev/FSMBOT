
#include "bot/utils/Utils.hpp"
#include "bot/handlers/Handlers.hpp"
#include "bot/database/UserStorage.hpp"
#include "bot/database/DB.hpp"

#include <exception>

#include <tgbot/tgbot.h>
#include "bot/coro.hpp"

using namespace TgBot;


int main()
{
    std::string bot_token = std::string(std::getenv("BOT_TOKEN"));
    auto bot = std::make_shared<TgBot::Bot>(std::move(bot_token));
    auto storage = std::make_shared<Storage<long, FSM>>();
    auto id_storage = std::make_shared<IdStorage<long>>();
    bot->getApi().setMyCommands(create_commands());
    bot->getEvents().onCommand("start", command_handlers::start_command(bot, id_storage));
   
    bot->getEvents().onCallbackQuery(handlers::start_registration(bot, storage));
    bot->getEvents().onCallbackQuery(handlers::end_registration(bot, storage, id_storage));
    bot->getEvents().onAnyMessage(handlers::registration(bot, storage));
    
    bot->getEvents().onCallbackQuery(handlers::show_data(bot, storage, id_storage));
    // bot->getEvents().onCallbackQuery(handlers::update_data(bot, storage, id_storage));
    // bot->getEvents().onCallbackQuery(handlers::delete_data(bot, storage, id_storage));


    try {
        printf("Bot username: %s\n", bot->getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(*bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }


    return 0;
}
