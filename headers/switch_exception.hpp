#pragma once

#include "../headers/engine_exceptions.hpp"

class switch_exception : public engine_exceptions {
public:
    explicit switch_exception(const std::string& message)
        : engine_exceptions(message) {}
};

