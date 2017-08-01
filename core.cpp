#include "core.h"

Auth Core::_Auth;
int Core::_Step = 0;

QString Core::_args;
QStringList Core::_args_list;

QString Core::_player_name;
QString Core::_uuid;
QString Core::_accessToken;

int Core::_args_Xmx;
int Core::_args_width;
int Core::_args_height;
bool Core::_args_fullscreen;
QString Core::_args_versionType;
QString Core::_args_address;
QString Core::_args_port;
QString Core::_args_additionArgsJava;
QString Core::_args_additionArgsMc;

void Core::init(){
    Json::_arch = SysInfo::is64bit() ? "64" : "32";
    Json::_OS = "windows";
}

void Core::setAssetsCheck(bool assetscheck){
    Json::_AssetsCheck = assetscheck;
}

void Core::setFileCheck(bool filecheck){
    Json::_FileCheck = filecheck;
}

void Core::setGameDirPath(const QString &path){
    Json::_GameDirPath = QDir(path).absolutePath().replace("/","\\");
}

void Core::setVersionDirPath(const QString &path){
    Json::_VersionDirPath = QDir(path).absolutePath().replace("/","\\");
}

void Core::setVersionID(const QString &id){
    Json::_VersionID = id;
}

void Core::setAuthMethod(int authmethod){
    _Auth.setVeifyIndex(authmethod);
}

void Core::setUsername(const QString &username){
    _Auth.setUsername(username);
}

void Core::setPassword(const QString &password){
    _Auth.setPassword(password);
}

void Core::setUUID(const QString &uuid){
    _Auth.setUUID(uuid);
}

void Core::setAccessToken(const QString &accessToken){
    _Auth.setAccessToken(accessToken);
}

void Core::setArgs_AutoConnect(const QString &address, const QString &port){
    _args_address = address;
    _args_port = port;
}

void Core::setArgs_Xmx(int xmx){
    _args_Xmx = xmx;
}

void Core::setArgs_Resolution(int width, int height, bool fullscreen){
    _args_width = width;
    _args_height = height;
    _args_fullscreen = fullscreen;
}

void Core::setArgs_VersionType(const QString &text){
    if(text.isEmpty())_args_versionType = "ShiyiMCL";
    else _args_versionType = "\"" + text + "\"";
}

void Core::setArgs_AdditionArgsJava(const QString &additionArgs){
    _args_additionArgsJava = additionArgs;
}

void Core::setArgs_AdditionArgsMc(const QString &additionArgs){
    _args_additionArgsMc = additionArgs;
}

void Core::resetLaunch(){
    _Step = 0;
    Json::_Step = 0;
}

QString Core::getAuth_player_name(){
    return _player_name;
}

QString Core::getAuth_uuid(){
    return _uuid;
}

QString Core::getAuth_accessToken(){
    return _accessToken;
}

QLinkedList<DownloadInfo> Core::getDownloadInfoList(){
    return Json::getDownloadInfoList();
}

//需要启动三次
QString Core::launch(){//返回"OK","AuthFailed","JsonFileNotExist","InheritsfromFileNotExist","LibrariesFileNotExist","Download"
    if(_Step == 0){
        //登录验证
        Log::write("游戏启动","进行身份验证");
        if(!_Auth.auth())return "AuthFailed";
        _accessToken = _Auth.get_auth_access_token();
        _uuid = _Auth.get_auth_uuid();
        _player_name = _Auth.get_auth_player_name();
        _Step = 1;
    }else if(_Step == 1){
        //解析json文件
        Log::write("游戏启动","分析Json文件");
        QString _ret = Json::process();
        if(_ret != "OK")return _ret;
        _Step = 2;
    }else if(_Step == 2){
        _args.clear();
        QString _args_cp = Json::get_args_cp();
        QString _args_minecraftArguments = Json::get_args_minecraftArguments();
        _args_minecraftArguments.replace("${auth_access_token}",_accessToken);
        _args_minecraftArguments.replace("${auth_player_name}",_player_name);
        _args_minecraftArguments.replace("${auth_uuid}",_uuid);
        _args_minecraftArguments.replace("${user_type}",_Auth.get_user_type());
        _args_minecraftArguments.replace("${version_type}",_args_versionType);
        //参数处理
        _args.append("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump ");
        _args.append("-Xmx" + QString::number(_args_Xmx) + "M ");
        _args.append("-Xmn" + QString::number(_args_Xmx / 3) + "M ");
        _args.append("-Dfml.ignoreInvalidMinecraftCertificates=true ");
        _args.append("-Dfml.ignorePatchDiscrepancies=true ");
        _args.append(_args_additionArgsJava + " ");//附加Java参数
        _args.append("\"-Djava.library.path=" + Json::get_NativesDirpath() + "\" ");
        _args.append("-cp ");
        _args.append(_args_cp + " ");
        //设置主类
        _args.append("\"" + Json::get_args_mainClass() + "\" ");
        _args.append(_args_minecraftArguments + " ");
        //设置分辨率
        if(_args_fullscreen)_args.append("--fullscreen ");
        else{
            _args.append("--width ");
            _args.append(QString::number(_args_width) + " ");
            _args.append("--height ");
            _args.append(QString::number(_args_height) + " ");
        }
        //设置自动连接
        if(!_args_address.isEmpty()){
            _args.append("--server ");
            _args.append(_args_address + " ");
            _args.append("--port ");
            _args.append(_args_port + " ");
        }
        //附加mc参数
        _args.append(_args_additionArgsMc);
        _Step = 3;
    }else if(_Step == 3){
        if(_args.right(1) == " ")_args = _args.left(_args.length() - 1);
        QString _str;
        for(QString::ConstIterator it = _args.constBegin();it != _args.constEnd();++it){
            if(*it == " "){
                if(!_str.isEmpty()){
                    _args_list.append(_str);
                    _str.clear();
                }
            }else if(*it == "\""){
                ++it;
                while(*it != "\"" && it != _args.constEnd() - 1){
                    _str.append(*it);
                    ++it;
                }
            }else if(*it != " "){
                _str.append(*it);
            }
        }
        _args_list.append(_str);
        Log::write("游戏启动","启动参数: " + _args);
        //设置参数，启动交给主程序
        return "OK";
    }
    return "Continue";
}
