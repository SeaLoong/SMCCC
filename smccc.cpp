#include "smccc.h"

SMCCC::SMCCC(){}

SMCCC::SMCCC(const QString &version,const QString &dotminecraftdirpath){
    _Json->Version = version,_Json->DotMinecraftDirPath = dotminecraftdirpath;
}

void SMCCC::setAssetsCheck(bool assetscheck){
    _Json->AssetsCheck = assetscheck;
}

void SMCCC::setFileCheck(bool filecheck){
    _Json->FileCheck = filecheck;
}

void SMCCC::setMergeInheritsFrom(bool mergeinheritsfrom){
    _Json->MergeInheritsFrom = mergeinheritsfrom;
}

void SMCCC::setOS(const QString &os){
    _Json->OS = os;
}

void SMCCC::setArch(const QString &arch){
    _Json->Arch = arch;
}

void SMCCC::setVersion(const QString &version){
    _Json->Version = version;
}

void SMCCC::setDotMinecraftDirPath(const QString &dotminecraftdirpath){
    _Json->DotMinecraftDirPath = dotminecraftdirpath;
}

void SMCCC::setAssetsDirPath(const QString &assetsdirpath){
    _Json->AssetsDirPath = assetsdirpath;
}

void SMCCC::setLibrariesDirPath(const QString &librariesdirpath){
    _Json->LibrariesDirPath = librariesdirpath;
}

void SMCCC::setVersionsDirPath(const QString &versiondirpath){
    _Json->VersionsDirPath = versiondirpath;
}

void SMCCC::setNativesDirPath(const QString &nativesdirpath){
    _Json->NativesDirPath = nativesdirpath;
}

void SMCCC::setJarFilePath(const QString &jarfilepath){
    _Json->JarFilePath = jarfilepath;
}

void SMCCC::setAuthMethod(int authmethod){
    _Auth->setAuthMethod(authmethod);
}

void SMCCC::set_username(const QString &username){
    _Auth->set_username(username);
}

void SMCCC::set_password(const QString &password){
    _Auth->set_password(password);
}

void SMCCC::set_accessToken(const QString &accessToken){
    _Auth->set_accessToken(accessToken);
}

void SMCCC::set_clientToken(const QString &clientToken){
    _Auth->set_clientToken(clientToken);
}

void SMCCC::setArgs_AutoConnect(const QString &host, const QString &port){
    _args_host = host;
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

void SMCCC::setArgs_VersionType(const QString &versiontype){
    if(!versiontype.isEmpty())_args_versionType = "\"" + versiontype + "\"";
}

void SMCCC::setArgs_AdditionArgsJava(const QString &additionArgs){
    _args_additionArgsJava = additionArgs;
}

void SMCCC::setArgs_AdditionArgsMc(const QString &additionArgs){
    _args_additionArgsMc = additionArgs;
}

QString SMCCC::getArgsString(){
    return ArgsString;
}

QStringList SMCCC::getArgsStringList(){
    return ArgsStringList;
}

QLinkedList<SMCCCDownloadInfo> SMCCC::getDownloadInfoList(){
    return _Json->DownloadInfoList;
}

QString SMCCC::getAuthError(){
    return _Auth->getError();
}

int SMCCC::processLaunchArgs(){
    if(_Step == 0){
        //解析json文件
        int _ret = _Json->process();
        if(_ret != 0)return _ret;
        _Step = 1;
    }
    if(_Step == 1){
        //登录验证
        if(!_Auth->auth())return 6;
        ArgsString.clear();
        QString _args_minecraftArguments = _Json->_minecraftArguments;
        _args_minecraftArguments.replace("${auth_access_token}",_Auth->get_auth_access_token());
        _args_minecraftArguments.replace("${auth_player_name}",_Auth->get_auth_player_name());
        _args_minecraftArguments.replace("${auth_uuid}",_Auth->get_auth_uuid());
        _args_minecraftArguments.replace("${user_type}",_Auth->get_user_type());
        _args_minecraftArguments.replace("${version_type}",_args_versionType);
        //参数处理
        ArgsString.append("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump ");
        ArgsString.append("-Xmx" + QString::number(_args_Xmx) + "M ");
        ArgsString.append("-Dfml.ignoreInvalidMinecraftCertificates=true ");
        ArgsString.append("-Dfml.ignorePatchDiscrepancies=true ");
        ArgsString.append(_args_additionArgsJava + " ");//附加Java参数
        ArgsString.append("\"-Djava.library.path=" + _Json->NativesDirPath + "\" ");
        ArgsString.append("-cp ");
        ArgsString.append(_Json->_args_cp + " ");
        //设置主类
        ArgsString.append("\"" + _Json->_mainClass + "\" ");
        ArgsString.append(_args_minecraftArguments + " ");
        //设置分辨率
        if(_args_fullscreen)ArgsString.append("--fullscreen ");
        else{
            ArgsString.append("--width ");
            ArgsString.append(QString::number(_args_width) + " ");
            ArgsString.append("--height ");
            ArgsString.append(QString::number(_args_height) + " ");
        }
        //设置自动连接
        if(!_args_host.isEmpty()){
            ArgsString.append("--server ");
            ArgsString.append(_args_host + " ");
            ArgsString.append("--port ");
            ArgsString.append(_args_port + " ");
        }
        //附加mc参数
        ArgsString.append(_args_additionArgsMc);
        //ArgsString转换成ArgsStringList
        ArgsStringList.clear();
        if(ArgsString.right(1) == " ")ArgsString = ArgsString.left(ArgsString.length() - 1);
        QString _str;
        for(QString::ConstIterator it = ArgsString.constBegin();it != ArgsString.constEnd();++it){
            if(*it == " "){
                if(!_str.isEmpty()){
                    ArgsStringList.append(_str);
                    _str.clear();
                }
            }else if(*it == "\""){
                ++it;
                while(*it != "\"" && it != ArgsString.constEnd() - 1){
                    _str.append(*it);
                    ++it;
                }
            }else if(*it != " "){
                _str.append(*it);
            }
        }
        ArgsStringList.append(_str);
        return 0;
    }
    return 7;
}
