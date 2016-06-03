//
// Created by Carrot on 16/6/1.
//

#ifndef FIRSTDEMO_HXLMYSQL_H
#define FIRSTDEMO_HXLMYSQL_H

#include <string>
#include <mysql.h>
using namespace std;

class HXLMysql {
public:
    HXLMysql();
    virtual ~HXLMysql();

    static void test();
    static void test_lastid();
    static void test_fetch_data();
    static void test_fetch_data2();
    static void test_fetch_data3();
    static void test_fetch_data4();

    static void display_row(MYSQL* mysql, MYSQL_ROW sqlrow);
    static void display_header(MYSQL* mysql, MYSQL_RES* result);
public:
    bool connect(string host, string user, string pwd, string db);
    int query(string query);
    my_ulonglong affected_rows();
    void disconnect();
private:
    string _host;
    string _user;
    string _pwd;
    string _dbName;

    MYSQL* _connecter;
};


#endif //FIRSTDEMO_HXLMYSQL_H
