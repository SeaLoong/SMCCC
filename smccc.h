#ifndef SMCCC_H
#define SMCCC_H

#include "smccc_global.h"
#include "smcccjson.h"
#include "smcccauth.h"

class SMCCCSHARED_EXPORT SMCCC
{
public:
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

    void setAuthMethod(int authmethod);
    void set_username(const QString &username);
    void set_password(const QString &password);
    void set_accessToken(const QString &accessToken);
    void set_clientToken(const QString &clientToken);

    void setArgs_AutoConnect(const QString &host,const QString &port);
    void setArgs_Xmx(int xmx);
    void setArgs_Resolution(int width = 854,int height = 480,bool fullscreen = false);
    void setArgs_VersionType(const QString &versiontype);
    void setArgs_AdditionArgsJava(const QString &additionArgs);
    void setArgs_AdditionArgsMc(const QString &additionArgs);

    QString getArgsString();
    QStringList getArgsStringList();
    QLinkedList<SMCCCDownloadInfo> getDownloadInfoList();
    QString getAuthError();

    int processLaunchArgs();
    /*返回值：
     * -1:未设置游戏目录/Json文件路径等,
     * 0:OK,
     * 1:Download,
     * 2:JsonFileNotFound,
     * 3:InheritsFromJsonFileNotFound
     * 4:LibrariesFileNotFound
     * 5:JsonError
     * 6:AuthFaild
     * 7:UnknownError
    */

private:
    SMCCCJson *_Json = new SMCCCJson;
    SMCCCAuth *_Auth = new SMCCCAuth;

    QString ArgsString;
    QStringList ArgsStringList;

    int _Step;
    int _args_Xmx = 1024;
    int _args_width = 854,_args_height = 480;
    bool _args_fullscreen = false;
    QString _args_versionType;
    QString _args_host,_args_port;
    QString _args_additionArgsJava;
    QString _args_additionArgsMc;

};

#endif // SMCCC_H
