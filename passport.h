#pragma once

class Passport
{
public:
    enum Type {
        General,
        Abroad
    };

    struct Series
    {
        Series(int s) // make int 32
        {

        }

        int a; // make int 32
    };

    struct Number
    {

    };

    Passport();

    Type type() const {return t;}

private:
    Type t;
};

