#pragma once

#include <exception>
#include <string>


class engine_exceptions : public std::exception {
private:
    std::string message;

public:
    explicit engine_exceptions(const std::string& msg)
        : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

