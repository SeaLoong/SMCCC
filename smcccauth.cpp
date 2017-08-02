#include "smcccauth.h"

SMCCCAuth::SMCCCAuth(){}

void SMCCCAuth::setAuthMethod(int index){
    if(index > 1)index = 0;
    AuthMethod = index;
}

void SMCCCAuth::set_username(const QString &username){
    _username = username;
}

void SMCCCAuth::set_password(const QString &password){
    _password = password;
}

void SMCCCAuth::set_accessToken(const QString &accessToken){
    _accessToken = accessToken;
}

void SMCCCAuth::set_clientToken(const QString &clientToken){
    _clientToken = clientToken;
}

QString SMCCCAuth::get_auth_player_name(){
    return _auth_player_name;
}

QString SMCCCAuth::get_auth_uuid(){
    return _auth_uuid;
}

QString SMCCCAuth::get_auth_access_token(){
    return _auth_access_token;
}

QString SMCCCAuth::get_user_type(){
    return _user_type;
}

QString SMCCCAuth::getError(){
    return Error;
}


bool SMCCCAuth::auth(){
    if(_username.isEmpty())return false;
    switch (AuthMethod) {
    case 0:
        _auth_player_name = _username;
        _auth_uuid = "00000000000000000000000000000000";
        _auth_access_token = "00000000000000000000000000000000";
        _user_type = "legacy";
        return true;
    case 1:
        SMCCCYggdrasil _Yggdrasil;
        _Yggdrasil.username = _username;
        _Yggdrasil.password = _password;
        _Yggdrasil.accessToken = _accessToken;
        _Yggdrasil.clientToken = _clientToken;
        if(_accessToken.isEmpty()){
            if(!_Yggdrasil.Authenticate()){
                Error = _Yggdrasil.getError();
                return false;
            }
        }
        if(!_Yggdrasil.Validate())if(!_Yggdrasil.Refresh()){
            Error = _Yggdrasil.getError();
            return false;
        }
        _auth_player_name = _Yggdrasil.name;
        _auth_uuid = _Yggdrasil.uuid;
        _auth_access_token = _Yggdrasil.accessToken;
        _user_type = _Yggdrasil.userType;
        return true;
    }
    return false;
}
