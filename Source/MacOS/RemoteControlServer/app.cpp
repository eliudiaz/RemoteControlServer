#include "apiv2.h"
#include "apiv3.h"
#include "app.h"
#include "authentication.h"
#include "logger.h"
#include "settings.h"

#include <QDebug>

App::App()
{
    ip = "Unknown";
    license = new License();
    appVersion = "Unknown";
    appName = "Unknown";
    deviceName = "Unknown";
    osVersion = "Unknown";
    status = "Unknown";
    pin = "";

    isConnected = false;
}

void App::onConnect()
{
    isConnected = true;
    Logger::Instance()->add(deviceName + " connected");
    // Server.gui.showNotification
    QString label = (appName == "Unknown" || appVersion == "Unknown")
            ? deviceName : appName + " " + appVersion + " on a " + deviceName;
    Logger::Instance()->trackEvent("App", "Connect", label);
    Settings::Instance()->showGuide = false;
}

void App::onDisconnect()
{
    isConnected = false;
    Logger::Instance()->add(deviceName + " disconnected");
}

void App::onPause()
{
    Logger::Instance()->add(deviceName + " paused the connection");
}

void App::onResume()
{
    Logger::Instance()->add(deviceName + " resumed the connection");
}

void App::onBroadCast(Command &command)
{
    qDebug() << "onBroadcast";
    Logger::Instance()->add("Connection request from " + ip);
    if (Authentication::Instance()->isAuthenticated(ip, pin))
    {
        qDebug() << "isauthenticated";
        Logger::Instance()->add("Allowing to connec");
        answerBroadCast(command);
    }
    else if (Settings::Instance()->usePin)
    {
        qDebug() << "requestpin";
        Logger::Instance()->add("Requesting Pin");
        requestPin(command);
    }
    else
    {
        qDebug() << "else";
        Logger::Instance()->add("Connection blocked");
        refuseBroadCast(command);
        //Server.gui.showNotification("Connection blocked", "A connection attempt from " & ip & " has been blocked.")
    }
}

void App::answerBroadCast(Command &command)
{
    switch (command.api) {
    case 3:
        ApiV3::Instance()->answerBroadCast(*this);
        break;
    case 2:
    case 1:
        qDebug() << "version 1 or 2";
        ApiV2::Instance()->answerBroadCast(*this);
        break;
    default:
        ApiV3::Instance()->answerBroadCast(*this);
        break;
    }
}

void App::refuseBroadCast(Command &command)
{

}

void App::requestPin(Command &command)
{

}

void App::detectOs()
{

}