#ifndef JSON_NATIVES_H
#define JSON_NATIVES_H

#include "core/json/json.h"
#include "ExtraLib/quazip/JlCompress.h"

class Json_Natives
{
public:

    static void append(const QString &filepath,const QJsonObject &jsonobj);
    static void process();

private:
    Json_Natives();

    static QMap<QString,QJsonObject> _listNatives;

};

#endif // JSON_NATIVES_H
