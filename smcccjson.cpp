#include "smcccjson.h"

SMCCCJson::SMCCCJson(){}

SMCCCJson::SMCCCJson(const QString &version,const QString &dotminecraftdirpath){
    Version = version,DotMinecraftDirPath = dotminecraftdirpath;
}

int SMCCCJson::process(){//_Step表示启动第几步，减少启动需要下载时再次启动的时间，0~4共5步
    if(DotMinecraftDirPath.isEmpty())return -1;
    if(AssetsDirPath.isEmpty())AssetsDirPath = DotMinecraftDirPath + "/assets";
    if(LibrariesDirPath.isEmpty())LibrariesDirPath = DotMinecraftDirPath + "/libraries/";
    if(VersionsDirPath.isEmpty())VersionsDirPath = DotMinecraftDirPath + "/versions";
    if(NativesDirPath.isEmpty())NativesDirPath = DotMinecraftDirPath + "/natives/" + Version;
    //读取versions\[版本]\[版本].json文件
    if(_Step == 0){
        DownloadInfoList.clear();
        _args_cp = "\"";
        if(!SMCCCJson::isFileExist(VersionsDirPath + "/" + Version + "/" + Version + ".json"))return 2;
        QFile _jsonFile(VersionsDirPath + "/" + Version + "/" + Version + ".json");
        _jsonFile.open(QIODevice::ReadOnly);
        _JsonObj = QJsonDocument::fromJson(_jsonFile.readAll()).object();
        _jsonFile.close();
        //初始化变量
        _assetIndex = _JsonObj.value("assetIndex").toObject();
        _assets = _JsonObj.value("assets").toString();
        _downloads = _JsonObj.value("downloads").toObject();
        _id = _JsonObj.value("id").toString();
        _libraries = _JsonObj.value("libraries").toArray();
        _mainClass = _JsonObj.value("mainClass").toString();
        _minecraftArguments = _JsonObj.value("minecraftArguments").toString();
        _inheritsFrom = _JsonObj.value("inheritsFrom").toString();
        _jar = _JsonObj.value("jar").toString();
        if(JarFilePath.isEmpty())JarFilePath = VersionsDirPath + "/" + Version + "/" + _id + ".jar";
        if(!_jar.isEmpty() && !isFileExist(JarFilePath))JarFilePath = VersionsDirPath + "/" + _jar + "/" + _jar + ".jar";
        _Step = 1;
    }
    if(_Step == 1){
        //处理inheritsFrom
        if(!_inheritsFrom.isEmpty()){
            if(_JsonInheritsFrom->process(this)){
                if(MergeInheritsFrom){
                    _JsonObj.insert("assetIndex",_assetIndex);
                    _JsonObj.insert("assets",_assets);
                    _JsonObj.insert("downloads",_downloads);
                    _JsonObj.insert("id",_id);
                    _JsonObj.insert("libraries",_libraries);
                    _JsonObj.insert("mainClass",_mainClass);
                    _JsonObj.insert("minecraftArguments",_minecraftArguments);
                    _JsonObj.remove("inheritsFrom");
                    _JsonObj.remove("jar");
                    if(!_jar.isEmpty() && isFileExist(VersionsDirPath + "/" + _jar + "/" + _jar + ".jar")){
                        QFile::copy(VersionsDirPath + "/" + _jar + "/" + _jar + ".jar",VersionsDirPath + "/" + Version + "/" + _id + ".jar");
                    }
                    JarFilePath = VersionsDirPath + "/" + Version + "/" + _id + ".jar";
                    QFile _jsonFile(VersionsDirPath + "/" + Version + "/" + Version + ".json");
                    _jsonFile.open(QIODevice::WriteOnly);
                    QJsonDocument _JsonDoc;
                    _JsonDoc.setObject(_JsonObj);
                    _jsonFile.write(_JsonDoc.toJson());
                    _jsonFile.close();
                }
            }else return 3;
        }
        _Step = 2;
    }
    if(_Step == 2){
        bool ret1 = _JsonDownloads->process(this);//处理downloads和
        int ret2 = _JsonLibraries->process(this,_JsonNatives);//处理ibraries
        bool ret3 = false;
        if(AssetsCheck)ret3 = _JsonAssets->processIndex(this);
        if(ret2 == 2)return 4;
        if(!ret1 || (AssetsCheck && !ret3) || ret2 == 1)return 1;
        _JsonNatives->process(this);//解压natives文件
        _Step = 3;
    }
    if(_Step == 3){
        //处理assetIndex
        if(AssetsCheck){
            bool ret = _JsonAssets->process(this);
            if(!ret)return 1;
        }
        _Step = 4;
    }
    if(_Step == 4){
        //对启动参数额外处理
        _args_cp.append(JarFilePath);
        _args_cp.append("\"");
        _minecraftArguments.replace("${version_name}","\"" + _id + "\"");
        _minecraftArguments.replace("${game_directory}","\"" + DotMinecraftDirPath + "\"");
        _minecraftArguments.replace("${assets_root}","\"" + AssetsDirPath + "\"");
        _minecraftArguments.replace("${game_assets}","\"" + AssetsDirPath + "/virtual/legacy\"");
        _minecraftArguments.replace("${assets_index_name}","\"" + _assets + "\"");
        _minecraftArguments.replace("${user_properties}","{}");
        _minecraftArguments.replace("${auth_session}","-");
        return 0;
    }
    return 5;
}

bool SMCCCJson::isDirExist(const QString &dirPath){
    QDir dir(dirPath);
    if(!dir.exists())
        return dir.mkpath(dir.absolutePath());
    return true;
}

bool SMCCCJson::isFileExist(const QString &filePath){
    QFileInfo info(filePath);
    return info.isFile();
}

bool SMCCCJson::checkFileSize(const QString &filePath, int size){
    return size <=0 || QFileInfo(filePath).size() == size;
}

bool SMCCCJson::checkFileSHA1(const QString &filePath, const QString &sha1){
    if(sha1.isEmpty())return true;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))return false;
    QByteArray data = file.readAll();
    file.close();
    QString _SHA1 = QCryptographicHash::hash(data,QCryptographicHash::Sha1).toHex().toLower();
    return _SHA1 == sha1.toLower();
}
