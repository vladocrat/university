#pragma once

#include <QString>

struct PassportTypeString
{
    QString name;
};

class Passport
{
public:
    enum Type {
        General,
        Abroad
    };


    struct Series
    {
        Series(int s)
        {

        }

        int a;
    };

    struct Number
    {

    };

    Passport();

    Type type() const {return t;}

private:
    Type t;
};

