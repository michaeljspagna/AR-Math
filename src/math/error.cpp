#include <iostream>
#include "error.hpp"

auto Error::throw_error(const std::string &message) -> void
{
    std::string error = "Error: ";
    error += message + ";";

    std::cout << error << std::endl;
}