#pragma once

#include "objects/object.hpp"
#include <memory>

namespace game{

class Command;

namespace macro_command {


class Factory {
public:
  Factory(const std::shared_ptr<objects::Object> &_object);

  std::shared_ptr<Command> createMove();

private:
    std::shared_ptr<objects::Object> object;
};

}

}