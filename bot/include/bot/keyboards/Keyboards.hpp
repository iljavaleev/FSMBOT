#ifndef KEYBOARDS_HPP
#define KEYBOARDS_HPP

#include <tgbot/tgbot.h>
#include <string>


using namespace TgBot;


namespace Keyboards
{
    InlineKeyboardMarkup::Ptr start_register(); 
    InlineKeyboardMarkup::Ptr register_menu();   
} 

#endif