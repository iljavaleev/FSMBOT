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
        data_btn->callbackData = "get";
        row.push_back(data_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));
        

        InlineKeyboardButton::Ptr update_btn(new InlineKeyboardButton);
        update_btn->text = "Update my data";
        update_btn->callbackData = "start_update";
        row.push_back(update_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));
        

        InlineKeyboardButton::Ptr delete_btn(new InlineKeyboardButton);
        delete_btn->text = "Delete my data";
        delete_btn->callbackData = "delete";
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

    InlineKeyboardMarkup::Ptr update_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::vector<InlineKeyboardButton::Ptr> row;
        
        InlineKeyboardButton::Ptr name_btn(new InlineKeyboardButton);
        name_btn->text = "Name";
        name_btn->callbackData = "update name";
        row.push_back(name_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));
        
        InlineKeyboardButton::Ptr surname_btn(new InlineKeyboardButton);
        surname_btn->text = "Surname";
        surname_btn->callbackData = "update surname";
        row.push_back(surname_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));

        InlineKeyboardButton::Ptr phone_btn(new InlineKeyboardButton);
        phone_btn->text = "Phone";
        phone_btn->callbackData = "update phone_number";
        row.push_back(phone_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));

        InlineKeyboardButton::Ptr email_btn(new InlineKeyboardButton);
        email_btn->text = "Email";
        email_btn->callbackData = "update email";
        row.push_back(email_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));

        InlineKeyboardButton::Ptr end_btn(new InlineKeyboardButton);
        end_btn->text = "Exit update";
        end_btn->callbackData = "update exit";
        row.push_back(end_btn);
        keyboard->inlineKeyboard.push_back(std::move(row));

        return keyboard;
    }
}   
