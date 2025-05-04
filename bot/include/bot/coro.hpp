#ifndef CORO_HPP
#define CORO_HPP

#include <cassert>
#include <coroutine>
#include <cstdio>
#include <functional>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <version>
#include <iostream>

#include "bot/utils/Utils.hpp"
#include "bot/keyboards/Keyboards.hpp"


template<typename T, typename G, typename... Bases> 
struct promise_type_base : public Bases... 
{
    T value;

    auto yield_value(T _value)
    {
        value = _value;
        return std::suspend_always{};
    }

    G get_return_object() { return G{this}; };

    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
};

template<typename T>
struct awaitable_promise_type_base 
{
    std::optional<T> message;

    struct awaiter 
    {
        std::optional<T>& message;

        bool await_ready() const { return message.has_value(); }
        void await_suspend(std::coroutine_handle<>) {}

        T await_resume()
        {
            assert(message.has_value());
            auto tmp = *message;
            message.reset();
            return tmp;
        }
    };

    awaiter await_transform(T) { return awaiter{message}; }
};


template<typename T, typename U>
struct generator
{
    using promise_type = promise_type_base<T, 
                                generator, 
                                awaitable_promise_type_base<U>>;
    using PromiseTypeHandle = std::coroutine_handle<promise_type>;

    T get_message()
    {
        auto tmp{std::move(coro_handle.promise().value)};
        coro_handle.promise().value = nullptr;

        return tmp;
    }

    void send_message(U message)
    {
        coro_handle.promise().message = message;
        if(!coro_handle.done()) { coro_handle.resume(); }
    }

    generator(const generator&) = delete;
    generator(generator&& rhs)
    : coro_handle{std::exchange(rhs.coro_handle, nullptr)}
    {}

    void interrupt()
    {
      if(coro_handle) { coro_handle.destroy(); }
    }

    ~generator()
    {
        if(coro_handle) { coro_handle.destroy(); }
    }

private:
    friend promise_type; 
    explicit generator(promise_type* p)
    : coro_handle(PromiseTypeHandle::from_promise(*p))
    {}

    PromiseTypeHandle coro_handle;
};


using FSM = generator<TgBot::Message::Ptr, std::string>;


inline FSM Register(long id, std::shared_ptr<TgBot::Bot> bot)
{
    TgUser user(id);
    co_yield bot->getApi().sendMessage(id,  "Enter your first name");
    while(1)
    {
      std::string name = co_await std::string{};
      if (is_valid_name(name))
      {
        user.name = name;
        co_yield bot->getApi().sendMessage(id,  "Enter your last name");
        break;
      }
      co_yield bot->getApi().sendMessage(id,  "Incorrect name. Try again");
    }
    
    while(1)
    {
      std::string surname = co_await std::string{};
      if (is_valid_name(surname))
      {
        user.surname = surname;
        co_yield bot->getApi().sendMessage(id,  "Enter your phone number");
        break;
      }
      co_yield bot->getApi().sendMessage(id,  "Incorrect last name. Try agin");
    }
    
    while(1)
    {
      std::string phone_number = co_await std::string{};
      if (is_valid_phone_number(phone_number))
      {
        user.phone_number = phone_number;
        co_yield bot->getApi().sendMessage(id,  "Enter your email");
        break;
      }
      co_yield bot->getApi().sendMessage(id,  "Incorrect phone number. Try agin");
    }
    
    while(1)
    {
      std::string email = co_await std::string{};
      if (is_valid_email(email))
      {
        user.email = email;
        co_yield bot->getApi().sendMessage(id,  
          "Consent to data processing", nullptr, nullptr, 
          Keyboards::agreement_kb());
        break;
      }
      co_yield bot->getApi().sendMessage(id,  "Incorrect email. Try agin");
    }
    
    std::string agr = co_await std::string{};
    if (agr == "y")
    {
      if(DBConnection::getInstance().create(std::move(user)))
          co_yield bot->getApi().sendMessage(id,  "Registration completed",
                  nullptr, nullptr, Keyboards::register_menu());
      else
        co_yield bot->getApi().sendMessage(id, "Sorry, an error occured, \
          try again later", nullptr, nullptr, Keyboards::start_register());
    }
    else
      co_yield bot->getApi().sendMessage(id,  
        "Sorry, you must consent to the processing of data", 
        nullptr, nullptr, Keyboards::start_register());
    
}
  

inline FSM UpdateCoro(long id, std::shared_ptr<TgBot::Bot> bot)
{
    TgUser user = *DBConnection::getInstance().get(std::move(id));
    while(1)
    {
        std::string field = co_await std::string{};

        if (field == "name")
        {
            co_yield bot->getApi().sendMessage(id,  "Enter new name");
            std::string name = co_await std::string{};
            user.name = name;
            co_yield bot->getApi().sendMessage(
              id,
              user.toString(),
              nullptr,
              nullptr,
              Keyboards::update_kb(),
              "HTML");
        }
        else if (field == "surname")
        {
              co_yield bot->getApi().sendMessage(id,  "Enter new surname");
              std::string surname = co_await std::string{};
              user.surname = surname;
              co_yield bot->getApi().sendMessage(
                id,
                user.toString(),
                nullptr,
                nullptr,
                Keyboards::update_kb(),
                "HTML");
        }
        else if (field == "phone_number")
        {
          co_yield bot->getApi().sendMessage(id,  "Enter new phone_number");
          std::string phone_number = co_await std::string{};
          user.phone_number = phone_number;
          co_yield bot->getApi().sendMessage(
            id,
            user.toString(),
            nullptr,
            nullptr,
            Keyboards::update_kb(),
            "HTML");
        }
        else if (field == "email")    
        {
              co_yield bot->getApi().sendMessage(id,  "Enter new phone_number");
              std::string email = co_await std::string{};
              user.email = email;
              co_yield bot->getApi().sendMessage(
                id,
                user.toString(),
                nullptr,
                nullptr,
                Keyboards::update_kb(),
                "HTML");
        }
        else if (field == "exit")
        {
            if (DBConnection::getInstance().update(user))
            {
              co_yield bot->getApi().sendMessage(id,  "Update completed",
                nullptr, nullptr, Keyboards::register_menu());
            }
            else
            {
              co_yield bot->getApi().sendMessage(id,  
                "Sorry, try again later", 
                nullptr, nullptr, Keyboards::update_kb());
            }
            break;
        }
    }
}

#endif
