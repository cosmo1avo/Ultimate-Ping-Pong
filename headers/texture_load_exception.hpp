#pragma once

#include "engine_exceptions.hpp"

class texture_load_exception : public engine_exceptions {
public:
    explicit texture_load_exception(const std::string& msg)
        : engine_exceptions("Texture Load Error: " + msg) {}
};

