#include "bot/utils/Utils.hpp"
                      
#include <vector>

#include "tgbot/Api.h"                       
#include "tgbot/Bot.h"


using namespace TgBot;

/*
    mock validation
*/

bool is_valid_name(const std::string& name)
{
    return 1;
}

bool is_valid_surname(const std::string& surname)
{
    return 1;
}

bool is_valid_phone_number(const std::string& phone_number)
{
    return 1;
}

bool is_valid_email(const std::string& email)
{
    return 1;
}


std::vector<BotCommand::Ptr> create_commands()
{
    std::vector<BotCommand::Ptr> commands;

    BotCommand::Ptr start_command{new BotCommand};
    start_command->command = "start";
    start_command->description = "run bot";
    commands.push_back(start_command);

    BotCommand::Ptr cancel_command{new BotCommand};
    cancel_command->command = "help";
    cancel_command->description = "help";
    commands.push_back(cancel_command);

    return commands;
}