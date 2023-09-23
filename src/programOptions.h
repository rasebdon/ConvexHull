#pragma once
#include <string>
#include <map>

class programOptions
{
private:
    std::map<std::string, std::string> args;
public:
    programOptions(int argc, char **argv);
    std::string getArg(const std::string& key);
};
