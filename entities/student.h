#pragma once

#include <QString>

#include "group.h"

struct Student
{
public:
    Student() {};

    QString toString() const {return fullName + " " + group.name;}

    QString fullName;
    Group group;
};

