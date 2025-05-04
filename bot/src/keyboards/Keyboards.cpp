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
        keyboard->inlineKeyboard.push_back(std::move(row));
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


    InlineKeyboardMarkup::Ptr agreement_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::vector<InlineKeyboardButton::Ptr> row;
        
        InlineKeyboardButton::Ptr yes_btn(new InlineKeyboardButton);
        yes_btn->text = "Yes";
        yes_btn->callbackData = "y";
        row.push_back(yes_btn);
        
        InlineKeyboardButton::Ptr no_btn(new InlineKeyboardButton);
        no_btn->text = "No";
        no_btn->callbackData = "n";
        row.push_back(no_btn);

        keyboard->inlineKeyboard.push_back(std::move(row));
        return keyboard;
    }
}   
