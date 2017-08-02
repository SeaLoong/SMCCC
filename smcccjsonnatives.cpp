#include "smcccjsonnatives.h"

#include "smcccjson.h"

SMCCCJsonNatives::SMCCCJsonNatives(){}

void SMCCCJsonNatives::process(SMCCCJson *Json){
    Json->isDirExist(Json->NativesDirPath);
    for (QMap<QString,QJsonObject>::ConstIterator it = NativesList.constBegin();it != NativesList.constEnd();++it){
        QString _filePath = it.key();
        if(!Json->isFileExist(_filePath))continue;
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
            if(Json->isFileExist(Json->NativesDirPath + "/" + _name))
                _zipFileList.removeOne(_name);
        }
        //解压
        JlCompress::extractFiles(_filePath,_zipFileList,Json->NativesDirPath);
    }
}
