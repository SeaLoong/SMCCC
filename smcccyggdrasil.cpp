#include "smcccyggdrasil.h"

SMCCCYggdrasil::SMCCCYggdrasil(){}

bool SMCCCYggdrasil::Authenticate(){
    //有关以下内容的解释自行查阅 http://wiki.vg/Authentication#Authenticate
    QJsonObject payload,agent;
    agent.insert("name","Minecraft");
    agent.insert("version",1);
    payload.insert("agent",agent);
    payload.insert("username",username);
    payload.insert("password",password);
    if(!clientToken.isEmpty())payload.insert("clientToken",clientToken);
    postData = QJsonDocument(payload).toJson();
    if(net.httpPost("https://authserver.mojang.com/authenticate",returnData,postData) != 200)return false;
    QJsonObject jsonObj = QJsonDocument::fromJson(returnData).object();
    if(!clientToken.isEmpty() && clientToken != jsonObj.value("clientToken").toString())return false;
    accessToken = jsonObj.value("accessToken").toString();
    uuid = jsonObj.value("selectedProfile").toObject().value("id").toString();
    name = jsonObj.value("selectedProfile").toObject().value("name").toString();
    if(accessToken.isEmpty() || uuid.isEmpty() || name.isEmpty())return false;
    QJsonArray userTypePayload;
    userTypePayload.append(name);
    postData = QJsonDocument(userTypePayload).toJson();
    if(net.httpPost("https://api.mojang.com/profiles/minecraft",returnData,postData) != 200)return false;
    QJsonArray jsonArr = QJsonDocument::fromJson(returnData).array();
    if(jsonArr.isEmpty() || !jsonArr.at(0).toObject().value("legacy").toBool())userType = "mojang";
    else userType = "legacy";
    return true;
}

bool SMCCCYggdrasil::Refresh(){
    //有关以下内容的解释自行查阅 http://wiki.vg/Authentication#Refresh
    QJsonObject payload;
    payload.insert("accessToken",accessToken);
    if(!clientToken.isEmpty())payload.insert("clientToken",clientToken);
    postData = QJsonDocument(payload).toJson();
    if(net.httpPost("https://authserver.mojang.com/refresh",returnData,postData) != 200)return false;
    QJsonObject jsonObj = QJsonDocument::fromJson(returnData).object();
    if(!clientToken.isEmpty() && clientToken != jsonObj.value("clientToken").toString())return false;
    accessToken = jsonObj.value("accessToken").toString();
    return true;
}

bool SMCCCYggdrasil::Validate(){
    //有关以下内容的解释自行查阅 http://wiki.vg/Authentication#Validate
    QJsonObject payload;
    payload.insert("accessToken",accessToken);
    if(!clientToken.isEmpty())payload.insert("clientToken",clientToken);
    postData = QJsonDocument(payload).toJson();
    if(net.httpPost("https://authserver.mojang.com/validate",returnData,postData) != 204)return false;
    return true;
}

bool SMCCCYggdrasil::Signout(){
    //有关以下内容的解释自行查阅 http://wiki.vg/Authentication#Signout
    QJsonObject payload;
    payload.insert("username",username);
    payload.insert("password",password);
    postData = QJsonDocument(payload).toJson();
    if(net.httpPost("https://authserver.mojang.com/signout",returnData,postData) != 200)return false;
    return true;
}

bool SMCCCYggdrasil::Invalidate(){
    if(clientToken.isEmpty())return true;
    //有关以下内容的解释自行查阅 http://wiki.vg/Authentication#Invalidate
    QJsonObject payload;
    payload.insert("accessToken",accessToken);
    payload.insert("clientToken",clientToken);
    postData = QJsonDocument(payload).toJson();
    if(net.httpPost("https://authserver.mojang.com/invalidate",returnData,postData) != 200)return false;
    return true;
}

QString SMCCCYggdrasil::getError(){
    //有关错误代码的解释自行查阅 http://wiki.vg/Authentication#Errors
    return QJsonDocument::fromJson(returnData).object().value("error").toString();
}
