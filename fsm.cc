
#include "bot/utils/Utils.hpp"
#include "bot/handlers/Handlers.hpp"
#include "bot/database/UserStorage.hpp"
#include "bot/database/DB.hpp"

#include <exception>

#include <tgbot/tgbot.h>
#include <spdlog/spdlog.h>
#include "spdlog/async.h"

using namespace TgBot;


int main()
{
    std::string bot_token = std::string(std::getenv("BOT_TOKEN"));
    TgBot::Bot bot(bot_token);
    auto storage = std::make_shared<Storage<long, char>>();
   
    bot.getApi().setMyCommands(create_commands());

    bot.getEvents().onCommand("start", command_handlers::start_command(bot));
    bot.getEvents().onCommand("help", command_handlers::help_command(bot));
    
    bot.getEvents().onAnyMessage(handlers::get_training(bot, storage));
    bot.getEvents().onCallbackQuery(handlers::prev_next_training(bot));
    bot.getEvents().onCallbackQuery(handlers::inform_handler(bot, storage));
    
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }


    return 0;
}
