#ifndef JSON_H
#define JSON_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QLinkedList>
#include "json_assets.h"
#include "json_downloads.h"
#include "json_inheritsfrom.h"
#include "json_libraries.h"
#include "json_natives.h"

class Json
{
public:

    static QLinkedList<DownloadInfo> getDownloadInfoList();
    static QString get_NativesDirpath();
    static QString get_args_cp();
    static QString get_args_minecraftArguments();
    static QString get_args_mainClass();
    static QString process();//返回错误文本

    static int _Step;

    static QLinkedList<DownloadInfo> _DownloadInfoList;
    static QString _arch;
    static QString _OS;
    static bool _FileCheck;
    static bool _AssetsCheck;
    static QString _GameDirPath;
    static QString _VersionDirPath;
    static QString _VersionID;
    static QString _JarFilePath;
    static QString _NativesDirpath;

    static QJsonObject _JsonObj;
    static QJsonObject _assetIndex;
    static QString _assets;
    static QJsonObject _downloads;
    static QString _id;
    static QJsonArray _libraries;
    static QString _mainClass;
    static QString _minecraftArguments;
    static QString _inheritsFrom;
    static QString _jar;

    static QString _args_cp;

private:
    Json();

};

#endif // JSON_H
