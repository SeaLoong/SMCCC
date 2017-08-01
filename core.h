#ifndef CORE_H
#define CORE_H

#include "launcher/global.h"
#include "launcher/sysinfo.h"
#include "core/json/json.h"
#include "core/auth/auth.h"

class Core
{
public:

    void init();
    void setAssetsCheck(bool assetscheck);
    void setFileCheck(bool filecheck);
    void setGameDirPath(const QString &path);
    void setVersionDirPath(const QString &path);
    void setVersionID(const QString &id);

    void setAuthMethod(int authmethod);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setUUID(const QString &uuid);
    void setAccessToken(const QString &accessToken);

    void setArgs_AutoConnect(const QString &address,const QString &port);
    void setArgs_Xmx(int xmx);
    void setArgs_Resolution(int width = 854,int height = 480,bool fullscreen = false);
    void setArgs_VersionType(const QString &text);
    void setArgs_AdditionArgsJava(const QString &additionArgs);
    void setArgs_AdditionArgsMc(const QString &additionArgs);

    void resetLaunch();

    QString getAuth_player_name();
    QString getAuth_uuid();
    QString getAuth_accessToken();
    QLinkedList<DownloadInfo> getDownloadInfoList();

    QString launch();

    int _Step;
    QString _args;
    QStringList _args_list;

private:
    Core();

    Auth _Auth;

    QString _player_name;
    QString _uuid;
    QString _accessToken;

    int _args_Xmx;
    int _args_width;
    int _args_height;
    bool _args_fullscreen;
    QString _args_versionType;
    QString _args_address;
    QString _args_port;
    QString _args_additionArgsJava;
    QString _args_additionArgsMc;

};

#endif // CORE_H
