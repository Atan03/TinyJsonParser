#pragma once
#include <stdexcept>
namespace atan{
namespace json{
    inline void Error(const char* message){throw std::logic_error(message);}
}
}