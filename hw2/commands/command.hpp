#pragma once


namespace game {

class Command {
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
};

}