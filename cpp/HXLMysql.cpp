//
// Created by Carrot on 16/6/1.
//

#include "../head/HXLMysql.h"

HXLMysql::HXLMysql() {
    _connecter = NULL;
}

HXLMysql::~HXLMysql() {
    disconnect();
}

bool HXLMysql::connect(string host, string user, string pwd, string db) {
    disconnect();
    _connecter =  mysql_init(NULL);

    bool bRes = false;
    if (_connecter){
       if (mysql_real_connect(_connecter, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), 0, NULL, 0)){
           bRes = true;
           _host = host;
           _user = user;
           _pwd = pwd;
           _dbName = db;
       }
    }
    return bRes;
}

int HXLMysql::query(string query) {
    if (!_connecter)
        return -1;
    return _connecter ? mysql_query(_connecter, query.c_str()) : -1;
}

my_ulonglong HXLMysql::affected_rows() {
    return mysql_affected_rows(_connecter);
}


void HXLMysql::disconnect(){
    if (_connecter)
        mysql_close(_connecter);
    _connecter = NULL;
}