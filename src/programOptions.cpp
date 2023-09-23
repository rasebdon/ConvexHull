#include "programOptions.h"
#include <iostream>

programOptions::programOptions(int argc, char **argv)
{
    if ((argc - 1) % 2 != 0)
        throw std::runtime_error("Invalid parameter count!");

    for (int i = 1; i < argc;)
    {
        std::string curIdentifier = argv[i++];
        std::string curValue = argv[i++];

        args[curIdentifier] = curValue;
    }
    
}

std::string programOptions::getArg(const std::string &key)
{
    try
    {
        return args[key];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }
}