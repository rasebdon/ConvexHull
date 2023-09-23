#include "programOptions.h"
#include <iostream>

programOptions::programOptions(int argc, char **argv)
{
    for (int i = 1; i < argc;)
    {
        std::string curIdentifier = argv[i++];

        std::string curValue = "";
        if (curIdentifier.find("--") != std::string::npos)
            curValue = argv[i++];

        args[curIdentifier] = curValue;
    }
    
}

std::string programOptions::getArg(const std::string &key) const
{
    try
    {
        return args.at(key);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }
}

bool programOptions::hasArg(const std::string &key) const
{
    return args.find(key) != args.end();
}
