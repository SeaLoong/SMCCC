#ifndef SMCCCJSONLIBRARIES_H
#define SMCCCJSONLIBRARIES_H

#include "json/smcccjson.h"

class SMCCCJsonLibraries
{
public:
    SMCCCJsonLibraries();
    int process(SMCCCJson *Json,SMCCCJsonNatives *JsonNatives);
    //返回值：0:OK,1:Download,2:Error

private:
    bool isAllow(const QJsonArray &rules, const SMCCCJson *Json);//true:继续；false:跳过
    QString getNativesString(const QJsonObject &jsonobj,const SMCCCJson *Json);
    void getDownloadsInfo(const QJsonObject &jsonobj,const QString &native_string,QString &path,QString &url,QString &sha1,int &size);
    QString getFilePath(const QString &name, const QString &native_string = QString());
};

#endif // SMCCCJSONLIBRARIES_H
