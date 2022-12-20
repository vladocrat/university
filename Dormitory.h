#pragma once

#include <QString>
#include <unordered_map>

#include "student.h"

struct Dormitory
{
    enum Status
    {
        Away,
        Present
    };

    struct StatusHash
    {
        std::size_t operator()(Status s) const
        {
            return static_cast<std::size_t>(s);
        }
    };

    QString statusString() const;

    QString address;
    int roomNumber;
    Status status;
    Student* student;
};

static const std::unordered_map<Dormitory::Status, QString, Dormitory::StatusHash> mapStatusToString
{
    {Dormitory::Away, "away"},
    {Dormitory::Present, "present"}
};

static const std::unordered_map<QString, Dormitory::Status, std::hash<QString>> mapStringToStatus
{
    {"away", Dormitory::Away},
    {"present", Dormitory::Present}
};

inline static QString statusToString(Dormitory::Status s)
{
    return mapStatusToString.find(s)->second;
}

inline static Dormitory::Status stringToStatus(const QString& s)
{
    return mapStringToStatus.find(s)->second;
}


inline QString Dormitory::statusString() const
{
    return statusToString(status);
}
