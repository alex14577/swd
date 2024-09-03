#include "ioc.hpp"
#include <algorithm>
#include <functional>
#include <string_view>
#include <unordered_map>


namespace ioc {

Ioc &get(std::string_view _scope)
{
    static std::unordered_map<std::size_t, Ioc> iocs;

    auto hash = std::hash<std::string_view>{}(_scope);

    if (auto it = std::ranges::find_if(iocs, [=](auto& ioc){
                                              return ioc.second.hash() == hash;
                                          }); it == iocs.end()) {
        auto res = iocs.emplace(hash, _scope);
        return res.first->second;
    } else {
        return it->second;
    }
}

std::vector<CreatorCleaner *> Ioc::scopes;

}