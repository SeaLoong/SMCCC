#ifndef SMCCCJSONNATIVES_H
#define SMCCCJSONNATIVES_H

#include <QMap>
#include "quazip/JlCompress.h"

class SMCCCJson;
class SMCCCJsonNatives
{
public:
    SMCCCJsonNatives();
    void process(SMCCCJson *Json);

    QMap<QString,QJsonObject> NativesList;
};

#endif // SMCCCJSONNATIVES_H
