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
     * -1:未设置游戏目录/Json文件路径等,
     * 0:OK,
     * 1:Download,
     * 2:JsonFileNotFound,
     * 3:InheritsFromJsonFileNotFound
     * 4:LibrariesFileNotFound
     * 5:JsonError
    */

    bool AssetsCheck = true;
    bool FileCheck = true;
    bool MergeInheritsFrom = true;

    QString Arch = "32",OS = "windows";
    QString Version,DotMinecraftDirPath,AssetsDirPath,LibrariesDirPath,VersionsDirPath,NativesDirPath,JarFilePath;

    QLinkedList<SMCCCDownloadInfo> DownloadInfoList;
    int _Step = 0;
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
    SMCCCJsonAssets *_JsonAssets = new SMCCCJsonAssets;
    SMCCCJsonDownloads *_JsonDownloads = new SMCCCJsonDownloads;
    SMCCCJsonInheritsFrom *_JsonInheritsFrom = new SMCCCJsonInheritsFrom;
    SMCCCJsonLibraries *_JsonLibraries = new SMCCCJsonLibraries;
    SMCCCJsonNatives *_JsonNatives = new SMCCCJsonNatives;
    bool isFileExist(const QString &filePath);
    bool isDirExist(const QString &dirPath);
    bool checkFileSize(const QString &filePath,int size);
    bool checkFileSHA1(const QString &filePath,const QString &sha1);

};

#endif // SMCCCJSON_H
