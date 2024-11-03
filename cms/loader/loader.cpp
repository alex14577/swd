#include "loader.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <ranges>
#include <utility>

namespace cms::loader {
    
Loader::Loader(const std::filesystem::path &_root) noexcept :
    root{ _root }
{ 
    collect();
}

std::shared_ptr<module::Module> Loader::create(const std::string &_name) noexcept
{
    if (fabrics.contains(_name)) {
        return fabrics[_name]();
    }

    return nullptr;    
}

std::vector<std::string> Loader::plugins() noexcept
{
    std::vector<std::string> res;

    auto elements = fabrics | std::ranges::views::all | std::ranges::views::elements<0>;
    std::ranges::copy(elements, std::back_inserter(res));

    return res;
}

void Loader::collect() noexcept
{
    namespace fs = std::filesystem;
    for (auto it : fs::directory_iterator(root)) {
        if (!it.is_directory()) {
            load(it.path());
        }
    }
}

void Loader::load(const std::filesystem::path &_path)
{
    try {
        using namespace std::string_literals;
        auto c = boost::dll::import_alias<module::Creator>(
                                                         _path.string(),
                                                        "create_plugin",
                                                        boost::dll::load_mode::append_decorations
                                                    );

        const auto fileName = _path.filename().string();
        fabrics.emplace(fileName.substr(3, fileName.size() - 6), std::move(c));
    } catch (const std::exception &_ex) {
        std::cerr << "No moodule with name " << _path << ". Error: " << _ex.what() << std::endl;
    }
}

}