#include "json.h"

int Json::_Step = 0;

QLinkedList<DownloadInfo> Json::_DownloadInfoList;
QString Json::_arch;
QString Json::_OS;
bool Json::_AssetsCheck;
bool Json::_FileCheck;
QString Json::_GameDirPath;
QString Json::_VersionDirPath;
QString Json::_VersionID;
QString Json::_JarFilePath;
QString Json::_NativesDirpath;

QJsonObject Json::_JsonObj;
QJsonObject Json::_assetIndex;
QString Json::_assets;
QJsonObject Json::_downloads;
QString Json::_id;
QJsonArray Json::_libraries;
QString Json::_mainClass;
QString Json::_minecraftArguments;
QString Json::_inheritsFrom;
QString Json::_jar;

QString Json::_args_cp;

QLinkedList<DownloadInfo> Json::getDownloadInfoList(){
    QLinkedList<DownloadInfo> _list = _DownloadInfoList;
    _DownloadInfoList.clear();
    return _list;
}

QString Json::get_args_cp(){
    return _args_cp;
}

QString Json::get_args_minecraftArguments(){
    return _minecraftArguments;
}

QString Json::get_args_mainClass(){
    return _mainClass;
}

QString Json::get_NativesDirpath(){
    return _NativesDirpath;
}

QString Json::process(){//_Step表示启动第几步，减少启动需要下载时再次启动的时间，0~4共5步
    //读取versions\[版本]\[版本].json文件
    _DownloadInfoList.clear();
    if(_Step == 0){
        _args_cp = "\"";
        QString _jsonFilePath = _VersionDirPath + "\\" + _VersionID + "\\" + _VersionID + ".json";
        Log::write("Json分析","分析文件: " + _jsonFilePath);
        if(!Launcher::isFileExist(_jsonFilePath))return "JsonFileNotExist";
        QFile _jsonFile(_jsonFilePath);
        _jsonFile.open(QIODevice::ReadOnly);
        _JsonObj = QJsonDocument::fromJson(_jsonFile.readAll()).object();
        _jsonFile.close();
        //初始化变量
        _assetIndex = _JsonObj.value("assetIndex").toObject();
        _assets = _JsonObj.value("assets").toString("");
        _downloads = _JsonObj.value("downloads").toObject();
        _id = _JsonObj.value("id").toString("");
        _libraries = _JsonObj.value("libraries").toArray();
        _mainClass = _JsonObj.value("mainClass").toString("");
        _minecraftArguments = _JsonObj.value("minecraftArguments").toString("");
        _inheritsFrom = _JsonObj.value("inheritsFrom").toString("");
        _jar = _JsonObj.value("jar").toString("");
        _NativesDirpath = _VersionDirPath + "\\" + _VersionID + "\\" + "natives";
        _JarFilePath = _VersionDirPath + "\\" + _VersionID + "\\" + _id + ".jar";
        if(!_jar.isEmpty() && !Launcher::isFileExist(_JarFilePath))_JarFilePath = _VersionDirPath + "\\" + _jar + "\\" + _jar + ".jar";
        _Step = 1;
    }
    if(_Step == 1){
        //处理inheritsFrom
        Log::write("Json分析","分析inheritsFrom");
        if(!_inheritsFrom.isEmpty()){
            if(Json_InheritsFrom::process()){
                _JsonObj.insert("assetIndex",_assetIndex);
                _JsonObj.insert("assets",_assets);
                _JsonObj.insert("downloads",_downloads);
                _JsonObj.insert("id",_id);
                _JsonObj.insert("libraries",_libraries);
                _JsonObj.insert("mainClass",_mainClass);
                _JsonObj.insert("minecraftArguments",_minecraftArguments);
                _JsonObj.remove("inheritsFrom");
                _JsonObj.remove("jar");
                if(!_jar.isEmpty() && Launcher::isFileExist(_VersionDirPath + "\\" + _jar + "\\" + _jar + ".jar")){
                    QFile::copy(_VersionDirPath + "\\" + _jar + "\\" + _jar + ".jar",_VersionDirPath + "\\" + _VersionID + "\\" + _id + ".jar");
                }
                _JarFilePath = _VersionDirPath + "\\" + _VersionID + "\\" + _id + ".jar";
                QFile _jsonFile(_VersionDirPath + "\\" + _VersionID + "\\" + _VersionID + ".json");
                _jsonFile.open(QIODevice::WriteOnly);
                QJsonDocument _JsonDoc;
                _JsonDoc.setObject(_JsonObj);
                _jsonFile.write(_JsonDoc.toJson());
                _jsonFile.close();
            }else return "InheritsfromFileNotExist";
        }
        _Step = 2;
    }
    if(_Step == 2){
        Log::write("Json分析","分析downloads");
        bool ret1 = Json_Downloads::process();//处理downloads和
        Log::write("Json分析","分析libraries");
        QString ret2 = Json_Libraries::process();//处理ibraries
        bool ret3 = false;
        if(_AssetsCheck){
            Log::write("Json分析","分析assetsIndex");
            ret3 = Json_Assets::processIndexFile();
        }
        if(ret2 == "Error")return "LibrariesFileNotExist";
        if(!ret1 || (_AssetsCheck && !ret3) || ret2 == "Download")return "Download";
        Log::write("Json分析","检查并解压natives文件");
        Json_Natives::process();//解压natives文件
        _Step = 3;
    }
    if(_Step == 3){
        //处理assetIndex
        if(_AssetsCheck){
            Log::write("Json分析","分析assets");
            bool ret = Json_Assets::processFile();
            if(!ret)return "Download";
        }
        _Step = 4;
    }
    if(_Step == 4){
        //对启动参数额外处理
        _args_cp.append(_JarFilePath);
        _args_cp.append("\"");
        _minecraftArguments.replace("${version_name}","\"" + _id + "\"");
        _minecraftArguments.replace("${game_directory}","\"" + _GameDirPath + "\"");
        _minecraftArguments.replace("${assets_root}","\"" + _GameDirPath + "\\assets\"");
        _minecraftArguments.replace("${game_assets}","\"" + _GameDirPath + "\\assets\\virtual\\legacy\"");
        _minecraftArguments.replace("${assets_index_name}","\"" + _assets + "\"");
        _minecraftArguments.replace("${user_properties}","{}");
        _minecraftArguments.replace("${auth_session}","-");
        return "OK";
    }
    return "Error";
}

