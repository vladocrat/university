#pragma once

#include "userdata.h"
#include "document.h"

struct GapYear
{
    QString start_date;
    QString end_date;
    Document document;
    UserData* creator;
};
