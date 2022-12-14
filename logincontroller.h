#pragma once
#include <QObject>
#include <QQmlEngine>

class LoginController final : public QObject
{
    Q_OBJECT
public:

    static LoginController* instance()
    {
        static LoginController lc;
        return &lc;
    }

    bool login(const std::string& email, const std::string& password) const;

    static void registerType()
    {
        qmlRegisterSingletonInstance<LoginController>
                ("LoginController", 1, 0,"LoginController",
                 LoginController::instance());
    }

private:
    LoginController() = default;
    ~LoginController() = default;
    LoginController(const LoginController&) = delete;
    LoginController(LoginController&&) = delete;
    LoginController operator=(const LoginController&) = delete;
};

#define loginController LoginController::instance()

