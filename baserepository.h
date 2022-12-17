#pragma once

#include <QObject>

template<class T>
class BaseRepository
{
public:
    BaseRepository();
    virtual ~BaseRepository();

    virtual void getAll() = 0;
    virtual void insert(const T&) = 0;
    virtual void deleteOne(const T&) = 0;
    virtual void update(const T&) = 0;
};

