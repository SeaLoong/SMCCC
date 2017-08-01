#ifndef SMCCC_H
#define SMCCC_H

#include "smccc_global.h"
#include "json/smcccjson.h"
#include "auth/smcccauth.h"

class SMCCCSHARED_EXPORT SMCCC
{
public:
    struct DownloadInfo {
        QString filepath,url,sha1;
        int size;
    };

    SMCCC();
    SMCCC(const QString &version,const QString &dotminecraftdirpath);

    void setAssetsCheck(bool assetscheck);//可选，默认为true
    void setFileCheck(bool filecheck);//可选，默认为true
    void setMergeInheritsFrom(bool mergeinheritsfrom);//可选，默认为true
    void setOS(const QString &os);//可选，"windows","osx","",默认为"windows"
    void setArch(const QString &arch);//可选，"32"or"64",默认为"32"
    void setVersion(const QString &version);
    void setDotMinecraftDirPath(const QString &dotminecraftdirpath);
    void setAssetsDirPath(const QString &assetsdirpath);//可选
    void setLibrariesDirPath(const QString &librariesdirpath);//可选
    void setVersionsDirPath(const QString &versiondirpath);//可选
    void setNativesDirPath(const QString &nativesdirpath);//可选
    void setJarFilePath(const QString &jarfilepath);//可选
//----------------------------------------//
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

    SMCCCJson _Json;

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

#endif // SMCCC_H
