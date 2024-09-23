#pragma once 

#include <cstddef>
#include <utility>
#include <memory>
#include <unordered_map>

#include <properties/property.hpp>


namespace game::objects {

class Object {
public:    
    using Pointer = std::shared_ptr<Object>;

    Object(std::string &&_name);

    template <typename AbilityType>
    AbilityType &get() const 
    {
        if (auto it = properties.find(property::id<AbilityType>()); it != properties.end()) {
            return dynamic_cast<AbilityType&>(*it->second);
        } else {
            throw std::runtime_error("No such ability");
        }
    }

    template <typename AbilityType>
    auto &add(auto&&... _args) {
        constexpr auto id = property::id<AbilityType>();

        auto [_, success] = properties.try_emplace(id, 
                                                   std::make_unique<AbilityType>(std::forward<decltype(_args)>(_args)...));
        
        if(!success) {
            throw std::runtime_error("Ability has already exist");
        }

        return *this;
    }

private:
    std::string name;
    std::unordered_map<int, property::Property::Pointer> properties;
};

}