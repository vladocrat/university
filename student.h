#pragma once

#include <string>

#include "group.h"
#include "passport.h"

class Student
{
public:
    Student(const std::string& name, const Group& group);

    std::string name() const {return m_fullName;}
    Group group()      const {return m_group;}

private:
    std::string m_fullName;
    Group m_group;
    Passport m_passport;
    //dormitory
    //medical insurance
};

