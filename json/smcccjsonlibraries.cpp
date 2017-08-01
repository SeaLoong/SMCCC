#include "smcccjsonlibraries.h"

int SMCCCJsonLibraries::process(SMCCCJson *Json, SMCCCJsonNatives *JsonNatives){
    int ret = 0;
    //检查libraries
    foreach (QJsonValue _value, _libraries) {
        QJsonObject _object = _value.toObject();
        //判断rules
        QJsonArray rules = _object.value("rules").toArray();
        if(!isAllow(rules,Json))continue;

        QString name = _object.value("name").toString();
        //获取native_string
        QJsonObject natives = _object.value("natives").toObject();
        QString native_string = getNativesString(natives,Json);
        //获取下载需要的信息
        QJsonObject downloads = _object.value("downloads").toObject();
        QString _path,_url,_sha1;
        int _size;
        getDownloadsInfo(downloads,native_string,_path,_url,_sha1,_size);
        //分析出文件路径(libraries\ + ...)
        QString _filePath = getFilePath(name,native_string);//理论上和_path相同
        if(_path.isEmpty() || _url.isEmpty()){//判断是否为forge版本
            _url = _object.value("url").toString("https://libraries.minecraft.net") + "/" + _filePath;
        }
        _filePath = Json->LibrariesDirPath + _filePath;//变为绝对路径
        //获取解压需要的信息
        QJsonObject extract = _object.value("extract").toObject();
        if(!extract.isEmpty())JsonNatives->NativesList.insert(_filePath,extract);
        //把文件路径加入-cp参数中
        Json->_args_cp.append(_filePath + ";");
        if(!Json->isFileExist(_filePath) || (Json->FileCheck && (!Json->checkFileSize(_filePath,_size) || !Json->checkFileSHA1(_filePath,_sha1)))){
            if(QUrl(_url).isValid() && _url.toLower().startsWith("http")){
                SMCCC::DownloadInfo info(_filePath,_url,_sha1,_size);
                Json->DownloadInfoList.append(info);
                ret = 1;
            }else{
                ret = 2;
            }
        }
    }
    return ret;
}

bool SMCCCJsonLibraries::isAllow(const QJsonArray &rules,const SMCCCJson *Json){//通过rules判断是否需要下载
    if(rules.isEmpty())return true;
    bool allow = false;
    foreach (QJsonValue rule,rules){
        QString os = rule.toObject().value("os").toObject().value("name").toString();
        if(os == Json->OS){
            if(rule.toObject().value("action").toString() == "allow")return true;
            return false;
        }else if(os.isEmpty()){
            if(rule.toObject().value("action").toString() == "allow")allow = true;
            else allow = false;
        }
    }
    return allow;
}

QString SMCCCJsonLibraries::getNativesString(const QJsonObject &jsonobj,const SMCCCJson *Json){
    QJsonObject nativesObj = jsonobj;
    QString native_string = nativesObj.value(Json->OS).toString();
    native_string.replace("${arch}",Json->Arch);
    return native_string;
}

void SMCCCJsonLibraries::getDownloadsInfo(const QJsonObject &jsonobj, const QString &native_string, QString &path, QString &url, QString &sha1, int &size){
    QJsonObject _object;
    if(!native_string.isEmpty())_object = jsonobj.value("classifiers").toObject().value(native_string).toObject();
    else _object = jsonobj.value("artifact").toObject();
    path = _object.value("path").toString();
    url = _object.value("url").toString();
    sha1 = _object.value("sha1").toString();
    size = _object.value("size").toInt();
}

QString SMCCCJson::getFilePath(const QString &name,const QString &native_string){
    QString temp = name;//<package>:<name>:<version>
    QString _package,_name,_version;
    int _p1 = temp.indexOf(":");
    int _p2 = temp.lastIndexOf(":");
    _package = temp.left(_p1);
    _name = temp.mid(_p1 + 1,_p2 - _p1 - 1);
    _version = temp.right(temp.length() - _p2 - 1);
    _package.replace(".","/");
    QString _path = _package + "/" + _name + "/" + _version + "/" + _name + "-" + _version;
    if(!native_string.isEmpty())_path += "-" + native_string;
    _path += ".jar";
    return _path;
}
