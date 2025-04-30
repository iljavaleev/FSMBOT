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

#include "database/DB.hpp"


namespace coro_iterator 
{
  template<typename PT>
  struct iterator 
  {
    std::coroutine_handle<PT> coro_handle{nullptr};
    bool done{true};

    using RetType = decltype(coro_handle.promise().value);

    void resume()
    {
      coro_handle.resume();
      done = coro_handle.done();
    }

    iterator() = default;

    iterator(std::coroutine_handle<PT> hco): coro_handle{hco}{ resume(); }

    iterator& operator++()
    {
      resume();
      return *this;
    }

    bool operator==(const iterator& other) const 
    { 
      return done == other.done; 
    }

    const RetType& operator*() const { return coro_handle.promise().value; }
    const RetType* operator->() const { return &(operator*()); }

  };
}  // namespace coro_iterator


template<typename T, typename G, typename... Bases> 
struct promise_type_base : public Bases... 
{
    T value;

    auto yield_value(T _value)
    {
        value = _value;
        return std::suspend_never{};
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
    std::optional<T> recent_signal;

    struct awaiter 
    {
        std::optional<T>& recent_signal;

        bool await_ready() const { return recent_signal.has_value(); }
        void await_suspend(std::coroutine_handle<>) {}

        T await_resume()
        {
            assert(recent_signal.has_value());
            auto tmp = *recent_signal;
            recent_signal.reset();
            return tmp;
        }
    };

    [[nodiscard]] awaiter await_transform(T) 
    { return awaiter{recent_signal}; }
};


template<typename T, typename U>
struct [[nodiscard]] async_generator
{
    using promise_type = promise_type_base<T, 
                                async_generator, 
                                awaitable_promise_type_base<U>>;
    using PromiseTypeHandle = std::coroutine_handle<promise_type>;

    T operator()()
    {
        auto tmp{std::move(coro_handle.promise().value)};
        coro_handle.promise().value.clear();

        return tmp;
    }

    void SendSignal(U signal)
    {
        coro_handle.promise().recent_signal = signal;
        if(!coro_handle.done()) { coro_handle.resume(); }
    }

    async_generator(const async_generator&) = delete;
    async_generator(async_generator&& rhs)
    : coro_handle{std::exchange(rhs.coro_handle, nullptr)}
    {}

    ~async_generator()
    {
        if(coro_handle) { coro_handle.destroy(); }
    }

private:
    friend promise_type; 
    explicit async_generator(promise_type* p)
    : coro_handle(PromiseTypeHandle::from_promise(*p))
    {}

    PromiseTypeHandle coro_handle;
};


template<typename T>
struct generator 
{
  using promise_type      = promise_type_base<T, generator>;
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;
  using iterator          = coro_iterator::iterator<promise_type>;

  iterator begin() { return {coro_handle}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs): coro_handle(rhs.coro_handle)
  {
        rhs.coro_handle = nullptr;
  }

  ~generator()
  {
        if(coro_handle) { coro_handle.destroy(); }
  }

private:
  friend promise_type;  // #A As the default ctor is private G needs to be a friend
  explicit generator(promise_type* p)
  : coro_handle(PromiseTypeHandle::from_promise(*p))
  {}

  PromiseTypeHandle coro_handle;
};


using FSM = async_generator<std::string>;


FSM Register(long id)
{
    User user(id);
    std::string name = co_await std::string{};
    // check
    co_yield message;

    user.name = name;
    std::string surname = co_await std::string{};
    user.surname = surname;

    std::string phone_number = co_await std::string{};
    user.phone_number = phone_number;

    std::string email = co_await std::string{};
    user.email = email;
    co_yield message;
}


generator<byte> sender(std::vector<byte> fakeBytes)
{
  for(const auto& b : fakeBytes) { co_yield b; }
}
  

#endif
