#ifndef AUTH_H
#define AUTH_H

#include "yggdrasil.h"

class Auth
{
public:
    Auth();

    void setAuthMethod(int index);//设置验证方式：0:离线，1:Yggdrasil
    void set_username(const QString &username);//必须
    void set_password(const QString &password);//可选，正版验证需要
    void set_accessToken(const QString &accessToken);//可选，可能可以加快验证速度
    void set_clientToken(const QString &clientToken);//可选
    QString get_auth_player_name();
    QString get_auth_uuid();
    QString get_auth_access_token();
    QString get_user_type();
    QString getError();
    bool auth();

private:

    int AuthMethod = 0;
    QString _username,_password,_accessToken,_clientToken;
    QString _auth_player_name,_auth_uuid,_auth_access_token,_user_type;
    QString Error;
};

#endif // AUTH_H
