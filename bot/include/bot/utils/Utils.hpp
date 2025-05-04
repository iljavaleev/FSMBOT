#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <tgbot/tgbot.h>
#include <string_view>

#include "spdlog/sinks/basic_file_sink.h"


using namespace TgBot;


bool is_valid_name(const std::string&);
bool is_valid_surname(const std::string&);
bool is_valid_phone_number(const std::string&);
bool is_valid_email(const std::string&);
std::vector<BotCommand::Ptr> create_commands();

#endif