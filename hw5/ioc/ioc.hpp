#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace ioc {

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value.data());
    }
    
    std::array<char, N> value;
    
    constexpr bool operator==(StringLiteral<N> _other) const noexcept {
        return value == _other.value;
    }

    constexpr bool operator==(std::string_view _str) const noexcept {
        if constexpr(N != _str.size()) {
            return false;
        } else {
            StringLiteral other(_str.data());
            return *this == other;
        }
    }

    template<size_t U>
    constexpr bool operator==(const char (&_str)[U]) const noexcept {
        if constexpr(N != U) {
            return false;
        } else {
            StringLiteral other(_str);
            return *this == other;
        }
    }
};

class CreatorCleaner {
public:
    virtual ~CreatorCleaner() = default;
    virtual void clear() = 0;
};

template<typename Type, StringLiteral Name>
struct Creator : public CreatorCleaner {
    using type = Type;
    constexpr static auto name = Name;

    using scope = std::size_t;
    using Creators = std::unordered_map<scope, std::function<Type*()>>;
    static Creators creator;

    void clear() override {
        creator.clear();
    }
};


template<typename Type, StringLiteral Name>
Creator<Type, Name>::Creators Creator<Type, Name>::creator;


template <typename... Args>
struct Arguments;

template <typename First, typename... Args>
struct Arguments<First, Args...> : Arguments<Args...> {

    constexpr Arguments(First&& _first) : 
        Arguments<Args...>() 
    { }

    constexpr Arguments() = default;

    constexpr static std::size_t id = Arguments<Args...>::id + 1;
    using type = First;

    template<typename Type>
    static constexpr std::size_t get() {
        if constexpr(std::is_same_v<Type, type>) {
            return id;
        } else {
            return  Arguments<Args...>::template get<Type>();
        }
    }

    template<std::size_t N, typename Type>
    static constexpr bool callable() {
        if constexpr((id == N) && std::is_invocable_v<First>) {
            return true;
        } else {
            return Arguments<Args...>::template callable<N, Type>();
        }
    }
};

template <>
struct Arguments<>{
    constexpr static std::size_t id = 0;
    
    template<std::size_t N, typename Type>
    static constexpr auto callable() {
        return false;
    }
};

template <std::size_t N, typename Type, typename... Args>
constexpr auto isCallable(Arguments<Args...> _args) {
    constexpr std::size_t size = sizeof...(Args);
    constexpr std::size_t idx = size - N;
    return _args.template callable<idx, Type>();
}

using namespace std::string_view_literals;

class Ioc {
public:
    Ioc(std::string_view _scope = "default"sv) :
        scope{ static_cast<std::string>(_scope) },
        scopeHash( std::hash<std::string>{}(scope))
    { }

    template<typename Type, StringLiteral Name, StringLiteral Action, typename... Args>
    auto resolve(Args&&... _args)
    {
        constexpr Arguments<Args...> args;

        if constexpr (Action == "Register") {
            if constexpr(isCallable<0, std::function<Type*()>>(args)) {
                std::tuple<Args...> t{ _args... };
                Creator<Type, Name>::creator[scopeHash] = std::get<0>(t);
            } else {
                Creator<Type, Name>::creator[scopeHash] = [=](){
                    return new Type(_args...);
                };
            }

            static Creator<Type, Name> c;
            if (auto it = std::ranges::find(scopes, &c); it == scopes.cend()) {
                scopes.emplace_back(&c);
            }

        } else if constexpr (Action == "Get") {
            if constexpr (std::is_pointer_v<Type>) {
                return Creator<Type, Name>::creator[scopeHash]();
            } else if constexpr (std::is_reference_v<Type>) {
                auto &result = *Creator<Type, Name>::creator[scopeHash]();
                return *result;
            } else {
                return *Creator<Type, Name>::creator[scopeHash]();
            }
        } else if constexpr (Action == "ChangeScope") {
            // std::tuple<Args...> t{ _args... };
            const auto &name = std::get<0>(std::tuple<Args...>{ _args... });
            if constexpr (std::is_convertible_v<std::string_view, decltype(name)>) {
                scope = name;
                scopeHash = std::hash<std::string>{}(name);
            }
        }
    }

    std::string_view name() const noexcept {
        return scope;
    }
    std::size_t hash() const noexcept {
        return scopeHash;
    }

    static void clear() {
        std::ranges::for_each(scopes, [](auto scope) {
            scope->clear();
        });
    }

    static std::vector<CreatorCleaner *> scopes;

private:
    std::string scope{ "Default" };
    std::size_t scopeHash{ 0 };
};


}