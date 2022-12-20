#pragma once

#include <QString>

#include "group.h"
#include "passport.h"

struct Student
{
public:
    Student() {};

    QString fullName;
    Group group;
};

