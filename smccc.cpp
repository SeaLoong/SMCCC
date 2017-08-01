#include "smccc.h"

SMCCC::SMCCC(const QString &version,const QString &dotminecraftdirpath){
    _Json.Version = version,_Json.DotMinecraftDirPath = dotminecraftdirpath;
}

void SMCCC::setAssetsCheck(bool assetscheck){
    _Json.AssetsCheck = assetscheck;
}

void SMCCC::setFileCheck(bool filecheck){
    _Json.FileCheck = filecheck;
}

void SMCCC::setMergeInheritsFrom(bool mergeinheritsfrom){
    _Json.MergeInheritsFrom = mergeinheritsfrom;
}

void SMCCC::setOS(const QString &os){
    _Json.OS = os;
}

void SMCCC::setArch(const QString &arch){
    _Json.Arch = arch;
}

void SMCCC::setVersion(const QString &version){
    _Json.Version = version;
}

void SMCCC::setDotMinecraftDirPath(const QString &dotminecraftdirpath){
    _Json.DotMinecraftDirPath = dotminecraftdirpath;
}

void SMCCC::setAssetsDirPath(const QString &assetsdirpath){
    _Json.AssetsDirPath = assetsdirpath;
}

void SMCCC::setLibrariesDirPath(const QString &librariesdirpath){
    _Json.LibrariesDirPath = librariesdirpath;
}

void SMCCC::setVersionsDirPath(const QString &versiondirpath){
    _Json.VersionsDirPath = versiondirpath;
}

void SMCCC::setNativesDirPath(const QString &nativesdirpath){
    _Json.NativesDirPath = nativesdirpath;
}

void SMCCC::setJarFilePath(const QString &jarfilepath){
    _Json.JarFilePath = jarfilepath;
}

void SMCCC::setAuthMethod(int authmethod){
    _Auth.setVeifyIndex(authmethod);
}

void SMCCC::setUsername(const QString &username){
    _Auth.setUsername(username);
}

void SMCCC::setPassword(const QString &password){
    _Auth.setPassword(password);
}

void SMCCC::setUUID(const QString &uuid){
    _Auth.setUUID(uuid);
}

void SMCCC::setAccessToken(const QString &accessToken){
    _Auth.setAccessToken(accessToken);
}

void SMCCC::setArgs_AutoConnect(const QString &address, const QString &port){
    _args_address = address;
    _args_port = port;
}

void SMCCC::setArgs_Xmx(int xmx){
    _args_Xmx = xmx;
}

void SMCCC::setArgs_Resolution(int width, int height, bool fullscreen){
    _args_width = width;
    _args_height = height;
    _args_fullscreen = fullscreen;
}

void SMCCC::setArgs_VersionType(const QString &text){
    if(text.isEmpty())_args_versionType = "ShiyiMCL";
    else _args_versionType = "\"" + text + "\"";
}

void SMCCC::setArgs_AdditionArgsJava(const QString &additionArgs){
    _args_additionArgsJava = additionArgs;
}

void SMCCC::setArgs_AdditionArgsMc(const QString &additionArgs){
    _args_additionArgsMc = additionArgs;
}

void SMCCC::resetLaunch(){
    _Step = 0;
    _Json._Step = 0;
}

QString SMCCC::getAuth_player_name(){
    return _player_name;
}

QString SMCCC::getAuth_uuid(){
    return _uuid;
}

QString SMCCC::getAuth_accessToken(){
    return _accessToken;
}

QLinkedList<SMCCC::DownloadInfo> SMCCC::getDownloadInfoList(){
    return _Json.getDownloadInfoList();
}

//需要启动三次
QString SMCCC::launch(){//返回"OK","AuthFailed","JsonFileNotExist","InheritsfromFileNotExist","LibrariesFileNotExist","Download"
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
        QString _ret = _Json.process();
        if(_ret != "OK")return _ret;
        _Step = 2;
    }else if(_Step == 2){
        _args.clear();
        QString _args_cp = _Json.get_args_cp();
        QString _args_minecraftArguments = _Json.get_args_minecraftArguments();
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
        _args.append("\"-Djava.library.path=" + _Json.get_NativesDirpath() + "\" ");
        _args.append("-cp ");
        _args.append(_args_cp + " ");
        //设置主类
        _args.append("\"" + _Json.get_args_mainClass() + "\" ");
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
