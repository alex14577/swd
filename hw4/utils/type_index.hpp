#pragma once

#include <type_traits>


namespace game::type_index {

template<typename ...Commands>
class IndexStorage;

template <typename Property, typename ...Properties>
class IndexStorage<Property, Properties...> : IndexStorage<Properties...> {
public:
    constexpr static int id = IndexStorage<Properties...>::id + 1;

    using type = Property;

    template<typename Type>
    static constexpr int get() {
        if constexpr(std::is_same_v<Type, type>) {
            return id;
        } else {
            return  IndexStorage<Properties...>::template get<Type>();
        }
    }
};

template <>
class IndexStorage<>
{
public:
    constexpr static int id = 0;

    template<typename Type>
    constexpr static int get() {
        return  id;
    }
};

}