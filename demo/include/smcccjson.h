#ifndef SMCCCJSON_H
#define SMCCCJSON_H

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QLinkedList>
#include <QCryptographicHash>
#include "smcccdownloadinfo.h"
#include "smcccjsonassets.h"
#include "smcccjsondownloads.h"
#include "smcccjsoninheritsfrom.h"
#include "smcccjsonlibraries.h"
#include "smcccjsonnatives.h"

class SMCCCJson
{
public:
    SMCCCJson();
    SMCCCJson(const QString &version,const QString &dotminecraftdirpath);
    int process();
    /*返回值：
     * -1:未设置DotMinecraftDirPath或Version,
     * 0:OK,
     * 1:Download,
     * 2:JsonFileNotFound,
     * 3:InheritsFromJsonFileNotFound
     * 4:LibrariesFileNotFound
     * 5:JsonError
    */

    bool AssetsCheck,FileCheck,MergeInheritsFrom;

    QString Arch,OS;
    QString Version,DotMinecraftDirPath,AssetsDirPath,LibrariesDirPath,VersionsDirPath,NativesDirPath,JarFilePath;

    QLinkedList<SMCCCDownloadInfo> DownloadInfoList;
    int _Step;
    QString _args_cp;
    QJsonObject _JsonObj;
    QJsonObject _assetIndex;
    QString _assets;
    QJsonObject _downloads;
    QString _id;
    QJsonArray _libraries;
    QString _mainClass;
    QString _minecraftArguments;
    QString _inheritsFrom;
    QString _jar;
    QString _type;
    SMCCCJsonAssets *_JsonAssets;
    SMCCCJsonDownloads *_JsonDownloads;
    SMCCCJsonInheritsFrom *_JsonInheritsFrom;
    SMCCCJsonLibraries *_JsonLibraries;
    SMCCCJsonNatives *_JsonNatives;
    bool isFileExist(const QString &filePath);
    bool isDirExist(const QString &dirPath);
    bool checkFileSize(const QString &filePath,int size);
    bool checkFileSHA1(const QString &filePath,const QString &sha1);

};

#endif // SMCCCJSON_H
