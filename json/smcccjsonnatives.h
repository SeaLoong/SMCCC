#ifndef SMCCCJSONNATIVES_H
#define SMCCCJSONNATIVES_H

#include <QMap>
#include "json/smcccjson.h"
#include "quazip/JlCompress.h"

class SMCCCJsonNatives
{
public:
    SMCCCJsonNatives();
    void process(SMCCCJson *Json);

    QMap<QString,QJsonObject> NativesList;
};

#endif // SMCCCJSONNATIVES_H
