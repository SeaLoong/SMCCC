#include "json_libraries.h"

QString Json_Libraries::process(){
    QString ret = "OK";
    //检查libraries
    foreach (QJsonValue _value, Json::_libraries) {
        QJsonObject _object = _value.toObject();
        //判断rules
        QJsonArray rules = _object.value("rules").toArray();
        if(!isAllow(rules))continue;

        QString name = _object.value("name").toString();
        //获取native_string
        QJsonObject natives = _object.value("natives").toObject();
        QString native_string = getNativesString(natives);
        //获取下载需要的信息
        QJsonObject downloads = _object.value("downloads").toObject();
        QString _path,_url,_sha1;
        int _size;
        getDownloadsInfo(downloads,native_string,_path,_url,_sha1,_size);
        //分析出文件路径(libraries\ + ...)
        QString _filePath = Launcher::getFilePath(name,native_string);//理论上和_path相同
        if(_path.isEmpty() || _url.isEmpty()){//判断是否为forge版本
            _url = _object.value("url").toString("https://libraries.minecraft.net") + "/" + _filePath;
            _url.replace("\\","/");
        }
        _filePath = Json::_GameDirPath + "\\libraries\\" + _filePath;//变为绝对路径
        //获取解压需要的信息
        QJsonObject extract = _object.value("extract").toObject();
        if(!extract.isEmpty())Json_Natives::append(_filePath,extract);
        //把文件路径加入-cp参数中
        Json::_args_cp.append(_filePath + ";");
        if(!Launcher::isFileExist(_filePath) || (Json::_FileCheck && (!Launcher::checkFileSize(_filePath,_size) || !Launcher::checkFileSHA1(_filePath,_sha1)))){
            if(QUrl(_url).isValid() && _url.toLower().startsWith("http")){
                DownloadInfo info(_filePath,_url,_sha1,_size);
                Json::_DownloadInfoList.append(info);
                ret = "Download";
            }else{
                return "Error";
            }
        }
    }
    return ret;
}

bool Json_Libraries::isAllow(const QJsonArray &rules){//通过rules判断是否需要下载
    if(rules.isEmpty())return true;
    bool allow = false;
    foreach (QJsonValue rule,rules){
        QString os = rule.toObject().value("os").toObject().value("name").toString("");
        if(os == Json::_OS){
            if(rule.toObject().value("action").toString() == "allow")return true;
            return false;
        }else if(os.isEmpty()){
            if(rule.toObject().value("action").toString() == "allow")allow = true;
            else allow = false;
        }
    }
    return allow;
}

QString Json_Libraries::getNativesString(const QJsonObject &jsonobj){
    QJsonObject nativesObj = jsonobj;
    QString native_string = nativesObj.value(Json::_OS).toString("");
    native_string.replace("${arch}",Json::_arch);
    return native_string;
}

void Json_Libraries::getDownloadsInfo(const QJsonObject &jsonobj, const QString &native_string, QString &path, QString &url, QString &sha1, int &size){
    QJsonObject _object;
    if(!native_string.isEmpty())_object = jsonobj.value("classifiers").toObject().value(native_string).toObject();
    else _object = jsonobj.value("artifact").toObject();
    path = _object.value("path").toString("");
    url = _object.value("url").toString("");
    sha1 = _object.value("sha1").toString("");
    size = _object.value("size").toInt(0);
}
