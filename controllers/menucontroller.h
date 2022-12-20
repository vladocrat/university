#pragma once

#include <QObject>
#include <QQmlEngine>

class MenuController : public QObject
{
    Q_OBJECT
public:
    enum Menues
    {
        Student,
        Contract,
        CapYear,
        Group,
        Passport,
        MedInsurance,
        Dormitory
    };

    static MenuController* instance()
    {
        static MenuController mc;
        return &mc;
    }

    static void registerType()
    {
        qmlRegisterSingletonInstance<MenuController>
                ("MenuController", 1, 0,"MenuController",
                 MenuController::instance());
    }

private:
    MenuController() = default;
    ~MenuController() = default;
    MenuController(const MenuController&) = delete;
    MenuController(MenuController&&) = delete;
    MenuController operator=(const MenuController&) = delete;

    bool menuOpen = false;
};

#define menuController MenuController::instance()
