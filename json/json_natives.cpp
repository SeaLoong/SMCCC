#include "json_natives.h"

QMap<QString,QJsonObject> Json_Natives::_listNatives;

void Json_Natives::append(const QString &filepath, const QJsonObject &jsonobj){
    _listNatives.insert(filepath,jsonobj);
}

void Json_Natives::process(){
    Launcher::isDirExist(Json::_NativesDirpath);
    for (QMap<QString,QJsonObject>::ConstIterator it = _listNatives.constBegin();it != _listNatives.constEnd();++it){
        QString _filePath = it.key();
        if(!Launcher::isFileExist(_filePath))continue;
        QJsonObject _NativesObj = it.value();
        QJsonArray _exclude = _NativesObj.value("exclude").toArray();
        QStringList _zipFileList = JlCompress::getFileList(_filePath);
        foreach (QJsonValue _v, _exclude) {
            foreach (QString _name, _zipFileList) {
                if(_name.indexOf(_v.toString()) > -1)
                    _zipFileList.removeOne(_name);
            }
        }
        foreach (QString _name, _zipFileList) {
            if(Launcher::isFileExist(Json::_NativesDirpath + "\\" + _name))
                _zipFileList.removeOne(_name);
        }
        //解压
        JlCompress::extractFiles(_filePath,_zipFileList,Json::_NativesDirpath);
    }
}
