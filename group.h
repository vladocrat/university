#pragma once

#include <string>

class Group
{
public:
    Group(const std::string& name) : m_name(name){};

private:
    std::string m_name;
};

