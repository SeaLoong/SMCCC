#include "auth.h"

Auth::Auth(){
}

void Auth::setAuthMethod(int index){
    if(index > 1)index = 0;
    AuthMethod = index;
}

void Auth::set_username(const QString &username){
    _username = username;
}

void Auth::set_password(const QString &password){
    _password = password;
}

void Auth::set_uuid(const QString &uuid){
    _uuid = uuid;
}

void Auth::set_accessToken(const QString &accessToken){
    _accessToken = accessToken;
}

void Auth::set_clientToken(const QString &clientToken){
    _clientToken = clientToken;
}

QString Auth::get_auth_player_name(){
    return _auth_player_name;
}

QString Auth::get_auth_uuid(){
    return _auth_uuid;
}

QString Auth::get_auth_access_token(){
    return _auth_access_token;
}

QString Auth::get_user_type(){
    return _user_type;
}

QString Auth::getError(){
    return Error;
}


bool Auth::auth(){
    if(_username.isEmpty())return false;
    switch (AuthMethod) {
    case 0:
        _auth_player_name = _username;
        _auth_uuid = "00000000000000000000000000000000";
        _auth_access_token = "00000000000000000000000000000000";
        _user_type = "legacy";
        return true;
    case 1:
        Yggdrasil _Yggdrasil;
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
