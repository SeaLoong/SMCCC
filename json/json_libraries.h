#ifndef JSON_LIBRARIES_H
#define JSON_LIBRARIES_H

#include "core/json/json.h"

class Json_Libraries
{
public:

    static QString process();

private:
    Json_Libraries();

    static bool isAllow(const QJsonArray &rules);//true:继续；false:跳过
    static QString getNativesString(const QJsonObject &jsonobj);
    static void getDownloadsInfo(const QJsonObject &jsonobj,const QString &native_string,QString &path,QString &url,QString &sha1,int &size);


};

#endif // JSON_LIBRARIES_H
