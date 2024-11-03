#pragma once

#include <modules/module.hpp>

#include <functional>
#include <filesystem>
#include <unordered_map>

#include <boost/function.hpp>
#include <boost/dll/import.hpp>
#include <boost/function/function_fwd.hpp>
#include <vector>


namespace cms::loader {

class Loader {
public:
    Loader(const std::filesystem::path &_root) noexcept;

    module::Plugin create(const std::string &_name) noexcept;

   std::vector<std::string> plugins() noexcept;

private:
    void collect() noexcept;
    void load(const std::filesystem::path &_name);

    using Creator = std::function<module::Creator>;

    std::filesystem::path root;
    std::unordered_map<std::string, Creator> fabrics;
};

}