#pragma once

#include <functional>


namespace ioc {


template <typename Type>
class Creator  {
public:
    template<typename ...Args>
    Creator(Args&& ..._args) :
        foo{ [=]() {
                 return new Type(std::forward<Args>(_args)...);
             }}
    { }

    Type *execute() {
        return foo();
    }

private:
    std::function<Type*()> foo;
};

}