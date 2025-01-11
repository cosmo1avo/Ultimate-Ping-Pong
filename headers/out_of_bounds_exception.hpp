#pragma once

#include "../headers/engine_exceptions.hpp"

class out_of_bounds_exception : public engine_exceptions {
public:
    explicit out_of_bounds_exception(const std::string& message)
        : engine_exceptions(message) {}
};

