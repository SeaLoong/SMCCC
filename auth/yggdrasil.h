#ifndef YGGDRASIL_H
#define YGGDRASIL_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "net/net.h"

class Yggdrasil
{
public:
    Yggdrasil();

    QString username,password,uuid,accessToken,clientToken,name,userType;

    bool Authenticate();//获取accessToken,uuid,name(要求用户名和密码)
    bool Refresh();//获取一个新的accessToken(要求当前accessToken有效)
    bool Validate();//检查accessToken是否可用
    bool Signout();//使当前accessToken无效(要求用户名和密码)
    bool Invalidate();//使当前clientToken无效(要求当前accessToken和clientToken有效))
    QString getError();//返回错误代码
private:
    QByteArray returnData,postData;
    Net net;
};

#endif // YGGDRASIL_H
