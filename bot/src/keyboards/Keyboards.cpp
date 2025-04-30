#include "bot/keyboards/Keyboards.hpp"
#include "bot/utils/Utils.hpp"

#include <tgbot/tgbot.h>
#include <vector>


using namespace TgBot;


namespace Keyboards
{
    InlineKeyboardMarkup::Ptr start_register() 
    { 
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::vector<InlineKeyboardButton::Ptr> row;
        InlineKeyboardButton::Ptr start_btn(new InlineKeyboardButton);
        start_btn->text = "Start registration";
        start_btn->callbackData = "reg";
        row.push_back(start_btn);
    
        return keyboard;
    }
    
    InlineKeyboardMarkup::Ptr register_menu()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr data_btn(new InlineKeyboardButton);
        data_btn->text = "Show my data";
        data_btn->callbackData = "data";
        row.push_back(data_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));
        

        InlineKeyboardButton::Ptr update_btn(new InlineKeyboardButton);
        update_btn->text = "Update my data";
        update_btn->callbackData = "data";
        row.push_back(update_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));
        

        InlineKeyboardButton::Ptr delete_btn(new InlineKeyboardButton);
        delete_btn->text = "Delete my data";
        delete_btn->callbackData = "data";
        row.push_back(delete_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));

        return keyboard;
    }

}
